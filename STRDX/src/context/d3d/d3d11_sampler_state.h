#pragma once

#include <d3d11.h>
#include "d3d11_context.h"
#include <stdio.h>

class D3D11SamplerState
{
public:
	D3D11SamplerState() {}

public:
	static D3D11SamplerState* Create();
	STRDXWRL<ID3D11SamplerState> Get();
	void Release();

private:
	STRDXWRL<ID3D11SamplerState> samplerState;
};