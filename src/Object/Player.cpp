
//=============================================================================
/*! 
    @addtogroup 
    @file       Player.cpp
    @brief      
    
    �v���C���[�N���X�̎���
    
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
#include	"DT_Player.h"	/* For DynamicTracer-TestPoint */
#include "Player.h"
#include "../Frontend/CharacterNamePlate.h"
#include "../Frontend/GameFrontendManager.h"
#include "../Effect/Effect_1.h"

//---------------------------------------------------------------------------
/*! 
	@brief Player::Player

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Player::Player()
{
	__DtTestPoint( __DtFunc_Player, __DtStep_0 )
	this->m_pszName = '\0'; //�ꎞ�I�B��œK���Ȗ��O��������
	this->m_eCharaState = CHARASTATE_WAIT;

	this->m_AnimePuttern = 0;

    // �U���ΏۃO���[�v�̓v���C���[��
    setAttackedGroup( ATKGROUP_PLAYER );

    memset( mWeaponExps, 0, sizeof( mWeaponExps ) );
	__DtTestPoint( __DtFunc_Player, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Player::~Player

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Player::~Player()
{
	__DtTestPoint( __DtFunc_Player, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Player, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Player::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Player::Initialize()
{
    __DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
    this->Release();

    memset( mWeaponExps, 0, sizeof( mWeaponExps ) );

    bool r = Character::Initialize();

    // �v���C���[�͌ォ��`�悷��悤�ɂ���
    //this->mCharaPanel->setPriority( 100 );



    // �v���C���[�L�����N�^�[�̃l�[���v���[�g�͕\�����Ȃ�
    this->mCharacterNamePlate->setVisible( false );

	this->mLevel = 1;
	this->mExp = 0;


#if 0 // �e�X�g�p
	mLevel = 10;
	this->mMaxLife = 150;
	mLife = 150;
	WeaponData data;
	data.WeaponType = WEAPON_STICK;
	data.UseCount = 40;
	this->changeWeapon(data);

#endif

    __DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
    return r;
}


//---------------------------------------------------------------------------
/*! 
	@brief Player::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Player::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //delete��Manager�ɔC����

	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------
// �� ���݂̕��탌�x���̎擾
//---------------------------------------------------------------------
u32 Player::getWeaponLevel() const
{
    u32 level = 0;
    __DtTestPoint( __DtFunc_getWeaponLevel, __DtStep_0 )
    for ( int i = 0; i < 2; ++i )
    {
        __DtTestPoint( __DtFunc_getWeaponLevel, __DtStep_1 )
        if ( gWeaponBaseData[ mWeaponData.WeaponType ].NecessaryExp[ i ] <= mWeaponExps[ mWeaponData.WeaponType ] )
        {
            __DtTestPoint( __DtFunc_getWeaponLevel, __DtStep_2 )
            level = i + 1;
        }
    }
    __DtTestPoint( __DtFunc_getWeaponLevel, __DtStep_3 )
    return level + 1;
}


//---------------------------------------------------------------------------
/*! 
	@brief Player::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Player::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	Character::Update();

	// �A�C�e���Ƃ̓����蔻��
	//CollisionToItem();


    //if ( Input.isOnTrigger( LN_BUTTON_L ) )
    //if ( Input.isPress( LN_BUTTON_L ) )
    //{
    //    NEW Effect_Test_1( getPosition() );
    //    Audio.playSE("./Data/Sound/SE/sword1.wav");
    //}

	//
	if((getCharaState()==CHARASTATE_GUARD)||((getCharaState()==CHARASTATE_SQGUARD)))
	{
		__DtTestPoint( __DtFunc_Update, __DtStep_1 )
		++mGuardFrame;
	}
	else
	{
		__DtTestPoint( __DtFunc_Update, __DtStep_2 )
		mGuardFrame = 0;
	}

	//���x���A�b�v�̏���
	if(this->mLevel<10)
	{
		//���x���A�b�v�ɕK�v�Ȍo���l�����܂����烌�x�����グ��
		u32 temp=0;
		__DtTestPoint( __DtFunc_Update, __DtStep_3 )
		for(int i= 0;i<mLevel;i++)
		{
			__DtTestPoint( __DtFunc_Update, __DtStep_4 )
			temp+=scg_nNextLevelExp[i];

		}
		//���x�����オ������ő僉�C�t�𑝂₷
		if(mExp>=temp)
		{
			__DtTestPoint( __DtFunc_Update, __DtStep_5 )
			this->mInvincibleFrame = 150;
			mLevel+=1;
			this->mMaxLife+=5;
			this->mLife+=30;
			if(mLevel==10)
			{
				__DtTestPoint( __DtFunc_Update, __DtStep_6 )
				this->mMaxLife+=5;
				mLife=mMaxLife;
			}
			if(this->mLife>=mMaxLife)
			{
				__DtTestPoint( __DtFunc_Update, __DtStep_7 )
				mLife=mMaxLife;
			}
			if(this->mMaxLife>=150)
			{
				__DtTestPoint( __DtFunc_Update, __DtStep_8 )
				this->mMaxLife = 150;
			}
			printf("LevelUP�I\n");
			printf("level%d\n",mLevel);

            GameFrontendManager::getInstance()->showLevelUp();
		}
	}
    
	
	__DtTestPointValue( __DtFunc_Update, __DtStep_9, ( void * )&mLife, sizeof( mLife ) )
	__DtTestPoint( __DtFunc_Update, __DtStep_10 )
	return true;
}

//---------------------------------------------------------------------------
// �� �t���[���X�V���� (�I�u�W�F�N�g�ɉe����^���鏈��)
//---------------------------------------------------------------------------
bool Player::UpdateSelf()
{
	__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_0 )
	return Character::UpdateSelf();
}




//---------------------------------------------------------------------------
/*! 
	@brief Player::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Player::HandleEvent(EventType event_,void *args_)
{
    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
    return Character::HandleEvent( event_, args_ );
}


//---------------------------------------------------------------------------
// �� �R���e�B�j���[�ɔ����ď�Ԃ�ۑ�����
//---------------------------------------------------------------------------
void Player::commit()
{
    __DtTestPoint( __DtFunc_commit, __DtStep_0 )
    mBackup.Life = this->getLife();
    mBackup.Exp = mExp;
    mBackup.Level = mLevel;
    mBackup.WeaponData = this->getWeaponData();

    printf( "�� Player::commit  ����:%d ��:%d\n", mBackup.WeaponData.WeaponType, mBackup.WeaponData.UseCount );
	__DtTestPoint( __DtFunc_commit, __DtStep_1 )
}

//---------------------------------------------------------------------------
// �� commit() ���Ă񂾎��̏�Ԃɕ�������
//---------------------------------------------------------------------------
void Player::reset()
{
    __DtTestPoint( __DtFunc_reset, __DtStep_0 )
    this->Initialize();

    //this->setLife( mBackup.Life );
    mExp = mBackup.Exp;
    mLevel = mBackup.Level;
    this->changeWeapon( mBackup.WeaponData );

    this->setLife( this->getMaxLife() );

     printf( "�� Player::reset  ����:%d ��:%d\n", mBackup.WeaponData.WeaponType, mBackup.WeaponData.UseCount );
	__DtTestPoint( __DtFunc_reset, __DtStep_1 )
}


//=============================================================================
//								End of File
//=============================================================================
