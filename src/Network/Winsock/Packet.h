//=============================================================================
/*! 
    @addtogroup 
    @file       Packet.h
    @brief      Packetクラスヘッダ
    
	固定長バッファを内包したパケットクラス
    
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
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_PACKET_H__
#define __INCLUDE_PACKET_H__


/*! @class Packet
	@brief Packetクラス

	固定長バッファを内包したパケットクラス
*/
class Packet
{
public:
	/*! @par publicメンバ変数 */

private:
	/*! @par privateメンバ変数 */
	char *m_pbyData;
	size_t m_unSize;


public:
	/*! @par 例外処理 */
	Packet &operator = (const Packet &obj_);


public:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief Packet::Packet
	
		デフォルトコンストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Packet();

	//---------------------------------------------------------------------------
	/*! 
		@brief Packet::Packet
	
		コピーコンストラクタ
	
		@param[in]      const Packet &obj_
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Packet(const Packet &obj_);

	//---------------------------------------------------------------------------
	/*! 
		@brief Packet::Packet
	
		コンストラクタ
	
		@param[in]      const char *c_pbyData_ - データ
		@param[in]      size_t     unsize_     - データサイズ
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Packet(const char *c_pbyData_,size_t unSize_);

	//---------------------------------------------------------------------------
	/*! 
		@brief Packet::~Packet
	
		デストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~Packet();

public:
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	char* getData() {return this->m_pbyData;}
    const char* getData() const {return this->m_pbyData;}

	size_t getSize() const {return this->m_unSize;}

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

private:
	/*! @par privateメンバ関数 */

};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================