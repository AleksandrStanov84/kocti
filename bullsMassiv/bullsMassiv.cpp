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
	cout << "\t\t\t\t(���� � ������)\n\n\n";

	cout << "������� ����:\n\n";
	cout << "\t��������� ���������� ������ ��������� ����� �� 0, 1, 2, ...9. ����� ������ ����, ����� ������ ��� �����\n";
	cout << "\t� �� �������. ������ ��� ������� �� ������ ����, 0 ����� ������ �� ������ �����. � ����� ���������\n";
	cout << "\t���������� ����� ���������� ����, ������� �� ����� ������(����� �����) � ����� ���������� ����, �������\n";
	cout << "\t�� �� ����� ������(����� �����).\n\n";
	cout << "������:\n\n";
	cout << "\t��������� ������� 1234. ����� ������ ��� 2034. ��������� ������� : 2 ����(����� 3 � 4) � 1 ������(����� 2).\n\n";
	cout << "\t\t��������� ��� ��� - �� �������. ������!\n\n";

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



	
	
		cout << "������� ���� �����: ";
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
		cout << "����: " << bulls << endl;
		cout << "������: " << cows << endl;
	 while (a[size] != b[playerNumber]);

	cout << "\t\t\t\t����������� �� ��������!!!\n\n" << endl;
}

