#include "match_cl.h"

// �������������� ����������� ����������
int Match::ALL_COUNTS= 0;
// ���������� �����������
int Match::MATCH_COUNT = 0;
// ������ ������
Match* Match::head = NULL;
// ����� ������
Match* Match::tail = NULL;
// �������� ���������
Match* Match::buf = NULL;
// ��������� �����
void gen_min(vector<int>& a,const int & min, const int & max)
{
	int min0 = min;
	
	for (int i = 0; i < a.size(); i++)
	{
		// ���� �������� �� ��� ��� ���� ��������,\
					 ������� ������������ ��������, �� ����� ������ \
			��� 90, ���� ��� �� ��������� �������, ������ \
            �������� ����������� � ������ ���������, ��� ���\
            ������ ��������� �������� ������ ���� ������ �����������
		bool exit = false;
		while (!exit) {
			a[i] = rand() % (max - min0 + 1) + min0;
			if ((i< a.size() - 1 && a[i] != max) || (i == a.size() - 1))
				exit = true;			
		}		 
		min0 = a[i];
	}
}
// ������ ��������� ��� �������
void Match::shapka()
{
	cout << " ___________________________________________________________________________________________________" << endl;
	cout << "/ # |            �������             |  ����  |  ������   |           ����������           |  ����  \\" << endl;
	cout << " ---------------------------------------------------------------------------------------------------" << endl;

}
// ����� ��� ������ ���� �� �����
void Match::match_setter()
{
	ifstream CIN;
	ofstream COUT;
	string path1 = "names.txt";
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
		}

		// �������� ������ ��� ������ ��������
		int b = rand() % size;
		// ������������� � ���� ������ ������ ��� ����� � ���� while(){}
		int c = b;
		// �������� �� ��� ��� ���� ������ ����� �������(�� ���� ������� �� ���� ����� ������)
		while (b == c) 
			c = rand() % size;
		// ������������ �����
		this->team1 = a[b];
		this->team2 = a[c];		
		// ����������� ������
		delete[] a;
	}
	CIN.close();
}
// ��������������� ����� ��� ������� ������ setw()
int Match:: col_count(const int & a, const int & b)
{
	// a - ������ ������, � - ������ �������
	int c = a + (b - a) / 2;
	return c;
}
// ���������� ��������� () � �������� ����������� �����
void Match::operator()(vector<int> a, vector<int> b, const string & team1_name, const string & team2_name)
{
	this->team1 = team1_name;
	this->team2 = team2_name;
	this->team1_count = a.size();
	this->team2_count = b.size();
	// �������� ����� ���������� �����
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
// ����� ������� ���������� ������� �� �������
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
// ���������� ��������� =
Match & Match::operator=(const Match & other)
{
	// TODO: insert return statement here
	this->operator()(other.team1_minutes, other.team2_minutes, other.team1, other.team2);
	return *this;
}
// ���� ��� ���������� �����������(� �����)
void Match::menu_add()
{
	// ������� ������� ������� ����
	int s = 3;
	int q = 0;
	// ���������� ��� �������� ������������ �����
	bool norm_enter = false;
	auto* menu = new string[s]{ "�������� ���������� ���������� ���������: " ,
		"1 - �� ���������, \n������������� ����������� 20 ����������",
		"2 - ���� �������, \n��� ����������, ��� ���������� ������, �� �� ������ �����������"
	};
	auto* menu2 = new string[s]{ "�������� ��� ������ ������ �������: " ,
		"1 - ���������� ����������� ���������",
		"2 - �������� ���� ������� � ������ \n��� ��� ���������"
	};
	string str = "������� ���������� ���������: ";
	// ������������ � �����
	Match::buf = tail;
	// ����_��� ��������� �������� �� 1 �� "������"
	switch (Menu_show(menu, s)) {
	case 1:
		system("cls");
		// �� ��������� ��������� 20 ���������
		for (int i = 0; i < 20; i++)			
			buf = buf->add_match();			
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

			// ��������� q ���������
			for (int i = 0; i < q; i++)
				buf = buf->add_match();
			break;
		case 2:
			// ������ ������ � ���� �� ����������� ���������
			system("cls");
			buf->add_match(2);
			break;
		}
		break;
	}
	delete[] menu;
	delete[] menu2;
}
// ����� ���������� ������ ����
Match * Match::add()
{
	buf = new Match; // ��������� ������ ��� ��������� ������� 
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
Match* Match::add_match(const int & Case)
{
	int i1 = rand() % 4;
	int i2 = rand() % 4;

	this->add();
	switch (Case) {
	    case 1:
			// ����������� ������ ����� �� ��������� ���������� ���� �� 0 �� 3
			Match::tail->team1_minutes.resize(i1);
			// ����������� ������ ����� �� ��������� ���������� ���� �� 0 �� 3
			Match::tail->team2_minutes.resize(i2);
			// ���������� ������
			gen_min(Match::tail->team1_minutes);
			// ���������� ������
			gen_min(Match::tail->team2_minutes);
			
			Match::tail->operator()(Match::tail->team1_minutes, Match::tail->team2_minutes);
			// ��������� � ����������� ����� �������
			Match::tail->match_setter();
			
			break;
		case 2:
			// � ���������� ������������� ��������� ��������� ������
			cin >> *tail;
			break;	
		default:
			cout << "������������ �����" << endl;
			system("pause");
	}

	tail->operator()(tail->team1_minutes, tail->team2_minutes, tail->team1, tail->team2);
	ALL_COUNTS += tail->team1_count + tail->team2_count;
	return tail;

}
// ����� �������� ������(������� ��������� ������� �������)
void Match::menu_del()
{
	if (Match::MATCH_COUNT<1) {
		cout << "������� ����������! ��� ������" << endl;
		return;
	}
	int s = 3;
	int q = 0;
	int s2 = MATCH_COUNT;
	bool norm_enter = false;
	auto* menu = new string[s]{ "�������� ���������� ���������� ���������: " ,
		"1 - �� ���������, ������������� ������ ������",
		"2 - ���� ������� ���������� ��������� ���������"
	};
	Match::buf = Match::tail;
	string str = "������� ���������� ���������: ";
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
				cout << "������� ����� ������" << endl;
			}
		}

		for (int i = 0; i < q; i++) {
			buf = buf->del_match();
		}
		break;
	}
	delete[] menu;
}
// �������� ������ �����
Match* Match::del_match()
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
// ������ ������ � ����
void Match::menu_write()
{
	if (Match::MATCH_COUNT<1) {
		cout << "������� ����������! ��� ������" << endl;
		return;
	}
	int s = 3;
	string q = "";
	int s2 = MATCH_COUNT;
	bool norm_enter = false;
	auto* menu = new string[s]{ "�������� ���� �������� ���������� " ,
		"1 - �� ���������, ������������� ������� � \"data.txt\"",
		"2 - ���� ������� ���� ��� ������"
	};
	Match::buf = Match::head;
	string str = "������� ���� ��� ������\n(�� �������� ��� ���������� :) ): ";
	switch (Menu_show(menu, s)) {
	case 1:
		system("cls");
		write();
		for (int i = 0; i < MATCH_COUNT; i++) {
			write(*buf);
			if(buf!= tail)
			buf = buf->next;
		}
		write("data.txt", 2);
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
		write(q, 2);
		break;
	}
	delete[] menu;
}
// ������ ������ ����� � ����
void Match::write( Match & a, const string & b)
{
	// cout << "/ # |           �������            | ����  |  ������  |  ���������� | ����  \\" << endl;

	const int size = 12;
	// ������� �������
	int COL[]{ 4, 33, 9, 12, 33, 9 };
	// ������� �������

	string Nichja = "�����";
	int txt[size]{
		to_string(a.index_numb).length(),// �����
		(a.team1).length(),// ����� �������� 1		
		to_string(a.team1_count).length(),// ���� ������ ������� 		
		a.team1_count>0 ? 2 * a.team1_count + a.team1_count - 1 : 0,// ������		
		a.first_team_win ? (a.team1).length() : a.second_team_win ? (a.team2).length() : Nichja.length(), // ����������
		to_string(a.teams_count).length(),//���������� �����
		3,
		(a.team2).length(),// ����� �������� 2
		to_string(a.team2_count).length(),// ���� ������ �������
		a.team2_count > 0 ? 2 * a.team2_count + a.team2_count - 1 : 0, // ������
		14, // ����������
		8//���������� �����
	};
	// ������ ����� ��� ������ �������
	int col[size]{};
	int i = 0;
	for (int &var : col)
	{
		var = a.col_count(txt[i], COL[i % 6]);
		i++;
	}
	// ������������ ������ �����
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
		to_string(a.index_numb),// �����
		a.team1,// �������� 1
		to_string(a.team1_count),// ���� ������ ������� 
		buf1,  // ������
		a.first_team_win ? (a.team1) : a.second_team_win ? (a.team2) : Nichja, // ����������
		to_string(a.teams_count),//���������� �����
		"   ", // �����
		a.team2,// �������� 2
		to_string(a.team2_count),// ���� ������ �������
		buf2,  // ������
		"             ", // ����������
		"       "//���������� �����
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
// ������ �����
void Match::write(const string & b, const int & Case)
{
	ifstream CIN;
	ofstream COUT;
	COUT.open(b, ios::app | ios::out);
	switch(Case){
	case 1 :	
		COUT << " ___________________________________________________________________________________________________\n";
		COUT << "/ # |            �������             |  ����  |  ������   |           ����������           |  ����  \\\n";
		COUT << " ---------------------------------------------------------------------------------------------------\n";
		break;
	case 2:
		COUT << "����� ������ ����� �� ��� �����: "<< Match::ALL_COUNTS<< "\n";
		break;
	}
	COUT.close();
}
// ������
void Match::print()
{
	if (Match::MATCH_COUNT<1) {
		cout << "������� ����������! ��� ������" << endl;
		return;
	}
	bool fin = false;
	int c = 0, c2 = 0, f = 0;
	bool norm_enter = false;
	auto* menu = new string[3]{ "�������� ��� ������: ", "1 - �������",	"2 - �� ��������� ������" },
		*menu2 = new string[3]{ "�������� �������:","1 - ������","2 - ��������" };
	auto str = "������� ����� �����, ������� ���������� �������: ";
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
				cout << "������� ����� ������" << endl;
			}
		}
		c2 = 1;
		fin = true;
		break;
	}
	if (!fin) {
		system("cls"); int lines = 7 + Match::MATCH_COUNT * 3;
		string mode = "mode con cols=105 lines=" + to_string(lines);
		system(mode.c_str());//������� �������� ���� �������
		Match::shapka();// �������� ��������� ��������
		while (buf !=  NULL) {
			cout << *buf;
			buf = (c2 == 1 ? buf->next : buf->prev);
		}
		cout << endl << "����� ���������� ������: " << Match::MATCH_COUNT << endl;
		cout << endl << "����� ���������� �����: " << Match::ALL_COUNTS << endl;
	}
	else {
		system("cls"); int lines = 9;
		string mode = "mode con cols=105 lines=" + to_string(lines);
		system(mode.c_str());//������� �������� ���� �������
		Match::shapka();// �������� ��������� ��������
		cout << buf->ret_el(f);
	}
	
	delete[] menu;
	delete[] menu2;	
}
// ���� � ���������
void Match::info()
{
	cout << "����� ������\n���-329" << endl;
}
// ����������
void Match::sort()
{
	if (Match::MATCH_COUNT<1) {
		cout << "������� ����������! ��� ������" << endl;
		return;
	}
	int lines = 6 + Match::MATCH_COUNT * 3;
	string mode = "mode con cols=105 lines=" + to_string(lines);
	system(mode.c_str());//������� �������� ���� �������
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
// �������
void Match::menu_filtr()
{
	if (Match::MATCH_COUNT<1) {
		cout << "������� ����������! ��� ������" << endl;
		return;
	}
	int size = 5;
	string* menu = new string[size]{
		"�������� ������: ",
		"1 - �� �������",
		"2 - �� ���������� �����",
		"3 - �� �������",
		"4 - �� �����������",
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
	"�������� ��� �����������(�������� � ��������� ������� ���������)", 
	"1- ������ ���������� ������",
	"2- ������ ���������� ������"
	};
	cout << "������� �����: ";
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
		"�������� ��� �����������(�������� � ��������� ����������� ����� ���������)",
		"1- ������ ���������� ���������� �����",
		"2- ������ ���������� ���������� �����"
	};
	cout << "������� �����: ";
	Enter_check(a);
	if (a > 6) {
		cout << "������� ������� ������� �����" << endl;
		return;
	}
	else  if (a < 0) {
		cout << "������� ������� ��������� �����" << endl;
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
		"�������� ��� �����������:",
		"1- ������� ����� ��� ���� ������ � ������ �����",
		"2- ������� ����� ��� ���� ������ �� ������ �����"
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
					if (buf->team2_minutes[buf->team2_minutes.size() - 1] <= 45)
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
		"�������� ��� �����������:",
		"1- ������� ����� ��� ���������� 1-� �������",
		"2- ������� ����� ��� ���������� 2-� �������",
		"3- ������� ����� ��� ����� �� �������"
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
// ��������������
void Match::edit()
{
	system("mode con cols=105 lines=15");//������� �������� ���� �������
	if(Match::MATCH_COUNT<1) {
		cout << "������� ����������! ��� ������" << endl;
		return;
	}	
	int in = 0;
	bool enter_ok = false;
	string * red = new string[3]{
		"��������� ������� ���, ������� �������������� � ��������������?",
		"1- ��",
		"2- ���"
	};
	while (!enter_ok)
	{
		cout << "������� ����� �����, ������� ����� ���������������: ";
		Enter_check(in);		
		*buf = buf->ret_el(in);
		cout << *buf;
		system("pause");
		if (in >= 1 && in <= Match::MATCH_COUNT) {			
			switch (Menu_show(red, 3)) {
			case 1:
				enter_ok = true;
				break;
			}
		}
     }
	
	string * menu = new string[4]{
	"�������� ���� ��� ��������������:",
	"1- �������",
	"2- ����",
	"3- ������"
	};

	switch (Menu_show(menu, 4)) {
	case 1:  		
		buf->edit_teams();
		break;
	case 2: 
		buf->edit_goals();
		break;
	case 3: 
		buf->edit_mins();
		break;
	
	}
	cout << *buf;
	delete[] menu;
	delete[] red;
}
void Match::edit_teams()
{
	string team_name;
	string * menu_1 = new string[3]{
		"�������� ������������� �������:",
		"1- 1-� �������",
		"2- 2-� �������"
	};
	switch (Menu_show(menu_1, 3)) {
	case 1:
		cout << "������� ��� ��� ������ �������: ";
		Enter_check(team_name);
		this->operator()(this->team1_minutes, this->team2_minutes, team_name, this->team2);
		break;
	case 2:
		cout << "������� ��� ��� ������ �������: ";
		Enter_check(team_name);
		this->operator()(this->team1_minutes, this->team2_minutes, this->team1, team_name);
		break;
	}
	delete[] menu_1;
}
void Match::edit_goals() {
	int b = -1, min = 0,  max = 90;
	string * menu_1 = new string[3]{
		"�������� ������������� �������:",
		"1- 1-� �������",
		"2- 2-� �������"
	};
	switch (Menu_show(menu_1, 3)) {
	case 1:
		cout << "������� ���������� ����� ��� ������ �������: ";

		while (b < 0 || b>4)
		{
			Enter_check(b);
			if (b < 0 || b>4)
				cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
		}
		this->team1_minutes.resize(b);
		cout << "������� " << b << " ������ ��� ������ ��������: ";
		for (int &var : this->team1_minutes)
		{
			var = -1;
			while (var < min || var > max) {
				Enter_check(var);
				min = var;
				if (var < min || var > max)
					cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
			}

		}
		this->operator()(this->team1_minutes, this->team2_minutes, this->team1, this->team2);

		break;
	case 2:
		cout << "������� ���������� ����� ��� ������ �������: ";

		while (b < 0 || b>4)
		{
			Enter_check(b);
			if (b < 0 || b>4)
				cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
		}
		this->team2_minutes.resize(b);
		cout << "������� " << b << " ������ ��� ������ ��������: ";
		for (int &var : this->team2_minutes)
		{
			var = -1;
			while (var < min || var > max) {
				Enter_check(var);
				min = var;
				if (var < min || var > max)
					cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
			}

		}
		this->operator()(this->team1_minutes, this->team2_minutes, this->team1, this->team2);
		break;
	}
	delete[] menu_1;
}
void Match::edit_mins() {
	int b = -1, min = 0, max = 90;
	string * menu_1 = new string[3]{
		"�������� ������������� �������:",
		"1- 1-� �������",
		"2- 2-� �������"
	};
	switch (Menu_show(menu_1, 3)) {
	case 1:
		cout << "������� " << this->team1_minutes.size() << " ������ ��� ������ ��������: ";
		for (int &var : this->team1_minutes)
		{
			var = -1;
			while (var < min || var > max) {
				Enter_check(var);
				min = var;
				if (var < min || var > max)
					cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
			}

		}
		
		break;
	case 2:
		cout << "������� " << this->team2_minutes.size() << " ������ ��� ������ ��������: ";
		for (int &var : this->team2_minutes)
		{
			var = -1;
			while (var < min || var > max) {
				Enter_check(var);
				min = var;
				if (var < min || var > max)
					cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
			}

		}
	
		break;
	}
	this->operator()(this->team1_minutes, this->team2_minutes, this->team1, this->team2);
	delete[] menu_1;
}
// �������� ���� �����
void Match::recalc_ALL_COUNTS()
{
	ALL_COUNTS = 0;
	buf = head;
	while (buf!=NULL) {
		ALL_COUNTS += buf->teams_count;
		buf = buf->next;
	}
}
// ������������� �������� ������
ostream & operator<< (ostream& out, Match& a) {

	// cout << "/ # |           �������            | ����  |  ������  |  ���������� | ����  \\" << endl;

	const int size = 12;
	// ������� �������
	int COL[]{ 4, 33, 9, 12, 33, 9 };
	// ������� �������

	string Nichja = "�����";
	int txt[size]{
		to_string(a.index_numb).length(),// �����
		(a.team1).length(),// ����� �������� 1		
		to_string(a.team1_count).length(),// ���� ������ ������� 		
		a.team1_count>0 ?2 * a.team1_count + a.team1_count - 1 : 0,// ������		
		a.first_team_win ? (a.team1).length() : a.second_team_win? (a.team2).length(): Nichja.length(), // ����������
		to_string(a.teams_count).length(),//���������� �����
		3,
		(a.team2).length(),// ����� �������� 2
		to_string(a.team2_count).length(),// ���� ������ �������
		a.team2_count > 0? 2 * a.team2_count + a.team2_count - 1: 0, // ������
		14, // ����������
		8//���������� �����
	};
	// ������ ����� ��� ������ �������
	int col[size]{};
	int i = 0;
	for (int &var :  col)
	{
		var = a.col_count(txt[i], COL[i%6]);
		i++;
	}
	// ������������ ������ �����
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
	to_string(a.index_numb),// �����
	a.team1,// �������� 1
	to_string(a.team1_count),// ���� ������ ������� 
	buf1,  // ������
		a.first_team_win ? (a.team1) : a.second_team_win ? (a.team2) : Nichja, // ����������
	to_string(a.teams_count),//���������� �����
	"   ", // �����
	a.team2,// �������� 2
	to_string(a.team2_count),// ���� ������ �������
	buf2,  // ������
	"             ", // ����������
	"       "//���������� �����
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
// ������������� �������� �����
istream& operator>>(istream & in, Match& a) {
	cout << "������� �������� �������:"<< endl;
	cout << "1-��: ";
	Enter_check(a.team1);
	cout << "2-��: ";
	Enter_check(a.team2);
	int a0 = -1, b0 = -1;
	cout << "������� ���������� ����� ��� ������ �������: ";

	while (a0 < 0 || a0>4)
	{
		Enter_check(a0);
		if (a0 < 0 || a0>4)
			cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
	}

	cout << "������� ���������� ����� ��� ������ �������: ";
	while (b0 < 0 || b0>4) {
		Enter_check(b0);
		if (b0 < 0 || b0>4)
			cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
	}	
	a.team1_count = a0;
	a.team2_count = b0;
	a.team1_minutes.resize(a0);
	a.team2_minutes.resize(b0);
	cout << "������� " << a.team1_minutes.size()<< " ������ ��� ������ ��������: ";
	int min = 0;
	int max = 90;
	for (int &var : a.team1_minutes)
	{ 
		var = -1;
		Enter_check(var);
		while (var < min ||var > max ) {
			if (var < min || var > max)
				cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
			Enter_check(var);
		}
		min = var;
		
	}
	cout << "������� " << a.team2_minutes.size() << " ������ ��� ������ ��������: ";
	min = 0;
	for (int &var : a.team2_minutes)
	{
		var = -1;
		while (var < min || var > max) {
			Enter_check(var);
			min = var;
			if (var < min || var > max)
				cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
		}
	}
	return in;
}
// ����� ����
void Match::MENU()
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
		"8 - � ���������(����)",
		"9 - �����"
	};
	for (;;) {
		int buf = Menu_show(menu, size);
		switch (buf) {
		case 1:	menu_add();	break;
		case 2:	menu_del();	break;
		case 3:	edit();	break;
		case 4:	print(); break;
		case 5: menu_write(); break;
		case 6:	menu_filtr(); break;
		case 7: sort();	break;
		case 8:	system("cls"); info();
			break;
		}
		if (buf == 9)break;
		else {
			recalc_ALL_COUNTS();
			system("pause");
			system("mode con cols=60 lines=15");//������� �������� ���� �������
		}
	}
	delete[] menu;
}
