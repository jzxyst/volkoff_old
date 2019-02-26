//=============================================================================
/*! @addtogroup 
    @file       Typedef.h
    @brief      ���ʒ萔�A�}�N���Atypedef��
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
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_WINSOCK_TYPEDEF_H__
#define __INCLUDE_WINSOCK_TYPEDEF_H__


/*! @par include */
#include <windows.h>
#include <string>


/*! @par �}�N�� */
//---------------------------------------------------------------------------
/*! @brief SAFE_DELETE

    �|�C���^�����S�ɉ������

	@param[in]      p �|�C���^
*/
//---------------------------------------------------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) delete(p); (p) = NULL; }
#endif

//---------------------------------------------------------------------------
/*! @brief SAFE_DELETES

    �|�C���^�z������S�ɉ������

	@param[in]      p �|�C���^�z��
*/
//---------------------------------------------------------------------------
#ifndef SAFE_DELETES
#define SAFE_DELETES(p) { if(p) delete[](p); (p) = NULL; }
#endif

//---------------------------------------------------------------------------
/*! @brief SAFE_FREE

    malloc�Ŋm�ۂ��������������S�ɉ������

	@param[in]      p �|�C���^
*/
//---------------------------------------------------------------------------
#ifndef SAFE_FREE
#define SAFE_FREE(p) { if(p) ::free(p); (p) = NULL; }
#endif


//---------------------------------------------------------------------------
/*! @brief SAFE_RELEASE

    ���S��Release�����o���Ăяo��

	@param[in]      p �|�C���^
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
#define IP_HEADER_SIZE (20)  //IP�w�b�_�T�C�Y
#define TCP_HEADER_SIZE (20) //TCP�w�b�_�T�C�Y
#define UDP_HEADER_SIZE (8)  //UDP�w�b�_�T�C�Y
#define ETHERNET_MTU (1500)  //�C�[�T�l�b�gMTU
#define FDDI_MTU (4352)      //FDDI MTU

#define CWR (0x01) //�t�s����E�B���h�E�k���ʒm�r�b�g
#define ECE (0x02) //�\��r�b�g�B���g�p
#define URG (0x04) //�ً}�r�b�g
#define ACK (0x08) //�m�F�����r�b�g 
#define PSH (0x10) //�D�揈���r�b�g
#define RST (0x20) //�����ؒf�r�b�g
#define SYN (0x40) //�����r�b�g
#define FIN (0x80) //�ʐM�I���r�b�g


#endif //End of Include Guard


//=============================================================================
//								End of File
//=============================================================================