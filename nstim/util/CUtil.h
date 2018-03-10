// CUtil.h: interface for the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CUTIL_H
#define CUTIL_H

#include <string.h>
#include <ctype.h>

class CUtil  
{

public:
	CUtil();
	virtual ~CUtil();


	static int u_strcmpi(const char* src, const char* dst);
//	static int strcmpi(const char* src, const char* dst);
};

#endif
