//=============================================================================
/*! 
    @addtogroup 
    @file       SceneGame.cpp
    @brief      
    
    �Q�[���̃��C���ƂȂ�V�[���̎���
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/13 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_SceneGame.h"	/* For DynamicTracer-TestPoint */
#include "../Object/Character.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Object/MidBoss1.h"
#include "../Object/Weapon.h"
#include "./../Object/GameObjectManager.h"
#include "./../Event/EventManager.h"
#include "../Frontend/GameFrontendManager.h"
#include "../Game/GameManager.h"
#include "./../Camera/CameraManager.h"
#include "./../Object/MidBoss1.h"
#include "./../Object/Bullet.h"
#include "SceneGame.h"
#include "SceneGameover.h"
#include "SceneTitle.h"
#include "SceneResult.h"

#include "./../Effect/Effect_1.h"
#include "./../Effect/Effect_2.h"

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
SceneGame::SceneGame()
    : mMapManager           ( NULL )
	, mFrameCount           ( 0 )
	, mBeginScene           ( false )
    , mBossCollapseCount         ( 0 ) 
{
	__DtTestPoint( __DtFunc_SceneGame, __DtStep_0 )
}

//---------------------------------------------------------------------
// �� �J�n����
//---------------------------------------------------------------------
void SceneGame::onStart()
{
	// �w�i�F
    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    Graphics.setBGColor( 0.0f, 0.0f, 0.0f );



	//BGM
	Audio.playBGM(MAIN_BGM_NAME,60);



	// 
	//Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setType( LN_CAMERA_MOUSE_MOVE );

	// ��Փx�̐ݒ�
	//GameManager::getInstance()->setRank(2);

	
    // GameManager �Ɉړ�
	//GameFrontendManager::getInstance()->initialize( GameManager::getInstance()->getPlayer() );
	GameFrontendManager::getInstance()->getPlayerStateWindow()->setOpacity(0);

    // �ŏ��̃}�b�v�̐ݒ�
	
	GameManager::getInstance()->setFloorNum(0);
	MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());


	
	//�J�����̐ݒ�
	CameraManager::getInstance()->Initialize();
	//CameraManager::getInstance()->ChaseObject(GameManager::getInstance()->getPlayer());
    
    // ����
    /*
    Weapon::CreateData wdata2;
    wdata2.Data.WeaponType  = WEAPON_SHOTGUN;
    wdata2.Data.UseCount    = 1000;//gWeaponBaseData[WEAPON_SHOTGUN].UseCount;
    wdata2.Position         = LVector3( 150.0f, 200.0f, -1.0f );
    Weapon* test_weapon2 = Weapon::create( &wdata2 );
    */

	

    GameManager::getInstance()->commit();
	GameManager::getInstance()->resetGameTime();

	//debug
	mUBW = 0;

	//�������o�p
	GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
	GameManager::getInstance()->getPlayer()->setVisible(false);
    //GameManager::getInstance()->getPlayer()->setLevel( 7 );

    mBossCollapseCount = 0;
	__DtTestPoint( __DtFunc_onStart, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void SceneGame::onUpdate()
{
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
	++mFrameCount;

	//---------------------------------------------------------
    // ���o�p
	if(this->mBeginScene)
	{
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
		GameFrontendManager::getInstance()->update();
	}

    //---------------------------------------------------------
    // �{�X���j�G�t�F�N�g
    if ( mBossCollapseCount > 0 )
    {
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_2)
        GameManager::getInstance()->getEffectManager()->update();
        CameraManager::getInstance()->Update();
        GameFrontendManager::getInstance()->update();
        --mBossCollapseCount;
        if ( mBossCollapseCount == 0 )
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_3)
            this->changeScene( NEW SceneResult( GameManager::getInstance()->getPlayer()->getWeaponData().WeaponType ) );
        }
        __DtTestPoint( __DtFunc_onUpdate, __DtStep_4 )
        return;
    }

	GameObjectManager::getInstance()->Update();
    GameManager::getInstance()->update();
	CameraManager::getInstance()->Update();

    
    



   /* _p( Framework.getFrameCount() );
    _p( GameObjectManager::getInstance()->findObject( 124 ) );*/

    // �ȉ��̓V�[�����A�N�e�B�u�ȏꍇ�ɂ̂݌Ă�
    if ( !this->isActiveScene() )
    {
        __DtTestPoint( __DtFunc_onUpdate, __DtStep_5 )
        return;
    }

    // �v���C���[���S���Ȃ��Ă�ꍇ�͎q�V�[���Ƃ��ăQ�[���I�[�o�[���Ă�
    if ( GameManager::getInstance()->getPlayer()->isDead() )
    {
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_6)
        this->callScene( NEW SceneGameover() );
    }

    // �{�X�����ē|��Ă���ꍇ�͌��j�G�t�F�N�g��
    Character* boss = GameManager::getInstance()->getLastBossCharacter();
    if ( boss && boss->isDead() )
    {
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_7)
        mBossCollapseCount = 300;
        NEW Effect_ValfirleDead( boss->getPosition() + LVector3( 0, 15, 0 ) );
        LLayer::getBGLayer().setTone( LTone( 1, 1, 1 ), 5.0f ); // ��ʃt�F�[�h�A�E�g
        Audio.stopBGM( 5000 );                                  // 5�b������BGM���t�F�[�h�A�E�g
        __DtTestPoint( __DtFunc_onUpdate, __DtStep_8 )
        return;
    }

#if 0

	static int a;
	a++;


	//Debug
	//�G�l�~�[�����ׂč폜����J���p�R�}���h
	if(::GetKeyState(VK_F1) & 0x8000)
	{
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_9)
		printf("%d\n",GameObjectManager::getInstance()->removeObject(OBJ_ENEMY));
	}
	//Debug �񕜃A�C�e���𓪏�ɏo��������
	if(::GetKeyState(VK_F2) & 0x8000)
	{
		Cure_L *pCure = new Cure_L();
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_10)
		pCure->Initialize();

		LVector3 v =  GameManager::getInstance()->getPlayer()->getPosition();
		v.y += 100;

		pCure->setPosition(v);
	}
	//Debug ���擾
	if(::GetKeyState(VK_F3) & 0x8000)
	{
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_11)
		printf("���擾�iDebug�j\n");
		GameManager::getInstance()->setKeyflag(1);
	//	GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+1);


	}
	//Debug ��Փx�ύX
	if((::GetKeyState(VK_F4) & 0x8000)&&(a%50==0))
	{
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_12)
		if(	GameManager::getInstance()->getRank()!=3)
			GameManager::getInstance()->setRank(GameManager::getInstance()->getRank()+1);
		else
			GameManager::getInstance()->setRank(0);
		switch(GameManager::getInstance()->getRank())
		{
		case 0:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_13)
			printf("�C�[�W�[\n");
			break;
		case 1:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_14)
			printf("�m�[�}��\n");
			break;
		case 2:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_15)
			printf("�n�[�h\n");
			break;
		case 3:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_16)
			printf("���@���t�@�[��\n");
			break;
		}
	}
	//Debug ���̃X�e�[�W�ֈړ�����
	if((::GetKeyState(VK_F5) & 0x8000)&&(a%50==0))
	{
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_17)
		GameManager::getInstance()->setKeyflag(0);
		GameObjectManager::getInstance()->deleteStageObject();
		GameManager::getInstance()->NextFloor();
		MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());
		printf("�X�e�[�W%d\n",GameManager::getInstance()->getFloorNum()+1);
	}
	//Debug �O�̃X�e�[�W�ֈړ�����
	if((::GetKeyState(VK_F6) & 0x8000)&&(a%50==0))
	{
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_18)
		GameManager::getInstance()->setKeyflag(0);
		GameObjectManager::getInstance()->deleteStageObject();
		GameManager::getInstance()->setFloorNum(GameManager::getInstance()->getFloorNum()-2);
		GameManager::getInstance()->NextFloor();
		MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());
		printf("�X�e�[�W%d\n",GameManager::getInstance()->getFloorNum()+1);
	}
	//Debug ����̎g�p�񐔂𑝂₷
	if(::GetKeyState(VK_F7) & 0x8000)
	{
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_19)
		GameManager::getInstance()->getPlayer()->setLife(100);
		GameManager::getInstance()->getPlayer()->setOpacity(1);
	}
	//Debug ������o��������
    if ( Input.isOnTrigger( LN_BUTTON_R ) )
    {
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_20)
		mUBW = 10;
		Audio.playSE("./Data/Sound/SE/UBW.wav");
		//Audio.playBGM("d:\\Users\\GamePG\\Desktop\\bgm\\�yFate�^unlimited codes�zEMIYA�yBGM�z.mp3",60);
    }

	//Debug ������o��������
    if ( Input.isOnTrigger( LN_BUTTON_L ) )
    {
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_21)
		mUBW = 10;
		Audio.playSE("./Data/Sound/SE/I_am_the_bone.wav");
		//Audio.playBGM("d:\\Users\\GamePG\\Desktop\\The Pink Panther Theme Song.mp3",100,100);
    }

	/*
	Animation::FixedLengthScalar anim( 32 );
	anim.addKeyFrame( 0, 10 );
	anim.addKeyFrame( 20, 100 );
	anim.addKeyFrame( 30, 50 );

	anim[0].InterMode = LN_ANIM_INTER_CATMULLROM;
	anim[1].InterMode = LN_ANIM_INTER_CATMULLROM;
	anim[2].InterMode = LN_ANIM_INTER_CATMULLROM;



















	while()
	{
		anim.advanceTime(0.016f);
		int x = anim.getValue();
	}
	*/




	//Debug UBW
	if(this->mUBW && !(this->mFrameCount % 2))
	{
		Weapon::CreateData wdata;

		__DtTestPoint(__DtFunc_onUpdate, __DtStep_22)
		wdata.Data.WeaponType  = static_cast<WeaponType>(::rand() % (WEAPON_NORMAL_MAX_NUM ) + 1);
		//wdata.Data.WeaponType = WEAPON_STICK;
		wdata.Data.UseCount    = 1000;//gWeaponBaseData[wdata.Data.WeaponType].UseCount;

		LVector3 v = GameManager::getInstance()->getPlayer()->getPosition();
		v.x += ::rand() % 300 - 150;
		v.y += 210;
		wdata.Position = v;
		Weapon::create( &wdata );

		mUBW--;
	}

#endif

	//Debug ���o�p
	if(!this->mBeginScene)
	{
		__DtTestPoint(__DtFunc_onUpdate, __DtStep_23)
		if ( Input.isOnTrigger( LN_BUTTON_A ) )
		{
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_24)
			LLayer::getBGLayer().setTone( LTone( 0, 0, 0, 0 ), 0.0 );
			CameraManager::getInstance()->ChaseObject(GameManager::getInstance()->getPlayer());
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(MapManager::getInstance()->getStartPosition().x,MapManager::getInstance()->getStartPosition().y + 40,MapManager::getInstance()->getStartPosition().z));
			GameManager::getInstance()->getPlayer()->setDefPosition(MapManager::getInstance()->getStartPosition());
			GameManager::getInstance()->getPlayer()->setVelocity(LVector3(20,5,0));
			GameManager::getInstance()->getPlayer()->setVisible(true);

			this->mBeginScene = true;
			__DtTestPoint( __DtFunc_onUpdate, __DtStep_25 )
			return;
		}

		LVector3 v;

		switch(this->mFrameCount)
		{
		case 1:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_26)
			LLayer::getBGLayer().setTone( LTone( -1, -1, -1, 0 ), 0.0 );
			LLayer::getBGLayer().setTone( LTone( 0, 0, 0, 0 ), 1.5 );
			v = LVector3(600,200,-400);
			CameraManager::getInstance()->Move(v,LVector3(0,0,-3));

			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 180:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_27)
			LLayer::getBGLayer().setTone( LTone( -1, -1, -1, 0 ), 0.4 );
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 200:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_28)
			LLayer::getBGLayer().setTone( LTone( 0, 0, 0, 0 ), 0.4 );
			v = LVector3(1000,180,-1000);
			CameraManager::getInstance()->Move(v,LVector3(0,2.5,0));

			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 370:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_29)
			LLayer::getBGLayer().setTone( LTone( -1, -1, -1, 0 ), 0.4 );
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 390:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_30)
			LLayer::getBGLayer().setTone( LTone( 0, 0, 0, 0 ), 0.4 );
			v = LVector3(1200,650,-400);
			CameraManager::getInstance()->Move(v,LVector3(4,0,0));

			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 570:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_31)
			LLayer::getBGLayer().setTone( LTone( -1, -1, -1, 0 ), 0.4 );
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 600:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_32)
			LLayer::getBGLayer().setTone( LTone( 0, 0, 0, 0 ), 0.6 );
			v = LVector3(1000,300,-1300);
			CameraManager::getInstance()->Move(v,LVector3(0,0,-15));

			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 720:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_33)
			CameraManager::getInstance()->Move(Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->getPosition(),LVector3(-9.8888888889,-2.66666667,20.0));
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 810:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_34)
			CameraManager::getInstance()->Move(LVector3(MapManager::getInstance()->getStartPosition().x,MapManager::getInstance()->getStartPosition().y + 40,-1300),LVector3(0,0,0));
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 820:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_35)
			CameraManager::getInstance()->ChaseObject(GameManager::getInstance()->getPlayer());
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(MapManager::getInstance()->getStartPosition().x,MapManager::getInstance()->getStartPosition().y + 40,MapManager::getInstance()->getStartPosition().z));
			GameManager::getInstance()->getPlayer()->setDefPosition(MapManager::getInstance()->getStartPosition());
			GameManager::getInstance()->getPlayer()->setVelocity(LVector3(20,5,0));
			GameManager::getInstance()->getPlayer()->setVisible(true);

			this->mBeginScene = true;
			break;

		default:
			__DtTestPoint(__DtFunc_onUpdate, __DtStep_36)
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;
		}
	}


    
    //Debug D�L�[
    if ( Input.isOnTrigger( LN_BUTTON_Z ) )
    {
        //GameFrontendManager::getInstance()->showLevelUp();
        //GameFrontendManager::getInstance()->showFloorNum( 5 );
        //NEW Effect_ValfirleDead( GameManager::getInstance()->getPlayer()->getPosition() );
		//NEW Effect_Thunder( GameManager::getInstance()->getPlayer()->getPosition() );
    	__DtTestPoint(__DtFunc_onUpdate, __DtStep_37)
    }
    
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_38 )
}

//---------------------------------------------------------------------
// �� �I������
//---------------------------------------------------------------------
void SceneGame::onTerminate()
{
    __DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
    MapManager::getInstance()->releaseTilemap();

    GameManager::getInstance()->finalize();
	
    //GameFrontendManager::getInstance()->finalize();
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_1 )
}


//=============================================================================
//								End of File
//=============================================================================
