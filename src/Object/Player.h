//=============================================================================
/*! 
    @addtogroup 
    @file       Player.h
    @brief      �v���C���[����
    
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
#ifndef __INCLUDE_PLAYER_H__
#define __INCLUDE_PLAYER_H__


/*! @par include */
#include "./Character.h"
#include "./Weapon.h"


//#include "../Frontend/GameFrontendManager.h"
//#include "../Frontend/PlayerStateWindow.h"

/*! @par global */
//���̃��x���܂łɕK�v�Ȍo���l
static const int scg_nNextLevelExp[]        = {100,200,350,400 ,600 ,700 ,840 ,1200,1610};
static const int scg_nNextLevelExpTotal[]   = {100,300,650,1050,1650,2350,3190,4390,6000};
///////////////////////////////////////{100,300,650,1050,1650,2350,3190,4390,6000}�݌v

const int MAX_PLAYER_LEVELS = 10;   ///< �ő僌�x���B�ꉞ10 �ŌŒ肾���ǁA�O�̂��߁B

/*! @class Player */
class Player : public Character
{
private:

	u32 mExp;
	u8 mLevel;
    u32 mGuardFrame;//�K�[�h�o�߃t���[��
public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_CHARACTER; }

    /// �������̕���n���x���擾����
    int getWeaponExp() { return mWeaponExps[ this->getWeaponData().WeaponType ]; }

    /// ����������̕��탌�x���̎擾
    virtual u32 getWeaponLevel() const;

	//�v���C���[�̌��݃��x���̎擾
	u8 getLevel(){return mLevel;}
	//�v���C���[�̌��݌o���l�̎擾
	u32 getExp() {return mExp;}

	u32 getGuardFrame() {return mGuardFrame;}

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	void setExit(bool bExit_) {return;}
   
	void setLevel(u8 Level_) { mLevel = Level_;}

	void setExp(u32 Exp_) { mExp = Exp_;}


	//---------------------------------------------------------------------------
	/*! 
		@brief Player::Player

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Player();

	//---------------------------------------------------------------------------
	/*! 
		@brief Player::~Player

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~Player();

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
	bool Initialize();

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
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief Player::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Update();

   
	/// �t���[���X�V���� (�I�u�W�F�N�g�ɉe����^���鏈��)
    virtual bool UpdateSelf();

	void setOnGround( bool flag ){ mOnGround = flag; }
    
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
	virtual int HandleEvent(EventType event_,void *args_);



    /// �R���e�B�j���[�ɔ����ď�Ԃ�ۑ�����
    void commit();

    /// commit() ���Ă񂾎��̏�Ԃɕ�������
    void reset();

protected:

    int     mWeaponExps[ WEAPON_MAX_NUM ];      ///< ����n���x�̔z��

    struct
    {
        int         Life;
        u32         Exp;
	    u8          Level;
        WeaponData  WeaponData;

    } mBackup;
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================