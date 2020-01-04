/*
 * workbdupdate.h
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#ifndef WORKBDUPDATE_WORKBDUPDATE_H_
#define WORKBDUPDATE_WORKBDUPDATE_H_

#include <deque>
#include <assert.h>
#include <cstdlib>// for exit(), EXIT_FAILURE
#include "workbdver.h"


class Workbdupdate{
	Workbdimp *m_bd;
	std::deque<Workbdver *> m_vers;
public:
	Workbdupdate(Workbdimp *bd);

	~Workbdupdate();

	void executeUpdate();
};



#endif /* WORKBDUPDATE_WORKBDUPDATE_H_ */
