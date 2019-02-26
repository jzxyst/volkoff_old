//=============================================================================
//�y AttackedObject �z
//=============================================================================

#include "stdafx.h"
#include	"DT_AttackedObject.h"	/* For DynamicTracer-TestPoint */
#include "AttackedObject.h"
#include "attackedobject.h"
#include "../Game/GameManager.h"
//#include "Character.h"
#include "Player.h"
//=============================================================================
// �� AttackedObject �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
AttackedObject::AttackedObject()
    : mAttackedGroup    ( 0 )
{
    __DtTestPoint(__DtFunc_AttackedObject, __DtStep_0)
    getManager()->addAttackedObject( this );
	__DtTestPoint(__DtFunc_AttackedObject, __DtStep_1)
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
AttackedObject::~AttackedObject()
{
    __DtTestPoint(__DtFunc_AttackedObject, __DtStep_2)
    getManager()->removeAttackedObject( this );
	__DtTestPoint(__DtFunc_AttackedObject, __DtStep_3)
}

//---------------------------------------------------------------------
// �� ���̃I�u�W�F�N�g�ɍU����^����
//---------------------------------------------------------------------
void AttackedObject::attackEffect( GameObject* attacker_, int damage_, u32 range_rate_, u32 critical_rate_,  LVector3& brow_vec_, u32 stun_frame_ )
{
    // �����ƃN���e�B�J���Ƃ��̌v�Z������ damage �ɓ���Ă���

    float dmg_rate = static_cast< float >( ( 100 - range_rate_ ) + ( rand() % ( range_rate_ * 2 ) ) ) * 0.01f;
    u32 damage = dmg_rate * damage_;
	u8 criticalflag=0;
	u8 guardflag=0;

	u8 Level = GameManager::getInstance()->getPlayer()->getLevel();
	u32 Floor = GameManager::getInstance()->getFloorNum();
	u8 Rank = GameManager::getInstance()->getRank();


	__DtTestPoint(__DtFunc_attackEffect, __DtStep_0)
	if((attacker_->getObjType() == OBJ_GRENADE)&&(this->getObjType() ==OBJ_CHARACTER)&&(damage_>=60))
	{
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_1)
		damage=50;
	}
	//�G�̏e�e���������邽��
	if((attacker_->getObjType() == OBJ_BULLET)&&(this->getObjType() ==OBJ_CHARACTER))
	{
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_2)
		damage=damage/2;
	}
	//��Փx�ɂ���_���[�W�̌v�Z
	if(getObjType()==OBJ_CHARACTER)
	{

		__DtTestPoint(__DtFunc_attackEffect, __DtStep_3)
		switch(Rank)
		{
		case RANK_EASY:
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_4)
			damage=damage/5;
			break;
		case RANK_NOMAL:
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_5)
			damage=damage/2.5;
			break;
		case RANK_HARD:
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_6)
			damage=damage/2;
			break;
		case RANK_VALFIRLE:
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_7)
			damage=damage/2+damage/4;
			break;

		}
		if(damage==0)
			damage=1;
	}
	//�v���C���[�̌��݃��x�������t���A���̂ق����傫�������ꍇ�G�̃N���e�B�J�������Փx�ɂ���Ă�����
	if((attacker_->getObjType()==OBJ_ENEMY)&&(Level<Floor+1))
	{
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_8)
		critical_rate_+=(Rank+1)*(Floor+1);
		//printf("�N���e�B�J����%d\n",critical_rate_);
	}

	//�v���C���[�̃��x�����Q�ȏ�Ȃ�N���e�B�J�������グ��
	if((attacker_->getObjType()==OBJ_CHARACTER)&&(Level>=2))
	{
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_9)
		critical_rate_+=Level*3;
	}

	//�v���C���[�m�����ɃN���e�B�J�����A�b�v
	if((attacker_->getLife()<=20)&&(attacker_->getObjType()==OBJ_CHARACTER)&&(critical_rate_<=50))
	{
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_10)
		critical_rate_=50;
	}

    // ���m���ŃK�[�h����悤�ȏꍇ�́AEV_ATTACK_EFFECT �𑗂�O�� �K�[�h�J�n�C�x���g�𑗂�B
	Character* chara = dynamic_cast< Character* >( this );
	if ( chara )
	{

		// �K�[�h����ꍇ
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_11)
		if ((chara->getCharaState()==CHARASTATE_GUARD)||(chara->getCharaState()==CHARASTATE_SQGUARD))
		{
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_12)
			guardflag=1;
			//�K�[�h���_���[�W�����炷
			if(chara->getCharaState()==CHARASTATE_GUARD)
			{
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_13)
				damage=damage/10+1;
				brow_vec_.y=0;
				brow_vec_.x=25;
			}
			else
			{
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_14)
				damage=damage/7+1;
				brow_vec_.y=0;
				brow_vec_.x=15;			
			}
			//�v���C���[�̓K�[�h�����u�Ԃ̃_���[�W���ɂ���
			if((chara->getObjType()==OBJ_CHARACTER)&&(10+Level*2>=GameManager::getInstance()->getPlayer()->getGuardFrame()))
			{
				//printf("�W���X�g��-��\n");
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_15)
				damage=0;
			}
			//�K�[�h�����E����Ȃ��悤�ɂ���
			if(this->getLife()<=3)
			{
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_16)
				damage=0;
			}
			//���ȏ�̃X�^���t���[���̍U�����󂯂���̂����点��
			if(((stun_frame_>=60)&&(CHARASTATE_GUARD))||((stun_frame_>=40)&&(CHARASTATE_SQGUARD)))
			{
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_17)
				stun_frame_=30;
			}
			else
			{
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_18)
				stun_frame_=0;
			}

		}
		else
		{

		// �K�[�h���Ȃ��ōU�����󂯂�ꍇ
			//�N���e�B�J���̌v�Z
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_19)
			if(rand()%100<=critical_rate_)
			{
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_20)
				damage*=2;
				criticalflag=1;
				//printf("�N���e�B�J��");
			}

		}

		//�v���C���[�̂����莞���G
		//if((chara->getCharaState()==CHARASTATE_STUN)&&(this->getObjType() == OBJ_CHARACTER))
		//�v���C���[�̂����莞���G�@�C�[�W�[�ȊO�̎��@�v���C���[�̃��x�����t���A����1�ȏ㑽���ꍇ����
		if((chara->getCharaState()==CHARASTATE_STUN)&&(this->getObjType() == OBJ_CHARACTER)&&((Level+1 > Floor)||(Rank == RANK_EASY)))
		//if(chara->getObjType()==OBJ_CHARACTER)//�f�o�b�O�p
		{
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_21)
			if(stun_frame_<=60)
			{
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_22)
				criticalflag=0;
				damage=0;
				stun_frame_=0;
				brow_vec_.y=0;
				brow_vec_.x=0;	
			}
		}
		//���G���Ԓ����G
		if(chara->getInvincibleFrame()>0)
		{
			//printf("muteki\n");
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_23)
			criticalflag=0;
			damage=0;
			stun_frame_=0;
			brow_vec_.y=0;
			brow_vec_.x=0;		
		}

		//��Փx�n�[�h�ȏ�Ń{�X�����m���Ń_�E�����Â炭����
		if((chara->getWeaponData().WeaponType>=WEAPON_BOSS_BEGIN)&&(rand()%2==1)&&(Rank>=2))
		{
			//printf("muteki\n");
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_24)
			criticalflag=0;
			if(stun_frame_>=25)
				stun_frame_=25;
			if(damage>=10)
				damage=damage/2+damage/4;
		}
		if((chara->getWeaponData().WeaponType>=WEAPON_BOSS_BEGIN)&&(attacker_->getObjType() == OBJ_BULLET))
		{
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_25)
			damage=damage/2;
		}
	}

	//�v���[���[�̕���̎�ނɂāA�A���U��3��50%�̊m����Super�U���ɂ���B
	if ((attacker_->getObjType() == OBJ_CHARACTER)) {
		Character* player = dynamic_cast< Character* >(attacker_);
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_26)
		if ((player->getObjType()==OBJ_CHARACTER) && player->getCharaState() == CHARASTATE_ATTACK_3) {
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_27)
			if ((::rand() % 2) == 1) {
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_28)
				switch (player->getWeaponData().WeaponType) {
				case WEAPON_KATANA:
						__DtTestPoint(__DtFunc_attackEffect, __DtStep_29)
						damage = 500;
					break;
				case WEAPON_SCYTHE:
						__DtTestPoint(__DtFunc_attackEffect, __DtStep_30)
						damage = 700;
					break;
				case WEAPON_STICK:
						__DtTestPoint(__DtFunc_attackEffect, __DtStep_31)
						damage = 300;
					break;
				case WEAPON_UMBRELLA:
						__DtTestPoint(__DtFunc_attackEffect, __DtStep_32)
						damage = 150;
					break;
				case WEAPON_TAEKWONDO:
						__DtTestPoint(__DtFunc_attackEffect, __DtStep_33)
						damage = 400;
					break;
				case WEAPON_KNIFE:
						__DtTestPoint(__DtFunc_attackEffect, __DtStep_34)
						damage = 200;
					break;
				default:
					__DtTestPoint(__DtFunc_attackEffect, __DtStep_35)
					break;
				}
			}
		}
		__DtTestPointValue(__DtFunc_attackEffect, __DtStep_36, (void *)&damage, sizeof(damage))
	}

	//if ( 0 < stun_frame_ && 0 != this->mVelocity.x && !this->mOnGround )
	if(60 <= stun_frame_)
	{
		// �ӂ��Ƃ΂�
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_37)
		getManager()->postEvent( getHandle(), EV_ACTION_BLOW, &stun_frame_, sizeof( u32 ) );
	}
	else
	{
		// �̂����点��
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_38)
		if(stun_frame_!=0)
		getManager()->postEvent( getHandle(), EV_ACTION_STUN, &stun_frame_, sizeof( u32 ) );
	}

	//
	//printf("damege%d\n",damage);
    AttackEventArg arg;
    arg.Damage      = damage;
	//    arg.Damage      = 0;//debug
	arg.Criticalflag=criticalflag;
	arg.Guardflag=guardflag;
    arg.BrowVector  = brow_vec_;
    arg.BrowVector.x *= ( attacker_->getDirection() == CHARADIR_LEFT ) ? -1.0f : 1.0f;  // �U�����̌����ɂ���Ăӂ���΂������𔽓]����
	arg.AttackerHandle = attacker_->getHandle();
    getManager()->postEvent( getHandle(), EV_APPLY_DAMAGE, &arg, sizeof( AttackEventArg ) );

    

    // �����ł͂܂� mLife �̌��Z�ȂǁA�����o�ϐ��͑��삵�Ȃ��B
    // ����� HandleEvent() �� EV_ATTACK_EFFECT ���󂯎�������ɍs���B

    // ����� HandleEvent �ŁB
    //if ( mLife <= 0 )
    //{
    //    // �퓬�s�\�J�n (�󂯎�������ŁA���[�V�������J�n����Ƃ�)
    //    getManager()->postEvent( 0xffffffff, EV_ACTION_START_DEAD, &mHandle, sizeof( mHandle ) );
    //}
	__DtTestPoint(__DtFunc_attackEffect, __DtStep_39)
}

//---------------------------------------------------------------------
// �� �C�x���g����
//---------------------------------------------------------------------
int AttackedObject::HandleEvent( u32 event_,void *args_ )
{
    //switch ( event_ )
    __DtTestPoint(__DtFunc_HandleEvent, __DtStep_0)
    {
        // �̂�����J�n (Character �Œ�`)
        //case EV_ACTION_STUN:

        // �_���[�W��^���� (�p����Œ�`)
        //case EV_APPLY_DAMAGE:

        
    }

    __DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
    return 0;
}


//=============================================================================
//								end of file
//=============================================================================
