//=============================================================================
/*! 
    @addtogroup 
    @file       Character.h
    @brief      �L�����N�^�[����
    
    �L�����N�^�[����̒�`
    
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


//Include Guard
#ifndef __INCLUDE_CHARACTER_H__
#define __INCLUDE_CHARACTER_H__


/*! @par include */
#include "./GameObject.h"
//#include "AttackedObject.h"
#include "./Weapon.h"
#include "../Utility/Collision.h"
#include "../Game/GameManager.h"




/*! @enum CharaState */
typedef enum _ENUM_CHARACTER_STATE
{
    CHARASTATE_DEFAULT = 0,      ///< setCharaState() �ɐݒ肷�邱�ƂŊ�{�̏�Ԃɖ߂� (����ȏꍇ�� CHARASTATE_WAIT�A���S���� CHARASTATE_DEAD �ɂ���ȂǁB)
	CHARASTATE_WAIT,           //�ҋ@
	CHARASTATE_RUN,            //����
	CHARASTATE_JUMP,           //�W�����v
	CHARASTATE_SQUAT,          //���Ⴊ��
	CHARASTATE_STUN,           //�̂�����
	CHARASTATE_BLOW,           //�������
	CHARASTATE_GUARD,          //�K�[�h
	CHARASTATE_SQGUARD,        //���Ⴊ�݃K�[�h
	CHARASTATE_LADDER_WAIT,    //�͂����ҋ@
	CHARASTATE_LADDER_UP,      //�͂������
	CHARASTATE_LADDER_DOWN,    //�͂����~��
	CHARASTATE_ITENGET,        //�A�C�e���E��
	CHARASTATE_DEAD,           //���S
    CHARASTATE_ITEMGET,         ///< �A�C�e���擾�̂��߁A������҂��Ă�����

    // �� ��������U���n
    CHARASTATE_ATTACK_BEGIN_,           ///< �萔�͈̔͂̎n�܂������

	CHARASTATE_ATTACK_1,                ///< �ʏ�U��1
	CHARASTATE_ATTACK_2,                ///< �ʏ�U��2
	CHARASTATE_ATTACK_3,                ///< �ʏ�U��3
	CHARASTATE_ATTACK_SQUAT_ATTACK,     ///< ���Ⴊ�ݍU��
	CHARASTATE_ATTACK_JUMP_ATTACK,      ///< �W�����v�U��
	CHARASTATE_ATTACK_ANTIAIR_ATTACK,   ///< �΋�U��
	CHARASTATE_ATTACK_DUSH_ATTACK,      ///< �_�b�V���U��

    CHARASTATE_ATTACK_END_              ///< �萔�͈̔͂̏I��������

}CharaState;






/// �L�����N�^�[�֌W�̃��\�[�X�����܂Ƃ߂��\����
struct CharaResource
{
    const char* Character;  ///< �L�����N�^�[�̉摜�t�@�C����
    const char* Collision;  ///< �����蔻��f�[�^�t�@�C����
    const char* Script;     ///< �X�N���v�g�t�@�C����
};

static const CharaResource CharaResourceNames[] = {
    // �f��
    { 
        "Data/Graphics/Character/Char_BareHands.png",
        "Data/Collision/Char_BareHands_col.dat",
        "Data/Scripts/Character_BareHands.lua"
		//"Data/Graphics/Character/Char_Scythe.png",
  //      "Data/Collision/Char_Scythe_col.dat",
  //      "Data/Scripts/BOSS_Scythe.lua"	

    },
    // �_
    { 
        "Data/Graphics/Character/Char_Stick.png",
        "Data/Collision/Char_Stick_col.dat",
        "Data/Scripts/Character_Stick.lua"
    },
	// ��
	{
		"Data/Graphics/Character/Char_KATANA.png",
		"Data/Collision/Char_KATANA_col.dat",
		"Data/Scripts/Character_KATANA.lua"
    },
	//�P
	{
		"Data/Graphics/Character/Char_Umbrella.png",

		"Data/Collision/Char_Umbrella_col.dat",
		"Data/Scripts/Character_Umbrella.lua"			
	},
	//�e�R���h�[
	{
		"Data/Graphics/Character/Char_Taekwondo.png",
		"Data/Collision/Char_Taekwondo_col.dat",
		"Data/Scripts/Character_Taekwondo.lua"			
	},
	//�i�C�t
	{
		"Data/Graphics/Character/Char_Knife.png",
		"Data/Collision/Char_Knife_col.dat",
		"Data/Scripts/Character_Knife.lua"			
	},
	//�O���l�[�h
	{
		"Data/Graphics/Character/Char_Grenade.png",
		"Data/Collision/Char_Knife_col.dat",
		"Data/Scripts/Character_Grenade.lua"			
	},
	//�n���}�[
	{
		"Data/Graphics/Character/Char_Hammer.png",
		"Data/Collision/Char_Hammer_col.dat",
		"Data/Scripts/Character_Hammer.lua"			
	},
	//�V���b�g�K��
	{
		"Data/Graphics/Character/Char_Shotgun.png",
		"Data/Collision/Char_Taekwondo_col.dat",
		"Data/Scripts/Character_Shotgun.lua"			
	},
	//��
	{
		"Data/Graphics/Character/Char_Scythe.png",
        "Data/Collision/Char_Scythe_col.dat",
        "Data/Scripts/Character_Scythe.lua"				
	},
	//enum�̊֌W��ANULL��u���Ă���
	//{
	//	'\0',
	//	'\0',
	//	'\0'
	//},
	//�{�X��
	{
		"Data/Graphics/Character/Char_KATANA.png",
		"Data/Collision/Char_KATANA_col.dat",
		"Data/Scripts/BOSS_KATANA.lua"	
	},
	//�{�X�e�R���h�[	
	{
		"Data/Graphics/Character/Char_Taekwondo.png",
		"Data/Collision/Char_Taekwondo_col.dat",
		"Data/Scripts/BOSS_Taekwondo.lua"	
	},
	//�{�X�i�C�t
	{
		"Data/Graphics/Character/Char_Knife.png",
		"Data/Collision/Char_Knife_col.dat",
		"Data/Scripts/BOSS_Knife.lua"			
	},
	//�{�X��
	{
		"Data/Graphics/Character/Char_Scythe.png",
        "Data/Collision/Char_Scythe_col.dat",
        "Data/Scripts/BOSS_Scythe.lua"			
	},
/////////////���@���t�@�[��
	{
		"Data/Graphics/Character/Char_Valfirle.png",
        "Data/Collision/Char_Valfirle_col.dat",
        "Data/Scripts/Valfirle.lua"	
	},
////////////////���@���t�@�[���g�[�N��
	{
		"Data/Graphics/Character/Char_Valfirle.png",
        "Data/Collision/Char_Valfirle_col.dat",
        "Data/Scripts/Valfirle_token.lua"	
	},
 //   // ��
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // �o�b�g
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // �n���}�[
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // �i�C�t
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },

 //   // �n���h�K��
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // �V���b�g�K��
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // �}�V���K��
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // �Ε����C�t��
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // ��֒e
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   }
	//},

};

static const float scg_fRunSpeed = 4.0f;//2.0f; //���鑬��

//static const float scg_fFallSpeed = 0.006f; // �������x ( =�d�͉����x )
//
//static const float scg_fJumpHeight = 3.0f; // �W�����v�̍���

//#define scg_fFallSpeed  0.112f    // [�R�{] GameObject �Ɉړ�
#define scg_fJumpHeight 7.2f

class CharacterScriptInterface;
class CharacterNamePlate;

/*! @class Character */
class Character : public AttackedObject
{
protected:
    
	const char *m_pszName;
	CharaState  m_eCharaState;      ///< ���݂̃L�����N�^�[�̏�� (setCharState �ŕύX���邱��)
	

	LBatchPanel mCharaPanel;

	//int m_nTime;

	//int mAnimetionCounter; // �A�j���[�V�����؂�ւ��̂��߂̃J�E���^
	int m_AnimePuttern;     // ���݂̃R�}��

	Collision* mCollision; // �����蔻��

	//int m_nAnime; //��ō폜����  

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	virtual const char* getName() const {return m_pszName;}

	const CharaState& getCharaState() const {return m_eCharaState;}

	const int& getAnimePuttern() const { return m_AnimePuttern; }

	/// �L�����N�^�[�̌�����ݒ肷��
    virtual void setDirection( CharaDir dir_ );


    /// �A�j���[�V�����t���[�����̎擾 (��ɃX�N���v�g����g��)
    int getFrameCount() const { return mFrameCount; }

    /// ����f�[�^�̎擾
    const WeaponData& getWeaponData() const { return mWeaponData; }


    /// ���[���h���W��ԏ�ł̓����蔻���`��Ԃ�
	virtual const LRect* getBoundingRect();

    /// ���[�J�����W��ԏ�ł̓����蔻���`��Ԃ� (���ォ��̈ʒu)
	virtual const LRect* getLocalBoundingRect();

    /// ���[���h���W��ԏ�ł̍U�������蔻���`��Ԃ�
	virtual const LRect* getAttackBoundingRect();

    /// �L�����N�^�[���U�����쒆���𔻒肷��
    bool isAttacking() const { return ( CHARASTATE_ATTACK_BEGIN_ < getCharaState() && getCharaState() < CHARASTATE_ATTACK_END_ ); }

	// �L�����N�^���n��ɂ��邩���肷��i�X�N���v�g�Ŏg�p�j
	const bool getOnGround() const { return mOnGround; _p("true"); }

    /// ����������̕��탌�x���̎擾 (Player Enemy �̊e�p����Œ�`����B�v���C���[�͏n���x�������A�G�l�~�[�͏����l�ŌŒ�B)
    virtual u32 getWeaponLevel() const = 0;

	// ���킪��ꂽ���ǂ����𔻒f����i�X�N���v�g�Ŏg�p
	bool getBreakWeapon(){ return mBreakWeapon; }

	u32 getInvincibleFrame() {return mInvincibleFrame;}
	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	//����̎g�p�񐔂̐ݒ�
	void setWeponUseCount(int UseCount_);
    /// �A�j���[�V�����p�^�[���̐ݒ� (��ɃX�N���v�g����g��)
    void setAnimePuttern( int puttern_ );

    /// �A�j���[�V�����t���[�����̐ݒ� (��ɃX�N���v�g����g��)
    void setFrameCount( int count_ ) { mFrameCount = count_; }

	// ���킪��ꂽ�ꍇ��true��ݒ肷��(�X�N���v�g�Ŏg�p
	void setBreakWeapon( bool break_ ){ mBreakWeapon = break_; }

	void setVisible( bool flg_ ) {this->mCharaPanel.setVisible(flg_); }
    
	void setInvincibleFrame(u32 invincible_frame_) {mInvincibleFrame = invincible_frame_;}

	void setOpacity(float opacity_) {this->mCharaPanel.setOpacity(opacity_);}
	//---------------------------------------------------------------------------
	/*! 
		@brief Character::Character

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Character();

	//---------------------------------------------------------------------------
	/*! 
		@brief Character::~Character

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~Character();

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
	bool Initialize();

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
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief Character::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Update();

   
	/// �t���[���X�V���� (�I�u�W�F�N�g�ɉe����^���鏈��)
    virtual bool UpdateSelf();


    
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
	virtual int HandleEvent(u32 event_,void *args_);

    //---------------------------------------------------------------------
    ///**
    //  @brief      �L�����N�^�[�̏�Ԃ�ύX����
    //
    //  @par
    //              �����o�ϐ��ɒ��ڒl��������̂ł͂Ȃ��A
    //              �K�����̊֐��ŕύX���邱�ƁB
    //*/
    //---------------------------------------------------------------------
    void setCharaState( CharaState state_ );

    
    //---------------------------------------------------------------------
    ///**
    //  @brief      �����ύX����
    //
    //  @par
    //              ���ݎ����Ă��镐��͂��̕ӂɒu���B
    //*/
    //---------------------------------------------------------------------
    void changeWeapon( const WeaponData& weapon_data_ );

	//
	// Character::JumpStart
	// �W�����v�J�n���ɌĂ�
	//
	void JumpStart();

	//
	// Character::CollisionToObj
	// �I�u�W�F�N�g�Ƃ̓����蔻��
	//
	// �������Ă���ꍇ��
	// �e�폈��������
	//
	void CollisionToObj();

	//
	// Character::AttackLock
	// �U�����̍s������
	//
	// �ĂԂƃ��b�N��������܂��B
	// �U�����[�V�������W�����v�ȂǂŃL�����Z�������Ȃ�����
	//
	void AttackLock();

	//
	// Character::AttackUnLock
	// �U�����̍s����������
	//
	// �ĂԂƃ��b�N���͂���܂��B
	// �U�����[�V�����I�����ɂ͕K���Ă�ł�������
	//
	void AttackUnLock();

protected:

    static const int ITEMGET_WAIT_COUNT = 60 * 20;  /// (20�b)

protected:

	LVector3    mOrigin;    // �摜�̊�_
    LRect       mWorldBoundingRect;

	bool		mJump;  // �W�����v���Ă��邩�ǂ���
	//			mOnGround(GameObject �Ɉړ�)

	ObjectType  mNewTouchObj; // ��q�𗣂������̏����Ɏg�p�A�����Ƌ�������������
	ObjectType  mOldTouchObj;
	bool		mTouchLadder; // ��q�ɐG���Ă��邩�ǂ���
	bool        mClimbLadder; // ��q��o���Ă��邩�ǂ���
	bool		mStandOnObject; // ���Ă�I�u�W�F�N�g�̏�ɂ��邩�ǂ���
	bool		mAttackLocked; // �U�����쒆���ǂ����������Btrue�Ȃ�s������
	LVector2    mDistance; // �L�����N�^�[�̒��S���W�ƁA���������I�u�W�F�N�g�̒��S���W�Ƃ̋���

    int         mFrameCount;    ///< �X�N���v�g�ł̃A�j���[�V��������Ɏg���A�o�߃t���[���� (update() ���ŏ�ɉ��Z��������)
	bool		mBreakWeapon; // �X�N���v�g�Ŏg�p�A����j�����Ɏg�p

    WeaponData  mWeaponData;    ///< �������̕���f�[�^ (�g�p�񐔂����̒�)

    u32         mStunFrame;         ///< �c��̂̂�����t���[���� (�l������ꍇ�A���t���[�� -1)
    u32         mItemGetWaitCount;  ///< 

	u32         mInvincibleFrame;   ///���G�t���[��
    CharacterNamePlate* mCharacterNamePlate;



};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
