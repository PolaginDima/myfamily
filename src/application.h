/*
 * application.h
 *
 *  Created on: 19.11.2019
 *      Author: papa
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>//временно
#include <vector>
#include "UI/peui.h"
#include "people.h"
#include "IF/model.h"
#include "IF/datasource.h"
#include "WORKBD/workbd.h"

using std::wcout;//временно
using std::vector;

class Application{
	vector<People *> m_Peoples;
public:
	Application();
	~Application();
	PeopleEditUI *makePEUI(int depth, DataSource<People, ERR> &, People *, History *);
};

#endif /* APPLICATION_H_ */
