//=============================================================================
//�y GameSession �z
//-----------------------------------------------------------------------------
///**
//  @file       GameSession.h
//  @brief      GameSession
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "../Event/EventType.h"

#define GAMEPORT (29796)

/// �e�E�q�ɂ�����炸�K�������Ă���z�X�g���
struct HostInfo
{
    char    IPAddress[ 32 ];    ///< IP �A�h���X
    char    Name[ 32 ];         ///< ���[�U�[�� (�Ƃ肠�����ڑ���ʂœ���)
    bool    IsParent;           ///< �e (�T�[�o) �̏ꍇ�� true
};



class GameServer;

//=============================================================================
// �� GameSession �N���X
//-----------------------------------------------------------------------------
///**
//  @brief      �T�[�o�Ƃ̃Z�b�V�������Ǘ�����N���X
//
//  @par
//              �e�E�q�֌W�Ȃ��A�T�[�o�Ƃ̒ʐM�͂��̃N���X���g���čs���B
//              �e�z�X�g�̏ꍇ�A���̃N���X�͎������g�ƒʐM���邱�ƂɂȂ�B
//
//              ���̃N���X�� GameManager ���ɂЂƂ������݂���B
//
//              ���̂Ƃ���\�P�b�g�ɂ��̃f�[�^��M�����́A�N���C�A���g��
//              GameSession �ōs���A�T�[�o�̏ꍇ�� GameServer ���璼��
//              GameSession �� HandleEvent ���Ă�ł���B
//*/
//=============================================================================
class GameSession
{
public:

    class EventListener
    {
    public:
        
        virtual ~EventListener() {}

        /// �C�x���g�����R�[���o�b�N
        virtual int HandleEvent( u32 event_, void* args_ ) = 0;
    };

public:

    /// �R���X�g���N�^
    GameSession();

    /// �f�X�g���N�^
    ~GameSession();

public:

    /// �e�Ƃ��ď����� (GameManager ����Ă΂��)
    void initialize( GameServer* server_ );

    /// �q�Ƃ��ď����� (GameManager ����Ă΂��)
    void initializeChild( const char* parent_ip_addr_ );

    /// �������g�̃z�X�g��\�������擾����
    const HostInfo& getHostInfo() const { return mHostInfo; }

    /// �e���𔻒肷��
    bool isParent() const { return mHostInfo.IsParent; }

    /// �C�x���g���X�i�[���Z�b�g���� (�O�����͎����� NULL �����邱��)
    void setEventListener( EventListener* listener_ ) { mEventListener = listener_; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      �T�[�o�Ƀf�[�^�𑗐M���� (GameSession ��)
    //
    //  @par
    //              �������g���e(�T�[�o)�̏ꍇ�̓l�b�g���[�N���g�킸�A
    //              ���� GameServer �N���X�ɑ��M����B
    //*/
    //---------------------------------------------------------------------
    void sendToServer( u32 event_, void* data_, u32 size_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      �I�u�W�F�N�g�쐬���b�Z�[�W (SYSEV_CREATEED_OBJECT) ���T�[�o�ɑ��M����
    //
    //  @param[in]  obj_type_ : enum ObjectType �̒l
    //
    //  @par
    //              SYSEV_CREATEED_OBJECT �𑗐M���邽�߂̃��[�e�B���e�B�֐��B
    //              �e GameObject �� create() ������ĂԁB
    //*/
    //---------------------------------------------------------------------
    void sendCreatedObjectEvent( u32 obj_type_, void* data_, u32 size_ );

    

    //---------------------------------------------------------------------
    ///**
    //  @brief      �����ҋ@
    //
    //  @par
    //              �T�[�o�ɐڑ����Ă���S�Ẵz�X�g�����̊֐����ĂԂ܂�
    //              �ҋ@����B���̊ԁA���̊֐��͐����Ԃ��Ȃ��B
    //             
    //              (�^�C���A�E�g�����Ă�����ƃx�X�g)
    //*/
    //---------------------------------------------------------------------
    void waitSync();

    //---------------------------------------------------------------------
    ///**
    //  @brief      �C�x���g�Ď�
    //
    //  @par
    //              �T�[�o����z�X�g���Ăɑ����Ă����f�[�^���Ď�����
    //              HandleEvent �ɑ���B
    //
    //              �e�̏ꍇ�� GameServer ���璼�� HandleEvent �Ă΂��̂�
    //              ���̊֐��͂Ȃɂ����Ȃ��B
    //*/
    //---------------------------------------------------------------------
    void polling();

    //---------------------------------------------------------------------
    ///**
    //  @brief      �C�x���g����
    //
    //  @par
    //              GameObject �̂Ƃ͈Ⴂ�ASYSEV_�`�n�̃V�X�e���C�x���g�̏����֐��B
    //*/
    //---------------------------------------------------------------------
    int HandleEvent( u32 event_, void* args_ );

private:

    static const int TEMP_BUFFER_SIZE = 2048;

    GameServer*     mGameServer;
    HostInfo        mHostInfo;      ///< �������g�̃z�X�g��� (initiaze() �ō쐬����)
    TcpStream*      mServerStream;  ///< �T�[�o�������X�g���[�� (�q�Ƃ��ď����������ꍇ�ɂ̂ݍ쐬�����)
    char            mTempBuffer[ TEMP_BUFFER_SIZE ];    ///< �ꎞ�o�b�t�@
    EventListener*  mEventListener;

};

//=============================================================================
//								end of file
//=============================================================================