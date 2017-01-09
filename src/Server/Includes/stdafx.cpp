// stdafx.cpp : source file that includes just the standard includes
// RS3D.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.hpp"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file


/* Removes leading and trailing spaces from a string
*  i.e. converts "      Hello, world!   " into "Hello, world!"
*/
string fTrimString(string str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
		return str;
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}