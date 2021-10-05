#include "match_cl.h"
// ������� �������� �����
void Enter_check(string & a) {
	string b;
	getline(cin, b);
	a = b;
}
// ������� �������� �����
void Enter_check(int & a) {
	bool ready = false;
	while (!ready) // ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
	{
		string b;
		cin >> b;
		try
		{
			a = stoi(b);
			ready = true;
		}
		catch (const std::exception&)
		{
			cout << "�������� ���� �����" << endl;
		}		
	}
}
// ������� ������������ ����������� ������ � �����
void �_gray(const string& a) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	cout << a;
	SetConsoleTextAttribute(hConsole, (WORD)((Magenta << 4) |Black));
}
// ������� ������� ���������� ����� ������ �������
void choose(const string& a) {
	cout << setw(11) << "--> ";
	�_gray(a);
	cout << endl;
}
// ������ ������ ������ ����(��)
int Menu_show(const string* arr, const int & size) {

	bool done = false;
	int choice;
	int pos = 1;
	for (;;)
	{
		system("cls");
		string back_txt = "color " + to_string(Magenta) + to_string(Black);
		system(back_txt.c_str());
		cout << setw(19) << arr[0] << endl;
		int i = 1;
		for (; i < pos; i++)
			cout << setw(11 + arr[i].length()) << arr[i] << endl;
		choose(arr[pos]);
		i++;
		for (; i < size; i++)
			cout << setw(11 + arr[i].length()) << arr[i] << endl;

		choice = _getch();
		if (choice == 224)
			choice = _getch();


		if (choice == 13)
			// enter
		{
			system("cls");
			return pos;
		}

		if (choice == 27 || done == true)
		{
			done = false;
			break;
		}

		switch (choice) {
		case 72:			
			if (pos == 1)	pos = size - 1;
			else pos--;
			break;
		case 80:			
			if (pos == size - 1)pos = 1;
			else pos++;
			break;
		}
	}

}
