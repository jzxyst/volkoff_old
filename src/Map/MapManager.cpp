//=============================================================================
// 【 MapManager 】
//=============================================================================

#include "stdafx.h"
#include	"DT_MapManager.h"	/* For DynamicTracer-TestPoint */
#include "MapManager.h"
#include "../Game/GameManager.h"
#include "../Frontend/GameFrontendManager.h"
#include"../Object/Player.h"
#include"../Object/Bullet.h"
extern int StageMap[8][100*100];



//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
MapManager::MapManager()
    : mTilemap  ( NULL )
    , mMapID    ( 0 )
    , mWidth    ( 100 )
    , mHeihgt   ( 100 )
{
    
	__DtTestPoint( __DtFunc_MapManager, __DtStep_0 )
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
MapManager::~MapManager()
{
    __DtTestPoint( __DtFunc_MapManager, __DtStep_1 )
    finalize();
	__DtTestPoint( __DtFunc_MapManager, __DtStep_2 )
}

/// インスタンスの取得
MapManager* MapManager::getInstance()
{
	static MapManager inst;
	__DtTestPoint( __DtFunc_getInstance, __DtStep_0 )
	return &inst;
}

//---------------------------------------------------------------------
//
//---------------------------------------------------------------------
void MapManager::finalize()
{
	__DtTestPoint( __DtFunc_finalize, __DtStep_0 )
	releaseTilemap();
	__DtTestPoint( __DtFunc_finalize, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● マップ (ステージ) の変更
//---------------------------------------------------------------------
void MapManager::changeMap( u32 map_id_ )
{
    // フロア数表示
    __DtTestPoint( __DtFunc_changeMap, __DtStep_0 )
    GameFrontendManager::getInstance()->showFloorNum( map_id_ + 1 );
    LLayer::getBGLayer().setTone( LTone( 0, 0, 0, 0 ), 0.1f );

    // 前回の mTilemap が残っている場合は解放する
    SAFE_RELEASE( mTilemap );

    mMapID = map_id_;
	//mMapID = 3;
	//memcpy( mMapData, StageMap[mMapID], sizeof(mMapData) );
	memcpy( mMapData, StageMap[mMapID], sizeof(mMapData) );
    
    // マップチップの画像を読み込む
    LTexture t = LTexture::create( "Data/Graphics/MapChip_1.png" );

    
    // タイルマップ作成
    //Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->createTilemap(
    //    &mTilemap, 100, 100, LN_TILEMAPDIR_XY );
    mTilemap = LN_NEW Core::Scene::Tilemap( Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph() );
    mTilemap->initialize( 100, 100, LN_TILEMAPDIR_XY );

    
    mTilemap->setMapData( mMapData );               // マップデータの設定
    mTilemap->setTilesetTexture( t->getInterface() );
    mTilemap->setPriority( -1000 );
    mTilemap->setBlendMode( LN_BLEND_NORMAL );
    //mTilemap->setVisible( false );
    mTilemap->setEnableDepthWrite( false );
   
    //LShader shader = LShader::create( "Data/Shader/Tilemap.fx" );
    //mTilemap->setShader( shader->getInterface() );




    //return;


    
    //mTilemap->setScale( 0.1f );
	mLadderCnt = 0;
	mLadderTopCnt = 0;
	mLockerCnt = 0;
	mWindowCnt = 0;
	mManholeCnt = 0;
	mDoorCnt = 0;
	mVaseCnt = 0;
	mMineCnt = 0;
	mBoxCnt = 0;
	mFortCnt = 0;
	mCure_Scnt=0;
	mCure_Mcnt=0;
	mCure_Lcnt=0;
	mDuctCnt = 0;
	mTopWallCnt = 0;
	mBottomWallCnt = 0;
	mUBWCnt = 0;
	for(int i= 0;i<=10000;i++ )
	{
		
		__DtTestPoint(__DtFunc_changeMap, __DtStep_1)
		switch(mMapData[i])
		{
		case MAP_LADDER:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_2)
			mLadder[mLadderCnt] = new Ladder();
			mLadder[mLadderCnt]->Initialize();
			mLadder[mLadderCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			++mLadderCnt;
			//printf("lada%d\n",mLadderCnt);
			break;
		case MAP_LADDERTOP:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_3)
			mLadderTop[mLadderTopCnt] = new LadderTop();
			mLadderTop[mLadderTopCnt]->Initialize();
			mLadderTop[mLadderTopCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			++mLadderCnt;
			//printf("lada%d\n",mLadderCnt);
			break;
		case MAP_ENTRY:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_4)
			mEntry = new Entry();
			mEntry->Initialize();
			mEntry->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
			break;
		case MAP_EXIT:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_5)
			mExit = new Exit();
			mExit->Initialize();
			mExit->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
			break;
		case MAP_ENTRYWALL:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_6)
			mBottomWall[mBottomWallCnt] = new BottomWall();
			mBottomWall[mBottomWallCnt]->Initialize();
			mBottomWall[mBottomWallCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20)+80,0.f));
			mBottomWall[mBottomWallCnt]->setEnemyNum(0);
			mBottomWall[mBottomWallCnt]->setActive(true);
			++mBottomWallCnt;
			break;
		case MAP_EXIT_LOCK:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_7)
			mExit_Lock = new Exit_Lock();
			mExit_Lock->Initialize();
			mExit_Lock->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
			break;
		case MAP_WINDOW_S:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_8)
			mWindow[mWindowCnt] = new Window();
			mWindow[mWindowCnt]->Initialize();
			mWindow[mWindowCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20)+40,0.f));
			mWindow[mWindowCnt]->setEnemyNum(2);
			mWindow[mWindowCnt]->setActive(true);
			++mWindowCnt;
			break;
		case MAP_WINDOW_L:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_9)
			mWindow[mWindowCnt] = new Window();
			mWindow[mWindowCnt]->Initialize();
			mWindow[mWindowCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20)+40,0.f));
			mWindow[mWindowCnt]->setEnemyNum(4);
			mWindow[mWindowCnt]->setActive(true);
			++mWindowCnt;
			break;
		case MAP_WINDOW_HARD:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_10)
			if(GameManager::getInstance()->getRank()>=RANK_HARD)
			{
				__DtTestPoint(__DtFunc_changeMap, __DtStep_11)
				mWindow[mWindowCnt] = new Window();
				mWindow[mWindowCnt]->Initialize();
				mWindow[mWindowCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20)+40,0.f));
				mWindow[mWindowCnt]->setEnemyNum(3);
				mWindow[mWindowCnt]->setActive(true);
				++mWindowCnt;			
			}
			break;
		case MAP_LOCKER_S:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_12)
			mLocker[mLockerCnt] = new Locker();
			mLocker[mLockerCnt]->Initialize();
			mLocker[mLockerCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			mLocker[mLockerCnt]->setEnemyNum(1);
			mLocker[mLockerCnt]->setActive(true);
			++mLockerCnt;
			break;
		case MAP_LOCKER_L:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_13)
			mLocker[mLockerCnt] = new Locker();
			mLocker[mLockerCnt]->Initialize();
			mLocker[mLockerCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			mLocker[mLockerCnt]->setEnemyNum(2);
			mLocker[mLockerCnt]->setActive(true);
			++mLockerCnt;
			break;
		case MAP_LOCKER_HARD:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_14)
			if(GameManager::getInstance()->getRank()>=RANK_HARD)
			{
				__DtTestPoint(__DtFunc_changeMap, __DtStep_15)
				mLocker[mLockerCnt] = new Locker();
				mLocker[mLockerCnt]->Initialize();
				mLocker[mLockerCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
				mLocker[mLockerCnt]->setEnemyNum(2);
				mLocker[mLockerCnt]->setActive(true);
				++mLockerCnt;
			}
			break;
		case MAP_MANHOLE_S:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_16)
			mManhole[mManholeCnt] = new Manhole();
			mManhole[mManholeCnt]->Initialize();
			mManhole[mManholeCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			mManhole[mManholeCnt]->setEnemyNum(2);
			mManhole[mManholeCnt]->setActive(true);
			++mManholeCnt;
			break;
		case MAP_MANHOLE_L:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_17)
			mManhole[mManholeCnt] = new Manhole();
			mManhole[mManholeCnt]->Initialize();
			mManhole[mManholeCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			mManhole[mManholeCnt]->setEnemyNum(4);
			mManhole[mManholeCnt]->setActive(true);
			++mManholeCnt;
			break;
		case MAP_MANHOLE_HARD:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_18)
			if(GameManager::getInstance()->getRank()>=RANK_HARD)
			{
				 __DtTestPoint(__DtFunc_changeMap, __DtStep_19)
				 mManhole[mManholeCnt] = new Manhole();
				 mManhole[mManholeCnt]->Initialize();
				 mManhole[mManholeCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
				 mManhole[mManholeCnt]->setEnemyNum(3);
				 mManhole[mManholeCnt]->setActive(true);
				 ++mManholeCnt;
			}
			break;
		case MAP_DOOR_S:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_20)
			mDoor[mDoorCnt] = new Door();
			mDoor[mDoorCnt]->Initialize();
			mDoor[mDoorCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
			mDoor[mDoorCnt]->setEnemyNum(2);
			mDoor[mDoorCnt]->setActive(true);
			++mDoorCnt;
			break;
		case MAP_DOOR_L:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_21)
			mDoor[mDoorCnt] = new Door();
			mDoor[mDoorCnt]->Initialize();
			mDoor[mDoorCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
			mDoor[mDoorCnt]->setEnemyNum(7);
			mDoor[mDoorCnt]->setActive(true);
			++mDoorCnt;
			break;
		case MAP_DOOR_HARD:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_22)
			if(GameManager::getInstance()->getRank()>=RANK_HARD)
			{
				__DtTestPoint(__DtFunc_changeMap, __DtStep_23)
				mDoor[mDoorCnt] = new Door();
				mDoor[mDoorCnt]->Initialize();
				mDoor[mDoorCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
				mDoor[mDoorCnt]->setEnemyNum(4);
				mDoor[mDoorCnt]->setActive(true);
				++mDoorCnt;
			}
			break;
		case MAP_WALL_S:

			__DtTestPoint(__DtFunc_changeMap, __DtStep_24)
			mTopWall[mTopWallCnt] = new TopWall();
			mTopWall[mTopWallCnt]->Initialize();
			mTopWall[mTopWallCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
			mTopWall[mTopWallCnt]->setEnemyNum(3);
			mTopWall[mTopWallCnt]->setActive(true);
			++mTopWallCnt;

			break;
		case MAP_WALL_L:

			__DtTestPoint(__DtFunc_changeMap, __DtStep_25)
			mTopWall[mTopWallCnt] = new TopWall();
			mTopWall[mTopWallCnt]->Initialize();
			mTopWall[mTopWallCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
			mTopWall[mTopWallCnt]->setEnemyNum(4);
			mTopWall[mTopWallCnt]->setActive(true);
			++mTopWallCnt;
			break;
		case MAP_WALL_HARD:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_26)
			if(GameManager::getInstance()->getRank()>=RANK_HARD)
			{
				__DtTestPoint(__DtFunc_changeMap, __DtStep_27)
				mTopWall[mTopWallCnt] = new TopWall();
				mTopWall[mTopWallCnt]->Initialize();
				mTopWall[mTopWallCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
				mTopWall[mTopWallCnt]->setEnemyNum(4);
				mTopWall[mTopWallCnt]->setActive(true);
				++mTopWallCnt;
			}
			break;
		case MAP_WALL2_S:

			__DtTestPoint(__DtFunc_changeMap, __DtStep_28)
			mBottomWall[mBottomWallCnt] = new BottomWall();
			mBottomWall[mBottomWallCnt]->Initialize();
			mBottomWall[mBottomWallCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20)+80,0.f));
			mBottomWall[mBottomWallCnt]->setEnemyNum(3);
			mBottomWall[mBottomWallCnt]->setActive(true);
			++mBottomWallCnt;
			break;
		case MAP_WALL2_L:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_29)
			mBottomWall[mBottomWallCnt] = new BottomWall();
			mBottomWall[mBottomWallCnt]->Initialize();
			mBottomWall[mBottomWallCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20)+80,0.f));
			mBottomWall[mBottomWallCnt]->setEnemyNum(4);
			mBottomWall[mBottomWallCnt]->setActive(true);
			++mBottomWallCnt;
			break;
		case MAP_WALL2_HARD:

			__DtTestPoint(__DtFunc_changeMap, __DtStep_30)
			if(GameManager::getInstance()->getRank()>=RANK_HARD)
			{
				__DtTestPoint(__DtFunc_changeMap, __DtStep_31)
				mBottomWall[mBottomWallCnt] = new BottomWall();
				mBottomWall[mBottomWallCnt]->Initialize();
				mBottomWall[mBottomWallCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20)+80,0.f));
				mBottomWall[mBottomWallCnt]->setEnemyNum(4);
				mBottomWall[mBottomWallCnt]->setActive(true);
				++mBottomWallCnt;
			}
			break;
		case MAP_DUCT_S:
				__DtTestPoint(__DtFunc_changeMap, __DtStep_32)
				mDuct[mDuctCnt] = new Duct();
				mDuct[mDuctCnt]->Initialize();
				mDuct[mDuctCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20)+40,0.f));
				mDuct[mDuctCnt]->setEnemyNum(4);
				mDuct[mDuctCnt]->setActive(true);
				++mDuctCnt;
			break;
		case MAP_DUCT_L:
				__DtTestPoint(__DtFunc_changeMap, __DtStep_33)
				mDuct[mDuctCnt] = new Duct();
				mDuct[mDuctCnt]->Initialize();
				mDuct[mDuctCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20)+40,0.f));
				mDuct[mDuctCnt]->setEnemyNum(8);
				mDuct[mDuctCnt]->setActive(true);
				++mDuctCnt;
			break;
		case MAP_FORT:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_34)
			mFort[mFortCnt] = new Fort();
			mFort[mFortCnt]->Initialize();
			mFort[mFortCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			++mFortCnt;
			break;
		case MAP_FORT_HARD:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_35)
			if(GameManager::getInstance()->getRank()>=RANK_HARD)
			{ 
				__DtTestPoint(__DtFunc_changeMap, __DtStep_36)
				mFort[mFortCnt] = new Fort();
				mFort[mFortCnt]->Initialize();
				mFort[mFortCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
				++mFortCnt;
			}
			break;
		case MAP_MINE:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_37)
			mMine[mMineCnt] = new Mine();
			mMine[mMineCnt]->Initialize();
			mMine[mMineCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			++mMineCnt;
			break;
		case MAP_MINE_HARD:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_38)
			if(GameManager::getInstance()->getRank()>=RANK_HARD)
			{
				__DtTestPoint(__DtFunc_changeMap, __DtStep_39)
				mMine[mMineCnt] = new Mine();
				mMine[mMineCnt]->Initialize();
				mMine[mMineCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
				++mMineCnt;
			}
			break;
		case MAP_WINDOW_DUMMY:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_40)
			mWindow[mWindowCnt] = new Window();
			mWindow[mWindowCnt]->Initialize();
			mWindow[mWindowCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20)+40,0.f));
			++mWindowCnt;
			break;
		case MAP_LOCKER_DUMMY:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_41)
			mLocker[mLockerCnt] = new Locker();
			mLocker[mLockerCnt]->Initialize();
			mLocker[mLockerCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			++mLockerCnt;
			break;
		case MAP_MANHOLE_DUMMY:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_42)
			mManhole[mManholeCnt] = new Manhole();
			mManhole[mManholeCnt]->Initialize();
			mManhole[mManholeCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			++mManholeCnt;
			break;
		case MAP_DOOR_DUMMY:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_43)
			mDoor[mDoorCnt] = new Door();
			mDoor[mDoorCnt]->Initialize();
			mDoor[mDoorCnt]->setPosition(LVector3((i%100)*20.0f-40,2000.0f-((i/100)*20),0.f));
			++mDoorCnt;
			break;
		case MAP_DUCT_DUMMY:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_44)
			mDuct[mDuctCnt] = new Duct();
			mDuct[mDuctCnt]->Initialize();
			mDuct[mDuctCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20)+40,0.f));
			++mDuctCnt;
			break;
		case MAP_BOX:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_45)
			mBox[mBoxCnt] = new Box();
			mBox[mBoxCnt]->Initialize();
			mBox[mBoxCnt]->setPosition(LVector3((i%100)*20.0f-20,2000.0f-((i/100)*20)+20,0.f));
			++mBoxCnt;
			break;
		case MAP_DRUM:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_46)
			break;
		case MAP_VASE:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_47)
			mVase[mVaseCnt] = new Vase();
			mVase[mVaseCnt]->Initialize();
			mVase[mVaseCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			++mVaseCnt;
			break;
		case MAP_UBW:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_48)
			mUBW[mUBWCnt] = new UBW();
			mUBW[mUBWCnt]->Initialize();
			mUBW[mUBWCnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			++mUBWCnt;
			break;
		case MAP_KEY:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_49)
			mKey = new Key();
			mKey->Initialize();
			mKey->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			break;
		case MAP_CURE_S:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_50)
			mCure_S[mCure_Scnt] = new Cure_S();
			mCure_S[mCure_Scnt]->Initialize();
			mCure_S[mCure_Scnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			break;
		case MAP_CURE_M:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_51)
			mCure_M[mCure_Mcnt] = new Cure_M();
			mCure_M[mCure_Mcnt]->Initialize();
			mCure_M[mCure_Mcnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			break;
		case MAP_CURE_L:
			__DtTestPoint(__DtFunc_changeMap, __DtStep_52)
			mCure_L[mCure_Lcnt] = new Cure_L();
			mCure_L[mCure_Lcnt]->Initialize();
			mCure_L[mCure_Lcnt]->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f));
			break;
		case MAP_GRENADE:
		{
			    Weapon::CreateData wdata2;
			    __DtTestPoint(__DtFunc_changeMap, __DtStep_53)
			    wdata2.Data.WeaponType  = WEAPON_GRENADE;
			    wdata2.Data.UseCount    = gWeaponBaseData[WEAPON_GRENADE].UseCount;
                wdata2.Position         = LVector3((i%100)*20.0f,2000.0f-((i/100)*20),0.f);
			    Weapon* test_weapon2 = Weapon::create( &wdata2 );
			break;
		}
		case MAP_ENEMY:
        {
			Enemy* mEnemy = Enemy::createRandom();
			__DtTestPoint(__DtFunc_changeMap, __DtStep_54)
			mEnemy->setPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f));
			mEnemy->setDefPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f));
			break;
        }
		case MAP_MIDBOSS_KATANA:
			{
			MidBoss1::CreateData data;
			__DtTestPoint(__DtFunc_changeMap, __DtStep_55)
			data.Position = LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f);
			data.WeaponLevel = 1;
			data.WeaponType = WEAPON_BOSS_KATANA;
			MidBoss1 *pBoss = MidBoss1::create(&data);
			pBoss->setDefPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f));
			break;
			}
		case MAP_MIDBOSS_TAEKWONDO:
			{
			MidBoss2::CreateData data;
			__DtTestPoint(__DtFunc_changeMap, __DtStep_56)
			data.Position = LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f);
			data.WeaponLevel = 1;
			data.WeaponType = WEAPON_BOSS_TAEKWONDO;
			MidBoss2 *pBoss = MidBoss2::create(&data);
			pBoss->setDefPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f));
			break;
			}
		case MAP_MIDBOSS_KNIFE:
			{
			MidBoss1::CreateData data;
			__DtTestPoint(__DtFunc_changeMap, __DtStep_57)
			data.Position = LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f);
			data.WeaponLevel = 1;
			data.WeaponType = WEAPON_BOSS_KNIFE;
			MidBoss1 *pBoss = MidBoss1::create(&data);
			pBoss->setDefPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f));
			break;
			}
		case MAP_MIDBOSS_SCYTHE:
			{
			MidBoss2::CreateData data;
			__DtTestPoint(__DtFunc_changeMap, __DtStep_58)
			data.Position = LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f);
			data.WeaponLevel = 1;
			data.WeaponType = WEAPON_BOSS_SCYTHE;
			MidBoss2 *pBoss = MidBoss2::create(&data);
			pBoss->setDefPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f));
			break;
			}
		case MAP_VALFIRLE :
			{
				Valfirle::CreateData data;
				__DtTestPoint(__DtFunc_changeMap, __DtStep_59)
				data.Position = LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f);
				data.WeaponLevel = 1;
				data.WeaponType = WEAPON_VALFIRLE;
				Valfirle *pBoss = Valfirle::create(&data);
				pBoss->setDefPosition(LVector3((i%100)*20.0f,2000.0f-((i/100)*20),1.f));	
				//Audio.playBGM("./Data/Sound/BGM/Theme_of_Valfirle.ogg",60);			
			}
			break;
		};

	}
	
	if ( this->mMapID == 7 )
	{
		__DtTestPoint(__DtFunc_changeMap, __DtStep_60)
		Audio.playBGM("./Data/Sound/BGM/Theme_of_Valfirle.ogg",60);			
	}
	else
	{
		
		__DtTestPoint(__DtFunc_changeMap, __DtStep_61)
	}


	 ///謎のはしごバグ防止
		Bullet *bul;
		bul = new Bullet();
		bul->Initialize();
		bul->setGeneObjType(OBJ_CHARACTER);
		bul->setPosition(LVector3(1,1,0));
		bul->setVelocity(LVector3(0,0,0));

		GameManager::getInstance()->getPlayer()->setPosition(getStartPosition());
		GameManager::getInstance()->getPlayer()->setDefPosition(getStartPosition());
	__DtTestPoint( __DtFunc_changeMap, __DtStep_62 )
}
//---------------------------------------------------------------------
// ● ステージのあたり判定
//---------------------------------------------------------------------
u32 MapManager::collision( LRect rect_, LVector3 velocity_, LVector3* out_pos_ )
{
	u32 result = 0;

	// マップの左上を 0,0 とした座標に変換(通常は右下が0,0)
	int px = rect_.x;
	int py = 2000-rect_.y;

	// とりあえず最初に結果を入れておく
	__DtTestPoint( __DtFunc_collision, __DtStep_0 )
	out_pos_->x = px;
	out_pos_->y = py;

//	printf("px%d  py%d\n",px,py);
//	printf("rect_X%d  rect_Y%d\n",rect_.x,rect_.y);

	//if(velocity_.x!=0)
	//{
	//	printf("velocitxY%f\n",velocity_.x);

	//}
	//if(rect_.width<=23)
	//{
	//	rect_.width=24;
	//}

	//	printf("wi%d\n",rect_.width);
	// 上下左右
	int l = px;
	int r = px + rect_.w;
	int t = py;
	int b = py + rect_.h;



	int mlx = ( l / 20 );
	int mrx = ( r / 20 );
	int mty = ( t / 20 );
	int mby = ( b / 20 );
//printf("mlx%d  mrx%d  mty%d mby%d\n",mlx,mrx,mty,mby);
	//上のブロックとのあたり判定
	if (( mMapData[ (mlx+1) + mty * 100 ] == MAP_BLOCK )||( mMapData[ (mlx+1) + mty * 100 ] == MAP_BLOCK_STEALTH ))
	{
		// 当たっていた場合、位置を下に戻していく
		__DtTestPoint(__DtFunc_collision, __DtStep_1)
		out_pos_->y = ( py  ) / 20;
		out_pos_->y *= 20;
		out_pos_->y+=20;		
		result |= MAPCOLL_UP;
	}
	py=out_pos_->y;
	t = py;
	b = py + rect_.h;
	mty = ( t / 20 );
	mby = ( b / 20 );

    //右のブロックとのあたり判定
	if (( mMapData[ mrx + mty * 100 ] == MAP_BLOCK )||( mMapData[ mrx + (mby-1) * 100 ] == MAP_BLOCK )||( mMapData[ mrx + (mty+1) * 100 ] == MAP_BLOCK )||( mMapData[ mrx + mty * 100 ] == MAP_BLOCK_STEALTH )||( mMapData[ mrx + (mby-1) * 100 ] == MAP_BLOCK_STEALTH )||( mMapData[ mrx + (mty+1) * 100 ] == MAP_BLOCK_STEALTH ))
	{
		// 当たっていた場合、位置を左に戻していく
		__DtTestPoint(__DtFunc_collision, __DtStep_2)
		out_pos_->x = ( px + rect_.w) / 20;
		out_pos_->x *= 20;
		out_pos_->x -= rect_.w+1;
		result |= MAPCOLL_RIGHT;
	}	
	//左のブロックとのあたり判定
	if (( mMapData[ mlx + mty * 100 ] == MAP_BLOCK )||( mMapData[ mlx + (mby-1) * 100 ] == MAP_BLOCK )||( mMapData[ mlx + (mty+1) * 100 ] == MAP_BLOCK )||( mMapData[ mlx + mty * 100 ] == MAP_BLOCK_STEALTH )||( mMapData[ mlx + (mby-1) * 100 ] == MAP_BLOCK_STEALTH )||( mMapData[ mlx + (mty+1) * 100 ] == MAP_BLOCK_STEALTH ))
	{
		//// 当たっていた場合、位置を右に戻していく
		__DtTestPoint(__DtFunc_collision, __DtStep_3)
		out_pos_->x = ( px ) / 20;
		out_pos_->x *= 20;
		out_pos_->x+=21;
		
		result |= MAPCOLL_LEFT;
	}	

	px=out_pos_->x;

	 l = px;
	 r = px + rect_.w;

	 mlx = ( l / 20 );
	 mrx = ( r / 20 );

	//下のブロックとのあたり判定
	if (( mMapData[ mlx + mby * 100 ] == MAP_BLOCK )||( mMapData[ mrx + mby * 100 ] == MAP_BLOCK )||( mMapData[ (mlx+1) + mby * 100 ] == MAP_BLOCK )||( mMapData[ mlx + mby * 100 ] == MAP_BLOCK_STEALTH )||( mMapData[ mrx + mby * 100 ] == MAP_BLOCK_STEALTH )||( mMapData[ (mlx+1) + mby * 100 ] == MAP_BLOCK_STEALTH ))
	{
		// 当たっていた場合、位置を上に戻していく
		__DtTestPoint(__DtFunc_collision, __DtStep_4)
		out_pos_->y = ( py + rect_.h ) / 20;
		out_pos_->y *= 20;
		out_pos_->y -= rect_.h;
		static int a;
		a++;
		result |= MAPCOLL_DOWN;
	}
	//上のブロックとのあたり判定
	//if ((( mMapData[ mlx + mty * 100 ] == MAP_BLOCK )||( mMapData[ mrx + mty * 100 ] == MAP_BLOCK )||( mMapData[ (mlx+1) + mty * 100 ] == MAP_BLOCK ))&&(velocity_.y>0))
	//{
	//	// 当たっていた場合、位置を下に戻していく
	//	out_pos_->y = ( py  ) / 20;
	//	out_pos_->y *= 20;
	//	out_pos_->y+=20;		

	//	result |= MAPCOLL_UP;
	//}
	out_pos_->y = 2000 - out_pos_->y;

	__DtTestPoint( __DtFunc_collision, __DtStep_5 )
	return result;


}
LVector3 MapManager::getStartPosition()
{
	LVector3 StartPos;
	__DtTestPoint( __DtFunc_getStartPosition, __DtStep_0 )
	for(int i=0;i<=10000;i++)
	{
		__DtTestPoint(__DtFunc_getStartPosition, __DtStep_1)
		if(( mMapData[i]==MAP_ENTRY)||(mMapData[i]==MAP_ENTRYWALL))
		{
			__DtTestPoint(__DtFunc_getStartPosition, __DtStep_2)
			StartPos.set((i%100)*20.0f+30,2000.0f-((i/100)*20)-80,-1.f);
		}
	}
	__DtTestPoint( __DtFunc_getStartPosition, __DtStep_3 )
	return StartPos;
}

// タイルマップ解放 (タイトルへ戻るときなど)
void MapManager::releaseTilemap()
{
    __DtTestPoint( __DtFunc_releaseTilemap, __DtStep_0 )
    LN_SAFE_RELEASE( mTilemap );
	__DtTestPoint( __DtFunc_releaseTilemap, __DtStep_1 )
}

bool MapManager::BulletCollision( LRect rect_)
{
//	int blockx,blocky;
	LRect block;
	__DtTestPoint( __DtFunc_BulletCollision, __DtStep_0 )
	rect_.y=2000-rect_.y;
	block.x=rect_.x-rect_.x%20;
	block.y=rect_.y-rect_.y%20;
	//block.y+20;
	block.h = 20;
	block.w = 20;


	if((mMapData[((block.y/20)*100)+(block.x/20)]==MAP_BLOCK)||(mMapData[((block.y/20)*100)+(block.x/20)]==MAP_BLOCK_STEALTH))
	{
	//	printf("aa\n");
		//if((block.contains(LPoint(rect_.x,rect_.y)))||(block.contains(LPoint(rect_.x+rect_.width,rect_.y)))||(block.contains(LPoint(rect_.x,rect_.y+rect_.height)))||(block.contains(LPoint(rect_.x+rect_.width,rect_.y+rect_.height))))
		__DtTestPoint(__DtFunc_BulletCollision, __DtStep_1)
		if(block.contains(LPoint(rect_.x,rect_.y)))
		{
			__DtTestPoint( __DtFunc_BulletCollision, __DtStep_2 )
			return true;
		}
	}

	__DtTestPoint( __DtFunc_BulletCollision, __DtStep_3 )
	return false;
}
//=============================================================================
//								End of File
//=============================================================================
