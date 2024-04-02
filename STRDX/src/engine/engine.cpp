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
    // create window
    window->Create(L"STRDX", // name
        1280, 720, // width, height
        0, 0, 0, // rgb
        false); // enable resize

    // enable darkmode window
    window->EnableDarkMode();

    // center window
    window->Center();

    // focus window
    window->Focus();

    // create context
    context->Create(R_DX11, window->GetClientWidth(), window->GetClientHeight());

    // set viewport
    context->SetViewport(window->GetClientWidth(), window->GetClientHeight());

    // set primitive topology
    context->SetPrimitiveTopology(PT_TRIANGLELIST);

    shader = Shader::Create(R_DX11);
    shader->LoadVertex("data\\shaders\\vertex.bin", false);
    shader->LoadPixel("data\\shaders\\pixel.bin", false);
    //shader->CompileVertex();
    //shader->CompilePixel();

    //shader->SaveVertex("data\\shaders\\vertex.bin");
    //shader->SavePixel("data\\shaders\\pixel.bin");

    shader->CreateVertex();
    shader->CreatePixel();

    shader->AddLayout("POSITION", 0, 3);
    shader->CreateLayout();
    shader->ReleaseCache();

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
    vertices.clear(); // free memory
    shader->CreateIndexBuffer();
    shader->CreateConstantBuffer<ConstantBuffer>();

    // show window
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

        // set render target (for new flip model)
        context->SetRenderTarget();

        // clear buffer
        context->ClearRenderTarget(0.0f, 0.0f, 0.0f, 1.0f);

        // render scene to buffer
        Render();

        // send buffer to screen
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
        cb.iTime = GetTime();
        cb.iResolution = DirectX::XMFLOAT2((float)window->GetClientWidth(), (float)window->GetClientHeight());
        shader->UpdateConstantBuffer<ConstantBuffer>(cb);
        shader->Draw(4, 6);
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