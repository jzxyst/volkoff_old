//=============================================================================
//�y GameFrontendManager �z
//-----------------------------------------------------------------------------
///**
//  @file       GameFrontendManager.h
//  @brief      GameFrontendManager
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "PlayerStateWindow.h"
#include "DamagePop.h"

class Player;
//class PlayerStateWindow;
class GuideNamePlate;
class PointCursor;

//=============================================================================
// �� GameFrontendManager �N���X
//-----------------------------------------------------------------------------
///**
//  @brief      �Q�[�����̃t�����g�G���h�̊Ǘ��N���X (�V���O���g��)
//*/
//=============================================================================
class GameFrontendManager
    : public LNote::Core::Base::NonCopyable
{
public:

    /// �C���X�^���X�̎擾
    static GameFrontendManager* getInstance();

    /// ������
    void initialize( Player* player_ );

    /// �I������
    void finalize();

    /// �t���[���X�V
    void update();

    /// PlayerStateWindow �̎擾
    PlayerStateWindow* getPlayerStateWindow() const { return mPlayerStateWindow; }

    /// �l�[���v���[�g�̕����`��Ɏg���t�H���g�̎擾
    Core::Graphics::IFont* getNamePlateFont() const { return mNamePlateFont; }

    /// �_���[�W�|�b�v�Ǘ��N���X�̎擾
    DamagePop* getDamagePopManager() const { return mDamagePop; }

    /// ��ʒ����ɁuLevelUp�v�\��
    void showLevelUp();

    /// �t���A�ύX���̃t���A���\���G�t�F�N�g�̕\���J�n
    void showFloorNum( int num_ );



    Core::Graphics::IFont* getGuidNamePlateFont() const { return mGuidNamePlateFont; }
 
    /// (GuidNamePlate �̃R���X�g���N�^����Ă΂��)
    void addGuidNamePlate( GuideNamePlate* plate_ );

    /// (GuidNamePlate �̃f�X�g���N�^����Ă΂��)
    void removeGuidNamePlate( GuideNamePlate* plate_ );

    /// CharacterNamePlate::show ���Ă΂ꂽ���̃R�[���o�b�N
    void onShowCharacterNamePlate();

    float getGlobalFadeOpacity() { return mGlobalFadeOpacity.getValue(); }

    PointCursor* getPointCursor() const { return mPointCursor; }

private:

    /// �R���X�g���N�^
    GameFrontendManager();

    /// �f�X�g���N�^
    ~GameFrontendManager();

private:

    enum ProcStep
    {
        GFM_PTEP_SETUP = 0,     ///< �J�n���
        GFM_PTEP_IDLE,          ///< ���ʂ̊Ď����
    };

    typedef std::list< GuideNamePlate* >    GuideNamePlateList;

private:

    ProcStep            mStep;
    u32                 mFrameCount;
    

    LTexture                mNumberTexture1;    ///< �����e�N�X�`��
    PlayerStateWindow*      mPlayerStateWindow;
    Core::Graphics::IFont*  mNamePlateFont;

    RapidNumber<int>        mFrameXPos;

    DamagePop*              mDamagePop;


    GuideNamePlateList      mGuideNamePlateList;
    Core::Graphics::IFont*  mGuidNamePlateFont;     ///< �K�C�h�p�̉����t�H���g

    u32                     mShowCharacterNamePlateCount;
    Core::Animation::FadeValue< float >  mGlobalFadeOpacity;

    u32                     mLevelupFrameCount;
    LSprite                 mLevelupSprites[ 2 ];
    LSprite                 mLevelEffectSprite;

    PointCursor*            mPointCursor;


    Core::Animation::FixedLengthScalar     mFloorNumAnim;
    Core::Animation::FixedLengthScalar     mFloorNumAnimAlpha;
    LTexture                mFloorInfoTexture;
    LSprite                 mFloorInfoSprite[ 3 ];
    float                   mFloorInfoOffset;
};

//=============================================================================
//								end of file
//=============================================================================