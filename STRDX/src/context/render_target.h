#pragma once

#include "d3d/d3d11_render_target.h"
#include "../strdx.h"

class RenderTarget
{
public:
	RenderTarget() : d3d11_render_target(NULL) {}

public:
	static RenderTarget* Create(UINT _Width, UINT _Height, UINT _Count);
	void Set();
	void ClearRenderTarget(float _R, float _G, float _B, float _A);
	ShaderResourceID* Get();
	void Release();

private:
	D3D11RenderTarget* d3d11_render_target;
};