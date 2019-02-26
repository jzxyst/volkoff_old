//=============================================================================
//�y GuideNamePlate �z
//-----------------------------------------------------------------------------
///**
//  @file       GuideNamePlate.h
//  @brief      GuideNamePlate.h
//  @author     yama
//*/
//=============================================================================

#pragma once

class GameObject;

//=============================================================================
// �� GuideNamePlate �N���X
//-----------------------------------------------------------------------------
///**
//  @brief      ����A���A�o���A�񕜃A�C�e�����w�������t�L�_�V
//*/
//=============================================================================
class GuideNamePlate
{
public:

    /// �R���X�g���N�^
    GuideNamePlate();

    /// �f�X�g���N�^
    ~GuideNamePlate();

public:

    /// ������ (arrow_color_:0���珇�ɁA�A�΁A��   ox_ oy_: ���W�I�t�Z�b�g(3D��ԏ�))
    void initialize( GameObject* object_, int arrow_color_, float ox_ = 0.0f, float oy_ = 0.0f );

    /*/// �t�F�[�h�C���J�n
    void startFadein();

    /// �t�F�[�h�A�E�g�J�n
    void startFadeout();*/

    /// �t���[���X�V
    void update();

private:

    /// �ʒu�̐ݒ� (update() ����Ă΂��B�����o���̐���ۂŎw�肷��B)
    void _setPosition( const LVector3& pos_ );

private:

    GameObject*     mGameObject;
    LSprite         mFrameSprite;
    LSprite         mArrowSprite;
    LSprite         mNameTextSprite;
    LTexture        mNameTextTexture;
    LVector3        mOffsetPos;

    Core::Animation::FadeValue< float >  mFadeOpacity;
    

    bool            mIsNearPlayer;  /// �v���C���[�̋߂��ɂ����āA�\�����Ă���t���O


    /*
    LSprite     mFrameSprite;
    LSprite     mHPBarSprite;
    LSprite     mDieBarSprite;
    LSprite     mNameTextSprite;
    LSprite     mBalloonPointSprite;
    LTexture    mNameTextTexture;

    RapidNumber< float >  mHPValue;

    u32         mVisibleFrameCount;

    bool        mVisible;
    */

};

//=============================================================================
//								end of file
//=============================================================================