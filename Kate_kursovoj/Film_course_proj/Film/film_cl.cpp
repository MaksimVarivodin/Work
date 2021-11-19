#include "film_cl.h"
ifstream & operator>>(ifstream & in, Line & a)
{
	string buf;
	getline(in, buf);
	int size = 2;
	string *buf0 = new string[size];
	int length = 1;
	int counter = 0;
	bool probel = false;
	//  проход по всей считанной строке
	while (length < buf.length()) {
		// если не разделитель или пробел перед словами
		if (buf[length] != ' ' && (buf[length] != '|' && length != 1)) {
			buf0[counter] += buf[length];
		}
		// если разделитель, то переход к заполенению данных другого типа
		else if (buf[length] == '|' && length != 1) {
			counter++;
		}
		// если пробел между словами
		else if (length < buf.length() - 2)
		{
			if ((buf[length - 1] != ' ' && buf[length - 1] != '|') &&
				buf[length] == ' ' && (buf[length + 1] != ' ' && buf[length + 1] != '|'))
				buf0[counter] += buf[length];
		}
		length++;
	}
	// сеттеры
	a(buf0[0], stoi(buf0[1]));
	delete[] buf0;
	getline(in, buf);
	return in;
}
Line Line::lSearch(const string & a, const string & path1)
{
	ifstream CIN;
	ofstream COUT;
	int size = 0;
	string buf0 = "Проблема с количеством имен в файле";
	Line to_return{};
	try
	{
		// открываем файл для чтения, чтобы получить названия комманд
		CIN.open(path1, ios::app | ios::in);
		// если не открылось, то ошибка
		if (!CIN.is_open()) { cout << "Error!"; }
		else {

			Line* lns = new Line[size];
			// пока не конец файла
			while (!CIN.eof()) {
				// изменяем размер массива стринг
				Resize(lns, size);
				// считываем в него строку
				CIN >> lns[size - 1];
			}

			if (size <= 1 || lns[size - 1].GETstr().length() <= 1)
				throw buf0;
			for (int i = 0; i < size; i++) {
				if (lns[i].GETstr().find(a) != string::npos)
				to_return = lns[i];
			}
			
			// освобождаем память
			delete[] lns;
		}
		CIN.close();
	}
	catch (const string &buf0)
	{
		if (size <= 1)throw buf0;
		cout << "Файл отсутствует или поврежден" << endl;
		// открываем файл для записи, на случай если он не создан
		COUT.open(path1, ios::app);
		COUT.close();
	}
	return to_return;
}
// перегрузка оператора () - инициализатор
Line Line::operator()(const string & a, const int & b)
{
	str = a;
	num = b;
	return *this;
}
bool Line::operator>(const Line & other)
{
	return this->str > other.str;
}
bool Line::operator<(const Line & other)
{
	return this->str < other.str;
}
bool Line::operator==(const Line & other)
{
	return this->str == other.str;
}
bool Line::operator>=(const Line & other)
{
	return (this->num > other.num) || (this->num == other.num);
}
bool Line::operator<=(const Line & other)
{
	return (this->num < other.num) || (this->num == other.num);
}
// инициализируем статические переменные
int Film::total_cash = 0;
// количество экземпляров
int Film::flm_count = 0;
// начало списка
Film* Film::head = NULL;
// конец списка
Film* Film::tail = NULL;
// буферный указатель
Film* Film::buf = NULL;

// просто заголовок для таблицы
void Film::shapka()
{
	cout << " _________________________________________________________________________________________________________________________________________" << endl;
	cout << "/ # |               Название               |       Режиссёр      |           Студия           |    Время(ч:м)  |    Время (м)  |   Сборы  \\" << endl;	
	cout << " -----------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
// метод для чтения имен из файла
Line Film::Line_setter(const string &path1)
{
	ifstream CIN;
	ofstream COUT;
	int size = 0;	
	string buf0 = "Проблема с количеством имен в файле";
	Line to_return{};
	try
	{
		// открываем файл для чтения, чтобы получить названия комманд
		CIN.open(path1, ios::app | ios::in);
		// если не открылось, то ошибка
		if (!CIN.is_open()) { cout << "Error!"; }
		else {
			
			Line* a = new Line[size];
			// пока не конец файла
			while (!CIN.eof()) {
				// изменяем размер массива стринг
				Resize(a, size);
				// считываем в него строку
				CIN >> a[size - 1];
			}
			
			if (size <= 1 || a[size - 1].GETstr().length()<=1)
				throw buf0;
			int b = rand() % size;
			to_return = a[b];			
			// освобождаем память
			delete[] a;
		}
		CIN.close();
	}
	catch (const string &buf0)
	{
		if (size <= 1)throw buf0;
		cout << "Файл отсутствует или поврежден" << endl;
		// открываем файл для записи, на случай если он не создан
		COUT.open(path1, ios::app);
		COUT.close();
	}
	return to_return;	
}
// вспомогательный метод для расчета метода setw()
int Film:: col_count(const int & a, const int & b)
{
	// a - размер строки, в - размер колонки
	int c = a + (b - a) / 2;
	return c;
}
// перегрузка оператора () с расчетом вычисляемых полей
void Film::operator()(const Line & n, const Line & p, const Line & s, const tm & d)
{
	this->name = n;
	this->producer = p;
	this->studio = s;
	this->dur = d;
	this->mins = this->dur.tm_hour * 60 + this->dur.tm_min;
	this->cash = name.GETnum() * 10000 + producer.GETnum() * 10000 + studio.GETnum() * 10000;
}

// метод который возвращает элемент по индексу
Film & Film::ret_el(int ind)
{
	if (ind < 1)
		return *head;
	else if (ind>Film::flm_count)
		return *tail;
	buf = head;
	while (buf->index_numb != ind) {
		buf = buf->next;
	}
	return *buf;
}
// перегрузка оператора =
Film & Film::operator=(const Film & other)
{
	// TODO: insert return statement here
	this->operator()(other.name, other.producer, other.studio, other.dur);
	return *this;
}
// рандомизатор для имени
Line Film::SETname()
{
	try
	{
		this->name = this->Line_setter("names.txt");
	}
	catch (const string &buf0)
	{
		string er = "Name setter Fu ";
		er += buf0;
		throw er;
	}
	return this->name;
}
// рандомизатор для режиссера
Line Film::SETprod()
{
	try
	{
		this->producer = this->Line_setter("prods.txt");
	}
	catch (const string &buf0)
	{
		string er = "Prod setter Fu ";
		er += buf0;
		throw er;
	}
	return this->producer;
}
// рандомизатор для студии
Line Film::SETstud()
{
	try
	{
		this->studio = this->Line_setter("studs.txt");
	}
	catch (const string &buf0)
	{
		string er = "Prod setter Fu ";
		er += buf0;
		throw er;
	}
	return this->studio;
}
// рандомизатор для длительности фильма
tm Film::SETdurt()
{
	tm time{};
	time.tm_hour = rand() % 3 + 1;
	switch (time.tm_hour) {
	case 1:
		time.tm_min = rand() % 30 + 30;
		break;
	case 2:
		time.tm_min = rand() %60;
		break;
	case 3:
		time.tm_min = 0;
		break;	
	}
	this->dur = time;
	return this->dur;
}
// меню для добавления экземпляров(в конец)
void Film::menu_add()
{
	// размеры массива пунктов меню
	int s = 4;
	int q = 20;
	// переменная для проверки правильности ввода
	bool norm_enter = false;
	auto* menu = new string[s]{ "Выберите количество добаляемых элементов: " ,
		"1 - ПО умолчанию, автоматически \n\t\tдобавляется 20 экзепляров",
		"2 - Ввод вручную, или количества, или \n\t\tдобавление одного, но со своими параметрами",
		"3 - Выход "
	};
	auto* menu2 = new string[s]{ "Выберите что хотите ввести вручную: " ,
		"1 - Количество добавляемых элементов",
		"2 - Добавить один элемент и ввести \nвсе его параметры",
		"3 - Выход "
	};
	string str = "Введите количество элементов: ";
	// перемещаемся в конец
	Film::buf = tail;
	// меню_шов возращает значения от 1 до "размер"
	switch (Menu_show(menu, s)) {
	case 1:
		system("cls");
		// по умолчанию добавляем 20 элементов
		// проверка на проблемы с файлом
		try
		{
			for (int i = 0; i < q; i++)
				buf = buf->ADDfilm();
		}
		catch (const string & buf0)
		{
			cout << buf0 << endl;
			cout << "Произвожу очистку мусорных элементов" << endl;
			for (int i = 0; i < Film::flm_count; i++)
				buf->del();
		}
				
		break;
	case 2:
		system("cls");
		switch (Menu_show(menu2, s)) {
		case 1:
			system("cls");
			cout << str;
			// проверка на ввод
			while (!norm_enter) {
				Enter_check(q);
				if (q > 0)
				{
					norm_enter = true;
				}
				else {
					cout << "Введите число больше" << endl;
				}
			}
			// проверка на проблемы с файлом
			try
			{
				for (int i = 0; i < q; i++)
					buf = buf->ADDfilm();
			}
			catch (const string & buf0)
			{
				cout << buf0 << endl;
			}
			break;
		case 2:
			// вводим данные в один из добавляемых элементов
			system("cls");
			buf->ADDfilm(2);
			break;
		default:
			delete[] menu;
			delete[] menu2;
			return;
		}
		break;
	default:
		delete[] menu;
		delete[] menu2;
		return;
	}
	delete[] menu;
	delete[] menu2;
}
// метод добавления одного узла
Film * Film::add()
{
	buf = new Film; // выделение памяти под следующий элемент 
	if (this == NULL && head == NULL) // Добавление нового корня
	{
		if (head == NULL) // если в списке нет элементов
		{
			head = buf;
			tail = buf;
		}
		else // если нужно добавить первый \
			 			    элемент в список, при том \
                что там уже есть элементы
		{
			buf->next = head;
			head->prev = buf;
			head = buf;
			buf->prev = NULL;
			// если следующий элемент это хвост
			if (buf->next->next == NULL) {
				tail = buf->next;
			}
		}
	}
	else if (this == tail) {
		if (head->next == NULL) // если в списке 1-элемент
		{
			tail = buf;
			buf->prev = head;
			head->next = buf;
		}
		else { // если в списке больше элементов
			buf->prev = tail;
			tail->next = buf;
			tail = buf;
		}
	}
	else // Добавление узла после текущего и текущий не head и не tail
	{
		if (buf->next != NULL) buf->next->prev = buf;
		buf->next = this->next;
		this->next = buf;
		buf->prev = this;
	}
	return buf;
}
// метод добавления одного матча
Film* Film::ADDfilm(const int & Case)
{
	this->add();
	try
	{
		switch (Case) {
		case 1:
			Film::tail->operator()(tail->SETname(), tail->SETprod(), tail->SETstud(), tail->SETdurt());
			break;
		case 2:
			// в перегрузке автоматически считаются остальные данные
			cin >> *tail;
			break;
		default:
			cout << "Неправильная цифра" << endl;
			system("pause");
		}
		total_cash += tail->cash;
	}
	catch (const string & buf0)
	{
		throw buf0;
	}

	return tail;

}
// метод удаления фильмов(удаляет последний элемент массива)
void Film::menu_del()
{
	if (Film::flm_count<=0) {
		cout << "Функция недоступна! Нет Фильмов" << endl;
		return;
	}
	int s = 4;
	int q = 0;
	int s2 = flm_count;
	bool norm_enter = false;
	auto* menu = new string[s]{ "Выберите количество добаляемых элементов: " ,
		"1 - ПО умолчанию, автоматически чистит список",
		"2 - Ввод вручную количества удаляемых елементов",
		"3 - Выход"
	};
	Film::buf = Film::tail;
	string str = "Введите количество элементов: ";
	switch (Menu_show(menu, s)) {
	case 1:
		system("cls");
		for (int i = 0; i < s2; i++) {			
			buf = buf->del();
		}
			
		break;
	case 2:
		cout << str;
		while (!norm_enter) {
			Enter_check(q);
			if (q > 0)
			{
				norm_enter = true;
			}
			else {
				cout << "Введите число больше" << endl;
			}
		}

		for (int i = 0; i < q; i++) {
			buf = buf->del();
		}
		break;
	default:
		delete[] menu;
		return;
	}
	delete[] menu;
}
// удаление одного фильма
Film* Film::del()
{
	if (this == NULL || head == NULL) { return NULL; } // В списке нет узлов
	if (this == head)	// Удаление корневого узла
	{
		head = this->next;
		buf = head;
		if (head == NULL)tail = NULL;
	}
	else if (this == tail) // 
	{
		this->prev->next = NULL;
		tail = this->prev;
		buf = tail;
	}
	else {
		if (this->next != NULL) // Удаление промежуточного узла
		{
			this->next->prev = this->prev;
		}
		this->prev->next = this->next;
		buf = this->next;
	}
	delete this;
	return buf;
}
// печать
void Film::print()
{
	if (Film::flm_count<1) {
		cout << "Функция недоступна! Нет Фильмов" << endl;
		return;
	}
	bool fin = false;
	int c = 0, c2 = 0, f = 0;
	bool norm_enter = false;
	auto* menu = new string[3]{ "Выберите вид печати: ", "1 - обычная",	"2 - по заданному номеру" },
		*menu2 = new string[3]{ "Выберите порядок:","1 - прямой","2 - обратный" };
	auto str = "Введите номер фильма, который необходимо вывести: ";
	c = Menu_show(menu, 3);
	switch (c) {
	case 1:
		system("cls");
		c2 = Menu_show(menu2, 3);
		switch (c2) {
		case 1:	Film::buf = Film::head;	break;
		case 2:	Film::buf = Film::tail;	break;
		default:
			delete[] menu;
			delete[] menu2;
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
		fin = true;
		break;
	default:
		delete[] menu;
		delete[] menu2;
		return;
	}
	if (!fin) {
		// 	int COL[]{ 4, 39, 22, 29, 17, 16, 11};
// 
		system("cls"); int lines = 7 + Film::flm_count * 3;
		string mode = "mode con cols=146 lines=" + to_string(lines);
		system(mode.c_str());//задание размеров окна консоли
		Film::shapka();// печатаем заголовок таблички
		while (buf !=  NULL) {
			cout << *buf;
			buf = (c2 == 1 ? buf->next : buf->prev);
		}
		cout << endl << "Общее количество фильмов: " << Film::flm_count<< endl;
		cout << endl << "Общее количество собранных денег: " << Film::total_cash<< endl;
	}
	else {
		system("cls"); int lines = 9;
		string mode = "mode con cols=105 lines=" + to_string(lines);
		system(mode.c_str());//задание размеров окна консоли
		Film::shapka();// печатаем заголовок таблички
		cout << buf->ret_el(f);
	}
	
	delete[] menu;
	delete[] menu2;	
}
// инфа о создателе
void Film::info()
{
	cout << "Колосова Катерина \nОПК-329" << endl;
}
// пересчет всех кассовых сборов
void Film::recalc_total_cash()
{
	Film::total_cash = 0;
	buf = head;
	while (buf!=NULL) {
		Film::total_cash += buf->cash;
		buf = buf->next;
	}
}
// перегруженный оператор вывода
ostream & operator<< (ostream& out, Film& a) {

	//	cout << "/ # |              Название               |      Режиссёр      |           Студия          |   Время(ч:м)  |   Время (м)  |  Сборы  \\" << endl;
	const int size = 7;
	char str[] = "   Время(ч:м)  ";
	// размеры колонок
	int COL[]{ 4, 39, 22, 29, 17, 16, 11};
	// размеры текстов
	int txt[size]{
		to_string(a.index_numb).length(),// номер
		(a.name.GETstr()).length(),// Название	
		(a.producer.GETstr()).length(),// Режиссёр		
		(a.studio.GETstr()).length(),// Студия				
		4,// Время(ч:м)
		to_string(a.mins).length(),// Время (м)
		to_string(a.cash).length(),// Сборы 
	};
	// размер сетва для каждой колонки
	int col[size]{};
	int i = 0;
	for (int &var :  col)
	{
		var = a.col_count(txt[i], COL[i]);
		i++;
	}
	// формирование строки минут
	string buf1 = "", str1 = "";
	if (a.dur.tm_min < 10) str1 += "0";
	buf1 += to_string(a.dur.tm_hour) +":" + str1 + to_string(a.dur.tm_min);
	
	string text[size]{
	to_string(a.index_numb),// номер
		(a.name.GETstr()),// Название	
		(a.producer.GETstr()),// Режиссёр		
		(a.studio.GETstr()),// Студия				
		buf1,// Время(ч:м)
		to_string(a.mins),// Время (м)
		to_string(a.cash),// Сборы
	};
	for (int i = 0; i < size; i++)
		cout << "|" << setw(col[i]) << text[i] << setw(COL[i] - col[i]);
	cout << "|" << endl;
	cout << " -----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	return out;
}


// перегруженный оператор ввода
istream& operator>>(istream & in, Film& a) {
	string ns = "", ps = "", ss = "";
	int ni = 0, pi = 0, si = 0, hour = 0, min = 0, mins = 0;
	
	cout << "Введите название фильма: "<< endl;
	Enter_check(ns);
	cout << "Введите коэффициэнт названия(0 - 100):" << endl;
	Enter_check(ni);
	cout << "Введите имя режиссёра фильма:" << endl;
	Enter_check(ps);
	cout << "Введите коэффициэнт режиссёра(0 - 100):" << endl;
	Enter_check(pi);
	cout << "Введите имя студии фильма:" << endl;
	Enter_check(ss);
	cout << "Введите коэффициэнт студии(0 - 100):" << endl;
	Enter_check(si);
	cout << "Введите введите сколько полных часов шел фильм( 1 - 3 ): " << endl;
	Enter_check(hour, 3, 1);
	cout << "и количество минут";
	switch (hour)
	{
	case 1:
		cout << "(30 - 59)";
		cout << ":" << endl;
		Enter_check(min, 59, 30);
		break;
	case 2:
		cout << "(0 - 59)";
		cout << ":" << endl;
		Enter_check(min, 59);
		break;
	case 3:
		cout << "Введена максимальная длительность фильма: 3 часа";
		break;
	}
	mins = hour * 60 + min;
	cout << "Длительность в минутах высчитывается как [hours] * 60 + min: " << mins << endl;


	// инициализация полей
	a.name(ns, ni); a.producer(ps, pi); a.studio(ss, si); 
	a.dur.tm_hour = hour;
	a.dur.tm_min = min;
    // пересчет вычисляемых полей
	a(a.name,a.producer, a.studio, a.dur);
	return in;
}
// метод меню
void Film::MENU()
{
	int size = 10;
	auto* menu = new string[size]{
		"МЕНЮ",
		"1 - Добавление элементов",
		"2 - Удаление элементов",
        "3 - Редактирование элементов", 
		"4 - Печать элементов",
		"5 - Запись элементов в файл",
		"6 - Фильтр элементов",
		"7 - Упорядоченные элементы",
		"8 - О создателе",
		"9 - Выход"
	};
	for (;;) {
		int buf = Menu_show(menu, size);
		switch (buf) {
		case 1:	menu_add();	break;
		case 2:	menu_del();	break;
		case 3:	menu_edit();	break;
		case 4:	print(); break;
		case 5: menu_write(); break;
		case 6:	menu_filtr(); break;
		case 7: sort();	break;
		case 8:	system("cls"); info();
			break;
		default:
			delete[] menu;
			return;
		}
			recalc_total_cash();
			system("pause");
			system("mode con cols=80 lines=20");//задание размеров окна консоли	
		
	}
	delete[] menu;
}

// методы записи в файл
void Film::menu_write()
{
	if (Film::flm_count<1) {
		cout << "Функция недоступна! Нет Фильмов" << endl;
		return;
	}
	int s = 3;
	string q = "";
	int s2 = flm_count;
	bool norm_enter = false;
	auto* menu = new string[s]{ "Выберите куда записать информацию " ,
		"1 - ПО умолчанию, автоматически запишет в \"data.txt\"",
		"2 - Ввод вручную пути для записи"
	};
	Film::buf = Film::head;
	string str = "Введите путь для записи\n(не забудьте про расширение :) ): ";
	switch (Menu_show(menu, s)) {
	case 1:
		system("cls");
		write();
		for (int i = 0; i < flm_count; i++) {
			write(*buf);
			if (buf != tail)
				buf = buf->next;
		}
		write("data.txt", 2);
		break;
	case 2:
		system("cls");
		cout << str;
		Enter_check(q);
		write(q);
		for (int i = 0; i < flm_count; i++) {
			write(*buf, q);
			if (buf != tail)
				buf = buf->next;
		}
		write(q, 2);
		break;
	}
	delete[] menu;
}
// запись одного фильма в файл
void Film::write(Film & a, const string & b)
{
	const int size = 7;
	// размеры колонок
	int COL[]{ 4, 39, 22, 29, 17, 16, 11 };	// размеры текстов

	int txt[size]{
		to_string(a.index_numb).length(),// номер
		(a.name.GETstr()).length(),// Название	
		(a.producer.GETstr()).length(),// Режиссёр		
		(a.studio.GETstr()).length(),// Студия				
		4,// Время(ч:м)
		to_string(a.mins).length(),// Время (м)
		to_string(a.cash).length(),// Сборы 
	};
	// размер сетва для каждой колонки
	int col[size]{};
	int i = 0;
	for (int &var : col)
	{
		var = a.col_count(txt[i], COL[i]);
		i++;
	}
	// формирование строки минут
	string buf1 = "", str = a.dur.tm_min<10 ? "0" : "";

	buf1 += to_string(a.dur.tm_hour) + ":" + str + to_string(a.dur.tm_min);

	string text[size]{
		to_string(a.index_numb),// номер
		(a.name.GETstr()),// Название	
		(a.producer.GETstr()),// Режиссёр		
		(a.studio.GETstr()),// Студия				
		buf1,// Время(ч:м)
		to_string(a.mins),// Время (м)
		to_string(a.cash),// Сборы
	};
	ifstream CIN;
	ofstream COUT;

	COUT.open(b, ios::app | ios::out);
	for (int i = 0; i < size; i++)
		COUT << "|" << setw(col[i]) << text[i] << setw(COL[i] - col[i]);
	COUT << "|";
	COUT << "\n";
    COUT << " -----------------------------------------------------------------------------------------------------------------------------------------" << endl;

	COUT.close();
}
// запись шапки
void Film::write(const string & b, const int & Case)
{
	ifstream CIN;
	ofstream COUT;
	COUT.open(b, ios::app | ios::out);
	switch (Case) {
	case 1:
		COUT << " _________________________________________________________________________________________________________________________________________" << endl;
		COUT << "/ # |               Название               |       Режиссёр      |           Студия           |    Время(ч:м)  |    Время (м)  |   Сборы  \\" << endl;
		COUT << " -----------------------------------------------------------------------------------------------------------------------------------------" << endl;
		break;
	case 2:
		COUT << "Всего собрано денег за все фильмы: " << Film::total_cash << "\n";
		break;
	}
	COUT.close();
}
// сортировка
void Film::sort()
{

   if (Film::flm_count<1) {
	   cout << "Функция недоступна! Нет Фильмов" << endl;
	   return;
   }

   system("cls"); int lines = 7 + Film::flm_count * 3;
   string mode = "mode con cols=146 lines=" + to_string(lines);
   system(mode.c_str());//задание размеров окна консоли

   int * ind = new int[Film::flm_count];
   buf = head;
   for (int i = 1; i < Film::flm_count + 1; i++)
   {
      ind[i - 1] = i;
   }
   for (int i = 0; i < Film::flm_count; i++) {   
      for (int j = i; j > 0 && buf->ret_el(ind[j - 1]).name > buf->ret_el(ind[j]).name; j--) {
         swap(ind[j - 1], ind[j]);
      }
   }
   Film::shapka();// печатаем заголовок таблички
   for (int i = 0; i < Film::flm_count; i++)
   {
        cout << buf->ret_el(ind[i]);
   }
   delete[] ind;   
}

void Film::menu_filtr()
{
	if (Film::flm_count<1) {
		cout << "Функция недоступна! Нет Фильмов" << endl;
		return;
	}
	int size = 9;
	string* menu = new string[size]{
		"Выберите фильтр: \n\t\t\t\
          P.S: все текстовые данные фильтруются\n\t\t\t \
          по их коэффициэнту прибыльности\n\t\t\t \
          (коэффициэнты хранятся в текстовых файлах данных проэкта)",
		"1 - По номерам",
		"2 - По имени фильма",
		"3 - По продюсеру",
		"4 - По студии",
		"5 - По длительности",
		"6 - По количеству минут",
		"7 - По сборам",
		"8 - Выход"
	};
    int lines = 7 + Film::flm_count * 3;
	string mode = "mode con cols=146 lines=" + to_string(lines);
	system(mode.c_str());//задание размеров окна консоли
	switch (Menu_show(menu, size)) {
	case 1:filtr_id(); break;
	case 2:filtr_name(); break;
	case 3:filtr_producer(); break;
	case 4:filtr_studio(); break;
	case 5:filtr_dur(); break;
	case 6:filtr_mins(); break;
	case 7:filtr_cash(); break;
	case 8:
		delete[] menu;
		return;
	}
	delete[] menu;
}

void Film::filtr_id()
{
	int a;
	string *menu = new string[3]{
		"Выберите как фильтровать(элементы с введенным номером выводятся)",
		"1- Больше введенного номера",
		"2- Меньше введенного номера"
	};
	cout << "Введите число: ";
	Enter_check(a, Film::flm_count, 1);
	
	int c = Menu_show(menu, 3);
	shapka();
	switch (c) {
	case 1: 
		buf = &buf->ret_el(a);
		
		while (buf != NULL) {
			assert(buf!= NULL);
			cout << *buf;
			buf = buf->next;
		}
		break;
	case 2: buf = head;
		
		while (buf->index_numb != a + 1) {
			cout << *buf;
			buf = buf->next;
		}
		break;
	}
	
	delete[] menu;
}

void Film::filtr_name()
{
	string a;
	string *menu = new string[3]{
		"Выберите как фильтровать(элементы с введенной буквой выводятся)\n\
		можно ввести и набор букв, например для поиска",
		"1- Больше введенной буквы",
		"2- Меньше введенной буквы" 
	};
	cout << "Введите набор букв: ";
	Enter_check(a);
	// поиск элемента и его коэффициэнта, ведь по нему происходит сравнение
	buf = head;
	Line extra{};
	extra = extra.lSearch(a, "names.txt");
	
	int c = Menu_show(menu, 3);
	shapka();
	switch (c) {
	case 1:
		while (buf != NULL) {
			if(buf->name >= extra)
			cout << *buf;
			buf = buf->next;
		}
		break;
	case 2: 

		while (buf != NULL) {
			if (buf->name <= extra)
				cout << *buf;
			buf = buf->next;
		}
		break;
	}
	delete[] menu;
}

void Film::filtr_producer()
{
	string a;
	string *menu = new string[3]{
		"Выберите как фильтровать(элементы с введенной буквой выводятся)\n\
		можно ввести и набор букв, например для поиска",
		"1- Больше введенной буквы",
		"2- Меньше введенной буквы"
	};
	cout << "Введите набор букв: ";
	Enter_check(a);

	buf = head;
	Line extra{};
	extra = extra.lSearch(a, "prods.txt");

	int c = Menu_show(menu, 3);
	shapka();
	switch (c) {
	case 1:
		while (buf != NULL) {
			if (buf->producer >= extra)
				cout << *buf;
			buf = buf->next;
		}
		break;
	case 2:

		while (buf != NULL) {
			if (buf->producer <= extra)
				cout << *buf;
			buf = buf->next;
		}
		break;
	}
	delete[] menu;
}

void Film::filtr_studio()
{
	string a;
	string *menu = new string[3]{
		"Выберите как фильтровать(элементы с введенной буквой выводятся)\n\
		можно ввести и набор букв, например для поиска",
		"1- Больше введенной буквы",
		"2- Меньше введенной буквы"
	};
	cout << "Введите набор букв: ";
	Enter_check(a);

	buf = head;
	Line extra{};
	extra = extra.lSearch(a, "studs.txt");

	int c = Menu_show(menu, 3);
	shapka();
	switch (c) {
	case 1:
		while (buf != NULL) {
			if (buf->studio >= extra)
				cout << *buf;
			buf = buf->next;
		}
		break;
	case 2:

		while (buf != NULL) {
			if (buf->studio <= extra)
				cout << *buf;
			buf = buf->next;
		}
		break;
	}	
	delete[] menu;
}

void Film::filtr_dur()
{
	int h = 0, m= 0;
	string *menu = new string[3]{
		"Выберите как фильтровать(элементы с введенными цифрами выводятся)",
		"1- Больше введенных часов",
		"2- Меньше введенных часов"
	};
	cout << "Введите  количество часов: ";
	Enter_check(h,3,1);
	cout << "Введите  количество минут: ";
	if(h== 1)
	Enter_check(m, 59, 30);
	else if(h == 2)
		Enter_check(m, 59, 0);
	buf = head;
	int k = Menu_show(menu, 3);
	shapka();
	while (buf != NULL) {
		switch (k) {
		case 1:
			if (buf->dur.tm_hour> h)
				cout << *buf;
			else if(buf->dur.tm_hour == h && buf->dur.tm_min>= m)
				cout << *buf;
			break;
		case 2:
			if (buf->dur.tm_hour < h)
				cout << *buf;
			else if (buf->dur.tm_hour == h && buf->dur.tm_min <= m)
				cout << *buf;
			break;
		}
		buf = buf->next;
	}
	delete[] menu;
}

void Film::filtr_mins()
{
	int m;
	string *menu = new string[3]{
		"Выберите как фильтровать(элементы с введенными цифрами выводятся)",
		"1- Больше введенных минут",
		"2- Меньше введенных минут"
	};
	cout << "Введите набор цифр: ";
    Enter_check(m, 180, 90);
	buf = head;
	int k = Menu_show(menu, 3);
	shapka();
	while (buf != NULL) {
		switch (k) {
		case 1:
			if (buf->mins >= m)
				cout << *buf;
			break;
		case 2:
			if (buf->mins >= m)
				cout << *buf;
			break;
		}
		buf = buf->next;
	}
	delete[] menu;
}

void Film::filtr_cash()
{
	int c;
	string *menu = new string[3]{
		"Выберите как фильтровать(элементы с введенными цифрами выводятся)",
		"1- Больше введенных денег",
		"2- Меньше введенных денег"
	};
	cout << "Введите цифры(10000 - 3000000): ";
	Enter_check(c, 3000000, 10000);
	buf = head;
	int k = Menu_show(menu, 3);
	shapka();
	while (buf != NULL) {
		switch (k) {
		case 1:
			if (buf->cash >= c)
				cout << *buf;
			break;
		case 2:
			if (buf->cash <= c)
				cout << *buf;
			break;
		}
		buf = buf->next;
	}
	delete[] menu;
}

void Film::menu_edit()
{
	string str1 = "";
	int  val1 = 0, val2 = 0;

	// пересчет вычисляемых полей
	
	system("mode con cols=105 lines=15");//задание размеров окна консоли
	if (Film::flm_count<1) {
		cout << "Функция недоступна! Нет Фильмов" << endl;
		return;
	}
	int in = 0;
	bool enter_ok = false;
	string * red = new string[4]{
		"Выбранный элемент тот, который предполагается к редактированию?",
		"1- Да",
		"2- Нет",
		"3- Выход"
	};
	while (!enter_ok)
	{
		system("cls");
		string mode = "mode con cols=146 lines=14";
		system(mode.c_str());
		cout << "Введите номер фильма, который нужно отредактировать: ";
		Enter_check(in, Film::flm_count,1);
		*buf = buf->ret_el(in);
		

		cout << *buf<< endl;
		system("pause");
		switch (Menu_show(red, 4)) {
			case 1:
			enter_ok = true;
			break;
			case 3:
				return;
				break;
		}
		
	}

	string * menu = new string[6]{
		"Выберите поле для редактирования:",
		"1 - Имя фильма",
		"2 - Имя продюсера",
		"3 - Имя студии",
		"4 - Длительность",
		"5 - Выход"
	};

	switch (Menu_show(menu, 6)) {
	case 1:
		cout << "Введите название фильма: " << endl;
		Enter_check(str1);
		cout << "Введите коэффициэнт названия(0 - 100): " << endl;
		Enter_check(val1);
		buf->name(str1, val1);
		break;
	case 2:
		cout << "Введите имя режиссёра фильма: " << endl;
		Enter_check(str1);
		cout << "Введите коэффициэнт режиссёра(0 - 100): " << endl;
		Enter_check(val1);
		buf->producer(str1, val1);
		break;
	case 3:
		cout << "Введите имя студии фильма: " << endl;
		Enter_check(str1);
		cout << "Введите коэффициэнт студии(0 - 100): " << endl;
		Enter_check(val1);
		buf->studio(str1, val1);
		break;

	case 4:
		cout << "Введите введите сколько полных часов шел фильм( 1 - 3 ): " << endl;
		Enter_check(val1, 3, 1);		
		switch (val1)
		{
		case 1:
			cout << "и количество минут"<< "(30 - 59): ";
			cout << ":" << endl;
			Enter_check(val2, 59, 30);
			break;
		case 2:
			cout << "и количество минут" << "(0 - 59): ";
			cout << ":" << endl;
			Enter_check(val2, 59);
			break;
		case 3:
			cout << "Введена максимальная длительность фильма: 3 часа"<< endl;
			break;
		}
		buf->dur.tm_hour = val1;
		buf->dur.tm_min = val2;
		break;
	case 5:  delete[] menu;
		delete[] red; return; break;
	}
	buf->operator()(buf->name, buf->producer, buf->studio, buf->dur);
	cout << *buf;
	delete[] menu;
	delete[] red;
}

