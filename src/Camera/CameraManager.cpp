//=============================================================================
/*! 
    @addtogroup 
    @file       CameraManager.cpp
    @brief      カメラの管理
    
    CameraManagerヘッダの実装
    
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
      -# 作成
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

	デフォルトコンストラクタ

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

	デストラクタ

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

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool CameraManager::Initialize()
{
	//カメラの初期位置
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

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
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

	フレーム更新処理
        
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

	指定された位置から動き続ける
        
	@param[in]      LVector3 pos_    - 始点
	@param[in]      LVector3 vector_ - ベクトル
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

	指定されたオブジェクトを追尾する
        
	@param[in]      GameObject *pObj_ - オブジェクトポインタ
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
