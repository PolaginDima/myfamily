/*
 * workbdver.h
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#ifndef WORKBDUPDATE_WORKBDVER_H_
#define WORKBDUPDATE_WORKBDVER_H_

#include "../WORKBD/workbdimp.h"

class Workbdver{
protected:
	Workbdver *m_next;
	Workbdimp *m_bd;
protected:
	virtual bool checkVersion() const = 0;
public:
	explicit Workbdver(Workbdimp *bd);
	explicit Workbdver(Workbdver *previouse_ver);

	virtual ~Workbdver(){/*std::wcout << L"Деструктор Workbdver" << std::endl;*/};
	void setNext(Workbdver *next_ = nullptr);
	virtual void handle() = 0;
};

/*Создаем начальное состояние БД*/
class Workbdver10: public Workbdver{
private:
	bool checkVersion() const override;
	void createStruct();
public:
	Workbdver10(Workbdimp *bd):Workbdver(bd){};
	Workbdver10(Workbdver *previouse_ver):Workbdver(previouse_ver){}
	~Workbdver10() override{};
	void handle() override;
};

class Workbdver20: public Workbdver{
private:
	bool checkVersion() const override;
public:
	Workbdver20(Workbdimp *bd):Workbdver(bd){}
	Workbdver20(Workbdver *previouse_ver):Workbdver(previouse_ver){}
	~Workbdver20() override{};
	void handle() override;
};

#endif /* WORKBDUPDATE_WORKBDVER_H_ */
