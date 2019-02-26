//=============================================================================
/*! 
    @addtogroup 
    @file       Weapon.h
    @brief      �������
    
    �������̒�`
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/17
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/17 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_WEAPON_H__
#define __INCLUDE_WEAPON_H__


/*! @par include */
#include "./GameObject.h"


class GuideNamePlate;


/*! @enum WeaponType */
typedef enum _ENUM_WEAPON_TYPE
{
	WEAPON_NON = 0,     ///< �f��
	WEAPON_STICK,       ///< �_
	WEAPON_KATANA,
	WEAPON_UMBRELLA,
	WEAPON_TAEKWONDO,
	WEAPON_KNIFE,
	WEAPON_GRENADE,
	WEAPON_HAMMER,
	WEAPON_SHOTGUN,
	WEAPON_SCYTHE,
	
	WEAPON_BOSS_KATANA,
	WEAPON_BOSS_TAEKWONDO,
	WEAPON_BOSS_KNIFE,
	WEAPON_BOSS_SCYTHE,
	WEAPON_VALFIRLE,
	WEAPON_VALFIRLE_TOKEN,
    WEAPON_MAX_NUM,     ///< �����ނ̐� (�X�N���v�g�Ŏg���̂�)



	WEAPON_NORMAL_BEGIN = WEAPON_NON,
	WEAPON_NORMAL_END   = WEAPON_SCYTHE,


	WEAPON_BOSS_BEGIN = WEAPON_BOSS_KATANA,
	WEAPON_BOSS_END   =	WEAPON_BOSS_SCYTHE,

	WEAPON_NORMAL_MAX_NUM = ( WEAPON_NORMAL_END - WEAPON_NORMAL_BEGIN + 1 ),

	
    /*
    WEAPON_SWORD,       ///< ��
    WEAPON_BAT,         ///< �o�b�g
    WEAPON_HAMMER,      ///< �n���}�[
    WEAPON_KNIFE,       ///< �i�C�t

    WEAPON_HANDGUN,     ///< �n���h�K��
    WEAPON_SHOTGUN,     ///< �V���b�g�K��
    WEAPON_MACHINEGUN,  ///< �}�V���K��
    WEAPON_RIFLE,       ///< �Ε����C�t��
    WEAPON_GRENADE,     ///< ��֒e
    */
    

}WeaponType;

/// ����̖��O
static const char* gWeaponNames[] =
{
    "NONE",
    "Stick",
    "KATANA",
    "Umbrella",
    "Taekwondo",
    "Knife",
	"Grenade",
	"Hammer",
	"Shotgun",
	"Scythe",

    "Boss1",    // �ꉞ
    "Boss2"
};


/// ����f�[�^
struct WeaponData
{
    WeaponType  WeaponType;     ///< ����̎��
    int         UseCount;       ///< �c��g�p�� (-1 �Ŗ����Ƃ���B�f��Ƃ�)

    /// ���݂̕��탌�x���̎擾 (1�`3)
    u32 getLevel() const;

    /// �w�肵�����x���ɕK�v�Ȍo���l�̎擾
    //static u32 getLevelEXP( WeaponType type_, u32 level_ );
};


struct WeaponBaseData
{
    int     NecessaryExp[ 2 ];      ///< ���x��2�A3 �ɂȂ邽�߂ɕK�v�ȗ݌v�o���l
	int     UseCount;               ///< �g�p��
	int     Rate;                   ///< �o���p�x(Enemy)
	int     BoxRate;                ///< �o���p�x(Box)
};

/// ���했�̊�{�f�[�^
extern const WeaponBaseData gWeaponBaseData[ WEAPON_MAX_NUM ];


/// ����n���x�f�[�^ (����� getLevelData() �̖߂�l�B�����ɃC���^�[�t�F�C�X�֌W�Ŏg��)
//struct WeaponLevelData
//{
//    int         Level;          ///< ���x�� (1�`3)
//    int         Exp;            ///< �o���l (����ɂ���ĕς��)
//    int         NextExp;        ///< ���̃��x���܂ł̌o���l
//};


/*
    Weapon �N���X�́A������X�e�[�W��ɔz�u���邽�߂Ɏg���N���X�Ƃ���B
    Weapon �N���X�� Initialize() �� WeaponData ���󂯎���ă����o�ɕێ����A
    ���� WeaponType �ɂ���ĉ�ʂɕ\�����镐��C���[�W�����肷��B

    Weapon �{��(isEnttiy() �� true)�𐶐��ł���̂̓T�[�o�����B

    �������������ɂ��Ă����������A�uGameObject �� GameObject �̒��Ɏ�������v
    �Ƃ��Ȃ񂩕��G�Ȃ��ƂɂȂ�Ȃ��Ă悳�����ȋC������B
*/

/*! @class Weapon */
class Weapon : public GameObject
{
public:

    struct CreateData
    {
        WeaponData  Data;       ///< ����f�[�^
        LVector3    Position;   ///< �ʒu
    };

    //---------------------------------------------------------------------
    ///**
    //  @brief      �I�u�W�F�N�g���쐬����
    //
    //  @param[in]  args_ : CreateData �\���̂ւ̃|�C���^
    //
    //  @par
    //              Initialize() �͂��̒��ŌĂ΂��B�ʏ�Ais_entity_ �� true �ɂ��Ă������ƁB
    //*/
    //---------------------------------------------------------------------
    static Weapon* create( void* args_, bool is_entity_ = true );
	
    
    //---------------------------------------------------------------------
    ///**
    //  @brief      �S�Ă̕���̒����烉���_���ɕ���ID��Ԃ� (�o�������l�����Ă���)
    //
    //  @return     ������Ȃ������ꍇ��(���邯��)�f�蕐���Ԃ��B
    //*/
    //---------------------------------------------------------------------
    static int getRandWeaponID();

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
    virtual const char* getName() const {return gWeaponNames[ mWeaponData.WeaponType ];}

	virtual ObjectType getObjType() const { return OBJ_WEAPON; }
	
	const WeaponData& getWeaponData() const { return mWeaponData; }

    /// ���[���h���W��ԏ�ł̓����蔻���`��Ԃ�
	virtual const LRect* getBoundingRect();

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief Hoge */
	//---------------------------------------------------------------------------
	Weapon();

    virtual ~Weapon();


	virtual bool Initialize( const CreateData& data_ );

    /// �t���[���X�V
    virtual bool Update();

	virtual int HandleEvent(EventType event_,void *args_) { return 0; }

protected:

	WeaponData  mWeaponData;
    LBatchPanel      mPanel;

    GuideNamePlate*     mGuideNamePlate;    
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
