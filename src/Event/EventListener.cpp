//=============================================================================
/*! 
    @addtogroup 
    @file       EventListener.cpp
    @brief      
    
    EventListener�N���X�̎���
    
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
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_EventListener.h"	/* For DynamicTracer-TestPoint */
#include "./EventType.h"
#include "./EventManager.h"

#if 0

//---------------------------------------------------------------------------
/*! 
	@brief EventListener::EventListener

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
EventListener::EventListener() : mHandle (0)
{
	__DtTestPoint( __DtFunc_EventListener, __DtStep_0 )
	this->mHandle = EventManager::getInstance()->AddListener(this);
	__DtTestPoint( __DtFunc_EventListener, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief EventListener::~EventListener

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
EventListener::~EventListener()
{
	__DtTestPoint( __DtFunc_EventListener, __DtStep_2 )
	EventManager::getInstance()->RemoveListener(this);
	__DtTestPoint( __DtFunc_EventListener, __DtStep_3 )
}

#endif

//=============================================================================
//								End of File
//=============================================================================