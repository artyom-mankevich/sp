// SP_lab6.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab6.h"
#include <string> 
#include <atlstr.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB6, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB6));
	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB6));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB6);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

DWORD CALLBACK drawFirst(HWND hWnd) {
	int speed = 5;
	RECT rc;
	HDC hdc = GetDC(hWnd);
	GetClientRect(hWnd, &rc);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(0, 200, 0));
	while (TRUE) {
		Rectangle(hdc, 150, 0, 300, speed);
		Sleep(100);
		speed += 10;
		if (speed > rc.bottom) break;
	}
	return 0;
}

DWORD CALLBACK drawSecond(HWND hWnd) {
	int speed = 5;
	RECT rc;
	HDC hdc = GetDC(hWnd);
	GetClientRect(hWnd, &rc);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(200, 0, 0));
	while (TRUE) {
		Rectangle(hdc, 300, 0, 450, speed);
		Sleep(100);
		speed += 10;
		if (speed > rc.bottom) break;
	}
	return 0;
}

DWORD CALLBACK drawThird(HWND hWnd) {
	int speed = 5;
	RECT rc;
	HDC hdc = GetDC(hWnd);
	GetClientRect(hWnd, &rc);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(0, 0, 200));
	while (TRUE) {
		Rectangle(hdc, 450, 0, 600, speed);
		Sleep(100);
		speed += 10;
		if (speed > rc.bottom) break;
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND btn_start;
	static HWND btn_stop;

	static HANDLE thread_handle_1;
	static HANDLE thread_handle_2;
	static HANDLE thread_handle_3;

	switch (message)
	{
	case WM_CREATE:
	{
		btn_start = CreateWindow(L"button", L"Start",
			WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON,
			0, 0, 100, 30, hWnd, (HMENU)1, hInst, NULL);
		btn_stop = CreateWindow(L"button", L"Stop",
			WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON,
			0, 30, 100, 30, hWnd, (HMENU)2, hInst, NULL);


		thread_handle_1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)drawFirst, hWnd, CREATE_SUSPENDED, NULL);
		thread_handle_2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)drawSecond, hWnd, CREATE_SUSPENDED, NULL);
		thread_handle_3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)drawThird, hWnd, CREATE_SUSPENDED, NULL);


	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case 1:
			ResumeThread(thread_handle_1);
			ResumeThread(thread_handle_2);
			ResumeThread(thread_handle_3);
			break;
		case 2:
			SuspendThread(thread_handle_1);
			SuspendThread(thread_handle_2);
			SuspendThread(thread_handle_3);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
