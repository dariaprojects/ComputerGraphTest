#include <iostream>
#include <Windows.h>
#include <cmath>
#define PI 3.14159
double ugol = PI / 20.0;

void multix(double Figure[][4], double Matrix[4][4]) {
	double res[4];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			res[j] = 0;
			for (int k = 0; k < 4; k++) {
				res[j] = res[j] + Figure[i][k] * Matrix[k][j];
			}
		}
		for (int j = 0; j < 4; j++) {
			Figure[i][j] = res[j];
		}
	}
}
void Del_koor(double Figure[][4]) {
	for (int i = 0; i < 6; i++) {
		Figure[i][0] = Figure[i][0] / Figure[i][3];
		Figure[i][1] = Figure[i][1] / Figure[i][3];
	}
}
void Proectia(double Figure[][4], double Figure2[][4], double k) {
	double r = 1 / k;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			Figure2[i][j] = Figure[i][j];
		}
	}
	double m[4][4] = { { 1,0,0,0 },{ 0,1,0,0 },{ 0,0,0,r },{ 0,0,0,1 } };
	multix(Figure2, m);
	Del_koor(Figure2);
}

void Perem_Z(double Figure[][4], double dz) {
	double m[4][4] = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,dz,1} };
	multix(Figure, m);
	Del_koor(Figure);
}
void Perem_X(double Figure[][4], double dx) {
	double m[4][4] = { { 1,0,0,0 },{ 0,1,0,0 },{ 0,0,1,0 },{ dx,0,0,1 } };
	multix(Figure, m);
	Del_koor(Figure);
}
void masht_Y(double Figure[][4], double sy) {
	double m[4][4] = { { 1,0,0,0 },{ 0,sy,0,0 },{ 0,0,1,0 },{ 0,0,0,1 } };
	multix(Figure, m);
	Del_koor(Figure);
}
void povorot_X(double Figure[][4]) {
	double m[4][4] = { {1,0,0,0},
					 {0,cos(ugol),sin(ugol),0},
					 {0,-sin(ugol),cos(ugol),0},
					 {0,0,0,1} };
	multix(Figure, m);
	Del_koor(Figure);
}
void otobr_YZ(double Figure[][4]) {
	double m[4][4] = { { -1,0,0,0 },{ 0,1,0,0 },{ 0,0,1,0 },{ 0,0,0,1 } };
	multix(Figure, m);
	Del_koor(Figure);
}
void ProectiaZ(double Figure[][4]) {
	double m[4][4] = { { 1,0,0,0 },{ 0,1,0,0 },{ 0,0,0,0 },{ 0,0,0,1 } };
	multix(Figure, m);
	Del_koor(Figure);
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	static double Figure2[6][4];
	static double Figure[6][4] = { 150,200,360,1,
								   450,200,430,1,
								   200,200,70,1,
								   210,100,320,1,
								   230,100,120,1,
								   330,100,350,1 };
	double x1, y1;

	switch (uMsg)
	{

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		Proectia(Figure, Figure2, 1000);
		x1 = rect.right / 2; y1 = rect.bottom / 2;
		MoveToEx(hdc, Figure2[0][0] + x1, Figure2[0][1], NULL); LineTo(hdc, Figure2[1][0] + x1, Figure2[1][1]);
		MoveToEx(hdc, Figure2[1][0] + x1, Figure2[1][1], NULL); LineTo(hdc, Figure2[2][0] + x1, Figure2[2][1]);
		MoveToEx(hdc, Figure2[2][0] + x1, Figure2[2][1], NULL); LineTo(hdc, Figure2[0][0] + x1, Figure2[0][1]);

		MoveToEx(hdc, Figure2[3][0] + x1, Figure2[3][1], NULL); LineTo(hdc, Figure2[4][0] + x1, Figure2[4][1]);
		MoveToEx(hdc, Figure2[4][0] + x1, Figure2[4][1], NULL); LineTo(hdc, Figure2[5][0] + x1, Figure2[5][1]);
		MoveToEx(hdc, Figure2[5][0] + x1, Figure2[5][1], NULL); LineTo(hdc, Figure2[3][0] + x1, Figure2[3][1]);

		MoveToEx(hdc, Figure2[0][0] + x1, Figure2[0][1], NULL); LineTo(hdc, Figure2[3][0] + x1, Figure2[3][1]);
		MoveToEx(hdc, Figure2[2][0] + x1, Figure2[2][1], NULL); LineTo(hdc, Figure2[4][0] + x1, Figure2[4][1]);
		MoveToEx(hdc, Figure2[1][0] + x1, Figure2[1][1], NULL); LineTo(hdc, Figure2[5][0] + x1, Figure2[5][1]);

		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			// Обработка события «нажата клавиша Стрелка вверх» перемещение по Z вверх
			Perem_Z(Figure, 2);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		case VK_DOWN:
			// Обработка события «нажата клавиша Стрелка вниз» перемещение по Z вниз
			Perem_Z(Figure, -2);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		case 68:
			// Обработка события «нажата клавиша D» сдвиг по Х впрево
			Perem_X(Figure, 2);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		case 87:
			// Обработка события «нажата клавиша W» масштаб Y +
			masht_Y(Figure, 2);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		case 83:
			// Обработка события «нажата клавиша S» масштаб Y -
			masht_Y(Figure, 0.5);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		case 65:
			// Обработка события «нажата клавиша A» поворот по X
			povorot_X(Figure);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		case VK_LEFT:
			// Обработка события «нажата клавиша Стрелка влево» отображение YZ
			otobr_YZ(Figure);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		case VK_RIGHT:
			// Обработка события «нажата клавиша Стрелка вправо» Проекция
			ProectiaZ(Figure);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

int WINAPI main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = (LPCWSTR)"WinClass";
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, (LPCWSTR)"Cannot register class", (LPCWSTR)"ERROR", MB_OK);
		return 0;
	}
	hWnd = CreateWindowEx(NULL, (LPCWSTR)"WinClass", (LPCWSTR)"Простое окно", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	if (!hWnd) {
		MessageBox(NULL, (LPCWSTR)"Cannot create window", (LPCWSTR)"ERROR", MB_OK);
		return 0;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
