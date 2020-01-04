/*
 * workbdtemp.h
 *
 *  Created on: 31.10.2019
 *      Author: papa
 */

#ifndef MY_FAMILYOLD2_SRC_WORKBDTEMP_H_
#define MY_FAMILYOLD2_SRC_WORKBDTEMP_H_

#include <iostream>//временно
#include "workbdimp.h"
#include "../DOP/globfunc.h"

using std::wcout;//временно

class Workbdtemp:public Workbdimp{
public:
	Workbdtemp(){}
	virtual ~Workbdtemp(){};

	const int getLastId() override {return 0;}

	const int getNextId(const int) override{
		static int currentID = 0;
		return ++currentID;
	}

	void add(People *people) override{
		wcout << L"save in BD People " << people->getId() <<L" " << people->getFam() << L" " << people->getName()
				<< L" " << people->getOtch() << '\n';
	}

	bool exec(const string &sql) const override{
		wstring wsql;
		toWstring(sql, std::locale(), wsql);
		wcout << wsql << std::endl;
		return true;
	}

	void openSQL(const string &sql) override{

	}

	void cleaningSQL() override{

	}

	bool connection() const override {return true;}
};

#endif /* MY_FAMILYOLD2_SRC_WORKBDTEMP_H_ */
