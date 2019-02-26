
#pragma once


template < typename TYPE_ >
class RapidNumber
{
public:

    /// �f�t�H���g�R���X�g���N�^
    RapidNumber()
        : mNowNumber    ( 0 )
        , mDestNumber   ( 0 )
        , mDivSpeed     ( 1.0f / 10.0f )
    {}

public:

    /// ���݂̒l�̎擾
    TYPE_ getValue() const 
    {
        return mNowNumber;
    }

    /// �����l�̐ݒ�
    void setInitValue( TYPE_ num_ )
    {
        mNowNumber = num_;
    }

    /// �ڕW�l�̐ݒ�
    void set( TYPE_ num_ )
    {
        mDestNumber = num_;
    }

    /// �l�ω��̑����̐ݒ� ( 1���傫���l��ݒ肷�邱�ƁB�f�t�H���g�� 10 )
    void setSpeed( u32 speed_ )
    {
        mDivSpeed = 1.0f / speed_;
    }

    /// �ω��I������
    bool isFinished() const
    {
        return ( mDestNumber == mNowNumber );
    }

    /// �t���[���X�V
    void update()
    {
        if ( mNowNumber != mDestNumber )
        {
            if ( abs( mNowNumber - mDestNumber ) < 2.0f )   // ���}���u
            {
                mNowNumber = mDestNumber;
                return;
            }
            int sign = ( mNowNumber > mDestNumber ) ? -1 : 1;
            mNowNumber = mNowNumber + static_cast< TYPE_ >( sign * LMath::max< TYPE_ >( abs( mDestNumber - mNowNumber ) * mDivSpeed, (TYPE_)1 ) );
        }
    }

private:

    TYPE_   mNowNumber;     ///< ���݂̒l
    TYPE_   mDestNumber;    ///< �ڕW�l
    lnfloat mDivSpeed;
};