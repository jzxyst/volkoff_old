//=============================================================================
/*! 
    @addtogroup 
    @file       TcpStream.h
    @brief      TcpStreamクラスヘッダ
    
    パケットの分割・組立や、セッションの管理を行う
    
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
      -# 作成
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
	unsigned int unDataSize; //トランスポートヘッダ分を含まない実データサイズ（セッションヘッダは含む）
}TransportHeader;

typedef struct _TAG_SESSION_HEADER
{
	unsigned char ucSessionBit; //セッションレイヤー用識別番号(SessionFuncNo)
}SessionHeader;


/*! @enum SessionFuncNo */
typedef enum _ENUM_SESSION_FUNCTION_NO
{
	SSF_UNDEF = 0, //未定義
	SSF_SEND,      //データ送信
	SSF_PING,      //応答要求
	SSF_PING_RES,  //応答
}SessionFuncNo;

/*! @enum SessionParam */
typedef enum _ENUM_SESSION_STATE
{
	SST_UNDEF = 0,   //未定義
	SST_NON_CONNECT, //未接続
	SST_LISTEN,      //接続要求待ち
	SST_CONNECTING,  //接続要求中
	SST_ESTABLISHED, //接続確立
	SST_FAILED,      //接続失敗
	SST_NO_RESPONSE, //応答なし
	SST_CLOSE        //切断
}SessionState;


/*! @class TcpStream
	@brief TcpStreamクラス

	パケットの分割・組立や、セッションの管理を行う
*/
class TcpStream : public TcpSocket
{
public:
	/*! @par publicメンバ変数 */

private:
	/*! @par privateメンバ変数 */
	static const int scm_nDefRecvBufSize = ETHERNET_MTU;
	static const int scm_nTimeoutClose = 10000; //タイムアウトによりセッションを閉じる時間(ms)

	std::vector<char> m_vcSendBuffer; //送信用バッファ
	std::vector<char> m_vcRecvBuffer; //保存用バッファ

	size_t m_unSaveSize;              //保存用バッファに残っているデータサイズ

	SessionState m_eSessionState;

	DWORD m_dwPing; //コネクション相手のレスポンスタイム
	DWORD m_dwPingSendTime; //Pingを最後に送信した時間（::timeGetiTime）
	bool m_bSendPing; //Pingを送っているフラグ。応答が返ってきた時点でfalseに戻る


public:
	/*! @par 例外処理 */


public:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief TcpStream::TcpStream
	
		デフォルトコンストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	TcpStream();

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpStream::~TcpStream
	
		デストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~TcpStream();

public:
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	SessionState getSessionState() const {return this->m_eSessionState;}

	DWORD getPing() const {return this->m_dwPing;}

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpStream::Initialize
	
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
		@brief TcpStream::Release
	
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
		@brief TcpStream::Close
	
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
		@brief TcpStream::AsyncClose
	
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
		@brief TcpStream::Listen
	
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
		@brief TcpStream::Accept
	
		接続要求を受理する
	
		@param[in]      TcpStream **ppCNewStream_ 接続要求を受理する新しいポインタ
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Accept(TcpStream **ppCNewStream_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpStream::Connect
	
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
		@brief TcpStream::Connect
	
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
		@brief TcpStream::Connect
	
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
		@brief TcpStream::Connect
	
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
		@brief TcpStream::Send
	
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

private:
	/*! @par privateメンバ関数 */
	//---------------------------------------------------------------------------
	/*! 
		@brief TcpStream::_Recv
	
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
		@brief TcpStream::Discernment
	
		受信データをセッションヘッダによって識別し、処理する
	
		@param[in]      void   *pData_ - データ
		@param[in]      size_t unSize_ - 格納先サイズ 
		@return         bool
		- true  SSF_SEND
		- false その他
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Discernment(void *pData_,size_t unSize_);

	//---------------------------------------------------------------------------
	/*! 
		@brief TcpStream::TimerProc
	
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
		@brief TcpStream::Proc
	
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