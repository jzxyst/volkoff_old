//=============================================================================
//�y SceneRanking �z
//-----------------------------------------------------------------------------
///**
//  @file       SceneRanking.h
//  @brief      SceneRanking
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "../Frontend/RankingNameplate.h"

//=============================================================================
// �� SceneRanking �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�����L���O���
//*/
//=============================================================================
class SceneRanking : public LGameScene
{
public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneRanking"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

private:

	

    int         mPhase;
    int         mFrameCount;


	LTexture	mRankingTexture;

    LSprite     mBGWhiteSprite;
    LSprite     mWeaponSprite;

	RankingNameplate	mRankingNameplate[MAX_RANKING_NUM];
};

//=============================================================================
//								end of file
//=============================================================================