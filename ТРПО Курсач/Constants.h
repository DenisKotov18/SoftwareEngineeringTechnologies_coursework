#pragma once

#define UP 72
#define DOWN 80
#define LIMIT_LENGTH 32
#define LEFT 75
#define RIGHT 77
#define OWNER 2
#define ADMIN 1
#define USER 0
#define YES 1
#define NO 0

using namespace std;

// Все сообщения и глобальные константы, появляющиеся в программе

//global
const char FILE_OF_USERS[] = "Users.bin";

const char FILE_OF_DATA[] = "Data.bin";

const char FILE_OF_FOOTWEAR[] = "Footwear.bin";

const char DONE[] = "\033[32mГОТОВО!\033[0m";

const char CANSEL[] = "\033[33mОтменено!\033[0m";

const char ENTRY_SUCCSESS[] = "\033[32m Личность подтверждена!\033[0m";

const vector<string> CONFIRM{ "Да", "Нет" };

const vector<string> INTENTIONAL_CONFIRM{ "\033[32mНет\033[0m", "\033[1;31mДа\033[0m" };

const vector<string> GREETING{ "Здравствуйте, ", "Приветствуем, ", "Доброго здоровья, ", "Мы ждали Вас, ", "Рады приветствовать, ", "С возвращением,"};

const vector<string> USER_ROLE{ "\033[32mUser \033[0m", "\033[33mAdmin\033[0m", "\033[1;31mOwner\033[0m" };

const vector<string> USER_ACCESS{ "\033[32mЕсть \033[0m", "\033[31mБлок.\033[0m" };

const char ENTER[] = "Enter - Выбрать";

const char ESC[] = " ESC - Выход";


//User
const int LOGIN_LENGTH = 21;

const int PASSWORD_LENGTH = 65;

const int SALT_LENGTH = 16;

const char LOGIN[] = "Логин: ";

const char PASSWORD[] = "Пароль: ";

//Product
const int NAME_LENGTH = 30;

//authorization
const char AUTHORIZATION_HEAD[] = "		Добро пожаловать! Пожалуйста авторизируйтесь.";

const vector<string> AUTHORIZATION_MENU{ "Регистрация", "Вход", "Выход из системы" };


//readUserFile
const char USERS_NOT_FOUND[] = "Не удаётся открыть файл с пользователями. Создать новый?";

// redirection
const char REDIRECTION_FAIL[] = "\033[31m Ваша учётная запись была заблокирована!\033[0m";



//adminMenu
const vector<string> ADMIN_MENU{ "Работа с данными пользователей", "Работа с ассортиментом магазина", "Редактировать учётную запись", "Выход"};


//userMenu
const vector<string> USER_MENU{ "Работа с ассортиментом магазина", "Редактировать учётную запись", "Выход" };


//inputWord
const char LIMIT[] = "\033[4;31mВы достигли лимита символов!\033[0m";


//newUser
const char NEW_USER_HEAD[] = "--------------/Создание Новой учётной записи/--------------";

const char ENTER_NEW_USER_LOGIN[] = "Придумайте логин : ";

const char INVALID_LOGIN[] = "\033[4;31mЭтот логин уже занят!\033[0m";

const char ENTER_NEW_USER_PASSWORD[] = "Придумайте пароль : ";

const char NEW_USER_CONF_HEAD[] = "Создавая новую запись, Вы соглашаетесь на обработку и хранение введённых Вами данных.";

const vector<string> NEW_USER_CONFIRM{ "Согласен","Отмена" };


//logon
const char LOGON_HEAD[] = "--------------/Вход/--------------";

const vector<string> LOGON_MENU{ "Ввести логин","Ввести пароль","Войти","Назад" };

const char ENTER_LOGIN[] = "Введите логин вашей учётной записи : ";

const char ENTER_PASSWORD[] = "Введите пароль вашей учётной записи : ";

const char LOGON_FAIL[] = "\033[1;31mНеверный логин и/или пароль!\033[0m";


//showUsers
const int NUMBER_OF_VISIBLE = 5;

const char TABLE_NAME[] = "Имя пользователя";

const char TABLE_ROLE[] = "Роль";

const char TABLE_ACCESS[] = "Доступ";

const char REDACT_ERROR[] = "\033[33mВы не можете редактировать данную учётную запись!\033[0m";


//adminRedact
const vector<string> OWNER_REDACT_MENU{ "Блокировка", "Изменить логин", "Изменить пароль", "Изменить роль", "Удалить учётную запись", "Назад" };

const vector<string> ADMIN_REDACT_MENU{ "Блокировка", "Назад" };

const char USER_FREEZE[] = "Желаете заблокировать данного Пользователя?";

const char USER_UNFREEZE[] = "Желаете разблокировать данного Пользователя?";

const char ADMIN_REDACT_HEAD[] = "Учётная запись пользователя ";

const char ADMIN_REDACT_ACCESS[] = "Наличие доступа: ";

const char NEW_LOGIN[] = " Новый логин : ";

const char NEW_PASSWORD[] = "Новый пароль : ";

const char NEW_ROLE_HEAD[] = " Выберите новую роль пользователя:";

const vector<string> NEW_ROLE_MENU{ "\033[32mUser\033[0m", "\033[33mAdmin\033[0m" };

const char ACCOUNT_REDACT_CONFIRM[] = " Вы уверены, что хотите изменить \033[31mличные данные\033[0m данного пользователя?";

const char ACCOUNT_DEL_CONFIRM[] = " Вы точно хотите \033[4;31mБЕЗВОЗВРАТНО УДАЛИТЬ\033[0m  данного пользователя из системы?";

const char ACCESS_ERROR[] = "\033[33mНедостаточно прав для совершения данного действия!\033[0m";


//redactProfile
const char REDACT_PROFILE_HEAD[] = "Настройки профиля ";

const vector<string> REDACT_PROFILE_MENU{ "Изменить логин", "Изменить пароль", "Удалить учётную запись", "Назад" };

const char SELF_REDACT[] = "Вы точно хотите \033[33mИЗМЕНИТЬ\033[0m свои данные?";

const char INCORRECT_PASSWORD[] = " \033[1;31mНеверный пароль!\033[0m";

const char SELF_DELETE[] = "Вы уверены, что хотите \033[4;31mБЕЗВОЗВРАТНО УДАЛИТЬ\033[0m свою учётную запись?";


//delUser
const char DEL_EXEPTION[] = "\033[33mДанную учётную запись нельзя удалить!\033[0m";

//assortmentManagment
const char MANAGEMENT_HEAD[] = "--------------/Управление ассортиментом/--------------";

const vector<string> MANAGEMENT_MENU{"Изменить ассортимент магазина", "Войти в режим пользователя", "Назад"};

struct User // Структура пользователя
{
	int role; // Уровень доступа 0 - user , 1 - admin , 2 - owner
	char login[LOGIN_LENGTH]; // логин пользователя
	char password[PASSWORD_LENGTH]; // Хешированный пароль
	char first_salt[SALT_LENGTH]; // 1-я соль для хеширования пароля
	char second_salt[SALT_LENGTH]; // 2-я солья для хеширования пароля
	bool account_freeze; // Состояние болкировки 
};

struct  Product // Структура ассортимента обуви
{
	char article; // артикул товара
	char name[NAME_LENGTH]; // имя товара
	char producer[NAME_LENGTH]; // название компании изготовителя
	int size; // размер обуви
	int amount; // количество пар
};