/*
 * model.h
 *
 *  Created on: 19.11.2019
 *      Author: papa
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <string>
#include <iostream>//временно
#include "../people.h"
#include "../DOP/globfunc.h"

using std::wcout;//временно
using std::string;

class ModelPeople{
	People *m_People;
public:
	ModelPeople(People *);
	~ModelPeople();
	string Fam() const;
	void setFam(const string &);
	string Name() const;
	void setName(const string &);
	string Otch() const;
	void setOtch(const string &);
	bool isWomen() const {return m_People->isWomen();};
	void setWomen(const bool);
	People *getPeople(){return m_People;}
};

#endif /* MODEL_H_ */
