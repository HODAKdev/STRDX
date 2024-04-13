#pragma once

struct XYZRGBA
{
public:
	XYZRGBA() : x(0), y(0), z(0), r(0), g(0), b(0), a(0) {}
	XYZRGBA(float x, float y, float z) : x(x), y(y), z(z), r(0), g(0), b(0), a(0) {}
	XYZRGBA(float x, float y, float z, float r, float g, float b, float a) : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}

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

struct XYZTEX
{
public:
	XYZTEX() : x(0), y(0), z(0), a(0), b(0) {}
	XYZTEX(float x, float y, float z, float a, float b) : x(x), y(y), z(z), a(a), b(b) {}

private:
	float x;
	float y;
	float z;

private:
	float a;
	float b;
};