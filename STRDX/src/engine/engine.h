#pragma once

#include "../context/shader.h"
#include "../context/constant_buffer.h"
#include "../context/render_target.h"
#include "../context/sampler_state.h"
#include "../context/rasterizer_state.h"
#include "../CB.h"

class Engine
{
public:
	Engine() : shader(NULL),
		       shader2(NULL),
		       constantBuffer(NULL),
		       renderTarget(NULL),
		       samplerState(NULL),
		       rasterizerState(NULL) {}

public:
	static Engine* GetSingleton();

public:
	void Start();
	void Update();
	void Release();

private:
	void Render();

public:
	float GetTime();
	UINT GetScreenWidth();
	UINT GetScreenHeight();
	void ShowCursor();
	void HideCursor();
	void SetCursorPos(UINT x, UINT y);

private:
	Shader* shader;
	Shader* shader2;
	ConstantBuffer* constantBuffer;
	RenderTarget* renderTarget;
	SamplerState* samplerState;
	RasterizerState* rasterizerState;
	CB cb;
};