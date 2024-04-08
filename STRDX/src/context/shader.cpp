#include "shader.h"

Shader* Shader::Create(Renderer _Renderer)
{
	Shader* shader = new Shader();
	shader->SetRenderer(_Renderer);

	if (_Renderer == R_DX11)
		shader->d3d11_shader = D3D11_Shader::Create();

	return shader;
}
bool Shader::LoadVertex(const char* _Filename, bool _Compile)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->LoadVertex(_Filename, _Compile))
				return false;

	return true;
}
bool Shader::LoadPixel(const char* _Filename, bool _Compile)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->LoadPixel(_Filename, _Compile))
				return false;

	return true;
}
bool Shader::CompileVertex()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->CompileVertex())
				return false;

	return true;
}
bool Shader::CompilePixel()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->CompilePixel())
				return false;

	return true;
}
bool Shader::SaveVertex(const char* _Filename)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->SaveVertex(_Filename))
				return false;

	return true;
}
bool Shader::SavePixel(const char* _Filename)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->SavePixel(_Filename))
				return false;

	return true;
}
bool Shader::CreateVertex()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->CreateVertex())
				return false;

	return true;
}
bool Shader::CreatePixel()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->CreatePixel())
				return false;

	return true;
}
void Shader::AddIndex(UINT _Index)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->AddIndex(_Index);
}
bool Shader::CreateIndexBuffer(bool _CpuAccess)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->CreateIndexBuffer(_CpuAccess))
				return false;

	return true;
}
bool Shader::UpdateIndexBuffer()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->UpdateIndexBuffer())
				return false;

	return true;
}
bool Shader::AddLayout(LPCSTR _Name, UINT _Index, UINT _Format, UINT _Slot, UINT _Offset)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->AddLayout(_Name, _Index, _Format, _Slot, _Offset))
				return false;

	return true;
}
bool Shader::CreateLayout()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->CreateLayout())
				return false;

	return true;
}
bool Shader::Draw(UINT _ConstantBufferSlot)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->Draw(_ConstantBufferSlot))
				return false;

	return true;
}
void Shader::ReleaseVertex()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->ReleaseVertex();
}
void Shader::ReleasePixel()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->ReleasePixel();
}
void Shader::ReleaseLayout()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->ReleaseLayout();
}
void Shader::ReleaseVertexBlob()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->ReleaseVertexBlob();
}
void Shader::ReleasePixelBlob()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->ReleasePixelBlob();
}
void Shader::Release()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->Release();
}
void Shader::SetRenderer(Renderer _Renderer)
{
	renderer = _Renderer;
}