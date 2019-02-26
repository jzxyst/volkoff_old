//=============================================================================
//【 PlayerStateWindow 】
//=============================================================================

#include "stdafx.h"
#include	"DT_PlayerStateWindow.h"	/* For DynamicTracer-TestPoint */
#include "../Utility/Util.h"
#include "../Object/Player.h"
#include "../Object/Weapon.h"
#include "../Game/GameManager.h"
#include "PlayerStateWindow.h"



//=============================================================================
// ■ PlayerStateWindow クラス
//=============================================================================


    //---------------------------------------------------------------------
    // ● コンストラクタ
    //---------------------------------------------------------------------
    PlayerStateWindow::PlayerStateWindow( Player* player_ )
        : mPlayer               ( player_ )
        , mStep                 ( PSW_PTEP_SETUP )
        , mLastWeaponCount      ( 0 )
        , mWarningFrameCount    ( 0 )
        , mWarningShowedFlag    ( 0 )
        , mHPDieWidth           ( 0 )
        , mDieWaitFrameCount    ( 0 )
        , mEXPBarFrameCount     ( 0 )
        , mHasKey               ( 0 )
        , mKeyEffectFrameCount  ( 0 )
    {
        __DtTestPoint( __DtFunc_PlayerStateWindow, __DtStep_0 )
        mHPNumber.setSpeed( 8 );

        mFrontendTexture = LTexture::create( "Data/Graphics/Frontend/Frontend_1.png" );
        mNumberTextureS  = LTexture::create( "Data/Graphics/Frontend/Number_2.png" );
        mNumberTextureL  = LTexture::create( "Data/Graphics/Frontend/Number_3.png" );

        mFrameWindow = LSprite::create( mFrontendTexture );
        mFrameWindow->setSrcRect( LRect( 128, 0, 128, 112 ) );

        // フロア数とスコアの数字
        mFloorNumSprite[ 0 ] = LSprite::create( mNumberTextureS );
        mFloorNumSprite[ 1 ] = LSprite::create( mNumberTextureS );
        mFloorNumSprite[ 0 ].setVisible( false );
        for ( int i = 0; i < 10; ++i )
        {
            __DtTestPoint(__DtFunc_PlayerStateWindow, __DtStep_1)
            mScoreNumSprite[ i ] = LSprite::create( mNumberTextureS );
        }


        // HP 関係
        mHPBarSprite    = LSprite::create( mFrontendTexture );
        mHPDieBarSprite = LSprite::create( mFrontendTexture );
        mHPBarSprite->setSrcRect( LRect( 256, 0, 120, 18 ) );
        mHPDieBarSprite->setSrcRect( LRect( 376, 0, 0, 18 ) );
        mHPDieBarSprite->setVisible( false );

        // 武器アイコン
        mWeaponIconSprite = LSprite::create( mFrontendTexture );

        // 武器レベル
        mWeaponLevelSprite = LSprite::create( mNumberTextureS );
        mWeaponEXPBar = LSprite::create( mFrontendTexture );
        mWeaponEXPBar->setSrcRect( 256, 57, 40, 7 );

        // 使用回数
        for ( int i = 0; i < 3; ++i )
        {
            __DtTestPoint(__DtFunc_PlayerStateWindow, __DtStep_2)
            mWeaponCountSprite[ i ] = LSprite::create( mNumberTextureL );
            mWeaponCountWarningSprite[ i ] = LSprite::create( mNumberTextureL );
            mWeaponCountWarningSprite[ i ]->setVisible( false );
            mWeaponCountWarningSprite[ i ]->setScale( 3.0f );
        }

        // 鍵
        mKeySprite = LSprite::create( mFrontendTexture );
        mKeySprite->setSrcRect( 104, 0, 24, 32 );
        mKeySprite->setCenter( 12, 16 );
        mKeySprite->setPosition( 118, 74 );
        mKeySprite->setVisible( false );
        mKeyEffectSprite[ 0 ] = LSprite::create( mFrontendTexture );
        mKeyEffectSprite[ 0 ]->setSrcRect( 104, 32, 24, 24 );
        mKeyEffectSprite[ 0 ]->setCenter( 12, 12 );
        mKeyEffectSprite[ 0 ]->setPosition( 118, 68 );
        mKeyEffectSprite[ 0 ]->setVisible( false );
        mKeyEffectSprite[ 1 ] = LSprite::create( mFrontendTexture );
        mKeyEffectSprite[ 1 ]->setSrcRect( 104, 0, 24, 32 );
        mKeyEffectSprite[ 1 ]->setCenter( 12, 16 );
        mKeyEffectSprite[ 1 ]->setPosition( 118 + 10, 68 + 10 );
        mKeyEffectSprite[ 1 ]->setVisible( false );

        // プレイヤーの HP を覚えておく
        mPlayerHP = mPlayer->getLife();
        mHPNumber.set( mPlayer->getLife() );

        setPosition( 12, 12 );
        
        refresh();
    	__DtTestPoint( __DtFunc_PlayerStateWindow, __DtStep_3 )
    }

    //---------------------------------------------------------------------
    // ● デストラクタ
    //---------------------------------------------------------------------
    PlayerStateWindow::~PlayerStateWindow()
    {
    	__DtTestPoint( __DtFunc_PlayerStateWindow, __DtStep_4 )
    }

    //---------------------------------------------------------------------
    // ● 位置の設定
    //---------------------------------------------------------------------
    void PlayerStateWindow::setPosition( float x_, float y_ )
    {
        __DtTestPoint( __DtFunc_setPosition, __DtStep_0 )
        mFrameWindow->setPosition( x_, y_ );
        mWeaponIconSprite->setPosition( x_ + 8, y_ + 69 ); //56

        for ( int i = 0; i < 2; ++i )
        {
            //mFloorNumSprite[ i ]->setPosition( x_ + 12 + 8 * i, y_ + 3 );
            __DtTestPoint(__DtFunc_setPosition, __DtStep_1)
            mFloorNumSprite[ i ]->setPosition( x_ + 12 + 8 * i - 4, y_ + 3 );
        }

        for ( int i = 0; i < 10; ++i )
        {
            __DtTestPoint(__DtFunc_setPosition, __DtStep_2)
            mScoreNumSprite[ i ]->setPosition( x_ + 38 + 8 * i, y_ + 3 );
        }

        mHPBarSprite->setPosition( x_ + 4, y_ + 18 );

        mWeaponEXPBar->setPosition( x_ + 49, y_ + 38, 0.1f );

        for ( int i = 0; i < 3; ++i )
        {
            __DtTestPoint(__DtFunc_setPosition, __DtStep_3)
            mWeaponCountSprite[ i ]->setPosition( x_ + 54 + 9 * i, y_ + 81 );
        }

        mPosition.set( x_, y_, 0.0f );
    	__DtTestPoint( __DtFunc_setPosition, __DtStep_4 )
    }

    //---------------------------------------------------------------------
    // ● 不透明度の設定
    //---------------------------------------------------------------------
    void PlayerStateWindow::setOpacity( float op_ )
    {
        __DtTestPoint( __DtFunc_setOpacity, __DtStep_0 )
        mFrameWindow->setOpacity( op_ );
        mWeaponIconSprite->setOpacity( op_ );

        for ( int i = 0; i < 2; ++i )
        {
            __DtTestPoint(__DtFunc_setOpacity, __DtStep_1)
            mFloorNumSprite[ i ]->setOpacity( op_ );
        }

        for ( int i = 0; i < 10; ++i )
        {
            __DtTestPoint(__DtFunc_setOpacity, __DtStep_2)
            mScoreNumSprite[ i ]->setOpacity( op_ );
        }

        mHPBarSprite->setOpacity( op_ );
        mHPDieBarSprite->setOpacity( op_ );
        mWeaponLevelSprite->setOpacity( op_ ); 
        mHPDieBarSprite->setOpacity( op_ );
		mWeaponEXPBar->setOpacity( op_ );

        for ( int i = 0; i < 3; ++i )
        {
            __DtTestPoint(__DtFunc_setOpacity, __DtStep_3)
            mWeaponCountSprite[ i ]->setOpacity( op_ );
        }
    	__DtTestPoint( __DtFunc_setOpacity, __DtStep_4 )
    }

    

    //---------------------------------------------------------------------
    // ● リフレッシュ
    //---------------------------------------------------------------------
    void PlayerStateWindow::refresh()
    {
        
    	__DtTestPoint( __DtFunc_refresh, __DtStep_0 )
    }

    //---------------------------------------------------------------------
    // ● フレーム更新
    //---------------------------------------------------------------------
    void PlayerStateWindow::update()
    {
        u32 nums[ 12 ];

        // フロア数
        __DtTestPoint( __DtFunc_update, __DtStep_0 )
        Util::numberToArray( GameManager::getInstance()->getFloorNum() + 1, 2, nums );
        //mFloorNumSprite[ 0 ]->setSrcRect( LRect( 7 * nums[ 0 ], 0, 7, 11 ) );
        mFloorNumSprite[ 1 ]->setSrcRect( LRect( 7 * nums[ 1 ], 0, 7, 11 ) );

        // スコア
        Util::numberToArray(  GameManager::getInstance()->getScore(), 10, nums );
        for ( int i = 0; i < 10; ++i )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_1)
            mScoreNumSprite[ i ]->setSrcRect( LRect( 7 * nums[ i ], 0, 7, 11 ) );
        }


        // 武器アイコン
        mWeaponIconSprite->setSrcRect( LRect( 128 + 32 * mPlayer->getWeaponData().WeaponType, 128, 32, 32 ) );

        //-----------------------------------------------------
        // レベル
        int level = mPlayer->getLevel();
        if ( level >= MAX_PLAYER_LEVELS )   // MAX
        {
            
            __DtTestPoint(__DtFunc_update, __DtStep_2)
            mWeaponLevelSprite->setTexture( mFrontendTexture );
            mWeaponLevelSprite->setSrcRect( 256, 64, 32, 16 );
            mWeaponLevelSprite->setPosition( mPosition.x + 24, mPosition.y + 40 );
            

            mWeaponEXPBar->setSrcRect( 256 + mEXPBarFrameCount, 57, 48, 7 );

            



            
            ++mEXPBarFrameCount;
            if ( mEXPBarFrameCount >= 80 )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_3)
                mEXPBarFrameCount = 0;
            }
        }
        else
        {
            __DtTestPoint(__DtFunc_update, __DtStep_4)
            mWeaponLevelSprite->setTexture( mNumberTextureS );
            mWeaponLevelSprite->setSrcRect( 7 * level, 0, 7, 11 );
            mWeaponLevelSprite->setPosition( mPosition.x + 24, mPosition.y + 39 );


            float rate;// = static_cast< float >( mPlayer->getExp() ) / scg_nNextLevelExpTotal[ level - 1 ];
            if ( level == 1 )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_5)
                rate = static_cast< float >( mPlayer->getExp() ) / scg_nNextLevelExpTotal[ level - 1 ];
            }
            else
            {
                int exp  = mPlayer->getExp() - scg_nNextLevelExpTotal[ level - 2 ];
                int next = scg_nNextLevelExpTotal[ level - 1 ] - scg_nNextLevelExpTotal[ level - 2 ];
                __DtTestPoint(__DtFunc_update, __DtStep_6)
                rate = static_cast< float >( exp ) / next;
            }

            rate = LMath::min( rate, 1.0f );

            mWeaponEXPBar->setSrcRect( 256 + mEXPBarFrameCount, 57, rate * 48, 7 );

        }

        //-----------------------------------------------------
        // 武器使用回数
        const WeaponData& weapon_data = mPlayer->getWeaponData();
        if ( weapon_data.WeaponType != WEAPON_NON )
        {
            int cnt = weapon_data.UseCount;
            int c1 = cnt / 100;
            int c2 = ( cnt - c1 * 100 ) / 10;
            int c3 = cnt % 10;

            // 3割以下は赤く表示
            int wy = 0;
            float rate = static_cast< float >( cnt ) / gWeaponBaseData[ weapon_data.WeaponType ].UseCount;
            __DtTestPoint(__DtFunc_update, __DtStep_7)
            if ( rate <= 0.5f )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_8)
                wy = 1;
            }

            mWeaponCountSprite[ 0 ]->setSrcRect( LRect( 8 * c1, wy * 16, 8, 14 ) );
            mWeaponCountSprite[ 1 ]->setSrcRect( LRect( 8 * c2, wy * 16, 8, 14 ) );
            mWeaponCountSprite[ 2 ]->setSrcRect( LRect( 8 * c3, wy * 16, 8, 14 ) );
            mWeaponCountSprite[ 0 ]->setVisible( true );
            mWeaponCountSprite[ 1 ]->setVisible( true );
            mWeaponCountSprite[ 2 ]->setVisible( true );


            // 警告を表示
            if ( wy == 1 && cnt != mLastWeaponCount )
            {
                
                bool show = false;

                __DtTestPoint(__DtFunc_update, __DtStep_9)
                if ( rate <= 0.5f && mWarningShowedFlag < 1 )
                {
                    __DtTestPoint(__DtFunc_update, __DtStep_10)
                    show = true;
                    mWarningShowedFlag = 1;
                }
                else if ( rate <= 0.33f && mWarningShowedFlag < 2 )
                {
                    __DtTestPoint(__DtFunc_update, __DtStep_11)
                    show = true;
                    mWarningShowedFlag = 2;
                }
                
                if ( show )
                {
                    __DtTestPoint(__DtFunc_update, __DtStep_12)
                    mWarningFrameCount = 60;
                    for ( int i = 0; i < 3; ++i )
                    {
                        __DtTestPoint(__DtFunc_update, __DtStep_13)
                        mWeaponCountWarningSprite[ i ]->setSrcRect( mWeaponCountSprite[ i ]->getSrcRect() );
                        mWeaponCountWarningSprite[ i ]->setVisible( true );
                    }
                }
            }

            mLastWeaponCount = cnt;

            // 50% 以上に回復していたら警告フラグをリセット
            if ( rate > 0.5f )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_14)
                mWarningShowedFlag = 0;
            }

        }
        // 素手の場合は何も表示しない
        else
        {
            __DtTestPoint(__DtFunc_update, __DtStep_15)
            mWeaponCountSprite[ 0 ]->setVisible( false );
            mWeaponCountSprite[ 1 ]->setVisible( false );
            mWeaponCountSprite[ 2 ]->setVisible( false );
        }

        // 警告表示中の場合
        if ( mWarningFrameCount > 0 )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_16)
            --mWarningFrameCount;

            float x = mPosition.x + 54 + ( 60 - mWarningFrameCount );
            float y = mPosition.y + 68 + ( 60 - mWarningFrameCount ) / 2;

            for ( int i = 0; i < 3; ++i )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_17)
                mWeaponCountWarningSprite[ i ]->setPosition( x + 24 * i, y );
                mWeaponCountWarningSprite[ i ]->setOpacity( mWarningFrameCount * 0.016f );
            }


            // 警告の表示終了
            if ( mWarningFrameCount == 0 )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_18)
                for ( int i = 0; i < 3; ++i )
                {
                    __DtTestPoint(__DtFunc_update, __DtStep_19)
                    mWeaponCountWarningSprite[ i ]->setVisible( false );
                }
            }
        }


        switch ( mStep )
        {
            ///////////////////////////////////////// 開始状態
            case PSW_PTEP_SETUP:
            {
                // プレイヤーの HP にわずかでも変化があったらセットアップ中断
                __DtTestPoint(__DtFunc_update, __DtStep_20)
                if ( mPlayerHP != mPlayer->getLife() || mHPNumber.isFinished() )
                {
                    __DtTestPoint(__DtFunc_update, __DtStep_21)
                    mPlayerHP = mPlayer->getLife();
                    mStep = PSW_PTEP_IDLE;
                }
                // HP バー
                float rate = static_cast< float >( mHPNumber.getValue() ) / mPlayer->getMaxLife();
                mHPBarSprite->setSrcRect( LRect( 256, 0, rate * 120, 18 ) );
                mHPNumber.update();
            }

            ///////////////////////////////////////// 監視状態
            case PSW_PTEP_IDLE:
            {
                __DtTestPoint(__DtFunc_update, __DtStep_22)
                if ( mPlayerHP != mPlayer->getLife() )
                {
                    int prev_hp = mPlayerHP;

                    // 回復したかどうか
                    bool heal = ( mPlayerHP < mPlayer->getLife() );

                    // HP 記憶
                    __DtTestPoint(__DtFunc_update, __DtStep_23)
                    mPlayerHP = mPlayer->getLife();

                    // HP バーはプレイヤーの実 HP に合わせる
                    float rate = static_cast< float >( mPlayer->getLife() ) / mPlayer->getMaxLife();
                    float width = rate * 120;
                    float y = 0;

                    // 残り HP によってバーの色を変える
                    if ( rate <= 0.15f )
                    {
                        __DtTestPoint(__DtFunc_update, __DtStep_24)
                        y = 36;
                    }
                    else if ( rate <= 0.50f )
                    {
                        __DtTestPoint(__DtFunc_update, __DtStep_25)
                        y = 18;
                    }

                    mHPBarSprite->setSrcRect( LRect( 256, y, width, 18 ) );


                    // 回復した場合
                    if ( heal )
                    {
                        __DtTestPoint(__DtFunc_update, __DtStep_26)
                        mHPDieBarSprite->setVisible( false );
                        mDieWaitFrameCount = 0;
                        mHPDieWidth = 0;
                    }
                    // ダメージを受けた場合
                    else
                    {
                        __DtTestPoint(__DtFunc_update, __DtStep_27)
                        rate = static_cast< float >( prev_hp - mPlayerHP ) / mPlayer->getMaxLife();
                        mHPDieWidth += rate * 120;

                        mHPDieBarSprite->setVisible( true );
                        mHPDieBarSprite->setPosition( mHPBarSprite->getPosition().x + width - 1, mHPBarSprite->getPosition().y );
                        mHPDieBarSprite->setSrcRect( 376 + width - 1, 0, mHPDieWidth + 1, 18 );
                        mDieWaitFrameCount = 30;
                    }
                }

                // HP の無くなった部分の減少処理
                if ( mDieWaitFrameCount > 0 )
                {
                    __DtTestPoint(__DtFunc_update, __DtStep_28)
                    --mDieWaitFrameCount;
                }
                else if ( mHPDieWidth > 0 )
                {
                    __DtTestPoint(__DtFunc_update, __DtStep_29)
                    --mHPDieWidth;
                    mHPDieBarSprite->setSrcRect( mHPDieBarSprite->getSrcRect().x, 0, mHPDieWidth + 1, 18 );
                    if ( mHPDieWidth == 0 )
                    {
                        __DtTestPoint(__DtFunc_update, __DtStep_30)
                        mHPDieBarSprite->setVisible( false );
                    }
                }
            }
        }

        //-----------------------------
        // 鍵

        u8 keyflag = GameManager::getInstance()->getKeyflag();
        if ( mHasKey != keyflag )
        {
            // 新しく入手した場合
            __DtTestPoint(__DtFunc_update, __DtStep_31)
            if ( keyflag != 0 )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_32)
                mKeySprite->setVisible( true );
                mKeyEffectSprite[ 0 ]->setVisible( true );
                mKeyEffectSprite[ 1 ]->setVisible( true );
                mKeyEffectFrameCount = 7;

                Audio.playSE( "Data/Sound/SE/coin04.wav", 80, 120 );
 
            }
            // 次のステージに進むとかで、リセットされた場合
            else
            {
                __DtTestPoint(__DtFunc_update, __DtStep_33)
                mKeySprite->setVisible( false );
                mKeyEffectSprite[ 0 ]->setVisible( false );
                mKeyEffectSprite[ 1 ]->setVisible( false );
            }

            mHasKey = keyflag;
        }

        if ( mKeyEffectFrameCount > 0 )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_34)
            --mKeyEffectFrameCount;

            mKeyEffectSprite[ 0 ]->setOpacity( static_cast< float >( mKeyEffectFrameCount ) / 7 + 0.1f );
            mKeyEffectSprite[ 1 ]->setOpacity( static_cast< float >( mKeyEffectFrameCount ) / 7 + 0.1f );

            mKeyEffectSprite[ 0 ]->setScale(
                7.0f * ( 7.0f - mKeyEffectFrameCount ) + 1.0f,
                0.3f * mKeyEffectFrameCount );
            
            mKeyEffectSprite[ 1 ]->setScale( 0.9 * ( 7.0f - mKeyEffectFrameCount ) + 1.0f );

            if ( mKeyEffectFrameCount == 0 )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_35)
                mKeyEffectSprite[ 0 ]->setVisible( false );
                mKeyEffectSprite[ 1 ]->setVisible( false );
            }
            
        }

    	__DtTestPoint( __DtFunc_update, __DtStep_36 )
    }



//=============================================================================
//								end of file
//=============================================================================
