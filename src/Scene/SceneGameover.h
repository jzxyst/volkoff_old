//=============================================================================
//�y SceneGameover �z
//-----------------------------------------------------------------------------
///**
//  @file       SceneGameover.h
//  @brief      SceneGameover
//  @author     yama
//*/
//=============================================================================

#pragma once

class PointCursor;

//=============================================================================
// �� SceneGameover �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�Q�[���I�[�o�[���
//*/
//=============================================================================
class SceneGameover
    : public LGameScene
{
public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneGameover"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

private:

    /// �I�����Ă��鍀�ڂ�ύX����
    void _onSelectIndex();

private:

    LSprite     mBlindSprite;
    LSprite     mBlindSprite2;

    int         mStep;
    int         mFrameCount;
    int         mGotoScene;
    int         mSelectIndex;

    Core::Animation::FadeValue< float >  mLogoFadeValue;
    Core::Animation::FadeValue< float >  mFadeValue;

    LSprite     mLogoSprite;

    LSprite     mDescWindowSprite;      // �����E�B���h�E�̘g
    LSprite     mDescContentsSprite;
    LTexture    mDescContents;          // �����E�B���h�E�̓��e
    LFont       mDescTitleFont;
    int         mWindowFadeCount;
    Utility::FormatText mFormatText;

    LSprite     mCommandSprite[ 2 ];

    PointCursor*    mPointCursor;

};

//=============================================================================
//								end of file
//=============================================================================