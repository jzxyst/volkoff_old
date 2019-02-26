//=============================================================================
//�y SceneStartup �z
//-----------------------------------------------------------------------------
///**
//  @file       SceneStartup.h
//  @brief      SceneStartup
//  @author     yama
//  @par
//              �N����A��ԍŏ��Ɏ��s�����V�[���B
//              �O�܂� SceneLogo �Ƃ����O�����Ă����́B
//*/
//=============================================================================

#pragma once

//=============================================================================
// �� SceneStartup �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�N����A��ԍŏ��Ɏ��s�����V�[��
//*/
//=============================================================================
class SceneStartup : public LGameScene
{
public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneStartup"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

private:

    

    LSprite                             mFlashSprite;
    Core::Animation::FixedLengthScalar  mFlashScale;

    LSprite     mLogoSprite;

    LSprite     mTitleSubTextSprite;

    int         mStep;
    u32         mFrameCount;


};

//=============================================================================
//								end of file
//=============================================================================