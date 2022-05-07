#pragma once

#include <iostream>

using namespace std;

// get size of line
int getLineSize(const char[]);

// line_size + additional_cells
char* lineResize(char*&, int);

char*& addToLine(char*&, const char[]);
