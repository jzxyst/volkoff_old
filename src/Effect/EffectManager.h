//=============================================================================
//�y EffectManager �z
//-----------------------------------------------------------------------------
///**
//  @file       EffectManager.h
//  @brief      EffectManager
//  @author     yama
//*/
//=============================================================================

#pragma once

#include <list>

class EffectBase;

//=============================================================================
// �� EffectManager �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�G�t�F�N�g�̊Ǘ��N���X�B�擾�� GameManager() ����B
//*/
//=============================================================================
class EffectManager
{
public:

	/// �R���X�g���N�^
    EffectManager();

    /// �f�X�g���N�^
    ~EffectManager();

public:

    /// �t���[���X�V (�쐬����Ă���S�ẴG�t�F�N�g�� update() ���Ă�)
    void update();

public:

    // �����̕��@���ƁA�C�e���[�g���͒ǉ����폜���ł��Ȃ��B��ŕK�v�ɂȂ����牽���l���Ă���

    /// EffectBase �̃R���X�g���N�^����Ă΂��
    void addEffect( EffectBase* effect_ );

    /// EffectBase �̃f�X�g���N�^����Ă΂��
    //void removeEffect( EffectBase* effect_ );

private:

    typedef std::list< EffectBase* >    EffectList;

private:

    EffectList      mEffectList;    ///< �S�ẴG�t�F�N�g���Ǘ����郊�X�g

};

//=============================================================================
//								end of file
//=============================================================================