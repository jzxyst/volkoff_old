//=============================================================================
/*! 
    @addtogroup 
    @file       Exit.cpp
    @brief      出口オブジェクト
    
    Exitクラスの定義
    
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
#include	"DT_Exit.h"	/* For DynamicTracer-TestPoint */
#include "./Exit.h"


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Exit

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit::Exit()
    : mGuideNamePlate   ( NULL )
{
	__DtTestPoint( __DtFunc_Exit, __DtStep_0 )
	mColRect.set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );
	__DtTestPoint( __DtFunc_Exit, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::~Exit

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit::~Exit()
{
	__DtTestPoint( __DtFunc_Exit, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Exit, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(140.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-70, 40, 0);
	this->mPanel.setTexture(LTexture::create(g_szExitFilePath));
	this->mPanel.setSrcRect(LRect(0,0,140,80));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 2, 70, 20 );

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit::Release()
{
    __DtTestPoint( __DtFunc_Release, __DtStep_0 )
    SAFE_DELETE( mGuideNamePlate );
	__DtTestPoint( __DtFunc_Release, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	this->mPanel.setPosition(this->mPosition);

	__DtTestPoint( __DtFunc_Update, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Exit::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}
const LRect* Exit::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================