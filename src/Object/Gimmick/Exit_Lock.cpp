//=============================================================================
/*! 
    @addtogroup 
    @file       Exit_Lock.cpp
    @brief      ���t���o���I�u�W�F�N�g
    
    Exit_Lock�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/11/25
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/25 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Exit_Lock.h"	/* For DynamicTracer-TestPoint */
#include "./Exit_Lock.h"
#include "./../GameObjectManager.h"
#include "./../../Game/GameManager.h"
#include "./../../Map/MapManager.h"
//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::Exit_Lock

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit_Lock::Exit_Lock()
    : mGuideNamePlate   ( NULL )
{
	__DtTestPoint( __DtFunc_Exit_Lock, __DtStep_0 )
	mColRect.set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );
	__DtTestPoint( __DtFunc_Exit_Lock, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::~Exit_Lock

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit_Lock::~Exit_Lock()
{

	__DtTestPoint( __DtFunc_Exit_Lock, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Exit_Lock, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit_Lock::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(140.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-70, 40, 0);
	this->mPanel.setTexture(LTexture::create(g_szExit_LockFilePath));
	this->mPanel.setSrcRect(LRect(0,0,140,80));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);
	this->mFlameCnt = 0;
    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 2, 70, 20 );

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit_Lock::Release()
{
    __DtTestPoint( __DtFunc_Release, __DtStep_0 )
    SAFE_DELETE( mGuideNamePlate );
	__DtTestPoint( __DtFunc_Release, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit_Lock::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	this->mPanel.setPosition(this->mPosition);

	if(GameManager::getInstance()->getOpenflag())
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		mFlameCnt++;

     
        if(mFlameCnt ==10)
		{
            __DtTestPoint(__DtFunc_Update, __DtStep_2)
            LLayer::getBGLayer().setTone( LTone( -1, -1, -1, 0 ), 15.f / 60 );
        }

		if(mFlameCnt ==15)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_3)
			Audio.playSE("./Data/Sound/SE/doorclose2.wav",100,100);
			Audio.playSE("./Data/Sound/SE/doorclose3.wav",90,80);


            
            
		}
		if((mFlameCnt>=15)&&(mFlameCnt <=21))
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_4)
			this->mPanel.setSrcRect(LRect((this->mFlameCnt-15) * 140,0,140,80));
		}
		if(mFlameCnt == 25)
		{
// �R���e�B�j���[�ɔ����ăo�b�N�A�b�v�����
                __DtTestPoint(__DtFunc_Update, __DtStep_5)
                GameManager::getInstance()->commit();
			GameManager::getInstance()->setOpenflag(0);
			GameManager::getInstance()->setKeyflag(0);
			GameObjectManager::getInstance()->deleteStageObject();
			GameManager::getInstance()->NextFloor();
            
			MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());	
		}
	}

	__DtTestPoint( __DtFunc_Update, __DtStep_6 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit_Lock::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Exit_Lock::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}

const LRect* Exit_Lock::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================
