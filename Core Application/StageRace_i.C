

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Dec 06 21:35:23 2012
 */
/* Compiler settings for StageRace.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ISRHalfStage,0x55B2C551,0x69F1,0x43D7,0x9D,0xCA,0x59,0x98,0x9C,0x3B,0x18,0x08);


MIDL_DEFINE_GUID(IID, IID_IStageRaceDoc,0xEB26427B,0x82AC,0x45FA,0x80,0xAF,0xF9,0x3C,0x8A,0x31,0x89,0xAD);


MIDL_DEFINE_GUID(IID, IID_IStageRaceServer,0x31AC26B2,0x80B3,0x4ACF,0xBB,0xB9,0x68,0x6C,0xA5,0x5E,0xDA,0x44);


MIDL_DEFINE_GUID(IID, LIBID_StageRaceLib,0x0F5CA62A,0x5B01,0x4FC6,0x9D,0x68,0x4F,0xC2,0x23,0xAE,0xF8,0x9C);


MIDL_DEFINE_GUID(CLSID, CLSID_StageRaceServer,0x5AD7E1A3,0xB139,0x4A1B,0x83,0xE0,0x11,0x7F,0x2F,0x38,0x31,0xD0);


MIDL_DEFINE_GUID(CLSID, CLSID_StageRaceDoc,0xC8B27B99,0xDDC6,0x457E,0xB7,0xDC,0x8D,0xC3,0x50,0x79,0xA9,0xC6);


MIDL_DEFINE_GUID(CLSID, CLSID_SRHalfStage,0x6612404C,0x66ED,0x4CAB,0x85,0x06,0x4B,0x8B,0x59,0x67,0xF1,0x8C);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



