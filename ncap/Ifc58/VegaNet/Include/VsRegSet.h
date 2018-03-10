/******************************************************************************
 *
 * MODULE   
 *		PMRegSet.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/VsRegSet.h $
 *		$Revision: 1.1 $
 *		$Modtime: 6/15/04 9:22a $
 *
 * ABSTRACT  
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2004 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/


#pragma once


/////////////////////////////////////////////////////////////////////////////


class CRegSettings {
public:  // Constructors/destructor
   CRegSettings() : m_hkeySubkey(NULL) { };

   CRegSettings(BOOL fReadOnly, HKEY hkeyRoot, LPCTSTR pszSubkey)
      : m_hkeySubkey(NULL) {
      OpenSubkey(fReadOnly, hkeyRoot, pszSubkey);
   }

   ~CRegSettings() { CloseKey(); }


public:  // Opening/closing registry subkey functions
   operator HKEY() const { return(m_hkeySubkey); }

   LONG OpenSubkey(BOOL fReadOnly, HKEY hkeyRoot, LPCTSTR pszSubkey,DWORD *dwDisposition=NULL) {
      CloseKey();
      LONG lErr;
      if (fReadOnly) {
         lErr = ::RegOpenKeyEx(hkeyRoot, pszSubkey, 0, 
            KEY_READ, &m_hkeySubkey); 
      } else {
         ;
         lErr = RegCreateKeyEx(hkeyRoot, pszSubkey, 0, NULL, 
            REG_OPTION_NON_VOLATILE, KEY_QUERY_VALUE | KEY_SET_VALUE, 
            NULL, &m_hkeySubkey, dwDisposition);
      }
      return(lErr);
   }

   void CloseKey() {
      if (m_hkeySubkey != NULL) { 
         ::RegCloseKey(m_hkeySubkey); 
         m_hkeySubkey = NULL;
      }
   }


public:  // Reading/writing registry value functions
   LONG GetDWORD(LPCTSTR pszValName, PDWORD pdw) const {
      DWORD cbData = sizeof(pdw);
      return(GetVal(pszValName, (PBYTE) pdw, &cbData));
   }

   LONG SetDWORD(LPCTSTR pszValName, DWORD dw) const {
      return(SetVal(pszValName, REG_DWORD, (BYTE*) &dw, sizeof(dw)));
   }


   LONG GetString(LPCTSTR pszValName, LPTSTR psz, int nMaxSize) const {
      DWORD cbData = nMaxSize;
      return(GetVal(pszValName, (PBYTE) psz, &cbData));
   }

   LONG SetString(LPCTSTR pszValName, LPCTSTR psz) const {
      return(SetVal(pszValName, REG_SZ, (PBYTE) psz, 
         sizeof(TCHAR) * (lstrlen(psz) + 1)));
   }

   
   LONG GetMultiString(LPCTSTR pszValName, LPTSTR psz, int nMaxSize) const {
      return(GetString(pszValName, psz, nMaxSize));
   }

   LONG SetMultiString(LPCTSTR pszValName, LPCTSTR psz) const {
      for (DWORD cch = 0; psz[cch] != 0; cch += 1 + lstrlen(&psz[cch])) ;
      return(SetVal(pszValName, REG_MULTI_SZ, (PBYTE) psz, 
         sizeof(TCHAR) * (cch + 1)));
   }

   
   LONG GetBinary(LPCTSTR pszValName, PBYTE pb, PDWORD pcbData) const {
      return(GetVal(pszValName, pb, pcbData));
   }

   LONG SetBinary(LPCTSTR pszValName, CONST BYTE* pb, int nSize) const {
      return(SetVal(pszValName, REG_BINARY, pb, nSize));
   }

   LONG GetSize(LPCTSTR pszValName, PDWORD pdw) {
      return(GetVal(pszValName, NULL, pdw));
   }


private:
   HKEY  m_hkeySubkey;
private:
   LONG GetVal(LPCTSTR pszValName, PBYTE pbData, PDWORD pcb) const {
      return(::RegQueryValueEx(m_hkeySubkey, pszValName, 
         NULL, NULL, pbData, pcb));
   }

   LONG SetVal(LPCTSTR pszValName, DWORD dwType, CONST BYTE *pbData, DWORD cb) const {
      return(::RegSetValueEx(m_hkeySubkey, pszValName, 
         0, dwType, pbData, cb));
   }
};


//////////////////////////////// End of File //////////////////////////////////
