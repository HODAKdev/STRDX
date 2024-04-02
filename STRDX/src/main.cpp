#include <Windows.h>
#include "engine/engine.h"

static Engine* engine = Engine::GetSingleton();

#if defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR lpCmdLine,
                   int nCmdShow)
#endif
{
    engine->Start();
    engine->Update();
    engine->Release();
    return 0;
}