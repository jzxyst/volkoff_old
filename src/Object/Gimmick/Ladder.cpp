//=============================================================================
/*! 
    @addtogroup 
    @file       Ladder.cpp
    @brief      はしごオブジェクト
    
    Ladderクラスの実装
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Ladder.h"	/* For DynamicTracer-TestPoint */
#include "./Ladder.h"


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Ladder

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Ladder::Ladder()
{
	__DtTestPoint( __DtFunc_Ladder, __DtStep_0 )
	mColRect.set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );
	__DtTestPoint( __DtFunc_Ladder, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::~Ladder

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Ladder::~Ladder()
{
	__DtTestPoint( __DtFunc_Ladder, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Ladder, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Ladder::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(60.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-30, 10, 0);
	this->mPanel.setTexture(LTexture::create(g_szLaderFilePath));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);




	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Ladder::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Ladder::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	this->mPanel.setPosition(this->mPosition);

	__DtTestPoint( __DtFunc_Update, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Ladder::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}

//
// Ladder::getBoundingRect
//
// 細田追加・当たり判定を返す
//
const LRect* Ladder::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================