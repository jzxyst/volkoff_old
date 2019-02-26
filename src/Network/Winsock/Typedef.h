//=============================================================================
/*! @addtogroup 
    @file       Typedef.h
    @brief      共通定数、マクロ、typedef等
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/09/01
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
//=============================================================================
    @par        History
    - 2011/09/01 Hi-ra Mizuno
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_WINSOCK_TYPEDEF_H__
#define __INCLUDE_WINSOCK_TYPEDEF_H__


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
typedef signed int		    s32;
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


typedef unsigned int   SOCKID;
typedef unsigned int   IPv4N;
typedef unsigned long  IPv4L;
typedef char*          IPv4A;
typedef wchar_t*       IPv4W;
typedef unsigned short PORT;

typedef enum _ENUM_PROTOCOL
{
	PRT_UNDEF = 0,
	PRT_TCP,
	PRT_UDP,
	PRT_RAW,
}Protocol;


/*! @par define */
#define IP_HEADER_SIZE (20)  //IPヘッダサイズ
#define TCP_HEADER_SIZE (20) //TCPヘッダサイズ
#define UDP_HEADER_SIZE (8)  //UDPヘッダサイズ
#define ETHERNET_MTU (1500)  //イーサネットMTU
#define FDDI_MTU (4352)      //FDDI MTU

#define CWR (0x01) //輻輳制御ウィンドウ縮小通知ビット
#define ECE (0x02) //予約ビット。未使用
#define URG (0x04) //緊急ビット
#define ACK (0x08) //確認応答ビット 
#define PSH (0x10) //優先処理ビット
#define RST (0x20) //強制切断ビット
#define SYN (0x40) //同期ビット
#define FIN (0x80) //通信終了ビット


#endif //End of Include Guard


//=============================================================================
//								End of File
//=============================================================================