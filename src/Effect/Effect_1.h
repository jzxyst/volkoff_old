//=============================================================================
//�y Effect_1 �z
//-----------------------------------------------------------------------------
///**
//  @file       Effect_1.h
//  @brief      Effect_1
//  @author     yama
//  @par
//              �G�t�F�N�g�ЂƂɂ��ЂƂ\�[�X�t�@�C���g���̂͗�ɂ���ăi�V�B
//              �ЂƂ̃\�[�X�� 10 ���炢�܂Ƃ߂�����ŁB
//*/
//=============================================================================

#pragma once

#include "EffectBase.h"

//=============================================================================
// �� Effect_Test_1 �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�e�X�g�p�G�t�F�N�g
//*/
//=============================================================================
class Effect_Test_1 : public EffectBase
{
public:

	/// �R���X�g���N�^
    Effect_Test_1( const LVector3& pos_ );

    /// �f�X�g���N�^
    ~Effect_Test_1();

public:

    /// �t���[���X�V (false ��Ԃ��Ɖ������)
    virtual bool update();

private:

    LBatchPanel  mPanel;
    u32     mFrameCount;

};


//=============================================================================
// �� Effect_Test_2 �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�e�X�g�p�G�t�F�N�g
//*/
//=============================================================================
class Effect_Test_2 : public EffectBase
{
public:

	/// �R���X�g���N�^
    Effect_Test_2( const LVector3& pos_ );

    /// �f�X�g���N�^
    ~Effect_Test_2();

public:

    /// �t���[���X�V (false ��Ԃ��Ɖ������)
    virtual bool update();

private:

    LBatchPanel  mPanel;
    u32     mFrameCount;

};



//=============================================================================
// �� Effect_Explosion �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�����G�t�F�N�g
//*/
//=============================================================================
class Effect_Explosion : public EffectBase
{
public:

	/// �R���X�g���N�^
    Effect_Explosion( const LVector3& pos_ );

    /// �f�X�g���N�^
    ~Effect_Explosion();

public:

    /// �t���[���X�V (false ��Ԃ��Ɖ������)
    virtual bool update();

private:
	static const int scm_nComNum = 5;

    LBatchPanel  mPanel;
    u32     mFrameCount;

};
//=============================================================================
// �� Effect_Explosion2 �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�����G�t�F�N�g2
//*/
//=============================================================================
class Effect_Explosion2 : public EffectBase
{
public:

	/// �R���X�g���N�^
    Effect_Explosion2( const LVector3& pos_ );

    /// �f�X�g���N�^
    ~Effect_Explosion2();

public:

    /// �t���[���X�V (false ��Ԃ��Ɖ������)
    virtual bool update();

private:
	static const int scm_nComNum = 5;

    LBatchPanel  mPanel;
    u32     mFrameCount;

};

//=============================================================================
// �� Effect_Test_3 �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�e�X�g�p�G�t�F�N�g
//*/
//=============================================================================
class Effect_Test_3 : public EffectBase
{
public:

	/// �R���X�g���N�^
    Effect_Test_3( const LVector3& pos_ );

    /// �f�X�g���N�^
    ~Effect_Test_3();

public:

    /// �t���[���X�V (false ��Ԃ��Ɖ������)
    virtual bool update();

private:

    LPanel  mPanel;
    u32     mFrameCount;

};

//=============================================================================
// �� Effect_Test_3 �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�e�X�g�p�G�t�F�N�g
//*/
//=============================================================================
class Effect_Thunder : public EffectBase
{
public:

	/// �R���X�g���N�^
    Effect_Thunder( const LVector3& pos_ );

    /// �f�X�g���N�^
    ~Effect_Thunder();

public:

    /// �t���[���X�V (false ��Ԃ��Ɖ������)
    virtual bool update();

private:

    LPanel  mPanel;
    u32     mFrameCount;

};
//=============================================================================
//								end of file
//=============================================================================
