#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include "d3d11.h"
#include "d3d11_constant_buffer.h"

#define SHADER_ENTRY_POINT "main"
#define SHADER_VERTEX_VERSION "vs_5_0"
#define SHADER_PIXEL_VERSION "ps_5_0"

template<typename T>
using STRDXWRL = Microsoft::WRL::ComPtr<T>;

class D3D11Shader
{
public:
	D3D11Shader() : vs_blob(NULL),
		            ps_blob(NULL),
		            vertices_size(0),
		            indices_size(0),
		            vs_blob_used(false),
		            ps_blob_used(false) {}

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
		if (FAILED(D3D11::GetSingleton()->GetDevice()->CreateBuffer(&desc, &data, vertex_buffer.GetAddressOf())))
		{
			printf("create vertex buffer failed\n");
			return false;
		}

		vertices_size = (UINT)_Vertices.size();
		return true;
	}
	template <typename T>
	bool UpdateVertexBuffer(std::vector<T>& _Vertices)
	{
		if (_Vertices.empty())
		{
			printf("vertices data is empty\n");
			return false;
		}

		if (!vertex_buffer)
		{
			printf("vertex buffer is null\n");
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE resource;
		if (FAILED(D3D11::GetSingleton()->GetDeviceContext()->Map(vertex_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
			return false;

		memcpy(resource.pData, _Vertices.data(), (sizeof(T) * _Vertices.size()));
		D3D11::GetSingleton()->GetDeviceContext()->Unmap(vertex_buffer.Get(), 0);

		return true;
	}
	void AddIndex(UINT _Index);
	bool CreateIndexBuffer(bool _CpuAccess);
	bool UpdateIndexBuffer();
	bool AddLayout(LPCSTR _Name, UINT _Index, UINT _Format, UINT _Slot, UINT _Offset);
	bool CreateLayout();
	template <typename T>
	bool Set()
	{
		if (!vertex_layout)
		{
			printf("vertex layout is null\n");
			return false;
		}

		if (!vertex_buffer)
		{
			printf("vertex buffer is null\n");
			return false;
		}

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

		D3D11::GetSingleton()->GetDeviceContext()->IASetInputLayout(vertex_layout.Get());

		UINT stride = sizeof(T);
		UINT offset = 0;
		D3D11::GetSingleton()->GetDeviceContext()->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);

		if (index_buffer)
			D3D11::GetSingleton()->GetDeviceContext()->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		D3D11::GetSingleton()->GetDeviceContext()->VSSetShader(vertex_shader.Get(), NULL, 0);
		D3D11::GetSingleton()->GetDeviceContext()->PSSetShader(pixel_shader.Get(), NULL, 0);

		return true;
	}
	bool Draw();
	void ReleaseVertex();
	void ReleasePixel();
	void ReleaseLayout();
	void ReleaseVertexBlob();
	void ReleasePixelBlob();
	void Release();
	bool SetVertexConstantBuffer(ID3D11Buffer* _ConstantBuffer, UINT _Slot);
	bool SetPixelConstantBuffer(ID3D11Buffer* _ConstantBuffer, UINT _Slot);
	bool SetVertexShaderResource(ID3D11ShaderResourceView* _ShaderResource, UINT _Slot);
	bool SetPixelShaderResource(ID3D11ShaderResourceView* _ShaderResource, UINT _Slot);
	bool SetVertexSampler(ID3D11SamplerState* _SamplerState, UINT _Slot);
	bool SetPixelSampler(ID3D11SamplerState* _SamplerState, UINT _Slot);
	void ReleaseShaderResources(UINT _Slot);

private:
	bool vs_blob_used;
	bool ps_blob_used;
	ID3DBlob* vs_blob;
	ID3DBlob* ps_blob;

	STRDXWRL<ID3D11VertexShader> vertex_shader;
	STRDXWRL<ID3D11PixelShader> pixel_shader;
	STRDXWRL<ID3D11InputLayout> vertex_layout;
	STRDXWRL<ID3D11Buffer> vertex_buffer;
	STRDXWRL<ID3D11Buffer> index_buffer;
	STRDXWRL<ID3D11Buffer> constant_buffer;

	std::vector<uint8_t> vertex_data;
	std::vector<uint8_t> pixel_data;
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
	std::vector<UINT> indices;

	UINT vertices_size;
	UINT indices_size;

	std::string vertexFilename;
	std::string pixelFilename;

private:
	bool Read(const char* _Filename, ID3DBlob** _Blob);
	bool Read(const char* _Filename, std::vector<uint8_t>& _Data);
	bool Write(const char* _Filename, ID3DBlob* _Blob);
	bool CompileShader(std::vector<uint8_t>& _Data, std::string _EntryPoint, std::string _Profile, ID3DBlob** _Blob);
};