#include "context.h"
#include "d3d/d3d11.h"

static D3D11* d3d11 = D3D11::GetSingleton();

Context* Context::GetSingleton()
{
	static Context context;
	return &context;
}
bool Context::Create(Renderer _Renderer, UINT _Width, UINT _Height)
{
	renderer = _Renderer;

	if (renderer == R_DX11)
		if (!d3d11->Create(_Width, _Height))
			return false;

	return true;
}
void Context::SetViewport(UINT _Width, UINT _Height)
{
	if (renderer == R_DX11)
		d3d11->SetViewport(_Width, _Height);
}
void Context::SetPrimitiveTopology(PrimitiveTopology _PrimitiveTopology)
{
	if (renderer == R_DX11)
		d3d11->SetPrimitiveTopology(_PrimitiveTopology);
}
void Context::SetRenderTarget()
{
	if (renderer == R_DX11)
		d3d11->SetRenderTarget();
}
void Context::ClearRenderTarget(float _R, float _G, float _B, float _A)
{
	if (renderer == R_DX11)
		d3d11->ClearRenderTarget(_R, _G, _B, _A);
}
bool Context::ResizeBuffer(UINT _Width, UINT _Height)
{
	if (renderer == R_DX11)
		return d3d11->ResizeBuffer(_Width, _Height);

	return false;
}
void Context::Present(bool _Vsync)
{
	if (renderer == R_DX11)
		d3d11->Present(_Vsync);
}
void Context::Release()
{
	if (renderer == R_DX11)
		d3d11->Release();
}