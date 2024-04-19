#include "sampler_state.h"

SamplerState* SamplerState::Create()
{
	SamplerState* samplerState = new SamplerState();

#if defined(RENDERER_D3D11)
	samplerState->d3d11_sampler_state = D3D11SamplerState::Create();
#endif

	return samplerState;
}
SamplerStateID* SamplerState::Get()
{
#if defined(RENDERER_D3D11)
	if (d3d11_sampler_state)
		return (SamplerStateID*)d3d11_sampler_state;
#endif

	return 0;
}
void SamplerState::Release()
{
#if defined(RENDERER_D3D11)
	if (d3d11_sampler_state)
		d3d11_sampler_state->Release();
#endif
}