//=============================================================================
/*! 
    @addtogroup 
    @file       Grenade.cpp
    @brief     �e�I�u�W�F�N�g
    
    Grenade�N���X�̎���
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/27
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/27 matsui
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Grenade.h"	/* For DynamicTracer-TestPoint */
#include "./Grenade.h"
#include "./Player.h"
#include "./../Effect/Effect_1.h"
#include "./attackedobject.h"
#include "../Map/MapManager.h"
#include"../Game/GameManager.h"
//---------------------------------------------------------------------------
/*! 
	@brief Grenade::Grenade

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Grenade::Grenade()
{
	__DtTestPoint( __DtFunc_Grenade, __DtStep_0 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::~Grenade

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Grenade::~Grenade()
{
	__DtTestPoint( __DtFunc_Grenade, __DtStep_1 )
	this->Release();
	__DtTestPoint( __DtFunc_Grenade, __DtStep_2 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Grenade::Initialize()
{
	//setAttackedGroup( ATKGROUP_ENEMY );
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();
	this->mScore = 0; 
	this->mPanel = LBatchPanel::create(20.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-10, 10, 0);
	this->mPanel.setTexture(LTexture::create(g_szGrenadeFilePath,0xffffffff));
	this->mPanel.setPosition(this->mPosition);
	this->mPanel.setVisible(true);
	this->mFrameCnt = 0;
	this->mGeneObjType = OBJ_CHARACTER;
	this->mRangeRate = 1;
	this-> mCriticalRate = 1;
	this->mBrowVec = 0;
	this->mStunFrame = 0;
	this->mDamage = 1;
	this->mFallSpeed = 0;
	this->mRandStun = 1;
	this->mRandBrowX = 1;
	this->mRandBrowY = 1;
	//this->mGeneObjType = OBJ_ENEMY;
	//this->setObjType(OBJ_Grenade);
	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Grenade::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Grenade::Update()
{

	//mVelocity 
	//mVelocity.x=100;
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	mVelocity.y-= mFallSpeed;
	if((this->getDirection()==CHARADIR_LEFT)&&(mFrameCnt == 0))
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		mVelocity.x*=-1;
		//mBrowVec*=-1;
	}
	mPosition+=mVelocity;
	this->mPanel.setPosition(this->mPosition );
	//printf("x%f,  y%f\n",mVelocity.x,mVelocity.y);
//	printf("x%f,  y%f\n",getPosition().x+8,getPosition().y+8);
    //float dx, dy;
    //u32 result = judgeCollisionToMap( &dx, &dy );
	LRect rect;
	rect.x=mPosition.x+8;
	rect.y=mPosition.y-8;
	rect.w=4;
	rect.h=4;

	LRect AttackLect;

	AttackLect.x = rect.x -80;
	AttackLect.y = rect.y +40;
	AttackLect.w = 160;
	AttackLect.h = 160;

	++mFrameCnt;



	//�ꉞ�͈͊O�ɂ����������
	if((this->getPosition().x>=2000)||(this->getPosition().y>=2000)||(this->getPosition().x<=0)||(this->getPosition().y<=0))
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_2)
		this->setExit(true);
	}
	bool result = MapManager::getInstance()->BulletCollision(rect);  
	if(result)
	{
		//printf("�O���l�[�h��damage%d\n",mDamage);
		LVector3 v(this->mPosition);
		__DtTestPoint(__DtFunc_Update, __DtStep_3)
		v.z = 0.f;
		new Effect_Explosion(v);
		Audio.playSE("./Data/Sound/SE/Explosion01.ogg",30,130);

		HitObjectList*  obj_list;
		if(this->mGeneObjType == OBJ_CHARACTER)
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_4)
			setAttackedGroup( ATKGROUP_PLAYER );
			obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(AttackLect,OBJ_ENEMY);
		}
		else
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_5)
			setAttackedGroup( ATKGROUP_ENEMY );
			obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(AttackLect,OBJ_CHARACTER);	
		}
		if ( obj_list->size() > 0 )
		{
			HitObjectList::iterator itr = obj_list->begin();
			HitObjectList::iterator end = obj_list->end();
			__DtTestPoint(__DtFunc_Update, __DtStep_6)
			for ( ; itr != end; ++itr )
			{
				__DtTestPoint(__DtFunc_Update, __DtStep_7)
				if(this->mGeneObjType == OBJ_CHARACTER)
				{
					//�Ȃ����v���C���[�ɂ�����̂�
				//	if((*itr)->getObjType() != OBJ_CHARACTER)
				//	{	
						__DtTestPoint(__DtFunc_Update, __DtStep_8)
						(*itr)->attackEffect(this,mDamage,mRangeRate,mCriticalRate,LVector3(mBrowVec.x+rand()%mRandBrowX,mBrowVec.y+rand()%mRandBrowY,0),mStunFrame+rand()%mRandStun);	
				//	}
				}
				else
				{
					__DtTestPoint(__DtFunc_Update, __DtStep_9)
					GameManager::getInstance()->getPlayer()->attackEffect(this,mDamage,mRangeRate,mCriticalRate,LVector3(mBrowVec.x+rand()%mRandBrowX,mBrowVec.y+rand()%mRandBrowY,0),mStunFrame+rand()%mRandStun);			
				}
				this->setExit(true);
				//GameObjectManager::getInstance()->deleteObject( this );	
			}
			__DtTestPoint( __DtFunc_Update, __DtStep_10 )
			return 1;
	    }
		this->setExit(true);
		//GameObjectManager::getInstance()->deleteObject( this );
	}
	__DtTestPoint( __DtFunc_Update, __DtStep_11 )
	return 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Grenade::HandleEvent(u32 event_,void *args_)
{
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	return true;
}

//
// Grenade::getBoundingRect
//
// �����蔻���Ԃ�
//
const LRect* Grenade::getBoundingRect()
{
	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
	mColRect.set( mPosition.x+8, mPosition.y-8, 4, 4 );

	__DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================
