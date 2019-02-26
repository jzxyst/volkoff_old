//=============================================================================
/*! 
    @addtogroup 
    @file       MapManager.h
    @brief      
    
    �}�b�v���Ǘ�����N���X�̒�`
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/13 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================

#pragma once 

/*! @par include */
#include "../Object/Gimmick/Ladder.h"
#include "../Object/Gimmick/LadderTop.h"
#include "../Object/Gimmick/Entry.h"
#include "../Object/Gimmick/Exit.h"
#include "../Object/Gimmick/Exit_Lock.h"
#include "../Object/Gimmick/Vase.h"
#include "../Object/Gimmick/Mine.h"
#include "../Object/Gimmick/Box.h"
#include "../Object/Gimmick/Fort.h"
#include "../Object/Gimmick/Locker.h"
#include "../Object/Gimmick/Window.h"
#include "../Object/Gimmick/Door.h"
#include "../Object/Gimmick/Manhole.h"
#include "../Object/Gimmick/Duct.h"
#include "../Object/Gimmick/TopWall.h"
#include "../Object/Gimmick/BottomWall.h"
#include "../Object/Gimmick/UBW.h"

#include "../Object/Item/Key.h"
#include "../Object/Item/Cure_S.h"
#include "../Object/Item/Cure_M.h"
#include "../Object/Item/Cure_L.h"

#include "../Object/Enemy.h"
#include "../Object/MidBoss1.h"
#include "../Object/MidBoss2.h"
#include "../Object/Valfirle.h"
/*! @enum MapType */
typedef enum _ENUM_MAP_TYPE
{
	MAP_NULL = 0,
	MAP_BLOCK,//�ǃu���b�N
	MAP_BLOCK_THROUGH,//���蔲������u���b�N
	MAP_BLOCK_STEALTH,

	MAP_LADDER = 10,//�͂���
	MAP_LADDERTOP,

	MAP_ENTRY = 20,//����
	MAP_EXIT,//�o��
	MAP_EXIT_LOCK,//�����t���o��
	MAP_ENTRYWALL,
//�G���o���������
	MAP_WINDOW_S = 30,//���i���j
	MAP_WINDOW_L,//��(��)
	MAP_WINDOW_HARD,//���iHARD�j
	MAP_LOCKER_S =33,//���b�J�[
	MAP_LOCKER_L,
	MAP_LOCKER_HARD,
	MAP_MANHOLE_S = 36,//�}���z�[��
	MAP_MANHOLE_L,
	MAP_MANHOLE_HARD,
	MAP_DOOR_S = 39 , //�h�A
	MAP_DOOR_L,
	MAP_DOOR_HARD,
	MAP_WALL_S = 42, //�ǉ�
	MAP_WALL_L,
	MAP_WALL_HARD,
	MAP_WALL2_S = 45,//�ǉ�
	MAP_WALL2_L,
	MAP_WALL2_HARD,
	MAP_DUCT_S = 48,//�_�N�g
	MAP_DUCT_L,
/////


	MAP_FORT = 50,//�����@�e
	MAP_FORT_HARD,
	MAP_MINE,//�n��
	MAP_MINE_HARD,
	MAP_WINDOW_DUMMY,//���_�~�[
	MAP_LOCKER_DUMMY,//���b�J�[�_�~�[
	MAP_MANHOLE_DUMMY,//�}���z�[���_�~�[
	MAP_DOOR_DUMMY,//�h�A�_�~�[
	MAP_DUCT_DUMMY,//�_�N�g�_�~�[
	MAP_WALL_DUMMY,

	MAP_BOX =60 ,//��
	MAP_DRUM,//�h������
	MAP_VASE,//�ԕr
	MAP_UBW, //ubw

	MAP_KEY =70,//��
	MAP_CURE_S,//�񕜃A�C�e��
	MAP_CURE_M,
	MAP_CURE_L,
	MAP_GRENADE,


	MAP_ENEMY = 90,
	MAP_ENEMY_S,
	MAP_ENEMY_L, 
	MAP_MIDBOSS_KATANA,
	MAP_MIDBOSS_TAEKWONDO,
	MAP_MIDBOSS_KNIFE,
	MAP_MIDBOSS_SCYTHE,
	MAP_VALFIRLE,
	MAP_UNDEF = 0xffffffff,
}MapType;


enum MapCollFlag
{
	MAPCOLL_LEFT	= 0x01,
	MAPCOLL_RIGHT	= 0x02,
	MAPCOLL_UP		= 0x04,
	MAPCOLL_DOWN	= 0x08,
};


class MapManager
{
public:

	/// �C���X�^���X�̎擾
	static MapManager* getInstance();

private:

    /// �R���X�g���N�^
    MapManager();

    /// �f�X�g���N�^
    ~MapManager();

	

public:

	/// �I������ (GameManager ����Ă΂��)
	void finalize();

    //---------------------------------------------------------------------
    ///**
    //  @brief      �}�b�v (�X�e�[�W) �̕ύX
    //
    //  @param[in]  map_id_ : �쐬����}�b�v�ԍ�
    //
    //  @par
    //              �X�g�[���[���[�h�ŁA�X�e�[�W��؂�ւ���Ƃ��ɌĂяo���B
    //
    //              �w�i�̃}�b�v�`�b�v�̔z�u��؂�ւ��A�K�v�� GameObject ��
    //              ���ׂ� new ����B
    //
    //              ���̊֐����ĂԂƂ��́A���݂̃X�e�[�W�ŉ������K�v��������̂�
    //              ���ׂĉ���ς݂ł��邱�ƁB
    //*/
    //---------------------------------------------------------------------
    void changeMap( u32 map_id_ );

	u32 collision( LRect rect_, LVector3 velocity_, LVector3* out_pos_ );	// out_pos_�͋�`�̍���̍��W

	bool BulletCollision(LRect rect_);

	LVector3 getStartPosition();

    // �^�C���}�b�v��� (�^�C�g���֖߂�Ƃ��Ȃ�)
    void releaseTilemap();


	int getMapID() { return mMapID; }

private:

	Core::Scene::Tilemap*    mTilemap;   ///< �^�C���}�b�v�̕`��N���X
    LPanel                      mTilemapPanel;
    LTexture                    mTilemapExpandedTexture;

    u32                         mMapID;     ///< ���݂̃}�b�v�ԍ� (�����_���}�b�v�ł͏�� 0)
    u32                         mWidth;     ///< �}�b�v�̕�
    u32                         mHeihgt;    ///< �}�b�v�̍���

	int							mMapData[100 * 100];

    Ladder* mLadder[250];//�͂����N���X
	u32 mLadderCnt;//�͂����̐�

    LadderTop* mLadderTop[50];//�͂����N���X
	u32 mLadderTopCnt;//�͂����̐�

	Entry* mEntry;

	Exit* mExit;

	Exit_Lock* mExit_Lock;

	Locker* mLocker[30];
	u32 mLockerCnt;

	Manhole* mManhole[30];
	u32 mManholeCnt;

	Window* mWindow[30];
	u32 mWindowCnt;

	Door* mDoor[30];
	u32 mDoorCnt;

	TopWall* mTopWall[30];
	u32 mTopWallCnt;

	BottomWall* mBottomWall[30];
	u32 mBottomWallCnt;

	Vase* mVase[30];//�ԕr�N���X
	u32 mVaseCnt;//�ԕr�̐�



	Mine* mMine[30];//�n���N���X
	u32 mMineCnt;//�n���̐�

	Box* mBox[30];//���N���X
	u32 mBoxCnt;//���̐�

	Fort* mFort[20];
	u32 mFortCnt;

	Key* mKey;//���N���X
	
	Cure_S* mCure_S[20];
	u32 mCure_Scnt;

	Cure_M* mCure_M[20];
	u32 mCure_Mcnt;

	Cure_L* mCure_L[20];
	u32 mCure_Lcnt;

	Duct* mDuct[30];
	u32 mDuctCnt;

	UBW * mUBW[10];
	u32 mUBWCnt;

	Enemy* mEnemy;

	MidBoss1* mMidBoss1;
	
};

//=============================================================================
//								End of File
//=============================================================================
