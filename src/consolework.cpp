/*
 * consolework.cpp
 *
 *  Created on: 17.12.2019
 *      Author: papa
 */

#include "consolework.h"
#include "log/log_trace.h"

static const string db_name = "test.dblite";//имя БД

#ifdef __linux__
char getche(){
	TerminalOpt term(true);
	char ch = getchar();
	//char ch = getc(stdin);
	return ch;
}
#endif

char getaChar(){
	char ch = getche();
	return ch;
}

/*char getaChar(){//эта функция ожидает Enter после ввода символа
	char ch = cin.get();
	cin.ignore(80,'\n');
	return ch;
}*/

void getaLine(string& inStr){
	char temp[21];
	cin.get(temp,20,'\n');
	cin.ignore(20,'\n');
	inStr = temp;
}

void clearDisplay(){
	//system("clear");
	for(size_t it = 1; it < 100; it++) std::wcout << '\n';std::wcout << std::endl;
}

void clearCin(){
	//char c;
	//while (!(std::cin >> c)){
		cin.clear();//на случай, если предыдущий ввод завершилдся ошибкой
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//}
}

void displayDataSource(DataSource<People, ERR> &ds){
	wcout << setw(int((123 + 12)/2)) << L"Список людей\n";
	wcout << setw(3) << L"№" << setw(3) << L"id" << setw(25) << L"Фамилия" << setw(25) << L"Имя"
			<< setw(25) << L"Отчество" << setw(5) << L"пол" << setw(10) << L"№ ошибки\n";
	for(auto it = 0; it < ds.count(); it++){
		ds.position(it);
		wcout << setw(3) << it << setw(3) << ds.current()->getId() << setw(25) << ds.current()->getFam() << setw(25) << ds.current()->getName()
				<<setw(25) << ds.current()->getOtch() << setw(5)
				<< /*std::setiosflags(std::ios::boolalpha) << lst.getByIndex(it)->isWomen() << '\n';*/((ds.position(it)->isWomen())?L"жен":L"муж")
				<< setw(10) << ds.validate(ds.current()).any()
				<< std::endl;
	}
	wcout << L"Всего людей: " << ds.count() << '\n' <<endl;
}

void mainDisplay(){
	LOG_TRACE();
	//LOG_TRACE_STRING("проверка");
	/*отобразим меню*/
	char key = 0;

	Application &app = theApp();
	return;
	//Workbdupdate(new Workbdsqlite(db_name)).executeUpdate();

	WorkbdA &bd = theApp().getbd();

	while (1){
		std::wcout.width(40);
		//std::wcout.fill(' ');
		std::wcout << L"ГЛАВНОЕ МЕНЮ\n";
		std::wcout << L"1 - список людей\n2 - список семей\n0 - выход\n\nвведите цифру и нажмите ENTER" << std::endl;
		//key = getaChar();
		std::cin >> key;
		if (key == '0') {
			break;
		}
		clearDisplay();
		executeAction(key);
	}
}

void executeAction(char &key){
	switch (key){
	case '1':{
		//clearCin();
		displayPeoples(cmdAddPeople);
		break;}
	case '2':{
		break;	}
	}
}

void displayPeoples(function<PeopleEditUI* (int depth, History *, DataSource<People, ERR> &, Application &)> cmdAdd){
	DataSource<People, ERR> l_dsp(l_sp);//интерфейс для взаимодействия с хранилищем
	char key;
	History *hist = new History();
	//Application *app = new Application();
	Application &app = theApp();

	while (key != '0'){
		displayDataSource(l_dsp);
		std::wcout << L"1 - Добавить		2 - Редактировать	3 - Удалить		0 - выход" << endl;
		//std::cin >> key;
		//clearCin();
		std::cin >> key;
		//key = getaChar();
		clearDisplay();
		switch (key){
		case '1':{
			PeopleEditUI *peui = cmdAdd(0, hist, l_dsp, app);
			//clearCin();
			addPeople(peui);
			break;
		}
		case '2':{
			break;
		}
		}
	}
	//getaChar();
	//cin.get();
	//clearDisplay();
}

void addPeople(PeopleEditUI* peui){
	while (1){
		InputPeople(peui->getModel());
		wcout << L"1 - Сохранить введенные данные\n2 - Отказаться" << endl;
		char key;// = getaChar();
		std::cin >> key;
		if (key == '1') {
			ERR err;
			err = peui->save();
			if (!err[ERRFATAL]) break;
		} else {
			peui->cancel();
			break;
		}
	}
}

void InputPeople(ModelPeople *model){
	clearDisplay();

	wcout << L"Ввод нового человека\n";
	clearCin();
	model->setFam(iInput(L"Введите фамилию: "));
	model->setName(iInput(L"Введите Имя: "));
	model->setOtch(iInput(L"Введите Отчество: "));
}

string iInput(wstring txt){
	wcout << txt << std::endl;
	string stmp;

	while (1){
		std::cin.unsetf(std::ios::skipws);
		std::cin >> stmp;
		if (std::cin.good()) break;
		wcout << txt << std::endl;
		clearCin();
	}
	clearCin();
	return stmp;
}
