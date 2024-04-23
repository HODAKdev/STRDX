#include "d3d11_constant_buffer.h"
#include "d3d11_context.h"

STRDXWRL<ID3D11Buffer> D3D11ConstantBuffer::Get()
{
	return constant_buffer;
}
void D3D11ConstantBuffer::Release()
{
	STRDXWRL_RESET(constant_buffer);
	delete this;
}
D3D11ConstantBuffer* D3D11ConstantBuffer::Create(UINT _SizeOf)
{
	D3D11ConstantBuffer* constantBuffer = new D3D11ConstantBuffer();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = _SizeOf;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	if (FAILED(D3D11Context::GetSingleton()->GetDevice()->CreateBuffer(&desc, NULL, constantBuffer->constant_buffer.GetAddressOf())))
		printf("create constant buffer failed\n");

	return constantBuffer;
}
bool D3D11ConstantBuffer::Update(const void* _ConstantBuffer)
{
	// error check
	if (!_ConstantBuffer)
	{
		printf("constant buffer data is null\n");
		return false;
	}
	else if (!constant_buffer)
	{
		printf("constant buffer is null\n");
		return false;
	}

	D3D11Context::GetSingleton()->GetDeviceContext()->UpdateSubresource(constant_buffer.Get(), 0, NULL, _ConstantBuffer, 0, 0);
	return true;
}