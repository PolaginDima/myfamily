/*
 * workbdver.cpp
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#include "workbdver.h"

Workbdver::Workbdver(Workbdimp *bd)
:m_next(nullptr), m_bd(bd){
	//std::wcout << L"Конструктор Workbdver" << std::endl;
}

Workbdver::Workbdver(Workbdver &previouse_ver):m_next(nullptr), m_bd(previouse_ver.m_bd){
	previouse_ver.setNext(this);
	//std::wcout << L"Конструктор Workbdver" << std::endl;
};

void Workbdver::setNext(Workbdver *next_) {
		m_next = next_;
};

void Workbdver::handle(){
	if (checkVersion())
		doUpdate();
	if (m_next)
		m_next->handle();
}
