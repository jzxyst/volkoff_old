//=============================================================================
/*! 
    @addtogroup 
    @file       Weapon.cpp
    @brief      �������
    
    Weapon�w�b�_�̎���
    
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


/*! @par include */
#include "stdafx.h"
#include	"DT_Weapon.h"	/* For DynamicTracer-TestPoint */
#include "Weapon.h"
#include "../Map/MapManager.h"
#include "../Frontend/GuideNamePlate.h"


//=============================================================================
// �� WeaponData �֌W
//=============================================================================

const WeaponBaseData gWeaponBaseData[ WEAPON_MAX_NUM ] =
{
    // �f��
    { { 20, 30 }, -1, 100, 250 },

    // �_
    { { 20, 30 }, 30, 150, 100  },

    // ��
    { { 20, 30 }, 15, 50, 70 },
	//�P
    { { 20, 30 }, 20, 100, 40 },
	// �e�R���h�[
    { { 20, 30 }, 25, 150, 100 },
	// �i�C�t
    { { 20, 30 }, 40, 150, 100 },
	// �O���l�[�h
    { { 20, 30 }, 1, 10, 70 },
	// �n���}�[
    { { 20, 30 }, 20, 150, 100 },
	// �V���b�g�K��
    { { 20, 30 }, 7, 30, 70 },
	// ��
    { { 20, 30 },15, 35, 70 },

    // �{�X��
    { { 20, 30 }, 15, -1 ,0},

	//�{�X�e�R���h�[
    { { 20, 30 }, 15, -1 ,0},
	//�{�X�i�C�t
    { { 20, 30 }, 15, -1 ,0},
	//�{�X��
    { { 20, 30 }, 15, -1 ,0},

	//���@���t�@�[��
    { { 20, 30 }, 15, -1 ,0},
	//���@���t�@�[���g�[�N��
    { { 20, 30 }, 15, -1 ,0},
};

////---------------------------------------------------------------------------
//// �� �w�肵�����x���ɕK�v�Ȍo���l�̎擾
////---------------------------------------------------------------------------
//u32 WeaponData::getLevelEXP( WeaponType type_, u32 level_ )
//{
//    return gWeaponBaseData[ type_ ].NecessaryExp[ level_ ];
//}


//=============================================================================
// �� Weapon �N���X
//=============================================================================

//---------------------------------------------------------------------------
// �� �I�u�W�F�N�g���쐬����
//---------------------------------------------------------------------------
Weapon* Weapon::create( void* args_, bool is_entity_ )
{
    Weapon* o = NEW Weapon();
    __DtTestPoint( __DtFunc_create, __DtStep_0 )
    o->Initialize( *static_cast< CreateData* >( args_ ) );
    o->mIsEntity = is_entity_;

    // ���������̃z�X�g�ō쐬���ꂽ���̂ł���΁A�����ȊO�̃z�X�g�ɐ����������Ƃ𑗐M����
    if ( is_entity_ )
    {
        __DtTestPoint(__DtFunc_create, __DtStep_1)
        GameManager::getInstance()->getGameSession()->sendCreatedObjectEvent( OBJ_WEAPON, args_, sizeof( CreateData ) );
    }

    __DtTestPoint( __DtFunc_create, __DtStep_2 )
    return o;
}

//---------------------------------------------------------------------
// �� �S�Ă̕���̒����烉���_���ɕ���ID��Ԃ� (�o�������l�����Ă���)
//---------------------------------------------------------------------
int Weapon::getRandWeaponID()
{
    // �o�����̑��a
    int rate_max = 0;
    __DtTestPoint( __DtFunc_getRandWeaponID, __DtStep_0 )
    for ( int i = 0; i < WEAPON_MAX_NUM; ++i )
    {
        __DtTestPoint(__DtFunc_getRandWeaponID, __DtStep_1)
        if ( gWeaponBaseData[ i ].Rate )
        {
            __DtTestPoint(__DtFunc_getRandWeaponID, __DtStep_2)
            rate_max += gWeaponBaseData[ i ].Rate;
        }
    }

    // �l���ЂƂ��߂�
    int value = rand() % rate_max;

    // �l�ɑΉ����镐���T��
    for ( int i = 1; i < WEAPON_MAX_NUM; ++i )
	{
		int rating = gWeaponBaseData[ i ].Rate;
        __DtTestPoint(__DtFunc_getRandWeaponID, __DtStep_3)
        if ( rating > 0 )
        {
		    __DtTestPoint(__DtFunc_getRandWeaponID, __DtStep_4)
		    if ( rating > value )
		    {
			    __DtTestPoint( __DtFunc_getRandWeaponID, __DtStep_5 )
			    return i;
		    }
		    value -= rating;
        }
	}
    __DtTestPoint( __DtFunc_getRandWeaponID, __DtStep_6 )
    return 0;
}

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
Weapon::Weapon()
{
	__DtTestPoint( __DtFunc_Weapon, __DtStep_0 )
	mWeaponData.WeaponType = WEAPON_NON;
    mWeaponData.UseCount   = 0;
    mGuideNamePlate = NULL;
	__DtTestPoint( __DtFunc_Weapon, __DtStep_1 )
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
Weapon::~Weapon()
{
	__DtTestPoint( __DtFunc_Weapon, __DtStep_2 )
	SAFE_DELETE( mGuideNamePlate );
	__DtTestPoint( __DtFunc_Weapon, __DtStep_3 )
}

//---------------------------------------------------------------------
// �� ������
//---------------------------------------------------------------------
bool Weapon::Initialize( const CreateData& data_ )
{
    __DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
    mWeaponData = data_.Data;

    mPanel = LBatchPanel::create( 80, 80);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel.setCenter(-40, 40, 0);
    mPanel->setTexture( LTexture::create( "Data/Graphics/Object/Weapons.png", 0xffffffff ) );
    mPanel->setSrcRect( 80 * mWeaponData.WeaponType, 0, 80, 80 );

    this->mPosition = data_.Position;
    this->mPosition.z = -5.f;

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 0, 30, -30 );

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}

//---------------------------------------------------------------------
// �� ���[���h���W��ԏ�ł̓����蔻���`��Ԃ�
//---------------------------------------------------------------------
const LRect* Weapon::getBoundingRect()
{
    static LRect rc;
    __DtTestPoint( __DtFunc_getBoundingRect, __DtStep_0 )
    rc.set(
        static_cast< int >( mPosition.x ),
        static_cast< int >( mPosition.y ),
        80, 80 );
    __DtTestPoint( __DtFunc_getBoundingRect, __DtStep_1 )
    return &rc;
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
bool Weapon::Update()
{
    __DtTestPoint( __DtFunc_Update, __DtStep_0 )
    GameObject::Update();

    mPanel->setPosition( this->mPosition );

    __DtTestPoint( __DtFunc_Update, __DtStep_1 )
    return true;
}


//=============================================================================
//								End of File
//=============================================================================
