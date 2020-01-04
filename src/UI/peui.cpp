/*
 * peui.cpp
 *
 *  Created on: 19.11.2019
 *      Author: papa
 */

#include "peui.h"

PeopleEditUI::PeopleEditUI(ModelPeople *mp, int depth, History *hist)
:m_mp(mp), m_hist(hist), m_depth(depth)/*, m_CmdSave(nullptr), m_CmdCancel(nullptr)*/{
	wcout << L"Конструктор PeopleEditUI\n";
	if (!m_hist) m_hist = new History();
}

PeopleEditUI::~PeopleEditUI(){
	wcout << L"Деструктор PeopleEditUI\n";
}

void PeopleEditUI::setSave(CMDSAVE cmd){
	m_CmdSave = cmd;
}

void PeopleEditUI::setCancel(CMDCANCEL cmd){
	m_CmdCancel = cmd;
}
