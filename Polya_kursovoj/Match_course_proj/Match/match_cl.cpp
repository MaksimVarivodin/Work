#include "match_cl.h"
// �������������� ����������� ����������
int Match::MATCH_COUNT = 0;
Match* Match::MATCH_POINTER = nullptr;
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
// ���������� ��������� =
Match & Match::operator=(const Match & other)
{
	// TODO: insert return statement here
	this->operator()(other.team1_minutes, other.team2_minutes, other.team1, other.team2);
	return *this;
}
// ����� ��������� ������� �������
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
		// �� �������� �� ����� �������� �������
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
// ����� ���������� ������ ����������(� �����)
void Match::add_match(const int & Case)
{
	int i1 = rand() % 4;
	int i2 = rand() % 4;
	Match::resize();
	switch (Case) {
	    case 1:
			// ����������� ������ ����� �� ��������� ���������� ���� �� 0 �� 3
			Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team1_minutes.resize(i1);
			// ����������� ������ ����� �� ��������� ���������� ���� �� 0 �� 3
			Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team2_minutes.resize(i2);
			// ���������� ������
			gen_min(Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team1_minutes);
			// ���������� ������
			gen_min(Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team2_minutes);
			
			Match::MATCH_POINTER[Match::MATCH_COUNT - 1](Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team1_minutes,
				Match::MATCH_POINTER[Match::MATCH_COUNT - 1].team2_minutes);
			// ��������� � ����������� ����� �������
			Match::MATCH_POINTER[Match::MATCH_COUNT - 1].match_setter();		
			
			break;
		case 2:
			// � ���������� ������������� ��������� ��������� ������
			cin >> Match::MATCH_POINTER[Match::MATCH_COUNT - 1];			
			break;	
		default:
			cout << "������������ �����" << endl;
			system("pause");
	}
	Match buf;
	buf = Match::MATCH_POINTER[Match::MATCH_COUNT - 2];
	Match::MATCH_POINTER[Match::MATCH_COUNT - 2] = buf;
}

void Match::menu_add()
{
	int q = 0;
	cout << "�������� ���������� ���������� ���������" << endl;
	cout << "1 - �� ���������" << endl;
	cout << "2 - ���� �������" << endl;
}

// ����� �������� ������(������� ��������� ������� �������)
void Match::del_match()
{
	Match::resize(Match::MATCH_COUNT - 1);
}
//  ������
void Match::print()
{
	int i = 0, c = 0, c2 = 0, f = 0;
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
				cout << "������� ����� ������" << endl;
			}
		}
		c2 = 1;
		i = 0;
		break;
	}
	system("cls");
	Match::shapka();// �������� ��������� ��������
	for (; c2 == 2 ? i > 0 : i < Match::MATCH_COUNT; c2 == 2 ? i-- : i++)
	{
		if ((MATCH_POINTER[i].index_numb == f && c == 2) || c == 1)
			cout << Match::MATCH_POINTER[i];
	}
	cout << endl << "����� ���������� ������: " << Match::MATCH_COUNT << endl;
	delete[] menu;
	delete[] menu2;
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

	while (a0 < 0 || a0>3)
	{
		Enter_check(a0);
		cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
	}

	cout << "������� ���������� ����� ��� ������ �������: ";
	while (b0 < 0 || b0>3) {
		Enter_check(b0);
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
		while (var < min ||var > max ) {
			Enter_check(var);
			min = var;
			if (var < min || var > max)
				cout << "��������� ����, �������� �� ������������ ����������� � ����" << endl;
		}
		
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
