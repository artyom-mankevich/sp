// SP_lab5.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab5.h"

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
	LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB5);
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

typedef struct data {
	int color;
	int figure;
	BOOL isDrawable;
}DATA;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwndServer;

	WIN32_FIND_DATA findData;
	HANDLE hFile;

	DATA dataToSend;

	static HWND red;
	static HWND green;
	static HWND blue;
	static HWND rhombus;
	static HWND square;
	static HWND circle;
	static HWND star;
	static HWND draw;

	switch (message)
	{
	case WM_CREATE:
	{
		SetWindowPos(hWnd, nullptr, 300, 100, 400, 400, SWP_SHOWWINDOW);
		red = CreateWindow(L"button", L"Red", WS_CHILD |
			WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT
			| WS_GROUP | WS_TABSTOP,
			100, 100, 70, 30, hWnd, NULL, hInst, NULL);
		green = CreateWindow(L"button", L"Green", WS_CHILD |
			WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
			100, 140, 70, 30, hWnd, NULL, hInst, NULL);
		blue = CreateWindow(L"button", L"Blue", WS_CHILD |
			WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
			100, 180, 70, 30, hWnd, NULL, hInst, NULL);

		rhombus = CreateWindow(L"button", L"Rhombus", WS_CHILD |
			WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT |
			WS_GROUP | WS_TABSTOP,
			200, 80, 70, 30, hWnd, NULL, hInst, NULL);
		square = CreateWindow(L"button", L"Square", WS_CHILD |
			WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
			200, 120, 70, 30, hWnd, NULL, hInst, NULL);
		circle = CreateWindow(L"button", L"Circle", WS_CHILD |
			WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
			200, 160, 70, 30, hWnd, NULL, hInst, NULL);
		star = CreateWindow(L"button", L"Star", WS_CHILD |
			WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
			200, 200, 70, 30, hWnd, NULL, hInst, NULL);
		draw = CreateWindow(L"button", L"Draw", WS_CHILD |
			WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,
			300, 140, 70, 30, hWnd, NULL, hInst, NULL);
	}
	break;
	case 101:
	{
		if (SendMessage(red, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
			dataToSend.color = 1;
		}
		if (SendMessage(green, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
			dataToSend.color = 2;
		}
		if (SendMessage(blue, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
			dataToSend.color = 3;
		}
		if (SendMessage(rhombus, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
			dataToSend.figure = 1;
		}
		if (SendMessage(square, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
			dataToSend.figure = 2;
		}
		if (SendMessage(circle, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
			dataToSend.figure = 3;
		}
		if (SendMessage(star, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
			dataToSend.figure = 4;
		}
		dataToSend.isDrawable = false;
		if (SendMessage(draw, BM_GETCHECK, 0, 0L) == BST_CHECKED)
			dataToSend.isDrawable = true;

		COPYDATASTRUCT MyCDS;

		hwndServer = FindWindow(NULL, L"lab5.2");
		if (!hwndServer)
		{
			MessageBox(hWnd, L"Error", L"lab5", MB_OK);
			break;
		}
		MyCDS.dwData = 1;
		MyCDS.cbData = sizeof(DATA);
		MyCDS.lpData = &dataToSend;

		SendMessage(hwndServer,
			WM_COPYDATA,
			(WPARAM)(HWND)hWnd,
			(LPARAM)(LPVOID)&MyCDS);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
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
