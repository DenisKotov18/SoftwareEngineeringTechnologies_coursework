#include "Input.h"

char* inputWord(char* line, const int& size, bool hide_flag)
{
	char symbol = NULL,
		not_trash = NULL;
	int counter = 0;
	bool break_flag = false,
		limit = false;

	while (line[counter] != '\0') counter++;
	char* backup_line = new char[counter+1];
	copyLine(line, backup_line, hide_flag);
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
				outputSymbol(line, '\0', --counter, 0, false);
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
				outputSymbol(line, symbol, counter, 1, hide_flag);
			}
			break;
		}
		case 27:
		{
			copyLine(backup_line, line, hide_flag);
			if (backup_line[0] != '\0')delete[]backup_line;
			return NULL;
		}

		default:
		{
			if ((symbol >= 'À' && symbol <= 'ß') || (symbol >= 'à' && symbol <= 'ÿ') ||
				(symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z') ||
				(symbol >= '0' && symbol <= '9') || symbol == '_') outputSymbol(line, symbol, counter, 1, hide_flag);
			break;
		}
		}
	}
	line[counter] = '\0';
	if (backup_line[0] != '\0')delete[]backup_line;
	return line;
}

void outputSymbol(char* line, char symbol, int& counter, int i, bool hide_flag)
{
	line[counter] = symbol;
	(hide_flag == true) ? cout << '*' : cout << symbol;
	counter += i;
}

char notTrashAssignment(char& not_trash)
{
	char symbol = not_trash;
	not_trash = NULL;
	return (symbol == NULL) ? _getch() : symbol;
}

char* dataEntry(char line[], const int& line_length, const char message[], bool hide_flag)
{
	system("cls");
	cout << endl << message;
	inputWord(line, line_length, hide_flag);
	return line;
}

double getDouble(const char message[])
{
	double number = 0;
	while (true)
	{
		cin >> number;
		if (cin.get() == '\n') break;
			cin.clear();
			cin.ignore(256, '\n');
			cout << '	' << ERROR_MESSAGE << endl;
	}
	return number;
}

int getInt(const char message[])
{
	int number = 0;
	while (true)
	{
		cin >> number;
		if (cin.get() == '\n') break;
		cin.clear();
		cin.ignore(256, '\n');
		cout << '	' << ERROR_MESSAGE << endl << message;
	}
	return number;
}
