/*
 * ver20.cpp
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#include "workbdver.h"

void Workbdver20::handle(){
	std::wcout << L"Update to ver. 2.0" << std::endl;
}

bool Workbdver20::checkVersion() const{
	return true;
}
