/*
 * workbdsqlie.h
 *
 *  Created on: 31.10.2019
 *      Author: papa
 */

/*
 * Функция sqlite3_reset(sqlite3_stmt *pStmt) вызывается для сброса подготовленного объекта оператора обратно в исходное
 * состояние, готовое к повторному выполнению. Любые переменные инструкции SQL, имеющие значения,
 * привязанные к ним с помощью API sqlite3_bind_* (), сохраняют свои значения.
 *
 * sqlite3_clear_bindings(sqlite3_stmt*) процедура для сброса всех параметров хоста в NULL
 *
 * Функция sqlite3_finalize(sqlite3_stmt *pStmt) вызывается для удаления подготовленного оператора.
 * Если последнее вычисление оператора не обнаружило ошибок или оператор никогда не был вычислен,
 * то sqlite3_finalize () возвращает SQLITE_OK. Если последнее вычисление операторов не удалось,
 * то sqlite3_finalize (S) возвращает соответствующий код ошибки или расширенный код ошибки.
 *
 * char *sqlite3_errmsg(sqlite3*) и sqlite3_errmsg 16 () возвращают текст на английском языке, описывающий ошибку,
 * как UTF-8 или UTF-16 соответственно. Память для хранения строки сообщения об ошибке управляется внутренне.
 * Приложение не должно беспокоиться об освобождении результата.
 * Однако строка ошибки может быть перезаписана или освобождена при последующих вызовах других функций интерфейса SQLite.
 *
 * Значения, возвращаемые int sqlite3_errcode(sqlite3 *db) и/или sqlite3_extended_errcode (),
 * могут изменяться при каждом вызове API. Кроме того, есть некоторые интерфейсы,
 * которые гарантированно никогда не изменят значение кода ошибки.
 * Интерфейсы, сохраняющие код ошибки, являются:
 * sqlite3_errcode()
 * sqlite3_extended_errcode()
 * sqlite3_errmsg()
 * sqlite3_errmsg 16()*/

#ifndef MY_FAMILY_SRC_WORKBDSQLITE_H_
#define MY_FAMILY_SRC_WORKBDSQLITE_H_

#include <stdio.h>
#include <sqlite3.h>
#include <iostream>//временно
#include "workbdimp.h"
#include "../DOP/globfunc.h"

using std::wcout;//временно

class Workbdsqlite:public Workbdimp{
	 char *err = 0;
	 const string m_db_name;
public:
	 Workbdsqlite(const string);

	 //Workbdsqlite();

	virtual ~Workbdsqlite() override;

	const int getLastId() override;

	const int getNextId(const int) override;

	void add(People *people) override;

	bool exec(const string &sql) const override;

	void openSQL(const string &sql) override;//выполнение запроса возвращающего данные

	void cleaningSQL() override;//сброс SQL запроса

	bool connection() const override;//соединение/создание с базой

	void close() const override;
};

#endif /* MY_FAMILY_SRC_WORKBDSQLITE_H_ */
