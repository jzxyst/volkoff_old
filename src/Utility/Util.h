//=============================================================================
//【 Util 】
//-----------------------------------------------------------------------------
///**
//  @file       Util.h
//  @brief      Util
//  @author     yama
//  @par
//              特に分類できないものとか、簡単な関数とかを書いておくところ。
//*/
//=============================================================================

#pragma once

//=============================================================================
// ■ Util クラス
//-----------------------------------------------------------------------------
///**
//  @brief      ユーティリティ関数。とりあえずモノステイト。
//*/
//=============================================================================
class Util
{
public:

    //---------------------------------------------------------------------
    ///**
    //  @brief      矩形同士が重なっているかを判定する
    //
    //  @param[in]  rect0_        : ワールド座標上の矩形
    //  @param[in]  rect1_        : ワールド座標上の矩形
    //
    //  @return     重なっていた場合 true
    //*/
    //---------------------------------------------------------------------
    static bool judgeCollitionRect( const LRect& rect0_, const LRect& rect1_ )
    {
        /*
        int l0, t0, r0, b0;
        int l1, t1, r1, b1;

        l0 = rect0_.x;
        t0 = rect0_.y - rect0_.height;
        b0 = rect0_.y;
        r0 = rect0_.x + rect0_.width;

        l1 = rect1_.x;
        t1 = rect1_.y - rect1_.height;
        b1 = rect1_.y;
        r1 = rect1_.x + rect1_.width;

        if ( l0 <= r1 && r0 >= l1 && t0 <= b1 && b0 >= t1 )
        {
            return true;
        }

        return false;
        */

        if ( rect0_.x                       <= ( rect1_.x + rect1_.w ) &&
             ( rect0_.x + rect0_.w )    >= rect1_.x &&
             ( rect0_.y - rect0_.h )   <= rect1_.y &&
             rect0_.y                       >= ( rect1_.y - rect1_.h ) )
        {
            return true;
        }

        return false;
    }

    //---------------------------------------------------------------------
    ///**
    //  @brief      数値の各桁の値を配列に格納する
    //
    //  @param[in]  num_        : 数値 (符号なし)
    //  @param[in]  max_digits_ : 最大桁数 (桁数に満たない場合は 0 を格納する)
	//  @param[in]  result_     : 結果を格納する配列(上の桁から順)
    //*/
    //---------------------------------------------------------------------
    static void numberToArray( u32 num_, u32 max_digits_, u32* result_ )
    {
        int prev;
        int div = 10 * max_digits_;
        int idx = max_digits_ - 1;  // 配列への書き込み位置

        for ( ; idx >= 0; --idx )
        {
            result_[ idx ] = num_ % 10;
            num_ /= 10;
        }
    }

	/// numberToArray() において、上の桁が 0 の場合は そこに -1 を格納する
	static void numberToArray2( u32 num_, u32 max_digits_, int* result_ )
    {
        u32 result[ 64 ];
		numberToArray( num_, max_digits_, result );
		int i = 0;
		for ( ; i < max_digits_; ++i )
		{
			if ( result[ i ] == 0 )
			{
				result_[ i ] = -1;
			}
			else
			{
				break;
			}
		}
		for ( ; i < max_digits_; ++i )
		{
			result_[ i ] = result[ i ];
		}
    }
};

//=============================================================================
//								end of file
//=============================================================================