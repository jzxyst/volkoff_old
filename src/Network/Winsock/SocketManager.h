//=============================================================================
/*! 
    @addtogroup 
    @file       SocketManager.h
    @brief      SocketManagerクラスヘッダ
    
    ソケットを管理するクラス
    
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
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_SOCKETMANAGER_H__
#define __INCLUDE_SOCKETMANAGER_H__


/*! @par define */
#define FD_SETSIZE (1024) //最大ソケット数を変更する


/*! @par include */
#include "./Common/Singleton.h"
#include "./TcpSocket.h"
#include "./UdpSocket.h"
#include "./Packet.h"
#include <vector>
#include <list>


/*! @par define */
#define WM_SOCKET (WM_APP + 100) //内部用
#define WM_SOCKETEVENT (WM_SOCKET + 100) //ユーザ用


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
	@brief SocketManagerクラス

	ソケットを管理するクラス
*/
class SocketManager : public Singleton<SocketManager>
{
	friend Singleton<SocketManager>;
	friend SocketBase;

public:
	/*! @par publicメンバ変数 */

protected:
	/*! @par protectedメンバ変数 */
	static const int scm_nDefRecvBufSize = ETHERNET_MTU; //デフォルト受信バッファサイズ(Byte)
	static const int scm_nSocketNum = FD_SETSIZE;        //最大ソケット数

	HWND m_hWnd;
	WSADATA m_stWsaData;
	unsigned int m_unMsg;
	std::list<SocketBase*> m_liSocketList;

	bool m_bSendBufEmpty;
	std::vector<char> m_vcRecvBuffer;

	SOCKID m_unTotalSockID;

public:
	/*! @par 例外処理 */


protected:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::SocketManager
	
		デフォルトコンストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	SocketManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::~SocketManager
	
		デストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~SocketManager();

public:
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	HWND getHWnd() const {return this->m_hWnd;}

	WSADATA getWsaData() const {return this->m_stWsaData;}

	unsigned int getMsg() const {return this->m_unMsg;}

	std::vector<char>& getRecvBuffer() {return this->m_vcRecvBuffer;}

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
	void setHWnd(HWND hWnd_) {this->m_hWnd = hWnd_;}

	void setRecvBufferSize(size_t unBuffSize_) {this->m_vcRecvBuffer.resize(unBuffSize_,NULL);}

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::Initialize
	
		初期化処理
	
		@param[in]      HWND         hWnd_  - ウィンドウハンドル
		@param[in]      unsigned int unMsg_ - 通知ウィンドウメッセージ
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize(HWND hWnd_,unsigned int unMsg_ = WM_SOCKETEVENT);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::Release
	
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
		@brief SocketManager::Proc
	
		プロシージャ処理
	
	    @param[in]      HWND         hWnd_
		@param[in]      unsigned int unMsg_
		@param[in]      WPARAM       wParam_
		@param[in]      LPARAM       lParam_
	    @return         LRESULT
		@exception      none
		@note
		- この関数をウィンドウプロシージャ内に組み込むこと
	*/
	//---------------------------------------------------------------------------
	LRESULT Proc(HWND hWnd_,unsigned int unMsg_,WPARAM wParam_,LPARAM lParam_);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::HandleSend
	
		ソケットのSendListを順次sendする
	
	    @param[in]      void
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void HandleSend(void);

protected:
	/*! @par protectedメンバ関数 */
	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::AcceptProc
	
		FD_ACCEPT発生時の処理
	
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
	
		FD_CONNECT発生時の処理
	
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
	
		FD_WRITE発生時の処理
	
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
	
		FD_READ発生時の処理
	
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
	
		FD_CLOSE発生時の処理
	
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
	
		ソケットリストに追加する
	
	    @param[in]      SocketBase *pCSocket_ ソケットポインタ
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void AddSocket(SocketBase *pCSocket_);

	//---------------------------------------------------------------------------
	/*! 
		@brief SocketManager::RemoveSocket
	
		ソケットリストから削除する
	
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