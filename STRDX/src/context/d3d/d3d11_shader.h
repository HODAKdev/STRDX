#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include "d3d11.h"

template<typename T>
using STRDXWRL = Microsoft::WRL::ComPtr<T>;

class D3D11_Shader
{
public:
	D3D11_Shader() : vs_blob(nullptr), ps_blob(nullptr) {}

public:
	static D3D11_Shader* Create();
	bool LoadVertex(const char* filename, bool compile);
	bool CompileVertex();
	bool LoadPixel(const char* filename, bool compile);
	bool CompilePixel();
	bool SaveVertex(const char* filename);
	bool SavePixel(const char* filename);
	bool CreateVertex();
	bool CreatePixel();
	void ReleaseCache();
	bool CreateLayout();
	bool AddLayout(LPCSTR name, UINT index, UINT format, UINT slot = 0, UINT offset = 0);
	void Release();
	void AddIndex(UINT index);
	template <typename T>
	bool CreateVertexBuffer(std::vector<T>& vertices)
	{
		D3D11* d3d11 = D3D11::GetSingleton();

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(T) * (UINT)vertices.size(); // fix
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data();
		if (FAILED(d3d11->GetDevice()->CreateBuffer(&desc, &data, vertex_buffer.GetAddressOf())))
		{
			printf("create vertex buffer failed\n");
			return false;
		}

		return true;
	}
	bool CreateIndexBuffer();
	template <typename T>
	bool CreateConstantBuffer()
	{
		D3D11* d3d11 = D3D11::GetSingleton();

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(T);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		if (FAILED(d3d11->GetDevice()->CreateBuffer(&desc, nullptr, constant_buffer.GetAddressOf())))
		{
			printf("create constant buffer failed\n");
			return false;
		}

		return true;
	}
	template <typename T>
	bool UpdateConstantBuffer(T& cb)
	{
		D3D11* d3d11 = D3D11::GetSingleton();

		if (!constant_buffer)
			return false;

		d3d11->GetDeviceContext()->UpdateSubresource(constant_buffer.Get(), 0, nullptr, &cb, 0, 0);

		return true;
	}
	template <typename T>
	bool Set()
	{
		D3D11* d3d11 = D3D11::GetSingleton();

		if (!vertex_layout)
			return false;

		if (!vertex_buffer)
			return false;

		d3d11->GetDeviceContext()->IASetInputLayout(vertex_layout.Get());

		UINT stride = sizeof(T);
		UINT offset = 0;
		d3d11->GetDeviceContext()->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);

		if (index_buffer)
			d3d11->GetDeviceContext()->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		return true;
	}
	bool Draw(UINT vertex_size, UINT index_size = 0);

private:
	std::vector<unsigned char> vertex_data;
	std::vector<unsigned char> pixel_data;
	ID3DBlob* vs_blob;
	ID3DBlob* ps_blob;
	STRDXWRL<ID3D11VertexShader> vertex_shader;
	STRDXWRL<ID3D11PixelShader> pixel_shader;
	STRDXWRL<ID3D11InputLayout> vertex_layout;
	STRDXWRL<ID3D11Buffer> vertex_buffer;
	STRDXWRL<ID3D11Buffer> index_buffer;
	STRDXWRL<ID3D11Buffer> constant_buffer;
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
	std::vector<UINT> indices;

private:
	bool Read(const char* filename, ID3DBlob** blob);
	bool Read(const char* filename, std::vector<unsigned char>& data);
	bool Write(const char* filename, ID3DBlob* blob);
	bool CompileShader(std::vector<unsigned char>& data, std::string entry_point, std::string profile, ID3DBlob** blob);
};