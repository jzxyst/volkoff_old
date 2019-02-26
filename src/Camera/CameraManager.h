//=============================================================================
/*! 
    @addtogroup 
    @file       CameraManager.h
    @brief      �J�����̊Ǘ�
    
    CameraManager�̒�`
    
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


//Include Guard
#ifndef __INCLUDE_CAMERAMANAGER_H__
#define __INCLUDE_CAMERAMANAGER_H__


/*! @par include */
#include "./../Utility/Singleton.h"
#include "./../Object/GameObject.h"


/*! @enum CameraMode */
typedef enum _ENUM_CAMERA_MODE
{
	CAMERA_UNDEF = 0,
	CAMERA_ZOOM_IN,
	CAMERA_ZOOM_OUT,
	CAMERA_MOVE,
	CAMERA_LOOK_OBJECT,
	CAMERA_LOOK_PLAYER,
}CameraMode;


/*! @class GameObjectManager */
class CameraManager : public Singleton<CameraManager>
{
	friend Singleton<CameraManager>;

private:
	/*! @par private�����o�ϐ� */
	CameraMode m_eMode;
	GameObject *m_pCLookObj;
	LVector3 m_CVector;

private:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::CameraManager

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	CameraManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::~CameraManager

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~CameraManager();

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	void setMode(CameraMode eMode_) {this->m_eMode = eMode_;}

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
	bool Initialize();

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
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::Update

		�t���[���X�V����
        
		@param[in]      void
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void Update();

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
	void Move(LVector3 pos_,LVector3 vector_);

	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::ChaseObject

		�w�肳�ꂽ�I�u�W�F�N�g��ǔ�����
        
		@param[in]      GameObject *pObj_ - �I�u�W�F�N�g�|�C���^
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void ChaseObject(GameObject *pObj_);
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
