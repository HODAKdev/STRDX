#pragma once

#include "d3d/d3d11_constant_buffer.h"
#include "../strdx.h"

class ConstantBuffer
{
public:
	ConstantBuffer() : d3d11_constant_buffer(NULL) {}

public:
	template <typename T>
	static ConstantBuffer* Create()
	{
		ConstantBuffer* constantBuffer = new ConstantBuffer();

#if defined(RENDERER_D3D11)
		constantBuffer->d3d11_constant_buffer = D3D11ConstantBuffer::Create<T>();
#endif

		return constantBuffer;
	}
	template <typename T>
	void Update(T& _ConstantBuffer)
	{
#if defined(RENDERER_D3D11)
		if (d3d11_constant_buffer)
			d3d11_constant_buffer->Update<T>(_ConstantBuffer);
#endif
	}
	ConstantBufferID* Get();
	void Release();

private:
	D3D11ConstantBuffer* d3d11_constant_buffer;
};