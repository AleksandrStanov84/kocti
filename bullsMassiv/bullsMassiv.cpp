#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	cout << "\t\t\t\t\t\t\t\t\t\t\tCopyRight by Aleksandr A. Stanov\n\n";

	cout << "\t\t\t\tBULLS AND COWS\n";
	cout << "\t\t\t\t(Быки и Коровы)\n\n\n";

	cout << "Правила игры:\n\n";
	cout << "\tКомпьютер задумывает четыре различные цифры из 0, 1, 2, ...9. Игрок делает ходы, чтобы узнать эти цифры\n";
	cout << "\tи их порядок. Каждый ход состоит из четырёх цифр, 0 может стоять на первом месте. В ответ компьютер\n";
	cout << "\tпоказывает число отгаданных цифр, стоящих на своих местах(число быков) и число отгаданных цифр, стоящих\n";
	cout << "\tне на своих местах(число коров).\n\n";
	cout << "Пример:\n\n";
	cout << "\tКомпьютер задумал 1234. Игрок сделал ход 2034. Компьютер ответил : 2 быка(цифры 3 и 4) и 1 корова(цифра 2).\n\n";
	cout << "\t\tКомпьютер уже что - то задумал. Играем!\n\n";

	const int size = 4;
	const int playerNumber = 4;
	int a[size]{};
	int b[playerNumber]{};
	int i1, i2, i3, i4, j1, j2, j3, j4;
	int bulls, cows;

	for (int i = 0; i < size; i++)
	{
		a[i] = (rand() % 10);
		i1 = i / 1000;
		i2 = (i % 1000) / 100;
		i3 = (i % 100) / 10;
		i4 = (i % 1000) % 10;
		//cout << a[i] << endl;
	}
	if (a[i1] == 0 || a[i1] == a[i2] || a[i1] == a[i3] || a[i1] == a[i4] || a[i2] == a[i3] || a[i2] == a[i4] || a[i3] == a[i4]);



	
	
		cout << "ВВЕДИТЕ ВАШЕ ЧИСЛО: ";
		cin >> b[playerNumber];

		for (int j = 0; j < playerNumber; j++)
		{
			j1 = j / 1000;
			j2 = (j % 1000) / 100;
			j3 = (j % 100) / 10;
			j4 = (j % 1000) % 10;

			bulls = 0;
			cows = 0;

			if (j1 == i1) bulls += 1;
			else if (j1 == i2 || j1 == i3 || j1 == i4) cows += 1;
			if (j2 == i2) bulls += 1;
			else if (j2 == i1 || j2 == i3 || j2 == i4) cows += 1;
			if (j3 == i3) bulls += 1;
			else if (j3 == i1 || j3 == i2 || j3 == i4) cows += 1;
			if (j4 == i4) bulls += 1;
			else if (j4 == i1 || j4 == i2 || j4 == i3) cows += 1;
		}
		cout << "БЫКИ: " << bulls << endl;
		cout << "КОРОВЫ: " << cows << endl;
	 while (a[size] != b[playerNumber]);

	cout << "\t\t\t\tПОЗДРОВЛЯЕМ ВЫ ПОБЕДИЛИ!!!\n\n" << endl;
}

