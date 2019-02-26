//=============================================================================
/*! 
    @addtogroup 
    @file       EventType.h
    @brief      �C�x���g����̒�`
    
    �C�x���g����̒�`
    
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


//Include Guard
#ifndef __INCLUDE_EVENT_TYPE_H__
#define __INCLUDE_EVENT_TYPE_H__


/*! @enum EventType */
typedef enum _ENUM_EVENT_TYPE
{
	EV_UNDEF = 0,
	EV_INPUT,


    // �� �s���֌W ////////////////////////////////////////////
    //      �s���֌W�̃C�x���g�́A�����Ă����Ƃ��ɒ����ɂ��̍s�����Ƃ�悤�ɂ���B
    //      ����́A�l�b�g���[�N�������ɉ�����x�Ƃ��̖��ł̂����莞�Ԃ��������Ă��܂����ꍇ�A
    //      ���̊ԍU���J�n���b�Z�[�W�������Ă��Ă����̓�������Ȃ��Ƃ������Ƃ�h�����߂ɕK�v�B

    EV_ACTION_WAIT,                     ///< [ �����Ȃ� ] �ҋ@�J�n
    EV_ACTION_RUN,                      ///< [ enum CharaDir ] ����J�n 

    EV_ACTION_STUN,                     ///< [ u32 �t���[���� ] �̂�����J�n
	EV_ACTION_BLOW,						// [ u32 �t���[���� ] �ӂ��Ƃю���

	EV_ACTION_JUMP,			            // [ �����Ȃ� ]�W�����v�J�n
	EV_ACTION_SQUAT,					// [ �����Ȃ� ]���Ⴊ�݊J�n
	EV_ACTION_LADDER_WAIT,              // [ �����Ȃ� ]�͂����ҋ@�J�n
	EV_ACTION_LADDER_UP,                // [ �����Ȃ� ]�͂����o��J�n
	EV_ACTION_LADDER_DOWN,              // [ �����Ȃ� ]�͂����~��J�n
	EV_ACTION_GUARD,					// [ �����Ȃ� ]�K�[�h�J�n
	EV_ACTION_SQUAT_GUARD,				// [ �����Ȃ� ]���Ⴊ�݃K�[�h�J�n

    EV_ACTION_ITEM_GET,                 ///< �A�C�e���擾�̂��߂̂��Ⴊ��

    EV_ACTION_ATTACK_1,                 ///< �ʏ�U��1
	EV_ACTION_ATTACK_2,                 ///< �ʏ�U��2
	EV_ACTION_ATTACK_3,                 ///< �ʏ�U��3
	EV_ACTION_ATTACK_SQUAT_ATTACK,      ///< ���Ⴊ�ݍU��
	EV_ACTION_ATTACK_JUMP_ATTACK,       ///< �W�����v�U��
	EV_ACTION_ATTACK_ANTIAIR_ATTACK,    ///< �΋�U��
	EV_ACTION_ATTACK_DUSH_ATTACK,       ///< �_�b�V���U��

    EV_ACTION_START_DEAD,               ///< [ �����Ȃ� ] �퓬�s�\�J�n (���[�V�����J�n�Ƃ�)
    // ��  ////////////////////////////////////////////
    EV_APPLY_DAMAGE,        ///< [ AttackEventArg ] �_���[�W��^����

    EV_GET_ITEM,            ///< [ u32 �A�C�e���ԍ� ] �A�C�e�����E�����Ƃ��ł���
    EV_GET_WEAPON,          ///< [ WeaponData ] ������E�����Ƃ��ł���
    

    // �� �V�X�e���n�C�x���g ////////////////////////////////////////////
    //      GameSession::send �Ŏg���BGameObject�ł͊�{�I�Ɏg��Ȃ��B
    SYSEV_BEGIN,

    SYSEV_GOTO_SCENEGAME,       ///< SceneGame �Ɉړ����� (�e�z�X�g����T�[�o(�������g)�ɑ���ꂽ��A�T�[�o����S�Ẵz�X�g�ɑ�����)


    SYSEV_GAMEOBJECT,           ///< �Q�[���I�u�W�F�N�g�֌W�̃f�[�^�B(LNote::Utility::MessageQueue �̃V���A���C�Y�f�[�^)
    SYSEV_ITEM_REQUEST,         ///< [ ItemRequestArgs ] �A�C�e��(����܂�)���E�������Ƃ��̗v�� (�e�z�X�g����T�[�o�ցB�T�[�o�� EV_GET_ITEM �܂��� EV_GET_WEAPON ��Ԃ�)

    SYSEV_DELETE_GAMEOBJECT,    ///< [ u32 �I�u�W�F�N�g�n���h�� ] �Q�[���I�u�W�F�N�g���폜���� (���ۂɂ͍폜�t���O�𗧂Ă�BGameObject �� isEntity() == true �̏ꍇ�A�f�X�g���N�^�ő��M����B�܂��́A�A�C�e���擾���̍폜�B)
                                //                                �f�X�g���N�^�ȊO����폜����ꍇ�A���M���͂��Ȃ炸�폜����I�u�W�F�N�g���폜������ł��̃C�x���g�𑗐M���邱�ƁB

    SYSEV_CREATEED_OBJECT,      ///< [ CreatedObjectArgs ]�e�z�X�g���ŃI�u�W�F�N�g���쐬������(create() �� is_entity_ = true �ɂ����Ƃ�)�A�T�[�o�o�R�ŁA�쐬�����z�X�g�ȊO�̃z�X�g�ɐ����������Ƃ�`����

    SYSEV_END,

}EventType;


/*! @enum InputType */
typedef enum _ENUM_INPUT_TYPE
{
	INPUT_UNDEF = 0,
	INPUT_ON_ATTACK,
}InputType;


/// �C�x���g�̃w�b�_�f�[�^ (���̃f�[�^�� postEvent ���A�����I�ɕt�������B���ɋC�ɂ���K�v�͖���)
struct EventHeader
{
    u32         Type;           ///< �C�x���g�̎��
    u32         ObjectHandle;   ///< ���M�Ώۂ̃I�u�W�F�N�g (0xffffffff �őS�Ăɑ��M����)
    u32         ArgSize;        ///< �ȍ~�ɑ��������f�[�^�̃T�C�Y
};

/// �Q�[���S�̂Ɋ֌W����C�x���g�̃w�b�_ (GameSession::send() �Ŏ����I�ɕs�����B�Q�[���I�u�W�F�N�g�p�̂��� (EventHeader) �Ƃ͕�)
struct GameSystemEventHeader
{
    u32         Type;           ///< �C�x���g�̎��
    u32         ArgSize;        ///< �ȍ~�ɑ��������f�[�^�̃T�C�Y
};

/// �U���C�x���g�̈����f�[�^
struct AttackEventArg
{
    s32         Damage;         ///< �_���[�W��
	u32         AttackerHandle; //
    LVector3    BrowVector;     ///< �ӂ���΂��x�N�g��
	u8          Criticalflag;    ///< �N���e�B�J���̃t���O
	u8			Guardflag;       ///<�K�[�h�̃t���O
};

struct ItemRequestArgs
{
    u32         GetterHandle;   ///< �E�����Ƃ��Ă���L�����N�^�[�̃n���h��
    u32         ItemObjHandle;  ///< �A�C�e���܂��͕���I�u�W�F�N�g�̃n���h��
};

/// �I�u�W�F�N�g�������A���̃z�X�g�ɓ`����Ƃ��̃f�[�^
struct CreatedObjectArgs
{
    u32         HostID;         ///< ���z�X�g�Ɋ��蓖�Ă��Ă���z�X�gID�B�T�[�o�ɑ���ꂽ��A����ȊO�̃z�X�g�ɑ��M�����BGameSession ����擾����B
    u32         ObjectType;     ///< ObjectType �̒l
    //void*       ArgData;        ///< �ȍ~�ɑ��������f�[�^�B���̃f�[�^�͊e�I�u�W�F�N�g�� create() �ɓn�����
};

/// �T�[�o�ɃI�u�W�F�N�g�̍쐬��v������Ƃ��̈����f�[�^
//struct CreateObjectArgs
//{
 //   u32         
//};


#if 0

class EventListener
{
private:
	unsigned int mHandle;

public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	const unsigned int& getHandle() const {return mHandle;}

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------
	void setHandle(unsigned int unHandle_) {mHandle = unHandle_;}

	EventListener();
	virtual ~EventListener();
	virtual int HandleEvent(u32 event_,void *args_) = 0;
};

#endif


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
