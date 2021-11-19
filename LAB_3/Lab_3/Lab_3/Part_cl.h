#pragma once
/*

   

*/
/*

if (cur == NULL|| head == NULL) { return NULL; } // В списке нет узлов
count--;
if (cur == head)	// Удаление корневого узла
{
head = cur->next;
buf = head;
if (head == NULL)tail = NULL;
}
else if (cur == tail) //
{
cur->prev->next = NULL;
tail = cur->prev;
buf = tail;
}
else {
if (cur->next != NULL) // Удаление промежуточного узла
{
cur->next->prev = cur->prev;
}
cur->prev->next = cur->next;
buf = cur->next;
}
delete[] cur->words;
delete cur;
return buf;

*/

#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;

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
int Enter_check(int & a, const int & max = 1000, const int & min = 0);
void С_gray(const string& a);
// функция которая показывает какую строку выбрали
void Choose(const string& a);
// фунция вывода любого меню(ЮИ)
int Menu_show(const string* arr, const int & size);

void add_l(string *&arr, int& size);
void read();
class part {
protected:
	part* next;
	part* prev;
	string company;
	short quantity;
	long long int yearSales;
	double marketPart;
public:
	part(const part & a) :part{ a.marketPart, a.quantity, a.yearSales }
	{
		this->company = a.company;
	}
	part(const string &c = "", const short & q = 0, const long long int &y = 0, const double &m = 0) :part{ m, q, y }
	{
		company = c;
	}
	part(const double &m, const short & q, const long long int &y) :part{ q, y }
	{
		marketPart = m;
	}
	part(const short & q, const long long int &y) :part{ y } {
		quantity = q;
	}
	part(const long long int &y) {
		yearSales = y;
	}
	part& operator()(part& other);
	// сеттеры
	void SetCompany(const string &c);
	void SetQuantity(const short & q);	void SetYearSales(const long  long int &y);
	void SetMarketPart(const double &m);
	// геттеры
	const string & GetCompany();
	const short & GetQuantity();
	const long long int & GetYearSales();
	const double & GetMarketPart();
	int col_count(const int& a, const int &b);
	// Потоковый вывод
	friend ostream& operator<< (ostream & out, part & a);
	friend ofstream& operator<< (ofstream & out, part & a);
	// Потоковый ввод
	friend istream& operator>> (istream & in, part & a);
	friend ifstream& operator>> (ifstream & in, part & a);
	// шапка таблицы
	void shapka();
	friend ofstream& shapkaF(ofstream &out);
	// проверка на соответствие
	bool operator==(part& other);
	friend class Parts;

};
class Parts {
	part* head;
	part* tail;
	part* buf;
	int size;
	bool equal(part*&a, const int s, const string & Fname = "data.txt");
	// изменение размера 
	void gener(part & a);
	part* add(part* cur);
	void clean(part *&a, int & b);
	// печать
	void print(part*& a, int & b);
	void printF(part*&a, int & b, const string & Fname = "data.txt");
	void printFL(part &a, int & c1, const string & Fname = "data.txt");
	// чтение
	void readFL(part *&a, const int & size, const int &c2, const string & Fname = "data.txt");
	void readF(part *&a, int & b, const string & Fname = "data.txt");
	// 
	void saved_check(part *&a, int & b, const string & Fname = "data.txt");
};