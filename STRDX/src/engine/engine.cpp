#include "engine.h"
#include "../Vertex.h"
#include "../window/window.h"

static Window* window = Window::GetSingleton();
static Context* context = Context::GetSingleton();

Engine* Engine::GetSingleton()
{
	static Engine engine;
	return &engine;
}
void Engine::Start()
{
    window->Create(L"STRDX", 1280, 720, 0, 0, 0, false);
    window->EnableDarkMode();
    window->Center();
    window->Focus();

    context->Create(R_DX11, window->GetClientWidth(), window->GetClientHeight());
    context->SetViewport(window->GetClientWidth(), window->GetClientHeight());
    context->SetPrimitiveTopology(PT_TRIANGLELIST);

    shader = Shader::Create(R_DX11);
    shader->LoadVertex("data\\shaders\\vertex.hlsl", true);
    shader->LoadPixel("data\\shaders\\pixel.hlsl", true);

    shader->CompileVertex();
    shader->CompilePixel();

    //shader->SaveVertex("data\\shaders\\vertex.bin");
    //shader->SavePixel("data\\shaders\\pixel.bin");

    shader->CreateVertex();
    shader->CreatePixel();
    shader->ReleasePixelBlob();

    shader->AddLayout("POSITION", 0, 3);
    shader->CreateLayout();
    shader->ReleaseVertexBlob();

    std::vector<Vertex> vertices;
    vertices.push_back(Vertex(-1.0f, -1.0f, 0.0f));
    vertices.push_back(Vertex(-1.0f, 1.0f, 0.0f));
    vertices.push_back(Vertex(1.0f, 1.0f, 0.0f));
    vertices.push_back(Vertex(1.0f, -1.0f, 0.0f));

    shader->AddIndex(0);
    shader->AddIndex(1);
    shader->AddIndex(2);
    shader->AddIndex(0);
    shader->AddIndex(2);
    shader->AddIndex(3);

    shader->CreateVertexBuffer<Vertex>(vertices);
    vertices.clear();
    shader->CreateIndexBuffer();
    shader->CreateConstantBuffer<ConstantBuffer>();

    window->Show();
}
void Engine::Update()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        context->SetRenderTarget();
        context->ClearRenderTarget(0.0f, 0.0f, 0.0f, 1.0f);
        Render();
        context->Present(false);
    }
}
void Engine::Release()
{
    window->Hide();
    if (shader) shader->Release();
	window->Release();
}
void Engine::Render()
{
    if (shader)
    {
        shader->Set<Vertex>();
        constantBuffer.SetTime(GetTime());
        constantBuffer.SetResolution((float)window->GetClientWidth(), (float)window->GetClientHeight());
        shader->UpdateConstantBuffer<ConstantBuffer>(constantBuffer);
        shader->Draw();
    }
}
float Engine::GetTime()
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER currentTime;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&currentTime);
    return float(currentTime.QuadPart) / float(frequency.QuadPart);
}
UINT Engine::GetScreenWidth()
{
    return GetSystemMetrics(SM_CXSCREEN);
}
UINT Engine::GetScreenHeight()
{
    return GetSystemMetrics(SM_CYSCREEN);
}
void Engine::ShowCursor()
{
    ::ShowCursor(TRUE);
}
void Engine::HideCursor()
{
    ::ShowCursor(FALSE);
}
void Engine::SetCursorPos(UINT x, UINT y)
{
    ::SetCursorPos(x, y);
}