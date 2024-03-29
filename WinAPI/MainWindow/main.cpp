﻿#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyFirstWindow";
//g_ - Global, i - Int 
CONST INT g_i_BTN_SIZE = 50;	//размер кнопки
CONST INT g_i_DISTANCE = 10;	//Расстояние между кнопками
CONST INT g_i_START_X = 10;	//Отступ от начала окна
CONST INT g_i_START_Y = 10;	//Отступ от начала окна
CONST INT g_i_DISPLAY_WIDTH = (g_i_BTN_SIZE * 5 + g_i_DISTANCE * 4);
CONST INT g_i_DISPLAY_HEIGHT = 32;
CONST CHAR g_sz_DISPLAY_FONT[] = "Tahoma";
CONST INT g_i_DISPLAY_FONT_HEIGHT = g_i_DISPLAY_HEIGHT - 2;
CONST INT g_i_DISPLAY_FONT_WIDTH = g_i_DISPLAY_FONT_HEIGHT / 2.5;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);	//Размер класса в Байтах (cb - Count Bytes)
	wc.cbClsExtra = 0;		//Class ExtraBytes дополнительные Байты класса
	wc.cbWndExtra = 0;		//WindowExtraBytes дополнительные Байты окна
	wc.style = 0;

	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_PALM));		//Отображается в панели задач
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_STAR));	//Отображается в заголовке окна

	wc.hIcon = (HICON)LoadImage(hInstance, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "star.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	wc.hCursor = (HCURSOR)LoadImage(hInstance, "starcraft_background.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	//wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hbrBackground = CreateSolidBrush(RGB(0,0,200));

	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_MY_WINDOW_CLASS;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Класс не зарегистрирован", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна

	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	//INT window_width = screen_width * 3 / 4;
	//INT window_height = screen_height * 3 / 4;
	INT window_width = g_i_START_X * 2 + g_i_DISPLAY_WIDTH + 16;
	INT window_height = g_i_START_Y * 2 + g_i_DISPLAY_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 4 + 35;

	INT start_x = screen_width / 8;
	INT start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		0,
		g_sz_MY_WINDOW_CLASS,	//Имя класса окна
		g_sz_MY_WINDOW_CLASS,	//Заголовок окна
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		//WS_OVERLAPPEDWINDOW,	//Стриль окна для главного окна программы всегда быдет WS_OVERLAPPEDWINDOW
								//WS_OVERLAPPEDWINDOW - это окно верхнего уровня (TOP_LEVEL_WINDOW), которое включает в себя дочерние окна (CHILDWINDOW)
		start_x, start_y,		//Начальная позиция окна
		window_width, window_height,	//Размер окна
		NULL,	//Parent Window
		NULL,	//Для главного окна это меню, для дочернего окна это ID его ресурса (IDC_EDIT)
		hInstance,
		NULL
	);
	if (hwnd == 0)
	{
		MessageBox(NULL, "Окно небыло создано", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	//задает режим отображения окна
	UpdateWindow(hwnd);	//Выполняет прорисовку окна

	//3) Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);	//Транслирует сообщения виртуальных клавиш в символные сообщения
		DispatchMessage(&msg);	//Отправляет сообщение процедуре окна. Сообщение берет от GetMessage();
	}

	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//SetFocus(hwnd);
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx
		(
			NULL, //exStyle
			"Edit",
			"0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT /*| ES_READONLY*/,
			g_i_START_X, g_i_START_Y,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd, (HMENU)IDC_EDIT, GetModuleHandle(NULL), NULL
		);
		/*LOGFONT lFont;
		ZeroMemory(&lFont, sizeof(LOGFONT));
		lFont.lfCharSet = DEFAULT_CHARSET;
		lFont.lfHeight = -20;
		HFONT hFont = CreateFontIndirect(&lFont);*/
		HFONT hFont = CreateFont
		(
			g_i_DISPLAY_FONT_HEIGHT, g_i_DISPLAY_FONT_WIDTH,	//Height, Width
			GM_ADVANCED, 0, 600,	//Escapement, Orientation, Weight - Толщина шрифта
			FALSE, FALSE, FALSE,	//Italic - Курсив, Underline - Подчеркнутый, Strikeout - Перечеркнутый
			DEFAULT_CHARSET,
			OUT_CHARACTER_PRECIS,
			CLIP_CHARACTER_PRECIS,
			ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			g_sz_DISPLAY_FONT
		);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);

		
		CHAR sz_btn_name[] = "0";
		INT number = 1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//https://learn.microsoft.com/en-us/windows/win32/controls/button-styles
				sz_btn_name[0] = number + 48;
				HWND hButtonDigit = CreateWindowEx
				(
					NULL,
					"Button",
					sz_btn_name,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
					g_i_START_X /*+ g_i_DISTANCE*/ + (g_i_BTN_SIZE + g_i_DISTANCE)*j,
					g_i_START_Y + g_i_DISTANCE + (g_i_BTN_SIZE + g_i_DISTANCE)*(2 - i) + g_i_DISPLAY_HEIGHT,
					g_i_BTN_SIZE, g_i_BTN_SIZE,
					hwnd,
					(HMENU)(number + 1000),
					GetModuleHandle(NULL),
					NULL
				);
				SendMessage
				(
					hButtonDigit, BM_SETIMAGE, IMAGE_ICON,
					(LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(number + 200))
				);
				number++;
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X, g_i_START_Y + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISPLAY_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE * 2 + g_i_DISTANCE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL), NULL
		);
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		CreateWindowEx
		(
			NULL, "BUTTON", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 2,
			g_i_START_Y + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISPLAY_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL), NULL
		);
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "/",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3, g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_SLASH,
			GetModuleHandle(NULL), NULL
		);
		HWND hBtnAster = CreateWindowEx
		(
			NULL, "Button", "*",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE * 2),
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_ASTER,
			GetModuleHandle(NULL), NULL
		);
		HICON hIconAster = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_STAR));
		SendMessage(hBtnAster, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconAster);
		CreateWindowEx
		(
			NULL, "Button", "-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISTANCE * 3 + g_i_BTN_SIZE * 2,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_MINUS,
			GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "+",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISTANCE + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,

			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_PLUS,
			GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 4,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE,
			g_i_BTN_SIZE * 2 + g_i_DISTANCE,
			hwnd, (HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 4,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISTANCE * 3 + g_i_BTN_SIZE * 2,

			g_i_BTN_SIZE,
			g_i_BTN_SIZE * 2 + g_i_DISTANCE,

			hwnd, (HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL), NULL
		);

	}
	break;
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		SetBkMode(hdc, OPAQUE);
		SetBkColor(hdc, RGB(0, 0, 100));
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
		SetTextColor(hdc, RGB(255, 0, 0));
		return (LRESULT)hBrush;
	}
	break;
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;	//Прямоугольник
		GetWindowRect(hwnd, &rect);	//Получаем прямоугольник окна
		//&rect - взятие адреса в памяти 'rect'

		//INT start_x = rect.left;
		//INT start_y = rect.top;
		INT width = rect.right - rect.left;
		INT height = rect.bottom - rect.top;

		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = "Have a nive day";

		sprintf(sz_buffer, "%s, Size: %ix%i, Position: %ix%i", g_sz_MY_WINDOW_CLASS, width, height, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;
	case WM_COMMAND:
	{
		//SendMessage(hwnd, WM_SETFOCUS, NULL, NULL);
		SetFocus(hwnd);
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		CHAR sz_digit[2] = {};
		static double a = 0;
		static double b = 0;
		static bool stored = false;
		static bool input = false;
		static bool operation_input = false;
		static char operation = 0;
		//static char old_operation = 0;
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			input = true;
			if (stored)
			{
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
				stored = false;
			}
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			while (sz_buffer[0] == '0')
			{
				for (int i = 0; i < sz_buffer[i]; i++)
					sz_buffer[i] = sz_buffer[i + 1];
			}
			sz_digit[0] = LOWORD(wParam) - 1000 + '0';
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (strchr(sz_buffer, '.'))break;
			sz_digit[0] = '.';
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"0");
			a = b = 0;
			stored = false;
			input = false;
			operation_input = false;
			operation = 0;
			//SendMessage(hwnd, WM_SETFOCUS, NULL, NULL);	//DOESN'T WORK
			//SetFocus(hwnd);
		}
		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (input)b = strtod(sz_buffer, NULL);
			if (a == 0)
				a = b;
			stored = true;
			if (input && operation_input)
			{
				SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0);
			}
			input = false;
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON_PLUS:	operation = '+'; break;
			case IDC_BUTTON_MINUS:	operation = '-'; break;
			case IDC_BUTTON_ASTER:	operation = '*'; break;
			case IDC_BUTTON_SLASH:	operation = '/'; break;
			}
			operation_input = true;
		}
		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (input)
				b = strtod(sz_buffer, NULL);
			input = false;
			switch (operation)
			{
			case '+': a += b; break;
			case '-': a -= b; break;
			case '*': a *= b; break;
			case '/': a /= b; break;
			}
			//old_operation = operation;
			operation_input = false;
			sprintf(sz_buffer, "%g", a);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
	}
	break;
	case WM_KEYDOWN:
	{
		//char symbol[2]{};
		//symbol[0] = LOWORD(wParam);
		//MessageBox(hwnd, symbol, "Symbol", MB_OK);

		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (wParam == 0x38)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
		}
		else
		{
			if (wParam >= 0x30 && wParam <= 0x39)
				SendMessage(hwnd, WM_COMMAND, wParam - 0x30 + 1000, 0);

		}
		if (wParam >= 0x60 && wParam <= 0x69)
			SendMessage(hwnd, WM_COMMAND, wParam - 0x60 + 1000, 0);

		//if(GetKeyState(0x38) & 0x8000)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
		switch (LOWORD(wParam))
		{
		case VK_OEM_PLUS:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_PLUS, 0);  break;
		case VK_OEM_MINUS:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_MINUS, 0); break;
			//case 0x09:
		case VK_MULTIPLY:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0); break;
		case VK_OEM_2:
		case VK_DIVIDE:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SLASH, 0); break;
		case VK_RETURN:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0); break;
		}
		//if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(0x38) & 0x8000)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);

		if (wParam == VK_OEM_PERIOD)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_POINT, 0);

		/*if (wParam >= 0x30 && wParam <= 0x39)
		{
			SendMessage(hwnd, WM_COMMAND, wParam - 0x30 + 1000, 0);
		}*/

	}
	break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:
		//if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
		DestroyWindow(hwnd); //Функция DestroyWindow() уничтожает окно
		//Конкретно здесь, функция DestroyWindow() посылает окну вообщение WM_DESTROY
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}