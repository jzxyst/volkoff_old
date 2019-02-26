//=============================================================================
/*! 
    @addtogroup 
    @file       Character.cpp
    @brief      
    
    �L�����N�^�[�N���X�̎���
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/17
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/17 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Character.h"	/* For DynamicTracer-TestPoint */
#include "Character.h"
#include "CharacterScriptInterface.h"
#include "../Map/MapManager.h"
#include "../Object/GameObjectManager.h"
#include"../Game/GameManager.h"
#include "../Frontend/CharacterNamePlate.h"
#include "../Frontend/GameFrontendManager.h"

//---------------------------------------------------------------------------
/*! 
	@brief Character::Character

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Character::Character()
	: mFrameCount   ( 0 )
    , mStunFrame    ( 0 )
    , mCharacterNamePlate   ( NULL )
{
	__DtTestPoint(__DtFunc_Character, __DtStep_0)
	this->m_pszName = '\0'; //�ꎞ�I�B��œK���Ȗ��O��������
	this->m_eCharaState = CHARASTATE_WAIT;
	this->m_eDirection = CHARADIR_RIGHT;

	this->mJump = false;
	this->mOnGround = false;
	this->mTouchLadder = false;
	this->mClimbLadder = false;
	this->mStandOnObject = false;
	this->mAttackLocked = false;
	this->mBreakWeapon = false;
	this->mDistance.set( 0, 0 );
	this->mCollision = NULL;
    this->mPosition.set( 0, 0, -10.0f );
	this->mOldTouchObj = OBJ_UNDEF;
	this->mNewTouchObj = OBJ_UNDEF;
	this->mInvincibleFrame = 0;
	__DtTestPoint(__DtFunc_Character, __DtStep_1)
}


//---------------------------------------------------------------------------
/*! 
	@brief Character::~Character

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Character::~Character()
{
	__DtTestPoint(__DtFunc_Character, __DtStep_2)
	this->mCollision->Release();
	this->Release();

    
	__DtTestPoint(__DtFunc_Character, __DtStep_3)
}

//---------------------------------------------------------------------
// �� �L�����N�^�[�̌�����ݒ肷��
//---------------------------------------------------------------------
void Character::setDirection( CharaDir dir_ )
{
    __DtTestPoint(__DtFunc_setDirection, __DtStep_0)
    GameObject::setDirection( dir_ );

    if(this->m_eDirection == CHARADIR_RIGHT)
	{
		__DtTestPoint(__DtFunc_setDirection, __DtStep_1)
		this->mCharaPanel.setAngle(0,0,0);
	}
	else
	{
		__DtTestPoint(__DtFunc_setDirection, __DtStep_2)
		this->mCharaPanel.setAngle(0,LMath::PI,0);
	}
	__DtTestPoint(__DtFunc_setDirection, __DtStep_3)
}

//---------------------------------------------------------------------
// �� ���[���h���W��ԏ�ł̓����蔻���`��Ԃ�
//---------------------------------------------------------------------
const LRect* Character::getBoundingRect()
{
    const LRect* rc = mCollision->getDmgCollisionByIndex( getAnimePuttern() );
    __DtTestPoint(__DtFunc_getBoundingRect, __DtStep_0)
    if ( rc )
    {
        // �E����
        __DtTestPoint(__DtFunc_getBoundingRect, __DtStep_1)
        if ( m_eDirection == CHARADIR_RIGHT )
        {
            __DtTestPoint(__DtFunc_getBoundingRect, __DtStep_2)
            mWorldBoundingRect.set(
                static_cast< int >( mPosition.x - ( mOrigin.x - rc->x ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->w, rc->h );
            __DtTestPoint(__DtFunc_getBoundingRect, __DtStep_3)
            return &mWorldBoundingRect;
        }
        // ������
        else
        {
            __DtTestPoint(__DtFunc_getBoundingRect, __DtStep_4)
            mWorldBoundingRect.set(
                static_cast< int >( mPosition.x - ( rc->w - ( mOrigin.x - rc->x ) ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->w, rc->h );
            __DtTestPoint(__DtFunc_getBoundingRect, __DtStep_5)
            return &mWorldBoundingRect;
        }
    }
    __DtTestPoint(__DtFunc_getBoundingRect, __DtStep_6)
    return NULL;
}

//---------------------------------------------------------------------
// �� ���[�J�����W��ԏ�ł̓����蔻���`��Ԃ� (���ォ��̈ʒu)
//---------------------------------------------------------------------
const LRect* Character::getLocalBoundingRect()
{
    static LRect tmp;

    const LRect* rc = mCollision->getDmgCollisionByIndex( getAnimePuttern() );
    __DtTestPoint(__DtFunc_getLocalBoundingRect, __DtStep_0)
    if ( rc )
    {
        // �E����
        //if ( m_eDirection == CHARADIR_RIGHT )
        __DtTestPoint(__DtFunc_getLocalBoundingRect, __DtStep_1)
        {
            tmp.set( rc->x, rc->y, rc->w, rc->h );
            __DtTestPoint(__DtFunc_getLocalBoundingRect, __DtStep_2)
            return &tmp;
        }
        // ������
        /*
        else
        {
            tmp.set(
                160 - rc->x - rc->width,
                rc->y, rc->width, rc->height );
            return &tmp;
        }
        */
    }
    __DtTestPoint(__DtFunc_getLocalBoundingRect, __DtStep_3)
    return NULL;
}


//---------------------------------------------------------------------
// �� ���[���h���W��ԏ�ł̍U�������蔻���`��Ԃ�
//---------------------------------------------------------------------
const LRect* Character::getAttackBoundingRect()
{
    static LRect tmp;

    const LRect* rc = mCollision->getAtkCollisionByIndex( getAnimePuttern() );
    __DtTestPoint(__DtFunc_getAttackBoundingRect, __DtStep_0)
    if ( rc )
    {
        // �E����
        __DtTestPoint(__DtFunc_getAttackBoundingRect, __DtStep_1)
        if ( m_eDirection == CHARADIR_RIGHT )
        {
            __DtTestPoint(__DtFunc_getAttackBoundingRect, __DtStep_2)
            tmp.set(
                static_cast< int >( mPosition.x - ( mOrigin.x - rc->x ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->w, rc->h );
            __DtTestPoint(__DtFunc_getAttackBoundingRect, __DtStep_3)
            return &tmp;
        }
        // ������
        else
        {
            __DtTestPoint(__DtFunc_getAttackBoundingRect, __DtStep_4)
            tmp.set(
                static_cast< int >( mPosition.x - ( rc->w - ( mOrigin.x - rc->x ) ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->w, rc->h );
            __DtTestPoint(__DtFunc_getAttackBoundingRect, __DtStep_5)
            return &tmp;
        }
    }
    __DtTestPoint(__DtFunc_getAttackBoundingRect, __DtStep_6)
    return NULL;
}

void Character::setWeponUseCount(int UseCount_)
{
	__DtTestPoint(__DtFunc_setWeponUseCount, __DtStep_0)
	mWeaponData.UseCount = UseCount_;
	__DtTestPointValue(__DtFunc_setWeponUseCount, __DtStep_1, (void *)&mWeaponData.WeaponType, sizeof(mWeaponData.WeaponType))
	__DtTestPointValue(__DtFunc_setWeponUseCount, __DtStep_2, (void *)&mWeaponData.UseCount, sizeof(mWeaponData.UseCount))
	__DtTestPoint(__DtFunc_setWeponUseCount, __DtStep_3)
}

//---------------------------------------------------------------------
// �� �A�j���[�V�����p�^�[���̐ݒ�
//---------------------------------------------------------------------
void Character::setAnimePuttern( int puttern_ )
{
    __DtTestPoint(__DtFunc_setAnimePuttern, __DtStep_0)
    m_AnimePuttern = puttern_;

    int x = ( m_AnimePuttern % 12 ) * 160;
    int y = ( m_AnimePuttern / 12 ) * 160;




    /*
    // ���� X ���W�̌v�Z
    int x = ( m_AnimePuttern % 6 ) * 160;
    if ( m_AnimePuttern >= 72 )
    {
        x += 960;
    }

    // ���� Y ���W�̌v�Z
    int y = ( m_AnimePuttern / 6 ) * 160;
    if ( m_AnimePuttern >= 72 )
    {
        y %= 1920;
    }
    */

    mCharaPanel->setSrcRect( LRect( x, y, 160, 160 ) );

    // ���_���ݒ肷��
	mOrigin.set(
		this->mCollision->getOriginByIndex( m_AnimePuttern ).x,
		this->mCollision->getOriginByIndex( m_AnimePuttern ).y,
		0.0f );
	this->mCharaPanel.setCenter( mOrigin.x - 80, -mOrigin.y + 80, 0 );
	__DtTestPoint(__DtFunc_setAnimePuttern, __DtStep_1)
}

//---------------------------------------------------------------------------
/*! 
	@brief Character::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Character::Initialize()
{
	__DtTestPoint(__DtFunc_Initialize, __DtStep_0)
	this->Release();

	//this->m_pszName = '\0'; //�ꎞ�I�B��œK���Ȗ��O��������    Enemy �� initialize �Ŗ��O�ݒ肷��Ƃ��ɕs�ւ������̂ŃJ�b�g
	this->m_eCharaState = CHARASTATE_WAIT;
	this->m_eDirection = CHARADIR_RIGHT;
	this->mJump = false;
	this->mOnGround = false;
	this->mTouchLadder = false;
	this->mClimbLadder = false;
	this->mStandOnObject = false;
	this->mAttackLocked = false;
	this->mStandOnObject = false;
	this->mBreakWeapon = 0;
	this->m_AnimePuttern = 0;
	this->mOldTouchObj = OBJ_UNDEF;
	this->mNewTouchObj = OBJ_UNDEF;

	mWeaponData.WeaponType = WEAPON_NON;//WEAPON_STICK;//WEAPON_KATANA;
    mWeaponData.UseCount   = -1;
	

	this->mCharaPanel = LBatchPanel::create(160.0f,160.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mCharaPanel.setCenter(-80, 80, 0);
	this->mCharaPanel.setTexture(LTexture::create(CharaResourceNames[mWeaponData.WeaponType].Character));//0xffffffff));
	this->mCharaPanel.setCullingMode(LN_CULL_DOUBLE);
	//this->mCharaPanel.setCenter(0.0f,0.0f,0.0f);
	this->mCharaPanel.setSrcRect(LRect(0,0,160,160));
	this->mCharaPanel.setPosition(0.0f,0.0f,0.0f);
	this->mCharaPanel.setVisible(true);



    /*mCharaPanel->setEnableDepthTest( false );
    mCharaPanel->setEnableDepthWrite( false );*/
    //mCharaPanel->setBlendMode( LN_BLEND_NORMAL );

    this->mCollision = NEW Collision();
	this->mCollision->Initialize();
	
    changeWeapon( mWeaponData );
    setAnimePuttern( 0 );


    mCharacterNamePlate = NEW CharacterNamePlate();
    mCharacterNamePlate->initialize( this );

	__DtTestPoint(__DtFunc_Initialize, __DtStep_1)
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Character::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Character::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //delete��Manager�ɔC����
	__DtTestPoint(__DtFunc_Release, __DtStep_0)
	SAFE_DELETE( this->mCollision );
    SAFE_DELETE( mCharacterNamePlate );

	__DtTestPoint(__DtFunc_Release, __DtStep_1)
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Character::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Character::Update()
{
    // �X�N���v�g���g���čX�V
    __DtTestPoint(__DtFunc_Update, __DtStep_0)
    CharacterScriptInterface::getInstance()->update( this );


    // ���S���[�V�������̏ꍇ (�Ƃ肠�����B�K�v������΃X�N���v�g�Ɉڂ�)
    //if ( getCharaState() == CHARASTATE_DEAD ) // ������уA�j���̂܂܃t�F�[�h�A�E�g�Ƃ��̏ꍇ�̓R������_��
    if ( isDead() )
    {
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		mClimbLadder = false;
        setAnimePuttern( 102 + mFrameCount / 10 );
        mCharaPanel->setOpacity( 1.0f - ( static_cast< float >( mFrameCount ) * 0.025641f ) ); // 0.025641f �� 39 �̋t��
        if ( mFrameCount == 39 )
        {
            __DtTestPoint(__DtFunc_Update, __DtStep_2)
            setExit( true );
            __DtTestPoint(__DtFunc_Update, __DtStep_3)
            return true;
        }
    };

	if(mInvincibleFrame>0)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_4)
		--mInvincibleFrame;
	}

    //---------------------------------------------------------
    // �� �ړ��ƃW�����v�A�n�`�Ƃ̓����蔻��̏���

	// �W�����v
	if ( mJump )
	{
		//mVelocity.y += scg_fJumpHeight;
		__DtTestPoint(__DtFunc_Update, __DtStep_5)
	}

	// �󒆂ɂ���ꍇ
	if ( !mOnGround )
	{
        // �n�ʂ̏�ɂ��Ȃ���Ώd�͂ŉ���
		__DtTestPoint(__DtFunc_Update, __DtStep_6)
		mAccel.y -= GRAVITY_ACCEL;

		if(mVelocity.x>=16)
			mVelocity.x=16;
		if(mVelocity.x<=-16)
			mVelocity.x=-16;
	}
    // �n�ʏ�ɂ���ꍇ
	else if ( !mClimbLadder || mStandOnObject )
	{
		// �n�ʂɓ������Ă��āA�������̉����x������ꍇ�̓��Z�b�g����
		__DtTestPoint(__DtFunc_Update, __DtStep_7)
		if ( mAccel.y < 0 )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_8)
			mAccel.y = 0;
		}
		if ( mVelocity.y < 0 )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_9)
			mVelocity.y = 0;
		}

        mVelocity *= FRICTION_COEFF;

        if ( mVelocity.getSquareLength() < 1.0f )
        {
            __DtTestPoint(__DtFunc_Update, __DtStep_10)
            mVelocity = 0.0f;
		}
	}
	//�A�j���[�V����
	switch(this->m_eCharaState)
	{
	case CHARASTATE_RUN:
		__DtTestPoint(__DtFunc_Update, __DtStep_11)
		if(this->m_eDirection == CHARADIR_RIGHT)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_12)
			mVelocity.x = scg_fRunSpeed;
		}
		else
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_13)
			mVelocity.x = -scg_fRunSpeed;
		}
		break;

	case CHARASTATE_JUMP:
		__DtTestPoint(__DtFunc_Update, __DtStep_14)
		mClimbLadder = false;
		break;

	case CHARASTATE_SQUAT:
		__DtTestPoint(__DtFunc_Update, __DtStep_15)
		break;

	case CHARASTATE_LADDER_WAIT:    //�͂����ҋ@
		__DtTestPoint(__DtFunc_Update, __DtStep_16)
		this->mVelocity.y = 0;
		break;

	// �� �͂������~���x�ύX�͂���----------------
	case CHARASTATE_LADDER_UP:      //�͂������

		__DtTestPoint(__DtFunc_Update, __DtStep_17)
		if ( this->mClimbLadder )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_18)
			this->mVelocity.y = static_cast< float >( scg_fRunSpeed*0.9f );
		}
		else
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_19)
			getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
		}
		break;

	case CHARASTATE_LADDER_DOWN:    //�͂����~��

		__DtTestPoint(__DtFunc_Update, __DtStep_20)
		if ( this->mClimbLadder )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_21)
			this->mVelocity.y = static_cast< float >( -scg_fRunSpeed*0.9f );
		}
		else
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_22)
			getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
		}
		
		break;
	// �� �͂������~���x�ύX�͂���----------------
	}


	// ��q�ɂ��܂��Ă�Ƃ��͉������̑��x�A�d�͂ɂ������x������
	if ( mClimbLadder )
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_23)
		mVelocity.x = 0;
		if ( !mJump ) mAccel.y = 0;
	}
	// ����ȊO�͕��ʂɉ���
	else
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_24)
		mVelocity += mAccel;
		if ( mVelocity.y < -10.0f )
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_25)
			mVelocity.y = -10.0f;
		}
	}

    // �����蔻��S�ʂ́A����p�̋�`������ꍇ�ɂ̂ݍs��
    const LRect* rc = getBoundingRect();
    if ( rc )
    {
        LRect col_rect = *rc;

        // �ړ�������̍��W
	    LVector3 d_pos = mPosition + mVelocity;

        // �ړ��O�̔���p��`�̍��W
        float px = static_cast< float >( col_rect.x );
        float py = static_cast< float >( col_rect.y );

        // ��`���ړ������āA�ړ���̔���̈�ɂ���
        __DtTestPoint(__DtFunc_Update, __DtStep_26)
        col_rect.x += static_cast< int >( mVelocity.x );
        col_rect.y += static_cast< int >( mVelocity.y );
        
	    // �ړ��� (���܂͂���Ȃ�����)
	    LVector3 dest = mPosition - d_pos;

	    // �}�b�v�Ƃ̓����蔻�茋�ʂ́A�C����̍��W���i�[����ϐ�
	    LVector3 result_pos;
  		//MapManager::getInstance()->BulletCollision(col_rect);      
	    u32 result = MapManager::getInstance()->collision( col_rect, dest, &result_pos );

        // �ړ��O�Ɣ�ׂāA�ړ��ʂ����߂�
        float dx = result_pos.x - px;
        float dy = result_pos.y - py;

        // �オ�������Ă���ꍇ�̓W�����v�̉��Z��0�ɂ���
		if ( result & MAPCOLL_UP )
			mVelocity.y = 0;

       
		
        


	// �� �n�㔻��-------------------------------
		// �ȉ��̏ꍇ�͒n�ʂ̏�ɂ���Ƃ���
		if ( result & MAPCOLL_DOWN || mClimbLadder || this->mStandOnObject )
	    {
		    __DtTestPoint(__DtFunc_Update, __DtStep_27)
		    mOnGround = true;
		    mJump = false;

			if ( result & MAPCOLL_DOWN )mClimbLadder = false;
	    }
		else
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_28)
			mOnGround = false;
		}
	// �� �n�㔻��-------------------------------

        
        

		// ���ۂ̍��W�ɔ��f������
	    mPosition.x += dx;//result_pos.x + ( mOrigin.x - getLocalBoundingRect()->x );
        mPosition.y += dy;//result_pos.y - ( mOrigin.y - getLocalBoundingRect()->y );

        // �I�u�W�F�N�g�Ƃ̓����蔻��
		CollisionToObj();
    }

    // �ŏI�I�Ƀp�l�����|�W�V�����ɍ��킹��
    this->mPosition.z = -5.0f;
    this->mCharaPanel.setPosition(this->mPosition);

	++mFrameCount;

    // �̂������Ă���ꍇ�͎c��t���[���������炵�Ă���
    if ( mStunFrame > 0 )
    {
        __DtTestPoint(__DtFunc_Update, __DtStep_29)
        --mStunFrame;
        if ( mStunFrame == 0 )
        {
            __DtTestPoint(__DtFunc_Update, __DtStep_30)
            setCharaState( CHARASTATE_DEFAULT );
        }
    }

    // �A�C�e���擾�҂���
    if ( getCharaState() == CHARASTATE_ITEMGET )
    {
        __DtTestPoint(__DtFunc_Update, __DtStep_31)
        --mItemGetWaitCount;

        // �^�C���A�E�g�B�p�������ɖ߂�
        if ( mItemGetWaitCount <= 0 )
        {
            __DtTestPoint(__DtFunc_Update, __DtStep_32)
            setCharaState( CHARASTATE_DEFAULT );
        }
    }


    mCharacterNamePlate->update();

	__DtTestPoint(__DtFunc_Update, __DtStep_33)
	return true;
}

//---------------------------------------------------------------------------
// �� �t���[���X�V���� (�I�u�W�F�N�g�ɉe����^���鏈��)
//---------------------------------------------------------------------------
bool Character::UpdateSelf()
{
    // ���̂ւ�̃L�[���͂͂��Ƃ� Player �Ɉړ�����\��

    // ���S (���S���[�V������) �͓��͂��󂯕t���Ȃ�
    __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_0)
    if ( isDead() )
    {
        __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_1)
        return true;
    }

    // ��{���[�V�������ŕ���j��t���O�������Ă���ꍇ�͑f��ɂ���
    if ( getCharaState() <= CHARASTATE_ATTACK_BEGIN_ && getWeaponData().WeaponType != WEAPON_NON && getWeaponData().UseCount <= 0 )//&& mBreakWeapon )
    {
        __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_2)
        AttackUnLock();
        mFrameCount = 0;

        WeaponData temp;
		temp.WeaponType=WEAPON_NON;
		temp.UseCount=-1;
        changeWeapon(temp);

        mBreakWeapon = false;
    }

    // �ړ��ł���ꍇ (�̂����蒆���ł͂Ȃ�)
    if ( mStunFrame == 0 )
    {
        bool right = Input.isPress( LN_BUTTON_RIGHT );
        bool left  = Input.isPress( LN_BUTTON_LEFT );
		bool button_B  = Input.isOnTrigger( LN_BUTTON_B );
		bool Up = Input.isPress( LN_BUTTON_UP );
		bool UpTrigger = Input.isOnTrigger( LN_BUTTON_UP );
		bool Down = Input.isPress( LN_BUTTON_DOWN );		
		bool DownTrigger = Input.isOnTrigger( LN_BUTTON_DOWN );
		bool Guard = Input.isPress( LN_BUTTON_C );
		bool GuardTrigger = Input.isOnTrigger( LN_BUTTON_C );

        //------------------------------------------------------
        // �U�����쒆�̏ꍇ
        __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_3)
        if ( isAttacking() )
        {
			// �s�����������i=�o���I���j���ĂȂ��Ƒ���s��
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_4)
			if ( !mAttackLocked )
			{
				// ������ς��邽�߂̏���
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_5)
				if ( right )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_6)
					setDirection( CHARADIR_RIGHT );
				}
				else if ( left )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_7)
					setDirection( CHARADIR_LEFT );
				}

				// �A���U��
				if ( Input.isOnTrigger( LN_BUTTON_A ) )
				{
					// �s������
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_8)
					this->AttackLock();

					switch( m_eCharaState )
					{
					case CHARASTATE_ATTACK_1:
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_9)
						getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_2, NULL, 0 );
						break;

					case CHARASTATE_ATTACK_2:
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_10)
						getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_3, NULL, 0 );
						break;

					default:
						// �����ꂨ�������l�ɂȂ����烍�b�N����
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_11)
						this->AttackUnLock();
						break;
					}
				}
			}
        }
        //------------------------------------------------------
        // �U�����쒆�ł͂Ȃ��ꍇ
        else
        {
			
			// �U���J�n
            __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_12)
            if ( !Guard && !this->mClimbLadder && Input.isOnTrigger( LN_BUTTON_A ) && m_eCharaState != EV_ACTION_ATTACK_1 )  // ���͉̂�
            {
                // �W�����v���̏ꍇ
                __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_13)
                if ( !mOnGround )
                {
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_14)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_JUMP_ATTACK, NULL, 0 );
                }
                // ���Ⴊ�ݒ��̏ꍇ
                else if ( Down )
                {
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_15)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_SQUAT_ATTACK, NULL, 0 );
                }
				// ��������Ȃ���̏ꍇ
				else if ( !this->mClimbLadder && Up )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_16)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_ANTIAIR_ATTACK, NULL, 0 );
				}
                // �ȏ�ȊO�͒ʏ�U��
                else
                {
					// �U���̂��ߍs������
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_17)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_1, NULL, 0 );
                }

                __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_18)
                return true;
            }

			// �K�[�h
			if ( !Down && Guard && this->mOnGround && !this->mClimbLadder && m_eCharaState != CHARASTATE_GUARD )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_19)
				getManager()->postEvent( getHandle(), EV_ACTION_GUARD, NULL, 0 );
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_20)
				return true;
			}

			// ������ς��邽�߂̏���
			if ( right )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_21)
				setDirection( CHARADIR_RIGHT );
			}
			else if ( left )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_22)
				setDirection( CHARADIR_LEFT );
			}

			//// �E�ړ�
			//if ( !mClimbLadder && right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
			//{
			//	// ���������� EV_ACTION_RUN �C�x���g�𑗂�B
			//	// ���̂��ƁAHandleEvent() �Ŏ��ۂɈړ����J�n����B
			//	// ���̃C�x���g�̓L���[�C���O�����A������ HandleEvent() �ɑ�����B
			//	//u32 dir = CHARADIR_RIGHT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		//getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}
			//// ���ړ�
			//else if( !mClimbLadder && left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) )
			//{
			//	//u32 dir = CHARADIR_LEFT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		//getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}


			// �ړ�
			if ( ( !Guard && !this->mClimbLadder && right && !left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
				|| ( !Guard && !this->mClimbLadder && left && !right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) ) )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_23)
				if ( !Down )
					getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			}
			// ���E�̂������������Ă��Ȃ��ꍇ�͑ҋ@�ɂ���
			// ��q�������Ƃ����ҋ@�ŁB
			// (���� mState != CHARASTATE_WAIT �́A�ҋ@���ɘA���ŃC�x���g�������Ȃ��悤�ɂ��邽�߂ɕK�v)
			else if (
                !Guard &&
                this->mOnGround &&
                ( ( !right && !left ) || ( right && left ) ) &&
                !Down &&
                ( !this->mClimbLadder ) &&
                this->m_eCharaState != CHARASTATE_WAIT )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_24)
				getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
			}

			// �W�����v�J�n
			if ( button_B && this->m_eCharaState != CHARASTATE_JUMP && ( this->mOnGround || this->mClimbLadder || mStandOnObject ) )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_25)
				getManager()->postEvent( getHandle(), EV_ACTION_JUMP, NULL, 0 );
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_26)
				return true;
			}

			// ���Ⴊ�݊J�n
			if ( Down && this->mOnGround && !this->mTouchLadder )
			{
				// ���Ⴊ�݂Ȃ���K�[�h�����ꍇ
				// �K�[�h���Ȃ��炵�Ⴊ�񂾏ꍇ
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_27)
				if ( ( ( GuardTrigger ) || ( DownTrigger && Guard ) ) && this->m_eCharaState != CHARASTATE_SQGUARD )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_28)
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT_GUARD, NULL, 0 );
				}
				else if ( !Guard && this->m_eCharaState != CHARASTATE_SQUAT )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_29)
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT, NULL, 0 );
				}
			}

			// �͂�������
			if ( this->mTouchLadder
				&& this->m_eCharaState != CHARASTATE_LADDER_UP
				&& this->m_eCharaState != CHARASTATE_LADDER_DOWN
				&& this->m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				bool Catch = false;

				// ��A�����������u��
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_30)
				if ( ( UpTrigger && !this->mStandOnObject )
					|| ( DownTrigger ) )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_31)
					Catch = true;
				}

				if ( Catch )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_32)
					if ( this->mDistance.y > 0 )
					{
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_33)
						this->mDistance.y = 0;
					}

					this->mPosition.set(
						this->mPosition.x + this->mDistance.x,
						this->mPosition.y ,//+ this->mDistance.y,
						this->mPosition.z
						);
					this->mClimbLadder = true;
					this->mOnGround = false;
				}
				else
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_34)
					this->mClimbLadder = false;
				}
			}

			// �͂����㏸
			if ( Up && this->mClimbLadder && this->m_eCharaState != CHARASTATE_LADDER_UP )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_35)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_UP, NULL, 0 );

				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_36)
				return true;
			}
			// �͂������~
			else if ( Down && this->mClimbLadder && this->m_eCharaState != CHARASTATE_LADDER_DOWN )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_37)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_DOWN, NULL, 0 );

				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_38)
				return true;
			}
			// �͂����ҋ@
			else if ( !Up && !Down && this->mClimbLadder && this->m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_39)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_WAIT, NULL, 0 );

				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_40)
				return true;
			}

			//�A�N�V�����{�^��
			if ( Input.isOnTrigger( LN_BUTTON_X ) )
			{
				const LRect* rc = getBoundingRect();
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_41)
				if ( rc )
				{
					//�o���Ƃ̂����蔻��
					u32 exit_handle =getManager()->judgeCollitionTypeSpecified( *rc, OBJ_EXIT );
					u32 exit_lock_handle =getManager()->judgeCollitionTypeSpecified( *rc, OBJ_EXIT_LOCK);
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_42)
					if(exit_handle)
					{

								
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_43)
					}

					if(exit_lock_handle)
					{
						//printf("���t���o��\n");
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_44)
						if(GameManager::getInstance()->getKeyflag())
						{
// �R���e�B�j���[�ɔ����ăo�b�N�A�b�v�����
                        __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_45)
                        GameManager::getInstance()->commit();
							Audio.playSE("./Data/Sound/SE/open.wav",150,100);
							GameManager::getInstance()->setOpenflag(1);		
						}
						else
						{
							__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_46)
							Audio.playSE("./Data/Sound/SE/lock.wav",150,100);					
						}
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_47)
						return true;
					}


                    // ����Ƃ̓����蔻��
					u32 item_handle = getManager()->judgeCollitionTypeSpecified( *rc, OBJ_WEAPON );
                    if ( item_handle )
                    {
                        // �A�C�e�����擾���邽�߂ɃT�[�o�Ƀ��b�Z�[�W�𑗂�B
                        ItemRequestArgs args;
                        __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_48)
                        args.GetterHandle  = this->getHandle();
                        args.ItemObjHandle = item_handle;
                        GameManager::getInstance()->getGameSession()->sendToServer( 
                            SYSEV_ITEM_REQUEST, &args, sizeof( ItemRequestArgs ) );
                    
                        // �A�C�e���擾�A�N�V�����J�n
                        //getManager()->postEvent( getHandle(), EV_ACTION_ITEM_GET, NULL, 0 );

					    __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_49)
					    return true;
                    }

                    // ���E�A�C�e���Ƃ̓����蔻��
                    // item_handle = getManager()->judgeCollitionTypeSpecified( *rc, OBJ_ITEM_BEGIN, OBJ_ITEM_END );
                    //if ( item_handle )
                    //{
                    //    _p("�����Ă�");
                    //}
				}
			}
        }
    }

    __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_50)
    return true;
}




//---------------------------------------------------------------------------
/*! 
	@brief Character::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Character::HandleEvent(u32 event_,void *args_)
{
    __DtTestPoint(__DtFunc_HandleEvent, __DtStep_0)
    AttackedObject::HandleEvent( event_, args_ );

    __DtTestPointEventTrigger(__DtFunc_HandleEvent, __DtStep_1, event_)
    switch ( event_ )
    {
        ///////////////////////////////////////// �ҋ@�J�n
        case EV_ACTION_WAIT:
            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_2)
            setCharaState( CHARASTATE_WAIT );
            break;

        ///////////////////////////////////////// ����J�n
        case EV_ACTION_RUN:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_3)
			setCharaState( CHARASTATE_RUN );
			//setDirection( *( (CharaDir*)args_ ) );
            break;

		///////////////////////////////////////// �W�����v�J�n
		case EV_ACTION_JUMP:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_4)
			setCharaState( CHARASTATE_JUMP );
			this->JumpStart();
			break;

		///////////////////////////////////////// ���Ⴊ�݊J�n
		case EV_ACTION_SQUAT:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_5)
			setCharaState( CHARASTATE_SQUAT );
			break;

        ///////////////////////////////////////// �̂�����J�n
        case EV_ACTION_STUN:
            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_6)
            mStunFrame = *( reinterpret_cast< u32* >( args_ ) );
            setCharaState( CHARASTATE_STUN );
            mClimbLadder = false;
            mJump = true;
            break;

		///////////////////////////////////////// �ӂ��ƂъJ�n
		case EV_ACTION_BLOW:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_7)
			mStunFrame = *( reinterpret_cast< u32* >( args_ ) );
			setCharaState( CHARASTATE_BLOW );
			break;

		///////////////////////////////////////// �͂����ҋ@�J�n
		case EV_ACTION_LADDER_WAIT:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_8)
			setCharaState( CHARASTATE_LADDER_WAIT );
			break;

		///////////////////////////////////////// �͂����o��J�n
		case EV_ACTION_LADDER_UP:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_9)
			setCharaState( CHARASTATE_LADDER_UP );
			break;

		///////////////////////////////////////// �͂����~��J�n
		case EV_ACTION_LADDER_DOWN:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_10)
			setCharaState( CHARASTATE_LADDER_DOWN );
			break;

        ///////////////////////////////////////// �A�C�e���擾�J�n
        case EV_ACTION_ITEM_GET:
            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_11)
            setCharaState( CHARASTATE_ITEMGET );
            mItemGetWaitCount = ITEMGET_WAIT_COUNT;     // �^�C���A�E�g����
            break;

        ///////////////////////////////////////// �ʏ�U�� 1 �i��
		case EV_ACTION_ATTACK_1:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_12)
			setCharaState( CHARASTATE_ATTACK_1 );
			break;

		///////////////////////////////////////// �ʏ�U�� 2 �i��
		case EV_ACTION_ATTACK_2:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_13)
			setCharaState( CHARASTATE_ATTACK_2 );
			break;

		///////////////////////////////////////// �ʏ�U�� 3 �i��
		case EV_ACTION_ATTACK_3:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_14)
			setCharaState( CHARASTATE_ATTACK_3 );
			break;

		///////////////////////////////////////// �W�����v�U��
		case EV_ACTION_ATTACK_JUMP_ATTACK:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_15)
			setCharaState( CHARASTATE_ATTACK_JUMP_ATTACK );
			break;

		///////////////////////////////////////// ���Ⴊ�ݍU��
		case EV_ACTION_ATTACK_SQUAT_ATTACK:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_16)
			setCharaState( CHARASTATE_ATTACK_SQUAT_ATTACK );
			break;

		///////////////////////////////////////// �΋�U��
		case EV_ACTION_ATTACK_ANTIAIR_ATTACK:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_17)
			setCharaState( CHARASTATE_ATTACK_ANTIAIR_ATTACK );
			break;

		///////////////////////////////////////// �K�[�h
		case EV_ACTION_GUARD:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_18)
			setCharaState( CHARASTATE_GUARD );
			break;

		///////////////////////////////////////// ���Ⴊ�݃K�[�h
		case EV_ACTION_SQUAT_GUARD:
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_19)
			setCharaState( CHARASTATE_SQGUARD );
			break;

        ///////////////////////////////////////// �퓬�s�\�J�n
        case EV_ACTION_START_DEAD:
            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_20)
            setCharaState( CHARASTATE_DEAD );
            break;

        ///////////////////////////////////////// �_���[�W��^����
        case EV_APPLY_DAMAGE:
        {
            AttackEventArg* arg = reinterpret_cast< AttackEventArg* >( args_ );



			GameObject* obj = GameObjectManager::getInstance()->findObject( arg->AttackerHandle );
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_21)
			if ( obj )
			{

				__DtTestPoint(__DtFunc_HandleEvent, __DtStep_22)
				if (( obj->getObjType() == OBJ_CHARACTER )||( obj->getObjType() == OBJ_ENEMY ))
				{
					__DtTestPoint(__DtFunc_HandleEvent, __DtStep_23)
					if((!arg->Guardflag)&&( arg->Damage > 0 ))
					{
						__DtTestPoint(__DtFunc_HandleEvent, __DtStep_24)
						switch ( ((Character*)obj)->getWeaponData().WeaponType )
						{
						case WEAPON_NON:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_25)
							Audio.playSE("./Data/Sound/SE/b_dead.wav");
							break;
						case WEAPON_STICK:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_26)
							Audio.playSE("./Data/Sound/SE/b_dead.wav",100,70);
							break;
						case WEAPON_KATANA:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_27)
							Audio.playSE("./Data/Sound/SE/KATANA_hit.wav",80,90);
							break;
						case WEAPON_UMBRELLA:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_28)
							Audio.playSE("./Data/Sound/SE/b_dead.wav",80,75);
							Audio.playSE("./Data/Sound/SE/sen_ge_bun04.wav",80,150);
							break;
						case WEAPON_TAEKWONDO:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_29)
							Audio.playSE("./Data/Sound/SE/b_dead.wav",85,70);
							Audio.playSE("./Data/Sound/SE/b_dead.wav",90,50);
							Audio.playSE("./Data/Sound/SE/sen_ge_bun04.wav",80,110);
							Audio.playSE("./Data/Sound/SE/sen_ge_bun04.wav",80,120);
							break;
						case WEAPON_KNIFE:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_30)
							Audio.playSE("./Data/Sound/SE/KATANA_hit.wav",85,90);
							Audio.playSE("./Data/Sound/SE/KATANA_hit.wav",85,120);
							break;
						case WEAPON_HAMMER:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_31)
							Audio.playSE("./Data/Sound/SE/b_dead.wav",85,70);
							Audio.playSE("./Data/Sound/SE/b_dead.wav",90,50);
							Audio.playSE("./Data/Sound/SE/sen_ge_bun04.wav",80,90);
							Audio.playSE("./Data/Sound/SE/sen_ge_bun04.wav",80,100);
							break;
						case WEAPON_SCYTHE:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_32)
							Audio.playSE("./Data/Sound/SE/chop_knife2.wav",80,140);
						case WEAPON_BOSS_KATANA:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_33)
							Audio.playSE("./Data/Sound/SE/KATANA_hit.wav",80,90);
							break;
						case WEAPON_BOSS_TAEKWONDO:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_34)
							Audio.playSE("./Data/Sound/SE/b_dead.wav",85,70);
							Audio.playSE("./Data/Sound/SE/b_dead.wav",90,50);
							Audio.playSE("./Data/Sound/SE/sen_ge_bun04.wav",80,110);
							Audio.playSE("./Data/Sound/SE/sen_ge_bun04.wav",80,120);
							break;
						case WEAPON_BOSS_KNIFE:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_35)
							Audio.playSE("./Data/Sound/SE/KATANA_hit.wav",75,90);
							Audio.playSE("./Data/Sound/SE/KATANA_hit.wav",75,120);
							break;
						case WEAPON_BOSS_SCYTHE:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_36)
							Audio.playSE("./Data/Sound/SE/chop_knife2.wav",80,90);
						case WEAPON_VALFIRLE:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_37)
							Audio.playSE("./Data/Sound/SE/KATANA_hit.wav",85,100);
							break;
						case WEAPON_VALFIRLE_TOKEN:
							__DtTestPoint(__DtFunc_HandleEvent, __DtStep_38)
							Audio.playSE("./Data/Sound/SE/KATANA_hit.wav",85,100);
							break;

						}
					}

					if(arg->Guardflag)
					{
						__DtTestPoint(__DtFunc_HandleEvent, __DtStep_39)
						Audio.playSE("./Data/Sound/SE/sen_ge_bun04.wav",70,80);
					}
				}
			}

            // �_���[�W�|�b�v�̕\��
            if ( arg->Damage > 0 )
            {
                int type = ( arg->Criticalflag ) ? 3 : 1;
                LVector3 pos( this->mPosition.x + 10,  this->mPosition.y + 70, -5 );
                __DtTestPoint(__DtFunc_HandleEvent, __DtStep_40)
                GameFrontendManager::getInstance()->getDamagePopManager()->popNumber( pos, arg->Damage, type );
            }
			if(mLife>0)
			{
				__DtTestPoint(__DtFunc_HandleEvent, __DtStep_41)
				mLife -= arg->Damage;
				// �퓬�s�\
				if ( mLife < 0 )
				{
					__DtTestPoint(__DtFunc_HandleEvent, __DtStep_42)
					mLife = 0;
					// ���S���[�V�����J�n
					getManager()->postEvent( getHandle(), EV_ACTION_START_DEAD, NULL, 0 );
				}
			}


            // HP �o�[��\������
            mCharacterNamePlate->startShow();

			

            //if ( mLife <= 0 )
            //{
            //    mLife = 0;

            //    // ���S���[�V�����J�n
            //    getManager()->postEvent( getHandle(), EV_ACTION_START_DEAD, NULL, 0 );
            //}
            // �܂������Ă�
            //else
            //{
                setVelocity( arg->BrowVector );
           // }
            break;
        }

        ///////////////////////////////////////// �T�[�o���畐�킪�����Ă���
        case EV_GET_WEAPON:
            //_p(EV_GET_WEAPON);

            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_43)
            WeaponData* data = reinterpret_cast< WeaponData* >( args_ );

            printf( "������擾 ���:%d  �g�p��:%d \n", data->WeaponType, data->UseCount );

            changeWeapon( *data );

            // �ʏ��Ԃɂ���
            setCharaState( CHARASTATE_DEFAULT );
            break;

    }
	__DtTestPoint(__DtFunc_HandleEvent, __DtStep_44)
	return 0;
}

//---------------------------------------------------------------------
// �� �L�����N�^�[�̏�Ԃ�ύX����
//---------------------------------------------------------------------
void Character::setCharaState( CharaState state_ )
{
	// ��Ԃɍ��킹������̃��[�V�����ɂ���ꍇ
	__DtTestPoint(__DtFunc_setCharaState, __DtStep_0)
	if ( state_ == CHARASTATE_DEFAULT )
	{
		__DtTestPoint(__DtFunc_setCharaState, __DtStep_1)
		if ( this->isDead() )
		{
			__DtTestPoint(__DtFunc_setCharaState, __DtStep_2)
			this->m_eCharaState = CHARASTATE_DEAD;
		}
		else
		{
			__DtTestPoint(__DtFunc_setCharaState, __DtStep_3)
			this->m_eCharaState = CHARASTATE_WAIT;
		}
	}
	else
	{
		__DtTestPoint(__DtFunc_setCharaState, __DtStep_4)
		this->m_eCharaState = state_;
	}

	mFrameCount = 0;

    // �Ƃ肠�����A���S���[�V�������͕ύX���󂯕t���Ȃ� (�h������Ƃ��Ȃ�����ύX����K�v�����邯��)
 //   if ( m_eCharaState == CHARASTATE_DEAD )
 //   {
 //       mFrameCount = 0;
 //   }
	//else
	//{
	//	
	//}
	

    // �A�C�e���擾��ԈȊO�ɂȂ�ꍇ�A�s��h�~�̂��߂Ɏ擾�҂����J�E���g�����Z�b�g����
    if ( this->m_eCharaState != CHARASTATE_ITEMGET )
    {
        __DtTestPoint(__DtFunc_setCharaState, __DtStep_5)
        mItemGetWaitCount = 0;
    }
	__DtTestPoint(__DtFunc_setCharaState, __DtStep_6)
}

//---------------------------------------------------------------------
// �� �����ύX����
//---------------------------------------------------------------------
void Character::changeWeapon( const WeaponData& weapon_data_ )
{
    // �������f��ȊO�̏ꍇ
    __DtTestPoint(__DtFunc_changeWeapon, __DtStep_0)
    if ( mWeaponData.WeaponType != WEAPON_NON )
    {
        // ���ݎ����Ă��镐���V�����I�u�W�F�N�g�Ƃ��ă}�b�v��ɐ������� (�T�[�o�փI�u�W�F�N�g�쐬�𑗐M)
		__DtTestPoint(__DtFunc_changeWeapon, __DtStep_1)
		if(this->mWeaponData.UseCount)
		{
			Weapon::CreateData data;
			__DtTestPoint(__DtFunc_changeWeapon, __DtStep_2)
			data.Data       = mWeaponData;
			data.Position   = this->getPosition();
			data.Position.x += ::rand() % 20 - 10;
			data.Position.y += 100;
			Weapon* weapon = Weapon::create( &data );
		}
    }

    // �󂯎��������𑕔�����Ƃ��Đݒ肷��
    mWeaponData = weapon_data_;


    // �����蔻��f�[�^
    const char* filename = CharaResourceNames[ mWeaponData.WeaponType ].Collision;
    if ( !filename )
    {
        __DtTestPoint(__DtFunc_changeWeapon, __DtStep_3)
        printf( "�����蔻��f�[�^�t�@�C������ NULL�B����ɑf��̃��m���g�p\n" );
        filename = CharaResourceNames[ WEAPON_NON ].Collision;
    }
    mCollision->LoadFile( filename );

    // �L�����N�^�[�摜
    filename = CharaResourceNames[mWeaponData.WeaponType].Character;
    if ( !filename )
    {
        __DtTestPoint(__DtFunc_changeWeapon, __DtStep_4)
        printf( "����e�N�X�`������ NULL�B����ɑf��̃��m���g�p\n" );
        filename = CharaResourceNames[ WEAPON_NON ].Character;
    }
    mCharaPanel.setTexture(LTexture::create(filename));//,0xffffffff));

    // ������ύX�������Ƃ��T�[�o�ɓ`���� (�T�[�o���瑼�̃z�X�g�ɒʒm���Ă��炤)


    // �v���C���[�̏ꍇ�̓t�����g�G���h�ɓ`������΃x�X�g����
	__DtTestPoint(__DtFunc_changeWeapon, __DtStep_5)
}

//
// Character::AttackLock
// �U�����̍s������
//
// �ĂԂƃ��b�N��������܂��B
// �U�����[�V�������W�����v�ȂǂŃL�����Z�������Ȃ�����
//
void Character::AttackLock()
{
	__DtTestPoint(__DtFunc_AttackLock, __DtStep_0)
	mAttackLocked = true;
	__DtTestPoint(__DtFunc_AttackLock, __DtStep_1)
}

//
// Character::AttackUnLock
// �U�����̍s����������
//
// �ĂԂƃ��b�N���͂���܂��B
// �U�����[�V�����I�����ɂ͕K���Ă�ł�������
//
void Character::AttackUnLock()
{
	__DtTestPoint(__DtFunc_AttackUnLock, __DtStep_0)
	mAttackLocked = false;
	__DtTestPoint(__DtFunc_AttackUnLock, __DtStep_1)
}

//
// Character::JumpStart
// �W�����v�J�n���ɌĂ�
//
void Character::JumpStart()
{
	__DtTestPoint(__DtFunc_JumpStart, __DtStep_0)
	if ( !mJump )
	{
		__DtTestPoint(__DtFunc_JumpStart, __DtStep_1)
		mJump = true;
		mOnGround = false;
        mStandOnObject = false;

		mVelocity.y += scg_fJumpHeight;
	}
	__DtTestPoint(__DtFunc_JumpStart, __DtStep_2)
}


//
// Character::CollisionToObj
// �I�u�W�F�N�g�Ƃ̓����蔻��
//
// �������Ă���ꍇ��
// �e�폈��������
//
void Character::CollisionToObj()
{
	//
	// �摜���m�̂߂荞�ݗ�
	// �ؔ��ɏ��Ƃ��ɕK�v
	//
	LVector2 overValue;
	__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_0)
	overValue.set( 0, 0 );

	// [11/11/15 �R�{] getBoundingRect() �œ�����`���Ƃ��̂ŏC��
    const LRect* nowRect = getBoundingRect();

	if ( nowRect )
    {
        LRect adv_rect = *nowRect;
        __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_1)
        adv_rect.x += mVelocity.x;
        adv_rect.y += ceil( mVelocity.y );

        //_p(ceil( mVelocity.y ));


		mOldTouchObj = mNewTouchObj;
		mNewTouchObj = static_cast< ObjectType >( GameObjectManager::getInstance()->CollisionToObject( this->getObjType(), *nowRect, &mDistance, &overValue ) );

		// �e��I�u�W�F�N�g�ɂ��������Ƃ��̓���
		// �e��`�ɂ��Ă�GameObjectManager.h ��
		//                 _ENUM_OBJECT_TYPE �Q�Ƃ̂���

        // ��x���ɂ��̂��Ă��Ȃ���Ԃɂ���
        mStandOnObject = false;

        

	// �� �͂���---------------------------------
        
		// �͂����A�͂�����[�ɐG��Ă���Ƃ�
		if ( this->mNewTouchObj == OBJ_LADDERTOP
			|| this->mNewTouchObj == OBJ_LADDER )
		{
			__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_2)
			this->mTouchLadder = true;

			// �͂�����[�ɐG��Ă���Ƃ�
			if ( this->mNewTouchObj == OBJ_LADDERTOP )
			{

                __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_3)
                if ( !mClimbLadder && !mJump )
                {
                    __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_4)
                    mPosition += LVector3( overValue, 0 );
                    mStandOnObject = true;
                }

                /*
				if ( -10 <= overValue.y && overValue.y <= 5 && !this->mClimbLadder
					&& ( this->mOnGround || this->m_eCharaState == CHARASTATE_WAIT ) )
				{
					this->mPosition.y -= overValue.y;
					this->mStandOnObject = true;
				}
				else
				{
					this->mStandOnObject = false;
				}
                */
			}
		}
		else
		{
			__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_5)
			if ( this->mOldTouchObj == OBJ_LADDERTOP && this->mClimbLadder )
			{
				__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_6)
				this->mVelocity.y = 0;
			}

			this->mTouchLadder = false;
		    this->mClimbLadder = false;
		}	
        
	// �� �͂���---------------------------------

#if 0
	// �� �ؔ�-----------------------------------

		if ( mNewTouchObj == OBJ_BOX )
		{
            __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_7)
            mPosition += overValue;

            // ��ɂ��炷�K�v������ꍇ�A��ɏ���Ă���Ƃ���
            if ( overValue.x == 0 && overValue.y >= 0 )
            {
                __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_8)
                mStandOnObject = true;
            }

 
            
            /*
			if ( -15 < overValue.y //&& overValue.y < 15
				&& ( !mJump || this->mVelocity.y <= 0 ) )
			{
				this->mPosition.y -= overValue.y;
				this->mStandOnObject = true;
			}
			else
			{
				this->mPosition.x -= overValue.x;
				this->mStandOnObject = false;
			}
            */
		}
#endif
        
	// �� �ؔ�-----------------------------------
		
	// �� ��ɏ���I�u�W�F�N�g-----------------
		if ( mNewTouchObj != OBJ_BOX && mNewTouchObj != OBJ_LADDERTOP )
		{
            //printf("��ɏ���I�u�W�F�N�g ������\n");
			//this->mStandOnObject = false;
			__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_9)
		}
	// �� ��ɏ���I�u�W�F�N�g-----------------
	

	// �� �񕜃A�C�e��---------------------------
		if ( this->mLife > 0 && this->getObjType() == OBJ_CHARACTER )
		{
			__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_10)
			int dead_cure = ::rand() % 7;
			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_CURE_S ) )
			{
				__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_11)
				printf("�񕜃A�C�e���擾�@��\n");
				Audio.playSE("./Data/Sound/SE/Powerup23.wav",100,150);

				static const int CURE_S_VALUE_ = static_cast< int >( this->mMaxLife * 0.30f );

				// �ő�l�𒴂���񕜗ʂ̏ꍇ�͍ő�l�ŌŒ�
				if ( this->mLife + CURE_S_VALUE_ > this->mMaxLife )
				{
					__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_12)
					if (dead_cure == 3) {
						__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_13)
						this->mLife = 0;
						getManager()->postEvent( getHandle(), EV_ACTION_START_DEAD, NULL, 0 );
					} else {
						__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_14)
						this->mLife = this->mMaxLife;
					}
				}
				else
				{
					__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_15)
					this->mLife += CURE_S_VALUE_;
				}
			}

			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_CURE_M ) )
			{
				__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_16)
				printf("�񕜃A�C�e���擾�@��\n");
				Audio.playSE("./Data/Sound/SE/Powerup23.wav",100,150);

				static const int CURE_M_VALUE_ = static_cast< int >( this->mMaxLife * 0.60f );

				// �ő�l�𒴂���񕜗ʂ̏ꍇ�͍ő�l�ŌŒ�
				if ( this->mLife + CURE_M_VALUE_ > this->mMaxLife )
				{
					__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_17)
					if (dead_cure == 3) {
						__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_18)
						this->mLife = 0;
						getManager()->postEvent( getHandle(), EV_ACTION_START_DEAD, NULL, 0 );
					} else {
						__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_19)
						this->mLife = this->mMaxLife;
					}
				}
				else
				{
					__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_20)
					this->mLife += CURE_M_VALUE_;
				}
			}

			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_CURE_L ) )
			{
				__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_21)
				printf("�񕜃A�C�e���擾�@��\n");
				Audio.playSE("./Data/Sound/SE/Powerup23.wav",100,150);

				static const int CURE_L_VALUE_ = static_cast< int >( this->mMaxLife * 0.80f );

				// �ő�l�𒴂���񕜗ʂ̏ꍇ�͍ő�l�ŌŒ�
				if ( this->mLife + CURE_L_VALUE_ > this->mMaxLife )
				{
					__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_22)
					if (dead_cure == 3) {
						__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_23)
						this->mLife = 0;
						getManager()->postEvent( getHandle(), EV_ACTION_START_DEAD, NULL, 0 );
					} else {
						__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_24)
						this->mLife = this->mMaxLife;
					}
				}
				else
				{
					__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_25)
					this->mLife += CURE_L_VALUE_;
				}
			}
	// �� �񕜃A�C�e��---------------------------

	// �� ��-------------------------------------
			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_KEY ) )
			{
				__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_26)
				printf("�A�C�e���擾  ��\n");
				GameManager::getInstance()->setKeyflag(1);
			}
		}
	// �� ��-------------------------------------
    }



    //---------------------------------------------------------
    // �� �ؔ��Ƃ̔���



    // �����̃��[���h��̍��A��A�E�A���B
    // �� > �� �ȓ_�ɒ��ӁB���̕��� 0 �ɋ߂��B
    int pl = nowRect->x;
    int pt = nowRect->y;
    int pr = nowRect->x + nowRect->w;
    int pb = nowRect->y - nowRect->h;
    int pwh = nowRect->w / 2;
    int phh = nowRect->h / 2;
    LVector2 pc( pl + ( pr - pl ) / 2, pb + ( pt - pb ) / 2 );

    GameObjectList& obj_list = GameObjectManager::getInstance()->getGameObjectList();
    GameObjectList::iterator itr = obj_list.begin();
    GameObjectList::iterator end = obj_list.end();
    for ( ;itr != end; ++itr )
    {
        u32          target_type = (*itr)->getObjType();
        const LRect* target_rc   = (*itr)->getBoundingRect();
        __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_27)
        if ( target_type == OBJ_BOX && target_rc )
        {
            int dx = 0;
            int dy = 0;

            // �^�[�Q�b�g�̃��[���h��̍��A��A�E�A���B
            int tl = target_rc->x;
            int tt = target_rc->y;
            int tr = target_rc->x + target_rc->w;
            int tb = target_rc->y - target_rc->h;
            LVector2 tc( tl + ( tr - tl ) / 2, tb + ( tt - tb ) / 2 );
          

            // �c�����̔���
            __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_28)
            if ( pl + pwh < tr && pr - pwh > tl && pt >= tb && pb <= tt )
            {
                // ������
                __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_29)
                if ( pc.y > tc.y )  // mVelocity.y < 0 && 
                {
                    __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_30)
                    dy = tt - pb + 1;     // ���̒l�̓v���X�ɂȂ�
                }
                // �㏸���A�������Ώۂ̉��ɂ���ꍇ
                else if ( pc.y < tc.y ) // mVelocity.y > 0 && 
                {
                    __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_31)
                    dy = tb - pt - 1;     // ���̒l�̓}�C�i�X�ɂȂ�
                }
                // Y ���W�̏C��
                if ( dy != 0 )
                {
                    __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_32)
                    pt += dy;
                    pb = pt - nowRect->h;
                    mPosition.y += dy;
                    mVelocity.y = 0;
                }
            }
            
            // ���̔���
            if ( pl <= tr && pr >= tl && pt >= tb && pb <= tt )
            {
                // �������Ώۂ̍��ɂ���ꍇ
                __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_33)
                if ( pl < tl )
                {
                    __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_34)
                    dx = tl - pr - 1;     // ���̒l�̓}�C�i�X�ɂȂ�
                }
                // �������Ώۂ̉E�ɂ���ꍇ
                else
                {
                    __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_35)
                    dx = tr - pl + 1;     // ���̒l�̓v���X�ɂȂ�
                }

                // X ���W�̏C��
                pl += dx;
                pr = pl + nowRect->w;
                mPosition.x += dx;
            }
            
            // �C����A�����̂������ɔ�������Ώ���Ă���
            if ( pl <= tr && pr >= tl && pt >= tb && pb - 1 <= tt )
            {
                __DtTestPoint(__DtFunc_CollisionToObj, __DtStep_36)
                mStandOnObject = true;
                //mOnGround = true;
            }
        }
    }
	__DtTestPoint(__DtFunc_CollisionToObj, __DtStep_37)
}

//=============================================================================
//								End of File
//=============================================================================
