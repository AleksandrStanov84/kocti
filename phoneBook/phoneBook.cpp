#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <conio.h>

using namespace std;



struct manName
{
	char *surName;
	char *adress;
	long long phone;
};

const char *fileName = "nameBooks.dat";


int Menu(const char *menuItems, int countItems)
{
	const int Esc = 27;

	cout << menuItems << "ÑÄÅËÀÉÒÅ ÂÀØ ÂÛÁÎÐ (or Esc to exit): [ ]\b\b" << flush;

	char key;
	do
	{
		key = (char)_getwch();
		if (key == 0 || key == 0xE0)
		{
			_getwch();
			key = 0;
		}
	} while ((key < '1' || key > '0' + countItems) && key != Esc);

	if (key == Esc)
		cout << "Esc]\n";
	else
		cout << key << endl;
	return (key == Esc) ? 0 : key - '0';
}

void DeleteNameBook(manName *&manNames, int &manCount)
{
	if (manCount > 0)
	{
		for (int i = 0; i < manCount; i++)
		{
			delete[] manNames[i].surName;
			delete[] manNames[i].adress;
		}
		delete[] manNames;

		manNames = nullptr;
		manCount = 0;
	}
}


void enterManPhone(manName &st)
{
	char str[200];

	cout << "Ô.È.Î: ";
	cin.ignore(1);
	cin.getline(str, 200);

	st.surName = new char[strlen(str) + 1];
	strcpy(st.surName, str);

	cout << "ÀÄÐÅÑ: ";
	cin.getline(str, 100);

	st.adress = new char[strlen(str) + 1];
	strcpy(st.adress, str);

	cout << "ÒÅËÅÔÎÍ: ";
	cin >> st.phone;
}

void enterCountManPhoneBook(manName *&manNames, int &manCount)
{
	cout << "ÂÂÅÄÈÒÅ ÊÎË-ÂÎ ËÞÄÅÉ: ";
	cin >> manCount;
	cout << endl;

	manNames = new manName[manCount];

	for (int i = 0; i < manCount; i++)
	{
		enterManPhone(manNames[i]);
		cout << endl;
	}
}

void printManNameInfo(const manName &st)
{
	cout << "Ô.È.Î: " << st.surName << endl
		 << "ÀÄÐÅÑ: " << st.adress << endl
		 << "ÒÅËÅÔÎÍ: " << st.phone << endl;
}

void printManBookInfo(const manName *manNames, int manCount)
{
	for (int i = 0; i < manCount; i++)
	{
		printManNameInfo(manNames[i]);
		cout << endl;
	}
}

void saveNameToFile(const manName &st, FILE *file)
{
	int len = strlen(st.surName);
	fwrite(&len, sizeof(len), 1, file);
	fwrite(st.surName, sizeof(char), len, file);

    len = strlen(st.adress);
	fwrite(&len, sizeof(len), 1, file);
	fwrite(st.adress, sizeof(char), len, file);

	fwrite(&st.phone, sizeof(st.phone), len, file);
}

void saveNameBookToFile(const manName *manNames, int manCount)
{
	if (manCount == 0)
	{
		cout << "Íå÷åãî ñîõðîíÿòü!\n\n";
		return;
	}

	FILE *file;

	if ((file = fopen(fileName, "w")) == nullptr)
	{
		cout << "Íåâîçìîæíî îòêðûòü ôàéë";
		return;
	}
	fwrite(&manCount, sizeof(manCount), 1, file);

	for (int i = 0; i < manCount; i++)
		saveNameToFile(manNames[i], file);
	fclose(file);

	cout << "Ôàéë ñîõðàíåí óäà÷íî.\n\n";	
}

void loadNameToFile(manName &st, FILE *file)
{
	int len;

	fread(&len, sizeof(len), 1, file);
	st.surName = new char[len + 1];
	fread(st.surName, sizeof(char), len, file);
	st.surName[len] = '\0';

	fread(&len, sizeof(len), 1, file);
	st.adress = new char[len + 1];
	fread(st.adress, sizeof(char), len, file);
	st.adress[len] = '\0';

	fread(&st.phone, sizeof(st.phone), len, file);
}

void loadNameBooktoFile(manName *&manNames, int &manCount)
{
	int len;
	FILE *file;
	if ((file = fopen(fileName, "r")) == nullptr)
	{
		cout << "Íåâîçìîæíî îòêðûòü ôàéë";
		return;
	}

	DeleteNameBook(manNames, manCount);

	fread(&manCount, sizeof(manCount), 1, file);

	manNames = new manName[manCount];

	for (int i = 0; i < manCount; i++) // äîáàòü äèíàì ïàìÿòü
		loadNameToFile(manNames[i], file);
	fclose(file);

	cout << "Ôàéë çàãðóæåí óäà÷íî.\n\n";
}


int main()
{
	setlocale(LC_ALL,"Russian");
	char menuItems[] =
	 "1. Ââåñòè èíôîðìàöèþ\n\n" 
	 "2. Íàïè÷àòàòü èíôîðìàöèþ\n\n"
	 "3. Ñîõðàíèòü èíôîðìàöèþ\n\n"
	 "4. Çàãðóçèòü èíôîðìàöèþ\n\n";
	cout << endl;

	cout << "Èñïîëüçóéòå öèôðû äëÿ âûáîðà ìåíþ\n";
	cout << "He çàáûâàéòå íàæèìàòü 'Enter' ïîñëå Âàøåãî âûáîðà!\n" << endl;

	int manCount = 0;
	manName *manNames = nullptr;

	int choice;
	do
	{
		choice = Menu(menuItems, 4);
		cout << endl;

		switch (choice)
		{
		case 1:
			enterCountManPhoneBook(manNames, manCount);
			break;
		case 2:
			printManBookInfo(manNames, manCount);
			break;
		case 3:
			saveNameBooktoFile(manNames, manCount);
			break;
		case 4:
			loadNameBookToFile(manNames, manCount);
			printManBookInfo(manNames, manCount);
			break;
		}
	} while (choice != 0);

	DeleteNameBook(manNames, manCount);
}
