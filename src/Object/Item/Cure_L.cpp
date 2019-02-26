//=============================================================================
/*! 
    @addtogroup 
    @file       Cure_L.cpp
    @brief     �񕜁@(��)�I�u�W�F�N�g
    
    Cure_L�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/31
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/31 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Cure_L.h"	/* For DynamicTracer-TestPoint */
#include "./Cure_L.h"


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Cure_L

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_L::Cure_L()
    : mGuideNamePlate   ( NULL )
{
	__DtTestPoint( __DtFunc_Cure_L, __DtStep_0 )
	this->mColRect.set(
		this->mPosition.x+( 11 * this->mScale.x ),
		this->mPosition.y, ( 19 * this->mScale.x ) + ( 11 * this->mScale.x ),
		34 * this->mScale.y );
	__DtTestPoint( __DtFunc_Cure_L, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::~Cure_L

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_L::~Cure_L()
{
    
	__DtTestPoint( __DtFunc_Cure_L, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Cure_L, __DtStep_3 )
}


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
bool Cure_L::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();
	this->mScore = 1000;
	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-20, 20, 0);
	this->mPanel.setTexture(LTexture::create(g_szCure_LFilePath));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


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
bool Cure_L::Release()
{
    __DtTestPoint( __DtFunc_Release, __DtStep_0 )
    SAFE_DELETE( mGuideNamePlate );
	__DtTestPoint( __DtFunc_Release, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_L::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	this->mPanel.setPosition(this->mPosition);

	__DtTestPoint( __DtFunc_Update, __DtStep_1 )
	return true;
}


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
int Cure_L::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}

//
// Ladder::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* Cure_L::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	this->mColRect.set(
		this->mPosition.x+( 11 * this->mScale.x ),
		this->mPosition.y, ( 19 * this->mScale.x ) + ( 11 * this->mScale.x ),
		34 * this->mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================