//=============================================================================
//【 SceneConnection 】
//=============================================================================

#include "stdafx.h"
#include	"DT_SceneConnection.h"	/* For DynamicTracer-TestPoint */
#include "../Game/GameManager.h"
#include "SceneTitle.h"
#include "SceneNetRoom.h"
#include "SceneConnection.h"

//=============================================================================
// ■ SceneConnection クラス
//=============================================================================


//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneConnection::onStart()
{
    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    printf( "-------------------------------------------------\n" );
    printf( " ▼ 接続画面\n" );
    printf( "-------------------------------------------------\n" );
    printf( "Z > 部屋を作る\n" );
    printf( "X > 部屋に入る\n" );
	__DtTestPoint( __DtFunc_onStart, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneConnection::onUpdate()
{
    // 部屋を作る
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    if ( Input.isOnTrigger( LN_BUTTON_A ) )
    {
        // 親として初期化し、部屋画面に移動
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
        GameManager::getInstance()->initializeParent();
        LGameScene::changeScene( "SceneNetRoom" );
        __DtTestPoint( __DtFunc_onUpdate, __DtStep_2 )
        return;
    }

    // 部屋に入る
    if ( Input.isOnTrigger( LN_BUTTON_B ) )
    {

        char addr[ 64 ];
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_3)
        printf( "IP アドレス入力\n>" );
        scanf( "%s", addr );

        printf( "接続...\n" );

        // 子として初期化
        GameManager::getInstance()->initializeChild( addr );

        // 接続が完了した場合に移動するようにしておく
        LGameScene::changeScene( NEW SceneNetRoom() );

        __DtTestPoint( __DtFunc_onUpdate, __DtStep_4 )
        return;
    }
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_5 )
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneConnection::onTerminate()
{
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
}

//=============================================================================
//								end of file
//=============================================================================