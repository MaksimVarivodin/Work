#include "match_cl.h"
// инициализируем статические переменные
int Match::MATCH_COUNT = 0;
Match* Match::MATCH_POINTER = nullptr;
// генератор минут
void gen_min(vector<int>& a,const int & min, const int & max)
{
	int min0 = min;
	
	for (int i = 0; i < a.size(); i++)
	{
		// цикл работает до тех пор пока значение,\
					 которое генерируется случайно, не будет меньше \
			чем 90, если это не последний элемент, причем \
            диапазон уменьшается с каждой итерацией, так как\
            каждое следующее значение должно быть больше предыдущего
		bool exit = false;
		while (!exit) {
			a[i] = rand() % (max - min0 + 1) + min0;
			if ((i< a.size() - 1 && a[i] != max) || (i == a.size() - 1))
				exit = true;			
		}		 
		min0 = a[i];
	}
}
// просто заголовок для таблицы
void Match::shapka()
{
	cout << " ___________________________________________________________________________________________________" << endl;
	cout << "/ # |            Команды             |  Счет  |  Минуты   |           Победитель           |  Голы  \\" << endl;
	cout << " ---------------------------------------------------------------------------------------------------" << endl;

}
// метод для чтения имен из файла
void Match::match_setter()
{
	ifstream CIN;
	ofstream COUT;
	string path1 = "names.txt";
	// открываем файл для записи, на случай если он не создан
	COUT.open(path1, ios::app);
	COUT.close();
	// открываем файл для чтения, чтобы получить названия комманд
	CIN.open(path1, ios::app | ios::in);

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
		}

		// выбираем индекс для первой комманды
		int b = rand() % size;
		// устанавливаем в него второй индекс для входа в цикл while(){}
		int c = b;
		// работает до тех пор пока первый равен второму(то есть выходит из него когда разные)
		while (b == c) 
			c = rand() % size;
		// устанвливаем имена
		this->team1 = a[b];
		this->team2 = a[c];		
		// освобождаем память
		delete[] a;
	}
	CIN.close();
}
// вспомогательный метод для расчета метода setw()
int Match:: col_count(const int & a, const int & b)
{
	// a - размер строки, в - размер колонки
	int c = a + (b - a) / 2;
	return c;
}
// перегрузка оператора () с расчетом вычисляемых полей
void Match::operator()(vector<int> a, vector<int> b, const string & team1_name, const string & team2_name)
{
	this->team1 = team1_name;
	this->team2 = team2_name;
	this->team1_count = a.size();
	this->team2_count = b.size();
	// получаем общее количество голов
	this->teams_count = this->team1_count + this->team2_count;
	if (this->team1_count > this->team2_count) {
		this->first_team_win = true;
		this->second_team_win = false;
	}		
	else if (this->team2_count > this->team1_count)
	{
		this->first_team_win = false;
		this->second_team_win = true;
	}
	else 
	{
		this->first_team_win = false;
		this->second_team_win = false;
	}
	this->team1_minutes = a;
	this->team2_minutes = b;
}
// перегрузка оператора =
Match & Match::operator=(const Match & other)
{
	// TODO: insert return statement here
	this->operator()(other.team1_minutes, other.team2_minutes, other.team1, other.team2);
	return *this;
}
// метод изменения размера массива
void Match::resize(const int & a)
{
	int n_size = a;
	bool smaller = a > MATCH_COUNT ? true:false;
	Match::MATCH_COUNT = 0;
	if (a == NULL) {
		delete[]Match::MATCH_POINTER;
		return;
	}
		Match* new_arr = new Match[n_size];
		// не выходить за рамки текущего массива
		if (smaller) {
			for (int i = 0; i < n_size - 1; i++) {
				new_arr[i] = Match::MATCH_POINTER[i];
			}
		}
		else {
			for (int i = 0; i < a; i++) {
				new_arr[i] = Match::MATCH_POINTER[i];
			}
		}
	
	delete[]Match :: MATCH_POINTER;
	Match::MATCH_POINTER = new_arr;
	Match::MATCH_COUNT = n_size;
}
// метод добавления одного экземпляра(в конец)
void Match::add_match(const int & Case)
{
	int i1 = rand() % 4;
	int i2 = rand() % 4;
	Match::resize();
	switch (Case) {
	    case 1:
			// увеличиваем массив минут на некоторое количество мест от 0 до 3
			Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team1_minutes.resize(i1);
			// увеличиваем массив минут на некоторое количество мест от 0 до 3
			Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team2_minutes.resize(i2);
			// генерируем минуты
			gen_min(Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team1_minutes);
			// генерируем минуты
			gen_min(Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team2_minutes);
			
			Match::MATCH_POINTER[Match::MATCH_COUNT - 1](Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team1_minutes,
				Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team2_minutes);
			// считываем и присваиваем имена комманд
			Match::MATCH_POINTER[Match::MATCH_COUNT - 1].match_setter();		
			
			break;
		case 2:
			// в перегрузке автоматически считаются остальные данные
			cin >> Match::MATCH_POINTER[Match::MATCH_COUNT - 1];			
			break;	
		default:
			cout << "Неправильная цифра" << endl;
			system("pause");
	}
	Match buf;
	buf = Match::MATCH_POINTER[Match::MATCH_COUNT - 2];
	Match::MATCH_POINTER[Match::MATCH_COUNT - 2] = buf;
}

void Match::menu_add()
{
	int q = 0;
	cout << "Выберите количество добаляемых элементов" << endl;
	cout << "1 - ПО умолчанию" << endl;
	cout << "2 - Ввод вручную" << endl;
}

// метод удаления матчей(удаляет последний элемент массива)
void Match::del_match()
{
	Match::resize(Match::MATCH_COUNT - 1);
}
//  печать
void Match::print()
{
	int i = 0, c = 0, c2 = 0, f = 0;
	bool norm_enter = false;
	auto* menu = new string[3]{ "Выберите вид печати: ", "1 - обычная",	"2 - по заданному номеру" },
		*menu2 = new string[3]{ "Выберите порядок:","1 - прямой","2 - обратный" };
	auto str = "Введите номер матча, который необходимо вывести: ";
	c = Menu_show(menu, 3);
	switch (c) {
	case 1:
		system("cls");
		c2 = Menu_show(menu2, 3);
		switch (c2) {
		case 2:
			i = Match::MATCH_COUNT;
			break;
		default:
			i = 0;
			break;
		}
		break;
	case 2:
		system("cls");
		cout << str;
		while (!norm_enter) {
			Enter_check(f);
			if (f > 0)
			{
				norm_enter = true;
			}
			else {
				cout << "Введите число больше" << endl;
			}
		}
		c2 = 1;
		i = 0;
		break;
	}
	system("cls");
	Match::shapka();// печатаем заголовок таблички
	for (; c2 == 2 ? i > 0 : i < Match::MATCH_COUNT; c2 == 2 ? i-- : i++)
	{
		if ((MATCH_POINTER[i].index_numb == f && c == 2) || c == 1)
			cout << Match::MATCH_POINTER[i];
	}
	cout << endl << "Общее количество матчей: " << Match::MATCH_COUNT << endl;
	delete[] menu;
	delete[] menu2;
}
// перегруженный оператор вывода
ostream & operator<< (ostream& out, Match& a) {

	// cout << "/ # |           Команды            | Счет  |  Минуты  |  Победитель | Голы  \\" << endl;

	const int size = 12;
	// размеры колонок
	int COL[]{ 4, 33, 9, 12, 33, 9 };
	// размеры текстов

	string Nichja = "Ничья";
	int txt[size]{
		to_string(a.index_numb).length(),// номер
		(a.team1).length(),// длина комманды 1		
		to_string(a.team1_count).length(),// счет первой команды 		
		a.team1_count>0 ?2 * a.team1_count + a.team1_count - 1 : 0,// минуты		
		a.first_team_win ? (a.team1).length() : a.second_team_win? (a.team2).length(): Nichja.length(), // победитель
		to_string(a.teams_count).length(),//количество голов
		3,
		(a.team2).length(),// длина комманды 2
		to_string(a.team2_count).length(),// счет второй команды
		a.team2_count > 0? 2 * a.team2_count + a.team2_count - 1: 0, // минуты
		14, // победитель
		8//количество голов
	};
	// размер сетва для каждой колонки
	int col[size]{};
	int i = 0;
	for (int &var :  col)
	{
		var = a.col_count(txt[i], COL[i%6]);
		i++;
	}
	// формирование строки минут
	string buf1 = "";
	i = 0;
	for each (int var in a.team1_minutes)
	{
		if (var < 10)
		{
			buf1 += "0";
		}
		buf1 += to_string(var);
		if (i < a.team1_minutes.size() - 1)
		{
			buf1 += ":";
		}
		i++;
	}
	string buf2 = "";
	i = 0;
	for each (int var in a.team2_minutes)
	{
		if (var< 10)
			buf2 += "0";
		buf2 += to_string(var);
		if (i < a.team2_minutes.size() - 1)
		{
			buf2 += ":";
		}
		i++;
	}
	string text[size]{
	to_string(a.index_numb),// номер
	a.team1,// комманда 1
	to_string(a.team1_count),// счет первой команды 
	buf1,  // минуты
		a.first_team_win ? (a.team1) : a.second_team_win ? (a.team2) : Nichja, // победитель
	to_string(a.teams_count),//количество голов
	"   ", // номер
	a.team2,// комманда 2
	to_string(a.team2_count),// счет второй команды
	buf2,  // минуты
	"             ", // победитель
	"       "//количество голов
	};
	for (int i = 0; i < size -6; i++)
		cout << "|" << setw(col[i]) << text[i] << setw(COL[i] - col[i]);
	cout << "|" << endl;
	
	for (int i = size - 6; i < size; i++)
		cout << "|" << setw(col[i]) << text[i] << setw(COL[i % 6] - col[i]);
	cout << "|" << endl;
	cout << " ---------------------------------------------------------------------------------------------------" << endl;
	return out;
}
// перегруженный оператор ввода
istream& operator>>(istream & in, Match& a) {
	cout << "Введите названия комманд:"<< endl;
	cout << "1-ой: ";
	Enter_check(a.team1);
	cout << "2-ой: ";
	Enter_check(a.team2);
	int a0 = -1, b0 = -1;
	cout << "Введите количество голов для первой команды: ";

	while (a0 < 0 || a0>3)
	{
		Enter_check(a0);
		cout << "Повторите ввод, значения не соотвествуют требованиям к полю" << endl;
	}

	cout << "Введите количество голов для первой команды: ";
	while (b0 < 0 || b0>3) {
		Enter_check(b0);
		cout << "Повторите ввод, значения не соотвествуют требованиям к полю" << endl;
	}	
	a.team1_count = a0;
	a.team2_count = b0;
	a.team1_minutes.resize(a0);
	a.team2_minutes.resize(b0);
	cout << "Введите " << a.team1_minutes.size()<< " минуты для первой комманды: ";
	int min = 0;
	int max = 90;
	for (int &var : a.team1_minutes)
	{ 
		var = -1;
		while (var < min ||var > max ) {
			Enter_check(var);
			min = var;
			if (var < min || var > max)
				cout << "Повторите ввод, значения не соотвествуют требованиям к полю" << endl;
		}
		
	}
	cout << "Введите " << a.team2_minutes.size() << " минуты для второй комманды: ";
	min = 0;
	for (int &var : a.team2_minutes)
	{
		var = -1;
		while (var < min || var > max) {
			Enter_check(var);
			min = var;
			if (var < min || var > max)
				cout << "Повторите ввод, значения не соотвествуют требованиям к полю" << endl;
		}
	}
	return in;
}
