//=============================================================================
/*! 
    @addtogroup 
    @file       NetworkHelper.h
    @brief      NetworkHelperクラスヘッダ
    
    ネットワーク情報を提供するクラス
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/25
    @version    1.0.0
	@note
	- NICが複数ある場合に対応していない。(2011/10/25)
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/25 Hi-ra Mizuno
      -# 作成
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
	@brief NetworkHelperクラス

	ネットワーク情報を提供するクラス

*/
class NetworkHelper : public Singleton<NetworkHelper>
{
	friend Singleton<NetworkHelper>;

public:
	/*! @par publicメンバ変数 */

private:
	/*! @par privateメンバ変数 */
	static const int scm_nDefTimeout = 5000; //ms

	WSADATA m_stWsaData;
	IPv4L m_ulLocalIP;
	IPv4L m_ulGlobalIP;
	char m_szHostName[256];
	char m_szRemoteHostName[256];
	char *m_pszMacAddr;
	TCHAR m_tszUserName[32]; //20字以上になることはない

public:
	/*! @par 例外処理 */


private:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::NetworkHelper
	
		デフォルトコンストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	NetworkHelper();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::~NetworkHelper
	
		デストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~NetworkHelper();

public:
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	WSADATA getWsaData() {return this->m_stWsaData;}

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

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
	bool Initialize();

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
	bool Release();

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
	bool ConnectEx(SOCKET hSock_,sockaddr_in stOtherAddr_,int nTimeout_);

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetLocalIPL
	
		ローカルIPアドレスをunsigned long型で返す
	
		@param[in]      void
		@return         IPv4L
		@exception      none
	*/
	//---------------------------------------------------------------------------
	IPv4L GetLocalIPL();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetLocalIPA
	
		ローカルIPアドレスをconst char*型で返す
	
		@param[in]      void
		@return         IPv4A
		@exception      none
	*/
	//---------------------------------------------------------------------------
	IPv4A GetLocalIPA();

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
	IPv4L GetGlobalIPL();

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
	const char* GetGlobalIPA();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetHostName
	
		ホスト名を返す
	
		@param[in]      void
		@return         const char*
		@exception      none
	*/
	//---------------------------------------------------------------------------
	const char* GetHostName();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetRemoteHostName
	
		リモートホスト名を返す
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	const char* GetRemoteHostName();

	//---------------------------------------------------------------------------
	/*! 
		@brief NetworkHelper::GetUserName
	
		ログインユーザ名をconst TCHAR*型で返す
	
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