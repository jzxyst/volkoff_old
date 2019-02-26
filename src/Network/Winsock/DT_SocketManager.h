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

#ifndef	__DT_SocketManager_h__
#define	__DT_SocketManager_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x3C0
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
#define		__DtFunc_SocketManager		0
#define		__DtFunc_Initialize		2
#define		__DtFunc_Release		3
#define		__DtFunc_Proc		4
#define		__DtFunc_HandleSend		5
#define		__DtFunc_AcceptProc		6
#define		__DtFunc_ConnectProc		7
#define		__DtFunc_WriteProc		8
#define		__DtFunc_ReadProc		9
#define		__DtFunc_CloseProc		10
#define		__DtFunc_AddSocket		11
#define		__DtFunc_RemoveSocket		12

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
#define	__Dt__DtFunc_SocketManager__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_SocketManager__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_SocketManager__DtStep_2	/*FuncIn*/	
#define	__Dt__DtFunc_SocketManager__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_Initialize__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Initialize__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_Release__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Release__DtStep_1	/*while*/	
#define	__Dt__DtFunc_Release__DtStep_2	/*FuncOut*/	
#define	__Dt__DtFunc_Proc__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Proc__DtStep_1	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_2	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_3	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_4	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_5	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_6	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_7	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_8	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_9	/*for*/	
#define	__Dt__DtFunc_Proc__DtStep_10	/*FuncOut*/	
#define	__Dt__DtFunc_HandleSend__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_HandleSend__DtStep_1	/*if*/	
#define	__Dt__DtFunc_HandleSend__DtStep_2	/*for*/	
#define	__Dt__DtFunc_HandleSend__DtStep_3	/*if*/	
#define	__Dt__DtFunc_HandleSend__DtStep_4	/*if*/	
#define	__Dt__DtFunc_HandleSend__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc_AcceptProc__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_ConnectProc__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_WriteProc__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_WriteProc__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_ReadProc__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_CloseProc__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_AddSocket__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_AddSocket__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_RemoveSocket__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_RemoveSocket__DtStep_1	/*FuncOut*/	

#endif	/* __DT_SocketManager_h__ */

