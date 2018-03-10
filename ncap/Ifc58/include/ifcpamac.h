/******************************************************************************
 *
 * MODULE   
 *		ifcpamac.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ifcpamac.h $
 *		$Revision: 1.1 $
 *		$Modtime: 4/20/04 1:37p $
 *
 * ABSTRACT  
 *		IFC interface of the CICamera class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c)1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_IFCPAMAC_H__962D5A85_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
#define AFX_IFCPAMAC_H__962D5A85_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#define MAKE_BRD_PARAM_CAP_TYPE(numPeculiarParams) \
	union {\
		struct {\
			IFC_PARAM_CAPS m_commonParmCaps[GEN_PARAM_END_MARKER];\
			IFC_PARAM_CAPS m_peculiarParmCaps[numPeculiarParams+1];\
		};\
		IFC_PARAM_CAPS m_paramCaps[GEN_PARAM_END_MARKER+numPeculiarParams+1];\
	}


#define ARG_LIST_END_MARKER ((char*)-1)

#define IFC_NULL_RANGE { 0,0,0,0 }

#define IFC_MAKE_ENUM(arg,rval) {#arg, arg,rval}
#define IFC_MAKE_END() {ARG_LIST_END_MARKER, IFC_LAST_SUP_PARAM,0}

#define MAKE_ENUM_ENTRY1(param,prettyName,ArrayDim,GroupMask,val1,rval1,reg1,reg2)\
	 {param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_END(), },IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }

#define MAKE_ENUM_ENTRY2(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,reg1,reg2)\
	 {param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_ENUM(val2,rval2),IFC_MAKE_END(), },IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }

#define MAKE_ENUM_ENTRY3(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,reg1,reg2)\
	 {param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_ENUM(val2,rval2),IFC_MAKE_ENUM(val3,rval3),IFC_MAKE_END(), },IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }

#define MAKE_ENUM_ENTRY4(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,reg1,reg2)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_ENUM(val2,rval2),\
	IFC_MAKE_ENUM(val3,rval3),IFC_MAKE_ENUM(val4,rval4),IFC_MAKE_END(), },IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }

#define MAKE_ENUM_ENTRY5(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,reg1,reg2)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_ENUM(val2,rval2),\
	IFC_MAKE_ENUM(val3,rval3),IFC_MAKE_ENUM(val4,rval4),IFC_MAKE_ENUM(val5,rval5),IFC_MAKE_END(), },\
	IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }

#define MAKE_ENUM_ENTRY6(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,reg1,reg2)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_ENUM(val2,rval2),\
	IFC_MAKE_ENUM(val3,rval3),IFC_MAKE_ENUM(val4,rval4),IFC_MAKE_ENUM(val5,rval5),IFC_MAKE_ENUM(val6,rval6),IFC_MAKE_END(), },\
	IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }

#define MAKE_ENUM_ENTRY7(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,reg1,reg2)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_ENUM(val2,rval2),\
	IFC_MAKE_ENUM(val3,rval3),IFC_MAKE_ENUM(val4,rval4),IFC_MAKE_ENUM(val5,rval5),IFC_MAKE_ENUM(val6,rval6),IFC_MAKE_ENUM(val7,rval7),IFC_MAKE_END(), },\
	IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }

#define MAKE_ENUM_ENTRY8(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,reg1,reg2)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_ENUM(val2,rval2),\
	IFC_MAKE_ENUM(val3,rval3),IFC_MAKE_ENUM(val4,rval4),IFC_MAKE_ENUM(val5,rval5),IFC_MAKE_ENUM(val6,rval6),IFC_MAKE_ENUM(val7,rval7),IFC_MAKE_ENUM(val8,rval8),IFC_MAKE_END(), },\
	IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }

#define MAKE_ENUM_ENTRY9(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,reg1,reg2)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_ENUM(val2,rval2),\
	IFC_MAKE_ENUM(val3,rval3),IFC_MAKE_ENUM(val4,rval4),IFC_MAKE_ENUM(val5,rval5),IFC_MAKE_ENUM(val6,rval6),IFC_MAKE_ENUM(val7,rval7),IFC_MAKE_ENUM(val8,rval8),IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_END(), },\
	IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }

#define MAKE_ENUM_ENTRY10(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,reg1,reg2)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask, { IFC_MAKE_ENUM(val1,rval1),IFC_MAKE_ENUM(val2,rval2),\
	IFC_MAKE_ENUM(val3,rval3),IFC_MAKE_ENUM(val4,rval4),IFC_MAKE_ENUM(val5,rval5),IFC_MAKE_ENUM(val6,rval6),IFC_MAKE_ENUM(val7,rval7),IFC_MAKE_ENUM(val8,rval8),IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),IFC_MAKE_END(), },\
	IFC_NULL_RANGE,NULL,{reg1,reg2},IfxRegGetEnumParam,IfxRegSetEnumParam }


#define MAKE_ENUM_SPEC_ENTRY1(param,prettyName,ArrayDim,GroupMask,val1,rval1,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY2(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY3(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY4(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY5(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY6(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY7(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY8(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY9(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),IFC_MAKE_ENUM(val9,rval9),  IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY10(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),   IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY11(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,val11,rval11,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),\
	IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),IFC_MAKE_ENUM(val11,rval11), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY12(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,val11,rval11,val12,rval12,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),\
	IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),IFC_MAKE_ENUM(val11,rval11),IFC_MAKE_ENUM(val12,rval12),  IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY13(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,val11,rval11,val12,rval12,val13,rval13,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),\
	IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),IFC_MAKE_ENUM(val11,rval11),IFC_MAKE_ENUM(val12,rval12),IFC_MAKE_ENUM(val13,rval13), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_ENTRY14(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,val11,rval11,val12,rval12,val13,rval13,val14,rval14,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),\
	IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),IFC_MAKE_ENUM(val11,rval11),IFC_MAKE_ENUM(val12,rval12),\
	IFC_MAKE_ENUM(val13,rval13),IFC_MAKE_ENUM(val14,rval14), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc}



#define MAKE_ENUM_SPEC_REG_ENTRY1(param,prettyName,ArrayDim,GroupMask,val1,rval1,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY2(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY3(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY4(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY5(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY6(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY7(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY8(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY9(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),IFC_MAKE_ENUM(val9,rval9),  IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY10(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),   IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY11(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,val11,rval11,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),\
	IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),IFC_MAKE_ENUM(val11,rval11), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define MAKE_ENUM_SPEC_REG_ENTRY12(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,val11,rval11,val12,rval12,reg1,reg2,GetFunc,SetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),\
	IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),IFC_MAKE_ENUM(val11,rval11),IFC_MAKE_ENUM(val12,rval12),  IFC_MAKE_END(),},\
	IFC_NULL_RANGE,NULL,{reg1,reg2},GetFunc,SetFunc}

#define IFC_MAKE_FLOAT_ENTRY(param,prettyName,ArrayDim,GroupMask, min, max, step,regBaseVal, reg1, reg2)\
	{param,prettyName, #param, IFC_FLOAT_TYPE, ArrayDim,GroupMask, {{NULL,0,0},} , {min, max, step, regBaseVal},\
	NULL,{reg1,reg2},IfxRegGetRangeParam,IfxRegSetRangeParam }

#define MAKE_FLOAT_SPEC_ENTRY(param,prettyName,ArrayDim,GroupMask, min, max, step,regBaseVal, GetFunc, SetFunc)\
	{param,prettyName, #param, IFC_FLOAT_TYPE, ArrayDim,GroupMask, {{NULL,0,0},} , {min, max, step, regBaseVal},\
	NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc,SetFunc }


#define MAKE_ENUM_RO_ENTRY1(param,prettyName,ArrayDim,GroupMask,val1,rval1,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY2(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY3(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY4(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY5(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY6(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY7(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4), IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY8(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY9(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),IFC_MAKE_ENUM(val9,rval9),  IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY10(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),   IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY11(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,val11,rval11,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),\
	IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),IFC_MAKE_ENUM(val11,rval11), IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define MAKE_ENUM_RO_ENTRY12(param,prettyName,ArrayDim,GroupMask,val1,rval1,val2,rval2,val3,rval3,val4,rval4,val5,rval5,val6,rval6,val7,rval7,val8,rval8,val9,rval9,val10,rval10,val11,rval11,val12,rval12,GetFunc)\
	{param,prettyName, #param, IFC_ENUM_TYPE,ArrayDim,GroupMask,\
	{IFC_MAKE_ENUM(val1,rval1), IFC_MAKE_ENUM(val2,rval2), IFC_MAKE_ENUM(val3,rval3), IFC_MAKE_ENUM(val4,rval4),\
	IFC_MAKE_ENUM(val5,rval5), IFC_MAKE_ENUM(val6,rval6), IFC_MAKE_ENUM(val7,rval7), IFC_MAKE_ENUM(val8,rval8),\
	IFC_MAKE_ENUM(val9,rval9),IFC_MAKE_ENUM(val10,rval10),IFC_MAKE_ENUM(val11,rval11),IFC_MAKE_ENUM(val12,rval12),  IFC_MAKE_END(),},\
	IFC_NULL_RANGE,IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}


#define IFC_MAKE_INTEGER_ENTRY(param,prettyName,ArrayDim,GroupMask, min, max, step,regBaseVal, reg1, reg2)\
	{param,prettyName, #param, IFC_INTEGER_TYPE, ArrayDim,GroupMask, {{NULL,0,0},}, {min, max, step, regBaseVal},\
	NULL,{reg1,reg2},IfxRegGetRangeParam,IfxRegSetRangeParam }

#define MAKE_INTEGER_SPEC_ENTRY(param,prettyName,ArrayDim,GroupMask, min, max, step,regBaseVal, GetFunc, SetFunc)\
	{param,prettyName, #param, IFC_INTEGER_TYPE, ArrayDim,GroupMask, {{NULL,0,0},}, {min, max, step, regBaseVal},\
	NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, SetFunc}

#define MAKE_INTEGER_RO_ENTRY(param,prettyName,ArrayDim,GroupMask, min, max, step,regBaseVal)\
	{param,prettyName, #param, IFC_INTEGER_TYPE, ArrayDim,GroupMask, {{NULL,0,0},}, {min, max, step, regBaseVal},\
	IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},IfxRegGetRangeParam, NULL}

#define MAKE_INTEGER_RO_SPEC_ENTRY(param,prettyName,ArrayDim,GroupMask, min, max, step,regBaseVal, GetFunc)\
	{param,prettyName, #param, IFC_INTEGER_TYPE, ArrayDim,GroupMask, {{NULL,0,0},}, {min, max, step, regBaseVal},\
	IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}

#define   MAKE_FLOAT_RO_SPEC_ENTRY(param,prettyName,ArrayDim,GroupMask, min, max, step,regBaseVal, GetFunc)\
	{param,prettyName, #param, IFC_FLOAT_TYPE, ArrayDim,GroupMask, {{NULL,0,0},} , {min, max, step, regBaseVal},\
	IFC_PARAMCAP_READ_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, NULL}


#define MAKE_INTEGER_WO_ENTRY(param,prettyName,ArrayDim,GroupMask, min, max, step,regBaseVal, reg1, reg2)\
	{param,prettyName, #param, IFC_INTEGER_TYPE, ArrayDim,GroupMask, {{NULL,0,0},}, {min, max, step, regBaseVal},\
	IFC_PARAMCAP_WRITE_ONLY,{reg1,reg2},NULL,IfxRegSetRangeParam }

#define MAKE_INTEGER_WO_SPEC_ENTRY(param,prettyName,ArrayDim,GroupMask, min, max, step,regBaseVal, SetFunc)\
	{param,prettyName, #param, IFC_INTEGER_TYPE, ArrayDim,GroupMask, {{NULL,0,0},}, {min, max, step, regBaseVal},\
	IFC_PARAMCAP_WRITE_ONLY,{IFC_SPEC_REGID,IFC_SPEC_REGID}, NULL,SetFunc}


#define MAKE_STRING_SPEC_ENTRY(param,prettyName,ArrayDim,GroupMask, GetFunc, SetFunc)\
	{param,prettyName, #param, IFC_STRING_TYPE, ArrayDim,GroupMask, {{NULL,0,0},}, {0, 0, 0, 0},\
	NULL,{IFC_SPEC_REGID,IFC_SPEC_REGID},GetFunc, SetFunc}


#define IFC_PARM_NULL { 0,0 }
#define IFC_PARM1(val1) { (val1),0 }
#define IFC_PARM2(val1,val2) { (val1),(val2) }

#define IFC_NULL_REGID 0xfffffffful
#define IFC_SPEC_REGID 0xfffffffeul

#define IFC_FIND_NEXT_PARAM(gOrder,paramID)\
	{ int i;\
		for (i=0; gOrder[i] != paramID && gOrder[i] != IFC_LAST_SUP_PARAM; i++);\
		if (gOrder[i] == paramID )\
			return gOrder[i+1];\
	}


#ifndef __IfcCmn_FWD_DEFINED__

// Enum types which are to be idl file accessible
typedef enum tagIFC_FRAME_ENCODE {
	IFC_FRAME_NO_ENCODE=0,
	IFC_FRAME_JPEG_ENCODE=1,

	IFC_FRAME_NUM_ENCODES=2
} IFC_FRAME_ENCODE;

#endif


#ifdef __cplusplus
typedef BOOL (IFCAPI *PF_IFC_PARAM_QUERYUI)(CICamera *pCamera,double &dVal, ACQ_PARAMS_TYPE paramID, DWORD index,void *pParentCWnd);

typedef BOOL (IFCAPI *PF_IFC_PARAM_GROUP_EDITDLG)(CICamera *pCamera, IFC_PARAM_GROUP_TYPE GroupID, void *pParentCWnd,ACQ_PARAMS_TYPE focalParam);


#define IFC_MAKE_PARAM_QUI_DECL(modName,param) \
	extern "C" BOOL IFCCALL	modName##param##_QueryUI(CICamera *pCamera, double &dVal, ACQ_PARAMS_TYPE paramID, DWORD index,void *pParentCWnd)

#define IFC_MAKE_PGROUP_EDITDLG_DECL(modName,paramGroup) \
	extern "C" BOOL IFCCALL	modName##paramGroup##_EditDlg(CICamera *pCamera, IFC_PARAM_GROUP_TYPE GroupID, void *pParentCWnd, ACQ_PARAMS_TYPE focalParam)



#endif


#endif // !defined(AFX_IFCPAMAC_H__962D5A85_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
