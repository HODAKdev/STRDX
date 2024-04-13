#include "constant_buffer.h"

void ConstantBuffer::Release()
{
#if defined(RENDERER_D3D11)
	if (d3d11_constant_buffer)
		d3d11_constant_buffer->Release();
#endif
}
ConstantBufferID* ConstantBuffer::Get()
{
#if defined(RENDERER_D3D11)
	if (d3d11_constant_buffer)
		return (ConstantBufferID*)d3d11_constant_buffer->Get().Get();
#endif

	return 0;
}