#include "MyString.h"

int getLineSize(const char line[]) 
{
	int i = 0;
	while (line[i] != '\0') i++;
	return i;
}

char* lineResize(char*& line, int additional_cells)
{
	int old_size = getLineSize(line),
		new_size = old_size + additional_cells;
	char* re_line = NULL;
	if (new_size >= 0) re_line = new char[new_size + 1]{ '\0' };
	else
	{
		cout << "ERROR LineResize: Line size < 1.";
		return NULL;
	}

	if (new_size > old_size)
		for (int i = 0; i < old_size; i++) re_line[i] = line[i];
	else
		for (int i = 0; i <= new_size-1; i++) re_line[i] = line[i];
	delete[]line;
	line = re_line;
	return line;
}

char*& addToLine(char*& original_line  , const char additional_line[])
{
	for (int i = getLineSize(original_line),
		j = 0; i < getLineSize(lineResize(original_line, getLineSize(additional_line))); i++, j++)
		original_line[i] = additional_line[j];
	return original_line;
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