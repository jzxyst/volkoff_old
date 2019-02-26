//=============================================================================
/*! 
    @addtogroup 
    @file       Duct.cpp
    @brief      ダクトオブジェクト
    
    Ductクラスの定義
    
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
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Duct.h"	/* For DynamicTracer-TestPoint */
#include "./Duct.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"


//---------------------------------------------------------------------------
/*! 
	@brief Duct::Duct

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Duct::Duct()
{
	__DtTestPoint( __DtFunc_Duct, __DtStep_0 )
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
	__DtTestPoint( __DtFunc_Duct, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::~Duct

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Duct::~Duct()
{
	__DtTestPoint( __DtFunc_Duct, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Duct, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Duct::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(100.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-50, 40, 0);
	this->mPanel.setTexture(LTexture::create(g_szDuctFilePath));
	this->mPanel.setSrcRect(LRect(0,0,100,80));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Duct::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Duct::Update()
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
		//Audio.playSE("./Data/Sound/SE/manhole03.wav",100,180);
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		Audio.playSE("./Data/Sound/SE/manhole02.wav",100,180);
		Audio.playSE("./Data/Sound/SE/manhole01.wav",100,160);
		this->m_bStart = true;
	}

	if(this->m_bActive)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		if(this->m_bStart)
		{
			//窓アニメーション
			__DtTestPoint(__DtFunc_Update, __DtStep_3)
			if(this->m_nAnime < 5)
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_4)
				this->m_nAnime++;
				this->mPanel.setSrcRect(LRect(this->m_nAnime * 100,0,100,80));
			}

			//敵出現
			if(!(this->m_nFrame % 6)) //2フレームに1回
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_5)
				if(this->m_nEnemyNum)
				{
					Enemy* pEnemy = Enemy::createRandom();
					__DtTestPoint(__DtFunc_Update, __DtStep_6)
					pEnemy->setPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 100,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 100,this->mPosition.z));
					pEnemy->setVelocity(LVector3(::rand() % 10 - 5,0,0));

					this->m_nEnemyNum -= 1;
				}
			}
		}

	}

	__DtTestPoint( __DtFunc_Update, __DtStep_7 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Duct::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Duct::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}



//=============================================================================
//								End of File
//=============================================================================