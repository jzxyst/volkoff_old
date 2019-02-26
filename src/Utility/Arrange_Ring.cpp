//=============================================================================
// �� Arrange_Ring
// 2011/1/21 Keisuke Hosoda
//
// ����F
//  2�����ɂ����钆�S�_����̉~����̍��W��Ԃ�
//=============================================================================
#include "stdafx.h"
#include	"DT_Arrange_Ring.h"	/* For DynamicTracer-TestPoint */
#include "Arrange_Ring.h"
#include <d3dx9math.h>
#include <windows.h>

// �R���X�g���N�^
Ring::Ring()
{
	__DtTestPoint( __DtFunc_Ring, __DtStep_0 )
	ZeroMemory( &mStdCir, sizeof( StandardCircle ) );
	ZeroMemory( &mSData, sizeof( StarData ) );
	ZeroMemory( &mTData, sizeof( TurnData ) );
	__DtTestPoint( __DtFunc_Ring, __DtStep_1 )
}

// �f�X�g���N�^
Ring::~Ring()
{
	__DtTestPoint( __DtFunc_Ring, __DtStep_2 )
}

//---------------------------------------------------------------------
// < 2011/1/21 Keisuke_Hosoda >
//
// �֐����F Initialize
//
//  ���� �F < void >
// �߂�l�F < void >
//  ���� �F �������B�g�p�O�Ɉ�x�����ĂԂ���
//---------------------------------------------------------------------
void Ring::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	mTData.InputLock = false;
	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F Process
//
//  ���� �F < void >
// �߂�l�F < void >
//  ���� �F ���[�v�̒��ŌĂԂ���
//---------------------------------------------------------------------
void Ring::Process()
{
	__DtTestPoint( __DtFunc_Process, __DtStep_0 )
	mTData.OldTurnVec = mTData.TurnVec;

	// ��]���Ă��邩�ǂ���
	if ( mTData.TurnVec != 0 )
	{
		float ditect = 1;

		// ��]���͓��͂��󂯕t���Ȃ�
		__DtTestPoint(__DtFunc_Process, __DtStep_1)
		mTData.InputLock = true;

		// ��]����
		if ( mTData.TurnVec > 0 ) ditect = -1;

		mTData.Deg += mTData.TurnSpeed * ditect;
		mTData.TurnLimit += mTData.TurnSpeed;
	}

	// ��]�p�x��͈͓��Ɏ��߂�
	if ( mTData.Deg < 0 )
		mTData.Deg += 360;
	
	if ( mTData.Deg >= 360 )
		mTData.Deg -= 360;

	// ��]��̊���W�ɂ���Star�̓Y����
	if ( mSData.Angle <= mTData.TurnLimit )
	{
		__DtTestPoint(__DtFunc_Process, __DtStep_2)
		mTData.TurnVec   = 0;
		mTData.TurnLimit = 0;
		mTData.InputLock = false;

		if ( mTData.OldTurnVec > 0 )
		{
			__DtTestPoint(__DtFunc_Process, __DtStep_3)
			if ( mSData.Target < ( mSData.setNum-1 ) )
				++mSData.Target;
			else
				mSData.Target = 0;
		}
		else
		{
			__DtTestPoint(__DtFunc_Process, __DtStep_4)
			if ( mSData.Target > 0 )
				--mSData.Target;
			else
				mSData.Target = ( mSData.setNum-1 );
		}

		ResetDeg( &mSData.Target );
	}

	// �p�x����~����̍��W���擾
	for ( unsigned int i = 0; i < mSData.setNum; ++i )
	{
		__DtTestPoint(__DtFunc_Process, __DtStep_5)
		mTData.Rad = D3DXToRadian( mTData.Deg + ( mSData.Angle * i ) + mSData.OriginDeg );
		mSData.Pos[ i ].x = mStdCir.Origin.x + mStdCir.Radius.x * cos( mTData.Rad );
		mSData.Pos[ i ].y = mStdCir.Origin.y - mStdCir.Radius.y * sin( mTData.Rad );
	}
	__DtTestPoint( __DtFunc_Process, __DtStep_6 )
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F Release
//
//  ���� �F < void >
// �߂�l�F < void >
//  ���� �F ��������B�K�������I�ɌĂԂ���
//---------------------------------------------------------------------
void Ring::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
}

// �ȉ��Z�b�^���Q�b�^

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setCircleOrigin
//
//  ���� �F < const int x, const int y >
// �߂�l�F < void >
//  ���� �F �����w��̏ꏊ���~�̌��_�Ƃ���
//---------------------------------------------------------------------
void Ring::setCircleOrigin( const int x, const int y )
{
	__DtTestPoint( __DtFunc_setCircleOrigin, __DtStep_0 )
	mStdCir.Origin.x = static_cast< float >( x );
	mStdCir.Origin.y = static_cast< float >( y );
	__DtTestPoint( __DtFunc_setCircleOrigin, __DtStep_1 )
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setCircleSize
//
//  ���� �F < const float width, const float height >
// �߂�l�F < void >
//  ���� �F �~�̑傫���������Ŏw�肷��
//---------------------------------------------------------------------
void Ring::setCircleSize( const float width, const float height )
{
	__DtTestPoint( __DtFunc_setCircleSize, __DtStep_0 )
	mStdCir.Radius.x = width;
	mStdCir.Radius.y = height;
	__DtTestPoint( __DtFunc_setCircleSize, __DtStep_1 )
}

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
void Ring::setCircle( const int x, const int y, const float width, const float height )
{
	__DtTestPoint( __DtFunc_setCircle, __DtStep_0 )
	mStdCir.Origin.x = static_cast< float >( x );
	mStdCir.Origin.y = static_cast< float >( y );
	mStdCir.Radius.x = width;
	mStdCir.Radius.y = height;
	__DtTestPoint( __DtFunc_setCircle, __DtStep_1 )
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setStarNum
//
//  ���� �F < const unsigned int number >
// �߂�l�F < void >
//  ���� �F �~����ɕ��ԍ��W( Star )�̐���ݒ�
//---------------------------------------------------------------------
void Ring::setStarNum( const unsigned int number )
{
	__DtTestPoint( __DtFunc_setStarNum, __DtStep_0 )
	mSData.setNum = number;

	for ( unsigned int i = 0; i < number; ++i )
	{
		HVector2 star;
		__DtTestPoint(__DtFunc_setStarNum, __DtStep_1)
		ZeroMemory( &star, sizeof( HVector2 ) );
		mSData.Pos.push_back( star );
	}
	__DtTestPoint( __DtFunc_setStarNum, __DtStep_2 )
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setOriginDeg
//
//  ���� �F < const float degree >
// �߂�l�F < void >
//  ���� �F Star�̊�p�x�������w��
//---------------------------------------------------------------------
void Ring::setOriginDeg( const float degree )
{
	__DtTestPoint( __DtFunc_setOriginDeg, __DtStep_0 )
	mSData.OriginDeg = degree;
	__DtTestPoint( __DtFunc_setOriginDeg, __DtStep_1 )
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setTarget
//
//  ���� �F < const unsigned int idx >
// �߂�l�F < void >
//  ���� �F ��ʒu�Ɉ����w���Star��z�u
//---------------------------------------------------------------------
void Ring::setTarget( const unsigned int idx )
{
	__DtTestPoint( __DtFunc_setTarget, __DtStep_0 )
	mSData.Target = idx;
	__DtTestPoint( __DtFunc_setTarget, __DtStep_1 )
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setTurnDirection
//
//  ���� �F < const int direct >
// �߂�l�F < void >
//  ���� �F ��]�����A-1, 0, 1�Ŏw��
//---------------------------------------------------------------------
void Ring::setTurnDirection( const int direct )
{
	__DtTestPoint( __DtFunc_setTurnDirection, __DtStep_0 )
	mTData.TurnVec = direct;
	__DtTestPoint( __DtFunc_setTurnDirection, __DtStep_1 )
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setTurnSpeed
//
//  ���� �F < const float speed >
// �߂�l�F < void >
//  ���� �F ��ʒu�Ɉ����w���Star��z�u
//---------------------------------------------------------------------
void Ring::setTurnSpeed( const float speed )
{
	__DtTestPoint( __DtFunc_setTurnSpeed, __DtStep_0 )
	mTData.TurnSpeed = speed;
	__DtTestPoint( __DtFunc_setTurnSpeed, __DtStep_1 )
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F ResetDeg
//
//  ���� �F < const int target >
// �߂�l�F < void >
//  ���� �F ����W�Ɉ����w���Star���Z�b�g����
//---------------------------------------------------------------------
void Ring::ResetDeg( const unsigned int *target )
{
	__DtTestPoint( __DtFunc_ResetDeg, __DtStep_0 )
	calcAngle();
	mTData.Deg = 360 - ( mSData.Angle * static_cast< float >( *target ) );
	__DtTestPoint( __DtFunc_ResetDeg, __DtStep_1 )
}

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
void Ring::calcAngle()
{
	__DtTestPoint( __DtFunc_calcAngle, __DtStep_0 )
	if ( mSData.setNum != 0 )
		mSData.Angle = 360 / static_cast< float >( mSData.setNum );
	else
		mSData.Angle = 0;
	__DtTestPoint( __DtFunc_calcAngle, __DtStep_1 )
}

//=============================================================================
//								End of File
//=============================================================================