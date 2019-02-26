//=============================================================================
/*! 
    @addtogroup 
    @file       TcpStream.cpp
    @brief      TcpStream�N���X�̎���
    
    �p�P�b�g�̕����E�g����A�Z�b�V�����̊Ǘ����s��
    
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
      -# �쐬
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
	
	�f�t�H���g�R���X�g���N�^
	
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
	
	�f�X�g���N�^
	
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
	
	����������
	
	@param[in]      SOCKET hSock_ �����\�P�b�g�n���h�� 
	@return         bool
	- true  ����
	- false ���s
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
	
	�I������
	
	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
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
	
	�ʐM��ؒf����
	
	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
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
	
	�ʐM����Ɠ�������炸�A�����I�Ƀ\�P�b�g�����
	
	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
	@note
		- ���E����܂���B
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
	
	�\�P�b�g��ڑ��ҋ@��Ԃɂ���
	
	@param[in]      int nMaxConnect_ - �ő�ڑ���t��
	@return         bool
	- true  ����
	- false ���s
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
	
	�ڑ��v�����󗝂���
	
	@param[in]      TcpStream **ppCNewStream_ �ڑ��v�����󗝂���V�����|�C���^
	@return         bool
	- true  ����
	- false ���s
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
	
	�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�
	
	@param[in]      IPv4L ulAddr_ - �ڑ���IP�A�h���X(IPv4)
	@param[in]      PORT  usPort_ - �ڑ���|�[�g�ԍ�
	@return         bool
	- true  ����
	- false ���s
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
	
	�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�
	
	@param[in]      IPv4A pszAddr_ - �ڑ���IP�A�h���X(IPv4)
	@param[in]      PORT  usPort_  - �ڑ���|�[�g�ԍ�
	@return         bool
	- true  ����
	- false ���s
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
	
	�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�
	
	@param[in]      IPv4W pwszAddr_ - �ڑ���IP�A�h���X(IPv4)
	@param[in]      PORT  usPort_   - �ڑ���|�[�g�ԍ�
	@return         bool
	- true  ����
	- false ���s
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
	
	�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�
	
	@param[in]      sockaddr_in stAddr_ - �ڑ�����
	@return         bool
	- true  ����
	- false ���s
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
	
	�f�[�^�𑗐M���X�g�ɒǉ�����
	
	@param[in]      const void *c_pData_  - �f�[�^
	@param[in]      size_t     unSize_    - �f�[�^�T�C�Y
	@param[in]      bool       bPriority_ - �D�悵�đ��M����
	@return         int
	- 0     ����
	- 0�ȊO �G���[�R�[�h
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

	//�w�b�_��K���ɃZ�b�g����
	stTransHead.unDataSize = unSize_ + sizeof(stSessionHead);
	stSessionHead.ucSessionBit = SSF_SEND;

	//���M�o�b�t�@�����T�C�Y
	if(this->m_vcSendBuffer.capacity() < sizeof(stTransHead) + sizeof(stSessionHead) + unSize_)
		this->m_vcSendBuffer.resize(sizeof(stTransHead) + sizeof(stSessionHead) + unSize_);

	//���M�o�b�t�@�Ƀw�b�_�ƃf�[�^���Z�b�g
	::memcpy_s(&this->m_vcSendBuffer[0],this->m_vcSendBuffer.capacity(),&stTransHead,sizeof(stTransHead));
	::memcpy_s(&this->m_vcSendBuffer[sizeof(stTransHead)],this->m_vcSendBuffer.capacity() - sizeof(stTransHead),&stSessionHead,sizeof(stSessionHead));
	::memcpy_s(&this->m_vcSendBuffer[sizeof(stTransHead) + sizeof(stSessionHead)],this->m_vcSendBuffer.capacity() - sizeof(stTransHead) - sizeof(stSessionHead),c_pData_,unSize_);

	//���M���X�g�ɒǉ�
	bPriority_ ? this->m_liSendList.push_front(new Packet(reinterpret_cast<const char*>(&this->m_vcSendBuffer[0]),sizeof(stTransHead) + sizeof(stSessionHead) + unSize_)) : this->m_liSendList.push_back(new Packet(reinterpret_cast<const char*>(&this->m_vcSendBuffer[0]),sizeof(stTransHead) + sizeof(stSessionHead) + unSize_));

	SocketManager::getInstance()->HandleSend();

	__DtTestPoint( __DtFunc_Send, __DtStep_1 )
	return 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::_Recv
	
	�f�[�^����M����
	
	@param[in]      void   *pBuff      - �f�[�^�i�[��|�C���^
	@param[in]      size_t unBuffSize_ - �i�[��T�C�Y 
	@return         int
	- ��M�f�[�^�T�C�Y(Byte)
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

	//�ȉ��g������
	if(this->m_vcRecvBuffer.capacity() < this->m_unSaveSize + nRecvSize)
		this->m_vcRecvBuffer.resize(this->m_unSaveSize + nRecvSize);

	//�ۑ��o�b�t�@�Ɏ�M�����R�s�[
	::memcpy_s(&this->m_vcRecvBuffer[this->m_unSaveSize],this->m_vcRecvBuffer.capacity() - this->m_unSaveSize,pBuff_,nRecvSize);
	this->m_unSaveSize += nRecvSize;

	//�o�b�t�@�����w�b�_�T�C�Y�����̏ꍇ�A������Ԃ�
	if(this->m_unSaveSize < sizeof(TransportHeader))
		return 0;

	//�w�b�_����
	TransportHeader *pstTransHead = reinterpret_cast<TransportHeader*>(&this->m_vcRecvBuffer[0]);

	bool bRes = false;

	//�o�b�t�@�������M�T�C�Y�ȏ�Ƀo�b�t�@�����O���ꂽ�ꍇ
	while(pstTransHead->unDataSize + sizeof(TransportHeader) <= this->m_unSaveSize)
	{
		//�Z�b�V�����w�b�_�ɂ��f�[�^����
		__DtTestPoint(__DtFunc__Recv, __DtStep_3)
		bRes |= this->Discernment(&this->m_vcRecvBuffer[sizeof(TransportHeader)],pstTransHead->unDataSize);

		//�o�b�t�@�������M�T�C�Y�ȏゾ�����ꍇ�A���̑��M������M���Ă���̂ŁA�o�b�t�@�̐擪�ֈړ����ĕێ�����
		if(this->m_unSaveSize - sizeof(TransportHeader) - pstTransHead->unDataSize > 0)
			::memcpy_s(&this->m_vcRecvBuffer[0],this->m_vcRecvBuffer.capacity(),&this->m_vcRecvBuffer[sizeof(TransportHeader) + pstTransHead->unDataSize],this->m_unSaveSize - sizeof(TransportHeader) - pstTransHead->unDataSize);

		this->m_unSaveSize = this->m_unSaveSize - sizeof(TransportHeader) - pstTransHead->unDataSize;

		//�c�����o�b�t�@�����w�b�_�T�C�Y�����ł���Ώ������Ȃ�
		if(this->m_unSaveSize < sizeof(TransportHeader))
			break;

		//�w�b�_����
		TransportHeader *pstTransHead = reinterpret_cast<TransportHeader*>(&this->m_vcRecvBuffer[0]);
	}

	//TotalRecvSize�́A�w�b�_�T�C�Y�Ȃǂ��܂߂��S��M�o�C�g��
	this->m_ullTotalRecvSize += nRecvSize;

	__DtTestPoint( __DtFunc__Recv, __DtStep_4 )
	return (bRes ? nRecvSize : 0);
}


//---------------------------------------------------------------------------
/*! 
	@brief TcpStream::Discernment
	
	��M�f�[�^���Z�b�V�����w�b�_�ɂ���Ď��ʂ��A��������
	
	@param[in]      void   *pData_ - �f�[�^
	@param[in]      size_t unSize_ - �i�[��T�C�Y 
	@return         bool
	- true  SSF_SEND
	- false ���̑�
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
		//��M���X�g�ɒǉ�
		__DtTestPoint(__DtFunc_Discernment, __DtStep_2)
		this->m_liRecvList.push_back(new Packet(&reinterpret_cast<const char*>(pData_)[sizeof(SessionHeader)],unSize_ - sizeof(SessionHeader)));
		::PostMessage(SocketManager::getInstance()->getHWnd(),SocketManager::getInstance()->getMsg(),SM_RECV,this->m_unSockID);
		bRes = true;
		break;

	case SSF_PING:
		{
			//Ping�ɑ΂��ĉ�������
			TransportHeader stTransHead;
			SessionHeader stSessionHead;
			char byBuf[sizeof(stTransHead) + sizeof(stSessionHead)];

			__DtTestPoint(__DtFunc_Discernment, __DtStep_3)
			::memset(&stTransHead,NULL,sizeof(stTransHead));
			::memset(&stSessionHead,NULL,sizeof(stSessionHead));
			::memset(&byBuf[0],NULL,sizeof(byBuf));

			//�w�b�_��K���ɃZ�b�g
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
	
	�^�C�}�[���Ă΂�邲�Ƃɍs���鏈��
	
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

	//�Z�b�V�������m�����Ă���ꍇ�A����I�ɉ����v���𑗐M����
	if(this->m_eSessionState == SST_ESTABLISHED)
	{
		//�܂������v���𔭐M���Ă��Ȃ�
		__DtTestPoint(__DtFunc_TimerProc, __DtStep_1)
		if(!this->m_bSendPing)
		{
			//�w�肵���^�C���A�E�g���ԂɒB�����瑗�M
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

				//�w�b�_��K���ɃZ�b�g
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
		//�ȑO�̉����v�����Ԃ��Ă��Ă��Ȃ��ꍇ
		else
		{
			//�Z�b�V���������^�C���A�E�g���Ԃ܂ŕԂ��Ă��Ȃ������ꍇ
			__DtTestPoint(__DtFunc_TimerProc, __DtStep_4)
			if(::timeGetTime() - this->m_dwPingSendTime >= this->scm_nTimeoutClose)
			{
				//�����I�ɃZ�b�V���������
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
	
	�v���V�[�W������
	
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
				//FD_CONNECT�������ہA�o�ߎ��Ԃ��^�C���A�E�g�Ԋu�ȓ��ł���ΐ���
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