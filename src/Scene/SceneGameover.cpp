//=============================================================================
//【 SceneGameover 】
//=============================================================================

#include "stdafx.h"
#include	"DT_SceneGameover.h"	/* For DynamicTracer-TestPoint */
#include "../Game/GameManager.h"
#include "../Map/MapManager.h"
#include "../Frontend/PointCursor.h"
#include "SceneGameover.h"
#include "SceneGame.h"
#include "SceneTitle.h"

//=============================================================================
// ■ SceneGameover クラス
//=============================================================================


static const int COMMAND_POS_X = 420;
static const int COMMAND_POS_Y = 290;
    
//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneGameover::onStart()
{
    LTexture tex = LTexture::create( 32, 32 );
    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    tex.clear( LColor( 0, 0, 0 ) );
    mBlindSprite = LSprite::create( tex );
    mBlindSprite.setScale( 20 );
    mBlindSprite2 = LSprite::create( tex );
    mBlindSprite2.setScale( 20 );
    mBlindSprite2.setPosition( 0, 240 );
    mBlindSprite2.setOpacity( 0 );


    // 説明ウィンドウ
    LTexture fe_tex = LTexture::create( "Data/Graphics/Frontend/Frontend_1.png" );
    mDescWindowSprite = LSprite::create( fe_tex );
    mDescWindowSprite.setPosition( 60, 280 );
    mDescWindowSprite.setSrcRect( 272, 368, 240, 144 );
    mDescWindowSprite.setOpacity( 0 );
    mDescContents = LTexture::create( 240, 144 );
    mDescContentsSprite = LSprite::create( mDescContents );
    mDescContentsSprite.setPosition( 60, 280 );
    mDescContentsSprite.setOpacity( 0 );

    mDescTitleFont = LFont::createDefaultFont();
    mDescTitleFont.setSize( 12 );
    mDescTitleFont.setColor( 1, 1, 1, 1 );

    // コマンド
    mCommandSprite[ 0 ] = LSprite::create( fe_tex );
    mCommandSprite[ 0 ].setSrcRect( 272, 304, 128, 32 );
    mCommandSprite[ 0 ].setPosition( COMMAND_POS_X, COMMAND_POS_Y );
    mCommandSprite[ 0 ].setOpacity( 0 );
    mCommandSprite[ 1 ] = LSprite::create( fe_tex );
    mCommandSprite[ 1 ].setSrcRect( 272, 336, 128, 32 );
    mCommandSprite[ 1 ].setPosition( COMMAND_POS_X, COMMAND_POS_Y + 32 );
    mCommandSprite[ 1 ].setOpacity( 0 );

    // 制御文字列描画クラス
    LFont desc_text = LFont::createDefaultFont();
    desc_text.setSize( 15 );
    desc_text.setColor( 1, 1, 1, 1 );
    mFormatText.setFont( desc_text.getInterface() );
    mFormatText.setDrawRect( LRect( 12, 20, 224, 120 ) );

    // GameOver
    mLogoSprite = LSprite::create( fe_tex );
    mLogoSprite.setSrcRect( 160, 224, 352, 64 );
    mLogoSprite.setPosition( 320, 128 );
    mLogoSprite.setCenter( 352 / 2, 64 / 2 );
    mLogoSprite.setOpacity( 0 );

    // カーソル
    mPointCursor = NEW PointCursor();

    // BGM フェードアウト
    Audio.stopBGM( 5000 );

    
    mStep = 0;
    mFrameCount = 0;
    mSelectIndex = 0;

    
	__DtTestPoint( __DtFunc_onStart, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneGameover::onUpdate()
{
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    mPointCursor->update();

    // 説明文描画中
    if ( !mFormatText.isFinished() )
    {
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
        mFormatText.update();
        LNFormatTextDrawData data;
        while ( mFormatText.getNextDrawData( &data ) )
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_2)
            mDescContents.getInterface()->setFont( data.Font );
            mDescContents.drawText( data.Text, data.Rect, LN_TEXTALIGN_LEFT, data.Length );
        }
    }

    switch ( mStep )
    {
        /////////////////////// ブラインド中
        case 0:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_3)
            mBlindSprite.setOpacity( static_cast< float >( mFrameCount ) / 180 );
            ++mFrameCount;
            if ( mFrameCount == 120 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_4)
                mStep = 1;
                mFrameCount = 0;
                mLogoFadeValue.start( 0.0f, 1.0f, 1.0f );
            }
            break;
        }
        /////////////////////// GameOver フェードイン中
        case 1:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_5)
            mLogoFadeValue.advanceTime( 0.016f );
            mLogoSprite.setOpacity( mLogoFadeValue.getValue() );

            float y = ( 1.0f - mLogoFadeValue.getValue() ) * 32 + 128;
            mLogoSprite.setPosition( 320, y );

            
            if ( mFrameCount == 60 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_6)
                mStep = 2;
                mFrameCount = 0;
                mFadeValue.start( 0.0f, 1.0f, 30.0f );
                _onSelectIndex();
            }
            ++mFrameCount;
            break;
        }
        /////////////////////// コンテンツフェードイン中
        case 2:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_7)
            mFadeValue.advanceTime( 1.0f );

            float op = mFadeValue.getValue();
            mDescWindowSprite.setOpacity( op );
            mDescContentsSprite.setOpacity( op );
            mCommandSprite[ 0 ].setOpacity( op );
            mCommandSprite[ 1 ].setOpacity( op );
            mBlindSprite2.setOpacity( op / 2 );

            ++mFrameCount;
            if ( mFrameCount == 60 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_8)
                mStep = 3;
                mFrameCount = 0;
            }
            break;
        }
        /////////////////////// コンテンツ選択中
        case 3:
        {
            // 決定
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_9)
            if ( Input.isOnTrigger( LN_BUTTON_A ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_10)
                mPointCursor->moveToInit();
                mStep = 4;
                mFrameCount = 0;
                LLayer::getBGLayer()->setTone( LTone( -1, -1, -1, -1 ), 1.0f );
            }

            // ↑
            if ( Input.isRepeat( LN_BUTTON_UP ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_11)
                --mSelectIndex;
                if ( mSelectIndex < 0 )
                {
                    __DtTestPoint(__DtFunc_onUpdate, __DtStep_12)
                    mSelectIndex = 1;
                }
                _onSelectIndex();
            }
            // ↓
            if ( Input.isRepeat( LN_BUTTON_DOWN ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_13)
                ++mSelectIndex;
                if ( mSelectIndex > 1 )
                {
                    __DtTestPoint(__DtFunc_onUpdate, __DtStep_14)
                    mSelectIndex = 0;
                }
                _onSelectIndex();
            }
            break;
        }
        /////////////////////// 終了中
        case 4:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_15)
            if ( mFrameCount == 60 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_16)
                if ( mSelectIndex == 0 )
                {

                    // 仮
                    //Audio.playBGM("Data/Sound/BGM/sol_battle014_xp.mid",60);

					__DtTestPoint(__DtFunc_onUpdate, __DtStep_17)
					if ( MapManager::getInstance()->getMapID() != 7 )
					{

						__DtTestPoint(__DtFunc_onUpdate, __DtStep_18)
						Audio.playBGM(MAIN_BGM_NAME,60);
					}

                    GameManager::getInstance()->reset();
                    this->returnScene();
                }
                else
                {
                    __DtTestPoint(__DtFunc_onUpdate, __DtStep_19)
                    GameManager::getInstance()->finalize();
                    this->changeScene( NEW SceneTitle() );
                }
            }
            ++mFrameCount;
            break;
        }
    }

	// 以前はこの関数 (SceneGameover::onUpdate()) の先頭で親シーンの onUpdate() を呼び出していた。
	// しかし、コンティニュー時に現在のマップを再構築した後に onUpdate() が呼ばれなかったため、
	// 古いオブジェクトたちの解放が1フレーム遅れていた。(必要なくなったオブジェクトは onUpdate() で開放しているため)
	// 結果、一瞬だけ2倍相当のオブジェクトが出現することになり、描画可能なスプライト数を超えてしまった。
    this->getParentScene()->onUpdate();
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_20 )
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneGameover::onTerminate()
{

    __DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
    LLayer::getBGLayer()->setTone( LTone( 0, 0, 0, 0 ), 1.0f );

    SAFE_DELETE( mPointCursor );
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● 選択している項目を変更した
//---------------------------------------------------------------------
void SceneGameover::_onSelectIndex()
{
    __DtTestPoint( __DtFunc__onSelectIndex, __DtStep_0 )
    mPointCursor->moveTo( COMMAND_POS_X - 38, COMMAND_POS_Y + mSelectIndex * 32 + 16 );

    mDescContents.clear( LColor( 0, 0, 0, 0 ) );

    if ( mSelectIndex == 0 )
    {
        __DtTestPoint(__DtFunc__onSelectIndex, __DtStep_1)
        mDescContents.setFont( mDescTitleFont );
        mDescContents.drawText( "Continue", LRect( 8, 2, 256, 256 ) );

        mFormatText.setText( "ステージの最初からやり直します。\n\nスコアが 0 にリセットされます。" );
        mFormatText.build();
    }
    else
    {
        __DtTestPoint(__DtFunc__onSelectIndex, __DtStep_2)
        mDescContents.setFont( mDescTitleFont );
        mDescContents.drawText( "End", LRect( 8, 2, 256, 256 ) );

        mFormatText.setText( "タイトル画面に戻ります。" );
        mFormatText.build();
    }
	__DtTestPoint( __DtFunc__onSelectIndex, __DtStep_3 )
}



//=============================================================================
//								end of file
//=============================================================================