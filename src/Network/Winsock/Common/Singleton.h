//=============================================================================
/*! 
    @addtogroup 
    @file       Singleton.h
    @brief      Singleton�N���X�w�b�_
    
    Singleton�e���v���[�g�N���X
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/06/20
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
//=============================================================================
    @par        History
    - 2011/06/20 Hi-ra Mizuno
      -# �쐬
    - 2011/06/28 Hi-ra Mizuno
      -# JZX���珜�O
*/
//=============================================================================


/*! @par Include Guard */
#ifndef __INCLUDE_SINGLETON_H__
#define __INCLUDE_SINGLETON_H__


/*! @par include */


/*! @class Singleton
    @brief Singleton�N���X

	�V���O���g���𕽈ՂɎ�������e���v���[�g�N���X
*/
template <typename Ty> class Singleton
{
public:
	/*! @par public�����o�ϐ� */

private:
	/*! @par private�����o�ϐ� */


private:
	/*! @par ��O���� */
	Singleton(const Singleton &obj);

	Singleton &operator = (const Singleton &obj);

public:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */

protected:
	/*! @par Singleton */
	//---------------------------------------------------------------------------
	/*! 
		@brief Singleton::Singleton
	
	    �f�t�H���g�R���X�g���N�^
	
		@param[in]      void
	    @return         none
	    @exception      none
	*/
	//---------------------------------------------------------------------------
	Singleton() {;}

	//---------------------------------------------------------------------------
	/*! 
		@brief Singleton::~Singleton
	
	    �f�X�g���N�^
	
		@param[in]      void
	    @return         none
	    @exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~Singleton() {;}

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! 
		@brief Singleton::getInstance
	
	    �C���X�^���X��Ԃ�
	
		@param[in]      void
	    @return         Ty*
	    @exception      none
	*/
	//---------------------------------------------------------------------------
	static Ty* getInstance() {static Ty CInstance; return &CInstance;}

private:
	/*! @par private�����o�֐� */

};


#endif //End of Include Guard


//=============================================================================
//								End of File
//=============================================================================