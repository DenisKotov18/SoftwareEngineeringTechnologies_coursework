#pragma once

#include "Magic.h"

using namespace std;

void createAdmin(User*&, int&); // �������� ��������������, ���� ���� �� ���������� ��� ����

void newUser(User*&, int&); // �������� ������ ������������

void logon(User*&, int&); // ���� �����

bool logonTry(char[], char[], User*&, int&); /* �������� ���������� �������� ������ � ������ ������������� �� ����������,
� ��� ��������� ����������� ���� � ������� */

void redirection(User*&, User&, int&, const int&); // �������� �� ���������� � ��������������� ������������� � ����, ��������������� �� ����

void adminMenu(User*&, User&, int&, const int&); // ������� ���� ��������������

void userMenu(User*&, User&, int&, const int&); // ������� ���� ������������

void showUsers(User*&, int&, User&); // ������� ������ ���� ������������� � ������� � ������������ ������ ������������

int redactProfile(User*&, User&, int&, const int&); // ������� ���� �������������� ������� ����� �������������

void adminRedact(User*&, int&, User&, User&, int); // ������� ���� �������������� ���������������� ������� ������ ���������������

void redactUserData(User*&, const int&, User&, char[], const int&, const char[], const char[]); // ������� ���������� ������ �/��� ������ ������������

void userMemoryReallocation(User*&, User&, int&); // ������������� ������ ������������� ������� �������������

int loginSearch(User*&, const int&, char[]); // ������� ������ ��������� ������ ����� ��� ������������

bool isUser(User&); // ������� ������������� �������� ������������, ������������ �������� � ������������ ������ 

bool delUser(User*&, int&, const int&, const char[]); // ������� �������� ������ ����������� ������������
