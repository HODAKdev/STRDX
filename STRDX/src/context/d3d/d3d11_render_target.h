#pragma once

#include <d3d11.h>
#include "d3d11.h"
#include <stdio.h>

template<typename T>
using STRDXWRL = Microsoft::WRL::ComPtr<T>;

class D3D11RenderTarget
{
public:
	D3D11RenderTarget() {}

public:
	static D3D11RenderTarget* Create(UINT _Width, UINT _Height);
	void Set();
	void ClearRenderTarget(float _R, float _G, float _B, float _A);
	void Unset();
	STRDXWRL<ID3D11ShaderResourceView> Get();
	void Release();

private:
	STRDXWRL<ID3D11Texture2D> texture;
	STRDXWRL<ID3D11RenderTargetView> renderTargetView;
	STRDXWRL<ID3D11ShaderResourceView> shaderResourceView;
};