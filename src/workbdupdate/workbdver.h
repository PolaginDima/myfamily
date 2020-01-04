/*
 * workbdver.h
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#ifndef WORKBDUPDATE_WORKBDVER_H_
#define WORKBDUPDATE_WORKBDVER_H_

#include <cstdlib>  // for exit(), EXIT_FAILURE
#include "../WORKBD/workbdimp.h"
#include "../log/log_trace.h"

class Workbdver{
protected:
	Workbdver *m_next;
	Workbdimp *m_bd;
protected:
	virtual bool checkVersion() const = 0;
public:
	explicit Workbdver(Workbdimp *bd);
	explicit Workbdver(Workbdver &previouse_ver);

	virtual ~Workbdver(){};
	void setNext(Workbdver *next_ = nullptr);
	/*virtual */void handle();
	virtual void doUpdate() = 0;
};

/*Создаем начальное состояние БД*/
class Workbdver10: public Workbdver{
private:
	bool checkVersion() const override;
	void createStruct();
public:
	Workbdver10(Workbdimp *bd):Workbdver(bd){};
	Workbdver10(Workbdver &previouse_ver):Workbdver(previouse_ver){}
	~Workbdver10() override{LOG_TRACE();};
	//void handle() override;
	void doUpdate() override;
};

class Workbdver20: public Workbdver{
private:
	bool checkVersion() const override;
public:
	Workbdver20(Workbdimp *bd):Workbdver(bd){}
	Workbdver20(Workbdver &previouse_ver):Workbdver(previouse_ver){}
	~Workbdver20() override{LOG_TRACE();};
	//void handle() override;
	void doUpdate() override;
};

#endif /* WORKBDUPDATE_WORKBDVER_H_ */
