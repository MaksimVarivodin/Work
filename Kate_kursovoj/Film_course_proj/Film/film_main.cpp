#include "film_cl.h"
int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
 	SetConsoleOutputCP(1251);
	system("title Films");//������� �������� ���� �������
	system("mode con cols=115 lines=90");//������� �������� ���� �������
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//��������� ������
	CONSOLE_CURSOR_INFO cursor = { 100,false };//����� �� 1 �� 100 ������ ������� � ���������; false\true - ���������
	SetConsoleCursorInfo(hCons, &cursor);
	string back_txt = "color C" + to_string(Black);
	system(back_txt.c_str());
	film();
	this_thread::sleep_for(chrono::seconds(3));
	system("cls");
	system("mode con cols=80 lines=20");//������� �������� ���� �������	
	Film::MENU();
}