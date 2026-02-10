#pragma once
#include "NogadWin.h"
#include "EngineException.h"
#include "Keyboard.h"

class Window {
public:
	class Exception : public EngineException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};

private:
	static constexpr const wchar_t* pClassName = L"NogadEngine";
	HINSTANCE hInst;
	HWND hWnd;

public:
	Window(int width, int height, std::wstring title);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard keyboard;
};


// error exception helper macro
#define ENGWND_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)
#define ENGWND_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError())