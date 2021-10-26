#include "match_cl.h"

// инициализируем статические переменные
int Match::MATCH_COUNT = 0;
Match* Match::head = NULL;
Match* Match::tail = NULL;
Match* Match::buf = NULL;
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
Match & Match::ret_el(int ind)
{
	if (ind < 1)
		return *head;
	else if (ind>Match::MATCH_COUNT)
		return *tail;
	buf = head;
	while (buf->index_numb != ind) {
		buf = buf->next;
	}
	return *buf;
}
// перегрузка оператора =
Match & Match::operator=(const Match & other)
{
	// TODO: insert return statement here
	this->operator()(other.team1_minutes, other.team2_minutes, other.team1, other.team2);
	return *this;
}
// метод добавления одного экземпляра(в конец)
void Match::menu_add()
{
	int s = 3;
	int q = 0;
	bool norm_enter = false;
	auto* menu = new string[s]{ "Выберите количество добаляемых элементов: " ,
		"1 - ПО умолчанию, \nавтоматически добавляется 20 экзепляров",
		"2 - Ввод вручную, \nили количества, или добавление одного, но со своими параметрами"
	};
	auto* menu2 = new string[s]{ "Выберите что хотите ввести вручную: " ,
		"1 - Количество добавляемых элементов",
		"2 - Добавить один элемент и ввести \nвсе его параметры"
	};
	string str = "Введите количество элементов: ";
	Match::buf = tail;
	switch (Menu_show(menu, s)) {
	case 1:
		system("cls");
		for (int i = 0; i < 20; i++)			
			buf = buf->add_match();			
		break;
	case 2:
		system("cls");
		switch (Menu_show(menu2, s)) {
		case 1:
			system("cls");
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

			for (int i = 0; i < q; i++)
				buf = buf->add_match();
			break;
		case 2:
			system("cls");
			buf->add_match(2);
			break;
		}
		break;
	}
	delete[] menu;
	delete[] menu2;
}
Match * Match::add()
{
	buf = new Match; // выделение памяти под следующий элемент 
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
Match* Match::add_match(const int & Case)
{
	int i1 = rand() % 4;
	int i2 = rand() % 4;

	this->add();
	switch (Case) {
	    case 1:
			// увеличиваем массив минут на некоторое количество мест от 0 до 3
			Match::tail->team1_minutes.resize(i1);
			// увеличиваем массив минут на некоторое количество мест от 0 до 3
			Match::tail->team2_minutes.resize(i2);
			// генерируем минуты
			gen_min(Match::tail->team1_minutes);
			// генерируем минуты
			gen_min(Match::tail->team2_minutes);
			
			Match::tail->operator()(Match::tail->team1_minutes, Match::tail->team2_minutes);
			// считываем и присваиваем имена комманд
			Match::tail->match_setter();
			
			break;
		case 2:
			// в перегрузке автоматически считаются остальные данные
			cin >> *(Match::tail);
			break;	
		default:
			cout << "Неправильная цифра" << endl;
			system("pause");
	}
	if (tail != head) {
		*buf = *tail;
		*tail = *buf;
	}
	return tail;

}

// метод удаления матчей(удаляет последний элемент массива)
void Match::menu_del()
{
	int s = 3;
	int q = 0;
	int s2 = MATCH_COUNT;
	bool norm_enter = false;
	auto* menu = new string[s]{ "Выберите количество добаляемых элементов: " ,
		"1 - ПО умолчанию, автоматически чистит список",
		"2 - Ввод вручную количества удаляемых елементов"
	};
	Match::buf = Match::tail;
	string str = "Введите количество элементов: ";
	switch (Menu_show(menu, s)) {
	case 1:
		system("cls");
		for (int i = 0; i < s2; i++) {			
			buf = buf->del_match();
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
			buf = buf->del_match();
		}
		break;
	}
	delete[] menu;
}

Match* Match::del_match()
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
// методы записи в файл
void Match::menu_write()
{
	int s = 3;
	string q = "";
	int s2 = MATCH_COUNT;
	bool norm_enter = false;
	auto* menu = new string[s]{ "Выберите куда записать информацию " ,
		"1 - ПО умолчанию, автоматически запишет в \"data.txt\"",
		"2 - Ввод вручную пути для записи"
	};
	Match::buf = Match::head;
	string str = "Введите путь для записи(не забудьте про расширение :) ): ";
	switch (Menu_show(menu, s)) {
	case 1:
		system("cls");
		write();
		for (int i = 0; i < MATCH_COUNT; i++) {
			write(*buf);
			if(buf!= tail)
			buf = buf->next;
		}
			
		break;
	case 2:
		system("cls");
		cout << str;
		Enter_check(q);
		write(q);
		for (int i = 0; i < MATCH_COUNT; i++) {
			write(*buf, q);
			if (buf != tail)
				buf = buf->next;
		}
		break;
	}
	delete[] menu;
}
void Match::write( Match & a, const string & b)
{
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
		a.team1_count>0 ? 2 * a.team1_count + a.team1_count - 1 : 0,// минуты		
		a.first_team_win ? (a.team1).length() : a.second_team_win ? (a.team2).length() : Nichja.length(), // победитель
		to_string(a.teams_count).length(),//количество голов
		3,
		(a.team2).length(),// длина комманды 2
		to_string(a.team2_count).length(),// счет второй команды
		a.team2_count > 0 ? 2 * a.team2_count + a.team2_count - 1 : 0, // минуты
		14, // победитель
		8//количество голов
	};
	// размер сетва для каждой колонки
	int col[size]{};
	int i = 0;
	for (int &var : col)
	{
		var = a.col_count(txt[i], COL[i % 6]);
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
	ifstream CIN;
	ofstream COUT;

	COUT.open(b, ios::app | ios::out);
	for (int i = 0; i < size - 6; i++)
		COUT << "|" << setw(col[i]) << text[i] << setw(COL[i] - col[i]);
	COUT << "|";
	COUT << "\n";

	for (int i = size - 6; i < size; i++)
		COUT << "|" << setw(col[i]) << text[i] << setw(COL[i % 6] - col[i]);
	COUT << "|";
	COUT << "\n";
	COUT << " ---------------------------------------------------------------------------------------------------\n";

	COUT.close();
}
void Match::write(const string & b)
{
	ifstream CIN;
	ofstream COUT;
	COUT.open(b, ios::app | ios::out);
	COUT << " ___________________________________________________________________________________________________\n";
	COUT << "/ # |            Команды             |  Счет  |  Минуты   |           Победитель           |  Голы  \\\n";
	COUT << " ---------------------------------------------------------------------------------------------------\n" ;

	COUT.close();
}
// печать
void Match::print()
{
	bool fin = false;
	int c = 0, c2 = 0, f = 0;
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
		case 1:	Match::buf = Match::head;	break;
		case 2:	Match::buf = Match::tail;	break;
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
	}
	if (!fin) {
		system("cls"); int lines = 6 + Match::MATCH_COUNT * 3;
		string mode = "mode con cols=105 lines=" + to_string(lines);
		system(mode.c_str());//задание размеров окна консоли
		Match::shapka();// печатаем заголовок таблички
		while (buf !=  NULL) {
			cout << *buf;
			buf = (c2 == 1 ? buf->next : buf->prev);
		}
		cout << endl << "Общее количество матчей: " << Match::MATCH_COUNT << endl;
	}
	else {
		system("cls"); int lines = 9;
		string mode = "mode con cols=105 lines=" + to_string(lines);
		system(mode.c_str());//задание размеров окна консоли
		Match::shapka();// печатаем заголовок таблички
		cout << buf->ret_el(f);
	}
	
	delete[] menu;
	delete[] menu2;	
}
void Match::info()
{
	cout << "Поліна Карлаш\nОПК-329" << endl;
}
// сортировка
void Match::sort()
{
	int lines = 6 + Match::MATCH_COUNT * 3;
	string mode = "mode con cols=105 lines=" + to_string(lines);
	system(mode.c_str());//задание размеров окна консоли
	int * ind = new int[Match::MATCH_COUNT];
	buf = head;
	for (int i = 1; i < Match::MATCH_COUNT+ 1; i++)
	{
		ind[i - 1] = i;
	} 
	for (int i = 0; i < Match::MATCH_COUNT; i++)	{
	
		for (int j = i; j > 0 && buf->ret_el(ind[j - 1]).teams_count >  buf->ret_el(ind[j]).teams_count; j--) {
			swap(ind[j - 1], ind[j]);
		}
	}
	shapka();
	for (int i = 0; i < Match::MATCH_COUNT; i++)
	{
	   cout << buf->ret_el(ind[i]);
	}
	delete[] ind;
}
// фильтры
void Match::menu_filtr()
{
	int size = 5;
	string* menu = new string[size]{
		"Выберите фильтр: ",
		"1 - По номерам",
		"2 - По количеству голов",
		"3 - По минутам",
		"4 - По победителям",
	};
	system("cls"); int lines = 6 + Match::MATCH_COUNT * 3;
	string mode = "mode con cols=105 lines=" + to_string(lines);
	system(mode.c_str());
	switch (Menu_show(menu, size)) {
	case 1: filtr_id(); break;
	case 2: filtr_goals(); break;
	case 3: filtr_mins(); break;
	case 4: filtr_win(); break;
	}
	delete[] menu;
}
void Match::filtr_id()
{
	int a;
	string *menu = new string [3]{
	"Выберите как фильтровать(элементы с введенным номером выводятся)", 
	"1- Больше введенного номера",
	"2- Меньше введенного номера"
	};
	cout << "Введите число: ";
	Enter_check(a);

	switch (Menu_show(menu, 3)) {
	case 1: *buf = buf->ret_el(a);
		shapka();
		while (buf != NULL) {
			cout << *buf;
			buf = buf->next;
		}
			break;
	case 2: buf = head;
		shapka();
		while ( buf->index_numb!= a+1) {
			cout << *buf;
			buf = buf->next;
		}
		break;
	}
	delete[] menu;
}
void Match::filtr_goals()
{
	int a;
	string *menu = new string[3]{
		"Выберите как фильтровать(элементы с введенным количеством голов выводятся)",
		"1- Больше введенного количества голов",
		"2- Меньше введенного количества голов"
	};
	cout << "Введите число: ";
	Enter_check(a);
	if (a > 6) {
		cout << "Введено слишком большое число" << endl;
		return;
	}
	else  if (a < 0) {
		cout << "Введено слишком маленькое число" << endl;
		return;
	}
	buf = head;
	int k = Menu_show(menu, 3);
	shapka();
	while (buf != NULL) {
		switch (k) {
		case 1:
			if (buf->teams_count >= a)
			    cout << *buf;
		break;
		case 2:
			if (buf->teams_count <= a)
				cout << *buf;
			break;
		}		
		buf = buf->next;
	}
	delete[] menu;
}
void Match::filtr_mins()
{
	buf = head;
	string *menu = new string[3]{
		"Выберите как фильтровать:",
		"1- Вывести матчи где голы забиты в первом тайме",
		"2- Вывести матчи где голы забиты во втором тайме"
	};
	int k = Menu_show(menu, 3);
	bool check = false;
	shapka();
	while (buf != NULL) {
		if (buf->teams_count > 0) {
			
			if (buf->team1_minutes.size() > 0) {
				switch (k) {
				case 1:
					if (buf->team1_minutes[buf->team1_minutes.size() - 1]<= 45 )
						check = true;
					break;
				case 2:
					if (buf->team1_minutes[0]>= 46)
						check = true;
					break;
				}
			}
			if (buf->team2_minutes.size() > 0) {
				switch (k) {
				case 1:
					if (buf->team1_minutes[buf->team2_minutes.size() - 1] <= 45)
						check = true;
					break;
				case 2:
					if (buf->team2_minutes[0] >= 46)
						check = true;
					break;
				}
			}
		}
		if (check) {
			cout << *buf;
		}
		
		buf = buf->next;
	}
	delete[] menu;
}
void Match::filtr_win()
{
	buf = head;
	string *menu = new string[4]{
		"Выберите как фильтровать:",
		"1- Вывести матчи где победитель 1-я команда",
		"2- Вывести матчи где победитель 2-я команда",
		"3- Вывести матчи где никто не победил"
	};
	int k = Menu_show(menu, 4);
	shapka();
	while (buf != NULL) {
		switch (k) {
		case 1:
			if (buf->first_team_win)
				cout << *buf;
			break;
		case 2:
			if (buf->second_team_win)
				cout << *buf;
			break;
		case 3:
			if ((!buf->first_team_win) && !(buf->second_team_win))
				cout << *buf;
			break;
		}

		buf = buf->next;
	}
	delete[] menu;
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
// метод меню
void Match::MENU()
{
	int size = 9;
	auto* menu = new string[size]{
		"МЕНЮ",
		"1 - Добавление элементов",
		"2 - Удаление элементов",
		"3 - Печать элементов",
		"4 - Запись элементов в файл",
		"5 - Фильтр элементов",
		"6 - Упорядоченные элементы",
		"7 - О создателе(Поле)",
		"8 - Выход"
	};
	for (;;) {
		int buf = Menu_show(menu, size);
		switch (buf) {
		case 1:	menu_add();	break;
		case 2:	menu_del();	break;
		case 3:	print(); break;
		case 4: menu_write(); break;
		case 5:	menu_filtr(); break;
		case 6: sort();	break;
		case 7:	system("cls"); info();
			break;
		}
		if (buf == 8)break;
		else {
			system("pause");
			system("mode con cols=60 lines=15");//задание размеров окна консоли
		}
	}
	delete[] menu;
}
