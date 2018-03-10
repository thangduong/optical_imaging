// testapp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "CCamStreamFile.h"
#include "CLPTPort.h"


int main(int argc, char* argv[])
{
	CLPTPort p;

	p.Init();
	p.SetPortNum(0);
	while (1){
		printf("Switch\r\n");
		p.SetBit(6,0);
		Sleep(1000);
		p.SetBit(6,1);
//		p.ToggleBit(6);
		Sleep(1000);
	} 
	return -1;
	CCamStreamFile cf;
	char temp[512];

	cf.OpenFile("c:\\test.csf", false);

	cf.WriteTimestamp();
	cf.WriteData(temp, 512);
	cf.WriteTimestamp();
	cf.WriteTimestamp();
	cf.WriteData(temp, 512);
	cf.WriteTimestamp();

	cf.CloseFile();

		cf.OpenFile("c:\\test.csf", false);

	cf.WriteTimestamp();
	cf.WriteData(temp, 512);
	cf.WriteTimestamp();
	cf.WriteTimestamp();
	cf.WriteData(temp, 512);
	cf.WriteTimestamp();

	cf.CloseFile();

	printf("all done\r\n");
	return 0;
}
