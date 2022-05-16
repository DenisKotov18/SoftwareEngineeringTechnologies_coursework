#pragma once

#include "Magic.h"

void readUserFile(User*&, int&); // функция считывания массива пользователей
int getUsersCount(); // Предварительный подсчёт кол-ва пользователей в файле
void writeToUser(User*&, const int&); // Запись всех изменений в файл
void addUserToFile(User&); // добавление 1 пользователя в конец файла

void readDataFile(Product*&, int&);
int getProductsCount();
void writeToData(Product*&, const int&);
void addDataToFile(Product&);