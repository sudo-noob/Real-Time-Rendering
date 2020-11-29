// Headers
#include<windows.h>
#include"Icon.h"
#include<stdio.h>

// new macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global function declartions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
FILE* gpfile = NULL;

//global variable declarations
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
bool gbFullScreen = false;
bool gbActiveWindow = false;
HWND ghwnd = NULL;

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function declaration
	void initialize(void);
	void display(void);

	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	bool BDone = false;

	UINT iWindowWidth = 800;
	UINT iWindowHeight = 600;
	UINT X, Y;
	
	// file IO
	if (fopen_s(&gpfile, "SSMLog.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Cannot create desired file \n"), ERROR, MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpfile, "Log file successfully created and program started successfully \n");
	}

	//code
	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));

	// register above class
	RegisterClassEx(&wndclass);

	// height & width calculation
	X = GetSystemMetrics(SM_CXSCREEN);
	Y = GetSystemMetrics(SM_CYSCREEN);

	X = (X - iWindowWidth) / 2;
	Y = (Y - iWindowHeight) / 2;

	// create window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName,
		TEXT("My Application"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		X,
		Y,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	initialize();
	
	ShowWindow(hwnd, iCmdShow);
	
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	
	// message loop / game loop
	while (BDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				BDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				//here you should call update funtion for OpenGL rendering

				//here you should call dispaly funtion for OpenGL rendering
				display();
			}
		}
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)

{
	//function declaration
	void ToggleFullScreen(void);
	void Resize(int, int);
	void Uninitialize(void);

	switch (iMsg)
	{
	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;
	
	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;
	
	case WM_ERASEBKGND:
		return(0);
	
	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));			// LOWORD = height & HIWORD = width
		break;
	
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;

		case 0x46:
		case 0x66:
			ToggleFullScreen();
			break;
		default:
			break;
		}
		break;

	case WM_CREATE:
		fprintf(gpfile, "India is my country.\n");
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	
	case WM_DESTROY:
		fprintf(gpfile, "Jay Hind.\n");

		Uninitialize();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

// Function Declartion
void ToggleFullScreen(void)
{
	//local variable declaration
	MONITORINFO mi = { sizeof(MONITORINFO) };

	//code
	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
		gbFullScreen = true;
	}

	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
		gbFullScreen = false;
	}
}

void initialize(void)
{
	//funtion declaration
	void Resize(int, int);

	// variable declaration

	//code
	Resize(WIN_WIDTH, WIN_HEIGHT);		//warmup call to resize
}

void Resize(int width, int height)
{
	//code
	if (height == 0)
		height = 1;
}

void display(void)
{
	//code

}

void Uninitialize(void)
{
	//code
	if (gpfile)
	{
		fprintf(gpfile, "Log file closed successfully program is completed successfully. \n");
		fclose(gpfile);
		gpfile = NULL;
	}
}
