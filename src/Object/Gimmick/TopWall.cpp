//=============================================================================
/*! 
    @addtogroup 
    @file       TopWall.cpp
    @brief      空中壁オブジェクト
    
    TopWallクラスの定義
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2012/01/23
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2012/01/23 Hi-ra Mizuno
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_TopWall.h"	/* For DynamicTracer-TestPoint */
#include "./TopWall.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"


//---------------------------------------------------------------------------
/*! 
	@brief TopWall::TopWall

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
TopWall::TopWall()
{
	__DtTestPoint( __DtFunc_TopWall, __DtStep_0 )
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
	__DtTestPoint( __DtFunc_TopWall, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief TopWall::~TopWall

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
TopWall::~TopWall()
{
	__DtTestPoint( __DtFunc_TopWall, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_TopWall, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief TopWall::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TopWall::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	LTexture t = LTexture::create(g_szTopWallFilePath);
	this->mPanel = LBatchPanel::create(160.0f,160.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-80, 80, 0);
	this->mPanel.setTexture(t);
	this->mPanel.setSrcRect(LRect(0,0,160,160));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TopWall::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TopWall::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TopWall::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool TopWall::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	++this->m_nFrame;
	this->mPanel.setPosition(this->mPosition);

	//発動条件（適当）//上下差が200以下 かつ 左右差が10以下
	const int y = 150;
	const int x = 100;
	LVector3 myPos = this->mPosition;
	myPos.x += 50;
	myPos.y -= 100;
	if(abs(myPos.y - GameManager::getInstance()->getPlayer()->getPosition().y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && this->m_bActive && !this->m_bStart)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		Audio.playSE("./Data/Sound/SE/don01.wav",75,100);
		Audio.playSE("./Data/Sound/SE/don01.wav",90,70);
		Audio.playSE("./Data/Sound/SE/don01.wav",90,60);
		this->m_bStart = true;
	}

	if(this->m_bActive)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		if(this->m_bStart)
		{
			//窓アニメーション
			__DtTestPoint(__DtFunc_Update, __DtStep_3)
			if(!(this->m_nFrame % 2))
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_4)
				if(this->m_nAnime < 7)
				{
					__DtTestPoint(__DtFunc_Update, __DtStep_5)
					this->m_nAnime++;
					this->mPanel.setSrcRect(LRect(this->m_nAnime * 160.0f,0,160.0f,160.0f));
				}
			}

			//敵出現
			if(!(this->m_nFrame % 6)) //2フレームに1回
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_6)
				if(this->m_nEnemyNum)
				{
					Enemy* pEnemy = Enemy::createRandom();
					__DtTestPoint(__DtFunc_Update, __DtStep_7)
					pEnemy->setPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
					pEnemy->setVelocity(LVector3(::rand() % 10 - 5,0,0));

					this->m_nEnemyNum -= 1;
				}
			}
		}

	}

	__DtTestPoint( __DtFunc_Update, __DtStep_8 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TopWall::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int TopWall::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}



//=============================================================================
//								End of File
//=============================================================================
