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

#ifndef	__DT_CharacterScriptInterface_h__
#define	__DT_CharacterScriptInterface_h__

#ifdef	__cplusplus
	#define	__DtEXTERN	extern "C"
#else
	#define	__DtEXTERN	extern
#endif

/* TestPoint MacroCode -----------------------------------------------------*/
#define		__DtBaseAddress		0x1E0
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
#define		__DtFunc_getInstance		0
#define		__DtFunc_CharacterScriptInterface		1
#define		__DtFunc_update		3
#define		__DtFunc_getCharaAttackedGroup		4
#define		__DtFunc_getCharaPosition		5
#define		__DtFunc_setCharaState		6
#define		__DtFunc_setFrameCount		7
#define		__DtFunc_setPuttern		8
#define		__DtFunc_judgeAttackCollision		9
#define		__DtFunc_attackEffect		10
#define		__DtFunc_disposeObject		11
#define		__DtFunc_AttackLock		12
#define		__DtFunc_AttackUnLock		13
#define		__DtFunc_getOnGround		14
#define		__DtFunc_setVelocity		15
#define		__DtFunc_CheckWeaponBreak		16
#define		__DtFunc_setBreakWeapon		17
#define		__DtFunc_getBreakWeapon		18
#define		__DtFunc_PlaySE		19
#define		__DtFunc_CreateEffect		20
#define		__DtFunc_setDirection		21
#define		__DtFunc_setPosition		22
#define		__DtFunc_GrenadeGenerate		23
#define		__DtFunc_BulletGenerate		24
#define		__DtFunc_setInvincibleFrame		25
#define		__DtFunc_setAccel		26
#define		__DtFunc_getLife		27
#define		__DtFunc_setLife		28
#define		__DtFunc_getDirection		29
#define		__DtFunc_getMaxLife		30
#define		__DtFunc_getRank		31
#define		__DtFunc_getPlayerPos		32
#define		__DtFunc_Rand		33
#define		__DtFunc_getPhase		34
#define		__DtFunc_getNum		35
#define		__DtFunc_setNum		36
#define		__DtFunc_SummonEnemy		37
#define		__DtFunc_Division		38
#define		__DtFunc_SetOpacity		39
#define		__DtFunc_SetDestructfrag		40
#define		__DtFunc_GetDestructfrag		41
#define		__DtFunc_SummonSoul		42
#define		__DtFunc_ThunderGenerate		43

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

/* TestPoint DisableList ---------------------------------------------------*/
#define	__Dt__DtFunc_getInstance__DtStep_0	/*FuncIn*/	
#define	__Dt__DtFunc_CharacterScriptInterface__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0001 );
#define	__Dt__DtFunc_CharacterScriptInterface__DtStep_1	/*for*/	_TP_BusOut( __DtBaseAddress, 0x0002 );
#define	__Dt__DtFunc_CharacterScriptInterface__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0003 );
#define	__Dt__DtFunc_CharacterScriptInterface__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0004 );
#define	__Dt__DtFunc_CharacterScriptInterface__DtStep_4	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0005 );
#define	__Dt__DtFunc_CharacterScriptInterface__DtStep_5	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0006 );
#define	__Dt__DtFunc_CharacterScriptInterface__DtStep_6	/*for*/	
#define	__Dt__DtFunc_CharacterScriptInterface__DtStep_7	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0008 );
#define	__Dt__DtFunc_CharacterScriptInterface__DtStep_8	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0009 );
#define	__Dt__DtFunc_update__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x000A );
#define	__Dt__DtFunc_update__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x000B );
#define	__Dt__DtFunc_getCharaAttackedGroup__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x000C );
#define	__Dt__DtFunc_getCharaAttackedGroup__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x000D );
#define	__Dt__DtFunc_getCharaPosition__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x000E );
#define	__Dt__DtFunc_getCharaPosition__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x000F );
#define	__Dt__DtFunc_setCharaState__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0010 );
#define	__Dt__DtFunc_setCharaState__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0011 );
#define	__Dt__DtFunc_setFrameCount__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0012 );
#define	__Dt__DtFunc_setFrameCount__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0013 );
#define	__Dt__DtFunc_setPuttern__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0014 );
#define	__Dt__DtFunc_setPuttern__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0015 );
#define	__Dt__DtFunc_judgeAttackCollision__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0016 );
#define	__Dt__DtFunc_judgeAttackCollision__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0017 );
#define	__Dt__DtFunc_judgeAttackCollision__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0018 );
#define	__Dt__DtFunc_judgeAttackCollision__DtStep_3	/*for*/	
#define	__Dt__DtFunc_judgeAttackCollision__DtStep_4	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x001A );
#define	__Dt__DtFunc_judgeAttackCollision__DtStep_5	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x001B );
#define	__Dt__DtFunc_attackEffect__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x001C );
#define	__Dt__DtFunc_attackEffect__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x001D );
#define	__Dt__DtFunc_disposeObject__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x001E );
#define	__Dt__DtFunc_disposeObject__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x001F );
#define	__Dt__DtFunc_AttackLock__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0020 );
#define	__Dt__DtFunc_AttackLock__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0021 );
#define	__Dt__DtFunc_AttackUnLock__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0022 );
#define	__Dt__DtFunc_AttackUnLock__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0023 );
#define	__Dt__DtFunc_AttackUnLock__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0024 );
#define	__Dt__DtFunc_AttackUnLock__DtStep_3	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0025 );
#define	__Dt__DtFunc_AttackUnLock__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0026 );
#define	__Dt__DtFunc_AttackUnLock__DtStep_5	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0027 );
#define	__Dt__DtFunc_getOnGround__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0028 );
#define	__Dt__DtFunc_getOnGround__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x002A );
#define	__Dt__DtFunc_setVelocity__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x002B );
#define	__Dt__DtFunc_setVelocity__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002C );
#define	__Dt__DtFunc_setVelocity__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x002D );
#define	__Dt__DtFunc_CheckWeaponBreak__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x002E );
#define	__Dt__DtFunc_CheckWeaponBreak__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x002F );
#define	__Dt__DtFunc_CheckWeaponBreak__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0031 );
#define	__Dt__DtFunc_CheckWeaponBreak__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0032 );
#define	__Dt__DtFunc_CheckWeaponBreak__DtStep_4	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0033 );
#define	__Dt__DtFunc_CheckWeaponBreak__DtStep_5	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0034 );
#define	__Dt__DtFunc_CheckWeaponBreak__DtStep_6	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0035 );
#define	__Dt__DtFunc_setBreakWeapon__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0036 );
#define	__Dt__DtFunc_setBreakWeapon__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0037 );
#define	__Dt__DtFunc_getBreakWeapon__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0038 );
#define	__Dt__DtFunc_getBreakWeapon__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0039 );
#define	__Dt__DtFunc_getBreakWeapon__DtStep_2	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x003A );
#define	__Dt__DtFunc_PlaySE__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x003B );
#define	__Dt__DtFunc_PlaySE__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x003C );
#define	__Dt__DtFunc_CreateEffect__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x003D );
#define	__Dt__DtFunc_CreateEffect__DtStep_1	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x003E );
#define	__Dt__DtFunc_CreateEffect__DtStep_2	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x003F );
#define	__Dt__DtFunc_CreateEffect__DtStep_3	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0040 );
#define	__Dt__DtFunc_CreateEffect__DtStep_4	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0041 );
#define	__Dt__DtFunc_CreateEffect__DtStep_5	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0042 );
#define	__Dt__DtFunc_CreateEffect__DtStep_6	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0043 );
#define	__Dt__DtFunc_CreateEffect__DtStep_7	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0044 );
#define	__Dt__DtFunc_setDirection__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0045 );
#define	__Dt__DtFunc_setDirection__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0046 );
#define	__Dt__DtFunc_setPosition__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0047 );
#define	__Dt__DtFunc_setPosition__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0048 );
#define	__Dt__DtFunc_GrenadeGenerate__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0049 );
#define	__Dt__DtFunc_GrenadeGenerate__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x004A );
#define	__Dt__DtFunc_BulletGenerate__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x004B );
#define	__Dt__DtFunc_BulletGenerate__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x004C );
#define	__Dt__DtFunc_setInvincibleFrame__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x004D );
#define	__Dt__DtFunc_setInvincibleFrame__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x004E );
#define	__Dt__DtFunc_setAccel__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x004F );
#define	__Dt__DtFunc_setAccel__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0050 );
#define	__Dt__DtFunc_getLife__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0051 );
#define	__Dt__DtFunc_getLife__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0052 );
#define	__Dt__DtFunc_setLife__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0053 );
#define	__Dt__DtFunc_setLife__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0054 );
#define	__Dt__DtFunc_getDirection__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0055 );
#define	__Dt__DtFunc_getDirection__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0056 );
#define	__Dt__DtFunc_getMaxLife__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0057 );
#define	__Dt__DtFunc_getMaxLife__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0058 );
#define	__Dt__DtFunc_getRank__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0059 );
#define	__Dt__DtFunc_getRank__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x005A );
#define	__Dt__DtFunc_getPlayerPos__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x005B );
#define	__Dt__DtFunc_getPlayerPos__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x005C );
#define	__Dt__DtFunc_Rand__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x005D );
#define	__Dt__DtFunc_Rand__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x005E );
#define	__Dt__DtFunc_getPhase__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x005F );
#define	__Dt__DtFunc_getPhase__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0060 );
#define	__Dt__DtFunc_getNum__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0061 );
#define	__Dt__DtFunc_getNum__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0062 );
#define	__Dt__DtFunc_setNum__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0063 );
#define	__Dt__DtFunc_setNum__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0064 );
#define	__Dt__DtFunc_SummonEnemy__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0065 );
#define	__Dt__DtFunc_SummonEnemy__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0066 );
#define	__Dt__DtFunc_Division__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0067 );
#define	__Dt__DtFunc_Division__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0068 );
#define	__Dt__DtFunc_SetOpacity__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0069 );
#define	__Dt__DtFunc_SetOpacity__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x006A );
#define	__Dt__DtFunc_SetDestructfrag__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x006B );
#define	__Dt__DtFunc_SetDestructfrag__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x006C );
#define	__Dt__DtFunc_GetDestructfrag__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x006D );
#define	__Dt__DtFunc_GetDestructfrag__DtStep_1	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x006E );
#define	__Dt__DtFunc_SummonSoul__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x006F );
#define	__Dt__DtFunc_SummonSoul__DtStep_1	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0070 );
#define	__Dt__DtFunc_SummonSoul__DtStep_2	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0071 );
#define	__Dt__DtFunc_SummonSoul__DtStep_3	/*switch*/	_TP_BusOut( __DtBaseAddress, 0x0072 );
#define	__Dt__DtFunc_SummonSoul__DtStep_4	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x0073 );
#define	__Dt__DtFunc_ThunderGenerate__DtStep_0	/*FuncIn*/	_TP_BusOut( __DtBaseAddress, 0x0074 );
#define	__Dt__DtFunc_ThunderGenerate__DtStep_1	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0075 );
#define	__Dt__DtFunc_ThunderGenerate__DtStep_2	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0076 );
#define	__Dt__DtFunc_ThunderGenerate__DtStep_3	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0077 );
#define	__Dt__DtFunc_ThunderGenerate__DtStep_4	/*for*/	
#define	__Dt__DtFunc_ThunderGenerate__DtStep_5	/*if*/	_TP_BusOut( __DtBaseAddress, 0x0079 );
#define	__Dt__DtFunc_ThunderGenerate__DtStep_6	/*if*/	_TP_BusOut( __DtBaseAddress, 0x007A );
#define	__Dt__DtFunc_ThunderGenerate__DtStep_7	/*FuncOut*/	_TP_BusOut( __DtBaseAddress, 0x007B );

#endif	/* __DT_CharacterScriptInterface_h__ */

