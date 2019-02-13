#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "ConsoleLib.h"

using namespace std;

bool gameOver;
const int Esc = 27;

void WriteMenu()                                                                 // ����
{
	const int Esc = 27;
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
	WriteStr(26, 10, "     $$$    KOCTI    $$$     ");
	WriteChar(56, 10, Vert);

	WriteChar(25, 11, Vert);
	WriteStr(26, 11, "          NEW  GAME           ");
	WriteChar(56, 11, Vert);

	WriteChar(25, 12, Vert);
	WriteStr(26, 12, "           OPTIONS            ");
	WriteChar(56, 12, Vert);

	WriteChar(25, 13, Vert);
	WriteStr(26, 13, "            RULSE             ");
	WriteChar(56, 13, Vert);

	WriteChar(25, 14, Vert);
	WriteStr(26, 14, "        PRODUCE OF GAME       ");
	WriteChar(56, 14, Vert);
}

void printCubse(int Cubse)                                                   // ��������� ������
{
	switch (Cubse)
	{
	case 1:
		cout << "===========" << endl;
		cout << "|         |" << endl;
		cout << "|    *    |" << endl;
		cout << "|         |" << endl;
		cout << "===========" << endl;
		break;
	case 2:
		cout << "===========" << endl;
		cout << "|  *      |" << endl;
		cout << "|         |" << endl;
		cout << "|      *  |" << endl;
		cout << "===========" << endl;
		break;
	case 3:
		cout << "===========" << endl;
		cout << "|  *      |" << endl;
		cout << "|    *    |" << endl;
		cout << "|      *  |" << endl;
		cout << "===========" << endl;
		break;
	case 4:
		cout << "===========" << endl;
		cout << "|  *   *  |" << endl;
		cout << "|         |" << endl;
		cout << "|  *   *  |" << endl;
		cout << "===========" << endl;
		break;
	case 5:
		cout << "===========" << endl;
		cout << "|  *   *  |" << endl;
		cout << "|    *    |" << endl;
		cout << "|  *   *  |" << endl;
		cout << "===========" << endl;
		break;
	case 6:
		cout << "===========" << endl;
		cout << "|  *   *  |" << endl;
		cout << "|  *   *  |" << endl;
		cout << "|  *   *  |" << endl;
		cout << "===========" << endl;
		break;
	}
}

int Res()                                                                //��������� ��������� �������
{
	int Cubse_1 = rand() % 6 + 1;
	printCubse(Cubse_1);

	int Cubse_2 = rand() % 6 + 1;
	printCubse(Cubse_2);

	int Result;
	Result = Cubse_1 + Cubse_2;

	cout << "��������� / TOTAL: " << Result << endl << endl;
	return Result;
}

void StartGame()                                                         //��������� ����
{
	setlocale(LC_ALL, "Russian");
	gameOver = false;
	int x = 40, y = 12;
	int key2;
	int PlayerScore = 0;
	int CompScore = 0;

	SetColor(White, Black);
	ShowCursor(false);
	char Turn;

	do
	{
		ShowCursor(false);
		SetColor(Red, White);
		system("cls");                                                 // ����� ����
		cout << "\n\n\t\t\t\tSTART GAME!)!)!)\n" << endl;
		cout << "\n\t\t������ ������, ��� ������ ������;) ��� ������ ���� ������� 'S'!)\b";
		cin >> Turn;
	} while (Turn != 's');

	int playerRes, CompRes;
	do
	{
		system("cls");

		cout << "\n��� ���!" << endl;
		playerRes = Res();                                             // ���������� ������
		cout << "��� ���������: " << playerRes << endl;

		cout << "\n��� ����������!" << endl;
		CompRes = Res();                                               //���������� ���������
		cout << "��������� ����������: " << CompRes << endl;
	} while (playerRes == CompRes);

	if (playerRes > CompRes)                                           // ���� ����� ����� ��...
	{
		cout << "\t��� ������ ���\n" << endl;
		for (int i = 1; i <= 2; i++)
		{
			do
			{
				cout << "\t������� 'S'" << endl;
				cin >> Turn;
			} while (Turn = 's');

			PlayerScore += Res();
			CompScore += Res();
		}
		cout << "��� ����� ����: " << PlayerScore << endl;
		cout << "��������� ����� ����: " << CompScore << endl;
	}
	else
	{                                                                // ���� ����� ��������� ��...
		cout << "\n������ ����� ���������\n" << endl;
		for (int i = 1; i <= 2; i++)
		{
			CompScore += Res();
			do
			{
				cout << "\t��� ����������� ������� 'S':" << endl;
				cin >> Turn;
			} while (Turn != 's');
			PlayerScore += Res();
		}
		cout << "��� ����: " << PlayerScore << endl;
		cout << "��������� ����: " << CompScore << endl;
	}
	if (PlayerScore == CompScore)                                        //��������� ����������
	{
		cout << "\n\n\t\t\t\t\t\t�����!\n\n" << Beep(1000, 500) << endl;                           //�����
	}
	else
	{
		if (PlayerScore > CompScore)                                    // ������� �����
		{
			cout << "\n\n\t\t\t\t�� ��������! �����������!)" << Beep(1000, 50) << endl;
		}
		if (PlayerScore < CompScore)                                    // ������� ���������
		{
			cout << "\n\n\t\t\t\t�� ���������!" << Beep(1000, 5000) << endl;
		}
	}
}

void PrintOptions()                                                     // ����� ����
{
	const int Esc = 27;
	int x = 40, y = 12;

	SetColor(Black, LightGray);
	ShowCursor(false);
	char Back;
	do
	{
		system("cls");
		cout << "\n        RIGHT -->  RIGHT\n" << endl;
		cout << "          LEFT <-- LEFT\n" << endl;
		cout << "          UP  | UP\n" << endl;
		cout << "          DOWN |\n" << endl;
		cout << "          \n\n\t\t\t\t\t\tIf you want get out, press 'B'\n";
		cin >> Back;
	} while (Back != 'b');

	system("cls");
	WriteMenu();
}



void ProduceGame()                                  //��� ����������� ����
{
	//setlocale(LC_ALL, "Russian");
	char Back;
	SetColor(Black, LightGray);
	ShowCursor(false);
	do
	{
		system("cls");
		cout << "\n\t\t\t\t\t\t\tCopyRight by Aleksandr A. Stanov!!!";
		cout << "         \n\n\t\t\t\t\t\tIf you want get out, press 'B'(Back)\n";
		cin >> Back;
	} while (Back != 'b');

	system("cls");
	WriteMenu();
}

int main()
{
	srand((unsigned)time(0));
	const int Enter = 13;
	const int Home = 71;
	const int Up = 72;
	const int Down = 80;
	const int End = 79;
	int key;

	system("cls");
	ShowCursor(false);
	SetColor(Black, White);
	WriteMenu();

	const int itemCount = 5;
	int curItem = 1;

	do
	{
		ChangeTextAttr(26, 9 + curItem, Red, Black, 30);
		key = _getch();
		if (key == Enter)
		{
			switch (curItem)
			{
			case 1:
				Beep(1000, 500);
				break;
			case 2:
				Beep(1000, 50);
				StartGame();
				break;
			case 3:
				Beep(1000, 50);
				PrintOptions();
				break;
			case 4:
				Beep(1000, 50);
			//PrintRulse();
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
			ChangeTextAttr(26, 9 + curItem, Black, White, 30);

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
	ShowCursor(true);
	SetColor(White, Black);
}