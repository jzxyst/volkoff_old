//=============================================================================
/*! 
    @addtogroup 
    @file       SocketBase.cpp
    @brief      SocketBaseクラスの実装
    
    ソケットの基底クラス
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/09/08
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/09/08 Hi-ra Mizuno
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_SocketBase.h"	/* For DynamicTracer-TestPoint */
#include "./SocketManager.h"
#include "./SocketBase.h"


//---------------------------------------------------------------------------
/*! 
	@brief SocketBase::SocketBase

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
SocketBase::SocketBase()
{
	//メンバ初期化
	__DtTestPoint( __DtFunc_SocketBase, __DtStep_0 )
	this->m_hSock = INVALID_SOCKET;
	this->m_unSockID = 0;
	::memset(&this->m_stMyAddrParam,NULL,sizeof(this->m_stMyAddrParam));
	::memset(&this->m_stOthAddrParam,NULL,sizeof(this->m_stOthAddrParam));
	this->m_eProtocol = PRT_UNDEF;
	this->m_bBind = false;
	this->m_bListen = false;
	this->m_bConnect = false;
	this->m_unOldSendSize = 0;
	this->m_unOldRecvSize = 0;
	this->m_unSendSizePerSecond = 0;
	this->m_unRecvSizePerSecond = 0;
	this->m_ullTotalSendSize = 0;
	this->m_ullTotalRecvSize = 0;
	this->m_unTime = 0;
	this->m_unTimerID = 0;
	this->m_nLastError = 0;

	::SetTimer(SocketManager::getInstance()->getHWnd(),this->m_unSockID,this->scm_nTimerIntv,NULL);
	this->m_unTimerID = this->m_unSockID;
	SocketManager::getInstance()->AddSocket(this);
	__DtTestPoint( __DtFunc_SocketBase, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketBase::~SocketBase

	デストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
SocketBase::~SocketBase()
{
	__DtTestPoint( __DtFunc_SocketBase, __DtStep_2 )
	::KillTimer(SocketManager::getInstance()->getHWnd(),this->m_unTimerID);
	SocketManager::getInstance()->RemoveSocket(this);
	__DtTestPoint( __DtFunc_SocketBase, __DtStep_3 )
}


//=============================================================================
//								End of File
//=============================================================================