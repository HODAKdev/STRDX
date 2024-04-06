#include "d3d11_shader.h"
#include <d3dcompiler.h>

static D3D11* d3d11 = D3D11::GetSingleton();

D3D11_Shader* D3D11_Shader::Create()
{
	D3D11_Shader* shader = new D3D11_Shader();
	return shader;
}
bool D3D11_Shader::LoadVertex(const char* filename, bool compile)
{
    if (!compile)
        if (!Read(filename, &vs_blob))
            return false;

    if (!Read(filename, vertex_data))
        return false;

	return true;
}
bool D3D11_Shader::CompileVertex()
{
    if (vertex_data.empty())
    {
        printf("vertex data is empty\n");
        return false;
    }

    if (!CompileShader(vertex_data, "main", "vs_4_0", &vs_blob))
        return false;

    vertex_data.clear();

	return true;
}
bool D3D11_Shader::LoadPixel(const char* filename, bool compile)
{
    if (!compile)
        if (!Read(filename, &ps_blob))
            return false;

    if (!Read(filename, pixel_data))
        return false;

    return true;
}
bool D3D11_Shader::CompilePixel()
{
    if (pixel_data.empty())
    {
        printf("pixel data is empty\n");
        return false;
    }

    if (!CompileShader(pixel_data, "main", "ps_4_0", &ps_blob))
        return false;

    pixel_data.clear();

    return true;
}
bool D3D11_Shader::Read(const char* filename, std::vector<unsigned char>& data)
{
    if (std::string(filename).empty())
    {
        printf("filename is empty\n");
        return false;
    }

	std::FILE* file = std::fopen(filename, "rb");
    if (file)
    {
        // seek file to end
        std::fseek(file, 0, SEEK_END);
        // get size and resize vector
        data.resize(std::ftell(file));
        // rewind file to back
        std::rewind(file);

        // read file
        std::fread(&data[0], 1, data.size(), file);
        // close file
        std::fclose(file);
    }
    else
    {
        printf("file read error\n");
        return false;
    }

    return true;
}
bool D3D11_Shader::CompileShader(std::vector<unsigned char>& data, std::string entry_point, std::string profile, ID3DBlob** blob)
{
    if (data.empty())
    {
        printf("data is empty\n");
        return false;
    }

    if (entry_point.empty())
    {
        printf("entry point is empty\n");
        return false;
    }

    if (profile.empty())
    {
        printf("profile is empty\n");
        return false;
    }

    *blob = nullptr;

    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
    flags |= D3DCOMPILE_DEBUG;
#endif

    const D3D_SHADER_MACRO defines[] =
    {
        "EXAMPLE_DEFINE", "1",
        NULL, NULL
    };

    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    if (FAILED(D3DCompile(data.data(),
                          data.size(),
                          NULL,
                          defines,
                          D3D_COMPILE_STANDARD_FILE_INCLUDE,
                          entry_point.c_str(),
                          profile.c_str(),
                          flags,
                          0,
                          &shaderBlob,
                          &errorBlob)))
    {
        if (errorBlob)
        {
            printf("compile failed\n");
            printf("%s\n", (char*)errorBlob->GetBufferPointer());
            return false;
        }
    }

    *blob = shaderBlob;
    return true;
}
bool D3D11_Shader::SaveVertex(const char* filename)
{
    if (!Write(filename, vs_blob))
        return false;

    return true;
}
bool D3D11_Shader::SavePixel(const char* filename)
{
    if (!Write(filename, ps_blob))
        return false;

    return true;
}
bool D3D11_Shader::Write(const char* filename, ID3DBlob* blob)
{
    if (std::string(filename).empty())
    {
        printf("filename is empty\n");
        return false;
    }

    if (blob == nullptr)
    {
        printf("blob is empty\n");
        return false;
    }

    std::FILE* file = std::fopen(filename, "wb");
    if (file)
    {
        // write file
        std::fwrite(blob->GetBufferPointer(), 1, blob->GetBufferSize(), file);
        // close file
        std::fclose(file);
    }
    else
    {
        printf("file write error\n");
        return false;
    }

    return true;
}
bool D3D11_Shader::CreateVertex()
{
    if (!vs_blob)
    {
        printf("vertex blob is empty\n");
        return false;
    }

    if (FAILED(d3d11->GetDevice()->CreateVertexShader(vs_blob->GetBufferPointer(),
                                                      vs_blob->GetBufferSize(),
                                                      NULL,
                                                      vertex_shader.GetAddressOf())))
    {
        printf("create vertex shader failed\n");
        return false;
    }

    return true;
}
bool D3D11_Shader::CreatePixel()
{
    if (!vs_blob)
    {
        printf("vertex blob is empty\n");
        return false;
    }

    if (FAILED(d3d11->GetDevice()->CreatePixelShader(ps_blob->GetBufferPointer(),
                                                     ps_blob->GetBufferSize(),
                                                     NULL,
                                                     pixel_shader.GetAddressOf())))
    {
        printf("create pixel shader failed\n");
        return false;
    }

    return true;
}
void D3D11_Shader::ReleaseCache()
{
    if (vs_blob) vs_blob->Release();
    if (ps_blob) ps_blob->Release();
}
bool D3D11_Shader::CreateLayout()
{
    if (FAILED(d3d11->GetDevice()->CreateInputLayout(layout.data(),
                                                     (UINT)layout.size(), // fix
                                                     vs_blob->GetBufferPointer(),
                                                     vs_blob->GetBufferSize(),
                                                     vertex_layout.GetAddressOf())))
    {
        printf("create input layout failed\n");
        return false;
    }

    return true;
}
bool D3D11_Shader::AddLayout(LPCSTR name, UINT index, UINT format, UINT slot, UINT offset)
{
    if (strlen(name) == 0)
    {
        printf("name is empty\n");
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.SemanticName = name;
    desc.SemanticIndex = index;

    if (format == 3)
        desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    else if (format == 4)
        desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    else
    {
        printf("format is wrong\n");
        return false;
    }

    desc.InputSlot = slot;
    desc.AlignedByteOffset = offset;
    desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    desc.InstanceDataStepRate = 0;

    layout.push_back(desc);
    return true;
}
void D3D11_Shader::Release()
{
    vertex_data.clear();
    pixel_data.clear();
    if (vertex_shader) vertex_shader->Release();
    if (pixel_shader) pixel_shader->Release();
    if (vertex_layout) vertex_layout->Release();
    if (vertex_buffer) vertex_buffer->Release();
    if (index_buffer) index_buffer->Release();
    if (constant_buffer) constant_buffer->Release();
}
void D3D11_Shader::AddIndex(UINT index)
{
    indices.push_back(index);
}
bool D3D11_Shader::CreateIndexBuffer()
{
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = sizeof(UINT) * (UINT)indices.size(); // fix
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(data));
    data.pSysMem = indices.data();
    if (FAILED(d3d11->GetDevice()->CreateBuffer(&desc, &data, index_buffer.GetAddressOf())))
    {
        printf("create index buffer failed\n");
        return false;
    }

    indices.clear();

    return true;
}
bool D3D11_Shader::Read(const char* filename, ID3DBlob** blob)
{
    if (std::string(filename).empty())
    {
        printf("filename is empty\n");
        return false;
    }

    std::vector<unsigned char> data;
    if (!Read(filename, data))
        return false;

    if (FAILED(D3DCreateBlob(data.size(), blob)))
    {
        printf("create blob failed\n");
        return false;
    }

    std::memcpy((*blob)->GetBufferPointer(), data.data(), data.size());

    data.clear();
    return true;
}
bool D3D11_Shader::Draw(UINT vertex_size, UINT index_size, UINT slot_index)
{
    if (!vertex_shader)
        return false;

    if (!pixel_shader)
        return false;

    d3d11->GetDeviceContext()->VSSetShader(vertex_shader.Get(), NULL, 0);
    if (constant_buffer)
        d3d11->GetDeviceContext()->VSSetConstantBuffers(slot_index, 1, constant_buffer.GetAddressOf());
    d3d11->GetDeviceContext()->PSSetShader(pixel_shader.Get(), NULL, 0);
    if (constant_buffer)
        d3d11->GetDeviceContext()->PSSetConstantBuffers(slot_index, 1, constant_buffer.GetAddressOf());
    if (index_buffer)
        d3d11->GetDeviceContext()->DrawIndexed(index_size, 0, 0); // fix
    else
        d3d11->GetDeviceContext()->Draw(vertex_size, 0); // fix

    return true;
}
