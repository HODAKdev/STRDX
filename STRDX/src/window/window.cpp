#include "window.h"
#include <dwmapi.h>

Window* Window::GetSingleton()
{
	static Window window;
	return &window;
}
bool Window::Create(std::wstring name, UINT width, UINT height, UINT r, UINT g, UINT b, bool resize)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Proc;
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(r, g, b));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = name.c_str();
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
		return false;

	hwnd = CreateWindowEx(NULL,
		                  name.c_str(),
		                  name.c_str(),
		                  resize ? WS_OVERLAPPEDWINDOW : (WS_OVERLAPPED |
			                                              WS_CAPTION |
			                                              WS_SYSMENU |
			                                              WS_MINIMIZEBOX),
		                  NULL, NULL,
		                  width, height,
		                  NULL,
		                  NULL,
		                  GetModuleHandle(NULL),
		                  NULL
	);

	if (!hwnd)
		return false;

	return true;
}
LRESULT CALLBACK Window::Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
HWND Window::GetHandle()
{
	return hwnd;
}
void Window::Show()
{
	ShowWindow(hwnd, SW_SHOW);
}
void Window::Hide()
{
	ShowWindow(hwnd, SW_HIDE);
}
void Window::Maximize()
{
	ShowWindow(hwnd, SW_MAXIMIZE);
}
void Window::Minimize()
{
	ShowWindow(hwnd, SW_MINIMIZE);
}
void Window::Restore()
{
	ShowWindow(hwnd, SW_RESTORE);
}
void Window::Focus()
{
	SetFocus(hwnd);
}
void Window::Release()
{
	std::wstring title = GetTitle();
	DestroyWindow(hwnd);
	UnregisterClass(title.c_str(), GetModuleHandle(NULL));
}
void Window::Update()
{
	UpdateWindow(hwnd);
}
UINT Window::GetClientWidth()
{
	RECT rc;
	GetClientRect(hwnd, &rc);
	UINT width = rc.right - rc.left;
	return width;
}
UINT Window::GetClientHeight()
{
	RECT rc;
	GetClientRect(hwnd, &rc);
	UINT height = rc.bottom - rc.top;
	return height;
}
void Window::Move(UINT x, UINT y)
{
	MoveWindow(hwnd,
		       x,
		       y,
		       GetWidth(),
		       GetHeight(),
		       false);
}
void Window::ShowCursor()
{
	::ShowCursor(TRUE);
}
void Window::HideCursor()
{
	::ShowCursor(FALSE);
}
void Window::SetCursorPos(UINT x, UINT y)
{
	::SetCursorPos(x, y);
}
void Window::SetTitle(std::wstring title)
{
	SetWindowText(hwnd, title.c_str());
}
void Window::EnableDarkMode()
{
	BOOL value = TRUE;
	DwmSetWindowAttribute(hwnd,
		                  DWMWA_USE_IMMERSIVE_DARK_MODE,
		                  &value,
		                  sizeof(value));
}
void Window::Center()
{
	UINT x = (GetSystemMetrics(SM_CXSCREEN) - GetWidth()) / 2;
	UINT y = (GetSystemMetrics(SM_CYSCREEN) - GetHeight()) / 2;
	Move(x, y);
}
std::wstring Window::GetTitle()
{
	wchar_t buffer[MAX_PATH];
	GetWindowText(hwnd, buffer, MAX_PATH);
	return std::wstring(buffer);
}
UINT Window::GetWidth()
{
	RECT rect;
	unsigned int width;
	GetWindowRect(hwnd, &rect);
	width = rect.right - rect.left;
	return width;
}
UINT Window::GetHeight()
{
	RECT rect;
	unsigned int height;
	GetWindowRect(hwnd, &rect);
	height = rect.bottom - rect.top;
	return height;
}