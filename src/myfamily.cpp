//============================================================================
// Name        : myfamily.cpp
// Author      : Polagin D.A.
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tests/test.h"
#include "consolework.h"

int main() {
	std::locale::global (std::locale ("") );// Set program locale to system locale
	std::ios::sync_with_stdio(false);

	//test();

	mainDisplay();

	return 0;
}

