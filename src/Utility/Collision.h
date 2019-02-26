//
// Collision.h
// Dat�t�@�C������f�[�^�𕜌����A
// �����蔻�������N���X
//

#ifndef COLLISION_H
#define COLLISION_H

#include <stdio.h>

class Collision
{
private:

	static const int SET_H_NUM = 12; // �Z�`���擾����͈͂������ɂ������Ԃ�
	static const int SET_V_NUM = 12; // �Z�`���擾����͈͂������ɂ������Ԃ�

	struct Position
	{
		int H;
		int V;
	};

	struct Data
	{
		Position Atk_pos; // �U������
		Position Atk_size;

		Position Dmg_pos; // �_���[�W����
		Position Dmg_size;

		Position origin; // ��_

		bool started;
	};

	FILE *mReadFP; // �ǂݍ��݃t�@�C���|�C���^
	Data mLoadData[ SET_H_NUM*SET_V_NUM ];

	LRect mAtkArea; // �U������Z�`
	LRect mDmgArea; // ��_���[�W����Z�`

public:

	// �R���X�g���N�^
	Collision();

	// �f�X�g���N�^
	~Collision();

	// ������
	void Initialize();

	//
	// LoadFile
	// ���@�� const char* fileName_
	// �߂�l void
	//
	// �����Ŏw�肳�ꂽ
	// �����蔻��f�[�^�̓ǂݍ���
	//
	void LoadFile( const char* fileName_ );

	//
	// getAtkCollision
	// ���@�� const unsigned int ActionIdx, const unsigned int Frames
	// �߂�l LRect
	//
	// �A�N�V�����ԍ��ƃR�}�ԍ���n����
	// �@���̓���̍U���̓����蔻�肪�Ԃ�( x, y, width, height )
	//
	LRect* getAtkCollision( const unsigned int ActionIdx, const unsigned int Frames );

	//
	// getDmgCollision
	// ���@�� const unsigned int ActionIdx, const unsigned int Frames
	// �߂�l LRect
	//
	// �A�N�V�����ԍ��ƃR�}�ԍ���n����
	// �@���̓���̃_���[�W�̓����蔻�肪�Ԃ�( x, y, width, height )
	//
	LRect* getDmgCollision( const unsigned int ActionIdx, const unsigned int Frames );

	//
	// getOrigin
	// ���@�� const unsigned int ActionIdx, const unsigned int Frames
	// �߂�l LVector2
	//
	// �A�N�V�����ԍ��ƃR�}�ԍ���n����
	// �@���̓���̊�_���Ԃ�( x, y )
	//
	LVector2 getOrigin( const unsigned int ActionIdx, const unsigned int Frames );


    /// [�R�{] �U���p�����蔻����R�}�ԍ�����擾���� (�R�}�ԍ��͍��ォ��E�ɂ����� +1�A���ɍs���ɂ�� +12)
    LRect* getAtkCollisionByIndex( const unsigned int index_ );

    /// [�R�{] �_���[�W�p�����蔻����R�}�ԍ�����擾����
    LRect* getDmgCollisionByIndex( const unsigned int index_ );

    /// [�R�{] ���_���R�}�ԍ�����擾����
    LVector2 getOriginByIndex( const unsigned int index_ );

	//
	// checkHit
	// ���@�� const LVector3 alphaPos, const LRect* alpha,
	//        const LVector3 betaPos,  const LRect* beta
	// �߂�l bool
	//
	// �����蔻���Rect��n����
	// �@�������Ă��邩�ǂ�����bool�ŕԂ�
	//
	bool checkHit( const LVector3 alphaPos, const LRect* alpha, const LVector3 betaPos, const LRect* beta );

	// ���
	void Release();
};

#endif
// EOF