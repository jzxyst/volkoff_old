//=============================================================================
/*! 
    @addtogroup 
    @file       Mine.h
    @brief      �n���I�u�W�F�N�g
    
    Mine�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/10/24
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/24 matsui
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_MINE_H__
#define __INCLUDE_MINE_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */
static const char g_szMineFilePath[] = "./Data/Graphics/Object/Mine.png";


/*! @class Ladder */
class Mine : public GameObject
{
private:
	LBatchPanel mPanel;
	bool m_bActive;
	bool m_bStart;
	int m_nAnime;
	int m_nEnemyNum;
	int m_nFrame;

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_MINE; }

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Mine::Mine

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Mine();

	//---------------------------------------------------------------------------
	/*! 
		@brief Mine::~Mine

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Mine();

	//---------------------------------------------------------------------------
	/*! 
		@brief Mine::Initialize

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
		@brief Mine::Release

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
		@brief Mine::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Mine::HandleEvent

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