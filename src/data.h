#ifndef _REFL_DATA_H_
#define _REFL_DATA_H_

#include <typeinfo>
#include <map>
#include "exception"

class DataMember
{
 public:
 	DataMember(string name, const std::type_info& ti): _name(name), _tinfo(ti)
 	{}
	
 	string _name;
	const std::type_info& _tinfo;
};

template<typename T>
class DataMember_tmpl: public DataMember
{
  public:
  	DataMember_tmpl(string name, T& t) : DataMember(name, typeid(t)), val(t) 
  	{
	}
    	
	T& val;
};

class DataMemberMap
{
  public:
	
  	template<typename T>
  	T getMember(string memberName)
  	{
        // check type first, if type of memberName identical with T
        map<string, DataMember*>::iterator iter = _dmap.find(memberName);
        if( iter == _dmap.end())
			throw std::exception();
         
		 DataMember_tmpl<T>* tptr = static_cast<DataMember_tmpl<T>* >(iter->second);
		 
         if(  tptr->_tinfo != typeid(T))
		 	throw std::exception();
		 
		 return tptr->val;	
	}

	template<typename T>
	void setMember(string memberName, T t)
	{
        map<string, DataMember*>::iterator iter = _dmap.find(memberName);
        if( iter == _dmap.end())
			throw std::exception();

		DataMember_tmpl<T>* tptr = static_cast<DataMember_tmpl<T>* >(iter->second);
		
		if(  tptr->_tinfo != typeid(T))
		 	throw std::exception();
		 
		tptr->val = t;
	}

	/*for array element*/
	template<typename T, int num>
	void setMember(string memberName, T t)
	{
        map<string, DataMember*>::iterator iter = _dmap.find(memberName);
        if( iter == _dmap.end())
			throw std::exception();

		DataMember_tmpl<T>* tptr = static_cast<DataMember_tmpl<T>* >(iter->second);
		
		if(  tptr->_tinfo != typeid(T))
		 	throw std::exception();
		 
		// check length, omit here.
		for(size_t i = 0; i != num; i++)
		{
           tptr->val[i] = t[i];
		}
	}
	
	/*for array element*/
	template<typename T, int num>
	void getMember(string memberName, T t)
	{
        map<string, DataMember*>::iterator iter = _dmap.find(memberName);
        if( iter == _dmap.end())
			throw std::exception();

		DataMember_tmpl<T>* tptr = static_cast<DataMember_tmpl<T>* >(iter->second);
		
		if(  tptr->_tinfo != typeid(T))
		 	throw std::exception();
		 
		// check length, omit here.
		for(size_t i = 0; i != num; i++)
		{
            t[i] = tptr->val[i];
		}
	}
	
    map<string, DataMember*> _dmap; 	
};

#endif

