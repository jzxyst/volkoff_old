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

#ifndef	__DT_GameObjectManager_h__
#define	__DT_GameObjectManager_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x210
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
#define		__DtFunc_GameObjectManager		0
#define		__DtFunc_Initialize		2
#define		__DtFunc_Release		3
#define		__DtFunc_Update		4
#define		__DtFunc_AddObject		5
#define		__DtFunc_deleteObject		6
#define		__DtFunc_addAttackedObject		7
#define		__DtFunc_removeAttackedObject		8
#define		__DtFunc_findObject		9
#define		__DtFunc_sendEvent		10
#define		__DtFunc_postEvent		11
#define		__DtFunc_judgeCollitionToAttackedObject		12
#define		__DtFunc_judgeCollitionTypeSpecified		13
#define		__DtFunc_judgeCollitionTypeSpecifiedAndDelete		14
#define		__DtFunc_CollisionToObject		15
#define		__DtFunc_removeObject		16
#define		__DtFunc_deleteStageObject		17

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
#define	__Dt__DtFunc_GameObjectManager__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0000 );
#define	__Dt__DtFunc_GameObjectManager__DtStep_1	/*for*/	
#define	__Dt__DtFunc_GameObjectManager__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0002 );
#define	__Dt__DtFunc_GameObjectManager__DtStep_3	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0003 );
#define	__Dt__DtFunc_GameObjectManager__DtStep_4	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0004 );
#define	__Dt__DtFunc_Initialize__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0005 );
#define	__Dt__DtFunc_Initialize__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0006 );
#define	__Dt__DtFunc_Release__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0007 );
#define	__Dt__DtFunc_Release__DtStep_1	/*while*/	_TP_BusOut( __DtBaseAddress, 0x0008 );
#define	__Dt__DtFunc_Release__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0009 );
#define	__Dt__DtFunc_Release__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x000A );
#define	__Dt__DtFunc_Update__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x000B );
#define	__Dt__DtFunc_Update__DtStep_1	/*for*/	
#define	__Dt__DtFunc_Update__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x000D );
#define	__Dt__DtFunc_Update__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x000E );
#define	__Dt__DtFunc_Update__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x000F );
#define	__Dt__DtFunc_Update__DtStep_5	/*for*/	
#define	__Dt__DtFunc_Update__DtStep_6	/*while*/	_TP_BusOut( __DtBaseAddress, 0x0011 );
#define	__Dt__DtFunc_Update__DtStep_7	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0012 );
#define	__Dt__DtFunc_Update__DtStep_8	/*for*/	
#define	__Dt__DtFunc_Update__DtStep_9	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0014 );
#define	__Dt__DtFunc_AddObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0015 );
#define	__Dt__DtFunc_AddObject__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0016 );
#define	__Dt__DtFunc_deleteObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0017 );
#define	__Dt__DtFunc_deleteObject__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0018 );
#define	__Dt__DtFunc_addAttackedObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0019 );
#define	__Dt__DtFunc_addAttackedObject__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x001A );
#define	__Dt__DtFunc_removeAttackedObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x001B );
#define	__Dt__DtFunc_removeAttackedObject__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x001C );
#define	__Dt__DtFunc_findObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x001D );
#define	__Dt__DtFunc_findObject__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x001E );
#define	__Dt__DtFunc_findObject__DtStep_2	/*if+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x001F );
#define	__Dt__DtFunc_findObject__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0020 );
#define	__Dt__DtFunc_findObject__DtStep_4	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0021 );
#define	__Dt__DtFunc_sendEvent__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0022 );
#define	__Dt__DtFunc_sendEvent__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0023 );
#define	__Dt__DtFunc_sendEvent__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0024 );
#define	__Dt__DtFunc_postEvent__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0025 );
#define	__Dt__DtFunc_postEvent__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0026 );
#define	__Dt__DtFunc_judgeCollitionToAttackedObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0027 );
#define	__Dt__DtFunc_judgeCollitionToAttackedObject__DtStep_1	/*for*/	
#define	__Dt__DtFunc_judgeCollitionToAttackedObject__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002A );
#define	__Dt__DtFunc_judgeCollitionToAttackedObject__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002B );
#define	__Dt__DtFunc_judgeCollitionToAttackedObject__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002C );
#define	__Dt__DtFunc_judgeCollitionToAttackedObject__DtStep_5	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x002D );
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x002E );
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002F );
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_2	/*for*/	
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0032 );
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_4	/*if+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0033 );
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_5	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0034 );
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_6	/*for*/	
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_7	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0036 );
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_8	/*if+FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0037 );
#define	__Dt__DtFunc_judgeCollitionTypeSpecified__DtStep_9	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0038 );
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0039 );
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003A );
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_2	/*for*/	
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003C );
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003D );
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_5	/*if*/	_TP_BusOut( __DtBaseAddress, 0x003E );
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_6	/*for*/	
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_7	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0040 );
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_8	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0041 );
#define	__Dt__DtFunc_judgeCollitionTypeSpecifiedAndDelete__DtStep_9	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0042 );
#define	__Dt__DtFunc_CollisionToObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0043 );
#define	__Dt__DtFunc_CollisionToObject__DtStep_1	/*for*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_2	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_3	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_4	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_5	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_6	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_7	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_8	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_9	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_10	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_11	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_12	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_13	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_14	/*switch*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_15	/*switch*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_16	/*switch*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_17	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_18	/*if*/	
#define	__Dt__DtFunc_CollisionToObject__DtStep_19	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0056 );
#define	__Dt__DtFunc_removeObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0057 );
#define	__Dt__DtFunc_removeObject__DtStep_1	/*for*/	
#define	__Dt__DtFunc_removeObject__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0059 );
#define	__Dt__DtFunc_removeObject__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x005A );
#define	__Dt__DtFunc_deleteStageObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x005B );
#define	__Dt__DtFunc_deleteStageObject__DtStep_1	/*for*/	
#define	__Dt__DtFunc_deleteStageObject__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x005D );
#define	__Dt__DtFunc_deleteStageObject__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x005E );

#endif	/* __DT_GameObjectManager_h__ */

