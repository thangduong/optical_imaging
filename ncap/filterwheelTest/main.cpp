#include <windows.h>
#include <stdio.h>
#include "../../nstim/lpt/CLPTPort.h"

int main(int argc, char* argv[]){
	CLPTPort::Init();
	CLPTPort p(0);
	p.SetBit(0,1);
	while (1) {
		Sleep(1000);
		p.SetBit(0,0);
		Sleep(10);
		p.SetBit(0,1);
	}
	return 0;
}