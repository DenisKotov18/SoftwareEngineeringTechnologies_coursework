#include<vector>
#pragma once



//global
const char FILE_OF_USERS[] = "Users.bin";
const char DONE[] = "\033[32m������!\033[0m";
const char CANSEL[] = "\033[33m��������!\033[0m";
const char ERROR_SALT[] = "ERRORERRORERROR";

//authorization
const char AUTHORIZATION_MENU[] = "		����� ����������! ���������� ���������������.";

//inputWord
const char LIMIT[] = "\033[4;31m�� �������� ������ ��������!\033[0m";

//User
const int LOGIN_LENGTH = 21;
const int PASSWORD_LENGTH = 65;
const int SALT_LENGTH = 16;

//newUser
const char NEW_USER_MENU[] = "--------------/�������� ����� ������� ������/--------------";
const char ENTER_NEW_USER_LOGIN[] = "���������� ����� : ";
const char INVALID_LOGIN[] = "\033[4;31m���� ����� ��� �����!\033[0m";
const char ENTER_NEW_USER_PASSWORD[] = "���������� ������ : ";
const char NEW_USER_CONF_MENU[] = "�������� ����� ������, �� ������������ �� ��������� � �������� �������� ���� ������.";
//logon
const char LOGON_MENU[] = "--------------/����/--------------";
const char ENTER_LOGIN[] = "������� ����� : ";
const char ENTER_PASSWORD[] = "������ : ";
const char LOGON_FAIL[] = "\033[1;31m�������� ����� �/��� ������!\033[0m";

