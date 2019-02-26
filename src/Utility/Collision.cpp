//
// Collision.cpp
// Dat�t�@�C������f�[�^�𕜌����A
// �����蔻�������N���X
//

#include "StdAfx.h"
#include	"DT_Collision.h"	/* For DynamicTracer-TestPoint */
#include "Collision.h"
#include <windows.h>

// �R���X�g���N�^
Collision::Collision()
{
    __DtTestPoint( __DtFunc_Collision, __DtStep_0 )
    mReadFP = NULL;
	__DtTestPoint( __DtFunc_Collision, __DtStep_1 )
}

// �f�X�g���N�^
Collision::~Collision()
{
	__DtTestPoint( __DtFunc_Collision, __DtStep_2 )
}

// ������
void Collision::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	for ( int i = 0; i < SET_H_NUM*SET_V_NUM; ++i )
		ZeroMemory( &mLoadData[ i ], sizeof( Data ) );
	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
}

//
// LoadFile
// ���@�� const char* fileName_
// �߂�l void
//
// �����Ŏw�肳�ꂽ
// �����蔻��f�[�^�̓ǂݍ���
//
void Collision::LoadFile( const char* fileName_ )
{
    __DtTestPoint( __DtFunc_LoadFile, __DtStep_0 )
    if ( mReadFP )
    {
        __DtTestPoint(__DtFunc_LoadFile, __DtStep_1)
        fclose( mReadFP );
        mReadFP = NULL;
    }

	// �ǂݍ���--------------------------
	fopen_s( &mReadFP, fileName_, "rb" );
	if ( mReadFP == NULL )
	{
		__DtTestPoint(__DtFunc_LoadFile, __DtStep_2)
		printf( "Error:dat�t�@�C���I�[�v���Ɏ��s\n" );
		printf( "�t�@�C�������݂��Ȃ����A�p�X���Ⴄ�\��������܂��B\n" );
		printf( "File< %s >\n", fileName_ );
		fclose( mReadFP );
		exit( 1 );
	}
	fread( &mLoadData, sizeof( Data ), SET_H_NUM*SET_V_NUM, mReadFP );
	__DtTestPoint( __DtFunc_LoadFile, __DtStep_3 )
}

//
// getAtkCollision
// ���@�� const unsigned int ActionIdx, const unsigned int Frames
// �߂�l LRect
//
// �A�N�V�����ԍ��ƃR�}�ԍ���n����
// �@���̓���̍U���̓����蔻�肪�Ԃ�( x, y, width, height )
//
LRect* Collision::getAtkCollision( const unsigned int ActionIdx, const unsigned int Frames )
{
	int idx   = ActionIdx;
	int frame = Frames;

	// idx��2���
	__DtTestPoint( __DtFunc_getAtkCollision, __DtStep_0 )
	if ( ActionIdx >= 6 )
	{
		__DtTestPoint(__DtFunc_getAtkCollision, __DtStep_1)
		idx   -= 6;
		frame += 6;
	}

	mAtkArea.set(
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.V,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.V );

	// ���ׂĂO(=�f�[�^�Ȃ�)�̏ꍇnull���^�[��
	if ( mAtkArea.x == 0
		&& mAtkArea.y == 0
		&& mAtkArea.w == 0
		&& mAtkArea.h == 0 )
	{
		//printf( "�擾�ʒu Idx %d, Frame %d �Y���f�[�^�Ȃ�\n", ActionIdx, Frames );
		__DtTestPoint( __DtFunc_getAtkCollision, __DtStep_2 )
		return NULL;
	}

    /*
	printf( "�����蔻��擾:�w��ʒu%d,%d/�擾�ʒu%d,%d\n  �U�� ����:x %d, y %d, width %d, height %d\n",
		ActionIdx,
		Frames,
		idx,
		frame,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.V,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.V );
        */

	__DtTestPoint( __DtFunc_getAtkCollision, __DtStep_3 )
	return &mAtkArea;
}

//
// getDmgCollision
// ���@�� const unsigned int ActionIdx, const unsigned int Frames
// �߂�l LRect
//
// �A�N�V�����ԍ��ƃR�}�ԍ���n����
// �@���̓���̃_���[�W�̓����蔻�肪�Ԃ�( x, y, width, height )
//
LRect* Collision::getDmgCollision( const unsigned int ActionIdx, const unsigned int Frames )
{
	int idx   = ActionIdx;
	int frame = Frames;

	// idx��2���
	__DtTestPoint( __DtFunc_getDmgCollision, __DtStep_0 )
	if ( ActionIdx >= 6 )
	{
		__DtTestPoint(__DtFunc_getDmgCollision, __DtStep_1)
		idx   -= 6;
		frame += 6;
	}

	mDmgArea.set(
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_pos.H,
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_pos.V,
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_size.H,
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_size.V );

	// ���ׂĂO(=�f�[�^�Ȃ�)�̏ꍇnull���^�[��
	if ( mDmgArea.x == 0
		&& mDmgArea.y == 0
		&& mDmgArea.w == 0
		&& mDmgArea.h == 0 )
	{
		__DtTestPoint(__DtFunc_getDmgCollision, __DtStep_2)
		printf( "�擾�ʒu Idx %d, Frame %d �Y���f�[�^�Ȃ�\n", ActionIdx, Frames );
		__DtTestPoint( __DtFunc_getDmgCollision, __DtStep_3 )
		return NULL;
	}

	__DtTestPoint( __DtFunc_getDmgCollision, __DtStep_4 )
	return &mDmgArea;
}

//
// getOrigin
// ���@�� const unsigned int ActionIdx, const unsigned int Frames
// �߂�l LVector2
//
// �A�N�V�����ԍ��ƃR�}�ԍ���n����
// �@���̓���̊�_���Ԃ�( x, y )
//
LVector2 Collision::getOrigin( const unsigned int ActionIdx, const unsigned int Frames )
{
	LVector2    Origin;
	int idx   = ActionIdx;
	int frame = Frames;

	// idx��2���
	__DtTestPoint( __DtFunc_getOrigin, __DtStep_0 )
	if ( ActionIdx >= 6 )
	{
		__DtTestPoint(__DtFunc_getOrigin, __DtStep_1)
		idx   -= 6;
		frame += 6;
	}

	Origin.x = static_cast< float >( mLoadData[ idx*SET_H_NUM + frame ].origin.H );
	Origin.y = static_cast< float >( mLoadData[ idx*SET_H_NUM + frame ].origin.V );

	__DtTestPoint( __DtFunc_getOrigin, __DtStep_2 )
	return Origin;
}

// [�R�{] �U���p�����蔻����R�}�ԍ�����擾���� (�R�}�ԍ��͍��ォ��E�ɂ����� +1�A���ɍs���ɂ�� +12)
LRect* Collision::getAtkCollisionByIndex( const unsigned int index_ )
{
    __DtTestPoint( __DtFunc_getAtkCollisionByIndex, __DtStep_0 )
    mAtkArea.set(
		mLoadData[ index_ ].Atk_pos.H,
		mLoadData[ index_ ].Atk_pos.V,
		mLoadData[ index_ ].Atk_size.H,
		mLoadData[ index_ ].Atk_size.V );

	if ( mAtkArea.x == 0
		&& mAtkArea.y == 0
		&& mAtkArea.w == 0
		&& mAtkArea.h == 0 )
	{
		__DtTestPoint( __DtFunc_getAtkCollisionByIndex, __DtStep_1 )
		return NULL;
	}

    __DtTestPoint( __DtFunc_getAtkCollisionByIndex, __DtStep_2 )
    return &mAtkArea;
}

// [�R�{] �_���[�W�p�����蔻����R�}�ԍ�����擾����
LRect* Collision::getDmgCollisionByIndex( const unsigned int index_ )
{
    __DtTestPoint( __DtFunc_getDmgCollisionByIndex, __DtStep_0 )
    mDmgArea.set(
		mLoadData[ index_ ].Dmg_pos.H,
		mLoadData[ index_ ].Dmg_pos.V,
		mLoadData[ index_ ].Dmg_size.H,
		mLoadData[ index_ ].Dmg_size.V );

	if ( mDmgArea.x == 0
		&& mDmgArea.y == 0
		&& mDmgArea.w == 0
		&& mDmgArea.h == 0 )
	{
		__DtTestPoint( __DtFunc_getDmgCollisionByIndex, __DtStep_1 )
		return NULL;
	}

	__DtTestPoint( __DtFunc_getDmgCollisionByIndex, __DtStep_2 )
	return &mDmgArea;
}

// [�R�{] ���_���R�}�ԍ�����擾����
LVector2 Collision::getOriginByIndex( const unsigned int index_ )
{
    __DtTestPoint( __DtFunc_getOriginByIndex, __DtStep_0 )
    return LVector2( 
        static_cast< float >( mLoadData[ index_ ].origin.H ),
        static_cast< float >( mLoadData[ index_ ].origin.V ) );
}

//
// checkHit
// ���@�� const LVector3 alphaPos, const LRect* alpha,
//        const LVector3 betaPos,  const LRect* beta
// �߂�l bool
//
// �����蔻���Rect��n����
// �@�������Ă��邩�ǂ�����bool�ŕԂ�
//
bool Collision::checkHit( const LVector3 alphaPos, const LRect* alpha, const LVector3 betaPos, const LRect* beta )
{
	LRect L = *alpha;
	LRect R = *beta;

	__DtTestPoint( __DtFunc_checkHit, __DtStep_0 )
	L.x      += static_cast< int >( alphaPos.x );
	L.y      += static_cast< int >( alphaPos.y );
	L.w  += static_cast< int >( alphaPos.x );
	L.h += static_cast< int >( alphaPos.y );

	R.x      += static_cast< int >( betaPos.x );
	R.y      += static_cast< int >( betaPos.y );
	R.w  += static_cast< int >( betaPos.x );
	R.h += static_cast< int >( betaPos.y );

	// �����������ق�����
	if ( L.x > R.x )
	{
		LRect temp;

		__DtTestPoint(__DtFunc_checkHit, __DtStep_1)
		temp = L;
		L = R;
		R = temp;		
	}

	// L�̉E�[��R�̍��[�ȏ�
	if ( L.w >= R.x )
	{
		__DtTestPoint(__DtFunc_checkHit, __DtStep_2)
		if ( L.h >= R.y )
		{
			__DtTestPoint( __DtFunc_checkHit, __DtStep_3 )
			return true;
		}
		else if ( L.y <= R.h )
		{
			__DtTestPoint( __DtFunc_checkHit, __DtStep_4 )
			return true;
		}
	}

	__DtTestPoint( __DtFunc_checkHit, __DtStep_5 )
	return false;
}

// ���
void Collision::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	fclose( mReadFP );
	__DtTestPoint( __DtFunc_Release, __DtStep_1 )
}
// EOF