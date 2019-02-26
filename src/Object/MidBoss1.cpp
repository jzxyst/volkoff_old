//=============================================================================
/*! 
    @addtogroup 
    @file       MidBoss1.cpp
    @brief      
    
    ���{�X�N���X�̎���
    
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
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_MidBoss1.h"	/* For DynamicTracer-TestPoint */
#include "MidBoss1.h"
#include "Player.h"
#include "./../Game/GameManager.h"

//---------------------------------------------------------------------------
// �� �I�u�W�F�N�g���쐬����
//---------------------------------------------------------------------------
MidBoss1* MidBoss1::create( void* args_, bool is_entity_ )
{
    MidBoss1* o = NEW MidBoss1();
    __DtTestPoint( __DtFunc_create, __DtStep_0 )
    o->Initialize( *static_cast< CreateData* >( args_ ) );
    o->mIsEntity = is_entity_;

    // ���������̃z�X�g�ō쐬���ꂽ���̂ł���΁A�����ȊO�̃z�X�g�ɐ����������Ƃ𑗐M����
    if ( is_entity_ )
    {
        __DtTestPoint(__DtFunc_create, __DtStep_1)
        GameManager::getInstance()->getGameSession()->sendCreatedObjectEvent( OBJ_ENEMY, args_, sizeof( CreateData ) );
    }

    __DtTestPoint( __DtFunc_create, __DtStep_2 )
    return o;
}


//---------------------------------------------------------------------------
// �� �I�u�W�F�N�g�������_���ō쐬����
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

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
MidBoss1::MidBoss1()
    : mWeaponLevel  ( 1 )
{
	__DtTestPoint( __DtFunc_MidBoss1, __DtStep_0 )
	this->m_pszName = "����𔄂�R�{"; //�ꎞ�I�B��œK���Ȗ��O��������
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
    // �U���ΏۃO���[�v�͓G��
    setAttackedGroup( ATKGROUP_ENEMY );
	__DtTestPoint( __DtFunc_MidBoss1, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::~Enemy

	�f�X�g���N�^

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

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
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
		this->m_pszName = "����𔄂�R�{";
		r = Character::Initialize();
		this->mCharaPanel.setColorScale(0.25f,0.80f,0.25f);
		break;

	case WEAPON_BOSS_TAEKWONDO:
		__DtTestPoint(__DtFunc_Initialize, __DtStep_2)
		this->m_pszName = "�Ԃ̕���";
		r = Character::Initialize();
		this->mCharaPanel.setColorScale(0.95f,0.7f,0.7f);
		break;

	case WEAPON_BOSS_KNIFE:
		__DtTestPoint(__DtFunc_Initialize, __DtStep_3)
		this->m_pszName = "�O�p�ؔn�̐΍�";
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
		this->m_pszName = "����𔄂�R�{";
		r = Character::Initialize();
		break;
	}

	this->mScore = 10000;
	this->mExp = 200;

    this->mPosition = data_.Position;
    this->mVelocity = data_.Velocity;
    mWeaponLevel    = data_.WeaponLevel;
    
    //this->m_pszName = "MidBoss"; //�ꎞ�I�B��œK���Ȗ��O��������
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

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool MidBoss1::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //delete��Manager�ɔC����

	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief MidBoss1::Update

	�t���[���X�V����

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
// �� �t���[���X�V���� (�I�u�W�F�N�g�ɉe����^���鏈��)
//---------------------------------------------------------------------------
bool MidBoss1::UpdateSelf()
{
	//���񂾍ۂɎ����Ă��镐��𗎂Ƃ�
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
	//����`
	case ENEMY_ACT_UNDEF:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_2)
		this->m_eAction = ENEMY_ACT_WAIT;
		break;

	//�ҋ@
	case ENEMY_ACT_WAIT:
		//�͈͓��T�����s��
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_3)
		if(this->SearchPlayer())
		{
			//�͈͓��ł���ΒǐՂ��J�n����
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_4)
			this->m_eAction = ENEMY_ACT_CHASE;
			break;
		}

		//�U�����J�n����
		if(this->m_nWalkIntvCnt > this->scm_nWalkIntv)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_5)
			this->m_nWalkRangeCnt = ::rand() % this->scm_nWalkRange; //�U�������̐ݒ�
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

	//�U��
	case ENEMY_ACT_WALK:
		//�U�����s���Ă���
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
		//�U���I���
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_9)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//�ǐ�
	case ENEMY_ACT_CHASE:
		//�v���C���[���T���͈͓��ł���
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_10)
		if(this->SearchPlayer())
		{
			//Player�͉E�ɂ���
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_11)
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_12)
				right = true;
			}
			//Player�͍��ɂ���
			else
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_13)
				left = true;
			}

			//�܂�ɃW�����v����
			if(!(::rand() % scg_nMidBoss1JumpRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_14)
				button_B = true;
			}

			//�v���C���[���ώ@�͈͓��ł���
			if(::abs(this->mPosition.x + ::rand() % this->scm_nSearchRand - pPlayer->getPosition().x) <= this->scm_nStandbyRange)
			{
				//�����_���Ŋώ@���J�n����
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_15)
				if(!(::rand() % scg_nMidBoss1StandbyRatio[GameManager::getInstance()->getRank()]))
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_16)
					this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
					this->m_eAction = ENEMY_ACT_STANDBY;
					break;
				}
			}

			//�v���C���[���U���͈͓��ł���
			if(this->SearchAttack1Range())
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_17)
				this->m_eAction = ENEMY_ACT_ATTACK_RANGE;
				break;
			}
		}
		else
		{
			//�T���͈͊O�ł���Αҋ@�ɖ߂�
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_18)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//�ώ@
	case ENEMY_ACT_STANDBY:
		//�v���C���[���W�����v�����u�ԑ΋�U�����s��
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_19)
		if(pPlayer->getCharaState() == CHARASTATE_JUMP)
		{
			//this->m_nStandbyCnt = 0;
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_20)
			break;
		}

		//�ώ@���s��
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

	//����
	case ENEMY_ACT_ESCAPE:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_23)
		if(this->m_nEscapeRangeCnt)
		{
			//Player�͉E�ɂ���
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_24)
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_25)
				left = true;
			}
			//Player�͍��ɂ���
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

	//�U���͈͓�
	case ENEMY_ACT_ATTACK_RANGE:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_28)
		if(this->SearchAttack1Range())
		{
			//�����_���ōU�����J�n����
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_29)
			if(!(::rand() % scg_nMidBoss1AttackRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_30)
				this->m_eAction = ENEMY_ACT_ATTACK;
				break;
			}
			//�����_���Ŗh����J�n����
			if(!(::rand() % scg_nMidBoss1GuardRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_31)
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_GUARD;
				break;
			}
			//�����_���Ŋώ@���J�n����
			if(!(::rand() % scg_nMidBoss1StandbyRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_32)
				this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_STANDBY;
				break;
			}
			//�����_���ł��Ⴊ�݃K�[�h���J�n����
			if(!(::rand() % scg_nMidBoss1SquatGuardRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_33)
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_SQUAT_GUARD;
				break;
			}
			//�����_���ł��Ⴊ�݂��J�n����
			if(!(::rand() % scg_nMidBoss1SquatRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_34)
				this->m_nSquatCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_SQUAT;
				break;
			}
			//�����_���œ������J�n����
			if(!(::rand() % scg_nMidBoss1EscapeRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_35)
				this->m_nEscapeRangeCnt = ::rand() % this->scm_nEscapeRange;
				this->m_eAction = ENEMY_ACT_ESCAPE;
				break;
			}
		}
		//�U���͈͊O
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_36)
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//�U����
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
				//����U����͑ҋ@�ɖ߂�
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_39)
				this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_1:
				//�ʏ�U��2�i��
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_40)
				if(scg_bMidBoss1Attack2Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nMidBoss1Attack2Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_2:
				//�ʏ�U��3�i��
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_41)
				if(scg_bMidBoss1Attack3Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nMidBoss1Attack3Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			default:
				//�W�����v�U���͎��O�ɃW�����v����
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_42)
				if(!(::rand() % scg_nMidBoss1JumpAttackRatio[GameManager::getInstance()->getRank()]))
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_43)
					button_B = true;
					break;
				}
				//���Ⴊ�ݍU��
				if(!(::rand() % scg_nMidBoss1SquatAttackRatio[GameManager::getInstance()->getRank()]))
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_44)
					Down = true;
				}

				//�ʏ�U��1�i��
				button_A = true;

				break;
			}

			//Player���W����ł���΁A�΋�U��������
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

	//�h��
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

	//���Ⴊ�݃K�[�h
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

	//���Ⴊ��
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

    // ���S (���S���[�V������) �͓��͂��󂯕t���Ȃ�
    if ( isDead() )
    {
        __DtTestPoint( __DtFunc_UpdateSelf, __DtStep_57 )
        return true;
    }

    // �ړ��ł���ꍇ (�̂����蒆���ł͂Ȃ�)
    if ( mStunFrame == 0 )
    {
        //------------------------------------------------------
        // �U�����쒆�̏ꍇ
        __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_58)
        if ( isAttacking() )
        {
			// �s�����������i=�o���I���j���ĂȂ��Ƒ���s��
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_59)
			if ( !mAttackLocked )
			{
				// �A���U��
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_60)
				if ( button_A )
				{
					// �s������
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
						// �����ꂨ�������l�ɂȂ����烍�b�N����
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_64)
						this->AttackUnLock();
						break;
					}
				}
			}
        }
        //------------------------------------------------------
        // �U�����쒆�ł͂Ȃ��ꍇ
        else
        {
			
			// �U���J�n
            __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_65)
            if ( button_A && m_eCharaState != EV_ACTION_ATTACK_1 )  // ���͉̂�
            {
                // �W�����v���̏ꍇ
                __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_66)
                if ( mJump )
                {
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_67)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_JUMP_ATTACK, NULL, 0 );
                }
                // ���Ⴊ�ݒ��̏ꍇ
                else if ( Down )
                {
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_68)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_SQUAT_ATTACK, NULL, 0 );
                }
				// ��������Ȃ���̏ꍇ
				else if ( !mTouchLadder && Up )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_69)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_ANTIAIR_ATTACK, NULL, 0 );
					this->m_nAttackDelay = 0;
				}
                // �ȏ�ȊO�͒ʏ�U��
                else
                {
					// �U���̂��ߍs������
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

			// �K�[�h
			if ( !Down && Guard && mOnGround && !mClimbLadder && m_eCharaState != CHARASTATE_GUARD )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_73)
				getManager()->postEvent( getHandle(), EV_ACTION_GUARD, NULL, 0 );
				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_74 )
				return true;
			}

			// ������ς��邽�߂̏���
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

			// �E�ړ�
			//if ( !mClimbLadder && right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
			//{
			//	// ���������� EV_ACTION_RUN �C�x���g�𑗂�B
			//	// ���̂��ƁAHandleEvent() �Ŏ��ۂɈړ����J�n����B
			//	// ���̃C�x���g�̓L���[�C���O�����A������ HandleEvent() �ɑ�����B
			//	//u32 dir = CHARADIR_RIGHT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		// getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}
			//// ���ړ�
			//else if( !mClimbLadder && left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) )
			//{
			//	//u32 dir = CHARADIR_LEFT;

			// �ړ�
			if ( ( !Guard && !this->mClimbLadder && right && !left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
				|| ( !Guard && !this->mClimbLadder && left && !right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) ) )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_77)
				if ( !Down )
					getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			}
			// ���E�̂������������Ă��Ȃ��ꍇ�͑ҋ@�ɂ���
			// ��q�������Ƃ����ҋ@�ŁB
			// (���� mState != CHARASTATE_WAIT �́A�ҋ@���ɘA���ŃC�x���g�������Ȃ��悤�ɂ��邽�߂ɕK�v)
			else if ( ( !Guard && this->mOnGround && ( ( !right && !left ) || ( right && left ) ) && !Down && !this->mClimbLadder && m_eCharaState != CHARASTATE_WAIT )
				|| this->mNewTouchObj != OBJ_LADDER && this->mOldTouchObj == OBJ_LADDER && m_eCharaState != CHARASTATE_WAIT && m_eCharaState != CHARASTATE_JUMP && m_eCharaState != CHARASTATE_RUN )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_78)
				getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
			}

			// �W�����v�J�n
			if ( button_B && m_eCharaState != CHARASTATE_JUMP && ( this->mOnGround || this->mClimbLadder ) )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_79)
				getManager()->postEvent( getHandle(), EV_ACTION_JUMP, NULL, 0 );
				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_80 )
				return true;
			}

			// ���Ⴊ�݊J�n
			if ( Down && this->mOnGround && !this->mTouchLadder )
			{
				// ���Ⴊ�݂Ȃ���K�[�h�����ꍇ
				// �K�[�h���Ȃ��炵�Ⴊ�񂾏ꍇ
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

			// �͂�������
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

			// �͂����㏸
			if ( Up && m_eCharaState != CHARASTATE_LADDER_UP && mClimbLadder )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_86)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_UP, NULL, 0 );

				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_87 )
				return true;
			}
			// �͂������~
			else if ( Down && m_eCharaState != CHARASTATE_LADDER_DOWN && mClimbLadder )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_88)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_DOWN, NULL, 0 );

				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_89 )
				return true;
			}
			// �͂����ҋ@
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

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int MidBoss1::HandleEvent(u32 event_,void *args_)
{
	///////////////////////////////////////// �퓬�s�\�J�n
	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	switch ( event_ )
	{
        case EV_ACTION_START_DEAD:
			//�o���l�̏���
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

	�v���C���[�̒T�����s��

	@return         bool
	- true  �͈͓�
	- false �͈͊O
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
		//�T���͈͓��ł���
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

	�U���͈͒T�����s��

	@return         bool
	- true  �͈͓�
	- false �͈͊O
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
		//�U���͈͓�
		__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_2)
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) <= r->x + r->w - 40) //40�͈ꎞ�I
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
