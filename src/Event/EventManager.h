//=============================================================================
/*! 
    @addtogroup 
    @file       EventManager.h
    @brief      EventListener�̊Ǘ�
    
    EventManager�̒�`
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/17
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/17 Hi-ra Mizuo
      -# �쐬

    - 2011/10/21 yama
      -# �p�~
*/
//=============================================================================

#if 0

//Include Guard
#ifndef __INCLUDE_EVENTMANAGER_H__
#define __INCLUDE_EVENTMANAGER_H__


/*! @par include */
#include "./../Utility/Singleton.h"
#include "./EventType.h"
#include <deque>
#include <map>


/*! @class EventManager */
class EventManager : public Singleton<EventManager>
{
	friend Singleton<EventManager>;

private:
	/*! @par private�����o�ϐ� */
	std::deque<EventListener*> m_dqListenerList;
	std::map<unsigned int,EventListener*> m_mListenerMap;

	unsigned int m_unNextHandle;

private:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::EventManager

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	EventManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::~EventManager

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~EventManager();

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::Initialize

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
		@brief EventManager::Release

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
		@brief EventManager::Update

		�t���[���X�V����

		@param[in]      void
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::AddListener

		���X�i�[�����X�g�ɒǉ�����

		@param[in]      EventListener *pCListener �ǉ����郊�X�i�[�|�C���^
		@return         unsigned int ���X�i�[�n���h��
		@exception      none
	*/
	//---------------------------------------------------------------------------
	unsigned int AddListener(EventListener *pCListener);

	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::RemoveListener

		���X�i�[�����X�g����폜����

		@param[in]      EventListener *pCListener �폜���郊�X�i�[�|�C���^
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void RemoveListener(EventListener *pCListener);
};


//End of Include Guard
#endif

#endif

//=============================================================================
//								End of File
//=============================================================================