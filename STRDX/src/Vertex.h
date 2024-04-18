#pragma once

// float3
struct POS
{
public:
	POS() : x(0.0f), y(0.0f), z(0.0f) {}
	POS(float x, float y, float z) : x(x), y(y), z(z) {}

private:
	float x;
	float y;
	float z;
};

// float3, float4
struct POSCOL
{
public:
	POSCOL() : x(0.0f), y(0.0f), z(0.0f), r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
	POSCOL(float x, float y, float z, float r, float g, float b, float a) : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}

private:
	float x;
	float y;
	float z;

private:
	float r;
	float g;
	float b;
	float a;
};

// float3, float2
struct POSTEX
{
public:
	POSTEX() : x(0.0f), y(0.0f), z(0.0f), v(0.0f), w(0.0f) {}
	POSTEX(float x, float y, float z, float v, float w) : x(x), y(y), z(z), v(v), w(w) {}

private:
	float x;
	float y;
	float z;

private:
	float v;
	float w;
};