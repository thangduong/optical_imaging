/******************************************************************************
 *
 * MODULE
 *    vixnserv.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/Vixnsrvi.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/30/02 6:56p $
 *
 * ABSTRACT
 *    IFC Vixn procedures, functions and constants.
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 ******************************************************************************/
#ifndef _VIXNSERV_
#define _VIXNSERV_

#include <vixnprxi.h>

typedef struct {
	DWORD devHandle;
	DWORD devDomainHBlock;
} VIXSRVRBLK,*PVIXSRVRBLK;


typedef struct {
	PVIXSRVRBLK entryBlock;
	DWORD devDomainHServer;
} VIXNSERVER,*PVIXNSERVER;




/* Support Functions not part of API */
 PVIXSRVRBLK IFCCALL vixn_new_server_block(HANDLE h_driver,DWORD intrEvent,PVIXSRVRBLK global_blk,DWORD ProcessID);
 PVIXSRVRBLK IFCCALL vixn_new_server_block2(HANDLE h_driver,DWORD intrEvent,DWORD intrEvent2,PVIXSRVRBLK global_blk,DWORD ProcessID);
 PVIXSRVRBLK IFCCALL vixn_new_time_server_block (HANDLE h_driver,DWORD microSeconds, DWORD InvokeCount, PVIXSRVRBLK global_blk,DWORD ProcessID);


 void IFCCALL vixn_del_server_block(PVIXSRVRBLK srvr_blk);

 VIXNSRVRELE IFCCALL vixn_new_dword_ele(PVIXSRVRBLK srv_block, DWORD initial_value);

 DWORD IFCCALL vixn_read_dword_ele(PVIXSRVRBLK srv_block, VIXNSRVRELE ele);

 void IFCCALL vixn_write_dword_ele(PVIXSRVRBLK srv_block, VIXNSRVRELE ele, DWORD val);

 VIXNSRVRELE IFCCALL vixn_assign_ele(PVIXSRVRBLK srv_block, VIXNSRVRELE lvalue, VIXNSRVRELE rvalue);

 VIXNSRVRELE IFCCALL vixn_srvr_loop_begin(PVIXSRVRBLK srv_block);

 VIXNSRVRELE IFCCALL vixn_exit_loop_when(PVIXSRVRBLK srv_block, VIXNSRVRELE condition);

 VIXNSRVRELE IFCCALL vixn_srvr_loop_end(PVIXSRVRBLK srv_block);

 VIXNSRVRELE IFCCALL vixn_srvr_if_then(PVIXSRVRBLK srv_block, VIXNSRVRELE condition);

 VIXNSRVRELE IFCCALL vixn_srvr_else_do(PVIXSRVRBLK srv_block);

 VIXNSRVRELE IFCCALL vixn_srvr_endif(PVIXSRVRBLK srv_block);

 PVIXNSERVER IFCCALL vixn_proxy_server ( PVIXSRVRBLK srv_block );
 void IFCCALL vixn_delete_server(PVIXNSERVER server_to_del);
 DWORD  IFCCALL vixn_get_server_state(PVIXNSERVER server);


 void IFCCALL vixn_execute_block(PVIXSRVRBLK srv_block);

 VIXNSRVRELE IFCCALL vixn_new_read_reg_func_ele(PVIXSRVRBLK srv_block,DWORD physAddr,VIXN_REG_WIDTH width,DWORD mask,DWORD shift);
 VIXNSRVRELE IFCCALL vixn_new_write_reg_func_ele(PVIXSRVRBLK srv_block,DWORD physAddr,VIXN_REG_WIDTH width,DWORD mask,DWORD shift,VIXNSRVRELE val);
 VIXNSRVRELE IFCCALL vixn_new_binary_func_ele(PVIXSRVRBLK srv_block, VIXNSRVRELE arg1, VIXNSRVRELE arg2, DWORD func);

 VIXNSRVRELE IFCCALL vixn_new_write_port_ele(PVIXSRVRBLK srv_block,VIXNSRVRELE portNum,VIXNSRVRELE val, VIXN_REG_WIDTH width);
 VIXNSRVRELE IFCCALL vixn_new_read_port_ele(PVIXSRVRBLK srv_block,VIXNSRVRELE portNum, VIXN_REG_WIDTH width);


 VIXNSRVRELE IFCCALL vixn_assign_array_ele(PVIXSRVRBLK srv_block, VIXNSRVRELE arrayBase,VIXNSRVRELE index, VIXNSRVRELE value);
 VIXNSRVRELE IFCCALL vixn_read_array_ele(PVIXSRVRBLK srv_block, VIXNSRVRELE arrayBase,VIXNSRVRELE index);

 VIXNSRVRELE IFCCALL vixn_new_read_mem_func_ele ( PVIXSRVRBLK srv_block, DWORD physBaseAddr, VIXN_REG_WIDTH width, VIXNSRVRELE offset);
 VIXNSRVRELE IFCCALL vixn_new_write_mem_func_ele( PVIXSRVRBLK srv_block, DWORD physBaseAddr, VIXN_REG_WIDTH width, VIXNSRVRELE offset, VIXNSRVRELE val );




#endif


