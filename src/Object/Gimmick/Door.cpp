//=============================================================================
/*! 
    @addtogroup 
    @file       Door.cpp
    @brief      ドアオブジェクト
    
    Doorクラスの定義
    
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
#include	"DT_Door.h"	/* For DynamicTracer-TestPoint */
#include "./Door.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"


//---------------------------------------------------------------------------
/*! 
	@brief Door::Door

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Door::Door()
{
	__DtTestPoint( __DtFunc_Door, __DtStep_0 )
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
	__DtTestPoint( __DtFunc_Door, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Door::~Door

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Door::~Door()
{
	__DtTestPoint( __DtFunc_Door, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Door, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Door::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Door::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(140.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-70, 40, 0);
	this->mPanel.setTexture(LTexture::create(g_szDoorFilePath));
	this->mPanel.setSrcRect(LRect(0,0,140,80));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Door::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Door::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Door::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Door::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	++this->m_nFrame;
	this->mPanel.setPosition(this->mPosition);

	//発動条件（適当）//上下差が200以下 かつ 左右差が10以下
	const int y = 100;
	const int x = 200;
	LVector3 myPos = this->mPosition;
	myPos.x += 50;
	if(abs(myPos.y - GameManager::getInstance()->getPlayer()->getPosition().y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && this->m_bActive && !this->m_bStart)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		Audio.playSE("./Data/Sound/SE/doorclose2.wav",100,100);
		Audio.playSE("./Data/Sound/SE/doorclose3.wav",90,80);
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
				this->mPanel.setSrcRect(LRect(this->m_nAnime * 140,0,140,80));
			}

			//敵出現
			if(!(this->m_nFrame % 6)) //2フレームに1回
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_5)
				if(this->m_nEnemyNum)
				{
					//Weapon::CreateData wdata2;
					//wdata2.Data.WeaponType  = WEAPON_STICK;
					//wdata2.Data.UseCount    = 30;
					//wdata2.Position         = LVector3(this->mPosition.x + 62 + ::rand() % 40 - 20,this->mPosition.y,this->mPosition.z);
					//Weapon* test_weapon2 = Weapon::create( &wdata2 );

					//Enemy *pEnemy = Enemy::create(NULL);
					//pEnemy->setPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
					//pEnemy->setVelocity(LVector3(::rand() % 10 - 5,0,0));

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
	@brief Door::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Door::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}



//=============================================================================
//								End of File
//=============================================================================