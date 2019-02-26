//=============================================================================
//�y CharacterNamePlate �z
//-----------------------------------------------------------------------------
///**
//  @file       CharacterNamePlate.h
//  @brief      CharacterNamePlate
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "RapidNumber.h"

class Character;

//=============================================================================
// �� CharacterNamePlate �N���X
//-----------------------------------------------------------------------------
///**
//  @brief      �L�����N�^�[�̓��̏゠����ɕ\������A���O�� HP �o�[
//
//  @par
//              �Ƃ肠�����L�����N�^�[�̃����o�Ƃ��Ď����Ă����B
//*/
//=============================================================================
class CharacterNamePlate
{
public:

    /// �R���X�g���N�^
    CharacterNamePlate();

    /// �f�X�g���N�^
    ~CharacterNamePlate();

public:

    /// ������
    void initialize( Character* character_ );

    /// ����Ԃ̐ݒ� (false �ɂ���ƁAstartShow() ���Ă΂�Ă��\�����Ȃ�)
    void setVisible( bool flag_ );

    /// �\���J�n (�U�������������ꍇ�ȂǁA�\������ꍇ�ɂ��ꂾ���ĂԁB���Ƃ͏����̪��ޱ�Ă���)
    void startShow();

    /// �t���[���X�V
    void update();

private:

    /// �ʒu�̐ݒ� (update() ����Ă΂��B�����o���̐���ۂŎw�肷��B)
    void _setPosition( float x_, float y_, const LVector3& screen_pos_ );

private:

    Character*  mCharacter;
    LSprite     mFrameSprite;
    LSprite     mHPBarSprite;
    LSprite     mDieBarSprite;
    LSprite     mNameTextSprite;
    LSprite     mBalloonPointSprite;
    LTexture    mNameTextTexture;

    RapidNumber< float >  mHPValue;

    u32         mVisibleFrameCount;

    int         mFrameWidth;        ///< �E�B���h�E�̕� (�ʏ�72�A�����������ꍇ��96)
    int         mSrcRectOY;
    float       mHPBarMaxWidth;

    bool        mVisible;

};

//=============================================================================
//								end of file
//=============================================================================