// matlabaux.cpp : Defines the entry point for the DLL application.
//

#include "matlabaux.h"

#ifdef _WIN32
#ifndef COMPILE_IN_MATLAB
#include <windows.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
#endif
#else
#define	__int64 long
#endif

MATLABAUX_API unsigned long maGetUINT32Element(const mxArray* pArray, unsigned long index)
{
	unsigned long result;
	switch(mxGetClassID(pArray))
	{
	case mxDOUBLE_CLASS: 
		result = (unsigned long)(((double*)mxGetData(pArray))[index]);
		break;
	case mxSINGLE_CLASS: 
		result = (unsigned long)(((float*)mxGetData(pArray))[index]);
		break;
	case mxINT8_CLASS: 
		result = (unsigned long)(((char*)mxGetData(pArray))[index]);
		break;
	case mxUINT8_CLASS: 
		result = (unsigned long)(((unsigned char*)mxGetData(pArray))[index]);
		break;
	case mxINT16_CLASS: 
		result = (unsigned long)(((short*)mxGetData(pArray))[index]);
		break;
	case mxUINT16_CLASS: 
		result = (unsigned long)(((unsigned short*)mxGetData(pArray))[index]);
		break;
	case mxINT32_CLASS: 
		result = (unsigned long)(((long*)mxGetData(pArray))[index]);
		break;
	case mxUINT32_CLASS: 
		result = (unsigned long)(((unsigned long*)mxGetData(pArray))[index]);
		break;
	case mxINT64_CLASS: 
		result = (unsigned long)(((__int64*)mxGetData(pArray))[index]);
		break;
	case mxUINT64_CLASS: 
		result = (unsigned long)(((unsigned __int64*)mxGetData(pArray))[index]);
		break;
	default:
		result = (unsigned long)-1;
		break;
	}
	return result;
}

MATLABAUX_API long maGetINT32Element(const mxArray* pArray, long index)
{
	long result;
	switch(mxGetClassID(pArray))
	{
	case mxDOUBLE_CLASS: 
		result = (long)(((double*)mxGetData(pArray))[index]);
		break;
	case mxSINGLE_CLASS: 
		result = (long)(((float*)mxGetData(pArray))[index]);
		break;
	case mxINT8_CLASS: 
		result = (long)(((char*)mxGetData(pArray))[index]);
		break;
	case mxUINT8_CLASS: 
		result = (long)(((unsigned char*)mxGetData(pArray))[index]);
		break;
	case mxINT16_CLASS: 
		result = (long)(((short*)mxGetData(pArray))[index]);
		break;
	case mxUINT16_CLASS: 
		result = (long)(((unsigned short*)mxGetData(pArray))[index]);
		break;
	case mxINT32_CLASS: 
		result = (long)(((long*)mxGetData(pArray))[index]);
		break;
	case mxUINT32_CLASS: 
		result = (long)(((unsigned long*)mxGetData(pArray))[index]);
		break;
	case mxINT64_CLASS: 
		result = (long)(((__int64*)mxGetData(pArray))[index]);
		break;
	case mxUINT64_CLASS: 
		result = (long)(((unsigned __int64*)mxGetData(pArray))[index]);
		break;
	default:
		result = (unsigned long)-1;
		break;
	}
	return result;
}

MATLABAUX_API double maGetDoubleElement(const mxArray* pArray, unsigned long index)
{
	double result;
	switch(mxGetClassID(pArray))
	{
	case mxDOUBLE_CLASS: 
		result = (double)(((double*)mxGetData(pArray))[index]);
		break;
	case mxSINGLE_CLASS: 
		result = (double)(((float*)mxGetData(pArray))[index]);
		break;
	case mxINT8_CLASS: 
		result = (double)(((char*)mxGetData(pArray))[index]);
		break;
	case mxUINT8_CLASS: 
		result = (double)(((unsigned char*)mxGetData(pArray))[index]);
		break;
	case mxINT16_CLASS: 
		result = (double)(((short*)mxGetData(pArray))[index]);
		break;
	case mxUINT16_CLASS: 
		result = (double)(((unsigned short*)mxGetData(pArray))[index]);
		break;
	case mxINT32_CLASS: 
		result = (double)(((long*)mxGetData(pArray))[index]);
		break;
	case mxUINT32_CLASS: 
		result = (double)(((unsigned long*)mxGetData(pArray))[index]);
		break;
	case mxINT64_CLASS: 
		result = (double)(((__int64*)mxGetData(pArray))[index]);
		break;
	case mxUINT64_CLASS: 
		result = (double)((unsigned long)(((unsigned __int64*)mxGetData(pArray))[index]));
		break;
	default:
		result = (unsigned long)-1;
		break;
	}
	return result;
}
