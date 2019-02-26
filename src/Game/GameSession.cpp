//=============================================================================
//【 GameSession 】
//=============================================================================

#include "stdafx.h"
#include	"DT_GameSession.h"	/* For DynamicTracer-TestPoint */
#include "../Object/GameObjectManager.h"
#include "GameServer.h"
#include "GameSession.h"

//=============================================================================
// ■ GameSession クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
GameSession::GameSession()
    : mGameServer       ( NULL )
    , mServerStream     ( NULL )
    , mEventListener    ( NULL )
{
    __DtTestPoint( __DtFunc_GameSession, __DtStep_0 )
    memset( &mHostInfo, 0, sizeof( mHostInfo ) );
    memset( &mTempBuffer, 0, sizeof( mTempBuffer ) );
	__DtTestPoint( __DtFunc_GameSession, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
GameSession::~GameSession()
{
    __DtTestPoint( __DtFunc_GameSession, __DtStep_2 )
    SAFE_DELETE( mServerStream );
	__DtTestPoint( __DtFunc_GameSession, __DtStep_3 )
}

//---------------------------------------------------------------------
// ● 初期化
//---------------------------------------------------------------------
void GameSession::initialize( GameServer* server_ )
{
    __DtTestPoint( __DtFunc_initialize, __DtStep_0 )
    mGameServer = server_;
    mHostInfo.IsParent = ( server_ != NULL );
	__DtTestPoint( __DtFunc_initialize, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● 子として初期化 (GameManager から呼ばれる)
//---------------------------------------------------------------------
void GameSession::initializeChild( const char* parent_ip_addr_ )
{
    __DtTestPoint( __DtFunc_initializeChild, __DtStep_0 )
    mHostInfo.IsParent = false;

    mServerStream = NEW TcpStream();
    mServerStream->Initialize();
    mServerStream->Connect( "127.0.0.1", GAMEPORT );

    printf("接続しました\n");
	__DtTestPoint( __DtFunc_initializeChild, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● サーバにデータを送信する
//---------------------------------------------------------------------
void GameSession::sendToServer( u32 event_, void* data_, u32 size_ )
{
    // 自分が親の場合
    __DtTestPoint( __DtFunc_sendToServer, __DtStep_0 )
    if ( mHostInfo.IsParent )
    {
        // すぐに処理
        __DtTestPoint(__DtFunc_sendToServer, __DtStep_1)
        mGameServer->HandleEvent( event_, data_ );
    }
    // 子の場合
    else
    {
        // ヘッダを作る
        GameSystemEventHeader header;
        __DtTestPoint(__DtFunc_sendToServer, __DtStep_2)
        header.Type         = event_;
        header.ArgSize      = size_;

        // 一度 mTempBuffer に全て格納
        memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
        if ( data_ )
        {
            __DtTestPoint(__DtFunc_sendToServer, __DtStep_3)
            memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );
        }

        // サーバに送る
        mServerStream->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
    }
	__DtTestPoint( __DtFunc_sendToServer, __DtStep_4 )
}

//---------------------------------------------------------------------
// ● オブジェクト作成メッセージ (SYSEV_CREATEED_OBJECT) を送信する
//---------------------------------------------------------------------
void GameSession::sendCreatedObjectEvent( u32 obj_type_, void* data_, u32 size_ )
{
    char temp[ 1024 ];

    u32 all_size = sizeof( CreatedObjectArgs ) + size_;

    CreatedObjectArgs* data = reinterpret_cast< CreatedObjectArgs* >( temp );

    //printf("ホストID受け取る処理ができてない\n");
    __DtTestPoint( __DtFunc_sendCreatedObjectEvent, __DtStep_0 )
    data->HostID = 0;
    data->ObjectType = obj_type_;

    memcpy( &data[ 1 ], data_, size_ );

    // サーバに送信。サーバの HandleEvent で、自分以外のホストに送信される。
    // 「自分以外」という判定は HandleEvent 内で行う。
    sendToServer( SYSEV_CREATEED_OBJECT, data, all_size );






    // 自分がサーバの場合
    //if ( mHostInfo.IsParent )
    //{
    //    // すぐに GameSession に送信

    //    //sendEventToExclusionHost

    //}
    //// 自分がクライアントの場合
    //else
    //{
    //    LN_ASSERT( 0, "sendCreatedObjectEvent 未対応" );
    //}
	__DtTestPoint( __DtFunc_sendCreatedObjectEvent, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● 同期待機
//---------------------------------------------------------------------
void GameSession::waitSync()
{
	__DtTestPoint( __DtFunc_waitSync, __DtStep_0 )
}

//---------------------------------------------------------------------
// ● イベント監視
//---------------------------------------------------------------------
void GameSession::polling()
{

    // 子の場合はサーバから送られてきているイベントをチェックする
    __DtTestPoint( __DtFunc_polling, __DtStep_0 )
    if ( mServerStream )
    {
        //mServerStream->getSessionState()
        __DtTestPoint(__DtFunc_polling, __DtStep_1)
        if ( !mServerStream->getRecvList().empty() )
	    {
            //printf( "data:%s\n", mServerStream->getRecvList().front()->getData() );
            //printf( "size:%d\n", mServerStream->getRecvList().front()->getSize() );

            GameSystemEventHeader* header = reinterpret_cast< GameSystemEventHeader* >( mServerStream->getRecvList().front()->getData() );

            // イベント処理
            __DtTestPoint(__DtFunc_polling, __DtStep_2)
            HandleEvent( header->Type, &header[ 1 ] );

		    mServerStream->getRecvList().pop_front();
	    }
    }
	__DtTestPoint( __DtFunc_polling, __DtStep_3 )
}

//---------------------------------------------------------------------
// ● イベント処理
//---------------------------------------------------------------------
int GameSession::HandleEvent( u32 event_, void* args_ )
{
    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
    if ( mEventListener )
    {
        __DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
        mEventListener->HandleEvent( event_, args_ );
    }

    switch ( event_ )
    {
        

        ///////////////////////////////////////////// オブジェクトを削除する
        case SYSEV_DELETE_GAMEOBJECT:
        {
            GameObjectManager* manager = GameObjectManager::getInstance();
            GameObject* obj = manager->findObject( *static_cast< u32* >( args_ ) );

            

            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_2)
            if ( obj )
            {
                //printf( "del handle %d\n", *static_cast< u32* >( args_ ) );

                __DtTestPoint(__DtFunc_HandleEvent, __DtStep_3)
                manager->deleteObject( obj );
            }
            break;
        }
    }

    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_4 )
    return 0;
}

//=============================================================================
//								end of file
//=============================================================================