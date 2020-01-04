/*
 * datasource.h
 *
 *  Created on: 13.11.2019
 *      Author: papa
 */

#ifndef MY_FAMILYOLD2_SRC_DATASOURCE_H_
#define MY_FAMILYOLD2_SRC_DATASOURCE_H_

#include <algorithm>
#include <vector>
#include <bitset>
#include <iostream>//временно

using std::vector;
using std::bitset;
using std::wcout;//временно

/*Абстрактный класс, задающий интерфейс взаимодействия со списком данных*/
template <typename T, typename E>
class DataSource{
	vector<T *> &m_data;
	int m_pos;
public:
	DataSource(vector<T *> &spis):m_data(spis), m_pos(int())/*,m_current(nullptr)*/{
		wcout << L"Конструктор DataSource\n";
		if (spis.empty())
			m_pos = -1;
	};

	~DataSource(){
		wcout << L"Деструктор DataSource\n";
	};

	T *current(){
		return (m_data.empty())?nullptr:m_data[m_pos];
	};

	int position(){return m_pos;}

	T *position(int index){
		m_pos = index;
		return (m_data.empty())?nullptr:m_data[m_pos];
	};

	int count(){return m_data.size();};

	E validate(T *obj){
		return obj->validate();
	}

	void add(T *obj){
		m_data.push_back(obj);
		if (m_pos == -1)
			m_pos = 0;
	}

	void removeFull(T *t){
		//если все в порядке удаляем
		t->notifyRemove();//оповещение всех об удалении
		m_data.erase(std::remove(m_data.begin(), m_data.end(), t), m_data.end());
		if (m_data.empty())
			m_pos = -1;
		delete t;
	}

	void removeLocal(T *t){
		//если все в порядке удаляем
		m_data.erase(std::remove(m_data.begin(), m_data.end(), t), m_data.end());
		if (m_data.empty())
			m_pos = -1;
	}

	void controlOfRemove(T *t, E &err){
		//проверим корректность удаления
		t->controlOfRemove(err);
	}
};

#endif /* MY_FAMILYOLD2_SRC_DATASOURCE_H_ */
