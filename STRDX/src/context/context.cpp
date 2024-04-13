#include "context.h"
#include "d3d/d3d11.h"

static D3D11* d3d11 = D3D11::GetSingleton();

Context* Context::GetSingleton()
{
	static Context context;
	return &context;
}
bool Context::Create(UINT _Width, UINT _Height)
{
#if defined(RENDERER_D3D11)
	if (!d3d11->Create(_Width, _Height))
		return false;
#endif

	return true;
}
void Context::SetViewport(UINT _Width, UINT _Height)
{
#if defined(RENDERER_D3D11)
	d3d11->SetViewport(_Width, _Height);
#endif
}
void Context::SetPrimitiveTopology(PrimitiveTopology _PrimitiveTopology)
{
#if defined(RENDERER_D3D11)
	d3d11->SetPrimitiveTopology(_PrimitiveTopology);
#endif
}
void Context::SetRenderTarget()
{
#if defined(RENDERER_D3D11)
	d3d11->SetRenderTarget();
#endif
}
void Context::UnsetRenderTarget()
{
#if defined(RENDERER_D3D11)
	d3d11->UnsetRenderTarget();
#endif
}
void Context::ClearRenderTarget(float _R, float _G, float _B, float _A)
{
#if defined(RENDERER_D3D11)
	d3d11->ClearRenderTarget(_R, _G, _B, _A);
#endif
}
bool Context::ResizeBuffer(UINT _Width, UINT _Height)
{
#if defined(RENDERER_D3D11)
	if (!d3d11->ResizeBuffer(_Width, _Height))
		return false;
#endif

	return true;
}
void Context::Present(bool _Vsync)
{
#if defined(RENDERER_D3D11)
	d3d11->Present(_Vsync);
#endif
}
bool Context::CheckMultisampleQualityLevels(UINT _SampleCount, UINT* _QualityLevels)
{
#if defined(RENDERER_D3D11)
	if (!d3d11->CheckMultisampleQualityLevels(_SampleCount, _QualityLevels))
		return false;
#endif

	return true;
}
void Context::Release()
{
#if defined(RENDERER_D3D11)
	d3d11->Release();
#endif
}