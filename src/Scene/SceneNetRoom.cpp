//=============================================================================
//【 SceneNetRoom 】
//=============================================================================

#include "stdafx.h"
#include	"DT_SceneNetRoom.h"	/* For DynamicTracer-TestPoint */
#include "../Game/GameManager.h"
#include "SceneGame.h"
#include "SceneConnection.h"
#include "SceneNetRoom.h"

//=============================================================================
// ■ SceneNetRoom クラス
//=============================================================================


//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneNetRoom::onStart()
{
    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    printf( "-------------------------------------------------\n" );
    printf( " ▼ ルーム画面\n" );
    printf( "-------------------------------------------------\n" );

    if ( GameManager::getInstance()->getGameSession()->isParent() )
    {
        __DtTestPoint(__DtFunc_onStart, __DtStep_1)
        printf( "Z > ゲーム画面へ\n" );
    }
    else
    {
        __DtTestPoint(__DtFunc_onStart, __DtStep_2)
        printf( "開始待ち...\n" );
    }

    GameManager::getInstance()->getGameSession()->setEventListener( this );
	__DtTestPoint( __DtFunc_onStart, __DtStep_3 )
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneNetRoom::onUpdate()
{
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    GameManager::getInstance()->update();



    GameSession* session = GameManager::getInstance()->getGameSession();

    if ( session->isParent() )
    {
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
        if ( Input.isOnTrigger( LN_BUTTON_A ) )
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_2)
            session->sendToServer( SYSEV_GOTO_SCENEGAME, NULL, 0 );

            //LGameScene::changeScene( NEW SceneGame() );
        }
    }

	__DtTestPoint( __DtFunc_onUpdate, __DtStep_3 )
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneNetRoom::onTerminate()
{
    __DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
    GameManager::getInstance()->getGameSession()->setEventListener( NULL );
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● イベント処理コールバック
//---------------------------------------------------------------------
int SceneNetRoom::HandleEvent( u32 event_, void* args_ )
{
    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
    switch ( event_ )
    {
        ///////////////////////////////////////////// SceneGame に移動する
        case SYSEV_GOTO_SCENEGAME:
        {
            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
            printf( "げーむいどう\n" );
            LGameScene::changeScene( NEW SceneGame() );
            break;
        }
    }
    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_2 )
    return 0;
}

//=============================================================================
//								end of file
//=============================================================================