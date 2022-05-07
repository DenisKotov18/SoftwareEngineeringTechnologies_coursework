#pragma once

#include "Magic.h"

using namespace std;

void inputWord(char*, const int&, bool); //функция считывания введённых символов и занесение их в переданное поле
char notTrashAssignment(char&); // часть функции InputWord. Проверяет такие исключения как нажатие знаков, кодирующихся 2 символами
void outputSymbol(char*, char, int&, int, bool); // часть InputWord выводит корректно введённый символ в консоль

char* dataEntry(char[], const int&, const char[], bool); // функция ввода символьного поля с предварительной очисткой экрана
