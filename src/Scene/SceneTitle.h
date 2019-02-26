//=============================================================================
/*! 
    @addtogroup 
    @file       SceneTitle.h
    @brief      
    
    �^�C�g���̃V�[��
    
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

class PointCursor;

class SceneTitle : public LGameScene
{
public:

    /// �R���X�g���N�^
    SceneTitle();

public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneTitle"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

    // This tale is the last message we present to everyone.

private:

    /// �R�}���h���ڂ̕\���J�n
    void _startShowCommand( int type_ );


    /// ���̈ʒu�ݒ�
    void _setPointCursorIndex( int index_ );

private:

    

    u32     mStep;
    int     mFrameCount;

    

    LSprite     mRandomSprite;
    LSprite     mTitleFrameSprite;
    LSprite     mTitleTextSprite;
    LSprite     mTitleSubTextSprite;
    LSprite     mPressAnyKeySprite;

    LSprite     mTitleEffectSprite;

    LSprite     mSuperSprite[ 2 ];  // �㉺�̎����X�[�p�[
    LSprite     mCommandSprite[ 4 ];

    LSprite     mDescWindowSprite;      // �����E�B���h�E�̘g
    LSprite     mDescContentsSprite;
    LTexture    mDescContents;          // �����E�B���h�E�̓��e
    LFont       mDescTitleFont;
    int         mWindowFadeCount;
    Utility::FormatText mFormatText;


    Core::Animation::FixedLengthScalar  mRoundTripValue;        ///< 0.2 �`1.0 ����������l�B�A���t�@�l�p

    Core::Animation::FixedLengthScalar  mCommandFadeInX;
    Core::Animation::FixedLengthScalar  mCommandFadeInOpacity;

    int         mEntryedStep;
    int         mSelectIndex;
 
    PointCursor*    mPointCursor;

    int         mEndFrameCount;
};

//=============================================================================
//								End of File
//=============================================================================