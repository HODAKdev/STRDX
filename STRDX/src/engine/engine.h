#pragma once

#include "../context/shader.h"
#include "../CB.h"

class Engine
{
public:
	Engine() : shader(NULL) {}

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
	CB cb;
};