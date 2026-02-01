#pragma once
#include "NogadWin.h"
#include <string>

class Window {
private:
	static constexpr const wchar_t* pClassName = L"NogadEngine";
	static constexpr const int width = 640;
	static constexpr const int height = 480;
	//// Only want one window
	//static Window window;
	HINSTANCE hInst;
	HWND hWnd;

public:
	Window() noexcept;
	~Window();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
};