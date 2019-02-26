//=============================================================================
/*! 
    @addtogroup 
    @file       Exit.h
    @brief      �o���I�u�W�F�N�g
    
    Exit�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/11/25
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/25 matsui
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_EXIT_H__
#define __INCLUDE_EXIT_H__


/*! @par include */
#include "./../GameObject.h"
#include "../../Frontend/GuideNamePlate.h"


/*! @par global */
static const char g_szExitFilePath[] = "./Data/Graphics/Object/Exit.png";


/*! @class Exit */
class Exit : public GameObject
{
private:
	LBatchPanel mPanel;

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_EXIT; }

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Exit::Exit

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Exit();

	//---------------------------------------------------------------------------
	/*! 
		@brief Exit::~Exit

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Exit();

	//---------------------------------------------------------------------------
	/*! 
		@brief Exit::Initialize

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
		@brief Exit::Release

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
		@brief Exit::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Exit::HandleEvent

		�C�x���g����

		@param[in]      EventType event_ �C�x���g�^�C�v
		@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);


	const LRect* getBoundingRect();

    /// ���O
    virtual const char* getName() const { return "Exit"; }

private:

    GuideNamePlate*     mGuideNamePlate;

};
//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================