
#ifndef __GMMETH_H
#define __GMMETH_H

#include "gmvect.h"

//-------------------------------------------------------------------------
// General mathematical methods
//-------------------------------------------------------------------------

class CGenMathMeth {
public:

	static bool VectCheckIfCollinear(double xV1, double yV1, double zV1, double xV2, double yV2, double zV2, double RelPrec);

	static double Integ1D_FuncWithEdgeDer(double (*pF)(double), double x1, double x2, double dFdx1, double dFdx2, double RelPrec);
	static double Integ1D_FuncDefByArray(double* FuncArr, long Np, double Step);
	static double Integ1D_FuncDefByArray(float* FuncArr, long Np, double Step);

	template <class T> static T tabFunc2D(int ix, int iy, int nx, T* pF)
	{//just function value
		if(pF == 0) return (T)0.;
		long ofst = iy*nx + ix;
		return *(pF + ofst);
	}
	template <class T> static T interpFunc2D(double x, double y, double xStart, double xEnd, int nx, double yStart, double yEnd, int ny, T* pF)
	{//uses bilinear interpolation
		if((pF == 0) || (nx <= 0) || (ny <= 0)) return (T)0.;

		double xStep = 0, yStep = 0;
		if(nx > 1) xStep = (xEnd - xStart)/(nx - 1);
		if(ny > 1) yStep = (yEnd - yStart)/(ny - 1);

		long ix1, iy1;
		if(x < xStart) ix1 = 0; 
		else if(x <= xEnd) ix1 = (int)((x - xStart)/xStep + 0.001*xStep); 
		else ix1 = nx - 1;

		if(y < yStart) iy1 = 0;
		else if(y <= yEnd) iy1 = (int)((y - yStart)/yStep + 0.001*yStep);
		else iy1 = ny - 1;

		long ix2 = ix1, iy2 = iy1;
		int nx_mi_1 = nx - 1;
		if(ix1 < nx_mi_1) ix2 = ix1 + 1;
		else if(ix1 >= nx_mi_1) { ix1 = nx - 2; ix2 = ix1 + 1;}

		int ny_mi_1 = ny - 1;
		if(iy1 < ny_mi_1) iy2 = iy1 + 1;
		else if(iy1 >= ny_mi_1) { iy1 = ny - 2; iy2 = iy1 + 1;}

		double xr = x - (xStart + ix1*xStep);
		double yr = y - (yStart + iy1*yStep);

		long ofst11 = nx*iy1 + ix1;
		long ofst12 = nx*iy2 + ix1;
		long ofst21 = nx*iy1 + ix2;
		long ofst22 = nx*iy2 + ix2;

		if(nx == 1)
		{
			if(ny == 1) return *(pF + ofst11);
			else return (*(pF + ofst11)) + ((*(pF + ofst12)) - (*(pF + ofst11)))*yr/yStep;
		}
		else
		{
			if(ny == 1) return (*(pF + ofst11)) + ((*(pF + ofst21)) - (*(pF + ofst11)))*xr/xStep;
			else 
			{
				double xt = xr/xStep, yt = yr/yStep;
				return (*(pF + ofst11))*(1 - xt)*(1 - yt) + (*(pF + ofst21))*xt*(1 - yt) + (*(pF + ofst12))*(1 - xt)*yt + (*(pF + ofst22))*xt*yt;
			}
		}
	}

	template <class T> static T tabTangOrtsToSurf2D(TVector3d& vHorRes, TVector3d& vVertRes, int ix, int iz, int nx, int nz, double xStep, double zStep, T* pF)
	{//calculates  "horizontal" and "vertical" tangential vector and inner normal (assuming y - longitudinal coordinate)
	 //returns function value, same as tabFunc2D
		if((pF == 0) || (nx <= 1) || (nz <= 1)) return (T)0.;

		double hx = xStep, hz = zStep;
		long ofst0 = iz*nx + ix;
		long ofstX1, ofstX2, ofstZ1, ofstZ2;
		if(ix == 0)
		{
			ofstX1 = ofst0; ofstX2 = ofst0 + 1;
		}
		else if(ix == (nx - 1))
		{
			ofstX1 = ofst0 - 1; ofstX2 = ofst0;
		}
		else
		{
			ofstX1 = ofst0 - 1; ofstX2 = ofst0 + 1; hx *= 2;
		}
		if(iz == 0)
		{
			ofstZ1 = ofst0; ofstZ2 = ofst0 + nx;
		}
		else if(iz == (nz - 1))
		{
			ofstZ1 = ofst0 - nx; ofstZ2 = ofst0;
		}
		else
		{
			ofstZ1 = ofst0 - nx; ofstZ2 = ofst0 + nx; hz *= 2;
		}

		vHorRes.x = hx; vHorRes.y = (double)(*(pF + ofstX2) - *(pF + ofstX1)); vHorRes.z = 0;
		vVertRes.x = 0; vVertRes.y = (double)(*(pF + ofstZ2) - *(pF + ofstZ1)); vVertRes.z = hz;
		vHorRes.Normalize(); vVertRes.Normalize();
		return *(pF + ofst0);
	}

	template <class T> static T differentiate(T* f, double h, int PoIndx, int AmOfPo)
	{//differentiate function of real argument
		if(AmOfPo==5)
		{
			if(PoIndx==2) return 0.08333333333333*(f[0] - 8.*f[1] + 8.*f[3] - f[4])/h;
			else if(PoIndx==1) return 0.08333333333333*(-3.*f[0] - 10.*f[1] + 18.*f[2] - 6.*f[3] + f[4])/h;
			else if(PoIndx==3) return 0.08333333333333*(-f[0] + 6.*f[1] - 18.*f[2] + 10.*f[3] + 3.*f[4])/h;
			else if(PoIndx==0) return 0.5*(-3.*f[0] + 4.*f[1] - f[2])/h;
			else return 0.5*(f[2] - 4.*f[3] + 3.*f[4])/h;
			//else if(PoIndx==4) return 0.5*(f[2] - 4.*f[3] + 3.*f[4])/h;
			//else return 1.E+23;
		}
		else if(AmOfPo==4)
		{
			if(PoIndx==1) return 0.5*(-f[0] + f[2])/h;
			else if(PoIndx==2) return 0.5*(-f[1] + f[3])/h;
			else if(PoIndx==0) return 0.5*(-3.*f[0] + 4.*f[1] - f[2])/h;
			else return 0.5*(f[1] - 4.*f[2] + 3.*f[3])/h;
			//else if(PoIndx==3) return 0.5*(f[1] - 4.*f[2] + 3.*f[3])/h;
			//else return 1.E+23;
		}
		else if(AmOfPo==3)
		{
			if(PoIndx==1) return 0.5*(-f[0] + f[2])/h;
			else if(PoIndx==0) return 0.5*(-3.*f[0] + 4.*f[1] - f[2])/h;
			else return 0.5*(f[0] - 4.*f[1] + 3.*f[2])/h;
			//else if(PoIndx==2) return 0.5*(f[0] - 4.*f[1] + 3.*f[2])/h;
			//else return 1.E+23;
		}
		else return (-f[0] + f[1])/h;
		//else if(AmOfPo==2) return (-f[0] + f[1])/h;
		//else return 1.E+23;
	}

	static double radicalOnePlusSmall(double x)
	{
		if(::fabs(x) > 0.01) return sqrt(1. + x);
		return 1. + x*(0.5 + x*(-0.125 + x*(0.0625 + x*(-0.0390625 + x*(0.02734375 + x*(-0.0205078125 + x*0.01611328125))))));
	}

	static double radicalOnePlusSmallMinusOne(double x)
	{
		if(::fabs(x) > 0.01) return sqrt(1. + x) - 1.;
		return x*(0.5 + x*(-0.125 + x*(0.0625 + x*(-0.0390625 + x*(0.02734375 + x*(-0.0205078125 + x*0.01611328125))))));
	}

};

//-------------------------------------------------------------------------

#endif


