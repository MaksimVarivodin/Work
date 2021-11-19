#include "film_cl.h"
// функция рисовки мяча
void film() {
	ifstream CIN;
	ofstream COUT;
	string path1 = "film.txt";
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
void Enter_check(int & a, const int & max, const int & min) {
	bool ready = false;
	string er = "Число не входит в диапазон значений!\n Введите число еще раз: ";
	while (!ready) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
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
			cout << "Замечены сторонние символы!\n Введите число еще раз: ";
		}
	}
}
// функция окрашивающая принимаемую строку в серый
void С_gray(const string& a) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	cout << a;
	SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) |Black));
}
// функция которая показывает какую строку выбрали
void Choose(const string& a) {
	int otstup_p = 25;
	cout << setw(otstup_p) << "--> ";
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
