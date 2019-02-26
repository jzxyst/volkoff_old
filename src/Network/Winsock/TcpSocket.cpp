//=============================================================================
/*! 
    @addtogroup 
    @file       TcpSocket.cpp
    @brief      TcpSocket�N���X�̎���
    
    TCP�\�P�b�g�N���X
    
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
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_TcpSocket.h"	/* For DynamicTracer-TestPoint */
#include "./SocketManager.h"
#include "./TcpSocket.h"


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::TcpSocket

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
TcpSocket::TcpSocket()
{
	__DtTestPoint( __DtFunc_TcpSocket, __DtStep_0 )
	this->m_nAcceptDemandNum = 0;
	this->m_unConnectTime = 0;
	this->m_bConnectting = false;
	__DtTestPoint( __DtFunc_TcpSocket, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::~TcpSocket

	�f�X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
TcpSocket::~TcpSocket()
{
	//���̃^�C�~���O�ł܂��Z�b�V�������c���Ă���ꍇ�A�����I�ɒʐM��ؒf����
	__DtTestPoint( __DtFunc_TcpSocket, __DtStep_2 )
	if(this->m_hSock != INVALID_SOCKET)
	{
		__DtTestPoint(__DtFunc_TcpSocket, __DtStep_3)
		this->AsyncClose();
	}

	this->Release();
	__DtTestPoint( __DtFunc_TcpSocket, __DtStep_4 )
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Initialize

	����������

	@param[in]      SOCKET hSock_ �����\�P�b�g�n���h�� 
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Initialize(SOCKET hSock_)
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	//�����o�����l���
	this->m_eProtocol = PRT_TCP;
	this->m_nAcceptDemandNum = 0;
	this->m_unConnectTime = 0;
	this->m_bConnectting = false;

	this->m_hSock = hSock_;

	//�\�P�b�g�̍쐬
	if(this->m_hSock == INVALID_SOCKET)
	{
		__DtTestPoint(__DtFunc_Initialize, __DtStep_1)
		if((this->m_hSock = ::WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,0)) == INVALID_SOCKET)
		{
			__DtTestPoint(__DtFunc_Initialize, __DtStep_2)
			this->m_nLastError = ::WSAGetLastError();
			__DtTestPoint( __DtFunc_Initialize, __DtStep_3 )
			return false;
		}
	}

	//�\�P�b�g��񓯊���
	if(::WSAAsyncSelect(this->m_hSock,SocketManager::getInstance()->getHWnd(),WM_SOCKET,FD_ACCEPT | FD_CONNECT | FD_WRITE | FD_READ | FD_CLOSE) == SOCKET_ERROR)
	{
		__DtTestPoint(__DtFunc_Initialize, __DtStep_4)
		this->m_nLastError = ::WSAGetLastError();
		__DtTestPoint( __DtFunc_Initialize, __DtStep_5 )
		return false;
	}

	__DtTestPoint( __DtFunc_Initialize, __DtStep_6 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Release()
{
	bool bRes = false;

	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	if(this->m_hSock != INVALID_SOCKET)
	{
		__DtTestPoint(__DtFunc_Release, __DtStep_1)
		bRes = this->AsyncClose();
	}

	__DtTestPoint( __DtFunc_Release, __DtStep_2 )
	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Close

	�ʐM��ؒf����

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Close()
{
	bool bRes = true;

	__DtTestPoint( __DtFunc_Close, __DtStep_0 )
	if(this->m_hSock != INVALID_SOCKET)
	{
		__DtTestPoint(__DtFunc_Close, __DtStep_1)
		if(::shutdown(this->m_hSock,SD_SEND) == SOCKET_ERROR)
		{
			__DtTestPoint(__DtFunc_Close, __DtStep_2)
			this->m_nLastError = ::WSAGetLastError();
			bRes = false;
		}
	}

	__DtTestPoint( __DtFunc_Close, __DtStep_3 )
	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::AsyncClose

	�ʐM����Ɠ�������炸�A�����I�ɐؒf����

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
	@note
	 - ���E����܂���B
*/
//---------------------------------------------------------------------------
bool TcpSocket::AsyncClose()
{
	bool bRes = true;

	__DtTestPoint( __DtFunc_AsyncClose, __DtStep_0 )
	if(this->m_hSock != INVALID_SOCKET)
	{
		//����M�𖳌��ɂ���
		__DtTestPoint(__DtFunc_AsyncClose, __DtStep_1)
		if(::shutdown(this->m_hSock,SD_BOTH) == SOCKET_ERROR)
		{
			__DtTestPoint(__DtFunc_AsyncClose, __DtStep_2)
			this->m_nLastError = ::WSAGetLastError();
			bRes = false;
		}

		//�\�P�b�g�����
		if(::closesocket(this->m_hSock) == SOCKET_ERROR)
		{
			__DtTestPoint(__DtFunc_AsyncClose, __DtStep_3)
			this->m_nLastError = ::WSAGetLastError();
			bRes = false;
		}

		this->m_hSock = INVALID_SOCKET;

		this->m_bConnect = false;
		this->m_bListen = false;
		this->m_bBind = false;
	}

	__DtTestPoint( __DtFunc_AsyncClose, __DtStep_4 )
	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Bind

	�w�肳�ꂽ�|�[�g�Ƀo�C���h����

	@param[in]      PORT usPort_ - �|�[�g�ԍ�
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Bind(PORT usPort_)
{
	__DtTestPoint( __DtFunc_Bind, __DtStep_0 )
	this->m_stMyAddrParam.sin_family = AF_INET;
	this->m_stMyAddrParam.sin_port = ::htons(usPort_);
	this->m_stMyAddrParam.sin_addr.S_un.S_addr = INADDR_ANY;

	if(::bind(this->m_hSock,reinterpret_cast<sockaddr*>(&this->m_stMyAddrParam),sizeof(this->m_stMyAddrParam)) == SOCKET_ERROR)
	{
		__DtTestPoint(__DtFunc_Bind, __DtStep_1)
		this->m_nLastError = ::WSAGetLastError();
		__DtTestPoint( __DtFunc_Bind, __DtStep_2 )
		return false;
	}

	__DtTestPoint( __DtFunc_Bind, __DtStep_3 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Listen

	�\�P�b�g��ڑ��ҋ@��Ԃɂ���

	@param[in]      int nMaxConnect_ - �ő�ڑ���t��
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Listen(int nMaxConnect_)
{
	__DtTestPoint( __DtFunc_Listen, __DtStep_0 )
	if(::listen(this->m_hSock,nMaxConnect_) == SOCKET_ERROR)
	{
		__DtTestPoint(__DtFunc_Listen, __DtStep_1)
		this->m_nLastError = ::WSAGetLastError();
		__DtTestPoint( __DtFunc_Listen, __DtStep_2 )
		return false;
	}

	__DtTestPoint( __DtFunc_Listen, __DtStep_3 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Accept
	
	�ڑ��v�����󗝂���
	
	@param[in]      TcpSocket **ppCNewSocket_ �ڑ��v�����󗝂���\�P�b�g�|�C���^�̃|�C���^
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Accept(TcpSocket **ppCNewSocket_)
{
	SOCKET hSock = INVALID_SOCKET;

	__DtTestPoint( __DtFunc_Accept, __DtStep_0 )
	*ppCNewSocket_ = new TcpSocket();
	int nLen = sizeof((*ppCNewSocket_)->getOthAddrParam());

	//::WSAAccept
	if((hSock = ::accept(this->m_hSock,reinterpret_cast<sockaddr*>(&(*ppCNewSocket_)->getOthAddrParam()),&nLen)) == INVALID_SOCKET)
	{
		__DtTestPoint(__DtFunc_Accept, __DtStep_1)
		this->m_nLastError = ::WSAGetLastError();
		__DtTestPoint( __DtFunc_Accept, __DtStep_2 )
		return false;
	}

	if(!(*ppCNewSocket_)->Initialize(hSock))
	{
		__DtTestPoint(__DtFunc_Accept, __DtStep_3)
		SAFE_DELETE(*ppCNewSocket_);
		__DtTestPoint( __DtFunc_Accept, __DtStep_4 )
		return false;
	}

	(*ppCNewSocket_)->m_bConnect = true;

	this->m_nAcceptDemandNum -= 1;

	__DtTestPoint( __DtFunc_Accept, __DtStep_5 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Connect

	�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�

	@param[in]      IPv4L ulAddr_ - �ڑ���IP�A�h���X(IPv4)
	@param[in]      PORT  usPort_ - �ڑ���|�[�g�ԍ�
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Connect(IPv4L ulAddr_,PORT usPort_)
{
	__DtTestPoint( __DtFunc_Connect, __DtStep_0 )
	this->m_stOthAddrParam.sin_family = AF_INET;
	this->m_stOthAddrParam.sin_port = ::htons(usPort_);
	this->m_stOthAddrParam.sin_addr.S_un.S_addr = ::ntohl(ulAddr_);

	//::WSAConnect
	if((::connect(this->m_hSock,reinterpret_cast<sockaddr*>(&this->m_stOthAddrParam),sizeof(this->m_stOthAddrParam))) == SOCKET_ERROR)
	{
		int nError = ::WSAGetLastError();
		__DtTestPoint(__DtFunc_Connect, __DtStep_1)
		if(nError != WSAEWOULDBLOCK)
		{
			__DtTestPoint(__DtFunc_Connect, __DtStep_2)
			this->m_nLastError = nError;
			__DtTestPoint( __DtFunc_Connect, __DtStep_3 )
			return false;
		}
	}

	this->m_bConnectting = true;

	__DtTestPoint( __DtFunc_Connect, __DtStep_4 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Connect

	�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�

	@param[in]      IPv4A pszAddr_ - �ڑ���IP�A�h���X(IPv4)
	@param[in]      PORT  usPort_  - �ڑ���|�[�g�ԍ�
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Connect(IPv4A pszAddr_,PORT usPort_)
{
	__DtTestPoint( __DtFunc_Connect, __DtStep_5 )
	this->m_stOthAddrParam.sin_family = AF_INET;
	this->m_stOthAddrParam.sin_port = ::htons(usPort_);
	this->m_stOthAddrParam.sin_addr.S_un.S_addr = ::inet_addr(pszAddr_);

	//::WSAConnect
	if((::connect(this->m_hSock,reinterpret_cast<sockaddr*>(&this->m_stOthAddrParam),sizeof(this->m_stOthAddrParam))) == SOCKET_ERROR)
	{
		int nError = ::WSAGetLastError();
		__DtTestPoint(__DtFunc_Connect, __DtStep_6)
		if(nError != WSAEWOULDBLOCK)
		{
			__DtTestPoint(__DtFunc_Connect, __DtStep_7)
			this->m_nLastError = nError;
			__DtTestPoint( __DtFunc_Connect, __DtStep_8 )
			return false;
		}
	}

	this->m_bConnectting = true;

	__DtTestPoint( __DtFunc_Connect, __DtStep_9 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Connect

	�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�

	@param[in]      IPv4W pwszAddr_ - �ڑ���IP�A�h���X(IPv4)
	@param[in]      PORT  usPort_   - �ڑ���|�[�g�ԍ�
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Connect(IPv4W pwszAddr_,PORT usPort_)
{
	char szAddr[64];
	size_t unLength = 0;

	__DtTestPoint( __DtFunc_Connect, __DtStep_10 )
	if(::wcstombs_s(&unLength,szAddr,sizeof(szAddr),pwszAddr_,_TRUNCATE))
		return false;

	this->m_stOthAddrParam.sin_family = AF_INET;
	this->m_stOthAddrParam.sin_port = ::htons(usPort_);
	this->m_stOthAddrParam.sin_addr.S_un.S_addr = ::inet_addr(szAddr);

	//::WSAConnect
	if((::connect(this->m_hSock,reinterpret_cast<sockaddr*>(&this->m_stOthAddrParam),sizeof(this->m_stOthAddrParam))) == SOCKET_ERROR)
	{
		int nError = ::WSAGetLastError();
		__DtTestPoint(__DtFunc_Connect, __DtStep_11)
		if(nError != WSAEWOULDBLOCK)
		{
			__DtTestPoint(__DtFunc_Connect, __DtStep_12)
			this->m_nLastError = nError;
			__DtTestPoint( __DtFunc_Connect, __DtStep_13 )
			return false;
		}
	}

	this->m_bConnectting = true;

	__DtTestPoint( __DtFunc_Connect, __DtStep_14 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Connect

	�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�

	@param[in]      sockaddr_in stAddr_ - �ڑ�����
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool TcpSocket::Connect(sockaddr_in stAddr_)
{
	__DtTestPoint( __DtFunc_Connect, __DtStep_15 )
	this->m_stOthAddrParam = stAddr_;

	//::WSAConnect
	if((::connect(this->m_hSock,reinterpret_cast<sockaddr*>(&this->m_stOthAddrParam),sizeof(this->m_stOthAddrParam))) == SOCKET_ERROR)
	{
		int nError = ::WSAGetLastError();
		__DtTestPoint(__DtFunc_Connect, __DtStep_16)
		if(nError != WSAEWOULDBLOCK)
		{
			__DtTestPoint(__DtFunc_Connect, __DtStep_17)
			this->m_nLastError = nError;
			__DtTestPoint( __DtFunc_Connect, __DtStep_18 )
			return false;
		}
	}

	this->m_bConnectting = true;

	__DtTestPoint( __DtFunc_Connect, __DtStep_19 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Send

	�f�[�^�𑗐M����

	@param[in]      const void *c_pData_  - �f�[�^
	@param[in]      size_t     unSize_    - �f�[�^�T�C�Y 
	@param[in]      bool       bPriority_ - �D�悵�đ��M����
	@return         int
	- 0     ����
	- 0�ȊO �G���[�R�[�h
	@exception      none
*/
//---------------------------------------------------------------------------
int TcpSocket::Send(const void *c_pData_,size_t unSize_,bool bPriority_)
{
	__DtTestPoint( __DtFunc_Send, __DtStep_0 )
	bPriority_ ? this->m_liSendList.push_front(new Packet(reinterpret_cast<const char*>(c_pData_),unSize_)) : this->m_liSendList.push_back(new Packet(reinterpret_cast<const char*>(c_pData_),unSize_));

	SocketManager::getInstance()->HandleSend();

	__DtTestPoint( __DtFunc_Send, __DtStep_1 )
	return 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::_Send
	
	�f�[�^�𑗐M����
	
	@param[in]      void
	@return         int
	- 0     ����
	- 0�ȊO �G���[�R�[�h
	@exception      none
*/
//---------------------------------------------------------------------------
int TcpSocket::_Send()
{
	int nCheck = 0;

	//::WSASend
	__DtTestPoint( __DtFunc__Send, __DtStep_0 )
	if(this->m_bConnect)
	{
		__DtTestPoint(__DtFunc__Send, __DtStep_1)
		if(!this->m_liSendList.empty())
		{
			__DtTestPoint(__DtFunc__Send, __DtStep_2)
			if((nCheck = ::send(this->m_hSock,this->m_liSendList.front()->getData(),this->m_liSendList.front()->getSize(),0)) == SOCKET_ERROR)
			{
				__DtTestPoint(__DtFunc__Send, __DtStep_3)
				this->m_nLastError = ::WSAGetLastError();
				__DtTestPoint( __DtFunc__Send, __DtStep_4 )
				return this->m_nLastError;
			}
		}
	}

	this->m_ullTotalSendSize += this->m_liSendList.front()->getSize();

	this->m_liSendList.pop_front();

	__DtTestPoint( __DtFunc__Send, __DtStep_5 )
	return 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::_Recv
	
	�f�[�^����M����
	
	@param[in]      void   *pBuff      - �f�[�^�i�[��|�C���^
	@param[in]      size_t unBuffSize_ - �i�[��T�C�Y 
	@return         int
	- ��M�f�[�^�T�C�Y(Byte)
	@exception      none
*/
//---------------------------------------------------------------------------
int TcpSocket::_Recv(void *pBuff_,size_t unBuffSize_)
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

	this->m_liRecvList.push_back(new Packet(reinterpret_cast<const char*>(pBuff_),nRecvSize));

	this->m_ullTotalRecvSize += nRecvSize;

	::PostMessage(SocketManager::getInstance()->getHWnd(),SocketManager::getInstance()->getMsg(),SM_RECV,this->m_unSockID);

	__DtTestPoint( __DtFunc__Recv, __DtStep_3 )
	return nRecvSize;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::TimerProc
	
	�^�C�}�[���Ă΂�邲�Ƃɍs���鏈��
	
	@param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void TcpSocket::TimerProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
{
	__DtTestPoint( __DtFunc_TimerProc, __DtStep_0 )
	this->m_unTime += this->scm_nTimerIntv;

	if(this->m_bConnectting)
		this->m_unConnectTime += this->scm_nTimerIntv;

	//���b�̑���M�ʂ�ێ�����
	this->m_unSendSizePerSecond = static_cast<unsigned int>(this->m_ullTotalSendSize - this->m_unOldSendSize);
	this->m_unRecvSizePerSecond = static_cast<unsigned int>(this->m_ullTotalRecvSize - this->m_unOldRecvSize);
	this->m_unOldSendSize = static_cast<unsigned int>(this->m_ullTotalSendSize);
	this->m_unOldRecvSize = static_cast<unsigned int>(this->m_ullTotalRecvSize);

	__DtTestPoint( __DtFunc_TimerProc, __DtStep_1 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpSocket::Proc
	
	�v���V�[�W������
	
	@param[in]      HWND         hWnd_
	@param[in]      unsigned int unMsg_
	@param[in]      WPARAM       wParam_
	@param[in]      LPARAM       lParam_
	@return         LRESULT
	@exception      none
*/
//---------------------------------------------------------------------------
LRESULT TcpSocket::Proc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_)
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
				//FD_CONNECT�������ہA�o�ߎ��Ԃ��^�C���A�E�g�Ԋu�ȓ��ł���ΐ���
				__DtTestPoint(__DtFunc_Proc, __DtStep_4)
				if(this->m_unConnectTime < this->scm_nTimeout)
				{
					__DtTestPoint(__DtFunc_Proc, __DtStep_5)
					this->m_bConnect = true;
					::PostMessage(SocketManager::getInstance()->getHWnd(),SocketManager::getInstance()->getMsg(),SM_CONNECT,this->m_unSockID);
				}
				else
				{
					__DtTestPoint(__DtFunc_Proc, __DtStep_6)
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