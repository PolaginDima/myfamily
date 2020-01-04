/*
 * history.cpp
 *
 *  Created on: 19.11.2019
 *      Author: papa
 */

#include "history.h"

History::History(){
	wcout << L"Конструктор History\n";
}

History::~History(){
	wcout << L"Деструктор History\n";
}

void History::add(HISTDATA data){
	m_Cmds.push_back(data);
	//m_Cmds.push_back({execute, undo, depth});
}
