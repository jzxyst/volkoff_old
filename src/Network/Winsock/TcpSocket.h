//=============================================================================
/*! 
    @addtogroup 
    @file       TcpSocket.h
    @brief      TcpSocketクラスヘッダ
    
    TCPソケットクラス
    
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
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_TCPSOCKET_H__
#define __INCLUDE_TCPSOCKET_H__


/*! @par include */
#include "./SocketBase.h"


/*! @class TcpSocket
	@brief TcpSocketクラス

	TCPソケットクラス
*/
class TcpSocket : public SocketBase
{
public:
	/*! @par publicメンバ変数 */

protected:
	/*! @par protectedメンバ変数 */
	static const int scm_nTimeout = 5000; //タイムアウト間隔(ms)

	int m_nAcceptDemandNum;
	unsigned int m_unConnectTime; //Connectを呼んでからの経過時間
	bool m_bConnectting;          //Connectを呼んだフラグ


public:
	/*! @par 例外処理 */


public:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::TcpSocket
	
		デフォルトコンストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	TcpSocket();

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::~TcpSocket
	
		デストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~TcpSocket();

public:
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	int getAcceptDemandNum() const {return this->m_nAcceptDemandNum;}

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Initialize
	
		初期化処理
	
		@param[in]      SOCKET hSock_ 初期ソケットハンドル 
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize(SOCKET hSock_ = INVALID_SOCKET);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Release
	
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
		@brief TcpSocket::Close
	
		通信を切断する
	
		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Close();

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::AsyncClose
	
		通信相手と同期を取らず、強制的にソケットを閉じる
	
		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
		@note
		 - 推薦されません。
	*/
	//---------------------------------------------------------------------------
	bool AsyncClose();

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Bind
	
		指定されたポートにバインドする
	
		@param[in]      PORT usPort_ - ポート番号
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Bind(PORT usPort_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Listen
	
		ソケットを接続待機状態にする
	
		@param[in]      int nMaxConnect_ - 最大接続受付数
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Listen(int nMaxConnect_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Accept
	
		接続要求を受理する
	
		@param[in]      TcpSocket **ppCNewSocket_ 接続要求を受理するソケットポインタのポインタ
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Accept(TcpSocket **ppCNewSocket_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Connect
	
		指定されたIPアドレスに対して接続を試みる
	
		@param[in]      IPv4L ulAddr_ - 接続先IPアドレス(IPv4)
		@param[in]      PORT  usPort_ - 接続先ポート番号
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Connect(IPv4L ulAddr_,PORT usPort_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Connect
	
		指定されたIPアドレスに対して接続を試みる
	
		@param[in]      IPv4A pszAddr_ - 接続先IPアドレス(IPv4)
		@param[in]      PORT  usPort_  - 接続先ポート番号
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Connect(IPv4A pszAddr_,PORT usPort_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Connect
	
		指定されたIPアドレスに対して接続を試みる
	
		@param[in]      IPv4W pwszAddr_ - 接続先IPアドレス(IPv4)
		@param[in]      PORT  usPort_   - 接続先ポート番号
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Connect(IPv4W pwszAddr_,PORT usPort_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Connect
	
		指定されたIPアドレスに対して接続を試みる
	
		@param[in]      sockaddr_in stAddr_ - 接続先情報
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Connect(sockaddr_in stAddr_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::Send
	
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
	int Send(const void *c_pData_,size_t unSize_,bool bPriority_ = false);

protected:
	/*! @par protectedメンバ関数 */
	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::_Send
	
		データを送信する
	
		@param[in]      void
		@return         int
		- 0     成功
		- 0以外 エラーコード
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int _Send();

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::_Recv
	
		データを受信する
	
		@param[in]      void   *pBuff      - データ格納先ポインタ
		@param[in]      size_t unBuffSize_ - 格納先サイズ 
		@return         int
		- 受信データサイズ(Byte)
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int _Recv(void *pBuff_,size_t unBuffSize_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpSocket::TimerProc
	
		タイマーが呼ばれるごとに行われる処理
	
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
	
		プロシージャ処理
	
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