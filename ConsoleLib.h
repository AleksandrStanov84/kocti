#ifndef __CONSOLELIB_H__
#define __CONSOLELIB_H__

#include <windows.h>

// Õåíäëû êîíñîëè
extern HANDLE hStdOut;
extern HANDLE hStdIn;

// Öâåòà
enum ConsoleColor
{
	Black         = 0,
	Blue          = 1,
	Green         = 2,
	Cyan          = 3,
	Red           = 4,
	Magenta       = 5,
	Brown         = 6,
	LightGray     = 7,
	DarkGray      = 8,
	LightBlue     = 9,
	LightGreen    = 10,
	LightCyan     = 11,
	LightRed      = 12,
	LightMagenta  = 13,
	Yellow        = 14,
	White         = 15
};

// Ïîêàçûâàåì/ïðÿ÷åì òåêñòîâûé êóðñîð
void ShowCursor(bool visible);

// Óñòàíàâëèâàåò öâåò ñèìâîëîâ è ôîíà
void SetColor(ConsoleColor text, ConsoleColor background);

// Ïåðåìåùàåò êóðñîð â çàäàííóþ ïîçèöèþ
void GotoXY(int X, int Y);

// Âûâîäèò çàäàííóþ ñòðîêó â çàäàííóþ ïîçèöèþ
void WriteStr(int X, int Y, const char *Str);

// Âûâîäèò çàäàííûé ñèìâîë íà÷èíàÿ ñ çàäàííîé ïîçèöèè
void WriteChar(int X, int Y, char Ch);

// Âûâîäèò óêàçàííîå êîëè÷åñòâî çàäàííûõ ñèìâîëîâ íà÷èíàÿ ñ çàäàííîé ïîçèöèè
void WriteChars(int X, int Y, char Ch, unsigned Len);

// Ìåíÿåò òåêñòîâûå àòðèáóòû, íà÷èíàÿ ñ çàäàííîé ïîçèöèè
void ChangeTextAttr(int X, int Y, ConsoleColor text, ConsoleColor background, unsigned Len);

#endif // __CONSOLELIB_H__
