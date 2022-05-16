#pragma once

#include "Magic.h"

using namespace std;

int menu(string, const vector<string>); // универсальная функция вывода меню
int pointerCatcher(int&, const int&, const int&, int, const int&); // функция считывания нажатия стрелочек

void generateSalt(char* const&); // создание соли
char* hashing(char[], const char[], const char[]); //хеширование пароля

bool isSimilar(const char[], const char[]); // функция сравнения строк

char* copyLine(const char[], char[], bool); // копирование С-строки в новую

void canselFunc();
void doneFunc();

int checkRange(const int&, const int&, const int&, const char[]);
