#include <windows.h>
#include "CScCap.h"
int main(int argc, char* argv[]) {
	CScCap cap;
	cap.Connect("192.168.2.14:5512");
	cap.SendCmd("master");
	cap.SendCmd("stop");
	cap.SendCmd("rawfilenametest");
	cap.SendCmd("go");
	Sleep(100000);
	cap.Disconnect();
	return 0;
}