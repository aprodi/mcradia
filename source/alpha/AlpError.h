/* *********************************************************************
#
#
# Project:       Alpha
#
# Description:   Error Class
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

#ifndef __ALPERROR_H
#define __ALPERROR_H

#include <vector>
#include <string>

//______________________________________________
class ErrorWarning {
public:
ErrorWarning() {
// Errors
error.push_back("Wrong Error Number"); 									// 0
error.push_back("Division by zero"); 									// 1
error.push_back("Array Dimension must be larger"); 						// 2
error.push_back("Array Dimension out of range"); 						// 3
error.push_back("aaa"); 												// 4


//Warning
warn.push_back("Wrong Warning Number"); 								// 0
warn.push_back("Negative Result"); 										// 1
warn.push_back("Warning # 2"); 											// 2
warn.push_back("Warning # 3"); 											// 3
}

virtual int geterrorsize(int e){
e=abs(e);
if(e>= error.size()) e=0; 
return error[e].size();}

virtual const char* geterror(int e){
e=abs(e);
if(e>= error.size()) e=0; 
return error[e].c_str();}

virtual int getwarningsize(int e){
e=abs(e);
if(e>= warn.size()) e=0; 
return warn[e].size();}

virtual const char*  getwarning(int e){
e=abs(e);
if(e>= warn.size()) e=0;
 return warn[e].c_str();}
 
protected:
vector<string> error;
vector<string> warn;
};

#endif
