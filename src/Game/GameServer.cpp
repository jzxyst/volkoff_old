//=============================================================================
//�y GameServer �z
//=============================================================================

#include "stdafx.h"
#include	"DT_GameServer.h"	/* For DynamicTracer-TestPoint */
#include "../Event/EventType.h"
#include "../Object/GameObjectManager.h"
#include "../Object/Weapon.h"
#include "GameManager.h"
#include "GameSession.h"
#include "GameServer.h"

//=============================================================================
// �� GameServer �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
GameServer::GameServer()
    : mMyGameSession    ( NULL )
    , mListen           ( NULL )
{
    
	__DtTestPoint( __DtFunc_GameServer, __DtStep_0 )
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
GameServer::~GameServer()
{
    __DtTestPoint( __DtFunc_GameServer, __DtStep_1 )
    SAFE_DELETE( mListen );


    TcpStreamArray::iterator itr = mConnectedStreamArray.begin();
    TcpStreamArray::iterator end = mConnectedStreamArray.end();
    for ( ;itr != end; ++itr )
    {
        __DtTestPoint(__DtFunc_GameServer, __DtStep_2)
        SAFE_DELETE( (*itr) );
    }
	__DtTestPoint( __DtFunc_GameServer, __DtStep_3 )
}

//---------------------------------------------------------------------
// �� ������
//---------------------------------------------------------------------
void GameServer::initialize( GameSession* sesson_ )
{
    __DtTestPoint( __DtFunc_initialize, __DtStep_0 )
    mMyGameSession = sesson_;

    mListen = NEW TcpStream();
    mListen->Initialize();
    mListen->Bind( GAMEPORT );
    mListen->Listen( 5 );
	__DtTestPoint( __DtFunc_initialize, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �ڑ����Ď����� (1�t���[����1�x�Ăяo��)
//---------------------------------------------------------------------
void GameServer::polling()
{
    __DtTestPoint( __DtFunc_polling, __DtStep_0 )
    if ( mListen->getAcceptDemandNum() > 0 )
    {
        TcpStream* tcp_stream;
        __DtTestPoint(__DtFunc_polling, __DtStep_1)
        mListen->Accept( &tcp_stream );

        mConnectedStreamArray.push_back( tcp_stream );

        printf("�ڑ����Ă��܂���\n");

        tcp_stream->Send( "f�������ł���", strlen( "f�������ł���" ) + 1 );
    }
	__DtTestPoint( __DtFunc_polling, __DtStep_2 )
}

//---------------------------------------------------------------------
// �� �S�ẴN���C�A���g�ɃC�x���g�𑗐M����
//---------------------------------------------------------------------
void GameServer::sendEventToAllHost( u32 event_, void* data_, u32 size_ )
{
    // �������g�ɂ͂����ɑ��M
    __DtTestPoint( __DtFunc_sendEventToAllHost, __DtStep_0 )
    mMyGameSession->HandleEvent( event_, data_ );

    // �w�b�_�����
    GameSystemEventHeader header;
    header.Type         = event_;
    header.ArgSize      = size_;

    // ��x mTempBuffer �ɑS�Ċi�[
    memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
    if ( data_ )
    {
        __DtTestPoint(__DtFunc_sendEventToAllHost, __DtStep_1)
        memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );
    }

    // �ڑ��ς݂̂��̂ɑS�đ��M
    TcpStreamArray::iterator itr = mConnectedStreamArray.begin();
    TcpStreamArray::iterator end = mConnectedStreamArray.end();
    for ( ;itr != end; ++itr )
    {
        __DtTestPoint(__DtFunc_sendEventToAllHost, __DtStep_2)
        (*itr)->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
    }
	__DtTestPoint( __DtFunc_sendEventToAllHost, __DtStep_3 )
}

//---------------------------------------------------------------------
// �� �w�肵���z�X�g�ȊO�̑S�Ẵz�X�g�� GameSession �ɃC�x���g�𑗐M����
//---------------------------------------------------------------------
void GameServer::sendEventToExclusionHost( u32 exc_host_id_, u32 event_, void* data_, u32 size_ )
{
    __DtTestPoint( __DtFunc_sendEventToExclusionHost, __DtStep_0 )
    if ( exc_host_id_ != 0 )
    {
        // �������g�ɂ͂����ɑ��M
        __DtTestPoint(__DtFunc_sendEventToExclusionHost, __DtStep_1)
        mMyGameSession->HandleEvent( event_, data_ );
    }

    // �w�b�_�����
    GameSystemEventHeader header;
    header.Type         = event_;
    header.ArgSize      = size_;

    // ��x mTempBuffer �ɑS�Ċi�[
    memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
    if ( data_ )
    {
        __DtTestPoint(__DtFunc_sendEventToExclusionHost, __DtStep_2)
        memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );
    }

    // �w��ȊO�̐ڑ��ς݂̂��̂ɑS�đ��M
    u32 n = mConnectedStreamArray.size();
    u32 exc = exc_host_id_ - 1;
    for ( u32 i = 0; i < n; ++i )
    {
        __DtTestPoint(__DtFunc_sendEventToExclusionHost, __DtStep_3)
        if ( i != exc )
        {
            __DtTestPoint(__DtFunc_sendEventToExclusionHost, __DtStep_4)
            mConnectedStreamArray[ i ]->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
        }
    }
	__DtTestPoint( __DtFunc_sendEventToExclusionHost, __DtStep_5 )
}

//---------------------------------------------------------------------
// �� �C�x���g����
//---------------------------------------------------------------------
int GameServer::HandleEvent( u32 event_, void* args_ )
{
    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
    switch ( event_ )
    {
        ///////////////////////////////////////////// SceneGame �Ɉړ�����
        case SYSEV_GOTO_SCENEGAME:
        {
            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
            sendEventToAllHost( SYSEV_GOTO_SCENEGAME, NULL, 0 );
            break;
        }

        ///////////////////////////////////////////// �A�C�e��(����܂�)���E�������Ƃ��̗v�� (�e�z�X�g����T�[�o�ɑ����Ă���)
        case SYSEV_ITEM_REQUEST:
        {
            ItemRequestArgs* args = static_cast< ItemRequestArgs* >( args_ );
            GameObjectManager* manager = GameObjectManager::getInstance();

            // �A�C�e���I�u�W�F�N�g��T��
            GameObject* obj = manager->findObject( args->ItemObjHandle );

            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_2)
            if ( obj )
            {
                // ����̏ꍇ
                __DtTestPoint(__DtFunc_HandleEvent, __DtStep_3)
                if ( obj->getObjType() == OBJ_WEAPON )
                {
                    // �擾����L�����N�^�[�ɑ΂��ăI�u�W�F�N�g�̎�����f�[�^�𑗐M����
                    WeaponData data = ( static_cast< Weapon* >( obj ) )->getWeaponData();
                    __DtTestPoint(__DtFunc_HandleEvent, __DtStep_4)
                    manager->postEvent( args->GetterHandle, EV_GET_WEAPON, &data, sizeof( WeaponData ) );

                    u32 handle = obj->getHandle();

                    // ����I�u�W�F�N�g���폜����
                    sendEventToAllHost( SYSEV_DELETE_GAMEOBJECT, &handle, sizeof( u32 ) );
                }  
            }
        }
    }

    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_5 )
    return 0;
}



//=============================================================================
//								End of File
//=============================================================================