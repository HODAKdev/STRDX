# STRDX
![](strdx.png)
Simple DirectX 11. Add new context implementation without modify main code base.
## Features
- Vertex, Pixel Shaders
- Constant Buffers
- Render Targets
- Sampler States
- Rasterizer States
- Anti-aliasing, Multisampling
## C++ API
```cpp
void Start()
{
    UINT width = GetWidth();
    UINT height = GetWidth();
    context->Create(width, height);
    context->SetViewport(width, height);
    context->SetPrimitiveTopology(PT_TRIANGLELIST);

    // create shader
    shader = Shader::Create();
    constantBuffer = ConstantBuffer::Create<CB>();

    // load shaders
    shader->LoadVertex("vertex.hlsl", true);
    shader->LoadPixel("pixel.hlsl", true);

    // compile shaders
    shader->CompileVertex();
    shader->CompilePixel();

    // save shaders
    shader->SaveVertex("vertex.bin");
    shader->SavePixel("pixel.bin");

    // create shaders
    shader->CreateVertex();
    shader->CreatePixel();

    shader->AddLayout("POSITION", 0, 3);
    shader->CreateLayout();

    // x, y, z coords
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
    shader->CreateIndexBuffer();
}

void Render()
{
    if (shader)
    {
        shader->Set<Vertex>();
        shader->SetPixelConstantBuffer(constantBuffer->Get());

        cb.SetTime(GetTime());
        cb.SetResolution(GetWidth(), GetHeight());
        constantBuffer->Update<CB>(cb);

        shader->Draw();
    }
}

void Release()
{
    if (shader) shader->Release();
    if (constantBuffer) constantBuffer->Release();
}
```
## Build
- Visual Studio 2022
- Platform Toolset: v143
- C++ Language Standard: C++ 2014
- Configuration: Debug or Release
- Platform: x64
## Credits
https://shadered.org/ \
https://www.shadertoy.com/view/lsKSWR \
https://www.shadertoy.com/view/NlKGWK
## License
STRDX is licensed under the Apache 2.0 License, see [LICENSE](/LICENSE) for more information.
