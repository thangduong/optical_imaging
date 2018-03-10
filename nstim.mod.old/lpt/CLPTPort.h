// CLPTPort.h: interface for the CLPTPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLPTPORT_H__57199140_8C58_4D88_868F_5682C6CB1C29__INCLUDED_)
#define AFX_CLPTPORT_H__57199140_8C58_4D88_868F_5682C6CB1C29__INCLUDED_

 class CLPTPort  
{
	static unsigned long IOBaseAddr[];
	unsigned long m_ulIOBase;
	unsigned long m_ulData;
	int m_iPortNum;
/*
	static bool IsWinNtFamily() {
		// returns true if we're running on windows NT+
		// meaning that we can't access ports w/o winio
		DWORD ver = GetVersion();

		return (ver & 0x8000) ? false : true;
	}
*/
	unsigned long ReadMem(unsigned long mem);
	unsigned long inport(unsigned short port);
	void outport(unsigned short port, unsigned long value);
public:
	CLPTPort(int portNum = -1);
	virtual ~CLPTPort();

	void SetPortNum(int portNum);
	void SetBit(int bit, bool value);
	void ToggleBit(int bit);

	static void Init();
};

#endif // !defined(AFX_CLPTPORT_H__57199140_8C58_4D88_868F_5682C6CB1C29__INCLUDED_)
