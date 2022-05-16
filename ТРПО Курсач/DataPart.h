#pragma once

#include "Magic.h"

void assortmentManagment(User&);

void dataRedact(Product*&, int&);
void newData(Product*&, int&);

void dataManipulation(Product*&, int&);

bool searchSimilarData(Product*&, Product&, int&);
bool compareByName(Product&, Product&);
bool compareByArticle(Product&, Product&);
bool compareBySize(Product&, Product&);

void individualTask(Product*&, int&);

void sortMenu(Product*&, int&);

bool searchByProducer(Product*&, Product&, int&, int&);

void sortBySize(Product*&, int&);
void sortByPrice(Product*&, int&);
void sortByAmount(Product*&, int&);
void sortByOrder(Product*&, int&);

int inputArticle(Product&);
char* inputDataNames(char* const&, const char[]);
int inputPrice(Product&);
int inputSize(Product&);
int inputAmount(Product&);

void productMemoryReallocation(Product*&, Product&, int&);

void showRedactData(Product*&, int&);
int dataTable(Product*&, int&, const char[]);

int productRedact(Product&);

void delData(Product*&, int&, const int);

void dataSync(Product*&, int&);
