//=============================================================================
/*! 
    @addtogroup 
    @file       Packet.h
    @brief      Packet�N���X�w�b�_
    
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


//Include Guard
#ifndef __INCLUDE_PACKET_H__
#define __INCLUDE_PACKET_H__


/*! @class Packet
	@brief Packet�N���X

	�Œ蒷�o�b�t�@�������p�P�b�g�N���X
*/
class Packet
{
public:
	/*! @par public�����o�ϐ� */

private:
	/*! @par private�����o�ϐ� */
	char *m_pbyData;
	size_t m_unSize;


public:
	/*! @par ��O���� */
	Packet &operator = (const Packet &obj_);


public:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief Packet::Packet
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Packet();

	//---------------------------------------------------------------------------
	/*! 
		@brief Packet::Packet
	
		�R�s�[�R���X�g���N�^
	
		@param[in]      const Packet &obj_
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Packet(const Packet &obj_);

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
	Packet(const char *c_pbyData_,size_t unSize_);

	//---------------------------------------------------------------------------
	/*! 
		@brief Packet::~Packet
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~Packet();

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	char* getData() {return this->m_pbyData;}
    const char* getData() const {return this->m_pbyData;}

	size_t getSize() const {return this->m_unSize;}

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

private:
	/*! @par private�����o�֐� */

};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================