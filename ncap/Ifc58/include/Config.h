/******************************************************************************
 *
 * MODULE   
 *		Config.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/Config.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/01/04 10:34a $
 *
 * ABSTRACT  
 *		IFC interface of the CConfig class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_CONFIG_H__1C94D443_8905_11D1_AE6E_00A0C959E757__INCLUDED_)
#define AFX_CONFIG_H__1C94D443_8905_11D1_AE6E_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <stdio.h>
#include <CfgFile.h>
#include <ifcclass.h>


/* id == GLOBAL_SCOPE means valid throught the module cnf, rather than one
 * configuartion parameter
 */
#define GLOBAL_SCOPE -1

/*=========================================================================*/
/* Configuration symbol structure                                          */
/* used for local configuration symbol table elements                      */
/*=========================================================================*/
typedef struct _Config_Symbol {
    char    *name;      /* configuration symbol name*/
    int     id;         /* configuration symbol ID */
    unsigned long   val;/* integer value (if FLAG or PARM)*/
    int     type;       /* configuration token type: (see defns below)*/
} ConfigSymbol;

typedef enum _CnfModuleType{
	SYSTYPE,
	DMTYPE,
	CMTYPE,
	AMTYPE,
	IMTYPE,
	CMCTYPE,
	XTYPE
} CnfModuleType;

typedef struct _CnfTable {
	char *groupName;  
	char *alias;
	CnfModuleType type;
	ConfigSymbol *cnfSymbols;
	char *sub1Name;
	ConfigSymbol *sub1Symbols;
} CnfTable;

enum {          /* configuration token type*/
    IFC_GROUP       = 0,    /* group marker tok*/
    /* (group ID is determined by 'value*/
    PARM        = 1,    /* constant (argument) token */
    /* (value contained in 'value*/
    FLAG        = 2,    /*  unary token ... no arg */
    /* (value contained in 'value*/
    NUMBER      = 3,    /* parameterized token */
    /* expects 1 or more numeric integer argument */
    /* (number of args is determined by 'value')*/
    FNUMBER     = 4,    /* parameterized token */
    /* expects 1 or more numeric float argument */
    /* (number of args is determined by 'value') */
    STRING      = 5,    /* parameterized token: expects 1 string */
    DNUMBER     = 6,
    BNUMBER     = 7
};

enum {
	CFG_READ,
	CFG_WRITE
};

// The following types are used for writing config data.

typedef enum {
	
	WORD_CFG_TYPE,
	DWORD_CFG_TYPE,
	STRING_CFG_TYPE

} ConfigDataTypes;

typedef union _Config_Value {

	DWORD	dwVal;
	char    *szVal;
	WORD	wVal;

} ConfigValue;

typedef struct _Config_Item {

    int	iId;
    ConfigDataTypes	dataType;
    // pConfigValue pVal;
    ConfigValue Val;

} ConfigItem;

#define IFC_CONFIG_TOKEN_MAX_LEN 80


#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CConfig  
{
public:

	CConfig(CConfig *parent, CCfgFile *cfgFile);
	virtual ~CConfig();
	void ProcessGroup(const CnfTable *modSymTable, const int seqNum);
	void ProcessGroups(const CnfTable *modSymTable);
	void ConvertGroup(const long lStartIndex);
	BOOL ConvertParam(char *p);
	long FindGroup(const CnfTable *modSymTable, int iSeqNum, const long lStartIndex);
	long FindGroup(char *szGroupName, int &iSeqNum, const long lStartIndex);
	long FindParentGroup(const DWORD dwStartIndex);
	BOOL IsGroup(char *p);
	BOOL IsParent(char *p);
	void CfgPutc(BYTE val);
	void CfgPuts(char *p);
	BYTE CfgGetc();
	char *CfgGets();
	ConfigSymbol *GetSym (char *p, int id, char *name);
	ConfigSymbol *GetSym(int nId);
	static int NumberCvt(char *s, DWORD * number);
	static DWORD ReadHex(const char *s);
	static DWORD ReadOct(const char *s);
	static DWORD ReadBin(const char *s);
	static DWORD ReadDec(const char *s);
	int strcmpI (char *s, char *t);
	int strncmpI (char *s, char *t, int n);
	virtual pSTRING ReadStr(void);
	virtual DWORD ReadDWord(void);
	virtual int ReadType(void);
	virtual WORD ReadWord(void);
	virtual BYTE ReadByte(void);
	void WriteParentHeader(CnfTable *modSymTable, int seqNum, char *ExplicitGroupName=NULL);
	void WriteDaughterHeader(CnfTable *modSymTable, int seqNum);
	void WriteGroup(char *GroupName, WORD wSeqNum);
	void WriteData(ConfigItem *cfgItem);
	virtual void WriteStr(pSTRING str);
	virtual void WriteDWord(DWORD dwVal);
	virtual void WriteFloat(double dVal);
	virtual void WriteType(int iVal);
	virtual void WriteWord(WORD wVal);
	virtual void WriteByte(BYTE bVal);
	BOOL FindParm(ConfigSymbol *cnfSymbol, const int nId, DWORD dwVal, char *szResult);
	void WriteSectionEndComment();

	DWORD m_startIndex;	 // location of object's section in cfgFile
	static char *szParentGroupNameList[];
	char m_szOutBuf[256];

// private:

	CConfig *m_parent;
	CCfgFile *m_cfgFile;
	ConfigSymbol *m_cnfSymbols;
	short m_modType;

	char m_SrcGroupName[IFC_CONFIG_TOKEN_MAX_LEN];


	// Buffer for converted symbol data for the config text file group
	// associated with an instance of this class. Same format as output
	// of the old bincnf.exe utility.

	BYTE *m_pBinCfgData;
	DWORD m_wBinCfgDataIndex;

	// Used for writing.
	ConfigSymbol *m_curSymbol;
	DWORD m_curSymbolIndex;
	WORD m_nNumVals;
};
#endif


#if defined( __cplusplus )
extern "C" {
#endif

pCConfig IFCCALL IfxCreateCConfig(CConfig *parent, CCfgFile *cfgFile);
void IFCCALL IfxDeleteCConfig(pCConfig cfg);

#ifdef __cplusplus
}
#endif



#endif // !defined(AFX_CONFIG_H__1C94D443_8905_11D1_AE6E_00A0C959E757__INCLUDED_)
