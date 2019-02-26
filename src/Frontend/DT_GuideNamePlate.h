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

#ifndef	__DT_GuideNamePlate_h__
#define	__DT_GuideNamePlate_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0xD0
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
#define		__DtFunc_GuideNamePlate		0
#define		__DtFunc_initialize		2
#define		__DtFunc_update		3
#define		__DtFunc__setPosition		4

/* TestPoint StepList ------------------------------------------------------*/
#define		__DtStep_0		0
#define		__DtStep_1		1
#define		__DtStep_2		2
#define		__DtStep_3		3
#define		__DtStep_4		4
#define		__DtStep_5		5

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_GuideNamePlate__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_GuideNamePlate__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_GuideNamePlate__DtStep_2	/*FuncIn*/	
#define	__Dt__DtFunc_GuideNamePlate__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_initialize__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_initialize__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_update__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_update__DtStep_1	/*if*/	
#define	__Dt__DtFunc_update__DtStep_2	/*if*/	
#define	__Dt__DtFunc_update__DtStep_3	/*if*/	
#define	__Dt__DtFunc_update__DtStep_4	/*if*/	
#define	__Dt__DtFunc_update__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc__setPosition__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc__setPosition__DtStep_1	/*FuncOut*/	

#endif	/* __DT_GuideNamePlate_h__ */

