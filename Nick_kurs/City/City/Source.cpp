#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <iomanip>

using namespace std;
string name_setter() {
	ifstream in_stream("city_name.txt");
	if (!in_stream.good())
	{
		cout << "Error opening file!" << endl;
	}

	vector<string> lines;
	while (!in_stream.eof())
	{
		string line;
		getline(in_stream, line);
		lines.push_back(line);
	}
	return lines[rand()%40];
}


class City
{

public:
	static int counter;
	static int residents_country_num;
private:
	int id;
	string name;
	int district_num;
	vector<int> residents_district_num;
	int residents_city_num = 0;
public:
	City() {
		counter++;
		id = counter;
		name = name_setter();
		district_num = 3 + rand() % 5;
		residents_district_num.resize(district_num);
		for each (int var in residents_district_num)
		{
			var = rand() % 100 + 1;
			residents_city_num += var;
		}
	}
	City(string city_name,vector<int> a) {

		counter++;
		id = counter;

		name = city_name;

		district_num = a.size();
		residents_district_num.resize(district_num);
		int i = 0;
		for each (int var in residents_district_num)
		{
			var = a[i];
			residents_city_num += var;
			i++;
		}
	}




	void change() {
		int temp;
		int residents;
		cout << "�������� ����� ��� ������" << endl;
		cin >> temp;
		int keyn = 0;

		if (temp > district_num || temp < 1)
		{
				while ((temp > district_num || temp < 1))
				{
					cout << "������ ������ ����" << endl;
					cout << "�������� ����� ��� ������,��� ���" << endl;
					cin >> temp;
				}
		}
		
		cout << "�������� ���������� ������� � ������" << endl;
		cin >> residents;
		residents_city_num -= residents_district_num[temp - 1];
		residents_district_num[temp-1] = residents;
		residents_city_num += residents_district_num[temp - 1];

	}
	void print() {


		cout << "|" << setw(5) << id << "|" << setw(20) << name << "|" << setw(10) << district_num << "|" << setw(15) << residents_city_num << "|" << setw(8) << residents_district_num[0] << "|" << setw(8) << residents_district_num[1] << "|" << setw(8) << residents_district_num[2] << "|" << setw(8) << residents_district_num[3] << "|" << setw(8) << residents_district_num[4] << "|" << setw(8) << residents_district_num[5] << "|" << setw(8) << residents_district_num[6] << "|" << endl;


	}

	~City() {
		file.close();
		counter--;
		residents_country_num -= residents_city_num;
	}



};
int City :: counter = 0;
int City::residents_country_num = 0;

struct Node {

	City exmpl;

	Node* next;

	int size = 5;

	Node() {

		City exmpl;
		next = nullptr;

	}
	Node(string name_city, int district_num,int * residents_district_num_handle):
		exmpl(name_city, district_num, residents_district_num_handle)
	{		
		next = nullptr;

	}
	// �����������

};

struct list {

	Node* first; // ��������� �� ������ ����

	Node* last; // ��������� �� ��������� ����

	list() {

		first = nullptr;

		last = nullptr;

	} // �����������

	bool is_empty() {

		return first == nullptr;

	}

	void push_back() {

		Node* p = new Node();

		if (is_empty()) {

			first = p;

			last = p;

			return;

		}

		last->next = p;

		last = p;

		size++;

	}

	void push_back_own(string name_city, int district_num, int* residents_district_num_handle) {

		Node* p = new Node(name_city, district_num, residents_district_num_handle);

		if (is_empty()) {

			first = p;

			last = p;

			return;

		}

		last->next = p;

		last = p;

		size++;

	}

	void print() {

		if (is_empty()) return;

		Node* p = first;

		while (p) {

			p->exmpl.print();

			cout << endl;

			p = p->next;

		}

		cout << endl;

	}



	void remove_first() {

		if (is_empty()) return;

		Node* p = first;

		first = p->next;

		delete p;

		size--;

	}

	void remove_last() {

		if (is_empty()) return;

		if (first == last) {

			remove_first();

			return;

		}

		Node* p = first;

		while (p->next != last) p = p->next;

		p->next = nullptr;

		delete last;

		last = p;

		size--;

	}

	void del(int n) // n - ������� ���������� ��������

	{

		// Mass - �������, ������� �������� � ������

		Node* temp = first, * helping = first;
		if (temp == NULL)
		{
			cout << "������ ���� ����" << endl;
			cout << "������� ���� ��� ����, ����� �����"<< endl;
			return;
		}
		for (int i = 0; i < n; i++)

		{

				helping = temp; // ���������� �������� temp

				temp = temp->next;




		}

		if (temp == first) // ���� ������� ������� ���� ������� ������

		{

			first = temp->next;
			cout << "���� ��� ������" << endl;

			cout << "������� ���� ��� ����, ����� �����" << endl;

		}

		else

		{

			helping->next = temp->next;
			cout << "���� ��� ������" << endl;

			cout << "������� ���� ��� ����, ����� �����" << endl;

		}

		free(temp);

		size--;

		// ��������� ������ ������

	}



	int size = 0;

};



int main()
{
	//srand(time(0));
	//setlocale(LC_ALL, "Russian");


	//int flag = false;
	//string mas1[8] = { "���������� ���������(20 ����)","�������� ������������ ���������� ���������","�������� ����� �������","������� ���������� �������","�� ������", "������� ��� ����������","������� ������� �� ������","�����"};
	//char symbol = NULL;
	//int key = 0;
	//int first = 0;
	//list l;
	//while (true) {
	//	if (first == 0)
	//	{
	//		for (size_t i = 0; i < 8; i++)
	//		{
	//			if (i == 0)
	//			{
	//				cout << "-->" << mas1[i] << endl;
	//			}
	//			else
	//			{
	//				cout << mas1[i] << endl;
	//			}
	//		}
	//		first = 55;

	//	}
	//
	//	symbol = _getch();
	//	if (key!=0)
	//	{
	//		if (symbol == 72)
	//		{
	//			system("cls");
	//			key--;
	//			for (size_t i = 0; i < 8; i++)
	//			{
	//				if (key == i)
	//				{
	//					cout << "-->" << mas1[i] << endl;
	//				}
	//				else
	//				{
	//					cout << mas1[i] << endl;
	//				}
	//			}

	//		}
	//	}
	//	if (key!=7)
	//	{
	//		if (symbol == 80)
	//		{
	//			system("cls");
	//			key++;
	//			for (size_t i = 0; i < 8; i++)
	//			{
	//				if (key == i)
	//				{
	//					cout << "-->" << mas1[i] << endl;
	//				}
	//				else
	//				{
	//					cout << mas1[i] << endl;
	//				}
	//			}
	//		}
	//	}
	//	if (symbol == 13)
	//	{
	//		switch (key)
	//		{
	//		case 0:
	//		{
	//			system("cls");
	//			for (int j = 0; j < 20; j++) {
	//				l.push_back();
	//			}
	//			cout << "��������������..."<<endl;
	//			cout << "����� ����� ������� ������� ����" << endl;
	//			
	//			break;
	//		}
	//		case 1:
	//		{
	//			system("cls");
	//			int temp;
	//			cout << "������ ���������� �����������:" << endl;
	//			cin >> temp;
	//			
	//			for (int j = 0; j < temp; j++)
	//				l.push_back();
	//			cout << "������� ������� ���� ������, ����� �����...." << endl;
	//			symbol = _getch();

	//				while ((symbol!= 80))
	//				{
	//					symbol = _getch();
	//				}
	//			break;
	//		}
	//		case 2:
	//		{
	//			system("cls");
	//			string name_city;
	//			int district_num;
	//			cout << "������� �������� ������" << endl;
	//			cin >> name_city;
	//			cout << "������� ���������� �������" << endl;
	//			cin >> district_num;
	//			int* residents_district_num = new int[7];
	//			for (size_t i = 0; i < district_num; i++)
	//			{
	//				int count;
	//				cout << "������� ���������� ������� � " << i + 1 << " ������" << endl;
	//				cin >> count;
	//				residents_district_num[i] = count;


	//			}
	//			l.push_back_own(name_city, district_num, residents_district_num);
	//			break;

	//		}
	//		case 3:
	//		{
	//			system("cls");
	//			//exmp3.change();
	//			//exmp3.print();
	//			break;
	//		
	//		}
	//		case 4:
	//		{
	//			system("cls");
	//			cout << "������ ������ ���-329" << endl << endl;
	//			cout << "������� ������� ����� ��� ���� ����� �����...." << endl;

	//			break;
	//
	//		}
	//		case 5: {
	//			system("cls");
	//			cout << "------------------------------------------------------------------------------------------------------------------------\n";
	//			cout << "|" << setw(5) << "Id" << "|" << setw(20) << "��������" << "|" << setw(10) << "�������" << "|" << setw(12) << "����� � ������:" << "|" << setw(8) << "�����1" << "|" << setw(8) << "�����2" << "|" << setw(8) << "�����3" << "|" << setw(8) << "�����4" << "|" << setw(8) << "�����5" << "|" << setw(8) << "�����6" << "|" << setw(8) << "�����7" << "|" << endl;
	//			cout << "------------------------------------------------------------------------------------------------------------------------\n";
	//			l.print();
	//			cout << "����� ����������� ������: " << City::counter << endl;
	//			cout << "���������� ������� �� ���� �������: " << City::residents_country_num << endl;
	//			cout << "������� ������� ����� ��� ���� ����� �����...." << endl;
	//			break;


	//		}
	//		case 6: {
	//			system("cls");
	//			int i;

	//			cout << "������� ����� ���� ������� ����� ������� : " << endl;

	//			cin >> i;

	//			i--;

	//			l.del(i);
	//			break;
	//		}
	//		case 7: {
	//			system("cls");
	//			exit(0);
	//			break;
	//		}
	//		default:
	//			break;
	//		}
	//	}
	//}



	//return 0;
	int* a = new int[4]{
	1, 2, 3, 4 };
	for each (int var in a)
	{
		cout << var << " ";
	}



}


