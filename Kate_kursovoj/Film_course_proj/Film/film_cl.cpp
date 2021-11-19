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
	//  ������ �� ���� ��������� ������
	while (length < buf.length()) {
		// ���� �� ����������� ��� ������ ����� �������
		if (buf[length] != ' ' && (buf[length] != '|' && length != 1)) {
			buf0[counter] += buf[length];
		}
		// ���� �����������, �� ������� � ����������� ������ ������� ����
		else if (buf[length] == '|' && length != 1) {
			counter++;
		}
		// ���� ������ ����� �������
		else if (length < buf.length() - 2)
		{
			if ((buf[length - 1] != ' ' && buf[length - 1] != '|') &&
				buf[length] == ' ' && (buf[length + 1] != ' ' && buf[length + 1] != '|'))
				buf0[counter] += buf[length];
		}
		length++;
	}
	// �������
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
	string buf0 = "�������� � ����������� ���� � �����";
	Line to_return{};
	try
	{
		// ��������� ���� ��� ������, ����� �������� �������� �������
		CIN.open(path1, ios::app | ios::in);
		// ���� �� ���������, �� ������
		if (!CIN.is_open()) { cout << "Error!"; }
		else {

			Line* lns = new Line[size];
			// ���� �� ����� �����
			while (!CIN.eof()) {
				// �������� ������ ������� ������
				Resize(lns, size);
				// ��������� � ���� ������
				CIN >> lns[size - 1];
			}

			if (size <= 1 || lns[size - 1].GETstr().length() <= 1)
				throw buf0;
			for (int i = 0; i < size; i++) {
				if (lns[i].GETstr().find(a) != string::npos)
				to_return = lns[i];
			}
			
			// ����������� ������
			delete[] lns;
		}
		CIN.close();
	}
	catch (const string &buf0)
	{
		if (size <= 1)throw buf0;
		cout << "���� ����������� ��� ���������" << endl;
		// ��������� ���� ��� ������, �� ������ ���� �� �� ������
		COUT.open(path1, ios::app);
		COUT.close();
	}
	return to_return;
}
// ���������� ��������� () - �������������
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
// �������������� ����������� ����������
int Film::total_cash = 0;
// ���������� �����������
int Film::flm_count = 0;
// ������ ������
Film* Film::head = NULL;
// ����� ������
Film* Film::tail = NULL;
// �������� ���������
Film* Film::buf = NULL;

// ������ ��������� ��� �������
void Film::shapka()
{
	cout << " _________________________________________________________________________________________________________________________________________" << endl;
	cout << "/ # |               ��������               |       �������      |           ������           |    �����(�:�)  |    ����� (�)  |   �����  \\" << endl;	
	cout << " -----------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
// ����� ��� ������ ���� �� �����
Line Film::Line_setter(const string &path1)
{
	ifstream CIN;
	ofstream COUT;
	int size = 0;	
	string buf0 = "�������� � ����������� ���� � �����";
	Line to_return{};
	try
	{
		// ��������� ���� ��� ������, ����� �������� �������� �������
		CIN.open(path1, ios::app | ios::in);
		// ���� �� ���������, �� ������
		if (!CIN.is_open()) { cout << "Error!"; }
		else {
			
			Line* a = new Line[size];
			// ���� �� ����� �����
			while (!CIN.eof()) {
				// �������� ������ ������� ������
				Resize(a, size);
				// ��������� � ���� ������
				CIN >> a[size - 1];
			}
			
			if (size <= 1 || a[size - 1].GETstr().length()<=1)
				throw buf0;
			int b = rand() % size;
			to_return = a[b];			
			// ����������� ������
			delete[] a;
		}
		CIN.close();
	}
	catch (const string &buf0)
	{
		if (size <= 1)throw buf0;
		cout << "���� ����������� ��� ���������" << endl;
		// ��������� ���� ��� ������, �� ������ ���� �� �� ������
		COUT.open(path1, ios::app);
		COUT.close();
	}
	return to_return;	
}
// ��������������� ����� ��� ������� ������ setw()
int Film:: col_count(const int & a, const int & b)
{
	// a - ������ ������, � - ������ �������
	int c = a + (b - a) / 2;
	return c;
}
// ���������� ��������� () � �������� ����������� �����
void Film::operator()(const Line & n, const Line & p, const Line & s, const tm & d)
{
	this->name = n;
	this->producer = p;
	this->studio = s;
	this->dur = d;
	this->mins = this->dur.tm_hour * 60 + this->dur.tm_min;
	this->cash = name.GETnum() * 10000 + producer.GETnum() * 10000 + studio.GETnum() * 10000;
}

// ����� ������� ���������� ������� �� �������
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
// ���������� ��������� =
Film & Film::operator=(const Film & other)
{
	// TODO: insert return statement here
	this->operator()(other.name, other.producer, other.studio, other.dur);
	return *this;
}
// ������������ ��� �����
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
// ������������ ��� ���������
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
// ������������ ��� ������
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
// ������������ ��� ������������ ������
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
// ���� ��� ���������� �����������(� �����)
void Film::menu_add()
{
	// ������� ������� ������� ����
	int s = 4;
	int q = 20;
	// ���������� ��� �������� ������������ �����
	bool norm_enter = false;
	auto* menu = new string[s]{ "�������� ���������� ���������� ���������: " ,
		"1 - �� ���������, ������������� \n\t\t����������� 20 ����������",
		"2 - ���� �������, ��� ����������, ��� \n\t\t���������� ������, �� �� ������ �����������",
		"3 - ����� "
	};
	auto* menu2 = new string[s]{ "�������� ��� ������ ������ �������: " ,
		"1 - ���������� ����������� ���������",
		"2 - �������� ���� ������� � ������ \n��� ��� ���������",
		"3 - ����� "
	};
	string str = "������� ���������� ���������: ";
	// ������������ � �����
	Film::buf = tail;
	// ����_��� ��������� �������� �� 1 �� "������"
	switch (Menu_show(menu, s)) {
	case 1:
		system("cls");
		// �� ��������� ��������� 20 ���������
		// �������� �� �������� � ������
		try
		{
			for (int i = 0; i < q; i++)
				buf = buf->ADDfilm();
		}
		catch (const string & buf0)
		{
			cout << buf0 << endl;
			cout << "��������� ������� �������� ���������" << endl;
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
			// �������� �� ����
			while (!norm_enter) {
				Enter_check(q);
				if (q > 0)
				{
					norm_enter = true;
				}
				else {
					cout << "������� ����� ������" << endl;
				}
			}
			// �������� �� �������� � ������
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
			// ������ ������ � ���� �� ����������� ���������
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
// ����� ���������� ������ ����
Film * Film::add()
{
	buf = new Film; // ��������� ������ ��� ��������� ������� 
	if (this == NULL && head == NULL) // ���������� ������ �����
	{
		if (head == NULL) // ���� � ������ ��� ���������
		{
			head = buf;
			tail = buf;
		}
		else // ���� ����� �������� ������ \
			 			    ������� � ������, ��� ��� \
                ��� ��� ��� ���� ��������
		{
			buf->next = head;
			head->prev = buf;
			head = buf;
			buf->prev = NULL;
			// ���� ��������� ������� ��� �����
			if (buf->next->next == NULL) {
				tail = buf->next;
			}
		}
	}
	else if (this == tail) {
		if (head->next == NULL) // ���� � ������ 1-�������
		{
			tail = buf;
			buf->prev = head;
			head->next = buf;
		}
		else { // ���� � ������ ������ ���������
			buf->prev = tail;
			tail->next = buf;
			tail = buf;
		}
	}
	else // ���������� ���� ����� �������� � ������� �� head � �� tail
	{
		if (buf->next != NULL) buf->next->prev = buf;
		buf->next = this->next;
		this->next = buf;
		buf->prev = this;
	}
	return buf;
}
// ����� ���������� ������ �����
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
			// � ���������� ������������� ��������� ��������� ������
			cin >> *tail;
			break;
		default:
			cout << "������������ �����" << endl;
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
// ����� �������� �������(������� ��������� ������� �������)
void Film::menu_del()
{
	if (Film::flm_count<=0) {
		cout << "������� ����������! ��� �������" << endl;
		return;
	}
	int s = 4;
	int q = 0;
	int s2 = flm_count;
	bool norm_enter = false;
	auto* menu = new string[s]{ "�������� ���������� ���������� ���������: " ,
		"1 - �� ���������, ������������� ������ ������",
		"2 - ���� ������� ���������� ��������� ���������",
		"3 - �����"
	};
	Film::buf = Film::tail;
	string str = "������� ���������� ���������: ";
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
				cout << "������� ����� ������" << endl;
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
// �������� ������ ������
Film* Film::del()
{
	if (this == NULL || head == NULL) { return NULL; } // � ������ ��� �����
	if (this == head)	// �������� ��������� ����
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
		if (this->next != NULL) // �������� �������������� ����
		{
			this->next->prev = this->prev;
		}
		this->prev->next = this->next;
		buf = this->next;
	}
	delete this;
	return buf;
}
// ������
void Film::print()
{
	if (Film::flm_count<1) {
		cout << "������� ����������! ��� �������" << endl;
		return;
	}
	bool fin = false;
	int c = 0, c2 = 0, f = 0;
	bool norm_enter = false;
	auto* menu = new string[3]{ "�������� ��� ������: ", "1 - �������",	"2 - �� ��������� ������" },
		*menu2 = new string[3]{ "�������� �������:","1 - ������","2 - ��������" };
	auto str = "������� ����� ������, ������� ���������� �������: ";
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
				cout << "������� ����� ������" << endl;
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
		system(mode.c_str());//������� �������� ���� �������
		Film::shapka();// �������� ��������� ��������
		while (buf !=  NULL) {
			cout << *buf;
			buf = (c2 == 1 ? buf->next : buf->prev);
		}
		cout << endl << "����� ���������� �������: " << Film::flm_count<< endl;
		cout << endl << "����� ���������� ��������� �����: " << Film::total_cash<< endl;
	}
	else {
		system("cls"); int lines = 9;
		string mode = "mode con cols=105 lines=" + to_string(lines);
		system(mode.c_str());//������� �������� ���� �������
		Film::shapka();// �������� ��������� ��������
		cout << buf->ret_el(f);
	}
	
	delete[] menu;
	delete[] menu2;	
}
// ���� � ���������
void Film::info()
{
	cout << "�������� �������� \n���-329" << endl;
}
// �������� ���� �������� ������
void Film::recalc_total_cash()
{
	Film::total_cash = 0;
	buf = head;
	while (buf!=NULL) {
		Film::total_cash += buf->cash;
		buf = buf->next;
	}
}
// ������������� �������� ������
ostream & operator<< (ostream& out, Film& a) {

	//	cout << "/ # |              ��������               |      �������      |           ������          |   �����(�:�)  |   ����� (�)  |  �����  \\" << endl;
	const int size = 7;
	char str[] = "   �����(�:�)  ";
	// ������� �������
	int COL[]{ 4, 39, 22, 29, 17, 16, 11};
	// ������� �������
	int txt[size]{
		to_string(a.index_numb).length(),// �����
		(a.name.GETstr()).length(),// ��������	
		(a.producer.GETstr()).length(),// �������		
		(a.studio.GETstr()).length(),// ������				
		4,// �����(�:�)
		to_string(a.mins).length(),// ����� (�)
		to_string(a.cash).length(),// ����� 
	};
	// ������ ����� ��� ������ �������
	int col[size]{};
	int i = 0;
	for (int &var :  col)
	{
		var = a.col_count(txt[i], COL[i]);
		i++;
	}
	// ������������ ������ �����
	string buf1 = "", str1 = "";
	if (a.dur.tm_min < 10) str1 += "0";
	buf1 += to_string(a.dur.tm_hour) +":" + str1 + to_string(a.dur.tm_min);
	
	string text[size]{
	to_string(a.index_numb),// �����
		(a.name.GETstr()),// ��������	
		(a.producer.GETstr()),// �������		
		(a.studio.GETstr()),// ������				
		buf1,// �����(�:�)
		to_string(a.mins),// ����� (�)
		to_string(a.cash),// �����
	};
	for (int i = 0; i < size; i++)
		cout << "|" << setw(col[i]) << text[i] << setw(COL[i] - col[i]);
	cout << "|" << endl;
	cout << " -----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	return out;
}


// ������������� �������� �����
istream& operator>>(istream & in, Film& a) {
	string ns = "", ps = "", ss = "";
	int ni = 0, pi = 0, si = 0, hour = 0, min = 0, mins = 0;
	
	cout << "������� �������� ������: "<< endl;
	Enter_check(ns);
	cout << "������� ����������� ��������(0 - 100):" << endl;
	Enter_check(ni);
	cout << "������� ��� �������� ������:" << endl;
	Enter_check(ps);
	cout << "������� ����������� ��������(0 - 100):" << endl;
	Enter_check(pi);
	cout << "������� ��� ������ ������:" << endl;
	Enter_check(ss);
	cout << "������� ����������� ������(0 - 100):" << endl;
	Enter_check(si);
	cout << "������� ������� ������� ������ ����� ��� �����( 1 - 3 ): " << endl;
	Enter_check(hour, 3, 1);
	cout << "� ���������� �����";
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
		cout << "������� ������������ ������������ ������: 3 ����";
		break;
	}
	mins = hour * 60 + min;
	cout << "������������ � ������� ������������� ��� [hours] * 60 + min: " << mins << endl;


	// ������������� �����
	a.name(ns, ni); a.producer(ps, pi); a.studio(ss, si); 
	a.dur.tm_hour = hour;
	a.dur.tm_min = min;
    // �������� ����������� �����
	a(a.name,a.producer, a.studio, a.dur);
	return in;
}
// ����� ����
void Film::MENU()
{
	int size = 10;
	auto* menu = new string[size]{
		"����",
		"1 - ���������� ���������",
		"2 - �������� ���������",
        "3 - �������������� ���������", 
		"4 - ������ ���������",
		"5 - ������ ��������� � ����",
		"6 - ������ ���������",
		"7 - ������������� ��������",
		"8 - � ���������",
		"9 - �����"
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
			system("mode con cols=80 lines=20");//������� �������� ���� �������	
		
	}
	delete[] menu;
}

// ������ ������ � ����
void Film::menu_write()
{
	if (Film::flm_count<1) {
		cout << "������� ����������! ��� �������" << endl;
		return;
	}
	int s = 3;
	string q = "";
	int s2 = flm_count;
	bool norm_enter = false;
	auto* menu = new string[s]{ "�������� ���� �������� ���������� " ,
		"1 - �� ���������, ������������� ������� � \"data.txt\"",
		"2 - ���� ������� ���� ��� ������"
	};
	Film::buf = Film::head;
	string str = "������� ���� ��� ������\n(�� �������� ��� ���������� :) ): ";
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
// ������ ������ ������ � ����
void Film::write(Film & a, const string & b)
{
	const int size = 7;
	// ������� �������
	int COL[]{ 4, 39, 22, 29, 17, 16, 11 };	// ������� �������

	int txt[size]{
		to_string(a.index_numb).length(),// �����
		(a.name.GETstr()).length(),// ��������	
		(a.producer.GETstr()).length(),// �������		
		(a.studio.GETstr()).length(),// ������				
		4,// �����(�:�)
		to_string(a.mins).length(),// ����� (�)
		to_string(a.cash).length(),// ����� 
	};
	// ������ ����� ��� ������ �������
	int col[size]{};
	int i = 0;
	for (int &var : col)
	{
		var = a.col_count(txt[i], COL[i]);
		i++;
	}
	// ������������ ������ �����
	string buf1 = "", str = a.dur.tm_min<10 ? "0" : "";

	buf1 += to_string(a.dur.tm_hour) + ":" + str + to_string(a.dur.tm_min);

	string text[size]{
		to_string(a.index_numb),// �����
		(a.name.GETstr()),// ��������	
		(a.producer.GETstr()),// �������		
		(a.studio.GETstr()),// ������				
		buf1,// �����(�:�)
		to_string(a.mins),// ����� (�)
		to_string(a.cash),// �����
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
// ������ �����
void Film::write(const string & b, const int & Case)
{
	ifstream CIN;
	ofstream COUT;
	COUT.open(b, ios::app | ios::out);
	switch (Case) {
	case 1:
		COUT << " _________________________________________________________________________________________________________________________________________" << endl;
		COUT << "/ # |               ��������               |       �������      |           ������           |    �����(�:�)  |    ����� (�)  |   �����  \\" << endl;
		COUT << " -----------------------------------------------------------------------------------------------------------------------------------------" << endl;
		break;
	case 2:
		COUT << "����� ������� ����� �� ��� ������: " << Film::total_cash << "\n";
		break;
	}
	COUT.close();
}
// ����������
void Film::sort()
{

   if (Film::flm_count<1) {
	   cout << "������� ����������! ��� �������" << endl;
	   return;
   }

   system("cls"); int lines = 7 + Film::flm_count * 3;
   string mode = "mode con cols=146 lines=" + to_string(lines);
   system(mode.c_str());//������� �������� ���� �������

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
   Film::shapka();// �������� ��������� ��������
   for (int i = 0; i < Film::flm_count; i++)
   {
        cout << buf->ret_el(ind[i]);
   }
   delete[] ind;   
}

void Film::menu_filtr()
{
	if (Film::flm_count<1) {
		cout << "������� ����������! ��� �������" << endl;
		return;
	}
	int size = 9;
	string* menu = new string[size]{
		"�������� ������: \n\t\t\t\
          P.S: ��� ��������� ������ �����������\n\t\t\t \
          �� �� ������������ ������������\n\t\t\t \
          (������������ �������� � ��������� ������ ������ �������)",
		"1 - �� �������",
		"2 - �� ����� ������",
		"3 - �� ���������",
		"4 - �� ������",
		"5 - �� ������������",
		"6 - �� ���������� �����",
		"7 - �� ������",
		"8 - �����"
	};
    int lines = 7 + Film::flm_count * 3;
	string mode = "mode con cols=146 lines=" + to_string(lines);
	system(mode.c_str());//������� �������� ���� �������
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
		"�������� ��� �����������(�������� � ��������� ������� ���������)",
		"1- ������ ���������� ������",
		"2- ������ ���������� ������"
	};
	cout << "������� �����: ";
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
		"�������� ��� �����������(�������� � ��������� ������ ���������)\n\
		����� ������ � ����� ����, �������� ��� ������",
		"1- ������ ��������� �����",
		"2- ������ ��������� �����" 
	};
	cout << "������� ����� ����: ";
	Enter_check(a);
	// ����� �������� � ��� ������������, ���� �� ���� ���������� ���������
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
		"�������� ��� �����������(�������� � ��������� ������ ���������)\n\
		����� ������ � ����� ����, �������� ��� ������",
		"1- ������ ��������� �����",
		"2- ������ ��������� �����"
	};
	cout << "������� ����� ����: ";
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
		"�������� ��� �����������(�������� � ��������� ������ ���������)\n\
		����� ������ � ����� ����, �������� ��� ������",
		"1- ������ ��������� �����",
		"2- ������ ��������� �����"
	};
	cout << "������� ����� ����: ";
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
		"�������� ��� �����������(�������� � ���������� ������� ���������)",
		"1- ������ ��������� �����",
		"2- ������ ��������� �����"
	};
	cout << "�������  ���������� �����: ";
	Enter_check(h,3,1);
	cout << "�������  ���������� �����: ";
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
		"�������� ��� �����������(�������� � ���������� ������� ���������)",
		"1- ������ ��������� �����",
		"2- ������ ��������� �����"
	};
	cout << "������� ����� ����: ";
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
		"�������� ��� �����������(�������� � ���������� ������� ���������)",
		"1- ������ ��������� �����",
		"2- ������ ��������� �����"
	};
	cout << "������� �����(10000 - 3000000): ";
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

	// �������� ����������� �����
	
	system("mode con cols=105 lines=15");//������� �������� ���� �������
	if (Film::flm_count<1) {
		cout << "������� ����������! ��� �������" << endl;
		return;
	}
	int in = 0;
	bool enter_ok = false;
	string * red = new string[4]{
		"��������� ������� ���, ������� �������������� � ��������������?",
		"1- ��",
		"2- ���",
		"3- �����"
	};
	while (!enter_ok)
	{
		system("cls");
		string mode = "mode con cols=146 lines=14";
		system(mode.c_str());
		cout << "������� ����� ������, ������� ����� ���������������: ";
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
		"�������� ���� ��� ��������������:",
		"1 - ��� ������",
		"2 - ��� ���������",
		"3 - ��� ������",
		"4 - ������������",
		"5 - �����"
	};

	switch (Menu_show(menu, 6)) {
	case 1:
		cout << "������� �������� ������: " << endl;
		Enter_check(str1);
		cout << "������� ����������� ��������(0 - 100): " << endl;
		Enter_check(val1);
		buf->name(str1, val1);
		break;
	case 2:
		cout << "������� ��� �������� ������: " << endl;
		Enter_check(str1);
		cout << "������� ����������� ��������(0 - 100): " << endl;
		Enter_check(val1);
		buf->producer(str1, val1);
		break;
	case 3:
		cout << "������� ��� ������ ������: " << endl;
		Enter_check(str1);
		cout << "������� ����������� ������(0 - 100): " << endl;
		Enter_check(val1);
		buf->studio(str1, val1);
		break;

	case 4:
		cout << "������� ������� ������� ������ ����� ��� �����( 1 - 3 ): " << endl;
		Enter_check(val1, 3, 1);		
		switch (val1)
		{
		case 1:
			cout << "� ���������� �����"<< "(30 - 59): ";
			cout << ":" << endl;
			Enter_check(val2, 59, 30);
			break;
		case 2:
			cout << "� ���������� �����" << "(0 - 59): ";
			cout << ":" << endl;
			Enter_check(val2, 59);
			break;
		case 3:
			cout << "������� ������������ ������������ ������: 3 ����"<< endl;
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

