// CUtil.cpp: implementation of the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#include <string.h>
#include "CUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtil::CUtil()
{

}

CUtil::~CUtil()
{

}

#ifndef max
#define	max(x,y)	((x<y)?y:x)
#endif
/*
int CUtil::strcmpi(const char* src, const char* dst) {
#ifdef _WIN32
	return ::strcmpi(src, dst);
#else
	// not a good way to do it, obviously,
	// but it makes use of older stuff :) and I am lazy
	// who needs it to be fast anyway...
	int sl = strlen(src);
	int dl = strlen(dst);
	char* tsrc = new char[sl+1];
	char* tdst = new char[dl+1];
	strcpy(tsrc, src);
	strcpy(tdst, dst);
	int i;
	for (i = 0; i < max(sl, dl); i++)
	{
		if (i < sl)
			tsrc[i] = toupper(tsrc[i]);
		if (i < dl)
			tdst[i] = toupper(tdst[i]);
	}
	int result = ::strcmp(tsrc, tdst);
	delete tsrc;
	delete tdst;
	return result;
#endif
}
*/

int CUtil::u_strcmpi(const char* src, const char* dst)
{ 
	// Reproducing code because unix/linux SUCKS!!
//#ifdef _WIN32
//	return ::strcmpi(src, dst);
//#else
	// not a good way to do it, obviously,
	// but it makes use of older stuff :) and I am lazy
	// who needs it to be fast anyway...
	
	int sl = strlen(src);
	int dl = strlen(dst);
	char* tsrc = new char[sl+1];
	char* tdst = new char[dl+1];
	strcpy(tsrc, src);
	strcpy(tdst, dst);
	int i;
	for (i = 0; i < max(sl, dl); i++)
	{
		if (i < sl)
			tsrc[i] = toupper(tsrc[i]);
		if (i < dl)
			tdst[i] = toupper(tdst[i]);
	}
	int result = ::strcmp(tsrc, tdst);
	delete tsrc;
	delete tdst;
	return result;
	
//#endif
}
