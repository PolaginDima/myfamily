/*
 * defineerrors.h
 *
 *  Created on: 16.11.2019
 *      Author: papa
 */

#ifndef MY_FAMILYOLD2_SRC_DEFINEERRORS_H_
#define MY_FAMILYOLD2_SRC_DEFINEERRORS_H_

#include <bitset>

//числовые значения ошибок для People
#define ERRPEOPLEFAM 	0//некорректная фамилия
#define ERRPEOPLENAME 	1//некорректное имя
#define ERRPEOPLEOTCH 	2//некорректное отчество
#define ERRPEOPLEDTB	3//некорректная дата рождения
#define ERRPEOPLEDTD	4//некорректная дата смерти
#define ERRPEOPLEDTBDTD	5//дата рождения позже даты смерти

//числовые значения ошибок для списка People
#define ERRDOUBLEPEOPLE	6

//не позволительная ошибка для сохранения
#define ERRFATAL		7

//максимальное значение ошибки
#define ERRMAX			7

//количество вариантов ошибок
#define ERRCOUNT		ERRMAX+1

//возвращаемые ошибки
typedef std::bitset<ERRCOUNT>	ERR;

#endif /* MY_FAMILYOLD2_SRC_DEFINEERRORS_H_ */
