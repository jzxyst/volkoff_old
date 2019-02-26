//=============================================================================
//�y CharacterNamePlate �z
//=============================================================================

#include "stdafx.h"
#include	"DT_CharacterNamePlate.h"	/* For DynamicTracer-TestPoint */
#include "../Object/Character.h"
#include "GameFrontendManager.h"
#include "CharacterNamePlate.h"

//=============================================================================
// �� CharacterNamePlate �N���X
//=============================================================================

    //---------------------------------------------------------------------
    // �� �R���X�g���N�^
    //---------------------------------------------------------------------
    CharacterNamePlate::CharacterNamePlate()
        : mCharacter            ( NULL )
        , mVisibleFrameCount    ( 0 )
        , mFrameWidth           ( 72 )
        , mSrcRectOY            ( 0 )
        , mHPBarMaxWidth        ( 64 )
        , mVisible              ( true )
    {
    	__DtTestPoint( __DtFunc_CharacterNamePlate, __DtStep_0 )
    }

    //---------------------------------------------------------------------
    // �� �f�X�g���N�^
    //---------------------------------------------------------------------
    CharacterNamePlate::~CharacterNamePlate()
    {
    	__DtTestPoint( __DtFunc_CharacterNamePlate, __DtStep_1 )
    }

    //---------------------------------------------------------------------
    // �� ������
    //---------------------------------------------------------------------
    void CharacterNamePlate::initialize( Character* character_ )
    {
        __DtTestPoint( __DtFunc_initialize, __DtStep_0 )
        mCharacter = character_;

        // �`�悷�閼�O
        const char* name = ( mCharacter->getName() ) ? mCharacter->getName() : "����������I";

        LTexture tex = LTexture::create( "Data/Graphics/Frontend/Frontend_1.png" );
        Core::Graphics::IFont* font = GameFrontendManager::getInstance()->getNamePlateFont();

        if ( !font )
        {
            __DtTestPoint(__DtFunc_initialize, __DtStep_1)
            setVisible( false );
            mFrameWidth = 72;
            mSrcRectOY = 0;
            mHPBarMaxWidth = 64;
        }
        else
        {
            // ���O��`�悵�����̕��ɂ���āA�E�B���h�E�T�C�Y�����߂�
            LRect rc;
            __DtTestPoint(__DtFunc_initialize, __DtStep_2)
            font->getTextSize( name, -1, &rc ); 
            if ( rc.w > 64 )
            {
                __DtTestPoint(__DtFunc_initialize, __DtStep_3)
                mFrameWidth = 96;
                mSrcRectOY = 48;
                mHPBarMaxWidth = 88;
            }
            else
            {
                __DtTestPoint(__DtFunc_initialize, __DtStep_4)
                mFrameWidth = 72;
                mSrcRectOY = 0;
                mHPBarMaxWidth = 64;
            }
        }



        // �g
        mFrameSprite = LSprite::create( tex );
        mFrameSprite->setSrcRect( 0, mSrcRectOY, mFrameWidth, 18 );

        // �o�[
        mHPBarSprite  = LSprite::create( tex );
        mHPBarSprite->setSrcRect( 8, mSrcRectOY + 24, 8, 8 );
        mDieBarSprite = LSprite::create( tex );
        mDieBarSprite->setSrcRect( 8, mSrcRectOY + 24, 8, 8 );

        // �����o��
        mBalloonPointSprite = LSprite::create( tex );
        mBalloonPointSprite->setSrcRect( 0, mSrcRectOY + 25, 5, 4 );

        // ���O��`�悷��e�N�X�`��
        mNameTextTexture = LTexture::create( mFrameWidth - 8, 16 );
        mNameTextTexture->getInterface()->setFont( font );
        mNameTextTexture->drawText( name, LRect( 0, 0, mFrameWidth - 8, 16 ), LN_TEXTALIGN_CENTER );
       
        // ���O�X�v���C�g
        mNameTextSprite = LSprite::create( mNameTextTexture );
        
        //mNameTextSprite->setSrcRect( 0, 48, 40, 16 );   // ��

        mHPValue.setInitValue( mCharacter->getLife() );


        // �ŏ��͑S����\��
        mFrameSprite->setVisible( false );
        mBalloonPointSprite->setVisible( false );
        mHPBarSprite->setVisible( false );
        mDieBarSprite->setVisible( false );
        mNameTextSprite->setVisible( false );

        mVisibleFrameCount = 0;
    	__DtTestPoint( __DtFunc_initialize, __DtStep_5 )
    }

    //---------------------------------------------------------------------
    // �� ����Ԃ̐ݒ� (false �ɂ���ƁAstartShow() ���Ă΂�Ă��\�����Ȃ�)
    //---------------------------------------------------------------------
    void CharacterNamePlate::setVisible( bool flag_ )
    {
        __DtTestPoint( __DtFunc_setVisible, __DtStep_0 )
        mVisible = flag_;
    	__DtTestPoint( __DtFunc_setVisible, __DtStep_1 )
    }

    //---------------------------------------------------------------------
    // �� �\���J�n (�U�������������ꍇ�ȂǁA�\������ꍇ�ɂ��ꂾ���ĂԁB���Ƃ͏����̪��ޱ�Ă���)
    //---------------------------------------------------------------------
    void CharacterNamePlate::startShow()
    {
        __DtTestPoint( __DtFunc_startShow, __DtStep_0 )
        if ( mVisible )
        {
            __DtTestPoint(__DtFunc_startShow, __DtStep_1)
            mVisibleFrameCount = 210;
            mFrameSprite->setOpacity( 1.0f );
            mBalloonPointSprite->setOpacity( 1.0f );
            mHPBarSprite->setOpacity( 1.0f );
            mDieBarSprite->setOpacity( 1.0f );
            mNameTextSprite->setOpacity( 1.0f );

            mFrameSprite->setVisible( true );
            mBalloonPointSprite->setVisible( true );
            mHPBarSprite->setVisible( true );
            mDieBarSprite->setVisible( true );
            mNameTextSprite->setVisible( true );

            mHPValue.set( mCharacter->getLife() );

            GameFrontendManager::getInstance()->onShowCharacterNamePlate();

            update();
        }
    	__DtTestPoint( __DtFunc_startShow, __DtStep_2 )
    }

    //---------------------------------------------------------------------
    // �� �t���[���X�V
    //---------------------------------------------------------------------
    void CharacterNamePlate::update()
    {
        __DtTestPoint( __DtFunc_update, __DtStep_0 )
        if ( mVisible && mVisibleFrameCount > 0 )
        {
            

            //-------------------------------------------------
            // HP�o�[
            __DtTestPoint(__DtFunc_update, __DtStep_1)
            if ( !mHPValue.isFinished() )
            {
                __DtTestPoint(__DtFunc_update, __DtStep_2)
                mHPValue.update();

                float rate = static_cast< float >( mHPValue.getValue() ) / mCharacter->getMaxLife();
                float w = rate * mHPBarMaxWidth;
                float lv = 0;

                // �c�� HP �ɂ���ăo�[�̐F��ς���
                if ( rate <= 0.15f )
                {
                    __DtTestPoint(__DtFunc_update, __DtStep_3)
                    lv = 2;
                }
                else if ( rate <= 0.50f )
                {
                    __DtTestPoint(__DtFunc_update, __DtStep_4)
                    lv = 1;
                }

                mHPBarSprite->setSrcRect(  0, mSrcRectOY + 32 + lv * 4, w, 4 );
                mDieBarSprite->setSrcRect( w, mSrcRectOY + 44, mHPBarMaxWidth - w, 4 );
            }




            //-------------------------------------------------
            // �ʒu
            const LMatrix& vp_mat = Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->getViewProjectionMatrix();


            LVector3 sc_pos;
            LVector3::transformCoord( &sc_pos, mCharacter->getPosition(), vp_mat );
        
            sc_pos.y *= -1.0f;  // y �͉��� + �Ȃ̂ŏ㉺���]
            sc_pos += 1.0f;     // 0.0�`2.0 �ɂ���
            sc_pos *= 0.5f;     // 0.0�`1.0 �ɂ���


            // _setPosition �ɓn���p�Ɉꎞ�ޔ�
            LVector3 tpos = sc_pos;

            const LVector2& size = Graphics->getScreenSize();
            sc_pos.x *= size.x;
            sc_pos.y *= size.y;

            // �ʒu���L�����̑����Ȃ̂ŁA��̕��Ɉړ�
            sc_pos.y -= 90.0f;
        

            _setPosition( sc_pos.x, sc_pos.y, tpos );

            

            

            
            


            
            --mVisibleFrameCount;

            // �t�F�[�h�A�E�g
            if ( mVisibleFrameCount <= 30 )
            {
                float op = 0.033f * mVisibleFrameCount;    // 0.033 = 1/30
                __DtTestPoint(__DtFunc_update, __DtStep_5)
                mFrameSprite->setOpacity( op );
                mBalloonPointSprite->setOpacity( op );
                mHPBarSprite->setOpacity( op );
                mDieBarSprite->setOpacity( op );
                mNameTextSprite->setOpacity( op );
            }

            
           
        }
        else
        {
            __DtTestPoint(__DtFunc_update, __DtStep_6)
            mFrameSprite->setVisible( false );
            mBalloonPointSprite->setVisible( false );
            mHPBarSprite->setVisible( false );
            mDieBarSprite->setVisible( false );
            mNameTextSprite->setVisible( false );
        }
    	__DtTestPoint( __DtFunc_update, __DtStep_7 )
    }

    //---------------------------------------------------------------------
    // �� �ʒu�̐ݒ� (update() ����Ă΂��)
    //---------------------------------------------------------------------
    void CharacterNamePlate::_setPosition( float x_, float y_, const LVector3& screen_pos_ )
    {
        __DtTestPoint( __DtFunc__setPosition, __DtStep_0 )
        mBalloonPointSprite->setPosition( x_ - 1, y_ - 3 );


        float ox = 62.0f * screen_pos_.x;

        // �t���[���̍���
        float x = x_ - 1 - ox;
        float y = y_ - 20;

        mFrameSprite->setPosition( x, y );
        mNameTextSprite->setPosition( x + 4, y + 1 );
        mHPBarSprite->setPosition( x + 4, y + 12 );
        mDieBarSprite->setPosition( x + 4 + mHPBarSprite->getSrcRect().w, y + 12 );
    	__DtTestPoint( __DtFunc__setPosition, __DtStep_1 )
    }

//=============================================================================
//								end of file
//=============================================================================