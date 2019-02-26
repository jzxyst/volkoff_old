//
// Collision.cpp
// Datファイルからデータを復元し、
// 当たり判定をするクラス
//

#include "StdAfx.h"
#include	"DT_Collision.h"	/* For DynamicTracer-TestPoint */
#include "Collision.h"
#include <windows.h>

// コンストラクタ
Collision::Collision()
{
    __DtTestPoint( __DtFunc_Collision, __DtStep_0 )
    mReadFP = NULL;
	__DtTestPoint( __DtFunc_Collision, __DtStep_1 )
}

// デストラクタ
Collision::~Collision()
{
	__DtTestPoint( __DtFunc_Collision, __DtStep_2 )
}

// 初期化
void Collision::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	for ( int i = 0; i < SET_H_NUM*SET_V_NUM; ++i )
		ZeroMemory( &mLoadData[ i ], sizeof( Data ) );
	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
}

//
// LoadFile
// 引　数 const char* fileName_
// 戻り値 void
//
// 引数で指定された
// 当たり判定データの読み込み
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

	// 読み込み--------------------------
	fopen_s( &mReadFP, fileName_, "rb" );
	if ( mReadFP == NULL )
	{
		__DtTestPoint(__DtFunc_LoadFile, __DtStep_2)
		printf( "Error:datファイルオープンに失敗\n" );
		printf( "ファイルが存在しないか、パスが違う可能性があります。\n" );
		printf( "File< %s >\n", fileName_ );
		fclose( mReadFP );
		exit( 1 );
	}
	fread( &mLoadData, sizeof( Data ), SET_H_NUM*SET_V_NUM, mReadFP );
	__DtTestPoint( __DtFunc_LoadFile, __DtStep_3 )
}

//
// getAtkCollision
// 引　数 const unsigned int ActionIdx, const unsigned int Frames
// 戻り値 LRect
//
// アクション番号とコマ番号を渡すと
// 　その動作の攻撃の当たり判定が返る( x, y, width, height )
//
LRect* Collision::getAtkCollision( const unsigned int ActionIdx, const unsigned int Frames )
{
	int idx   = ActionIdx;
	int frame = Frames;

	// idxが2列目
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

	// すべて０(=データなし)の場合nullリターン
	if ( mAtkArea.x == 0
		&& mAtkArea.y == 0
		&& mAtkArea.w == 0
		&& mAtkArea.h == 0 )
	{
		//printf( "取得位置 Idx %d, Frame %d 該当データなし\n", ActionIdx, Frames );
		__DtTestPoint( __DtFunc_getAtkCollision, __DtStep_2 )
		return NULL;
	}

    /*
	printf( "当たり判定取得:指定位置%d,%d/取得位置%d,%d\n  攻撃 判定:x %d, y %d, width %d, height %d\n",
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
// 引　数 const unsigned int ActionIdx, const unsigned int Frames
// 戻り値 LRect
//
// アクション番号とコマ番号を渡すと
// 　その動作のダメージの当たり判定が返る( x, y, width, height )
//
LRect* Collision::getDmgCollision( const unsigned int ActionIdx, const unsigned int Frames )
{
	int idx   = ActionIdx;
	int frame = Frames;

	// idxが2列目
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

	// すべて０(=データなし)の場合nullリターン
	if ( mDmgArea.x == 0
		&& mDmgArea.y == 0
		&& mDmgArea.w == 0
		&& mDmgArea.h == 0 )
	{
		__DtTestPoint(__DtFunc_getDmgCollision, __DtStep_2)
		printf( "取得位置 Idx %d, Frame %d 該当データなし\n", ActionIdx, Frames );
		__DtTestPoint( __DtFunc_getDmgCollision, __DtStep_3 )
		return NULL;
	}

	__DtTestPoint( __DtFunc_getDmgCollision, __DtStep_4 )
	return &mDmgArea;
}

//
// getOrigin
// 引　数 const unsigned int ActionIdx, const unsigned int Frames
// 戻り値 LVector2
//
// アクション番号とコマ番号を渡すと
// 　その動作の基準点が返る( x, y )
//
LVector2 Collision::getOrigin( const unsigned int ActionIdx, const unsigned int Frames )
{
	LVector2    Origin;
	int idx   = ActionIdx;
	int frame = Frames;

	// idxが2列目
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

// [山本] 攻撃用当たり判定をコマ番号から取得する (コマ番号は左上から右にかけて +1、下に行くにつれて +12)
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

// [山本] ダメージ用当たり判定をコマ番号から取得する
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

// [山本] 原点をコマ番号から取得する
LVector2 Collision::getOriginByIndex( const unsigned int index_ )
{
    __DtTestPoint( __DtFunc_getOriginByIndex, __DtStep_0 )
    return LVector2( 
        static_cast< float >( mLoadData[ index_ ].origin.H ),
        static_cast< float >( mLoadData[ index_ ].origin.V ) );
}

//
// checkHit
// 引　数 const LVector3 alphaPos, const LRect* alpha,
//        const LVector3 betaPos,  const LRect* beta
// 戻り値 bool
//
// 当たり判定のRectを渡すと
// 　当たっているかどうかをboolで返す
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

	// ｘが小さいほうが左
	if ( L.x > R.x )
	{
		LRect temp;

		__DtTestPoint(__DtFunc_checkHit, __DtStep_1)
		temp = L;
		L = R;
		R = temp;		
	}

	// Lの右端がRの左端以上
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

// 解放
void Collision::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	fclose( mReadFP );
	__DtTestPoint( __DtFunc_Release, __DtStep_1 )
}
// EOF