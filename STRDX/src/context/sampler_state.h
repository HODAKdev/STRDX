#pragma once

#include "d3d/d3d11_sampler_state.h"
#include "../strdx.h"

class SamplerState
{
public:
	SamplerState() : d3d11_sampler_state(NULL) {}

public:
	static SamplerState* Create();
	SamplerStateID* Get();
	void Release();

public:
	D3D11SamplerState* d3d11_sampler_state;
};