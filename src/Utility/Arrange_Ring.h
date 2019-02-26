//=============================================================================
// �� Arrange_Ring
// 2011/1/21 Keisuke Hosoda
//
// ����F
//   ���S�_����̉~����̍��W��Ԃ�
//=============================================================================
#ifndef ARRANGE_RING_H
#define ARRANGE_RING_H

#include <vector>

class Ring
{
private:

	struct HVector2
	{
		float x;
		float y;
	};

	// �~����ɍ��W�����ԉ~�̃f�[�^
	struct StandardCircle
	{
		// �~�̒��S�_
		HVector2 Origin;
		// �~�̔��a
		HVector2 Radius;
	};

	// �~����ɕ��ԍ��W(Star)�̃f�[�^
	struct StarData
	{
		// Star���W
		std::vector< HVector2 > Pos;
		// �����z�u����̂�
		unsigned int setNum;
		// ���x�Ԋu��
		float Angle;
		// ����W�̊p�x( 0�`359 )
		float OriginDeg;
		// ����W�ɂ���Star�̓Y����( 0~setNum-1 )
		unsigned int Target;
	};

	// ��]�ɕK�v�ȃf�[�^
	struct TurnData
	{
		// ���W�̉�]����( -1, 0, 1 )
		int TurnVec;
		// 1�t���[���O�̉�]������ێ�
		int OldTurnVec;
		// ��]���鑬�x
		float TurnSpeed;
		//���x��]���邩
		float TurnLimit;

		// ��]�p�x
		float Deg;
		float Rad; // ���W�A���w��̏ꏊ�����邽�߁B

		// Star�Ԉړ��Ŏg�����̓��b�N
		bool InputLock;
	};

	StandardCircle mStdCir;
	StarData       mSData;
	TurnData       mTData;

public:

	// �R���X�g���N�^
	Ring();
	
	// �f�X�g���N�^
	~Ring();

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F Initialize
	//
	//  ���� �F < void >
	// �߂�l�F < void >
	//  ���� �F �������B�g�p�O�Ɉ�x�����ĂԂ���
	//---------------------------------------------------------------------
	void Initialize();

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F Process
	//
	//  ���� �F < void >
	// �߂�l�F < void >
	//  ���� �F ���[�v�̒��ŌĂԂ���
	//---------------------------------------------------------------------
	void Process();

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F Release
	//
	//  ���� �F < void >
	// �߂�l�F < void >
	//  ���� �F ��������B�K�������I�ɌĂԂ���
	//---------------------------------------------------------------------
	void Release();

// �ȉ��Z�b�^&�Q�b�^

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F setCircleOrigin
	//
	//  ���� �F < const int x, const int y >
	// �߂�l�F < void >
	//  ���� �F �����w��̏ꏊ���~�̌��_�Ƃ���
	//---------------------------------------------------------------------
	void setCircleOrigin( const int x, const int y );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F setCircleSize
	//
	//  ���� �F < const float width, const float height >
	// �߂�l�F < void >
	//  ���� �F �~�̑傫���������Ŏw�肷��
	//---------------------------------------------------------------------
	void setCircleSize( const float width, const float height );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F setCircle
	//
	//  ���� �F < const int x, const int y, 
	//            const float width, const float height >
	// �߂�l�F < void >
	//  ���� �F �~�̃f�[�^�������Ŏw�肷��
	//---------------------------------------------------------------------
	void setCircle( const int x, const int y, const float width, const float height );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F setStarNum
	//
	//  ���� �F < const unsigned int number >
	// �߂�l�F < void >
	//  ���� �F �~����ɕ��ԍ��W( Star )�̐���ݒ�
	//---------------------------------------------------------------------
	void setStarNum( const unsigned int number );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F setOriginDeg
	//
	//  ���� �F < const float degree >
	// �߂�l�F < void >
	//  ���� �F Star�̊�p�x�������w��( 0�`359 )
	//---------------------------------------------------------------------
	void setOriginDeg( const float degree );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F setTarget
	//
	//  ���� �F < const unsigned int idx >
	// �߂�l�F < void >
	//  ���� �F ��ʒu�Ɉ����w���Star��z�u
	//---------------------------------------------------------------------
	void setTarget( const unsigned int idx );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F setTurnDirection
	//
	//  ���� �F < const int direct >
	// �߂�l�F < void >
	//  ���� �F ��]�����A-1, 0, 1�Ŏw��
	//---------------------------------------------------------------------
	void setTurnDirection( const int direct );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F setTurnSpeed
	//
	//  ���� �F < const float speed >
	// �߂�l�F < void >
	//  ���� �F ��ʒu�Ɉ����w���Star��z�u
	//---------------------------------------------------------------------
	void setTurnSpeed( const float speed );

  // �Q�b�^

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F getCircle
	//
	//  ���� �F < void >
	// �߂�l�F < StandardCircle >
	//  ���� �F �~�̃f�[�^���擾
	//---------------------------------------------------------------------
	StandardCircle *getCircle(){ return &mStdCir; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F getStarNum
	//
	//  ���� �F < void >
	// �߂�l�F < const int >
	//  ���� �F �~����ɕ��ԍ��W( Star )�̐����擾
	//---------------------------------------------------------------------
	const unsigned int *getStarNum(){ return &mSData.setNum; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F getTarget
	//
	//  ���� �F < void >
	// �߂�l�F < const unsigned int >
	//  ���� �F ��ʒu��Star�̓Y�������擾
	//---------------------------------------------------------------------
	const unsigned int *getTarget(){ return &mSData.Target; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F getTurnDirection
	//
	//  ���� �F < void >
	// �߂�l�F < const int >
	//  ���� �F ��]�����A-1, 0, 1�Ŏw��
	//---------------------------------------------------------------------
	const int *getTurnDirection(){ return &mTData.TurnVec; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F nowTurn
	//
	//  ���� �F < void >
	// �߂�l�F < const bool >
	//  ���� �F ��]���Ă邩�ǂ����Atrue�ŉ�]��
	//---------------------------------------------------------------------
	const bool *nowTurn(){ return &mTData.InputLock; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F getStarPos
	//
	//  ���� �F < const int >
	// �߂�l�F < const StarData >
	//  ���� �F Star�̍��W���擾
	//---------------------------------------------------------------------
	const HVector2* getStarPos( const int idx ){ return &mSData.Pos[ idx ]; }

private:

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F ResetDeg
	//
	//  ���� �F < const int target >
	// �߂�l�F < void >
	//  ���� �F ����W�Ɉ����w���Star���Z�b�g����
	//---------------------------------------------------------------------
	void ResetDeg( const unsigned int *target );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// �֐����F calcAngle
	//
	//  ���� �F < void >
	// �߂�l�F < void >
	//  ���� �F �~����̓_�𓙊Ԋu�ɕ��ׂ邽�߂̊p�x���v�Z�B
	//    ��_���猩�čœK�Ȋp�x�ɒ�������B
	//    ���������邽�тɈ�x�����ĂԁB
	//---------------------------------------------------------------------
	void calcAngle();
};

#endif

//=============================================================================
//								End of File
//=============================================================================