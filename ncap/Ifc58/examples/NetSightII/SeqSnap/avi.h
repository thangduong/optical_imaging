/****************************************************************************
 *                                                                          *
 *  FUNCTION   : read_from_AVI_file(........)   					        *
 *                                                                          *
 *  PURPOSE    : Given a Pointer to a   buffer,						    *
 * 				 it reads a movie from the AVI file into the buffer		    *
 *                                                                          *
 *  RETURNS    : TRUE if successful, FALSE otherwise                        *
 *                                                                          *
 ****************************************************************************/

BOOL WINAPI read_from_AVI_file(UINT lstart,DWORD n_frames, LPSTR fname, 
									BYTE   *buff, BITMAPINFOHEADER *bi);

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : acquire_to_AVI_file(........)		   				        *
 *                                                                          *
 *  PURPOSE    : Saves a video frame to AVI file							*
 *                                                                          *
 *  RETURNS    : TRUE if successful, FALSE otherwise					    *
 *                                                                          *
 ****************************************************************************/
BOOL  WINAPI acquire_to_AVI_file(DWORD context,DWORD frame_seqnum,BYTE   *buff); 
/****************************************************************************
 *                                                                          *
 *  FUNCTION   : cleanup_acquire_to_AVI_file(........)				        *
 *                                                                          *
 *  PURPOSE    : De-allocates buffers, closes streams and files				*
 *                                                                          *
 ****************************************************************************/

void  WINAPI  cleanup_acquire_to_AVI_file(DWORD context);

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : setup_acquire_to_AVI_file(........)   				*
 *                                                                          *
 *  PURPOSE    : Prepare the AVI file to receive data						*
 *                                                                          *
 *  RETURNS    : a context id for the AVI save session, 0 if failure        *
 *                                                                          *
 ****************************************************************************/

DWORD WINAPI  setup_acquire_to_AVI_file(LPSTR fname, UINT dx,UINT dy,UINT bits, DWORD fps,
											UINT logical_bitmap,UINT compress_flag,
                                 			DWORD dwBytesPerSecond, DWORD fccHandler, DWORD dwQuality, 
                                 			DWORD dwKeyFrameEvery);

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : save_to_AVI_file                                           *
 *                                                                          *
 *  PURPOSE    : This routine will save the movie pointed to by buff into   *
 				 the specified AVI file.                                    *
 *                                                                          *
 *  RETURNS    : TRUE if successful, FALSE otherwise.                       *
 *                                                                          *
 ****************************************************************************/
BOOL  WINAPI save_to_AVI_file(DWORD n_frames,UINT logical_bitmap, LPSTR fname, BYTE   *buff, 
                                 UINT dx,UINT dy,UINT bits, DWORD fps,UINT compress_flag,
                                 DWORD dwBytesPerSecond, DWORD fccHandler, DWORD dwQuality, DWORD dwKeyFrameEvery);


