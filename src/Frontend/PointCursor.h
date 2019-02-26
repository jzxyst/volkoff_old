//=============================================================================
//�y PointCursor �z
//-----------------------------------------------------------------------------
///**
//  @file       PointCursor.h
//  @brief      PointCursor
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "RapidNumber.h"

//=============================================================================
// �� PointCursor �N���X
//-----------------------------------------------------------------------------
///**
//  @brief     ���ڑI���Ŏg�����J�[�\��
//*/
//=============================================================================
class PointCursor
{
public:

    /// �R���X�g���N�^
    PointCursor()
    {
        mXPos.setInitValue( 0 );
        mXPos.setSpeed( 5 );
        mYPos.setInitValue( 0 );
        mYPos.setSpeed( 5 );
        mCursorSprite = LSprite::create( LTexture::create( "Data/Graphics/Frontend/Cursor_1.png" ) );
        mCursorSprite.setSrcRect( 0, 0, 32, 32 );
        mCursorSprite.setOpacity( 0 );
        mFrameCount = 0;
    }

    /// �f�X�g���N�^
    ~PointCursor() {}

public:

    /// �ړ���w��
    void moveTo( int x_, int y_ )
    {
        mXPos.set( x_ );
        mYPos.set( y_ );
        mFadeValue.start( mFadeValue.getValue(), 1.0f, 10 );
    }

    /// �����ʒu�ւ��ǂ��Ȃ���t�F�[�h�A�E�g
    void moveToInit()
    {
        mFadeValue.start( mFadeValue.getValue(), 0.0f, 10 );
    }

    /// �t���[���X�V
    void update()
    {
        mFadeValue.advanceTime( 1.0f );
        mXPos.update();
        mYPos.update();

        mCursorSprite.setPosition( mXPos.getValue(), mYPos.getValue() );
        mCursorSprite.setOpacity( mFadeValue.getValue() );

        mCursorSprite.setSrcRect( ( mFrameCount / 10 ) * 32, 0, 32, 32 );
        if ( mFrameCount >= 59 )
        {
            mFrameCount = 0;
        }
        
        ++mFrameCount;
    }


private:

    RapidNumber< int > mXPos;
    RapidNumber< int > mYPos;
    Core::Animation::FadeValue< float >   mFadeValue;

    LSprite mCursorSprite;
    int     mFrameCount;
    
};

//=============================================================================
//								end of file
//=============================================================================