#pragma once

#include "Magic.h"

using namespace std;

void createAdmin(User*&, int&); // создание администратора, если файл не существует или пуст

void newUser(User*&, int&); // создание нового пользователя

void logon(User*&, int&); // меню входа

bool logonTry(char[], char[], User*&, int&); /* проверка совпадения введённых данных и данных пользователей на совпадение,
и при последнем последующий вход в систему */

void redirection(User*&, User&, int&, const int&); // проверка на блокировку и перенаправление пользователей в меню, соответствующее их роли

void adminMenu(User*&, User&, int&, const int&); // функция меню администратора

void userMenu(User*&, User&, int&, const int&); // функция меню пользователя

void showUsers(User*&, int&, User&); // функция вывода всех пользователей в консоль с возможностью выбора определённого

int redactProfile(User*&, User&, int&, const int&); // функция меню редактирования профиля самим пользователем

void adminRedact(User*&, int&, User&, User&, int); // функция меню редактирования пользовательской учётной записи администратором

void redactUserData(User*&, const int&, User&, char[], const int&, const char[], const char[]); // функция перезаписи логина и/или пароля пользователя

void userMemoryReallocation(User*&, User&, int&); // перевыделение памяти динамического массива пользователей

int loginSearch(User*&, const int&, char[]); // функция поиска введённого логина среди уже существующих

bool isUser(User&); // функция подтверждения личности пользователя, сравнивающая введённый и существующий пароли 

bool delUser(User*&, int&, const int&, const char[]); // функция удаления данных переданного пользователя
