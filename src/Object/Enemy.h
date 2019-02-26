//=============================================================================
/*! 
    @addtogroup 
    @file       Enemy.h
    @brief      �G�l�~�[
    
    �G�l�~�[����̒�`
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/11/07
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/07 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_ENEMY_H__
#define __INCLUDE_ENEMY_H__


/*! @par include */
#include "./Character.h"


/*! @par global */
//��Փx�����p�ϐ� //������Easy,Normal,Hard,Valfirle
static const bool scg_bAttack1Permission[] = {true,true,true,true};    //�U��1�i�ڂ��o���邩�ǂ���
static const bool scg_bAttack2Permission[] = {false,true,true,true};   //�U��2�i�ڂ��o���邩�ǂ���
static const bool scg_bAttack3Permission[] = {false,false,false,true}; //�U��3�i�ڂ��o���邩�ǂ���
static const int scg_nAttackRatio[] = {50,40,30,20};                   //�U�����J�n����䗦�B10�ł����1/10�ōU�����J�n����
static const int scg_nAttack2Ratio[] = {5,7,8,12};                     //�U��2�i�ڂ��s���䗦�B10�ł����9/10�ōU�����J�n����
static const int scg_nAttack3Ratio[] = {5,7,8,12};                     //�U��3�i�ڂ��s���䗦�B10�ł����9/10�ōU�����J�n����
static const int scg_nJumpAttackRatio[] = {6,6,6,6};                   //�W�����v�U�����s�������B10�ł����1/10�ŃW�����v�U�����J�n����
static const int scg_nSquatAttackRatio[] = {6,6,6,6};                  //���Ⴊ�ݍU�����s�������B10�ł����1/10�ł��Ⴊ�ݍU�����J�n����
static const int scg_nStandbyRatio[] = {20,20,20,20};                  //�ώ@���s�������B10�ł����1/10�Ŋώ@���J�n����
static const int scg_nGuardRatio[] = {100,90,85,80};                   //�h����s�������B10�ł����1/10�Ŗh����J�n����
static const int scg_nSquatGuardRatio[] = {100,90,85,80};              //���Ⴊ�ݖh����s�������B10�ł����1/10�Ŗh����J�n����
static const int scg_nSquatRatio[] = {120,120,120,120};                //���Ⴊ�݂��s������
static const int scg_nJumpRatio[] = {120,120,120,120};                 //�W�����v���s������
static const int scg_nEscapeRatio[] = {60,60,60,60};                   //�������s������
static const int scg_nLife[] = {50,70,90,100};                         //�̗�


	
/*! @enum WeaponType */
typedef enum _ENUM_ENEMY_ACTION
{
	ENEMY_ACT_UNDEF,        //����`
	ENEMY_ACT_WAIT,         //�ҋ@
	ENEMY_ACT_SEARCH,       //�T��
	ENEMY_ACT_WALK,         //�U��
	ENEMY_ACT_CHASE,        //�ǐ�
	ENEMY_ACT_STANDBY,      //�ώ@
	ENEMY_ACT_ESCAPE,       //����
	ENEMY_ACT_ATTACK_RANGE, //�U���͈͓�
	ENEMY_ACT_ATTACK,       //�U��
	ENEMY_ACT_GUARD,        //�h��
	ENEMY_ACT_SQUAT,        //���Ⴊ��
	ENEMY_ACT_SQUAT_GUARD,  //���Ⴊ�݃K�[�h
}EnemyAction;


/*! @class Enemy */
class Enemy : public Character
{
public:

    struct CreateData
    {
        LVector3    Position;
        LVector3    Velocity;
		u32			WeaponType;	
        u32         WeaponLevel;    ///< ���탌�x�� (1�`3)
		

        /// �O�̂��߂̏����l
        CreateData()
            : WeaponType	( WEAPON_NON )
			, WeaponLevel	( 1 )
        {}
    };

protected:
	static const int scm_nSearchX = 450;         //X���W�T���͈�
	static const int scm_nSearchY = 100;         //Y���W�T���͈�
	static const int scm_nSearchRand = 10;       //�T���͈͌덷
	static const int scm_nWalkIntv = 130;        //�U���Ԋu�t���[����
	static const int scm_nWalkRange = 50;        //�U���͈�
	static const int scm_nAttackRangeRand = 80;  //�U���͈͌덷 //50
	static const int scm_nEscapeRange = 60;      //�����͈�
	static const int scm_nStandbyRange = 250;    //�ώ@�͈�
	static const int scm_nStandbyIntv = 120;     //�ώ@�t���[����
	static const int scm_nGuardIntv = 100;       //�h��t���[����

	EnemyAction m_eAction;

	bool m_bCreateWeapon;

	int m_nAttackDelay;     //�ݐύU���f�B���C��
	int m_nRandAttackDelay; //�����_���f�B���C
	int m_nAttackRangeRand; //�U���͈͌덷
	int m_nRandAttackRange; //�����_���U���͈�
	int m_nRandSearchRange; //�����_���T���͈�
	int m_nWalkIntvCnt;     //�U���܂ł̗ݐσt���[����
	int m_nWalkRangeCnt;    //�U���c�����
	bool m_bWalkDir;        //�U������
	int m_nEscapeRangeCnt;  //�����c�����
	int m_nStandbyCnt;      //�ώ@�c��t���[����
	int m_nGuardCnt;        //�h��c��t���[����
	int m_nSquatCnt;        //���Ⴊ�ݎc��t���[����

	u32 mExp;//�|������������o���l

private:

    /// �R���X�g���N�^�͎g�p�s�Bcreate() �ō쐬���邱�ƁB
    Enemy();

	bool SearchPlayer();

	bool SearchAttack1Range();

	bool SearchJumpAttackRange();

	bool SearchAntiairAttackRange();



public:
    
    /// �f�X�g���N�^
    virtual ~Enemy();

    /// �I�u�W�F�N�g���쐬���� (Initialize() �͂��̒��ŌĂ΂��B�ʏ�Ais_entity_ �� true �ɂ��Ă�������)
    static Enemy* create( void* args_, bool is_entity_ = true );

	static Enemy* createRandom();

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	virtual const char* getName() const {return m_pszName;}

	const CharaState& getCharaState() const {return m_eCharaState;}

	const int& getAnimePuttern() const { return m_AnimePuttern; }

	const CharaDir& getDirection() const {return m_eDirection;}

    
    virtual ObjectType getObjType() const { return OBJ_ENEMY; }
    


    /// ����������̕��탌�x���̎擾
    virtual u32 getWeaponLevel() const { return mWeaponLevel; }

    virtual u32 getExp() const { return mExp; }
	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	

	//---------------------------------------------------------------------------
	/*! 
		@brief Enemy::Initialize

		����������

		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize( const CreateData& data_ );

	//---------------------------------------------------------------------------
	/*! 
		@brief Enemy::Release

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
		@brief Enemy::Update

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
		@brief Enemy::HandleEvent

		�C�x���g����

		@param[in]      EventType event_ �C�x���g�^�C�v
		@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual int HandleEvent(u32 event_,void *args_);

protected:

    Character*  mTargetCharacter;   ///< �U���Ώ�
    u32         mWeaponLevel;       ///< ���탌�x�� (���������Ɏw��)
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
