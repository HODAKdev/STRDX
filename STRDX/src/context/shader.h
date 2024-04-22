#pragma once

#include "d3d/d3d11_shader.h"
#include "constant_buffer.h"
#include "../strdx.h"
#include "sampler_state.h"

class Shader
{
public:
	Shader() : d3d11_shader(NULL) {}

public:
	static Shader* Create();
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
#if defined(RENDERER_D3D11)
		if (d3d11_shader)
			if (!d3d11_shader->CreateVertexBuffer<T>(_Vertices, _CpuAccess))
				return false;
#endif

		return true;
	}
	void AddIndex(UINT _Index);
	bool CreateIndexBuffer(bool _CpuAccess = false);
	bool UpdateIndexBuffer();
	bool AddLayout(LPCSTR _Name, UINT _Index, UINT _Format, UINT _Slot, UINT _Offset);
	bool CreateLayout();
	bool Set()
	{
#if defined(RENDERER_D3D11)
		if (d3d11_shader)
			if (!d3d11_shader->Set())
				return false;
#endif

		return true;
	}
	bool Draw();
	void ReleaseVertex();
	void ReleasePixel();
	void ReleaseLayout();
	void ReleaseVertexBlob();
	void ReleasePixelBlob();
	void Release();
	bool SetVertexShaderResource(ShaderResourceID* _ShaderResource, UINT _Slot);
	bool SetPixelShaderResource(ShaderResourceID* _ShaderResource, UINT _Slot);
	bool SetVertexSampler(SamplerState* _SamplerState, UINT _Slot);
	bool SetPixelSampler(SamplerState* _SamplerState, UINT _Slot);
	void ReleaseShaderResources(UINT _Slot = 0);

private:
	D3D11Shader* d3d11_shader;
};