#include<Windows.h>

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyFirstWindow";

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

	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

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

	HWND hwnd = CreateWindowEx
	(
		0,
		g_sz_MY_WINDOW_CLASS,	//Имя класса окна
		g_sz_MY_WINDOW_CLASS,	//Заголовок окна
		WS_OVERLAPPEDWINDOW,	//Стриль окна для главного окна программы всегда быдет WS_OVERLAPPEDWINDOW
								//WS_OVERLAPPEDWINDOW - это окно верхнего уровня (TOP_LEVEL_WINDOW), которое включает в себя дочерние окна (CHILDWINDOW)
		CW_USEDEFAULT, CW_USEDEFAULT,	//Начальная позиция окна
		CW_USEDEFAULT, CW_USEDEFAULT,	//Размер окна
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
	

	//3) Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:	DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}