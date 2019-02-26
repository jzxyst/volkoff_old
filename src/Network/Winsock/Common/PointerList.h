//=============================================================================
/*! 
    @addtogroup 
    @file       PointerList.h
    @brief      PointerListクラスヘッダ
    
    ポインターを管理するリスト構造体
    
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
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_POINER_LIST_H__
#define __INCLUDE_POINER_LIST_H__


/*! @par include */
#include "./Typedef.h"
#include <list>


/*! @class PointerList
	@brief PointerListクラス

	コンソールを管理するクラス
*/
template <typename Ty> class PointerList
{
public:
	/*! @par publicメンバ変数 */

private:
	/*! @par privateメンバ変数 */
	std::list<Ty> m_liList;


public:
	/*! @par 例外処理 */


public:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief PointerList::PointerList
	
		デフォルトコンストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	PointerList() {}

	//---------------------------------------------------------------------------
	/*! 
		@brief PointerList::~PointerList
	
		デストラクタ
	
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
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
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
	/*! @par privateメンバ関数 */

};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================