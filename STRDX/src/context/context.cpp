#include "context.h"
#include "d3d/d3d11_context.h"

#include "constant_buffer.h"
#include "rasterizer_state.h"
#include "render_target.h"
#include "sampler_state.h"
#include "shader.h"

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

	delete this;
}
bool Context::SetVertexConstantBuffer(ConstantBuffer* _ConstantBuffer, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (_ConstantBuffer)
		if (!context->SetVertexConstantBuffer((D3D11ConstantBuffer*)_ConstantBuffer->Get(), _Slot))
			return false;
#endif

	return true;
}
bool Context::SetPixelConstantBuffer(ConstantBuffer* _ConstantBuffer, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (_ConstantBuffer)
		if (!context->SetPixelConstantBuffer((D3D11ConstantBuffer*)_ConstantBuffer->Get(), _Slot))
			return false;
#endif

	return true;
}
bool Context::SetVertexShaderResource(ShaderResourceID* _ShaderResource, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (_ShaderResource)
		if (!context->SetVertexShaderResource((ID3D11ShaderResourceView*)_ShaderResource, _Slot))
			return false;
#endif

	return true;
}
bool Context::SetPixelShaderResource(ShaderResourceID* _ShaderResource, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (_ShaderResource)
		if (!context->SetPixelShaderResource((ID3D11ShaderResourceView*)_ShaderResource, _Slot))
			return false;
#endif

	return true;
}
bool Context::SetVertexSampler(SamplerState* _SamplerState, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (_SamplerState)
		if (!context->SetVertexSampler((D3D11SamplerState*)_SamplerState->Get(), _Slot))
			return false;
#endif

	return true;
}
bool Context::SetPixelSampler(SamplerState* _SamplerState, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (_SamplerState)
		if (!context->SetPixelSampler((D3D11SamplerState*)_SamplerState->Get(), _Slot))
			return false;
#endif

	return true;
}
void Context::ReleaseVertexShaderResources(UINT _Slot)
{
#if defined(RENDERER_D3D11)
	context->ReleaseVertexShaderResources(_Slot);
#endif
}
void Context::ReleasePixelShaderResources(UINT _Slot)
{
#if defined(RENDERER_D3D11)
	context->ReleasePixelShaderResources(_Slot);
#endif
}
bool Context::UpdateIndexBuffer(Shader* _Shader)
{
#if defined(RENDERER_D3D11)
		if (!context->UpdateIndexBuffer((D3D11Shader*)_Shader->Get()))
			return false;
#endif

	return true;
}
bool Context::Draw(Shader* _Shader)
{
#if defined(RENDERER_D3D11)
	if (_Shader)
		if (!context->Draw((D3D11Shader*)_Shader->Get()))
			return false;
#endif

	return true;
}
bool Context::Set(Shader* _Shader)
{
#if defined(RENDERER_D3D11)
	if (_Shader)
		if (!context->Set((D3D11Shader*)_Shader->Get()))
			return false;
#endif

	return true;
}