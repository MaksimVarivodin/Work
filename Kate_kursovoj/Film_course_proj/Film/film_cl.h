#pragma once
#include <iostream>
#include <iomanip>
#include <ctime> 
#include <string>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include <cassert>
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
void Choose(const string& a);
// ������ ������ ������ ����(��)
int Menu_show(const string* arr, const int & size);
// ����������� ����
void film();
// ������� ���������� ��������
template<typename T>
void Resize(T*& arr, int & size);
// ������� �� �������� �� ����
void Enter_check(int & a, const int & max = 100, const int & min = 0);
void Enter_check(string & a);

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

class Line {
	string str;// ����� ��������� ����
	int num; // ����� ��������� ����
public:
	
	Line lSearch(const string & a, const string &path1);
	// �����������
	Line(const string & a = "", const int& b = 0)
	{
		str = a;
		num = b;
	}
	// ������������� �������� () ��� �������������
	Line operator()(const string & a = "", const int& b = 0);
	Line operator= (const Line &other) {
		return this->operator()(other.str, other.num);
	}
	// ������������� �������� >
	bool operator>(const Line & other);
	bool operator<(const Line & other);
	// ������������� �������� ==
	bool operator==(const Line& other);
	bool operator>=(const Line & other);
	bool operator<=(const Line & other);
	// ������������� �������� ����� (��������� ���� �� �����)
	friend ifstream& operator>>(ifstream & in, Line& a);
	// �������
	string GETstr() { return str; }
	int GETnum() { return num; }
	// �������
	void SETstr(const string & a = "") { str = a; }
	void SETnum(const int & a = 0) { num = a; }
};

class Film
{
	static Film* head;
	static Film* tail;
	static Film* buf;
	Film* next;
	Film* prev;

	// ������������ ����:
	//______________________________________
	
	// ����� �� �������
	int index_numb;
	// ��������
	Line name; 
	// ��������
	Line producer;
	// ������
	Line studio;
	// ������������ (��������� ����� ����: ����� � �����)
	tm dur;
	// ������������ � �������
	int mins;
	// �������� �����
	int cash;
	static int total_cash;
	// ������� ���������� �����������
	static int flm_count;
	//_______________________________________
	

	// ����������� ������:
	// ______________________________________

	// �������:

	// ������ ���������� �����
	Film* add();
	static void menu_add();
	// ������� ������ �������� � ������ ��������
	static Film & ret_el(int ind);
	// ������ �������� �����
	Film* del();
	static void menu_del();
	friend void �_gray(const string& a);
	// ������� ������� ���������� ����� ������ �������
	friend void Choose(const string& a);
	// ������ ������ ������ ����(��)
	friend int Menu_show(const string* arr, const int & size);

	friend void Enter_check(int& , const int &, const int&);
	friend void Enter_check(string& a);

	// ������������� �������� () - ������������� 
	void operator()(const Line& n, const Line& p, const Line& s, const tm& d);
	Film& operator=(const Film& other);
	Line Line_setter(const string &path1);
	// ������ ��������� ������� ������
	Line SETname();
	Line SETprod();
	Line SETstud();
	tm SETdurt();
	Film* ADDfilm(const int& Case = 1);
	friend istream& operator>>(istream& in, Film & a);
	friend ostream& operator<< (ostream& out, Film & a);
	// ������ ������ ������ �� �����
	int col_count(const int & a, const int & b);
	static void shapka();
	static void print();
	static void info();

	static void recalc_total_cash();

	// ������ ������ ������ � ����
	static void menu_write();
	static void write(Film & a, const string & b = "data.txt");
	static void write(const string & b = "data.txt", const int & Case = 1);

	// �� �������:

	// ����� ����������
	static void sort();

	// ������ ����������
	static void menu_filtr();

	static void filtr_id();
	static void filtr_name();
	static void filtr_producer();
	static void filtr_studio();
	static void filtr_dur();
	static void filtr_mins();
	static void filtr_cash();
	
	
	// ��������������
	static void menu_edit();
public:	
	// (�����������)������������� ����������� ���������� ������, ���������� �������� �����������
	Film(const int &index) : index_numb{index} {
		// ����������� ����������� ����������
		flm_count++;
	};
	// (�����������)������������� ���� ���������� ������ �� ������������ ����������
	Film(const Line &n,const Line &p, const Line &s,const tm &d):Film {	flm_count + 1} 
	{
		// ����������� ������������ ���������
		name = n;
		producer = p;
		studio = s;
		dur = d;
	}

	// (����������� �� ���������) ������������ ����������� 
	Film() : Film{ Line{},Line{},Line{}, tm{} } {};

	// (����������)
	~Film() {
		// ��� ���������� ������ ���������� ��������� �������
		flm_count--;
	}
	static void MENU();
};