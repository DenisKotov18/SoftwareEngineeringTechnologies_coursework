#include "Magic.h"

using namespace std;

void authorization();// меню авторизации

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUSSIAN");
	SetConsoleCP(1251);
	authorization();
}

void authorization()
{
	User* users = NULL; // ћассив пользователей

	int users_count = 0; //  ол-во пользователей
	bool program_end = false; // флаг выхода из цикла меню авторизации и завершени€ программы
	readUserFile(users, users_count); // запись информации о пользовател€х в массив
	if (users_count != 0) //проверка на пустой массив
	{
		while (program_end == false)
		{
			switch (menu(AUTHORIZATION_HEAD, AUTHORIZATION_MENU)) // переход в функцию меню и выбор варианта там
			{
			case 0: newUser(users, users_count); break; //переход в меню регистрации
			case 1: logon(users, users_count); break; //переход в меню ввода парол€ и логина
			case 2: program_end = true; break; //завершение работы
			default:
				break;
			}
		}
		delete[]users; // удаление массива пользователей
	}
}
