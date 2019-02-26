//=============================================================================
/*! 
    @addtogroup 
    @file       Cure_L.h
    @brief      �񕜁i��j�I�u�W�F�N�g
    
    Cure_L�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/10/31
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/31matsui
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_CURE_L_H__
#define __INCLUDE_CURE_L_H__


/*! @par include */
#include "./../GameObject.h"
#include "../../Frontend/GuideNamePlate.h"


/*! @par global */
static const char g_szCure_LFilePath[] = "./Data/Graphics/Object/Cure_L.png";


/*! @class Ladder */
class Cure_L : public GameObject
{
private:
	LBatchPanel mPanel;

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_CURE_L; }

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Cure_L::Cure_L

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Cure_L();

	//---------------------------------------------------------------------------
	/*! 
		@brief Cure_L::~Cure_L

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Cure_L();

	//---------------------------------------------------------------------------
	/*! 
		@brief Cure_L::Initialize

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
		@brief Cure_L::Release

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
		@brief Cure_L::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Cure_L::HandleEvent

		�C�x���g����

		@param[in]      EventType event_ �C�x���g�^�C�v
		@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	//
	// Ladder::getBoundingRect
	//
	// �דc�ǉ��E�����蔻���Ԃ�
	//
	const LRect* getBoundingRect();

    /// ���O
    virtual const char* getName() const { return "Recover 3"; }

private:

    GuideNamePlate*     mGuideNamePlate;
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================