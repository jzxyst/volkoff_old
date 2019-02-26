//=============================================================================
//�y SceneConnection �z
//=============================================================================

#include "stdafx.h"
#include	"DT_SceneConnection.h"	/* For DynamicTracer-TestPoint */
#include "../Game/GameManager.h"
#include "SceneTitle.h"
#include "SceneNetRoom.h"
#include "SceneConnection.h"

//=============================================================================
// �� SceneConnection �N���X
//=============================================================================


//---------------------------------------------------------------------
// �� �J�n����
//---------------------------------------------------------------------
void SceneConnection::onStart()
{
    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    printf( "-------------------------------------------------\n" );
    printf( " �� �ڑ����\n" );
    printf( "-------------------------------------------------\n" );
    printf( "Z > ���������\n" );
    printf( "X > �����ɓ���\n" );
	__DtTestPoint( __DtFunc_onStart, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void SceneConnection::onUpdate()
{
    // ���������
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    if ( Input.isOnTrigger( LN_BUTTON_A ) )
    {
        // �e�Ƃ��ď��������A������ʂɈړ�
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
        GameManager::getInstance()->initializeParent();
        LGameScene::changeScene( "SceneNetRoom" );
        __DtTestPoint( __DtFunc_onUpdate, __DtStep_2 )
        return;
    }

    // �����ɓ���
    if ( Input.isOnTrigger( LN_BUTTON_B ) )
    {

        char addr[ 64 ];
        __DtTestPoint(__DtFunc_onUpdate, __DtStep_3)
        printf( "IP �A�h���X����\n>" );
        scanf( "%s", addr );

        printf( "�ڑ�...\n" );

        // �q�Ƃ��ď�����
        GameManager::getInstance()->initializeChild( addr );

        // �ڑ������������ꍇ�Ɉړ�����悤�ɂ��Ă���
        LGameScene::changeScene( NEW SceneNetRoom() );

        __DtTestPoint( __DtFunc_onUpdate, __DtStep_4 )
        return;
    }
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_5 )
}

//---------------------------------------------------------------------
// �� �I������
//---------------------------------------------------------------------
void SceneConnection::onTerminate()
{
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
}

//=============================================================================
//								end of file
//=============================================================================