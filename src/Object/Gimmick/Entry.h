//=============================================================================
/*! 
    @addtogroup 
    @file       Entry.h
    @brief      �����I�u�W�F�N�g
    
    Entry�N���X�̒�`
    
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
#ifndef __INCLUDE_ENTRY_H__
#define __INCLUDE_ENTRY_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */
static const char g_szEntryFilePath[] = "./Data/Graphics/Object/Entry.png";


/*! @class Entry */
class Entry : public GameObject
{
private:
	LBatchPanel mPanel;

	u32 mFlameCnt;
public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_ENTRY; }

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Entry::Entry

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Entry();

	//---------------------------------------------------------------------------
	/*! 
		@brief Entry::~Entry

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Entry();

	//---------------------------------------------------------------------------
	/*! 
		@brief Entry::Initialize

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
		@brief Entry::Release

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
		@brief Entry::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Entry::HandleEvent

		�C�x���g����

		@param[in]      EventType event_ �C�x���g�^�C�v
		@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================