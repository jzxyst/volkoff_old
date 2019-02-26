//=============================================================================
//【 SceneResult 】
//=============================================================================

#include "stdafx.h"
#include	"DT_SceneResult.h"	/* For DynamicTracer-TestPoint */
#include "../Utility/Util.h"
#include "../Game/GameManager.h"
#include "../Game/RankingManager.h"
#include "SceneTitle.h"
#include "SceneCredit.h"
#include "SceneResult.h"

//=============================================================================
// ■ SceneResult クラス
//=============================================================================

SceneResult* gSceneResult = NULL;

//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneResult::onStart()
{
    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    printf( "-------------------------------------------------\n" );
    printf( " ▼ リザルト\n" );
    printf( "       スコア:%d\n", GameManager::getInstance()->getScore() );
    printf( "       難易度:%d\n", GameManager::getInstance()->getRank() );
    printf( "-------------------------------------------------\n" );

	// 各スコア値
	mScore = LMath::max<lnU32>( 10, GameManager::getInstance()->getScore());
	mTime = LMath::max<lnU32>( 0, ( 1800 * 60 ) - GameManager::getInstance()->getGameTime() );	// 30 分から減算
	mRank = GameManager::getInstance()->getRank() * 1000000;
	mTotalScore = mScore + mTime + mRank;


	// ランクインのチェック
	mIsNewRecord = false;
	mRankingNo = 0;
	std::list<ScoreData> score_list = RankingManager::getInstance()->GetLocalStoryRanking( 10 );
	if (score_list.size() < MAX_RANKING_NUM)
	{
		__DtTestPoint(__DtFunc_onStart, __DtStep_1)
		mIsNewRecord = true;
		std::list<ScoreData>::iterator itr = score_list.begin();
		std::list<ScoreData>::iterator end = score_list.end();
		for (int i = 0; (itr != end) && (i < MAX_RANKING_NUM); ++itr, ++i)
		{
			__DtTestPoint(__DtFunc_onStart, __DtStep_2)
			if (mTotalScore > (*itr).unScore)
			{
				__DtTestPoint(__DtFunc_onStart, __DtStep_3)
				mRankingNo = i;
				break;
			}
		}
	}
	else
	{
		__DtTestPoint(__DtFunc_onStart, __DtStep_4)
		std::list<ScoreData>::iterator itr = score_list.begin();
		std::list<ScoreData>::iterator end = score_list.end();
		for (int i = 0; i < MAX_RANKING_NUM; ++itr, ++i)
		{
			__DtTestPoint(__DtFunc_onStart, __DtStep_5)
			if (mTotalScore > (*itr).unScore)
			{
				__DtTestPoint(__DtFunc_onStart, __DtStep_6)
				mIsNewRecord = true;
				mRankingNo = i;
				break;
			}
		}
	}

	

	
	mScoreRapid.set(mScore);
	mTimeRapid.set(mTime);
	mRankRapid.set(mRank);
	mTotalRapid.set(mTotalScore);


    // 背景色
    Graphics.setBGColor( 1.0f, 1.0f, 1.0f );

    mCharacterSprite = LSprite::create( LTexture::create( "Data/Graphics/Character/Char_Knife.png" ) );
    mCharacterSprite.setSrcRect( 0, 1760, 160, 160 );
    mCharacterSprite.setPosition( 160, 320, 0 );
    mWeaponSprite = LSprite::create( LTexture::create( "Data/Graphics/Object/Weapons.png" ) );
    mWeaponSprite.setSrcRect( mWeaponNo * 80, 0, 80, 80 );
    mWeaponSprite.setPosition( 100, 400, 0 );

	//------------------------------------------------------------
	//
	mResultTexture = LTexture::create( "Data/Graphics/Frontend/Result_1.png" );
	
	for ( int i = 0; i < 3; ++i )
	{
		__DtTestPoint(__DtFunc_onStart, __DtStep_7)
		mScoreLineSprites[ i ] = LSprite::create( mResultTexture );
		mScoreLineSprites[ i ].setSrcRect( 0, 96 + 32 * i, 352, 32 );
		mScoreLineSprites[ i ].setPosition( 0, LINE_MARGIN_Y - 4 + 48 * i );
		mScoreLineSprites[ i ].setOpacity( 0 );
	}

	mTotalLineSprite = LSprite::create( mResultTexture );
	mTotalLineSprite.setSrcRect( 0, 192, 608, 32 );
	mTotalLineSprite.setPosition( LINE_MARGIN_X, 256 );
	mTotalLineSprite.setOpacity( 0 );

	// 時間
	for ( int i = 0; i < 6; ++i )
	{
		__DtTestPoint(__DtFunc_onStart, __DtStep_8)
		mTimeSprite[ i ] = LSprite::create( mResultTexture );
		mTimeSprite[ i ].setSrcRect( 0, 0, 11, 16 );
		mTimeSprite[ i ].setPosition(
			LINE_MARGIN_X + 108 + 11 * i + (i / 2 * 8), LINE_MARGIN_Y + 2 + 48 );
		mTimeSprite[ i ].setOpacity( 0 );
	}
	u32 h, m, s;
	GameManager::getInstance()->splitGameTime(
		GameManager::getInstance()->getGameTime(),
		&h, &m, &s );

	// h
	u32 buf[2];
	Util::numberToArray(h, 2, buf);
	mTimeSprite[ 0 ].setSrcRect( 11 * buf[0], 0, 11, 16 );
	mTimeSprite[ 1 ].setSrcRect( 11 * buf[1], 0, 11, 16 );

	// m
	Util::numberToArray(m, 2, buf);
	mTimeSprite[ 2 ].setSrcRect( 11 * buf[0], 0, 11, 16 );
	mTimeSprite[ 3 ].setSrcRect( 11 * buf[1], 0, 11, 16 );

	// s
	Util::numberToArray(s, 2, buf);
	mTimeSprite[ 4 ].setSrcRect( 11 * buf[0], 0, 11, 16 );
	mTimeSprite[ 5 ].setSrcRect( 11 * buf[1], 0, 11, 16 );

	// ランク
	mRankSprite = LSprite::create( mResultTexture );
	mRankSprite.setSrcRect( 272, 20 * GameManager::getInstance()->getRank(), 92, 20 );
	mRankSprite.setPosition( LINE_MARGIN_X + 110, LINE_MARGIN_Y - 2 + 96 );
	mRankSprite.setOpacity( 0 );

	// Score 数値
	for ( int i = 0; i < 10; ++i )
	{
		__DtTestPoint(__DtFunc_onStart, __DtStep_9)
		mScoreNumberSprites[ i ] = LSprite::create( mResultTexture );
		mScoreNumberSprites[ i ].setSrcRect( 0, 0, 11, 16 );
		mScoreNumberSprites[ i ].setPosition( LINE_MARGIN_X + 234 + 11 * i - 32, LINE_MARGIN_Y + 2 );
		mScoreNumberSprites[ i ].setOpacity( 0 );
	}

	// Time 数値
	for ( int i = 0; i < 10; ++i )
	{
		__DtTestPoint(__DtFunc_onStart, __DtStep_10)
		mTimeNumberSprites[ i ] = LSprite::create( mResultTexture );
		mTimeNumberSprites[ i ].setSrcRect( 0, 0, 11, 16 );
		mTimeNumberSprites[ i ].setPosition( LINE_MARGIN_X + 234 + 11 * i - 32, LINE_MARGIN_Y + 2 + 48 );
		mTimeNumberSprites[ i ].setOpacity( 0 );
	}

	// Rank 数値
	for ( int i = 0; i < 10; ++i )
	{
		__DtTestPoint(__DtFunc_onStart, __DtStep_11)
		mRankNumberSprites[ i ] = LSprite::create( mResultTexture );
		mRankNumberSprites[ i ].setSrcRect( 0, 0, 11, 16 );
		mRankNumberSprites[ i ].setPosition( LINE_MARGIN_X + 234 + 11 * i - 32, LINE_MARGIN_Y + 2 + 96 );
		mRankNumberSprites[ i ].setOpacity( 0 );
	}

	// Total 数値
	for ( int i = 0; i < 10; ++i )
	{
		__DtTestPoint(__DtFunc_onStart, __DtStep_12)
		mTotalNumberSprites[ i ] = LSprite::create( mResultTexture );
		mTotalNumberSprites[ i ].setSrcRect( 0, 16, 18, 24 );
		mTotalNumberSprites[ i ].setPosition( LINE_MARGIN_X + 368 + 18 * i, LINE_MARGIN_Y + 206 );
		mTotalNumberSprites[ i ].setOpacity( 0 );
	}

	// New Record
	mNewRecordSprite = LSprite::create( mResultTexture );
	mNewRecordSprite.setSrcRect( 384, 0, 160, 32 );
	mNewRecordSprite.setPosition( 452, 340 );
	mNewRecordSprite.setOpacity( 0 );

	mNewRecordBGSprite = LSprite::create( mResultTexture );
	mNewRecordBGSprite.setSrcRect( 0, 224, 32, 32 );
	mNewRecordBGSprite.setScale(20);
	mNewRecordBGSprite.setPosition(0, 0);
	mNewRecordBGSprite.setOpacity( 0 );

	mRankingFrameSprite = LSprite::create(
		LTexture::create( "Data/Graphics/Frontend/Ranking_1.png" ));
	mRankingFrameSprite.setPosition(320, 200 + 48 / 2);
	mRankingFrameSprite.setCenter(256 / 2, 48 / 2);
	mRankingFrameSprite.setSrcRect(0, 0, 256, 48);
	mRankingFrameSprite.setOpacity(0);
	//mRankingFrameSprite.setScale(2);


	// コマンドのフェードインX座標
    mCommandFadeInX.setCapacity( 2 );
    mCommandFadeInX.addKeyFrame( 0, 0 );
    mCommandFadeInX.addKeyFrame( 30, 32 );
    mCommandFadeInX[ 0 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mCommandFadeInX[ 1 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mCommandFadeInX.setTime( 0.0 );
    mCommandFadeInX.setTimeTickPerSec( 1.0f );

    // コマンドのフェードイン不透明度
    mCommandFadeInOpacity.setCapacity( 3 );
    mCommandFadeInOpacity.addKeyFrame( 0,  0.0f );
    mCommandFadeInOpacity.addKeyFrame( 15, 0.5f );
    mCommandFadeInOpacity.addKeyFrame( 30, 1.0f );
    mCommandFadeInOpacity.setTime( 0.0 );
    mCommandFadeInOpacity.setTimeTickPerSec( 1.0f );





    LLayer::getBGLayer().setTone( LTone( 0, 0, 0 ), 2.0f );
	


	LTexture tex = LTexture::create( 640, 96 );
	tex.drawText(
		"",
		LRect( 0, 0, 512, 96 ) );
	mMessageSprite = LSprite::create( tex );
	mMessageSprite.setPosition( 100, 100 );
	mMessageSprite.setVisible(false);


    mPhase = 0;
    mFrameCount = 0;

	gSceneResult = this;
	__DtTestPoint( __DtFunc_onStart, __DtStep_13 )
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneResult::onUpdate()
{
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    switch ( mPhase )
    {
        /////////////////////// ウェイト
        case 0:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
            if ( mFrameCount >= 30 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_2)
                mPhase = 1;
                mFrameCount = 0;
            }
            break;
        }

        /////////////////////// フェードインフェーズ
        case 1:
        {
			// アンダーラインのフェードイン
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_3)
			if ( mFrameCount >= 20 && mFrameCount <= 60 )
            {
				int t = mFrameCount - 20;
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_4)
				for ( int i = 0; i < 3; ++i )
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_5)
					mCommandFadeInX.setTime( static_cast< double >( t - 5 * i ) );
					mScoreLineSprites[ i ].setPosition(
						LINE_MARGIN_X + mCommandFadeInX.getValue() - 32, LINE_MARGIN_Y + 48 * i );

					mCommandFadeInOpacity.setTime( static_cast< double >( t - 5 * i ) );
					mScoreLineSprites[ i ].setOpacity( mCommandFadeInOpacity.getValue() );
				}

				// 時間
				mCommandFadeInX.setTime( static_cast< double >( t - 5 ) );
				mCommandFadeInOpacity.setTime( t - 5 );
				for ( int i = 0; i < 6; ++i )
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_6)
					mTimeSprite[ i ].setPosition(
						LINE_MARGIN_X + 108 + 11 * i + (i / 2 * 8) + mCommandFadeInX.getValue() - 32 - 32, LINE_MARGIN_Y + 2 + 48 );
					mTimeSprite[ i ].setOpacity( mCommandFadeInOpacity.getValue() );
				}

				// ランク
				mCommandFadeInX.setTime( static_cast< double >( t - 10 ) );
				mCommandFadeInOpacity.setTime( t - 10 );
				mRankSprite.setPosition(
						LINE_MARGIN_X + 110 + mCommandFadeInX.getValue() - 32 - 32, LINE_MARGIN_Y - 2 + 96 );
				mRankSprite.setOpacity( mCommandFadeInOpacity.getValue() );
			}


			// Score 数値のフェードイン
			if ( mFrameCount >= 50 )// && mFrameCount <= 80 + 160 )
            {
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_7)
				mCommandFadeInOpacity.setTime( static_cast< double >( mFrameCount - 50 ) );
				for ( int i = 0; i < 10; ++i )
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_8)
					mScoreNumberSprites[ i ].setOpacity( mCommandFadeInOpacity.getValue() );
				}

				mScoreRapid.update();
			}

			// Time 数値のフェードイン
			if ( mFrameCount >= 60 )// && mFrameCount <= 90 + 160 )
            {
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_9)
				mCommandFadeInOpacity.setTime( static_cast< double >( mFrameCount - 60 ) );
				for ( int i = 0; i < 10; ++i )
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_10)
					mTimeNumberSprites[ i ].setOpacity( mCommandFadeInOpacity.getValue() );
				}

				mTimeRapid.update();
			}

			// Rank 数値のフェードイン
			if ( mFrameCount >= 70 )// && mFrameCount <= 100 + 160 )
            {
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_11)
				mCommandFadeInOpacity.setTime( static_cast< double >( mFrameCount - 70 ) );
				for ( int i = 0; i < 10; ++i )
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_12)
					mRankNumberSprites[ i ].setOpacity( mCommandFadeInOpacity.getValue() );
				}
				
				mRankRapid.update();
			}


			


			//----------------------------------------------------------
			// 数値更新
			int value[10];

			// Score
			Util::numberToArray2( mScoreRapid.getValue(), 10, value );
			for ( int i = 0; i < 10; ++i )
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_13)
				if ( value[i] == -1 )
					mScoreNumberSprites[ i ].setVisible(false);
				else
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_14)
					mScoreNumberSprites[ i ].setVisible(true);
					mScoreNumberSprites[ i ].setSrcRect( value[i] * 11, 0, 11, 16 );
				}
			}

			// Time
			Util::numberToArray2( mTimeRapid.getValue(), 10, value );
			for ( int i = 0; i < 10; ++i )
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_15)
				if ( value[i] == -1 )
					mTimeNumberSprites[ i ].setVisible(false);
				else
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_16)
					mTimeNumberSprites[ i ].setVisible(true);
					mTimeNumberSprites[ i ].setSrcRect( value[i] * 11, 0, 11, 16 );
				}
			}

			// Rank
			Util::numberToArray2( mRankRapid.getValue(), 10, value );
			for ( int i = 0; i < 10; ++i )
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_17)
				if ( value[i] == -1 )
					mRankNumberSprites[ i ].setVisible(false);
				else
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_18)
					mRankNumberSprites[ i ].setVisible(true);
					mRankNumberSprites[ i ].setSrcRect( value[i] * 11, 0, 11, 16 );
				}
			}

			


			if ( mScoreRapid.isFinished() && mTimeRapid.isFinished() && mRankRapid.isFinished() )//mFrameCount >= 260 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_19)
                mPhase = 2;
                mFrameCount = 0;
            }
            break;
        }

        /////////////////////// 仮
        case 2:
        {
			// Total Line
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_20)
			if ( mFrameCount >= 0 && mFrameCount <= 60 )
			{
				float t = mFrameCount - 0;
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_21)
				mCommandFadeInX.setTime( t / 2 );
				mCommandFadeInOpacity.setTime( t / 2  );
				mTotalLineSprite.setSrcRect( 0, 192, 608.0 * mCommandFadeInX.getValue() / 32, 32 );
				mTotalLineSprite.setOpacity( mCommandFadeInOpacity.getValue() );
			}

			// Total 数値のフェードイン
			if ( mFrameCount >= 60 )// && mFrameCount <= 250 + 160 )
            {
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_22)
				mCommandFadeInOpacity.setTime( static_cast< double >( mFrameCount - 60 ) );
				for ( int i = 0; i < 10; ++i )
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_23)
					mTotalNumberSprites[ i ].setOpacity( mCommandFadeInOpacity.getValue() );
				}
				
				mTotalRapid.update();
			}

			// Total 数値更新
			int value[10];
			Util::numberToArray2( mTotalRapid.getValue(), 10, value );
			for ( int i = 0; i < 10; ++i )
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_24)
				if ( value[i] == -1 )
					mTotalNumberSprites[ i ].setVisible(false);
				else
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_25)
					mTotalNumberSprites[ i ].setVisible(true);
					mTotalNumberSprites[ i ].setSrcRect( value[i] * 18, 16, 18, 24 );
				}
			}


			if ( mTotalRapid.isFinished() )
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_26)
				mPhase = 3;
                mFrameCount = 0;
				__DtTestPoint( __DtFunc_onUpdate, __DtStep_27 )
				return;
			}
            break;
        }

		/////////////////////// 決定ボタン待ちフェーズ
        case 3:
        {
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_28)
			if ( mIsNewRecord )
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_29)
				if ( mFrameCount == 0 )
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_30)
					mNewRecordOpacity.start(0.5, 1.0, 20);
				}

				mNewRecordSprite.setOpacity( mNewRecordOpacity.getValue() );
				mNewRecordOpacity.advanceTime( 1 );
			}


			if ( Input.isOnTrigger( LN_BUTTON_A ) )
            {
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_31)
				if (mIsNewRecord)
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_32)
					mPhase = 4;
				}
				else
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_33)
					mPhase = -1;
				}
                mFrameCount = 0;
                __DtTestPoint( __DtFunc_onUpdate, __DtStep_34 )
                return;
            }
            break;
		}

		/////////////////////// 名前入力開始フェーズ
        case 4:
        {
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_35)
			if (mFrameCount == 0)
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_36)
				mRankingNameplate.initialize(
					mRankingNo + 1, "",
					GameManager::getInstance()->getRank(),
					GameManager::getInstance()->getGameTime(),
					mTotalScore );
				mRankingNameplate.setOpacity(0);
				mRankingNameplate.setPosition( 320 - 128, 200 );
				mNameplateOpacity.start(0, 1, 30);
			}

			mNameplateOpacity.advanceTime(1);
			mRankingNameplate.setOpacity(mNameplateOpacity.getValue());
			mNewRecordBGSprite.setOpacity(mNameplateOpacity.getValue() * 0.75);
			
			if (mFrameCount >= 30)
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_37)
				mPhase = 5;
				mFrameCount = 0;
				__DtTestPoint( __DtFunc_onUpdate, __DtStep_38 )
				return;
			}
			break;
		}

		/////////////////////// 名前入力フェーズ
        case 5:
        {
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_39)
			mRankingNameplate.updateCaret();
			//{
			//	mPhase = 6;
			//	mFrameCount = 0;
			//	return;
			//}
			break;
		}

		/////////////////////// 名前入力終了フェーズ
        case 6:
        {
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_40)
			if (mFrameCount == 0)
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_41)
				mNameplateOpacity.start(1, 0, 30);
			}
			mNameplateOpacity.advanceTime(1);
			mRankingNameplate.setOpacity(mNameplateOpacity.getValue());
			mNewRecordBGSprite.setOpacity(mNameplateOpacity.getValue() * 0.75);

			if (mFrameCount <= 8)
			{
				float rate = LMath::min<float>(((float)mFrameCount) / 8.f, 1.f);
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_42)
				mRankingFrameSprite.setOpacity(1.0f - rate);
				mRankingFrameSprite.setScale(rate * 0.5f + 1.f);
			}
			

			if (mFrameCount >= 30)
			{
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_43)
				mPhase = -1;
				mFrameCount = 0;
				__DtTestPoint( __DtFunc_onUpdate, __DtStep_44 )
				return;
			}
			break;
		}

        /////////////////////// フェードアウトフェーズ
        case -1:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_45)
            if ( mFrameCount <= 120 )
            {
				float op = 0.008f * ( 120 - mFrameCount );

                __DtTestPoint(__DtFunc_onUpdate, __DtStep_46)
                mCharacterSprite.setOpacity( op );

				for ( int i = 0; i < 3; ++i ) mScoreLineSprites[i].setOpacity( op );
				mTotalLineSprite.setOpacity( op );
				for ( int i = 0; i < 6; ++i ) mTimeSprite[i].setOpacity( op );
				mRankSprite.setOpacity( op );
				for ( int i = 0; i < 10; ++i ) 
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_47)
					mScoreNumberSprites[i].setOpacity( op );
					mTimeNumberSprites[i].setOpacity( op );
	 				mRankNumberSprites[i].setOpacity( op );
					mTotalNumberSprites[i].setOpacity( op );
				}

				if (mIsNewRecord)
				{
					__DtTestPoint(__DtFunc_onUpdate, __DtStep_48)
					mNewRecordSprite.setOpacity( op );
				}
            }

			if ( mFrameCount == 120 )
            {
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_49)
				LLayer::getBGLayer().setTone( LTone( 1, 1, 1 ), 2.0f );
			}

            if ( mFrameCount >= 300 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_50)
                this->changeScene( NEW SceneCredit() );
                __DtTestPoint( __DtFunc_onUpdate, __DtStep_51 )
                return;
            }
            break;
        }
    }

    ++mFrameCount;
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_52 )
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneResult::onTerminate()
{
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
	gSceneResult = NULL;
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● 文字入力イベント処理
//---------------------------------------------------------------------
void SceneResult::onkeyEvent( char code_ )
{
	__DtTestPoint( __DtFunc_onkeyEvent, __DtStep_0 )
	if (mPhase == 5)
	{
		__DtTestPoint(__DtFunc_onkeyEvent, __DtStep_1)
		if (code_ == VK_RETURN)
		{
			__DtTestPoint(__DtFunc_onkeyEvent, __DtStep_2)
			if (strlen(mRankingName) > 0)
			{
				__DtTestPoint(__DtFunc_onkeyEvent, __DtStep_3)
				RankingManager::getInstance()->PostLocalStoryScore(
					mRankingName,
					mTotalScore, 
					0,
					GameManager::getInstance()->getGameTime(),
					GameManager::getInstance()->getRank() );

				mRankingNameplate.setVisibleCaret(false);
				mPhase = 6;
				mFrameCount = 0;
			}
		}
		else if (code_ == VK_BACK)
		{
			int last = strlen(mRankingName);
			__DtTestPoint(__DtFunc_onkeyEvent, __DtStep_4)
			if (last > 0)
			{
				__DtTestPoint(__DtFunc_onkeyEvent, __DtStep_5)
				mRankingName[last - 1] = '\0';
			}
		}
		else
		{
			int last = strlen(mRankingName);
			__DtTestPoint(__DtFunc_onkeyEvent, __DtStep_6)
			if (last < MAX_RANKING_NAME_LEN)
			{
				__DtTestPoint(__DtFunc_onkeyEvent, __DtStep_7)
				mRankingName[last] = code_;
				mRankingName[last + 1] = '\0';
			}
		}

		mRankingNameplate.setName(mRankingName);
	}
	__DtTestPoint( __DtFunc_onkeyEvent, __DtStep_8 )
}

//=============================================================================
//								end of file
//=============================================================================