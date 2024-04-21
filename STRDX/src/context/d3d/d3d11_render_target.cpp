#include "d3d11_render_target.h"
#include "d3d11_context.h"

static D3D11Context* context = D3D11Context::GetSingleton();

D3D11RenderTarget* D3D11RenderTarget::Create(UINT _Width, UINT _Height, UINT _Count)
{
	D3D11RenderTarget* renderTarget = new D3D11RenderTarget();

	if (_Count == 0)
		printf("Count is zero\n");

	renderTarget->CreateRenderTargetView(_Width, _Height, _Count);
	renderTarget->CreateDepthStencilView(_Width, _Height, _Count);

	return renderTarget;
}
void D3D11RenderTarget::Set()
{
	context->GetDeviceContext()->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
}
void D3D11RenderTarget::ClearRenderTarget(float _R, float _G, float _B, float _A)
{
	float clear_color[4] = { _R, _G, _B, _A };
	context->GetDeviceContext()->ClearRenderTargetView(renderTargetView.Get(), clear_color);
	context->GetDeviceContext()->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
STRDXWRL<ID3D11ShaderResourceView> D3D11RenderTarget::Get()
{
	return shaderResourceView;
}
void D3D11RenderTarget::Release()
{
	STRDXWRL_RESET(texture);
	STRDXWRL_RESET(renderTargetView);
	STRDXWRL_RESET(shaderResourceView);
	STRDXWRL_RESET(depthStencilView);

	delete this;
}
bool D3D11RenderTarget::CreateRenderTargetView(UINT _Width, UINT _Height, UINT _Count)
{
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
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = _Count;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	if (FAILED(context->GetDevice()->CreateTexture2D(&textureDesc, NULL, texture.GetAddressOf())))
		printf("create texture failed\n");

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = (_Count == 1) ? D3D11_RTV_DIMENSION_TEXTURE2D : D3D11_RTV_DIMENSION_TEXTURE2DMS;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	if (FAILED(context->GetDevice()->CreateRenderTargetView(texture.Get(), &renderTargetViewDesc, renderTargetView.GetAddressOf())))
		printf("create render target view failed\n");

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = (_Count == 1) ? D3D11_SRV_DIMENSION_TEXTURE2D : D3D11_SRV_DIMENSION_TEXTURE2DMS;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	if (FAILED(context->GetDevice()->CreateShaderResourceView(texture.Get(), &shaderResourceViewDesc, shaderResourceView.GetAddressOf())))
		printf("create shader resource view failed\n");

	return true;
}
bool D3D11RenderTarget::CreateDepthStencilView(UINT _Width, UINT _Height, UINT _Count)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	textureDesc.Width = _Width;
	textureDesc.Height = _Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc.Count = _Count;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	ID3D11Texture2D* texture = NULL;
	if (FAILED(context->GetDevice()->CreateTexture2D(&textureDesc, NULL, &texture)))
		printf("create texture failed\n");

	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = (_Count == 1) ? D3D11_DSV_DIMENSION_TEXTURE2D : D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	if (FAILED(context->GetDevice()->CreateDepthStencilView(texture, &depthStencilViewDesc, depthStencilView.GetAddressOf())))
		printf("create depth stencil view failed\n");

	texture->Release();
	return true;
}