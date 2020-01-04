/*
 * workbdupdate.cpp
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#include "workbdupdate.h"

Workbdupdate::Workbdupdate(Workbdimp *bd):m_bd(bd){
	if (bd->connection()){
		exit(EXIT_FAILURE);
		return;
	}

	//первая версия базы
	Workbdver10 v1(bd);

	//вторая версия базы
	Workbdver20 v2(v1);

	//Запускаем проверку и обновление БД(если нужно)
	v1.handle();
};

/*Workbdupdate::~Workbdupdate(){
	//delete m_bd;
}*/
