/*
 * test.cpp
 *
 *  Created on: 18.11.2019
 *      Author: papa
 */

#include "../tests/test.h"

const int nPeople = 5;//сколько людей создавать для тестирования
const int nFamily = 3;//сколько семей создавать для тестирования

int getIndex(){static int index = 0;return ++index;}

wstring &getRandomWString(char len){
	static wstring word;
	toWstring(getRandomString(), std::locale(), word);
	return word;
}

void init_rand(){
	static bool flag = false;
	if (flag) return;
	srand(time(0));
	flag = true;
}//инициализируем датчик случайных чисел

string &getRandomString(char len){
	static string word;
	init_rand();
	len = (!len)?(rand() % 30):len;
	int s;
	wstring wordw;
	wordw = L"";
	for(auto it = 1; it <= len; it++){
		s = rand() % 3;
		switch (s){
		case 0://русские буквы
			//s = 1040 + rand() % 64;//получим случайное число от 1040 до 1103
			//wordw += wchar_t(s);
			break;
		case 1://английские буквы
			if (rand() % 2)
				s = 65 + rand() % 26;//Большие буквы
			else
				s = 97 + rand() % 16;//Большие буквы
			wordw += wchar_t(s);
			break;
		case 2://цифры
			s = 48 + rand() % 10;//получим случайное число от 48 до 59
			wordw += wchar_t(s);
			break;
		}
	}
	fromWstring(wordw, std::locale(), word);
	return word;
}

People *createRNDPeople(){
	People *p = new People;
	p->setId(getIndex());
	fillRNDPeople(p);
	return p;
}

void fillRNDPeople(People *p){
	p->setFam(getRandomWString(20));
	p->setName(getRandomWString(20));
	p->setOtch(getRandomWString(20));
	p->setWomen(rand() & 2);
}

void fillRNDModelPeople(ModelPeople *mp){
	mp->setFam(getRandomString(20));
	mp->setName(getRandomString(20));
	mp->setOtch(getRandomString(20));
	mp->setWomen(rand() & 2);
}

void displayPeople(const People *p){
	wcout<<L"id = "<<p->getId()<<"\n"
			<<L"Фамилия = "<<p->getFam() << "\n"
			<<L"Имя = "<<p->getName() << "\n"
			<<L"Отчество = "<<p->getOtch() << "\n"
			<<L"пол = "<<((p->isWomen())?L"женский\n":L"мужской\n")
			<<endl;
}

void test(){
	//testPeople();
	//testDataSource();
	//testModelPeople();
	//testCmdAddSaveUndo();
	//testCmdEditSaveUndo();
	//testCmdDelete();
	testCmdDepth();
	//testAllCmd();
}

void testPeople(){
	for(auto it = 1; it <= nPeople; it++){
		People *p = createRNDPeople();
		//People *p2 = p->clone();
		People *p2 = new People(*p);
		wcout << "Pointer = " << (long)p << '\n';
		displayPeople(p);
		wcout << "Clone\n";
		wcout << "Pointer = " << (long)p2 << '\n';
		displayPeople(p2);
		wcout << "Validate: " << p2->validate() << '\n';
		delete p;
		delete p2;
		wcout << '\n';
	}
}

void testDataSource(){
	vector<People *> l_sp;//хранилище людей
	for(auto it = 1; it <= nPeople; it++) l_sp.push_back(createRNDPeople());

	DataSource<People, ERR> l_dsp(l_sp);
	displayDataSource(l_dsp);

	for(auto p:l_sp) delete p;
	l_sp.erase(l_sp.begin(), l_sp.end());
	displayDataSource(l_dsp);

	for (auto it = 1; it <= nPeople; it++) l_dsp.add(createRNDPeople());
	displayDataSource(l_dsp);
}

void testModelPeople(){
	People *p = createRNDPeople();
	ModelPeople *mp = new ModelPeople(p);
	wcout << endl;
	cout << mp->Fam() << '\n';
	cout << mp->Name() << '\n';
	cout << mp->Otch() << '\n';
	cout << ((mp->isWomen())?("муж"):("жен")) << '\n';
	cout << endl;
}

void testCmdAddSaveUndo(){
	Application &app = app::theApp();
	vector<People *> l_sp;//хранилище людей
	DataSource<People, ERR> l_dsp(l_sp);
	History *hist = new History();
	int total = l_dsp.count();

	//создадим команду для вызова PEUI для добавления
	function<PeopleEditUI* (int depth, History *)> cmdAdd = [&l_dsp, &app](int depth, History *hist)->PeopleEditUI*{
		People *p = new People();

		l_dsp.add(p);

		hist->add({CmdAdd<People>(p, l_dsp, theApp().getbd()),
				CmdAdd<People>(p, l_dsp, theApp().getbd(), CmdAdd<People>::Action::UNDO),
				0});
		return app.makePEUI(depth, l_dsp, p, hist);
	};

	wcout <<L"\nПроверяем cmdAdd()" << std::endl;

	PeopleEditUI *peui = cmdAdd(0, hist);

	wcout << L"\nПроверяем кнопку сохранить\n" << std::endl;

	while (1){
		fillRNDModelPeople(peui->getModel());//заполняем
		{//кнопка сохранить
			ERR err = peui->save();//пробуем сохранить
			if (!(err[ERRFATAL])){//Если критических ошибок нет
				//выводим если есть и если нужно не критические ошибки
				if (err.test(ERRPEOPLENAME))
					wcout << L"Ошибка имени\n";
				break;
			}
		}
	}

	displayPeople(peui->getModel()->getPeople());
	displayDataSource(l_dsp);
	assert(l_dsp.count() == total + 1);
	total = l_dsp.count();

	wcout <<L"Выполняем cmdAdd()\n";

	peui = cmdAdd(0, hist);
	fillRNDModelPeople(peui->getModel());
	displayDataSource(l_dsp);
	assert(l_dsp.count() == total + 1);

	wcout << L"Проверяем кнопку отменить\n";

	{//кнопка отменить
		peui->cancel();
	}
	assert(l_dsp.count() == total);
	displayDataSource(l_dsp);

}

void testCmdEditSaveUndo(){
	Application &app = theApp();
	//Application *app = new Application();
	vector<People *> l_sp;//хранилище людей
	for(auto it = 1; it <= nPeople; it++) {
		People *p = createRNDPeople();
		while (1){
			ERR err = p->validate();
			if (!err[ERRFATAL])
				break;
			fillRNDPeople(p);
		}
		l_sp.push_back(p);//заполним данными
	}
	DataSource<People, ERR> l_dsp(l_sp);
	History *hist = new History();
	//int total = l_dsp.count();

	//создадим команду для вызова PEUI для редактирования
	function<PeopleEditUI* (int depth, History *)> cmdEdit = [&l_dsp, &app](int depth, History *hist)->PeopleEditUI*{
		People *p = l_dsp.current();

		hist->add({CmdEdit<People>(p, l_dsp, theApp().getbd()),
			CmdEdit<People>(p, l_dsp, theApp().getbd(), CmdAdd<People>::Action::UNDO),
			0});

		return app.makePEUI(depth, l_dsp, p, hist);
	};

	displayDataSource(l_dsp);

	wcout <<L"\nПроверяем cmdEdit()\n";

	l_dsp.position(rand() % (l_dsp.count()));//встанем в случайную позицию
	wcout <<L"\nРедактируемый человек\n" << l_dsp.position() << std::endl;
	PeopleEditUI *peui = cmdEdit(0, hist);
	displayPeople(peui->getModel()->getPeople());

	wcout << L"Проверяем кнопку сохранить\n" << std::endl;

	while (1){
		fillRNDModelPeople(peui->getModel());//заполняем
		displayPeople(peui->getModel()->getPeople());
		{//кнопка сохранить
			ERR err = peui->save();//пробуем сохранить
			if (!(err[ERRFATAL])){//Если критических ошибок нет
				//выводим если есть и если нужно не критические ошибки
				if (err.test(ERRPEOPLENAME))
					wcout << L"Ошибка имени\n";
				break;
			}
		}
	}

	//displayPeople(peui->getModel()->getPeople());
	displayDataSource(l_dsp);

	l_dsp.position(rand() % (l_dsp.count()));//встанем в случайную позицию
	peui = cmdEdit(0, hist);
	wcout <<L"\nРедактируемый человек " << l_dsp.position() << "\n";
	displayPeople(peui->getModel()->getPeople());
	fillRNDModelPeople(peui->getModel());
	displayPeople(peui->getModel()->getPeople());
	wcout << L"Проверяем кнопку отменить\n" << std::endl;

	{//кнопка отменить
		peui->cancel();
	}

	//displayPeople(peui->getModel()->getPeople());
	displayDataSource(l_dsp);

}

void testCmdDelete(){
	Application &app = theApp();
	//Application *app = new Application();
	vector<People *> l_sp;//хранилище людей
	for(auto it = 1; it <= nPeople; it++) {
		People *p = createRNDPeople();
		while (1){
			ERR err = p->validate();
			if (!err[ERRFATAL])
				break;
			fillRNDPeople(p);
		}
		l_sp.push_back(p);//заполним данными
		}
	DataSource<People, ERR> l_dsp(l_sp);

	int l_total = l_dsp.count();

	History *hist = new History();
	displayDataSource(l_dsp);

	//создадим команду для удаления
	function<void (int depth, History *, ERR &)> cmdDelete = [&l_dsp, &app](int depth, History *hist, ERR &err){

		l_dsp.controlOfRemove(l_dsp.current(), err);
		if (err == ERRFATAL)
			return err;

		if (!depth){
			CmdDelete<People>(l_dsp, theApp().getbd())();
			return err;
		}

		l_dsp.removeLocal(l_dsp.current());
		hist->add({CmdDelete<People>(l_dsp, theApp().getbd()),
			CmdDelete<People>(l_dsp, theApp().getbd(), CmdDelete<People>::Action::UNDO),
			0});
		return err;
	};

	wcout <<L"\nПроверяем cmdDelete()\n";

	l_dsp.position(rand() % (l_dsp.count()));//встанем в случайную позицию

	wcout << L"Будем удалять People id = " << l_dsp.current()->getId() << std::endl;

	ERR err;

	cmdDelete(0, hist, err);

	if (err == ERRFATAL){
		assert(l_dsp.count() == l_total);
		wcout << L"ошибка удаления" << std::endl;
	}
	assert(l_dsp.count() == l_total - 1);
	displayDataSource(l_dsp);
}
/*
 * Проверка вложенных команд
 * на применение и отмену*/
void testCmdDepth(){
	Application &app = theApp();
	//Application *app = new Application();
	vector<People *> l_sp;//хранилище людей
	DataSource<People, ERR> l_dsp(l_sp);
	History *hist = new History();

	//создадим команду для вызова PEUI для добавления
	function<PeopleEditUI* (int depth, History *)> cmdAdd = [&l_dsp, &app](int depth, History *hist)->PeopleEditUI*{
		People *p = new People();

		l_dsp.add(p);

		hist->add({CmdAdd<People>(p, l_dsp, theApp().getbd()),
			CmdAdd<People>(p, l_dsp, theApp().getbd(), CmdAdd<People>::Action::UNDO),
			depth});
		return app.makePEUI(depth, l_dsp, p, hist);
	};

	PeopleEditUI *peui1 = cmdAdd(0, hist);//добавили
	PeopleEditUI *peui2 = cmdAdd(1, hist);//тут как будто внутри еще добавили

	while (1){
		fillRNDModelPeople(peui2->getModel());//заполняем
		{//кнопка сохранить
			ERR err = peui2->save();//пробуем сохранить
			if (!(err[ERRFATAL])){//Если критических ошибок нет
				//выводим если есть и если нужно не критические ошибки
				if (err.test(ERRPEOPLENAME))
					wcout << L"Ошибка имени\n";
				break;
			}
		}
	}

	while (1){
			fillRNDModelPeople(peui1->getModel());//заполняем
			{//кнопка сохранить
				ERR err = peui1->save();//пробуем сохранить
				if (!(err[ERRFATAL])){//Если критических ошибок нет
					//выводим если есть и если нужно не критические ошибки
					if (err.test(ERRPEOPLENAME))
						wcout << L"Ошибка имени\n";
					break;
				}
			}
		}

	assert(l_dsp.count() == 2);

	peui1 = cmdAdd(0, hist);//добавили
	peui2 = cmdAdd(1, hist);//тут как будто внутри еще добавили

	{//кнопка отменить
		peui2->cancel();
	}

	while (1){
		fillRNDModelPeople(peui1->getModel());//заполняем
		{//кнопка сохранить
			ERR err = peui1->save();//пробуем сохранить
			if (!(err[ERRFATAL])){//Если критических ошибок нет
				//выводим если есть и если нужно не критические ошибки
				if (err.test(ERRPEOPLENAME))
					wcout << L"Ошибка имени\n";
				break;
			}
		}
	}

	assert(l_dsp.count() == 3);

}

/*void testAllCmd(){
	Application *app = new Application();
	vector<People *> l_sp;//хранилище людей
	DataSource<People, ERR> l_dsp(l_sp);
	History *hist = new History();

	//создадим команду для вызова PEUI для добавления
	function<PeopleEditUI* (int depth, History *)> cmdAdd = [&l_dsp, app](int depth, History *hist)->PeopleEditUI*{
		People *p = new People();

		l_dsp.add(p);

		hist->add({CmdAdd<People>(p, l_dsp, Workbd::instance()),
			CmdAdd<People>(p, l_dsp, Workbd::instance(), CmdAdd<People>::Action::UNDO),
			0});
		return app->makePEUI(depth, l_dsp, p, hist);
	};

	//создадим команду для вызова PEUI для редактирования
	function<PeopleEditUI* (int depth, History *)> cmdEdit = [&l_dsp, app](int depth, History *hist)->PeopleEditUI*{
		People *p = l_dsp.current();

		hist->add({CmdEdit<People>(p, l_dsp, Workbd::instance()),
			CmdEdit<People>(p, l_dsp, Workbd::instance(), CmdAdd<People>::Action::UNDO),
			0});

		return app->makePEUI(depth, l_dsp, p, hist);
	};

	//создадим команду для удаления
	function<void (int depth, History *)> cmdDelete = [&l_dsp, app](int depth, History *hist){
		l_dsp.remove(l_dsp.current());

		asdfadf
	};
}*/
