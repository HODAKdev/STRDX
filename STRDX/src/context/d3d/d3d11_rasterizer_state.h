#pragma once

#include <d3d11.h>
#include <stdio.h>
#include "strdxwrl.h"

class D3D11RasterizerState
{
public:
	D3D11RasterizerState() {}

public:
	static D3D11RasterizerState* Create();
	void Set();
	void Unset();
	STRDXWRL<ID3D11RasterizerState> Get();
	void Release();

private:
	STRDXWRL<ID3D11RasterizerState> rasterizerState;
};