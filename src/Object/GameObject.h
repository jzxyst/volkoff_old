//=============================================================================
/*! 
    @addtogroup 
    @file       GameObject.h
    @brief      �I�u�W�F�N�g�x�[�X
    
    �I�u�W�F�N�g�x�[�X�̒�`
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/12
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/12 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_GAME_OBJECT_H__
#define __INCLUDE_GAME_OBJECT_H__


/*! @par include */
#include "./../Event/EventType.h"
#include "./GameObjectManager.h"
//
class GameObjectManager;

// [�R�{] enum ObjectType �� GameObjectManager.h �Ɉړ����܂��� (Include �̓s����)

/// ������\���萔
typedef enum _ENUM_CHARACTER_DIRECTION
{
	CHARADIR_UNDEF = 0, //����`
	CHARADIR_RIGHT,     //�E
	CHARADIR_LEFT,      //��
}CharaDir;

    
static const float GRAVITY_ACCEL = 0.0512f;      ///< �d�͉����x
static const float FRICTION_COEFF = 0.5;//0.112f;     ///< ���C�W��

class GameObjectManager;


/*! @class GameObject */
class GameObject// : public EventListener
{
protected:
    u32     mHandle;        ///< GameObjectManager �ɂ���Ċ��蓖�Ă����ӂ̃n���h��

	//ObjectType  mObjType;       //�I�u�W�F�N�g�^�C�v
	LVector3    mPosition;      //���[���h���W
	LVector3    mDefPosition;   //�������[���h���W
	LVector3    mScrPosition;   //�X�N���[�����W (�g���ĂȂ��H)
	LVector3    mScale;         //�g�嗦
    LVector3    mAccel;		    ///< �����x (�����Ƃ��d�͂Ƃ�)
	LVector3	mVelocity;	    ///< ���x

    CharaDir    m_eDirection;       ///< ���݂̃L�����N�^�[�̌��� (setDirection �ŕύX���邱��)

	float mAngle;          //Radian

	int         mLife;      //�̗�
    int         mMaxLife;   ///< �ő�̗�
	int         mScore;     //�X�R�A
	

	LRect mColRect;	       // �����蔻���`

    bool		mOnGround;      ///< �n��ɂ��邩�ǂ���
    bool        mIsEntity;      ///< ���Ԃ�̃z�X�g���ō쐬���ꂽ�I�u�W�F�N�g�̏ꍇ�Atrue (�p����I�u�W�F�N�g�� create() ���Őݒ肷��)

private:
    bool mExit;            //�폜�t���O

public:
    

	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
    const unsigned int getHandle() const {return mHandle;}

	//virtual const ObjectType& getObjType() const {return mObjType;}
	virtual ObjectType getObjType() const = 0;

	virtual const int getScore() const {return mScore;}

	const LVector3& getPosition() const {return mPosition;}

	const LVector3& getDefPosition() const {return mDefPosition;}

	const LVector3& getScrPosition() const {return mScrPosition;}

	const LVector3& getScale() const {return mScale;}

	const float& getAngle() const {return mAngle;}

    const CharaDir& getDirection() const {return m_eDirection;}

	const int& getLife() const {return mLife;}

    /// �ő� HP
    const int& getMaxLife() const {return mMaxLife;}     
	
	virtual const char* getName() const {return NULL;}

	const bool getExit() const {return mExit;}

    /// ���S����
    bool isDead() const { return mLife <= 0; }

    /// �����̃z�X�g������쐬�����I�u�W�F�N�g���𔻒肷��
    bool isEntity() const { return mIsEntity; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      ���[���h���W��ԏ�ł̓����蔻���`��Ԃ�
    //
    //  @author     �דc�Eyama
    //  @par
    //              ������s��Ȃ��ꍇ�� NULL ��Ԃ��B
    //              ��`�̍����A���͂���܂Œʂ�B
    //              ���̊֐��̓I�[�o�[���C�h���Ď�������B
    //*/
    //---------------------------------------------------------------------
	virtual const LRect* getBoundingRect(){ return NULL; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      ���[�J�����W��ԏ�ł̓����蔻���`��Ԃ�
    //
    //  @author     yama
    //  @par
    //              getBoundingRect() �́A���ݍ��W���l�����Ȃ�����
    //*/
    //---------------------------------------------------------------------
	virtual const LRect* getLocalBoundingRect(){ return NULL; }



	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
    void setHandle(unsigned int unHandle_) {mHandle = unHandle_;}   // ���ʂ͂���������_��

	virtual void setScore(int Score_) {mScore = Score_;}

    void setPosition(const LVector3 &pos_) {mPosition = pos_;}

	void setDefPosition(const LVector3 &pos_) {mDefPosition = pos_;}

	void setScrPosition(const LVector3 &pos_) {mScrPosition = pos_;}

	void setAccel(const     LVector3 &pos_) {mAccel = pos_;}

    ///// ���x�̐ݒ� (�U���ɂ��ӂ���΂����Ŏg��)
    void setVelocity(  LVector3& vel_ );//{ mVelocity = vel_; }

    /// �L�����N�^�[�̌�����ݒ肷�� (Character �N���X�ł̓I�[�o�[���C�h���āAPanel �̌�����ς��Ă�)
    virtual void setDirection( CharaDir dir_ ) { m_eDirection = dir_; }

    /// true ��n���ƁA����� update() �I����ɍ폜����
    virtual void setExit( bool f_ ) { mExit = f_; }

	virtual void setLife( int life_ ) { mLife = life_; }

	//---------------------------------------------------------------------------
	/*! @brief Hoge */
	//---------------------------------------------------------------------------
	GameObject();

	virtual ~GameObject();

	//virtual bool Initialize() = 0;    // �����t���� Initialize() �����Ȃ��Ȃ�I

	virtual int HandleEvent(u32 event_,void *args_) { return 0; }

	


    /// �������O�����̂��ʓ|�Ȃ̂ł�����Ɏ���
    GameObjectManager* getManager();

    //---------------------------------------------------------------------
    ///**
    //  @brief      �t���[���X�V
    //
    //  @author     yama
    //  @par
    //              ���� Update() �͎��R��������I�u�W�F�N�g�̍X�V������
    //              ������Ă���B
    //              Player �͂�����ƕ��G�Ȃ̂ł��̊֐��͌Ă΂��A�Ǝ���
    //              ��`���Ă���B
    //*/
    //---------------------------------------------------------------------
    virtual bool Update();

    //---------------------------------------------------------------------
    ///**
    //  @brief      �t���[���X�V (�I�u�W�F�N�g�ɉe����^���鏈��)
    //
    //  @author     yama
    //  @par
    //              �����蔻���_���[�W��^���鏈�����A
    //              �t���[���X�V���ɂ���ׂ������̂����A
    //              �u�I�u�W�F�N�g�ɉe����^���鏈���v�����̊֐��Œ�`����B
    //              
    //              ����́A�l�b�g���[�N�������Ɏ����̃z�X�g�ō쐬����
    //              �I�u�W�F�N�g (���g�����삷��v���C���[��A���˂����e)
    //              ���s�������蔻��͎����̂Ƃ���ōs���K�v�����邽�߁A
    //              ���̏����𕪗����邽�߂ɕK�v�ɂȂ�B
    //
    //              ���̊֐��́AUpdate() �̌�ɁA�����̃z�X�g�ō쐬���� 
    //              GameObject �݂̂ɑ΂��āAGameObjectManager ����Ăяo�����B
    //
    //
    //              �v����Ɂc
    //
    //                  �E����
    //                  �E�A�j���[�V�������̍U���̓����蔻��
    //
    //              ���͂����ɏ����Ă��������B
    //*/
    //---------------------------------------------------------------------
    virtual bool UpdateSelf() { return true; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      �n�`�Ƃ̓����蔻����s��
    //
    //  @param[out] dx_  : �C�� X �I�t�Z�b�g (�Ăяo������ mPosition �ɉ��Z���邱��)
    //  @param[out] dy_  : �C�� Y �I�t�Z�b�g (�Ăяo������ mPosition �ɉ��Z���邱��)
    //
    //  @return     enum MapCollFlag �̑g�ݍ��킹
    //
    //  @par
    //              �֐����Ă΂ꂽ���_�ł̑��x�ɂ���Ĉړ��������Ƃ�
    //              �ʒu���g���Ĕ�����s���B
    //              �X�e�[�W��ɗ����Ă��镐���A�C�e���p�ɗp�ӂ������́B
    //              Character �� Update() ���œƎ��ɒ�`���Ă���B
    //*/
    //---------------------------------------------------------------------
    virtual u32 judgeCollisionToMap( float* dx_, float* dy_ );

 
    friend class GameObjectManager;
};

/// �I�u�W�F�N�g��������U������O���[�v
enum AttackedGroup
{
    ATKGROUP_NONE       = 0,        ///< �ǂ��ɂ������Ȃ�
    ATKGROUP_PLAYER     = 0x01,     ///< �v���C���[���ɑ�����
    ATKGROUP_ENEMY      = 0x02,     ///< �G���ɑ�����
    ATKGROUP_ALL        = ATKGROUP_PLAYER | ATKGROUP_ENEMY ///< ���� (�G�̍U���ł�����I�u�W�F�N�g�Ƃ��A�G����������΂��n���Ƃ�)
};

//=============================================================================
// �� AttackedObject �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�U��������E�U�����󂯂�I�u�W�F�N�g�̊��      
//
//  @note
//              �Ȃ� include ���S�`���S�`���ɂȂ��ăR���p�C���ʂ�Ȃ��Ȃ��Ă��̂ŁA
//              �Ƃ肠�����ʂ����߂ɂ������Ɉړ��B
//*/
//=============================================================================
class AttackedObject
    : public GameObject
    , public LNote::Core::Base::NodeList< AttackedObject >::Node
{
public:
    
    /// �R���X�g���N�^
    AttackedObject();

    /// �f�X�g���N�^
    virtual ~AttackedObject();

public:

    //---------------------------------------------------------------------
    ///**
    //  @brief      �I�u�W�F�N�g��������O���[�v��ݒ肷��
    //
    //  @return     AttackedGroup �̃t���O�̑g�ݍ��킹
    //*/
    //---------------------------------------------------------------------
    void setAttackedGroup( u32 flags_ ) { mAttackedGroup = flags_; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      �I�u�W�F�N�g��������O���[�v��Ԃ�
    //
    //  @return     AttackedGroup �̃t���O�̑g�ݍ��킹
    //*/
    //---------------------------------------------------------------------
    u32 getAttackedGroup() { return mAttackedGroup; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      �I�u�W�F�N�g�́A�U�����󂯂�Ƃ��̓����蔻���`��Ԃ�
    //
    //  @par
    //              �I�[�o�[���C�h���Ȃ��ꍇ�AgetBoundingRect() �Ɠ�������B
    //              �K�v�ȏꍇ�A���̊֐��̓I�[�o�[���C�h���Ď������邱�ƁB
    //              NULL ��Ԃ��ꍇ�A�����蔻����s��Ȃ��B
    //*/
    //---------------------------------------------------------------------
    virtual const LRect* getAttackedCollisionRect() { return getBoundingRect(); }

    //---------------------------------------------------------------------
    ///**
    //  @brief      ���̃I�u�W�F�N�g�ɍU����^����
    //
    //  @param[in]  attacker_       : �U���� (��ŉ����g����������Ȃ��̂ňꉞ)
    //  @param[in]  damage_         : �^����_���[�W
    //  @param[in]  range_rate_     : damage_ �ɑ΂���΂���͈̔́B�}range_rate_�� �͈̔͂ŕω�����
    //  @param[in]  critical_rate_  : �N���e�B�J���� (0�`100)
    //  @param[in]  brow_vec_       : �ӂ���΂��x�N�g��
    //  @param[in]  stun_frame_     : �̂�����t���[����
    //
    //  @author     yama
    //  @note
    //              �l�b�g���[�N�Ńv���C���Ă���ꍇ�A���ʂɃ_���[�W��^�����
    //              ���Ԃł͂Ȃ��I�u�W�F�N�g�ɑ΂��ă_���[�W��^���邱�ƂɂȂ��Ă��܂��B
    //              ���̂��߁A���̊֐����ł͎��ۂɃ_���[�W��^���邱�Ƃ͂����A
    //                  �E�_���[�W��
    //                  �E�N���e�B�J���L��
    //              �����b�Z�[�W�Ƃ��Ă��ׂẴz�X�g�ɑ��M����B
    //
    //              (�K�[�h�u���C�N�̋������K�v�H)
    //*/
    //---------------------------------------------------------------------
    virtual void attackEffect( GameObject* attacker_, int damage_, u32 range_rate_, u32 critical_rate_,  LVector3& brow_vec_, u32 stun_frame_ );

    /// �C�x���g����
    virtual int HandleEvent( u32 event_,void *args_ );

private:

    u32     mAttackedGroup;     ///< AttackedGroup �̑g�ݍ��킹�B�ʏ�͂ǂꂩ���

};

//End of Include Guard
#endif



//=============================================================================
//								End of File
//=============================================================================
