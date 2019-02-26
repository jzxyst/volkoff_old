/*
 Copyright (C) 2009-2013, Heartland. Data Co.,Ltd.  All Rights Reserved.  
                                                                          
 This software is furnished under a license and may be used and copied    
 only in accordance with the terms of such license and with the inclusion 
 of the above copyright notice. No title to and ownership of the software 
 is transferred.                                                          
 Heartland. Data Co.,Ltd. makes no representation or warranties with      
 respect to the performance of this computer program, and specifically    
 disclaims any responsibility for any damages, special or consequential,  
 connected with the use of this program.                                  
*/

#ifndef	__DT_NetworkHelper_h__
#define	__DT_NetworkHelper_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x180
#define		__DtAllEnable		1
#if ( __DtAllEnable == 1 )
#define		__DtTestPoint(func, step)		__Dt##func##step
#define		__DtTestPointValue(func, step, value, size)		__Dt##func##step(value,size)
#define		__DtTestPointWrite(func, step, value, size)		__Dt##func##step(value,size)
#define		__DtTestPointEventTrigger(func, step, data)		__Dt##func##step(data)
#else
#define		__DtTestPoint(func, step)		
#define		__DtTestPointValue(func, step, value, size)		
#define		__DtTestPointWrite(func, step, value, size)		
#define		__DtTestPointEventTrigger(func, step, data)		
#endif
__DtEXTERN		void	_TP_BusOut( unsigned int addr, unsigned int dat );
__DtEXTERN		void	_TP_MemoryOutput( unsigned int addr, unsigned int dat, void *value, unsigned int size );
__DtEXTERN		void	_TP_WritePoint( unsigned int addr, unsigned int dat, void *value, unsigned int size );
__DtEXTERN		void	_TP_EventTrigger( unsigned int addr, unsigned int dat );

/* TestPoint FuncList ------------------------------------------------------*/
#define		__DtFunc_NetworkHelper		0
#define		__DtFunc_Initialize		2
#define		__DtFunc_Release		3
#define		__DtFunc_ConnectEx		4
#define		__DtFunc_GetLocalIPL		5
#define		__DtFunc_GetLocalIPA		6
#define		__DtFunc_GetGlobalIPL		7
#define		__DtFunc_GetGlobalIPA		8
#define		__DtFunc_GetHostName		9
#define		__DtFunc_GetRemoteHostName		10
#define		__DtFunc_GetUserName		11

/* TestPoint StepList ------------------------------------------------------*/
#define		__DtStep_0		0
#define		__DtStep_1		1
#define		__DtStep_2		2
#define		__DtStep_3		3
#define		__DtStep_4		4
#define		__DtStep_5		5
#define		__DtStep_6		6
#define		__DtStep_7		7
#define		__DtStep_8		8
#define		__DtStep_9		9
#define		__DtStep_10		10

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_NetworkHelper__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_NetworkHelper__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_NetworkHelper__DtStep_2	/*FuncIn*/	
#define	__Dt__DtFunc_NetworkHelper__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_Initialize__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Initialize__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_Release__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Release__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_1	/*if*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_2	/*FuncOut*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_3	/*if*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_4	/*if*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_6	/*if*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_7	/*FuncOut*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_8	/*if*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_9	/*FuncOut*/	
#define	__Dt__DtFunc_ConnectEx__DtStep_10	/*FuncOut*/	
#define	__Dt__DtFunc_GetLocalIPL__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GetLocalIPL__DtStep_1	/*if*/	
#define	__Dt__DtFunc_GetLocalIPL__DtStep_2	/*for*/	
#define	__Dt__DtFunc_GetLocalIPL__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_GetLocalIPA__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GetLocalIPA__DtStep_1	/*if*/	
#define	__Dt__DtFunc_GetLocalIPA__DtStep_2	/*for*/	
#define	__Dt__DtFunc_GetLocalIPA__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_GetGlobalIPL__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GetGlobalIPL__DtStep_1	/*if*/	
#define	__Dt__DtFunc_GetGlobalIPL__DtStep_2	/*if*/	
#define	__Dt__DtFunc_GetGlobalIPL__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_GetGlobalIPL__DtStep_4	/*if*/	
#define	__Dt__DtFunc_GetGlobalIPL__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc_GetGlobalIPL__DtStep_6	/*do*/	
#define	__Dt__DtFunc_GetGlobalIPL__DtStep_7	/*for*/	
#define	__Dt__DtFunc_GetGlobalIPL__DtStep_8	/*FuncOut*/	
#define	__Dt__DtFunc_GetGlobalIPA__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GetGlobalIPA__DtStep_1	/*if*/	
#define	__Dt__DtFunc_GetGlobalIPA__DtStep_2	/*if*/	
#define	__Dt__DtFunc_GetGlobalIPA__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_GetGlobalIPA__DtStep_4	/*if*/	
#define	__Dt__DtFunc_GetGlobalIPA__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc_GetGlobalIPA__DtStep_6	/*do*/	
#define	__Dt__DtFunc_GetGlobalIPA__DtStep_7	/*for*/	
#define	__Dt__DtFunc_GetGlobalIPA__DtStep_8	/*FuncOut*/	
#define	__Dt__DtFunc_GetHostName__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GetHostName__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_GetRemoteHostName__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GetRemoteHostName__DtStep_1	/*if*/	
#define	__Dt__DtFunc_GetRemoteHostName__DtStep_2	/*if*/	
#define	__Dt__DtFunc_GetRemoteHostName__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_GetRemoteHostName__DtStep_4	/*if*/	
#define	__Dt__DtFunc_GetRemoteHostName__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc_GetRemoteHostName__DtStep_6	/*do*/	
#define	__Dt__DtFunc_GetRemoteHostName__DtStep_7	/*for*/	
#define	__Dt__DtFunc_GetRemoteHostName__DtStep_8	/*FuncOut*/	
#define	__Dt__DtFunc_GetUserName__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GetUserName__DtStep_1	/*FuncOut*/	

#endif	/* __DT_NetworkHelper_h__ */

