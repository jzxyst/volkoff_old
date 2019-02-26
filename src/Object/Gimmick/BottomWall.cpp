//=============================================================================
/*! 
    @addtogroup 
    @file       BottomWall.cpp
    @brief      壁オブジェクト
    
    BottomWallクラスの定義
    
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
#include	"DT_BottomWall.h"	/* For DynamicTracer-TestPoint */
#include "./BottomWall.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"


//---------------------------------------------------------------------------
/*! 
	@brief BottomWall::BottomWall

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
BottomWall::BottomWall()
{
	__DtTestPoint( __DtFunc_BottomWall, __DtStep_0 )
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
	__DtTestPoint( __DtFunc_BottomWall, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief BottomWall::~BottomWall

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
BottomWall::~BottomWall()
{
	__DtTestPoint( __DtFunc_BottomWall, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_BottomWall, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief BottomWall::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool BottomWall::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	LTexture t = LTexture::create(g_szBottomWallFilePath);
	//this->mPanel = LBatchPanel::create(160.0f,160.0f,LN_PANELDIR_UPPER_REFT);
    this->mPanel = LBatchPanel::create(160.0f,160.0f);
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
	@brief BottomWall::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool BottomWall::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief BottomWall::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool BottomWall::Update()
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
				if(this->m_nAnime < 8)
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
					pEnemy->setPosition(LVector3(this->mPosition.x + 65,this->mPosition.y - 130,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 65,this->mPosition.y - 130,this->mPosition.z));
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
	@brief BottomWall::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int BottomWall::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}



//=============================================================================
//								End of File
//=============================================================================
