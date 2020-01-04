/*
 * workbdupdate.cpp
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#include "workbdupdate.h"

Workbdupdate::Workbdupdate(Workbdimp *bd):m_bd(bd){
	assert(!bd->connection());
	if (bd->connection()){
		exit(EXIT_FAILURE);
		return;
	}

	//первая версия базы
	Workbdver *prev = new Workbdver10(bd);
	m_vers.push_back(prev);

	//вторая версия базы
	prev = new Workbdver20(prev);
	m_vers.push_back(prev);
};

Workbdupdate::~Workbdupdate(){
	delete m_bd;
}

void Workbdupdate::executeUpdate(){
	m_vers.front()->handle();
	//освободим память
	while (!m_vers.empty()){
		delete m_vers.front();
		m_vers.pop_front();
	}
}
