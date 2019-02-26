//=============================================================================
//�y Util �z
//-----------------------------------------------------------------------------
///**
//  @file       Util.h
//  @brief      Util
//  @author     yama
//  @par
//              ���ɕ��ނł��Ȃ����̂Ƃ��A�ȒP�Ȋ֐��Ƃ��������Ă����Ƃ���B
//*/
//=============================================================================

#pragma once

//=============================================================================
// �� Util �N���X
//-----------------------------------------------------------------------------
///**
//  @brief      ���[�e�B���e�B�֐��B�Ƃ肠�������m�X�e�C�g�B
//*/
//=============================================================================
class Util
{
public:

    //---------------------------------------------------------------------
    ///**
    //  @brief      ��`���m���d�Ȃ��Ă��邩�𔻒肷��
    //
    //  @param[in]  rect0_        : ���[���h���W��̋�`
    //  @param[in]  rect1_        : ���[���h���W��̋�`
    //
    //  @return     �d�Ȃ��Ă����ꍇ true
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
    //  @brief      ���l�̊e���̒l��z��Ɋi�[����
    //
    //  @param[in]  num_        : ���l (�����Ȃ�)
    //  @param[in]  max_digits_ : �ő包�� (�����ɖ����Ȃ��ꍇ�� 0 ���i�[����)
	//  @param[in]  result_     : ���ʂ��i�[����z��(��̌����珇)
    //*/
    //---------------------------------------------------------------------
    static void numberToArray( u32 num_, u32 max_digits_, u32* result_ )
    {
        int prev;
        int div = 10 * max_digits_;
        int idx = max_digits_ - 1;  // �z��ւ̏������݈ʒu

        for ( ; idx >= 0; --idx )
        {
            result_[ idx ] = num_ % 10;
            num_ /= 10;
        }
    }

	/// numberToArray() �ɂ����āA��̌��� 0 �̏ꍇ�� ������ -1 ���i�[����
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