//=============================================================================
/*! 
    @addtogroup 
    @file       MidBoss1.cpp
    @brief      
    
    中ボスクラスの実装
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/12/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/12/13 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_MidBoss1.h"	/* For DynamicTracer-TestPoint */
#include "MidBoss1.h"
#include "Player.h"
#include "./../Game/GameManager.h"

//---------------------------------------------------------------------------
// ● オブジェクトを作成する
//---------------------------------------------------------------------------
MidBoss1* MidBoss1::create( void* args_, bool is_entity_ )
{
    MidBoss1* o = NEW MidBoss1();
    __DtTestPoint( __DtFunc_create, __DtStep_0 )
    o->Initialize( *static_cast< CreateData* >( args_ ) );
    o->mIsEntity = is_entity_;

    // 自分がこのホストで作成されたものであれば、自分以外のホストに生成したことを送信する
    if ( is_entity_ )
    {
        __DtTestPoint(__DtFunc_create, __DtStep_1)
        GameManager::getInstance()->getGameSession()->sendCreatedObjectEvent( OBJ_ENEMY, args_, sizeof( CreateData ) );
    }

    __DtTestPoint( __DtFunc_create, __DtStep_2 )
    return o;
}


//---------------------------------------------------------------------------
// ● オブジェクトをランダムで作成する
//---------------------------------------------------------------------------
MidBoss1* MidBoss1::createRandom()
{
    MidBoss1::CreateData data;
    __DtTestPoint( __DtFunc_createRandom, __DtStep_0 )
    data.Position = LVector3(0,0,0);
    data.WeaponLevel = 1;
	data.WeaponType = WEAPON_NON;
	for(int i = 0;i < WEAPON_MAX_NUM;++i)
	{
		__DtTestPoint(__DtFunc_createRandom, __DtStep_1)
		if(!(::rand() % gWeaponBaseData[i].Rate))
		{
			__DtTestPoint(__DtFunc_createRandom, __DtStep_2)
			data.WeaponType = static_cast<WeaponType>(i);
			break;
		}
	}
	data.WeaponType = static_cast<WeaponType>(::rand() % WEAPON_NORMAL_MAX_NUM);
	//data.WeaponType = WEAPON_KATANA;
	MidBoss1* pEnemy = MidBoss1::create( &data );

    __DtTestPoint( __DtFunc_createRandom, __DtStep_3 )
    return pEnemy;
}


//---------------------------------------------------------------------------
/*! 
	@brief MidBoss1::MidBoss1

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
MidBoss1::MidBoss1()
    : mWeaponLevel  ( 1 )
{
	__DtTestPoint( __DtFunc_MidBoss1, __DtStep_0 )
	this->m_pszName = "眠りを売る山本"; //一時的。後で適当な名前を代入する
	this->m_eCharaState = CHARASTATE_WAIT;

	this->m_AnimePuttern = 0;

	this->m_eAction = ENEMY_ACT_WAIT;

	this->m_bCreateWeapon = false;

	this->m_nAttackDelay = 0;
	this->m_nWalkIntvCnt = 0;
	this->m_nWalkRangeCnt = 0;
	this->m_bWalkDir = false;
	this->m_nEscapeRangeCnt = 0;
	this->m_nStandbyCnt = 0;
	this->m_nGuardCnt = 0;
	this->m_nSquatCnt = 0;
    // 攻撃対象グループは敵側
    setAttackedGroup( ATKGROUP_ENEMY );
	__DtTestPoint( __DtFunc_MidBoss1, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::~Enemy

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
MidBoss1::~MidBoss1()
{
	__DtTestPoint( __DtFunc_MidBoss1, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_MidBoss1, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief MidBoss1::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool MidBoss1::Initialize( const CreateData& data_ )
{
	bool r = false;
	
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	switch(data_.WeaponType)
	{
	case WEAPON_BOSS_KATANA:
		__DtTestPoint(__DtFunc_Initialize, __DtStep_1)
		this->m_pszName = "眠りを売る山本";
		r = Character::Initialize();
		this->mCharaPanel.setColorScale(0.25f,0.80f,0.25f);
		break;

	case WEAPON_BOSS_TAEKWONDO:
		__DtTestPoint(__DtFunc_Initialize, __DtStep_2)
		this->m_pszName = "花の服部";
		r = Character::Initialize();
		this->mCharaPanel.setColorScale(0.95f,0.7f,0.7f);
		break;

	case WEAPON_BOSS_KNIFE:
		__DtTestPoint(__DtFunc_Initialize, __DtStep_3)
		this->m_pszName = "三角木馬の石黒";
		r = Character::Initialize();
		this->mCharaPanel.setColorScale(0.7f,0.7f,0.95f);
		break;
	case WEAPON_VALFIRLE_TOKEN:
		__DtTestPoint(__DtFunc_Initialize, __DtStep_4)
		this->m_pszName = "Valfirle";
		r = Character::Initialize();
		break;
	default:
		__DtTestPoint(__DtFunc_Initialize, __DtStep_5)
		this->m_pszName = "眠りを売る山本";
		r = Character::Initialize();
		break;
	}

	this->mScore = 10000;
	this->mExp = 200;

    this->mPosition = data_.Position;
    this->mVelocity = data_.Velocity;
    mWeaponLevel    = data_.WeaponLevel;
    
    //this->m_pszName = "MidBoss"; //一時的。後で適当な名前を代入する
	this->mLife = this->mMaxLife = scg_nMidBoss1Life[GameManager::getInstance()->getRank()];

	this->m_nRandAttackRange = ::rand() % 40 - 20;
	this->m_nRandAttackDelay = ::rand() % 40 - 10;
	this->m_nRandSearchRange = this->scm_nSearchX;

	WeaponData data;
	data.UseCount = -1;
	data.WeaponType =  static_cast<WeaponType>(data_.WeaponType);
	this->changeWeapon(data);

	__DtTestPoint( __DtFunc_Initialize, __DtStep_6 )
	return r;
}


//---------------------------------------------------------------------------
/*! 
	@brief MidBoss1::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool MidBoss1::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //deleteはManagerに任せる

	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief MidBoss1::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool MidBoss1::Update()
{
    __DtTestPoint( __DtFunc_Update, __DtStep_0 )
    return Character::Update();
}

//---------------------------------------------------------------------------
// ● フレーム更新処理 (オブジェクトに影響を与える処理)
//---------------------------------------------------------------------------
bool MidBoss1::UpdateSelf()
{
	//死んだ際に持っている武器を落とす
	__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_0 )
	if(this->mLife <= 0 && !this->m_bCreateWeapon)
	{
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_1)
		GameManager::getInstance()->setKeyflag(1);
		//if(this->mWeaponData.WeaponType)
		//{
		//	Weapon::CreateData wdata;

		//	wdata.Data.WeaponType  = this->mWeaponData.WeaponType;
		//	wdata.Data.UseCount    = gWeaponBaseData[this->mWeaponData.WeaponType].UseCount;

		//	LVector3 v = this->mPosition;
		//	v.y += 100;
		//	wdata.Position = v;
		//	Weapon::create( &wdata );

		//	this->m_bCreateWeapon = true;
		//}
	}

	bool right = false;
	bool left  = false;
	bool button_A  = false;
	bool button_B  = false;
	bool Up = false;
	bool UpTrigger = false;
	bool Down = false;
	bool DownTrigger = false;
	bool Guard = false;
	bool GuardTrigger = false;

	Player *pPlayer = GameManager::getInstance()->getPlayer();

	//AI
	switch(this->m_eAction)
	{
	//未定義
	case ENEMY_ACT_UNDEF:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_2)
		this->m_eAction = ENEMY_ACT_WAIT;
		break;

	//待機
	case ENEMY_ACT_WAIT:
		//範囲内探索を行う
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_3)
		if(this->SearchPlayer())
		{
			//範囲内であれば追跡を開始する
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_4)
			this->m_eAction = ENEMY_ACT_CHASE;
			break;
		}

		//散歩を開始する
		if(this->m_nWalkIntvCnt > this->scm_nWalkIntv)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_5)
			this->m_nWalkRangeCnt = ::rand() % this->scm_nWalkRange; //散歩距離の設定
			this->m_nWalkIntvCnt = 0;
			this->m_bWalkDir = static_cast<bool>(::rand() % 2);
			this->m_eAction = ENEMY_ACT_WALK;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_6)
			++this->m_nWalkIntvCnt;
		}
		break;

	//散歩
	case ENEMY_ACT_WALK:
		//散歩を行っている
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_7)
		if(this->m_nWalkRangeCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_8)
			if(this->m_bWalkDir)
				right = true;
			else
				left = true;

			--this->m_nWalkRangeCnt;
		}
		//散歩終わり
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_9)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//追跡
	case ENEMY_ACT_CHASE:
		//プレイヤーが探索範囲内である
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_10)
		if(this->SearchPlayer())
		{
			//Playerは右にいる
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_11)
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_12)
				right = true;
			}
			//Playerは左にいる
			else
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_13)
				left = true;
			}

			//まれにジャンプする
			if(!(::rand() % scg_nMidBoss1JumpRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_14)
				button_B = true;
			}

			//プレイヤーが観察範囲内である
			if(::abs(this->mPosition.x + ::rand() % this->scm_nSearchRand - pPlayer->getPosition().x) <= this->scm_nStandbyRange)
			{
				//ランダムで観察を開始する
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_15)
				if(!(::rand() % scg_nMidBoss1StandbyRatio[GameManager::getInstance()->getRank()]))
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_16)
					this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
					this->m_eAction = ENEMY_ACT_STANDBY;
					break;
				}
			}

			//プレイヤーが攻撃範囲内である
			if(this->SearchAttack1Range())
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_17)
				this->m_eAction = ENEMY_ACT_ATTACK_RANGE;
				break;
			}
		}
		else
		{
			//探索範囲外であれば待機に戻す
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_18)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//観察
	case ENEMY_ACT_STANDBY:
		//プレイヤーがジャンプした瞬間対空攻撃を行う
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_19)
		if(pPlayer->getCharaState() == CHARASTATE_JUMP)
		{
			//this->m_nStandbyCnt = 0;
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_20)
			break;
		}

		//観察を行う
		if(this->m_nStandbyCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_21)
			--this->m_nStandbyCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_22)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//逃走
	case ENEMY_ACT_ESCAPE:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_23)
		if(this->m_nEscapeRangeCnt)
		{
			//Playerは右にいる
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_24)
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_25)
				left = true;
			}
			//Playerは左にいる
			else
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_26)
				right = true;
			}

			--this->m_nEscapeRangeCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_27)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//攻撃範囲内
	case ENEMY_ACT_ATTACK_RANGE:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_28)
		if(this->SearchAttack1Range())
		{
			//ランダムで攻撃を開始する
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_29)
			if(!(::rand() % scg_nMidBoss1AttackRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_30)
				this->m_eAction = ENEMY_ACT_ATTACK;
				break;
			}
			//ランダムで防御を開始する
			if(!(::rand() % scg_nMidBoss1GuardRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_31)
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_GUARD;
				break;
			}
			//ランダムで観察を開始する
			if(!(::rand() % scg_nMidBoss1StandbyRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_32)
				this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_STANDBY;
				break;
			}
			//ランダムでしゃがみガードを開始する
			if(!(::rand() % scg_nMidBoss1SquatGuardRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_33)
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_SQUAT_GUARD;
				break;
			}
			//ランダムでしゃがみを開始する
			if(!(::rand() % scg_nMidBoss1SquatRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_34)
				this->m_nSquatCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_SQUAT;
				break;
			}
			//ランダムで逃走を開始する
			if(!(::rand() % scg_nMidBoss1EscapeRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_35)
				this->m_nEscapeRangeCnt = ::rand() % this->scm_nEscapeRange;
				this->m_eAction = ENEMY_ACT_ESCAPE;
				break;
			}
		}
		//攻撃範囲外
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_36)
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//攻撃中
	case ENEMY_ACT_ATTACK:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_37)
		if(this->SearchAttack1Range())
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_38)
			switch(this->m_eCharaState)
			{
			case CHARASTATE_ATTACK_SQUAT_ATTACK:
			case CHARASTATE_ATTACK_JUMP_ATTACK:
			case CHARASTATE_ATTACK_ANTIAIR_ATTACK:
			case CHARASTATE_ATTACK_DUSH_ATTACK:
				//特殊攻撃後は待機に戻す
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_39)
				this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_1:
				//通常攻撃2段目
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_40)
				if(scg_bMidBoss1Attack2Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nMidBoss1Attack2Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_2:
				//通常攻撃3段目
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_41)
				if(scg_bMidBoss1Attack3Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nMidBoss1Attack3Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			default:
				//ジャンプ攻撃は事前にジャンプする
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_42)
				if(!(::rand() % scg_nMidBoss1JumpAttackRatio[GameManager::getInstance()->getRank()]))
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_43)
					button_B = true;
					break;
				}
				//しゃがみ攻撃
				if(!(::rand() % scg_nMidBoss1SquatAttackRatio[GameManager::getInstance()->getRank()]))
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_44)
					Down = true;
				}

				//通常攻撃1段目
				button_A = true;

				break;
			}

			//Player座標が上であれば、対空攻撃をする
			if(this->mPosition.y < pPlayer->getPosition().y)
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_45)
				Up = true;
			}
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_46)
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//防御
	case ENEMY_ACT_GUARD:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_47)
		if(this->m_nGuardCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_48)
			Guard = true;
			--this->m_nGuardCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_49)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//しゃがみガード
	case ENEMY_ACT_SQUAT_GUARD:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_50)
		if(this->m_nGuardCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_51)
			GuardTrigger = true;
			Guard = true;
			Down = true;
			--this->m_nGuardCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_52)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//しゃがみ
	case ENEMY_ACT_SQUAT:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_53)
		if(this->m_nSquatCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_54)
			Down = true;
			--this->m_nSquatCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_55)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	default:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_56)
		this->m_eAction = ENEMY_ACT_WAIT;
		break;
	}
	//AI end

    // 死亡 (死亡モーション中) は入力を受け付けない
    if ( isDead() )
    {
        __DtTestPoint( __DtFunc_UpdateSelf, __DtStep_57 )
        return true;
    }

    // 移動できる場合 (のけぞり中等ではない)
    if ( mStunFrame == 0 )
    {
        //------------------------------------------------------
        // 攻撃動作中の場合
        __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_58)
        if ( isAttacking() )
        {
			// 行動制限解除（=出し終わり）してないと操作不可
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_59)
			if ( !mAttackLocked )
			{
				// 連続攻撃
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_60)
				if ( button_A )
				{
					// 行動制限
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_61)
					this->AttackLock();

					switch( m_eCharaState )
					{
					case CHARASTATE_ATTACK_1:
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_62)
						if(scg_bMidBoss1Attack2Permission[GameManager::getInstance()->getRank()])
							getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_2, NULL, 0 );
						break;

					case CHARASTATE_ATTACK_2:
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_63)
						if(scg_bMidBoss1Attack3Permission[GameManager::getInstance()->getRank()])
							getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_3, NULL, 0 );
						break;

					default:
						// 万が一おかしい値になったらロック解除
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_64)
						this->AttackUnLock();
						break;
					}
				}
			}
        }
        //------------------------------------------------------
        // 攻撃動作中ではない場合
        else
        {
			
			// 攻撃開始
            __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_65)
            if ( button_A && m_eCharaState != EV_ACTION_ATTACK_1 )  // 後ろのは仮
            {
                // ジャンプ中の場合
                __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_66)
                if ( mJump )
                {
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_67)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_JUMP_ATTACK, NULL, 0 );
                }
                // しゃがみ中の場合
                else if ( Down )
                {
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_68)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_SQUAT_ATTACK, NULL, 0 );
                }
				// 上を押しながらの場合
				else if ( !mTouchLadder && Up )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_69)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_ANTIAIR_ATTACK, NULL, 0 );
					this->m_nAttackDelay = 0;
				}
                // 以上以外は通常攻撃
                else
                {
					// 攻撃のため行動制限
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_70)
					if(scg_bMidBoss1Attack1Permission[GameManager::getInstance()->getRank()])
					{
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_71)
						this->AttackLock();
						getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_1, NULL, 0 );
					}
                }

                __DtTestPoint( __DtFunc_UpdateSelf, __DtStep_72 )
                return true;
            }

			// ガード
			if ( !Down && Guard && mOnGround && !mClimbLadder && m_eCharaState != CHARASTATE_GUARD )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_73)
				getManager()->postEvent( getHandle(), EV_ACTION_GUARD, NULL, 0 );
				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_74 )
				return true;
			}

			// 向きを変えるための処理
			if ( right )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_75)
				setDirection( CHARADIR_RIGHT );
			}
			else if ( left )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_76)
				setDirection( CHARADIR_LEFT );
			}

			// 右移動
			//if ( !mClimbLadder && right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
			//{
			//	// 方向をつけて EV_ACTION_RUN イベントを送る。
			//	// このあと、HandleEvent() で実際に移動を開始する。
			//	// このイベントはキューイングせず、即座に HandleEvent() に送られる。
			//	//u32 dir = CHARADIR_RIGHT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		// getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}
			//// 左移動
			//else if( !mClimbLadder && left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) )
			//{
			//	//u32 dir = CHARADIR_LEFT;

			// 移動
			if ( ( !Guard && !this->mClimbLadder && right && !left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
				|| ( !Guard && !this->mClimbLadder && left && !right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) ) )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_77)
				if ( !Down )
					getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			}
			// 左右のいずれも押されていない場合は待機にする
			// 梯子離したときも待機で。
			// (後ろの mState != CHARASTATE_WAIT は、待機中に連続でイベントが送られないようにするために必要)
			else if ( ( !Guard && this->mOnGround && ( ( !right && !left ) || ( right && left ) ) && !Down && !this->mClimbLadder && m_eCharaState != CHARASTATE_WAIT )
				|| this->mNewTouchObj != OBJ_LADDER && this->mOldTouchObj == OBJ_LADDER && m_eCharaState != CHARASTATE_WAIT && m_eCharaState != CHARASTATE_JUMP && m_eCharaState != CHARASTATE_RUN )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_78)
				getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
			}

			// ジャンプ開始
			if ( button_B && m_eCharaState != CHARASTATE_JUMP && ( this->mOnGround || this->mClimbLadder ) )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_79)
				getManager()->postEvent( getHandle(), EV_ACTION_JUMP, NULL, 0 );
				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_80 )
				return true;
			}

			// しゃがみ開始
			if ( Down && this->mOnGround && !this->mTouchLadder )
			{
				// しゃがみながらガードした場合
				// ガードしながらしゃがんだ場合
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_81)
				if ( ( ( GuardTrigger ) || ( DownTrigger && Guard ) ) && m_eCharaState != CHARASTATE_SQGUARD )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_82)
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT_GUARD, NULL, 0 );
				}
				else if ( !Guard && m_eCharaState != CHARASTATE_SQUAT )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_83)
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT, NULL, 0 );
				}
			}

			// はしごつかみ
			if ( mTouchLadder
				&& m_eCharaState != CHARASTATE_LADDER_UP
				&& m_eCharaState != CHARASTATE_LADDER_DOWN
				&& m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				bool Catch = false;

				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_84)
				if ( UpTrigger && mDistance.y > 0 )
					Catch = true;

				if ( DownTrigger && mDistance.y < 0 )
					Catch = true;

				if ( Catch )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_85)
					this->mPosition.set(
						mPosition.x + mDistance.x,
						mPosition.y,
						mPosition.z
						);
					mClimbLadder = true;
				}
			}

			// はしご上昇
			if ( Up && m_eCharaState != CHARASTATE_LADDER_UP && mClimbLadder )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_86)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_UP, NULL, 0 );

				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_87 )
				return true;
			}
			// はしご下降
			else if ( Down && m_eCharaState != CHARASTATE_LADDER_DOWN && mClimbLadder )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_88)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_DOWN, NULL, 0 );

				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_89 )
				return true;
			}
			// はしご待機
			else if ( !Up && !Down && mClimbLadder && m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_90)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_WAIT, NULL, 0 );

				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_91 )
				return true;
			}
        }
    }

    __DtTestPoint( __DtFunc_UpdateSelf, __DtStep_92 )
    return true;
}




//---------------------------------------------------------------------------
/*! 
	@brief MidBoss1::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int MidBoss1::HandleEvent(u32 event_,void *args_)
{
	///////////////////////////////////////// 戦闘不能開始
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	switch ( event_ )
	{
        case EV_ACTION_START_DEAD:
			//経験値の処理
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
			GameManager::getInstance()->getPlayer()->setExp(GameManager::getInstance()->getPlayer()->getExp()+this->mExp);

			printf("score%d\n",this->mScore);
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2))); 
            break;
	}
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_2 )
	return Character::HandleEvent( event_, args_ );
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::SearchPlayer

	プレイヤーの探索を行う

	@return         bool
	- true  範囲内
	- false 範囲外
	@exception      none
*/
//---------------------------------------------------------------------------
bool MidBoss1::SearchPlayer()
{
	bool bRes = false;
	Player *pPlayer = GameManager::getInstance()->getPlayer();

	__DtTestPoint( __DtFunc_SearchPlayer, __DtStep_0 )
	if(::abs(this->mPosition.y - pPlayer->getPosition().y) < this->scm_nSearchY)
	{
		//探索範囲内である
		__DtTestPoint(__DtFunc_SearchPlayer, __DtStep_1)
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) < this->m_nRandSearchRange)
		{
			__DtTestPoint(__DtFunc_SearchPlayer, __DtStep_2)
			bRes = true;
		}
	}

	__DtTestPoint( __DtFunc_SearchPlayer, __DtStep_3 )
	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief MidBoss1::SearchAttack1Range

	攻撃範囲探索を行う

	@return         bool
	- true  範囲内
	- false 範囲外
	@exception      none
*/
//---------------------------------------------------------------------------
bool MidBoss1::SearchAttack1Range()
{
	bool bRes = false;
	LRect *r = NULL;
	Player *pPlayer = GameManager::getInstance()->getPlayer();

	__DtTestPoint( __DtFunc_SearchAttack1Range, __DtStep_0 )
	for(int i = 6;i < 11;++i)
	{
		__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_1)
		r = this->mCollision->getAtkCollisionByIndex(i);

		if(r)
			break;
	}

	if(r)
	{
		//攻撃範囲内
		__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_2)
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) <= r->x + r->w - 40) //40は一時的
		{
			__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_3)
			bRes = true;
		}
	}

	__DtTestPoint( __DtFunc_SearchAttack1Range, __DtStep_4 )
	return bRes;
}


//=============================================================================
//								End of File
//=============================================================================
