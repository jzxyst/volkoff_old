//=============================================================================
/*! 
    @addtogroup 
    @file       Cure_M.cpp
    @brief     �񕜁@(��)�I�u�W�F�N�g
    
    Cure_M�N���X�̎���
    
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
#include	"DT_Cure_M.h"	/* For DynamicTracer-TestPoint */
#include "./Cure_M.h"


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Cure_M

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_M::Cure_M()
    : mGuideNamePlate   ( NULL )
{
	__DtTestPoint( __DtFunc_Cure_M, __DtStep_0 )
	mColRect.set( mPosition.x+(13*mScale.x), mPosition.y, (15*mScale.x)+(13*mScale.x), 27*mScale.y );
	__DtTestPoint( __DtFunc_Cure_M, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::~Cure_M

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_M::~Cure_M()
{
	__DtTestPoint( __DtFunc_Cure_M, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Cure_M, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_M::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();
	this->mScore = 500;
	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-20, 20, 0);
	this->mPanel.setTexture(LTexture::create(g_szCure_MFilePath));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_M::Release()
{
    __DtTestPoint( __DtFunc_Release, __DtStep_0 )
    SAFE_DELETE( mGuideNamePlate );
	__DtTestPoint( __DtFunc_Release, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_M::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	this->mPanel.setPosition(this->mPosition);

	__DtTestPoint( __DtFunc_Update, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Cure_M::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}

//
// Cure_M::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* Cure_M::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x+(13*mScale.x), mPosition.y, (15*mScale.x)+(13*mScale.x), 27*mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}



//=============================================================================
//								End of File
//=============================================================================