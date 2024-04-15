#include "d3d11_rasterizer_state.h"

static D3D11* d3d11 = D3D11::GetSingleton();

D3D11RasterizerState* D3D11RasterizerState::Create()
{
    D3D11RasterizerState* rasterizerState = new D3D11RasterizerState();

    D3D11_RASTERIZER_DESC  desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_NONE;
    desc.FrontCounterClockwise = false;
    desc.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
    desc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
    desc.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
    desc.DepthClipEnable = true;
    desc.ScissorEnable = false;
    desc.MultisampleEnable = false;
    desc.AntialiasedLineEnable = true;

    if (FAILED(d3d11->GetDevice()->CreateRasterizerState(&desc, rasterizerState->rasterizerState.GetAddressOf())))
        printf("create rasterizer state failed\n");

	return rasterizerState;
}
void D3D11RasterizerState::Set()
{
    d3d11->GetDeviceContext()->RSSetState(rasterizerState.Get());
}
void D3D11RasterizerState::Unset()
{
    d3d11->GetDeviceContext()->RSSetState(NULL);
}
STRDXWRL<ID3D11RasterizerState> D3D11RasterizerState::Get()
{
	return rasterizerState;
}
void D3D11RasterizerState::Release()
{
	if (rasterizerState) rasterizerState->Release();
}