//=============================================================================
/*! 
    @addtogroup 
    @file       NetworkHelper.h
    @brief      NetworkHelper�N���X�w�b�_
    
    �l�b�g���[�N����񋟂���N���X
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/25
    @version    1.0.0
	@note
	- NIC����������ꍇ�ɑΉ����Ă��Ȃ��B(2011/10/25)
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/25 Hi-ra Mizuno
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_NETWORK_HELPER_H__
#define __INCLUDE_NETWORK_HELPER_H__


/*! @par include */
#include <winsock2.h>
#include "./Winsock/Typedef.h"
#include "./Winsock/Common/Singleton.h"


/*! @val global */
static const char scg_szServerName[] = "www.aleibar.net";
static const char scg_szHttpRequest[] = "GET /script/network-info/ HTTP/1.1\r\nHost: www.aleibar.net\r\nConnection: close\r\n\r\n";
static const char scg_szIPRefPoint[] = "IP=";
static const char scg_szHostRefPoint[] = "HOST=";
static const char scg_szPortRefPoint[] = "PORT=";


/*! @class NetworkHelper
	@brief NetworkHelper�N���X

	�l�b�g���[�N����񋟂���N���X

*/
class NetworkHelper : public Singleton<NetworkHelper>
{
	friend Singleton<NetworkHelper>;

public:
	/*! @par public�����o�ϐ� */

private:
	/*! @par private�����o�ϐ� */
	static const int scm_nDefTimeout = 5000; //ms

	WSADATA m_stWsaData;
	IPv4L m_ulLocalIP;
	IPv4L m_ulGlobalIP;
	char m_szHostName[256];
	char m_szRemoteHostName[256];
	char *m_pszMacAddr;
	TCHAR m_tszUserName[32]; //20���ȏ�ɂȂ邱�Ƃ͂Ȃ�

public:
	/*! @par ��O���� */


private:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::NetworkHelper
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	NetworkHelper();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::~NetworkHelper
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~NetworkHelper();

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	WSADATA getWsaData() {return this->m_stWsaData;}

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::Initialize
	
		����������
	
		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::Release
	
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
		@brief NetworkHelper::ConnectEx
	
		�^�C���A�E�g���Ԃ��w�肵��connect
	
		@param[in]      SOCKET      hSock_       �\�P�b�g�n���h��
		@param[in]      sockaddr_in stOtherAddr_ �ڑ�����
		@param[in]      int         nTimeout_    �^�C���A�E�g����(ms)
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool ConnectEx(SOCKET hSock_,sockaddr_in stOtherAddr_,int nTimeout_);

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetLocalIPL
	
		���[�J��IP�A�h���X��unsigned long�^�ŕԂ�
	
		@param[in]      void
		@return         IPv4L
		@exception      none
	*/
	//---------------------------------------------------------------------------
	IPv4L GetLocalIPL();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetLocalIPA
	
		���[�J��IP�A�h���X��const char*�^�ŕԂ�
	
		@param[in]      void
		@return         IPv4A
		@exception      none
	*/
	//---------------------------------------------------------------------------
	IPv4A GetLocalIPA();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetGlobalIPL
	
		�O���[�o��IP�A�h���X��unsigned long�^�ŕԂ�
	
		@param[in]      void
		@return         IPv4A
		@exception      none
		@attention
		- �O���T�[�o�ɖ₢���킹��ׁA���X�|���X���Ԃ�܂ł̊ԃu���b�L���O����B
	*/
	//---------------------------------------------------------------------------
	IPv4L GetGlobalIPL();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetGlobalIPA
	
		�O���[�o��IP�A�h���X��const char*�^�ŕԂ�
	
		@param[in]      void
		@return         IPv4A
		@exception      none
		@attention
		- �O���T�[�o�ɖ₢���킹��ׁA���X�|���X���Ԃ�܂ł̊ԃu���b�L���O����B
	*/
	//---------------------------------------------------------------------------
	const char* GetGlobalIPA();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetHostName
	
		�z�X�g����Ԃ�
	
		@param[in]      void
		@return         const char*
		@exception      none
	*/
	//---------------------------------------------------------------------------
	const char* GetHostName();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetRemoteHostName
	
		�����[�g�z�X�g����Ԃ�
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	const char* GetRemoteHostName();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetUserName
	
		���O�C�����[�U����const TCHAR*�^�ŕԂ�
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	const TCHAR* GetUserName();
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================