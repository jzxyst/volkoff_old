//=============================================================================
//�y EffectManager �z
//=============================================================================

#include "stdafx.h"
#include	"DT_EffectManager.h"	/* For DynamicTracer-TestPoint */
#include "../Game/GameManager.h"
#include "EffectBase.h"
#include "EffectManager.h"


//=============================================================================
// �� EffectManager �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
EffectManager::EffectManager()
{
	__DtTestPoint( __DtFunc_EffectManager, __DtStep_0 )
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
EffectManager::~EffectManager()
{
    EffectList::iterator itr = mEffectList.begin();
    EffectList::iterator end = mEffectList.end();
    __DtTestPoint( __DtFunc_EffectManager, __DtStep_1 )
    for ( ; itr != end; ++itr )
    {
        __DtTestPoint(__DtFunc_EffectManager, __DtStep_2)
        SAFE_DELETE( (*itr) );
    }
	__DtTestPoint( __DtFunc_EffectManager, __DtStep_3 )
}


//---------------------------------------------------------------------
// �� �t���[���X�V (�쐬����Ă���S�ẴG�t�F�N�g�� update() ���Ă�)
//---------------------------------------------------------------------
void EffectManager::update()
{
    EffectList::iterator itr = mEffectList.begin();
    EffectList::iterator end = mEffectList.end();
    __DtTestPoint( __DtFunc_update, __DtStep_0 )
    for ( ; itr != end; )
    {
        __DtTestPoint(__DtFunc_update, __DtStep_1)
        if ( (*itr)->update() == false )
        {
            __DtTestPoint(__DtFunc_update, __DtStep_2)
            delete (*itr);
            itr = mEffectList.erase( itr );
        }
        else
        {
            __DtTestPoint(__DtFunc_update, __DtStep_3)
            ++itr;
        }
    }
	__DtTestPoint( __DtFunc_update, __DtStep_4 )
}

//---------------------------------------------------------------------
// �� EffectBase �̃R���X�g���N�^����Ă΂��
//---------------------------------------------------------------------
void EffectManager::addEffect( EffectBase* effect_ )
{
    __DtTestPoint( __DtFunc_addEffect, __DtStep_0 )
    mEffectList.push_back( effect_ );
	__DtTestPoint( __DtFunc_addEffect, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� EffectBase �̃f�X�g���N�^����Ă΂��
//---------------------------------------------------------------------
//void EffectManager::removeEffect( EffectBase* effect_ )
//{
//    mEffectList.remove( effect_ );
//}


//=============================================================================
// �� EffectBase �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
EffectBase::EffectBase()
{
    __DtTestPoint( __DtFunc_EffectBase, __DtStep_0 )
    GameManager::getInstance()->getEffectManager()->addEffect( this );
	__DtTestPoint( __DtFunc_EffectBase, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
EffectBase::~EffectBase()
{
    //GameManager::getInstance()->getEffectManager()->removeEffect( this );
	__DtTestPoint( __DtFunc_EffectBase, __DtStep_2 )
}



//=============================================================================
//								end of file
//=============================================================================