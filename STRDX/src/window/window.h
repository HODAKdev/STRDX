#pragma once

#include <string>
#include <Windows.h>

// settings
#define WINDOW_NAME L"STRDX"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_COLOR RGB(0, 0, 0)
#define WINDOW_ENABLE_RESIZE FALSE
#define WINDOW_ENABLE_DARKMODE_TITLE_BAR TRUE

class Window
{
public:
	Window() : hwnd(NULL) {}

public:
	static Window* GetSingleton();

public:
	bool Create();
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
	void Center();
	std::wstring GetTitle();

private:
	static LRESULT CALLBACK Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND hwnd;
};