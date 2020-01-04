/*
 * globfunc.h
 *
 *  Created on: 26.09.2019
 *      Author: papa
 */

#ifndef MYFAMILY_OLD_SRC_GLOBFUNC_H_
#define MYFAMILY_OLD_SRC_GLOBFUNC_H_

//#include <iostream> // C++ IO
#include <locale>   // std::locale
#include <string>   // std::string, std::wstring

typedef std::codecvt_base::result res;
typedef std::codecvt<wchar_t, char, mbstate_t> codecvt_type; // internal, external, state

extern std::mbstate_t state;

std::codecvt_base::result toWstring (const std::string & str,
   const std::locale & loc, std::wstring & out);

std::codecvt_base::result fromWstring (const std::wstring & str,
   const std::locale & loc, std::string & out);

#endif /* MYFAMILY_OLD_SRC_GLOBFUNC_H_ */
