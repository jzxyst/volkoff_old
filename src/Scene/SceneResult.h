//=============================================================================
//�y SceneResult �z
//-----------------------------------------------------------------------------
///**
//  @file       SceneResult.h
//  @brief      SceneResult
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "../Frontend/rapidnumber.h"
#include "../Frontend/RankingNameplate.h"

class SceneResult;

/// Main.cpp �̃C�x���g���X�i�[���� onKeyEvent() ���Ăяo�����߂ɗp�ӁBSceneResult �����݂��Ă��Ȃ���� NULL�B�����������Ƃ�������ˁc
extern SceneResult* gSceneResult;

//=============================================================================
// �� SceneResult �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		���U���g���
//*/
//=============================================================================
class SceneResult : public LGameScene
{
public:

    /// �R���X�g���N�^ (�v���C���[���Ō�ɑ������Ă�������ԍ���n��)
    SceneResult( int weapon_no_ )
        : mWeaponNo ( weapon_no_ )
    {
		memset( mRankingName, 0, sizeof(mRankingName) );
	}

public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneResult"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

	/// Main.cpp �̃C�x���g���X�i�[����Ă΂��
	void onkeyEvent( char code_ );

private:

	static const int MAX_RANKING_NAME_LEN = 10;

	int			mScore;
	int			mTime;		// (�X�R�A�l)
	int			mRank;		// (�X�R�A�l)
	int			mTotalScore;
    int         mWeaponNo;
    int         mPhase;
    int         mFrameCount;

	RapidNumber<int>	mScoreRapid;
	RapidNumber<int>	mTimeRapid;
	RapidNumber<int>	mRankRapid;
	RapidNumber<int>	mTotalRapid;

    LSprite     mCharacterSprite;
    LSprite     mWeaponSprite;

	LTexture	mResultTexture;
	LSprite		mScoreLineSprites[3];
	LSprite		mTotalLineSprite;
	LSprite		mTimeSprite[6];
	LSprite		mRankSprite;
	LSprite		mScoreNumberSprites[10];
	LSprite		mTimeNumberSprites[10];
	LSprite		mRankNumberSprites[10];
	LSprite		mTotalNumberSprites[10];
	LSprite		mRankingFrameSprite;

	Core::Animation::FixedLengthScalar	mCommandFadeInX;
    Core::Animation::FixedLengthScalar	mCommandFadeInOpacity;

	bool								mIsNewRecord;
	int									mRankingNo;
	LSprite								mNewRecordSprite;
	Core::Animation::RoundTripValue<float>	mNewRecordOpacity;
	Core::Animation::FadeValue<float>			mNameplateOpacity;
	LSprite								mNewRecordBGSprite;

	LSprite		mMessageSprite;
	RankingNameplate	mRankingNameplate;

	lnChar	mRankingName[MAX_RANKING_NAME_LEN + 1];

	static const int LINE_MARGIN_X = 36;
	static const int LINE_MARGIN_Y = 82;

};

//=============================================================================
//								end of file
//=============================================================================