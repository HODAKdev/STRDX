#include "d3d11_shader.h"
#include <d3dcompiler.h>

static D3D11Context* context = D3D11Context::GetSingleton();

D3D11Shader* D3D11Shader::Create()
{
    D3D11Shader* shader = new D3D11Shader();
	return shader;
}
bool D3D11Shader::LoadVertex(const char* _Filename, bool _Compile)
{
    if (!_Compile)
        if (!ReadFromFileToBlob(_Filename, &vs_blob))
            return false;

    if (!ReadFromFileToVector(_Filename, vertex_data))
        return false;

    vertexFilename = _Filename;

    vs_blob_used = true;
	return true;
}
bool D3D11Shader::LoadPixel(const char* _Filename, bool _Compile)
{
    if (!_Compile)
        if (!ReadFromFileToBlob(_Filename, &ps_blob))
            return false;

    if (!ReadFromFileToVector(_Filename, pixel_data))
        return false;

    pixelFilename = _Filename;

    ps_blob_used = true;
    return true;
}
bool D3D11Shader::CompileVertex()
{
    if (vertex_data.empty())
    {
        printf("vertex data is empty\n");
        return false;
    }

    if (!CompileShader(vertex_data, SHADER_ENTRY_POINT, SHADER_VERTEX_VERSION, &vs_blob))
    {
        printf("filename of vertex shader %s\n", vertexFilename.c_str());
        return false;
    }

    vertex_data.clear();
	return true;
}
bool D3D11Shader::CompilePixel()
{
    if (pixel_data.empty())
    {
        printf("pixel data is empty\n");
        return false;
    }

    if (!CompileShader(pixel_data, SHADER_ENTRY_POINT, SHADER_PIXEL_VERSION, &ps_blob))
    {
        printf("filename of pixel shader %s\n", pixelFilename.c_str());
        return false;
    }

    pixel_data.clear();
    return true;
}
bool D3D11Shader::SaveVertex(const char* _Filename)
{
    if (!Write(_Filename, vs_blob.Get()))
        return false;

    return true;
}
bool D3D11Shader::SavePixel(const char* _Filename)
{
    if (!Write(_Filename, ps_blob.Get()))
        return false;

    return true;
}
bool D3D11Shader::CreateVertex()
{
    if (!vs_blob)
    {
        printf("vertex blob is empty\n");
        return false;
    }

    if (FAILED(context->GetDevice()->CreateVertexShader(vs_blob->GetBufferPointer(),
                                                        vs_blob->GetBufferSize(),
                                                        NULL,
                                                        vertex_shader.GetAddressOf())))
    {
        printf("create vertex shader failed\n");
        return false;
    }

    return true;
}
bool D3D11Shader::CreatePixel()
{
    if (!ps_blob)
    {
        printf("pixel blob is empty\n");
        return false;
    }

    if (FAILED(context->GetDevice()->CreatePixelShader(ps_blob->GetBufferPointer(),
                                                       ps_blob->GetBufferSize(),
                                                       NULL,
                                                       pixel_shader.GetAddressOf())))
    {
        printf("create pixel shader failed\n");
        return false;
    }

    return true;
}
void D3D11Shader::AddIndex(UINT _Index)
{
    indices.push_back(_Index);
}
bool D3D11Shader::CreateIndexBuffer(bool _CpuAccess)
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
    if (FAILED(context->GetDevice()->CreateBuffer(&desc, &data, index_buffer.GetAddressOf())))
    {
        printf("create index buffer failed\n");
        return false;
    }

    indices_size = (UINT)indices.size();
    indices.clear();
    return true;
}
bool D3D11Shader::UpdateIndexBuffer()
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
    if (FAILED(context->GetDeviceContext()->Map(index_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
        return false;

    memcpy(resource.pData, indices.data(), (sizeof(UINT) * (UINT)indices.size()));
    context->GetDeviceContext()->Unmap(index_buffer.Get(), 0);

    indices_size = (UINT)indices.size();
    indices.clear();
    return true;
}
bool D3D11Shader::AddLayout(LPCSTR _Name, UINT _Index, UINT _Format, UINT _Slot, UINT _Offset)
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
    else if (_Format == 2)
        desc.Format = DXGI_FORMAT_R32G32_FLOAT;
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
bool D3D11Shader::CreateLayout()
{
    if (FAILED(context->GetDevice()->CreateInputLayout(layout.data(),
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
bool D3D11Shader::Draw()
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

    if (index_buffer) context->GetDeviceContext()->DrawIndexed(indices_size, 0, 0);
    else context->GetDeviceContext()->Draw(vertices_size, 0);

    return true;
}
void D3D11Shader::ReleaseVertex()
{
    if (vertex_shader) vertex_shader->Release();
}
void D3D11Shader::ReleasePixel()
{
    if (pixel_shader) pixel_shader->Release();
}
void D3D11Shader::ReleaseLayout()
{
    if (vertex_layout) vertex_layout->Release();
}
void D3D11Shader::ReleaseVertexBlob()
{
    if (vs_blob_used) vs_blob->Release();
    vs_blob_used = false;
}
void D3D11Shader::ReleasePixelBlob()
{
    if (ps_blob_used) ps_blob->Release();
    ps_blob_used = false;
}
void D3D11Shader::Release()
{
    // pointers
    if (vs_blob_used) vs_blob->Release();
    if (ps_blob_used) ps_blob->Release();
    if (vertex_shader) vertex_shader->Release();
    if (pixel_shader) pixel_shader->Release();
    if (vertex_layout) vertex_layout->Release();
    if (vertex_buffer) vertex_buffer->Release();
    if (index_buffer) index_buffer->Release();

    // vectors
    vertex_data.clear();
    pixel_data.clear();
    layout.clear();
    indices.clear();

    // bools
    vs_blob_used = false;
    ps_blob_used = false;

    // uints
    vertices_size = 0;
    indices_size = 0;

    // strings
    vertexFilename = "";
    pixelFilename = "";
}
bool D3D11Shader::SetVertexConstantBuffer(D3D11ConstantBuffer* _ConstantBuffer, UINT _Slot)
{
    if (!_ConstantBuffer)
    {
        printf("vertex constant buffer is null\n");
        return false;
    }

    context->GetDeviceContext()->VSSetConstantBuffers(_Slot, 1, _ConstantBuffer->Get().GetAddressOf());
    return true;
}
bool D3D11Shader::SetPixelConstantBuffer(D3D11ConstantBuffer* _ConstantBuffer, UINT _Slot)
{
    if (!_ConstantBuffer)
    {
        printf("pixel constant buffer is null\n");
        return false;
    }

    context->GetDeviceContext()->PSSetConstantBuffers(_Slot, 1, _ConstantBuffer->Get().GetAddressOf());
    return true;
}
bool D3D11Shader::SetVertexShaderResource(ID3D11ShaderResourceView* _ShaderResource, UINT _Slot)
{
    if (!_ShaderResource)
    {
        printf("vertex shader resource is null\n");
        return false;
    }

    context->GetDeviceContext()->VSSetShaderResources(_Slot, 1, &_ShaderResource);
    return true;
}
bool D3D11Shader::SetPixelShaderResource(ID3D11ShaderResourceView* _ShaderResource, UINT _Slot)
{
    if (!_ShaderResource)
    {
        printf("pixel shader resource is null\n");
        return false;
    }

    context->GetDeviceContext()->PSSetShaderResources(_Slot, 1, &_ShaderResource);
    return true;
}
bool D3D11Shader::SetVertexSampler(D3D11SamplerState* _SamplerState, UINT _Slot)
{
    if (!_SamplerState)
    {
        printf("vertex sampler state is null\n");
        return false;
    }

    context->GetDeviceContext()->VSSetSamplers(_Slot, 1, _SamplerState->Get().GetAddressOf());
    return true;
}
bool D3D11Shader::SetPixelSampler(D3D11SamplerState* _SamplerState, UINT _Slot)
{
    if (!_SamplerState)
    {
        printf("vertex sampler state is null\n");
        return false;
    }

    context->GetDeviceContext()->PSSetSamplers(_Slot, 1, _SamplerState->Get().GetAddressOf());
    return true;
}
void D3D11Shader::ReleaseShaderResources(UINT _Slot)
{
    ID3D11ShaderResourceView* shaderResourceView = NULL;
    context->GetDeviceContext()->VSSetShaderResources(_Slot, 1, &shaderResourceView);
    context->GetDeviceContext()->PSSetShaderResources(_Slot, 1, &shaderResourceView);
}
bool D3D11Shader::ReadFromFileToBlob(const char* _Filename, ID3DBlob** _Blob)
{
    if (std::string(_Filename).empty())
    {
        printf("filename is empty\n");
        return false;
    }

    std::vector<unsigned char> data;
    if (!ReadFromFileToVector(_Filename, data))
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
bool D3D11Shader::ReadFromFileToVector(const char* _Filename, std::vector<uint8_t>& _Data)
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
bool D3D11Shader::Write(const char* _Filename, ID3DBlob* _Blob)
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
bool D3D11Shader::CompileShader(std::vector<uint8_t>& _Data, std::string _EntryPoint, std::string _Profile, ID3DBlob** _Blob)
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
