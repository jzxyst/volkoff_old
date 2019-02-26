//=============================================================================
//【 GameFrontendManager 】
//=============================================================================

#include "stdafx.h"
#include	"DT_GameFrontendManager.h"	/* For DynamicTracer-TestPoint */
#include "GameFrontendManager.h"
#include "PlayerStateWindow.h"
#include "GuideNamePlate.h"
#include "PointCursor.h"

//=============================================================================
// ■ GameFrontendManager クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
GameFrontendManager::GameFrontendManager()
    : mPlayerStateWindow    ( NULL )
    , mStep                 ( GFM_PTEP_SETUP )
    , mFrameCount           ( 0 )
    , mNamePlateFont        ( NULL )
    , mDamagePop            ( NULL )
    , mGuidNamePlateFont    ( NULL )
    , mPointCursor          ( NULL )
    , mFloorInfoOffset      ( 0.0f )
{
    __DtTestPoint( __DtFunc_GameFrontendManager, __DtStep_0 )
    mFrameXPos.setInitValue( -32 );
    mFrameXPos.set( 12 );
    mFrameXPos.setSpeed( 6 );
	__DtTestPoint( __DtFunc_GameFrontendManager, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
GameFrontendManager::~GameFrontendManager()
{
    __DtTestPoint( __DtFunc_GameFrontendManager, __DtStep_2 )
    finalize();
    
	__DtTestPoint( __DtFunc_GameFrontendManager, __DtStep_3 )
}

//---------------------------------------------------------------------
// ● インスタンスの取得
//---------------------------------------------------------------------
GameFrontendManager* GameFrontendManager::getInstance()
{
    static GameFrontendManager instance;
    __DtTestPoint( __DtFunc_getInstance, __DtStep_0 )
    return &instance;
}

//---------------------------------------------------------------------
// ● 初期化
//---------------------------------------------------------------------
void GameFrontendManager::initialize( Player* player_ )
{
	__DtTestPoint( __DtFunc_initialize, __DtStep_0 )
	mStep = GFM_PTEP_SETUP;
	mFrameCount = 0;
	mFloorInfoOffset = 0;


    mNumberTexture1 = LTexture::create( "Data/Graphics/Frontend/Number_1.png" );
	
    mPlayerStateWindow = NEW PlayerStateWindow( player_ );

    LN_PCALL( Engine::Framework::getInstance()->getGraphicsManager()->createFont( &mNamePlateFont, "МＳ Ｐゴシック" ) );
    mNamePlateFont->setSize( 10 );
    mNamePlateFont->setColor( LColor( 1, 1, 1 ) );
    mNamePlateFont->setAntiAlias( false );


    LN_PCALL( Engine::Framework::getInstance()->getGraphicsManager()->createFont( &mGuidNamePlateFont, "МＳ Ｐゴシック" ) );
    mGuidNamePlateFont->setSize( 10 );
    mGuidNamePlateFont->setColor( LColor( 1, 1, 1 ) );
    //mGuidNamePlateFont->setEdgeSize( 1 );
    //mGuidNamePlateFont->setEdgeColor( LColor( 0.25f, 0.25f, 0.25f ) );
    mGuidNamePlateFont->setAntiAlias( false );

    

    mDamagePop = NEW DamagePop();


    mShowCharacterNamePlateCount = 0;
    mGlobalFadeOpacity.start( 1.0f, 1.0f, 0.1f );

    mLevelupFrameCount = 0;

    LTexture tex = LTexture::create( "Data/Graphics/Frontend/Frontend_1.png" );
    mLevelupSprites[ 0 ] = LSprite::create( tex );//return;
    mLevelupSprites[ 0 ].setSrcRect( 0, 480, 256, 16 );
    mLevelupSprites[ 0 ].setCenter( 128, 8 );
    mLevelupSprites[ 0 ].setVisible( false );
    mLevelupSprites[ 1 ] = LSprite::create( tex );
    mLevelupSprites[ 1 ].setSrcRect( 0, 496, 256, 16 );
    mLevelupSprites[ 1 ].setCenter( 128, 8 );
    mLevelupSprites[ 1 ].setVisible( false );
    mLevelEffectSprite = LSprite::create( tex );
    mLevelEffectSprite.setSrcRect( 0, 416, 64, 64 );
    mLevelEffectSprite.setPosition( 320, 200 );
    mLevelEffectSprite.setCenter( 32, 32 );
    mLevelEffectSprite.setVisible( false );

    mLevelupSprites[ 0 ].setPosition( 320, 200 - 8 );
    mLevelupSprites[ 1 ].setPosition( 320, 200 + 8 );

    mPointCursor = NEW PointCursor();



    mFloorNumAnim.setCapacity( 4 );
    mFloorNumAnim.addKeyFrame( 0, 0.0f );
    mFloorNumAnim.addKeyFrame( 30, 1.0f );
    mFloorNumAnim.addKeyFrame( 90, 1.0f );
    mFloorNumAnim.addKeyFrame( 120, 2.0f );
    mFloorNumAnim[ 0 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mFloorNumAnim[ 1 ].InterMode = LN_ANIM_INTER_LINEAR;
    mFloorNumAnim[ 2 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mFloorNumAnim[ 3 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mFloorNumAnim.setTimeTickPerSec( 1.0f );
    mFloorNumAnim.setTime( 1000 );

    mFloorNumAnimAlpha.setCapacity( 4 );
    mFloorNumAnimAlpha.addKeyFrame( 0, 0.0f );
    mFloorNumAnimAlpha.addKeyFrame( 30, 1.0f );
    mFloorNumAnimAlpha.addKeyFrame( 90, 1.0f );
    mFloorNumAnimAlpha.addKeyFrame( 120, 0.0f );
    mFloorNumAnimAlpha[ 0 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mFloorNumAnimAlpha[ 1 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mFloorNumAnimAlpha[ 2 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mFloorNumAnimAlpha[ 3 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mFloorNumAnimAlpha.setTimeTickPerSec( 1.0f );
    mFloorNumAnimAlpha.setTime( 1000 );

    mFloorInfoTexture = LTexture::create( "Data/Graphics/Frontend/FloorInfo_1.png" );
    for ( int i = 0; i < 3; ++i )
    {
        __DtTestPoint(__DtFunc_initialize, __DtStep_1)
        mFloorInfoSprite[ i ] = LSprite::create( mFloorInfoTexture );
        mFloorInfoSprite[ i ].setVisible( false );
    }
    mFloorInfoSprite[ 0 ].setSrcRect( 0, 0, 512, 32 ); // 下線
	__DtTestPoint( __DtFunc_initialize, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void GameFrontendManager::finalize()
{
    __DtTestPoint( __DtFunc_finalize, __DtStep_0 )
    SAFE_DELETE( mPlayerStateWindow );
    LN_SAFE_RELEASE( mNamePlateFont );
    LN_SAFE_RELEASE( mGuidNamePlateFont );
    SAFE_DELETE( mDamagePop );
    SAFE_DELETE( mPointCursor );

	mNumberTexture1 = nil;
	mLevelupSprites[ 0 ] = nil;
	mLevelupSprites[ 1 ] = nil;
	mLevelEffectSprite = nil;
	mFloorInfoTexture = nil;
	mFloorInfoSprite[ 0 ] = nil;
	mFloorInfoSprite[ 1 ] = nil;
	mFloorInfoSprite[ 2 ] = nil;
	__DtTestPoint( __DtFunc_finalize, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void GameFrontendManager::update()
{
    __DtTestPoint( __DtFunc_update, __DtStep_0 )
    mPlayerStateWindow->update();
    mDamagePop->update();
    mPointCursor->update();

    {
        GuideNamePlateList::iterator itr = mGuideNamePlateList.begin();
        GuideNamePlateList::iterator end = mGuideNamePlateList.end();
        for ( ; itr != end; ++itr )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_1)
            (*itr)->update();
        }
    }

    switch ( mStep )
    {
        ///////////////////////////////////////// 開始状態
        case GFM_PTEP_SETUP:
        {
            __DtTestPoint(__DtFunc_update, __DtStep_2)
            mPlayerStateWindow->setPosition( mFrameXPos.getValue(), 12 );
            mPlayerStateWindow->setOpacity( static_cast< float >( mFrameCount ) / 20.0f );

            ++mFrameCount;
            if ( mFrameCount == 20 )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_3)
                mStep = GFM_PTEP_IDLE;
            }
            mFrameXPos.update();
            break;
        }
        ///////////////////////////////////////// 待機状態
        case GFM_PTEP_IDLE:
        {
            __DtTestPoint(__DtFunc_update, __DtStep_4)
            break;
        }
    };



    if ( mShowCharacterNamePlateCount > 0 )
    {
        __DtTestPoint(__DtFunc_update, __DtStep_5)
        --mShowCharacterNamePlateCount;
        if ( mShowCharacterNamePlateCount == 0 )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_6)
            mGlobalFadeOpacity.start( mGlobalFadeOpacity.getValue(), 1.0f, 20.0 );
        }
    }

    // GuidNamePlate 全体の透明度
    if ( !mGlobalFadeOpacity.isFinished() )
    {
        __DtTestPoint(__DtFunc_update, __DtStep_7)
        mGlobalFadeOpacity.advanceTime( 1.0 );
    }


    //---------------------------------------------------------
    // レベルアップ関係
    if ( mLevelupFrameCount > 0 )
    {
        // 閃光
        __DtTestPoint(__DtFunc_update, __DtStep_8)
        if ( mLevelupFrameCount >= 50 )
        {
            float c = static_cast< float >( mLevelupFrameCount - 50 );

            __DtTestPoint(__DtFunc_update, __DtStep_9)
            mLevelEffectSprite.setScale(
                7.0f * (10.0f - c) + 1.0f,
                0.8f * c );

            mLevelEffectSprite.setOpacity( 0.05f + c / 10.0f );

            if ( mLevelupFrameCount == 50 )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_10)
                mLevelEffectSprite.setVisible( false );
            }
        }

        // 文字フェードイン
        if ( mLevelupFrameCount >= 50 )
        {
            float c = static_cast< float >( 10 - ( mLevelupFrameCount - 50 ) );
            __DtTestPoint(__DtFunc_update, __DtStep_11)
            mLevelupSprites[ 0 ].setOpacity( c / 10.0f );
            mLevelupSprites[ 1 ].setOpacity( c / 10.0f );
        }

        // 文字フェードアウト
        if ( mLevelupFrameCount < 10 )
        {
            float c = static_cast< float >( mLevelupFrameCount - 1 );
            float rate = c / 10.0f;

            __DtTestPoint(__DtFunc_update, __DtStep_12)
            mLevelupSprites[ 0 ].setOpacity( rate );
            mLevelupSprites[ 1 ].setOpacity( rate );

            mLevelupSprites[ 0 ].setScale( 1.0f + (10.0f - c), rate );
            mLevelupSprites[ 1 ].setScale( 1.0f + (10.0f - c), rate );
        }


        --mLevelupFrameCount;

        if ( mLevelupFrameCount == 0 )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_13)
            mLevelupSprites[ 0 ].setVisible( false );
            mLevelupSprites[ 1 ].setVisible( false );
            mLevelEffectSprite.setVisible( false );
        }
    }
    
    //---------------------------------------------------------
    // フロア数
    if ( !mFloorNumAnim.isFinished() )
    {
        float v = mFloorNumAnim.getValue();
        
        __DtTestPoint(__DtFunc_update, __DtStep_14)
        mFloorInfoSprite[ 0 ].setPosition( 300 - v * 32, 448 );
        mFloorInfoSprite[ 1 ].setPosition( mFloorInfoOffset + 320 + v * 32, 400 );
        mFloorInfoSprite[ 2 ].setPosition( 520, 320 + v * 48 );

        float a = mFloorNumAnimAlpha.getValue();
        for ( int i = 0; i < 3; ++i )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_15)
            mFloorInfoSprite[ i ].setOpacity( a );
        }

        mFloorNumAnim.advanceTime( 1.0f );
        mFloorNumAnimAlpha.advanceTime( 1.0f );


        if ( mFloorNumAnim.isFinished() )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_16)
            for ( int i = 0; i < 3; ++i )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_17)
                mFloorInfoSprite[ i ].setVisible( false );
            }
        }
    }
	__DtTestPoint( __DtFunc_update, __DtStep_18 )
}

//---------------------------------------------------------------------
// ● 画面中央に「LevelUp」表示
//---------------------------------------------------------------------
void GameFrontendManager::showLevelUp()
{
    __DtTestPoint( __DtFunc_showLevelUp, __DtStep_0 )
    mLevelupFrameCount = 60;

    

    mLevelupSprites[ 0 ].setOpacity( 0 );
    mLevelupSprites[ 1 ].setOpacity( 0 );

    mLevelupSprites[ 0 ].setScale( 1 );
    mLevelupSprites[ 1 ].setScale( 1 );

    mLevelupSprites[ 0 ].setVisible( true );
    mLevelupSprites[ 1 ].setVisible( true );
    mLevelEffectSprite.setVisible( true );
	__DtTestPoint( __DtFunc_showLevelUp, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● フロア変更時のフロア数表示エフェクトの表示開始
//---------------------------------------------------------------------
void GameFrontendManager::showFloorNum( int num_ )
{
    __DtTestPoint( __DtFunc_showFloorNum, __DtStep_0 )
    for ( int i = 0; i < 3; ++i )
    {
        __DtTestPoint(__DtFunc_showFloorNum, __DtStep_1)
        mFloorInfoSprite[ i ].setVisible( true );
        mFloorInfoSprite[ i ].setOpacity( 0 );
    }

    if ( num_ < 8 )
    {
        __DtTestPoint(__DtFunc_showFloorNum, __DtStep_2)
        mFloorInfoSprite[ 1 ].setSrcRect( 0, 32, 160, 64 );

        int x = num_ % 5;
        int y = num_ / 5;
        mFloorInfoSprite[ 2 ].setSrcRect( x * 96, 128 + y * 96, 96, 96 );
    }
    // ラストフロア
    else
    {
        __DtTestPoint(__DtFunc_showFloorNum, __DtStep_3)
        mFloorInfoSprite[ 1 ].setSrcRect( 160, 32, 352, 64 );
        mFloorInfoSprite[ 2 ].setSrcRect( 0, 96, 8, 8 );    // 透明
        mFloorInfoOffset = -50.0;
    }


    mFloorNumAnim.setTime( 0.0f );
    mFloorNumAnimAlpha.setTime( 0.0f );
	__DtTestPoint( __DtFunc_showFloorNum, __DtStep_4 )
}

//---------------------------------------------------------------------
// ● (GuidNamePlate のコンストラクタから呼ばれる)
//---------------------------------------------------------------------
void GameFrontendManager::addGuidNamePlate( GuideNamePlate* plate_ )
{
    __DtTestPoint( __DtFunc_addGuidNamePlate, __DtStep_0 )
    mGuideNamePlateList.push_back( plate_ );
	__DtTestPoint( __DtFunc_addGuidNamePlate, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● (GuidNamePlate のデストラクタから呼ばれる)
//---------------------------------------------------------------------
void GameFrontendManager::removeGuidNamePlate( GuideNamePlate* plate_ )
{
    __DtTestPoint( __DtFunc_removeGuidNamePlate, __DtStep_0 )
    if ( !mGuideNamePlateList.empty() )
    {
        __DtTestPoint(__DtFunc_removeGuidNamePlate, __DtStep_1)
        mGuideNamePlateList.remove( plate_ );
    }
	__DtTestPoint( __DtFunc_removeGuidNamePlate, __DtStep_2 )
}


//---------------------------------------------------------------------
// ● CharacterNamePlate::show が呼ばれた時のコールバック
//---------------------------------------------------------------------
void GameFrontendManager::onShowCharacterNamePlate()
{ 
    __DtTestPoint( __DtFunc_onShowCharacterNamePlate, __DtStep_0 )
    mShowCharacterNamePlateCount = 100; 

    mGlobalFadeOpacity.start( mGlobalFadeOpacity.getValue(), 0.0f, 20.0 );
	__DtTestPoint( __DtFunc_onShowCharacterNamePlate, __DtStep_1 )
}


//=============================================================================
//								end of file
//=============================================================================