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
	PT_TRIANGLELIST,
	PT_LINELIST,
};

class Context
{
public:
	Context() : renderer(Renderer::R_NONE) {}

public:
	static Context* GetSingleton();

public:
	bool Create(Renderer renderer, UINT width, UINT height);
	void Release();
	void ClearRenderTarget(float r, float g, float b, float a);
	void SetRenderTarget();
	bool ResizeBuffer(UINT width, UINT height);
	void SetViewport(UINT width, UINT height);
	void Present(bool vsync);
	void SetPrimitiveTopology(PrimitiveTopology primitiveTopology);

private:
	Renderer renderer;
};