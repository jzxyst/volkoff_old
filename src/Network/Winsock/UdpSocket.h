//=============================================================================
/*! 
    @addtogroup 
    @file       UdpSocket.h
    @brief      UdpSocket�N���X�w�b�_
    
    UDP�\�P�b�g�N���X
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/20
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/20 Hi-ra Mizuno
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_UDPSOCKET_H__
#define __INCLUDE_UDPSOCKET_H__


/*! @par include */
#include "./SocketBase.h"


/*! @class UdpSocket
	@brief UdpSocket�N���X

	UDP�\�P�b�g�N���X
*/
class UdpSocket : public SocketBase
{
public:
	/*! @par public�����o�ϐ� */

private:
	/*! @par private�����o�ϐ� */


public:
	/*! @par ��O���� */


public:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief UdpSocket::UdpSocket
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	UdpSocket();

	//---------------------------------------------------------------------------
	/*! 
		@brief UdpSocket::~UdpSocket
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~UdpSocket();

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief UdpSocket::Initialize
	
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
		@brief UdpSocket::Release
	
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
		@brief UdpSocket::Close
	
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
		@brief UdpSocket::AsyncClose
	
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
		@brief UdpSocket::Bind
	
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
		@brief UdpSocket::Connect
	
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
		@brief UdpSocket::Connect
	
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
		@brief UdpSocket::Connect
	
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
		@brief UdpSocket::Connect
	
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
		@brief UdpSocket::Send
	
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

private:
	/*! @par private�����o�֐� */
	//---------------------------------------------------------------------------
	/*! 
		@brief UdpSocket::_Send
	
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
		@brief UdpSocket::_Recv
	
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
		@brief UdpSocket::TimerProc
	
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
		@brief UdpSocket::Proc
	
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