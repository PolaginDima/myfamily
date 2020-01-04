/*
 * peui.h
 *
 *  Created on: 19.11.2019
 *      Author: papa
 */

#ifndef PEUI_H_
#define PEUI_H_

#include <tr1/functional>
#include "../IF/model.h"
#include "../people.h"
#include "../IF/history.h"
#include <iostream>//временно

using std::wcout;//временно
using std::cout;//временно
using std::tr1::function;

typedef function<ERR (ModelPeople *, int depth, History *)> CMDSAVE;
typedef function<void(int depth, History *)> CMDCANCEL;

class PeopleEditUI{
	ModelPeople *m_mp;
	History *m_hist;
	int m_depth;
	CMDSAVE m_CmdSave;
	CMDCANCEL m_CmdCancel;
public:
	PeopleEditUI(ModelPeople *mp, int depth, History *hist = nullptr);
	~PeopleEditUI();

	void setSave(CMDSAVE vmd);

	void setCancel(CMDCANCEL);

	ERR save(){
		return m_CmdSave(m_mp, m_depth, m_hist);
	};

	void cancel(){
		m_CmdCancel(m_depth, m_hist);
	};

	ModelPeople *getModel(){return m_mp;}//временно для тестирования?
};

#endif /* PEUI_H_ */
