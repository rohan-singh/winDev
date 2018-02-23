#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

// forward declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
/*
* There are four parameters:
* hwnd is a handle to the window.
* uMsg is the message code; for example, the WM_SIZE message indicates the window was resized.
* wParam and lParam contain additional data that pertains to the message. The exact meaning depends on the message code.
* LRESULT is an integer value that your program returns to Windows. It contains your program's response to a particular message.
* The meaning of this value depends on the message code. CALLBACK is the calling convention for the function.
*/

// main function
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
/*
* The four parameters are :
 * hInstance is something called a "handle to an instance" or "handle to a module." The operating system uses this value to identify the executable(EXE) when it is loaded in memory.The instance handle is needed for certain Windows functions — for example, to load icons or bitmaps.
 * hPrevInstance has no meaning.It was used in 16 - bit Windows, but is now always zero.
 * pCmdLine contains the command - line arguments as a Unicode string.
 * nCmdShow is a flag that says whether the main application window will be minimized, maximized, or shown normally.
*/
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc; //ptr to an application-defined func called window procedure(defines most of the window behaviour)
	wc.hInstance = hInstance; //handle to the application instance
	wc.lpszClassName = CLASS_NAME; //string that identifies the window class

	RegisterClass(&wc); //registers window class to the operating system 

	// Create the window.
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

										// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); //calls the window procedure of the window that is the target of the message
		//PostQuitMessage(0);
	}

	return 0;
}

// message handler
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// painting the window : fills the entire client area with a solid color
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0); //puts a WM_QUIT message on the message queue, causing the message loop to end.
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);//his function clears the update region, which signals to Windows that the window has completed painting itself.
		}
		return 0;

		case WM_CLOSE:
			if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hwnd);
			}
			// Else: User canceled. Do nothing.
			return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
