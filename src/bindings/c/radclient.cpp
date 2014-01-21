// radclient.cpp : Defines the entry point for the console application to test Radia shared library
// illustrating the use of the Radia shared library by implicit linking 
// (which is also referred as static load or load-time dynamic linking)

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN		// Exclure les en-t�tes Windows rarement utilis�s
#endif

#include <iostream>
using namespace std;
#include "stdio.h"

#include "radentry.h"

//----------------------------------------------------------------------

void ErrProc(int er)
{
	char ErrorBuf[2048];

	if(er == 0) return;
	else if(er < 0)
	{
		RadWarGetText(ErrorBuf, er);
		cout << "WARNING: " << ErrorBuf << endl;
		//return/send warning message to Python in place of the above
	}
	else if(er > 0)
	{
		RadErrGetText(ErrorBuf, er);
		cout << "ERROR: " << ErrorBuf << endl;
		//return/send error message to Python in place of the above
	}
}

//----------------------------------------------------------------------

int radObjRecMag(double* P, double* L, double* M)
{//make such function accessible from Python via SWIG
 //convert double* to appropriate "native" type of SWIG/Python
	int n;
    ErrProc(RadObjRecMag(&n, P, L, M));
	//RadObjRecMag function is declared in radentry.h and implemented in radia.dll
	return n;
}

//----------------------------------------------------------------------

int radObjCnt(int* Elems, int nElems)
{//make such function accessible from Python via SWIG
 //convert double* to appropriate "native" type of SWIG/Python
	int n;
    ErrProc(RadObjCnt(&n, Elems, nElems));
	//RadObjCnt(int *n, int* Elems, int ne) function is declared in radentry.h and implemented in radia.dll
	return n;
}

//----------------------------------------------------------------------

int radObjAddToCnt(int n, int* Elems, int nElems)
{//make such function accessible from Python via SWIG
 //convert double* to appropriate "native" type of SWIG/Python
    ErrProc(RadObjAddToCnt(n, Elems, nElems));
	//RadObjCnt(int *n, int* Elems, int ne) function is declared in radentry.h and implemented in radia.dll
	return n;
}

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
	//the following would move to a Radia/Python example
	double P[] = {0., 0., 0.};
	double L[] = {10., 10., 10.};
	double M[] = {0., 0., 1.};

	//RadObjDrwQD3D(mag, 0, 0, 0);
	//RadObjDrwOpenGL(mag, "EdgeLines->True", 0, 0);
	//RadObjDrwOpenGL(mag, 0, 0, 0);

	double FV[] = {0.,0.,1.,1.,-1.,1.,-1.,-1.,1.,-1.,0.,0.,0.,1.,1.,1.,1.,0.};
	int SL[] = {1,4,1,3};
	double AT[] = {0., 1., 2., 3.};
	int ppoly;

	ErrProc(RadObjMltExtPgn(&ppoly,FV,SL,AT,4,M));
	//ErrProc(RadObjDrwOpenGL(ppoly, 0, 0, 0));

	double ArrB[3];
	double ObsP[] = {2,1,2};
	int pNb[] = {1};

	ErrProc(RadFld(ArrB, pNb, ppoly, "B", ObsP, 1));


	int mag = radObjRecMag(P, L, M);
	int mag1 = radObjRecMag(P, L, M);

	int Elems[] = {mag};
	int Elems1[] = {mag1};
	int cnt = radObjCnt(Elems, 1);

	int ContSize = 0;
	ErrProc(RadObjCntSize(&ContSize, cnt));

	cnt = radObjAddToCnt(cnt, Elems1, 1);
	ErrProc(RadObjCntSize(&ContSize, cnt));

	int* CntStuffArr = new int[ContSize];
	ErrProc(RadObjCntStuf(CntStuffArr, cnt));

	cout << ArrB[0] << ", " << ArrB[1] << ", " << ArrB[2] << endl; 
	cout << "press \"Enter\" to exit" << endl;

	delete[] CntStuffArr;

	getchar();
	return 0;
}

//----------------------------------------------------------------------
