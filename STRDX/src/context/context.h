#pragma once

#include <Windows.h>
#include "../strdx.h"

// classes
class ConstantBuffer;
class RasterizerState;
class RenderTarget;
class SamplerState;
class Shader;

enum PrimitiveTopology
{
	PT_NONE,
	PT_POINTLIST,
	PT_LINELIST,
	PT_LINESTRIP,
	PT_TRIANGLELIST,
	PT_TRIANGLESTRIP,
};

class Context
{
public:
	Context() {}

public:
	static Context* GetSingleton();

public:
	bool Create(UINT _Width, UINT _Height);
	void SetViewport(UINT _Width, UINT _Height);
	void SetPrimitiveTopology(PrimitiveTopology _PrimitiveTopology);
	void SetRenderTarget();
	void UnsetRenderTarget();
	void ClearRenderTarget(float _R, float _G, float _B, float _A);
	bool ResizeBuffer(UINT _Width, UINT _Height);
	void Present(bool _Vsync);
	bool CheckMultisampleQualityLevels(UINT _SampleCount, UINT* _QualityLevels);
	void Release();
	bool SetVertexConstantBuffer(ConstantBuffer* _ConstantBuffer, UINT _Slot);
	bool SetPixelConstantBuffer(ConstantBuffer* _ConstantBuffer, UINT _Slot);
};