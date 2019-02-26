//=============================================================================
//【 GuideNamePlate 】
//=============================================================================

#include "stdafx.h"
#include	"DT_GuideNamePlate.h"	/* For DynamicTracer-TestPoint */
#include "../Object/GameObject.h"
#include "GameFrontendManager.h"
#include "GuideNamePlate.h"
#include "../Game/GameManager.h"
#include "../Object/Player.h"


//=============================================================================
// ■ GuideNamePlate クラス
//=============================================================================

//#define GUIDE_UNDER

    //---------------------------------------------------------------------
    // ● コンストラクタ
    //---------------------------------------------------------------------
    GuideNamePlate::GuideNamePlate()
        : mIsNearPlayer ( false )
    {
        __DtTestPoint( __DtFunc_GuideNamePlate, __DtStep_0 )
        GameFrontendManager::getInstance()->addGuidNamePlate( this );
    	__DtTestPoint( __DtFunc_GuideNamePlate, __DtStep_1 )
    }

    //---------------------------------------------------------------------
    // ● デストラクタ
    //---------------------------------------------------------------------
    GuideNamePlate::~GuideNamePlate()
    {
        __DtTestPoint( __DtFunc_GuideNamePlate, __DtStep_2 )
        GameFrontendManager::getInstance()->removeGuidNamePlate( this );
    	__DtTestPoint( __DtFunc_GuideNamePlate, __DtStep_3 )
    }

    //---------------------------------------------------------------------
    // ● 初期化
    //---------------------------------------------------------------------
    void GuideNamePlate::initialize( GameObject* object_, int arrow_color_, float ox_, float oy_ )
    {
        __DtTestPoint( __DtFunc_initialize, __DtStep_0 )
        mGameObject = object_;

        LTexture tex = LTexture::create( "Data/Graphics/Frontend/Frontend_1.png" );

        // フレーム
        mFrameSprite = LSprite::create(  tex);
        mFrameSprite.setSrcRect( 0, 168 + 16 * arrow_color_, 64, 13 );
        mFrameSprite.setVisible( false );

        // 矢印
        mArrowSprite = LSprite::create( tex );
        mArrowSprite.setSrcRect( 16 * arrow_color_, 128, 16, 8 );
        mArrowSprite.setCenter( 6, 7 );
        mArrowSprite.setVisible( false );

        // 名前
        Core::Graphics::IFont* font = GameFrontendManager::getInstance()->getGuidNamePlateFont();

        LRect size;
        font->getTextSize( mGameObject->getName(), -1, &size );

        mNameTextTexture = LTexture::create( size.w , 20 );
        mNameTextTexture->getInterface()->setFont( font );
        mNameTextTexture->drawText( mGameObject->getName(), size );
             
        mNameTextSprite = LSprite::create( mNameTextTexture );
        mNameTextSprite.setVisible( false );


        mOffsetPos.set( ox_, oy_, 0 );
        


#ifdef GUIDE_UNDER

        mArrowSprite.setSrcRect( 32 * arrow_color_, 128 + 16, 16, 8 );
        mOffsetPos.set( ox_, -96, 0 );
#endif
    	__DtTestPoint( __DtFunc_initialize, __DtStep_1 )
    }

    /*
    //---------------------------------------------------------------------
    // ● フェードイン開始
    //---------------------------------------------------------------------
    void GuideNamePlate::startFadein()
    {
        mGlobalFadeOpacity.start( mGlobalFadeOpacity.getValue(), 1.0f, 20.0 );
    }

    //---------------------------------------------------------------------
    // ● フェードアウト開始
    //---------------------------------------------------------------------
    void GuideNamePlate::startFadeout()
    {
        mGlobalFadeOpacity.start( mGlobalFadeOpacity.getValue(), 0.0f, 20.0 );
    }
    */

    //---------------------------------------------------------------------
    // ● フレーム更新
    //---------------------------------------------------------------------
    void GuideNamePlate::update()
    {
        const LVector3& player_pos = GameManager::getInstance()->getPlayer()->getPosition();
        const LVector3& object_pos = mGameObject->getPosition();

        //if ( ( player_pos - object_pos ).getLength() < 200 )

        float length = ( player_pos - object_pos ).getSquareLength();

        // プレイヤーと近ければ表示
        __DtTestPoint( __DtFunc_update, __DtStep_0 )
        if ( !mIsNearPlayer && length < 60000 )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_1)
            mIsNearPlayer = true;

            mFadeOpacity.start( mFadeOpacity.getValue(), 1.0f, 20 );

            mArrowSprite.setVisible( true );
            mFrameSprite.setVisible( true );
            mNameTextSprite.setVisible( true );

#ifdef GUIDE_UNDER

            mNameTextSprite.setPosition( pos_2d.x, pos_2d.y + 10 );
#endif

        }
        // プレイヤーから離れていれば非表示
        else if ( mIsNearPlayer && length >= 60000 )
        { 
            __DtTestPoint(__DtFunc_update, __DtStep_2)
            mIsNearPlayer = false;
            mFadeOpacity.start( mFadeOpacity.getValue(), 0.0f, 20 );


        }

        float op = GameFrontendManager::getInstance()->getGlobalFadeOpacity() * mFadeOpacity.getValue();

        mArrowSprite.setOpacity( mFadeOpacity.getValue() );  // 矢印だけは Global が透明でも表示する
        mFrameSprite.setOpacity( op );
        mNameTextSprite.setOpacity( op );


        

        mFadeOpacity.advanceTime( 1.0 );


        // 完全にフェードアウトした場合は非表示にする
        if ( mFadeOpacity.isFinished() && mFadeOpacity.getValue() == 0.0f )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_3)
            mArrowSprite.setVisible( false );
            mFrameSprite.setVisible( false );
            mNameTextSprite.setVisible( false );
        }
        else
        {
            

            // オブジェクトの座標をスクリーン座標に変換
            LVector3 pos_2d;
            __DtTestPoint(__DtFunc_update, __DtStep_4)
            Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->convertWorldPosToScreenPos( &pos_2d, ( object_pos + mOffsetPos ) );

            _setPosition( pos_2d );
        }
    	__DtTestPoint( __DtFunc_update, __DtStep_5 )
    }

    //---------------------------------------------------------------------
    // ● 位置の設定 (update() から呼ばれる。吹き出しの先っぽで指定する。)
    //---------------------------------------------------------------------
    void GuideNamePlate::_setPosition( const LVector3& pos_ )
    {
        __DtTestPoint( __DtFunc__setPosition, __DtStep_0 )
        mArrowSprite.setPosition( pos_.x, pos_.y, 100 );
        



        // フレームの左上
        float x = pos_.x  - mFrameSprite.getSrcRect().w / 2;
        
        mFrameSprite.setPosition( x, pos_.y - 24, 100 );
        

        x = pos_.x  - mNameTextSprite.getSrcRect().w / 2;
        mNameTextSprite.setPosition( x, pos_.y - 23, 100 );
        

        
    	__DtTestPoint( __DtFunc__setPosition, __DtStep_1 )
    }


//=============================================================================
//								end of file
//=============================================================================