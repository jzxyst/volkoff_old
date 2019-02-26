//=============================================================================
/*! 
    @addtogroup 
    @file       TcpStream.cpp
    @brief      TcpStreamクラスの実装
    
    パケットの分割・組立や、セッションの管理を行う
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/28
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/28 Hi-ra Mizuno
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_TcpStream.h"	/* For DynamicTracer-TestPoint */
#include "./Winsock/SocketManager.h"
#include "./TcpStream.h"


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::TcpStream
	
	デフォルトコンストラクタ
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
TcpStream::TcpStream()
{
	__DtTestPoint( __DtFunc_TcpStream, __DtStep_0 )
	this->m_unSaveSize = 0;
	this->m_eSessionState = SST_UNDEF;
	this->m_dwPing = 0;
	this->m_dwPingSendTime = 0;
	this->m_bSendPing = false;
	__DtTestPoint( __DtFunc_TcpStream, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::~TcpStream
	
	デストラクタ
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
TcpStream::~TcpStream()
{
	__DtTestPoint( __DtFunc_TcpStream, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_TcpStream, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Initialize
	
	初期化処理
	
	@param[in]      SOCKET hSock_ 初期ソケットハンドル 
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Initialize(SOCKET hSock_)
{
	bool bRes = true;

	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	bRes = this->TcpSocket::Initialize(hSock_);

	this->m_unSaveSize = 0;
	this->m_eSessionState = SST_UNDEF;
	this->m_dwPing = 0;
	this->m_dwPingSendTime = 0;
	this->m_bSendPing = false;

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Release
	
	終了処理
	
	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Release()
{
	bool bRes = true;

	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	bRes = this->TcpSocket::Release();

	__DtTestPoint( __DtFunc_Release, __DtStep_1 )
	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Close
	
	通信を切断する
	
	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Close()
{
	__DtTestPoint( __DtFunc_Close, __DtStep_0 )
	this->m_eSessionState = SST_CLOSE;

	__DtTestPoint( __DtFunc_Close, __DtStep_1 )
	return this->TcpSocket::Close();
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::AsyncClose
	
	通信相手と同期を取らず、強制的にソケットを閉じる
	
	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
	@note
		- 推薦されません。
*/
//---------------------------------------------------------------------------
bool TcpStream::AsyncClose()
{
	__DtTestPoint( __DtFunc_AsyncClose, __DtStep_0 )
	this->m_eSessionState = SST_CLOSE;

	__DtTestPoint( __DtFunc_AsyncClose, __DtStep_1 )
	return this->TcpSocket::AsyncClose();
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Listen
	
	ソケットを接続待機状態にする
	
	@param[in]      int nMaxConnect_ - 最大接続受付数
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Listen(int nMaxConnect_)
{
	__DtTestPoint( __DtFunc_Listen, __DtStep_0 )
	this->m_eSessionState = SST_LISTEN;

	__DtTestPoint( __DtFunc_Listen, __DtStep_1 )
	return this->TcpSocket::Listen(nMaxConnect_);
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Accept
	
	接続要求を受理する
	
	@param[in]      TcpStream **ppCNewStream_ 接続要求を受理する新しいポインタ
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Accept(TcpStream **ppCNewStream_)
{
	SOCKET hSock = INVALID_SOCKET;

	__DtTestPoint( __DtFunc_Accept, __DtStep_0 )
	(*ppCNewStream_) = new TcpStream();
	int nLen = sizeof((*ppCNewStream_)->getOthAddrParam());

	//::WSAAccept
	if((hSock = ::accept(this->m_hSock,reinterpret_cast<sockaddr*>(&(*ppCNewStream_)->getOthAddrParam()),&nLen)) == INVALID_SOCKET)
	{
		__DtTestPoint(__DtFunc_Accept, __DtStep_1)
		this->m_nLastError = ::WSAGetLastError();
		__DtTestPoint( __DtFunc_Accept, __DtStep_2 )
		return false;
	}
	if(!(*ppCNewStream_)->Initialize(hSock))
	{
		__DtTestPoint(__DtFunc_Accept, __DtStep_3)
		SAFE_DELETE((*ppCNewStream_));
		__DtTestPoint( __DtFunc_Accept, __DtStep_4 )
		return false;
	}

	(*ppCNewStream_)->m_bConnect = true;
	(*ppCNewStream_)->m_eSessionState = SST_ESTABLISHED;

	this->m_nAcceptDemandNum -= 1;

	__DtTestPoint( __DtFunc_Accept, __DtStep_5 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Connect
	
	指定されたIPアドレスに対して接続を試みる
	
	@param[in]      IPv4L ulAddr_ - 接続先IPアドレス(IPv4)
	@param[in]      PORT  usPort_ - 接続先ポート番号
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Connect(IPv4L ulAddr_,PORT usPort_)
{
	__DtTestPoint( __DtFunc_Connect, __DtStep_0 )
	this->m_eSessionState = SST_CONNECTING;

	__DtTestPoint( __DtFunc_Connect, __DtStep_1 )
	return this->TcpSocket::Connect(ulAddr_,usPort_);
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Connect
	
	指定されたIPアドレスに対して接続を試みる
	
	@param[in]      IPv4A pszAddr_ - 接続先IPアドレス(IPv4)
	@param[in]      PORT  usPort_  - 接続先ポート番号
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Connect(IPv4A pszAddr_,PORT usPort_)
{
	__DtTestPoint( __DtFunc_Connect, __DtStep_2 )
	this->m_eSessionState = SST_CONNECTING;

	__DtTestPoint( __DtFunc_Connect, __DtStep_3 )
	return this->TcpSocket::Connect(pszAddr_,usPort_);
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Connect
	
	指定されたIPアドレスに対して接続を試みる
	
	@param[in]      IPv4W pwszAddr_ - 接続先IPアドレス(IPv4)
	@param[in]      PORT  usPort_   - 接続先ポート番号
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Connect(IPv4W pwszAddr_,PORT usPort_)
{
	__DtTestPoint( __DtFunc_Connect, __DtStep_4 )
	this->m_eSessionState = SST_CONNECTING;

	__DtTestPoint( __DtFunc_Connect, __DtStep_5 )
	return this->TcpSocket::Connect(pwszAddr_,usPort_);
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Connect
	
	指定されたIPアドレスに対して接続を試みる
	
	@param[in]      sockaddr_in stAddr_ - 接続先情報
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Connect(sockaddr_in stAddr_)
{
	__DtTestPoint( __DtFunc_Connect, __DtStep_6 )
	this->m_eSessionState = SST_CONNECTING;

	__DtTestPoint( __DtFunc_Connect, __DtStep_7 )
	return this->TcpSocket::Connect(stAddr_);
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Send
	
	データを送信リストに追加する
	
	@param[in]      const void *c_pData_  - データ
	@param[in]      size_t     unSize_    - データサイズ
	@param[in]      bool       bPriority_ - 優先して送信する
	@return         int
	- 0     成功
	- 0以外 エラーコード
	@exception      none
*/
//---------------------------------------------------------------------------
int TcpStream::Send(const void *c_pData_,size_t unSize_,bool bPriority_)
{
	TransportHeader stTransHead;
	SessionHeader stSessionHead;

	__DtTestPoint( __DtFunc_Send, __DtStep_0 )
	::memset(&stTransHead,NULL,sizeof(stTransHead));
	::memset(&stSessionHead,NULL,sizeof(stSessionHead));

	//ヘッダを適当にセットする
	stTransHead.unDataSize = unSize_ + sizeof(stSessionHead);
	stSessionHead.ucSessionBit = SSF_SEND;

	//送信バッファをリサイズ
	if(this->m_vcSendBuffer.capacity() < sizeof(stTransHead) + sizeof(stSessionHead) + unSize_)
		this->m_vcSendBuffer.resize(sizeof(stTransHead) + sizeof(stSessionHead) + unSize_);

	//送信バッファにヘッダとデータをセット
	::memcpy_s(&this->m_vcSendBuffer[0],this->m_vcSendBuffer.capacity(),&stTransHead,sizeof(stTransHead));
	::memcpy_s(&this->m_vcSendBuffer[sizeof(stTransHead)],this->m_vcSendBuffer.capacity() - sizeof(stTransHead),&stSessionHead,sizeof(stSessionHead));
	::memcpy_s(&this->m_vcSendBuffer[sizeof(stTransHead) + sizeof(stSessionHead)],this->m_vcSendBuffer.capacity() - sizeof(stTransHead) - sizeof(stSessionHead),c_pData_,unSize_);

	//送信リストに追加
	bPriority_ ? this->m_liSendList.push_front(new Packet(reinterpret_cast<const char*>(&this->m_vcSendBuffer[0]),sizeof(stTransHead) + sizeof(stSessionHead) + unSize_)) : this->m_liSendList.push_back(new Packet(reinterpret_cast<const char*>(&this->m_vcSendBuffer[0]),sizeof(stTransHead) + sizeof(stSessionHead) + unSize_));

	SocketManager::getInstance()->HandleSend();

	__DtTestPoint( __DtFunc_Send, __DtStep_1 )
	return 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::_Recv
	
	データを受信する
	
	@param[in]      void   *pBuff      - データ格納先ポインタ
	@param[in]      size_t unBuffSize_ - 格納先サイズ 
	@return         int
	- 受信データサイズ(Byte)
	@exception      none
*/
//---------------------------------------------------------------------------
int TcpStream::_Recv(void *pBuff_,size_t unBuffSize_)
{
	int nRecvSize = 0;

	//::WSARecv
	__DtTestPoint( __DtFunc__Recv, __DtStep_0 )
	if((nRecvSize = ::recv(this->m_hSock,reinterpret_cast<char*>(pBuff_),unBuffSize_,0)) == SOCKET_ERROR)
	{
		__DtTestPoint(__DtFunc__Recv, __DtStep_1)
		this->m_nLastError = ::WSAGetLastError();
		__DtTestPoint( __DtFunc__Recv, __DtStep_2 )
		return 0;
	}

	//以下組立処理
	if(this->m_vcRecvBuffer.capacity() < this->m_unSaveSize + nRecvSize)
		this->m_vcRecvBuffer.resize(this->m_unSaveSize + nRecvSize);

	//保存バッファに受信分をコピー
	::memcpy_s(&this->m_vcRecvBuffer[this->m_unSaveSize],this->m_vcRecvBuffer.capacity() - this->m_unSaveSize,pBuff_,nRecvSize);
	this->m_unSaveSize += nRecvSize;

	//バッファ分がヘッダサイズ未満の場合、処理を返す
	if(this->m_unSaveSize < sizeof(TransportHeader))
		return 0;

	//ヘッダ解釈
	TransportHeader *pstTransHead = reinterpret_cast<TransportHeader*>(&this->m_vcRecvBuffer[0]);

	bool bRes = false;

	//バッファ分が送信サイズ以上にバッファリングされた場合
	while(pstTransHead->unDataSize + sizeof(TransportHeader) <= this->m_unSaveSize)
	{
		//セッションヘッダによるデータ識別
		__DtTestPoint(__DtFunc__Recv, __DtStep_3)
		bRes |= this->Discernment(&this->m_vcRecvBuffer[sizeof(TransportHeader)],pstTransHead->unDataSize);

		//バッファ分が送信サイズ以上だった場合、次の送信分を受信しているので、バッファの先頭へ移動して保持する
		if(this->m_unSaveSize - sizeof(TransportHeader) - pstTransHead->unDataSize > 0)
			::memcpy_s(&this->m_vcRecvBuffer[0],this->m_vcRecvBuffer.capacity(),&this->m_vcRecvBuffer[sizeof(TransportHeader) + pstTransHead->unDataSize],this->m_unSaveSize - sizeof(TransportHeader) - pstTransHead->unDataSize);

		this->m_unSaveSize = this->m_unSaveSize - sizeof(TransportHeader) - pstTransHead->unDataSize;

		//残ったバッファ分がヘッダサイズ未満であれば処理しない
		if(this->m_unSaveSize < sizeof(TransportHeader))
			break;

		//ヘッダ解釈
		TransportHeader *pstTransHead = reinterpret_cast<TransportHeader*>(&this->m_vcRecvBuffer[0]);
	}

	//TotalRecvSizeは、ヘッダサイズなどを含めた全受信バイト数
	this->m_ullTotalRecvSize += nRecvSize;

	__DtTestPoint( __DtFunc__Recv, __DtStep_4 )
	return (bRes ? nRecvSize : 0);
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Discernment
	
	受信データをセッションヘッダによって識別し、処理する
	
	@param[in]      void   *pData_ - データ
	@param[in]      size_t unSize_ - 格納先サイズ 
	@return         bool
	- true  SSF_SEND
	- false その他
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpStream::Discernment(void *pData_,size_t unSize_)
{
	bool bRes = false;
	SessionHeader *pstSesHead = reinterpret_cast<SessionHeader*>(pData_);

	__DtTestPoint( __DtFunc_Discernment, __DtStep_0 )
	switch(pstSesHead->ucSessionBit)
	{
	case SSF_UNDEF:
		__DtTestPoint(__DtFunc_Discernment, __DtStep_1)
		break;

	case SSF_SEND:
		//受信リストに追加
		__DtTestPoint(__DtFunc_Discernment, __DtStep_2)
		this->m_liRecvList.push_back(new Packet(&reinterpret_cast<const char*>(pData_)[sizeof(SessionHeader)],unSize_ - sizeof(SessionHeader)));
		::PostMessage(SocketManager::getInstance()->getHWnd(),SocketManager::getInstance()->getMsg(),SM_RECV,this->m_unSockID);
		bRes = true;
		break;

	case SSF_PING:
		{
			//Pingに対して応答する
			TransportHeader stTransHead;
			SessionHeader stSessionHead;
			char byBuf[sizeof(stTransHead) + sizeof(stSessionHead)];

			__DtTestPoint(__DtFunc_Discernment, __DtStep_3)
			::memset(&stTransHead,NULL,sizeof(stTransHead));
			::memset(&stSessionHead,NULL,sizeof(stSessionHead));
			::memset(&byBuf[0],NULL,sizeof(byBuf));

			//ヘッダを適当にセット
			stTransHead.unDataSize = sizeof(stSessionHead);
			stSessionHead.ucSessionBit = SSF_PING_RES;
			::memcpy_s(&byBuf[0],sizeof(byBuf),&stTransHead,sizeof(stTransHead));
			::memcpy_s(&byBuf[sizeof(stTransHead)],sizeof(byBuf - sizeof(stTransHead)),&stSessionHead,sizeof(stSessionHead));

			this->m_liSendList.push_front(new Packet(reinterpret_cast<const char*>(&byBuf[0]),sizeof(byBuf)));

			this->m_dwPingSendTime = ::timeGetTime();

			SocketManager::getInstance()->HandleSend();

			bRes = false;
			break;
		}

	case SSF_PING_RES:
		__DtTestPoint(__DtFunc_Discernment, __DtStep_4)
		this->m_eSessionState = SST_ESTABLISHED;
		this->m_dwPingSendTime = ::timeGetTime() - this->m_dwPingSendTime;
		this->m_bSendPing = false;

		bRes = false;
		break;

	default:
		__DtTestPoint(__DtFunc_Discernment, __DtStep_5)
		break;
	}

	__DtTestPoint( __DtFunc_Discernment, __DtStep_6 )
	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::TimerProc
	
	タイマーが呼ばれるごとに行われる処理
	
	@param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void TcpStream::TimerProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
{
	__DtTestPoint( __DtFunc_TimerProc, __DtStep_0 )
	this->TcpSocket::TimerProc(hWnd_,unMsg_,wParam_,lParam_);

	//セッションが確立している場合、定期的に応答要求を送信する
	if(this->m_eSessionState == SST_ESTABLISHED)
	{
		//まだ応答要求を発信していない
		__DtTestPoint(__DtFunc_TimerProc, __DtStep_1)
		if(!this->m_bSendPing)
		{
			//指定したタイムアウト時間に達したら送信
			__DtTestPoint(__DtFunc_TimerProc, __DtStep_2)
			if(!(this->m_unTime % this->scm_nTimeout))
			{
				TransportHeader stTransHead;
				SessionHeader stSessionHead;
				char byBuf[sizeof(stTransHead) + sizeof(stSessionHead)];

				__DtTestPoint(__DtFunc_TimerProc, __DtStep_3)
				::memset(&stTransHead,NULL,sizeof(stTransHead));
				::memset(&stSessionHead,NULL,sizeof(stSessionHead));
				::memset(&byBuf[0],NULL,sizeof(byBuf));

				//ヘッダを適当にセット
				stTransHead.unDataSize = sizeof(stSessionHead);
				stSessionHead.ucSessionBit = SSF_PING;
				::memcpy_s(&byBuf[0],sizeof(byBuf),&stTransHead,sizeof(stTransHead));
				::memcpy_s(&byBuf[sizeof(stTransHead)],sizeof(byBuf - sizeof(stTransHead)),&stSessionHead,sizeof(stSessionHead));

				this->m_liSendList.push_front(new Packet(reinterpret_cast<const char*>(&byBuf[0]),sizeof(byBuf)));

				this->m_dwPingSendTime = ::timeGetTime();
				this->m_bSendPing = true;

				SocketManager::getInstance()->HandleSend();
			}
		}
		//以前の応答要求が返ってきていない場合
		else
		{
			//セッションを閉じるタイムアウト時間まで返ってこなかった場合
			__DtTestPoint(__DtFunc_TimerProc, __DtStep_4)
			if(::timeGetTime() - this->m_dwPingSendTime >= this->scm_nTimeoutClose)
			{
				//強制的にセッションを閉じる
				__DtTestPoint(__DtFunc_TimerProc, __DtStep_5)
				this->m_bSendPing = false;
				this->AsyncClose();
			}
		}
	}

	__DtTestPoint( __DtFunc_TimerProc, __DtStep_6 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Proc
	
	プロシージャ処理
	
	@param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         LRESULT
	@exception      none
*/
//---------------------------------------------------------------------------
LRESULT TcpStream::Proc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
{
	__DtTestPoint( __DtFunc_Proc, __DtStep_0 )
	switch(unMsg_)
	{
	case WM_SOCKET:
		__DtTestPoint(__DtFunc_Proc, __DtStep_1)
		if(static_cast<SOCKET>(wParam_) == this->m_hSock)
		{
			__DtTestPoint(__DtFunc_Proc, __DtStep_2)
			switch(WSAGETSELECTEVENT(lParam_))
			{
			case FD_ACCEPT:
				__DtTestPoint(__DtFunc_Proc, __DtStep_3)
				this->m_nAcceptDemandNum += 1;
				::PostMessage(SocketManager::getInstance()->getHWnd(),SocketManager::getInstance()->getMsg(),SM_ACCEPT,this->m_unSockID);
				break;

			case FD_CONNECT:
				//FD_CONNECTが来た際、経過時間がタイムアウト間隔以内であれば成功
				__DtTestPoint(__DtFunc_Proc, __DtStep_4)
				if(this->m_unConnectTime < this->scm_nTimeout)
				{
					__DtTestPoint(__DtFunc_Proc, __DtStep_5)
					this->m_bConnect = true;
					this->m_eSessionState = SST_ESTABLISHED;
					::PostMessage(SocketManager::getInstance()->getHWnd(),SocketManager::getInstance()->getMsg(),SM_CONNECT,this->m_unSockID);
				}
				else
				{
					__DtTestPoint(__DtFunc_Proc, __DtStep_6)
					this->m_bConnect = false;
					this->m_eSessionState = SST_FAILED;
					this->AsyncClose();
				}
				break;

			case FD_WRITE:
				__DtTestPoint(__DtFunc_Proc, __DtStep_7)
				break;

			case FD_READ:
				__DtTestPoint(__DtFunc_Proc, __DtStep_8)
				::memset(&SocketManager::getInstance()->getRecvBuffer()[0],NULL,SocketManager::getInstance()->getRecvBuffer().capacity());
				this->_Recv(&SocketManager::getInstance()->getRecvBuffer()[0],SocketManager::getInstance()->getRecvBuffer().capacity());
				break;

			case FD_CLOSE:
				__DtTestPoint(__DtFunc_Proc, __DtStep_9)
				this->AsyncClose();
				::PostMessage(SocketManager::getInstance()->getHWnd(),SocketManager::getInstance()->getMsg(),SM_CLOSE,this->m_unSockID);
				break;

			default:
				__DtTestPoint(__DtFunc_Proc, __DtStep_10)
				break;
			}
		}
		break;

	case WM_TIMER:
		__DtTestPoint(__DtFunc_Proc, __DtStep_11)
		if(wParam_ == this->m_unTimerID)
		{
			__DtTestPoint(__DtFunc_Proc, __DtStep_12)
			this->TimerProc(hWnd_,unMsg_,wParam_,lParam_);
		}
		break;

	default:
		__DtTestPoint(__DtFunc_Proc, __DtStep_13)
		break;
	}

	__DtTestPoint( __DtFunc_Proc, __DtStep_14 )
	return 0;
}


//=============================================================================
//								End of File
//=============================================================================