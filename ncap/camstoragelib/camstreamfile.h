////////////////////////////////////////////////////////////////////////////////////////////////////
//	CAMSTREAMFILE.H
//
//	This file contains headers defining the file format of .CSF files.  
//
//  REVISION HISTORY
//  
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMSTREAMFILE_H
#define CAMSTREAMFILE_H

#pragma pack(push,1)

struct CCDInfoType
{
	char desc[512];
	unsigned long well_size;			// in electrons
	unsigned long adc_speed;			// in hertz
};


// This is an older header!
// All the new code should use the header below!
struct CamStreamFileHdrOld
{
	unsigned long magic;				// magic #, should be VTQD
	unsigned long width;				// width of the image (in num of pixels)
	unsigned long height;				// height of the image (in num of pixels)
	unsigned long ebpp;					// effective bpp (12 bits generally)
	unsigned long bpp;					// # of bits per pixel (should be 16 most of the time)
	unsigned long xbin;					// binning information (width and height are AFTER binning)
	unsigned long ybin;
	unsigned long frame_size;			// # of bytes per frame -- including padding and what not
	LARGE_INTEGER timestamp_freq;		// frequency of the timestamp
	double expected_fps;				// expected # of frames per second
	CCDInfoType CCDInfo;				// information on the CCD
	unsigned long bytes_to_skip;		// # of bytes to skip after this header to start data
};

struct CamStreamFileHdr
{
	unsigned long magic;				// magic #, should be VTQD
	unsigned long version;				// version # -- should start with 0
	unsigned long width;				// width of the image (in num of pixels)
	unsigned long height;				// height of the image (in num of pixels)
	unsigned long ebpp;					// effective bpp (12 bits generally)
	unsigned long bpp;					// # of bits per pixel (should be 16 most of the time)
	unsigned long pixeltype;			// type of the pixel -- see below for more info
	unsigned long xbin;					// binning information (width and height are AFTER binning)
	unsigned long ybin;
	unsigned long frame_size;			// # of bytes per frame -- including padding and what not
	LARGE_INTEGER timestamp_freq;		// frequency of the timestamp
	double expected_fps;				// expected # of frames per second
	CCDInfoType CCDInfo;				// information on the CCD
	unsigned long bytes_to_skip;		// # of bytes to skip after this header to start data
	unsigned long reserved;
};


#define	PIXELTYPE_WORD					0
#define	PIXELTYPE_DWORD					1
#define	PIXELTYPE_FLOAT					2
#define	PIXELTYPE_DOUBLE				3
#define	PIXELTYPE_BYTE					4


#define	CUR_CSF_VERSION					0

#pragma pack(pop)
#endif