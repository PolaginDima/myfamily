/*
 * model.cpp
 *
 *  Created on: 19.11.2019
 *      Author: papa
 */

#include "model.h"

ModelPeople::ModelPeople(People *people):m_People(people){
	wcout << L"Конструктор ModelPeople\n";
}

ModelPeople::~ModelPeople(){
	wcout << L"Деструктор ModelPeople\n";
}

string ModelPeople::Fam() const{
	string l_s;
	fromWstring(m_People->getFam(), std::locale(), l_s);
	return l_s;
}

void ModelPeople::setFam(const string &fam){
	wstring l_ws;
	toWstring(fam, std::locale(), l_ws);
	m_People->setFam(l_ws);
}

string ModelPeople::Name() const{
	string l_s;
	fromWstring(m_People->getName(), std::locale(), l_s);
	return l_s;
}

void ModelPeople::setName(const string &name){
	wstring l_ws;
	toWstring(name, std::locale(), l_ws);
	m_People->setName(l_ws);
}

string ModelPeople::Otch() const{
	string l_s;
	fromWstring(m_People->getOtch(), std::locale(), l_s);
	return l_s;
}

void ModelPeople::setOtch(const string &otch){
	wstring l_ws;
	toWstring(otch, std::locale(), l_ws);
	m_People->setOtch(l_ws);
}

void ModelPeople::setWomen(const bool women){
	m_People->setWomen(women);
}
