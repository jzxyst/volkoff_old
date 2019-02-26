//=============================================================================
/*! 
    @addtogroup 
    @file       GameObject.cpp
    @brief      �I�u�W�F�N�g�x�[�X
    
    �I�u�W�F�N�g�x�[�X�̎���
    
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
      -# �쐬
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

// �������O�����̂��ʓ|�Ȃ̂ł�����Ɏ���
GameObjectManager* GameObject::getManager() { 
	__DtTestPoint( __DtFunc_getManager, __DtStep_0 )
	return GameObjectManager::getInstance(); }

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
bool GameObject::Update()
{
    // �󒆂ɂ���ꍇ
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	if ( !mOnGround )
	{
        // �n�ʂ̏�ɂ��Ȃ���Ώd�͂ŉ���
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		mAccel.y -= GRAVITY_ACCEL;

		if ( mVelocity.y < -10.0f )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_2)
			mVelocity.y = -10.0f;
		}
	}
    // �n�ʏ�ɂ���ꍇ
	else
	{
		// �n�ʂɓ������Ă��āA�������̉����x������ꍇ�̓��Z�b�g����
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

    // ���ʂɈړ�
    mVelocity += mAccel;

    // �n�`�Ƃ̓����蔻��
    float dx, dy;
    u32 result = judgeCollisionToMap( &dx, &dy );
    if ( result )
    {
        // �����������Ă���ꍇ�͒n�ʂ̏�ɂ���Ƃ���
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
// �� �n�`�Ƃ̓����蔻����s��
//---------------------------------------------------------------------
u32 GameObject::judgeCollisionToMap( float* dx_, float* dy_ )
{
    __DtTestPoint( __DtFunc_judgeCollisionToMap, __DtStep_0 )
    *dx_ = *dy_ = 0.0f;

    // �����蔻��S�ʂ́A����p�̋�`������ꍇ�ɂ̂ݍs��
    const LRect* rc = getBoundingRect();
    if ( rc )
    {
        LRect col_rect = *rc;

        // �ړ�������̍��W
	    LVector3 d_pos = mPosition + mVelocity;

        // �ړ��O�̔���p��`�̍��W
        float px = col_rect.x;
        float py = col_rect.y;

        // ��`���ړ������āA�ړ���̔���̈�ɂ���
        __DtTestPoint(__DtFunc_judgeCollisionToMap, __DtStep_1)
        col_rect.x += static_cast< int >( mVelocity.x );
        col_rect.y += static_cast< int >( mVelocity.y );
        
	    // �ړ��� (���܂͂���Ȃ�����)
	    LVector3 dest = mPosition - d_pos;

	    // �}�b�v�Ƃ̓����蔻�茋�ʂ́A�C����̍��W���i�[����ϐ�
	    LVector3 result_pos;
		
        
	    u32 result = MapManager::getInstance()->collision( col_rect, dest, &result_pos );

        // �ړ��O�Ɣ�ׂāA�ړ��ʂ����߂�
        *dx_ = result_pos.x - px;
        *dy_ = result_pos.y - py;

		__DtTestPoint( __DtFunc_judgeCollisionToMap, __DtStep_2 )
		return result;
    }
    __DtTestPoint( __DtFunc_judgeCollisionToMap, __DtStep_3 )
    return 0;
}
    /// ���x�̐ݒ� (�U���ɂ��ӂ���΂����Ŏg��)
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
