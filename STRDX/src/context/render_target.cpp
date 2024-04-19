#include "render_target.h"

RenderTarget* RenderTarget::Create(UINT _Width, UINT _Height, UINT _Count)
{
	RenderTarget* renderTarget = new RenderTarget();

#if defined(RENDERER_D3D11)
	renderTarget->d3d11_render_target = D3D11RenderTarget::Create(_Width, _Height, _Count);
#endif

	return renderTarget;
}
void RenderTarget::Set()
{
#if defined(RENDERER_D3D11)
	if (d3d11_render_target)
		d3d11_render_target->Set();
#endif
}
void RenderTarget::ClearRenderTarget(float _R, float _G, float _B, float _A)
{
#if defined(RENDERER_D3D11)
	if (d3d11_render_target)
		d3d11_render_target->ClearRenderTarget(_R, _G, _B, _A);
#endif
}
ShaderResourceID* RenderTarget::GetShaderResource()
{
#if defined(RENDERER_D3D11)
	if (d3d11_render_target)
		return (ShaderResourceID*)d3d11_render_target->Get().Get();
#endif

	return 0;
}
void RenderTarget::Release()
{
#if defined(RENDERER_D3D11)
	if (d3d11_render_target)
		d3d11_render_target->Release();
#endif
}