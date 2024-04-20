#include "context.h"
#include "d3d/d3d11_context.h"

static D3D11Context* context = D3D11Context::GetSingleton();

Context* Context::GetSingleton()
{
	static Context context;
	return &context;
}
bool Context::Create(UINT _Width, UINT _Height)
{
#if defined(RENDERER_D3D11)
	if (!context->Create(_Width, _Height))
		return false;
#endif

	return true;
}
void Context::SetViewport(UINT _Width, UINT _Height)
{
#if defined(RENDERER_D3D11)
	context->SetViewport(_Width, _Height);
#endif
}
void Context::SetPrimitiveTopology(PrimitiveTopology _PrimitiveTopology)
{
#if defined(RENDERER_D3D11)
	context->SetPrimitiveTopology(_PrimitiveTopology);
#endif
}
void Context::SetRenderTarget()
{
#if defined(RENDERER_D3D11)
	context->SetRenderTarget();
#endif
}
void Context::UnsetRenderTarget()
{
#if defined(RENDERER_D3D11)
	context->UnsetRenderTarget();
#endif
}
void Context::ClearRenderTarget(float _R, float _G, float _B, float _A)
{
#if defined(RENDERER_D3D11)
	context->ClearRenderTarget(_R, _G, _B, _A);
#endif
}
bool Context::ResizeBuffer(UINT _Width, UINT _Height)
{
#if defined(RENDERER_D3D11)
	if (!context->ResizeBuffer(_Width, _Height))
		return false;
#endif

	return true;
}
void Context::Present(bool _Vsync)
{
#if defined(RENDERER_D3D11)
	context->Present(_Vsync);
#endif
}
bool Context::CheckMultisampleQualityLevels(UINT _SampleCount, UINT* _QualityLevels)
{
#if defined(RENDERER_D3D11)
	if (!context->CheckMultisampleQualityLevels(_SampleCount, _QualityLevels))
		return false;
#endif

	return true;
}
void Context::Release()
{
#if defined(RENDERER_D3D11)
	context->Release();
#endif
}