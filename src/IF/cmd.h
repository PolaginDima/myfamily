/*
 * cmd.h
 *
 *  Created on: 19.11.2019
 *      Author: papa
 */

#ifndef CMD_H_
#define CMD_H_

#include <iostream>//временно
#include <bitset>
#include <assert.h>
//#include <utility>
#include "datasource.h"
#include "../DOP/defineerrors.h"
#include "../WORKBD/workbd.h"

using std::wcout;//временно
using std::cout;//временно

class Cmd{
public:
	enum class Action{EXECUTE, UNDO};
	Cmd(){};
	virtual ~Cmd(){};
	virtual void operator()() = 0;
};

template <class T>
class CmdAdd: public Cmd{
	T *m_Cache;

	DataSource<T, ERR> &m_ds;
	Workbd &m_bd;
	Action m_action;
public:
	CmdAdd(T *t, DataSource<T, ERR> &ds, Workbd &bd, Action act = Action::EXECUTE)
:m_Cache(t), m_ds(ds),m_bd(bd), m_action(act){
		wcout << L"Конструктор CmdAdd " << (long)this << std::endl;
	}

	CmdAdd(const CmdAdd &f)//конструктор копирования
	:m_Cache(f.m_Cache), m_ds(f.m_ds),m_bd(f.m_bd), m_action(f.m_action){
		wcout << L"Конструктор копирования CmdAdd " << (long)this << std::endl;
	}

	CmdAdd(CmdAdd &&f)//конструктор переноса
	:m_Cache(f.m_Cache), m_ds(f.m_ds),m_bd(f.m_bd), m_action(f.m_action){
		wcout << L"Конструктор переноса CmdAdd " << (long)this << std::endl;
	}

	~CmdAdd()override {
		wcout << L"Деструктор CmdAdd " << (long)this << std::endl;
	};

	/*CmdAdd &operator=(const CmdAdd &cmd){
		wcout << L"Присваивание копированием CmdAdd " << (long)this << std::endl;
		if (this == &cmd)
			return *this;
		this->m_Cache = cmd.m_Cache;
		this->m_bd = cmd.m_bd;
		this->m_ds = cmd.m_ds;
		this->m_action = cmd.m_action;
		return *this;
	}*/

	/*CmdAdd &operator=(CmdAdd &&cmd){
		wcout << L"Присваивание переносом CmdAdd " << (long)this << std::endl;
		if (this == &cmd)
			return *this;
		this->m_Cache = cmd.m_Cache;
		this->m_bd = cmd.m_bd;
		this->m_ds = cmd.m_ds;
		this->m_action = cmd.m_action;
		cmd.m_Cache = nullptr;
		cmd.m_bd = nullptr;
		cmd.m_ds = nullptr;
		return *this;
	}*/

	void operator ()() override{
		if (m_action == Action::EXECUTE){
			m_Cache->setId(m_bd.getNextId(m_Cache));
			m_bd.add(m_Cache);
		} else{
			m_ds.removeLocal(m_Cache);
			delete m_Cache;
			m_Cache = nullptr;
		}

	};
};

template <class T>
class CmdEdit: public Cmd{
	T *m_Cache;
	T *m_Current;
	DataSource<T, ERR> &m_ds;
	Workbd &m_bd;
	Action m_action;
public:
	CmdEdit(T *t, DataSource<T, ERR> &ds, Workbd &bd, Action act = Action::EXECUTE)
:m_Cache(new People(*t)), m_Current(t), m_ds(ds),m_bd(bd), m_action(act){
		wcout << L"Конструктор CmdEdit " << (long)this << std::endl;
	}

	CmdEdit(const CmdEdit &f)//конструктор копирования
	:m_Cache(f.m_Cache), m_Current(f.m_Current), m_ds(f.m_ds),m_bd(f.m_bd), m_action(f.m_action){
		wcout << L"Конструктор копирования CmdEdit " << (long)this << std::endl;
	}

	CmdEdit(CmdEdit &&f)//конструктор переноса
	:m_Cache(f.m_Cache), m_Current(f.m_Current), m_ds(f.m_ds),m_bd(f.m_bd), m_action(f.m_action){
		wcout << L"Конструктор переноса CmdEdit " << (long)this << std::endl;
	}

	~CmdEdit()override {
		wcout << L"Деструктор CmdEdit " << (long)this << std::endl;
	};

	void operator ()() override{
		if (m_action == Action::EXECUTE){
			m_bd.update(m_Current, m_Cache);
		} else{
			*m_Current = static_cast<People &&> (*m_Cache);//принудительно вызываем присваивание с переносом с помощью static_cast
			delete m_Cache;
		}

	};
};

template <class T>
class CmdDelete: public Cmd{
	T *m_Cache;
	T *m_Current;
	DataSource<T, ERR> &m_ds;
	Workbd &m_bd;
	Action m_action;
public:
	CmdDelete(DataSource<T, ERR> &ds, Workbd &bd, Action act = Action::EXECUTE)
:m_Cache(new People(*(ds.current()))), m_Current(ds.current()), m_ds(ds),m_bd(bd), m_action(act){
		wcout << L"Конструктор CmdDelete " << (long)this << std::endl;
	}

	CmdDelete(const CmdDelete &f)//конструктор копирования
	:m_Cache(f.m_Cache), m_Current(f.m_Current), m_ds(f.m_ds),m_bd(f.m_bd), m_action(f.m_action){
		wcout << L"Конструктор копирования CmdDelete " << (long)this << std::endl;
	}

	CmdDelete(CmdDelete &&f)//конструктор переноса
	:m_Cache(f.m_Cache), m_Current(f.m_Current), m_ds(f.m_ds),m_bd(f.m_bd), m_action(f.m_action){
		wcout << L"Конструктор переноса CmdDelete " << (long)this << std::endl;
	}

	~CmdDelete()override {
		wcout << L"Деструктор CmdDelete " << (long)this << std::endl;
	};

	void operator ()() override{
		if (m_action == Action::EXECUTE){
			this->m_ds.removeFull(m_Current);
			m_bd.remove(m_Current);//удалим из базы
		} else{
			*m_Current = static_cast<People &&> (*m_Cache);//принудительно вызываем присваивание с переносом с помощью static_cast
			delete m_Cache;
			m_ds.add(m_Current);
		}

	};
};

#endif /* CMD_H_ */
