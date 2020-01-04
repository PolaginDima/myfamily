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
//#include "WORKBD/workbd.h"
#include "workbdadapter.h"

using std::wcout;//временно
using std::vector;

namespace app{
/*ключевой класс который хранит и уничтожает необходимые для работы объекты*/
class Application{
	vector<People *> m_Peoples;
	WorkbdAdapter m_bd;
private:
	Application();
	Application(const Application&);
	Application &operator = (const Application &);
	~Application();
public:
	friend Application &theApp();
	WorkbdA &getbd();
	PeopleEditUI *makePEUI(int depth, DataSource<People, ERR> &, People *, History *);
};

/*функция позволяющая получить единственный экземпляр Application*/
Application &theApp();

}

#endif /* APPLICATION_H_ */
