//=============================================================================
/*! 
    @addtogroup 
    @file       Fort.h
    @brief      ฉฎ@eIuWFNg
    
    FortNXฬ่`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/11/2
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/2 matsui
      -# ์ฌ
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_FORT_H__
#define __INCLUDE_FORT_H__


/*! @par include */
#include "./../GameObject.h"
#include "./../attackedobject.h"


/*! @par global */
static const char g_szFortFilePath[] = "./Data/Graphics/Object/Fort.png";
static const char g_szFortFilePath2[] = "./Data/Graphics/Object/Black.png";
static const int scg_nFortLife[] = {10,30,50,60};         //@eฬฯvอiฬอj
static const int scg_nReactionSpeed[] = {2,2,2,2};        //@eฬpx๐โณท้ิu
static const int scg_nSearchRangeX[] = {400,400,400,400}; //@eฬฝฃ XภW
static const int scg_nSearchRangeY[] = {400,400,400,400}; //@eฬฝฃ YภW
static const int scg_nAttackRangeX[] = {400,400,400,400}; //@eฬUฃ XภW
static const int scg_nAttackRangeY[] = {400,400,400,400}; //@eฬUฃ YภW
static const int scg_nShootSpeed[] = {3,4,5,6};           //eฌ
static const int scg_nShootDamage[] = {10,10,10,10};          //eฬะอ
static const int scg_nAttackIntv[] = {150,120,130,130};   //@eฬUิu
static const int scg_nShootIntv[] = {5,4,2,4};            //1๑ฬUฬญหิu
static const int scg_nShootNum[] = {4,6,7,6};             //1๑ฬUฬญห๑


/*! @enum FortAction */
typedef enum _ENUM_FORT_ACTION
{
	FORT_ACT_UNDEF,        //ข่`
	FORT_ACT_WAIT,         //า@
	FORT_ACT_SEARCH,       //T๕
	FORT_ACT_ATTACK_RANGE, //Uออเ
	FORT_ACT_ATTACK,       //U
}FortAction;


/*! @class Ladder */
class Fort : public AttackedObject
{
private:
	LBatchPanel mPanel;
	LBatchPanel mPanel2;
	int m_nFrame;
	int m_nAttackFrame;
	int m_nShootFrame;
	int m_nShootNum;
	LVector3 mShootVec;
	FortAction m_eAction;

public:
	//---------------------------------------------------------------------------
	/*! @brief oQb^[ */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_FORT; }

	//---------------------------------------------------------------------------
	/*! @brief oZb^[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::Fort

		ftHgRXgN^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Fort();

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::~Fort

		fXgN^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Fort();

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::Initialize

		๚ป

		@param[in]      void
		@return         bool
		- true  ฌ๗
		- false ธs
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize();

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::Release

		Iน

		@param[in]      void
		@return         bool
		- true  ฌ๗
		- false ธs
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::Update

		t[XV

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::HandleEvent

		Cxg

		@param[in]      EventType event_ Cxg^Cv
		@param[in]      void      *args_ f[^(KษLXgท้)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	const LRect* getBoundingRect();
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================