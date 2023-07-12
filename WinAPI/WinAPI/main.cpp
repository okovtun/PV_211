#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITE[] = "Введите имя пользователя";
//g_ - Global;
//sz_ - String Zero (NULL Terminated Line)

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
/*
----------------------------------------------------------------
HWND hwnd - Handler To Window (Обработчик окна). Обратиться к окну можно только через его обработчик (Handler)
UINT uMsg - Сообщение
WPARAM wParam, LPARAM lParam - параметры сообщения, зависят от самого сообщения.
----------------------------------------------------------------
*/

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*
	----------------------------------------------------------------
	HINSTANCE hInstance - это экземпляр запущенного *.exe-файла нашей программы
	hInstance запущенной программы всегда можно получить при промрощи функции GetModuleHandle(NULL);

	HINSTANCE hPrefInst - это экземпляр редыдущего запущенного *.exe-файла
	
	LPSTR lpCmdLine:
	LPSTR - Long Pointer to String
	lpCmdLine - командная строка приложения, через которую можно определить параметры запуска приложения

	INT nCmdShow - определяет режим отображения окна, например, свернуто в окно, развернуто на весь экран, свернуто на панель задач.
	----------------------------------------------------------------
	*/
	//MessageBox(NULL, "Привет Мир! Я окно сообщения :-)", "Info", MB_YESNOCANCEL | MB_ICONINFORMATION);

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	//Создаем элемменты окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITE);
	}
	break;
	case WM_COMMAND:	//Обрабатываем команды нажатия на кнопки, наведение мыши........
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if (strcmp(sz_buffer, g_sz_LOGIN_INVITE) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				if (strlen(sz_buffer) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITE);
			}
		}
		break;
		case IDC_BUTTON_COPY:
		{
			//
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};	//sz_ - String Zero (NULL-Terminated Line)
			//
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);	//Обращаемся к окну, и сообщаем ему, что хотим прочитать его тект
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(GetDlgItem(hwnd, IDC_STATIC_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:		MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:	EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}