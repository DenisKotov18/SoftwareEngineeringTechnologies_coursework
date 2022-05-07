#pragma once

#include "Magic.h"

void readUserFile(User*&, int&); // ������� ���������� ������� �������������
int getUsersCount(); // ��������������� ������� ���-�� ������������� � �����
void writeToUser(User*&, const int&); // ������ ���� ��������� � ����
void addUserToFile(User&); // ���������� 1 ������������ � ����� �����

void readDataFile(Product*&, int&);
int getProductsCount();
void writeToData(Product*&, const int&);
void addDataToFile(Product&);