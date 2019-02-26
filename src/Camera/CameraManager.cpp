//=============================================================================
/*! 
    @addtogroup 
    @file       CameraManager.cpp
    @brief      �J�����̊Ǘ�
    
    CameraManager�w�b�_�̎���
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/12/12
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/12/12 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_CameraManager.h"	/* For DynamicTracer-TestPoint */
#include "./CameraManager.h"
#include "./../Game/GameManager.h"
#include "./../Object/Player.h"


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::CameraManager

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
CameraManager::CameraManager()
{
	__DtTestPoint( __DtFunc_CameraManager, __DtStep_0 )
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::~CameraManager

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
CameraManager::~CameraManager()
{
	__DtTestPoint( __DtFunc_CameraManager, __DtStep_1 )
	this->Release();
	__DtTestPoint( __DtFunc_CameraManager, __DtStep_2 )
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool CameraManager::Initialize()
{
	//�J�����̏����ʒu
	//LVector3 v(GameManager::getInstance()->getPlayer()->getPosition().x,(GameManager::getInstance()->getPlayer())->getPosition().y + 80,-1200.0f);
	//LVector3 look(v);

	//Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setPosition(v);
 //   v.z = 0;
	//Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setLookAt(v);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->m_eMode = CAMERA_UNDEF;
	this->m_pCLookObj = NULL;

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool CameraManager::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::Update

	�t���[���X�V����
        
	@param[in]      void
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void CameraManager::Update()
{
	LVector3 v;

	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	switch(this->m_eMode)
	{
	case CAMERA_UNDEF:
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		break;

	case CAMERA_MOVE:
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		v = Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->getPosition();
		v += this->m_CVector;
		Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setPosition(v);
		v.z = 0;
		Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setLookAt(v);
		break;

	case CAMERA_LOOK_OBJECT:
		__DtTestPoint(__DtFunc_Update, __DtStep_3)
		v = this->m_pCLookObj->getPosition();
		v.y += 80;
		v.z = -1200.0f;
		Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setPosition(v);
		v.z = 0;
		Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setLookAt(v);
		break;

	case CAMERA_LOOK_PLAYER:
		__DtTestPoint(__DtFunc_Update, __DtStep_4)
		v = GameManager::getInstance()->getPlayer()->getPosition();
		v.y += 80;
		v.z = -1200.0f;
		Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setPosition(v);
		v.z = 0;
		Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setLookAt(v);
		break;

	default:
		__DtTestPoint(__DtFunc_Update, __DtStep_5)
		break;
	}

	__DtTestPoint( __DtFunc_Update, __DtStep_6 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::Move

	�w�肳�ꂽ�ʒu���瓮��������
        
	@param[in]      LVector3 pos_    - �n�_
	@param[in]      LVector3 vector_ - �x�N�g��
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void CameraManager::Move(LVector3 pos_,LVector3 vector_)
{
	__DtTestPoint( __DtFunc_Move, __DtStep_0 )
	this->m_CVector = vector_;
	Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setPosition(pos_);
	this->m_eMode = CAMERA_MOVE;

	__DtTestPoint( __DtFunc_Move, __DtStep_1 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::ChaseObject

	�w�肳�ꂽ�I�u�W�F�N�g��ǔ�����
        
	@param[in]      GameObject *pObj_ - �I�u�W�F�N�g�|�C���^
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void CameraManager::ChaseObject(GameObject *pObj_)
{
	__DtTestPoint( __DtFunc_ChaseObject, __DtStep_0 )
	this->m_pCLookObj = pObj_;
	this->m_eMode = CAMERA_LOOK_OBJECT;

	__DtTestPoint( __DtFunc_ChaseObject, __DtStep_1 )
	return;
}


//=============================================================================
//								End of File
//=============================================================================
