#include <iostream>
using namespace std;

#include <windows.h>
#include "ConsoleLib.h"


// Õåíäëû êîíñîëè
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);


// Ïîêàçûâàåì/ïðÿ÷åì òåêñòîâûé êóðñîð
void ShowCursor(bool visible)
{
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), visible };
	SetConsoleCursorInfo(hStdOut, &cci);
}

// Óñòàíàâëèâàåò öâåò ñèìâîëîâ è ôîíà
void SetColor(ConsoleColor text, ConsoleColor background)
{
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

// Ïåðåìåùàåò êóðñîð â çàäàííóþ ïîçèöèþ
void GotoXY(int X, int Y)
{
    COORD coord = { (SHORT)X, (SHORT)Y };
    SetConsoleCursorPosition(hStdOut, coord);
}

// Âûâîäèò çàäàííóþ ñòðîêó â çàäàííóþ ïîçèöèþ
void WriteStr(int X, int Y, const char *Str)
{
    GotoXY(X, Y);
    cout << Str << flush;
}

// Âûâîäèò çàäàííûé ñèìâîë íà÷èíàÿ ñ çàäàííîé ïîçèöèè
void WriteChar(int X, int Y, char Ch)
{
	GotoXY(X, Y);
	cout << Ch;
}

// Âûâîäèò óêàçàííîå êîëè÷åñòâî çàäàííûõ ñèìâîëîâ íà÷èíàÿ ñ çàäàííîé ïîçèöèè
void WriteChars(int X, int Y, char Ch, unsigned Len)
{
	GotoXY(X, Y);
	for (unsigned i = 0; i < Len; i++)
		cout << Ch;
}

// Ìåíÿåò òåêñòîâûå àòðèáóòû, íà÷èíàÿ ñ çàäàííîé ïîçèöèè
void ChangeTextAttr(int X, int Y, ConsoleColor text, ConsoleColor background, unsigned Len)
{
	COORD coord = { (SHORT)X, (SHORT)Y };
	DWORD dwDummy;
	FillConsoleOutputAttribute(hStdOut, (WORD)((background << 4) | text), Len, coord, &dwDummy);
}
