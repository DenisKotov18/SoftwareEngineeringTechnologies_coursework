#include "AccountsPart.h"

void newUser( User*& users, int& users_count)
{
	User new_user = { 0, '\0', '\0','\0','\0', false };

	system("cls");
	while ((new_user.login[0] == '\0') || (loginSearch(users, users_count, new_user.login) != -1))
	{
		if (new_user.login[0] != '\0')
		{
			cout << '	' << INVALID_LOGIN << endl;
			system("pause");
			system("cls");
		}
		cout << NEW_USER_HEAD << endl << ENTER_NEW_USER_LOGIN;
		if (inputWord(new_user.login, LOGIN_LENGTH, false) == NULL)
		{
			canselFunc();
			return;
		}
	}
	cout << endl << ENTER_NEW_USER_PASSWORD;
	if(inputWord(new_user.password, PASSWORD_LENGTH, true) == NULL)
	{
		canselFunc();
			return;
	}
	if (menu(NEW_USER_CONF_HEAD, NEW_USER_CONFIRM) == 0)
	{
		generateSalt(new_user.first_salt);
		generateSalt(new_user.second_salt);
		hashing(new_user.password, new_user.first_salt, new_user.second_salt);
		userMemoryReallocation(users, new_user, users_count);
		addUserToFile(new_user);
		doneFunc();
	}
	else canselFunc();
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


void logon(User*& users, int& users_count)
{
	char login[LOGIN_LENGTH] = { '\0' };
	char password[PASSWORD_LENGTH] = { '\0' },
		last_password[PASSWORD_LENGTH] = { '\0' };
	while (true)
	{
		copyLine(last_password, password, false);
		switch (menu((string)LOGON_HEAD + '\n' + LOGIN + login + '\n' + PASSWORD + copyLine(password, last_password, true) + '\n', LOGON_MENU))
		{
		case 0: dataEntry(login, LOGIN_LENGTH, ENTER_LOGIN, false); break;
		case 1:
		{
			dataEntry(password, PASSWORD_LENGTH, ENTER_PASSWORD, true);
			copyLine(password, last_password, false);
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

bool logonTry(char login[], char password[], User*& users, int& users_count)
{
	int user_pos = loginSearch(users, users_count, login);

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

void redirection(User*& users, User& user, int& users_count, const int& user_pos)
{
	system("cls");
	if (user.account_freeze == false) cout << ENTRY_SUCCSESS << endl;
	else
	{
		cout << REDIRECTION_FAIL << endl;
		system("pause");
		return;
	}

	system("pause");
	(user.role == USER) ? userMenu(users, user, users_count, user_pos) : adminMenu(users, user, users_count, user_pos);

}

void adminMenu(User*& users, User& admin, int& users_count, const int& admin_pos)
{
	while (true)
	{
		switch (menu((GREETING.at(rand() % GREETING.size()) + admin.login + '!'), ADMIN_MENU))
		{
		case 0: showUsers(users, users_count, admin); break;
		case 1: assortmentManagment(admin); break;
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
	while (true)
	{
		switch (menu((GREETING.at(rand() % GREETING.size()) + user.login + '!'), USER_MENU))
		{
		case 0:assortmentManagment(user); break;
		case 1:
			if (redactProfile(users, user, users_count, user_pos) == 0) return;
			else break;
		case 2: return;
		default:
			break;
		}
	}
}



void showUsers(User*& users, int& users_count, User& admin)
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
		cout << '|' << setw(21) << right << page + 1 << '/' << setw(19) << left << ((users_count - 1) / NUMBER_OF_VISIBLE + 1) << '|'
			<< endl << '|' << setfill('-') << setw(41) << '-' << setfill(' ') << '|' << endl
			<< ENTER_USER << endl << ESC << endl;

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
				break;
			}
			case 27: return;
			case 224: page = pointerCatcher(counter, first_visible, last_visible, page, ((users_count - 1) / NUMBER_OF_VISIBLE + 1)); break;
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
			+ TABLE_ROLE + ": " + USER_ROLE.at(user.role) + "   " +
			ADMIN_REDACT_ACCESS + USER_ACCESS.at(user.account_freeze), OWNER_REDACT_MENU);
		switch (choise)
		{
		case 0:
		{
			if (menu((user.account_freeze == false) ? USER_FREEZE : USER_UNFREEZE, CONFIRM) == 0)
			{
				(user.account_freeze == false) ? user.account_freeze = true : user.account_freeze = false;
				writeToUser(users, users_count);
				doneFunc();
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
					writeToUser(users, users_count);
					doneFunc();
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

int redactProfile(User*& users, User& user, int& users_count, const int& user_pos)
{
	int choise = menu((string)REDACT_PROFILE_HEAD + user.login + ':', REDACT_PROFILE_MENU);
	while (true)
	{
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
		choise = menu((string)REDACT_PROFILE_HEAD + user.login + ':', REDACT_PROFILE_MENU);
	}
}

void redactUserData(User*& users, const int& users_count, User& user, char user_data[],
	const int& size, const char message[], const char redact_confirm[])
{
	char* new_data = new char[size];
	new_data[0] = '\0';
	dataEntry(new_data, size, message, false);
	switch (size) // по максимальному размеру выбирается, какое поле подлежит изменению
	{
	case LOGIN_LENGTH:
	{
		while (loginSearch(users, users_count, new_data) != -1)
		{
			cout << "   " << INVALID_LOGIN << endl;
			system("pause");
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
		copyLine(new_data, user_data, false);
		writeToUser(users, users_count);
		doneFunc();
	}
	else canselFunc();
	delete[]new_data;
}

void userMemoryReallocation(User*& users, User& new_user, int& users_count)
{
	User* re_users = new User[users_count + 1];

	for (int i = 0; i < users_count; i++) re_users[i] = users[i];
	re_users[users_count] = new_user;
	users_count++;
	delete[]users;
	users = re_users;
}

int loginSearch(User*& users, const int& users_count, char login[])
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

bool delUser(User*& users, int& users_count, const int& del_pos, const char message[])
{
	if (users[del_pos].role != 2)
	{
		if (menu(message, INTENTIONAL_CONFIRM) == YES)
		{
			for (int i = del_pos; i < users_count - 1; i++)
				users[i] = users[i + 1];
			users_count--;
			writeToUser(users, users_count);
			doneFunc();
			return true;
		}
		canselFunc();
	}
	else cout << DEL_EXEPTION << endl;
	system("pause");
	return false;
}
