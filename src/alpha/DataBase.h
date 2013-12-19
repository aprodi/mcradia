/* *********************************************************************
#
#
# Project:       Alpha
#
# Description:   Database class  to gather object 
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



#ifndef __DATABASE_H
#define __DATABASE_H

//-------------------------------------------------------------------------

#include "SmartPointer.h"

template<class T>
class database {

public:

database() {pos=1;}

int insert(T *i) {
SmartPointer<T> p(i);
data[pos++]=p;
return pos-1;}

int insert(SmartPointer<T> p) {
data[pos++]=p;
return pos-1;}

void erase(int j) {
if( exist(j)==1) data.erase(data.find(j));}

void erase() {
data.erase(data.begin(),data.end());}

~database(){erase();}

int exist(int j) {
if(data.find(j)==data.end()) return 0;
 return 1;}
 
 SmartPointer<T> get(int j) {return data[j];}
 
private:
 map<int, SmartPointer<T> , less<int> > data;
int pos;
};

#endif
