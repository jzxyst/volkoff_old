//=============================================================================
/*! 
    @addtogroup 
    @file       Box.cpp
    @brief     ���I�u�W�F�N�g
    
    Box�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/26
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/26 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Box.h"	/* For DynamicTracer-TestPoint */
#include "./Box.h"
#include "./../Weapon.h"
#include "./../Player.h"
#include "./../../Game/GameManager.h"

//---------------------------------------------------------------------------
/*! 
	@brief Box::Box

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Box::Box()
{
	// �U���ΏۃO���[�v�͓G��
    __DtTestPoint( __DtFunc_Box, __DtStep_0 )
    setAttackedGroup( ATKGROUP_ENEMY );
	mColRect.set( mPosition.x+20, mPosition.y-20, 60*mScale.x, 60*mScale.y );
	__DtTestPoint( __DtFunc_Box, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::~Box

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Box::~Box()
{
	__DtTestPoint( __DtFunc_Box, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Box, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Box::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(100.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-50, 40, 0);
	this->mPanel.setTexture(LTexture::create(g_szBoxFilePath));
	this->mPanel.setSrcRect(LRect(0,0,100,80));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

	this->mLife = 1;
	this->m_nAnime = 0;
	this->m_nFrame = 0;
	this->m_bCreate = false;
	this->mScore = 500;

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Box::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Box::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	if ( this->mLife > 0 )
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		this->mPanel.setPosition(this->mPosition);
	}



	if ( this->mLife <= 0)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		this->mLife = 0;
		this->m_nFrame++;
		if(m_nFrame==1)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_3)
			Audio.playSE("./Data/Sound/SE/don01.wav",50,170);
			Audio.playSE("./Data/Sound/SE/don01.wav",50,120);
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2))); 
    
		}
		if(m_nFrame%2==0)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_4)
			this->m_nAnime++;
			this->mPanel.setSrcRect(LRect(this->m_nAnime * 100,0,100,80));
		}

		if(m_nAnime >=5)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_5)
			this->setExit( true );
		}
		
	}

	//�A�C�e�����o��
	if ( this->mLife <= 0 && !this->m_bCreate)
	{
		// �o�����̑��a
		int rate_max = 0;
		__DtTestPoint(__DtFunc_Update, __DtStep_6)
		for ( int i = 0; i < WEAPON_NORMAL_MAX_NUM; ++i )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_7)
			if ( gWeaponBaseData[ i ].BoxRate )
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_8)
				rate_max += gWeaponBaseData[ i ].BoxRate;
			}
		}

		// �l���ЂƂ��߂�
		int value = rand() % rate_max;

		// �l�ɑΉ����镐���T��
		int i = 0;
		for ( ; 0 < WEAPON_NORMAL_MAX_NUM; ++i )
		{
			int rating = gWeaponBaseData[ i ].BoxRate;
			__DtTestPoint(__DtFunc_Update, __DtStep_9)
			if ( rating > 0 )
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_10)
				if ( rating > value )
				{
					__DtTestPoint(__DtFunc_Update, __DtStep_11)
					break;
				}
				value -= rating;
			}
		}

		if(i)
		{
			Weapon::CreateData wdata;

			__DtTestPoint(__DtFunc_Update, __DtStep_12)
			wdata.Data.WeaponType  = static_cast<WeaponType>(i);
			wdata.Data.UseCount    = gWeaponBaseData[i].UseCount;

			LVector3 v = this->mPosition;
			//v.y += 100;
			wdata.Position = v;
			Weapon::create( &wdata );
		}

		this->m_bCreate = true;
	}

	__DtTestPoint( __DtFunc_Update, __DtStep_13 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Box::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	AttackedObject::HandleEvent( event_, args_ );

    switch ( event_ )
	{
		case EV_APPLY_DAMAGE:
			// �_���[�W�󂯂���
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
			this->mLife -= 50;
			break;
	}

	//if ( this->mLife <= 0 )
	//{
	//	this->mLife = 0;
	//		this->setExit( true );
	//		return true;
	//}

	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_2 )
	return true;
}

//
// Box::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* Box::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x+20, mPosition.y-20, 60*mScale.x, 60*mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================