#ifndef _REFL_EXCEPTION_H_
#define _REFL_EXCEPTION_H_

#include <exception>
#include <string>

using std::exception;
using std::string;

class RException: public exception
{
public:
	RException(string message)
	{
       msg = message;
	}
	string what()
	{
        return msg;
	}
	
	string msg;
};

#endif

