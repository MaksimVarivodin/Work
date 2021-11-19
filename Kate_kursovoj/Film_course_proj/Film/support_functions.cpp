#include "film_cl.h"
// ������� ������� ����
void film() {
	ifstream CIN;
	ofstream COUT;
	string path1 = "film.txt";
	// ��������� ���� ��� ������, �� ������ ���� �� �� ������
	COUT.open(path1, ios::app);
	COUT.close();
	// ��������� ���� ��� ������, ����� �������� �������� �������
	CIN.open(path1, ios::app | ios::in);
	// ���� �� ���������, �� ������
	if (!CIN.is_open()) { cout << "Error!"; }
	else {
		int size = 0;
		string* a = new string[size];
		// ���� �� ����� �����
		while (!CIN.eof()) {
			// �������� ������ ������� ������
			Resize(a, size);
			// �������������� ������� �������
			a[size - 1] = "";
			// ��������� � ���� ������
			getline(CIN, a[size - 1]);
			cout << a[size - 1]<< endl;
		}
		delete[] a;
	}
	CIN.close();
}
// ������� �������� �����
void Enter_check(string & a) {
	string b;
	getline(cin, b);
	a = b;
}
// ������� �������� �����
void Enter_check(int & a, const int & max, const int & min) {
	bool ready = false;
	string er = "����� �� ������ � �������� ��������!\n ������� ����� ��� ���: ";
	while (!ready) // ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
	{

		string b;
		getline(cin, b);
		try
		{
			a = stoi(b);
			if (a < min || a> max)  throw er;
			ready = true;
		}
		catch (const string & er)
		{
			cout << er;
		}		
		catch (const std::exception&)
		{
			cout << "�������� ��������� �������!\n ������� ����� ��� ���: ";
		}
	}
}
// ������� ������������ ����������� ������ � �����
void �_gray(const string& a) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	cout << a;
	SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) |Black));
}
// ������� ������� ���������� ����� ������ �������
void Choose(const string& a) {
	int otstup_p = 25;
	cout << setw(otstup_p) << "--> ";
	�_gray(a);
	cout << endl;
}
// ������ ������ ������ ����(��)
int Menu_show(const string* arr, const int & size) {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//��������� ������
	CONSOLE_CURSOR_INFO cursor = { 100,false };//����� �� 1 �� 100 ������ ������� � ���������; false\true - ���������
	SetConsoleCursorInfo(hCons, &cursor);
	bool done = false;
	int choice;
	int pos = 1;

	int otstup_p = 25, otstup_m = 31;
	for (;;)
	{
		system("cls");
		cout << "\n\n\n";
		string back_txt = "color C" + to_string(Black);
		system(back_txt.c_str());

		cout << setw(otstup_m + arr[0].length()) << arr[0] << endl;
		int i = 1;
		for (; i < pos; i++)
			cout << setw(otstup_p + arr[i].length()) << arr[i] << endl;
		Choose(arr[pos]);
		i++;
		for (; i < size; i++)
			cout << setw(otstup_p + arr[i].length()) << arr[i] << endl;

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
