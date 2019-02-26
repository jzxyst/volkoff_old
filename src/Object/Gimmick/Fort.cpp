//=============================================================================
/*! 
    @addtogroup 
    @file       Fort.cpp
    @brief     自動機銃オブジェクト
    
    Fortクラスの実装
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/26
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/26 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Fort.h"	/* For DynamicTracer-TestPoint */
#include "./Fort.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Bullet.h"
#include "./../../Effect/Effect_1.h"


//---------------------------------------------------------------------------
/*! 
	@brief Fort::Fort

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Fort::Fort()
{
	__DtTestPoint( __DtFunc_Fort, __DtStep_0 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Fort::~Fort

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Fort::~Fort()
{
	__DtTestPoint( __DtFunc_Fort, __DtStep_1 )
	this->Release();
	__DtTestPoint( __DtFunc_Fort, __DtStep_2 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Fort::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Fort::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mLife = scg_nFortLife[GameManager::getInstance()->getRank()];
	this->m_nFrame = 0;
	this->mScore = 500;
	this->m_nAttackFrame = 0;
	this->m_nShootFrame = 0;
	this->m_nShootNum = 0;
	this->m_eAction = FORT_ACT_WAIT;

	this->setAttackedGroup( ATKGROUP_ENEMY );
	this->mColRect.set( mPosition.x+11, mPosition.y-7, 18*mScale.x, 33*mScale.y );

	this->mPanel = LBatchPanel::create(60.0f,60.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-30, 30, 0);
	this->mPanel.setTexture(LTexture::create(g_szFortFilePath,0xffffffff));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);
	this->mPanel.setCenter(17.0f,20.0f,0.0f);

	this->mPanel2 = LBatchPanel::create(20.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel2.setCenter(-10, 10, 0);
	this->mPanel2.setTexture(LTexture::create(g_szFortFilePath2));
	this->mPanel2.setPosition(LVector3(this->mPosition.x,this->mPosition.y,0));
	this->mPanel2.setVisible(true);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Fort::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Fort::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Fort::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Fort::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	++this->m_nFrame;
	int x = ::abs(this->mPosition.x - GameManager::getInstance()->getPlayer()->getPosition().x);
	int y = this->mPosition.y - GameManager::getInstance()->getPlayer()->getPosition().y;
	LVector3 pv = GameManager::getInstance()->getPlayer()->getPosition();
	pv.y += 30;

	switch(this->m_eAction)
	{
	case FORT_ACT_UNDEF:
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		break;

	case FORT_ACT_WAIT:
		//探索範囲内にプレイヤーが侵入した場合、動作を開始する
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		if(x <= scg_nSearchRangeX[GameManager::getInstance()->getRank()] && y <= scg_nSearchRangeY[GameManager::getInstance()->getRank()] && y >= 0)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_3)
			this->m_eAction = FORT_ACT_SEARCH;
		}
		break;

	case FORT_ACT_SEARCH:
		//指定した間隔でプレイヤーの方向に向く
		__DtTestPoint(__DtFunc_Update, __DtStep_4)
		if(!(this->m_nFrame % scg_nReactionSpeed[GameManager::getInstance()->getRank()]))
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_5)
			this->mPanel.setAngle(0.0f,0.0f,::atan2f((this->mPosition - pv).y,(this->mPosition - pv).x));
		}

		//探索範囲内の場合のみ動作する
		if(x <= scg_nSearchRangeX[GameManager::getInstance()->getRank()] && y <= scg_nSearchRangeY[GameManager::getInstance()->getRank()] && y >= 0)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_6)
			this->m_eAction = FORT_ACT_SEARCH;

			//攻撃範囲内の場合、動作を移行する
			if(x <= scg_nAttackRangeX[GameManager::getInstance()->getRank()] && y <= scg_nAttackRangeY[GameManager::getInstance()->getRank()] && y >= 0)
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_7)
				this->m_eAction = FORT_ACT_ATTACK_RANGE;
			}
		}
		//探索範囲外の場合、動作を終了する
		else
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_8)
			this->m_eAction = FORT_ACT_WAIT;
		}
		break;

	case FORT_ACT_ATTACK_RANGE:
		//指定した間隔でプレイヤーの方向に向く
		__DtTestPoint(__DtFunc_Update, __DtStep_9)
		if(!(this->m_nFrame % scg_nReactionSpeed[GameManager::getInstance()->getRank()]))
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_10)
			this->mPanel.setAngle(0.0f,0.0f,::atan2f((this->mPosition - pv).y,(this->mPosition - pv).x));
		}

		//攻撃範囲内の場合のみ動作する
		if(x <= scg_nAttackRangeX[GameManager::getInstance()->getRank()] && y <= scg_nAttackRangeY[GameManager::getInstance()->getRank()] && y >= 0)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_11)
			++this->m_nAttackFrame;
			if(this->m_nAttackFrame >= scg_nAttackIntv[GameManager::getInstance()->getRank()])
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_12)
				this->m_nAttackFrame = 0;
				this->m_nShootNum = scg_nShootNum[GameManager::getInstance()->getRank()];
				this->mShootVec = pv - this->mPosition;
				this->mShootVec.normalize();
				this->mShootVec *= scg_nShootSpeed[GameManager::getInstance()->getRank()];
				this->m_eAction = FORT_ACT_ATTACK;
			}
		}
		//探索範囲外の場合、動作を終了する
		else
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_13)
			this->m_nAttackFrame = 0;
			this->m_eAction = FORT_ACT_SEARCH;
		}
		break;

	case FORT_ACT_ATTACK:
		//指定した間隔でプレイヤーの方向に向く
		__DtTestPoint(__DtFunc_Update, __DtStep_14)
		if(!(this->m_nFrame % scg_nReactionSpeed[GameManager::getInstance()->getRank()]))
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_15)
			this->mShootVec = pv - this->mPosition;
			this->mShootVec.normalize();
			this->mShootVec *= scg_nShootSpeed[GameManager::getInstance()->getRank()];
			this->mPanel.setAngle(0.0f,0.0f,::atan2f((this->mPosition - pv).y,(this->mPosition - pv).x));
		}
		//攻撃回数が残っている間、攻撃を繰り返す
		if(this->m_nShootNum)
		{
			//発射間隔
			__DtTestPoint(__DtFunc_Update, __DtStep_16)
			if(this->m_nShootFrame >= scg_nShootIntv[GameManager::getInstance()->getRank()])
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_17)
				this->m_nShootFrame = 0;
				this->m_nShootNum -= 1;

				Bullet* obj = new Bullet();
				obj->Initialize();
				obj->setGeneObjType(OBJ_ENEMY);
				LVector3 pos = this->mPosition;
				pos.x -= 8;
				pos.y += 10;
				obj->setPosition(pos);
				obj->setVelocity(this->mShootVec);
				this->mShootVec.x >= 0 ? obj->setDirection(CHARADIR_RIGHT) : obj->setDirection(CHARADIR_LEFT);
				obj->setAttackParam(scg_nShootDamage[GameManager::getInstance()->getRank()],1,0,LVector3(0,0,0),5);

				Audio.playSE("./Data/Sound/SE/gun01.wav",30,100);
			}
			else
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_18)
				++this->m_nShootFrame;
			}
		}
		//攻撃回数の分繰り返した場合、攻撃動作を終了する
		else
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_19)
			this->m_nShootFrame = 0;
			this->m_eAction = FORT_ACT_ATTACK_RANGE;
		}
		break;

	default:
		__DtTestPoint(__DtFunc_Update, __DtStep_20)
		break;
	}

	if (this->mLife <= 0)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_21)
		this->mLife = 0;
		this->setExit(true);
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2))); 

		new Effect_Explosion(this->mPosition);
		Audio.playSE("./Data/Sound/SE/Explosion01.ogg",50,80);
	}

	this->mPanel.setPosition(this->mPosition);
	this->mPanel2.setPosition(this->mPosition);
	__DtTestPoint( __DtFunc_Update, __DtStep_22 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Fort::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Fort::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	AttackedObject::HandleEvent( event_, args_ );

	AttackEventArg* arg = reinterpret_cast< AttackEventArg* >( args_ );

    switch ( event_ )
	{
		case EV_APPLY_DAMAGE:
			// ダメージ受けた時
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
			this->mLife -= arg->Damage;
			Audio.playSE("./Data/Sound/SE/Explosion02.mp3",90,130);

			break;
	}

	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_2 )
	return true;
}


const LRect* Fort::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x+11, mPosition.y-7, 18*mScale.x, 33*mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================