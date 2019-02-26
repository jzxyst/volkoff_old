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

#ifndef	__DT_SceneResult_h__
#define	__DT_SceneResult_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x310
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
#define		__DtFunc_onStart		0
#define		__DtFunc_onUpdate		1
#define		__DtFunc_onTerminate		2
#define		__DtFunc_onkeyEvent		3

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
#define		__DtStep_41		41
#define		__DtStep_42		42
#define		__DtStep_43		43
#define		__DtStep_44		44
#define		__DtStep_45		45
#define		__DtStep_46		46
#define		__DtStep_47		47
#define		__DtStep_48		48
#define		__DtStep_49		49
#define		__DtStep_50		50
#define		__DtStep_51		51
#define		__DtStep_52		52

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_onStart__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0000 );
#define	__Dt__DtFunc_onStart__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0001 );
#define	__Dt__DtFunc_onStart__DtStep_2	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0002 );
#define	__Dt__DtFunc_onStart__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0003 );
#define	__Dt__DtFunc_onStart__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0004 );
#define	__Dt__DtFunc_onStart__DtStep_5	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0005 );
#define	__Dt__DtFunc_onStart__DtStep_6	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0006 );
#define	__Dt__DtFunc_onStart__DtStep_7	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0007 );
#define	__Dt__DtFunc_onStart__DtStep_8	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0008 );
#define	__Dt__DtFunc_onStart__DtStep_9	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0009 );
#define	__Dt__DtFunc_onStart__DtStep_10	/*for*/	_TP_BusOut( __DtBaseAddress, 0x000A );
#define	__Dt__DtFunc_onStart__DtStep_11	/*for*/	_TP_BusOut( __DtBaseAddress, 0x000B );
#define	__Dt__DtFunc_onStart__DtStep_12	/*for*/	_TP_BusOut( __DtBaseAddress, 0x000C );
#define	__Dt__DtFunc_onStart__DtStep_13	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x000D );
#define	__Dt__DtFunc_onUpdate__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x000E );
#define	__Dt__DtFunc_onUpdate__DtStep_1	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x000F );
#define	__Dt__DtFunc_onUpdate__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0010 );
#define	__Dt__DtFunc_onUpdate__DtStep_3	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0011 );
#define	__Dt__DtFunc_onUpdate__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0012 );
#define	__Dt__DtFunc_onUpdate__DtStep_5	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0013 );
#define	__Dt__DtFunc_onUpdate__DtStep_6	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0014 );
#define	__Dt__DtFunc_onUpdate__DtStep_7	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0015 );
#define	__Dt__DtFunc_onUpdate__DtStep_8	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0016 );
#define	__Dt__DtFunc_onUpdate__DtStep_9	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0017 );
#define	__Dt__DtFunc_onUpdate__DtStep_10	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0018 );
#define	__Dt__DtFunc_onUpdate__DtStep_11	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0019 );
#define	__Dt__DtFunc_onUpdate__DtStep_12	/*for*/	_TP_BusOut( __DtBaseAddress, 0x001A );
#define	__Dt__DtFunc_onUpdate__DtStep_13	/*for*/	_TP_BusOut( __DtBaseAddress, 0x001B );
#define	__Dt__DtFunc_onUpdate__DtStep_14	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001C );
#define	__Dt__DtFunc_onUpdate__DtStep_15	/*for*/	_TP_BusOut( __DtBaseAddress, 0x001D );
#define	__Dt__DtFunc_onUpdate__DtStep_16	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001E );
#define	__Dt__DtFunc_onUpdate__DtStep_17	/*for*/	_TP_BusOut( __DtBaseAddress, 0x001F );
#define	__Dt__DtFunc_onUpdate__DtStep_18	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0020 );
#define	__Dt__DtFunc_onUpdate__DtStep_19	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0021 );
#define	__Dt__DtFunc_onUpdate__DtStep_20	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0022 );
#define	__Dt__DtFunc_onUpdate__DtStep_21	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0023 );
#define	__Dt__DtFunc_onUpdate__DtStep_22	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0024 );
#define	__Dt__DtFunc_onUpdate__DtStep_23	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0025 );
#define	__Dt__DtFunc_onUpdate__DtStep_24	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0026 );
#define	__Dt__DtFunc_onUpdate__DtStep_25	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0027 );
#define	__Dt__DtFunc_onUpdate__DtStep_26	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0028 );
#define	__Dt__DtFunc_onUpdate__DtStep_27	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x002A );
#define	__Dt__DtFunc_onUpdate__DtStep_28	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x002B );
#define	__Dt__DtFunc_onUpdate__DtStep_29	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002C );
#define	__Dt__DtFunc_onUpdate__DtStep_30	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002D );
#define	__Dt__DtFunc_onUpdate__DtStep_31	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002E );
#define	__Dt__DtFunc_onUpdate__DtStep_32	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002F );
#define	__Dt__DtFunc_onUpdate__DtStep_33	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0031 );
#define	__Dt__DtFunc_onUpdate__DtStep_34	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0032 );
#define	__Dt__DtFunc_onUpdate__DtStep_35	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0033 );
#define	__Dt__DtFunc_onUpdate__DtStep_36	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0034 );
#define	__Dt__DtFunc_onUpdate__DtStep_37	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0035 );
#define	__Dt__DtFunc_onUpdate__DtStep_38	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0036 );
#define	__Dt__DtFunc_onUpdate__DtStep_39	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0037 );
#define	__Dt__DtFunc_onUpdate__DtStep_40	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0038 );
#define	__Dt__DtFunc_onUpdate__DtStep_41	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0039 );
#define	__Dt__DtFunc_onUpdate__DtStep_42	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003A );
#define	__Dt__DtFunc_onUpdate__DtStep_43	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003B );
#define	__Dt__DtFunc_onUpdate__DtStep_44	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x003C );
#define	__Dt__DtFunc_onUpdate__DtStep_45	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x003D );
#define	__Dt__DtFunc_onUpdate__DtStep_46	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003E );
#define	__Dt__DtFunc_onUpdate__DtStep_47	/*for*/	_TP_BusOut( __DtBaseAddress, 0x003F );
#define	__Dt__DtFunc_onUpdate__DtStep_48	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0040 );
#define	__Dt__DtFunc_onUpdate__DtStep_49	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0041 );
#define	__Dt__DtFunc_onUpdate__DtStep_50	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0042 );
#define	__Dt__DtFunc_onUpdate__DtStep_51	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0043 );
#define	__Dt__DtFunc_onUpdate__DtStep_52	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0044 );
#define	__Dt__DtFunc_onTerminate__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0045 );
#define	__Dt__DtFunc_onTerminate__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0046 );
#define	__Dt__DtFunc_onkeyEvent__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0047 );
#define	__Dt__DtFunc_onkeyEvent__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0048 );
#define	__Dt__DtFunc_onkeyEvent__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0049 );
#define	__Dt__DtFunc_onkeyEvent__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004A );
#define	__Dt__DtFunc_onkeyEvent__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004B );
#define	__Dt__DtFunc_onkeyEvent__DtStep_5	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004C );
#define	__Dt__DtFunc_onkeyEvent__DtStep_6	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004D );
#define	__Dt__DtFunc_onkeyEvent__DtStep_7	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004E );
#define	__Dt__DtFunc_onkeyEvent__DtStep_8	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x004F );

#endif	/* __DT_SceneResult_h__ */

