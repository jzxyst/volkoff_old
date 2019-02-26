//=============================================================================
//�y SceneGameover �z
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
// �� SceneGameover �N���X
//=============================================================================


static const int COMMAND_POS_X = 420;
static const int COMMAND_POS_Y = 290;
    
//---------------------------------------------------------------------
// �� �J�n����
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


    // �����E�B���h�E
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

    // �R�}���h
    mCommandSprite[ 0 ] = LSprite::create( fe_tex );
    mCommandSprite[ 0 ].setSrcRect( 272, 304, 128, 32 );
    mCommandSprite[ 0 ].setPosition( COMMAND_POS_X, COMMAND_POS_Y );
    mCommandSprite[ 0 ].setOpacity( 0 );
    mCommandSprite[ 1 ] = LSprite::create( fe_tex );
    mCommandSprite[ 1 ].setSrcRect( 272, 336, 128, 32 );
    mCommandSprite[ 1 ].setPosition( COMMAND_POS_X, COMMAND_POS_Y + 32 );
    mCommandSprite[ 1 ].setOpacity( 0 );

    // ���䕶����`��N���X
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

    // �J�[�\��
    mPointCursor = NEW PointCursor();

    // BGM �t�F�[�h�A�E�g
    Audio.stopBGM( 5000 );

    
    mStep = 0;
    mFrameCount = 0;
    mSelectIndex = 0;

    
	__DtTestPoint( __DtFunc_onStart, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void SceneGameover::onUpdate()
{
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    mPointCursor->update();

    // �������`�撆
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
        /////////////////////// �u���C���h��
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
        /////////////////////// GameOver �t�F�[�h�C����
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
        /////////////////////// �R���e���c�t�F�[�h�C����
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
        /////////////////////// �R���e���c�I��
        case 3:
        {
            // ����
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_9)
            if ( Input.isOnTrigger( LN_BUTTON_A ) )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_10)
                mPointCursor->moveToInit();
                mStep = 4;
                mFrameCount = 0;
                LLayer::getBGLayer()->setTone( LTone( -1, -1, -1, -1 ), 1.0f );
            }

            // ��
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
            // ��
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
        /////////////////////// �I����
        case 4:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_15)
            if ( mFrameCount == 60 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_16)
                if ( mSelectIndex == 0 )
                {

                    // ��
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

	// �ȑO�͂��̊֐� (SceneGameover::onUpdate()) �̐擪�Őe�V�[���� onUpdate() ���Ăяo���Ă����B
	// �������A�R���e�B�j���[���Ɍ��݂̃}�b�v���č\�z������� onUpdate() ���Ă΂�Ȃ��������߁A
	// �Â��I�u�W�F�N�g�����̉����1�t���[���x��Ă����B(�K�v�Ȃ��Ȃ����I�u�W�F�N�g�� onUpdate() �ŊJ�����Ă��邽��)
	// ���ʁA��u����2�{�����̃I�u�W�F�N�g���o�����邱�ƂɂȂ�A�`��\�ȃX�v���C�g���𒴂��Ă��܂����B
    this->getParentScene()->onUpdate();
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_20 )
}

//---------------------------------------------------------------------
// �� �I������
//---------------------------------------------------------------------
void SceneGameover::onTerminate()
{

    __DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
    LLayer::getBGLayer()->setTone( LTone( 0, 0, 0, 0 ), 1.0f );

    SAFE_DELETE( mPointCursor );
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �I�����Ă��鍀�ڂ�ύX����
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

        mFormatText.setText( "�X�e�[�W�̍ŏ������蒼���܂��B\n\n�X�R�A�� 0 �Ƀ��Z�b�g����܂��B" );
        mFormatText.build();
    }
    else
    {
        __DtTestPoint(__DtFunc__onSelectIndex, __DtStep_2)
        mDescContents.setFont( mDescTitleFont );
        mDescContents.drawText( "End", LRect( 8, 2, 256, 256 ) );

        mFormatText.setText( "�^�C�g����ʂɖ߂�܂��B" );
        mFormatText.build();
    }
	__DtTestPoint( __DtFunc__onSelectIndex, __DtStep_3 )
}



//=============================================================================
//								end of file
//=============================================================================