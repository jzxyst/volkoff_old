//=============================================================================
/*! 
    @addtogroup 
    @file       Key.h
    @brief      ���I�u�W�F�N�g
    
    Key�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/10/27
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/27 matsui
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_KEY_H__
#define __INCLUDE_KEY_H__


/*! @par include */
#include "./../GameObject.h"
#include "../../Frontend/GuideNamePlate.h"


/*! @par global */
static const char g_szKeyFilePath[] = "./Data/Graphics/Object/Key.png";


/*! @class Ladder */
class Key : public GameObject
{
private:
	LBatchPanel mPanel;

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------

    /// �I�u�W�F�N�g�̎�ނ́u���v
    virtual ObjectType getObjType() const { return OBJ_KEY; }   

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

    virtual void setExit( bool f_ );

	//---------------------------------------------------------------------------
	/*! 
		@brief Key::Key

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Key();

	//---------------------------------------------------------------------------
	/*! 
		@brief Key::~Key

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Key();

	//---------------------------------------------------------------------------
	/*! 
		@brief Key::Initialize

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
		@brief Key::Release

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
		@brief Key::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Key::HandleEvent

		�C�x���g����

		@param[in]      EventType event_ �C�x���g�^�C�v
		@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	//
	// Key::getBoundingRect
	//
	// �דc�ǉ��E�����蔻���Ԃ�
	//
	const LRect* getBoundingRect();


    /// ���O
    virtual const char* getName() const { return "Key"; }


private:

    GuideNamePlate*     mGuideNamePlate;
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================