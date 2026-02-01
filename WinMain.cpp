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
	// Create window
	Window wnd;

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

	return msg.wParam;
}