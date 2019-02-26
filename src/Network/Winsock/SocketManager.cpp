//=============================================================================
/*! 
    @addtogroup 
    @file       SocketManager.cpp
    @brief      SocketManagerクラスの実装
    
    ソケットを管理するクラス
    
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
#include	"DT_SocketManager.h"	/* For DynamicTracer-TestPoint */
#include "./SocketManager.h"


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::SocketManager

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
SocketManager::SocketManager()
{
	__DtTestPoint( __DtFunc_SocketManager, __DtStep_0 )
	this->m_hWnd = NULL;
	::memset(&this->m_stWsaData,NULL,sizeof(this->m_stWsaData));
	this->m_unMsg = 0;
	this->m_bSendBufEmpty = false;
	this->m_unTotalSockID = 0;
	__DtTestPoint( __DtFunc_SocketManager, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::~SocketManager

	デストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
SocketManager::~SocketManager()
{
	__DtTestPoint( __DtFunc_SocketManager, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_SocketManager, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::Initialize

	初期化処理

	@param[in]      HWND         hWnd_  - ウィンドウハンドル
	@param[in]      unsigned int unMsg_ - 通知ウィンドウメッセージ
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool SocketManager::Initialize(HWND hWnd_,unsigned int unMsg_)
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	//メンバの初期化
	this->m_hWnd = hWnd_;
	::memset(&this->m_stWsaData,NULL,sizeof(this->m_stWsaData));
	this->m_unMsg = unMsg_;
	this->m_bSendBufEmpty = false;
	this->m_unTotalSockID = 0;

	//受信バッファサイズセット
	this->m_vcRecvBuffer.resize(this->scm_nDefRecvBufSize,NULL);

	//Winsockの初期化(Ver2.2)
	if(::WSAStartup(MAKEWORD(2,2),&this->m_stWsaData))
		return false;

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool SocketManager::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	while(!this->m_liSocketList.empty())
	{
		__DtTestPoint(__DtFunc_Release, __DtStep_1)
		this->m_liSocketList.front()->Release();
		SAFE_DELETE(this->m_liSocketList.front());
		this->m_liSocketList.pop_front();
	}

	::WSACleanup();

	__DtTestPoint( __DtFunc_Release, __DtStep_2 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::Proc

	プロシージャ処理

    @param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
    @return         LRESULT
	@exception      none
	@note
	- この関数をウィンドウプロシージャ内に組み込むこと
*/
//---------------------------------------------------------------------------
LRESULT SocketManager::Proc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
{
	__DtTestPoint( __DtFunc_Proc, __DtStep_0 )
	switch(unMsg_)
	{
	case WM_SOCKET:
		__DtTestPoint(__DtFunc_Proc, __DtStep_1)
		switch(WSAGETSELECTEVENT(lParam_))
		{
		case FD_ACCEPT:
			__DtTestPoint(__DtFunc_Proc, __DtStep_2)
			this->AcceptProc(hWnd_,unMsg_,wParam_,lParam_);
			break;

		case FD_CONNECT:
			__DtTestPoint(__DtFunc_Proc, __DtStep_3)
			this->ConnectProc(hWnd_,unMsg_,wParam_,lParam_);
			break;

		case FD_WRITE:
			__DtTestPoint(__DtFunc_Proc, __DtStep_4)
			this->WriteProc(hWnd_,unMsg_,wParam_,lParam_);
			break;

		case FD_READ:
			__DtTestPoint(__DtFunc_Proc, __DtStep_5)
			this->ReadProc(hWnd_,unMsg_,wParam_,lParam_);
			break;

		case FD_CLOSE:
			__DtTestPoint(__DtFunc_Proc, __DtStep_6)
			this->CloseProc(hWnd_,unMsg_,wParam_,lParam_);
			break;

		default:
			__DtTestPoint(__DtFunc_Proc, __DtStep_7)
			break;
		}
		break;

	default:
		__DtTestPoint(__DtFunc_Proc, __DtStep_8)
		break;
	}

	for(std::list<SocketBase*>::iterator itr = this->m_liSocketList.begin();itr != this->m_liSocketList.end();++itr)
	{
		__DtTestPoint(__DtFunc_Proc, __DtStep_9)
		(*itr)->Proc(hWnd_,unMsg_,wParam_,lParam_);
	}

	__DtTestPoint( __DtFunc_Proc, __DtStep_10 )
	return 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::HandleSend
	
	ソケットのSendListを順次sendする
	
	@param[in]      void
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void SocketManager::HandleSend(void)
{
	__DtTestPoint( __DtFunc_HandleSend, __DtStep_0 )
	if(this->m_bSendBufEmpty)
	{
		__DtTestPoint(__DtFunc_HandleSend, __DtStep_1)
		for(std::list<SocketBase*>::iterator itr = this->m_liSocketList.begin();itr != this->m_liSocketList.end();++itr)
		{
			__DtTestPoint(__DtFunc_HandleSend, __DtStep_2)
			if(!(*itr)->m_liSendList.empty())
			{
				__DtTestPoint(__DtFunc_HandleSend, __DtStep_3)
				if((*itr)->_Send() == WSAEWOULDBLOCK)
				{
					__DtTestPoint(__DtFunc_HandleSend, __DtStep_4)
					this->m_bSendBufEmpty = false;
					break;
				}
			}
		}
	}

	__DtTestPoint( __DtFunc_HandleSend, __DtStep_5 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::AcceptProc

	FD_ACCEPT発生時の処理

    @param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void SocketManager::AcceptProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
{
	//std::list<SocketBase*>::iterator itr = this->m_liSocketList.begin();

	//for(;itr != this->m_liSocketList.end();++itr)
	//{
	//	if((*itr)->getSock() == static_cast<SOCKET>(wParam_))
	//	{
	//		break;
	//	}
	//}

	//dynamic_cast<TcpSocket*>((*itr))->m_nAcceptDemandNum += 1;

	//::PostMessage(this->m_hWnd,this->m_unMsg,SM_ACCEPT,(*itr)->getSockID());

	__DtTestPoint( __DtFunc_AcceptProc, __DtStep_0 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::ConnectProc

	FD_CONNECT発生時の処理

    @param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void SocketManager::ConnectProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
{
	//std::list<SocketBase*>::iterator itr = this->m_liSocketList.begin();

	//for(;itr != this->m_liSocketList.end();++itr)
	//{
	//	if((*itr)->getSock() == static_cast<SOCKET>(wParam_))
	//	{
	//		break;
	//	}
	//}

	//(*itr)->m_bConnect = true;

	//::PostMessage(this->m_hWnd,this->m_unMsg,SM_CONNECT,(*itr)->getSockID());

	__DtTestPoint( __DtFunc_ConnectProc, __DtStep_0 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::WriteProc

	FD_WRITE発生時の処理

    @param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void SocketManager::WriteProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
{
	__DtTestPoint( __DtFunc_WriteProc, __DtStep_0 )
	this->m_bSendBufEmpty = true;

	//順次送信を再開する
	this->HandleSend();

	__DtTestPoint( __DtFunc_WriteProc, __DtStep_1 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::ReadProc

	FD_READ発生時の処理

    @param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void SocketManager::ReadProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
{
	//受信バッファ初期化
	//::memset(&this->m_vcRecvBuffer[0],NULL,this->m_vcRecvBuffer.capacity());

	//std::list<SocketBase*>::iterator itr = this->m_liSocketList.begin();

	//for(;itr != this->m_liSocketList.end();++itr)
	//{
	//	if((*itr)->getSock() == static_cast<SOCKET>(wParam_))
	//	{
	//		break;
	//	}
	//}

	//int nRecvSize = 0;

	//nRecvSize = (*itr)->_Recv(&this->m_vcRecvBuffer[0],this->m_vcRecvBuffer.capacity());

	//if(nRecvSize > 0)
	//	::PostMessage(this->m_hWnd,this->m_unMsg,SM_RECV,(*itr)->getSockID());

	__DtTestPoint( __DtFunc_ReadProc, __DtStep_0 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::CloseProc

	FD_CLOSE発生時の処理

    @param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void SocketManager::CloseProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
{
	//std::list<SocketBase*>::iterator itr = this->m_liSocketList.begin();

	//for(;itr != this->m_liSocketList.end();++itr)
	//{
	//	if((*itr)->getSock() == static_cast<SOCKET>(wParam_))
	//	{
	//		break;
	//	}
	//}

	//(*itr)->AsyncClose();

	//::PostMessage(this->m_hWnd,this->m_unMsg,SM_CLOSE,(*itr)->getSockID());

	__DtTestPoint( __DtFunc_CloseProc, __DtStep_0 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::AddSocket
	
	ソケットリストに追加する
	
	@param[in]      SocketBase *pCSocket_ ソケットポインタ
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void SocketManager::AddSocket(SocketBase *pCSocket_)
{
	//ソケットメンバの初期化
	__DtTestPoint( __DtFunc_AddSocket, __DtStep_0 )
	pCSocket_->setSockID(this->m_unTotalSockID);

	//リストに追加
	this->m_liSocketList.push_back(pCSocket_);

	this->m_unTotalSockID++;

	__DtTestPoint( __DtFunc_AddSocket, __DtStep_1 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief SocketManager::RemoveSocket
	
	ソケットリストから削除する
	
	@param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         void
	@exception      none
	@note
	- この関数は子がdeleteされる際に呼ばれるので、こちらからはdeleteしない。
	- 引数にmapのkeyを渡す方法も考える。
*/
//---------------------------------------------------------------------------
void SocketManager::RemoveSocket(SocketBase *pCSocket_)
{
	//リストからの削除
	__DtTestPoint( __DtFunc_RemoveSocket, __DtStep_0 )
	this->m_liSocketList.remove(pCSocket_);

	__DtTestPoint( __DtFunc_RemoveSocket, __DtStep_1 )
	return;
}


//=============================================================================
//								End of File
//=============================================================================