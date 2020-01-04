/*
 * workbd.h
 *
 *  Created on: 31.10.2019
 *      Author: papa
 */

#ifndef MY_FAMILYOLD2_SRC_WORKBD_H_
#define MY_FAMILYOLD2_SRC_WORKBD_H_

#include <iostream>
#include <sstream>
//#include "workbdimp.h"
#include "../workbdupdate/workbdupdate.h"
#include "workbdtemp.h"
#include "workbdsqlite.h"
#include "../people.h"

class Workbd{
private:
	Workbdimp *m_bd;//класс реализующий взаимодействие с БД(SQLite, Firebird, PostgreeSQL)
	//static Workbd *m_Instance;
	Workbd(Workbdimp *bd);
	Workbd(const Workbd&);
	Workbd &operator = (const Workbd &);
	~Workbd();
public:
	//Workbd(Workbdimp *bd);
	static Workbd &instance(){
		//static Workbd l_bd(new Workbdtemp);
		static Workbd l_bd(new Workbdsqlite("test.dblite"));
		return l_bd;
	}

	const int getLastId() const;//получить последний вставленный ID

	const int getNextId(People *) const;//получить следующий ID для таблицы Tbl

	void add(People *people);//сохранить объект в базе

	void update(People *currnet, People *old);

	void remove(People *people);//удалить объект из базы
};

#endif /* MY_FAMILYOLD2_SRC_WORKBD_H_ */
