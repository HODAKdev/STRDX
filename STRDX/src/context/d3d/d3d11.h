#pragma once

#include <d3d11.h>
#include <wrl/client.h>
#include "../context.h"

template<typename T>
using STRDXWRL = Microsoft::WRL::ComPtr<T>;

class D3D11
{
public:
	D3D11() {}

public:
	static D3D11* GetSingleton();

public:
	bool Create(UINT width, UINT height);
	void Release();
	void ClearRenderTarget(float r, float g, float b, float a);
	void SetRenderTarget();
	bool ResizeBuffer(UINT width, UINT height);
	void SetViewport(UINT width, UINT height);
	void Present(bool vsync);
	void SetPrimitiveTopology(PrimitiveTopology primitiveTopology);

private:
	bool CreateRenderTargetView();
	bool CreateDepthStencilView(UINT width, UINT height);

private:
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_1;
	DXGI_SWAP_EFFECT swapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

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
};