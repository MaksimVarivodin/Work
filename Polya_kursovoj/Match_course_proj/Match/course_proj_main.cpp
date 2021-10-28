#include "match_cl.h"
int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
 	SetConsoleOutputCP(1251);
	system("title Football Matches");//задание описания окна консоли
	system("mode con cols=78 lines=40");//задание размеров окна консоли
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//получение хендла
	CONSOLE_CURSOR_INFO cursor = { 100,false };//число от 1 до 100 размер курсора в процентах; false\true - видимость
	SetConsoleCursorInfo(hCons, &cursor);
	string back_txt = "color " + to_string(Magenta) + to_string(Black);
	system(back_txt.c_str());
	ball();
	this_thread::sleep_for(chrono::seconds(3));
	system("cls");
	system("mode con cols=60 lines=15");//задание размеров окна консоли	
	Match::MENU();
}