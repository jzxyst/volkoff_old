//=============================================================================
/*! 
    @addtogroup 
    @file       Grenade.h
    @brief      �e�I�u�W�F�N�g
    
    Grenade�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/12/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/12/13 matsui
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_GRENADE_H__
#define __INCLUDE_GRENADE_H__


/*! @par include */
#include "./AttackedObject.h"
#include "../Object/GameObjectManager.h"

/*! @par global */
static const char g_szGrenadeFilePath[] = "./Data/Graphics/Object/Grenade.png";


/*! @class Ladder */
class Grenade : public AttackedObject
{
private:
	LBatchPanel mPanel;
 //int damage_, u32 range_rate_, u32 critical_rate_,  LVector3& brow_vec_, u32 stun_frame_ 
	int mDamage;
	u32 mRangeRate;
	u32 mCriticalRate;
	LVector3 mBrowVec;
	u32 mFrameCnt;
	u32 mStunFrame;
	ObjectType mGeneObjType;
	float mFallSpeed;
	int mRandBrowX;
	int mRandBrowY;
	u32   mRandStun;
public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
 
	virtual ObjectType getObjType() const { return OBJ_GRENADE; }
	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	void setGeneObjType(ObjectType gene_obj_type_) {mGeneObjType = gene_obj_type_;}
	//�e�̈З͂̐ݒ�
	void setAttackParam(int damage_,u32 range_rate_,u32 critical_rate_,LVector3& brow_vec_,u32 stun_frame_ ){
						mDamage = damage_;
						mRangeRate = range_rate_;
						mCriticalRate = critical_rate_;
						mBrowVec = brow_vec_;
						mStunFrame = stun_frame_;
						}
	void setFallSpeed(float fall_speed_) { mFallSpeed = fall_speed_;}

	//�w�肵�����l��������ѕ��������_���ɕς��
	void setRandBrow(int rand_brow_x_,int rand_brow_y_) { mRandBrowX = rand_brow_x_; mRandBrowY = rand_brow_y_;}

	void setRandStun(u32 rand_stun_) { mRandStun = rand_stun_;}
	//---------------------------------------------------------------------------
	/*! 
		@brief Grenade::Grenade

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Grenade();

	//---------------------------------------------------------------------------
	/*! 
		@brief Grenade::~Grenade

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Grenade();

	//---------------------------------------------------------------------------
	/*! 
		@brief Grenade::Initialize

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
		@brief Grenade::Release

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
		@brief Grenade::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Grenade::HandleEvent

		�C�x���g����

		@param[in]      EventType event_ �C�x���g�^�C�v
		@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	//
	const LRect* getBoundingRect();
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================