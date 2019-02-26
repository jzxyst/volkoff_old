//=============================================================================
/*! @addtogroup JZX
    @file       Typedef.h
    @brief      共通定数、マクロ、typedef等
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
      -# 作成
    - 2011/06 28 Hi-ra Mizuno
      -# typedef追加
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_TYPEDEF_H__
#define __INCLUDE_TYPEDEF_H__


/*! @par include */
#include <windows.h>
#include <string>



/*! @par マクロ */
//---------------------------------------------------------------------------
/*! @brief SAFE_DELETE

    ポインタを安全に解放する

	@param[in]      p ポインタ
*/
//---------------------------------------------------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) delete(p); (p) = NULL; }
#endif

//---------------------------------------------------------------------------
/*! @brief SAFE_DELETES

    ポインタ配列を安全に解放する

	@param[in]      p ポインタ配列
*/
//---------------------------------------------------------------------------
#ifndef SAFE_DELETES
#define SAFE_DELETES(p) { if(p) delete[](p); (p) = NULL; }
#endif

//---------------------------------------------------------------------------
/*! @brief SAFE_FREE

    mallocで確保したメモリを安全に解放する

	@param[in]      p ポインタ
*/
//---------------------------------------------------------------------------
#ifndef SAFE_FREE
#define SAFE_FREE(p) { if(p) ::free(p); (p) = NULL; }
#endif


//---------------------------------------------------------------------------
/*! @brief SAFE_RELEASE

    安全にReleaseメンバを呼び出す

	@param[in]      p ポインタ
*/
//---------------------------------------------------------------------------
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) (p)->Release(); (p) = NULL; }
#endif

#if 0

/*! @par typedef */
typedef signed char 		s8;
typedef signed short		s16;
typedef signed int  		s32;
typedef signed long long	s64;

typedef unsigned char		u8;
typedef unsigned short  	u16;
typedef unsigned int    	u32;
typedef unsigned long long  u64;

typedef float   			f32;
typedef double  			f64;

#endif


typedef std::basic_string<TCHAR> tstring;
typedef std::basic_stringstream<TCHAR> tstream;

#ifdef _UNICODE
#define tcout wcout
#else
#define tcout cout
#endif


typedef HRESULT (*LPPROC)(HWND,UINT,WPARAM,LPARAM);


#endif //End of Include Guard


//=============================================================================
//								End of File
//=============================================================================