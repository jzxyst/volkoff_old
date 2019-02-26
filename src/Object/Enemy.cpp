//=============================================================================
/*! 
    @addtogroup 
    @file       Enemy.cpp
    @brief      
    
    �L�����N�^�[�N���X�̎���
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/11/07
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/07 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Enemy.h"	/* For DynamicTracer-TestPoint */
#include "Enemy.h"
#include "Player.h"
#include "./Item/Cure_S.h"
#include "./Item/Cure_M.h"
#include "./Item/Cure_L.h"
#include "./../Game/GameManager.h"

static const char* gEnemyRandomNames[] =
{
    "K.Yamamoto",
    "S.Mizuno",
    "T.Matsui",
    "K.Hosoda",

    "Kouhei",
    "Takuya",
    "Hiroki",
    "Satoru",
	////////
	"vellfire",
	"Valfarle",
	"Velfirle",
	"VilFarle",
	"Valfire",
	"Varforle",
	"Walfirle",
	"Volfire",
    "WARST",
    "unsigned",
	"Tolman",
	"Oppenheimer",
	"Abdul",
	"Corleone",
	"Al Pacino",
	"James",
	"Robin",
	"Bond",
	"Regan",
	"Damien",
	"Vincent",
	"Joe",
	"Frank",
	"Albert",
	"Thomas",
	"Paul",
	"Marcello",
	"Carlos",
	"Silvio",
	"Roberto",
	"Jimmy",
	"Edison",
	"C6H2CH3(NO2)3",
	"H2SO4",
	"VEGA",
	"KCN",
	"Lucky Luciano",
	"Salvatore",
	"Giovanni",
	"Bernardo",
	"Vito",
	"Al Capone"
	"Terminator",
	"Mad Max",
	"HUMAN GAS",
	"gyro",
	"Sentinel",
	"Rotterdam",
	"Tom",
	"Frederico",
	"Jason",
	"Freddy",
	"Predator",
	"SpiderMa",
	"Hannibal",
	"Jack",
	"Claude",
	"Debussy",
	"Nordstrom",
	"Lee",
	"Andre",
	"Great Andre",
	"Reissner",
	"Kami - Kaze",
	"Geisya",
	"Ninja",
	"Harakiri",
	"Little Boy",
	"Invincible",
	"Fat Man",
	"Badguy",
    "����",
    "�y�J��",
    "��������",
	"xxx",
    "WARST",
	"smith",
	"ken",
	"kumi",
	"emiya",
	"�l��",
	"VTEC",
	"Lethal Weapon",//�M���M��
	"TAKAHASHI",
	"New Yorker",
	"Human Rocket",
	"�O���}�[����",
	"�ŋ��̐땺",
	"�����Y",
	"��g",
	"�t�g",
	"�͘Z",
	"����",
	"�Ђ���",
	"�ۂ񂱂�",
	"�Ƃ񂱂�",
	"�Ȃ񂱂�",
	"�݂�т����",
	"��������",
	"����",
	"���u�j",
	"���u�Y",
	"���u��",
	"���u�q",
	"������]",
	" ]-[!35_#! ",
	"K99999",
	"k,",
	"���ǂ�",
	"���[����",
	"��`����",
	"�L��S��",
	"���񕔈�",
	"�q�ɔ�",
	"�N����",
	"���c���Y",
	"�ɐ��肾�낤",
	"�����̃J�J�g",
	"�����r�ԕ�",
	"�r�ꋶ�����",
	"��������n",
	"���̂�����",
	"���͓I�ȍ��z",
	"�키�s��",
	"������F",
	"���h�S",
	"�ږ��",
	"�Í�����",
	"�މ�V�N",
	"�퓬����",
	"�ŏI�h�q��",
	"�ŋ��`��",
	"�c�s���l",
	"���G���l",
	"���s���l",
	"���_",
	"��Ŋ뜜��",
	"�������R��",
	"�S���͎��P��",
	"9��ړŖ���",
	"�������I",
	"�G��",
	"�A����",
	"���N��",
	"�l�ԋ���",
	"�S�g�ؓ�",
	"����",
	"�e�����X�g",
	"�h�q",
	"�O��",
	"�����[",
	"�`���s��",
	"�S�C��",
	"�s��",
	"�U�R�L����",
	"���N�⌇",
	"FBI",
	"UMA",
	"KGB",
	"CIA",
	"LV 5",
	"LV 100",
	"�퓬�͂T",
	"�퓬��1200",
	"�퓬��4000",
	"�퓬��53��",
	"IQ 106 4�n��",
	"IQ 80",
	"IQ 200",
	"IQ 13��",
	"IQ 1��3��",
	"2012�N",
	"007",
	"????",
	"���̕s��",
	"Algernon",
	"ash",
	"Fender",
	"Strat",
	"Swinger",
	"Telecaster",
	"Speed Freak",
	"����",
	"Magneto",
	"Klaus",
	"Kinkel",
	"DENON",
	"flanger",
	"Wesson",
	"Henrietta",
	"Marian",
	"������F",
	"Charles",
	"���I���e��",
	"199X�N",
	"��Y",
	"��Y",
	"�O�Y",
	"�l�N",
	"�ܘY",
	"�Z�Y",
	"���Y",
	"���Y",
	"��Y",
	"�\�Y",
	"�\��Y",
	"Howard",
	"Cessna",
	"Megadeth",
	"Anthrax",
	"Leazas",
	"Calvin",
	"Klein",
	"Habmann",
	"CATOREX",
	"Kesselring"
	"Svend",
	"Andersen",
	"Philippe",
	"Graham",
	"edmundo",
	"���ώ��",
	"�s���s��",
	"���l�Y",
	"����",
	"���@",
	"AKG",
	".exe",
	".rar",
	".zip",
	".lzh",
	".png",
	".jpg",
	".wav",
	".frac",
	".tak",
	".dat",
	"Michelangelo",
	"�n���̖��",
	"19990707",
	"Kaspersky",
	"Norton",
	"Angolmois",
	"Samoen",
	"Butcher",
	"Blackwell",
	"Gibson",
	"Rickenbacker",
	"Pfeifer",
	"Zeliska",
	"Pylon",
	"Gates",
	"Jobs",
	"netero",
	"Hartmann",
	"Alfred",
	"Giaccho",
	"Abbacchio",
	"�k����",
	"Fatalpulse",
	"�ɍʐF",
	"Black Ace",
	"Magento",
	"Reno",
	"ide",
	"curse",
	"Stroheim",
	"Emmerich",
	"�����̒鉤",
	"Noah",
	"Brocken",
	"Magento",
	"Ferdinand",
	"Hans",
	"Friedrich",
	"Ernst",
	"Richthofen",
	"Gotthard",
	"���G�^�C�̒鉤",
	"��������̎h�q",
	"Heinrich",
	"Marseille",
	"�H��",
	"Edvard",
	"Walter",
	"Barbarossa",
	"�V�l�̔���",
	"�_�l�̔���",
	"�^�_�̔���",
	"�q�B�b�c",
	"�Ռ���",
	"���s�_�b",
	"�������̑V�g��",
	"�V��V��",
	"���S����",
	"���������a",
	"OI�EOIO",
	"�W���b�N�n���}�[",
	"��",
	"�C��",
	"�M",
	"�����`��",
	"���Ђ�",
	"�k���",
	"���A�a",
	"�ጌ��",
	"���̎��",
	"�B�l��",
	"�Ǌ�̕��Q�S",
	"�b��z�O",
	"�b���z�O",
	"�Í��X�̎x�z��",
	"�_�j�[",
	"�O���b�O",
	"�����j�[�g",
	"�\���΍�",
	"�ϑz�΍�",
	"�����ɂ߂�����",
	"SG�X�~�j�[",
	"����YES",
	"�C�N�V�I��",
	"AX-2",
	"���r�J���t�[",
	"���ԃM���`��",
	"�]����13��",
	"��",
	"�ܒܗ�",
	"�ϐl",
	"���������t",
	"�ۑ�����",
	"���D�ݏĂ�",
	"Hello world",
	"凋C�O",
	"TAO",
	"����̂䂤����",
	"���S�ʒm",
	"���S�V�Y",
	"�_�~�[�������",
	"�E�т��e",
	"���肭�鋰�|",
	"������郂�m",
    /*
    �[�[�[�[�[�[�[�[ ���S�p8����
    ����𔄂�R�{
    */

    "�����",  // �l�Ɛl�Ƃ́A�݂��ɋC�S����������Ȃ����Ƃ����邪�A����͕s�v�c�ȉ��ɂ����̂��Ƃ������ƁB
    "���ʗ���",  // �e�q�E�Z��E�v�w�����ʁE���ʂ���A���̋ꂵ�݂�߂��݁B
    "�B���͌�",  // ���Ԃ��͂����肹���A�悭������Ȃ����܁B
    "�F�f��",  // �����S�z���ł������肵�ċꂵ�����ɓf�����ߑ��B
    "���f��",
    "���߈��H",  // �e���Ȉߕ��Ƒe���ȐH�ו��B�ߐH�̕n�����ȂǁA�O�ʓI�Ȃ��̂ɐS��D���Ă͂Ȃ�Ȃ��B
    "��������",  // �����s���⌴���ɂ́A���Ȃ炸�����񂢂⌋�ʂ�����B
    "���t����",  // �l���⓹���ɊO�ꂽ�A�Ђǂ��������s�����ƁB
    "�����痢",  // �������Ƃ͐痢�̔ޕ��ɂ܂Œm��n���Ă��܂����ƁB
    "����ꓬ",  // ����ɒ��ʂ��Ȃ���A���ɕ������̋ꂵ���w�͂�������A������肷�邱�ƁB
    "���@����",  // �����̐l���A�ߎS�ȏ󋵂̉��ŁA�ꂵ�񂾂苃�����񂾂肵�ċ~�������߂邳�܁B
    "�^�䚄",  // ���ɗ����ʋc�_��A���e�̂Ȃ����͂̂��Ƃ��B
    "��懒Ǐ]",  // ����ɋC�ɓ����悤�Ƃ��āA���ׂ����������Ăւ炤���ƁB
    "�É_���",  // ���ɂ��댯��j�ǂ��N���肻���ȕs���Ȃ��܁B
    "���՜���",  // �������Ȃ����炩�ŁA�Â��Ȃ��ƁB���~�ŗ��������Ă�����̋��n�B
    "�����y��",  // ���̒������a�ŁA�l�X�̐��������肵�A�y�����d���ɗ��ł����ԁB
    "�Ò��͍�",  // �肪����̂Ȃ��������A���낢��ƍl���āA�T���Ă���Ă݂邱�ƁB
    "���J����",  // ���̒������₩�Ɏ��܂�A���S�ƒ�����������ƕۂ���Ă��邱�ƁB

    "�j�����O����b",  // �^�C�̊O����b
    "�o�J�c��",         // �o�J�E�f�B�G�X�c���B�{���r�A�̏�@�c��
    "�q�b�L�[�卲",   // �W�F�C���Y�E�q�b�L�[�卲�B�A�����J��S�����t�c�E��P���c�i�ߊ��B
    "�X�g���[�O��",   // �W���b�N�E�X�g���[�B�C�M���X�̊O��
    "�T����",         // �Z�l�K���̎�
    "������ް�",        // �ČR�����Q�d�{����핛����
    "�x���i��",         // �J�����X�E�t�B���y�E�V���l�X�E�x���B���e�B���[���̎i��
    "��������ȋZ��",       // �X���x�j�A���a���̉ȋZ��
    "�N�[�����哝��",     // �X���x�j�A���a���̑哝��
    "�h���S�j���o�ϑ�",     // �X���x�j�A���a���̌o�ϑ�
    "�V���x�^�O������",     // �{�X�j�A�E�w���c�F�S�r�i�̊O������
    "�J���r�[�O��",       // �C�G�����̊O��
    "ϯ�����ƌo�ϑ�",  // �I�}�[�����̍��ƌo�ϑ�
    "�A�z�J�X��g",       // ���B�����E�A�z�J�X�B�t�B�������h�̑�g�B
    "�`�����E�V�l",       // �؍����v���̎Љ�v�ǒ�
    "�A�_���E�j�[�g",      // �C�M���X�̃A�[�e�B�X�g
    "�ۂ��ێ�",      // 
    "�R�b�R�ɑ�",      // 

    "�d���̋�",
    "������",
    "�N�z��",
    "�ܗk�}",
    "��������",
    "��������",
    "�����x�ő������@",
    "�����w��",
    "�V����",
    "�����x�V����",
    "���䑕�u",
    "�ܐ؂��p��",
    "�u���̊Ǘ���",

    "�K������I",
    "�悢��I",
    "��������I",
    "��H���܂�",
    "�Q���Ⴄ�[",
    "�A�肽���c",

    "�Ȃ���",
    "�ӂ݂��",

    "�A�i�i�X",
    "�A�}�]�����",
    "�A���G",
    "�u�h�E����",
    "����",
    "�ۗ�",

    "�����ʓ�",
    "���Ȃ��F��",
    "���`������",
    "���̓��̋L��",
    "����Ȃ���",
    "�u���Ă������z",
    "�̑�Ȃ鉴",


    /*
    �[�[�[�[�[�[�[�[ ���S�p8����
    �O�p�ؔn�̐΍�
    */
    

    "-���̕�����-",
    "-�����̉~��-",
    "-�����̞g-",
    "-�I���̍�-",

	"�O������",
	"�O������",
	"�O�����",
	"�G�[�J�Q���Q��",
	"�N�\�X���[�^",
	"�������X�L�[",
	"��O�� �[��",
	"�ɘH�� ���",
	"���[�l���H�c",

	"�Ҍ��I",
	"�ʓV�C",
	"����A�C",
	"�֏o��",
	"�֌`����",
	"���q����",
	"�嗴�`",
	"��|��",
	"�~��",
	"�W�q����",
	"�P�c",
	"�Ў�",
	"�֝���",
	"�w��",
	"��@��",
	"����",
	"��Z���x",
	"�W�q�r�V",
	"��ԓW��",
	"����",
	"�n�`�Z�{",
	"�n�`���a",
	"�œ˘A��",
	"�œˋ��c",
	"�V��r",
	"���n��",
	"���ވ���r",
	"��g��|��",
	"�ώ�r",
	"�v�r�O�|���",
	"�r���o�c",
	"�r���o�c�k",
	"��ɐ���",
	"���L�R",
	"����",
	"��g�Ց�",
	"����r",
	"�G������",
	"�o�c",
	"��n�z��",
	"�\�{��",
	"�Ֆo�c",
	"�W�q������",
	"����",
	"���_�I",
	"��k�r",
	"��k��",
	"�⏵�ʓV�C",
	"�⏵�鑨�c",
	"��|���P�r",
	"���e��",
	"�}��l�c��",
	"�E�����",
	"���g�o�ʏ�",
	"����C",
	"���q�����c",
	"�՗z��",
	"�|��",
	"��n菑�",



    
};

// gEnemyRandomNames �̐�
static const int ENEMY_RAND_NAME_MAX = sizeof( gEnemyRandomNames ) / sizeof( gEnemyRandomNames[ 0 ] );


//---------------------------------------------------------------------------
// �� �I�u�W�F�N�g���쐬����
//---------------------------------------------------------------------------
Enemy* Enemy::create( void* args_, bool is_entity_ )
{
    Enemy* o = NEW Enemy();
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
Enemy* Enemy::createRandom()
{
    Enemy::CreateData data;
    __DtTestPoint( __DtFunc_createRandom, __DtStep_0 )
    data.Position = LVector3(0,0,0);
    data.WeaponLevel = 1;
    data.WeaponType  = Weapon::getRandWeaponID();
    /*
	data.WeaponType = WEAPON_NON;
	for(int i = 0;i < WEAPON_MAX_NUM;++i)
	{
		if(!(::rand() % gWeaponBaseData[i].Rate))
		{
			data.WeaponType = static_cast<WeaponType>(i);
			break;
		}
	}

	data.WeaponType = static_cast<WeaponType>(::rand() % WEAPON_NORMAL_MAX_NUM);
	//data.WeaponType = WEAPON_KATANA;
    */

	Enemy* pEnemy = Enemy::create( &data );

    __DtTestPoint( __DtFunc_createRandom, __DtStep_1 )
    return pEnemy;
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::Enemy

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Enemy::Enemy()
    : mWeaponLevel  ( 1 )
{
	
	__DtTestPoint( __DtFunc_Enemy, __DtStep_0 )
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
	this->mStandOnObject = false;

    // �U���ΏۃO���[�v�͓G��
    setAttackedGroup( ATKGROUP_ENEMY );
	__DtTestPoint( __DtFunc_Enemy, __DtStep_1 )
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
Enemy::~Enemy()
{
	__DtTestPoint( __DtFunc_Enemy, __DtStep_2 )
	this->Release();
	__DtTestPoint( __DtFunc_Enemy, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Enemy::Initialize( const CreateData& data_ )
{
    __DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
    this->m_pszName = gEnemyRandomNames[ rand() % ENEMY_RAND_NAME_MAX ]; // �����_����
	this->mScore = 100;
	this->mExp = 10;
    this->mPosition = data_.Position;
    this->mVelocity = data_.Velocity;
    mWeaponLevel    = data_.WeaponLevel;
    
	bool r = Character::Initialize();
	this->mCharaPanel.setColorScale(0.5f,0.5f,0.5f);

    
	this->mLife = this->mMaxLife = scg_nLife[GameManager::getInstance()->getRank()];

	this->m_nRandAttackRange = ::rand() % 40 - 20;
	this->m_nRandAttackDelay = ::rand() % 40 - 10;
	this->m_nRandSearchRange = this->scm_nSearchX;
	this->m_nAttackRangeRand = ::rand() % this->scm_nAttackRangeRand;

	WeaponData data;
	data.UseCount = -1;
	data.WeaponType =  static_cast<WeaponType>(data_.WeaponType);
	this->changeWeapon(data);

	this->mStandOnObject = false;


	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return r;
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Enemy::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //delete��Manager�ɔC����

	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Enemy::Update()
{
	//_p(mOnGround);
	//_p(mClimbLadder);
	//_p(this->mStandOnObject);

    __DtTestPoint( __DtFunc_Update, __DtStep_0 )
    return Character::Update();
}

//---------------------------------------------------------------------------
// �� �t���[���X�V���� (�I�u�W�F�N�g�ɉe����^���鏈��)
//---------------------------------------------------------------------------
bool Enemy::UpdateSelf()
{
	//���񂾍ۂɎ����Ă��镐��𗎂Ƃ�
	__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_0 )
	if(this->mLife <= 0 && !this->m_bCreateWeapon)
	{
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_1)
		if(this->mWeaponData.WeaponType)
		{
			Weapon::CreateData wdata;

			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_2)
			wdata.Data.WeaponType  = this->mWeaponData.WeaponType;
			wdata.Data.UseCount    = gWeaponBaseData[this->mWeaponData.WeaponType].UseCount;

			LVector3 v = this->mPosition;
			v.x -= 25;
			v.y += 80;
			wdata.Position = v;
			Weapon::create( &wdata );

			this->m_bCreateWeapon = true;
		}
		else
		{
			//�f��̏ꍇ�A��m���ŉ񕜃A�C�e���𗎂Ƃ�
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_3)
			if(!(::rand() % 10))
			{
				Cure_S *pCure = new Cure_S();
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_4)
				pCure->Initialize();

				LVector3 v = this->mPosition;
				v.x -= 30;
				v.y += 100;

				pCure->setPosition(v);
			}
			this->m_bCreateWeapon = true;
		}
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
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_5)
		this->m_eAction = ENEMY_ACT_WAIT;
		break;

	//�ҋ@
	case ENEMY_ACT_WAIT:
		//�͈͓��T�����s��
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_6)
		if(this->SearchPlayer())
		{
			//�͈͓��ł���ΒǐՂ��J�n����
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_7)
			this->m_eAction = ENEMY_ACT_CHASE;
			break;
		}

		//�U�����J�n����
		if(this->m_nWalkIntvCnt > this->scm_nWalkIntv)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_8)
			this->m_nWalkRangeCnt = ::rand() % this->scm_nWalkRange; //�U�������̐ݒ�
			this->m_nWalkIntvCnt = 0;
			this->m_bWalkDir = static_cast<bool>(::rand() % 2);
			this->m_eAction = ENEMY_ACT_WALK;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_9)
			++this->m_nWalkIntvCnt;
		}
		break;

	//�U��
	case ENEMY_ACT_WALK:
		//�U�����s���Ă���
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_10)
		if(this->m_nWalkRangeCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_11)
			if(this->m_bWalkDir)
				right = true;
			else
				left = true;

			--this->m_nWalkRangeCnt;
		}
		//�U���I���
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_12)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//�ǐ�
	case ENEMY_ACT_CHASE:
		//�v���C���[���T���͈͓��ł���
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_13)
		if(this->SearchPlayer())
		{
			//Player�͉E�ɂ���
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_14)
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_15)
				right = true;
			}
			//Player�͍��ɂ���
			else
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_16)
				left = true;
			}

			//�܂�ɃW�����v����
			if(!(::rand() % scg_nJumpRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_17)
				button_B = true;
			}

			//�v���C���[���ώ@�͈͓��ł���
			if(::abs(this->mPosition.x + ::rand() % this->scm_nSearchRand - pPlayer->getPosition().x) <= this->scm_nStandbyRange)
			{
				//�����_���Ŋώ@���J�n����
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_18)
				if(!(::rand() % scg_nStandbyRatio[GameManager::getInstance()->getRank()]))
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_19)
					this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
					this->m_eAction = ENEMY_ACT_STANDBY;
					break;
				}
			}

			//�v���C���[���U���͈͓��ł���
			if(this->SearchAttack1Range())
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_20)
				this->m_eAction = ENEMY_ACT_ATTACK_RANGE;
				break;
			}
		}
		else
		{
			//�T���͈͊O�ł���Αҋ@�ɖ߂�
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_21)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//�ώ@
	case ENEMY_ACT_STANDBY:
		//�v���C���[���W�����v�����u�ԑ΋�U�����s��
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_22)
		if(pPlayer->getCharaState() == CHARASTATE_JUMP)
		{
			//this->m_nStandbyCnt = 0;
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_23)
			break;
		}

		//�ώ@���s��
		if(this->m_nStandbyCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_24)
			--this->m_nStandbyCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_25)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//����
	case ENEMY_ACT_ESCAPE:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_26)
		if(this->m_nEscapeRangeCnt)
		{
			//Player�͉E�ɂ���
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_27)
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_28)
				left = true;
			}
			//Player�͍��ɂ���
			else
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_29)
				right = true;
			}

			--this->m_nEscapeRangeCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_30)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//�U���͈͓�
	case ENEMY_ACT_ATTACK_RANGE:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_31)
		if(this->SearchAttack1Range())
		{
			//�����_���ōU�����J�n����
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_32)
			if(!(::rand() % scg_nAttackRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_33)
				this->m_eAction = ENEMY_ACT_ATTACK;
				break;
			}
			//�����_���Ŗh����J�n����
			if(!(::rand() % scg_nGuardRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_34)
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_GUARD;
				break;
			}
			//�����_���Ŋώ@���J�n����
			if(!(::rand() % scg_nStandbyRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_35)
				this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_STANDBY;
				break;
			}
			//�����_���ł��Ⴊ�݃K�[�h���J�n����
			if(!(::rand() % scg_nSquatGuardRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_36)
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_SQUAT_GUARD;
				break;
			}
			//�����_���ł��Ⴊ�݂��J�n����
			if(!(::rand() % scg_nSquatRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_37)
				this->m_nSquatCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_SQUAT;
				break;
			}
			//�����_���œ������J�n����
			if(!(::rand() % scg_nEscapeRatio[GameManager::getInstance()->getRank()]))
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_38)
				this->m_nEscapeRangeCnt = ::rand() % this->scm_nEscapeRange;
				this->m_eAction = ENEMY_ACT_ESCAPE;
				break;
			}
		}
		//�U���͈͊O
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_39)
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//�U����
	case ENEMY_ACT_ATTACK:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_40)
		if(this->SearchAttack1Range())
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_41)
			switch(this->m_eCharaState)
			{
			case CHARASTATE_ATTACK_SQUAT_ATTACK:
			case CHARASTATE_ATTACK_JUMP_ATTACK:
			case CHARASTATE_ATTACK_ANTIAIR_ATTACK:
			case CHARASTATE_ATTACK_DUSH_ATTACK:
				//����U����͑ҋ@�ɖ߂�
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_42)
				this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_1:
				//�ʏ�U��2�i��
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_43)
				if(scg_bAttack2Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nAttack2Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_2:
				//�ʏ�U��3�i��
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_44)
				if(scg_bAttack3Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nAttack3Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			default:
				//�W�����v�U���͎��O�ɃW�����v����
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_45)
				if(!(::rand() % scg_nJumpAttackRatio[GameManager::getInstance()->getRank()]))
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_46)
					button_B = true;
					break;
				}
				//���Ⴊ�ݍU��
				if(!(::rand() % scg_nSquatAttackRatio[GameManager::getInstance()->getRank()]))
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_47)
					Down = true;
				}

				//�ʏ�U��1�i��
				button_A = true;

				break;
			}

			//Player���W����ł���΁A�΋�U��������
			if(this->mPosition.y < pPlayer->getPosition().y)
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_48)
				Up = true;
			}
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_49)
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//�h��
	case ENEMY_ACT_GUARD:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_50)
		if(this->m_nGuardCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_51)
			Guard = true;
			--this->m_nGuardCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_52)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//���Ⴊ�݃K�[�h
	case ENEMY_ACT_SQUAT_GUARD:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_53)
		if(this->m_nGuardCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_54)
			GuardTrigger = true;
			Guard = true;
			Down = true;
			--this->m_nGuardCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_55)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//���Ⴊ��
	case ENEMY_ACT_SQUAT:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_56)
		if(this->m_nSquatCnt)
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_57)
			Down = true;
			--this->m_nSquatCnt;
		}
		else
		{
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_58)
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	default:
		__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_59)
		this->m_eAction = ENEMY_ACT_WAIT;
		break;
	}
	//AI end

    // ���S (���S���[�V������) �͓��͂��󂯕t���Ȃ�
    if ( isDead() )
    {
        __DtTestPoint( __DtFunc_UpdateSelf, __DtStep_60 )
        return true;
    }

    // �ړ��ł���ꍇ (�̂����蒆���ł͂Ȃ�)
    if ( mStunFrame == 0 )
    {
        //------------------------------------------------------
        // �U�����쒆�̏ꍇ
        __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_61)
        if ( isAttacking() )
        {
			// �s�����������i=�o���I���j���ĂȂ��Ƒ���s��
			__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_62)
			if ( !mAttackLocked )
			{
				// �A���U��
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_63)
				if ( button_A )
				{
					// �s������
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_64)
					this->AttackLock();

					switch( m_eCharaState )
					{
					case CHARASTATE_ATTACK_1:
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_65)
						if(scg_bAttack2Permission[GameManager::getInstance()->getRank()])
							getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_2, NULL, 0 );
						break;

					case CHARASTATE_ATTACK_2:
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_66)
						if(scg_bAttack3Permission[GameManager::getInstance()->getRank()])
							getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_3, NULL, 0 );
						break;

					default:
						// �����ꂨ�������l�ɂȂ����烍�b�N����
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_67)
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
            __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_68)
            if ( button_A && m_eCharaState != EV_ACTION_ATTACK_1 )  // ���͉̂�
            {
                // �W�����v���̏ꍇ
                __DtTestPoint(__DtFunc_UpdateSelf, __DtStep_69)
                if ( mJump )
                {
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_70)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_JUMP_ATTACK, NULL, 0 );
                }
                // ���Ⴊ�ݒ��̏ꍇ
                else if ( Down )
                {
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_71)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_SQUAT_ATTACK, NULL, 0 );
                }
				// ��������Ȃ���̏ꍇ
				else if ( !mTouchLadder && Up )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_72)
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_ANTIAIR_ATTACK, NULL, 0 );
					this->m_nAttackDelay = 0;
				}
                // �ȏ�ȊO�͒ʏ�U��
                else
                {
					// �U���̂��ߍs������
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_73)
					if(scg_bAttack1Permission[GameManager::getInstance()->getRank()])
					{
						__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_74)
						this->AttackLock();
						getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_1, NULL, 0 );
					}
                }

                __DtTestPoint( __DtFunc_UpdateSelf, __DtStep_75 )
                return true;
            }

			// �K�[�h
			if ( !Down && Guard && mOnGround && !mClimbLadder && m_eCharaState != CHARASTATE_GUARD )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_76)
				getManager()->postEvent( getHandle(), EV_ACTION_GUARD, NULL, 0 );
				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_77 )
				return true;
			}

			// ������ς��邽�߂̏���
			if ( right )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_78)
				setDirection( CHARADIR_RIGHT );
			}
			else if ( left )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_79)
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
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_80)
				if ( !Down )
					getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			}
			// ���E�̂������������Ă��Ȃ��ꍇ�͑ҋ@�ɂ���
			// ��q�������Ƃ����ҋ@�ŁB
			// (���� mState != CHARASTATE_WAIT �́A�ҋ@���ɘA���ŃC�x���g�������Ȃ��悤�ɂ��邽�߂ɕK�v)
			else if ( ( !Guard && this->mOnGround && ( ( !right && !left ) || ( right && left ) ) && !Down && !this->mClimbLadder && m_eCharaState != CHARASTATE_WAIT )
				|| this->mNewTouchObj != OBJ_LADDER && this->mOldTouchObj == OBJ_LADDER && m_eCharaState != CHARASTATE_WAIT && m_eCharaState != CHARASTATE_JUMP && m_eCharaState != CHARASTATE_RUN )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_81)
				getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
			}

			// �W�����v�J�n
			if ( button_B && m_eCharaState != CHARASTATE_JUMP && ( this->mOnGround || this->mClimbLadder ) )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_82)
				getManager()->postEvent( getHandle(), EV_ACTION_JUMP, NULL, 0 );
				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_83 )
				return true;
			}

			// ���Ⴊ�݊J�n
			if ( Down && this->mOnGround && !this->mTouchLadder )
			{
				// ���Ⴊ�݂Ȃ���K�[�h�����ꍇ
				// �K�[�h���Ȃ��炵�Ⴊ�񂾏ꍇ
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_84)
				if ( ( ( GuardTrigger ) || ( DownTrigger && Guard ) ) && m_eCharaState != CHARASTATE_SQGUARD )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_85)
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT_GUARD, NULL, 0 );
				}
				else if ( !Guard && m_eCharaState != CHARASTATE_SQUAT )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_86)
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

				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_87)
				if ( UpTrigger && mDistance.y > 0 )
					Catch = true;

				if ( DownTrigger && mDistance.y < 0 )
					Catch = true;

				if ( Catch )
				{
					__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_88)
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
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_89)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_UP, NULL, 0 );

				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_90 )
				return true;
			}
			// �͂������~
			else if ( Down && m_eCharaState != CHARASTATE_LADDER_DOWN && mClimbLadder )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_91)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_DOWN, NULL, 0 );

				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_92 )
				return true;
			}
			// �͂����ҋ@
			else if ( !Up && !Down && mClimbLadder && m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				__DtTestPoint(__DtFunc_UpdateSelf, __DtStep_93)
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_WAIT, NULL, 0 );

				__DtTestPoint( __DtFunc_UpdateSelf, __DtStep_94 )
				return true;
			}
        }
    }

    __DtTestPoint( __DtFunc_UpdateSelf, __DtStep_95 )
    return true;
}




//---------------------------------------------------------------------------
/*! 
	@brief Enemy::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Enemy::HandleEvent(u32 event_,void *args_)
{

	__DtTestPoint( __DtFunc_HandleEvent, __DtStep_0 )
	switch ( event_ )
	{
	///////////////////////////////////////// �퓬�s�\�J�n
        case EV_ACTION_START_DEAD:
			//�o���l�̏���
			__DtTestPoint(__DtFunc_HandleEvent, __DtStep_1)
			GameManager::getInstance()->getPlayer()->setExp(GameManager::getInstance()->getPlayer()->getExp()+this->mExp);
			//printf("exp%d\n",GameManager::getInstance()->getPlayer()->getExp());
			//�X�R�A�̏���
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
bool Enemy::SearchPlayer()
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
	@brief Enemy::SearchAttack1Range

	�U���͈͒T�����s��

	@return         bool
	- true  �͈͓�
	- false �͈͊O
	@exception      none
*/
//---------------------------------------------------------------------------
bool Enemy::SearchAttack1Range()
{
	bool bRes = false;
	LRect *r = NULL;
	Player *pPlayer = GameManager::getInstance()->getPlayer();

	__DtTestPoint( __DtFunc_SearchAttack1Range, __DtStep_0 )
	switch(this->mWeaponData.WeaponType)
	{
	case WEAPON_NON:
	case WEAPON_STICK:
	case WEAPON_KATANA:
	case WEAPON_UMBRELLA:
	case WEAPON_TAEKWONDO:
	case WEAPON_KNIFE:
	case WEAPON_GRENADE:
	case WEAPON_HAMMER:
	case WEAPON_BOSS_KATANA:
	case WEAPON_BOSS_TAEKWONDO:
	case WEAPON_BOSS_KNIFE:
		__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_1)
		for(int i = 6;i < 23;++i)
		{
			__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_2)
			r = this->mCollision->getAtkCollisionByIndex(i);

			if(r)
			{
				__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_3)
				break;
			}
		}
		break;

	case WEAPON_SHOTGUN:
	{
		LRect rect = LRect(0,0,210,60);
		__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_4)
		r = &rect;
		break;
	}

	default:
		__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_5)
		for(int i = 6;i < 23;++i)
		{
			__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_6)
			r = this->mCollision->getAtkCollisionByIndex(i);

			if(r)
			{
				__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_7)
				break;
			}
		}
		break;
	}

	if(r)
	{
		//�U���͈͓�
		__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_8)
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) <= r->x + r->w - 40 + this->m_nAttackRangeRand) //40�͈ꎞ�I
		{
			__DtTestPoint(__DtFunc_SearchAttack1Range, __DtStep_9)
			bRes = true;
		}
	}

	__DtTestPoint( __DtFunc_SearchAttack1Range, __DtStep_10 )
	return bRes;
}


/*

    �� �G�l�~�[AI

        �E���G���

            ���̕ӂ����낤�낵�Ă��鏉����ԁB
            �ȉ��̏����ōU����ԂɂȂ�B

                �E�v���C���[�L�����N�^�[�����G�͈͓��ɓ��� (���E���Ƃ��Ȃ猋�\�������������ǁA�Ƃ肠�����͉~��)
                �E�v���C���[�L�����N�^�[����̍U�����󂯂�
                �E�x�񑕒u����̌x�� (���b�Z�[�W�Ŏ󂯎��)

            �U����ԂɂȂ�Ƃ� (m_eCharaState �ɒl������Ƃ�) �ɁA
            �^�[�Q�b�g�ƂȂ�v���C���[�̃n���h����ێ����Ă���


        �E�U�����

            �����̎����Ă��镐��̗L���͈͓��Ƀ^�[�Q�b�g�����Ȃ��ꍇ�A
            �o�H�T���Ƃ�����Ȋ����̃��m���g���ă^�[�Q�b�g�ɋ߂Â��Ă����B

            �^�[�Q�b�g���L���͈͓��ɂ���ꍇ�͎���s����I�����čU�����s���B


            


*/


//=============================================================================
//								End of File
//=============================================================================
