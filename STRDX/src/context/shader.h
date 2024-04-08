#pragma once

#include "d3d/d3d11_shader.h"

class Shader
{
public:
	Shader() : renderer(Renderer::R_NONE), d3d11_shader(nullptr) {}

public:
	static Shader* Create(Renderer _Renderer);
	bool LoadVertex(const char* _Filename, bool _Compile);
	bool LoadPixel(const char* _Filename, bool _Compile);
	bool CompileVertex();
	bool CompilePixel();
	bool SaveVertex(const char* _Filename);
	bool SavePixel(const char* _Filename);
	bool CreateVertex();
	bool CreatePixel();
	template <typename T>
	bool CreateVertexBuffer(std::vector<T>& _Vertices, bool _CpuAccess = false)
	{
		if (renderer == R_DX11)
			if (d3d11_shader)
				if (!d3d11_shader->CreateVertexBuffer<T>(_Vertices, _CpuAccess))
					return false;

		return true;
	}
	template <typename T>
	bool UpdateVertexBuffer(std::vector<T>& _Vertices)
	{
		if (renderer == R_DX11)
			if (d3d11_shader)
				if (!d3d11_shader->UpdateVertexBuffer<T>(_Vertices))
					return false;

		return true;
	}
	void AddIndex(UINT _Index);
	bool CreateIndexBuffer(bool _CpuAccess = false);
	bool UpdateIndexBuffer();
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
	bool UpdateConstantBuffer(T& _ConstantBuffer)
	{
		if (renderer == R_DX11)
			if (d3d11_shader)
				if (!d3d11_shader->UpdateConstantBuffer<T>(_ConstantBuffer))
					return false;

		return true;
	}
	bool AddLayout(LPCSTR _Name, UINT _Index, UINT _Format, UINT _Slot = 0, UINT _Offset = 0);
	bool CreateLayout();
	template <typename T>
	bool Set()
	{
		if (renderer == R_DX11)
			if (d3d11_shader)
				if (!d3d11_shader->Set<T>())
					return false;

		return true;
	}
	bool Draw(UINT _ConstantBufferSlot = 0);
	void ReleaseVertex();
	void ReleasePixel();
	void ReleaseLayout();
	void ReleaseVertexBlob();
	void ReleasePixelBlob();
	void Release();

public:
	void SetRenderer(Renderer _Renderer);

private:
	Renderer renderer;
	D3D11_Shader* d3d11_shader;
};