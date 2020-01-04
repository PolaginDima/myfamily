/*
 * workbdsqlite.cpp
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#include "workbdsqlite.h"

static sqlite3 *db = 0; // хэндл объекта соединение к БД
//static /*const */string db_name = "test.dblite";//имя БД

/*Workbdsqlite::Workbdsqlite(){
	std::wcout << L"Конструктор Workbdsqlite" << std::endl;
}*/

Workbdsqlite::Workbdsqlite(const string db_name)
:m_db_name(db_name){
}

Workbdsqlite::~Workbdsqlite(){
	//закрываем соединение, если открыто
	if (db){
		sqlite3_close(db);
		db = 0;
	}
};

const int Workbdsqlite::getLastId(){return 0;}

const int Workbdsqlite::getNextId(const int){
	static int currentID = 0;
	return ++currentID;
}

void Workbdsqlite::add(People *people){
	wcout << L"save in BD People " << people->getId() <<L" " << people->getFam() << L" " << people->getName()
			<< L" " << people->getOtch() << '\n';
}

/*выполнение sql запроса*/
bool Workbdsqlite::exec(const string &sql) const{
	char *err = 0;

	if (sqlite3_exec(db, sql.c_str(), 0, 0, &err)){//;// выполняем _SQLquery
		fprintf(stderr, "Error SQL query: %s\n", err);
		sqlite3_free(err);
		return true;
	} return false;
};

void Workbdsqlite::openSQL(const string &sql){
	sqlite3_stmt *l_stmt;

	if (sqlite3_prepare_v2(db, sql.c_str(), -1, &l_stmt, 0)){
		fprintf(stderr, "Error executing SQL %s\n", sql.c_str());
	}
	if (!l_stmt){
		fprintf(stderr, "Could not prepare SQL statement %s\n", sql.c_str());
	}
}

void Workbdsqlite::cleaningSQL(){

}

bool Workbdsqlite::connection() const{
	int l_result;
	const char *l_msg = nullptr;

	//Создание или открытие БД
	l_result = sqlite3_open(m_db_name.c_str(), &db);
	if (l_result != SQLITE_OK){
		if (db){
			l_msg = sqlite3_errmsg(db);
			fprintf(stderr, "Error create DB %s: %s\n", m_db_name.c_str(),l_msg);
		}else{
			fprintf(stderr, "Error create DB %s: \nunknown error", m_db_name.c_str());
		}
		sqlite3_close(db);
		db = nullptr;
		if (l_msg) sqlite3_free((void *)l_msg);
	}
	return l_result;
}

void Workbdsqlite::close() const{
}
