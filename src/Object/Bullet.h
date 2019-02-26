//=============================================================================
/*! 
    @addtogroup 
    @file       Bullet.h
    @brief      �e�I�u�W�F�N�g
    
    Bullet�N���X�̒�`
    
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
#ifndef __INCLUDE_BULLET_H__
#define __INCLUDE_BULLET_H__


/*! @par include */
#include "./AttackedObject.h"
#include "../Object/GameObjectManager.h"

/*! @par global */
static const char g_szBulletFilePath[] = "./Data/Graphics/Object/Bullet.png";


/*! @class Ladder */
class Bullet : public AttackedObject
{
private:
	LBatchPanel mPanel;
 //int damage_, u32 range_rate_, u32 critical_rate_,  LVector3& brow_vec_, u32 stun_frame_ 
	int mDamage;
    u32 mLifeFrame;
	u32 mRangeRate;
	u32 mCriticalRate;
	LVector3 mBrowVec;
	u32 mFrameCnt;
	u32 mStunFrame;
	ObjectType mGeneObjType;
	int mSeVol;//����
public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
 
	virtual ObjectType getObjType() const { return OBJ_BULLET; }
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
	//�e�̎���
	void setLifeFrame(u32 life_frame_){mLifeFrame = life_frame_;}

	void setSeVol(int se_vol_){mSeVol = se_vol_;}
	//---------------------------------------------------------------------------
	/*! 
		@brief Bullet::Bullet

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Bullet();

	//---------------------------------------------------------------------------
	/*! 
		@brief Bullet::~Bullet

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Bullet();

	//---------------------------------------------------------------------------
	/*! 
		@brief Bullet::Initialize

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
		@brief Bullet::Release

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
		@brief Bullet::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Bullet::HandleEvent

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