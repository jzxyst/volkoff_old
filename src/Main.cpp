//=============================================================================
/*! 
    @addtogroup 
    @file       Main.cpp
    @brief      �v���O�������C������
    
    �v���O�������C������
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/05
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/05 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


/*! @par include */
//�C���N���[�h�t�@�C���́A�s�K�v�ɂȂ莟�撀����������
#include "stdafx.h"
#include	"DT_Main.h"	/* For DynamicTracer-TestPoint */
#include <crtdbg.h>
#include <time.h>
#include <Core/System/Win32/Win32WindowManager.h>
#include "Object/GameObject.h"
#include "Scene/SceneStartup.h"
#include "Scene/SceneTitle.h"
#include "Scene/SceneGame.h"
#include "Scene/SceneConnection.h"
#include "Scene/SceneNetRoom.h"
#include "Network/WinSock/SocketManager.h"

#include "Object/CharacterScriptInterface.h"
#include "Game/GameManager.h"
#include "Game/RankingManager.h"
#include "Scene/SceneResult.h"

//---------------------------------------------------------------------
// �ݒ�֐�
//---------------------------------------------------------------------
void lnConfig( LConfig config )
{
	//Base::Error::setProcessMode(LN_ERROR_PROC_IMMABORT);
	//
    //config.setEnableConsole( true );
    //config.Framework.setProcessMode( LN_SYSPROCMODE_ALWAYS );
    __DtTestPoint( __DtFunc_lnConfig, __DtStep_0 )
    config.setEnableFPUPreserve( true );

    config.setWindowTitle( _T( "Last Valfirle Ver1.0.1" ) );

	config.setDirectMusicInitMode( Core::Audio::DMINITMODE_THREAD_WAIT );
	__DtTestPoint( __DtFunc_lnConfig, __DtStep_1 )
}

// �E�B���h�E���b�Z�[�W�̃��X�i�[�N���X
class RelayWndProc
	: public LNote::Core::System::IWin32MessageListener
	//: public LNote::Core::System::IEventListener
{
	
	//virtual bool onEvent( const LNote::Core::System::Event& event_ )
	//{ 
	//	if ( event_.Type == LNEV_KEY_CHAR )
	//	{
	//		const Core::System::KeyEvent& key_args = (const Core::System::KeyEvent&)event_;
	//	}
	//	return false;
	//}
	

    virtual LRESULT WndProc( HWND hwnd_, UINT msg_, WPARAM wparam_, LPARAM lparam_, bool* handled_ )
    {
        /*
        

        if ( msg_ == WM_DESTROY )
        {
            printf( "WM_DESTROY\n" );
        }
        if ( msg_ == WM_CLOSE )
        {
            printf( "WM_CLOSE\n" );
        }
        if ( msg_ == WM_SOCKET )
        {
            printf( "WM_SOCKET\n" );
        }
        */

        if ( msg_ != WM_DESTROY )
        {
            SocketManager::getInstance()->Proc(hwnd_,msg_,wparam_,lparam_);
        }

		if ( msg_ == WM_CHAR )
		{
			// ����
			if ( 0x20 <= wparam_ && wparam_ <= 0x7E )
			{
				char code = wparam_;
				if ( ::GetKeyState( VK_SHIFT ) < 0 )
				{
					code = toupper( code );
				}
				if (gSceneResult)
				{
					gSceneResult->onkeyEvent( code );
				}
			}
			// Enter  BackSpace
			if (( wparam_ == VK_RETURN ) || ( wparam_ == VK_BACK ))
			{
				if (gSceneResult)
				{
					gSceneResult->onkeyEvent( wparam_ );
				}
			}
		}

        return 0;
    }
};

static RelayWndProc gRelayWndProc;


//---------------------------------------------------------------------
// �G���g���[�|�C���g
//---------------------------------------------------------------------
int lnMain()
{
//    LNote::Base::Error::setProcessMode( LN_ERROR_PROC_IMMABORT );

	__DtTestPoint( __DtFunc_lnMain, __DtStep_0 )
	Core::Scene::SceneGraph* scene = static_cast< Core::Scene::SceneGraph* >(
        Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph() );

    scene->getBatchSpriteProxy(true)->getSpriteRenderer()->setSortMode(
		LN_SPRITESORT_NONE, false );

	scene->getBatchSpriteProxy(true)->setCullingMode( LN_CULL_DOUBLE );

	//LRenderState state;
	//state.Culling = LN_CULL_DOUBLE;
	//scene->setNodeDefaultRenderState( state );

#if 0
    {
        Engine::Input::JoypadConfig joy_cfg;
        joy_cfg.setButton( LN_BUTTON_A, 4 );
        joy_cfg.setButton( LN_BUTTON_B, 3 );
        joy_cfg.setButton( LN_BUTTON_C, 1 );//5
        joy_cfg.setButton( LN_BUTTON_X, 2 );


        LKeyConfigData data = Input.getConfigData();
        data.setJoypadConfig( joy_cfg );
        Input.setConfigData( data );
    }
#endif

    LSound so = LSound::create( "Data/Sound/BGM/monochrome.ogg" );
    so.release();


    //---------------------------------------------------------
	// ����������
	//Debug
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	::SetConsoleTitle(TEXT("Volkoff Debug System[Ver.1.0.1]"));
	::printf("Volkoff Debug System[Ver.0.9.0]\n");
	::printf("Copyright (c) 2011 Valfirle Developer. All Rights Reserved.\n\n");
	//::SetWindowText(Engine::Framework::getInstance()->getSystemManager()->getMainWindow()->getWindowHandle(),TEXT("Last Valfirle Ver1.0.1"));

	::srand(static_cast<unsigned int>(::time(NULL)));

	LNote::Core::System::Win32WindowManager* window_manager =
		(LNote::Core::System::Win32WindowManager*)Framework.getInterface()->getSystemManager()->getWindowManager();

    // �l�b�g���[�N
	//SocketManager::getInstance()->Initialize( Framework.getInterface()->getSystemManager()->getMainWindow()->getWindowHandle() );
	window_manager->attachWin32MessageListener( &gRelayWndProc, 0 );

    // �w�i�F
    Graphics.setBGColor( 0.0f, 0.0f, 0.0f );
	Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setFarClip( 5000.f );

    // �J�������}�E�X�ő���\
	//Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setType( LN_CAMERA_MOUSE_MOVE );
	//Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setPosition(LVector3(0.0f,0.0f,-500.0f));
    
    CharacterScriptInterface::getInstance();

	RankingManager::getInstance()->Initialize();


    
    
    


    //LTexture t = LTexture::create("test");

    // �J�n���AGUI �͔�A�N�e�B�u
    //Framework->getInterface()->getGUIManager()->setActive( false );

    // �t���[�����[�g�����肷��܂ł�����Ƒ҂�
    for ( int i = 0; i < 60; ++i )
    {
        __DtTestPoint(__DtFunc_lnMain, __DtStep_1)
        Framework.update();
    }

    //---------------------------------------------------------
	// �Q�[�����[�v�J�n

#if 0   // �f�o�b�O�̂��߁A�����ɃQ�[���J�n����ꍇ�� 1

    GameManager::getInstance()->initializeParent();
    Framework.run( NEW SceneGame() );

#else

	Framework.run( NEW SceneStartup() );
	//Framework.run( NEW SceneResult( 1 ) );

#endif

	
    //---------------------------------------------------------
	// �I������

	RankingManager::getInstance()->Release();
	GameManager::getInstance()->finalize();

	window_manager->detachWin32MessageListener( &gRelayWndProc );

    __DtTestPoint( __DtFunc_lnMain, __DtStep_2 )
    return 0;
}

//---------------------------------------------------------------------
// �l�b�g���[�N�����ɂ���
/*

    �� �ڑ��̗���

        �\ ���� �\

        �E�^�C�g����ʂŁA�u�l�b�g���[�N�v���ڂ�I��
        �E�ڑ���ʂŁA�u���������v�u�������ɓ���v�����ꂩ��I��


        �\ �e �\

        �E�ڑ���ʊJ�n���AGameServer �N���X�����B(GameManager?)
        �E�q����̐ڑ����������ꍇ�́A�v���C���[�ԍ������߂�(�A��)�A�q�̏����L���[�ɓ����B
          �ԍ������߂���͂�����
          �L���[�̏��́A���C�����[�v�ŐV�����ڑ��𔻒肵�ĉ�ʂɕ\�����邽�߂Ɏg���B

        �E��t����ߐ؂��ăQ�[���ɐi�ނ���I��
        �@


        �\ �q �\

        �E�����̖��O�Ɛe�� IP �A�h���X����͂��āA�e�ɐڑ�


    �� 

*/


/*
// �Q�[�����A�����Ƒ��݂���V���O���g���B�e�z�X�g���ł̂ݑ��݂���
class GameServer
    : public ServerEventListener
{
public:
    
    // ���ׂẴN���C�A���g�ɁA�Q�[���V�[���Ɉړ����郁�b�Z�[�W�𑗐M���� (�����ƈꏏ�ɂł��邩��)
    void send_GotoGameScene()
    {
    }
    
    
    
private:
    
    std::vector< IClientOfServer* >     mClients;
};



    �� ��{�ړ�

        -------------------------------------------------------
        �� �Q�[���J�n (�I�u�W�F�N�g�����Ƃ�������Ƃ��Ԃ�)

            SceneGame::onStart()


            �O�D[�S] GameManager::initialize()
                        �ȉ��̈�A�̏������I���܂Ő����Ԃ��Ȃ��B
                        �����������ׂĂ��̒��ōs���B


            �P�D[P1] GameServer::changeMap()
                        //�}�b�v���\�z (�܂� GameObject �͍��Ȃ�)
                        mMapManager->makeRandomMap();
                        
                        //�N���C�A���g�� GameClient �Ƀ}�b�v�f�[�^�𑗐M����
                        PacketMapData data;
                        memcpy( data.MapData, mMapManager->getMapData(), sizeof());
                        foreach ( crient in mClients )
                        {
                            crient->send( data, sizeof( MapData ) );
                        }

                        // �}�b�v�f�[�^����K�v�ȃI�u�W�F�N�g���쐬����
                        mMapManager->createGameObject();

            �Q�D[P1] MapManager::createGameObject()
                        �}�b�v�����ׂđ������āAGameObject ���쐬����B
                        �Ȃ��A�����ō쐬����� GameObject �͂��ׂĐe�z�X�g(�T�[�o)�ō쐬���ꂽ���̂Ƃ��Ĉ����B
                        

                 GameServer �� GameClient �� GameManager �ɓ����ł��������B

            -- ���� --

            �R�D[P1] GameManager::createGameObjectEntity( u32 obj_key_, void* args_ )
                        ���炩���ߓo�^���Ă����� obj_key_ �ɑΉ����� create �֐����Ăяo���B
                        WoodBox::create( args_, true ) �݂����ɁAis_entity_ �� true �ō쐬�B
                        �����ł�����A�����ȊO�̂��ׂẴz�X�g�� EV_CREATE_GAME_OBJECT �𑗐M����B

                        EV_CREATE_GAME_OBJECT
                            obj_key_
                            args_
                            ���蓖�Ă�ꂽ�I�u�W�F�N�g�n���h��


            �S�D[P2] GameManager::HandleEvent()
                        EV_CREATE_GAME_OBJECT �̏����B
                        ����������o�����I�u�W�F�N�g�̎�ނɑΉ����� create �֐��ŁA
                        �I�u�W�F�N�g���쐬����B
                        WoodBox::create( args_, false ) �݂����ɁAis_entity_ �� false �ō쐬�B

            -- ���� �����܂� --


            �T�D[�S] GameManager::createPlayer(�����Ȃ�) �߂�l����
                        �e�z�X�g�ŁA���������삷�� Player ���쐬����B�쐬�ł��� Player �͊e�z�X�g 1 �܂ŁB
                        �쐬�� createGameObjectEntity() �ōs���A�߂�l�� mPlayer �ɕێ�����B
                        ���� Player �� GameManager::getPlayer() �Ŏ擾�\�B


                        �v���C���[�̐����O�Ɉ�x����������������������H
                        �������ȒP�Ɏ���V�X�e�����ق����B
                        ���j���[��ʂƂ����܂߂āB

                        �v���C���[�́A�X�e�[�W���Ƃɍ�蒼���Ƃ��͖����B
                        �Q�[�����͏�ɑ��݂���B

            �U�D[�S] GameManager::
                        ���ׂẴz�X�g�������������T�[�o�ɓ`����B
                        �T�[�o�́A�������ł�����Q�[���J�n��`����B


        -------------------------------------------------------
        �� GameObject �̍폜

            �� WoodBox (WoodBoxCommon �ł͂Ȃ�)

            �P�Dupdate() HandleEvent()
                    ���Ԍo�߂��_���[�W����ŃI�u�W�F�N�g���폜����ꍇ�A
                    GameObjectManager->deleteObject( this ); �ō폜����B
                    this ���A���� Object �ɂ���ĕێ�����Ă���ꍇ�͍l���Ȃ��B
                    ���̂悤�ȃI�u�W�F�N�g���K�v�ȏꍇ�Athis �������Ă��鑤��
                    �Q�Ƃ��O������� deleteObject() ���ĂԁB

            �Q�D[P1] GameObjectManager->deleteObject( GameObject* obj_ )
                    �Ƃ肠�����A�������܂ނ��ׂẴz�X�g�ɑ��M����B
                    EventManager->sendToAllHost( EV_DELETE_OBJECT, args_(obj_->Handle) );
                    �����֑��镪�͈�x�L���[�ɂ��߂���̂ŁA���ۂɍ폜�����̂�
                    ������Ƃ�����B


            �R�D[�S] GameObjectManager::HandleEvent()
                    EV_DELETE_OBJECT �̏����B
                    �P���Ƀ}�b�v���������āA�L�[�Ɉ�v����I�u�W�F�N�g�����ׂ� delete ����B
                    �M�~�b�N�ȂǂŁA�u�������폜���ꂽ�ꍇ�v�����o�������ꍇ�́A
                    P1 ����u�n���h�� x �̃I�u�W�F�N�g���폜����悤�Ƃ��Ă���v�C�x���g�����ׂĂɑ��M����B

                    





            ���폜�C�x���g�𔭍s����̂́A��� Entity ���B
              ���̃z�X�g�����邱�Ƃ́A�_���[�W����������Ƃ������B

        -------------------------------------------------------
        �� �v���C���[�̎��S

            �����ꂩ�� Player �� HP �� 0 �ɂȂ����ꍇ�A
            �e�z�X�g���� EV_DEAD �݂����ȃC�x���g��
            �����ȊO�̂��ׂẴz�X�g�ɑ��M����B
            
            ������ Player �������Ɏ��S�����ꍇ�A
            �ǂ� Player �������ŃQ�[���I�[�o�[�ɂȂ����̂��킩��Ȃ��Ȃ�B
            ���̂܂܂̎d�l�ł����Ȃ���Ȃ����ǁA
            �����ɔ��肷��Ȃ��x�T�[�o�Ɏ��S�C�x���g�𑗂��Ă���A
            ���߂đS�z�X�g�� EV_GAMEORVER �𑗂�B


        -------------------------------------------------------
        �� �Q�[���I�[�o�[

            �e�z�X�g�� EV_GAMEORVER ���󂯎�����ꍇ�A
            �ⓚ���p�ŃQ�[���I�[�o�[�̏���\������B

            �v���C���[����l�ȏ㓯���Ɏ��S�����ꍇ�A
            EV_GAMEORVER �͕����񗈂�\�������邽�߁A
            ���̕ӂ̑Ή����K�v�B
            (���ɃQ�[���I�[�o�[�ł���� EV_GAMEORVER �̓X���[���铙)

            �P�D[�S] GameManager::HandleEvent()
                        EV_GAMEORVER �̏����B
                        ���݂̃Q�[���V�[�� (SceneGame) �� startGameOver() ���Ăяo���B
                        Framework->getActiveScene()->startGameOver()�B

            or�P�D[�S] SceneGame::HandleEvent()
                        EV_GAMEORVER �̏����B
                        startGameOver() ���ĂԁB

            �Q�D[�S] SceneGame::startGameOver()
                        SceneGameover �Ɉړ��B
                        ���݂� SceneGame ���X�^�b�N���Ă��������Ƃ���B

            �R�D[�S] SceneGameover::update()
                        �e���R���e�j���[ or �Q�[���I����I������B
                        �q�͂Ƃ肠����������݂Ă邾���B

                        �R���e�j���[���I�����ꂽ�ꍇ�́A
                        �X�e�[�W�̊J�n�ʒu����ĊJ����B





            �� �R���e�j���[�̂��߂Ɋo���Ă������

                �T�[�o
                    �E�����_���}�b�v�̏�� (�܂��͗����V�[�h)

                �S�z�X�g
                    �E�X�e�[�W�J�n���̃X�e�[�^�X (�V���A���C�Y�H)

        -------------------------------------------------------
        �� �Q�[���N���A

            �{�X�ɍŌ�̈ꌂ����ꂽ�Ƃ���܂ł̓Q�[���Ƃ��ē������Ƃ��Ă����B
            �{�X���j�`���U���g��ʂŌ���{�^���������܂ł͊e�z�X�g�Ői�s�B
            �{�X���j���ɃT�[�o�����тƂ��̃f�[�^���쐬���Ċe�z�X�g�ɑ��M���A
            ���U���g��ʂŌ���{�^�����������܂ő҂B

            �I��������ڑ��҂���ʂցB����������āA�݂�ȎQ�����Ă��ԁB
            �Q�����󂯕t����B


            

        -------------------------------------------------------
        �� �G�̍U���̓����蔻��͊e�z�X�g�ōs������
            
        -------------------------------------------------------
        �� �_���[�W��^�������Ȃǂ̃X�R�A�̉��Z

            ���S�ȓ����͕s�\�B
            �G�� HP �� 1 �̏�Ԃ� P1 �� P2 �������ɍU��������A
            �ǂ����ɓ_�����邩�𐳂������肷��̂͂�����Ǝ�ԁB
            ����ɁA�u���ăQ�[�v���Ă��ƂȂ�A���̏ꍇ�͗�����
            �X�R�A�����Ă����邪�x�X�g���ƁB

            �|�������ɂ������链�_�͂�����ƕʂ��ȂƎv�����ǁB 

        -------------------------------------------------------
        �� �A�C�e���̎擾

            ��x�T�[�o�ɗv�����āA�ԓ�������܂�
            ���Ⴊ�ݏ�Ԃ𑱂���B
            �^�C���A�E�g���K�v�����B

            �P�D[2P] Player::updateSelf();
                        �A�C�e�����E���ׂ��t���[���ɂȂ����̂ŁA
                        �u�A�C�e�����擾�������v�Ƃ������b�Z�[�W�𑗂�
                        EV_GET_ITEM_REQUEST
                            �擾�v������ GameObject �̃n���h��
                            �A�C�e���̃I�u�W�F�N�g�n���h�� (�����Ƒ��M���ŃA�C�e�����ǂ����`�F�b�N���Ă���)

            �Q�D[1P] GameManager::HandleEvent(  )        //onReceive( void*  )
                        






    
        -------------------------------------------------------
        �� ���E�ړ��J�n
            
            �P�D[P1] �E�{�^��������
            �Q�D[P1] Controller �N���X����A�����̃z�X�g�Ɋ֘A�t�����Ă��� Player �Ɂu�E�������v�𑗐M����
                    �T�[�o�͉�Ȃ��B�z�X�g���� EventManager ���璼�� Player �ɑ��M����B
                    EventManager->sendToSelf( mPlayer, EV_INPUT );
                    
            �R�D[P1] EventManager::SendToSelf( GameObject* recver_obj_, u32 event_, void* args_ )
                        recver_obj_ �̎��n���h�����L�[�ɂ��āAEventManager ���Ǘ����Ă���
                        Listener �I�u�W�F�N�g�������B
                        �������� Listener �� event_ �������ɑ��M����B

            �S�D[P1] Player::HandleEvent()
                        EV_INPUT �̏����B
                        �����̃z�X�g���ŁA���݂̏�Ԃ����Ɉړ��J�n�ł��邩�ǂ����𔻒肷��B
                        (�G�̍U���ɓ������Ă̂����蒆�ł͂Ȃ���)
                        �ړ��J�n�ł���ꍇ�AEV_ACTION_MOVE �������܂ނ��ׂẴz�X�g�ɑ��M����B

            �T�D[P1] EventManager::sendToAllHost( GameObject* recver_obj_, u32 event_, void* args_ )
                        �����ւ̑��M�� SendToSelf() �ő����M�B
                        ���z�X�g�ւ̑��M�́A���M�p�̃L���[�ɋl�߂�B
                        ���� EventManager::process() �ŁA���z�X�g�ɑ��M����B

            �U�D[P1 P2] Player::HandleEvent()
                        EV_ACTION_MOVE �̏����B
                        �����Ŏ󂯎�����ړ����x(����͈ړ����x�Œ�ɂȂ邩��)�ɂ����
                        mVelocity �ɑ��x��ݒ肵�u�����ԁv�ɂȂ�B

            �V�D[P1 P2] Player::update()
                        if (�����Ԃ̏ꍇ)
                        {
                            �A�j���[�V����
                            ���W�X�V
                        }

            �� �K�v�Ȃ���

                �EEV_INPUT
                    �{�^���ԍ�
                    ���������

                �EEV_ACTION_START_RUN
                    ����

                �EEventManager::sendToSelf( GameObject* recver_obj_, u32 event_, void* args_, u32 size_ );
                �EEventManager::sendToAllHost( GameObject* recver_obj_, u32 event_, void* args_, u32 size_ );

                �EPlayer Enemy::isIdle()
                    ���� �W�����v ���Ⴊ�� �K�[�h �U�����̊e��{�A�N�V�������J�n�ł��邩�𔻒肷��

                �� isIdle() �œ���J�n�\���������̂� INPUT �n�C�x���g�̒��̂݁B
                   ACTION �n�C�x���g�̒��ōs���ƁA�e�z�X�g���Ŕ��肪�s���邽�߁A����̕s��������������B
                   �����ȊO�̃L�����̓������A�W�����v���ŋ󒆂ɂ���̂ɑ���A�j���[�V�����ɂȂ�Ƃ�
                   �s���R�Ȃ��Ƃ͂��邯�ǁA����͍��͖ڂ��ނ��Ă����B


        �� ���E�ړ��I��

            �菇�� �u���E�ړ��J�n�v�Ƃقړ����B
            INPUT �ŁA���݁u�����ԁv�ł����
            ���ׂẴz�X�g�� EV_ACTION_STOP_RUN �𑗂�B

            �󂯎�������ł͑��x�� 0 �ɂ���B���邢�́A�u�ҋ@��ԁv�ɂ���B
            


        �� �G����U�����󂯂�

            �����ׂĂ̓G�̓�����Ǘ�����̂̓T�[�o

                        
                    
                        
                        
        
    
        
        
        
        
        

    �E�U���𓖂Ă܂���
        �N���C�A���g    �� �T�[�o
        �T�[�o          �� �T�[�o


    -------------------------------------------------------
    �� �e GameObject �� ::create( void* args_, bool is_entity_ )

        ������

        class WoodBoxCommon : public GameObject
        {
            struct CreateArgs
            {
                LVector3    Pos;
            };

            // �R���X�g���N�^
            WoodBoxCommon( CreateArgs* args_ )
            {
                
            }

            
        };

        class WoodBox : public WoodBoxCommon
        {
            // args_ �́ACreateArgs �ւ̃|�C���^
            static void* create( void* args_, bool is_entity_ = true )
            {
                if ( is_entity_ )
                {
                    return NEW WoodBox( (CreateArgs*)args_ );
                }
                else
                {
                    return NEW WoodBoxCommon( (CreateArgs*)args_ );
                }
            }

            // �R���X�g���N�^
            WoodBox( CreateArgs* args_ )
                : WoodBoxCommon( args_ )
            {
                // �����Ɠ����ɑ��̃I�u�W�F�N�g���쐬����K�v������ꍇ�Ȃǂ͂����ɏ���
            }

            
        };


        �O�ꂷ�邱�Ƃ́AGameObject ���� create ���ĂԕK�v������Ƃ���
        �T�u�N���X���ł̂݌ĂԂ悤�ɂ��邱�ƁB


*/

//=============================================================================
//								End of File
//=============================================================================
