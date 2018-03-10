#include <windows.h>
#include "mex.h"
#include "matrix.h"
//#include "master.h"
//#include "pvcam.h"
#include "CCamStreamFile.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

unsigned long ExtractUInt32FromArray(const mxArray* pNum, int index)
// This function extracts an UINT32 from a matlab array
// it automatically casts variables of other types to UINT32
{
	unsigned long result = 0;

	if (mxIsDouble(pNum))
		result = (unsigned long)(((double*)mxGetData(pNum))[index]);
	else if (mxIsInt32(pNum) || mxIsUint32(pNum))
		result = (unsigned long)(((unsigned long*)mxGetData(pNum))[index]);

	return result;
}


void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
	if (nrhs < 3)
	{
		printf("usage N = getframes(filename, start, stop, [oldstyle])\n");
	}
	else
	{	
		unsigned long start = ExtractUInt32FromArray(prhs[1], 0), stop = ExtractUInt32FromArray(prhs[2],0);

		char fname[512];
		bool bOldStyle = false;
		mxGetString(prhs[0], fname, 512);
		if (nrhs >= 4)
			bOldStyle = ExtractUInt32FromArray(prhs[3], 0) ? true : false;

		CCamStreamFile csf;
		if (csf.OpenFile(fname, true, bOldStyle))
		{
			unsigned long width, height, ebpp, bpp, xbin, ybin, frame_size;
			double expected_fps;
			csf.GetStreamInfo(width, height, ebpp, bpp, xbin, ybin, frame_size, expected_fps);

			// allocate a 2d array of size widthxheightxn
				printf("%d %d \n", width, height);
			int dim[] = { width, height, stop - start + 1 };
			mxArray* result = mxCreateNumericArray(3, dim, mxUINT16_CLASS, mxREAL);
			int dim2[] = { 2, stop - start + 1};
			mxArray* timedata = mxCreateNumericArray(2, dim2, mxDOUBLE_CLASS, mxREAL);
			void* frame = new char[frame_size];
			unsigned char* data = (unsigned char*)mxGetData(result);
			int i = 0;
			unsigned long prets, postts;
			double* time = (double*)mxGetData(timedata);
			while (i <= stop)
			{
				csf.ReadFrame(frame, prets, postts);
				if (i >= start)
				{
					memcpy(data, frame, width*height*2);
					data += width*height*2;
					(*time) = prets; time++;
					(*time) = postts; time++;
				}
				i++;
			}
			plhs[0] = result;
			plhs[1] = timedata;
			delete frame;
			csf.CloseFile();
		}
		else
			printf("failed to open file %s\n", fname);

	}
}
