//=============================================================================
/*! 
    @addtogroup 
    @file       Vase.cpp
    @brief      花瓶オブジェクト
    
    Vaseクラスの実装
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Vase.h"	/* For DynamicTracer-TestPoint */
#include "./Vase.h"
//#include "./Item/Cure_L.h"
#include "./../Player.h"
#include "./../../Game/GameManager.h"

//---------------------------------------------------------------------------
/*! 
	@brief Vase::Vase

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Vase::Vase()
{
	__DtTestPoint( __DtFunc_Vase, __DtStep_0 )
	setAttackedGroup( ATKGROUP_ENEMY );
	mColRect.set( mPosition.x+11, mPosition.y-7, 18*mScale.x, 33*mScale.y );
	__DtTestPoint( __DtFunc_Vase, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::~Vase

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Vase::~Vase()
{
	__DtTestPoint( __DtFunc_Vase, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Vase, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Vase::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();
	this->mScore = 250;
	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-20, 20, 0);
	this->mPanel.setTexture(LTexture::create(g_szVaseFilePath));
	this->mPanel.setSrcRect(LRect(0,0,40,40));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

	this->mLife = 1;
	this->m_nAnime = 0;
	this->m_nFrame = 0;
	this->m_bCreate = false;
	this->mScore = 300;

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Vase::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Vase::Update()
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
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2))); 
            
			Audio.playSE("./Data/Sound/SE/crash_grass2.wav",80,100);
			Audio.playSE("./Data/Sound/SE/crash_grass2.wav",80,130);
		}
		if(m_nFrame%1==0)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_4)
			this->m_nAnime++;
			this->mPanel.setSrcRect(LRect(this->m_nAnime * 40,0,40,40));
		}

		if(m_nAnime >=5)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_5)
			this->setExit( true );
		}
		
	}

	__DtTestPoint( __DtFunc_Update, __DtStep_6 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Vase::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	AttackedObject::HandleEvent( event_, args_ );

    switch ( event_ )
	{
		case EV_APPLY_DAMAGE:
			// ダメージ受けた時
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
			this->mLife -= 50;
			break;
	}

	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_2 )
	return true;
}

// Box::getBoundingRect
//
// 細田追加・当たり判定を返す
//
const LRect* Vase::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x+11, mPosition.y-7, 18*mScale.x, 33*mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}



//=============================================================================
//								End of File
//=============================================================================