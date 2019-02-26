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

#ifndef	__DT_GameFrontendManager_h__
#define	__DT_GameFrontendManager_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0xC0
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
#define		__DtFunc_GameFrontendManager		0
#define		__DtFunc_getInstance		2
#define		__DtFunc_initialize		3
#define		__DtFunc_finalize		4
#define		__DtFunc_update		5
#define		__DtFunc_showLevelUp		6
#define		__DtFunc_showFloorNum		7
#define		__DtFunc_addGuidNamePlate		8
#define		__DtFunc_removeGuidNamePlate		9
#define		__DtFunc_onShowCharacterNamePlate		10

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

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_GameFrontendManager__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GameFrontendManager__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_GameFrontendManager__DtStep_2	/*FuncIn*/	
#define	__Dt__DtFunc_GameFrontendManager__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_getInstance__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_initialize__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_initialize__DtStep_1	/*for*/	
#define	__Dt__DtFunc_initialize__DtStep_2	/*FuncOut*/	
#define	__Dt__DtFunc_finalize__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_finalize__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_update__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_update__DtStep_1	/*for*/	
#define	__Dt__DtFunc_update__DtStep_2	/*switch*/	
#define	__Dt__DtFunc_update__DtStep_3	/*if*/	
#define	__Dt__DtFunc_update__DtStep_4	/*switch*/	
#define	__Dt__DtFunc_update__DtStep_5	/*if*/	
#define	__Dt__DtFunc_update__DtStep_6	/*if*/	
#define	__Dt__DtFunc_update__DtStep_7	/*if*/	
#define	__Dt__DtFunc_update__DtStep_8	/*if*/	
#define	__Dt__DtFunc_update__DtStep_9	/*if*/	
#define	__Dt__DtFunc_update__DtStep_10	/*if*/	
#define	__Dt__DtFunc_update__DtStep_11	/*if*/	
#define	__Dt__DtFunc_update__DtStep_12	/*if*/	
#define	__Dt__DtFunc_update__DtStep_13	/*if*/	
#define	__Dt__DtFunc_update__DtStep_14	/*if*/	
#define	__Dt__DtFunc_update__DtStep_15	/*for*/	
#define	__Dt__DtFunc_update__DtStep_16	/*if*/	
#define	__Dt__DtFunc_update__DtStep_17	/*for*/	
#define	__Dt__DtFunc_update__DtStep_18	/*FuncOut*/	
#define	__Dt__DtFunc_showLevelUp__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_showLevelUp__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_showFloorNum__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_showFloorNum__DtStep_1	/*for*/	
#define	__Dt__DtFunc_showFloorNum__DtStep_2	/*if*/	
#define	__Dt__DtFunc_showFloorNum__DtStep_3	/*if*/	
#define	__Dt__DtFunc_showFloorNum__DtStep_4	/*FuncOut*/	
#define	__Dt__DtFunc_addGuidNamePlate__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_addGuidNamePlate__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_removeGuidNamePlate__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_removeGuidNamePlate__DtStep_1	/*if*/	
#define	__Dt__DtFunc_removeGuidNamePlate__DtStep_2	/*FuncOut*/	
#define	__Dt__DtFunc_onShowCharacterNamePlate__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_onShowCharacterNamePlate__DtStep_1	/*FuncOut*/	

#endif	/* __DT_GameFrontendManager_h__ */

