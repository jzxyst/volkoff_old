//=============================================================================
/*! 
    @addtogroup 
    @file       Manhole.h
    @brief      �}���z�[���I�u�W�F�N�g
    
    Manhole�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/12/1
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/12/1 matsui
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_Manhole_H__
#define __INCLUDE_Manhole_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */
static const char g_szManholeFilePath[] = "./Data/Graphics/Object/Manhole.png";


/*! @class Ladder */
class Manhole : public GameObject
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
	virtual ObjectType getObjType() const { return OBJ_MANHOLE; }

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	void setEnemyNum(int nEnemyNum_) {this->m_nEnemyNum = nEnemyNum_;}

	void setActive(bool bActive_) {this->m_bActive = bActive_;}

	//---------------------------------------------------------------------------
	/*! 
		@brief Manhole::Manhole

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Manhole();

	//---------------------------------------------------------------------------
	/*! 
		@brief Manhole::~Manhole

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Manhole();

	//---------------------------------------------------------------------------
	/*! 
		@brief Manhole::Initialize

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
		@brief Manhole::Release

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
		@brief Manhole::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Manhole::HandleEvent

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