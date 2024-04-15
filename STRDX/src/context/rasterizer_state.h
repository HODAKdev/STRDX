#pragma once

#include "d3d/d3d11_rasterizer_state.h"
#include "../strdx.h"

class RasterizerState
{
public:
	RasterizerState() : d3d11_rasterizer_state(NULL) {}

public:
	static RasterizerState* Create();
	void Set();
	void Unset();
	RasterizerStateID* Get();
	void Release();

private:
	D3D11RasterizerState* d3d11_rasterizer_state;
};