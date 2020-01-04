/*
 * test.h
 *
 *  Created on: 18.11.2019
 *      Author: papa
 */

#ifndef TESTS_TEST_H_
#define TESTS_TEST_H_

#include <cstdlib>//for exit(), EXIT_FAILURE, //for atoi(), atof(), for rand, srand
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <assert.h>
#include <tr1/functional>
#include <bitset>
#include "../DOP//globfunc.h"
#include "../people.h"
#include "../IF/datasource.h"
#include "../IF/model.h"
#include "../IF/cmd.h"
#include "../UI/peui.h"
#include "../IF/history.h"
#include "../application.h"
#include "../DOP/defineerrors.h"

using std::wcout;
using std::cout;
using std::wcin;
using std::wcerr;
using std::endl;
using std::setw;
using std::string;
using std::wstring;
using std::vector;
using std::tr1::function;
using std::bitset;

int getIndex();

wstring &getRandomWString(char len = 0);

string &getRandomString(char len = 0);

People *createRNDPeople();

void fillRNDPeople(People *p);

void displayPeople(const People *);

//void displayLisPeople(ListPeople &);

void displayDataSource(DataSource<People, ERR> &);

void test();

void testPeople();

void testDataSource();

void testModelPeople();

void testCmdAddSaveUndo();

void testCmdEditSaveUndo();

void testCmdDelete();

void testRNDCmd();

void testCmdDepth();

#endif /* TESTS_TEST_H_ */
