//=============================================================================
//【 GameServer 】
//=============================================================================

#include "stdafx.h"
#include	"DT_GameServer.h"	/* For DynamicTracer-TestPoint */
#include "../Event/EventType.h"
#include "../Object/GameObjectManager.h"
#include "../Object/Weapon.h"
#include "GameManager.h"
#include "GameSession.h"
#include "GameServer.h"

//=============================================================================
// ■ GameServer クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
GameServer::GameServer()
    : mMyGameSession    ( NULL )
    , mListen           ( NULL )
{
    
	__DtTestPoint( __DtFunc_GameServer, __DtStep_0 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
GameServer::~GameServer()
{
    __DtTestPoint( __DtFunc_GameServer, __DtStep_1 )
    SAFE_DELETE( mListen );


    TcpStreamArray::iterator itr = mConnectedStreamArray.begin();
    TcpStreamArray::iterator end = mConnectedStreamArray.end();
    for ( ;itr != end; ++itr )
    {
        __DtTestPoint(__DtFunc_GameServer, __DtStep_2)
        SAFE_DELETE( (*itr) );
    }
	__DtTestPoint( __DtFunc_GameServer, __DtStep_3 )
}

//---------------------------------------------------------------------
// ● 初期化
//---------------------------------------------------------------------
void GameServer::initialize( GameSession* sesson_ )
{
    __DtTestPoint( __DtFunc_initialize, __DtStep_0 )
    mMyGameSession = sesson_;

    mListen = NEW TcpStream();
    mListen->Initialize();
    mListen->Bind( GAMEPORT );
    mListen->Listen( 5 );
	__DtTestPoint( __DtFunc_initialize, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● 接続を監視する (1フレームに1度呼び出す)
//---------------------------------------------------------------------
void GameServer::polling()
{
    __DtTestPoint( __DtFunc_polling, __DtStep_0 )
    if ( mListen->getAcceptDemandNum() > 0 )
    {
        TcpStream* tcp_stream;
        __DtTestPoint(__DtFunc_polling, __DtStep_1)
        mListen->Accept( &tcp_stream );

        mConnectedStreamArray.push_back( tcp_stream );

        printf("接続してきました\n");

        tcp_stream->Send( "fせつぞくできた", strlen( "fせつぞくできた" ) + 1 );
    }
	__DtTestPoint( __DtFunc_polling, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● 全てのクライアントにイベントを送信する
//---------------------------------------------------------------------
void GameServer::sendEventToAllHost( u32 event_, void* data_, u32 size_ )
{
    // 自分自身にはすぐに送信
    __DtTestPoint( __DtFunc_sendEventToAllHost, __DtStep_0 )
    mMyGameSession->HandleEvent( event_, data_ );

    // ヘッダを作る
    GameSystemEventHeader header;
    header.Type         = event_;
    header.ArgSize      = size_;

    // 一度 mTempBuffer に全て格納
    memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
    if ( data_ )
    {
        __DtTestPoint(__DtFunc_sendEventToAllHost, __DtStep_1)
        memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );
    }

    // 接続済みのものに全て送信
    TcpStreamArray::iterator itr = mConnectedStreamArray.begin();
    TcpStreamArray::iterator end = mConnectedStreamArray.end();
    for ( ;itr != end; ++itr )
    {
        __DtTestPoint(__DtFunc_sendEventToAllHost, __DtStep_2)
        (*itr)->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
    }
	__DtTestPoint( __DtFunc_sendEventToAllHost, __DtStep_3 )
}

//---------------------------------------------------------------------
// ● 指定したホスト以外の全てのホストの GameSession にイベントを送信する
//---------------------------------------------------------------------
void GameServer::sendEventToExclusionHost( u32 exc_host_id_, u32 event_, void* data_, u32 size_ )
{
    __DtTestPoint( __DtFunc_sendEventToExclusionHost, __DtStep_0 )
    if ( exc_host_id_ != 0 )
    {
        // 自分自身にはすぐに送信
        __DtTestPoint(__DtFunc_sendEventToExclusionHost, __DtStep_1)
        mMyGameSession->HandleEvent( event_, data_ );
    }

    // ヘッダを作る
    GameSystemEventHeader header;
    header.Type         = event_;
    header.ArgSize      = size_;

    // 一度 mTempBuffer に全て格納
    memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
    if ( data_ )
    {
        __DtTestPoint(__DtFunc_sendEventToExclusionHost, __DtStep_2)
        memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );
    }

    // 指定以外の接続済みのものに全て送信
    u32 n = mConnectedStreamArray.size();
    u32 exc = exc_host_id_ - 1;
    for ( u32 i = 0; i < n; ++i )
    {
        __DtTestPoint(__DtFunc_sendEventToExclusionHost, __DtStep_3)
        if ( i != exc )
        {
            __DtTestPoint(__DtFunc_sendEventToExclusionHost, __DtStep_4)
            mConnectedStreamArray[ i ]->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
        }
    }
	__DtTestPoint( __DtFunc_sendEventToExclusionHost, __DtStep_5 )
}

//---------------------------------------------------------------------
// ● イベント処理
//---------------------------------------------------------------------
int GameServer::HandleEvent( u32 event_, void* args_ )
{
    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
    switch ( event_ )
    {
        ///////////////////////////////////////////// SceneGame に移動する
        case SYSEV_GOTO_SCENEGAME:
        {
            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
            sendEventToAllHost( SYSEV_GOTO_SCENEGAME, NULL, 0 );
            break;
        }

        ///////////////////////////////////////////// アイテム(武器含む)を拾いたいときの要求 (各ホストからサーバに送られてくる)
        case SYSEV_ITEM_REQUEST:
        {
            ItemRequestArgs* args = static_cast< ItemRequestArgs* >( args_ );
            GameObjectManager* manager = GameObjectManager::getInstance();

            // アイテムオブジェクトを探す
            GameObject* obj = manager->findObject( args->ItemObjHandle );

            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_2)
            if ( obj )
            {
                // 武器の場合
                __DtTestPoint(__DtFunc_HandleEvent, __DtStep_3)
                if ( obj->getObjType() == OBJ_WEAPON )
                {
                    // 取得するキャラクターに対してオブジェクトの持つ武器データを送信する
                    WeaponData data = ( static_cast< Weapon* >( obj ) )->getWeaponData();
                    __DtTestPoint(__DtFunc_HandleEvent, __DtStep_4)
                    manager->postEvent( args->GetterHandle, EV_GET_WEAPON, &data, sizeof( WeaponData ) );

                    u32 handle = obj->getHandle();

                    // 武器オブジェクトを削除する
                    sendEventToAllHost( SYSEV_DELETE_GAMEOBJECT, &handle, sizeof( u32 ) );
                }  
            }
        }
    }

    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_5 )
    return 0;
}



//=============================================================================
//								End of File
//=============================================================================