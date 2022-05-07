#include"Files.h"

void readUserFile(User*& users, int& users_count)
{
	ifstream fin(FILE_OF_USERS, ios::binary | ios::in);
	if (!fin.is_open())
	{
		if (menu(USERS_NOT_FOUND, CONFIRM)) // запрос у пользовател€ на создание нового файла
			createAdmin(users, users_count);
	}
	else
	{
		users_count = getUsersCount();
		if (users_count != 0)
		{
			users = new User[users_count];
			fin.read((char*)&users[0], sizeof(User) * users_count);
		}
		else createAdmin(users, users_count);
	}
	fin.close();
}

int getUsersCount()
{
	ifstream file(FILE_OF_USERS, ios::ate | ios::binary);
	const int users_count = file.tellg() / sizeof(User);
	file.close();
	return users_count;
}

void writeToUser(User*& users, const int& users_count)
{
	ofstream fout(FILE_OF_USERS, ios::binary | ios::out);
	fout.write((char*)&users[0], sizeof(User) * users_count);
	fout.close();
}

void addUserToFile(User& user)
{
	ofstream fout(FILE_OF_USERS, ios::binary | ios::app);
	fout.write((char*)&user, sizeof(User));
	fout.close();
}


void readDataFile(Product*& products, int& products_count)
{
	ifstream fin(FILE_OF_USERS, ios::binary | ios::in);
	if (!fin.is_open()) return;
	else
	{
		products_count = getProductsCount();
		if (products_count != 0)
		{
			products = new Product[products_count];
			fin.read((char*)&products[0], sizeof(User) * products_count);
		}
	}
	fin.close();
}

int getProductsCount()
{
	ifstream file(FILE_OF_DATA, ios::ate | ios::binary);
	const int data_count = file.tellg() / sizeof(Product);
	file.close();
	return data_count;
}

void writeToData(Product*& products, const int& products_count)
{
	ofstream fout(FILE_OF_DATA, ios::binary | ios::out);
	fout.write((char*)&products[0], sizeof(User) * products_count);
	fout.close();
}

void addDataToFile(Product& product)
{
	ofstream fout(FILE_OF_DATA, ios::binary | ios::app);
	fout.write((char*)&product, sizeof(User));
	fout.close();
}