// CNStimProfile.cpp: implementation of the CNStimProfile class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimProfile.h"


CNStimProfile* CNStimProfile::m_pStimProfile = 0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNStimProfile* CNStimProfile::GetStimProfile() { 
	return m_pStimProfile; 
}

CNStimProfile::CNStimProfile() : m_iCount(1), m_Profile("nstim.ini")
{
	m_pStimProfile = this;
	SetDefault();
}

CNStimProfile::~CNStimProfile()
{

}

ULONG __stdcall CNStimProfile::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimProfile::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (iid == IID_INStimProfile)
	{
		if (ppvObject)
		{
			AddRef();
			(*ppvObject) = this;
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	else if (iid == IID_IUnknown)
	{
		if (ppvObject)
		{
			AddRef();
			(*ppvObject) = this;
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	return hr;
}

ULONG __stdcall CNStimProfile::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

double __stdcall CNStimProfile::GetConversionFactor(const char* type) {
	double result = 0.0;
	if (strcmpi(type, "cmpd") == 0) {
		// cm per degrees
		// tan(1deg)*distanceaway
		result = m_ScreenDistance*0.01745506;
	}
	else if (strcmpi(type, "dpcm") == 0) {
		// degrees per cm
		// tan(1deg)*distanceaway
		result = 1/GetConversionFactor("cmpd");
	}
	else if (strcmpi(type, "ppcm") == 0) {
		// pixels per cm
		result = this->m_FullscreenResX/this->m_ScreenSizeX;
		if (result != this->m_FullscreenResY/this->m_ScreenSizeY)
		{
			// TODO: error aspect ratio not equal
		}
	}
	else if (strcmpi(type, "cmpp") == 0) {
		// cm per pixel
		result = 1/GetConversionFactor("ppcm");
	}
	else if (strcmpi(type, "ppd") == 0) {
		result = GetConversionFactor("ppcm")*GetConversionFactor("cmpd");
	}
	else if (strcmpi(type, "dpp") == 0) {
		result = 1/GetConversionFactor("ppd");
	}
	else {
		MessageBox(0,"invalid conversion factor", "invalid conversion factor", MB_ICONERROR);
	}
	return result;
}

double __stdcall CNStimProfile::ConvertUnit(double src, const char* srcStr, const char* destStr) {
	double result = 0.0;
	if (strcmpi(srcStr, "cpd")==0) {
		if (strcmpi(destStr, "ppc")==0) {
			result = GetConversionFactor("ppd")/src;
		}
		else {
			// TODO: error conversion not defined
		}
	}
	else if (strcmpi(srcStr, "ppc") == 0) {
		if (strcmpi(destStr, "cpd") == 0) {
			result = GetConversionFactor("ppd")/src;
		}
		else {
			// TODO: error conversion not defined
		}
	}
	else if (strcmpi(srcStr, "deg") == 0) {
		if (strcmpi(destStr, "pix") == 0) {
			result = src*GetConversionFactor("ppd");
		}
		else if (strcmpi(destStr, "cm") == 0) {
			result = src*GetConversionFactor("cmpd");
		}
		else {
			// TODO: error conversion not defined
		}
	}
	else if (strcmpi(srcStr, "pdeg") == 0) {
	}
	return result;
}
