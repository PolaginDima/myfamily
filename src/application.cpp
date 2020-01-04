/*
 * application.cpp
 *
 *  Created on: 19.11.2019
 *      Author: papa
 */

#include "application.h"

static const string db_name = "test.dblite";//имя БД

namespace app{
Application::Application()
:m_bd(new Workbdsqlite(db_name)){
}

Application::~Application(){
}

WorkbdA &Application::getbd(){
	return m_bd;
}

PeopleEditUI *Application::makePEUI(int depth, DataSource<People, ERR> &ds, People *people, History *hist){
	PeopleEditUI *l_peui = new PeopleEditUI(new ModelPeople(people), depth, hist);
	auto l_save = [&ds](ModelPeople *mp, int depth, History *hist)->ERR{
		ERR err = ds.validate(mp->getPeople());
		if (err[ERRFATAL]) return err;
		//выполняем и удаляем все команды в History для которых depth<=переданного depth

		if (!depth){
			hist->executeForDepth(depth);
			hist->deleteForDepth(depth);
		}

		return err;
	};
	l_peui->setSave(l_save);

	auto l_cancel = [](int depth, History *hist){
		hist->canceledForDepth(depth);
		hist->deleteForDepth(depth);
	};

	l_peui->setCancel(l_cancel);

	return l_peui;

}

Application &theApp(){
	static Application app;
	return app;
}
}
