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
	bool Create(UINT _Width, UINT _Height);
	void SetViewport(UINT _Width, UINT _Height);
	void SetPrimitiveTopology(PrimitiveTopology _PrimitiveTopology);
	void SetRenderTarget();
	void ClearRenderTarget(float _R, float _G, float _B, float _A);
	bool ResizeBuffer(UINT _Width, UINT _Height);
	void Present(bool _Vsync);
	bool CheckMultisampleQualityLevels(UINT _SampleCount, UINT* _QualityLevels);
	void Release();

private:
	bool CreateRenderTargetView();
	bool CreateDepthStencilView(UINT _Width, UINT _Height);

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