/*
 * people.cpp
 *
 *  Created on: 31.10.2019
 *      Author: papa
 */

#include "people.h"

People::People()
:m_Id(-1), m_Women(false){wcout<<L"Конструктор People" << std::endl;}

void People::copy(const People &people){
	this->m_Fam = people.m_Fam;
	this->m_Name = people.m_Name;
	this->m_Otch = people.m_Otch;
	this->m_Women = people.m_Women;
	this->m_Id = people.m_Id;
}

People::People(const People &people){
	wcout<<L"Конструктор копирования People" << std::endl;
	copy(people);
}

//People::People(People &&people){}

/*People &People::operator =(const People &people){
	if (this == &people)
		return *this;
	copy(people);
	return *this;
}*/

People &People::operator =(People &&people){
	if (this == &people)
		return *this;
	//освобождаем/обнуляем ресурсы this

	//переносим данные
	this->m_Fam = people.m_Fam;
	this->m_FamHusb = people.m_FamHusb;
	this->m_Name = people.m_Name;
	this->m_Otch = people.m_Otch;
	this->m_Women = people.m_Women;
	this->m_Id = people.m_Id;
	//освобождаем/обнуляем ресурсы people
	//people.m_Fam = nullptr;
	//people.m_FamHusb = nullptr;
	//people.m_Name = nullptr;
	//people.m_Otch = nullptr;
	return *this;
}

People::~People(){wcout<<L"Деструктор People ID=" << m_Id << std::endl;}

const int People::getId() const{return m_Id;}

void People::setFam(const wstring &fam){m_Fam = fam;}

const wstring &People::getFam() const{return m_Fam;}

void People::setFamHusb(const wstring &fam){m_FamHusb = fam;}

const wstring &People::getFamHusb() const{return m_FamHusb;}

void People::setName(const wstring &name){m_Name= name;}

const wstring &People::getName() const{return m_Name;}

void People::setOtch(const wstring &otch){m_Otch= otch;}

const wstring &People::getOtch() const{return m_Otch;}

void People::setWomen(const bool women){m_Women= women;}

const bool People::isWomen() const{return m_Women;}

/*People *People::clone() const{
	return new People(*this);
}*/

const ERR People::validate() const{
	bitset<ERRCOUNT> b;
	if (m_Fam.size() < 2) b.set(ERRPEOPLEFAM);
	if (m_Name.size() < 2) b.set(ERRPEOPLENAME);
	if (b[ERRPEOPLEFAM]||b[ERRPEOPLENAME]) b.set(ERRFATAL);
	return b;
}

const UPD_FLD People::compare(const People *people) const{
	UPD_FLD b;
	b[IDX_ID] = (m_Id != people->getId())?1:0;
	b[IDX_FAM] = (m_Fam != people->getFam())?1:0;
	b[IDX_NAME] = (m_Name != people->getName())?1:0;
	b[IDX_OTCH] = (m_Otch != people->getOtch())?1:0;
	b[IDX_WOMEN] = (m_Women != people->isWomen())?1:0;
	b[IDX_FAMHUSB] = (m_FamHusb != people->getFamHusb())?1:0;
	return b;
}

void People::controlOfRemove(ERR &err){
	this->Notify(NOTIFYTYPE::CHECKREMOVEPEOPLE, err);
}

void People::notifyRemove(){
	this->Notify(NOTIFYTYPE::REMOVEPEOPLE);
}
