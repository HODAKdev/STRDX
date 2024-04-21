#include "d3d11_constant_buffer.h"

STRDXWRL<ID3D11Buffer> D3D11ConstantBuffer::Get()
{
	return constant_buffer;
}
void D3D11ConstantBuffer::Release()
{
	STRDXWRL_RESET(constant_buffer);
}