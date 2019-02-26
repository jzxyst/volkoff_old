//=============================================================================
//�y SceneRanking �z
//=============================================================================

#include "stdafx.h"
#include	"DT_SceneRanking.h"	/* For DynamicTracer-TestPoint */
#include "SceneTitle.h"
#include "SceneRanking.h"
#include "../Game/RankingManager.h"

//=============================================================================
// �� SceneRanking �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �J�n����
//---------------------------------------------------------------------
void SceneRanking::onStart()
{
    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    printf( "-------------------------------------------------\n" );
    printf( " �� �����L���O\n" );
    printf( "-------------------------------------------------\n" );

	mRankingTexture = LTexture::create( "Data/Graphics/Frontend/Ranking_1.png" );
    
    mBGWhiteSprite = LSprite::create( mRankingTexture );
    mBGWhiteSprite.setSrcRect( 320, 0, 32, 32 );
    mBGWhiteSprite.setScale( 20 );
	mBGWhiteSprite.setOpacity( 1.0 );


	//RankingManager::getInstance()->PostLocalStoryScore( "Tom", 31200971, 5, 71000 * 60 * 2, 0 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Jason", 51050986, 5, 13000 * 60 * 2, 1 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Freddy", 73027916, 5, 11000 * 60 * 2, 2 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Predator", 31050981, 5, 104500 * 60 * 2, 3 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Lee", 63020186, 5, 1000 * 60 * 2, 2 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Jack", 31438678, 5, 12000 * 60 * 2, 2 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Vito", 41000986, 5, 10500 * 60 * 2, 3 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Jimmy", 36021786, 5, 10600 * 60 * 2, 0 );
	//RankingManager::getInstance()->PostLocalStoryScore( "James", 61006569, 5, 341000 * 60 * 2, 1 );

	std::list<ScoreData> score_list = RankingManager::getInstance()->GetLocalStoryRanking( 10 );

	int i = 0;
	std::list<ScoreData>::iterator itr = score_list.begin();
	std::list<ScoreData>::iterator end = score_list.end();
	for (; itr != end && (i < MAX_RANKING_NUM); ++itr, ++i)
	{
		__DtTestPoint(__DtFunc_onStart, __DtStep_1)
		mRankingNameplate[i].initialize(i + 1, (*itr).szName, (*itr).nRank, (*itr).unTime, (*itr).unScore);
		mRankingNameplate[i].setPosition(44, 52 * i + 35);
	}
    
    mPhase = 0;
    mFrameCount = 0;
	Framework.getInterface()->resetDelayTime();
	__DtTestPoint( __DtFunc_onStart, __DtStep_2 )
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void SceneRanking::onUpdate()
{
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    switch ( mPhase )
    {
        /////////////////////// �t�F�[�h�C���t�F�[�Y
        case 0:
        {
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
			mBGWhiteSprite.setOpacity( ( mFrameCount / 30.0 ) * 0.8 );

			for (int i = 0; i < MAX_RANKING_NUM; ++i)
			{
				float op = ( (mFrameCount - i * 2) / 15.0 );
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_2)
				mRankingNameplate[i].setOpacity(LMath::limit<float>(op, 0, 1));
			}

            if ( mFrameCount >= 30 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_3)
                mPhase = 1;
                mFrameCount = 0;
            }
            break;
        }

        /////////////////////// ��
        case 1:
        {
            // �I��
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_4)
            if ( Input.isOnTrigger( LN_BUTTON_A ) || Input.isOnTrigger( LN_BUTTON_B ) )
            {
                
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_5)
                mPhase = -1;
                mFrameCount = 0;
                __DtTestPoint( __DtFunc_onUpdate, __DtStep_6 )
                return;
            }
            break;
        }

        /////////////////////// �t�F�[�h�A�E�g�t�F�[�Y
        case -1:
        {
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_7)
			mBGWhiteSprite.setOpacity( 0.8 - ( mFrameCount / 30.0 ) * 0.8 );
			for (int i = 0; i < MAX_RANKING_NUM; ++i)
			{
				float op = ( (mFrameCount - i * 2) / 15.0 );
				__DtTestPoint(__DtFunc_onUpdate, __DtStep_8)
				mRankingNameplate[i].setOpacity(1.0 - LMath::limit<float>(op, 0, 1));
			}

            if ( mFrameCount >= 30 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_9)
                this->returnScene();
                __DtTestPoint( __DtFunc_onUpdate, __DtStep_10 )
                return;
            }
            break;
        }
    }

    ++mFrameCount;
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_11 )
}

//---------------------------------------------------------------------
// �� �I������
//---------------------------------------------------------------------
void SceneRanking::onTerminate()
{
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
}

//=============================================================================
//								end of file
//=============================================================================