//1.	После двойного щелчка левой кнопки в клиентской области окна окно начинает перемещаться по вертикали.Нажатие любой клавиши прекращает движение.

#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>

static TCHAR WindowsClass[] = _T("win32app");
static TCHAR Title[] = _T("MyApp");
int top = 100;
int dir = 1;

#define ID_Timer 1001

HINSTANCE hinst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	/*wcex.hbrBackground = CreateSolidBrush(RGB(100, 70, 150));*/
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, _T("Call faild!"), _T("MyApp"), NULL);
		return 1;
	}

	hinst = hinstance;

	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		500,
		500,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Create window faild!"), _T("MyApp"), NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	RECT desktop;
		
	switch (message)
	{
	
	case WM_TIMER:
				
		//Получить координаты рабочего стола
		GetWindowRect(GetDesktopWindow(), &desktop);

		top += 10 * dir;

		//вывод окна с измененными координатами
		SetWindowPos(hWnd, HWND_TOP, 100, top, 500, 500, SWP_SHOWWINDOW);
		
		if (top + 500 == desktop.bottom)
			dir = -1;
		else if (top == 0)
			dir = 1;
		
		break;

	case WM_KEYDOWN:
		KillTimer(hWnd, ID_Timer);
		break;
	case WM_LBUTTONDBLCLK:
		SetTimer(hWnd, ID_Timer, 10, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}