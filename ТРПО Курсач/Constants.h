#include<vector>
#pragma once



//global
const char FILE_OF_USERS[] = "Users.bin";
const char DONE[] = "\033[32mГОТОВО!\033[0m";
const char CANSEL[] = "\033[33mОтменено!\033[0m";
const char ERROR_SALT[] = "ERRORERRORERROR";

//authorization
const char AUTHORIZATION_MENU[] = "		Добро пожаловать! Пожалуйста авторизируйтесь.";

//inputWord
const char LIMIT[] = "\033[4;31mВы достигли лимита символов!\033[0m";

//User
const int LOGIN_LENGTH = 21;
const int PASSWORD_LENGTH = 65;
const int SALT_LENGTH = 16;

//newUser
const char NEW_USER_MENU[] = "--------------/Создание Новой учётной записи/--------------";
const char ENTER_NEW_USER_LOGIN[] = "Придумайте логин : ";
const char INVALID_LOGIN[] = "\033[4;31mЭтот логин уже занят!\033[0m";
const char ENTER_NEW_USER_PASSWORD[] = "Придумайте пароль : ";
const char NEW_USER_CONF_MENU[] = "Создавая новую запись, Вы соглашаетесь на обработку и хранение введённых Вами данных.";
//logon
const char LOGON_MENU[] = "--------------/Вход/--------------";
const char ENTER_LOGIN[] = "Введите логин : ";
const char ENTER_PASSWORD[] = "Пароль : ";
const char LOGON_FAIL[] = "\033[1;31mНеверный логин и/или пароль!\033[0m";

