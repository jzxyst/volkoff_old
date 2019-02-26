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

#ifndef	__DT_RankingManager_h__
#define	__DT_RankingManager_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x140
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
#define		__DtFunc_RankingManager		0
#define		__DtFunc_Initialize		2
#define		__DtFunc_Release		3
#define		__DtFunc_GetStoryRanking		4
#define		__DtFunc_GetSurvivalRanking		5
#define		__DtFunc_GetLocalStoryRanking		6
#define		__DtFunc_PostStoryScore		7
#define		__DtFunc_PostSurvivalScore		8
#define		__DtFunc_PostLocalStoryScore		9
#define		__DtFunc_ScoreDesc		10

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

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_RankingManager__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0000 );
#define	__Dt__DtFunc_RankingManager__DtStep_1	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0001 );
#define	__Dt__DtFunc_RankingManager__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0002 );
#define	__Dt__DtFunc_Initialize__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0003 );
#define	__Dt__DtFunc_Initialize__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0004 );
#define	__Dt__DtFunc_Release__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0005 );
#define	__Dt__DtFunc_GetStoryRanking__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0006 );
#define	__Dt__DtFunc_GetStoryRanking__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0007 );
#define	__Dt__DtFunc_GetStoryRanking__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0008 );
#define	__Dt__DtFunc_GetStoryRanking__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0009 );
#define	__Dt__DtFunc_GetStoryRanking__DtStep_4	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x000A );
#define	__Dt__DtFunc_GetStoryRanking__DtStep_5	/*do*/	_TP_BusOut( __DtBaseAddress, 0x000B );
#define	__Dt__DtFunc_GetStoryRanking__DtStep_6	/*for*/	
#define	__Dt__DtFunc_GetStoryRanking__DtStep_7	/*for*/	
#define	__Dt__DtFunc_GetStoryRanking__DtStep_8	/*for*/	
#define	__Dt__DtFunc_GetStoryRanking__DtStep_9	/*for*/	
#define	__Dt__DtFunc_GetStoryRanking__DtStep_10	/*for*/	
#define	__Dt__DtFunc_GetStoryRanking__DtStep_11	/*for*/	
#define	__Dt__DtFunc_GetStoryRanking__DtStep_12	/*for*/	
#define	__Dt__DtFunc_GetStoryRanking__DtStep_13	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0013 );
#define	__Dt__DtFunc_GetSurvivalRanking__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0014 );
#define	__Dt__DtFunc_GetSurvivalRanking__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0015 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0016 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0017 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0018 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0019 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_4	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x001A );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_5	/*while*/	_TP_BusOut( __DtBaseAddress, 0x001B );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_6	/*for*/	
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_7	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x001D );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_8	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x001E );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_9	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x001F );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_10	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0020 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_11	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0021 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_12	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0022 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_13	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0023 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_14	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0024 );
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_15	/*for*/	
#define	__Dt__DtFunc_GetLocalStoryRanking__DtStep_16	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0026 );
#define	__Dt__DtFunc_PostStoryScore__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0027 );
#define	__Dt__DtFunc_PostStoryScore__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0028 );
#define	__Dt__DtFunc_PostStoryScore__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x002A );
#define	__Dt__DtFunc_PostStoryScore__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002B );
#define	__Dt__DtFunc_PostStoryScore__DtStep_4	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x002C );
#define	__Dt__DtFunc_PostStoryScore__DtStep_5	/*do*/	_TP_BusOut( __DtBaseAddress, 0x002D );
#define	__Dt__DtFunc_PostStoryScore__DtStep_6	/*for*/	
#define	__Dt__DtFunc_PostStoryScore__DtStep_7	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x002F );
#define	__Dt__DtFunc_PostSurvivalScore__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0031 );
#define	__Dt__DtFunc_PostLocalStoryScore__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0032 );
#define	__Dt__DtFunc_PostLocalStoryScore__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0033 );
#define	__Dt__DtFunc_PostLocalStoryScore__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0034 );
#define	__Dt__DtFunc_PostLocalStoryScore__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0035 );
#define	__Dt__DtFunc_PostLocalStoryScore__DtStep_4	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0036 );
#define	__Dt__DtFunc_PostLocalStoryScore__DtStep_5	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0037 );
#define	__Dt__DtFunc_ScoreDesc__DtStep_0	/*FuncIn+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0038 );

#endif	/* __DT_RankingManager_h__ */

