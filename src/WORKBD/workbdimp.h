/*
 * workbdimp.h
 *
 *  Created on: 31.10.2019
 *      Author: papa
 */

#ifndef MY_FAMILYOLD2_SRC_WORKBDIMP_H_
#define MY_FAMILYOLD2_SRC_WORKBDIMP_H_

#include <string>
#include "../people.h"

using std::string;

/*Абстрактный класс, который определяет интерфейс работы с БД*/
class Workbdimp{
public:
	enum Tbl{TBL_PEOPLE = 0,TBL_FAMILY = 1};
	virtual ~Workbdimp(){};
	virtual const int getLastId() = 0;
	virtual const int getNextId(const int tbl) = 0;
	virtual void add(People *) = 0;
	virtual bool exec(const string &sql) const = 0;
	virtual void openSQL(const string &sql) = 0;
	virtual void cleaningSQL() = 0;
	virtual bool connection() const = 0;
	virtual void close() const = 0;
};

#endif /* MY_FAMILYOLD2_SRC_WORKBDIMP_H_ */
