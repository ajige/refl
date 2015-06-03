/*       
 *       Filename:  main.cpp
 *       Created:  2015年05月29日 15时19分56秒
 *       Author:  wushangqing@sogou-inc.com
 */

// reflection means get member from member name,
// call member function from member name and arguments.

#include "aclass.h"

int main()
{
  A aobj;
  Aref aref(aobj);

//void invoke(string funcname, A& obj, R& r)
  int bb = aref.invoke<int>("func");
  cout << bb << endl;

  int cc = aref.invoke<int, int>("secondfunc", 30);
  cout << cc << endl;

  int val = 100;
  aref.setMember<int>("aval", val);
  int dd = aref.getMember<int>("aval");
  cout << dd << endl;

  string zz = "hellozzz";
  aref.setMember<string>("astr", zz);
  
  string dstr = aref.getMember<string>("astr");
  cout << dstr << endl;

  int ary[50] = {0,1,2,3,4};
  aref.setMember<int[50], 50>("array", ary);

  int bry[50];
  aref.getMember<int[50], 50>("array", bry);
  cout << bry[0] << " " << bry[1] << " "<< endl;

  Z zobj;
  Zref zref(zobj);
  val = 110;
  zref.setMember<int>("mval", val);
  
  aref.setMember<Zref>("zz", zref);
  int newval = aref.getMember<Zref>("zz").getMember<int>("mval");
  cout << newval << endl;
}

