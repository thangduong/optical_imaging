/******************************************************************************
 *
 *  NOTE:: This module is for internal use only!!
 *  Distribution outside the company is forbidden!!
 *
 ******************************************************************************/

/******************************************************************************
 *
 * MODULE
 *       SWPAPI.H, Software Protection
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/include/swpapi.h $
 *     $Revision: 1.1 $
 *     $Modtime: 8/03/99 11:35a $
 *
 * ABSTRACT
 *       This module contains the Software Protection routines used to perform
 *       software license validation. The functions contained in this module
 *       are product independent.
 *
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ******************************************************************************/


int IFCCALL IfxSwpFieldUpdate(
	CModule *module,
	char *library_name,
	char *code,
	BOOL eAbortOnFail,
	char *authorize_code);


int IFCCALL IfxSwpOemGetDaysLeft(
	CModule *module,
	char *swp_appid,
	char *code);



int IFCCALL IfxSwpOemFieldUpdate(
	CModule *module,
	char *swp_appid,
	char *code,
	BYTE *oem_key,
	char *license);


int IFCCALL IfxSwpOemEraseLicense(
	CModule *module,
	char *swp_appid,
	char *code,
	BYTE *oem_key);

