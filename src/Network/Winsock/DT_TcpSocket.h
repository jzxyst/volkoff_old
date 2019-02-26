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

#ifndef	__DT_TcpSocket_h__
#define	__DT_TcpSocket_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x3D0
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
#define		__DtFunc_TcpSocket		0
#define		__DtFunc_Initialize		2
#define		__DtFunc_Release		3
#define		__DtFunc_Close		4
#define		__DtFunc_AsyncClose		5
#define		__DtFunc_Bind		6
#define		__DtFunc_Listen		7
#define		__DtFunc_Accept		8
#define		__DtFunc_Connect		9
#define		__DtFunc_Send		13
#define		__DtFunc__Send		14
#define		__DtFunc__Recv		15
#define		__DtFunc_TimerProc		16
#define		__DtFunc_Proc		17

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
#define		__DtStep_11		11
#define		__DtStep_12		12
#define		__DtStep_13		13
#define		__DtStep_14		14
#define		__DtStep_15		15
#define		__DtStep_16		16
#define		__DtStep_17		17
#define		__DtStep_18		18
#define		__DtStep_19		19

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_TcpSocket__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_TcpSocket__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_TcpSocket__DtStep_2	/*FuncIn*/	
#define	__Dt__DtFunc_TcpSocket__DtStep_3	/*if*/	
#define	__Dt__DtFunc_TcpSocket__DtStep_4	/*FuncOut*/	
#define	__Dt__DtFunc_Initialize__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Initialize__DtStep_1	/*if*/	
#define	__Dt__DtFunc_Initialize__DtStep_2	/*if*/	
#define	__Dt__DtFunc_Initialize__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_Initialize__DtStep_4	/*if*/	
#define	__Dt__DtFunc_Initialize__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc_Initialize__DtStep_6	/*FuncOut*/	
#define	__Dt__DtFunc_Release__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Release__DtStep_1	/*if*/	
#define	__Dt__DtFunc_Release__DtStep_2	/*FuncOut*/	
#define	__Dt__DtFunc_Close__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Close__DtStep_1	/*if*/	
#define	__Dt__DtFunc_Close__DtStep_2	/*if*/	
#define	__Dt__DtFunc_Close__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_AsyncClose__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_AsyncClose__DtStep_1	/*if*/	
#define	__Dt__DtFunc_AsyncClose__DtStep_2	/*if*/	
#define	__Dt__DtFunc_AsyncClose__DtStep_3	/*if*/	
#define	__Dt__DtFunc_AsyncClose__DtStep_4	/*FuncOut*/	
#define	__Dt__DtFunc_Bind__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Bind__DtStep_1	/*if*/	
#define	__Dt__DtFunc_Bind__DtStep_2	/*FuncOut*/	
#define	__Dt__DtFunc_Bind__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_Listen__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Listen__DtStep_1	/*if*/	
#define	__Dt__DtFunc_Listen__DtStep_2	/*FuncOut*/	
#define	__Dt__DtFunc_Listen__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_Accept__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Accept__DtStep_1	/*if*/	
#define	__Dt__DtFunc_Accept__DtStep_2	/*FuncOut*/	
#define	__Dt__DtFunc_Accept__DtStep_3	/*if*/	
#define	__Dt__DtFunc_Accept__DtStep_4	/*FuncOut*/	
#define	__Dt__DtFunc_Accept__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc_Connect__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Connect__DtStep_1	/*if*/	
#define	__Dt__DtFunc_Connect__DtStep_2	/*if*/	
#define	__Dt__DtFunc_Connect__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_Connect__DtStep_4	/*FuncOut*/	
#define	__Dt__DtFunc_Connect__DtStep_5	/*FuncIn*/	
#define	__Dt__DtFunc_Connect__DtStep_6	/*if*/	
#define	__Dt__DtFunc_Connect__DtStep_7	/*if*/	
#define	__Dt__DtFunc_Connect__DtStep_8	/*FuncOut*/	
#define	__Dt__DtFunc_Connect__DtStep_9	/*FuncOut*/	
#define	__Dt__DtFunc_Connect__DtStep_10	/*FuncIn*/	
#define	__Dt__DtFunc_Connect__DtStep_11	/*if*/	
#define	__Dt__DtFunc_Connect__DtStep_12	/*if*/	
#define	__Dt__DtFunc_Connect__DtStep_13	/*FuncOut*/	
#define	__Dt__DtFunc_Connect__DtStep_14	/*FuncOut*/	
#define	__Dt__DtFunc_Connect__DtStep_15	/*FuncIn*/	
#define	__Dt__DtFunc_Connect__DtStep_16	/*if*/	
#define	__Dt__DtFunc_Connect__DtStep_17	/*if*/	
#define	__Dt__DtFunc_Connect__DtStep_18	/*FuncOut*/	
#define	__Dt__DtFunc_Connect__DtStep_19	/*FuncOut*/	
#define	__Dt__DtFunc_Send__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Send__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc__Send__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc__Send__DtStep_1	/*if*/	
#define	__Dt__DtFunc__Send__DtStep_2	/*if*/	
#define	__Dt__DtFunc__Send__DtStep_3	/*if*/	
#define	__Dt__DtFunc__Send__DtStep_4	/*FuncOut*/	
#define	__Dt__DtFunc__Send__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc__Recv__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc__Recv__DtStep_1	/*if*/	
#define	__Dt__DtFunc__Recv__DtStep_2	/*FuncOut*/	
#define	__Dt__DtFunc__Recv__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_TimerProc__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_TimerProc__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_Proc__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Proc__DtStep_1	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_2	/*if*/	
#define	__Dt__DtFunc_Proc__DtStep_3	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_4	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_5	/*if*/	
#define	__Dt__DtFunc_Proc__DtStep_6	/*if*/	
#define	__Dt__DtFunc_Proc__DtStep_7	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_8	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_9	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_10	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_11	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_12	/*if*/	
#define	__Dt__DtFunc_Proc__DtStep_13	/*switch*/	
#define	__Dt__DtFunc_Proc__DtStep_14	/*FuncOut*/	

#endif	/* __DT_TcpSocket_h__ */

