#include "d3d11_shader.h"
#include <d3dcompiler.h>

static D3D11* d3d11 = D3D11::GetSingleton();

D3D11_Shader* D3D11_Shader::Create()
{
	D3D11_Shader* shader = new D3D11_Shader();
	return shader;
}
bool D3D11_Shader::LoadVertex(const char* _Filename, bool _Compile)
{
    if (!_Compile)
        if (!Read(_Filename, &vs_blob))
            return false;

    if (!Read(_Filename, vertex_data))
        return false;

    vs_blob_used = true;
	return true;
}
bool D3D11_Shader::LoadPixel(const char* _Filename, bool _Compile)
{
    if (!_Compile)
        if (!Read(_Filename, &ps_blob))
            return false;

    if (!Read(_Filename, pixel_data))
        return false;

    ps_blob_used = true;
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
bool D3D11_Shader::SaveVertex(const char* _Filename)
{
    if (!Write(_Filename, vs_blob))
        return false;

    return true;
}
bool D3D11_Shader::SavePixel(const char* _Filename)
{
    if (!Write(_Filename, ps_blob))
        return false;

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
    if (!ps_blob)
    {
        printf("pixel blob is empty\n");
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
void D3D11_Shader::AddIndex(UINT _Index)
{
    indices.push_back(_Index);
}
bool D3D11_Shader::CreateIndexBuffer(bool _CpuAccess)
{
    if (indices.empty())
    {
        printf("indices data is empty\n");
        return false;
    }

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = _CpuAccess ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
    desc.ByteWidth = (sizeof(UINT) * (UINT)indices.size());
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.CPUAccessFlags = _CpuAccess ? D3D11_CPU_ACCESS_WRITE : 0;
    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(data));
    data.pSysMem = indices.data();
    if (FAILED(d3d11->GetDevice()->CreateBuffer(&desc, &data, index_buffer.GetAddressOf())))
    {
        printf("create index buffer failed\n");
        return false;
    }

    indices_size = (UINT)indices.size();
    indices.clear();
    return true;
}
bool D3D11_Shader::UpdateIndexBuffer()
{
    if (indices.empty())
    {
        printf("indices data is empty\n");
        return false;
    }

    if (!index_buffer)
    {
        printf("index buffer is null\n");
        return false;
    }

    D3D11_MAPPED_SUBRESOURCE resource;
    if (FAILED(d3d11->GetDeviceContext()->Map(index_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
        return false;

    memcpy(resource.pData, indices.data(), (sizeof(UINT) * (UINT)indices.size()));
    d3d11->GetDeviceContext()->Unmap(index_buffer.Get(), 0);

    indices_size = (UINT)indices.size();
    indices.clear();
    return true;
}
bool D3D11_Shader::AddLayout(LPCSTR _Name, UINT _Index, UINT _Format, UINT _Slot, UINT _Offset)
{
    if (strlen(_Name) == 0)
    {
        printf("name is empty\n");
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.SemanticName = _Name;
    desc.SemanticIndex = _Index;

    if (_Format == 3)
        desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    else if (_Format == 4)
        desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    else
    {
        printf("format is wrong\n");
        return false;
    }

    desc.InputSlot = _Slot;
    desc.AlignedByteOffset = _Offset;
    desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    desc.InstanceDataStepRate = 0;

    layout.push_back(desc);
    return true;
}
bool D3D11_Shader::CreateLayout()
{
    if (FAILED(d3d11->GetDevice()->CreateInputLayout(layout.data(),
                                                     (UINT)layout.size(),
                                                     vs_blob->GetBufferPointer(),
                                                     vs_blob->GetBufferSize(),
                                                     vertex_layout.GetAddressOf())))
    {
        printf("create input layout failed\n");
        return false;
    }

    layout.clear();
    return true;
}
bool D3D11_Shader::Draw(UINT _ConstantBufferSlot)
{
    if (!vertex_shader)
    {
        printf("vertex shader is null\n");
        return false;
    }

    if (!pixel_shader)
    {
        printf("pixel shader is null\n");
        return false;
    }

    d3d11->GetDeviceContext()->VSSetShader(vertex_shader.Get(), NULL, 0);
    if (constant_buffer)
        d3d11->GetDeviceContext()->VSSetConstantBuffers(_ConstantBufferSlot, 1, constant_buffer.GetAddressOf());
    d3d11->GetDeviceContext()->PSSetShader(pixel_shader.Get(), NULL, 0);
    if (constant_buffer)
        d3d11->GetDeviceContext()->PSSetConstantBuffers(_ConstantBufferSlot, 1, constant_buffer.GetAddressOf());
    if (index_buffer)
        d3d11->GetDeviceContext()->DrawIndexed(indices_size, 0, 0);
    else
        d3d11->GetDeviceContext()->Draw(vertices_size, 0);

    return true;
}
void D3D11_Shader::ReleaseVertex()
{
    if (vertex_shader) vertex_shader->Release();
}
void D3D11_Shader::ReleasePixel()
{
    if (pixel_shader) pixel_shader->Release();
}
void D3D11_Shader::ReleaseLayout()
{
    if (vertex_layout) vertex_layout->Release();
}
void D3D11_Shader::ReleaseVertexBlob()
{
    if (vs_blob_used) vs_blob->Release();
    vs_blob_used = false;
}
void D3D11_Shader::ReleasePixelBlob()
{
    if (ps_blob_used) ps_blob->Release();
    ps_blob_used = false;
}
void D3D11_Shader::Release()
{
    vertex_data.clear();
    pixel_data.clear();
    if (vs_blob_used) vs_blob->Release();
    vs_blob_used = false;
    if (ps_blob_used) ps_blob->Release();
    ps_blob_used = false;
    if (vertex_shader) vertex_shader->Release();
    if (pixel_shader) pixel_shader->Release();
    if (vertex_layout) vertex_layout->Release();
    if (vertex_buffer) vertex_buffer->Release();
    if (index_buffer) index_buffer->Release();
    if (constant_buffer) constant_buffer->Release();
    vertices_size = 0;
    indices_size = 0;
}
bool D3D11_Shader::Read(const char* _Filename, ID3DBlob** _Blob)
{
    if (std::string(_Filename).empty())
    {
        printf("filename is empty\n");
        return false;
    }

    std::vector<unsigned char> data;
    if (!Read(_Filename, data))
        return false;

    if (FAILED(D3DCreateBlob(data.size(), _Blob)))
    {
        printf("create blob failed\n");
        return false;
    }

    memcpy((*_Blob)->GetBufferPointer(), data.data(), data.size());

    data.clear();
    return true;
}
bool D3D11_Shader::Read(const char* _Filename, std::vector<unsigned char>& _Data)
{
    if (std::string(_Filename).empty())
    {
        printf("filename is empty\n");
        return false;
    }

	std::FILE* file = std::fopen(_Filename, "rb");
    if (file)
    {
        std::fseek(file, 0, SEEK_END);
        _Data.resize(std::ftell(file));
        std::rewind(file);

        std::fread(&_Data[0], 1, _Data.size(), file);
        std::fclose(file);
    }
    else
    {
        printf("file read failed\n");
        return false;
    }

    return true;
}
bool D3D11_Shader::Write(const char* _Filename, ID3DBlob* _Blob)
{
    if (std::string(_Filename).empty())
    {
        printf("filename is empty\n");
        return false;
    }

    if (!_Blob)
    {
        printf("blob is null\n");
        return false;
    }

    std::FILE* file = std::fopen(_Filename, "wb");
    if (file)
    {
        std::fwrite(_Blob->GetBufferPointer(), 1, _Blob->GetBufferSize(), file);
        std::fclose(file);
    }
    else
    {
        printf("file write failed\n");
        return false;
    }

    return true;
}
bool D3D11_Shader::CompileShader(std::vector<unsigned char>& _Data, std::string _EntryPoint, std::string _Profile, ID3DBlob** _Blob)
{
    if (_Data.empty())
    {
        printf("data is empty\n");
        return false;
    }

    if (_EntryPoint.empty())
    {
        printf("entry point is empty\n");
        return false;
    }

    if (_Profile.empty())
    {
        printf("profile is empty\n");
        return false;
    }

    *_Blob = NULL;

    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
    flags |= D3DCOMPILE_DEBUG;
#endif

    const D3D_SHADER_MACRO defines[] =
    {
        "EXAMPLE_DEFINE", "1",
        NULL, NULL
    };

    ID3DBlob* shaderBlob = NULL;
    ID3DBlob* errorBlob = NULL;
    if (FAILED(D3DCompile(_Data.data(),
                          _Data.size(),
                          NULL,
                          defines,
                          D3D_COMPILE_STANDARD_FILE_INCLUDE,
                          _EntryPoint.c_str(),
                          _Profile.c_str(),
                          flags,
                          0,
                          &shaderBlob,
                          &errorBlob)))
    {
        if (errorBlob)
        {
            printf("compile shader failed\n");
            printf("%s\n", (char*)errorBlob->GetBufferPointer());
            return false;
        }
    }

    *_Blob = shaderBlob;
    return true;
}