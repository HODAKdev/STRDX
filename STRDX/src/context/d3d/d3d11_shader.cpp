#include "d3d11_shader.h"
#include <d3dcompiler.h>
#include "d3d11_context.h"

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
void D3D11Shader::ReleaseVertex()
{
    STRDXWRL_RESET(vertex_shader);
}
void D3D11Shader::ReleasePixel()
{
    STRDXWRL_RESET(pixel_shader);
}
void D3D11Shader::ReleaseLayout()
{
    STRDXWRL_RESET(vertex_layout);
}
void D3D11Shader::ReleaseVertexBlob()
{
    STRDXWRL_RESET(vs_blob);
}
void D3D11Shader::ReleasePixelBlob()
{
    STRDXWRL_RESET(ps_blob);
}
void D3D11Shader::Release()
{
    STRDXWRL_RESET(vertex_shader);
    STRDXWRL_RESET(pixel_shader);
    STRDXWRL_RESET(vertex_layout);
    STRDXWRL_RESET(vertex_buffer);
    STRDXWRL_RESET(index_buffer);
    STRDXWRL_RESET(vs_blob);
    STRDXWRL_RESET(ps_blob);

    vertex_data.clear();
    pixel_data.clear();
    layout.clear();
    indices.clear();

    vertices_size = 0;
    indices_size = 0;

    vertexFilename = "";
    pixelFilename = "";

    delete this;
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
STRDXWRL<ID3D11Device> D3D11Shader::GetDevice()
{
    return context->GetDevice();
}
STRDXWRL<ID3D11Buffer> D3D11Shader::GetVertexBuffer()
{
    return vertex_buffer;
}
std::vector<UINT>& D3D11Shader::GetIndices()
{
    return indices;
}
STRDXWRL<ID3D11Buffer> D3D11Shader::GetIndexBuffer()
{
    return index_buffer;
}
void D3D11Shader::SetIndicesSize(UINT _Size)
{
    indices_size = _Size;
}
void D3D11Shader::ClearIndices()
{
    indices.clear();
}
STRDXWRL<ID3D11VertexShader> D3D11Shader::GetVertexShader()
{
    return vertex_shader;
}
STRDXWRL<ID3D11PixelShader> D3D11Shader::GetPixelShader()
{
    return pixel_shader;
}
UINT D3D11Shader::GetVerticesSize()
{
    return vertices_size;
}
UINT D3D11Shader::GetIndicesSize()
{
    return indices_size;
}
STRDXWRL<ID3D11InputLayout> D3D11Shader::GetVertexLayout()
{
    return vertex_layout;
}
UINT D3D11Shader::GetSizeOf()
{
    return sizeOf;
}