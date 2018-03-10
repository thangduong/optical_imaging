// CIniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CINIFILE_H__9E1A97E1_BAB1_4547_BB80_2720694E79D0__INCLUDED_)
#define AFX_CINIFILE_H__9E1A97E1_BAB1_4547_BB80_2720694E79D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniFile  
{
	char m_Filename[512];
	char m_Buff[1024];
public:
	CIniFile(const char* filename = 0);
	virtual ~CIniFile();


	bool WriteString(char* section, char* key, char* string);
	char* ReadString(char* section, char* key, char* def = "");
	bool WriteInt(char* section, char* key, int value);
	int ReadInt(char* section, char* key, int def = 0);
	bool WriteDouble(char* section, char* key, double value);
	double ReadDouble(char* section, char* key, double def = 0);
};

#endif // !defined(AFX_CINIFILE_H__9E1A97E1_BAB1_4547_BB80_2720694E79D0__INCLUDED_)
