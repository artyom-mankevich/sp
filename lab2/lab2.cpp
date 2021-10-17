// SP_lab2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR titleBarText[MAX_LOADSTRING];                  // The title bar text
WCHAR windowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                rRegisterClass(HINSTANCE hInstance);
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
	LoadStringW(hInstance, IDS_APP_TITLE, titleBarText, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB2, windowClass, MAX_LOADSTRING);
	rRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

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



ATOM rRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB2);
	wcex.lpszClassName = windowClass;
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

	HWND hWnd = CreateWindowW(windowClass, titleBarText, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
void del(HWND box)
{
	int pos = SendMessage(box, LB_GETCURSEL, 0, 0L);

	if (pos != -1) {
		SendMessage(box, LB_DELETESTRING, (WPARAM)pos, 0L);
	}
	else return;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;

	static HWND leftList;
	static HWND rightList;
	static HWND btn_add;
	static HWND btn_clear;
	static HWND btn_toRight;
	static HWND btn_delete;
	static HWND edit_Input;

	switch (message)
	{
	case WM_CREATE:
	{
		SetWindowPos(hWnd, nullptr, 300, 100, 800, 500, SWP_SHOWWINDOW);
		btn_add = CreateWindow(L"button", L"Add",
			WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON,
			80, 30, 80, 30,
			hWnd, (HMENU)1, hInst, NULL);
		
		btn_delete = CreateWindow(L"button", L"Delete",
			WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON,
			190, 30, 80, 30,
			hWnd, (HMENU)4, hInst, NULL);

		btn_clear = CreateWindow(L"button", L"Clear",
			WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON,
			80, 80, 80, 30,
			hWnd, (HMENU)2, hInst, NULL);

		btn_toRight = CreateWindow(L"button", L"ToRight",
			WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON,
			190, 80, 80, 30,
			hWnd, (HMENU)3, hInst, NULL);

		edit_Input = CreateWindow(L"edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_LEFT,
			80, 120, 190, 30,
			hWnd, NULL, hInst, NULL);


		GetClientRect(hWnd, &rc);
		leftList = CreateWindow(L"listbox", NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD,
			300, 30, 200, 400,
			hWnd, NULL, hInst, NULL);
		rightList = CreateWindow(L"listbox", NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD,
			510, 30, 200, 400,
			hWnd, NULL, hInst, NULL);


	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case 1: //add
			TCHAR ch[128];
			WORD txt;

			txt = SendMessage(edit_Input, EM_GETLINE, 0, (LPARAM)(LPSTR)ch);
			ch[txt] = '\0';

			if (SendMessage(leftList, LB_FINDSTRINGEXACT, 0, (LPARAM)(LPSTR)ch) != -1) break;

			SendMessage(leftList, LB_ADDSTRING, 0, (LPARAM)(LPSTR)ch);
			break;

		case 2: //clear
			SendMessage(leftList, LB_RESETCONTENT, 0, 0L);
			SendMessage(rightList, LB_RESETCONTENT, 0, 0L);
			break;

		case 3: //to right
			INT pos;

			pos = SendMessage(leftList, LB_GETCURSEL, 0, 0L);

			if (pos == -1) break;

			*(WORD*)ch = sizeof(ch) - 1;

			SendMessage(leftList, LB_GETTEXT, (WPARAM)pos, (LPARAM)(LPSTR)ch);

			if (SendMessage(rightList, LB_FINDSTRINGEXACT, 0, (LPARAM)(LPSTR)ch) != -1) break;

			SendMessage(rightList, LB_ADDSTRING, 0, (LPARAM)(LPSTR)ch);
			break;

		case 4: //del
			del(leftList);
			del(rightList);
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
