#include "Utility.h"

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
	char switcher = _getch();

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
	case RIGHT: return ((line + 1) % line_size);
	default: break;
	}
	return line;
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

char* hashing(char password[], const char first_salt[], const char second_salt[])
{
	string str_1_salt = +first_salt,
		str_2_salt = +second_salt,
		hashed_password = sha256(sha256(str_1_salt + password) + sha256(str_2_salt + password));

	for (int i = 0; i < PASSWORD_LENGTH - 1; i++) password[i] = hashed_password.at(i);
	password[PASSWORD_LENGTH - 1] = '\0';
	return password;
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

char* copyLine(const char old_line[], char new_line[], bool hide_flag)
{
	int i = 0;
	while (old_line[i] != '\0')
	{
		if (hide_flag == false)new_line[i] = old_line[i];
		else new_line[i] = '*';
		i++;
	}
	new_line[i] = '\0';
	return new_line;
}

void canselFunc()
{
	cout << endl << CANSEL << endl;
	system("pause");
}

void doneFunc()
{
	cout << endl << DONE << endl;
	system("pause");
}

int checkRange(const int& l_range, const int& r_range, const int& exit_number, const char message[])
{
	cout << endl << message;
	int number = getInt(message);
	if (number == exit_number) return number;
	while (number<l_range || number > r_range)
	{
		cout << ERROR_MESSAGE << endl << message;
		number = getInt(message);
	}
	return number;
}
