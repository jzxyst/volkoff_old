//=============================================================================
//【 Effect_1 】
//=============================================================================

#include "stdafx.h"
#include	"DT_Effect_1.h"	/* For DynamicTracer-TestPoint */
#include "Effect_1.h"

//=============================================================================
// ■ Effect_1 クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Test_1::Effect_Test_1( const LVector3& pos_ )
{
    //static Math::Random random;

    __DtTestPoint( __DtFunc_Effect_Test_1, __DtStep_0 )
    mPanel = LBatchPanel::create( 80, 80 );
    mPanel->setTexture( LTexture::create( "Data/Graphics/Effect/Effect_1.png" ) );
    mPanel->setSrcRect( 0, 128, 128, 128 );
    mPanel->setAngle( 0, 0, 0 );//random.getFloat( 3.0f ) );
    mPanel->setPosition( pos_ );

    mFrameCount = 0;
	__DtTestPoint( __DtFunc_Effect_Test_1, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Test_1::~Effect_Test_1()
{

	__DtTestPoint( __DtFunc_Effect_Test_1, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Test_1::update()
{
    __DtTestPoint( __DtFunc_update, __DtStep_0 )
    mPanel->setScale( mFrameCount, 0.3f, 1 );
    mPanel->setOpacity( 1.0f - ( mFrameCount / 6.0f ) );

    ++mFrameCount;
    if ( mFrameCount > 6 )
    {
        __DtTestPoint( __DtFunc_update, __DtStep_1 )
        return false;
    }
    __DtTestPoint( __DtFunc_update, __DtStep_2 )
    return true;
}




//=============================================================================
// ■ Effect_2 クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Test_2::Effect_Test_2( const LVector3& pos_ )
{
    //static Math::Random random;

    __DtTestPoint( __DtFunc_Effect_Test_2, __DtStep_0 )
    mPanel = LBatchPanel::create( 80, 80 );
    mPanel->setTexture( LTexture::create( "Data/Graphics/Effect/Effect_1.png" ) );
    mPanel->setSrcRect( 0, 128, 128, 128 );
    mPanel->setAngle( 0, 0, LMath::PI / 2 );//random.getFloat( 3.0f ) );
    mPanel->setPosition( pos_ );

    mFrameCount = 0;
	__DtTestPoint( __DtFunc_Effect_Test_2, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Test_2::~Effect_Test_2()
{
	__DtTestPoint( __DtFunc_Effect_Test_2, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Test_2::update()
{
    __DtTestPoint( __DtFunc_update, __DtStep_3 )
    mPanel->setScale( mFrameCount / 2, 1.0f, mFrameCount / 2);
    //mPanel->setOpacity( 1.0f - ( mFrameCount / 6.0f ) );

    ++mFrameCount;
    if ( mFrameCount > 6 )
    {
        __DtTestPoint( __DtFunc_update, __DtStep_4 )
        return false;
    }
    __DtTestPoint( __DtFunc_update, __DtStep_5 )
    return true;
}



//=============================================================================
// ■ Effect_Explosion クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Explosion::Effect_Explosion( const LVector3& pos_ )
{
    //static Math::Random random;

    __DtTestPoint( __DtFunc_Effect_Explosion, __DtStep_0 )
    mPanel = LBatchPanel::create( 160, 160 );
    mPanel->setTexture( LTexture::create( "./Data/Graphics/Effect/Explosion01.png" ) );
    mPanel->setSrcRect( 0, 128, 128, 128 );
    mPanel->setAngle( 0, 0, 0 );//random.getFloat( 3.0f ) );
    mPanel->setPosition( pos_ );

	LLayer::getBGLayer()->blur(0.6, 0.5, 1.05, pos_, true );

    mFrameCount = 0;
	__DtTestPoint( __DtFunc_Effect_Explosion, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Explosion::~Effect_Explosion()
{

	__DtTestPoint( __DtFunc_Effect_Explosion, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Explosion::update()
{
    __DtTestPoint( __DtFunc_update, __DtStep_6 )
    ++mFrameCount;
    if ( mFrameCount > 30 )
    {
        __DtTestPoint( __DtFunc_update, __DtStep_7 )
        return false;
    }

	//アニメーション
	this->mPanel.setSrcRect(128 * (mFrameCount % 5),128 * (mFrameCount / 5),128,128);
    __DtTestPoint( __DtFunc_update, __DtStep_8 )
    return true;
}

//=============================================================================
// ■ Effect_Explosion2 クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Explosion2::Effect_Explosion2( const LVector3& pos_ )
{
    //static Math::Random random;

    __DtTestPoint( __DtFunc_Effect_Explosion2, __DtStep_0 )
    mPanel = LBatchPanel::create( 20, 20 );
    mPanel->setTexture( LTexture::create( "./Data/Graphics/Effect/Explosion01.png" ) );
    mPanel->setSrcRect( 0, 128, 128, 128 );
    mPanel->setAngle( 0, 0, 0 );//random.getFloat( 3.0f ) );
    mPanel->setPosition( pos_ );



    mFrameCount = 0;
	__DtTestPoint( __DtFunc_Effect_Explosion2, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Explosion2::~Effect_Explosion2()
{

	__DtTestPoint( __DtFunc_Effect_Explosion2, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Explosion2::update()
{
    __DtTestPoint( __DtFunc_update, __DtStep_9 )
    ++mFrameCount;
    if ( mFrameCount > 15 )
    {
        __DtTestPoint( __DtFunc_update, __DtStep_10 )
        return false;
    }

	//アニメーション
	this->mPanel.setSrcRect(128 * (mFrameCount ),128 * (mFrameCount / 5),128,128);
    __DtTestPoint( __DtFunc_update, __DtStep_11 )
    return true;
}

//=============================================================================
// ■ Effect_3 クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Test_3::Effect_Test_3( const LVector3& pos_ )
{
    //static Math::Random random;

    __DtTestPoint( __DtFunc_Effect_Test_3, __DtStep_0 )
    mPanel = LPanel::create( 120,130 );
    mPanel->setTexture( LTexture::create( "Data/Graphics/Effect/Effect_1.png" ) );
    mPanel->setSrcRect( 0, 128, 128, 128 );
  //  mPanel->setAngle( 0, 0, LMath::PI / 2 );//random.getFloat( 3.0f ) );
    mPanel->setPosition( pos_ );

    mFrameCount = 0;
	__DtTestPoint( __DtFunc_Effect_Test_3, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Test_3::~Effect_Test_3()
{
	__DtTestPoint( __DtFunc_Effect_Test_3, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Test_3::update()
{
    __DtTestPoint( __DtFunc_update, __DtStep_12 )
    mPanel->setScale( mFrameCount / 3, 1.0f, mFrameCount / 3);
    //mPanel->setOpacity( 1.0f - ( mFrameCount / 6.0f ) );

    ++mFrameCount;
    if ( mFrameCount > 9 )
    {
        __DtTestPoint( __DtFunc_update, __DtStep_13 )
        return false;
    }
    __DtTestPoint( __DtFunc_update, __DtStep_14 )
    return true;
}

//=============================================================================
// ■ Effect_Thunder クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Thunder::Effect_Thunder( const LVector3& pos_ )
{
    //static Math::Random random;

    __DtTestPoint( __DtFunc_Effect_Thunder, __DtStep_0 )
    mPanel = LPanel::create( 64,2000 );
    mPanel->setTexture( LTexture::create( "Data/Graphics/Effect/Thunder_1.png" ) );
    mPanel->setSrcRect(0, 512, 64, 512 );
  //  mPanel->setAngle( 0, 0, LMath::PI / 2 );//random.getFloat( 3.0f ) );
    mPanel->setPosition( pos_ );

	LLayer::getBGLayer()->blur(0.6, 0.5, 1.05, pos_, true );

    mFrameCount = 0;
	__DtTestPoint( __DtFunc_Effect_Thunder, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Thunder::~Effect_Thunder()
{
	__DtTestPoint( __DtFunc_Effect_Thunder, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Thunder::update()
{
  //  mPanel->setScale(1, 1.0f, 1);
    //mPanel->setOpacity( 1.0f - ( mFrameCount / 6.0f ) );
    __DtTestPoint( __DtFunc_update, __DtStep_15 )
    mPanel->setSrcRect(64*(mFrameCount/5), 512, 64, 512 );
    ++mFrameCount;
    if ( mFrameCount >20 )
    {
        __DtTestPoint( __DtFunc_update, __DtStep_16 )
        return false;
    }
    __DtTestPoint( __DtFunc_update, __DtStep_17 )
    return true;
}
//=============================================================================
//								end of file
//=============================================================================