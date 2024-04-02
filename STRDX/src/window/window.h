#pragma once

#include <string>
#include <Windows.h>

class Window
{
public:
	Window() : hwnd(NULL) {}

public:
	static Window* GetSingleton();

public:
	bool Create(std::wstring name, UINT width, UINT height, UINT r, UINT g, UINT b, bool resize);
	HWND GetHandle();
	void Show();
	void Hide();
	void Maximize();
	void Minimize();
	void Restore();
	void Focus();
	void Release();
	void Update();
	UINT GetClientWidth();
	UINT GetClientHeight();
	UINT GetWidth();
	UINT GetHeight();
	void Move(UINT x, UINT y);
	void ShowCursor();
	void HideCursor();
	void SetCursorPos(UINT x, UINT y);
	void SetTitle(std::wstring title);
	void EnableDarkMode();
	void Center();
	std::wstring GetTitle();

private:
	static LRESULT CALLBACK Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND hwnd;
};