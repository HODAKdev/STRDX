#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include "d3d11_constant_buffer.h"
#include "d3d11_sampler_state.h"

// settings
#define SHADER_ENTRY_POINT "main"
#define SHADER_VERTEX_VERSION "vs_5_0"
#define SHADER_PIXEL_VERSION "ps_5_0"

class D3D11Shader
{
public:
	D3D11Shader() : vertices_size(0),
		            indices_size(0),
		            sizeOf(0) {}

public:
	static D3D11Shader* Create();
	bool LoadVertex(const char* _Filename, bool _Compile);
	bool LoadPixel(const char* _Filename, bool _Compile);
	bool CompileVertex();
	bool CompilePixel();
	bool SaveVertex(const char* _Filename);
	bool SavePixel(const char* _Filename);
	bool CreateVertex();
	bool CreatePixel();
	template <typename T>
	bool CreateVertexBuffer(std::vector<T>& _Vertices, bool _CpuAccess)
	{
		if (_Vertices.empty())
		{
			printf("vertices data is empty\n");
			return false;
		}

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = _CpuAccess ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		desc.ByteWidth = (sizeof(T) * (UINT)_Vertices.size());
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = _CpuAccess ? D3D11_CPU_ACCESS_WRITE : 0;
		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _Vertices.data();
		if (FAILED(GetDevice()->CreateBuffer(&desc, &data, vertex_buffer.GetAddressOf())))
		{
			printf("create vertex buffer failed\n");
			return false;
		}

		vertices_size = (UINT)_Vertices.size();
		sizeOf = sizeof(T);
		return true;
	}
	void AddIndex(UINT _Index);
	bool CreateIndexBuffer(bool _CpuAccess);
	bool AddLayout(LPCSTR _Name, UINT _Index, UINT _Format, UINT _Slot, UINT _Offset);
	bool CreateLayout();
	bool Set();
	void ReleaseVertex();
	void ReleasePixel();
	void ReleaseLayout();
	void ReleaseVertexBlob();
	void ReleasePixelBlob();
	void Release();
	STRDXWRL<ID3D11Buffer> GetVertexBuffer();
	std::vector<UINT>& GetIndices();
	STRDXWRL<ID3D11Buffer> GetIndexBuffer();
	void SetIndicesSize(UINT _Size);
	void ClearIndices();
	STRDXWRL<ID3D11VertexShader> GetVertexShader();
	STRDXWRL<ID3D11PixelShader> GetPixelShader();
	UINT GetVerticesSize();
	UINT GetIndicesSize();
	STRDXWRL<ID3D11InputLayout> GetVertexLayout();
	UINT GetSizeOf();

private:
	STRDXWRL<ID3D11Device> GetDevice();

private:
	STRDXWRL<ID3DBlob> vs_blob;
	STRDXWRL<ID3DBlob> ps_blob;
	STRDXWRL<ID3D11VertexShader> vertex_shader;
	STRDXWRL<ID3D11PixelShader> pixel_shader;
	STRDXWRL<ID3D11InputLayout> vertex_layout;
	STRDXWRL<ID3D11Buffer> vertex_buffer;
	STRDXWRL<ID3D11Buffer> index_buffer;
	std::vector<uint8_t> vertex_data;
	std::vector<uint8_t> pixel_data;
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
	std::vector<UINT> indices;
	UINT vertices_size;
	UINT indices_size;
	std::string vertexFilename;
	std::string pixelFilename;
	UINT sizeOf;

private:
	bool ReadFromFileToBlob(const char* _Filename, ID3DBlob** _Blob);
	bool ReadFromFileToVector(const char* _Filename, std::vector<uint8_t>& _Data);
	bool Write(const char* _Filename, ID3DBlob* _Blob);
	bool CompileShader(std::vector<uint8_t>& _Data, std::string _EntryPoint, std::string _Profile, ID3DBlob** _Blob);
};
