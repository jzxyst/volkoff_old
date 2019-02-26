//=============================================================================
/*! 
    @addtogroup 
    @file       PointerList.h
    @brief      PointerList�N���X�w�b�_
    
    �|�C���^�[���Ǘ����郊�X�g�\����
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 Hi-ra Mizuno
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_POINER_LIST_H__
#define __INCLUDE_POINER_LIST_H__


/*! @par include */
#include "./Typedef.h"
#include <list>


/*! @class PointerList
	@brief PointerList�N���X

	�R���\�[�����Ǘ�����N���X
*/
template <typename Ty> class PointerList
{
public:
	/*! @par public�����o�ϐ� */

private:
	/*! @par private�����o�ϐ� */
	std::list<Ty> m_liList;


public:
	/*! @par ��O���� */


public:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief PointerList::PointerList
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	PointerList() {}

	//---------------------------------------------------------------------------
	/*! 
		@brief PointerList::~PointerList
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~PointerList()
	{
		this->clear();
	}

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief Function	*/
	//---------------------------------------------------------------------------
	bool empty() {return this->m_liList.empty();}

	bool size() {return this->m_liList.size();}

	void push_back(typename Ty p) {this->m_liList.push_back(p);}

	void push_front(typename Ty p) {this->m_liList.push_front(p);}

	void pop_back()
	{
		if(!this->m_liList.empty())
		{
			SAFE_DELETE(this->m_liList.back());
			this->m_liList.pop_back();
		}

		return;
	}

	void pop_front()
	{
		if(!this->m_liList.empty())
		{
			SAFE_DELETE(this->m_liList.front());
			this->m_liList.pop_front();
		}

		return;
	}

	void clear()
	{
		while(!this->m_liList.empty())
		{
			SAFE_DELETE(this->m_liList.front());
			this->m_liList.pop_front();
		}

		return;
	}

	typename Ty front() {return this->m_liList.front();}
	
	typename Ty back() {return this->m_liList.back();}

private:
	/*! @par private�����o�֐� */

};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================