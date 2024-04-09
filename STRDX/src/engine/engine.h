#pragma once

#include "../context/shader.h"
#include "../ConstantBuffer.h"

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
	float GetTime();

private:
	Shader* shader;
	ConstantBuffer constantBuffer;
};