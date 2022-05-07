#include "Magic.h"

using namespace std;

void authorization();// ���� �����������

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUSSIAN");
	SetConsoleCP(1251);
	authorization();
}

void authorization()
{
	User* users = NULL; // ������ �������������

	int users_count = 0; // ���-�� �������������
	bool program_end = false; // ���� ������ �� ����� ���� ����������� � ���������� ���������
	readUserFile(users, users_count); // ������ ���������� � ������������� � ������
	if (users_count != 0) //�������� �� ������ ������
	{
		while (program_end == false)
		{
			switch (menu(AUTHORIZATION_HEAD, AUTHORIZATION_MENU)) // ������� � ������� ���� � ����� �������� ���
			{
			case 0: newUser(users, users_count); break; //������� � ���� �����������
			case 1: logon(users, users_count); break; //������� � ���� ����� ������ � ������
			case 2: program_end = true; break; //���������� ������
			default:
				break;
			}
		}
		delete[]users; // �������� ������� �������������
	}
}
