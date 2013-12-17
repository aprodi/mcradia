/* *********************************************************************
#
#
# Project:       Alpha
#
# Description:   definition of the DLL Functions 
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

/**@name	Introduction

- The Goal of the Alpha Project is to provide a template of DLL/Sharedlibrary interface
 portable between platforms  (PowerMac, Windows 9x/NT, Linux, Unix..). Such a DLL interface
 greately simplifies the interfacing of an application to existing commercial packages 
 (MatLoab, Mathematica, VBA, Igor Pro, ...) or public domain (Python, Lua, TCL/TK,..).
 
 - An important  domain of application of Alpha is the scientific computing  for which a 
 scripting & graphing environment is essential. Very complete an sophisticated graphing 
 and scripting environment are available commercially and we believe that it would be a 
 mistake for the scientist developing a scientific software to also develop such an environment.
 The developper writes a DLL and one small size interface to whichever environment he prefers. 
 The future writing of an interface to an other environment is a small tasks which can be performed
  by someon who does not know the detail scientific content  of the application. Obviously, the
  developper must documents all public functions made available at the interface. 
  
  - Alpha is written in C++  and compile on
  CodeWarrior (PowerMac and WIndows), Visual C++ (Windows), aCC (HPUX)  
  gcc (Linux, all Unix). In order to accep the largest number of possible clients, 
  the  DLL interface is written in C . In addition Alpha provides two simple template classes
 of a simple container and autoreferencing pointers which greately simplified the memory 
 management. Any comment on this project is welcome. Alpha also presents a few example of interfaces 
 (C,C++, Mathematica, Matlab and VBA ). 
 
 */
 /** @name	Remarks

- It is important to avoid any memeory leak. Any memory allocated in the dll or client must be 
deallocated in the same dll or client respectively. This impose a number of constraints when passing
arrays or any variable length structure. 

- The Interfacing to Visual Basic for Applications (VBA) impose a number of limitations . Structure cannot accomodate char* but it
 is OK with fixed dimensionned arrays. Structure must be passed by reference (pointer). VBA cannot access directly DLL arrays
 
		
- Any function to be exported must be declared  using the qualifiers EXP and CALL. 
On some platforms, these qualifiers may be dropped but we advise to keep them for portability. 
*/

#include "AlphaDll.h"

#ifdef __cplusplus  
extern "C" {
#endif

/* OK = 0 */
#define OK 0
#define Nchar 4


struct st_ {
double d;
int i;
char c[Nchar]; /* fixed length only {VBA)  */
}  ;

typedef struct st_ st;

	/**. Return a stream generated in the dll.
	 This function cannot be called from Visual Basic For Applications. 
 	@param		No input parameters 
 	@return	the chain of characters of the stream. 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */ 
EXP  const char * CALL getostream(); 

	/**. Return the error message associated to er. 
	This function cannot be called from Visual Basic For Applications. 
 	@param		er Error number 
 	@return	the chain of characters of the stream. 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		geterrorsize  and  geterrortext */ 
EXP const char * CALL geterror(int er); 

	/**. Return the warning message associated to er. 
	This function cannot be called from Visual Basic For Applications. 
 	@param		er Warning number 
 	@return	the chain of characters of the stream. 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */ 
EXP const char * CALL getwarning(int er); 

	/**.Return the length of the error message not counting "\0". 
 	@param		er Error number 
 	@param		siz Size of the error message  
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */ 
EXP int CALL geterrorsize(int *siz,int er);

	/**.Return the length of the warning message not counting "\0". 
 	@param		er Warning number 
 	@param		siz Size of the warning message  
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */ 
EXP int CALL getwarningsize(int *siz,int er);

	/**. Get the error message associated to the error number er. 
	Must be pre-allocated with geterrorsize +1 to include "\0". 
	@param		t Chain of character holding the error message   
 	@param		er Error number 
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		geterrorsize */ 
EXP int CALL geterrortext(char*t,int er);

	/**. Get the warning message associated to the warning number er. 
	Must be pre-allocated with getwarningsize +1 to include "\0". 
	@param		t Chain of character holding the warning message   
 	@param		er Warning number 
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		getwarningsize */ 
EXP int CALL getwarningtext(char*t,int er);


 	/**.  A teste function which use the database and smart pointer template classes. 
 	@param		No input parameters 
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */ 
EXP int CALL teste();

 	/**.  compute x/y . 
	@param		ret  return value
	@param		x  input value 
 	@param		y  input value 
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */ 
EXP int CALL divi(double* ret,double x,double y ); 

	/**.  The client allocate memory for a user defined structure which is modified
	by the dll.  
	@param		s   structure to be modified
	@param		x  input value 
 	@param		i  input value 
 	@param		p  input value 
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */
EXP int CALL clientstructure(st* s,double x, int i,char*p);

	/**.  The client allocate memory for an array which content is modified
	by the dll.  
	@param		a  array to be modified
	@param		n  input value 
 	@param		y  input value 
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */
EXP int CALL clientarray(double*a,int n, double y );

	/**.Allocate an array in the DLL and make it available to the clients using special reading functions
	the array is bufferized in a fixed pointer to avoid the need to delete it each time. 
	@param		n   size of the array 
	@param		y  input value 
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */
EXP int CALL dllarray(int n, double y );

	/**. Read a double from an array allocated by dllarray.  
	@param		v  double value to be retrieved
 	@param		i  array index
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */
EXP int CALL getdouble(double *v,int i);

	/**. Read the size of the array allocated by dllarray.  
	@param		v  number of byte allocated 
 	@return	An integer  value ( 0 : No Erro,  > 0 : Error Number,  < 0 : Warning Number) 
 	@author	P. Elleaume 
 	@version	1.0 
 	@see		... */
EXP int CALL getsize(int *v);



#ifdef __cplusplus  
}
#endif

