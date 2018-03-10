/******************************************************************************
 *
 * MODULE
 *    vixnprox.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/Vixnprxi.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/31/02 8:22a $
 *
 * ABSTRACT
 *    IFC Vixn procedures, functions and constants.
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999-2001 Imaging Technology, Inc.  All rights reserved.
 ******************************************************************************/
#ifndef _VIXNPROX_
#define _VIXNPROX_


#define VIXN_MAXARG   6	 /* max number of arguments passed to VIXN */

/*
 *	Argument Types
 */
#define vixn_tdword		0x04	/* type 32 bit dword */
#define vixn_tfloat		0x05	/* type float */
#define vixn_tdevhandle 0x06
#define vixn_tfuncname	0x0a	/* type RPC func name/ep */

typedef unsigned long DWORD;
typedef unsigned char BYTE;

typedef DWORD VIXNSRVRELE;
typedef DWORD VIXNSRVRBLOCK;

#define VIXN_NULL_SRVR_ELE 0xffffffff

typedef enum {
	VIXN_NEW_SERVER_BLOCK,
	VIXN_DEL_SERVER_BLOCK,
	VIXN_NEW_DWORD_ELE,
	VIXN_READ_DWORD_ELE,
	VIXN_WRITE_DWORD_ELE,
	VIXN_ASSIGN_ELE,
	VIXN_SRVR_LOOP_BEGIN,
	VIXN_EXIT_LOOP_WHEN,
	VIXN_SRVR_LOOP_END,
	VIXN_SRVR_IF_THEN,
	VIXN_SRVR_ELSE_DO,
	VIXN_SRVR_ENDIF,
	VIXN_PROXY_SERVER ,
	VIXN_DELETE_SERVER,
	VIXN_EXECUTE_BLOCK,
	VIXN_NEW_READ_REG_FUNC_ELE,
	VIXN_NEW_WRITE_REG_FUNC_ELE,
	VIXN_NEW_BINARY_FUNC_ELE,
	VIXN_GET_SERVER_STATE,
	VIXN_NEW_TIME_SERVER_BLOCK,
	VIXN_NEW_WRITE_PORT_ELE,
	VIXN_NEW_READ_PORT_ELE,
	VIXN_NEW_SERVER_BLOCK2,
	VIXN_ASSIGN_ARRAY_ELE,
	VIXN_NEW_READ_MEM_FUNC_ELE,
	VIXN_NEW_WRITE_MEM_FUNC_ELE,
	VIXN_READ_ARRAY_ELE,

	VIXN_NUM_RPC_FUNCS
} VIXN_RPC_FUNC;

typedef enum {
	BIT_AND_BF,		// &
	BIT_OR_BF, 		// |
	BIT_XOR_BF,		// ^
	SHIFT_RIGHT_BF, // >>
	SHIFT_LEFT_BF,	// <<
	LOG_AND_BF,		// &&
	LOG_OR_BF,		// ||
	MOD_BF,			// %
	BIT_COMP_UF,	// ~
	LOG_COMP_UF,	// !

	ARITH_ADD_BF,	// +
	ARITH_SUB_BF,	// -
	ARITH_MUL_BF,	// *
	ARITH_DIV_BF,	// /

	EQUALS_COND_BF, // ==
	NOT_EQUALS_COND_BF,			// !=
	GREATER_THAN_EQUALS_COND_BF,// >=
	GREATER_THAN_COND_BF,		// >
	LESS_THAN_EQUALS_COND_BF,	// <=
	LESS_THAN_COND_BF,			// <

	READ_TIME_MICRO_BF,
	SCHEDULE_INVOKE_BF,
	READ_INTR_EVENT_BF,
	READ_SYSTIME_MICRO_LOW_BF,
	READ_SYSTIME_MICRO_HI_BF,

	NUM_BINARY_FUNC_ENUMS
} BINARY_FUNC_ENUM;


typedef enum {
	VIXN_ARG_DWORD,
	VIXN_ARG_FLOAT
} VIXN_SRVR_ARG_TYPE;

typedef enum {
	VIXN_REG8,
	VIXN_REG16,
	VIXN_REG32
} VIXN_REG_WIDTH;


typedef struct  {
	DWORD type;		/* arg type			*/
	DWORD val;		/* value, or address of array */
} VIXN_ARG;


/*
** VIXN Function Control Block 
**
**
**  WARNING: If you change anything here, you must
**  also change the VIXN code (host/vixn/src)
**
*/
typedef struct vixn_rpc {
	DWORD ep;			/* entry point in control store 				*/
	DWORD iretval;		/* completion code - function return val		*/
	DWORD nargs;		/* total number of arguments 					*/
	VIXN_ARG vixn_arg[VIXN_MAXARG];  /* argument array, arg[0:nargs-1] */
} VIXN_RPC;




void  X_vixn_execute_block(VIXNSRVRBLOCK srv_block);

DWORD  X_vixn_del_server_block(VIXNSRVRBLOCK srv_block);
VIXNSRVRBLOCK GetGlobalBlock(VIXNSRVRBLOCK srv_block);
DWORD GetBlockProcessID(VIXNSRVRBLOCK srv_block);


#endif