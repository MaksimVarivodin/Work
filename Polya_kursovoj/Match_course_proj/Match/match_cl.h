#pragma once
#include <iostream>
#include <iomanip>
#include <ctime> 
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <conio.h>
using namespace std;
// ����� �������, ������� ���������� ��� ����������� ������ � ��� ����, \
   ������ ����������� � ��������� ����������� ������� 
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

// ������� ������������ ����������� ������ � �����
void �_gray(const string& a);
// ������� ������� ���������� ����� ������ �������
void choose(const string& a);
// ������ ������ ������ ����(��)
int Menu_show(const string* arr, const int & size);

// ������� ���������� ��������
template<typename T>
void Resize(T*& arr, int & size);
// ������� �� �������� �� ����
void Enter_check(int & a);
void Enter_check(string & a);
// ��������� ���������� ���������� �����
void gen_min(vector<int>& a, const int & min = 0, const int & max = 90);

// ������� ���������� ��������
template<typename T>
void Resize(T*& arr, int & size) {
	T* n_arr = new T[size + 1];
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			n_arr[i] = arr[i];
		}
	}
	delete[]arr;
	arr = n_arr;
	size++;
	n_arr = nullptr;
}
class Match
{
	
	// ������������ ����:
	//______________________________________
	// ������� ���������� �����������
	static Match* MATCH_POINTER;
	static int MATCH_COUNT;
	// ����� �� �������
	const int index_numb;
	// �������� �������� 1
	string team1;
	// �������� �������� 2
	string team2;
	// ������ � ������� ���� ������ ���� ��� ������ ��������
	vector<int> team1_minutes;
	// ������ � ������� ���� ������ ���� ��� ������ ��������
	vector<int> team2_minutes;
	// ���������� ����� �������� 1
	int team1_count;
	// ���������� ����� �������� 2
	int team2_count;
	// ����������
	bool first_team_win;
	bool second_team_win;	
	// ����� ���������� �����
	int teams_count;
	//_______________________________________
	

	// ����������� ������:
	// ______________________________________

	// ������������� �������� () - ������������� 
	void operator()( vector<int >a , vector<int >b, const string& team1_name = "", const string &team2_name = "");
	
	static void resize(const int & a = Match::MATCH_COUNT+ 1);	
	void match_setter();
	int col_count(const int & a, const int & b);
	Match& operator=(const Match& other);
	static void shapka();
	static void add_match(const int& Case = 1);
	static void menu_add();	
	static void del_match();
	static void menu_del();
	static void print();
	// ������� ������������ ����������� ������ � �����
	friend void �_gray(const string& a);
	// ������� ������� ���������� ����� ������ �������
	friend void choose(const string& a);
	// ������ ������ ������ ����(��)
	friend int Menu_show(const string* arr, const int & size);
	friend void Enter_check(int& a);
	friend void Enter_check(string& a);
	friend void gen_min(vector<int>& a, const int & min, const int & max);
	friend istream& operator>>(istream& in, Match & a);
	friend ostream& operator<< (ostream& out, Match & a);
public:

	
	// (�����������)������������� ����������� ���������� ������, ���������� �������� �����������
	Match(const int &index) : index_numb{index} {
		// ����������� ����������� ����������
		MATCH_COUNT++;
	};

	// (�����������)������������� ���� ���������� ������ �� ������������ ���������
	Match
	(const int &team1, const int & team2, const string& team1_name, const string &team2_name):
		Match {	MATCH_COUNT + 1	} 
	{
		// ����������� ������������ ���������
		this->team1 = team1_name;
		this->team2 = team2_name;
		team1_count = team1;
		team2_count = team2;
	}

	// (����������� �� ���������) ������������ ����������� 
	Match() : Match{ 0, 0, "", "" } {};

	// (����������)
	~Match() {
		// ��� ���������� ������ ���������� ��������� �������
		MATCH_COUNT--;
	}

};