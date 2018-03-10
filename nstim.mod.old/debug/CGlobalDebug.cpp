// CGlobalDebug.cpp: implementation of the CGlobalDebug class.
//
//////////////////////////////////////////////////////////////////////

#include "CGlobalDebug.h"
#include <stdio.h>
#include <string.h>
#include <memory.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define	mkdir(x,y)	_mkdir(x)
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif
#include <stdarg.h>
#include "CUtil.h"

CGlobalDebug debug;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlobalDebug::CGlobalDebug(const char* name)
{
	if (name)
		SetAppName(name);
}

void CGlobalDebug::SetAppName(const char* name)
{
	strcpy(appName, name);

	char temp[512];
#ifdef _WIN32
	sprintf(temp, "c:\\temp\\%s\\%s", appName, name);
#else
	sprintf(temp, "/tmp/%s", appName);
#endif

	mkdir(temp,0xfff);

	SetSection("default");
}


void CGlobalDebug::SetSection(const char* newSection)
{
	strcpy(section, newSection);
	char temp[512];
#ifdef _WIN32
	sprintf(temp, "c:\\temp\\%s\\%s", appName, section);
#else
	sprintf(temp, "/tmp/%s/%s", appName, section);
#endif
	mkdir(temp,0xfff);
}


CGlobalDebug::~CGlobalDebug()
{
	POSITION Pos = DbgMsgContextList.GetHeadPosition();
	DbgMsgFileContext* pContext = NULL;
	while (Pos)
	{
		pContext = DbgMsgContextList.GetNext(Pos);
		if (pContext->fp)
			fclose(pContext->fp);
		delete pContext;
	}
}

void CGlobalDebug::Purge(const char* name) {
//	printf("looking for file: %s\r\n", name);
	POSITION Pos = DbgMsgContextList.GetHeadPosition();
	DbgMsgFileContext* pContext = NULL;
	POSITION ContextPosition;
	while (Pos)
	{
		ContextPosition = Pos;
		DbgMsgFileContext* pCurContext = DbgMsgContextList.GetNext(Pos);
		if (CUtil::u_strcmpi(pCurContext->name, name) == 0)
		{
			pContext = pCurContext;
			break;
		}
	}
	if (pContext) {
		DbgMsgContextList.RemoveAt(ContextPosition);
		fclose(pContext->fp);
		delete pContext;
	}
	else {
		char msg[512];
		sprintf(msg, "trying to purge file %s that doesn't exist\r\n", name);
#ifdef _WIN32
		OutputDebugString(msg);
#endif
	}
}

FILE* CGlobalDebug::GetDebugFile(const char* name)
{
//	printf("looking for file: %s\r\n", name);
	POSITION Pos = DbgMsgContextList.GetHeadPosition();
	DbgMsgFileContext* pContext = NULL;
	while (Pos)
	{
		DbgMsgFileContext* pCurContext = DbgMsgContextList.GetNext(Pos);
		if (CUtil::u_strcmpi(pCurContext->name, name) == 0)
		{
			pContext = pCurContext;
			break;
		}
	}
	if (pContext)
	{
	}
	else
	{
		// add a new context
		pContext = new DbgMsgFileContext;
		strcpy(pContext->name, name);
#ifdef _WIN32
		sprintf(pContext->filename, "c:\\temp\\%s\\%s\\%s", appName, section, name);
//		printf("wfilename: %s\r\n", (pContext->filename));
#else
		sprintf(pContext->filename, "/tmp/%s/%s/%s", appName, section, name);
//		printf("filename: %s\r\n", (pContext->filename));
#endif
		pContext->fp = fopen(pContext->filename, "wb");

		DbgMsgContextList.AddTail(pContext);
	}
	if (pContext)
		return pContext->fp;
	else
		return 0;
}

void CGlobalDebug::WriteDbgMsg(const char* name, const char* format, ...)
{
	FILE* fp = GetDebugFile(name);

	if (fp)
	{
		va_list arguments;
		va_start(arguments, format);
		vfprintf(fp, format, arguments);
		va_end(arguments);
		fflush(fp);
	}
}
void CGlobalDebug::WriteDbgLine(const char* name, const char* format, ...)
{
	FILE* fp = GetDebugFile(name);

	if (fp)
	{
		va_list arguments;
		va_start(arguments, format);
		vfprintf(fp, format, arguments);
		va_end(arguments);
		fprintf(fp, "\r\n");
		fflush(fp);
	}
}

void CGlobalDebug::WriteDbgBuff(const char* name, char* buff, int size)
{
	//. TODO:
	FILE* fp = GetDebugFile(name);
	if (fp)
	{
		fwrite(buff, size, 1, fp);
		fflush(fp);
	}
}

void CGlobalDebug::WriteDbgTxtBuff(const char* name, char* buff, int size)
{
	FILE* fp = GetDebugFile(name);
	if (fp)
	{
		for (int i = 0; i < size; i++)
			fprintf(fp, "%c", buff[i]);
		fflush(fp);
	}
}
