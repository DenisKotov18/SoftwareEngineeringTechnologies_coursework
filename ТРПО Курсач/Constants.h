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

// ��� ��������� � ���������� ���������, ������������ � ���������

//global
const char FILE_OF_USERS[] = "Users.bin";
const char FILE_OF_DATA[] = "Data.bin";
const char FILE_OF_FOOTWEAR[] = "Footwear.bin";
const char SAVE_CONFIRM[] = "��������� ���������?";
const char DONE[] = "\033[32m������!\033[0m";
const char CANSEL[] = "\033[33m��������!\033[0m";
const char ERROR_MESSAGE[] = "\033[1;31m������!\033[0m ���������� �����.";
const char ENTRY_SUCCSESS[] = "\033[32m �������� ������������!\033[0m";
const vector<string> CONFIRM{ "��", "���" };
const vector<string> INTENTIONAL_CONFIRM{ "\033[32m���\033[0m", "\033[1;31m��\033[0m" };
const vector<string> GREETING{ "������������, ", "������������, ", "������� ��������, ", "�� ����� ���, ", "���� ��������������, ", "� ������������, "};
const vector<string> USER_ROLE{ "\033[32mUser \033[0m", "\033[33mAdmin\033[0m", "\033[1;31mOwner\033[0m" };
const vector<string> USER_ACCESS{ "\033[32m���� \033[0m", "\033[31m����.\033[0m" };
const int NUMBER_OF_VISIBLE = 5;

const char ESC[] = " ESC - �����";


//User
const int LOGIN_LENGTH = 21;
const int PASSWORD_LENGTH = 65;
const int SALT_LENGTH = 16;
const char LOGIN[] = "�����: ";
const char PASSWORD[] = "������: ";

//Product
const int NAME_LENGTH = 30;

//authorization
const char AUTHORIZATION_HEAD[] = "		����� ����������! ���������� ���������������.";
const vector<string> AUTHORIZATION_MENU{ "�����������", "����", "����� �� �������" };


//readUserFile
const char USERS_NOT_FOUND[] = "�� ������ ������� ���� � ��������������. ������� �����?";

// redirection
const char REDIRECTION_FAIL[] = "\033[31m ���� ������� ������ ���� �������������!\033[0m";



//adminMenu
const vector<string> ADMIN_MENU{ "������ � ������� �������������", "������ � ������������� ��������", "������������� ������� ������", "�����"};


//userMenu
const vector<string> USER_MENU{ "������ � ������������� ��������", "������������� ������� ������", "�����" };


//inputWord
const char LIMIT[] = "\033[4;31m�� �������� ������ ��������!\033[0m";


//newUser
const char NEW_USER_HEAD[] = "--------------/�������� ����� ������� ������/--------------";
const char ENTER_NEW_USER_LOGIN[] = "���������� ����� : ";
const char INVALID_LOGIN[] = "\033[4;31m���� ����� ��� �����!\033[0m";
const char ENTER_NEW_USER_PASSWORD[] = "���������� ������ : ";
const char NEW_USER_CONF_HEAD[] = "�������� ����� ������, �� ������������ �� ��������� � �������� �������� ���� ������.";
const vector<string> NEW_USER_CONFIRM{ "��������","������" };


//logon
const char LOGON_HEAD[] = "--------------/����/--------------";
const vector<string> LOGON_MENU{ "������ �����","������ ������","�����","�����" };
const char ENTER_LOGIN[] = "������� ����� ����� ������� ������ : ";
const char ENTER_PASSWORD[] = "������� ������ ����� ������� ������ : ";
const char LOGON_FAIL[] = "\033[1;31m�������� ����� �/��� ������!\033[0m";


//showUsers
const char ENTER_USER[] = "Enter - �������";
const char TABLE_NAME[] = "��� ������������";
const char TABLE_ROLE[] = "����";
const char TABLE_ACCESS[] = "������";
const char REDACT_ERROR[] = "\033[33m�� �� ������ ������������� ������ ������� ������!\033[0m";


//adminRedact
const vector<string> OWNER_REDACT_MENU{ "����������", "�������� �����", "�������� ������", "�������� ����", "������� ������� ������", "�����" };
const vector<string> ADMIN_REDACT_MENU{ "����������", "�����" };
const char USER_FREEZE[] = "������� ������������� ������� ������������?";
const char USER_UNFREEZE[] = "������� �������������� ������� ������������?";
const char ADMIN_REDACT_HEAD[] = "������� ������ ������������ ";
const char ADMIN_REDACT_ACCESS[] = "������� �������: ";
const char NEW_LOGIN[] = " ����� ����� : ";
const char NEW_PASSWORD[] = "����� ������ : ";
const char NEW_ROLE_HEAD[] = " �������� ����� ���� ������������:";
const vector<string> NEW_ROLE_MENU{ "\033[32mUser\033[0m", "\033[33mAdmin\033[0m" };
const char ACCOUNT_REDACT_CONFIRM[] = " �� �������, ��� ������ �������� \033[31m������ ������\033[0m ������� ������������?";
const char ACCOUNT_DEL_CONFIRM[] = " �� ����� ������ \033[4;31m������������ �������\033[0m  ������� ������������ �� �������?";
const char ACCESS_ERROR[] = "\033[33m������������ ���� ��� ���������� ������� ��������!\033[0m";


//redactProfile
const char REDACT_PROFILE_HEAD[] = "��������� ������� ";
const vector<string> REDACT_PROFILE_MENU{ "�������� �����", "�������� ������", "������� ������� ������", "�����" };
const char SELF_REDACT[] = "�� ����� ������ \033[33m��������\033[0m ���� ������?";
const char INCORRECT_PASSWORD[] = " \033[1;31m�������� ������!\033[0m";
const char SELF_DELETE[] = "�� �������, ��� ������ \033[4;31m������������ �������\033[0m ���� ������� ������?";


//delUser
const char DEL_EXEPTION[] = "\033[33m������ ������� ������ ������ �������!\033[0m";

//assortmentManagment
const char MANAGEMENT_HEAD[] = "--------------/���������� �������������/--------------";
const vector<string> MANAGEMENT_MENU{"�������� ����������� ��������", "����� � ����� ������������", "�����"};


//dataRedact
const char DATA_RED_HEAD[] = "__________________/�������������� ��������/__________________";
const vector<string> DATA_RED_MENU{"������ �� ������ �������������", "�������� ����� �����", "�����"};
const char DATA_EMPTY[] = "�� ������ ������ � ������������ ��� �� ����� ���� �����...";

//newData
const int CHILD_MIN_SIZE = 32;
const int CHILD_MAX_SIZE = 40;
const int ADULT_SIZE = 48;
const char NEW_DATA_HEAD[] = "--------------/���������� ����� ������ ������/--------------";
const char INPUT_ARTICLE[] = "�������� ������� ����� (� - �������, � - �������, � - �������) ";
const vector<string> ARTICLE_POINTS{"�", "�", "�", "��������"};
const char INPUT_PRODUCT_NAME[] = "������� �������� ������ : ";
const char INPUT_PRODUCER_NAME[] = "������� ��� ������������� : ";
const char INPUT_PRICE[] = "������� ���� �� ����(0 - ������):";
const char INPUT_CHILD_SIZE[] = "������� ������ �����(����� ����� �� 32 �� 40, 0 - ������) : ";
const char INPUT_ADULT_SIZE[] = "������� ������ �����(����� ����� �� 40 �� 48, 0 - ������) : ";
const char INPUT_AMOUNT[] = "������� ���������� ��� : ";
const char PRICE_ERROR[] = "���� �� ����� ���� �������������.";
const char AMOUNT_ERROR[] = "������� ������������� ����� ����� ���.";
const char FINAL_PRODUCT[] = "------����� �����------";
const char FINAL_NAME[] = "��������: ";
const char FINAL_ARTICLE[] = "�������: ";
const char FINAL_PRODUCER[] = "�������������: ";
const char FINAL_PRICE[] = "���� �� ����: ";
const char FINAL_SIZE[] = "������: ";
const char FINAL_AMOUNT[] = "���-�� ���: ";
const char FINAL_CONFIRMATION[] = " ������ �������� ���� ����� � ��� �����������?";
const char MATCH_FOUND[] = " ����� ����� ��� ���� � ������������, ���������� ����� ��� ����� ��������� � ���������...";

//showData
const char TABLE_ASSORTMENT[] = "�����������";
const char ENTER_DATA[] = "Enter - ������ ��������������";
const char DATA_CHOOSE[] = "������� ���������� ����� �������������� ������ ( 0 - ������ ) : ";

//productRedact
const char PRODUCT_REDACT_HEAD[] = "------������������� �����------";
const vector<string> PRODUCT_REDACT_MENU{ "�������������", "������� �������������", "�������� ����", "�������� �������", "�������� ������", "�������� ����������","������� �����", "�����"};
const char ERROR_ARTICLE_SIZE[] = "������ ����� �� ������������� ��������!";
const char DATA_DELETE[] = "�� �������, ��� ������ \033[4;31m�������\033[0m ���� ����� �� ������������?";

//dataManipulation
const char DATA_MANIPULATION_HEAD[] = "����������� � ����� ��������! �������� ������������ ��� �����.\n";
const vector<string> DATA_MANIPULATION_MENU{ "�������� ������������", "������� ������ ����� �� �������� �������� � �������(�.�.)", "����������", "�����"};

//individualTask
const char SORT_DATA_NOT_FOUND[] = "������ � ������ ����������� �� �������!";

//sortMenu
const char SORT_MENU_HEAD[] = "------���� ����������------\n";
const vector<string> SORT_MENU_POINTS{ "�� ���������� ���", "�� ������� �����", "�� ����",  "�����" };

//sortByOrder
const char SORT_QUESTION[] = "��� �����������?";
const vector<string>SORT_POINTS{  "�� �����������", "�� ��������"};

struct User // ��������� ������������
{
	int role; // ������� ������� 0 - user , 1 - admin , 2 - owner
	char login[LOGIN_LENGTH]; // ����� ������������
	char password[PASSWORD_LENGTH]; // ������������ ������
	char first_salt[SALT_LENGTH]; // 1-� ���� ��� ����������� ������
	char second_salt[SALT_LENGTH]; // 2-� ����� ��� ����������� ������
	bool account_freeze; // ��������� ���������� 
};

struct  Product // ��������� ������������ �����
{
	char article; // ������� ������
	char name[NAME_LENGTH]; // ��� ������
	char producer[NAME_LENGTH]; // �������� �������� ������������
	double price; //���� ������
	int size; // ������ �����
	int amount; // ���������� ���
};

