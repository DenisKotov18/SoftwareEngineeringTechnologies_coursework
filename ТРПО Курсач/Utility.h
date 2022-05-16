#pragma once

#include "Magic.h"

using namespace std;

int menu(string, const vector<string>); // ������������� ������� ������ ����
int pointerCatcher(int&, const int&, const int&, int, const int&); // ������� ���������� ������� ���������

void generateSalt(char* const&); // �������� ����
char* hashing(char[], const char[], const char[]); //����������� ������

bool isSimilar(const char[], const char[]); // ������� ��������� �����

char* copyLine(const char[], char[], bool); // ����������� �-������ � �����

void canselFunc();
void doneFunc();

int checkRange(const int&, const int&, const int&, const char[]);
