//=============================================================================
//�y GameManager �z
//-----------------------------------------------------------------------------
///**
//  @file       GameManager.h
//  @brief      GameManager
//  @author     yama
//*/
//=============================================================================

#pragma once

#include <vector>
#include "../Event/EventManager.h"
#include "../Effect/EffectManager.h"
#include "GameServer.h"
#include "GameSession.h"

#define MAIN_BGM_NAME "Data/Sound/BGM/n32.ogg"


typedef enum _ENUM_RANK
{
	RANK_EASY = 0,
	RANK_NOMAL,
	RANK_HARD,
	RANK_VALFIRLE
}Rank;
class Player;
class Character;

//=============================================================================
// �� GameManager �N���X
//-----------------------------------------------------------------------------
///**
//  @brief      �Q�[���S�̂̊Ǘ��N���X�B�V���O���g���B
//
//  @par
//              �Q�[���S�̂ňꌳ�ɊǗ�����K�v������f�[�^�������B
//              �܂��A
//*/
//=============================================================================
class GameManager
    : public LNote::Core::Base::NonCopyable
{
public:

    /// �C���X�^���X�̎擾
    static GameManager* getInstance();

public:

    //---------------------------------------------------------------------
    ///**
    //  @brief      �e�Ƃ��ď���������
    //
    //  @par
    //              ���������A���̃z�X�g���T�[�o�Ƃ��ē��삷��悤�ɂ���B
    //              ��������A������ IP �A�h���X�Ȃǂ�m�邽�߂ɂ� getHostInfo() ���g�����ƁB
    //              �ЂƂ�Ńv���C����Ƃ��͂���ŏ������B
    //*/
    //---------------------------------------------------------------------
    void initializeParent();

    //---------------------------------------------------------------------
    ///**
    //  @brief      �q�Ƃ��ď���������
    //
    //  @retval     true  : ����
    //  @retval     false : ���s (�ڑ��ł��Ȃ�����)
    //
    //  @par
    //              �ڑ���ʂŐڑ���� IP �A�h���X����͂�����A
    //              ��������̊֐��ɓn���ď���������B
    //
    //              �����ɏ�����Ԃ��āA�ڑ������������ꍇ��
    //              �ڑ������C�x���g���������g�ɔ��s����̂������Ǝv���B
    //*/
    //---------------------------------------------------------------------
    bool initializeChild( const char* parent_ip_addr_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      �Q�[���̏I������
    //
    //  @par
    //              �Q�[����ʂ���^�C�g����ʂɖ߂�Ƃ����ɌĂԂ��ƁB
    //*/
    //---------------------------------------------------------------------
    void finalize();

    //---------------------------------------------------------------------
    ///**
    //  @brief      �R���e�B�j���[�ɔ����ăo�b�N�A�b�v�����
    //*/
    //---------------------------------------------------------------------
    void commit();

    //---------------------------------------------------------------------
    ///**
    //  @brief      �R���e�B�j���[���̃��Z�b�g
    //
    //  @par
    //              �Q�[���I�[�o�[��ʂ� reset �� SceneGame �ړ� �̏��ɌĂԂ��ƁB
    //*/
    //---------------------------------------------------------------------
    void reset();

    //---------------------------------------------------------------------
    ///**
    //  @brief      GameSession �̎擾
    //
    //  @par
    //              �T�[�o�Ƃ̃Z�b�V������\���B
    //              �������g���T�[�o(�e)�ł���ꍇ�A����͎������g���w���B
    //              (���ʂ͂���Ȃ��ƋC�ɂ��Ȃ��Ă������悤�ɍ���Ă��邯��)
    //*/
    //---------------------------------------------------------------------
    GameSession* getGameSession() { return mGameSession; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      �t���[���X�V
    //
    //  @par
    //              ���t���[���Ăяo���K�v�̂���X�V�����B
    //*/
    //---------------------------------------------------------------------
    void update();

    //---------------------------------------------------------------------
    ///**
    //  @brief      �C�x���g����
    //
    //  @par
    //              �e�I�u�W�F�N�g�� HandleEvent �̌Ăяo�����݂����Ȃ��񂶁c
    //*/
    //---------------------------------------------------------------------
    int HandleEvent( u32 event_, void *args_ );

	void setRank(u32 rank_) { mRank = rank_; }

    /// EffectManager �擾
    EffectManager* getEffectManager() const { return mEffectManager; }

    /// ���X�{�X�𐶐��������ɃR���ŃZ�b�g����
    void setLastBossCharacter( Character* boss_ ) { mLastBoss = boss_; }

    /// (�O���[�o���ϐ��ɂ��Ă��������ǁA�Ƃ肠�����V���O���g���œO��)
    Character* getLastBossCharacter() const { return mLastBoss; }



public:

    /// ���݂̃t���A���̎擾
    u32 getFloorNum() const { return mFloorNum; }

    /// ���݂̃X�R�A�̎擾
    u32 getScore() const { return mScore; }
	u8  getRank() const {return mRank;}
	/// Player �̎擾
	Player* getPlayer() { return mPlayer; }
	u8  getOpenflag() { return mOpenflag;}
	void NextFloor() {++mFloorNum;}

	const u8 getKeyflag() const {return mKeyflag;}

    void setKeyflag(const u8 Keyflag_) {mKeyflag = Keyflag_;}

	void setFloorNum(const u32 FloorNum_){mFloorNum=FloorNum_;}

	void setScore(const u32 Score_){mScore=Score_;}

	void setOpenflag(const u8 open_flag_) {mOpenflag = open_flag_ ;}

	void resetGameTime() { mGameTime = 0; }

	// �t���[�����P��
	lnU32 getGameTime() const { return mGameTime; }

	// ���ݎ��Ԃ�S�̂̕b�� ����/��/�b �Ŏ擾
	static void splitGameTime( lnU32 frame_count_, u32* h_, u32* m_, u32* s_ )
	{
		//mGameTime;	// �t���[����

		u32 s = frame_count_ / 60;
		*h_ = s / 3600;
		*m_ = (s % 3600) / 60;
		*s_ = (s % 60);
	}

private:

    /// �R���X�g���N�^
    GameManager();

    /// �f�X�g���N�^
    ~GameManager();

private:

    GameServer*     mGameServer;    ///< �T�[�o�BGameManager ���e�Ƃ��ď��������ꂽ�ꍇ�ɂ̂ݍ쐬�����
    GameSession*    mGameSession;
    EffectManager*  mEffectManager;

    u32             mFloorNum;      ///< ���݂̃t���A��
    u32             mScore;         ///< ���݂̃X�R�A
	u8              mRank;           ///<�@��Փx
	Player*			mPlayer;        ///< �����̃z�X�g�ő��삷��L�����N�^�[
	u8             mKeyflag;	//���t���O	
	u8             mOpenflag;
	//u32            mTime;
	lnU32			mGameTime;

    Character*      mLastBoss;

    struct
    {
        u32 Score;
		u32 Time;

    } mBackup;

};

//=============================================================================
//								end of file
//=============================================================================
