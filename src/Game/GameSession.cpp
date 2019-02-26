//=============================================================================
//�y GameSession �z
//=============================================================================

#include "stdafx.h"
#include	"DT_GameSession.h"	/* For DynamicTracer-TestPoint */
#include "../Object/GameObjectManager.h"
#include "GameServer.h"
#include "GameSession.h"

//=============================================================================
// �� GameSession �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
GameSession::GameSession()
    : mGameServer       ( NULL )
    , mServerStream     ( NULL )
    , mEventListener    ( NULL )
{
    __DtTestPoint( __DtFunc_GameSession, __DtStep_0 )
    memset( &mHostInfo, 0, sizeof( mHostInfo ) );
    memset( &mTempBuffer, 0, sizeof( mTempBuffer ) );
	__DtTestPoint( __DtFunc_GameSession, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
GameSession::~GameSession()
{
    __DtTestPoint( __DtFunc_GameSession, __DtStep_2 )
    SAFE_DELETE( mServerStream );
	__DtTestPoint( __DtFunc_GameSession, __DtStep_3 )
}

//---------------------------------------------------------------------
// �� ������
//---------------------------------------------------------------------
void GameSession::initialize( GameServer* server_ )
{
    __DtTestPoint( __DtFunc_initialize, __DtStep_0 )
    mGameServer = server_;
    mHostInfo.IsParent = ( server_ != NULL );
	__DtTestPoint( __DtFunc_initialize, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �q�Ƃ��ď����� (GameManager ����Ă΂��)
//---------------------------------------------------------------------
void GameSession::initializeChild( const char* parent_ip_addr_ )
{
    __DtTestPoint( __DtFunc_initializeChild, __DtStep_0 )
    mHostInfo.IsParent = false;

    mServerStream = NEW TcpStream();
    mServerStream->Initialize();
    mServerStream->Connect( "127.0.0.1", GAMEPORT );

    printf("�ڑ����܂���\n");
	__DtTestPoint( __DtFunc_initializeChild, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �T�[�o�Ƀf�[�^�𑗐M����
//---------------------------------------------------------------------
void GameSession::sendToServer( u32 event_, void* data_, u32 size_ )
{
    // �������e�̏ꍇ
    __DtTestPoint( __DtFunc_sendToServer, __DtStep_0 )
    if ( mHostInfo.IsParent )
    {
        // �����ɏ���
        __DtTestPoint(__DtFunc_sendToServer, __DtStep_1)
        mGameServer->HandleEvent( event_, data_ );
    }
    // �q�̏ꍇ
    else
    {
        // �w�b�_�����
        GameSystemEventHeader header;
        __DtTestPoint(__DtFunc_sendToServer, __DtStep_2)
        header.Type         = event_;
        header.ArgSize      = size_;

        // ��x mTempBuffer �ɑS�Ċi�[
        memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
        if ( data_ )
        {
            __DtTestPoint(__DtFunc_sendToServer, __DtStep_3)
            memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );
        }

        // �T�[�o�ɑ���
        mServerStream->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
    }
	__DtTestPoint( __DtFunc_sendToServer, __DtStep_4 )
}

//---------------------------------------------------------------------
// �� �I�u�W�F�N�g�쐬���b�Z�[�W (SYSEV_CREATEED_OBJECT) �𑗐M����
//---------------------------------------------------------------------
void GameSession::sendCreatedObjectEvent( u32 obj_type_, void* data_, u32 size_ )
{
    char temp[ 1024 ];

    u32 all_size = sizeof( CreatedObjectArgs ) + size_;

    CreatedObjectArgs* data = reinterpret_cast< CreatedObjectArgs* >( temp );

    //printf("�z�X�gID�󂯎�鏈�����ł��ĂȂ�\n");
    __DtTestPoint( __DtFunc_sendCreatedObjectEvent, __DtStep_0 )
    data->HostID = 0;
    data->ObjectType = obj_type_;

    memcpy( &data[ 1 ], data_, size_ );

    // �T�[�o�ɑ��M�B�T�[�o�� HandleEvent �ŁA�����ȊO�̃z�X�g�ɑ��M�����B
    // �u�����ȊO�v�Ƃ�������� HandleEvent ���ōs���B
    sendToServer( SYSEV_CREATEED_OBJECT, data, all_size );






    // �������T�[�o�̏ꍇ
    //if ( mHostInfo.IsParent )
    //{
    //    // ������ GameSession �ɑ��M

    //    //sendEventToExclusionHost

    //}
    //// �������N���C�A���g�̏ꍇ
    //else
    //{
    //    LN_ASSERT( 0, "sendCreatedObjectEvent ���Ή�" );
    //}
	__DtTestPoint( __DtFunc_sendCreatedObjectEvent, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �����ҋ@
//---------------------------------------------------------------------
void GameSession::waitSync()
{
	__DtTestPoint( __DtFunc_waitSync, __DtStep_0 )
}

//---------------------------------------------------------------------
// �� �C�x���g�Ď�
//---------------------------------------------------------------------
void GameSession::polling()
{

    // �q�̏ꍇ�̓T�[�o���瑗���Ă��Ă���C�x���g���`�F�b�N����
    __DtTestPoint( __DtFunc_polling, __DtStep_0 )
    if ( mServerStream )
    {
        //mServerStream->getSessionState()
        __DtTestPoint(__DtFunc_polling, __DtStep_1)
        if ( !mServerStream->getRecvList().empty() )
	    {
            //printf( "data:%s\n", mServerStream->getRecvList().front()->getData() );
            //printf( "size:%d\n", mServerStream->getRecvList().front()->getSize() );

            GameSystemEventHeader* header = reinterpret_cast< GameSystemEventHeader* >( mServerStream->getRecvList().front()->getData() );

            // �C�x���g����
            __DtTestPoint(__DtFunc_polling, __DtStep_2)
            HandleEvent( header->Type, &header[ 1 ] );

		    mServerStream->getRecvList().pop_front();
	    }
    }
	__DtTestPoint( __DtFunc_polling, __DtStep_3 )
}

//---------------------------------------------------------------------
// �� �C�x���g����
//---------------------------------------------------------------------
int GameSession::HandleEvent( u32 event_, void* args_ )
{
    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
    if ( mEventListener )
    {
        __DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
        mEventListener->HandleEvent( event_, args_ );
    }

    switch ( event_ )
    {
        

        ///////////////////////////////////////////// �I�u�W�F�N�g���폜����
        case SYSEV_DELETE_GAMEOBJECT:
        {
            GameObjectManager* manager = GameObjectManager::getInstance();
            GameObject* obj = manager->findObject( *static_cast< u32* >( args_ ) );

            

            __DtTestPoint(__DtFunc_HandleEvent, __DtStep_2)
            if ( obj )
            {
                //printf( "del handle %d\n", *static_cast< u32* >( args_ ) );

                __DtTestPoint(__DtFunc_HandleEvent, __DtStep_3)
                manager->deleteObject( obj );
            }
            break;
        }
    }

    __DtTestPoint( __DtFunc_HandleEvent, __DtStep_4 )
    return 0;
}

//=============================================================================
//								end of file
//=============================================================================