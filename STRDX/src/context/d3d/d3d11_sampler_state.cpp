#include "d3d11_sampler_state.h"
#include "d3d11_context.h"

static D3D11Context* context = D3D11Context::GetSingleton();

D3D11SamplerState* D3D11SamplerState::Create()
{
	D3D11SamplerState* samplerState = new D3D11SamplerState();

    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;

    if (FAILED(context->GetDevice()->CreateSamplerState(&desc, samplerState->samplerState.GetAddressOf())))
        printf("create sampler state failed\n");

	return samplerState;
}
STRDXWRL<ID3D11SamplerState> D3D11SamplerState::Get()
{
	return samplerState;
}
void D3D11SamplerState::Release()
{
    STRDXWRL_RESET(samplerState);
    delete this;
}