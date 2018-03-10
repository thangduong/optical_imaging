// CGlobalDebug.h: interface for the CGlobalDebug class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGLOBALDEBUG_H__02239316_E931_4D57_8ED0_9E76B6CC0D6F__INCLUDED_)
#define AFX_CGLOBALDEBUG_H__02239316_E931_4D57_8ED0_9E76B6CC0D6F__INCLUDED_

#include <stdio.h>
#include "CList.h"
#define	CTQDList	CList

class CGlobalDebug  
{
	char section[512];
	char appName[512];
	struct DbgMsgFileContext
	{
		FILE* fp;
		char filename[512];
		char name[512];
	};
	CTQDList<DbgMsgFileContext*, DbgMsgFileContext*> DbgMsgContextList;

public:
	CGlobalDebug(const char* name = 0);
	virtual ~CGlobalDebug();


	void WriteDbgMsg(const char* name, const char* format, ...);
	void WriteDbgLine(const char* name, const char* format, ...);
	void WriteDbgBuff(const char* name, char* buff, int size);
	void WriteDbgTxtBuff(const char* name, char* buff, int size);
	void SetSection(const char* newSection);
	void SetAppName(const char* name);
	void Purge(const char* name);

	FILE* GetDebugFile(const char* name);
	char* GetAppName() { return appName; };
};

#endif // !defined(AFX_CGLOBALDEBUG_H__02239316_E931_4D57_8ED0_9E76B6CC0D6F__INCLUDED_)
