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
	bool Create(std::wstring _Name, UINT _Width, UINT _Height, UINT _R, UINT _G, UINT _B, bool _Resize);
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
	void Move(UINT _X, UINT _Y);
	void SetTitle(std::wstring _Title);
	void EnableDarkMode();
	void Center();
	std::wstring GetTitle();

private:
	static LRESULT CALLBACK Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND hwnd;
};