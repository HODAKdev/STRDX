#include "engine.h"
#include "../Vertex.h"
#include "../window/window.h"

static Window* window = Window::GetSingleton();
static Context* context = Context::GetSingleton();

/* A simple example of how to create a rectangle covering the entire screen, which is drawn into a
   texture, and then once again, but this time not into a texture, but into the back buffer. The first
   shader will be for the ocean, and the second one for vignette, where we will combine it with the
   first shader, the ocean. (Yes, I know it's possible to do this in one shader)
*/

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

    context->Create(window->GetClientWidth(), window->GetClientHeight());
    context->SetViewport(window->GetClientWidth(), window->GetClientHeight());
    context->SetPrimitiveTopology(PT_TRIANGLELIST);

    constantBuffer = ConstantBuffer::Create<CB>();
    renderTarget = RenderTarget::Create(window->GetClientWidth(), window->GetClientHeight(), 1);
    samplerState = SamplerState::Create();
    rasterizerState = RasterizerState::Create();
    rasterizerState->Set();

    shader = Shader::Create();
    {
        shader->LoadVertex("data\\shaders\\1\\vertex.hlsl", true);
        shader->LoadPixel("data\\shaders\\1\\pixel.hlsl", true);

        shader->CompileVertex();
        shader->CompilePixel();

        //shader->SaveVertex("data\\shaders\\1\\vertex.bin");
        //shader->SavePixel("data\\shaders\\1\\pixel.bin");

        shader->CreateVertex();
        shader->CreatePixel();
        shader->ReleasePixelBlob();

        shader->AddLayout("POSITION", 0, 3);
        shader->CreateLayout();
        shader->ReleaseVertexBlob();

        std::vector<POS> vertices;
        vertices.push_back(POS(-1.0f, -1.0f, 0.0f));
        vertices.push_back(POS(-1.0f, 1.0f, 0.0f));
        vertices.push_back(POS(1.0f, 1.0f, 0.0f));
        vertices.push_back(POS(1.0f, -1.0f, 0.0f));

        shader->AddIndex(0);
        shader->AddIndex(1);
        shader->AddIndex(2);
        shader->AddIndex(0);
        shader->AddIndex(2);
        shader->AddIndex(3);

        shader->CreateVertexBuffer<POS>(vertices);
        vertices.clear();
        shader->CreateIndexBuffer();
    }

    shader2 = Shader::Create();
    {
        shader2->LoadVertex("data\\shaders\\2\\vertex.hlsl", true);
        shader2->LoadPixel("data\\shaders\\2\\pixel.hlsl", true);

        shader2->CompileVertex();
        shader2->CompilePixel();

        //shader2->SaveVertex("data\\shaders\\2\\vertex.bin");
        //shader2->SavePixel("data\\shaders\\2\\pixel.bin");

        shader2->CreateVertex();
        shader2->CreatePixel();
        shader2->ReleasePixelBlob();

        shader2->AddLayout("POSITION", 0, 3);
        shader2->AddLayout("TEXTURE", 0, 2, 0, 12);
        shader2->CreateLayout();
        shader2->ReleaseVertexBlob();

        std::vector<POSTEX> vertices;
        vertices.push_back(POSTEX(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f));
        vertices.push_back(POSTEX(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f));
        vertices.push_back(POSTEX(1.0f, 1.0f, 0.0f, 1.0f, 0.0f));
        vertices.push_back(POSTEX(1.0f, -1.0f, 0.0f, 1.0f, 1.0f));

        shader2->AddIndex(0);
        shader2->AddIndex(1);
        shader2->AddIndex(2);
        shader2->AddIndex(0);
        shader2->AddIndex(2);
        shader2->AddIndex(3);

        shader2->CreateVertexBuffer<POSTEX>(vertices);
        vertices.clear();
        shader2->CreateIndexBuffer();
    }

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

        Render();
        context->Present(false);
    }
}
void Engine::Release()
{
    window->Hide();
    if (shader) shader->Release();
    if (shader2) shader2->Release();
    if (constantBuffer) constantBuffer->Release();
    if (renderTarget) renderTarget->Release();
    if (samplerState) samplerState->Release();
    if (rasterizerState) rasterizerState->Release();
	window->Release();
}
void Engine::Render()
{
    if (shader)
    {
        renderTarget->Set();
        renderTarget->ClearRenderTarget(0.0f, 0.0f, 0.0f, 0.0f);
        {
            shader->Set<POS>();
            shader->SetPixelConstantBuffer(constantBuffer->Get());

            cb.SetTime(GetTime());
            cb.SetResolution((float)window->GetClientWidth(), (float)window->GetClientHeight());
            constantBuffer->Update<CB>(cb);

            shader->Draw();
        }
        context->UnsetRenderTarget();

        context->SetRenderTarget();
        context->ClearRenderTarget(0.0f, 0.0f, 0.0f, 0.0f);
        {
            shader2->Set<POSTEX>();
            shader2->SetPixelConstantBuffer(constantBuffer->Get());
            shader2->SetPixelShaderResource(renderTarget->Get());
            shader2->SetPixelSampler(samplerState->Get());

            cb.SetTime(GetTime());
            cb.SetResolution((float)window->GetClientWidth(), (float)window->GetClientHeight());
            constantBuffer->Update<CB>(cb);

            shader2->Draw();
            shader2->ReleaseShaderResources();
        }
        context->UnsetRenderTarget();
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