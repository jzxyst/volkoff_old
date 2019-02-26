//=============================================================================
/*! 
    @addtogroup 
    @file       SceneTitle.cpp
    @brief      
    
    �^�C�g���̃V�[���̎���
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/13 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================

#include "stdafx.h"
#include	"DT_SceneTitle.h"	/* For DynamicTracer-TestPoint */
#include "../Game/GameManager.h"
#include "../Frontend/GameFrontendManager.h"
#include "../Frontend/PointCursor.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneConnection.h"
#include "SceneRanking.h"

static const int COMMAND_POS_X = 420;
static const int COMMAND_POS_Y = 290;
static const int MAX_END_FRAME_COUNT = 120;
static const char* START_DESC_SE = "Data/Sound/SE/cursor21.wav";
static const char* CURSOR_SE = "Data/Sound/SE/kachi38.wav";
static const char* TITLE_BGM = "Data/Sound/BGM/monochrome.ogg";//"H:/DataSource/yumenoato.mp3";//

static const char* gDescContentTitles_1[] =
{
    "GameStart",
    "Ranking",
    "Exit"
};

static const char* gDescContents_1[] =
{
    "�Q�[�����n�߂܂��B\n����T���Ȃ���X�e�[�W��i�݁A\n�ŏI�X�e�[�W�̃{�X��|����\n�Q�[���N���A�ł��B\n",
    "����܂ł̃����L���O��\n�m�F���܂��B",
    "�Q�[�����I�����܂��B"
};

static const char* gDescContentTitles_2[] =
{
    "Easy",
    "Normal",
    "Hard",
    "Valfirle"
};

static const char* gDescContents_2[] =
{
    "���S�Ҍ����̓�Փx�Ŏn�߂܂��B\n�G�̍U���������キ�Ȃ�܂��B\n",
    "�ӂ��̓�Փx�Ŏn�߂܂��B",
    "�㋉�Ҍ����̓�Փx�Ŏn�߂܂��B\n�G�̍U�����������Ȃ�A\n㩂̐��������܂��B",
    "�_�b��̌��ł��܂��B"

};
//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
SceneTitle::SceneTitle()
    : mStep         ( 0 )
    , mFrameCount   ( 0 )
    , mPointCursor  ( NULL )
{

	__DtTestPoint( __DtFunc_SceneTitle, __DtStep_0 )
}


//---------------------------------------------------------------------
// �� �J�n����
//---------------------------------------------------------------------
void SceneTitle::onStart()
{
    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    printf( "-------------------------------------------------\n" );
    printf( " �� �^�C�g�����\n" );
    printf( "-------------------------------------------------\n" );
    printf( "Z > �Q�[���J�n\n" );
    printf( "X > �l�b�g�ڑ�\n" );


    Graphics.setBGColor( 1, 1, 1 );
    LLayer::getBGLayer().setTone( LTone( 0, 0, 0, 0 ), 1.5 );


    mRandomSprite = LSprite::create( LTexture::create( "Data/Graphics/Frontend/Random_1.png" ) );
    mRandomSprite->setCenter( 256, 32 );
    mRandomSprite->setPosition( 320, 160 );

    LTexture tex = LTexture::create( "Data/Graphics/Frontend/Title_1.png" );

    
    // �e�L�X�g���̃t���[��
    mTitleFrameSprite = LSprite::create( tex );
    mTitleFrameSprite->setSrcRect( 0, 128, 512, 64 );
    mTitleFrameSprite->setCenter( 256, 32 );
    mTitleFrameSprite->setPosition( 320, 160 );

    // �^�C�g���e�L�X�g
    mTitleTextSprite = LSprite::create( tex );
    mTitleTextSprite->setCenter( 196, 32 );
    mTitleTextSprite->setSrcRect( 0, 0, 392, 64 );
    mTitleTextSprite->setPosition( 320, 160 );

    // �t���[�������̕���
    mTitleSubTextSprite = LSprite::create( tex );
    mTitleSubTextSprite->setCenter( 216, 0 );
    mTitleSubTextSprite->setSrcRect( 0, 192, 432, 16 );
    mTitleSubTextSprite->setPosition( 320, 192 );

    // �uPressAnyKey�v
    mPressAnyKeySprite = LSprite::create( tex );
    mPressAnyKeySprite->setSrcRect( 0, 224, 176, 32 );
    mPressAnyKeySprite->setCenter( 176 / 2, 16 );
    mPressAnyKeySprite->setPosition( 320, 350 );

    // �G�t�F�N�g�p
    mTitleEffectSprite = LSprite::create( tex );
    mTitleEffectSprite.setSrcRect( 0, 64, 512, 64 );
    mTitleEffectSprite.setCenter( 256, 42 );
    mTitleEffectSprite.setPosition( 320, 170 );
    mTitleEffectSprite.setOpacity( 0 );


    // �㉺�̎����X�[�p�[
    for ( int i = 0; i < 2; ++i )
    {
        __DtTestPoint(__DtFunc_onStart, __DtStep_1)
        mSuperSprite[ i ] = LSprite::create( tex );
        mSuperSprite[ i ]->setSrcRect( 128, 496, 256, 16 );
        mSuperSprite[ i ]->setScale( 4, 2 );
        mSuperSprite[ i ]->setVisible( false );
    }


    // �R�}���h
    for ( int i = 0; i < 4; ++i )
    {
        __DtTestPoint(__DtFunc_onStart, __DtStep_2)
        mCommandSprite[ i ] = LSprite::create( tex );
        mCommandSprite[ i ]->setVisible( false );
    }

    // �����E�B���h�E
    mDescWindowSprite = LSprite::create( tex );
    mDescWindowSprite.setPosition( -500, 0 );       // �ʓ|�Ȃ̂ŉ�ʊO�ŉB��
    mDescWindowSprite.setSrcRect( 272, 224, 240, 144 );

    mDescContents = LTexture::create( 240, 144 );
    mDescContentsSprite = LSprite::create( mDescContents );
    mDescContentsSprite.setPosition( -500, 0 );     // �ʓ|�Ȃ̂ŉ�ʊO�ŉB��

    mDescTitleFont = LFont::createDefaultFont();
    mDescTitleFont.setSize( 12 );
    mDescTitleFont.setColor( 0, 0, 0, 1 );

    LFont desc_text = LFont::createDefaultFont();
    desc_text.setSize( 15 );
    desc_text.setColor( 0, 0, 0, 1 );
    mFormatText.setFont( desc_text.getInterface() );
    mFormatText.setDrawRect( LRect( 12, 20, 224, 120 ) );

    // �A���t�@�l�p�����l
    mRoundTripValue.setCapacity( 3 );
    mRoundTripValue.addKeyFrame( 0, 0.2f );
    mRoundTripValue.addKeyFrame( 60, 1.0f );
    mRoundTripValue.addKeyFrame( 120, 0.2f );
    mRoundTripValue.setEnableLoop( true );
    mRoundTripValue.setTime( 0.0 );

    // �R�}���h�̃t�F�[�h�C��X���W
    mCommandFadeInX.setCapacity( 2 );
    mCommandFadeInX.addKeyFrame( 0, 32 );
    mCommandFadeInX.addKeyFrame( 30, 0 );
    mCommandFadeInX[ 0 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mCommandFadeInX[ 1 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mCommandFadeInX.setTime( 0.0 );
    mCommandFadeInX.setTimeTickPerSec( 1.0f );

    // �R�}���h�̃t�F�[�h�C���s�����x
    mCommandFadeInOpacity.setCapacity( 3 );
    mCommandFadeInOpacity.addKeyFrame( 0,  0.0f );
    mCommandFadeInOpacity.addKeyFrame( 15, 0.5f );
    mCommandFadeInOpacity.addKeyFrame( 30, 1.0f );
    mCommandFadeInOpacity.setTime( 0.0 );
    mCommandFadeInOpacity.setTimeTickPerSec( 1.0f );
    
    mPointCursor = NEW PointCursor();

    
    
    mStep = 0;
    mFrameCount = 0;
    mEntryedStep = 0;
    mWindowFadeCount = 0;
    mEndFrameCount = 0;

    Audio.playBGM( TITLE_BGM, 80 );

	Framework->getInterface()->resetDelayTime();
	__DtTestPoint( __DtFunc_onStart, __DtStep_3 )
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void SceneTitle::onUpdate()
{
    int count = Framework.getFrameCount();
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    mRandomSprite->setSrcRect( count, count, 512, 64 );

    mPointCursor->update();



    // �I�����H
    if ( mEndFrameCount > 0 )
    {
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
        --mEndFrameCount;

        // �����̃t�F�[�h�A�E�g
        int t = MAX_END_FRAME_COUNT - mEndFrameCount;
        mSuperSprite[ 0 ]->setPosition( 0, -t * 4 );
        mSuperSprite[ 1 ]->setPosition( 0, 448 + t * 6  );

        // �E�B���h�E�E�R�}���h�̃t�F�[�h�A�E�g
        t = mEndFrameCount - ( MAX_END_FRAME_COUNT - 20 );
        mCommandFadeInOpacity.setTime( t );

        mDescWindowSprite.setOpacity(  mCommandFadeInOpacity.getValue() );
        mDescContentsSprite.setOpacity(  mCommandFadeInOpacity.getValue() );

        // �g��G�t�F�N�g
        float op = LMath::min( MAX_END_FRAME_COUNT - mEndFrameCount, 20 );
        mTitleEffectSprite.setOpacity( 1.0f - op / 20 );
        mTitleEffectSprite.setScale( op / 100 + 1 );

        for ( int i = 0; i < 4; ++i )
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_2)
            mCommandSprite[ i ].setOpacity( mCommandFadeInOpacity.getValue() );
        }

        // �S�̃t�F�[�h�A�E�g
        if ( mEndFrameCount == 60 )
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_3)
            LLayer::getBGLayer()->setTone( LTone( 1, 1, 1, 1 ), 1.0 );
        }


        if ( mEndFrameCount == 0 )
        {
            // �e�Ƃ��ď�����������A�Q�[����ʂɈړ�����
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_4)
            GameManager::getInstance()->initializeParent();
            GameManager::getInstance()->setRank( mSelectIndex );
            LGameScene::changeScene( NEW SceneGame() );
        }

        
    }

    

    switch ( mStep )
    {
        /////////////////////// Press Any Key
        case 0:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_5)
            mRoundTripValue.advanceTime( Framework.getGameTime().getElapsedGameTime() );

            mPressAnyKeySprite->setOpacity( mRoundTripValue.getValue() );

            if ( Input->getPressedButton() )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_6)
                mStep = 1;
                mFrameCount = 0;
                mEntryedStep = 1;
                _startShowCommand( 0 );

                mSelectIndex = 0;
                

                mWindowFadeCount = 40;

                Audio.playSE( "Data/Sound/SE/cursor21.wav", 40, 100 );
                //Audio.playSE( "Data/Sound/SE/metal33_a.wav", 50, 120 );
                
            }

            break;
        }  
        /////////////////////// ���[�h�I��
        case 1:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_7)
            if ( mFrameCount == 20 && mWindowFadeCount > 10 ) // mWindowFadeCount > 30 �́Astep1 0 ���痈���Ƃ����Ӗ�
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_8)
                _setPointCursorIndex( mSelectIndex );
            }
            if ( mFrameCount >= 20 && mFrameCount <= 60 )
            {
                int t = mFrameCount - 20;
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_9)
                for ( int i = 0; i < 3; ++i )
                {
                    __DtTestPoint(__DtFunc_onUpdate, __DtStep_10)
                    mCommandFadeInX.setTime( static_cast< double >( t - 5 * i ) );
                    mCommandSprite[ i ].setPosition( COMMAND_POS_X + mCommandFadeInX.getValue(), COMMAND_POS_Y + 32 * i );

                    mCommandFadeInOpacity.setTime( static_cast< double >( t - 5 * i ) );
                    mCommandSprite[ i ].setOpacity( mCommandFadeInOpacity.getValue() );
                }
            }

			

            // ����{�^��
            if ( Input.isOnTrigger( LN_BUTTON_A ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_11)
                switch ( mSelectIndex )
                {
                    case 0:
                        __DtTestPoint(__DtFunc_onUpdate, __DtStep_12)
                        mSelectIndex = 1;
                        break;
                    case 1:
                        // �����L���O
						__DtTestPoint(__DtFunc_onUpdate, __DtStep_13)
						this->callScene( NEW SceneRanking() );
                        Audio.playSE( CURSOR_SE, 80 );
						__DtTestPoint( __DtFunc_onUpdate, __DtStep_14 )
						return;
                    case 2:
                        // �I��
						__DtTestPoint(__DtFunc_onUpdate, __DtStep_15)
						Framework.exit();
                        break;
                }

				mStep = 2;
                mFrameCount = 0;
                _startShowCommand( 1 );

                _setPointCursorIndex( mSelectIndex );
                Audio.playSE( CURSOR_SE, 80 );
				__DtTestPoint( __DtFunc_onUpdate, __DtStep_16 )
				return;
            }

            // ��
            if ( Input.isRepeat( LN_BUTTON_UP ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_17)
                --mSelectIndex;
                if ( mSelectIndex < 0 )
                {
                    __DtTestPoint(__DtFunc_onUpdate, __DtStep_18)
                    mSelectIndex = 2;
                }
                _setPointCursorIndex( mSelectIndex );
                Audio.playSE( CURSOR_SE, 80 );
				__DtTestPoint( __DtFunc_onUpdate, __DtStep_19 )
				return;
            }
            // ��
            if ( Input.isRepeat( LN_BUTTON_DOWN ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_20)
                ++mSelectIndex;
                if ( mSelectIndex > 2 )
                {
                    __DtTestPoint(__DtFunc_onUpdate, __DtStep_21)
                    mSelectIndex = 0;
                }
                _setPointCursorIndex( mSelectIndex );
                Audio.playSE( CURSOR_SE, 80 );
				__DtTestPoint( __DtFunc_onUpdate, __DtStep_22 )
				return;
            }
            

            break;
        }
        /////////////////////// ��Փx�I��
        case 2:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_23)
            if ( mFrameCount <= 50 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_24)
                for ( int i = 0; i < 4; ++i )
                {
                    __DtTestPoint(__DtFunc_onUpdate, __DtStep_25)
                    mCommandFadeInX.setTime( static_cast< double >( mFrameCount - 5 * i ) );
                    mCommandSprite[ i ].setPosition( COMMAND_POS_X + mCommandFadeInX.getValue(), COMMAND_POS_Y + 32 * i );

                    mCommandFadeInOpacity.setTime( static_cast< double >( mFrameCount - 5 * i ) );
                    mCommandSprite[ i ].setOpacity( mCommandFadeInOpacity.getValue() );
                }
            }

            // ����
            if ( Input.isOnTrigger( LN_BUTTON_A ) )
            {

                // �I��
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_26)
                mEndFrameCount = MAX_END_FRAME_COUNT;

                mPointCursor->moveToInit();

                Audio.playSE( "Data/Sound/SE/cursor21.wav", 80, 120 );
                Audio.stopBGM( 3000 );
            }

            // �L�����Z��
            if ( Input.isOnTrigger( LN_BUTTON_B ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_27)
                mStep = 1;
                mFrameCount = 0;
                _startShowCommand( 0 );
                mSelectIndex = 0;
                _setPointCursorIndex( mSelectIndex );
            }

            // ��
            if ( Input.isRepeat( LN_BUTTON_UP ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_28)
                --mSelectIndex;
                if ( mSelectIndex < 0 )
                {
                    __DtTestPoint(__DtFunc_onUpdate, __DtStep_29)
                    mSelectIndex = 3;
                }
                _setPointCursorIndex( mSelectIndex );
                Audio.playSE( CURSOR_SE, 80 );
            }
            // ��
            if ( Input.isRepeat( LN_BUTTON_DOWN ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_30)
                ++mSelectIndex;
                if ( mSelectIndex > 3 )
                {
                    __DtTestPoint(__DtFunc_onUpdate, __DtStep_31)
                    mSelectIndex = 0;
                }
                _setPointCursorIndex( mSelectIndex );
                Audio.playSE( CURSOR_SE, 80 );
            }
            break;
        }
    };


    if ( mEntryedStep == 1 )
    {
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_32)
        if ( mPressAnyKeySprite.isVisible() && mFrameCount <= 10 )
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_33)
            mPressAnyKeySprite->setScale( mFrameCount / 4.0f + 1.0f, ( 10.0f - mFrameCount ) / 10.0f );
            if ( mFrameCount == 10 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_34)
                mPressAnyKeySprite.setVisible( false );
                mEntryedStep = 2;
            }
        }

        if ( mFrameCount <= 8 )
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_35)
            mSuperSprite[ 0 ]->setVisible( true );
            mSuperSprite[ 1 ]->setVisible( true );
            mSuperSprite[ 0 ]->setPosition( 0, -32 + mFrameCount * 4 );
            mSuperSprite[ 1 ]->setPosition( 0, 480 - mFrameCount * 4  );
        }
    }

    // �E�B���h�E��̪��޲ݒ�
    if ( mWindowFadeCount > 0 )
    {
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_36)
        --mWindowFadeCount;

        if ( mWindowFadeCount <= 30 )
        {
            double t = static_cast< double >( 30 - mWindowFadeCount );

            // �R�}���h�p�̃A�j�����g���܂킷
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_37)
            mCommandFadeInX.setTime( t );
            mCommandFadeInOpacity.setTime( t );

            mDescWindowSprite.setPosition( 60 - mCommandFadeInX.getValue(), 280 );
            mDescWindowSprite.setOpacity(  mCommandFadeInOpacity.getValue() );

            mDescContentsSprite.setPosition( 60 - mCommandFadeInX.getValue(), 280 );
            mDescContentsSprite.setOpacity(  mCommandFadeInOpacity.getValue() ); 
        }
    }

    // �������`�撆
    if ( !mFormatText.isFinished() )
    {

        __DtTestPoint(__DtFunc_onUpdate, __DtStep_38)
        mFormatText.update();

        LNFormatTextDrawData data;
        while ( mFormatText.getNextDrawData( &data ) )
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_39)
            mDescContents.getInterface()->setFont( data.Font );
            mDescContents.drawText( data.Text, data.Rect, LN_TEXTALIGN_LEFT, data.Length );
        }
    }


    /*
    if ( Input.isOnTrigger( LN_BUTTON_A ) )
    {
        // �e�Ƃ��ď�����������A�Q�[����ʂɈړ�����
        GameManager::getInstance()->initializeParent();

        LGameScene::changeScene( NEW SceneGame() );
        return;
    }
    
    
    if ( Input.isOnTrigger( LN_BUTTON_B ) )
    {
        LGameScene::changeScene( NEW SceneConnection() );
        return;
    }
    */

    ++mFrameCount;

	__DtTestPoint( __DtFunc_onUpdate, __DtStep_40 )
}

//---------------------------------------------------------------------
// �� �I������
//---------------------------------------------------------------------
void SceneTitle::onTerminate()
{
    __DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
    SAFE_DELETE( mPointCursor );

    // �Ƃ肠����
    LLayer::getBGLayer()->setTone( LTone( 0, 0, 0, 0 ), 0.5 );

    
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �R�}���h���ڂ̕\���J�n
//---------------------------------------------------------------------
void SceneTitle::_startShowCommand( int type_ )
{
    __DtTestPoint( __DtFunc__startShowCommand, __DtStep_0 )
    if ( type_ == 0 )
    {
        __DtTestPoint(__DtFunc__startShowCommand, __DtStep_1)
        for ( int i = 0; i < 3; ++i )
        {
            __DtTestPoint(__DtFunc__startShowCommand, __DtStep_2)
            mCommandSprite[ i ]->setSrcRect( 0, 256 + i * 32, 128, 32 );
            mCommandSprite[ i ]->setVisible( true );
            mCommandSprite[ i ]->setOpacity( 0.0f );
        }
        mCommandSprite[ 3 ]->setVisible( false );
    }
    else
    {
        __DtTestPoint(__DtFunc__startShowCommand, __DtStep_3)
        for ( int i = 0; i < 4; ++i )
        {
            __DtTestPoint(__DtFunc__startShowCommand, __DtStep_4)
            mCommandSprite[ i ]->setSrcRect( 128, 256 + i * 32, 128, 32 );
            mCommandSprite[ i ]->setVisible( true );
            mCommandSprite[ i ]->setOpacity( 0.0f );
        }
    }

	__DtTestPoint( __DtFunc__startShowCommand, __DtStep_5 )
}

//---------------------------------------------------------------------
// �� ���̈ʒu�ݒ�
//---------------------------------------------------------------------
void SceneTitle::_setPointCursorIndex( int index_ )
{
    //mSelectIndex = index_;
    __DtTestPoint( __DtFunc__setPointCursorIndex, __DtStep_0 )
    mPointCursor->moveTo( COMMAND_POS_X - 38, COMMAND_POS_Y + mSelectIndex * 32 + 16 );


    mDescContents.clear( LColor( 0, 0, 0, 0 ) );

    // ���[�h�I��
    if ( mStep == 1 )
    {
        __DtTestPoint(__DtFunc__setPointCursorIndex, __DtStep_1)
        mDescContents.setFont( mDescTitleFont );
        mDescContents.drawText( gDescContentTitles_1[ mSelectIndex ], LRect( 8, 2, 256, 256 ) );

        mFormatText.setText( gDescContents_1[ mSelectIndex ] );
        mFormatText.build();
    }
    // ��Փx�I��
    else if ( mStep == 2 )
    {
        __DtTestPoint(__DtFunc__setPointCursorIndex, __DtStep_2)
        mDescContents.setFont( mDescTitleFont );
        mDescContents.drawText( gDescContentTitles_2[ mSelectIndex ], LRect( 8, 2, 256, 256 ) );

        mFormatText.setText( gDescContents_2[ mSelectIndex ] );
        mFormatText.build();
    }
	__DtTestPoint( __DtFunc__setPointCursorIndex, __DtStep_3 )
}

//=============================================================================
//								End of File
//=============================================================================