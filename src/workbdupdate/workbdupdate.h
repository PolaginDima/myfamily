/*
 * workbdupdate.h
 *
 *  Created on: 26.12.2019
 *      Author: papa
 */

#ifndef WORKBDUPDATE_WORKBDUPDATE_H_
#define WORKBDUPDATE_WORKBDUPDATE_H_

#include <cstdlib>// for exit(), EXIT_FAILURE
#include "workbdver.h"


class Workbdupdate{
	Workbdimp *m_bd;
public:
	Workbdupdate(Workbdimp *bd);
};



#endif /* WORKBDUPDATE_WORKBDUPDATE_H_ */
