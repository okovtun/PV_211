#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* values[] = { "This", "is", "my", "First", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "ComboBox check", "Info", MB_OK | MB_ICONINFORMATION);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)values[i]);
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);	//Определем номер выбранного элемента выпадающего списка
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_message[SIZE] = {};
			sprintf(sz_message, "Вы выбрали элемент № %i, со значением \"%s\"", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}