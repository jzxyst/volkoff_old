//=============================================================================
/*! 
    @addtogroup 
    @file       UBW.cpp
    @brief      UBW�I�u�W�F�N�g
    
    UBW�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2012/2/3
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2012/2/3 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_UBW.h"	/* For DynamicTracer-TestPoint */
#include "./UBW.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Weapon.h"


//---------------------------------------------------------------------------
/*! 
	@brief UBW::UBW

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
UBW::UBW()
{

	__DtTestPoint( __DtFunc_UBW, __DtStep_0 )
}


//---------------------------------------------------------------------------
/*! 
	@brief UBW::~UBW

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
UBW::~UBW()
{
	__DtTestPoint( __DtFunc_UBW, __DtStep_1 )
	this->Release();
	__DtTestPoint( __DtFunc_UBW, __DtStep_2 )
}


//---------------------------------------------------------------------------
/*! 
	@brief UBW::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool UBW::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();
	this->mUBW = 0;
	this->mFlameCnt = 0;
	this->m_bStart = false;
	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief UBW::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool UBW::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief UBW::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool UBW::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	++mFlameCnt;

	const int y = 120;
	const int x = 250;
	LVector3 myPos = this->mPosition;
	//myPos.x += 50;
	//myPos.y -= 0;
	if(abs(myPos.y - GameManager::getInstance()->getPlayer()->getPosition().y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && !this->m_bStart)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		this->m_bStart = true;

		this->mUBW = 15;
	}

	if(this->m_bStart)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		if(this->mUBW && !(this->mFlameCnt % 2))
		{
			Weapon::CreateData wdata;

			__DtTestPoint(__DtFunc_Update, __DtStep_3)
			wdata.Data.WeaponType  = static_cast<WeaponType>(::rand() % (WEAPON_NORMAL_MAX_NUM - 1) + 1);
			wdata.Data.UseCount   = gWeaponBaseData[wdata.Data.WeaponType].UseCount;

			LVector3 v = this->mPosition;
			v.x += ::rand() % 250 - 125;
			v.y += 180;
			wdata.Position = v;
			Weapon::create( &wdata );

			mUBW--;
		}
	}

	__DtTestPoint( __DtFunc_Update, __DtStep_4 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief UBW::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int UBW::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}


//=============================================================================
//								End of File
//=============================================================================