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

#ifndef	__DT_GameManager_h__
#define	__DT_GameManager_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x110
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
#define		__DtFunc_getInstance		0
#define		__DtFunc_GameManager		1
#define		__DtFunc_initializeParent		3
#define		__DtFunc_initializeChild		4
#define		__DtFunc_finalize		5
#define		__DtFunc_commit		6
#define		__DtFunc_reset		7
#define		__DtFunc_update		8
#define		__DtFunc_HandleEvent		9

/* TestPoint StepList ------------------------------------------------------*/
#define		__DtStep_0		0
#define		__DtStep_1		1
#define		__DtStep_2		2
#define		__DtStep_3		3

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_getInstance__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GameManager__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0001 );
#define	__Dt__DtFunc_GameManager__DtStep_1	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0002 );
#define	__Dt__DtFunc_GameManager__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0003 );
#define	__Dt__DtFunc_initializeParent__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0004 );
#define	__Dt__DtFunc_initializeParent__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0005 );
#define	__Dt__DtFunc_initializeChild__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0006 );
#define	__Dt__DtFunc_initializeChild__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0007 );
#define	__Dt__DtFunc_finalize__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0008 );
#define	__Dt__DtFunc_finalize__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0009 );
#define	__Dt__DtFunc_commit__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x000A );
#define	__Dt__DtFunc_commit__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x000B );
#define	__Dt__DtFunc_reset__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x000C );
#define	__Dt__DtFunc_reset__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x000D );
#define	__Dt__DtFunc_update__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x000E );
#define	__Dt__DtFunc_update__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x000F );
#define	__Dt__DtFunc_update__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0010 );
#define	__Dt__DtFunc_update__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0011 );
#define	__Dt__DtFunc_HandleEvent__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0012 );

#endif	/* __DT_GameManager_h__ */

