//=============================================================================
//�y PlayerStateWindow �z
//-----------------------------------------------------------------------------
///**
//  @file       PlayerStateWindow.h
//  @brief      PlayerStateWindow
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "RapidNumber.h"

class Player;


//=============================================================================
// �� PlayerStateWindow �N���X
//-----------------------------------------------------------------------------
///**
//  @brief      �v���C���[�̏�Ԃ�\������E�B���h�E (�Q�[����ʂ̍����)
//*/
//=============================================================================
class PlayerStateWindow
{
public:

    /// �R���X�g���N�^
    PlayerStateWindow( Player* player_ );

    /// �f�X�g���N�^
    ~PlayerStateWindow();

public:

    /// �ʒu�̐ݒ�
    void setPosition( float x_, float y_ );

    /// �s�����x�̐ݒ�
    void setOpacity( float op_ );

    /// ���t���b�V�� (�Ƃ肠�������͋�B���A���^�C���ɍX�V�ł��Ȃ���������������g���悤�ɂ���)
    void refresh();

    /// �t���[���X�V
    void update();

private:

    enum ProcStep
    {
        PSW_PTEP_SETUP = 0,     ///< �J�n��ԁB�o�[�𑝂₷�B
        PSW_PTEP_IDLE,          ///< ���ʂ̊Ď����
    };

private:

    LVector3    mPosition;

    Player*     mPlayer;
    ProcStep    mStep;

    LTexture    mFrontendTexture;           ///< Frontend_1.png
    LTexture    mNumberTextureS;            ///< �����������e�N�X�`��
    LTexture    mNumberTextureL;            ///< �傫�������e�N�X�`��

    LSprite     mFrameWindow;               ///< �g
    LSprite     mFloorNumSprite[ 2 ];       ///< �t���A��
    LSprite     mScoreNumSprite[ 10 ];      ///< �X�R�A
    LSprite     mHPBarSprite;               ///< HP �o�[
    LSprite     mHPDieBarSprite;            ///< HP �o�[�́A�_���[�W���󂯂č��ꂽ����
    LSprite     mWeaponIconSprite;          ///< ����A�C�R��
    LSprite     mWeaponLevelSprite;         ///< ���탌�x��
    LSprite     mWeaponEXPBar;              ///< ����o���l�o�[
    LSprite     mWeaponCountSprite[ 3 ];    ///< ����g�p��
    LSprite     mKeySprite;                 ///< ��
    LSprite     mKeyEffectSprite[ 2 ];      ///< �����莞�G�t�F�N�g


    u32         mLastWeaponCount;           ///< �g�p�񐔂̌x���J�n�̔���Ɏg��
    LSprite     mWeaponCountWarningSprite[ 3 ];    ///< ����g�p��
    u32         mWarningFrameCount;
    u8          mWarningShowedFlag;         ///< 30%�ȉ��ɂȂ����u�Ԃ�\�������ꍇ�� 1�A15%�ȉ���\�������ꍇ��2

    u32         mPlayerHP;
    u32         mHPDieWidth;                ///< HP �̖����Ȃ��������̕�

    RapidNumber<int>    mHPNumber;
    u32                 mDieWaitFrameCount; ///< �����Ȃ����������̌����J�n�܂ł̑҂��t���[����

    u32         mEXPBarFrameCount;

    u8          mHasKey;    ///< ����\�����Ă���t���O
    u32         mKeyEffectFrameCount;


};

//=============================================================================
//								end of file
//=============================================================================