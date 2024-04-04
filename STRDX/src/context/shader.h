#pragma once

#include "d3d/d3d11_shader.h"

class Shader
{
public:
	Shader() : renderer(Renderer::R_NONE), d3d11_shader(nullptr) {}

public:
	static Shader* Create(Renderer renderer);
	bool LoadVertex(const char* filename, bool compile);
	bool CompileVertex();
	bool LoadPixel(const char* filename, bool compile);
	bool CompilePixel();
	bool SaveVertex(const char* filename);
	bool SavePixel(const char* filename);
	bool CreateVertex();
	bool CreatePixel();
	void ReleaseCache();
	void Release();
	bool CreateLayout();
	bool AddLayout(LPCSTR name, UINT index, UINT format, UINT slot = 0, UINT offset = 0);
	void AddIndex(UINT index);
	template <typename T>
	bool CreateVertexBuffer(std::vector<T>& vertices)
	{
		if (renderer == R_DX11)
			if (d3d11_shader)
				if (!d3d11_shader->CreateVertexBuffer<T>(vertices))
					return false;

		return true;
	}
	bool CreateIndexBuffer();
	template <typename T>
	bool Set()
	{
		if (renderer == R_DX11)
			if (d3d11_shader)
				if (!d3d11_shader->Set<T>())
					return false;

		return true;
	}
	bool Draw(UINT vertex_size, UINT index_size = 0, UINT slot_index = 0);
	template <typename T>
	bool CreateConstantBuffer()
	{
		if (renderer == R_DX11)
			if (d3d11_shader)
				if (!d3d11_shader->CreateConstantBuffer<T>())
					return false;

		return true;
	}
	template <typename T>
	bool UpdateConstantBuffer(T& cb)
	{
		if (renderer == R_DX11)
			if (d3d11_shader)
				if (!d3d11_shader->UpdateConstantBuffer<T>(cb))
					return false;

		return true;
	}
	void SetRenderer(Renderer renderer);

private:
	Renderer renderer;
	D3D11_Shader* d3d11_shader;
};