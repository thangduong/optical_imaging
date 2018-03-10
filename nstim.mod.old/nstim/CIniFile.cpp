// CIniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "CIniFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile(const char* filename)
{
	GetCurrentDirectory(sizeof(m_Filename), m_Filename);
	strcat(m_Filename, "\\");
	strcat(m_Filename, filename);
}

CIniFile::~CIniFile()
{

}


bool CIniFile::WriteString(char* section, char* key, char* string) {
	return WritePrivateProfileString(section, key, string, m_Filename) ? true : false;
}

char* CIniFile::ReadString(char* section, char* key, char* def) {
	GetPrivateProfileString(section, key, def, m_Buff, sizeof(m_Buff), m_Filename);
	return m_Buff;
}


bool CIniFile::WriteInt(char* section, char* key, int value) {
	sprintf(m_Buff, "%d", value);
	return WriteString(section, key, m_Buff);
}

int CIniFile::ReadInt(char* section, char* key, int def) {
	sprintf(m_Buff, "%d", def);
	ReadString(section, key, m_Buff);
	return atoi(m_Buff);
}

bool CIniFile::WriteDouble(char* section, char* key, double value) {
	sprintf(m_Buff, "%f", value);
	return WriteString(section, key, m_Buff);
}

double CIniFile::ReadDouble(char* section, char* key, double def) {
	sprintf(m_Buff, "%f", def);
	ReadString(section, key, m_Buff);
	return atof(m_Buff);
}
