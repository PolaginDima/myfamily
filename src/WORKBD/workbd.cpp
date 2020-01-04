/*
 * workbd.cpp
 *
 *  Created on: 31.10.2019
 *      Author: papa
 */

#include "workbd.h"

//Workbd *Workbd::m_Instance = 0;

Workbd::Workbd(Workbdimp *bd):m_bd(bd){
	std::wcout<<L"Конструктор Workbbd\n";
	bd->connection();
}

Workbd::~Workbd(){
	delete m_bd;
	std::wcout<<L"Деструктор Workbbd\n";
}

const int Workbd::getLastId() const{
	return m_bd->getLastId();
}

const int Workbd::getNextId(People *) const {
	return m_bd->getNextId(Workbdimp::TBL_PEOPLE);
}

void Workbd::add(People *people){
	//m_bd->add(people);
	std::wstringstream wss;

	wss <<"insert into peoples(id, fam, name, otch) values(" << people->getId() << ", "
			<< people->getFam() << ", " << people->getName() << ", "
			<< people->getOtch() << ");";

	string sql;

	fromWstring(wss.str(), std::locale(), sql);
	m_bd->exec(sql);
}

void Workbd::update(People *current, People *old){
	UPD_FLD b = old->compare(current);
	/*if (b[IDX_ID])
		wcout << L"обновляем ID" << std::endl;*/
	if (b[IDX_FAM])
		wcout << L"обновляем Fam" << std::endl;
	if (b[IDX_NAME])
		wcout <<L"обновляем Name" << std::endl;
	if (b[IDX_OTCH])
		wcout <<L"обновляем Otch" << std::endl;
	if (b[IDX_WOMEN])
		wcout << L"обновляем m_Women" << std::endl;
	if (b[IDX_FAMHUSB])
		wcout << L"обновляем FamHusb" << std::endl;
}

void Workbd::remove(People *people){
	wcout << L"удаляем People id=" << people->getId() << L" из базы" << std::endl;
}
