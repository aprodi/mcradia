/* *********************************************************************
#
#
# Project:       Alpha
#
# Description:   Referece Counted  pointer class  
#
#
# Basis :	 Stroustrup, The C++ Programming Language
# Modification :   P. Elleaume, O. Chubar
#
# 
# Copyright (c) 2000 by European Synchrotron Radiation Facility,
#                       Grenoble, France
#
#                       All Rights Reserved
#
#********************************************************************** */


#ifndef __POINTER_H
#define __POINTER_H

//-------------------------------------------------------------------------

template<class T> class SmartPointer {
public:
	T* rep;
	int* pcount;

	SmartPointer () { rep=0; pcount=0;}
	SmartPointer (T* pp) : rep(pp), pcount(new int) {  (*pcount)=1;}
	SmartPointer (const SmartPointer& r) : rep(r.rep), pcount(r.pcount) 
	{ 
		if(pcount != 0) (*pcount)++;
	}

	void destroy()
	{
		if(pcount!=0)
			if(--(*pcount)==0)
			{
				delete rep;
				delete pcount;
				rep=0; pcount=0;
			}
	}

	T* operator->() { return rep;}
	T* obj() { return rep;}
	void bind(const SmartPointer& r)
	{
		if(rep!=r.rep)
		{
			if(r.rep!=0)
			{
				destroy();
				rep = r.rep;
				pcount = r.pcount;
				(*pcount)++;
			}
			else
			{
				rep = 0;
				pcount = 0;
			}
		}
	}

	SmartPointer& operator=(const SmartPointer& r) 
	{ 
		bind(r); return *this;
	}

	int operator<(const SmartPointer& r)
	{
		if(rep<r.rep) return 1;
		else return 0;
	}
	int operator==(const SmartPointer& r)
	{
		if(rep==r.rep) return 1;
		else return 0;
	}

	~SmartPointer()
	{
		destroy();
	}
};

//-------------------------------------------------------------------------

template<class T> inline int operator <(const SmartPointer<T>& h1, const SmartPointer<T>& h2)
{
	return (h1.rep < h2.rep); 
}

//-------------------------------------------------------------------------

template<class T> inline int operator ==(const SmartPointer<T>& h1, const SmartPointer<T>& h2)
{
	return (h1.rep == h2.rep); 
}

//-------------------------------------------------------------------------

#endif
