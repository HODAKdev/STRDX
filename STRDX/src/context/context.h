#pragma once

#include <Windows.h>

enum Renderer
{
	R_NONE,
	R_DX11,
};
enum PrimitiveTopology
{
	PT_NONE,
	PT_POINTLIST,
	PT_LINELIST,
	PT_LINESTRIP,
	PT_TRIANGLELIST,
	PT_TRIANGLESTRIP,
};
enum Format
{
	F_NONE,
	F_RGBA,
	F_RGBA_SRGB,
};

class Context
{
public:
	Context() : renderer(Renderer::R_NONE) {}

public:
	static Context* GetSingleton();

public:
	bool Create(Renderer _Renderer, UINT _Width, UINT _Height);
	void SetViewport(UINT _Width, UINT _Height);
	void SetPrimitiveTopology(PrimitiveTopology _PrimitiveTopology);
	void SetRenderTarget();
	void ClearRenderTarget(float _R, float _G, float _B, float _A);
	bool ResizeBuffer(UINT _Width, UINT _Height);
	void Present(bool _Vsync);
	bool CheckMultisampleQualityLevels(UINT _SampleCount, UINT* _QualityLevels);
	void Release();

private:
	Renderer renderer;
};