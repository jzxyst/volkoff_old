//=============================================================================
/*! 
    @addtogroup 
    @file       Bullet.cpp
    @brief     弾オブジェクト
    
    Bulletクラスの実装
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/27
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/27 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Bullet.h"	/* For DynamicTracer-TestPoint */
#include "./Bullet.h"
#include "./Player.h"
#include "./../Effect/Effect_1.h"
#include "./attackedobject.h"
#include "../Map/MapManager.h"
#include"../Game/GameManager.h"
//---------------------------------------------------------------------------
/*! 
	@brief Bullet::Bullet

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Bullet::Bullet()
{
	__DtTestPoint( __DtFunc_Bullet, __DtStep_0 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::~Bullet

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Bullet::~Bullet()
{
	__DtTestPoint( __DtFunc_Bullet, __DtStep_1 )
	this->Release();
	__DtTestPoint( __DtFunc_Bullet, __DtStep_2 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Bullet::Initialize()
{
	//setAttackedGroup( ATKGROUP_ENEMY );
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();
	this->mScore = 0; 
	this->mPanel = LBatchPanel::create(20.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-10, 10, 0);
	this->mPanel.setTexture(LTexture::create(g_szBulletFilePath,0xffffffff));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);
	this->mLife = 1;
	this->mFrameCnt = 0;
	this->mLifeFrame = 0;
	this->mGeneObjType = OBJ_CHARACTER;
	this->mRangeRate = 1;
	this-> mCriticalRate = 1;
	this->mBrowVec = 0;
	this->mStunFrame = 0;
	this->mDamage = 1;
	this->mSeVol = 30;
	//this->mGeneObjType = OBJ_ENEMY;
	//this->setObjType(OBJ_BULLET);
	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Bullet::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Bullet::Update()
{

	//mVelocity 
	//mVelocity.x=100;
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	if((this->getDirection()==CHARADIR_LEFT)&&(mFrameCnt == 0))
	{
		//mVelocity*=-1;
		//mBrowVec*=-1;
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
	}
	mPosition+=mVelocity;
	this->mPanel.setPosition(this->mPosition );
	//printf("x%f,  y%f\n",mVelocity.x,mVelocity.y);
//	printf("x%f,  y%f\n",getPosition().x+8,getPosition().y+8);
    //float dx, dy;
    //u32 result = judgeCollisionToMap( &dx, &dy );
	LRect rect;
	rect.x=mPosition.x+8;
	rect.y=mPosition.y-8;
	rect.w=4;
	rect.h=4;

	++mFrameCnt;
	//寿命が来たら弾を消す
	if((mLifeFrame!=0)&&(mFrameCnt>=mLifeFrame))
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		GameObjectManager::getInstance()->deleteObject( this );		
	}

	if(this->mLife<=0)
	{
		LVector3 v(this->mPosition);
		__DtTestPoint(__DtFunc_Update, __DtStep_3)
		v.z = 0.f;
		new Effect_Explosion2(v);
		Audio.playSE("./Data/Sound/SE/Explosion01.ogg",mSeVol,180);
		GameObjectManager::getInstance()->deleteObject( this );	
		//printf("sibou\n");
		this->setExit(true);
	}
	//一応範囲外にいったら消す
	if((this->getPosition().x>=2000)||(this->getPosition().y>=2000)||(this->getPosition().x<=0)||(this->getPosition().y<=0))
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_4)
		this->setExit(true);
	}


	HitObjectList*  obj_list;
	if(this->mGeneObjType == OBJ_CHARACTER)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_5)
		setAttackedGroup( ATKGROUP_PLAYER );
		obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(rect,OBJ_ENEMY);
	}
	else
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_6)
		setAttackedGroup( ATKGROUP_ENEMY );
		obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(rect,OBJ_CHARACTER);	
	}
    if ( obj_list->size() > 0 )
    {
        // 当たったオブジェクトのハンドルを 

        int idx = 1;
        HitObjectList::iterator itr = obj_list->begin();
        HitObjectList::iterator end = obj_list->end();
        __DtTestPoint(__DtFunc_Update, __DtStep_7)
        for ( ; itr != end; ++itr )
        {
		//	printf("敵hit\n");
			__DtTestPoint(__DtFunc_Update, __DtStep_8)
			if(this->mGeneObjType == OBJ_CHARACTER)
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_9)
				(*itr)->attackEffect(this,mDamage,mRangeRate,mCriticalRate,mBrowVec,mStunFrame);	
			}
			else
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_10)
				GameManager::getInstance()->getPlayer()->attackEffect(this,mDamage,mRangeRate,mCriticalRate,mBrowVec,mStunFrame);			
			}
			LVector3 v(this->mPosition);
			v.z = 0.f;
			new Effect_Explosion2(v);
			Audio.playSE("./Data/Sound/SE/Explosion01.ogg",mSeVol,180);
			this->setExit(true);
			//GameObjectManager::getInstance()->deleteObject( this );	
        }
        __DtTestPoint( __DtFunc_Update, __DtStep_11 )
        return 1;
    }


	bool result = MapManager::getInstance()->BulletCollision(rect);      
	if(result)
	{
		//LVector3 v(this->mPosition);
		//v.z = 0.f;
		//new Effect_Explosion2(v);
		//Audio.playSE("./Data/Sound/SE/Explosion01.ogg",30,180);
		__DtTestPoint(__DtFunc_Update, __DtStep_12)
		this->setExit(true);
		//GameObjectManager::getInstance()->deleteObject( this );
	}
	__DtTestPoint( __DtFunc_Update, __DtStep_13 )
	return 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Bullet::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	AttackedObject::HandleEvent( event_, args_ );

    switch ( event_ )
	{
		case EV_APPLY_DAMAGE:
			// ダメージ受けた時
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
			this->mLife -= 1;
			break;
	}

	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_2 )
	return true;
}

//
// Bullet::getBoundingRect
//
// 当たり判定を返す
//
const LRect* Bullet::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x+8, mPosition.y-8, 4, 4 );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================
