#include "match_cl.h"
int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
 	SetConsoleOutputCP(1251);
	system("mode con cols=100 lines=30");//������� �������� ���� �������
	system("title Football Matches");//������� �������� ���� �������
	Match::MENU();
}