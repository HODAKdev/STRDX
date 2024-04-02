#include "shader.h"

Shader* Shader::Create(Renderer renderer)
{
	Shader* shader = new Shader();
	shader->SetRenderer(renderer);

	if (renderer == R_DX11)
		shader->d3d11_shader = D3D11_Shader::Create();

	return shader;
}
void Shader::SetRenderer(Renderer renderer)
{
	this->renderer = renderer;
}
bool Shader::LoadVertex(const char* filename, bool compile)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->LoadVertex(filename, compile))
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
bool Shader::LoadPixel(const char* filename, bool compile)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->LoadPixel(filename, compile))
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
bool Shader::SaveVertex(const char* filename)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->SaveVertex(filename))
				return false;

	return true;
}
bool Shader::SavePixel(const char* filename)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->SavePixel(filename))
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
void Shader::ReleaseCache()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->ReleaseCache();
}
void Shader::Release()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->Release();
}
bool Shader::CreateLayout()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->CreateLayout())
				return false;

	return true;
}
bool Shader::AddLayout(LPCSTR name, UINT index, UINT format, UINT slot, UINT offset)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->AddLayout(name, index, format, slot, offset))
				return false;

	return true;
}
void Shader::AddIndex(UINT index)
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			d3d11_shader->AddIndex(index);
}
bool Shader::CreateIndexBuffer()
{
	if (renderer == R_DX11)
		if (d3d11_shader)
			if (!d3d11_shader->CreateIndexBuffer())
				return false;

	return true;
}