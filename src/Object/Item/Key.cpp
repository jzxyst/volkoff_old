//=============================================================================
/*! 
    @addtogroup 
    @file       Key.cpp
    @brief     ���I�u�W�F�N�g
    
    Key�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
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


/*! @par include */
#include "stdafx.h"
#include	"DT_Key.h"	/* For DynamicTracer-TestPoint */
#include "./Key.h"



//---------------------------------------------------------------------------
/*! 
	@brief Key::Key

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Key::Key()
    : mGuideNamePlate   ( NULL )
{
	__DtTestPoint( __DtFunc_Key, __DtStep_0 )
	mColRect.set( mPosition.x, mPosition.y, 40*mScale.x, 40*mScale.y );
	__DtTestPoint( __DtFunc_Key, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Key::~Key

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Key::~Key()
{
	__DtTestPoint( __DtFunc_Key, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Key, __DtStep_3 )
}


void Key::setExit( bool f_ )
{
    __DtTestPoint( __DtFunc_setExit, __DtStep_0 )
    GameObject::setExit( f_ );
	__DtTestPoint( __DtFunc_setExit, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Key::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ��
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Key::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();
	this->mScore = 500; 
	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-20, 20, 0);
	this->mPanel.setTexture(LTexture::create(g_szKeyFilePath));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);


    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

    //printf( "�� key h:%d p:%p\n", this->getHandle(), this );
         
	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


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
bool Key::Release()
{
    __DtTestPoint( __DtFunc_Release, __DtStep_0 )
    SAFE_DELETE( mGuideNamePlate );
	__DtTestPoint( __DtFunc_Release, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Key::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Key::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	this->mPanel.setPosition(this->mPosition);

	__DtTestPoint( __DtFunc_Update, __DtStep_1 )
	return true;
}


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
int Key::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}

//
// Key::getBoundingRect
//
// �דc�ǉ��E�����蔻���Ԃ�
//
const LRect* Key::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x, mPosition.y, 40*mScale.x, 40*mScale.y );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================