/*
 * =====================================================================================
 *       Filename:  aclass.h
 *       Created:  2015年05月29日 14时30分05秒
 *       Author:  wushangqing@sogou-inc.com
 * =====================================================================================
 */
#ifndef _REFL_ACLASS_H_
#define _REFL_ACLASS_H_

#include "func.h"
#include "data.h"
#include <iostream>
#include <map>
#include "array.h"

using namespace std;

class Z
{
 public:
  int mval;
};

class Zref : public FuncMap, public DataMemberMap
{
  public:
   Zref(Z& zz)
   {
     zptr = &zz;
	 DataMember_tmpl<int>* dm = new DataMember_tmpl<int>("mval", zptr->mval);
	 _dmap.insert(std::make_pair(dm->_name, dm));
   }
      
   Z* zptr;
};

class A
{
 public:
  A()
  {}

  ~A()
  {}
  
  int func()
  {
    return 20;
    // return a;
  }
  int secondfunc(int cc)
  {
     return cc;
  }
  
  int aval; 
  string astr;
  int array[50];
  Z zz;
};



// typedef boost::function<void(Ret, Arguments)> Func;

class Aref : public FuncMap, public DataMemberMap
{
  public:
   Aref(A& aobj)
   {
     aptr = &aobj;
     MemberFunc func1(boost::bind(&Aref::func1, this, _1, _2));
	 MemberFunc func2(boost::bind(&Aref::func2, this,_1, _2));
	 _funcMap.insert(std::make_pair("func", func1));
	 _funcMap.insert(std::make_pair("secondfunc", func2));

	 DataMember_tmpl<int>* dm = new DataMember_tmpl<int>("aval", aptr->aval);
	 DataMember_tmpl<string>* dm2 = new DataMember_tmpl<string>("astr", aptr->astr);

     // DataMember_tmpl<Array<int, 50> >*dm3 = new DataMember_tmpl<Array<int, 50> >
     //        ("array", aptr->array);
     DataMember_tmpl<int[50] >* dm3 = new DataMember_tmpl<int[50] >("array", aptr->array);

	 //Todo here need change..
	 Zref *zref = new Zref(aptr->zz);
	 DataMember_tmpl<Zref>* dmz = new DataMember_tmpl<Zref>("zz", *zref);
	 
	 _dmap.insert(std::make_pair(dm->_name, dm));
	 _dmap.insert(std::make_pair(dm2->_name, dm2));
	 _dmap.insert(std::make_pair(dm3->_name, dm3));
	 _dmap.insert(std::make_pair(dmz->_name, dmz));
   }
   
   void func1(Ret* r, Arguments& args)
   {
      int a = aptr->func();
	  Ret_tmpl<int>* gg = static_cast<Ret_tmpl<int>* >(r);
	  gg->val = a;
   }

   void func2(Ret* r, Arguments& args)
   {
      Argument_tmpl<int>* arg = static_cast<Argument_tmpl<int>* >(args[0]);
      int a = aptr->secondfunc(arg->val);
	  Ret_tmpl<int> *gg = static_cast<Ret_tmpl<int>* >(r);
	  gg->val = a;
   }

   A* aptr;
};


#endif

/*
class Aref
{
 public:
  Aref()
  {
    _func0 = boost::bind(&A::func, _1);
	_func1 = boost::bind(&A::secondfunc, _1);
  }

  boost::function<int(A& )> _func0;
  boost::function<int(A& )> _func1;

  
  template<typename R>
  void invoke(string funcname, A& obj, R& r)
  {
     if(funcname == "func")
	 	r = _func0(obj);
	 else if (funcname == "secondfunc")
	 	r = _func1(obj);
  }
  
};
*/

