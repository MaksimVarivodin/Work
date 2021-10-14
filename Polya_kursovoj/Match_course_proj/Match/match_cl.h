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
   номера вставл€ютс€ в структуру управл€ющую цветами 
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

// функци€ окрашивающа€ принимаемую строку в серый
void —_gray(const string& a);
// функци€ котора€ показывает какую строку выбрали
void Choose(const string& a);
// фунци€ вывода любого меню(ё»)
int Menu_show(const string* arr, const int & size);

// функци€ расширени€ массивов
template<typename T>
void Resize(T*& arr, int & size);
// кор€ва€ но проверка на ввод
void Enter_check(int & a);
void Enter_check(string & a);
// генератор случайного количества минут
void gen_min(vector<int>& a, const int & min = 0, const int & max = 90);

// функци€ расширени€ массивов
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
	
	// ќЅя«ј“≈Ћ№Ќџ≈ ѕќЋя:
	//______________________________________
	// счетчик количества экземпл€ров
	static Match* MATCH_POINTER;
	static int MATCH_COUNT;
	// номер по пор€дку
	const int index_numb;
	// название комманды 1
	string team1;
	// название комманды 2
	string team2;
	// минуты в которые были забиты голы дл€ первой комманды
	vector<int> team1_minutes;
	// минуты в которые были забиты голы дл€ второй комманды
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
	

	// ¬ќ«ћќ∆Ќќ—“»  Ћј——ј:
	// ______________________________________

	// перегруженный оператор () - инициализатор 
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
	static void write( Match & a, const string & b = "data.txt");
	static void write( const string & b = "data.txt");
	static void menu_write();
	static void print();
	static void sort();
	static void menu_filtr();

	//
	static void filtr_id();
	static void filtr_team();
	static void filtr_goals();
	static void filtr_mins();
	static void filtr_win();


	// функци€ окрашивающа€ принимаемую строку в серый
	friend void —_gray(const string& a);
	// функци€ котора€ показывает какую строку выбрали
	friend void Choose(const string& a);
	// фунци€ вывода любого меню(ё»)
	friend int Menu_show(const string* arr, const int & size);
	friend void Enter_check(int& a);
	friend void Enter_check(string& a);
	friend void gen_min(vector<int>& a, const int & min, const int & max);
	friend istream& operator>>(istream& in, Match & a);	
	friend ostream& operator<< (ostream& out, Match & a);

public:

	
	// (конструктор)инициализаци€ константной переменной класса, увеличение счетчика экземпл€ров
	Match(const int &index) : index_numb{index} {
		// увеличиваем статическую переменную
		MATCH_COUNT++;
	};

	// (конструктор)инициализаци€ всех переменных класса по передаваемым аргментам
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
		// при разрушении одного экземпл€ра уменьшаем счетчик
		MATCH_COUNT--;
	}
	static void MENU();
};