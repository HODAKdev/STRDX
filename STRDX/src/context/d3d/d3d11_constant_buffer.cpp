#include "d3d11_constant_buffer.h"

STRDXWRL<ID3D11Buffer> D3D11ConstantBuffer::Get()
{
	return constant_buffer;
}
void D3D11ConstantBuffer::Release()
{
	if (constant_buffer) constant_buffer->Release();
}