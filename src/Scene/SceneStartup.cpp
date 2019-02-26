//=============================================================================
//�y SceneStartup �z
//=============================================================================

#include "stdafx.h"
#include	"DT_SceneStartup.h"	/* For DynamicTracer-TestPoint */
#include "SceneTitle.h"
#include "SceneStartup.h"


//=============================================================================
// �� SceneStartup �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �J�n����
//---------------------------------------------------------------------
void SceneStartup::onStart()
{

    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    Graphics->setBGColor( 0, 0, 0 );

    mLogoSprite = LSprite::create( LTexture::create( "Data/Graphics/Frontend/Logo_1.png" ) );

    LTexture tex = LTexture::create( "Data/Graphics/Frontend/Title_1.png" );

    mFlashSprite = LSprite::create( tex );
    mFlashSprite->setCenter( 64, 8 );
    mFlashSprite->setPosition( Graphics.getScreenSize().x, Graphics.getScreenSize().y / 2 );
    mFlashSprite->setSrcRect( 0, 496, 128, 16 );

    mFlashScale.setCapacity( 2 );
    mFlashScale.setTimeTickPerSec( 1.0 );
    mFlashScale.addKeyFrame( 0, 60 );
    mFlashScale.addKeyFrame( 5, 0 );

    // �����p
    mTitleSubTextSprite = LSprite::create( LTexture::create( "Data/Graphics/Frontend/Title_1.png" ) );
    mTitleSubTextSprite->setPosition( 108, 192 );
    mTitleSubTextSprite->setSrcRect( 0, 192 + 16, 424, 16 );
    mTitleSubTextSprite->setVisible( false );

    mStep = 0;
    mFrameCount = 0;



	__DtTestPoint( __DtFunc_onStart, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void SceneStartup::onUpdate()
{
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    switch ( mStep )
    {
        /////////////////////// ���S�\���X�e�b�v
        case 0:
        {
            // �M��
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
            mFlashScale.setTime( mFrameCount );
            mFlashSprite->setScale( mFlashScale.getValue() );

            if ( mFrameCount < 20 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_2)
                LLayer::getBGLayer()->blur( 0, 0.9f, 1.02, LVector3( ( 20 - mFrameCount ) * 30, 240, 0 ), false );
            }
            else if ( mFrameCount == 20 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_3)
                LLayer::getBGLayer()->blur( 0.2, 0.9f, 1.02, LVector3( ( 20 - mFrameCount ) * 30, 240, 0 ), false );
            }

            // �{�^���������ꂽ�ꍇ�A150 �t���[���ڂ܂Ŕ�΂�
            if ( Input->getPressedButton() && mFrameCount < 150 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_4)
                mFrameCount = 150;
            }

            // �t�F�[�h�A�E�g�J�n
            if ( mFrameCount == 150 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_5)
                LLayer::getBGLayer()->setTone( LTone( -1, -1, -1, -1 ), 0.5 );
            }

            // �����\����
            if ( mFrameCount >= 200 )
            {
                // �t�F�[�h�C��
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_6)
                LLayer::getBGLayer()->setTone( LTone( 0, 0, 0, 0 ), 0.5 );

                LLayer::getBGLayer()->blur( 0, 0, 1.00, LVector3( 0, 0, 0 ), false );

                mLogoSprite->setVisible( false );
                mStep = 1;
                mFrameCount = 0;
            }
            break;
        }
        /////////////////////// �����\���X�e�b�v
        case 1:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_7)
            if ( mFrameCount >= 50 && mFrameCount <= (50 + 53 * 2) ) // 53 ����
            {
                u32 count = mFrameCount - 50;
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_8)
                mTitleSubTextSprite->setVisible( true );
                mTitleSubTextSprite->setSrcRect( 0, 192 + 16, count / 2 * 8, 16 );
            }

            // �{�^���܂��ꂽ�ꍇ�A220 �t���[���ڂ܂Ŕ�΂�
            if ( Input->getPressedButton() && mFrameCount < 150 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_9)
                mFrameCount = 220;
            }


            // �t�F�[�h�A�E�g�J�n
            if ( mFrameCount == 220 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_10)
                LLayer::getBGLayer()->setTone( LTone( 1, 1, 1, 1 ), 0.4 );
            }

            // �^�C�g����ʂ�
            if ( mFrameCount >= 280 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_11)
                LGameScene::changeScene( LN_NEW SceneTitle() );
            }
            break;
        }
    }
    
    ++mFrameCount;
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_12 )
}

//---------------------------------------------------------------------
// �� �I������
//---------------------------------------------------------------------
void SceneStartup::onTerminate()
{

	__DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
}



//=============================================================================
//								end of file
//=============================================================================