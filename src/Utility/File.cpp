//=============================================================================
/*! 
    @addtogroup 
    @file       File.cpp
    @brief      File�N���X�̎���
    
    �t�@�C���������蕽�Ղɂ���N���X
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/06/23
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/06/23 Hi-ra Mizuno
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_File.h"	/* For DynamicTracer-TestPoint */
#include "./File.h"
#include "./Convert.h"

namespace JZX
{

//---------------------------------------------------------------------------
/*! 
	@brief File::File

    �f�t�H���g�R���X�g���N�^

	@param[in]      void
    @return         none
    @exception      none
*/
//---------------------------------------------------------------------------
File::File()
{
	__DtTestPoint( __DtFunc_File, __DtStep_0 )
	this->m_pfFile = NULL;
	this->m_nSize = 0;
	this->m_eFileParam = FILE_UNDEF;
	__DtTestPoint( __DtFunc_File, __DtStep_1 )
}


//---------------------------------------------------------------------------
/*! 
	@brief File::File

    �R���X�g���N�^

	@param[in]      const char *c_pszFileName_ :�t�@�C���p�X
	@param[in]      const char *c_pszMode_     :���[�h
    @return         none
    @exception      none
*/
//---------------------------------------------------------------------------
File::File(const char *c_pszFileName_,const char *c_pszMode_)
{
	__DtTestPoint( __DtFunc_File, __DtStep_2 )
	this->m_pfFile = NULL;
	this->m_nSize = 0;
	this->m_eFileParam = FILE_UNDEF;

	this->Open(c_pszFileName_,c_pszMode_);
	__DtTestPoint( __DtFunc_File, __DtStep_3 )
}


//---------------------------------------------------------------------------
/*! 
	@brief File::File

    �R���X�g���N�^

	@param[in]      const wchar_t *c_pwszFileName_ :�t�@�C���p�X
	@param[in]      const char *c_pszMode_         :���[�h
    @return         none
    @exception      none
*/
//---------------------------------------------------------------------------
File::File(const wchar_t *c_pwszFileName_,const char *c_pszMode_)
{
	__DtTestPoint( __DtFunc_File, __DtStep_4 )
	this->m_pfFile = NULL;
	this->m_nSize = 0;
	this->m_eFileParam = FILE_UNDEF;

	this->Open(Convert::StrWtoA(c_pwszFileName_),c_pszMode_);
	__DtTestPoint( __DtFunc_File, __DtStep_5 )
}


//---------------------------------------------------------------------------
/*! 
	@brief File::~File

    �f�X�g���N�^

	@param[in]      void
    @return         none
    @exception      none
*/
//---------------------------------------------------------------------------
File::~File()
{
	__DtTestPoint( __DtFunc_File, __DtStep_6 )
	this->Close();
	__DtTestPoint( __DtFunc_File, __DtStep_7 )
}


//---------------------------------------------------------------------------
/*! 
	@brief File::Open

	�t�@�C�����J��

	@param[in]      const char *c_pszFileName_ :�t�@�C���p�X
	@param[in]      const char *c_pszMode_     :���[�h
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool File::Open(const char *c_pszFileName_,const char *c_pszMode_)
{
	__DtTestPoint( __DtFunc_Open, __DtStep_0 )
	this->m_strFileName = c_pszFileName_;
	this->m_strMode = c_pszMode_;

	if(!(::fopen_s(&this->m_pfFile,this->m_strFileName.c_str(),this->m_strMode.c_str())))
	{
		__DtTestPoint(__DtFunc_Open, __DtStep_1)
		this->m_eFileParam = FILE_OPEN_SUCCEED;
	}
	else
	{
		__DtTestPoint(__DtFunc_Open, __DtStep_2)
		this->m_eFileParam = FILE_OPEN_FAILED;

		__DtTestPoint( __DtFunc_Open, __DtStep_3 )
		return false;
	}

	if(this->m_pfFile)
	{
		__DtTestPoint(__DtFunc_Open, __DtStep_4)
		if(::fseek(this->m_pfFile,0,SEEK_END))
			return false;

		if(::fgetpos(this->m_pfFile,&this->m_nSize))
			return false;

		if(::fseek(this->m_pfFile,0,SEEK_SET))
			return false;
	}

	__DtTestPoint( __DtFunc_Open, __DtStep_5 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief File::Close

	�t�@�C�������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool File::Close()
{
	bool bRes = false;

	__DtTestPoint( __DtFunc_Close, __DtStep_0 )
	if(this->m_pfFile)
	{
		__DtTestPoint(__DtFunc_Close, __DtStep_1)
		if(::fclose(this->m_pfFile))
		{
			__DtTestPoint(__DtFunc_Close, __DtStep_2)
			this->m_pfFile = NULL;
			bRes = true;
		}
	}

	__DtTestPoint( __DtFunc_Close, __DtStep_3 )
	return bRes;
}

} // namespace JZX

//=============================================================================
//								End of File
//=============================================================================