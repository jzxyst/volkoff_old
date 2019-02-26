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

#ifndef	__DT_SceneTitle_h__
#define	__DT_SceneTitle_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x330
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
#define		__DtFunc_SceneTitle		0
#define		__DtFunc_onStart		1
#define		__DtFunc_onUpdate		2
#define		__DtFunc_onTerminate		3
#define		__DtFunc__startShowCommand		4
#define		__DtFunc__setPointCursorIndex		5

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
#define		__DtStep_20		20
#define		__DtStep_21		21
#define		__DtStep_22		22
#define		__DtStep_23		23
#define		__DtStep_24		24
#define		__DtStep_25		25
#define		__DtStep_26		26
#define		__DtStep_27		27
#define		__DtStep_28		28
#define		__DtStep_29		29
#define		__DtStep_30		30
#define		__DtStep_31		31
#define		__DtStep_32		32
#define		__DtStep_33		33
#define		__DtStep_34		34
#define		__DtStep_35		35
#define		__DtStep_36		36
#define		__DtStep_37		37
#define		__DtStep_38		38
#define		__DtStep_39		39
#define		__DtStep_40		40

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_SceneTitle__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0000 );
#define	__Dt__DtFunc_onStart__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0001 );
#define	__Dt__DtFunc_onStart__DtStep_1	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0002 );
#define	__Dt__DtFunc_onStart__DtStep_2	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0003 );
#define	__Dt__DtFunc_onStart__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0004 );
#define	__Dt__DtFunc_onUpdate__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0005 );
#define	__Dt__DtFunc_onUpdate__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0006 );
#define	__Dt__DtFunc_onUpdate__DtStep_2	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0007 );
#define	__Dt__DtFunc_onUpdate__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0008 );
#define	__Dt__DtFunc_onUpdate__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0009 );
#define	__Dt__DtFunc_onUpdate__DtStep_5	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x000A );
#define	__Dt__DtFunc_onUpdate__DtStep_6	/*if*/	_TP_BusOut( __DtBaseAddress, 0x000B );
#define	__Dt__DtFunc_onUpdate__DtStep_7	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x000C );
#define	__Dt__DtFunc_onUpdate__DtStep_8	/*if*/	_TP_BusOut( __DtBaseAddress, 0x000D );
#define	__Dt__DtFunc_onUpdate__DtStep_9	/*if*/	_TP_BusOut( __DtBaseAddress, 0x000E );
#define	__Dt__DtFunc_onUpdate__DtStep_10	/*for*/	_TP_BusOut( __DtBaseAddress, 0x000F );
#define	__Dt__DtFunc_onUpdate__DtStep_11	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0010 );
#define	__Dt__DtFunc_onUpdate__DtStep_12	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0011 );
#define	__Dt__DtFunc_onUpdate__DtStep_13	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0012 );
#define	__Dt__DtFunc_onUpdate__DtStep_14	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0013 );
#define	__Dt__DtFunc_onUpdate__DtStep_15	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0014 );
#define	__Dt__DtFunc_onUpdate__DtStep_16	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0015 );
#define	__Dt__DtFunc_onUpdate__DtStep_17	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0016 );
#define	__Dt__DtFunc_onUpdate__DtStep_18	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0017 );
#define	__Dt__DtFunc_onUpdate__DtStep_19	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0018 );
#define	__Dt__DtFunc_onUpdate__DtStep_20	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0019 );
#define	__Dt__DtFunc_onUpdate__DtStep_21	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001A );
#define	__Dt__DtFunc_onUpdate__DtStep_22	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x001B );
#define	__Dt__DtFunc_onUpdate__DtStep_23	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x001C );
#define	__Dt__DtFunc_onUpdate__DtStep_24	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001D );
#define	__Dt__DtFunc_onUpdate__DtStep_25	/*for*/	_TP_BusOut( __DtBaseAddress, 0x001E );
#define	__Dt__DtFunc_onUpdate__DtStep_26	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001F );
#define	__Dt__DtFunc_onUpdate__DtStep_27	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0020 );
#define	__Dt__DtFunc_onUpdate__DtStep_28	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0021 );
#define	__Dt__DtFunc_onUpdate__DtStep_29	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0022 );
#define	__Dt__DtFunc_onUpdate__DtStep_30	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0023 );
#define	__Dt__DtFunc_onUpdate__DtStep_31	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0024 );
#define	__Dt__DtFunc_onUpdate__DtStep_32	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0025 );
#define	__Dt__DtFunc_onUpdate__DtStep_33	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0026 );
#define	__Dt__DtFunc_onUpdate__DtStep_34	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0027 );
#define	__Dt__DtFunc_onUpdate__DtStep_35	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0028 );
#define	__Dt__DtFunc_onUpdate__DtStep_36	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002A );
#define	__Dt__DtFunc_onUpdate__DtStep_37	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002B );
#define	__Dt__DtFunc_onUpdate__DtStep_38	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002C );
#define	__Dt__DtFunc_onUpdate__DtStep_39	/*while*/	_TP_BusOut( __DtBaseAddress, 0x002D );
#define	__Dt__DtFunc_onUpdate__DtStep_40	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x002E );
#define	__Dt__DtFunc_onTerminate__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x002F );
#define	__Dt__DtFunc_onTerminate__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0031 );
#define	__Dt__DtFunc__startShowCommand__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0032 );
#define	__Dt__DtFunc__startShowCommand__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0033 );
#define	__Dt__DtFunc__startShowCommand__DtStep_2	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0034 );
#define	__Dt__DtFunc__startShowCommand__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0035 );
#define	__Dt__DtFunc__startShowCommand__DtStep_4	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0036 );
#define	__Dt__DtFunc__startShowCommand__DtStep_5	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0037 );
#define	__Dt__DtFunc__setPointCursorIndex__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0038 );
#define	__Dt__DtFunc__setPointCursorIndex__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0039 );
#define	__Dt__DtFunc__setPointCursorIndex__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003A );
#define	__Dt__DtFunc__setPointCursorIndex__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x003B );

#endif	/* __DT_SceneTitle_h__ */

