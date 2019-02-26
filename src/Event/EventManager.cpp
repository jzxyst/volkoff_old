//=============================================================================
/*! 
    @addtogroup 
    @file       EventManager.cpp
    @brief      
    
    EventManagerクラスの実装
    
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
      -# 作成
*/
//=============================================================================



/*! @par include */
#include "stdafx.h"
#include	"DT_EventManager.h"	/* For DynamicTracer-TestPoint */
#include "./EventManager.h"

#if 0

//---------------------------------------------------------------------------
/*! 
	@brief EventManager::EventManager

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
EventManager::EventManager()
{
	__DtTestPoint( __DtFunc_EventManager, __DtStep_0 )
	this->m_unNextHandle = 1;
	__DtTestPoint( __DtFunc_EventManager, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::~EventManager

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
EventManager::~EventManager()
{
	__DtTestPoint( __DtFunc_EventManager, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_EventManager, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool EventManager::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	this->m_unNextHandle = 1;

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool EventManager::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::Update

	フレーム更新処理

	@param[in]      void
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void EventManager::Update()
{
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::AddListener

	リスナーをリストに追加する

	@param[in]      EventListener *pCListener 追加するリスナーポインタ
	@return         unsigned int リスナーハンドル
	@exception      none
*/
//---------------------------------------------------------------------------
unsigned int EventManager::AddListener(EventListener *pCListener)
{
	__DtTestPoint( __DtFunc_AddListener, __DtStep_0 )
	pCListener->setHandle(this->m_unNextHandle);
	this->m_dqListenerList.push_back(pCListener);
	this->m_mListenerMap.insert(std::pair<unsigned int,EventListener*>(this->m_unNextHandle,pCListener));

	__DtTestPoint( __DtFunc_AddListener, __DtStep_1 )
	return (m_unNextHandle++);
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::RemoveListener

	リスナーをリストから削除する

	@param[in]      EventListener *pCListener 削除するリスナーポインタ
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
void EventManager::RemoveListener(EventListener *pCListener)
{
	__DtTestPoint( __DtFunc_RemoveListener, __DtStep_0 )
	for(std::deque<EventListener*>::iterator itr = this->m_dqListenerList.begin();itr != this->m_dqListenerList.end();++itr)
	{
		__DtTestPoint(__DtFunc_RemoveListener, __DtStep_1)
		if((*itr) == pCListener)
		{
			__DtTestPoint(__DtFunc_RemoveListener, __DtStep_2)
			this->m_dqListenerList.erase(itr);
			break;
		}
	}

	for(std::map<unsigned int,EventListener*>::iterator itr = this->m_mListenerMap.begin();itr != this->m_mListenerMap.end();++itr)
	{
		__DtTestPoint(__DtFunc_RemoveListener, __DtStep_3)
		if((*itr).second == pCListener)
		{
			__DtTestPoint(__DtFunc_RemoveListener, __DtStep_4)
			this->m_mListenerMap.erase(itr);
			break;
		}
	}

	__DtTestPoint( __DtFunc_RemoveListener, __DtStep_5 )
	return;
}

#endif

//=============================================================================
//								End of File
//=============================================================================