#include "shader.h"

Shader* Shader::Create()
{
	Shader* shader = new Shader();

#if defined(RENDERER_D3D11)
	shader->d3d11_shader = D3D11Shader::Create();
#endif

	return shader;
}
bool Shader::LoadVertex(const char* _Filename, bool _Compile)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->LoadVertex(_Filename, _Compile))
			return false;
#endif

	return true;
}
bool Shader::LoadPixel(const char* _Filename, bool _Compile)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->LoadPixel(_Filename, _Compile))
			return false;
#endif

	return true;
}
bool Shader::CompileVertex()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->CompileVertex())
			return false;
#endif

	return true;
}
bool Shader::CompilePixel()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->CompilePixel())
			return false;
#endif

	return true;
}
bool Shader::SaveVertex(const char* _Filename)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->SaveVertex(_Filename))
			return false;
#endif

	return true;
}
bool Shader::SavePixel(const char* _Filename)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->SavePixel(_Filename))
			return false;
#endif

	return true;
}
bool Shader::CreateVertex()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->CreateVertex())
			return false;
#endif

	return true;
}
bool Shader::CreatePixel()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->CreatePixel())
			return false;
#endif

	return true;
}
void Shader::AddIndex(UINT _Index)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		d3d11_shader->AddIndex(_Index);
#endif
}
bool Shader::CreateIndexBuffer(bool _CpuAccess)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->CreateIndexBuffer(_CpuAccess))
			return false;
#endif

	return true;
}
bool Shader::UpdateIndexBuffer()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->UpdateIndexBuffer())
			return false;
#endif

	return true;
}
bool Shader::AddLayout(LPCSTR _Name, UINT _Index, UINT _Format, UINT _Slot, UINT _Offset)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->AddLayout(_Name, _Index, _Format, _Slot, _Offset))
			return false;
#endif

	return true;
}
bool Shader::CreateLayout()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->CreateLayout())
			return false;
#endif

	return true;
}
bool Shader::Draw()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->Draw())
			return false;
#endif

	return true;
}
void Shader::ReleaseVertex()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		d3d11_shader->ReleaseVertex();
#endif
}
void Shader::ReleasePixel()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		d3d11_shader->ReleasePixel();
#endif
}
void Shader::ReleaseLayout()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		d3d11_shader->ReleaseLayout();
#endif
}
void Shader::ReleaseVertexBlob()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		d3d11_shader->ReleaseVertexBlob();
#endif
}
void Shader::ReleasePixelBlob()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		d3d11_shader->ReleasePixelBlob();
#endif
}
void Shader::Release()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		d3d11_shader->Release();
#endif

	delete this;
}
bool Shader::SetVertexConstantBuffer(ConstantBuffer* _ConstantBuffer, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->SetVertexConstantBuffer((D3D11ConstantBuffer*)_ConstantBuffer->Get(), _Slot))
			return false;
#endif

	return true;
}
bool Shader::SetPixelConstantBuffer(ConstantBuffer* _ConstantBuffer, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->SetPixelConstantBuffer((D3D11ConstantBuffer*)_ConstantBuffer->Get(), _Slot))
			return false;
#endif

	return true;
}
bool Shader::SetVertexShaderResource(ShaderResourceID* _ShaderResource, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->SetVertexShaderResource((ID3D11ShaderResourceView*)_ShaderResource, _Slot))
			return false;
#endif

	return true;
}
bool Shader::SetPixelShaderResource(ShaderResourceID* _ShaderResource, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->SetPixelShaderResource((ID3D11ShaderResourceView*)_ShaderResource, _Slot))
			return false;
#endif

	return true;
}
bool Shader::SetVertexSampler(SamplerState* _SamplerState, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->SetVertexSampler((D3D11SamplerState*)_SamplerState->Get(), _Slot))
			return false;
#endif

	return true;
}
bool Shader::SetPixelSampler(SamplerState* _SamplerState, UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		if (!d3d11_shader->SetPixelSampler((D3D11SamplerState*)_SamplerState->Get(), _Slot))
			return false;
#endif

	return true;
}
void Shader::ReleaseShaderResources(UINT _Slot)
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		d3d11_shader->ReleaseShaderResources(_Slot);
#endif
}