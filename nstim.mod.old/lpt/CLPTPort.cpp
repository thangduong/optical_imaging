// CLPTPort.cpp: implementation of the CLPTPort class.
//
//////////////////////////////////////////////////////////////////////

#include "CLPTPort.h"
#include <windows.h>
#include <conio.h>
#include "WinIo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

unsigned long CLPTPort::IOBaseAddr[] = 
{
0x0408,
0x040A,
0x040C,
0x040E
};


CLPTPort::CLPTPort(int portNum)
{
	SetPortNum(portNum);
}

CLPTPort::~CLPTPort()
{

}

unsigned long CLPTPort::ReadMem(unsigned long mem) {
	//if (IsWinNtFamily()) {
		unsigned long res;
		GetPhysLong((unsigned char*)mem, &res);
		return res;
	//}
	//else {
	//	return (*((unsigned long*)mem));
	//}
}

unsigned long CLPTPort::inport(unsigned short port) {
//	if (IsWinNtFamily()) {
		unsigned long res;
		GetPortVal(port, &res, 1);
		return res;
//	}
//	else {
//		return _inpd(port);
//	}
}

void CLPTPort::outport(unsigned short port, unsigned long value) {
//	if (IsWinNtFamily()) {
		SetPortVal(m_ulIOBase, m_ulData, 1);
//	}
//	else {
//		_outpd(port, value);
//	}
}

void CLPTPort::SetPortNum(int portNum) {

	m_iPortNum = portNum;

	if ((portNum >= 0) && (portNum <= 3)) {
		m_ulIOBase = IOBaseAddr[portNum];
	}
	else
		m_ulIOBase = 0;

	if (m_ulIOBase > 0) {
		m_ulIOBase = ReadMem(m_ulIOBase);

//		GetPortVal(m_ulIOBase, &m_ulData, 1);
		m_ulData = 0;
		outport(m_ulIOBase, m_ulData);
//		SetPortVal(m_ulIOBase, m_ulData, 1);
	}
}

void CLPTPort::SetBit(int bit, bool value) {
	if (value) {
		m_ulData |= (1<<bit);
	}
	else {
		m_ulData &= ~(1<<bit);
	}
	outport(m_ulIOBase, m_ulData);
//	SetPortVal(m_ulIOBase, m_ulData, 1);
}

void CLPTPort::ToggleBit(int bit) {
	SetBit(bit, (m_ulData&(1<<bit))?false:true);
}

void CLPTPort::Init() {
//	if (IsWinNtFamily()) {
		if (!InitializeWinIo()) {
//			InstallWinIoDriver("WinIo.sys", false);
//			StartWinIoDriver();
			MessageBox(0, "can't init winio", "can't init winio", MB_ICONERROR);
			ExitProcess(-1);
		}
//	}
}
