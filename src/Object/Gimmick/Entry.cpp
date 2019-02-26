//=============================================================================
/*! 
    @addtogroup 
    @file       Entry.cpp
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


/*! @par include */
#include "stdafx.h"
#include	"DT_Entry.h"	/* For DynamicTracer-TestPoint */
#include "./Entry.h"


//---------------------------------------------------------------------------
/*! 
	@brief Entry::Entry

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Entry::Entry()
{
	__DtTestPoint( __DtFunc_Entry, __DtStep_0 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Entry::~Entry

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Entry::~Entry()
{
	__DtTestPoint( __DtFunc_Entry, __DtStep_1 )
	this->Release();
	__DtTestPoint( __DtFunc_Entry, __DtStep_2 )
}


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
bool Entry::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(140.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-70, 40, 0);
	this->mPanel.setTexture(LTexture::create(g_szEntryFilePath));
	this->mPanel.setSrcRect(LRect(0,0,140,80));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);
	this->mFlameCnt = 0;
	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


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
bool Entry::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Entry::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Entry::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	this->mPanel.setPosition(this->mPosition);

	++mFlameCnt;

	if(mFlameCnt == 1)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		Audio.playSE("./Data/Sound/SE/doorclose2.wav",100,100);
		Audio.playSE("./Data/Sound/SE/doorclose3.wav",90,80);	
	}
	if(mFlameCnt <= 5)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		this->mPanel.setSrcRect(LRect(this->mFlameCnt * 140,0,140,80));
	}

	__DtTestPoint( __DtFunc_Update, __DtStep_3 )
	return true;
}


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
int Entry::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}



//=============================================================================
//								End of File
//=============================================================================