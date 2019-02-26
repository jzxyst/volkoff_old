//=============================================================================
/*! 
    @addtogroup 
    @file       LadderTop.h
    @brief      �͂����I�u�W�F�N�g
    
    LadderTop�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matsui
    @date       2012/1/12
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
#ifndef __INCLUDE_LADDERTOP_H__
#define __INCLUDE_LADDERTOP_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */
//static const char g_szLaderFilePath[] = "./Data/Graphics/Object/Ladder.png";


/*! @class LadderTop */
class LadderTop : public GameObject
{
private:
	LBatchPanel mPanel;

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_LADDERTOP; }

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief LadderTop::LadderTop

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	LadderTop();

	//---------------------------------------------------------------------------
	/*! 
		@brief LadderTop::~LadderTop

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~LadderTop();

	//---------------------------------------------------------------------------
	/*! 
		@brief LadderTop::Initialize

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
		@brief LadderTop::Release

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
		@brief LadderTop::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief LadderTop::HandleEvent

		�C�x���g����

		@param[in]      EventType event_ �C�x���g�^�C�v
		@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	//
	// LadderTop::getBoundingRect
	//
	// �דc�ǉ��E�����蔻���Ԃ�
	//
	const LRect* getBoundingRect();
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================