#pragma once

#include <d3d11.h>
#include "d3d11_context.h"
#include <stdio.h>

template<typename T>
using STRDXWRL = Microsoft::WRL::ComPtr<T>;

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