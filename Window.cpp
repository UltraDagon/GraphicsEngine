#include "Window.h"

Window::Window() noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
	// Register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// Calculate window size based on desired canvas size
	RECT canvasRect;
	canvasRect.left = 100;
	canvasRect.right = width + canvasRect.left;
	canvasRect.top = 100;
	canvasRect.bottom = height + canvasRect.top;
	AdjustWindowRect(&canvasRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	// Create window instance
	hWnd = CreateWindowW(
		pClassName,
		L"Hello, World! Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, canvasRect.right - canvasRect.left, canvasRect.bottom - canvasRect.top,
		nullptr, nullptr, hInst, this
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
	UnregisterClass(pClassName, hInst);
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		// Extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// Set WinAPI managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// Set message proc to normal handler now
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// Retrieve ptr to window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// Forward message to window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE: // Exit application if window is closed
		PostQuitMessage(0);
		return 0;

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