#include "rasterizer_state.h"

RasterizerState* RasterizerState::Create()
{
	RasterizerState* rasterizerState = new RasterizerState();

#if defined(RENDERER_D3D11)
	rasterizerState->d3d11_rasterizer_state = D3D11RasterizerState::Create();
#endif

	return rasterizerState;
}
void RasterizerState::Set()
{
#if defined(RENDERER_D3D11)
	if (d3d11_rasterizer_state)
		d3d11_rasterizer_state->Set();
#endif
}
void RasterizerState::Unset()
{
#if defined(RENDERER_D3D11)
	if (d3d11_rasterizer_state)
		d3d11_rasterizer_state->Unset();
#endif
}
RasterizerStateID* RasterizerState::Get()
{
#if defined(RENDERER_D3D11)
	if (d3d11_rasterizer_state)
		return (RasterizerStateID*)d3d11_rasterizer_state->Get().Get();
#endif

	return 0;
}
void RasterizerState::Release()
{
#if defined(RENDERER_D3D11)
	if (d3d11_rasterizer_state)
		d3d11_rasterizer_state->Release();
#endif
}