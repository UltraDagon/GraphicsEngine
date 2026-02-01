/*
For now I'm just gonna call this Nogad Engine since it's my name backwards
*/

#include "NogadWin.h"
#include <string>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE: // Exit application if window is closed
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		SetWindowTextW(hWnd, (
			std::wstring(L"KeyDown: ") +
			static_cast<wchar_t>(wParam)).c_str());
		break;

	case WM_KEYUP:
		SetWindowTextW(hWnd, (
			std::wstring(L"KeyUp: ") +
			static_cast<wchar_t>(wParam)).c_str());
		break;
	case WM_CHAR: // Use this for taking in text input
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	const auto pClassName = L"HelloWorld";
	// Register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// Create window instance
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		L"Hello, World! Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	// Show window
	ShowWindow(hWnd, SW_SHOW);

	// Message pump
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Return -1 if error, otherwise return window exit status
	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}