//=============================================================================
/*! 
    @addtogroup 
    @file       GameObjectManager.h
    @brief      GameObject�̊Ǘ�
    
    GameObjectManager�̒�`
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_GAMEOBJECTMANAGER_H__
#define __INCLUDE_GAMEOBJECTMANAGER_H__


/*! @par include */
#include "./../Utility/Singleton.h"
#include "./../Event/EventType.h"
#include <list>
#include <map>


class GameObject;
class AttackedObject;

typedef std::list<GameObject*>                  GameObjectList;
typedef std::map<u32,GameObject*>               GameObjectMap;
typedef std::pair<u32,GameObject*>              GameObjectPair;
typedef std::list< AttackedObject* >            AttackedObjectList;
typedef Core::Base::NodeList< AttackedObject >  HitObjectList;

/*! @enum ObjectType */
typedef enum _ENUM_OBJECT_TYPE
{
	OBJ_UNDEF = 0,
	OBJ_CHARACTER, //�ꎞ�I
	OBJ_LADDER,    // �͂���           �c static �I�u�W�F�N�g�B �ȉ��͓��I�B
	OBJ_LADDERTOP,
	OBJ_BOX,       // �ؔ�

    OBJ_ITEM_BEGIN, // �� ��������A�C�e��
	OBJ_CURE_S,    // �񕜃A�C�e����
	OBJ_CURE_M,    // �񕜃A�C�e����       
	OBJ_CURE_L,    // �񕜃A�C�e����
	OBJ_KEY,       // ��
    OBJ_ITEM_END,   // �� �����܂ŃA�C�e��
	OBJ_EXIT,     //�o��
	OBJ_EXIT_LOCK,//���t���o��
    OBJ_WEAPON,     ///< ����
	OBJ_DOOR,		///< �h�A	[�R�{]�Ƃ肠�����p��
	OBJ_ENTRY,		///< �����@�Ƃ肠����
	OBJ_FORT,		///< �����@�e
	OBJ_LOCKER,		///< ���b�J�[
	OBJ_MANHOLE,	///< �}���z�[��
	OBJ_MINE,		///< �n��
	OBJ_VASE,		///< �ԕr
	OBJ_WINDOW,		///< ��
	OBJ_ENEMY,
	OBJ_UBW,        ///UBW
	OBJ_BULLET,
	OBJ_GRENADE,

}ObjectType;


/*! @class GameObjectManager */
class GameObjectManager : public Singleton<GameObjectManager>
{
	friend Singleton<GameObjectManager>;

private:
	/*! @par private�����o�ϐ� */
	GameObjectList  m_dqObjectList;     ///< ���ׂĂ� GameObject ���i�[���郊�X�g
	GameObjectList  m_dqTempList;       ///< Update����new���ꂽ�I�u�W�F�N�g���i�[���郊�X�g
    GameObjectMap   m_mObjectMap;       ///< GameObject �ƃn���h���̑Ή��\

    u32             m_unNextHandle;     ///< ���ɍ쐬�����I�u�W�F�N�g�Ɋ��蓖�Ă�n���h�� (���n���h���̓T�[�o������炤�K�v������B��Œ����Ă���)

private:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::GameObjectManager

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	GameObjectManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::~GameObjectManager

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~GameObjectManager();

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::Initialize

		����������

		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize();

	//---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::Release

		�I������

		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::Update

		�t���[���X�V����
        
		@param[in]      void
		@return         void
		@exception      none
        @par
                        [yama]
                        �L���[�ɂ��܂��Ă���C�x���g�����킹�ď�������B
                        �֐��̎��s�����́A
                        
                            HandleEvent() �� Update() �� UpdateSelf() �� �폜����K�v������΍폜
	*/
	//---------------------------------------------------------------------------
	void Update();



    //---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::AddObject

		���X�i�[�����X�g�ɒǉ�����

		@param[in]      GameObject *pCObj �ǉ�����I�u�W�F�N�g�|�C���^
		@return         �ǉ����ꂽ�I�u�W�F�N�g�Ɋ��蓖�Ă�ꂽ�n���h�� (gatHandle() �œ�������̂Ɠ���)
		@exception      none
	*/
	//---------------------------------------------------------------------------
	u32 AddObject(GameObject *pCObj);

    /// �I�u�W�F�N�g���폜����
    void deleteObject( GameObject* obj_ );


    /// �U���̊֌W����I�u�W�F�N�g��ǉ����� (AttackedObject �̃R���X�g���N�^����Ă΂��)
    void addAttackedObject( AttackedObject* obj_ );

    /// �U���̊֌W����I�u�W�F�N�g���O�� (AttackedObject �̃f�X�g���N�^����Ă΂��)
    void removeAttackedObject( AttackedObject* obj_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      �I�u�W�F�N�g����������
    //
    //  @param[in]  handle_ : �ΏۃI�u�W�F�N�g�̃n���h��
    //
    //  @par
    //              ���݂��Ȃ��ꍇ�� NULL ��Ԃ��B
    //*/
    //---------------------------------------------------------------------
    GameObject* findObject( u32 handle_ );
	



    //---------------------------------------------------------------------
    ///**
    //  @brief      �w�肵���n���h�������I�u�W�F�N�g�ɃC�x���g�𑗐M���� (�L���[�C���O����)
    //
    //  @param[in]  handle_ : �ΏۃI�u�W�F�N�g�̃n���h�� (0xffffffff �ł��ׂẴI�u�W�F�N�g�ɑ��M����)
    //  @param[in]  event_  : �C�x���g�̎��
    //  @param[in]  data_   : �C�x���g�̈����f�[�^)
    //  @param[in]  size_   : data_ �̃T�C�Y (�o�C�g�P��)
    //
    //  @par
    //              �C�x���g���L���[�ɂ��߂��A�����ɃI�u�W�F�N�g�ɑ��M����B
    //              �l�b�g���[�N�z���ɂ͎g���Ȃ��̂Œ��ӁB
    //              ��ɃR���g���[������̓��͂� Player �ɓ`���邽�߂Ɏg���B
    //*/
    //---------------------------------------------------------------------
    void sendEvent( u32 handle_, u32 event_, void* data_, u32 size_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      �w�肵���n���h�������I�u�W�F�N�g�ɃC�x���g�𑗐M���� (�L���[�C���O����)
    //
    //  @param[in]  handle_ : �ΏۃI�u�W�F�N�g�̃n���h�� (0xffffffff �ł��ׂẴI�u�W�F�N�g�ɑ��M����)
    //  @param[in]  event_  : �C�x���g�̎��
    //  @param[in]  data_   : �C�x���g�̈����f�[�^)
    //  @param[in]  size_   : data_ �̃T�C�Y (�o�C�g�P��)
    //
    //  @par
    //              �C�x���g����x�L���[�ɂ��߁A���� GameObjectManager::Update() ��
    //              �Ă΂ꂽ�Ƃ��ɂ��ׂď�������B
    //              �l�b�g���[�N�z���Ɏg���C�x���g�͂�����B
    //*/
    //---------------------------------------------------------------------
    void postEvent( u32 handle_, u32 event_, void* data_, u32 size_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      AttackedObject �ƂƂ̓����蔻����s��
    //
    //  @param[in]  rect_         : ���[���h���W��̋�`
    //  @param[in]  target_group_ : �Ώۂ̃O���[�v (AttackedGroup �̑g�ݍ��킹)
    //
    //  @return     ���������I�u�W�F�N�g�̃��X�g
    //*/
    //---------------------------------------------------------------------
    HitObjectList* judgeCollitionToAttackedObject( const LRect& rect_, u32 target_group_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      �w�肵����ނ̃I�u�W�F�N�g�Ɠ����蔻����s��
    //
    //  @param[in]  rect_             : ���[���h���W��̋�`
    //  @param[in]  target_type_      : �Ώۂ̎��
    //  @param[in]  target_type_end_  : �Ώۂ̎��
    //
    //  @return     ���������I�u�W�F�N�g�̃n���h��
    //
    //  @par
    //              target_type_end_ �͔͈͎w�肷��ꍇ�ɒl��n���B
    //              �w�肵���ꍇ�Atarget_type_ �ȏ�Atarget_type_end_ �ȉ���
    //              ��ނ̃I�u�W�F�N�g�Ɣ�����s���B
    //*/
    //---------------------------------------------------------------------
    u32 judgeCollitionTypeSpecified( const LRect& rect_, ObjectType target_type_, ObjectType target_type_end_ = OBJ_UNDEF );

	//---------------------------------------------------------------------
    ///**
    //  @brief      �w�肵����ނ̃I�u�W�F�N�g�Ɠ����蔻����s�����̂��ɏ�������
    //
    //  @param[in]  rect_             : ���[���h���W��̋�`
    //  @param[in]  target_type_      : �Ώۂ̎��
    //  @param[in]  target_type_end_  : �Ώۂ̎��
    //
    //  @return     ���������I�u�W�F�N�g�̃n���h��
    //
    //  @par
    //              target_type_end_ �͔͈͎w�肷��ꍇ�ɒl��n���B
    //              �w�肵���ꍇ�Atarget_type_ �ȏ�Atarget_type_end_ �ȉ���
    //              ��ނ̃I�u�W�F�N�g�Ɣ�����s���B
    //*/
    //---------------------------------------------------------------------
    u32 judgeCollitionTypeSpecifiedAndDelete( const LRect& rect_, ObjectType target_type_, ObjectType target_type_end_ = OBJ_UNDEF );


    

	//
	// GameObjectManager::CollisionToObject
	//
	// @param[u32]  obj_type_ : �Ώۂ̃I�u�W�F�N�g�^�C�v
	// @param[LRect]    rect_ : �Ώۂ̋�`
	// @param[LVector2] dist_ : �I�u�W�F�N�g�ƑΏۋ�`�̒��S���W�̋���
	// @param[LVector2] over_ : �I�u�W�F�N�g�Ƃ̂߂荞�ݗ�
	// @return[u32]           : ���X�g�̒��̓������Ă����I�u�W�F�N�g�̎��
	//
	//    �n���ꂽ��`�ƃ��X�g���̋�`���r
	//    �������Ă����ꍇObjectType��Ԃ�
	//
	u32 CollisionToObject( const u32 obj_type_, LRect rect_, LVector2* dist_, LVector2* over_ );


    //---------------------------------------------------------------------
    ///**
    //  @brief      �w�肵����ނ̃I�u�W�F�N�g���폜����
    //
    //  @param[in]  target_type_  : �Ώۂ̎��
    //
    //  @return     ���������I�u�W�F�N�g�̃n���h��
    //*/
    //---------------------------------------------------------------------
    u32 removeObject( ObjectType target_type_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      �v���C���[�ȊO�̃I�u�W�F�N�g���폜����
    //
    //  @return     
    //*/
    //---------------------------------------------------------------------
    void deleteStageObject();


    GameObjectList& getGameObjectList() { return m_dqObjectList; }


private:

    static const int MSGQUEUE_SIZE = 16384;	///< ���b�Z�[�W�L���[����̃T�C�Y (�o�C�g��)
    static const int TEMPBUFFER_SIZE = 256;
    static const int MAX_MSG_QUEUES = 64;	///< ���b�Z�[�W�L���[�̐�
    LNote::Utility::MessageQueue    mEventQueueArray[ MAX_MSG_QUEUES ];
    u32                             mUsingEventQueueIndex;
    u8                              mTempBuffer[ TEMPBUFFER_SIZE ];
    AttackedObjectList              mAttackedObjectList;                ///< �U��������E�U�����󂯂�I�u�W�F�N�g�̃��X�g
    HitObjectList                   mHitObjectList;                     ///< judgeCollitionToAttackedObject() �p�̈ꎞ���X�g
};


//End of Include Guard
#endif

#include "AttackedObject.h"

//=============================================================================
//								End of File
//=============================================================================
