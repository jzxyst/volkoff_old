//=============================================================================
/*! 
    @addtogroup 
    @file       TcpSocket.h
    @brief      TcpSocket�N���X�w�b�_
    
    TCP�\�P�b�g�N���X
    
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
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_TCPSOCKET_H__
#define __INCLUDE_TCPSOCKET_H__


/*! @par include */
#include "./SocketBase.h"


/*! @class TcpSocket
	@brief TcpSocket�N���X

	TCP�\�P�b�g�N���X
*/
class TcpSocket : public SocketBase
{
public:
	/*! @par public�����o�ϐ� */

protected:
	/*! @par protected�����o�ϐ� */
	static const int scm_nTimeout = 5000; //�^�C���A�E�g�Ԋu(ms)

	int m_nAcceptDemandNum;
	unsigned int m_unConnectTime; //Connect���Ă�ł���̌o�ߎ���
	bool m_bConnectting;          //Connect���Ă񂾃t���O


public:
	/*! @par ��O���� */


public:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::TcpSocket
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	TcpSocket();

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::~TcpSocket
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~TcpSocket();

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	int getAcceptDemandNum() const {return this->m_nAcceptDemandNum;}

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

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
	bool Initialize(SOCKET hSock_ = INVALID_SOCKET);

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
	bool Release();

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
	bool Close();

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::AsyncClose
	
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
	bool AsyncClose();

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
	bool Bind(PORT usPort_);

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
	bool Listen(int nMaxConnect_);

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
	bool Accept(TcpSocket **ppCNewSocket_);

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
	bool Connect(IPv4L ulAddr_,PORT usPort_);

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
	bool Connect(IPv4A pszAddr_,PORT usPort_);

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
	bool Connect(IPv4W pwszAddr_,PORT usPort_);

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
	bool Connect(sockaddr_in stAddr_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Send
	
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
	int Send(const void *c_pData_,size_t unSize_,bool bPriority_ = false);

protected:
	/*! @par protected�����o�֐� */
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
	int _Send();

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
	int _Recv(void *pBuff_,size_t unBuffSize_);

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
	void TimerProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);

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
	LRESULT Proc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================