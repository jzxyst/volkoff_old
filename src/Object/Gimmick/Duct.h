//=============================================================================
/*! 
    @addtogroup 
    @file       Duct.h
    @brief      �_�N�g�I�u�W�F�N�g
    
    Duct�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/11/25
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2012/01/12 matsui
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_DUCT_H__
#define __INCLUDE_DUCT_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */
static const char g_szDuctFilePath[] = "./Data/Graphics/Object/Duct.png";


/*! @class Duct */
class Duct : public GameObject
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
	virtual ObjectType getObjType() const { return OBJ_DOOR; }

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	void setEnemyNum(int nEnemyNum_) {this->m_nEnemyNum = nEnemyNum_;}

	void setActive(bool bActive_) {this->m_bActive = bActive_;}


	//---------------------------------------------------------------------------
	/*! 
		@brief Duct::Duct

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Duct();

	//---------------------------------------------------------------------------
	/*! 
		@brief Duct::~Duct

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Duct();

	//---------------------------------------------------------------------------
	/*! 
		@brief Duct::Initialize

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
		@brief Duct::Release

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
		@brief Duct::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Duct::HandleEvent

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