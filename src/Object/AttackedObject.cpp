//=============================================================================
//【 AttackedObject 】
//=============================================================================

#include "stdafx.h"
#include	"DT_AttackedObject.h"	/* For DynamicTracer-TestPoint */
#include "AttackedObject.h"
#include "attackedobject.h"
#include "../Game/GameManager.h"
//#include "Character.h"
#include "Player.h"
//=============================================================================
// ■ AttackedObject クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
AttackedObject::AttackedObject()
    : mAttackedGroup    ( 0 )
{
    __DtTestPoint(__DtFunc_AttackedObject, __DtStep_0)
    getManager()->addAttackedObject( this );
	__DtTestPoint(__DtFunc_AttackedObject, __DtStep_1)
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
AttackedObject::~AttackedObject()
{
    __DtTestPoint(__DtFunc_AttackedObject, __DtStep_2)
    getManager()->removeAttackedObject( this );
	__DtTestPoint(__DtFunc_AttackedObject, __DtStep_3)
}

//---------------------------------------------------------------------
// ● このオブジェクトに攻撃を与える
//---------------------------------------------------------------------
void AttackedObject::attackEffect( GameObject* attacker_, int damage_, u32 range_rate_, u32 critical_rate_,  LVector3& brow_vec_, u32 stun_frame_ )
{
    // ちゃんとクリティカルとかの計算をして damage に入れておく

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
	//敵の銃弾が強すぎるため
	if((attacker_->getObjType() == OBJ_BULLET)&&(this->getObjType() ==OBJ_CHARACTER))
	{
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_2)
		damage=damage/2;
	}
	//難易度による被ダメージの計算
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
	//プレイヤーの現在レベルよりもフロア数のほうが大きかった場合敵のクリティカル率を難易度によってあげる
	if((attacker_->getObjType()==OBJ_ENEMY)&&(Level<Floor+1))
	{
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_8)
		critical_rate_+=(Rank+1)*(Floor+1);
		//printf("クリティカル率%d\n",critical_rate_);
	}

	//プレイヤーのレベルが２以上ならクリティカル率を上げる
	if((attacker_->getObjType()==OBJ_CHARACTER)&&(Level>=2))
	{
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_9)
		critical_rate_+=Level*3;
	}

	//プレイヤー瀕死時にクリティカル率アップ
	if((attacker_->getLife()<=20)&&(attacker_->getObjType()==OBJ_CHARACTER)&&(critical_rate_<=50))
	{
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_10)
		critical_rate_=50;
	}

    // 一定確率でガードするような場合は、EV_ATTACK_EFFECT を送る前に ガード開始イベントを送る。
	Character* chara = dynamic_cast< Character* >( this );
	if ( chara )
	{

		// ガードする場合
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_11)
		if ((chara->getCharaState()==CHARASTATE_GUARD)||(chara->getCharaState()==CHARASTATE_SQGUARD))
		{
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_12)
			guardflag=1;
			//ガード中ダメージを減らす
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
			//プレイヤーはガードした瞬間のダメージを零にする
			if((chara->getObjType()==OBJ_CHARACTER)&&(10+Level*2>=GameManager::getInstance()->getPlayer()->getGuardFrame()))
			{
				//printf("ジャストが-ど\n");
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_15)
				damage=0;
			}
			//ガード中削り殺されないようにする
			if(this->getLife()<=3)
			{
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_16)
				damage=0;
			}
			//一定以上のスタンフレームの攻撃を受けたらのけぞらせる
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

		// ガードしないで攻撃を受ける場合
			//クリティカルの計算
			__DtTestPoint(__DtFunc_attackEffect, __DtStep_19)
			if(rand()%100<=critical_rate_)
			{
				__DtTestPoint(__DtFunc_attackEffect, __DtStep_20)
				damage*=2;
				criticalflag=1;
				//printf("クリティカル");
			}

		}

		//プレイヤーのけぞり時無敵
		//if((chara->getCharaState()==CHARASTATE_STUN)&&(this->getObjType() == OBJ_CHARACTER))
		//プレイヤーのけぞり時無敵　イージー以外の時　プレイヤーのレベルよりフロア数が1以上多い場合無効
		if((chara->getCharaState()==CHARASTATE_STUN)&&(this->getObjType() == OBJ_CHARACTER)&&((Level+1 > Floor)||(Rank == RANK_EASY)))
		//if(chara->getObjType()==OBJ_CHARACTER)//デバッグ用
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
		//無敵時間中無敵
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

		//難易度ハード以上でボスを一定確率でダウンしづらくする
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

	//プレーヤーの武器の種類にて、連続攻撃3は50%の確率でSuper攻撃にする。
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
		// ふっとばす
		__DtTestPoint(__DtFunc_attackEffect, __DtStep_37)
		getManager()->postEvent( getHandle(), EV_ACTION_BLOW, &stun_frame_, sizeof( u32 ) );
	}
	else
	{
		// のけぞらせる
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
    arg.BrowVector.x *= ( attacker_->getDirection() == CHARADIR_LEFT ) ? -1.0f : 1.0f;  // 攻撃側の向きによってふっ飛ばし方向を反転する
	arg.AttackerHandle = attacker_->getHandle();
    getManager()->postEvent( getHandle(), EV_APPLY_DAMAGE, &arg, sizeof( AttackEventArg ) );

    

    // ここではまだ mLife の減算など、メンバ変数は操作しない。
    // それは HandleEvent() で EV_ATTACK_EFFECT を受け取った時に行う。

    // これは HandleEvent で。
    //if ( mLife <= 0 )
    //{
    //    // 戦闘不能開始 (受け取った側で、モーションを開始するとか)
    //    getManager()->postEvent( 0xffffffff, EV_ACTION_START_DEAD, &mHandle, sizeof( mHandle ) );
    //}
	__DtTestPoint(__DtFunc_attackEffect, __DtStep_39)
}

//---------------------------------------------------------------------
// ● イベント処理
//---------------------------------------------------------------------
int AttackedObject::HandleEvent( u32 event_,void *args_ )
{
    //switch ( event_ )
    __DtTestPoint(__DtFunc_HandleEvent, __DtStep_0)
    {
        // のけぞり開始 (Character で定義)
        //case EV_ACTION_STUN:

        // ダメージを与える (継承先で定義)
        //case EV_APPLY_DAMAGE:

        
    }

    __DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
    return 0;
}


//=============================================================================
//								end of file
//=============================================================================
