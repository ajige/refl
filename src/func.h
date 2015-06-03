/*
 * =====================================================================================
 *       Filename:  arefl.h
 *       Created:  2015年05月29日 14时32分45秒
 *       Author:  wushangqing@sogou-inc.com
 * =====================================================================================
 */
#ifndef _REFL_H_
#define _REFL_H_

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <map>
#include <exception>

using namespace std;

class Ret
{
};

template<typename T>
class Ret_tmpl: public Ret
{
 public:	
   T  val;
};

class Argument
{ 

};

template<typename T>
class Argument_tmpl: public Argument
{
 public:
 	Argument_tmpl(T src)
 	{
 	   val = src;
 	}
 	T val;
};

class Arguments : public vector<Argument*>
{
 public:
 	void addArgument(Argument* arg)
 	{
 	  push_back(arg);
 	}
};

typedef boost::function<void(Ret*, Arguments)> Func;

class MemberFunc
{ 
 public:  	
  MemberFunc(Func func)
  {
    _func = func;
  }
  
  template<typename R>
  R invoke(Arguments args)
  {
	 Ret* ret = new Ret_tmpl<R>;
	 _func(ret, args);
	 return static_cast<Ret_tmpl<R>*>(ret)->val;
  }
  Func _func;
};

class FuncMap
{
  public:
    template<typename R>
	R invoke(string funcName)
    {
	   map<string, MemberFunc>::iterator iter = _funcMap.find(funcName);
	   if( iter != _funcMap.end())
	   {
	       Arguments args;
           return iter->second.invoke<R>(args);
	   }
	   else
	   	throw exception();
    }
	
	template<typename R, typename A1>
	R invoke(string funcName, A1 a)
    {
	   map<string, MemberFunc>::iterator iter = _funcMap.find(funcName);
	   if( iter != _funcMap.end())
	   {
	       Arguments args;
	       Argument* arg = new Argument_tmpl<A1>(a);
		   args.push_back(arg);
           return iter->second.invoke<R>(args);
	   }
	   else
	   	throw exception();
    }
	
	/*todo: invoke with three arguments and more*/
	
    map<string, MemberFunc> _funcMap;
};

#endif

