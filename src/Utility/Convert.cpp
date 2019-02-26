//=============================================================================
/*! 
    @addtogroup 
    @file       Convert.cpp
    @brief      ��������n�֐��Q
    
    Convert�̎���
    
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
    - 2011/06/28
      -# �t�@�C������JZString����Convert�ɕύX
    - 2011/08/25
      -# ���m�X�e�[�g�X�^�C���ɕύX
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_Convert.h"	/* For DynamicTracer-TestPoint */
#include "./Convert.h"
#include <vector>


//---------------------------------------------------------------------------
/*! 
	@brief Convert::StrAtoW

	char�^����wchar_t�^�ɕϊ�����

	@param[in]      const char *c_pszStr_ :�ϊ��Ώە�����
	@return         wchar_t*
	- �ϊ��㕶����
	@exception      none
*/
//---------------------------------------------------------------------------
wchar_t* Convert::StrAtoW(const char *c_pszStr_)
{
	static std::vector<wchar_t> s_vwszBuff;
	size_t unLength = 0;

	__DtTestPoint( __DtFunc_StrAtoW, __DtStep_0 )
	if(s_vwszBuff.capacity() < ::strlen(c_pszStr_))
		s_vwszBuff.resize(::strlen(c_pszStr_) * sizeof(wchar_t));

	::mbstowcs_s(&unLength,&s_vwszBuff[0],s_vwszBuff.capacity(),c_pszStr_,_TRUNCATE);

	__DtTestPoint( __DtFunc_StrAtoW, __DtStep_1 )
	return &s_vwszBuff[0];
}


//---------------------------------------------------------------------------
/*! 
	@brief Convert::StrWtoA

	wchar_t�^����char�^�ɕϊ�����

	@param[in]      const wchar_t *c_pwszStr_ :�ϊ��Ώە�����
	@return         char*
	- �ϊ��㕶����
	@exception      none
*/
//---------------------------------------------------------------------------
char* Convert::StrWtoA(const wchar_t *c_pwszStr_)
{
	static std::vector<char> s_vszBuff;
	size_t unLength = 0;

	__DtTestPoint( __DtFunc_StrWtoA, __DtStep_0 )
	if(s_vszBuff.capacity() < ::wcslen(c_pwszStr_))
		s_vszBuff.resize(::wcslen(c_pwszStr_));

	if(::wcstombs_s(&unLength,&s_vszBuff[0],s_vszBuff.capacity(),c_pwszStr_,_TRUNCATE))
		return NULL;

	__DtTestPoint( __DtFunc_StrWtoA, __DtStep_1 )
	return &s_vszBuff[0];
}


//=============================================================================
//								End of File
//=============================================================================