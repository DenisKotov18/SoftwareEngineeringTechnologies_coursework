#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <ctime>
#include "Constants.h"
#include "sha256.h"

#define UP 72
#define DOWN 80
#define LIMIT_LENGTH 32
using namespace std;

const vector<string> AUTHORIZATION_POINTS{ "Регистрация", "Вход", "Выход из системы" };
const vector<string> ADMIN_MENU_POINTS{ "Работа с данными пользователей", "Работа с ассортиментом магазина", "Выход" };
const vector<string> LOGON_POINTS{ "Ввести логин","Ввести пароль","Войти","Назад" };
const vector<string> NEW_USER_CONFIRM{ "Согласен","Отмена" };
const vector<string> DEL_CONFIRM{ "\033[32mНет\033[0m", "\033[1;31mДа\033[0m" };
const vector<string> USER_POINTS;
const vector<string> ADMIN_POINTS{ "Работа с данными пользователей", "Работа с ассортиментом магазина", "Выход" };
const vector<string> MAIN_ADMIN_POINTS{ "Работа с данными пользователей", "Работа с ассортиментом магазина", "Выход" };
const vector<string> GREETING{ "Здравствуйте\, ", "Приветствуем\, ", "Доброго здоровья\, ", "Мы ждали Вас\, ", "Рады приветствовать\, " };


void authorization();
void readUserFile(struct User *&, int&);
void addUserToFile(User&);
int menu(string, const vector<string>);
void logon(User*&, int&);
void logonInput(char[], const int&, const char[], bool);
bool logonTry(char[], char[], User*&, int&);
int compare(User*&, const int&, char[]);
bool compare(const char[], const char[]);
void createAdmin(User *&, int&);
void newUser(User*&, int&);
void memoryReallocation(User*&, User&, int&);
int getUsersCount();
char*& hashing(char[],const char[],const char[]);
void generateSalt(char* const&);
void inputWord(char*, const int&, bool);
char notTrashAssignment(char& not_trash);
void outputSymbol(char*, char, int&, int, bool);
void redirection(User*&, User&, int&);
void adminMenu(User*&, User&, int&);
void userMenu(User&);
void showUsers(User&, int&);

struct User
{
	int role; //1 - user , 2 - admin , 3 - main admin
	char login[LOGIN_LENGTH];
	char password[PASSWORD_LENGTH];
	char first_salt[SALT_LENGTH];
	char second_salt[SALT_LENGTH];
	bool account_freeze;
};
 
void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUSSIAN");
	SetConsoleCP(1251);
	/*cout << LIMIT;
	for (int i = 65; i < 122; i++) cout <<(char) i;
	while (true) {
		char trash = 27;
		char musor = _getch();
	}
	while (true) cout << _getch();*/
	authorization();
}

void authorization()
{
	User* users = NULL;
	int users_count = 0;
	bool program_end = false;
	readUserFile(users, users_count);
	while (program_end == false)
	{
		switch (menu(AUTHORIZATION_MENU, AUTHORIZATION_POINTS))
		{
		case 0: newUser(users, users_count); break;
		case 1: logon(users, users_count); break;
		case 2: program_end = true; break;
		default:
			break;
		}
	}
	cout << users[1].password;
	delete[]users;
}

void readUserFile(User*& users, int& users_count)
{
	ifstream fin(FILE_OF_USERS, ios::binary | ios::in);
	if (!fin.is_open()) createAdmin(users, users_count);
	else
	{
		users_count = getUsersCount();
		if (users_count != 0)
		{
			users = new User[users_count];
			fin.read((char*)&users[0], sizeof(User) * users_count);
		}
		else createAdmin(users, users_count);
	}
	fin.close();
}

int getUsersCount() 
{
	ifstream file(FILE_OF_USERS, ios::ate | ios::binary);
	const int users_count = file.tellg() / sizeof(User);
	file.close();
	return users_count;
}

void addUserToFile(User& user)
{
	ofstream fout(FILE_OF_USERS, ios::binary | ios::app);
	fout.write((char*)&user, sizeof(User));
	fout.close();
}

void createAdmin(User*& users, int& users_count)
{
	users = new User[1];
	users[0].role = 3;
	users[0].account_freeze = false;
	users[0].login[0] = users[0].password[0] = 'a';
	users[0].login[1] = users[0].password[1] = 'd';
	users[0].login[2] = users[0].password[2] = 'm';
	users[0].login[3] = users[0].password[3] = 'i';
	users[0].login[4] = users[0].password[4] = 'n';
	users[0].login[5] = users[0].password[5] = '\0';
	generateSalt(users[0].first_salt);
	generateSalt(users[0].second_salt);
	hashing(users[0].password, users[0].first_salt, users[0].second_salt);
	
	users_count++;
	addUserToFile(users[0]);
}

int menu(string head, const vector<string> menu_point)
{
	char exit_catcher = NULL,
		switcher = NULL;
	int choise = 0;
	const int points_amt = menu_point.size();

	while (true)
	{
		system("cls");
		cout << head << endl;
		for (int i = 0; i < points_amt; i++)
		{
			if (i == choise)
			{
				cout << '>' << "\033[32m" << menu_point.at(i) << "\033[0m" << '<' << endl;
				continue;
			}
			cout << " " << menu_point.at(i) << endl;
		}
		exit_catcher = NULL;
		while (exit_catcher != -32)
		{
			exit_catcher = _getch();
			if (exit_catcher == '\r' || switcher == '\r') return choise;
		}
		switcher = _getch();
		switch (switcher)
		{
		case UP:
		{
			if (choise == 0) choise = points_amt - 1;
			else choise--;
			break;
		}
		case DOWN:
		{
			choise = (++choise) % points_amt;
			break;
		}
		case '\r': return choise;
		default: break;
		}
	}
}

void newUser(User*& users, int& users_count)
{
	User new_user = { 3, '\0', '\0','\0','\0', false};

	system("cls");
	while ((new_user.login[0] == '\0' )|| (compare(users, users_count, new_user.login) != -1))
	{
		if (new_user.login[0] != '\0')
		{
			cout << '	' << INVALID_LOGIN << endl;
			system("pause");
			system("cls");
		}
		cout << NEW_USER_MENU << endl << ENTER_NEW_USER_LOGIN;
		inputWord(new_user.login, LOGIN_LENGTH, false);
	}
	cout << endl << ENTER_NEW_USER_PASSWORD;
	inputWord(new_user.password, PASSWORD_LENGTH, true);
	if (menu(NEW_USER_CONF_MENU, NEW_USER_CONFIRM) == 0)
	{
		generateSalt(new_user.first_salt);
		generateSalt(new_user.first_salt);
		hashing(new_user.password, new_user.first_salt, new_user.second_salt);
		memoryReallocation(users, new_user, users_count);
		addUserToFile(new_user);
		cout << endl << DONE << endl;
	}
	else cout << endl << CANSEL << endl;
	system("pause");
}

void logon(User*& users, int& users_count)
{
	char login[LOGIN_LENGTH] = { '\0' };
	char password[PASSWORD_LENGTH] = { '\0' };
	while (true)
	{
		switch (menu(LOGON_MENU, LOGON_POINTS))
		{
		case 0: logonInput(login, LOGIN_LENGTH, ENTER_LOGIN, false); break;
		case 1: logonInput(password, PASSWORD_LENGTH, ENTER_PASSWORD, true); break;
		case 2: 
		{
			if (logonTry(login, password, users, users_count) == true) return;
			else 
			{
				cout << LOGON_FAIL << endl;
				system("pause");
			}
			break;
		}
		case 3: return;
		}
	}
}

void logonInput(char line[], const int& line_length, const char message[], bool hide_flag)
{
	cout << endl << message;
	inputWord(line, line_length, hide_flag);
}

bool logonTry(char login[], char password[], User*& users, int &users_count)
{
	int user_pos = compare(users, users_count, login);

	if (user_pos != -1)
	{
		if (compare(users[user_pos].password,
			hashing(password, users[user_pos].first_salt,
				users[user_pos].second_salt)) == true)
			redirection(users, users[user_pos], users_count);
		return true;
	}
	return false;
}

int compare(User*& users, const int& users_count, char login[])
{
	for (int i = 0; i < users_count; i++)
	{
		int j = 0;
		while (users[i].login[j] == login[j])
		{
			j++;
			if (users[i].login[j] == '\0' && login[j] == '\0')
				return i;
		}
	}
	return -1;
}

bool compare(const char correct[], const char entered[])
{
	for (int i = 0; i < PASSWORD_LENGTH; i++)
		if (correct[i] != entered[i]) return false;
	return true;
}

void memoryReallocation(User*& users, User& new_user, int& users_count)
{
	User* re_users = new User[users_count + 1];

	for (int i = 0; i < users_count; i++) re_users[i] = users[i];
	re_users[users_count] = new_user;
	users_count++;
	delete[]users;
	users = re_users;
}

char*& hashing(char password[], const char first_salt[], const char second_salt[])
{
	string str_1_salt =+ first_salt,
		str_2_salt =+ second_salt,
		hashed_password = sha256(sha256(str_1_salt + password) + sha256(str_2_salt + password));

	for (int i = 0; i < PASSWORD_LENGTH - 1; i++) password[i] = hashed_password.at(i);
	password[PASSWORD_LENGTH - 1] = '\0';
	return password;
}

void generateSalt(char* const& salt)
{
	for (int i = 0; i < SALT_LENGTH - 1; i++)
	{
		if ((rand() % (2 - 1 + 1) + 1) % 2 == 0)
		{
			char symbol = rand() % ('z' - 'A' + 1) + 'A';
			if (!(symbol > 'Z' && symbol < 'a')) salt[i] = symbol;
		}
		else salt[i] = rand() % ('9' - '0' + 1) + '0';
	}
	salt[SALT_LENGTH - 1] = '\0';
}

void inputWord(char* line, const int& size, bool hide_flag)
{
	char symbol = NULL,
		not_trash = NULL;
	int counter = 0;
	bool break_flag = false,
		limit = false;

	while (line[counter] != '\0') counter++;
	if (counter > 0)
	{
		if (hide_flag == true)
			for (int i = 0; i < counter; i++)
				cout << '*';
		else cout << line;
	}
	while (break_flag == false)
	{
		symbol = notTrashAssignment(not_trash);
		if ((counter == size - 1) && (symbol != '\b') && (symbol != '\r'))
		{
			if (!limit)
			{
				cout << "    " << LIMIT;
				limit = true;
			}
			continue;
		}
		if (limit) for (int i = 0; i < LIMIT_LENGTH; i++)
		{
			cout << '\b' << ' ' << '\b';
			limit = false;
		}
		switch (symbol)
		{
		case '\r':
		{
			if (counter > 0) break_flag = true;
			break;
		}
		case '\b':
		{
			if (counter > 0)
			{
				
				outputSymbol(line, '\0', counter, -1, false);
				cout << '\b' << ' ' << '\b';
			}
			break;
		}
		case -32:case'\0':
		{
			char trash = _getch();
			if ((symbol != '\0') && 
				!((trash == 75) || (trash == 80) || (trash == 72) || (trash == 77) || (trash == -123)))
			{
				not_trash = trash;
				outputSymbol(line, symbol, counter, 1,hide_flag);
			}
			break;
		}
		default:
		{
			if ((symbol >= 'А' && symbol <= 'Я') || (symbol >= 'а' && symbol <= 'я') ||
				(symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z') ||
				(symbol >= '0' && symbol <= '9')) outputSymbol(line, symbol, counter, 1, hide_flag);
			break;
		}
		}
	}
	line[counter] = '\0';
}

void outputSymbol(char*line, char symbol,int& counter, int i, bool hide_flag)
{
	line[counter] = symbol;
	(hide_flag == true)? cout<<'*' : cout << symbol;
	counter += i;
}


char notTrashAssignment(char& not_trash)
{
	char symbol = not_trash;
	not_trash = NULL;
	return (symbol == NULL) ? _getch() : symbol;
}

void redirection(User*& users, User& user, int& users_count)
{
	cout << " Вход выполнен успешно!";
	system("pause");
	(user.role == 1) ? userMenu(user) : adminMenu(users, user, users_count);
}

void adminMenu(User*& users, User& admin, int& users_count)
{
	while (true)
	{
		switch (menu((GREETING.at(rand() % 4) + admin.login + '!'), ADMIN_MENU_POINTS))
		{
		case 0: menu("проверка", DEL_CONFIRM); break;
		case 1: break;
		case 2: return;
		}
	}
}

void userMenu(User& user)
{
	cout << " Вход выполнен успешно!";
	system("pause");
}
//s
//void showUsers(User&, int& users_count)
//{
//	int num_of_visible = users_count;
//	cout<<
//	for(int i = 0;i< num_of_visible)
//}