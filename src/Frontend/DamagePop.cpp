//=============================================================================
//【 DamagePop 】
//=============================================================================

#include "stdafx.h"
#include	"DT_DamagePop.h"	/* For DynamicTracer-TestPoint */
#include "DamagePop.h"

//=============================================================================
// ■ DamagePop クラス
//=============================================================================


    //---------------------------------------------------------------------
    // ● コンストラクタ
    //---------------------------------------------------------------------
    DamagePop::DamagePop()
    {
        __DtTestPoint( __DtFunc_DamagePop, __DtStep_0 )
        mNumberTexture = LTexture::create( "Data/Graphics/Frontend/Number_1.png" );
    	__DtTestPoint( __DtFunc_DamagePop, __DtStep_1 )
    }

    //---------------------------------------------------------------------
    // ● デストラクタ
    //---------------------------------------------------------------------
    DamagePop::~DamagePop()
    {
        PopNumberList::iterator itr = mPopNumberList.begin();
        PopNumberList::iterator end = mPopNumberList.end();
        __DtTestPoint( __DtFunc_DamagePop, __DtStep_2 )
        for ( ; itr != end; ++itr )
        {
            __DtTestPoint(__DtFunc_DamagePop, __DtStep_3)
            delete (*itr);
        }
    	__DtTestPoint( __DtFunc_DamagePop, __DtStep_4 )
    }

    //---------------------------------------------------------------------
    // ● 数字を表示させる
    //---------------------------------------------------------------------
    void DamagePop::popNumber( const LVector3& pos_, u32 value_, int type_ )
    {
        PopNumber* number = NEW PopNumber( pos_, value_, type_, mNumberTexture );
        __DtTestPoint( __DtFunc_popNumber, __DtStep_0 )
        mPopNumberList.push_back( number );
    	__DtTestPoint( __DtFunc_popNumber, __DtStep_1 )
    }

    //---------------------------------------------------------------------
    // ● フレーム更新
    //---------------------------------------------------------------------
    void DamagePop::update()
    {
        PopNumberList::iterator itr = mPopNumberList.begin();
        PopNumberList::iterator end = mPopNumberList.end();
        __DtTestPoint( __DtFunc_update, __DtStep_0 )
        for ( ; itr != end; )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_1)
            if ( !(*itr)->update() )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_2)
                delete (*itr);
                itr = mPopNumberList.erase( itr );
            }
            else
            {
                __DtTestPoint(__DtFunc_update, __DtStep_3)
                ++itr;
            }
        }
    	__DtTestPoint( __DtFunc_update, __DtStep_4 )
    }


//=============================================================================
// ■ DamagePop::PopNumber クラス
//=============================================================================


    //---------------------------------------------------------------------
    // ● コンストラクタ
    //---------------------------------------------------------------------
    DamagePop::PopNumber::PopNumber( const LVector3& pos_, u32 value_, int type_, LTexture texture_ )
        : mFrameCount   ( 0 )
    {
        const int num_w = 8;            // 1文字のピクセル幅
        const int num_h = 14;           // 1文字のピクセル高さ
        int digit = Core::Base::getNumberDigits( value_ );    // 桁数


        

        __DtTestPoint( __DtFunc_PopNumber, __DtStep_0 )
        mNumberTexture = LTexture::create( num_w * digit, num_h );
        int x = num_w * digit - num_w;
        for ( int i = 0; i < digit; ++i )
        {
            int v = value_ % 10;

            __DtTestPoint(__DtFunc_PopNumber, __DtStep_1)
            mNumberTexture.blt( x, 0, texture_, LRect( v * num_w, num_h * type_, num_w, num_h ) );

            value_ /= 10;
            x -= num_w;
        }

        static LRandom random( Framework.getFrameCount() );

        mPosition.x = random.getFloat( pos_.x - 10.f, pos_.x + 10.f );
        mPosition.y = random.getFloat( pos_.y - 10.f, pos_.y + 10.f );

        mVelocity.x = random.getFloat( -3.f, 3.f );
        mVelocity.y = 4.f;//random.getFloat( 0.f, 10.f );
        mVelocity.z = 0;

        //_p(pos_.y);
        //_p(mPosition.y);


        mNumberSprite = LSprite::create( mNumberTexture );
        mNumberSprite.setCenter( mNumberTexture.getSize().x / 2, mNumberTexture.getSize().y / 2 );
        mNumberSprite.setPriority( 1000 );
        mNumberSprite.setEnableDepthTest( false );
    	__DtTestPoint( __DtFunc_PopNumber, __DtStep_2 )
    }

    //---------------------------------------------------------------------
    // ● デストラクタ
    //---------------------------------------------------------------------
    DamagePop::PopNumber::~PopNumber()
    {
    	__DtTestPoint( __DtFunc_PopNumber, __DtStep_3 )
    }

    //---------------------------------------------------------------------
    // ● フレーム更新
    //---------------------------------------------------------------------
    bool DamagePop::PopNumber::update()
    {
        __DtTestPoint( __DtFunc_update, __DtStep_5 )
        mPosition += mVelocity;
        mVelocity.y -= 0.25f;

        // スクリーン座標に変換
        LVector3 pos_2d;
        Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->convertWorldPosToScreenPos( &pos_2d, mPosition );
        mNumberSprite.setPosition( pos_2d );


        if ( mFrameCount <= 7 )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_6)
            mNumberSprite.setScale( 1.25f + 0.25f * ( 7 - mFrameCount ) );
        }

        if ( mFrameCount > 10 )
        {
            float c = static_cast< float >( 40 - mFrameCount ) / 40;
            __DtTestPoint(__DtFunc_update, __DtStep_7)
            mNumberSprite.setOpacity( c );
        }

        if ( mFrameCount > 40 )
        {
            __DtTestPoint( __DtFunc_update, __DtStep_8 )
            return false;
        }
        ++mFrameCount;


        /*

        // スクリーン座標に変換
        LVector3 pos_2d;
        Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->convertWorldPosToScreenPos( &pos_2d, mPosition );
        //mPosition.y -= 100;
        mNumberSprite.setPosition( pos_2d );



        ++mFrameCount;

        if ( mFrameCount <= 7 )
        {
            mNumberSprite.setScale( 1.25f + 0.25f * ( 7 - mFrameCount ) );
            return true;
        }

        //mNumberSprite.setOpacity( 0.7f );

        
        if ( mFrameCount < 60 )
        {
            return true;
        }

        //mPosition.y += 1.0f;
        //mNumberSprite.setPosition( mPosition );

        float c = 0.033f *( 90 - mFrameCount );
        mNumberSprite.setOpacity( c );//max( c, 0.7f ) );
 

        
        if ( mFrameCount > 90 )
        {
            return false;
        }
        */
        __DtTestPoint( __DtFunc_update, __DtStep_9 )
        return true;
    }

 

//=============================================================================
//								end of file
//=============================================================================