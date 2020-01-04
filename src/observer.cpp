/*
 * observer.cpp
 *
 *  Created on: 27.11.2019
 *      Author: papa
 */

#include "observer.h"

void Subject::attach(ObServer *o){
	this->m_observers.push_back(o);
}

void Subject::detach(ObServer *o){
	this->m_observers.remove(o);
}

void Subject::Notify(NOTIFYTYPE action, ERR &err){
	for(const auto &o:this->m_observers)
		o->update(this, action, err);
}

void Subject::Notify(NOTIFYTYPE action){
	for(const auto &o:this->m_observers)
		o->update(this, action);
}
