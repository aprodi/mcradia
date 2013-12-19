/*-------------------------------------------------------------------------
*
* File name:      radiobuf.h
*
* Project:        RADIA
*
* Description:    Input/output buffer; errors and warnings
*
* Author(s):      Oleg Chubar
*
* First release:  1997
* 
* Copyright (C):  1997 by European Synchrotron Radiation Facility, France
*                 All Rights Reserved
*
-------------------------------------------------------------------------*/

#ifndef __RADIOBUF_H
#define __RADIOBUF_H

#include <vector>
#include <string>


//-added for compatibility with gcc > 4.6.3 ------- -----------------------

#include <math.h>
#include <cstring> 

using namespace std;

//-------------------------------------------------------------------------

class radTIOBuffer /*: public ErrorWarning*/ {

	vector<int> ErrNoBuffer;
	vector<int> WarNoBuffer;

	vector<int> IntBuffer;
	vector<double> DoubleBuffer;
	vector<string> StringBuffer;

	double *DoubleBufferMulti;
	int *DimsDoubleBufferMulti, NumDimsDoubleBufferMulti;

	int *IntBufferMulti;
	int *DimsIntBufferMulti, NumDimsIntBufferMulti;

	static string err_ar[];
	static int AmOfErrors;
	static string warn_ar[];
	static int AmOfWarnings;

public:

	radTIOBuffer() /*: ErrorWarning()*/ {}

	const char* GetError(int e)
	{
		e = abs(e);
		if(e >= AmOfErrors) e = 0; 
		const char* DecoratedStr = err_ar[e].c_str();
		return RemoveDecorFromErrWarnStr(DecoratedStr);
	}

	int GetErrorSize(int e)
	{
		const char* ErrStr = GetError(e);
		if(ErrStr == NULL) return 0;
		return (int)strlen(ErrStr);
	}

	const char* GetWarning(int e)
	{
		e = abs(e);
		if(e >= AmOfWarnings) e = 0; 
		const char* DecoratedStr = warn_ar[e].c_str();
		return RemoveDecorFromErrWarnStr(DecoratedStr);
	}

	int GetWarningSize(int e)
	{
		const char* ErrStr = GetWarning(e);
		if(ErrStr == NULL) return 0;
		return (int)strlen(ErrStr);
	}

	void StoreErrorMessage(const char* InStr)
	{
		int ErrIndex = DecodeErrorIndex(InStr);
		if(ErrIndex >= 0) ErrNoBuffer.push_back(ErrIndex);
	}
	void StoreWarningMessage(const char* InStr)
	{
		int WarnIndex = DecodeWarningIndex(InStr);
		if(WarnIndex >= 0) WarNoBuffer.push_back(WarnIndex);
	}

	void StoreInt(int IntValue)
	{
		IntBuffer.push_back(IntValue);
	}
	void StoreMultiDimArrayOfInt(int* Array, int* Dims, int NumDims)
	{
		DimsIntBufferMulti = new int[NumDims];
		if(DimsIntBufferMulti == 0) { StoreErrorMessage("Radia::Error900"); return;}
		long TotLen = 1;
		for(int i=0; i<NumDims; i++) 
		{
			int aDim = Dims[i];
			TotLen *= aDim;
			DimsIntBufferMulti[i] = aDim;
		}
		NumDimsIntBufferMulti = NumDims;

		IntBufferMulti = new int[TotLen];
		if(IntBufferMulti == 0) { StoreErrorMessage("Radia::Error900"); return;}
		int *tIntBufferMulti = IntBufferMulti;
		int *tArray = Array;
		for(int k=0; k<TotLen; k++) *(tIntBufferMulti++) = *(tArray++);
	}
	void StoreDouble(double DoubleValue)
	{
		DoubleBuffer.push_back(DoubleValue);
	}
	void StoreMultiDimArrayOfDouble(double* Array, int* Dims, int NumDims)
	{
		DimsDoubleBufferMulti = new int[NumDims];
		if(DimsDoubleBufferMulti == 0) { StoreErrorMessage("Radia::Error900"); return;}
		long TotLen = 1;
		for(int i=0; i<NumDims; i++) 
		{
			int aDim = Dims[i];
			TotLen *= aDim;
			DimsDoubleBufferMulti[i] = aDim;
		}
		NumDimsDoubleBufferMulti = NumDims;

		DoubleBufferMulti = new double[TotLen];
		if(DoubleBufferMulti == 0) { StoreErrorMessage("Radia::Error900"); return;}
		double *tDoubleBufferMulti = DoubleBufferMulti;
		double *tArray = Array;
		for(int k=0; k<TotLen; k++) *(tDoubleBufferMulti++) = *(tArray++);
	}
	void StoreString(const char* MessageString)
	{
		StringBuffer.push_back(MessageString);
	}

	int OutErrorStatus()
	{
		if(!ErrNoBuffer.empty())
		{
			int OutErrNo = ErrNoBuffer[0];
			ErrNoBuffer.erase(ErrNoBuffer.begin(), ErrNoBuffer.end());
			return OutErrNo;
		}
		else if(!WarNoBuffer.empty())
		{
			int OutWarNo = WarNoBuffer[0];
			WarNoBuffer.erase(WarNoBuffer.begin(), WarNoBuffer.end());
			return -OutWarNo;
		}
		else return 0;
	}
	int OutInt()
	{
		if(IntBuffer.empty()) return 0;
		int Value = *(IntBuffer.end() - 1);
		IntBuffer.erase(IntBuffer.end() - 1);
		return Value;
	}
	void OutMultiDimArrayOfInt(int* Array, int* Dims, int& NumDims)
	{
		if((IntBufferMulti != 0) && (DimsIntBufferMulti != 0))
		{
			long TotLen = 1;
			for(int i=0; i<NumDimsIntBufferMulti; i++)
			{
				int aDim = DimsIntBufferMulti[i];
				TotLen *= aDim;
				Dims[i] = aDim;
			}
			NumDims = NumDimsIntBufferMulti;
			int *tIntBufferMulti = IntBufferMulti;
			int *tArray = Array;
			for(int k=0; k<TotLen; k++) *(tArray++) = *(tIntBufferMulti++);

			EraseIntBufferMulti();
		}
	}
	double OutDouble()
	{
		if(DoubleBuffer.empty()) return 0;
		double Value = *(DoubleBuffer.end() - 1);
		DoubleBuffer.erase(DoubleBuffer.end() - 1);
		return Value;
	}
	void OutMultiDimArrayOfDouble(double* Array, int* Dims, int& NumDims)
	{
		if((DoubleBufferMulti != 0) && (DimsDoubleBufferMulti != 0))
		{
			long TotLen = 1;
			for(int i=0; i<NumDimsDoubleBufferMulti; i++)
			{
				int aDim = DimsDoubleBufferMulti[i];
				TotLen *= aDim;
				Dims[i] = aDim;
			}
			NumDims = NumDimsDoubleBufferMulti;
			double *tDoubleBufferMulti = DoubleBufferMulti;
			double *tArray = Array;
			for(int k=0; k<TotLen; k++) *(tArray++) = *(tDoubleBufferMulti++);

			EraseDoubleBufferMulti();
		}
	}
	const char* OutString()
	{
		if(StringBuffer.empty()) return "\0";
		return (StringBuffer.end() - 1)->c_str();
	}
	void EraseStringBuffer()
	{
		if(!StringBuffer.empty()) StringBuffer.erase(StringBuffer.begin(), StringBuffer.end());
	}
	void OutStringClean(char* OutStrCont)
	{
        strcpy(OutStrCont, OutString());
        EraseStringBuffer();
	}

	const char* DecodeErrorText(const char* ErrorTitle)
	{
		if(ErrorTitle == 0) return 0;
		int LenErrorTitle = (int)strlen(ErrorTitle);
		if(LenErrorTitle <= 0) return 0;

		for(int i=0; i<AmOfErrors; i++)
		{
			int CurStrLen = (int)err_ar[i].size();
			if(CurStrLen < LenErrorTitle) continue;
			const char* CurStr = err_ar[i].c_str();
			if(strncmp(CurStr, ErrorTitle, LenErrorTitle) == 0) 
			{
				return RemoveDecorFromErrWarnStr(CurStr);
			}
		}
		return NULL;
	}
	const char* DecodeWarningText(const char* ErrorTitle)
	{
		if(ErrorTitle == 0) return 0;
		int LenErrorTitle = (int)strlen(ErrorTitle);
		if(LenErrorTitle <= 0) return 0;

		for(int i=0; i<AmOfWarnings; i++)
		{
			int CurStrLen = (int)warn_ar[i].size();
			if(CurStrLen < LenErrorTitle) continue;
			const char* CurStr = warn_ar[i].c_str();
			if(strncmp(CurStr, ErrorTitle, LenErrorTitle) == 0) 
			{
				return RemoveDecorFromErrWarnStr(CurStr);
			}
		}
		return NULL;
	}

	void PrepErrWarnMesageForMathematica(char* ErrMesForMath, const char* ErrorTitle, char e_or_w)
	{
		*ErrMesForMath = '\0';
		if(ErrorTitle == 0) return;

		strcpy(ErrMesForMath, ErrorTitle);

		const char* DecodedErrMes = 0;
		if((e_or_w == 'w') || (e_or_w == 'W'))
		{
			DecodedErrMes = DecodeWarningText(ErrorTitle);
		}
		else
		{
			DecodedErrMes = DecodeErrorText(ErrorTitle);
		}

		if(DecodedErrMes == 0) return;

		strcat(ErrMesForMath, " = \"");
		strcat(ErrMesForMath, DecodedErrMes);
		strcat(ErrMesForMath, "\"");
	}

private:

	int DecodeErrorIndex(const char* ErrorTitle)
	{
		if(ErrorTitle == 0) return 0;
		int LenErrorTitle = (int)strlen(ErrorTitle);
		if(LenErrorTitle <= 0) return 0;
		//char* cAuxBuf = new char[LenErrorTitle];

		for(int i=0; i<AmOfErrors; i++)
		{
			int CurStrLen = (int)err_ar[i].size();
			if(CurStrLen < LenErrorTitle) continue;
			const char* CurStr = err_ar[i].c_str();
			//strncpy(cAuxBuf, CurStr, LenErrorTitle);
			if(strncmp(CurStr, ErrorTitle, LenErrorTitle) == 0) return i;
		}
		return 0;

		//char *pNum = strrchr(ErrorTitle, 'r') + 1;
		//int ErrNo = atoi(pNum);
		//
		//for(int i=0; i<ErrNos.size(); i++)
		//{
		//	if(ErrNo == ErrNos[i]) return i;
		//}
	}
	int DecodeWarningIndex(const char* WarningTitle)
	{
		if(WarningTitle == 0) return 0;
		int LenWarningTitle = (int)strlen(WarningTitle);
		if(LenWarningTitle <= 0) return 0;
		//char* cAuxBuf = new char[LenWarningTitle];

		for(int i=0; i<AmOfWarnings; i++)
		{
			int CurStrLen = (int)warn_ar[i].size();
			if(CurStrLen < LenWarningTitle) continue;
			const char* CurStr = warn_ar[i].c_str();
			//strncpy(cAuxBuf, warn_ar[i].c_str(), LenWarningTitle);
			if(strncmp(CurStr, WarningTitle, LenWarningTitle) == 0) return i;
		}
		return 0;

		//char *pNum = strrchr(WarningTitle, 'g') + 1;
		//int WarNo = atoi(pNum);
		//
		//for(int i=0; i<WarNos.size(); i++)
		//{
		//	if(WarNo == WarNos[i]) return i;
		//}
	}

	void EraseIntBufferMulti()
	{
		if(IntBufferMulti != 0) delete[] IntBufferMulti; IntBufferMulti = 0;
		if(DimsIntBufferMulti != 0) delete[] DimsIntBufferMulti; DimsIntBufferMulti = 0;
		NumDimsIntBufferMulti = 0;
	}
	void EraseDoubleBufferMulti()
	{
		if(DoubleBufferMulti != 0) delete[] DoubleBufferMulti; DoubleBufferMulti = 0;
		if(DimsDoubleBufferMulti != 0) delete[] DimsDoubleBufferMulti; DimsDoubleBufferMulti = 0;
		NumDimsDoubleBufferMulti = 0;
	}

	const char* RemoveDecorFromErrWarnStr(const char* DecoratedStr)
	{
		const char* StrSepar = "::::";
		int LenStrSepar = (int)strlen(StrSepar);

		int LenDecoratedStr = (int)strlen(DecoratedStr);
		if(LenDecoratedStr <= LenStrSepar) return NULL;

		const char* StrSeparAndNonDecoratedStr = strstr(DecoratedStr, StrSepar);
		if(StrSeparAndNonDecoratedStr == NULL) return NULL;

		int LenStrSeparAndNonDecoratedStr = (int)strlen(StrSeparAndNonDecoratedStr);
		if(LenStrSeparAndNonDecoratedStr <= LenStrSepar) return NULL;
		
		return StrSeparAndNonDecoratedStr + LenStrSepar;
	}

};

#endif

