////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// getkernellocation.cpp
//
//    code to get location of kernels.  type 'help getkernellocation' in matlab for additional info.
//
// REVISION HISTORY
//
// Thang Duong	1/20/2004	Added this comment in the header.  Everything should be working, I think.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "mex.h"
#include "matrix.h"
#include "matlabaux.h"

#ifdef _WIN32
#include <windows.h>
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
#endif

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
	if (nrhs != 3)
	{
		mexEvalString("help getkernellocation;");
	}
	else
	{
		unsigned long order = maGetUINT32Element(prhs[0], 0);
		unsigned long seed = maGetUINT32Element(prhs[1], 0);
		unsigned long kernel_order_minus_one = mxGetNumberOfElements(prhs[2]);

		// there is probably a nice way to figure this out, but 
		// i am just going to brute force it since it doesn't take very long
		// and i am kinda tired.

		unsigned long pattern = 1;
		unsigned long current_order_minus_one = 1;
		unsigned long reg1 = 1, reg2;
		unsigned long size = 1 << order;

		long* deltas = new long[kernel_order_minus_one];
		// shift everything forward so i won't have to cycle through the m-seq to search
		// for patterns to mask
		int i, j;
		long min = maGetINT32Element(prhs[2], 0);
		for (i = 0; i < kernel_order_minus_one; i++)
		{
			deltas[i] = maGetINT32Element(prhs[2], i);
			if (deltas[i]<min)
				min = deltas[i];
		}

		for (i = 0; i < kernel_order_minus_one; i++)
			deltas[i] -= min;

		// bit counter! -- TODO: use permanent lookup table for this!
		unsigned long* newbit = new unsigned long[size];
		for (i = 0; i < size; i++)
		{
			unsigned long j;	
			newbit[i] = 0;
			for (j = 0; j < order; j++)
				newbit[i] += ((1<<j)&i) ? 1 : 0;
			newbit[i] = (newbit[i] % 2) << (order - 1);
		}

		unsigned long outputmask = size - 1;	

		// use Sutter's generating register method
		// see Sutter's section in (Marmarelis 1987, Vol I)
		for (i = 1; i < size; i++)
		{
			if (current_order_minus_one == kernel_order_minus_one)
				break;
//			printf("reg1[%d] = %d\n", i, (reg1 & outputmask));
			reg2 = reg1 & seed;
			reg1 = (reg1 >> 1)+newbit[reg2];

			for (j = 0; j < kernel_order_minus_one; j++)
			{
				if (deltas[j] == i)
				{
					pattern = pattern ^ (reg1 & outputmask);
					current_order_minus_one++;
				}
			}
		}

		reg1 = 1;

		for (i = 0; i < size; i++)
		{
//			printf("reg1[%d] = %d newbit[%d] = %d\n", i, (reg1 & outputmask), reg2, newbit[reg2]);
			if ((reg1 & outputmask) == pattern)
			{
				break;
			}
			reg2 = reg1 & seed;
			reg1 = (reg1 >> 1)+newbit[reg2];

		}
//		printf("pattern = %d (%08x) i = %d\n", pattern, pattern, i);
		delete [] newbit;


		// result is i + min
		int dim[] = {1, 1};
		plhs[0] = mxCreateNumericArray(2,dim,mxDOUBLE_CLASS,mxREAL);

		double* pResult = (double*)mxGetData(plhs[0]);
		(*pResult) = i + min;
	}	
}
