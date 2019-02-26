//=============================================================================
//�y DamagePop �z
//-----------------------------------------------------------------------------
///**
//  @file       DamagePop.h
//  @brief      DamagePop
//  @author     yama
//*/
//=============================================================================

#pragma once

#include <list>

//=============================================================================
// �� DamagePop �N���X
//-----------------------------------------------------------------------------
///**
//  @brief     ��_���[�W���ȂǂɃ|�b�v���鐔�����Ǘ�����N���X
//*/
//=============================================================================
class DamagePop
{
public:

    DamagePop();

    ~DamagePop();

    //---------------------------------------------------------------------
    ///**
    //  @brief      ������\��������
    //
    //  @param[in]  pos_   : �o����������W (3D���)
    //  @param[in]  value_ : �l (���̐���)
    //  @param[in]  type_  : ���l�̎��(�F 0=�� 1=�_���[�W 2=�� 3=�N���e�B�J��)
    //
    //*/
    //---------------------------------------------------------------------
    void popNumber( const LVector3& pos_, u32 value_, int type_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      �t���[���X�V
    //*/
    //---------------------------------------------------------------------
    void update();



    
private:

    // �|�b�v���Ă��鐔���ЂƂ���\���N���X
    class PopNumber
    {
    public:
        PopNumber( const LVector3& pos_, u32 value_, int type_, LTexture texture_ );
        ~PopNumber();

        bool update();

    private:

        LVector3    mPosition;
        LVector3    mVelocity;
        LSprite     mNumberSprite;
        LTexture    mNumberTexture;
        u32         mFrameCount;

    };

private:

    typedef std::list< PopNumber* >     PopNumberList;

private:

    PopNumberList   mPopNumberList;
    LTexture        mNumberTexture;
    
    
};

//=============================================================================
//								end of file
//=============================================================================