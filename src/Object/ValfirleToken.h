//=============================================================================
/*! 
    @addtogroup 
    @file       ValfirleToken.h
    @brief      ���@���t�@�[���g�[�N��
    
    ���@���t�@�[���g�[�N������̒�`
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/2/17
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011//2/17
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_VALFIRLETOKEN_H__
#define __INCLUDE_VALFIRLETOKEN_H__


/*! @par include */
#include "./Character.h"
#include "Enemy.h"


/*! @par global */
//��Փx�����p�ϐ� //������Easy,Normal,Hard,Valfirle
static const bool scg_bValfirleTokenAttack1Permission[] = {true,true,true,true};    //�U��1�i�ڂ��o���邩�ǂ���
static const bool scg_bValfirleTokenAttack2Permission[] = {true,true,true,true};    //�U��2�i�ڂ��o���邩�ǂ���
static const bool scg_bValfirleTokenAttack3Permission[] = {true,true,true,true};    //�U��3�i�ڂ��o���邩�ǂ���
static const int scg_nValfirleTokenAttackRatio[] = {15,12,12,10};                   //�U�����J�n����䗦�B10�ł����1/10�ōU�����J�n����
static const int scg_nValfirleTokenAttack2Ratio[] = {25,35,40,40};                  //�U��2�i�ڂ��s���䗦�B10�ł����9/10�ōU�����J�n����
static const int scg_nValfirleTokenAttack3Ratio[] = {25,35,40,40};                  //�U��3�i�ڂ��s���䗦�B10�ł����9/10�ōU�����J�n����
static const int scg_nValfirleTokenJumpAttackRatio[] = {4,4,4,4};                   //�W�����v�U�����s�������B10�ł����1/10�ŃW�����v�U�����J�n����
static const int scg_nValfirleTokenSquatAttackRatio[] = {4,4,4,4};                  //���Ⴊ�ݍU�����s�������B10�ł����1/10�ł��Ⴊ�ݍU�����J�n����
static const int scg_nValfirleTokenStandbyRatio[] = {20,19,18,17};                  //�ώ@���s�������B10�ł����1/10�Ŋώ@���J�n����
static const int scg_nValfirleTokenGuardRatio[] = {70,60,50,40};                    //�h����s�������B10�ł����1/10�Ŗh����J�n����
static const int scg_nValfirleTokenSquatGuardRatio[] = {100,90,85,80};              //���Ⴊ�ݖh����s�������B10�ł����1/10�Ŗh����J�n����
static const int scg_nValfirleTokenSquatRatio[] = {60,60,60,60};                    //���Ⴊ�݂��s������
static const int scg_nValfirleTokenJumpRatio[] = {40,40,40,40};                     //�W�����v���s������
static const int scg_nValfirleTokenEscapeRatio[] = {20,20,20,20};                   //�������s������
static const int scg_nValfirleTokenLife[] = {100,100,100,100};                      //�̗�


/*! @class ValfirleToken */
class ValfirleToken : public Character
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
	static const int scm_nSearchX = 350;       //X���W�T���͈�
	static const int scm_nSearchY = 100;       //Y���W�T���͈�
	static const int scm_nSearchRand = 10;     //�T���͈͌덷
	static const int scm_nWalkIntv = 110;      //�U���Ԋu�t���[����
	static const int scm_nWalkRange = 50;      //�U���͈�
	static const int scm_nEscapeRange = 60;    //�����͈�
	static const int scm_nStandbyRange = 200;  //�ώ@�͈�
	static const int scm_nStandbyIntv = 30;    //�ώ@�t���[����
	static const int scm_nGuardIntv = 70;     //�h��t���[����

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

	bool mDestructfrag; ///�����t���O

private:

    /// �R���X�g���N�^�͎g�p�s�Bcreate() �ō쐬���邱�ƁB
    ValfirleToken();

	bool SearchPlayer();

	bool SearchAttack1Range();

	bool SearchJumpAttackRange();

	bool SearchAntiairAttackRange();

public:
    
    /// �f�X�g���N�^
    virtual ~ValfirleToken();

    /// �I�u�W�F�N�g���쐬���� (Initialize() �͂��̒��ŌĂ΂��B�ʏ�Ais_entity_ �� true �ɂ��Ă�������)
    static ValfirleToken* create( void* args_, bool is_entity_ = true );

	static ValfirleToken* createRandom();

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	const char* getName() const {return m_pszName;}

	const CharaState& getCharaState() const {return m_eCharaState;}

	const int& getAnimePuttern() const { return m_AnimePuttern; }

	const CharaDir& getDirection() const {return m_eDirection;}

    
    virtual ObjectType getObjType() const { return OBJ_ENEMY; }
    
	const bool getDestructfrag() const { return mDestructfrag;}

    /// ����������̕��탌�x���̎擾
    virtual u32 getWeaponLevel() const { return mWeaponLevel; }

	virtual u32 getExp() const { return mExp; }
	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	void setDestructfrag(bool destruct_frag_){ mDestructfrag = destruct_frag_;} 
	

	//---------------------------------------------------------------------------
	/*! 
		@brief ValfirleToken::Initialize

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
		@brief ValfirleToken::Release

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
		@brief ValfirleToken::Update

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
		@brief ValfirleToken::HandleEvent

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
