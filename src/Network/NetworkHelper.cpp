//=============================================================================
/*! 
    @addtogroup 
    @file       NetworkHelper.cpp
    @brief      NetworkHelperクラスの実装
    
    ネットワーク情報を提供するクラス
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/25
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/25 Hi-ra Mizuno
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_NetworkHelper.h"	/* For DynamicTracer-TestPoint */
#include "./NetworkHelper.h"
#include <vector>


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::NetworkHelper
	
	デフォルトコンストラクタ
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
NetworkHelper::NetworkHelper()
{
	__DtTestPoint( __DtFunc_NetworkHelper, __DtStep_0 )
	::memset(&this->m_stWsaData,NULL,sizeof(this->m_stWsaData));
	this->m_ulLocalIP = 0x00000000;
	this->m_ulGlobalIP = 0x00000000;
	::memset(&this->m_szHostName[0],'\0',sizeof(this->m_szHostName));
	::memset(&this->m_szRemoteHostName[0],'\0',sizeof(this->m_szRemoteHostName));
	::memset(&this->m_tszUserName[0],'\0',sizeof(this->m_tszUserName));
	__DtTestPoint( __DtFunc_NetworkHelper, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::~NetworkHelper
	
	デストラクタ
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
NetworkHelper::~NetworkHelper()
{
	__DtTestPoint( __DtFunc_NetworkHelper, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_NetworkHelper, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::Initialize
	
	初期化処理
	
	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool NetworkHelper::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	::memset(&this->m_stWsaData,NULL,sizeof(this->m_stWsaData));
	this->m_ulLocalIP = 0x00000000;
	this->m_ulGlobalIP = 0x00000000;
	::memset(&this->m_szHostName[0],'\0',sizeof(this->m_szHostName));
	::memset(&this->m_szRemoteHostName[0],'\0',sizeof(this->m_szRemoteHostName));
	::memset(&this->m_tszUserName[0],'\0',sizeof(this->m_tszUserName));

	::WSAStartup(MAKEWORD(2,2),&this->m_stWsaData);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::Release
	
	終了処理
	
	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool NetworkHelper::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	::WSACleanup();

	__DtTestPoint( __DtFunc_Release, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::ConnectEx
	
	タイムアウト時間を指定したconnect
	
	@param[in]      SOCKET      hSock_       ソケットハンドル
	@param[in]      sockaddr_in stOtherAddr_ 接続先情報
	@param[in]      int         nTimeout_    タイムアウト時間(ms)
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool NetworkHelper::ConnectEx(SOCKET hSock_,sockaddr_in stOtherAddr_,int nTimeout_)
{
	WSAEVENT hEvent;
	WSANETWORKEVENTS stEvents;
	unsigned long ulEvent = 0;
	int nRet = 0;
	bool bRes = false;

	//イベントハンドルの作成
	__DtTestPoint( __DtFunc_ConnectEx, __DtStep_0 )
	if((hEvent = ::WSACreateEvent()) == WSA_INVALID_EVENT)
		return bRes;

	if(::WSAEventSelect(hSock_,hEvent,FD_CONNECT) == SOCKET_ERROR)
	{
	   __DtTestPoint(__DtFunc_ConnectEx, __DtStep_1)
	   ::WSACloseEvent(hEvent);
	   __DtTestPoint( __DtFunc_ConnectEx, __DtStep_2 )
	   return bRes;
	}

	//接続
	if(::connect(hSock_,reinterpret_cast<sockaddr*>(&stOtherAddr_),sizeof(stOtherAddr_)) == SOCKET_ERROR)
	{
		__DtTestPoint(__DtFunc_ConnectEx, __DtStep_3)
		if(::WSAGetLastError() != WSAEWOULDBLOCK)
		{
			__DtTestPoint(__DtFunc_ConnectEx, __DtStep_4)
			::WSAEventSelect(hSock_,NULL,0);
			::WSACloseEvent(hEvent);
			::ioctlsocket(hSock_,FIONBIO,&ulEvent);

			__DtTestPoint( __DtFunc_ConnectEx, __DtStep_5 )
			return bRes;
		}
	}

	//タイムアウトを待つ
	if((ulEvent = ::WSAWaitForMultipleEvents(1,&hEvent,false,nTimeout_,false)) != WSA_WAIT_EVENT_0)
	{
		__DtTestPoint(__DtFunc_ConnectEx, __DtStep_6)
		::WSAEventSelect(hSock_,NULL,0);
		::WSACloseEvent(hEvent);
		::ioctlsocket(hSock_,FIONBIO,&ulEvent);

		__DtTestPoint( __DtFunc_ConnectEx, __DtStep_7 )
		return bRes;
	}
	
	if((nRet = ::WSAEnumNetworkEvents(hSock_,hEvent,&stEvents)) == SOCKET_ERROR)
	{
		__DtTestPoint(__DtFunc_ConnectEx, __DtStep_8)
		::WSAEventSelect(hSock_,NULL,0);
		::WSACloseEvent(hEvent);
		::ioctlsocket(hSock_,FIONBIO,&ulEvent);

		__DtTestPoint( __DtFunc_ConnectEx, __DtStep_9 )
		return bRes;
	}

	if((stEvents.lNetworkEvents & FD_CONNECT) && stEvents.iErrorCode[FD_CONNECT_BIT] == 0)
		bRes = true;
	else
		return bRes;

	::WSAEventSelect(hSock_,NULL,0);
	::WSACloseEvent(hEvent);
	::ioctlsocket(hSock_,FIONBIO,&ulEvent);

	__DtTestPoint( __DtFunc_ConnectEx, __DtStep_10 )
	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::GetLocalIPL
	
	ローカルIPアドレスをunsigned long型で返す
	
	@param[in]      void
	@return         IPv4L
	@exception      none
*/
//---------------------------------------------------------------------------
IPv4L NetworkHelper::GetLocalIPL()
{
	__DtTestPoint( __DtFunc_GetLocalIPL, __DtStep_0 )
	if(!this->m_ulLocalIP)
	{
		char szBuf[16];
		HOSTENT *pstHost;
		in_addr stInaddr;

		__DtTestPoint(__DtFunc_GetLocalIPL, __DtStep_1)
		if(::gethostname(szBuf,sizeof(szBuf)))
			return this->m_ulLocalIP;

		pstHost = ::gethostbyname(szBuf);

		for(int i = 0;pstHost->h_addr_list[i];++i)
		{
			__DtTestPoint(__DtFunc_GetLocalIPL, __DtStep_2)
			::memcpy_s(&stInaddr,sizeof(stInaddr),pstHost->h_addr_list[i],sizeof(unsigned long));
			::strcpy_s(szBuf,sizeof(szBuf),::inet_ntoa(stInaddr));
		}

		this->m_ulLocalIP = ::inet_addr(szBuf);
	}

	__DtTestPoint( __DtFunc_GetLocalIPL, __DtStep_3 )
	return this->m_ulLocalIP;
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::GetLocalIPA
	
	ローカルIPアドレスをconst char*型で返す
	
	@param[in]      void
	@return         IPv4A
	@exception      none
*/
//---------------------------------------------------------------------------
IPv4A NetworkHelper::GetLocalIPA()
{
	__DtTestPoint( __DtFunc_GetLocalIPA, __DtStep_0 )
	if(!this->m_ulLocalIP)
	{
		char szBuf[16];
		HOSTENT *pstHost;
		in_addr stInaddr;

		__DtTestPoint(__DtFunc_GetLocalIPA, __DtStep_1)
		if(::gethostname(szBuf,sizeof(szBuf)))
			return '\0';

		pstHost = ::gethostbyname(szBuf);

		for(int i = 0;pstHost->h_addr_list[i];++i)
		{
			__DtTestPoint(__DtFunc_GetLocalIPA, __DtStep_2)
			::memcpy_s(&stInaddr,sizeof(stInaddr),pstHost->h_addr_list[i],sizeof(unsigned long));
			::strcpy_s(szBuf,sizeof(szBuf),::inet_ntoa(stInaddr));
		}

		this->m_ulLocalIP = ::inet_addr(szBuf);
	}

	in_addr stRetAddr;

	stRetAddr.S_un.S_addr = this->m_ulLocalIP;

	__DtTestPoint( __DtFunc_GetLocalIPA, __DtStep_3 )
	return ::inet_ntoa(stRetAddr);
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::GetGlobalIPL
	
	グローバルIPアドレスをunsigned long型で返す
	
	@param[in]      void
	@return         IPv4A
	@exception      none
	@attention
	- 外部サーバに問い合わせる為、レスポンスが返るまでの間ブロッキングする。
*/
//---------------------------------------------------------------------------
IPv4L NetworkHelper::GetGlobalIPL()
{
	__DtTestPoint( __DtFunc_GetGlobalIPL, __DtStep_0 )
	if(!this->m_ulGlobalIP)
	{
		//初期化
		SOCKET hSock = INVALID_SOCKET;
		sockaddr_in stServerAddr;

		__DtTestPoint(__DtFunc_GetGlobalIPL, __DtStep_1)
		::memset(&stServerAddr,NULL,sizeof(stServerAddr));


		//ソケット作成
		if((hSock = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
			return this->m_ulGlobalIP;

		//接続先設定
		stServerAddr.sin_family = AF_INET;
		stServerAddr.sin_port = ::htons(80);

		hostent* stHost = ::gethostbyname(scg_szServerName);
		if(!stHost)
			return this->m_ulGlobalIP;

		if(::memcpy_s(&stServerAddr.sin_addr,sizeof(stServerAddr.sin_addr),stHost->h_addr_list[0],stHost->h_length))
			return this->m_ulGlobalIP;

		//サーバに接続
		if(!this->ConnectEx(hSock,stServerAddr,this->scm_nDefTimeout))
		{
			__DtTestPoint(__DtFunc_GetGlobalIPL, __DtStep_2)
			::shutdown(hSock,SD_BOTH);
			::closesocket(hSock);

			__DtTestPoint( __DtFunc_GetGlobalIPL, __DtStep_3 )
			return this->m_ulGlobalIP;
		}

		//サーバにHTTPリクエストを送信し、IPアドレスを問い合わせる
		if(::send(hSock,scg_szHttpRequest,sizeof(scg_szHttpRequest),0) < 0)
		{
			__DtTestPoint(__DtFunc_GetGlobalIPL, __DtStep_4)
			::shutdown(hSock,SD_BOTH);
			::closesocket(hSock);

			__DtTestPoint( __DtFunc_GetGlobalIPL, __DtStep_5 )
			return this->m_ulGlobalIP;
		}

		//サーバからの応答を受信
		int nRecvSize = 0,nDone = 0,cnt = 0;
		std::vector<char> vcRecvBuffer;
		const int c_nRecvBufferSize = ETHERNET_MTU;

		do
		{
			__DtTestPoint(__DtFunc_GetGlobalIPL, __DtStep_6)
			++cnt;
			vcRecvBuffer.resize(vcRecvBuffer.size() + c_nRecvBufferSize);

			nRecvSize = ::recv(hSock,&vcRecvBuffer[nDone],vcRecvBuffer.capacity(),0);

			if(nRecvSize <= 0)
				break;

			nDone += nRecvSize;
		}while(nRecvSize >= c_nRecvBufferSize);

		//ソケットの解放
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);
		
		//レスポンスの解析
		std::string strRes = &vcRecvBuffer[0];
		char szBuf[16];
		unsigned int nIndex = 0,nEndIndex = 0;

		::memset(&szBuf[0],'\0',sizeof(szBuf));
		
		//"IP="を検索する
		if((nIndex = strRes.find(scg_szIPRefPoint)) == std::string::npos)
			return this->m_ulGlobalIP;

		//検索された値に"IP="分を加算
		nIndex += sizeof(scg_szIPRefPoint) - 1;

		//区切りである'\r'が見つかるまで続ける
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			__DtTestPoint(__DtFunc_GetGlobalIPL, __DtStep_7)
			if(strRes[nEndIndex] == '\r')
				break;
		}

		//見つかったIPアドレスをバッファにコピー
		if(::memcpy_s(&szBuf[0],sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex - 1))
			return this->m_ulGlobalIP;

		this->m_ulGlobalIP = ::inet_addr(szBuf);
	}

	__DtTestPoint( __DtFunc_GetGlobalIPL, __DtStep_8 )
	return this->m_ulGlobalIP;
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::GetGlobalIPA
	
	グローバルIPアドレスをconst char*型で返す
	
	@param[in]      void
	@return         IPv4A
	@exception      none
	@attention
	- 外部サーバに問い合わせる為、レスポンスが返るまでの間ブロッキングする。
*/
//---------------------------------------------------------------------------
const char* NetworkHelper::GetGlobalIPA()
{
	__DtTestPoint( __DtFunc_GetGlobalIPA, __DtStep_0 )
	if(!this->m_ulGlobalIP)
	{
		//初期化
		SOCKET hSock = INVALID_SOCKET;
		sockaddr_in stServerAddr;

		__DtTestPoint(__DtFunc_GetGlobalIPA, __DtStep_1)
		::memset(&stServerAddr,NULL,sizeof(stServerAddr));


		//ソケット作成
		if((hSock = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
			return '\0';

		//接続先設定
		stServerAddr.sin_family = AF_INET;
		stServerAddr.sin_port = ::htons(80);

		hostent* stHost = ::gethostbyname(scg_szServerName);
		if(!stHost)
			return '\0';

		if(::memcpy_s(&stServerAddr.sin_addr,sizeof(stServerAddr.sin_addr),stHost->h_addr_list[0],stHost->h_length))
			return '\0';

		//サーバに接続
		if(!this->ConnectEx(hSock,stServerAddr,this->scm_nDefTimeout))
		{
			__DtTestPoint(__DtFunc_GetGlobalIPA, __DtStep_2)
			::shutdown(hSock,SD_BOTH);
			::closesocket(hSock);

			__DtTestPoint( __DtFunc_GetGlobalIPA, __DtStep_3 )
			return '\0';
		}

		//サーバにHTTPリクエストを送信し、IPアドレスを問い合わせる
		if(::send(hSock,scg_szHttpRequest,sizeof(scg_szHttpRequest),0) < 0)
		{
			__DtTestPoint(__DtFunc_GetGlobalIPA, __DtStep_4)
			::shutdown(hSock,SD_BOTH);
			::closesocket(hSock);

			__DtTestPoint( __DtFunc_GetGlobalIPA, __DtStep_5 )
			return '\0';
		}

		//サーバからの応答を受信
		int nRecvSize = 0,nDone = 0,cnt = 0;
		std::vector<char> vcRecvBuffer;
		const int c_nRecvBufferSize = ETHERNET_MTU;

		do
		{
			__DtTestPoint(__DtFunc_GetGlobalIPA, __DtStep_6)
			++cnt;
			vcRecvBuffer.resize(vcRecvBuffer.size() + c_nRecvBufferSize);

			nRecvSize = ::recv(hSock,&vcRecvBuffer[nDone],vcRecvBuffer.capacity(),0);

			if(nRecvSize <= 0)
				break;

			nDone += nRecvSize;
		}while(nRecvSize >= c_nRecvBufferSize);

		//ソケットの解放
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);
		
		//レスポンスの解析
		std::string strRes = &vcRecvBuffer[0];
		char szBuf[16];
		unsigned int nIndex = 0,nEndIndex = 0;

		::memset(&szBuf[0],'\0',sizeof(szBuf));
		
		//"IP="を検索する
		if((nIndex = strRes.find(scg_szIPRefPoint)) == std::string::npos)
			return '\0';

		//検索された値に"IP="分を加算
		nIndex += sizeof(scg_szIPRefPoint) - 1;

		//区切りである'\r'が見つかるまで続ける
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			__DtTestPoint(__DtFunc_GetGlobalIPA, __DtStep_7)
			if(strRes[nEndIndex] == '\r')
				break;
		}

		//見つかったIPアドレスをバッファにコピー
		if(::memcpy_s(&szBuf[0],sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return '\0';

		this->m_ulGlobalIP = ::inet_addr(szBuf);
	}

	in_addr stAddr;
	::memset(&stAddr,NULL,sizeof(stAddr));
	stAddr.S_un.S_addr = this->m_ulGlobalIP;

	__DtTestPoint( __DtFunc_GetGlobalIPA, __DtStep_8 )
	return ::inet_ntoa(stAddr);
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::GetHostName
	
	ホスト名を返す
	
	@param[in]      void
	@return         const char*
	@exception      none
*/
//---------------------------------------------------------------------------
const char* NetworkHelper::GetHostName()
{
	char szBuf[256];

	__DtTestPoint( __DtFunc_GetHostName, __DtStep_0 )
	::memset(&szBuf[0],'\0',sizeof(szBuf));

	if(::gethostname(&szBuf[0],sizeof(szBuf)))
		return '\0';

	::strcpy_s(&this->m_szHostName[0],sizeof(this->m_szHostName),szBuf);

	__DtTestPoint( __DtFunc_GetHostName, __DtStep_1 )
	return this->m_szHostName;
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::GetRemoteHostName
	
	リモートホスト名を返す
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
const char* NetworkHelper::GetRemoteHostName()
{
	__DtTestPoint( __DtFunc_GetRemoteHostName, __DtStep_0 )
	if(!this->m_szRemoteHostName[0])
	{
		//初期化
		SOCKET hSock = INVALID_SOCKET;
		sockaddr_in stServerAddr;

		__DtTestPoint(__DtFunc_GetRemoteHostName, __DtStep_1)
		::memset(&stServerAddr,NULL,sizeof(stServerAddr));


		//ソケット作成
		if((hSock = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
			return this->m_szRemoteHostName;

		//接続先設定
		stServerAddr.sin_family = AF_INET;
		stServerAddr.sin_port = ::htons(80);

		hostent* stHost = ::gethostbyname(scg_szServerName);
		if(!stHost)
			return this->m_szRemoteHostName;

		if(::memcpy_s(&stServerAddr.sin_addr,sizeof(stServerAddr.sin_addr),stHost->h_addr_list[0],stHost->h_length))
			return this->m_szRemoteHostName;

		//サーバに接続
		if(!this->ConnectEx(hSock,stServerAddr,this->scm_nDefTimeout))
		{
			__DtTestPoint(__DtFunc_GetRemoteHostName, __DtStep_2)
			::shutdown(hSock,SD_BOTH);
			::closesocket(hSock);

			__DtTestPoint( __DtFunc_GetRemoteHostName, __DtStep_3 )
			return this->m_szRemoteHostName;
		}

		//サーバにHTTPリクエストを送信し、IPアドレスを問い合わせる
		if(::send(hSock,scg_szHttpRequest,sizeof(scg_szHttpRequest),0) < 0)
		{
			__DtTestPoint(__DtFunc_GetRemoteHostName, __DtStep_4)
			::shutdown(hSock,SD_BOTH);
			::closesocket(hSock);

			__DtTestPoint( __DtFunc_GetRemoteHostName, __DtStep_5 )
			return this->m_szRemoteHostName;
		}

		//サーバからの応答を受信
		int nRecvSize = 0,nDone = 0,cnt = 0;
		std::vector<char> vcRecvBuffer;
		const int c_nRecvBufferSize = ETHERNET_MTU;

		do
		{
			__DtTestPoint(__DtFunc_GetRemoteHostName, __DtStep_6)
			++cnt;
			vcRecvBuffer.resize(vcRecvBuffer.size() + c_nRecvBufferSize);

			nRecvSize = ::recv(hSock,&vcRecvBuffer[nDone],vcRecvBuffer.capacity(),0);

			if(nRecvSize <= 0)
				break;

			nDone += nRecvSize;
		}while(nRecvSize >= c_nRecvBufferSize);

		//ソケットの解放
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);
		
		//レスポンスの解析
		std::string strRes = &vcRecvBuffer[0];
		char szBuf[16];
		unsigned int nIndex = 0,nEndIndex = 0;

		::memset(&szBuf[0],'\0',sizeof(szBuf));
		
		//"HOST="を検索する
		if((nIndex = strRes.find(scg_szHostRefPoint)) == std::string::npos)
			return this->m_szRemoteHostName;

		//検索された値に"HOST="分を加算
		nIndex += sizeof(scg_szHostRefPoint) - 1;

		//区切りである'\r'が見つかるまで続ける
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			__DtTestPoint(__DtFunc_GetRemoteHostName, __DtStep_7)
			if(strRes[nEndIndex] == '\r')
				break;
		}

		//見つかったリモートホスト名をコピー
		if(::memcpy_s(&this->m_szRemoteHostName[0],sizeof(this->m_szRemoteHostName),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return this->m_szRemoteHostName;
	}

	__DtTestPoint( __DtFunc_GetRemoteHostName, __DtStep_8 )
	return this->m_szRemoteHostName;
}


//---------------------------------------------------------------------------
/*! 
	@brief NetworkHelper::GetUserName
	
	ログインユーザ名をconst TCHAR*型で返す
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
const TCHAR* NetworkHelper::GetUserName()
{
	DWORD dwSize = sizeof(this->m_tszUserName);

	__DtTestPoint( __DtFunc_GetUserName, __DtStep_0 )
	if(!::GetUserName(&this->m_tszUserName[0],&dwSize))
		return this->m_tszUserName;

	__DtTestPoint( __DtFunc_GetUserName, __DtStep_1 )
	return this->m_tszUserName;
}


//=============================================================================
//								End of File
//=============================================================================