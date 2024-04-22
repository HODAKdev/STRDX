#pragma once

#include <d3d11.h>
#include "../context.h"
#include "strdxwrl.h"

#include "d3d11_shader.h"

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
	bool SetVertexConstantBuffer(D3D11ConstantBuffer* _ConstantBuffer, UINT _Slot);
	bool SetPixelConstantBuffer(D3D11ConstantBuffer* _ConstantBuffer, UINT _Slot);
	template <typename T>
	bool UpdateVertexBuffer(D3D11Shader* _Shader, std::vector<T>& _Vertices)
	{
		if (!_Shader)
		{
			printf("shader is null\n");
			return false;
		}

		if (_Vertices.empty())
		{
			printf("vertices data is empty\n");
			return false;
		}

		if (!_Shader->GetVertexBuffer())
		{
			printf("vertex buffer is null\n");
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE resource;
		if (FAILED(deviceContext->Map(_Shader->GetVertexBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
			return false;

		memcpy(resource.pData, _Vertices.data(), (sizeof(T) * _Vertices.size()));
		deviceContext->Unmap(_Shader->GetVertexBuffer().Get(), 0);

		return true;
	}
	bool SetVertexShaderResource(ID3D11ShaderResourceView* _ShaderResource, UINT _Slot);
	bool SetPixelShaderResource(ID3D11ShaderResourceView* _ShaderResource, UINT _Slot);
	bool SetVertexSampler(D3D11SamplerState* _SamplerState, UINT _Slot);
	bool SetPixelSampler(D3D11SamplerState* _SamplerState, UINT _Slot);
	void ReleaseVertexShaderResources(UINT _Slot);
	void ReleasePixelShaderResources(UINT _Slot);
	bool UpdateIndexBuffer(D3D11Shader* _Shader);
	bool Draw(D3D11Shader* _Shader);
	bool Set(D3D11Shader* _Shader);

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