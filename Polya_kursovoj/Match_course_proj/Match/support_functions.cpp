#include "match_cl.h"
// функция рисовки мяча
void ball() {
	ifstream CIN;
	ofstream COUT;
	string path1 = "ball.txt";
	// открываем файл для записи, на случай если он не создан
	COUT.open(path1, ios::app);
	COUT.close();
	// открываем файл для чтения, чтобы получить названия комманд
	CIN.open(path1, ios::app | ios::in);
	// если не открылось, то ошибка
	if (!CIN.is_open()) { cout << "Error!"; }
	else {
		int size = 0;
		string* a = new string[size];
		// пока не конец файла
		while (!CIN.eof()) {
			// изменяем размер массива стринг
			Resize(a, size);
			// инициализируем элемент массива
			a[size - 1] = "";
			// считываем в него строку
			getline(CIN, a[size - 1]);
			cout << a[size - 1]<< endl;
		}
		delete[] a;
	}
	CIN.close();
}
// фукнция проверки ввода
void Enter_check(string & a) {
	string b;
	getline(cin, b);
	a = b;
}
// функция проверки ввода
void Enter_check(int & a) {
	bool ready = false;
	while (!ready) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		string b;
		getline(cin, b);
		try
		{
			a = stoi(b);
			ready = true;
		}
		catch (const std::exception&)
		{
			cout << "Неверный ввод числа" << endl;
		}		
	}
}
// функция окрашивающая принимаемую строку в серый
void С_gray(const string& a) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	cout << a;
	SetConsoleTextAttribute(hConsole, (WORD)((Magenta << 4) |Black));
}
// функция которая показывает какую строку выбрали
void Choose(const string& a) {
	cout << setw(11) << "--> ";
	С_gray(a);
	cout << endl;
}
// фунция вывода любого меню(ЮИ)
int Menu_show(const string* arr, const int & size) {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//получение хендла
	CONSOLE_CURSOR_INFO cursor = { 100,false };//число от 1 до 100 размер курсора в процентах; false\true - видимость
	SetConsoleCursorInfo(hCons, &cursor);
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
		Choose(arr[pos]);
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
