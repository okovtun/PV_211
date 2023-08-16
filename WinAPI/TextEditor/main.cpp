#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<Richedit.h>
#include"resource.h"

CONST CHAR g_sz_CLASS_NAME[] = "Text Editor PV_211";
//g_ - Global
//sz_ - string zero
HFONT g_hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
COLORREF g_RGB_Text = RGB(0, 0, 0);

COLORREF g_rgbBackground = RGB(255, 255, 255);
COLORREF g_rgbCustom[16] = {};

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL LoadTextFileToEdit(HWND hEdit, LPCSTR lpszFileName);
BOOL SaveTextFileFromEdit(HWND hEdit, LPCSTR lpszFileName);

VOID SelectFont(HWND hwnd);
VOID SelectColor(HWND hwnd);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	GlobalFree(NULL);
	//1) Регистрация класса окна:
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	wc.hIcon = (HICON)LoadImage(hInstance, "fdd.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "fdd.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = g_sz_CLASS_NAME;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,	//Window Class name
		g_sz_CLASS_NAME,	//Window Title
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,	//Position
		CW_USEDEFAULT, CW_USEDEFAULT,	//Window size
		NULL,	//Parent
		NULL,//(HMENU)IDR_MAIN_MENU// - this value doesn't work,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static CHAR szFileName[MAX_PATH]{};
	static LPSTR lpszFileContent = NULL;
	switch (uMsg)
	{
	case WM_CREATE:
	{
		LoadLibrary("riched20.dll");
		RECT window_rect;
		RECT client_rect;
		GetWindowRect(hwnd, &window_rect);
		GetClientRect(hwnd, &client_rect);
		//MessageBox(hwnd, "Rects aquired", "Info", MB_OK);
		HWND hEdit = CreateWindowEx
		(
			NULL, RICHEDIT_CLASS, "",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, //| WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			0, 0,	//start position
			client_rect.right, client_rect.bottom,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		//Строка состояния:
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
			LPSTR lpszText = new CHAR[dwTextLength + 1]{};
			SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszText);
			if (lpszFileContent && strcmp(lpszFileContent, lpszText) || lpszFileContent == NULL && lpszText[0])
			{
				switch (MessageBox(hwnd, "Сохранить изменения?", "Вопрос", MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDYES:	SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
				case IDNO:	
					//delete[] lpszFileContent;
					GlobalFree(lpszFileContent);
					lpszFileContent = nullptr;
					//ZeroMemory(szFileName, sizeof(szFileName));
					szFileName[0] = 0;
					SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
				case IDCANCEL:break;
				}
			}
			else
			{
				//delete[] lpszFileContent;
				GlobalFree(lpszFileContent);
				lpszFileContent = nullptr;
				//ZeroMemory(szFileName, sizeof(szFileName));
				szFileName[0] = 0;
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
			}
		}
		break;
		case ID_FILE_OPEN:
		{
			//CHAR szFileName[MAX_PATH]{};

			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files: (*.txt)\0*.txt\0All files (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrDefExt = "txt";

			if (GetOpenFileName(&ofn))
			{
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				LoadTextFileToEdit(hEdit, szFileName);
				DWORD dwTextLenght = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
				//GlobalFree(lpszFileContent);
				lpszFileContent = (LPSTR)GlobalAlloc(GPTR, dwTextLenght + 1);
				SendMessage(hEdit, WM_GETTEXT, dwTextLenght + 1, (LPARAM)lpszFileContent);
				//GlobalFree(lpszFileContent);
			}
		}
		break;
		case ID_FILE_SAVE:
		{
			if (szFileName[0] == 0)SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVEAS, 0);
			else
			{
				SaveTextFileFromEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName);
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				DWORD dwTextLenght = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
				//LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLenght + 1);
				/*lpszFileContent[strlen(lpszFileContent) + 0] = 0xfdfdfdfd;
				lpszFileContent[strlen(lpszFileContent) + 1] = 0xfdfdfdfd;
				lpszFileContent[strlen(lpszFileContent) + 2] = 0xfdfdfdfd;
				lpszFileContent[strlen(lpszFileContent) + 3] = 0xfdfdfdfd;*/
				//GlobalFree(lpszFileContent);
				lpszFileContent = (LPSTR)GlobalAlloc(GPTR, dwTextLenght + 1);
				SendMessage(hEdit, WM_GETTEXT, dwTextLenght + 1, (LPARAM)lpszFileContent);
				//strcpy(lpszFileContent, lpszText);
			}
		}
		break;
		case ID_FILE_SAVEAS:
		{
			//CHAR szFileName[MAX_PATH] = {};

			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0AllFiles (*.*)\0*.*\0";	//Double NULL-Terminated line
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "txt";

			if (GetSaveFileName(&ofn))SaveTextFileFromEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName);
		}
		break;
		case ID_FORMAT_FONT:	SelectFont(hwnd);	break;
		case ID_FORMAT_COLOR:	SelectColor(hwnd);	break;
		}
	}
	break;
	case WM_DESTROY:PostQuitMessage(0); break;
	case WM_CLOSE:
	{
		//CHAR sz_buffer[INT_MAX/2] = {};
		BOOL close = FALSE;
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
		LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
		if (lpszText != NULL)
		{
			SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszText);

			if (lpszFileContent && strcmp(lpszFileContent, lpszText) || lpszFileContent == NULL && lpszText[0])
			{
				switch (MessageBox(hwnd, "Сохранить изменения?", "Вопрос", MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDYES:		SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
				case IDNO:		close = TRUE;
					//case IDCANCEL:	return DefWindowProc(hwnd, uMsg, wParam, lParam);	break;
				}
			}
			else
			{
				close = TRUE;
			}
			GlobalFree(lpszText);
			GlobalFree(lpszFileContent);
		}
		//else DestroyWindow(hwnd);
		if (close)DestroyWindow(hwnd);
	}
	break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam); break;
	}
	return 0;
}
BOOL LoadTextFileToEdit(HWND hEdit, LPCSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != UINT_MAX)
		{
			LPSTR lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			if (lpszFileText)
			{
				DWORD dwRead;
				if (ReadFile(hFile, lpszFileText, dwFileSize, &dwRead, NULL))
				{
					lpszFileText[dwFileSize] = 0;
					if (SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)lpszFileText))bSuccess = TRUE;
				}
				GlobalFree(lpszFileText);
			}
			CloseHandle(hFile);
		}
	}
	return bSuccess;
}
BOOL SaveTextFileFromEdit(HWND hEdit, LPCSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
		if (dwTextLength > 0)
		{
			LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
			if (lpszText)
			{
				if (SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszText))
				{
					DWORD dwWritten;
					if (WriteFile(hFile, lpszText, dwTextLength, &dwWritten, NULL))bSuccess = TRUE;
				}
				GlobalFree(lpszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}

VOID SelectFont(HWND hwnd)
{
	CHOOSEFONT cf;
	LOGFONT lf;
	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);

	ZeroMemory(&cf, sizeof(cf));
	ZeroMemory(&lf, sizeof(lf));

	GetObject(g_hFont, sizeof(LOGFONT), &lf);

	cf.lStructSize = sizeof(cf);
	cf.hwndOwner = hwnd;

	cf.Flags = CF_EFFECTS | CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
	cf.hInstance = GetModuleHandle(NULL);
	cf.lpLogFont = &lf;
	cf.rgbColors = g_RGB_Text;

	if (ChooseFont(&cf))
	{
		HFONT hf = CreateFontIndirect(&lf);
		if (hf)
		{
			g_hFont = hf;
		}
		else
		{
			MessageBox(hwnd, "Font creation failed", "Error", MB_OK | MB_ICONERROR);
		}
		g_RGB_Text = cf.rgbColors;
	}
	SendMessage(hEdit, WM_SETFONT, (WPARAM)g_hFont, TRUE);
	SetFocus(hEdit);
}
VOID SelectColor(HWND hwnd)
{
	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
	HDC hdc = GetDC(hwnd);
	CHOOSECOLOR cc = { sizeof(CHOOSECOLOR) };

	cc.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR;
	cc.hwndOwner = hwnd;
	cc.rgbResult = g_rgbBackground;
	cc.lpCustColors = g_rgbCustom;

	if (ChooseColor(&cc))g_rgbBackground = cc.rgbResult;
	//SendMessage(GetDlgItem(hwnd, IDC_EDIT), EMR_SETTEXTCOLOR)
	//SetTextColor(hdc, )
}