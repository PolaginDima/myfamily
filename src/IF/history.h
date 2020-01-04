/*
 * history.h
 *
 *  Created on: 19.11.2019
 *      Author: papa
 */

#ifndef HISTORY_H_
#define HISTORY_H_

#include <vector>
#include <algorithm>
#include <tr1/functional>
#include <iostream>//временно
#include "cmd.h"

using std::vector;
using std::wcout;//временно
using std::cout;//временно
using std::tr1::tuple;
using std::tr1::function;

//typedef tuple<Cmd *, Cmd *, int> ACTION;
//typedef struct{Cmd *apply; Cmd *undo; int depth;} HISTDATA;
typedef struct{function<void ()> apply; function<void ()> undo; int depth;} HISTDATA;
typedef vector< HISTDATA > HIST;
typedef vector< HISTDATA >::iterator HISTIT;

class History{
	HIST m_Cmds;
public:
	History();
	~History();

	void add(HISTDATA);
	//void add(function<void ()>, function<void ()>, int);

	const int cout() const{return m_Cmds.size();}

	void deleteForDepth(int depth){
		m_Cmds.erase(remove_if(m_Cmds.begin(), m_Cmds.end(), [depth](HISTDATA &data){return data.depth >= depth;}),
				m_Cmds.end());
	}

	void executeForDepth(int depth){
		for_each(m_Cmds.begin(), m_Cmds.end(),[depth](HISTDATA &data){
			if (data.depth >= depth)
				data.apply();
		});
	}

	void canceledForDepth(int depth){
		for_each(m_Cmds.begin(), m_Cmds.end(),[depth](HISTDATA &data){
			if (data.depth >= depth){
				data.undo();
			}
		});
	}
};

#endif /* HISTORY_H_ */
