//=============================================================================
/*! 
    @addtogroup 
    @file       TcpStream.h
    @brief      TcpStream�N���X�w�b�_
    
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


//Include Guard
#ifndef __INCLUDE_TCPSTREAM_H__
#define __INCLUDE_TCPSTREAM_H__


/*! @par include */
#include "./Winsock/TcpSocket.h"
#include <vector>


/*! @par struct */
typedef struct _TAG_TRANSPORT_HEADER
{
	unsigned int unDataSize; //�g�����X�|�[�g�w�b�_�����܂܂Ȃ����f�[�^�T�C�Y�i�Z�b�V�����w�b�_�͊܂ށj
}TransportHeader;

typedef struct _TAG_SESSION_HEADER
{
	unsigned char ucSessionBit; //�Z�b�V�������C���[�p���ʔԍ�(SessionFuncNo)
}SessionHeader;


/*! @enum SessionFuncNo */
typedef enum _ENUM_SESSION_FUNCTION_NO
{
	SSF_UNDEF = 0, //����`
	SSF_SEND,      //�f�[�^���M
	SSF_PING,      //�����v��
	SSF_PING_RES,  //����
}SessionFuncNo;

/*! @enum SessionParam */
typedef enum _ENUM_SESSION_STATE
{
	SST_UNDEF = 0,   //����`
	SST_NON_CONNECT, //���ڑ�
	SST_LISTEN,      //�ڑ��v���҂�
	SST_CONNECTING,  //�ڑ��v����
	SST_ESTABLISHED, //�ڑ��m��
	SST_FAILED,      //�ڑ����s
	SST_NO_RESPONSE, //�����Ȃ�
	SST_CLOSE        //�ؒf
}SessionState;


/*! @class TcpStream
	@brief TcpStream�N���X

	�p�P�b�g�̕����E�g����A�Z�b�V�����̊Ǘ����s��
*/
class TcpStream : public TcpSocket
{
public:
	/*! @par public�����o�ϐ� */

private:
	/*! @par private�����o�ϐ� */
	static const int scm_nDefRecvBufSize = ETHERNET_MTU;
	static const int scm_nTimeoutClose = 10000; //�^�C���A�E�g�ɂ��Z�b�V��������鎞��(ms)

	std::vector<char> m_vcSendBuffer; //���M�p�o�b�t�@
	std::vector<char> m_vcRecvBuffer; //�ۑ��p�o�b�t�@

	size_t m_unSaveSize;              //�ۑ��p�o�b�t�@�Ɏc���Ă���f�[�^�T�C�Y

	SessionState m_eSessionState;

	DWORD m_dwPing; //�R�l�N�V��������̃��X�|���X�^�C��
	DWORD m_dwPingSendTime; //Ping���Ō�ɑ��M�������ԁi::timeGetiTime�j
	bool m_bSendPing; //Ping�𑗂��Ă���t���O�B�������Ԃ��Ă������_��false�ɖ߂�


public:
	/*! @par ��O���� */


public:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief TcpStream::TcpStream
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	TcpStream();

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpStream::~TcpStream
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~TcpStream();

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	SessionState getSessionState() const {return this->m_eSessionState;}

	DWORD getPing() const {return this->m_dwPing;}

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

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
	bool Initialize(SOCKET hSock_ = INVALID_SOCKET);

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
	bool Release();

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
	bool Close();

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
	bool AsyncClose();

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
	bool Listen(int nMaxConnect_);

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
	bool Accept(TcpStream **ppCNewStream_);

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
	bool Connect(IPv4L ulAddr_,PORT usPort_);

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
	bool Connect(IPv4A pszAddr_,PORT usPort_);

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
	bool Connect(IPv4W pwszAddr_,PORT usPort_);

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
	bool Connect(sockaddr_in stAddr_);

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
	int Send(const void *c_pData_,size_t unSize_,bool bPriority_ = false);

private:
	/*! @par private�����o�֐� */
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
	int _Recv(void *pBuff_,size_t unBuffSize_);

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
	bool Discernment(void *pData_,size_t unSize_);

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
	void TimerProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);

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
	LRESULT Proc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================