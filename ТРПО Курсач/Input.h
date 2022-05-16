#pragma once

#include "Magic.h"

using namespace std;

char* inputWord(char*, const int&, bool); //������� ���������� �������� �������� � ��������� �� � ���������� ����
char notTrashAssignment(char&); // ����� ������� InputWord. ��������� ����� ���������� ��� ������� ������, ������������ 2 ���������
void outputSymbol(char*, char, int&, int, bool); // ����� InputWord ������� ��������� �������� ������ � �������

char* dataEntry(char[], const int&, const char[], bool); // ������� ����� ����������� ���� � ��������������� �������� ������

double getDouble(const char[]);
int getInt(const char[]);
