#include "match_cl.h"
int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
 	SetConsoleOutputCP(1251);
	system("title Football Matches");//������� �������� ���� �������
	system("mode con cols=78 lines=40");//������� �������� ���� �������
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//��������� ������
	CONSOLE_CURSOR_INFO cursor = { 100,false };//����� �� 1 �� 100 ������ ������� � ���������; false\true - ���������
	SetConsoleCursorInfo(hCons, &cursor);
	string back_txt = "color " + to_string(Magenta) + to_string(Black);
	system(back_txt.c_str());
	ball();
	this_thread::sleep_for(chrono::seconds(3));
	system("cls");
	system("mode con cols=60 lines=15");//������� �������� ���� �������	
	Match::MENU();
}