/*
 * consolework.h
 *
 *  Created on: 17.12.2019
 *      Author: papa
 */

#ifndef CONSOLEWORK_H_
#define CONSOLEWORK_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <tr1/functional>
//#include "tests/test.h"
#include "application.h"
//#include "people.h"

#include <stdio.h>
#ifdef _WIN32
	#include <conio.h>//для getch, getche
#elif __linux__
	#include <unistd.h>
	#include <termios.h>
#endif

using std::string;
using std::cin;
using std::wcout;
using std::setw;
using std::vector;
using app::theApp;
using app::Application;

#ifdef __linux__
struct TerminalOpt{//настройка терминала
	TerminalOpt(bool offEcho = false){
		//отключение буферизации терминалом
		termios new_settings;
		tcgetattr(0,&stored_settings);
		new_settings = stored_settings;
		if (offEcho)
			new_settings.c_lflag &= ~(ICANON|ECHO);
		else
			new_settings.c_lflag &= ~(ICANON);
		new_settings.c_cc[VTIME] = 0;
		new_settings.c_cc[VMIN] = 1;
		tcsetattr(0,TCSANOW,&new_settings);
	}
	~TerminalOpt() {
		tcsetattr(0,TCSANOW,&stored_settings);//возврат старых настроек
	}
	termios stored_settings;
};
#endif

#ifdef __linux__
	char getche();
#endif

char getaChar();//получение символа с клавиатуры
void getaLine(string &inStr);//получение строки текста
void clearDisplay();
void clearCin();

static vector<People *> l_sp;//хранилище людей

void displayDataSource(DataSource<People, ERR> &);

//команда для вызова для добавления человека
static function<PeopleEditUI* (int depth, History *, DataSource<People, ERR> &, Application &)> cmdAddPeople = [](int depth, History *hist, DataSource<People, ERR> &l_dsp, Application &app)->PeopleEditUI*{
	People *p = new People();

	 l_dsp.add(p);

	 hist->add({CmdAdd<People>(p, l_dsp, theApp().getbd()),
		 CmdAdd<People>(p, l_dsp, theApp().getbd(), CmdAdd<People>::Action::UNDO),
		 0});
	 return app.makePEUI(depth, l_dsp, p, hist);
};

void mainDisplay();
void executeAction(char &key);
void displayPeoples(function<PeopleEditUI* (int depth, History *, DataSource<People, ERR> &, Application &)>);
void addPeople(PeopleEditUI* peui);
void InputPeople(ModelPeople *model);
string iInput(wstring);

#endif /* CONSOLEWORK_H_ */
