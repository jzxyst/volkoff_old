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

#ifndef	__DT_MidBoss2_h__
#define	__DT_MidBoss2_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x240
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
#define		__DtFunc_create		0
#define		__DtFunc_createRandom		1
#define		__DtFunc_MidBoss2		2
#define		__DtFunc_Initialize		4
#define		__DtFunc_Release		5
#define		__DtFunc_Update		6
#define		__DtFunc_UpdateSelf		7
#define		__DtFunc_HandleEvent		8
#define		__DtFunc_SearchPlayer		9
#define		__DtFunc_SearchAttack1Range		10

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
#define		__DtStep_63		63
#define		__DtStep_64		64
#define		__DtStep_65		65
#define		__DtStep_66		66
#define		__DtStep_67		67
#define		__DtStep_68		68
#define		__DtStep_69		69
#define		__DtStep_70		70
#define		__DtStep_71		71
#define		__DtStep_72		72
#define		__DtStep_73		73
#define		__DtStep_74		74
#define		__DtStep_75		75
#define		__DtStep_76		76
#define		__DtStep_77		77
#define		__DtStep_78		78
#define		__DtStep_79		79
#define		__DtStep_80		80
#define		__DtStep_81		81
#define		__DtStep_82		82
#define		__DtStep_83		83
#define		__DtStep_84		84
#define		__DtStep_85		85
#define		__DtStep_86		86
#define		__DtStep_87		87
#define		__DtStep_88		88
#define		__DtStep_89		89
#define		__DtStep_90		90
#define		__DtStep_91		91
#define		__DtStep_92		92

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_create__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0000 );
#define	__Dt__DtFunc_create__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0001 );
#define	__Dt__DtFunc_create__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0002 );
#define	__Dt__DtFunc_createRandom__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0003 );
#define	__Dt__DtFunc_createRandom__DtStep_1	/*for*/	
#define	__Dt__DtFunc_createRandom__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0005 );
#define	__Dt__DtFunc_createRandom__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0006 );
#define	__Dt__DtFunc_MidBoss2__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0007 );
#define	__Dt__DtFunc_MidBoss2__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0008 );
#define	__Dt__DtFunc_MidBoss2__DtStep_2	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0009 );
#define	__Dt__DtFunc_MidBoss2__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x000A );
#define	__Dt__DtFunc_Initialize__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x000B );
#define	__Dt__DtFunc_Initialize__DtStep_1	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x000C );
#define	__Dt__DtFunc_Initialize__DtStep_2	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x000D );
#define	__Dt__DtFunc_Initialize__DtStep_3	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x000E );
#define	__Dt__DtFunc_Initialize__DtStep_4	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x000F );
#define	__Dt__DtFunc_Initialize__DtStep_5	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0010 );
#define	__Dt__DtFunc_Initialize__DtStep_6	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0011 );
#define	__Dt__DtFunc_Initialize__DtStep_7	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0012 );
#define	__Dt__DtFunc_Release__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0013 );
#define	__Dt__DtFunc_Update__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0014 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0015 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0016 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_2	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0017 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_3	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0018 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0019 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_5	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001A );
#define	__Dt__DtFunc_UpdateSelf__DtStep_6	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001B );
#define	__Dt__DtFunc_UpdateSelf__DtStep_7	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x001C );
#define	__Dt__DtFunc_UpdateSelf__DtStep_8	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001D );
#define	__Dt__DtFunc_UpdateSelf__DtStep_9	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001E );
#define	__Dt__DtFunc_UpdateSelf__DtStep_10	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x001F );
#define	__Dt__DtFunc_UpdateSelf__DtStep_11	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0020 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_12	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0021 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_13	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0022 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_14	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0023 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_15	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0024 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_16	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0025 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_17	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0026 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_18	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0027 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_19	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0028 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_20	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002A );
#define	__Dt__DtFunc_UpdateSelf__DtStep_21	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002B );
#define	__Dt__DtFunc_UpdateSelf__DtStep_22	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002C );
#define	__Dt__DtFunc_UpdateSelf__DtStep_23	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x002D );
#define	__Dt__DtFunc_UpdateSelf__DtStep_24	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002E );
#define	__Dt__DtFunc_UpdateSelf__DtStep_25	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002F );
#define	__Dt__DtFunc_UpdateSelf__DtStep_26	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0031 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_27	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0032 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_28	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0033 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_29	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0034 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_30	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0035 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_31	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0036 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_32	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0037 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_33	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0038 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_34	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0039 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_35	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003A );
#define	__Dt__DtFunc_UpdateSelf__DtStep_36	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003B );
#define	__Dt__DtFunc_UpdateSelf__DtStep_37	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x003C );
#define	__Dt__DtFunc_UpdateSelf__DtStep_38	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003D );
#define	__Dt__DtFunc_UpdateSelf__DtStep_39	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x003E );
#define	__Dt__DtFunc_UpdateSelf__DtStep_40	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x003F );
#define	__Dt__DtFunc_UpdateSelf__DtStep_41	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0040 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_42	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0041 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_43	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0042 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_44	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0043 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_45	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0044 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_46	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0045 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_47	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0046 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_48	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0047 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_49	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0048 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_50	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0049 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_51	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004A );
#define	__Dt__DtFunc_UpdateSelf__DtStep_52	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004B );
#define	__Dt__DtFunc_UpdateSelf__DtStep_53	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x004C );
#define	__Dt__DtFunc_UpdateSelf__DtStep_54	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004D );
#define	__Dt__DtFunc_UpdateSelf__DtStep_55	/*if*/	_TP_BusOut( __DtBaseAddress, 0x004E );
#define	__Dt__DtFunc_UpdateSelf__DtStep_56	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x004F );
#define	__Dt__DtFunc_UpdateSelf__DtStep_57	/*if+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0050 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_58	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0051 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_59	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0052 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_60	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0053 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_61	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0054 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_62	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0055 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_63	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0056 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_64	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0057 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_65	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0058 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_66	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0059 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_67	/*if*/	_TP_BusOut( __DtBaseAddress, 0x005A );
#define	__Dt__DtFunc_UpdateSelf__DtStep_68	/*if*/	_TP_BusOut( __DtBaseAddress, 0x005B );
#define	__Dt__DtFunc_UpdateSelf__DtStep_69	/*if*/	_TP_BusOut( __DtBaseAddress, 0x005C );
#define	__Dt__DtFunc_UpdateSelf__DtStep_70	/*if*/	_TP_BusOut( __DtBaseAddress, 0x005D );
#define	__Dt__DtFunc_UpdateSelf__DtStep_71	/*if*/	_TP_BusOut( __DtBaseAddress, 0x005E );
#define	__Dt__DtFunc_UpdateSelf__DtStep_72	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x005F );
#define	__Dt__DtFunc_UpdateSelf__DtStep_73	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0060 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_74	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0061 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_75	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0062 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_76	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0063 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_77	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0064 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_78	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0065 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_79	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0066 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_80	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0067 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_81	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0068 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_82	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0069 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_83	/*if*/	_TP_BusOut( __DtBaseAddress, 0x006A );
#define	__Dt__DtFunc_UpdateSelf__DtStep_84	/*if*/	_TP_BusOut( __DtBaseAddress, 0x006B );
#define	__Dt__DtFunc_UpdateSelf__DtStep_85	/*if*/	_TP_BusOut( __DtBaseAddress, 0x006C );
#define	__Dt__DtFunc_UpdateSelf__DtStep_86	/*if*/	_TP_BusOut( __DtBaseAddress, 0x006D );
#define	__Dt__DtFunc_UpdateSelf__DtStep_87	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x006E );
#define	__Dt__DtFunc_UpdateSelf__DtStep_88	/*if*/	_TP_BusOut( __DtBaseAddress, 0x006F );
#define	__Dt__DtFunc_UpdateSelf__DtStep_89	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0070 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_90	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0071 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_91	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0072 );
#define	__Dt__DtFunc_UpdateSelf__DtStep_92	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0073 );
#define	__Dt__DtFunc_HandleEvent__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0074 );
#define	__Dt__DtFunc_HandleEvent__DtStep_1	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0075 );
#define	__Dt__DtFunc_HandleEvent__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0076 );
#define	__Dt__DtFunc_SearchPlayer__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0077 );
#define	__Dt__DtFunc_SearchPlayer__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0078 );
#define	__Dt__DtFunc_SearchPlayer__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0079 );
#define	__Dt__DtFunc_SearchPlayer__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x007A );
#define	__Dt__DtFunc_SearchAttack1Range__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x007B );
#define	__Dt__DtFunc_SearchAttack1Range__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x007C );
#define	__Dt__DtFunc_SearchAttack1Range__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x007D );

#endif	/* __DT_MidBoss2_h__ */

