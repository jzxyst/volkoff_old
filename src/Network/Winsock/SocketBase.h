//=============================================================================
/*! 
    @addtogroup 
    @file       SocketBase.h
    @brief      SocketBaseクラスヘッダ
    
    ソケットの基底クラス
    
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
      -# 作成
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
	@brief SocketBaseクラス

	ソケットの基底クラス
*/
class SocketBase
{
	friend SocketManager;

public:
	/*! @par publicメンバ変数 */

protected:
	/*! @par protectedメンバ変数 */
	static const int scm_nTimerIntv = 1000; //タイマー間隔(ms)

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

	unsigned int m_unTime; //オブジェクトが生成されてからの経過時間

	UINT_PTR m_unTimerID;

	int m_nLastError;


private:
	/*! @par privateメンバ変数 */


public:
	/*! @par 例外処理 */


public:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::SocketBase
	
		デフォルトコンストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	SocketBase();

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::~SocketBase
	
		デストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~SocketBase();

public:
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
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
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
	void setSockID(SOCKID unSockID_) {this->m_unSockID = unSockID_;}

protected:
	/*! @par protectedメンバ関数 */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Initialize
	
		初期化処理
	
		@param[in]      SOCKET hSock_ 初期ソケットハンドル 
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Initialize(SOCKET hSock_ = INVALID_SOCKET) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Release
	
		終了処理
	
		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Release() = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Close
	
		通信を切断する
	
		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Close() = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::AsyncClose
	
		通信相手と同期を取らず、強制的に切断する
	
		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
		@note
		 - 推薦されません。
	*/
	//---------------------------------------------------------------------------
	virtual bool AsyncClose() = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Bind
	
		指定されたポートにバインドする
	
		@param[in]      PORT usPort_ - ポート番号
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Bind(PORT usPort_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Connect
	
		指定されたIPアドレスに対して接続を試みる
	
		@param[in]      IPv4L ulAddr_ - 接続先IPアドレス(IPv4)
		@param[in]      PORT  usPort_ - 接続先ポート番号
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Connect(IPv4L ulAddr_,PORT usPort_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Connect
	
		指定されたIPアドレスに対して接続を試みる
	
		@param[in]      IPv4A pszAddr_ - 接続先IPアドレス(IPv4)
		@param[in]      PORT  usPort_  - 接続先ポート番号
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Connect(IPv4A pszAddr_,PORT usPort_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Connect
	
		指定されたIPアドレスに対して接続を試みる
	
		@param[in]      IPv4W pwszAddr_ - 接続先IPアドレス(IPv4)
		@param[in]      PORT  usPort_   - 接続先ポート番号
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Connect(IPv4W pwszAddr_,PORT usPort_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Connect
	
		指定されたIPアドレスに対して接続を試みる
	
		@param[in]      sockaddr_in stAddr_ - 接続先情報
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Connect(sockaddr_in stAddr_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Send
	
		データを送信リストに追加する
	
		@param[in]      const void *c_pData_  - データ
		@param[in]      size_t     unSize_    - データサイズ
		@param[in]      bool       bPriority_ - 優先して送信する
		@return         int
		- 0     成功
		- 0以外 エラーコード
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual int Send(const void *c_pData_,size_t unSize_,bool bPriority_ = false) = 0;

protected:
	/*! @par protectedメンバ関数 */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::_Send
	
		データを送信する
	
		@param[in]      void
		@return         int
		- 0     成功
		- 0以外 エラーコード
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual int _Send() = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::_Recv
	
		データを受信する
	
		@param[in]      void   *pBuff      - データ格納先ポインタ
		@param[in]      size_t unBuffSize_ - 格納先サイズ 
		@return         int
		- 受信データサイズ(Byte)
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual int _Recv(void *pBuff_,size_t unBuffSize_) = 0;

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketBase::Proc
	
		プロシージャ処理
	
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
	/*! @par privateメンバ関数 */

};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================