/*
 * people.h
 *
 *  Created on: 31.10.2019
 *      Author: Полагин Дмитрий Александрович
 *      Этот класс человека - члена семьи
 */

#ifndef MY_FAMILYOLD2_SRC_PEOPLE_H_
#define MY_FAMILYOLD2_SRC_PEOPLE_H_

#include <iostream>//временно
#include <string>
#include <bitset>
#include "DOP/defineerrors.h"
#include "observer.h"

using std::wcout;//временно
using std::wstring;
using std::bitset;

class People;

typedef People HUSB;
typedef People WIFE;
typedef People CHILD;
typedef People SPOUSE;

#define IDX_ID 				0
#define IDX_FAM				1
#define IDX_NAME			2
#define IDX_OTCH			3
#define IDX_WOMEN			4
#define IDX_FAMHUSB			5
const int count_fld = 5;
typedef bitset<count_fld> 	UPD_FLD;

class People:public Subject{
	int m_Id;
	wstring m_Fam;
	wstring m_FamHusb;
	wstring m_Name;
	wstring m_Otch;
	bool m_Women;
private:
	void copy(const People &);
public:
	People();
	People (const People &);//конструктор копирования
	People(People &&) = delete;//конструктор переноса
	People &operator=(const People &plp) = delete;//присваивание с копированием
	People &operator=(People &&);// = delete;//присваивание с переносом
	~People();
	//уникальный ID
	void setId(const int id) {m_Id = id;};
	const int getId() const;
	//Фамилия
	void setFam(const wstring &fam);
	const wstring &getFam() const;
	//Фамилия по мужу
	void setFamHusb(const wstring &famHusb);
	const wstring &getFamHusb() const;
	//Имя
	void setName(const wstring &name);
	const wstring &getName() const;
	//Отчество
	void setOtch(const wstring &otch);
	const wstring &getOtch() const;
	//устанавливаем пол
	void setWomen(const bool);
	const bool isWomen() const;
	//void setFamilyWhereParent(const Family);//семья где был родителем
	//void setFamilyWhereChild(const Family);//семья где был ребенком
	//HUSB *getHusb() const;//папа
	//WIFE *getWife() const;//мама
	//CHILD *getChildByIndex(int index);//ребенок под номером index
	//const int nChild() const;//количество детей
	//People *clone() const;
	const ERR validate() const;
	//ищет различные поля
	const UPD_FLD compare(const People *) const;
	//проверка корректности удаления
	void controlOfRemove(ERR &);
	/*оповещение об удалении
	 * заинтересованные объекты удаляют ссылки*/
	void notifyRemove();
};

#endif /* MY_FAMILYOLD2_SRC_PEOPLE_H_ */
