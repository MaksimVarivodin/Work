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
// изображение мяча
void film();
// функция расширения массивов
template<typename T>
void Resize(T*& arr, int & size);
// корявая но проверка на ввод
void Enter_check(int & a, const int & max = 100, const int & min = 0);
void Enter_check(string & a);

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

class Line {
	string str;// любая строковая инфа
	int num; // любая численная инфа
public:
	
	Line lSearch(const string & a, const string &path1);
	// конструктор
	Line(const string & a = "", const int& b = 0)
	{
		str = a;
		num = b;
	}
	// перегруженный оператор () для инициализации
	Line operator()(const string & a = "", const int& b = 0);
	Line operator= (const Line &other) {
		return this->operator()(other.str, other.num);
	}
	// перегруженный оператор >
	bool operator>(const Line & other);
	bool operator<(const Line & other);
	// перегруженный оператор ==
	bool operator==(const Line& other);
	bool operator>=(const Line & other);
	bool operator<=(const Line & other);
	// перегруженный оператор ввода (получение инфы из файла)
	friend ifstream& operator>>(ifstream & in, Line& a);
	// геттеры
	string GETstr() { return str; }
	int GETnum() { return num; }
	// сеттеры
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

	// ОБЯЗАТЕЛЬНЫЕ ПОЛЯ:
	//______________________________________
	
	// номер по порядку
	int index_numb;
	// название
	Line name; 
	// режиссер
	Line producer;
	// студия
	Line studio;
	// длительность (структура имеет поля: часов и минут)
	tm dur;
	// длительность в минутах
	int mins;
	// кассовые сборы
	int cash;
	static int total_cash;
	// счетчик количества экземпляров
	static int flm_count;
	//_______________________________________
	

	// ВОЗМОЖНОСТИ КЛАССА:
	// ______________________________________

	// готовые:

	// методы добавления узлов
	Film* add();
	static void menu_add();
	// фукнция поиска элемента с нужным индексом
	static Film & ret_el(int ind);
	// методы удаления узлов
	Film* del();
	static void menu_del();
	friend void С_gray(const string& a);
	// функция которая показывает какую строку выбрали
	friend void Choose(const string& a);
	// фунция вывода любого меню(ЮИ)
	friend int Menu_show(const string* arr, const int & size);

	friend void Enter_check(int& , const int &, const int&);
	friend void Enter_check(string& a);

	// перегруженный оператор () - инициализатор 
	void operator()(const Line& n, const Line& p, const Line& s, const tm& d);
	Film& operator=(const Film& other);
	Line Line_setter(const string &path1);
	// методы изменения размера списка
	Line SETname();
	Line SETprod();
	Line SETstud();
	tm SETdurt();
	Film* ADDfilm(const int& Case = 1);
	friend istream& operator>>(istream& in, Film & a);
	friend ostream& operator<< (ostream& out, Film & a);
	// методы печати списка на экран
	int col_count(const int & a, const int & b);
	static void shapka();
	static void print();
	static void info();

	static void recalc_total_cash();

	// методы записи списка в файл
	static void menu_write();
	static void write(Film & a, const string & b = "data.txt");
	static void write(const string & b = "data.txt", const int & Case = 1);

	// не готовые:

	// метод сортировки
	static void sort();

	// методы фильтрации
	static void menu_filtr();

	static void filtr_id();
	static void filtr_name();
	static void filtr_producer();
	static void filtr_studio();
	static void filtr_dur();
	static void filtr_mins();
	static void filtr_cash();
	
	
	// редактирование
	static void menu_edit();
public:	
	// (конструктор)инициализация константной переменной класса, увеличение счетчика экземпляров
	Film(const int &index) : index_numb{index} {
		// увеличиваем статическую переменную
		flm_count++;
	};
	// (конструктор)инициализация всех переменных класса по передаваемым аргументам
	Film(const Line &n,const Line &p, const Line &s,const tm &d):Film {	flm_count + 1} 
	{
		// присваиваем передаваимые аргументы
		name = n;
		producer = p;
		studio = s;
		dur = d;
	}

	// (конструктор по умолчанию) делегирующий конструктор 
	Film() : Film{ Line{},Line{},Line{}, tm{} } {};

	// (деструктор)
	~Film() {
		// при разрушении одного экземпляра уменьшаем счетчик
		flm_count--;
	}
	static void MENU();
};