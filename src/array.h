#ifndef _REFL_ARRAY_H_
#define _REFL_ARRAY_H_

#include "exception"

template<typename T, int size>
class Array
{
  public:
    int length() const
    {
      return size;
    }

	T& operator[](int index)
	{
      // if(index < 0 || index >= size)
	  // 	throw RException("index out of bound");

	   return val[index];
	}
	
  	T val[size];
    int num;
};

#endif

