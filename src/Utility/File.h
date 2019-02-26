//=============================================================================
/*! 
    @addtogroup 
    @file       File.h
    @brief      File�N���X�w�b�_
    
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
    - 2011/06/28 Hi-ra Mizuno
      -# JZX���珜�O
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_FILE_H__
#define __INCLUDE_FILE_H__


/*! @par include */
#include <iostream>
#include <stdlib.h>
#include <vector>

namespace JZX
{

/*! @enum FileParam
    @brief  �G���[�R�[�h
*/
typedef enum _ENUM_FILE_PARAM
{
	FILE_UNDEF = 0,
	FILE_OPEN_SUCCEED,
	FILE_OPEN_FAILED
}FileParam;


/*! @class File
	@brief File�N���X

	�t�@�C���������蕽�Ղɂ���N���X
*/
class File
{
public:
	/*! @par public�����o�ϐ� */

private:
	/*! @par private�����o�ϐ� */
	std::string m_strFileName;
	std::string m_strMode;

	std::vector<char> m_vszMode;
	FILE *m_pfFile;
	fpos_t m_nSize;

	FileParam m_eFileParam;


public:
	/*! @par ��O���� */


public:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief File::File
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	File();

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
	File(const char *c_pszFileName_,const char *c_pszMode_);

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
	File(const wchar_t *c_pwszFileName_,const char *c_pszMode_);

	//---------------------------------------------------------------------------
	/*! 
		@brief File::~File
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~File();

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	FILE* getFile() const {return this->m_pfFile;}

	fpos_t getSize() const {return this->m_nSize;}

	FileParam getFileParam() const {return this->m_eFileParam;}

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

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
	bool Open(const char *c_pszFileName_,const char *c_pszMode_);

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
	bool Close();

private:
	/*! @par private�����o�֐� */

};

} // namespace JZX

//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================