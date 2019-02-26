//=============================================================================
/*! 
    @addtogroup 
    @file       Packet.cpp
    @brief      Packet�N���X�̎���
    
	�Œ蒷�o�b�t�@�������p�P�b�g�N���X
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/09/02
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/09/02 Hi-ra Mizuno
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Packet.h"	/* For DynamicTracer-TestPoint */
#include "./Typedef.h"
#include "./Packet.h"


//---------------------------------------------------------------------------
/*! 
	@brief Packet &operator = (const Packet &obj_);
*/
//---------------------------------------------------------------------------
Packet& Packet::operator = (const Packet &obj_)
{
	__DtTestPoint( __DtFunc_Packet, __DtStep_0 )
	this->m_pbyData = NULL;
	this->m_pbyData = new char[obj_.getSize()];
	this->m_unSize = obj_.getSize();

	::memcpy_s(this->m_pbyData,this->m_unSize,obj_.getData(),obj_.getSize());

	__DtTestPoint( __DtFunc_Packet, __DtStep_1 )
	return *this;
}


//---------------------------------------------------------------------------
/*! 
	@brief Packet::Packet

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Packet::Packet()
{
	__DtTestPoint( __DtFunc_Packet, __DtStep_2 )
	this->m_pbyData = NULL;
	this->m_pbyData = 0;
	__DtTestPoint( __DtFunc_Packet, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Packet::Packet

	�R�s�[�R���X�g���N�^

	@param[in]      const Packet &obj_
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Packet::Packet(const Packet &obj_)
{
	__DtTestPoint( __DtFunc_Packet, __DtStep_4 )
	this->m_pbyData = NULL;
	this->m_pbyData = new char[obj_.getSize()];
	this->m_unSize = obj_.getSize();

	::memcpy_s(this->m_pbyData,this->m_unSize,obj_.getData(),obj_.getSize());
	__DtTestPoint( __DtFunc_Packet, __DtStep_5 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Packet::Packet

	�R���X�g���N�^

	@param[in]      const char *c_pbyData_ - �f�[�^
	@param[in]      size_t     unsize_     - �f�[�^�T�C�Y
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Packet::Packet(const char *c_pbyData_,size_t unSize_)
{
	__DtTestPoint( __DtFunc_Packet, __DtStep_6 )
	this->m_pbyData = NULL;
	this->m_pbyData = new char[unSize_];
	this->m_unSize = unSize_;

	::memcpy_s(this->m_pbyData,this->m_unSize,c_pbyData_,unSize_);
	__DtTestPoint( __DtFunc_Packet, __DtStep_7 )
}


//---------------------------------------------------------------------------
/*! 
	@brief Packet::~Packet

	�f�X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Packet::~Packet()
{
	__DtTestPoint( __DtFunc_Packet, __DtStep_8 )
	SAFE_DELETES(this->m_pbyData);
	__DtTestPoint( __DtFunc_Packet, __DtStep_9 )
}


//=============================================================================
//								End of File
//=============================================================================