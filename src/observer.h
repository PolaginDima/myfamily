/*
 * observer.h
 *
 *  Created on: 27.11.2019
 *      Author: papa
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <list>
#include "DOP/defineerrors.h"

enum NOTIFYTYPE{CHECKREMOVEPEOPLE, REMOVEPEOPLE};

class Subject;

class ObServer{
public:
	virtual ~ObServer();
	virtual void update(Subject *, NOTIFYTYPE action, ERR &) = 0;
	virtual void update(Subject *, NOTIFYTYPE action) = 0;
};

class Subject{
	std::list<ObServer *> m_observers;
public:
	virtual ~Subject(){};
	virtual void attach(ObServer *);
	virtual void detach(ObServer *);
	virtual void Notify(NOTIFYTYPE action, ERR &);
	virtual void Notify(NOTIFYTYPE action);
protected:
	Subject(){};
};

#endif /* OBSERVER_H_ */
