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
ShaderID* Shader::Get()
{
#if defined(RENDERER_D3D11)
	if (d3d11_shader)
		return (ShaderID*)d3d11_shader;
#endif

	return 0;
}