//=============================================================================
/*! 
    @addtogroup 
    @file       SocketBase.h
    @brief      SocketBase�N���X�w�b�_
    
    �\�P�b�g�̊��N���X
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/09/01
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/09/01 Hi-ra Mizuno
      -# �쐬
	- 2011/10/19 Hi-ra Mizuno
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_SOCKETBASE_H__
#define __INCLUDE_SOCKETBASE_H__


/*! @par include */
#include <winsock2.h>
#include <windows.h>
#include <list>
#include "./Typedef.h"
#include "./Packet.h"
#include "./Common/PointerList.h"


/*! @par pragma */
#pragma comment(lib,"ws2_32.lib")


/*! @par prototype */
class SocketManager;


/*! @class SocketBase
	@brief SocketBase�N���X

	�\�P�b�g�̊��N���X
*/
class SocketBase
{
	friend SocketManager;

public:
	/*! @par public�����o�ϐ� */

protected:
	/*! @par protected�����o�ϐ� */
	static const int scm_nTimerIntv = 1000; //�^�C�}�[�Ԋu(ms)

	SOCKET m_hSock;
	SOCKID m_unSockID;
	sockaddr_in m_stMyAddrParam;
	sockaddr_in m_stOthAddrParam;

	Protocol m_eProtocol;

	bool m_bBind;
	bool m_bListen;
	bool m_bConnect;

	unsigned int m_unOldSendSize;
	unsigned int m_unOldRecvSize;
	unsigned int m_unSendSizePerSecond;
	unsigned int m_unRecvSizePerSecond;

	unsigned long long m_ullTotalSendSize;
	unsigned long long m_ullTotalRecvSize;

	PointerList<Packet*> m_liSendList;
	PointerList<Packet*> m_liRecvList;

	unsigned int m_unTime; //�I�u�W�F�N�g����������Ă���̌o�ߎ���

	UINT_PTR m_unTimerID;

	int m_nLastError;


private:
	/*! @par private�����o�ϐ� */


public:
	/*! @par ��O���� */


public:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::SocketBase
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	SocketBase();

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::~SocketBase
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~SocketBase();

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	SOCKET getSock() const {return this->m_hSock;}

	SOCKET getSockID() const {return this->m_unSockID;}

	const sockaddr_in& getMyAddrParam() const {return this->m_stMyAddrParam;}

	sockaddr_in& getOthAddrParam() {return this->m_stOthAddrParam;}

	Protocol getProtocol() const {return this->m_eProtocol;}

	bool getBind() const {return this->m_bBind;}

	bool getListen() const {return this->m_bListen;}

	bool getConnect() const {return this->m_bConnect;}

	unsigned int getSendSizePerSecond() const {return this->m_unSendSizePerSecond;}

	unsigned int getRecvSizePerSecond() const {return this->m_unRecvSizePerSecond;}

	unsigned long long getTotalSendSize() const {return this->m_ullTotalSendSize;}

	unsigned long long getTotalRecvSize() const {return this->m_ullTotalRecvSize;}

	PointerList<Packet*>& getRecvList() {return this->m_liRecvList;}

	UINT_PTR getTimetID() const {return this->m_unTimerID;}

	int getLastError() const {return this->m_nLastError;}

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	void setSockID(SOCKID unSockID_) {this->m_unSockID = unSockID_;}

protected:
	/*! @par protected�����o�֐� */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Initialize
	
		����������
	
		@param[in]      SOCKET hSock_ �����\�P�b�g�n���h�� 
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Initialize(SOCKET hSock_ = INVALID_SOCKET) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Release
	
		�I������
	
		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Release() = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Close
	
		�ʐM��ؒf����
	
		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Close() = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::AsyncClose
	
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
	virtual bool AsyncClose() = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Bind
	
		�w�肳�ꂽ�|�[�g�Ƀo�C���h����
	
		@param[in]      PORT usPort_ - �|�[�g�ԍ�
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Bind(PORT usPort_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Connect
	
		�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�
	
		@param[in]      IPv4L ulAddr_ - �ڑ���IP�A�h���X(IPv4)
		@param[in]      PORT  usPort_ - �ڑ���|�[�g�ԍ�
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Connect(IPv4L ulAddr_,PORT usPort_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Connect
	
		�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�
	
		@param[in]      IPv4A pszAddr_ - �ڑ���IP�A�h���X(IPv4)
		@param[in]      PORT  usPort_  - �ڑ���|�[�g�ԍ�
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Connect(IPv4A pszAddr_,PORT usPort_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Connect
	
		�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�
	
		@param[in]      IPv4W pwszAddr_ - �ڑ���IP�A�h���X(IPv4)
		@param[in]      PORT  usPort_   - �ڑ���|�[�g�ԍ�
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Connect(IPv4W pwszAddr_,PORT usPort_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Connect
	
		�w�肳�ꂽIP�A�h���X�ɑ΂��Đڑ������݂�
	
		@param[in]      sockaddr_in stAddr_ - �ڑ�����
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Connect(sockaddr_in stAddr_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Send
	
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
	virtual int Send(const void *c_pData_,size_t unSize_,bool bPriority_ = false) = 0;

protected:
	/*! @par protected�����o�֐� */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::_Send
	
		�f�[�^�𑗐M����
	
		@param[in]      void
		@return         int
		- 0     ����
		- 0�ȊO �G���[�R�[�h
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual int _Send() = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::_Recv
	
		�f�[�^����M����
	
		@param[in]      void   *pBuff      - �f�[�^�i�[��|�C���^
		@param[in]      size_t unBuffSize_ - �i�[��T�C�Y 
		@return         int
		- ��M�f�[�^�T�C�Y(Byte)
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual int _Recv(void *pBuff_,size_t unBuffSize_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Proc
	
		�v���V�[�W������
	
	    @param[in]      HWND         hWnd_
		@param[in]      unsigned int unMsg_
		@param[in]      WPARAM       wParam_
		@param[in]      LPARAM       lParam_
	    @return         LRESULT
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual LRESULT Proc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_) = 0;

private:
	/*! @par private�����o�֐� */

};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================