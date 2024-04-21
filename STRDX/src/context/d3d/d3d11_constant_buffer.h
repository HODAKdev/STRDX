#pragma once

#include <d3d11.h>
#include <stdio.h>
#include "strdxwrl.h"

class D3D11ConstantBuffer
{
public:
	D3D11ConstantBuffer() {}

public:
	static D3D11ConstantBuffer* Create(UINT _SizeOf);
	bool Update(const void* _ConstantBuffer);
	STRDXWRL<ID3D11Buffer> Get();
	void Release();

private:
	STRDXWRL<ID3D11Buffer> constant_buffer;
};