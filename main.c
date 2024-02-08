#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define BUTTON_EXIT 0
#define BUTTON_OSSZEG 1
#define BUTTON_SZAMA 2
#define BUTTON_MINIMUM 3
#define BUTTON_MAXIMUM 4
#define BUTTON_TUKOR 5
#define BUTTON_DUPLAZOTT 6

#include <Windows.h>
#include <stdio.h>
#include <string.h>

HFONT font;

BOOL isNumeric(const char* str) {
	while (*str) {
		if (*str < '0' || *str > '9')
			return FALSE;
		str++;
	}

	return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	static HWND groupBox;
	static HWND inputBox;
	static HWND listBox;

	HWND buttonOsszeg, buttonSzama, buttonMin, buttonMax, buttonTukor, buttonDuplazott;
	HWND buttonExit;

	if (message == WM_CREATE) {
		groupBox = CreateWindowA(
			"BUTTON",
			"Szam",
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
			10, 10, 315, 50,
			hwnd, NULL, NULL, NULL
		);

		SendMessageA(groupBox, WM_SETFONT, (WPARAM)font, TRUE);

		inputBox = CreateWindowA(
			"EDIT",
			NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
			10, 20, 295, 20,
			groupBox, NULL, NULL, NULL
		);

		SendMessageA(inputBox, WM_SETFONT, (WPARAM)font, TRUE);

		// BUTTONS
		buttonOsszeg = CreateWindowA(
			"BUTTON",
			"Osszeg",
			WS_VISIBLE | WS_CHILD,
			10, 65, 150, 25,
			hwnd, (HMENU)BUTTON_OSSZEG, NULL, NULL
		);

		SendMessageA(buttonOsszeg, WM_SETFONT, (WPARAM)font, TRUE);

		buttonSzama = CreateWindowA(
			"BUTTON",
			"Szama",
			WS_VISIBLE | WS_CHILD,
			175, 65, 150, 25,
			hwnd, (HMENU)BUTTON_SZAMA, NULL, NULL
		);

		SendMessageA(buttonSzama, WM_SETFONT, (WPARAM)font, TRUE);

		buttonMin = CreateWindowA(
			"BUTTON",
			"Minimum",
			WS_VISIBLE | WS_CHILD,
			10, 95, 150, 25,
			hwnd, (HMENU)BUTTON_MINIMUM, NULL, NULL
		);

		SendMessageA(buttonMin, WM_SETFONT, (WPARAM)font, TRUE);

		buttonMax = CreateWindowA(
			"BUTTON",
			"Maximum",
			WS_VISIBLE | WS_CHILD,
			175, 95, 150, 25,
			hwnd, (HMENU)BUTTON_MAXIMUM, NULL, NULL
		);

		SendMessageA(buttonMax, WM_SETFONT, (WPARAM)font, TRUE);

		buttonTukor = CreateWindowA(
			"BUTTON",
			"Tukor",
			WS_VISIBLE | WS_CHILD,
			10, 125, 150, 25,
			hwnd, (HMENU)BUTTON_TUKOR, NULL, NULL
		);

		SendMessageA(buttonTukor, WM_SETFONT, (WPARAM)font, TRUE);

		buttonDuplazott = CreateWindowA(
			"BUTTON",
			"Duplazott",
			WS_VISIBLE | WS_CHILD,
			175, 125, 150, 25,
			hwnd, (HMENU)BUTTON_DUPLAZOTT, NULL, NULL
		);

		SendMessageA(buttonDuplazott, WM_SETFONT, (WPARAM)font, TRUE);

		listBox = CreateWindowA(
			"LISTBOX",
			NULL,
			WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY | LBS_SORT,
			10, 155, 315, 150,
			hwnd, (HMENU)-1, NULL, NULL
		);

		SendMessageA(listBox, WM_SETFONT, (WPARAM)font, TRUE);

		buttonExit = CreateWindowA(
			"BUTTON",
			"Exit",
			WS_VISIBLE | WS_CHILD,
			10, 305, 315, 25,
			hwnd, (HMENU)BUTTON_EXIT, NULL, NULL
		);

		SendMessageA(buttonExit, WM_SETFONT, (WPARAM)font, TRUE);
	}
	else if (message == WM_COMMAND) {
		int button = LOWORD(wparam);

		if (button == BUTTON_EXIT) {
			DestroyWindow(hwnd);
		}
		else if (button == BUTTON_OSSZEG) {
			char input[100];

			GetWindowTextA(GetDlgItem(groupBox, 0), input, 100);
			
			if (strlen(input) != 0 && isNumeric(input)) {
				int x = atoi(input);
				int ox = x;
				int r, s = 0;

				do {
					r = x % 10;
					s += r;
					x /= 10;
				} while (x != 0);

				char output[100];
				snprintf(output, 100, "Osszeg (%d): %d", ox, s);

				SendMessageA(listBox, LB_INSERTSTRING, -1, (LPARAM)output);
			}
		}
		else if (button == BUTTON_SZAMA) {
			char input[100];

			GetWindowTextA(GetDlgItem(groupBox, 0), input, 100);

			if (strlen(input) != 0 && isNumeric(input)) {
				int x = atoi(input);
				int ox = x;
				int k = 0;

				do {
					k++;
					x /= 10;
				} while (x != 0);

				char output[100];
				
				snprintf(output, 100, "Szama (%d): %d", ox, k);

				SendMessageA(listBox, LB_INSERTSTRING, -1, (LPARAM)output);
			}
		}
		else if (button == BUTTON_MINIMUM) {
			char input[100];

			GetWindowTextA(GetDlgItem(groupBox, 0), input, 100);

			if (strlen(input) != 0 && isNumeric(input)) {
				int x = atoi(input);
				int ox = x;
				int r, min = x;

				do {
					r = x % 10;

					if(r < min)
						min = r;

					x /= 10;
				} while (x != 0);

				char output[100];
				
				snprintf(output, 100, "Minimum (%d): %d", ox, min);

				SendMessageA(listBox, LB_INSERTSTRING, -1, (LPARAM)output);
			}
		}
		else if (button == BUTTON_MAXIMUM) {
			char input[100];

			GetWindowTextA(GetDlgItem(groupBox, 0), input, 100);

			if (strlen(input) != 0 && isNumeric(input)) {
				int x = atoi(input);
				int ox = x;
				int r, max = 0;

				do {
					r = x % 10;

					if (r > max)
						max = r;

					x /= 10;
				} while (x != 0);

				char output[100];
				
				snprintf(output, 100, "Maximum (%d): %d", ox, max);

				SendMessageA(listBox, LB_INSERTSTRING, -1, (LPARAM)output);
			}
		}
		else if (button == BUTTON_TUKOR) {
			char input[100];

			GetWindowTextA(GetDlgItem(groupBox, 0), input, 100);

			if (strlen(input) != 0 && isNumeric(input)) {
				int x = atoi(input);
				int ox = x;
				int r, t = 0;

				do {
					r = x % 10;
					t = t * 10 + r;
					x /= 10;
				} while (x != 0);

				char output[100];

				snprintf(output, 100, "Tukor (%d): %d", ox, t);

				SendMessageA(listBox, LB_INSERTSTRING, -1, (LPARAM)output);
			}
		}
		else if (button == BUTTON_DUPLAZOTT) {
			char input[100];

			GetWindowTextA(GetDlgItem(groupBox, 0), input, 100);

			if (strlen(input) != 0 && isNumeric(input)) {
				int x = atoi(input);
				int ox = x;
				int r, y = 0, p = 1;

				do {
					r = x % 10;
					y = y + r * p;
					p = p * 10;
					y = y + r * p;
					p = p * 10;
					x /= 10;
				} while (x != 0);

				char output[100];
				
				snprintf(output, 100, "Duplazott (%d): %d", ox, y);

				SendMessageA(listBox, LB_INSERTSTRING, -1, (LPARAM)output);
			}
		}
	}
	else if (message == WM_CLOSE) {
		DestroyWindow(hwnd);
	}
	else if (message == WM_DESTROY) {
		PostQuitMessage(0);
	}
	else {
		return DefWindowProcA(hwnd, message, wparam, lparam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	const char* szClassName = "DefaultClass";
	const char* szWindowName = "Szam";

	WNDCLASSEXA c;
	c.cbSize = sizeof(WNDCLASSEXA);
	c.lpfnWndProc = WindowProc;
	c.lpszClassName = szClassName;
	c.style = CS_HREDRAW | CS_VREDRAW;
	c.cbClsExtra = 0;
	c.cbWndExtra = 0;
	c.hInstance = NULL;
	c.hIcon = 0;
	c.hCursor = 0;
	c.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
	c.lpszMenuName = NULL;
	c.hIconSm = 0;

	RegisterClassExA(&c);

	LOGFONTA lf;
	GetObjectA(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	font = CreateFontA(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	HWND mainWindow = CreateWindowExA(NULL,
		szClassName, szWindowName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		GetSystemMetrics(SM_CXSCREEN) / 2 - 190,
		GetSystemMetrics(SM_CYSCREEN) / 2 - 200,
		350, 375,
		NULL, NULL,
		GetModuleHandleA(NULL), NULL);

	SendMessageA(mainWindow, WM_SETFONT, (WPARAM)font, TRUE);

	ShowWindow(mainWindow, SW_SHOW);
	UpdateWindow(mainWindow);

	MSG msg;
	while (GetMessageA(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;
}


