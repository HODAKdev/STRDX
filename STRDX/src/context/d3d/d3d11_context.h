#pragma once

#include <d3d11.h>
#include "../context.h"
#include "strdxwrl.h"

// settings
#define D3D11_FORMAT DXGI_FORMAT_R8G8B8A8_UNORM
#define D3D11_DRIVER_TYPE D3D_DRIVER_TYPE_HARDWARE
#define D3D11_FEATURE_LEVEL D3D_FEATURE_LEVEL_11_1
#define D3D11_SWAP_EFFECT DXGI_SWAP_EFFECT_FLIP_DISCARD


class D3D11Context
{
public:
	D3D11Context() {}

public:
	static D3D11Context* GetSingleton();

public:
	bool Create(UINT _Width, UINT _Height);
	void SetViewport(UINT _Width, UINT _Height);
	void SetPrimitiveTopology(PrimitiveTopology _PrimitiveTopology);
	void SetRenderTarget();
	void UnsetRenderTarget();
	void ClearRenderTarget(float _R, float _G, float _B, float _A);
	bool ResizeBuffer(UINT _Width, UINT _Height);
	void Present(bool _Vsync);
	bool CheckMultisampleQualityLevels(UINT _SampleCount, UINT* _QualityLevels);
	void Release();

private:
	bool CreateRenderTargetView();
	bool CreateDepthStencilView(UINT _Width, UINT _Height);

private:
	STRDXWRL<IDXGISwapChain> swapChain;
	STRDXWRL<ID3D11Device> device;
	STRDXWRL<ID3D11DeviceContext> deviceContext;
	STRDXWRL<ID3D11RenderTargetView> renderTargetView;
	STRDXWRL<ID3D11DepthStencilView> depthStencilView;

public:
	STRDXWRL<IDXGISwapChain> GetSwapChain() { return swapChain; }
	STRDXWRL<ID3D11Device> GetDevice() { return device; }
	STRDXWRL<ID3D11DeviceContext> GetDeviceContext() { return deviceContext; }
	STRDXWRL<ID3D11RenderTargetView> GetRenderTargetView() { return renderTargetView; }
	STRDXWRL<ID3D11DepthStencilView> GetDepthStencilView() { return depthStencilView; }
};