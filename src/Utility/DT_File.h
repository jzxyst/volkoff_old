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

#ifndef	__DT_File_h__
#define	__DT_File_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x380
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
#define		__DtFunc_File		0
#define		__DtFunc_Open		4
#define		__DtFunc_Close		5

/* TestPoint StepList ------------------------------------------------------*/
#define		__DtStep_0		0
#define		__DtStep_1		1
#define		__DtStep_2		2
#define		__DtStep_3		3
#define		__DtStep_4		4
#define		__DtStep_5		5
#define		__DtStep_6		6
#define		__DtStep_7		7

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_File__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_File__DtStep_1	/*FuncOut*/	
#define	__Dt__DtFunc_File__DtStep_2	/*FuncIn*/	
#define	__Dt__DtFunc_File__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_File__DtStep_4	/*FuncIn*/	
#define	__Dt__DtFunc_File__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc_File__DtStep_6	/*FuncIn*/	
#define	__Dt__DtFunc_File__DtStep_7	/*FuncOut*/	
#define	__Dt__DtFunc_Open__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Open__DtStep_1	/*if*/	
#define	__Dt__DtFunc_Open__DtStep_2	/*if*/	
#define	__Dt__DtFunc_Open__DtStep_3	/*FuncOut*/	
#define	__Dt__DtFunc_Open__DtStep_4	/*if*/	
#define	__Dt__DtFunc_Open__DtStep_5	/*FuncOut*/	
#define	__Dt__DtFunc_Close__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_Close__DtStep_1	/*if*/	
#define	__Dt__DtFunc_Close__DtStep_2	/*if*/	
#define	__Dt__DtFunc_Close__DtStep_3	/*FuncOut*/	

#endif	/* __DT_File_h__ */

