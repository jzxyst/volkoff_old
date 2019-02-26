//=============================================================================
/*! 
    @addtogroup 
    @file       Window.cpp
    @brief      窓オブジェクト
    
    Windowクラスの定義
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/11/22
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/22 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Window.h"	/* For DynamicTracer-TestPoint */
#include "./Window.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"


//---------------------------------------------------------------------------
/*! 
	@brief Window::Window

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Window::Window()
{
	__DtTestPoint( __DtFunc_Window, __DtStep_0 )
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
	__DtTestPoint( __DtFunc_Window, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Window::~Window

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Window::~Window()
{
	__DtTestPoint( __DtFunc_Window, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Window, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Window::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Window::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(128.0f,192.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-64, 96, 0);
	this->mPanel.setTexture(LTexture::create(g_szWindowFilePath));
	this->mPanel.setSrcRect(LRect(0,0,128,192));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Window::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Window::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Window::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Window::Update()
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
		//Enemy *pEnemy = NULL;
		//for(int i = 0;i < this->m_nEnemyNum;++i)
		//{
		//	pEnemy = Enemy::create(NULL);
		//	pEnemy->setPosition(LVector3(this->getPosition().x + 62,this->getPosition().y - 80,this->getPosition().z));
		//	pEnemy->setVelocity(LVector3(::rand() % 10 - 5,0,0));
		//}

		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		Audio.playSE("./Data/Sound/SE/crash_grass2.wav",60,30);
		Audio.playSE("./Data/Sound/SE/crash_grass2.wav",60,50);
		Audio.playSE("./Data/Sound/SE/crash_grass2.wav",60,65);
		Audio.playSE("./Data/Sound/SE/crash_grass2.wav",60,100);
		Audio.playSE("./Data/Sound/SE/crash_grass2.wav",60,80);
		this->m_bStart = true;
	}

	if(this->m_bActive)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		if(this->m_bStart)
		{
			//窓アニメーション
			__DtTestPoint(__DtFunc_Update, __DtStep_3)
			if(this->m_nAnime < 8)
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_4)
				this->m_nAnime++;
				this->mPanel.setSrcRect(LRect(this->m_nAnime * 128,0,128,192));
			}

			//敵出現
			if(!(this->m_nFrame % 6)) //2フレームに1回
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_5)
				if(this->m_nEnemyNum)
				{
					Enemy* pEnemy = Enemy::createRandom();
					__DtTestPoint(__DtFunc_Update, __DtStep_6)
					pEnemy->setPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
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
	@brief Window::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Window::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}



//=============================================================================
//								End of File
//=============================================================================
