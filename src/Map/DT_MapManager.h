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

#ifndef	__DT_MapManager_h__
#define	__DT_MapManager_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x170
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
#define		__DtFunc_MapManager		0
#define		__DtFunc_getInstance		2
#define		__DtFunc_finalize		3
#define		__DtFunc_changeMap		4
#define		__DtFunc_collision		5
#define		__DtFunc_getStartPosition		6
#define		__DtFunc_releaseTilemap		7
#define		__DtFunc_BulletCollision		8

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
#define		__DtStep_53		53
#define		__DtStep_54		54
#define		__DtStep_55		55
#define		__DtStep_56		56
#define		__DtStep_57		57
#define		__DtStep_58		58
#define		__DtStep_59		59
#define		__DtStep_60		60
#define		__DtStep_61		61
#define		__DtStep_62		62

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_MapManager__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0000 );
#define	__Dt__DtFunc_MapManager__DtStep_1	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0001 );
#define	__Dt__DtFunc_MapManager__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0002 );
#define	__Dt__DtFunc_getInstance__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_finalize__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0004 );
#define	__Dt__DtFunc_finalize__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0005 );
#define	__Dt__DtFunc_changeMap__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0006 );
#define	__Dt__DtFunc_changeMap__DtStep_1	/*for*/	
#define	__Dt__DtFunc_changeMap__DtStep_2	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_3	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_4	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_5	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_6	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_7	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_8	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_9	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_10	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_11	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_12	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_13	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_14	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_15	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_16	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_17	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_18	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_19	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_20	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_21	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_22	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_23	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_24	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_25	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_26	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_27	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_28	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_29	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_30	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_31	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_32	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_33	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_34	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_35	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_36	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_37	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_38	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_39	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_40	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_41	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_42	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_43	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_44	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_45	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_46	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_47	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_48	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_49	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_50	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_51	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_52	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_53	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_54	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_55	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_56	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_57	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_58	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_59	/*switch*/	
#define	__Dt__DtFunc_changeMap__DtStep_60	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_61	/*if*/	
#define	__Dt__DtFunc_changeMap__DtStep_62	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0046 );
#define	__Dt__DtFunc_collision__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0047 );
#define	__Dt__DtFunc_collision__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0048 );
#define	__Dt__DtFunc_collision__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0049 );
#define	__Dt__DtFunc_collision__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004A );
#define	__Dt__DtFunc_collision__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004B );
#define	__Dt__DtFunc_collision__DtStep_5	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x004C );
#define	__Dt__DtFunc_getStartPosition__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x004D );
#define	__Dt__DtFunc_getStartPosition__DtStep_1	/*for*/	
#define	__Dt__DtFunc_getStartPosition__DtStep_2	/*if*/	
#define	__Dt__DtFunc_getStartPosition__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0050 );
#define	__Dt__DtFunc_releaseTilemap__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0051 );
#define	__Dt__DtFunc_releaseTilemap__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0052 );
#define	__Dt__DtFunc_BulletCollision__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0053 );
#define	__Dt__DtFunc_BulletCollision__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0054 );
#define	__Dt__DtFunc_BulletCollision__DtStep_2	/*if+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0055 );
#define	__Dt__DtFunc_BulletCollision__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0056 );

#endif	/* __DT_MapManager_h__ */

