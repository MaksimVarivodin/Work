#include "match_cl.h"
int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
 	SetConsoleOutputCP(1251);
	system("mode con cols=51 lines=14");//задание размеров окна консоли
	system("title Football Matches");//задание описания окна консоли
	int size = 5;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//получение хендла
	CONSOLE_CURSOR_INFO cursor = { 100,false };//число от 1 до 100 размер курсора в процентах; false\true - видимость
	SetConsoleCursorInfo(hCons, &cursor);

	string* menu = new string [size]{
	"Menu", "case1", "case2", "case3", "case4"
	};
	Menu_show(menu, size);
	system("pause");
	delete[] menu;
}