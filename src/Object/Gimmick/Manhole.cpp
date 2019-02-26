//=============================================================================
/*! 
    @addtogroup 
    @file       Manhole.cpp
    @brief      �}���z�[���I�u�W�F�N�g
    
    Manhole�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
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


/*! @par include */
#include "stdafx.h"
#include	"DT_Manhole.h"	/* For DynamicTracer-TestPoint */
#include "./Manhole.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"



//---------------------------------------------------------------------------
/*! 
	@brief Manhole::Manhole

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Manhole::Manhole()
{
	__DtTestPoint( __DtFunc_Manhole, __DtStep_0 )
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
	__DtTestPoint( __DtFunc_Manhole, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Manhole::~Manhole

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Manhole::~Manhole()
{
	__DtTestPoint( __DtFunc_Manhole, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Manhole, __DtStep_3 )
}


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
bool Manhole::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-20, 20, 0);
	this->mPanel.setTexture(LTexture::create(g_szManholeFilePath));
	this->mPanel.setSrcRect(LRect(0,0,40,40));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


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
bool Manhole::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Manhole::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Manhole::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	++this->m_nFrame;
	this->mPanel.setPosition(this->mPosition);

	//���������i�K���j//�㉺����200�ȉ� ���� ���E����10�ȉ�
	const int y = 100;
	const int x = 200;
	LVector3 myPos = this->mPosition;
	myPos.x += 50;
	myPos.y -= 50;
	if(abs(myPos.y - GameManager::getInstance()->getPlayer()->getPosition().y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && this->m_bActive && !this->m_bStart)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		Audio.playSE("./Data/Sound/SE/manhole03.wav",100,150);
		Audio.playSE("./Data/Sound/SE/manhole02.wav",100,130);
		Audio.playSE("./Data/Sound/SE/manhole01.wav",100,100);
		this->m_bStart = true;
	}

	if(this->m_bActive)
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		if(this->m_bStart)
		{
			//�A�j���[�V����
			__DtTestPoint(__DtFunc_Update, __DtStep_3)
			if(this->m_nAnime < 4)
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_4)
				this->m_nAnime++;
				this->mPanel.setSrcRect(LRect(this->m_nAnime * 40,0,40,40));
			}

			//�G�o��
			if(!(this->m_nFrame % 8)) //2�t���[����1��
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_5)
				if(this->m_nEnemyNum)
				{
					Enemy* pEnemy = Enemy::createRandom();
					__DtTestPoint(__DtFunc_Update, __DtStep_6)
					pEnemy->setPosition(LVector3(this->mPosition.x + 40,this->mPosition.y - 42,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 40,this->mPosition.y - 42,this->mPosition.z));
					pEnemy->setVelocity(LVector3(::rand() % 10 - 5,10,0));
                    Enemy::CreateData data;

					this->m_nEnemyNum -= 1;
				}
			}
		}

	}

	__DtTestPoint( __DtFunc_Update, __DtStep_7 )
	return true;
}


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
int Manhole::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}


//=============================================================================
//								End of File
//=============================================================================