//=============================================================================
/*! 
    @addtogroup 
    @file       Valfirle.h
    @brief      ���@���t�@�[���w�b�_
    
    ���@���t�@�[����pAI�̒�`
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2012/02/15
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2012 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2012/02/15 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_VALFIRLE_H__
#define __INCLUDE_VALFIRLE_H__


/*! @par include */
#include "./Character.h"
#include "Enemy.h"


/*! @par global */
//��Փx�����p�ϐ� //������Easy,Normal,Hard,Valfirle
static const bool scg_bValfirleAttack1Permission[] = {true,true,true,true};    //�U��1�i�ڂ��o���邩�ǂ���
static const bool scg_bValfirleAttack2Permission[] = {true,true,true,true};    //�U��2�i�ڂ��o���邩�ǂ���
static const bool scg_bValfirleAttack3Permission[] = {true,true,true,true};    //�U��3�i�ڂ��o���邩�ǂ���
static const int scg_nValfirleAttackRatio[] = {12,10,9,8};                     //�U�����J�n����䗦�B10�ł����1/10�ōU�����J�n����
static const int scg_nValfirleAttack2Ratio[] = {30,40,50,60};                  //�U��2�i�ڂ��s���䗦�B10�ł����9/10�ōU�����J�n����
static const int scg_nValfirleAttack3Ratio[] = {30,40,50,60};                  //�U��3�i�ڂ��s���䗦�B10�ł����9/10�ōU�����J�n����
static const int scg_nValfirleJumpAttackRatio[] = {4,4,4,4};                   //�W�����v�U�����s�������B10�ł����1/10�ŃW�����v�U�����J�n����
static const int scg_nValfirleSquatAttackRatio[] = {4,4,4,4};                  //���Ⴊ�ݍU�����s�������B10�ł����1/10�ł��Ⴊ�ݍU�����J�n����
static const int scg_nValfirleStandbyRatio[] = {25,25,25,25};                  //�ώ@���s�������B10�ł����1/10�Ŋώ@���J�n����
static const int scg_nValfirleGuardRatio[] = {70,60,50,40};                    //�h����s�������B10�ł����1/10�Ŗh����J�n����
static const int scg_nValfirleSquatGuardRatio[] = {100,90,85,80};              //���Ⴊ�ݖh����s�������B10�ł����1/10�Ŗh����J�n����
static const int scg_nValfirleSquatRatio[] = {50,50,50,50};                    //���Ⴊ�݂��s������
static const int scg_nValfirleJumpRatio[] = {30,30,30,30};                     //�W�����v���s������
static const int scg_nValfirleEscapeRatio[] = {20,20,20,20};                   //�������s������
static const int scg_nValfirleLife[] = {1200,1200,1200,1200};                  //�̗�
static const int scg_nValfirleLifePhase2[] = {500,700,750,800};                //���i�K�ɓ���HP


/*! @class Valfirle */
class Valfirle : public Character
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
	static const int scm_nSearchX = 400;       //X���W�T���͈�
	static const int scm_nSearchY = 100;       //Y���W�T���͈�
	static const int scm_nSearchRand = 10;     //�T���͈͌덷
	static const int scm_nWalkIntv = 0;        //�U���Ԋu�t���[����
	static const int scm_nWalkRange = 50;      //�U���͈�
	static const int scm_nEscapeRange = 60;    //�����͈�
	static const int scm_nStandbyRange = 200;  //�ώ@�͈�
	static const int scm_nStandbyIntv = 60;    //�ώ@�t���[����
	static const int scm_nGuardIntv = 120;     //�h��t���[����

	EnemyAction m_eAction;

	bool m_bCreateWeapon;

	int m_nAttackDelay;     //�ݐύU���f�B���C��
	int m_nRandAttackDelay; //�����_���f�B���C
	int m_nRandAttackRange; //�����_���U���͈�
	int m_nRandSearchRange; //�����_���T���͈�
	int m_nWalkIntvCnt;     //�U���܂ł̗ݐσt���[����
	int m_nWalkRangeCnt;    //�U���c�����
	bool m_bWalkDir;        //�U������
	int m_nEscapeRangeCnt;  //�����c�����
	int m_nStandbyCnt;      //�ώ@�c��t���[����
	int m_nGuardCnt;        //�h��c��t���[����
	int m_nSquatCnt;        //���Ⴊ�ݎc��t���[����
	
	u32 mExp; //�|�������擾�ł���o���l

	int m_nPhase;             //�{�X�̒i�K

	int m_nNum[10];           //�X�N���v�g������g���ϐ�

private:

    /// �R���X�g���N�^�͎g�p�s�Bcreate() �ō쐬���邱�ƁB
    Valfirle();

	bool SearchPlayer();

	bool SearchAttack1Range();

	bool SearchJumpAttackRange();

	bool SearchAntiairAttackRange();

	void ChangePhase();

public:
    
    /// �f�X�g���N�^
    virtual ~Valfirle();

    /// �I�u�W�F�N�g���쐬���� (Initialize() �͂��̒��ŌĂ΂��B�ʏ�Ais_entity_ �� true �ɂ��Ă�������)
    static Valfirle* create( void* args_, bool is_entity_ = true );

	static Valfirle* createRandom();

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	const char* getName() const {return m_pszName;}

	const CharaState& getCharaState() const {return m_eCharaState;}

	const int& getAnimePuttern() const { return m_AnimePuttern; }

	const CharaDir& getDirection() const {return m_eDirection;}

    virtual ObjectType getObjType() const { return OBJ_ENEMY; }

	const int getPhase() const {return this->m_nPhase;}
    
	const int getNum(int nElm_) const {return this->m_nNum[nElm_];}

    /// ����������̕��탌�x���̎擾
    virtual u32 getWeaponLevel() const { return mWeaponLevel; }

	virtual u32 getExp() const { return mExp; }

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	void setNum(int nElm_,int nNum_) {this->m_nNum[nElm_] = nNum_;}
	

	//---------------------------------------------------------------------------
	/*! 
		@brief Valfirle::Initialize

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
		@brief Valfirle::Release

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
		@brief Valfirle::Update

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
		@brief Valfirle::HandleEvent

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
