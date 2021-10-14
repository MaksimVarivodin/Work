#include "match_cl.h"
int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
 	SetConsoleOutputCP(1251);
	system("mode con cols=50 lines=10");//задание размеров окна консоли
	system("title Football Matches");//задание описания окна консоли
	Match::MENU();
}