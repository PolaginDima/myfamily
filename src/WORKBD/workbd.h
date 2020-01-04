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
public:
	//static Workbd *m_Instance;
	explicit Workbd(Workbdimp *bd);
	//Workbd(const Workbd&);
	//Workbd &operator = (const Workbd &);
	virtual ~Workbd();
	bool exec(const string &sql) const;
	//Workbd(Workbdimp *bd);
	/*static Workbd &instance(){
		//static Workbd l_bd(new Workbdtemp);
		static Workbd l_bd(new Workbdsqlite("test.dblite"));
		return l_bd;
	}*/

	const int LastId() const;//получить последний вставленный ID

	const int NextId(People *) const;//получить следующий ID для таблицы Tbl
};

#endif /* MY_FAMILYOLD2_SRC_WORKBD_H_ */
