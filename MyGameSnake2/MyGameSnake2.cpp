#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include "ConsoleLib.h"
//#include <Mmsystem.h>   // ƒобавить winmm.lib в Project Properties -> Linker -> Command Line -> Additional Options

using namespace std;

bool gameOver = true;
bool WOLL = true;
const int Esc = 27;
int key = 0;

struct Snake
{
	COORD *t; //точки 
	int ACount; //количество €блок
};

struct Game
{
	Snake snakes;
	COORD apples;
	int dx, dy;
	int pause;
	int dir;
};

enum direction { LEFT, UP, RIGHT, DOWN }; //упровление 

enum { END, STOP, PLUS, MOVE };  //напровление, добавление ... 

void WriteMenu()
{
	ShowCursor(false);
	SetColor(White, Blue);

	const unsigned char LeftTop = 201;
	const unsigned char Horz = 205;
	const unsigned char Vert = 186;
	const unsigned char RightTop = 187;
	const unsigned char LeftBottom = 200;
	const unsigned char RightBottom = 188;

	WriteChar(25, 9, LeftTop);
	WriteChars(26, 9, Horz, 30);
	WriteChar(56, 9, RightTop);

	WriteChar(25, 10, Vert);
	WriteStr(26, 10, "          START GAME         ");
	WriteChar(56, 10, Vert);

	WriteChar(25, 11, Vert);
	WriteStr(26, 11, "           OPTIONS           ");
	WriteChar(56, 11, Vert);

	WriteChar(25, 12, Vert);
	WriteStr(26, 12, "            RULES            ");
	WriteChar(56, 12, Vert);

	WriteChar(25, 13, Vert);
	WriteStr(26, 13, "           RECORDS           ");
	WriteChar(56, 13, Vert);

	WriteChar(25, 14, Vert);
	WriteStr(26, 14, "       ABOUT OF PRODUCE      ");
	WriteChar(56, 14, Vert);

	WriteChar(25, 15, LeftBottom);
	WriteChars(26, 15, Horz, 30);
	WriteChar(56, 15, RightBottom);

	SetColor(LightGray, Black);
	ShowCursor(false);
}

char* GetName(char* st)// им€ пользовател€
{
	SetColor(Blue, Black);

	cout << "Please, enter your name:\n";
	GotoXY(53, 26); cin >> st;
	return st;
}

void PrintApple(Game &g) // рандом дл€ €блок
{
	int i, x, y;
	int n = g.snakes.ACount;
	do
	{
		x = rand() % 77 + 3;
		y = rand() % 25 + 3; //кординаты €блока
		for (i = 0; i < n; i++)
		{
			if (x == g.snakes.t[i].X && y == g.snakes.t[i].Y) // проверка чтоб €блоко не попало на змею
				break;
		}

	}while (i < n);
	g.apples.X = x;
	g.apples.Y = y; //запоминаем позицию €блока

	SetConsoleCursorPosition(hStdOut, g.apples); //переносим курсор в эту позицию

	SetConsoleTextAttribute(hStdOut, 0x0c); //цвет €блока  
	cout << "Q"; //рисуем €блоко
}

void StartSnake(Game &g) //старт змейки и ее координаыт и скорость
{
	system("cls");
	g.snakes.ACount = 3; //сколько точек в змейке
	g.snakes.t = new COORD[3];//создали точки
	for (int i = 0; i < 3; i++)
	{
		g.snakes.t[i].X = 20 + i;
		g.snakes.t[i].Y = 20;
	}

	g.dx = 1;
	g.dy = 0;
	g.pause = 100;//скорость передвижение змеи

	PrintApple(g);//рисуем €блоко
}

void TaskAndWishes()//условие
{
	SetColor(Yellow, Black);
	GotoXY(20, 12); cout << "           *** WELL, LET'S START THE GAME ***" << endl;
	GotoXY(20, 15); cout << "               YOU MUST COLLECT 30 APPLES." << endl;
	GotoXY(20, 17); cout << "                        GOOD LUCK " << endl;
}

void SnakeConcol()//рисуем заставку
{
	SetColor(Blue, Black);
	ShowCursor(false);

	GotoXY(30, 5); cout << "***********************************************" << endl;
	GotoXY(30, 6); cout << "*                                             *" << endl;
	GotoXY(30, 7); cout << "*    @@@    @@  @@@    @     @@  @@  @@@@@    *" << endl;
	GotoXY(30, 8); cout << "*   @   @   @@   @    @ @    @  @    @   @    *" << endl;
	GotoXY(30, 9); cout << "*    @      @ @  @   @   @   @@@     @        *" << endl;

	SetColor(Yellow, Black);
	GotoXY(30, 10); cout << "*     @     @  @ @  @@   @@  @@      @@@@     *" << endl;
	GotoXY(30, 11); cout << "*      @    @   @@  @@@@@@@  @ @     @        *" << endl;
	GotoXY(30, 12); cout << "*   @   @   @    @  @     @  @  @    @   @    *" << endl;
	GotoXY(30, 13); cout << "*    @@@   @@@   @  @@   @@  @@  @@  @@@@@    *" << endl;
	GotoXY(30, 14); cout << "*                                             *" << endl;
	GotoXY(30, 15); cout << "***********************************************" << endl;

	SetColor(Blue, Black);
	GotoXY(77, 15); cout << ".5D INSTALLER Inc" << endl;

	SetColor(Red, Black);
	GotoXY(30, 19); cout << "                *** PRESENTS ***                " << endl;
}

void StartGame()//–исуем карту
{
	SetColor(Red, Black);
	ShowCursor(false);

	GotoXY(87, 1); cout << "******_******_*****" << endl;
	GotoXY(87, 2); cout << "* |  |_  W  |_ |  *" << endl;
	GotoXY(87, 3); cout << "* |_ |_  V  |_ |_ *" << endl;
	GotoXY(87, 4); cout << "*******************" << endl;
	GotoXY(84, 7); cout << "[NAME]: " << endl;
	GotoXY(84, 9); cout << "[SCORE]: 0" << endl;
	GotoXY(84, 11); cout << "[SPEED]:100" << endl;
	GotoXY(84, 25); cout << "PAUSE -> Press key 'P'!" << endl;
	GotoXY(84, 26); cout << "press -> 'P' to continue!" << endl;
	GotoXY(84, 27); cout << "Press ->'Esc'(Exit)" << endl;
	GotoXY(84, 28); cout << "Press -> ....(Back to menu)" << endl;
	{
		SetColor(LightBlue, Black);
		GotoXY(2, 1); //рисуем верхнюю горизонтальную линию-стенку

		int m = 0;
		for (m = 0; m < 80; m++)
		{
			cout << "_";
		}
		{
			GotoXY(2, 29); //рисуем нижнюю горизонтальную линию-стенку
			int m = 0;
			for (m = 0; m < 80; m++)
			{
				cout << "_";
			}
		}
	}
	//рисуем левую вертикальную линию-стенку
	{
		GotoXY(2, 2); cout << "|" << endl;
		GotoXY(2, 3); cout << "|" << endl;
		GotoXY(2, 4); cout << "|" << endl;
		GotoXY(2, 5); cout << "|" << endl;
		GotoXY(2, 6); cout << "|" << endl;
		GotoXY(2, 7); cout << "|" << endl;
		GotoXY(2, 8); cout << "|" << endl;
		GotoXY(2, 9); cout << "|" << endl;
		GotoXY(2, 10); cout << "|" << endl;
		GotoXY(2, 11); cout << "|" << endl;
		GotoXY(2, 12); cout << "|" << endl;
		GotoXY(2, 13); cout << "|" << endl;
		GotoXY(2, 14); cout << "|" << endl;
		GotoXY(2, 15); cout << "|" << endl;
		GotoXY(2, 16); cout << "|" << endl;
		GotoXY(2, 17); cout << "|" << endl;
		GotoXY(2, 18); cout << "|" << endl;
		GotoXY(2, 19); cout << "|" << endl;
		GotoXY(2, 20); cout << "|" << endl;
		GotoXY(2, 21); cout << "|" << endl;
		GotoXY(2, 22); cout << "|" << endl;
		GotoXY(2, 23); cout << "|" << endl;
		GotoXY(2, 24); cout << "|" << endl;
		GotoXY(2, 25); cout << "|" << endl;
		GotoXY(2, 26); cout << "|" << endl;
		GotoXY(2, 27); cout << "|" << endl;
		GotoXY(2, 28); cout << "|" << endl;
		GotoXY(2, 29); cout << "|" << endl;
	}
	{
		GotoXY(81, 2); cout << "|" << endl;
		GotoXY(81, 3); cout << "|" << endl;
		GotoXY(81, 4); cout << "|" << endl;//рисуем правую вертикальную линию-стенку
		GotoXY(81, 5); cout << "|" << endl;
		GotoXY(81, 6); cout << "|" << endl;
		GotoXY(81, 7); cout << "|" << endl;
		GotoXY(81, 8); cout << "|" << endl;
		GotoXY(81, 9); cout << "|" << endl;
		GotoXY(81, 10); cout << "|" << endl;
		GotoXY(81, 11); cout << "|" << endl;
		GotoXY(81, 12); cout << "|" << endl;
		GotoXY(81, 13); cout << "|" << endl;
		GotoXY(81, 14); cout << "|" << endl;
		GotoXY(81, 15); cout << "|" << endl;
		GotoXY(81, 16); cout << "|" << endl;
		GotoXY(81, 17); cout << "|" << endl;
		GotoXY(81, 18); cout << "|" << endl;
		GotoXY(81, 19); cout << "|" << endl;
		GotoXY(81, 20); cout << "|" << endl;
		GotoXY(81, 21); cout << "|" << endl;
		GotoXY(81, 22); cout << "|" << endl;
		GotoXY(81, 23); cout << "|" << endl;
		GotoXY(81, 24); cout << "|" << endl;
		GotoXY(81, 25); cout << "|" << endl;
		GotoXY(81, 26); cout << "|" << endl;
		GotoXY(81, 27); cout << "|" << endl;
		GotoXY(81, 28); cout << "|" << endl;
		GotoXY(81, 29); cout << "|" << endl;
	}

	{
		SetColor(LightGray, Black);
		ShowCursor(false);
	}
}

int PrintMove(Game &g)
{
	int &n = g.snakes.ACount;
	COORD head = g.snakes.t[n - 1]; //голова
	COORD tail = g.snakes.t[0]; //хвост
	COORD next;

	next.X = head.X + g.dx;
	next.Y = head.Y + g.dy; //проверка следующей точки по направлению

	if (WOLL == true)
	{
		if (next.X < 3 || next.Y < 3 || next.X > 80 || next.Y > 28)//не уперлась ли в стену
			return STOP;
	}

	else
	{
		if (next.X <= 2)
			next.X = 80;
		else if (next.X >= 81)
			next.X = 3;
		else if (next.Y <= 1) // если уперлись в стену переход на другую сторону
			next.Y = 28;
		else if (next.Y >= 29)
			next.Y = 2;
	}

	if (n > 4)
	{
		for (int i = 0; i < n; i++)
			if (next.X == g.snakes.t[i].X && next.Y == g.snakes.t[i].Y) //не наехали ли на себ€
				return END;
	}

	if (next.X == g.apples.X && next.Y == g.apples.Y)
	{
		COORD *tmp = new COORD[++n]; //новый масив больший на 1
		for (int i = 0; i < n; i++)
			tmp[i] = g.snakes.t[i]; //перекопируем
		tmp[n - 1] = next; //добавл€ем одну
		delete[] g.snakes.t;
		g.snakes.t = tmp;

		SetConsoleCursorPosition(hStdOut, head);

		SetConsoleTextAttribute(hStdOut, 0x0a); //закрашываем €блоко которое съели
		cout << "O";

		SetConsoleCursorPosition(hStdOut, next);

		SetConsoleTextAttribute(hStdOut, 0x0a);
		cout << "@";

		PrintApple(g);
		return PLUS;
	}

	for (int i = 0; i < n - 1; i++)
		g.snakes.t[i] = g.snakes.t[i + 1];
	g.snakes.t[n - 1] = next;

	SetConsoleCursorPosition(hStdOut, tail);//закрашиваем хвост
	cout << " ";

	SetConsoleCursorPosition(hStdOut, head);

	SetConsoleTextAttribute(hStdOut, 0x0a);//рисуем хвост змеи
	cout << "O";

	SetConsoleCursorPosition(hStdOut, next);

	SetConsoleTextAttribute(hStdOut, 0x0a); //рисуем  голову
	cout << "@";
	return MOVE;
}

void PrintOptions() // опции игры
{
	system("cls");
	ShowCursor(false);

	SetColor(White, Blue);

	const unsigned char LeftTop = 201;
	const unsigned char Horz = 205;
	const unsigned char Vert = 186;
	const unsigned char RightTop = 187;
	const unsigned char LeftBottom = 200;
	const unsigned char RightBottom = 188;

	WriteChar(25, 9, LeftTop);
	WriteChars(26, 9, Horz, 30);
	WriteChar(56, 9, RightTop);

	WriteChar(25, 10, Vert);
	WriteStr(26, 10, "               NO            ");
	WriteChar(56, 10, Vert);

	WriteChar(25, 11, Vert);
	WriteStr(26, 11, "              YES            ");
	WriteChar(56, 11, Vert);;

	WriteChar(25, 12, LeftBottom);
	WriteChars(26, 12, Horz, 30);
	WriteChar(56, 12, RightBottom);

	SetColor(Red, Black);
	GotoXY(4, 4); cout << "\tIf you want your snake to pass through the wall, press 'YES',\n";
	GotoXY(4, 6); cout << "\tif not, then click 'NO'. Then if you touch the wall you lose. ";

	SetColor(LightBlue, Black);
	ShowCursor(false);
}


void PrintRulse()                                                     // правила игры
{
	ShowCursor(false);
	do
	{
		system("cls");
		SetColor(LightBlue, Black);
		cout << "\n\t\tSnake, Telmac 1800, 1978\n";
		cout << "\tSnake(Python, Boa, Snake, etc.) is a computer game that arose in the middle or in the late 1970s.\n";
		cout << "\tThe player controls a long, thin creature that resembles a snake, which crawls along a plane\n";
		cout << "\t(usually bounded by walls),collecting food(or other objects), avoiding collision with its own \n";
		cout << "\ttail and edges of the playing field.In some embodiments, there are additional obstacles on the\n";
		cout << "\the field.Each time a snake eats a piece of food,it becomes longer, which gradually complicates \n";
		cout << "\tthe game.The player controls the direction of movement of the snake's head \n";
		cout << "\t(usually 4 directions: up, down, left, right), and the snake's tail follows.\n" << endl;
		cout << "\tThe player can not stop the movement of the snake.\n" << endl;

		SetColor(Red, Black);
		GotoXY(85, 24); cout << "Press ->'Esc'(Back to Menu)" << endl;

		key = _getch();
	} while (key != Esc);

	SetColor(LightBlue, Black);
	ShowCursor(false);

	system("cls");
	WriteMenu();
}

void PrintUserRecords()
{
	ShowCursor(false);
	system("cls");
	do
	{
		SetColor(Blue, Black);
		GotoXY(25, 5); cout << "***********************************************" << endl;
		GotoXY(25, 6); cout << "*                                             *" << endl;
		GotoXY(25, 7); cout << "*    @@@    @@  @@@    @     @@  @@  @@@@@    *" << endl;
		GotoXY(25, 8); cout << "*   @   @   @@   @    @ @    @  @    @   @    *" << endl;
		GotoXY(25, 9); cout << "*    @      @ @  @   @   @   @@@     @        *" << endl;

		SetColor(Yellow, Black);
		GotoXY(25, 10); cout << "*     @     @  @ @  @@   @@  @@      @@@@     *" << endl;
		GotoXY(25, 11); cout << "*      @    @   @@  @@@@@@@  @ @     @        *" << endl;
		GotoXY(25, 12); cout << "*   @   @   @    @  @     @  @  @    @   @    *" << endl;
		GotoXY(25, 13); cout << "*    @@@   @@@   @  @@   @@  @@  @@  @@@@@    *" << endl;
		GotoXY(25, 14); cout << "*                                             *" << endl;
		GotoXY(25, 15); cout << "***********************************************" << endl;

		SetColor(Blue, Black);
		GotoXY(72, 15); cout << ".5D INSTALLER Inc" << endl;

		SetColor(Yellow, Black);
		GotoXY(30, 16); cout << "Records" << endl;

		SetColor(Red, Black);
		GotoXY(25, 17); cout << "1. [ALEX] 00030";
		GotoXY(25, 18); cout << "2. [NEW_NAME]: -|-|-";
		GotoXY(25, 19); cout << "3. [NEW_NAME]: -|-|-";
		GotoXY(25, 20); cout << "4. [NEW_NAME]: -|-|-";
		GotoXY(25, 21); cout << "5. [NEW_NAME]: -|-|-";
		GotoXY(25, 22); cout << "6. [NEW_NAME]: -|-|-";
		GotoXY(25, 23); cout << "7. [NEW_NAME]: -|-|-";
		GotoXY(25, 24); cout << "8. [NEW_NAME]: -|-|-";
		GotoXY(25, 25); cout << "9. [NEW_NAME]: -|-|-";
		GotoXY(25, 26); cout << "10.[NEW_NAME]: -|-|-";

		key = _getch();
	} while (key != Esc);

	SetColor(LightBlue, Black);
	ShowCursor(false);

	system("cls");
	WriteMenu();
}

void ProduceGame()                                  // производитель игры
{
	ShowCursor(false);
	do
	{
		system("cls");
		SetColor(LightBlue, Black);

		GotoXY(60, 5); cout << "CopyRight by Aleksandr A. Stanov!!!\n";
		GotoXY(50, 8); cout << "BND - 1811(2018)\n" << endl;
		cout << "\t\tMy name is Alexander Alexandrovich Stanov.\n";
		cout << "\tI am a student of the Step Academy. This game was developed by me as\n";
		cout << "\tan examination task. And I hope I did it. Have a nice day, everyone.\n";
		GotoXY(60, 20); cout << " With the delight of Stanov Alexander.";

		SetColor(Red, Black);
		GotoXY(84, 24); cout << "Press ->'Esc'(Back to Menu)" << endl;

		key = _getch();
	} while (key != Esc);

	SetColor(LightBlue, Black);
	ShowCursor(false);

	system("cls");
	WriteMenu();
}

int main()
{
	Game g;
	char st[50];
	bool Pause = false;
	const int Esc = 27;
	const int Enter = 13;
	const int Up = 72;
	const int Down = 80;
	int key = 0, Rec = 0, count = 0;
	const int itemCount = 5;
	const int itemCount1 = 2;
	int curItem = 1;
	int curItem1 = 1;

	srand((unsigned)time(0));
	system("cls");

	ShowCursor(false);
	SetColor(White, Cyan);

	SnakeConcol();
	Sleep(3500);

	GotoXY(44, 24);
	cout << GetName(st) << " ";

	system("cls");
	WriteMenu();
	do
	{

		ChangeTextAttr(26, 9 + curItem, White, Black, 30);

		key = _getch();

		if (key == Enter)
		{
			switch (curItem)
			{
			case 1:
				Beep(1000, 50);

				system("cls");

				TaskAndWishes();

				Sleep(1000);

				StartSnake(g);

				StartGame();

				while (key != 27)
				{
					while (!_kbhit())
					{
						if (Pause == true)
						{
							Sleep(1);
							continue;
						}

						switch (PrintMove(g))
						{

						case PLUS:
							++count;
							g.pause -= 3;   // овичает за скоростсь

							SetColor(Red, Black);

							GotoXY(87, 1); cout << "******_******_*****" << endl;
							GotoXY(87, 2); cout << "* |  |_  W  |_ |  *" << endl;
							GotoXY(87, 3); cout << "* |_ |_  V  |_ |_ *" << endl;
							GotoXY(87, 4); cout << "*******************" << endl;
							GotoXY(84, 7); cout << "[NAME] " << st << endl;
							GotoXY(84, 9); cout << "[SCORE]: " << count << endl;
							GotoXY(84, 11); cout << "[SPEED]: " << g.pause << endl;
							GotoXY(84, 25); cout << "PAUSE -> Press key 'P'!" << endl;
							GotoXY(84, 26); cout << "press -> 'P' to continue!" << endl;
							GotoXY(84, 27); cout << "Press ->'Esc'(Exit)" << endl;
							GotoXY(84, 28); cout << "Press -> PAUSE + 'Esc'(Back to menu)" << endl;

							if (count == 30)
							{
								SetColor(Yellow, Black);

								GotoXY(28, 12); cout << st << " CONGRATULATIONS!!!" << endl;
								GotoXY(28, 14); cout << "     YOU WIN!!!" << endl;
								GotoXY(28, 16); cout << "   YOUR RECORD: " << count << endl;

								_getch();
								return(0);
							}
							break;

						case STOP:

						case END:
							SetColor(Yellow, Black);

							GotoXY(31, 12); cout << st << "! LOSHARA!" << endl;
							GotoXY(33, 14); cout << "YOU LOSE!!!" << endl;
							GotoXY(31, 16); cout << "YOUR RECORD: " << count << endl;
							_getch();
							break;
						}
						Sleep(g.pause); //Ђзадержка 
					}

					key = _getch();

					if (key == 'P' || key == 'p')
						Pause = !Pause;

					if (key == 0 || key == 224)
					{
						key = _getch();

						if (key == 72 && g.dir != DOWN)
						{
							g.dir = UP;
							g.dx = 0;
							g.dy = -1;
						}
						else if (key == 80 && g.dir != UP)
						{
							g.dir = DOWN;
							g.dx = 0;
							g.dy = 1;
						}
						else if (key == 75 && g.dir != RIGHT)
						{
							g.dir = LEFT;
							g.dx = -1;
							g.dy = 0;
						}
						else if (key == 77 && g.dir != LEFT)
						{
							g.dir = RIGHT;
							g.dx = 1;
							g.dy = 0;
						}
					}
				}
				while (key != Esc);

				SetColor(LightBlue, Black);

				ShowCursor(false);

				system("cls");

				WriteMenu();
				break;

			case 2:
				Beep(1000, 50);

				PrintOptions();

				do
				{
					ChangeTextAttr(26, 9 + curItem1, White, Black, 30);

					key = _getch();

					if (key == Enter)
					{
						switch (curItem1)
						{
						case 1:
							Beep(1000, 50);
							WOLL = true;

							system("cls");
							TaskAndWishes();
							Sleep(2500);

							StartSnake(g);
							StartGame();

							while (key != 27)
							{
								while (!_kbhit())
								{
									if (Pause == true)
									{
										Sleep(1);
										continue;
									}

									switch (PrintMove(g))
									{

									case PLUS:
										++count;
										g.pause -= 3;   // овичает за скоростсь

										SetColor(Red, Black);
										GotoXY(87, 1); cout << "******_******_*****" << endl;
										GotoXY(87, 2); cout << "* |  |_  W  |_ |  *" << endl;
										GotoXY(87, 3); cout << "* |_ |_  V  |_ |_ *" << endl;
										GotoXY(87, 4); cout << "*******************" << endl;
										GotoXY(84, 7); cout << "[NAME] " << st << endl;
										GotoXY(84, 9); cout << "[SCORE]: " << count << endl;
										GotoXY(84, 11); cout << "[SPEED]: " << g.pause << endl;
										GotoXY(84, 25); cout << "PAUSE -> Press key 'P'!" << endl;
										GotoXY(84, 26); cout << "press -> 'P' to continue!" << endl;
										GotoXY(84, 27); cout << "Press ->'Esc'(Exit)" << endl;
										GotoXY(84, 28); cout << "Press -> .....(Back to menu)" << endl;

										if (count == 30)
										{
											SetColor(Yellow, Black);
											GotoXY(28, 12); cout << st << " CONGRATULATIONS!!!" << endl;
											GotoXY(28, 14); cout << "     YOU WIN!!!" << endl;
											GotoXY(28, 16); cout << "   YOUR RECORD: " << count << endl;

											_getch();
											return(0);
										}
										break;

									case STOP:

									case END:
										SetColor(Yellow, Black);
										GotoXY(31, 12); cout << st << "! LOSHARA!" << endl;
										GotoXY(33, 14); cout << "YOU LOSE!!!" << endl;
										GotoXY(31, 16); cout << "YOUR RECORD: " << count << endl;
										_getch();
										break;
									}

									Sleep(g.pause); //Ђзадержка 
								}

								key = _getch();

								if (key == 'P' || key == 'p')
									Pause = !Pause;

								if (key == 0 || key == 224)
								{
									key = _getch();

									if (key == 72 && g.dir != DOWN)
									{
										g.dir = UP;
										g.dx = 0;
										g.dy = -1;
									}
									else if (key == 80 && g.dir != UP)
									{
										g.dir = DOWN;
										g.dx = 0;
										g.dy = 1;
									}
									else if (key == 75 && g.dir != RIGHT)
									{
										g.dir = LEFT;
										g.dx = -1;
										g.dy = 0;
									}
									else if (key == 77 && g.dir != LEFT)
									{
										g.dir = RIGHT;
										g.dx = 1;
										g.dy = 0;
									}
									
								}//break;							
							}while (key != Esc);

							SetColor(LightBlue, Black);

							ShowCursor(false);

							system("cls");

							WriteMenu();

						case 2:
							Beep(1000, 50);
							WOLL = !true;

							do
							{
								system("cls");

								TaskAndWishes();

								Sleep(500);

								StartSnake(g);

								StartGame();

								while (key != 27)
								{
									while (!_kbhit())
									{
										if (Pause == true)
										{
											Sleep(1);
											continue;
										}

										switch (PrintMove(g))
										{

										case PLUS:
											++count;
											g.pause -= 3;   // овичает за скоростсь

											SetColor(Red, Black);
											GotoXY(87, 1); cout << "******_******_*****" << endl;
											GotoXY(87, 2); cout << "* |  |_  W  |_ |  *" << endl;
											GotoXY(87, 3); cout << "* |_ |_  V  |_ |_ *" << endl;
											GotoXY(87, 4); cout << "*******************" << endl;
											GotoXY(84, 7); cout << "[NAME] " << st << endl;
											GotoXY(84, 9); cout << "[SCORE]: " << count << endl;
											GotoXY(84, 11); cout << "[SPEED]: " << g.pause << endl;
											GotoXY(84, 25); cout << "PAUSE -> Press key 'P'!" << endl;
											GotoXY(84, 26); cout << "press -> 'P' to continue!" << endl;
											GotoXY(84, 27); cout << "Press ->'Esc'(Exit)" << endl;
											GotoXY(84, 28); cout << "Press -> PAUSE + 'Esc'(Back to menu)" << endl;

											if (count == 30)
											{
												SetColor(Yellow, Black);
												GotoXY(28, 12); cout << st << " CONGRATULATIONS!!!" << endl;
												GotoXY(28, 14); cout << "     YOU WIN!!!" << endl;
												GotoXY(28, 16); cout << "   YOUR RECORD: " << count << endl;

												_getch();
												return(0);
											}
											break;

										case STOP:

										case END:
											SetColor(Yellow, Black);
											GotoXY(31, 12); cout << st << "! LOSHARA!" << endl;
											GotoXY(33, 14); cout << "YOU LOSE!!!" << endl;
											GotoXY(31, 16); cout << "YOUR RECORD: " << count << endl;
											_getch();
											break;
										}

										Sleep(g.pause); //Ђзадержка 
									}

									key = _getch();

									if (key == 'P' || key == 'p')
										Pause = !Pause;

									if (key == 0 || key == 224)
									{
										key = _getch();

										if (key == 72 && g.dir != DOWN)
										{
											g.dir = UP;
											g.dx = 0;
											g.dy = -1;
										}
										else if (key == 80 && g.dir != UP)
										{
											g.dir = DOWN;
											g.dx = 0;
											g.dy = 1;
										}
										else if (key == 75 && g.dir != RIGHT)
										{
											g.dir = LEFT;
											g.dx = -1;
											g.dy = 0;
										}
										else if (key == 77 && g.dir != LEFT)
										{
											g.dir = RIGHT;
											g.dx = 1;
											g.dy = 0;
										}									
									}
								}
							} while (key != Esc);

							SetColor(LightBlue, Black);

							ShowCursor(false);

							system("cls");

							WriteMenu();
							
						}break;
					}
					if (key == 0 || key == 0xE0)
					{
						key = _getch();

						ChangeTextAttr(26, 9 + curItem1, White, Blue, 29);

						switch (key)
						{
						case Up:
							if (curItem1 == 1)
								curItem1 = itemCount1;
							else
								curItem1--;
							break;
						case Down:
							if (curItem1 == itemCount1)
								curItem1 = 1;
							else
								curItem1++;
							break;
						}
					}
				} while (key != Esc);
				
			case 3:
				Beep(1000, 50);
				PrintRulse();
				break;

			case 4:
				Beep(1000, 50);
				PrintUserRecords();
				break;

			case 5:
				Beep(1000, 50);
				ProduceGame();
				break;
			}
		}

		if (key == 0 || key == 0xE0)
		{
			key = _getch();

			ChangeTextAttr(26, 9 + curItem, White, Blue, 29);

			switch (key)
			{
			case Up:
				if (curItem == 1)
					curItem = itemCount;
				else
					curItem--;
				break;
			case Down:
				if (curItem == itemCount)
					curItem = 1;
				else
					curItem++;
				break;
			}
		}

	} while (key != Esc);

	system("cls");

	WriteMenu();

	SetColor(LightGray, Black);

	ShowCursor(true);
}
