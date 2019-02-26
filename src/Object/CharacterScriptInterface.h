//=============================================================================
//�y CharacterScriptInterface �z
//-----------------------------------------------------------------------------
///**
//  @file       CharacterScriptInterface.h
//  @brief      CharacterScriptInterface
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "Character.h"

//=============================================================================
// �� CharacterScriptInterface �N���X
//-----------------------------------------------------------------------------
///**
//	@brief      Lua �ɓo�^����֐����܂Ƃ߂��N���X
//
//  
//*/
//=============================================================================
class CharacterScriptInterface
{
public:

    /// �C���X�^���X�̎擾
    static CharacterScriptInterface* getInstance();

    //---------------------------------------------------------------------
	///**
    //  @brief      �A�j���[�V�����̃t���[���X�V
    //
    //  @param[in]  character_  : �X�V����L�����N�^�[
    //*/    
    //---------------------------------------------------------------------
    void update( Character* character_ );

private:

    /// �R���X�g���N�^
    CharacterScriptInterface();

    /// �f�X�g���N�^
    ~CharacterScriptInterface();


private:

    // �� �ȉ��� Lua �ɓo�^����֐�

    //---------------------------------------------------------------------
	///**
    //  @brief      �L�����N�^�[�̑�����U���O���[�v�̎擾
    //
    //  @param[in]  p1 : �L�����N�^�[�̃|�C���^
    //
    //  @return     AttackedGroup �̒l
    //*/
    //---------------------------------------------------------------------
	static int getCharaAttackedGroup( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      �L�����N�^�[�̃|�W�V�����̎擾
    //
    //  @param[in]  p1 : �L�����N�^�[�̃|�C���^
    //
    //  @return     X���W,Y���W
    //*/
    //---------------------------------------------------------------------
	static int getCharaPosition( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      �L�����N�^�[�̏�Ԃ�ݒ肷��
    //
    //  @param[in]  p1 : �L�����N�^�[�̃|�C���^
    //  @param[in]  p2 : �ݒ肷����
    //*/
    //---------------------------------------------------------------------
	static int setCharaState( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      �t���[������ݒ肷��
    //
    //  @param[in]  p1 : �L�����N�^�[�̃|�C���^
    //  @param[in]  p2 : �t���[����
    //
    //  @par
    //              lua �� update() ���I�������A�����I�Ƀt���[������ +1 �����B
    //              �A�j���[�V�������[�v���s�������ꍇ�A���̊֐����g����
    //              �l��ݒ肷�邱�ƁB
    //*/
    //---------------------------------------------------------------------
	static int setFrameCount( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      �L�����N�^�[�̃A�j���p�^�[����ݒ肷��
    //
    //  @param[in]  p1 : �L�����N�^�[�̃|�C���^
    //  @param[in]  p2 : �ݒ肷��p�^�[���ԍ�
    //*/
    //---------------------------------------------------------------------
	static int setPuttern( lua_State *l_ );


    //---------------------------------------------------------------------
	///**
    //  @brief      �U���̓����蔻����s��
    //
    //  @param[in]  p1 : �L�����N�^�[�̃|�C���^
    //  @param[in]  p2 : �Ώۂ̃O���[�v (AttackedGroup �̑g�ݍ��킹)
    //
    //  @par
    //              ���݂̃A�j���[�V������� (CharaState�A�����A�o�߃t���[����)
    //              ����U���̓����蔻������s���A���������I�u�W�F�N�g��
    //              �n���h���̔z�� (�e�[�u��) ��Ԃ��B
    //*/
    //---------------------------------------------------------------------
	static int judgeAttackCollision( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      �U�����ʂ̓K�p (�Ώۂ��U������)
    //
    //  @param[in]  p1 : �L�����N�^�[�̃|�C���^ (�U�����L�����N�^�[)
    //  @param[in]  p2 : �U���Ώۂ�\���L�����N�^�[�̃|�C���^ (��_���[�W���L�����N�^�[)
    //  @param[in]  p3 : ��{�_���[�W��
    //  @param[in]  p4 : �����_���� (30�Ƃ���ƁA�}30% �͈̔͂ŕϓ�����)
    //  @param[in]  p5 : �N���e�B�J���� (%)
    //  @param[in]  p6 : �ӂ���΂��x�N�g�� X (�L�������E�������Ă��鎞)
    //  @param[in]  p7 : �ӂ���΂��x�N�g�� Y
    //  @param[in]  p8 : �̂�����t���[����
    //*/
    //---------------------------------------------------------------------
	static int attackEffect( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      �L�����N�^�[���폜����
    //
    //  @param[in]  p1 : �L�����N�^�[�̃|�C���^
    //
    //  @par
    //              �Ă΂ꂽ�t���[���� update() �I�����ɉ������B
    //*/
    //---------------------------------------------------------------------
	static int disposeObject( lua_State *l_ );

	//
	// Character::AttackLock
	// �U�����̍s������
	//
	// @param[in] p1 : �L�����N�^�[�̃|�C���^
	//
	// �ĂԂƃ��b�N��������܂��B
	// �U�����[�V�������W�����v�ȂǂŃL�����Z�������Ȃ�����
	//
	static int AttackLock( lua_State *l_ );

	//
	// Character::AttackUnLock
	// �U�����̍s����������
	//
	// @param[in] p1 : �L�����N�^�[�̃|�C���^
	//
	// �ĂԂƃ��b�N���͂���܂��B
	// �U�����[�V�����I�����ɂ͕K���Ă�ł�������
	//
	static int AttackUnLock( lua_State *l_ );

	//
	// CharacterScriptInterface::getOnGround
	//
	// @param[in] p1 : �L�����N�^�̃|�C���^
	//
	// ���ݒn��ɂ��邩�ǂ�����Ԃ�
	// 1        = �n��
	// ����ȊO = ��
	//
	static int getOnGround( lua_State *l_ );

	//
	// CharacterScriptInterface::setVelocity
	// �U�����̈ړ��ʂ��w��
	//
	// @param[in] p1 : �L�����N�^�̃|�C���^
	// @param[in] p2 : �L�����N�^�̂��x�N�g��
	// @param[in] p3 : �L�����N�^�̂��x�N�g��
	//
	// ���̓L�����������Ă�ق����{�ł�
	// �߂�l�͖���
	//
	static int setVelocity( lua_State *l_ );

	//
	// CharacterScriptInterface::CheckWeaponBreak
	//
	// @param[in] p1 : �L�����N�^�̃|�C���^
	// @param[in] p2 : ����ւ̃_���[�W
	//
	// �߂�l
	// �@�O�@�F����
	// �@�P�@�F����j��
	// ���킪��ꂽ���ǂ����𔻒肵�܂��B
	//
	static int CheckWeaponBreak( lua_State *l_ );

	//
	// CharacterScriptInterface::setBreakWeapon
	//
	// @param[in] p1 : �L�����N�^�̃|�C���^
	// @param[in] p2 : ���킪�j���������ǂ���
	//
	// �U�����ɌĂ�ł��������B
	// ���킪�j�����Ă����1���w�肵�Ă��������B
    //
    //  [yama] ����j�󎞂̑f��؂�ւ��� Character::UpdateSelf() �Ɉڍs�����̂ɍ��킹�āA
    //  ���̊֐��͔񐄏��B���g�͋�̎����ɂ��܂����B
	//
	static int setBreakWeapon( lua_State *l_ );

	//
	// CharacterScriptInterface::getBreakWeapon
	//
	// @param[in] p1 : �L�����N�^�̃|�C���^
	//
	// �U�����A���킪�j�����Ă��邩�m�F����
	// �f��͌Ă΂Ȃ���[�ɁI
	//
	static int getBreakWeapon( lua_State *l_ );

	static int PlaySE( lua_State *l_ );

	static int CreateEffect( lua_State *l_ );

	static int setDirection( lua_State *l_);

	static int setPosition( lua_State *l_);

	static int GrenadeGenerate( lua_State * l_);

	static int BulletGenerate( lua_State * l_);

	static int setInvincibleFrame( lua_State * l_);

	static int setAccel(lua_State * l_);

	static int getDirection( lua_State * l_);

	static int getLife(lua_State * l_);

	static int setLife(lua_State *l_);

	static int getMaxLife(lua_State * l_);

	static int getRank(lua_State * l_);

	static int getPlayerPos(lua_State *l_);
	static int Rand(lua_State *l_);

	static int getPhase(lua_State *l_);

	static int setNum(lua_State *l_);

	static int getNum(lua_State *l_);

	static int SummonEnemy(lua_State *l_);

	static int Division(lua_State *l_);

	static int SetOpacity(lua_State *l_);

	static int SetDestructfrag(lua_State *l_);

	static int GetDestructfrag(lua_State *_);

	static int ThunderGenerate(lua_State *_);

	static int SummonSoul(lua_State *_);

private:

    lua_State* mLuaStates[ WEAPON_MAX_NUM ];

};

//=============================================================================
//                              end of file
//=============================================================================
