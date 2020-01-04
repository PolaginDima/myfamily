/*
 * globfunc.cpp
 *
 *  Created on: 26.09.2019
 *      Author: papa
 */

#include "globfunc.h"

std::mbstate_t state;

std::codecvt_base::result toWstring (const std::string & str,
   const std::locale & loc, std::wstring & out)
{
  const codecvt_type& cdcvt = std::use_facet<codecvt_type>(loc);
  std::codecvt_base::result r;

  wchar_t * wchars = new wchar_t [str.size () + 1];

  const char *in_next = 0;
  wchar_t *out_next = 0;

  r = cdcvt.in (state, str.c_str (), str.c_str () + str.size (), in_next,
                wchars, wchars + str.size () + 1, out_next);
  *out_next = '\0';
  out = wchars;

  delete [] wchars;

  return r;
}

std::codecvt_base::result fromWstring (const std::wstring & str,
   const std::locale & loc, std::string & out)
{
  const codecvt_type& cdcvt = std::use_facet<codecvt_type>(loc);
  std::codecvt_base::result r;

  const wchar_t *in_next = 0;
  char *out_next = 0;

  std::wstring::size_type len = str.size () << 2;

  char * chars = new char [len + 1];

  r = cdcvt.out (state, str.c_str (), str.c_str () + str.size (), in_next,
                 chars, chars + len, out_next);
  *out_next = '\0';
  out = chars;

  delete [] chars;

  return r;
}


