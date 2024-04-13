#include "d3d11_render_target.h"

static D3D11* d3d11 = D3D11::GetSingleton();

D3D11RenderTarget* D3D11RenderTarget::Create(UINT _Width, UINT _Height)
{
	D3D11RenderTarget* renderTarget = new D3D11RenderTarget();

	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));

	textureDesc.Width = _Width;
	textureDesc.Height = _Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	if (FAILED(d3d11->GetDevice()->CreateTexture2D(&textureDesc, NULL, renderTarget->texture.GetAddressOf())))
		printf("create texture failed\n");

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	if (FAILED(d3d11->GetDevice()->CreateRenderTargetView(renderTarget->texture.Get(), &renderTargetViewDesc, renderTarget->renderTargetView.GetAddressOf())))
		printf("create render target view failed\n");

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	if (FAILED(d3d11->GetDevice()->CreateShaderResourceView(renderTarget->texture.Get(), &shaderResourceViewDesc, renderTarget->shaderResourceView.GetAddressOf())))
		printf("create shader resource view failed\n");

	return renderTarget;
}
void D3D11RenderTarget::Set()
{
	d3d11->GetDeviceContext()->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), d3d11->GetDepthStencilView().Get());
}
void D3D11RenderTarget::ClearRenderTarget(float _R, float _G, float _B, float _A)
{
	float clear_color[4] = { _R, _G, _B, _A };
	d3d11->GetDeviceContext()->ClearRenderTargetView(renderTargetView.Get(), clear_color);
	d3d11->GetDeviceContext()->ClearDepthStencilView(d3d11->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
void D3D11RenderTarget::Unset()
{
	d3d11->GetDeviceContext()->OMSetRenderTargets(0, NULL, NULL);
}
STRDXWRL<ID3D11ShaderResourceView> D3D11RenderTarget::Get()
{
	return shaderResourceView;
}
void D3D11RenderTarget::Release()
{
	if (texture) texture->Release();
	if (renderTargetView) renderTargetView->Release();
	if (shaderResourceView) shaderResourceView->Release();
}