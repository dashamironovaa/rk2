#include <iostream>
#include <windows.h>
#include <locale>
#include <conio.h>
#include <limits>

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void console_set_text_color(int text_color, int background_color) {
	HANDLE handle;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(
		handle,
		(WORD)((background_color << 4) | text_color));
}
void console_gotoxy(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord);
}

void console_hide_cursor() {
	HANDLE handle;
	CONSOLE_CURSOR_INFO structCursorInfo;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

WORD console_get_vk() {
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD rec;
	DWORD event;

	//FlushConsoleInputBuffer(hstdin);
	while (ReadConsoleInputA(hstdin, &rec, 1, &event)) {
		if ((rec.EventType == KEY_EVENT)
			&& (rec.Event.KeyEvent.bKeyDown)) {
			return rec.Event.KeyEvent.wVirtualKeyCode;
		}
	}
	return 0;
}
