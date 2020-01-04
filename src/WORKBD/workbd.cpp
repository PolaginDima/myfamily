/*
 * workbd.cpp
 *
 *  Created on: 31.10.2019
 *      Author: papa
 */

#include "workbd.h"

//Workbd *Workbd::m_Instance = 0;

Workbd::Workbd(Workbdimp *bd):m_bd(bd){
	//выполним обновление
	Workbdupdate u(bd);//.executeUpdate();
	bd->connection();
}

Workbd::~Workbd(){
	delete m_bd;
}

bool Workbd::exec(const string &sql) const{
	return m_bd->exec(sql);
}

const int Workbd::LastId() const{
	return m_bd->getLastId();
}

const int Workbd::NextId(People *) const {
	return m_bd->getNextId(Workbdimp::TBL_PEOPLE);
}
