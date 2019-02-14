#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int>Alex(20);
	int minIndex = 0;
	int maxIndex = 0;

	for (int i = 0; i < Alex.size(); i++)
	{
		Alex[i] = rand() % 100;
		cout << Alex[i] << endl;
	}
	cout << "********" << endl; 

	Alex.push_back(100);

	for (int i = 0; i < Alex.size(); i++)
	{
		cout << Alex[i] << endl;
	}

	cout << "********" << endl;


	auto begin = Alex.cbegin(); // указатель на первый элемент
	auto end = Alex.cend();// указатель на последний элемент

	Alex.erase(begin + 1, end - 1);

	for (int i = 0; i < Alex.size(); i++)
	{
		cout << Alex[i] << endl;
	}
}