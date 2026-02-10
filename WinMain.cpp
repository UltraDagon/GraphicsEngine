/*
For now I'm just gonna call this Nogad Engine since it's my name backwards
*/

#include "NogadWin.h"
#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	try
	{
		// Create window
		Window window(800, 300, L"Awesome window");

		// Message pump
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			// Take in message from Windows
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (window.keyboard.KeyIsPressed(VK_SPACE))
			{
				MessageBox(nullptr, L"SPACE PRESSED", L"SPACE PRESSED!", MB_OK);
			}
		}

		// Return -1 if error, otherwise return window exit status
		if (gResult == -1)
		{
			return -1;
		}

		return msg.wParam;
	}
	catch (const EngineException& e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}