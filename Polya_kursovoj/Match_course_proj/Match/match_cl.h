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
// набор величин, которые необходимы при окрашивании текста и его фона, \
   номера вставляются в структуру управляющую цветами 
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

// функция окрашивающая принимаемую строку в серый
void С_gray(const string& a);
// функция которая показывает какую строку выбрали
void Choose(const string& a);
// фунция вывода любого меню(ЮИ)
int Menu_show(const string* arr, const int & size);

// функция расширения массивов
template<typename T>
void Resize(T*& arr, int & size);
// корявая но проверка на ввод
void Enter_check(int & a);
void Enter_check(string & a);
// генератор случайного количества минут
void gen_min(vector<int>& a, const int & min = 0, const int & max = 90);

// функция расширения массивов
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
	static Match* head;
	static Match* tail;
	static Match* buf;
	Match* next;
	Match* prev;

	// ОБЯЗАТЕЛЬНЫЕ ПОЛЯ:
	//______________________________________
	// счетчик количества экземпляров
	static int MATCH_COUNT;
	// номер по порядку
	int index_numb;
	// название комманды 1
	string team1;
	// название комманды 2
	string team2;
	// минуты в которые были забиты голы для первой комманды
	vector<int> team1_minutes;
	// минуты в которые были забиты голы для второй комманды
	vector<int> team2_minutes;
	// количество голов комманды 1
	int team1_count;
	// количество голов комманды 2
	int team2_count;
	// победитель
	bool first_team_win;
	bool second_team_win;	
	// общее количество голов
	int teams_count;
	//_______________________________________
	

	// ВОЗМОЖНОСТИ КЛАССА:
	// ______________________________________

	// перегруженный оператор () - инициализатор 
	void operator()( vector<int >a , vector<int >b, const string& team1_name = "", const string &team2_name = "");

	// фукнция поиска элемента с нужным индексом
	static Match & ret_el(int ind);
	// методы изменения размера списка
	void match_setter();
	Match& operator=(const Match& other);

	// методы добавления узлов
	Match* add();
	Match* add_match(const int& Case = 1);
	static void menu_add();

	// методы удаления узлов
    Match* del_match();
	static void menu_del();

	// методы печати списка на экран
	int col_count(const int & a, const int & b);
	static void shapka();
	static void print();
	static void info();

	// методы записи списка в файл
	static void menu_write();
	static void write( Match & a, const string & b = "data.txt");
	static void write( const string & b = "data.txt");

	// метод сортировки
	static void sort();

	// методы фильтрации
	static void menu_filtr();
	static void filtr_id();
	static void filtr_goals();
	static void filtr_mins();
	static void filtr_win();


	// функция окрашивающая принимаемую строку в серый
	friend void С_gray(const string& a);
	// функция которая показывает какую строку выбрали
	friend void Choose(const string& a);
	// фунция вывода любого меню(ЮИ)
	friend int Menu_show(const string* arr, const int & size);

	friend void Enter_check(int& a);
	friend void Enter_check(string& a);

	friend void gen_min(vector<int>& a, const int & min, const int & max);
	friend istream& operator>>(istream& in, Match & a);	
	friend ostream& operator<< (ostream& out, Match & a);

public:	
	// (конструктор)инициализация константной переменной класса, увеличение счетчика экземпляров
	Match(const int &index) : index_numb{index} {
		// увеличиваем статическую переменную
		MATCH_COUNT++;
	};
	// (конструктор)инициализация всех переменных класса по передаваемым аргументам
	Match
	(const int &team1, const int & team2, const string& team1_name, const string &team2_name):
		Match {	MATCH_COUNT + 1	} 
	{
		// присваиваем передаваимые аргументы
		this->team1 = team1_name;
		this->team2 = team2_name;
		team1_count = team1;
		team2_count = team2;
	}

	// (конструктор по умолчанию) делегирующий конструктор 
	Match() : Match{ 0, 0, "", "" } {};

	// (деструктор)
	~Match() {
		// при разрушении одного экземпляра уменьшаем счетчик
		MATCH_COUNT--;
	}
	static void MENU();
};