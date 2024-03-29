//=============================================================================
/*! 
    @addtogroup 
    @file       GameObject.cpp
    @brief      オブジェクトベース
    
    オブジェクトベースの実装
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/13 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


#include "stdafx.h"
#include	"DT_GameObject.h"	/* For DynamicTracer-TestPoint */
#include "GameObject.h"
#include "../Map/MapManager.h"
#include "../Game/GameManager.h"

GameObject::GameObject()
	: mHandle   ( 0 )
	, mScale	(1,1,1)
    , m_eDirection  ( CHARADIR_RIGHT )
	, mLife     (100)
    , mMaxLife  ( 100 )
	, mScore  (0)
	, mExit   (false)
    , mOnGround     ( false )
	, mPosition(0.0f)
	, mDefPosition(0.0f)
{
	__DtTestPoint( __DtFunc_GameObject, __DtStep_0 )
	GameObjectManager::getInstance()->AddObject(this);
	__DtTestPoint( __DtFunc_GameObject, __DtStep_1 )
}


GameObject::~GameObject()
{
    __DtTestPoint( __DtFunc_GameObject, __DtStep_2 )
    GameManager::getInstance()->getGameSession()->sendToServer( SYSEV_DELETE_GAMEOBJECT, &mHandle, sizeof( u32 ) );

	mExit = true;
	__DtTestPoint( __DtFunc_GameObject, __DtStep_3 )
}

// 長い名前書くのが面倒なのでこちらに実装
GameObjectManager* GameObject::getManager() { 
	__DtTestPoint( __DtFunc_getManager, __DtStep_0 )
	return GameObjectManager::getInstance(); }

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
bool GameObject::Update()
{
    // 空中にいる場合
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	if ( !mOnGround )
	{
        // 地面の上にいなければ重力で加速
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		mAccel.y -= GRAVITY_ACCEL;

		if ( mVelocity.y < -10.0f )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_2)
			mVelocity.y = -10.0f;
		}
	}
    // 地面上にいる場合
	else
	{
		// 地面に当たっていて、下方向の加速度がある場合はリセットする
		__DtTestPoint(__DtFunc_Update, __DtStep_3)
		if ( mAccel.y < 0 )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_4)
			mAccel.y = 0;
		}
		if ( mVelocity.y < 0 )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_5)
			mVelocity.y = 0;
		}

        if ( mVelocity.getSquareLength() < 1.0f )
        {
            __DtTestPoint(__DtFunc_Update, __DtStep_6)
            mVelocity = 0.0f;
		}
	}

    // 普通に移動
    mVelocity += mAccel;

    // 地形との当たり判定
    float dx, dy;
    u32 result = judgeCollisionToMap( &dx, &dy );
    if ( result )
    {
        // 下が当たっている場合は地面の上にいるとする
	    __DtTestPoint(__DtFunc_Update, __DtStep_7)
	    if ( result & MAPCOLL_DOWN )
        {
            __DtTestPoint(__DtFunc_Update, __DtStep_8)
            mOnGround = true;
        }
    }
    else
    {
        __DtTestPoint(__DtFunc_Update, __DtStep_9)
        mOnGround = false;
    }

    mPosition.x += dx;
    mPosition.y += dy;
    mPosition.z = -6.0f;

    __DtTestPoint( __DtFunc_Update, __DtStep_10 )
    return true;
}

//---------------------------------------------------------------------
// ● 地形との当たり判定を行う
//---------------------------------------------------------------------
u32 GameObject::judgeCollisionToMap( float* dx_, float* dy_ )
{
    __DtTestPoint( __DtFunc_judgeCollisionToMap, __DtStep_0 )
    *dx_ = *dy_ = 0.0f;

    // 当たり判定全般は、判定用の矩形がある場合にのみ行う
    const LRect* rc = getBoundingRect();
    if ( rc )
    {
        LRect col_rect = *rc;

        // 移動した後の座標
	    LVector3 d_pos = mPosition + mVelocity;

        // 移動前の判定用矩形の座標
        float px = col_rect.x;
        float py = col_rect.y;

        // 矩形を移動させて、移動後の判定領域にする
        __DtTestPoint(__DtFunc_judgeCollisionToMap, __DtStep_1)
        col_rect.x += static_cast< int >( mVelocity.x );
        col_rect.y += static_cast< int >( mVelocity.y );
        
	    // 移動量 (いまはつかわないかも)
	    LVector3 dest = mPosition - d_pos;

	    // マップとの当たり判定結果の、修正後の座標を格納する変数
	    LVector3 result_pos;
		
        
	    u32 result = MapManager::getInstance()->collision( col_rect, dest, &result_pos );

        // 移動前と比べて、移動量を求める
        *dx_ = result_pos.x - px;
        *dy_ = result_pos.y - py;

		__DtTestPoint( __DtFunc_judgeCollisionToMap, __DtStep_2 )
		return result;
    }
    __DtTestPoint( __DtFunc_judgeCollisionToMap, __DtStep_3 )
    return 0;
}
    /// 速度の設定 (攻撃によるふっ飛ばし等で使う)
void GameObject::setVelocity(  LVector3& vel_ ) 
{
	__DtTestPoint( __DtFunc_setVelocity, __DtStep_0 )
	if(!mOnGround)
	{
		__DtTestPoint(__DtFunc_setVelocity, __DtStep_1)
		if(vel_.x>=16)
			vel_.x=16;
		if(vel_.x<=-16)
			vel_.x=-16;		
	}
	mVelocity = vel_; 
	__DtTestPoint( __DtFunc_setVelocity, __DtStep_2 )
}

//=============================================================================
//								End of File
//=============================================================================
