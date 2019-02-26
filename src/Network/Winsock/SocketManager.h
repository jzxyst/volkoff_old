//=============================================================================
/*! 
    @addtogroup 
    @file       SocketManager.h
    @brief      SocketManager�N���X�w�b�_
    
    �\�P�b�g���Ǘ�����N���X
    
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


//Include Guard
#ifndef __INCLUDE_SOCKETMANAGER_H__
#define __INCLUDE_SOCKETMANAGER_H__


/*! @par define */
#define FD_SETSIZE (1024) //�ő�\�P�b�g����ύX����


/*! @par include */
#include "./Common/Singleton.h"
#include "./TcpSocket.h"
#include "./UdpSocket.h"
#include "./Packet.h"
#include <vector>
#include <list>


/*! @par define */
#define WM_SOCKET (WM_APP + 100) //�����p
#define WM_SOCKETEVENT (WM_SOCKET + 100) //���[�U�p


/*! @enum SocketEvent */
typedef enum _ENUM_SOCKET_EVENT
{
	SM_UNDEF = 0,
	SM_ACCEPT,
	SM_CONNECT,
	SM_RECV,
	SM_CLOSE,
}SocketEvent;


/*! @class SocketManager
	@brief SocketManager�N���X

	�\�P�b�g���Ǘ�����N���X
*/
class SocketManager : public Singleton<SocketManager>
{
	friend Singleton<SocketManager>;
	friend SocketBase;

public:
	/*! @par public�����o�ϐ� */

protected:
	/*! @par protected�����o�ϐ� */
	static const int scm_nDefRecvBufSize = ETHERNET_MTU; //�f�t�H���g��M�o�b�t�@�T�C�Y(Byte)
	static const int scm_nSocketNum = FD_SETSIZE;        //�ő�\�P�b�g��

	HWND m_hWnd;
	WSADATA m_stWsaData;
	unsigned int m_unMsg;
	std::list<SocketBase*> m_liSocketList;

	bool m_bSendBufEmpty;
	std::vector<char> m_vcRecvBuffer;

	SOCKID m_unTotalSockID;

public:
	/*! @par ��O���� */


protected:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::SocketManager
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	SocketManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::~SocketManager
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~SocketManager();

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	HWND getHWnd() const {return this->m_hWnd;}

	WSADATA getWsaData() const {return this->m_stWsaData;}

	unsigned int getMsg() const {return this->m_unMsg;}

	std::vector<char>& getRecvBuffer() {return this->m_vcRecvBuffer;}

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	void setHWnd(HWND hWnd_) {this->m_hWnd = hWnd_;}

	void setRecvBufferSize(size_t unBuffSize_) {this->m_vcRecvBuffer.resize(unBuffSize_,NULL);}

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::Initialize
	
		����������
	
		@param[in]      HWND         hWnd_  - �E�B���h�E�n���h��
		@param[in]      unsigned int unMsg_ - �ʒm�E�B���h�E���b�Z�[�W
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize(HWND hWnd_,unsigned int unMsg_ = WM_SOCKETEVENT);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::Release
	
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
		@brief SocketManager::Proc
	
		�v���V�[�W������
	
	    @param[in]      HWND         hWnd_
		@param[in]      unsigned int unMsg_
		@param[in]      WPARAM       wParam_
		@param[in]      LPARAM       lParam_
	    @return         LRESULT
		@exception      none
		@note
		- ���̊֐����E�B���h�E�v���V�[�W�����ɑg�ݍ��ނ���
	*/
	//---------------------------------------------------------------------------
	LRESULT Proc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::HandleSend
	
		�\�P�b�g��SendList������send����
	
	    @param[in]      void
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void HandleSend(void);

protected:
	/*! @par protected�����o�֐� */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::AcceptProc
	
		FD_ACCEPT�������̏���
	
	    @param[in]      HWND         hWnd_
		@param[in]      unsigned int unMsg_
		@param[in]      WPARAM       wParam_
		@param[in]      LPARAM       lParam_
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void AcceptProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::ConnectProc
	
		FD_CONNECT�������̏���
	
	    @param[in]      HWND         hWnd_
		@param[in]      unsigned int unMsg_
		@param[in]      WPARAM       wParam_
		@param[in]      LPARAM       lParam_
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void ConnectProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::WriteProc
	
		FD_WRITE�������̏���
	
	    @param[in]      HWND         hWnd_
		@param[in]      unsigned int unMsg_
		@param[in]      WPARAM       wParam_
		@param[in]      LPARAM       lParam_
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void WriteProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::ReadProc
	
		FD_READ�������̏���
	
	    @param[in]      HWND         hWnd_
		@param[in]      unsigned int unMsg_
		@param[in]      WPARAM       wParam_
		@param[in]      LPARAM       lParam_
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void ReadProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::CloseProc
	
		FD_CLOSE�������̏���
	
	    @param[in]      HWND         hWnd_
		@param[in]      unsigned int unMsg_
		@param[in]      WPARAM       wParam_
		@param[in]      LPARAM       lParam_
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void CloseProc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::AddSocket
	
		�\�P�b�g���X�g�ɒǉ�����
	
	    @param[in]      SocketBase *pCSocket_ �\�P�b�g�|�C���^
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void AddSocket(SocketBase *pCSocket_);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::RemoveSocket
	
		�\�P�b�g���X�g����폜����
	
	    @param[in]      HWND         hWnd_
		@param[in]      unsigned int unMsg_
		@param[in]      WPARAM       wParam_
		@param[in]      LPARAM       lParam_
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void RemoveSocket(SocketBase *pCSocket_);
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================