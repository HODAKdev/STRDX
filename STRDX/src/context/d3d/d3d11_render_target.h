#pragma once

#include <d3d11.h>
#include <stdio.h>
#include "strdxwrl.h"

class D3D11RenderTarget
{
public:
	D3D11RenderTarget() {}

public:
	static D3D11RenderTarget* Create(UINT _Width, UINT _Height, UINT _Count);
	void Set();
	void ClearRenderTarget(float _R, float _G, float _B, float _A);
	STRDXWRL<ID3D11ShaderResourceView> Get();
	void Release();

private:
	bool CreateRenderTargetView(UINT _Width, UINT _Height, UINT _Count);
	bool CreateDepthStencilView(UINT _Width, UINT _Height, UINT _Count);

private:
	STRDXWRL<ID3D11Texture2D> texture;
	STRDXWRL<ID3D11RenderTargetView> renderTargetView;
	STRDXWRL<ID3D11ShaderResourceView> shaderResourceView;
	STRDXWRL<ID3D11DepthStencilView> depthStencilView;
};