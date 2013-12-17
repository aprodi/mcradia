/* *********************************************************************
#
#
# Project:       Alpha
#
# Description:   coding of the DLL Functions 
#
# Author(s):     Oleg Chubar, Pascal Elleaume, Laurent Farvacque
#
# Original:	 May 2000
#
# 
# Copyright (c) 2000 by European Synchrotron Radiation Facility,
#                       Grenoble, France
#
#                       All Rights Reserved
#
#********************************************************************** */



#if defined _MSC_VER 
#pragma warning(disable : 4786) // to suppress annoying warning from STL
#include <map>
#include <strstream>
#include <iostream>
using namespace std;

#elif defined  __HP_aCC
#include <map>
#include <strstream.h>
#include <iostream.h>

#elif defined __MWERKS__
#include <map.h>
#include <strstream.h>
#include <iostream.h>

#else
#include <map>
#include <strstream>
#include <iostream>
using namespace std;
#endif


#include "AlpDllEntry.h"
#include "AlpError.h"
#include "DataBase.h"




//_____________________________________________
class object {
public:
object(){i=0;}
virtual void dump(ostream &os){os<<"Type object"<<endl;}
virtual ~object(){} // virtual destructor is necessary according to Oleg 
private:
int i;
};
//_____________________________________________

class object2 : public object  {
public:
object2(){j=0;}
virtual void dump(ostream &os){os<<"Type object2"<<endl;}
~object2(){}
private:
int j;
};

//_____________________________________________


database<object>  db;
ErrorWarning ErrWarn;	
ostrstream out;	

/* May be better to encapsulate in a class ?? */
void *pt;
int npt=0;

//______________________________________________
 const char * CALL getostream(){out<<"\0"; return out.str();} 
//______________________________________________
const char * CALL geterror(int er){return ErrWarn.geterror(er);}

int CALL geterrorsize(int *siz,int er){
*siz= ErrWarn.geterrorsize(er);
return OK;}

int CALL geterrortext(char*t,int er){
strcpy(t,ErrWarn.geterror(er));
return OK;}
//______________________________________________
const char * CALL getwarning(int er){
return ErrWarn.getwarning(er);}

int CALL getwarningsize(int *siz,int er){
*siz= ErrWarn.getwarningsize(er);
return OK;}

int CALL getwarningtext(char*t,int er){
strcpy(t,ErrWarn.getwarning(er));
return OK;}
//______________________________________
int CALL divi(double* ret,double x,double y ){
 if(y==0.) return 1;
*ret=x/y;
if(*ret<0) return -1; else return OK;
}

//______________________________________
int CALL getsize(int *v){
*v=npt;
return OK;}
//______________________________________
int CALL getdouble(double *v,int i){
//if (i<0 | i>= npt/sizeof(*v)) return -3; else 
if ((i<0) || (i>= npt/sizeof(*v))) return -3; else //OC

*v=((double*)pt)[i];
return OK;}
//______________________________________
int CALL clientstructure(st* s,double x, int i,char*p){
s->d+=x;
s->i+=i;
i=0;
//while (i<Nchar & p[i]!='\0')
while ((i<Nchar) && (p[i]!='\0')) //OC
{s->c[i]=p[i];i++;}
s->c[i]='\0';
return OK;}

//______________________________________
int CALL dllarray(int n,double y ){

if (n<0) return -2;  


if (npt!=0) delete[] (double*)pt;
pt=new double[n];
npt=n*sizeof(double);


for (int i=0;i<n;i++) ((double*)pt)[i]=y*i;



return OK;}
//______________________________________________
 int CALL clientarray(double*a,int n, double y ){
  
 
  int i;
  for (i=0;i<n;i++) a[i]=i*y;
  return OK;
  }
 
 //______________________________________________
  int CALL teste()
 {
/* Here are some example of use of the DataBase */ 

/* insert objects in database */
int e2=db.insert(new object);
int e1=db.insert(new object2);

/* recover Pointer<object> and execute a method  */
db.get(e2)->dump(out);
db.get(e1)->dump(out);

/* recover a particular pointer */
object2 *a = dynamic_cast<object2*>(db.get(e2).obj());
if (!a) out<<"Not of type object2" <<endl;
object *b = dynamic_cast<object*>(db.get(e2).obj());
if (!b) out<<" Not of type object" <<endl;

db.erase(e1);  /* erase one element */
db.erase(); /* erase all elements */

return OK;}
