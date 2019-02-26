//=============================================================================
/*! 
    @addtogroup 
    @file       Mine.cpp
    @brief      地雷オブジェクト
    
    Mineクラスの実装
    
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
#include	"DT_Mine.h"	/* For DynamicTracer-TestPoint */
#include "./Mine.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../../Effect/Effect_1.h"
#include "./../attackedobject.h"


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Mine

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Mine::Mine()
{
	__DtTestPoint( __DtFunc_Mine, __DtStep_0 )
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
	__DtTestPoint( __DtFunc_Mine, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::~Mine

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Mine::~Mine()
{
	__DtTestPoint( __DtFunc_Mine, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Mine, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Mine::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(20.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-10, 10, 0);
	this->mPanel.setTexture(LTexture::create(g_szMineFilePath));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Mine::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Mine::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	++this->m_nFrame;
	this->mPanel.setPosition(this->mPosition);

	//発動条件（適当）//上下差が200以下 かつ 左右差が10以下
	const int y = 20;
	const int x = 6;
	LVector3 myPos = this->mPosition;
	myPos.x += 10;
	//myPos.y -= 50;
	if(::abs(GameManager::getInstance()->getPlayer()->getPosition().y - myPos.y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && !this->m_bStart)
	{
		LVector3 v(this->mPosition);
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		v.z = 0.f;
		new Effect_Explosion(v);
		this->m_bStart = true;

		//ダメージを与えたい場合はここに書く
		GameManager::getInstance()->getPlayer()->attackEffect(GameManager::getInstance()->getPlayer(),100,1,1,LVector3(0,6,0),65);
		Audio.playSE("./Data/Sound/SE/Explosion01.ogg",50,130);
		//ここまで

		GameObjectManager::getInstance()->deleteObject(this);
	}

	__DtTestPoint( __DtFunc_Update, __DtStep_2 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Mine::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}


//=============================================================================
//								End of File
//=============================================================================