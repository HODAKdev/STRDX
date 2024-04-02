#include "context.h"
#include "d3d/d3d11.h"

static D3D11* d3d11 = D3D11::GetSingleton();

Context* Context::GetSingleton()
{
	static Context context;
	return &context;
}
bool Context::Create(Renderer renderer, UINT width, UINT height)
{
	this->renderer = renderer;

	if (renderer == R_DX11)
		if (!d3d11->Create(width, height))
			return false;

	return true;
}
void Context::Release()
{
	if (renderer == R_DX11)
		d3d11->Release();
}
void Context::ClearRenderTarget(float r, float g, float b, float a)
{
	if (renderer == R_DX11)
		d3d11->ClearRenderTarget(r, g, b, a);
}
void Context::SetRenderTarget()
{
	if (renderer == R_DX11)
		d3d11->SetRenderTarget();
}
bool Context::ResizeBuffer(UINT width, UINT height)
{
	if (renderer == R_DX11)
		return d3d11->ResizeBuffer(width, height);

	return false;
}
void Context::SetViewport(UINT width, UINT height)
{
	if (renderer == R_DX11)
		d3d11->SetViewport(width, height);
}
void Context::Present(bool vsync)
{
	if (renderer == R_DX11)
		d3d11->Present(vsync);
}
void Context::SetPrimitiveTopology(PrimitiveTopology primitiveTopology)
{
	if (renderer == R_DX11)
		d3d11->SetPrimitiveTopology(primitiveTopology);
}