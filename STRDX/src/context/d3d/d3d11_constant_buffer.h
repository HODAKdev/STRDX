#pragma once

#include <d3d11.h>
#include "d3d11_context.h"
#include <stdio.h>

template<typename T>
using STRDXWRL = Microsoft::WRL::ComPtr<T>;

class D3D11ConstantBuffer
{
public:
	D3D11ConstantBuffer() {}

public:
	template <typename T>
	static D3D11ConstantBuffer* Create()
	{
		D3D11ConstantBuffer* constantBuffer = new D3D11ConstantBuffer();

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(T);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		if (FAILED(D3D11Context::GetSingleton()->GetDevice()->CreateBuffer(&desc, NULL, constantBuffer->constant_buffer.GetAddressOf())))
			printf("create constant buffer failed\n");

		return constantBuffer;
	}
	template <typename T>
	bool Update(T& _ConstantBuffer)
	{
		if (!constant_buffer)
		{
			printf("constant buffer is null\n");
			return false;
		}

		D3D11Context::GetSingleton()->GetDeviceContext()->UpdateSubresource(constant_buffer.Get(), 0, NULL, &_ConstantBuffer, 0, 0);

		return true;
	}
	STRDXWRL<ID3D11Buffer> Get();
	void Release();

private:
	STRDXWRL<ID3D11Buffer> constant_buffer;
};