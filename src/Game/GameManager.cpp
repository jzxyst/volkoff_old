//=============================================================================
//【 GameManager 】
//=============================================================================

#include "stdafx.h"
#include	"DT_GameManager.h"	/* For DynamicTracer-TestPoint */
#include "../Object/Player.h"
#include "GameManager.h"
#include "../Frontend/GameFrontendManager.h"
#include "../Map/MapManager.h"

//=============================================================================
// ■ GameManager クラス
//=============================================================================

//---------------------------------------------------------------------
// ● インスタンスの取得
//---------------------------------------------------------------------
GameManager* GameManager::getInstance()
{
    static GameManager instance;
    __DtTestPoint( __DtFunc_getInstance, __DtStep_0 )
    return &instance;
}

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
GameManager::GameManager()
    : mGameServer       ( NULL )
    , mGameSession      ( NULL )
    , mEffectManager    ( NULL )
    , mFloorNum         ( 0 )
    , mScore            ( 0 )
	, mRank             ( 1 )
	, mOpenflag         ( 0 )
	//, mTime             ( 0 )
	, mGameTime			(3660)	// 仮
    , mLastBoss         ( NULL )
{
    
	__DtTestPoint( __DtFunc_GameManager, __DtStep_0 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
GameManager::~GameManager()
{
    __DtTestPoint( __DtFunc_GameManager, __DtStep_1 )
    finalize();
	__DtTestPoint( __DtFunc_GameManager, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● 親として初期化する
//---------------------------------------------------------------------
void GameManager::initializeParent()
{
    //SAFE_DELETE( mGameSession );

    __DtTestPoint( __DtFunc_initializeParent, __DtStep_0 )
    mGameServer = NEW GameServer();
    mGameSession = NEW GameSession();

    mGameServer->initialize( mGameSession );
    mGameSession->initialize( mGameServer );

	//mTime = 0;
    mLastBoss = NULL;
    
	GameObjectManager::getInstance()->Initialize();
    mEffectManager = NEW EffectManager();
    mPlayer = NEW Player();
    mPlayer->Initialize();
    mPlayer->setPosition( LVector3( 80.0f, 50.0f, -1.0f ) );    // 仮の初期位置

    GameFrontendManager::getInstance()->initialize( mPlayer );
	__DtTestPoint( __DtFunc_initializeParent, __DtStep_1 )
	return;
    
}

//---------------------------------------------------------------------
// ● 子として初期化する
//---------------------------------------------------------------------
bool GameManager::initializeChild( const char* parent_ip_addr_ )
{
    //SAFE_DELETE( mGameSession );

    __DtTestPoint( __DtFunc_initializeChild, __DtStep_0 )
    mGameSession = NEW GameSession();
    mGameSession->initializeChild( parent_ip_addr_ );

	//mTime = 0;
    mLastBoss = NULL;

    GameObjectManager::getInstance()->Initialize();
    mEffectManager = NEW EffectManager();
    mPlayer = NEW Player();
    mPlayer->Initialize();
    //mPlayer->setPosition( LVector3( 80.0f, 50.0f, -1.0f ) );
  
    GameFrontendManager::getInstance()->initialize( mPlayer );
    __DtTestPoint( __DtFunc_initializeChild, __DtStep_1 )
    return true;
}

//---------------------------------------------------------------------
// ● ゲームの終了処理
//---------------------------------------------------------------------
void GameManager::finalize()
{
    //SAFE_DELETE( mPlayer );   // GameObjectManager が解放してくれるので必要なし
    __DtTestPoint( __DtFunc_finalize, __DtStep_0 )
    SAFE_DELETE( mEffectManager );

    GameObjectManager::getInstance()->Release();
    
	MapManager::getInstance()->finalize();
    GameFrontendManager::getInstance()->finalize();

    SAFE_DELETE( mGameServer );
    SAFE_DELETE( mGameSession );
    
    mLastBoss = NULL;
	__DtTestPoint( __DtFunc_finalize, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● コンティニューに備えてバックアップを取る
//---------------------------------------------------------------------
void GameManager::commit()
{
    __DtTestPoint( __DtFunc_commit, __DtStep_0 )
    mPlayer->commit();

    mBackup.Score = mScore;
	//mBackup.Time= mTime;
	__DtTestPoint( __DtFunc_commit, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● コンティニュー時のリセット
//---------------------------------------------------------------------
void GameManager::reset()
{
    __DtTestPoint( __DtFunc_reset, __DtStep_0 )
    printf( "◆ reset\n" );

    //GameObjectManager::getInstance()->Release();
    setOpenflag(0);
    setKeyflag(0);
    GameObjectManager::getInstance()->deleteStageObject();
    

    mPlayer->reset();

    //mScore = mBackup.Score;
    mScore = 0;
	//mTime = 0;
    mLastBoss = NULL;


    MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());

    
	__DtTestPoint( __DtFunc_reset, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void GameManager::update()
{
    __DtTestPoint( __DtFunc_update, __DtStep_0 )
    if ( mGameServer )
    {
        __DtTestPoint(__DtFunc_update, __DtStep_1)
        mGameServer->polling();
    }

    if ( mGameSession )
    {
        __DtTestPoint(__DtFunc_update, __DtStep_2)
        mGameSession->polling();
    }

//++mTime;
	++mGameTime;
    mEffectManager->update();
	__DtTestPoint( __DtFunc_update, __DtStep_3 )
}

//---------------------------------------------------------------------
// ● イベント処理
//---------------------------------------------------------------------
int GameManager::HandleEvent( u32 event_, void *args_ )
{

    
         
    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
    return 0;
}

//=============================================================================
//								End of File
//=============================================================================
