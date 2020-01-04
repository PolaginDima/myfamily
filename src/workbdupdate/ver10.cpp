/*
 * ver10.cpp
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#include "workbdver.h"

/*void Workbdver10::handle(){
	if (checkVersion())
		LOG_TRACE_STRING("Update to ver. 1.0\nCreate structure\n");
	if (m_next)
		m_next->handle();
}*/
void Workbdver10::doUpdate(){
	LOG_TRACE_STRING("Update to ver. 1.0\nCreate structure\n");
}


bool Workbdver10::checkVersion() const{
	/*таблица для хранения версии и др. вспомогательной информации
	 * создадим, если нет
	 * добавим строку с версией базы*/

	string lv_query = "CREATE TABLE IF NOT EXISTS [technical] "
			"([id] INTEGER primary key, "
			"[name] TEXT NOT NULL, "
			"[value] TEXT NOT NULL);"
			"INSERT INTO [technical](name, value) values('version', '1.0');";
	if (m_bd->exec(lv_query))
		exit(EXIT_FAILURE);
	lv_query = "SELECT [name], [value] FROM [technical] where name = 'version'";
	//m_bd->openSQL(lv_query);
	/*lv_query = "INSERT INTO [technical](name, value) values('version', '1.0')";
	res = m_bd->exec(lv_query);*/
	//if (!res) return res;

	return true;
}

void Workbdver10::createStruct(){

}
