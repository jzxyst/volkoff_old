//=============================================================================
/*! 
    @addtogroup 
    @file       LadderTop.cpp
    @brief      �͂����I�u�W�F�N�g
    
    LadderTop�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_LadderTop.h"	/* For DynamicTracer-TestPoint */
#include "./LadderTop.h"


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::LadderTop

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
LadderTop::LadderTop()
{
	__DtTestPoint( __DtFunc_LadderTop, __DtStep_0 )
	mColRect.set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );
	__DtTestPoint( __DtFunc_LadderTop, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::~LadderTop

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
LadderTop::~LadderTop()
{
	__DtTestPoint( __DtFunc_LadderTop, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_LadderTop, __DtStep_3 )
}


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
bool LadderTop::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(60.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-30, 10, 0);
	this->mPanel.setTexture(LTexture::create("./Data/Graphics/Object/Ladder.png"));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


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
bool LadderTop::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool LadderTop::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	this->mPanel.setPosition(this->mPosition);

	__DtTestPoint( __DtFunc_Update, __DtStep_1 )
	return true;
}


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
int LadderTop::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}

//
// LadderTop::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* LadderTop::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================