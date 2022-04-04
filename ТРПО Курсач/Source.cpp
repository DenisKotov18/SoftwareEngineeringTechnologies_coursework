#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <ctime>
#include<iomanip>
#include "Constants.h"
#include "sha256.h"

using namespace std;

void authorization();// меню авторизации
void readUserFile(struct User *&, int&); // функция считывания массива пользователей
int getUsersCount(); // Предварительный подсчёт кол-ва пользователей в файле
void sunc(User*&, const int&); // Запись всех изменений в файл
void addUserToFile(User&); // добавление 1 пользователя в конец файла
int menu(string, const vector<string>); // универсальная функция вывода меню
int pointerCatcher(int&, const int&, const int&, int, const int&); // функция считывания нажатия стрелочек
void logon(User*&, int&); // меню входа
char* dataEntry(char[], const int&, const char[], bool); // функция ввода логина или пароля
bool logonTry(char[], char[], User*&, int&); /* проверка совпадения введённых данных и данных пользователей на совпадение,
и при последнем последующий вход в систему */
int compare(User*&, const int&, char[]); // функция сравнения логинов
bool isSimilar(const char[], const char[]); // функция сравнения паролей
void createAdmin(User *&, int&); // создание администратора, если файл не существует или пуст
void newUser(User*&, int&); // создание нового пользователя
void memoryReallocation(User*&, User&, int&); // перевыделение памяти динамического массива пользователей
char* hashing(char[],const char[],const char[]); //хеширование пароля
void copyLine(const char[], char[]); // копирование С-строки в новую
void generateSalt(char* const&); // создание соли
void inputWord(char*, const int&, bool); //функция считывания введённых символов и занесение их в переданное поле
char notTrashAssignment(char&); // часть функции InputWord. Проверяет такие исключения как нажатие символов, кодирующихся 2 кодами
void outputSymbol(char*, char, int&, int, bool); // часть InputWord выводит корректно введённый символ в консоль
void redirection(User*&, User&, int&, const int&); // проверка на блокировку и перенаправление пользователей в меню, соответствующее их роли
void adminMenu(User*&, User&, int&, const int&); // меню администратора
void userMenu(User*&, User&, int&, const int&); // меню пользователя
void showUsers(User*&, int&, User&); // функция вывода всех пользователей в консоль с возможностью выбора определённого
void adminRedact(User*&, int&, User&, User&, int); // функция редактирования пользовательской учётной записи администратором
void redactUserData(User*&, const int& , User&, char[], const int&, const char[], const char[]);
bool delUser(User*&, int&, const int&, const char[]);
bool isUser(User&);
int redactProfile(User*&, User&, int&, const int&);

struct User
{
	int role; // Уровень доступа 0 - user , 1 - admin , 2 - owner
	char login[LOGIN_LENGTH]; // логин пользователя
	char password[PASSWORD_LENGTH]; // Хешированный пароль
	char first_salt[SALT_LENGTH]; // 1-я соль для хеширования пароля
	char second_salt[SALT_LENGTH]; // 2-я солья для хеширования пароля
	bool account_freeze; // Состояние болкировки 
};
 
void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUSSIAN");
	SetConsoleCP(1251);
	authorization();
}

void authorization()
{
	User* users = NULL; // Массив пользователей
	int users_count = 0; // Кол-во пользователей
	bool program_end = false; // флаг выхода из цикла меню авторизации и завершения программы
	readUserFile(users, users_count);
	while (program_end == false)
	{
		switch (menu(AUTHORIZATION_HEAD, AUTHORIZATION_MENU)) // вывод пунктов меню
		{
		case 0: newUser(users, users_count); break;
		case 1: logon(users, users_count); break;
		case 2: program_end = true; break;
		default:
			break;
		}
	}
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

void sunc(User*& users, const int & users_count)
{
	ofstream fout(FILE_OF_USERS, ios::binary | ios::out);
	fout.write((char*)&users[0], sizeof(User) * users_count);
	fout.close();
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
	users[0].role = OWNER;
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
	char exit_catcher;
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
			if (exit_catcher == '\r') return choise;
		}
		pointerCatcher(choise, 0, points_amt, 0, 1);
	}
}

int pointerCatcher(int& column, const int& first_point, const int& last_point, int line, const int& line_size)
{
	char switcher = NULL;

	switcher = _getch();
	
	switch (switcher)
	{
	case UP: 
	{
		(column == first_point) ? column = last_point - 1 : column--;
		return line;
	}
	case DOWN:
	{
		column = ++column % last_point;
		return line;
	}
	case LEFT: return (line == 0) ? line_size - 1 : --line;
	case RIGHT: return ((line +1) % line_size);
	default: break;
	}
	return line;
}

void newUser(User*& users, int& users_count)
{
	User new_user = { 0, '\0', '\0','\0','\0', false};

	system("cls");
	while ((new_user.login[0] == '\0' )|| (compare(users, users_count, new_user.login) != -1))
	{
		if (new_user.login[0] != '\0')
		{
			cout << '	' << INVALID_LOGIN << endl;
			system("pause");
			system("cls");
		}
		cout << NEW_USER_HEAD << endl << ENTER_NEW_USER_LOGIN;
		inputWord(new_user.login, LOGIN_LENGTH, false);
	}
	cout << endl << ENTER_NEW_USER_PASSWORD;
	inputWord(new_user.password, PASSWORD_LENGTH, true);
	if (menu(NEW_USER_CONF_HEAD, NEW_USER_CONFIRM) == 0)
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
	char password[PASSWORD_LENGTH] = { '\0' },
		last_password[PASSWORD_LENGTH] = { '\0' };
	while (true)
	{
		copyLine(last_password, password);
		switch (menu(LOGON_HEAD, LOGON_MENU))
		{
		case 0: dataEntry(login, LOGIN_LENGTH, ENTER_LOGIN, false); break;
		case 1: 
		{
			dataEntry(password, PASSWORD_LENGTH, ENTER_PASSWORD, true);
			copyLine(password, last_password);
			break;
		}
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

char* dataEntry(char line[], const int& line_length, const char message[], bool hide_flag)
{
	cout << endl << message;
	inputWord(line, line_length, hide_flag);
	return line;
}

bool logonTry(char login[], char password[], User*& users, int &users_count)
{
	int user_pos = compare(users, users_count, login);

	if (user_pos != -1)
	{
		if (isSimilar(users[user_pos].password,
			hashing(password, users[user_pos].first_salt,
				users[user_pos].second_salt)) == true)
		{
			redirection(users, users[user_pos], users_count, user_pos);
			return true;
		}
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

bool isSimilar(const char correct[], const char entered[])
{
	int i = 0;
	while (correct[i] != '\0')
	{
		if (correct[i] != entered[i]) return false;
		i++;
	}
	if (entered[i] == '\0')return true;
	else return false;
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

char* hashing(char password[], const char first_salt[], const char second_salt[])
{
	string str_1_salt =+ first_salt,
		str_2_salt =+ second_salt,
		hashed_password = sha256(sha256(str_1_salt + password) + sha256(str_2_salt + password));

	for (int i = 0; i < PASSWORD_LENGTH - 1; i++) password[i] = hashed_password.at(i);
	password[PASSWORD_LENGTH - 1] = '\0';
	return password;
}

void copyLine(const char old_line[], char new_line[])
{
	int i = 0;
	while (old_line[i] != '\0')
	{
		new_line[i] = old_line[i];
		i++;
	}
	new_line[i] = '\0';
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

void redirection(User*& users, User& user, int& users_count, const int& user_pos)
{
	system("cls");
	if(user.account_freeze == false) cout << ENTRY_SUCCSESS << endl;
	else
	{
		cout << REDIRECTION_FAIL << endl;
		system("pause");
		return;
	}
	system("pause");
	(user.role == USER) ? userMenu(users,user, users_count, user_pos) : adminMenu(users, user, users_count, user_pos);
}

void adminMenu(User*& users, User& admin, int& users_count, const int& admin_pos)
{
	while (true)
	{
		switch (menu((GREETING.at(rand() % 4) + admin.login + '!'), ADMIN_MENU))
		{
		case 0: showUsers(users, users_count, admin); break;
		case 1: break;
		case 2: 
			if (redactProfile(users, admin, users_count, admin_pos) == 0) return;
			else break;
		case 3: return;
		default: break;
		}
	}
}

void userMenu(User*& users, User& user, int& users_count, const int& user_pos)
{
	cout << " Вход выполнен успешно!";
	system("pause");
}

void showUsers(User *& users, int& users_count, User& admin)
{
	int counter = 0,
		page = 0,
		first_visible = 0,
		last_visible = 0;
	bool uncorrect_flag = false;

	while (true)
	{
		system("cls");
		first_visible = NUMBER_OF_VISIBLE * page;
		last_visible = (first_visible + NUMBER_OF_VISIBLE < users_count) ? first_visible + NUMBER_OF_VISIBLE : users_count;
		if (counter < first_visible || counter >= last_visible) counter = first_visible;

		cout << setfill('_') << setw(43) << '_' << setfill(' ') << endl
			<< '|' << "     " << TABLE_NAME << "    | " << TABLE_ROLE << " | " << TABLE_ACCESS << " |" << endl
			<< '|' << setfill('-') << setw(41) << '-' << setfill(' ') << '|' << endl;
		for (int i = first_visible; i < last_visible; i++)
		{

			if (i == counter) cout << "| >\033[32m" << setw(22) << left << users[i].login << "\033[0m   ";
			else  cout << "|  " << setw(22) << users[i].login << "   ";

			cout << setw(5) << USER_ROLE.at(users[i].role) << "   "
				<< USER_ACCESS.at(users[i].account_freeze) << " |" << endl
				<< '|' << setfill('-') << setw(41) << '-' << setfill(' ') << '|' << endl;
		}
		cout << '|' << setw(21) << right << page + 1 << '/' << setw(19) << left << ((users_count-1) / NUMBER_OF_VISIBLE + 1) << '|'
			<< endl << '|' << setfill('-') << setw(41) << '-' << setfill(' ') << '|' << endl 
			<< "Enter - Выбрать"  << endl <<  " ESC - Выход" << endl;

		do
		{
			uncorrect_flag = false;
			switch (_getch())
			{
			case '\r': 
			{
				if (isSimilar(admin.login, users[counter].login) == true)
				{
					redactProfile(users, admin, users_count, counter);
					break;
				}
				if (admin.role > users[counter].role) adminRedact(users, users_count, admin, users[counter], counter);
				else cout << REDACT_ERROR << endl;
				system("pause");
				break;
			}
			case 27: return;
			case 224: page = pointerCatcher(counter, first_visible, last_visible, page, ((users_count-1) / NUMBER_OF_VISIBLE + 1)); break;
			default: uncorrect_flag = true;
			}
		} while (uncorrect_flag == true);
	}
}

void adminRedact(User*& users, int& users_count, User& admin, User& user, int user_pos)
{
	int choise = 0;
	while (true)
	{
		system("cls");
		choise = menu(ADMIN_REDACT_HEAD + (string)user.login + ".   "
			+ TABLE_ROLE +": " + USER_ROLE.at(user.role) + "   " +
			ADMIN_REDACT_ACCESS + USER_ACCESS.at(user.account_freeze), OWNER_REDACT_MENU);
		switch (choise)
		{
		case 0:
		{
			if (menu((user.account_freeze == false) ? USER_FREEZE : USER_UNFREEZE, CONFIRM) == 0)
			{
				(user.account_freeze == false) ? user.account_freeze = true : user.account_freeze = false;
				cout << DONE << endl;
				sunc(users, users_count);
				system("pause");
			}
			break;
		}
		case 1:case 2: case 3: case 4:
		{
			if (admin.role == OWNER)
			{
				switch (choise)
				{
				case 1:redactUserData(users, users_count, user, user.login
					, LOGIN_LENGTH, NEW_LOGIN, ACCOUNT_REDACT_CONFIRM); break;
				case 2:redactUserData(users, users_count, user, user.password,
					PASSWORD_LENGTH, NEW_PASSWORD, ACCOUNT_REDACT_CONFIRM); break;
				case 3:
				{
					user.role = menu(NEW_ROLE_HEAD, NEW_ROLE_MENU);
					cout << DONE << endl;
					sunc(users, users_count);
					system("pause");
					break;
				}
				case 4:
					if (delUser(users, users_count, user_pos, ACCOUNT_DEL_CONFIRM) == true)
						return;
					else 
						break;
				default: break;
				}
			}
			else cout << ACCESS_ERROR << endl;
			break;
		}
		case 5: return;
		default: break;
		}
	}
}

void redactUserData(User*& users, const int& users_count, User& user, char user_data[],
	const int& size, const char message[], const char redact_confirm[])
{
	char* new_data = new char[size];
	new_data[0] = '\0';
	dataEntry(new_data, size, message, false);
	switch (size)
	{
	case LOGIN_LENGTH:
	{
		while (compare(users, users_count, new_data) != -1)
		{
			cout << "   " << INVALID_LOGIN << endl;
			system("pause");
			system("cls");
			dataEntry(new_data, size, message, false);
		}
		break;
	}
	case PASSWORD_LENGTH: hashing(new_data, user.first_salt, user.second_salt); break;
	default: 
		break;
	}	
	if (menu(redact_confirm, INTENTIONAL_CONFIRM) == YES)
	{
		copyLine(new_data, user_data);
		sunc(users, users_count);
		cout << DONE << endl;
	}
	else cout << CANSEL << endl;
	delete[]new_data;
	system("pause");
}

bool delUser(User*& users, int& users_count, const int& del_pos, const char message[])
{
	if (users[del_pos].role != 2)
	{
		if (menu(message, INTENTIONAL_CONFIRM) == YES)
		{
			for (int i = del_pos; i < users_count - 1; i++)
				users[i] = users[i + 1];
			users_count--;
			cout << DONE << endl;
			sunc(users, users_count);
			system("pause");
			return true;
		}
		cout << CANSEL << endl;
	}
	else cout << DEL_EXEPTION << endl;
	system("pause");
	return false;
}

bool isUser(User& user)
{
	char password[PASSWORD_LENGTH] = { '\0' };
	if (isSimilar(user.password, hashing(dataEntry(password, PASSWORD_LENGTH, ENTER_PASSWORD, true),
		user.first_salt, user.second_salt)) != true)
	{
		cout << INCORRECT_PASSWORD << endl;
		system("pause");
		return false;
	}
	cout << ENTRY_SUCCSESS << endl;
	return true;
}

int redactProfile(User*& users, User& user, int& users_count, const int& user_pos)
{
	int choise = menu((string)REDACT_PROFILE_HEAD + user.login + ':', REDACT_PROFILE_MENU);
	while (true)
	{
		system("cls");
		if (choise == 3) return 1;
		if (isUser(user) == true)
		{
			switch (choise)
			{
			case 0:
				redactUserData(users, users_count, user, user.login, LOGIN_LENGTH, NEW_LOGIN, SELF_REDACT);
				break;
			case 1:
				redactUserData(users, users_count, user, user.password, PASSWORD_LENGTH, NEW_PASSWORD, SELF_REDACT);
				break;
			case 2:
				if (delUser(users, users_count, user_pos, SELF_DELETE) == true)
					return 0;
				else
					break;
			default: break;
			}
		}
		choise = menu(REDACT_PROFILE_HEAD, REDACT_PROFILE_MENU);
	}
}
