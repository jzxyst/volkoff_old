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

#ifndef	__DT_PlayerStateWindow_h__
#define	__DT_PlayerStateWindow_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0xF0
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
#define		__DtFunc_PlayerStateWindow		0
#define		__DtFunc_setPosition		2
#define		__DtFunc_setOpacity		3
#define		__DtFunc_refresh		4
#define		__DtFunc_update		5

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

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_PlayerStateWindow__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_PlayerStateWindow__DtStep_1	/*for*/	
#define	__Dt__DtFunc_PlayerStateWindow__DtStep_2	/*for*/	
#define	__Dt__DtFunc_PlayerStateWindow__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_PlayerStateWindow__DtStep_4	/*FuncOut*/	
#define	__Dt__DtFunc_setPosition__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_setPosition__DtStep_1	/*for*/	
#define	__Dt__DtFunc_setPosition__DtStep_2	/*for*/	
#define	__Dt__DtFunc_setPosition__DtStep_3	/*for*/	
#define	__Dt__DtFunc_setPosition__DtStep_4	/*FuncOut*/	
#define	__Dt__DtFunc_setOpacity__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_setOpacity__DtStep_1	/*for*/	
#define	__Dt__DtFunc_setOpacity__DtStep_2	/*for*/	
#define	__Dt__DtFunc_setOpacity__DtStep_3	/*for*/	
#define	__Dt__DtFunc_setOpacity__DtStep_4	/*FuncOut*/	
#define	__Dt__DtFunc_refresh__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_update__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_update__DtStep_1	/*for*/	
#define	__Dt__DtFunc_update__DtStep_2	/*if*/	
#define	__Dt__DtFunc_update__DtStep_3	/*if*/	
#define	__Dt__DtFunc_update__DtStep_4	/*if*/	
#define	__Dt__DtFunc_update__DtStep_5	/*if*/	
#define	__Dt__DtFunc_update__DtStep_6	/*if*/	
#define	__Dt__DtFunc_update__DtStep_7	/*if*/	
#define	__Dt__DtFunc_update__DtStep_8	/*if*/	
#define	__Dt__DtFunc_update__DtStep_9	/*if*/	
#define	__Dt__DtFunc_update__DtStep_10	/*if*/	
#define	__Dt__DtFunc_update__DtStep_11	/*if*/	
#define	__Dt__DtFunc_update__DtStep_12	/*if*/	
#define	__Dt__DtFunc_update__DtStep_13	/*for*/	
#define	__Dt__DtFunc_update__DtStep_14	/*if*/	
#define	__Dt__DtFunc_update__DtStep_15	/*if*/	
#define	__Dt__DtFunc_update__DtStep_16	/*if*/	
#define	__Dt__DtFunc_update__DtStep_17	/*for*/	
#define	__Dt__DtFunc_update__DtStep_18	/*if*/	
#define	__Dt__DtFunc_update__DtStep_19	/*for*/	
#define	__Dt__DtFunc_update__DtStep_20	/*switch*/	
#define	__Dt__DtFunc_update__DtStep_21	/*if*/	
#define	__Dt__DtFunc_update__DtStep_22	/*switch*/	
#define	__Dt__DtFunc_update__DtStep_23	/*if*/	
#define	__Dt__DtFunc_update__DtStep_24	/*if*/	
#define	__Dt__DtFunc_update__DtStep_25	/*if*/	
#define	__Dt__DtFunc_update__DtStep_26	/*if*/	
#define	__Dt__DtFunc_update__DtStep_27	/*if*/	
#define	__Dt__DtFunc_update__DtStep_28	/*if*/	
#define	__Dt__DtFunc_update__DtStep_29	/*if*/	
#define	__Dt__DtFunc_update__DtStep_30	/*if*/	
#define	__Dt__DtFunc_update__DtStep_31	/*if*/	
#define	__Dt__DtFunc_update__DtStep_32	/*if*/	
#define	__Dt__DtFunc_update__DtStep_33	/*if*/	
#define	__Dt__DtFunc_update__DtStep_34	/*if*/	
#define	__Dt__DtFunc_update__DtStep_35	/*if*/	
#define	__Dt__DtFunc_update__DtStep_36	/*FuncOut*/	

#endif	/* __DT_PlayerStateWindow_h__ */

