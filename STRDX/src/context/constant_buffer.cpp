#include "constant_buffer.h"

void ConstantBuffer::Release()
{
#if defined(RENDERER_D3D11)
	if (d3d11_constant_buffer)
		d3d11_constant_buffer->Release();
#endif

	delete this;
}
ConstantBufferID* ConstantBuffer::Get()
{
#if defined(RENDERER_D3D11)
	if (d3d11_constant_buffer)
		return (ConstantBufferID*)d3d11_constant_buffer;
#endif

	return 0;
}
ConstantBuffer* ConstantBuffer::Create(UINT _SizeOf)
{
	ConstantBuffer* constantBuffer = new ConstantBuffer();

#if defined(RENDERER_D3D11)
	constantBuffer->d3d11_constant_buffer = D3D11ConstantBuffer::Create(_SizeOf);
#endif

	return constantBuffer;
}