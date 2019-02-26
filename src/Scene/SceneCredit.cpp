//=============================================================================
//�y SceneCredit �z
//=============================================================================

#include "stdafx.h"
#include	"DT_SceneCredit.h"	/* For DynamicTracer-TestPoint */
#include "SceneTitle.h"
#include "SceneCredit.h"

//=============================================================================
// �� SceneCredit �N���X
//=============================================================================

// �v���O���}
const char* PROGRAM[] =
{
    "impmlv", "2", "3", "4", NULL
};         

// �O���t�B�b�N
const char* GRAPHICS[] =
{
    "impmlv", "2", "3", "", NULL
};

// ���y�f��
const char* SOUND_MAT[] =
{
    "1", "URL", "", "2", "URL", "", NULL
};

// �X�y�V�����T���N�X
const char* THANKS[] =
{
    "1", "2", "3", "", NULL
};

//---------------------------------------------------------------------
// �� �J�n����
//---------------------------------------------------------------------
void SceneCredit::onStart()
{
    __DtTestPoint( __DtFunc_onStart, __DtStep_0 )
    printf( "-------------------------------------------------\n" );
    printf( " �� �X�^�b�t���[��\n" );
    printf( "-------------------------------------------------\n" );

    
    mBGBlackSprite = LSprite::create( LTexture::create( "Data/Graphics/Frontend/Logo_1.png" ) );
    mBGBlackSprite.setSrcRect( 0, 0, 32, 32 );
    mBGBlackSprite.setScale( 20 );

    LLayer::getBGLayer().setTone( LTone( 0, 0, 0 ), 1.0f );


    mPhase = 0;
    mFrameCount = 0;
	__DtTestPoint( __DtFunc_onStart, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void SceneCredit::onUpdate()
{
    __DtTestPoint( __DtFunc_onUpdate, __DtStep_0 )
    switch ( mPhase )
    {
        /////////////////////// �t�F�[�h�C���t�F�[�Y
        case 0:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_1)
            if ( mFrameCount >= 60 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_2)
                mPhase = 1;
                mFrameCount = 0;
            }
            break;
        }

        /////////////////////// ��
        case 1:
        {
            // �I��
            //if ( Input.isOnTrigger( LN_BUTTON_A ) )
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_3)
            {
                LLayer::getBGLayer().setTone( LTone( 1, 1, 1 ), 3.0f );
                mPhase = -1;
                mFrameCount = 0;
                __DtTestPoint( __DtFunc_onUpdate, __DtStep_4 )
                return;
            }
            break;
        }

        /////////////////////// �t�F�[�h�A�E�g�t�F�[�Y
        case -1:
        {
            __DtTestPoint(__DtFunc_onUpdate, __DtStep_5)
            if ( mFrameCount >= 200 )
            {
                __DtTestPoint(__DtFunc_onUpdate, __DtStep_6)
                this->changeScene( NEW SceneTitle() );
                __DtTestPoint( __DtFunc_onUpdate, __DtStep_7 )
                return;
            }
            break;
        }
    }

    ++mFrameCount;
	__DtTestPoint( __DtFunc_onUpdate, __DtStep_8 )
}

//---------------------------------------------------------------------
// �� �I������
//---------------------------------------------------------------------
void SceneCredit::onTerminate()
{
	__DtTestPoint( __DtFunc_onTerminate, __DtStep_0 )
}

//=============================================================================
//								end of file
//=============================================================================