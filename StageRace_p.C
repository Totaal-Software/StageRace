/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun May 08 16:17:16 2005
 */
/* Compiler settings for D:\Projects\StageRace 2005\StageRace.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "StageRace_i.h"

#define TYPE_FORMAT_STRING_SIZE   1081                              
#define PROC_FORMAT_STRING_SIZE   727                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISRHalfStage, ver. 0.0,
   GUID={0x55B2C551,0x69F1,0x43D7,{0x9D,0xCA,0x59,0x98,0x9C,0x3B,0x18,0x08}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISRHalfStage_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short ISRHalfStage_FormatStringOffsetTable[] = 
    {
    0,
    34,
    68,
    108,
    148,
    188,
    234,
    274,
    302,
    330
    };

static const MIDL_SERVER_INFO ISRHalfStage_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISRHalfStage_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ISRHalfStage_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISRHalfStage_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(13) _ISRHalfStageProxyVtbl = 
{
    &ISRHalfStage_ProxyInfo,
    &IID_ISRHalfStage,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* ISRHalfStage::SetArrivalByTime */ ,
    (void *)-1 /* ISRHalfStage::SetArrivalByRank */ ,
    (void *)-1 /* ISRHalfStage::SetArrival */ ,
    (void *)-1 /* ISRHalfStage::GetArrivalByRank */ ,
    (void *)-1 /* ISRHalfStage::GetArrivalByStaNo */ ,
    (void *)-1 /* ISRHalfStage::GetArrivalByTime */ ,
    (void *)-1 /* ISRHalfStage::GetStart */ ,
    (void *)-1 /* ISRHalfStage::ResetArrival */ ,
    (void *)-1 /* ISRHalfStage::EnumerateStarts */ ,
    (void *)-1 /* ISRHalfStage::SetTimingIdle */
};

const CInterfaceStubVtbl _ISRHalfStageStubVtbl =
{
    &IID_ISRHalfStage,
    &ISRHalfStage_ServerInfo,
    13,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IStageRaceDoc, ver. 0.0,
   GUID={0xEB26427B,0x82AC,0x45FA,{0x80,0xAF,0xF9,0x3C,0x8A,0x31,0x89,0xAD}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IStageRaceDoc_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IStageRaceDoc_FormatStringOffsetTable[] = 
    {
    352,
    386,
    414,
    454,
    488,
    528,
    562
    };

static const MIDL_SERVER_INFO IStageRaceDoc_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IStageRaceDoc_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IStageRaceDoc_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IStageRaceDoc_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(10) _IStageRaceDocProxyVtbl = 
{
    &IStageRaceDoc_ProxyInfo,
    &IID_IStageRaceDoc,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* IStageRaceDoc::GetCountHalfStages */ ,
    (void *)-1 /* IStageRaceDoc::GetCountFullStages */ ,
    (void *)-1 /* IStageRaceDoc::GetHalfStageName */ ,
    (void *)-1 /* IStageRaceDoc::GetFullStageName */ ,
    (void *)-1 /* IStageRaceDoc::GetHalfStage */ ,
    (void *)-1 /* IStageRaceDoc::CompetitorExists */ ,
    (void *)-1 /* IStageRaceDoc::GetCompetitor */
};

const CInterfaceStubVtbl _IStageRaceDocStubVtbl =
{
    &IID_IStageRaceDoc,
    &IStageRaceDoc_ServerInfo,
    10,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IStageRaceServer, ver. 0.0,
   GUID={0x31AC26B2,0x80B3,0x4ACF,{0xBB,0xB9,0x68,0x6C,0xA5,0x5E,0xDA,0x44}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IStageRaceServer_ServerInfo;

#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short IStageRaceServer_FormatStringOffsetTable[] = 
    {
    602,
    630,
    664,
    698
    };

static const MIDL_SERVER_INFO IStageRaceServer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IStageRaceServer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IStageRaceServer_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IStageRaceServer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(7) _IStageRaceServerProxyVtbl = 
{
    &IStageRaceServer_ProxyInfo,
    &IID_IStageRaceServer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* IStageRaceServer::EnumerateDocuments */ ,
    (void *)-1 /* IStageRaceServer::SendMessage */ ,
    (void *)-1 /* IStageRaceServer::GetDocument */ ,
    (void *)-1 /* IStageRaceServer::GetActiveDocName */
};

const CInterfaceStubVtbl _IStageRaceServerStubVtbl =
{
    &IID_IStageRaceServer,
    &IStageRaceServer_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
        {
            
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            },
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SetArrivalByTime */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/*  8 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 10 */	NdrFcShort( 0xe ),	/* 14 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter nStaNo */

/* 16 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 18 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 20 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 22 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 24 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 28 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 30 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 32 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetArrivalByRank */

/* 34 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 36 */	NdrFcLong( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 42 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 44 */	NdrFcShort( 0xc ),	/* 12 */
/* 46 */	NdrFcShort( 0x8 ),	/* 8 */
/* 48 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter nStaNo */

/* 50 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 52 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 54 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nRank */

/* 56 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 58 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 60 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 62 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 64 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 66 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetArrival */

/* 68 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 70 */	NdrFcLong( 0x0 ),	/* 0 */
/* 74 */	NdrFcShort( 0x5 ),	/* 5 */
#ifndef _ALPHA_
/* 76 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 78 */	NdrFcShort( 0x14 ),	/* 20 */
/* 80 */	NdrFcShort( 0x8 ),	/* 8 */
/* 82 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter nStaNo */

/* 84 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 86 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 88 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nRank */

/* 90 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 92 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 94 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 96 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 98 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 104 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetArrivalByRank */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x6 ),	/* 6 */
#ifndef _ALPHA_
/* 116 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 118 */	NdrFcShort( 0x14 ),	/* 20 */
/* 120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 122 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter nRank */

/* 124 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 126 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 128 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nStaNo */

/* 130 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 132 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 134 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 136 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 138 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 140 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 142 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 144 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 146 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetArrivalByStaNo */

/* 148 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 150 */	NdrFcLong( 0x0 ),	/* 0 */
/* 154 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 156 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 158 */	NdrFcShort( 0x14 ),	/* 20 */
/* 160 */	NdrFcShort( 0x8 ),	/* 8 */
/* 162 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter nStaNo */

/* 164 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 166 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 168 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nRank */

/* 170 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 172 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 174 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 176 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 178 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 180 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 182 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 184 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 186 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetArrivalByTime */

/* 188 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 190 */	NdrFcLong( 0x0 ),	/* 0 */
/* 194 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 196 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 198 */	NdrFcShort( 0x1c ),	/* 28 */
/* 200 */	NdrFcShort( 0x8 ),	/* 8 */
/* 202 */	0x4,		/* Oi2 Flags:  has return, */
			0x5,		/* 5 */

	/* Parameter nUnits */

/* 204 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 206 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 208 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nStaNo */

/* 210 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 212 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 214 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nRank */

/* 216 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 218 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 220 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pnUnits */

/* 222 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 224 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 228 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 230 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetStart */

/* 234 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 236 */	NdrFcLong( 0x0 ),	/* 0 */
/* 240 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 242 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 244 */	NdrFcShort( 0x14 ),	/* 20 */
/* 246 */	NdrFcShort( 0x8 ),	/* 8 */
/* 248 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter nStaNo */

/* 250 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 252 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 254 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nOrder */

/* 256 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 258 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 260 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 262 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 264 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 266 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 268 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 270 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 272 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ResetArrival */

/* 274 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 276 */	NdrFcLong( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 282 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 284 */	NdrFcShort( 0x8 ),	/* 8 */
/* 286 */	NdrFcShort( 0x8 ),	/* 8 */
/* 288 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter nStaNo */

/* 290 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 292 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 296 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 298 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 300 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateStarts */

/* 302 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 304 */	NdrFcLong( 0x0 ),	/* 0 */
/* 308 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 310 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x8 ),	/* 8 */
/* 316 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter pStarts */

/* 318 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 320 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 322 */	NdrFcShort( 0x3cc ),	/* Type Offset=972 */

	/* Return value */

/* 324 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 326 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetTimingIdle */

/* 330 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 336 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 338 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x8 ),	/* 8 */
/* 344 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 346 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 348 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 350 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCountHalfStages */

/* 352 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 354 */	NdrFcLong( 0x0 ),	/* 0 */
/* 358 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/* 360 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 362 */	NdrFcShort( 0x10 ),	/* 16 */
/* 364 */	NdrFcShort( 0x10 ),	/* 16 */
/* 366 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter nFS */

/* 368 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 370 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 372 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pnCount */

/* 374 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
#ifndef _ALPHA_
/* 376 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 380 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 382 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCountFullStages */

/* 386 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 388 */	NdrFcLong( 0x0 ),	/* 0 */
/* 392 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 394 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 396 */	NdrFcShort( 0x8 ),	/* 8 */
/* 398 */	NdrFcShort( 0x10 ),	/* 16 */
/* 400 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pnCount */

/* 402 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
#ifndef _ALPHA_
/* 404 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 406 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 408 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 410 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 412 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetHalfStageName */

/* 414 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 416 */	NdrFcLong( 0x0 ),	/* 0 */
/* 420 */	NdrFcShort( 0x5 ),	/* 5 */
#ifndef _ALPHA_
/* 422 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 424 */	NdrFcShort( 0x10 ),	/* 16 */
/* 426 */	NdrFcShort( 0x8 ),	/* 8 */
/* 428 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter nFS */

/* 430 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 432 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 434 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nHS */

/* 436 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 438 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 440 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pname */

/* 442 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
#ifndef _ALPHA_
/* 444 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 446 */	NdrFcShort( 0x3de ),	/* Type Offset=990 */

	/* Return value */

/* 448 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 450 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 452 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetFullStageName */

/* 454 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 456 */	NdrFcLong( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x6 ),	/* 6 */
#ifndef _ALPHA_
/* 462 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 464 */	NdrFcShort( 0x8 ),	/* 8 */
/* 466 */	NdrFcShort( 0x8 ),	/* 8 */
/* 468 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter nFS */

/* 470 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 472 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pname */

/* 476 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
#ifndef _ALPHA_
/* 478 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 480 */	NdrFcShort( 0x3de ),	/* Type Offset=990 */

	/* Return value */

/* 482 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 484 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 486 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetHalfStage */

/* 488 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 490 */	NdrFcLong( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 496 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 498 */	NdrFcShort( 0x10 ),	/* 16 */
/* 500 */	NdrFcShort( 0x8 ),	/* 8 */
/* 502 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter nFS */

/* 504 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 506 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 508 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nHS */

/* 510 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 512 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppHS */

/* 516 */	NdrFcShort( 0x201b ),	/* Flags:  must size, must free, in, out, srv alloc size=8 */
#ifndef _ALPHA_
/* 518 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 520 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Return value */

/* 522 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 524 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 526 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CompetitorExists */

/* 528 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 530 */	NdrFcLong( 0x0 ),	/* 0 */
/* 534 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 536 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 538 */	NdrFcShort( 0x6 ),	/* 6 */
/* 540 */	NdrFcShort( 0x10 ),	/* 16 */
/* 542 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter nStaNo */

/* 544 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 546 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 548 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter bExists */

/* 550 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 552 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 554 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 556 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 558 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 560 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCompetitor */

/* 562 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 564 */	NdrFcLong( 0x0 ),	/* 0 */
/* 568 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 570 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 572 */	NdrFcShort( 0x6 ),	/* 6 */
/* 574 */	NdrFcShort( 0x8 ),	/* 8 */
/* 576 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter nStaNo */

/* 578 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 580 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 582 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pname */

/* 584 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
#ifndef _ALPHA_
/* 586 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 588 */	NdrFcShort( 0x3de ),	/* Type Offset=990 */

	/* Parameter pteam */

/* 590 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
#ifndef _ALPHA_
/* 592 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 594 */	NdrFcShort( 0x3de ),	/* Type Offset=990 */

	/* Return value */

/* 596 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 598 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 600 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateDocuments */

/* 602 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 604 */	NdrFcLong( 0x0 ),	/* 0 */
/* 608 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/* 610 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 614 */	NdrFcShort( 0x8 ),	/* 8 */
/* 616 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pDocs */

/* 618 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 620 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 622 */	NdrFcShort( 0x40a ),	/* Type Offset=1034 */

	/* Return value */

/* 624 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 626 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 628 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SendMessage */

/* 630 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 632 */	NdrFcLong( 0x0 ),	/* 0 */
/* 636 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 638 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 642 */	NdrFcShort( 0x8 ),	/* 8 */
/* 644 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter user */

/* 646 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 648 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 650 */	NdrFcShort( 0x414 ),	/* Type Offset=1044 */

	/* Parameter message */

/* 652 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 654 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 656 */	NdrFcShort( 0x414 ),	/* Type Offset=1044 */

	/* Return value */

/* 658 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 660 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 662 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDocument */

/* 664 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 666 */	NdrFcLong( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x5 ),	/* 5 */
#ifndef _ALPHA_
/* 672 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x8 ),	/* 8 */
/* 678 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter title */

/* 680 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 682 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 684 */	NdrFcShort( 0x414 ),	/* Type Offset=1044 */

	/* Parameter ppDoc */

/* 686 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 688 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 690 */	NdrFcShort( 0x41e ),	/* Type Offset=1054 */

	/* Return value */

/* 692 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 694 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 696 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetActiveDocName */

/* 698 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 700 */	NdrFcLong( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x6 ),	/* 6 */
#ifndef _ALPHA_
/* 706 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	NdrFcShort( 0x8 ),	/* 8 */
/* 712 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter pTitle */

/* 714 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 716 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 718 */	NdrFcShort( 0x414 ),	/* Type Offset=1044 */

	/* Return value */

/* 720 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 722 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 724 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  8 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 10 */	
			0x11, 0x0,	/* FC_RP */
/* 12 */	NdrFcShort( 0x3c0 ),	/* Offset= 960 (972) */
/* 14 */	
			0x12, 0x0,	/* FC_UP */
/* 16 */	NdrFcShort( 0x3a8 ),	/* Offset= 936 (952) */
/* 18 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 20 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 22 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 24 */	NdrFcShort( 0x2 ),	/* Offset= 2 (26) */
/* 26 */	NdrFcShort( 0x10 ),	/* 16 */
/* 28 */	NdrFcShort( 0x2b ),	/* 43 */
/* 30 */	NdrFcLong( 0x3 ),	/* 3 */
/* 34 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 36 */	NdrFcLong( 0x11 ),	/* 17 */
/* 40 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 42 */	NdrFcLong( 0x2 ),	/* 2 */
/* 46 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 48 */	NdrFcLong( 0x4 ),	/* 4 */
/* 52 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 54 */	NdrFcLong( 0x5 ),	/* 5 */
/* 58 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 60 */	NdrFcLong( 0xb ),	/* 11 */
/* 64 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 66 */	NdrFcLong( 0xa ),	/* 10 */
/* 70 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 72 */	NdrFcLong( 0x6 ),	/* 6 */
/* 76 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (290) */
/* 78 */	NdrFcLong( 0x7 ),	/* 7 */
/* 82 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 84 */	NdrFcLong( 0x8 ),	/* 8 */
/* 88 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (296) */
/* 90 */	NdrFcLong( 0xd ),	/* 13 */
/* 94 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (320) */
/* 96 */	NdrFcLong( 0x9 ),	/* 9 */
/* 100 */	NdrFcShort( 0xee ),	/* Offset= 238 (338) */
/* 102 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 106 */	NdrFcShort( 0xfa ),	/* Offset= 250 (356) */
/* 108 */	NdrFcLong( 0x24 ),	/* 36 */
/* 112 */	NdrFcShort( 0x304 ),	/* Offset= 772 (884) */
/* 114 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 118 */	NdrFcShort( 0x2fe ),	/* Offset= 766 (884) */
/* 120 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 124 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (888) */
/* 126 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 130 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (892) */
/* 132 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 136 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (896) */
/* 138 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 142 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (900) */
/* 144 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 148 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (904) */
/* 150 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 154 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (892) */
/* 156 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 160 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (896) */
/* 162 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 166 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (908) */
/* 168 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 172 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (904) */
/* 174 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 178 */	NdrFcShort( 0x2de ),	/* Offset= 734 (912) */
/* 180 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 184 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (916) */
/* 186 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 190 */	NdrFcShort( 0x2da ),	/* Offset= 730 (920) */
/* 192 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 196 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (924) */
/* 198 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 202 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (928) */
/* 204 */	NdrFcLong( 0x10 ),	/* 16 */
/* 208 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 210 */	NdrFcLong( 0x12 ),	/* 18 */
/* 214 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 216 */	NdrFcLong( 0x13 ),	/* 19 */
/* 220 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 222 */	NdrFcLong( 0x16 ),	/* 22 */
/* 226 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 228 */	NdrFcLong( 0x17 ),	/* 23 */
/* 232 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 234 */	NdrFcLong( 0xe ),	/* 14 */
/* 238 */	NdrFcShort( 0x2ba ),	/* Offset= 698 (936) */
/* 240 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 244 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (948) */
/* 246 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 250 */	NdrFcShort( 0x27e ),	/* Offset= 638 (888) */
/* 252 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 256 */	NdrFcShort( 0x27c ),	/* Offset= 636 (892) */
/* 258 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 262 */	NdrFcShort( 0x27a ),	/* Offset= 634 (896) */
/* 264 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 268 */	NdrFcShort( 0x274 ),	/* Offset= 628 (896) */
/* 270 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 274 */	NdrFcShort( 0x26e ),	/* Offset= 622 (896) */
/* 276 */	NdrFcLong( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x0 ),	/* Offset= 0 (280) */
/* 282 */	NdrFcLong( 0x1 ),	/* 1 */
/* 286 */	NdrFcShort( 0x0 ),	/* Offset= 0 (286) */
/* 288 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (287) */
/* 290 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 292 */	NdrFcShort( 0x8 ),	/* 8 */
/* 294 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 296 */	
			0x12, 0x0,	/* FC_UP */
/* 298 */	NdrFcShort( 0xc ),	/* Offset= 12 (310) */
/* 300 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 302 */	NdrFcShort( 0x2 ),	/* 2 */
/* 304 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 306 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 308 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 310 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 314 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (300) */
/* 316 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 318 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 320 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 322 */	NdrFcLong( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 330 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 332 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 334 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 336 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 338 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 340 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 344 */	NdrFcShort( 0x0 ),	/* 0 */
/* 346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 348 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 350 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 352 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 354 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 356 */	
			0x12, 0x0,	/* FC_UP */
/* 358 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (866) */
/* 360 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 362 */	NdrFcShort( 0x18 ),	/* 24 */
/* 364 */	NdrFcShort( 0xa ),	/* 10 */
/* 366 */	NdrFcLong( 0x8 ),	/* 8 */
/* 370 */	NdrFcShort( 0x58 ),	/* Offset= 88 (458) */
/* 372 */	NdrFcLong( 0xd ),	/* 13 */
/* 376 */	NdrFcShort( 0x78 ),	/* Offset= 120 (496) */
/* 378 */	NdrFcLong( 0x9 ),	/* 9 */
/* 382 */	NdrFcShort( 0x94 ),	/* Offset= 148 (530) */
/* 384 */	NdrFcLong( 0xc ),	/* 12 */
/* 388 */	NdrFcShort( 0xbc ),	/* Offset= 188 (576) */
/* 390 */	NdrFcLong( 0x24 ),	/* 36 */
/* 394 */	NdrFcShort( 0x114 ),	/* Offset= 276 (670) */
/* 396 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 400 */	NdrFcShort( 0x130 ),	/* Offset= 304 (704) */
/* 402 */	NdrFcLong( 0x10 ),	/* 16 */
/* 406 */	NdrFcShort( 0x148 ),	/* Offset= 328 (734) */
/* 408 */	NdrFcLong( 0x2 ),	/* 2 */
/* 412 */	NdrFcShort( 0x160 ),	/* Offset= 352 (764) */
/* 414 */	NdrFcLong( 0x3 ),	/* 3 */
/* 418 */	NdrFcShort( 0x178 ),	/* Offset= 376 (794) */
/* 420 */	NdrFcLong( 0x14 ),	/* 20 */
/* 424 */	NdrFcShort( 0x190 ),	/* Offset= 400 (824) */
/* 426 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (425) */
/* 428 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 430 */	NdrFcShort( 0x4 ),	/* 4 */
/* 432 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 434 */	NdrFcShort( 0x0 ),	/* 0 */
/* 436 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 438 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 440 */	NdrFcShort( 0x4 ),	/* 4 */
/* 442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 444 */	NdrFcShort( 0x1 ),	/* 1 */
/* 446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	0x12, 0x0,	/* FC_UP */
/* 452 */	NdrFcShort( 0xffffff72 ),	/* Offset= -142 (310) */
/* 454 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 456 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 458 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 460 */	NdrFcShort( 0x8 ),	/* 8 */
/* 462 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 464 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 466 */	NdrFcShort( 0x4 ),	/* 4 */
/* 468 */	NdrFcShort( 0x4 ),	/* 4 */
/* 470 */	0x11, 0x0,	/* FC_RP */
/* 472 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (428) */
/* 474 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 476 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 478 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 482 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 490 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 492 */	NdrFcShort( 0xffffff54 ),	/* Offset= -172 (320) */
/* 494 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 496 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 498 */	NdrFcShort( 0x8 ),	/* 8 */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 502 */	NdrFcShort( 0x6 ),	/* Offset= 6 (508) */
/* 504 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 506 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 508 */	
			0x11, 0x0,	/* FC_RP */
/* 510 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (478) */
/* 512 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 520 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 524 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 526 */	NdrFcShort( 0xffffff44 ),	/* Offset= -188 (338) */
/* 528 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 530 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 532 */	NdrFcShort( 0x8 ),	/* 8 */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	NdrFcShort( 0x6 ),	/* Offset= 6 (542) */
/* 538 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 540 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 542 */	
			0x11, 0x0,	/* FC_RP */
/* 544 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (512) */
/* 546 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 548 */	NdrFcShort( 0x4 ),	/* 4 */
/* 550 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 556 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 558 */	NdrFcShort( 0x4 ),	/* 4 */
/* 560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 562 */	NdrFcShort( 0x1 ),	/* 1 */
/* 564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 566 */	NdrFcShort( 0x0 ),	/* 0 */
/* 568 */	0x12, 0x0,	/* FC_UP */
/* 570 */	NdrFcShort( 0x17e ),	/* Offset= 382 (952) */
/* 572 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 574 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 576 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 578 */	NdrFcShort( 0x8 ),	/* 8 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x6 ),	/* Offset= 6 (588) */
/* 584 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 586 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 588 */	
			0x11, 0x0,	/* FC_RP */
/* 590 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (546) */
/* 592 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 594 */	NdrFcLong( 0x2f ),	/* 47 */
/* 598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 604 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 606 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 608 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 610 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 612 */	NdrFcShort( 0x1 ),	/* 1 */
/* 614 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 616 */	NdrFcShort( 0x4 ),	/* 4 */
/* 618 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 620 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 622 */	NdrFcShort( 0x10 ),	/* 16 */
/* 624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 626 */	NdrFcShort( 0xa ),	/* Offset= 10 (636) */
/* 628 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 630 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 632 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (592) */
/* 634 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 636 */	
			0x12, 0x0,	/* FC_UP */
/* 638 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (610) */
/* 640 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 642 */	NdrFcShort( 0x4 ),	/* 4 */
/* 644 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 648 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 650 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 652 */	NdrFcShort( 0x4 ),	/* 4 */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	NdrFcShort( 0x1 ),	/* 1 */
/* 658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 662 */	0x12, 0x0,	/* FC_UP */
/* 664 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (620) */
/* 666 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 668 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 670 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 672 */	NdrFcShort( 0x8 ),	/* 8 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x6 ),	/* Offset= 6 (682) */
/* 678 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 680 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 682 */	
			0x11, 0x0,	/* FC_RP */
/* 684 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (640) */
/* 686 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 688 */	NdrFcShort( 0x8 ),	/* 8 */
/* 690 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 692 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 694 */	NdrFcShort( 0x10 ),	/* 16 */
/* 696 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 698 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 700 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (686) */
			0x5b,		/* FC_END */
/* 704 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 706 */	NdrFcShort( 0x18 ),	/* 24 */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	NdrFcShort( 0xa ),	/* Offset= 10 (720) */
/* 712 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 714 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 716 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (692) */
/* 718 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 720 */	
			0x11, 0x0,	/* FC_RP */
/* 722 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (478) */
/* 724 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 726 */	NdrFcShort( 0x1 ),	/* 1 */
/* 728 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 734 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 736 */	NdrFcShort( 0x8 ),	/* 8 */
/* 738 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 740 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 742 */	NdrFcShort( 0x4 ),	/* 4 */
/* 744 */	NdrFcShort( 0x4 ),	/* 4 */
/* 746 */	0x12, 0x0,	/* FC_UP */
/* 748 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (724) */
/* 750 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 752 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 754 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 756 */	NdrFcShort( 0x2 ),	/* 2 */
/* 758 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 762 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 764 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 766 */	NdrFcShort( 0x8 ),	/* 8 */
/* 768 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 770 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 772 */	NdrFcShort( 0x4 ),	/* 4 */
/* 774 */	NdrFcShort( 0x4 ),	/* 4 */
/* 776 */	0x12, 0x0,	/* FC_UP */
/* 778 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (754) */
/* 780 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 782 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 784 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 786 */	NdrFcShort( 0x4 ),	/* 4 */
/* 788 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 792 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 794 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 796 */	NdrFcShort( 0x8 ),	/* 8 */
/* 798 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 800 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 802 */	NdrFcShort( 0x4 ),	/* 4 */
/* 804 */	NdrFcShort( 0x4 ),	/* 4 */
/* 806 */	0x12, 0x0,	/* FC_UP */
/* 808 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (784) */
/* 810 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 812 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 814 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 816 */	NdrFcShort( 0x8 ),	/* 8 */
/* 818 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 822 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 824 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 826 */	NdrFcShort( 0x8 ),	/* 8 */
/* 828 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 830 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 832 */	NdrFcShort( 0x4 ),	/* 4 */
/* 834 */	NdrFcShort( 0x4 ),	/* 4 */
/* 836 */	0x12, 0x0,	/* FC_UP */
/* 838 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (814) */
/* 840 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 842 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 844 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 848 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 850 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 852 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 854 */	NdrFcShort( 0x8 ),	/* 8 */
/* 856 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 858 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 860 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 862 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (844) */
/* 864 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 866 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 868 */	NdrFcShort( 0x28 ),	/* 40 */
/* 870 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (852) */
/* 872 */	NdrFcShort( 0x0 ),	/* Offset= 0 (872) */
/* 874 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 876 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 878 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 880 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdf7 ),	/* Offset= -521 (360) */
			0x5b,		/* FC_END */
/* 884 */	
			0x12, 0x0,	/* FC_UP */
/* 886 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (620) */
/* 888 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 890 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 892 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 894 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 896 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 898 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 900 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 902 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 904 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 906 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 908 */	
			0x12, 0x0,	/* FC_UP */
/* 910 */	NdrFcShort( 0xfffffd94 ),	/* Offset= -620 (290) */
/* 912 */	
			0x12, 0x10,	/* FC_UP */
/* 914 */	NdrFcShort( 0xfffffd96 ),	/* Offset= -618 (296) */
/* 916 */	
			0x12, 0x10,	/* FC_UP */
/* 918 */	NdrFcShort( 0xfffffdaa ),	/* Offset= -598 (320) */
/* 920 */	
			0x12, 0x10,	/* FC_UP */
/* 922 */	NdrFcShort( 0xfffffdb8 ),	/* Offset= -584 (338) */
/* 924 */	
			0x12, 0x10,	/* FC_UP */
/* 926 */	NdrFcShort( 0xfffffdc6 ),	/* Offset= -570 (356) */
/* 928 */	
			0x12, 0x10,	/* FC_UP */
/* 930 */	NdrFcShort( 0x2 ),	/* Offset= 2 (932) */
/* 932 */	
			0x12, 0x0,	/* FC_UP */
/* 934 */	NdrFcShort( 0xfffffc5a ),	/* Offset= -934 (0) */
/* 936 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 938 */	NdrFcShort( 0x10 ),	/* 16 */
/* 940 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 942 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 944 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 946 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 948 */	
			0x12, 0x0,	/* FC_UP */
/* 950 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (936) */
/* 952 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 954 */	NdrFcShort( 0x20 ),	/* 32 */
/* 956 */	NdrFcShort( 0x0 ),	/* 0 */
/* 958 */	NdrFcShort( 0x0 ),	/* Offset= 0 (958) */
/* 960 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 962 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 964 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 966 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 968 */	NdrFcShort( 0xfffffc4a ),	/* Offset= -950 (18) */
/* 970 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 972 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 974 */	NdrFcShort( 0x0 ),	/* 0 */
/* 976 */	NdrFcShort( 0x10 ),	/* 16 */
/* 978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 980 */	NdrFcShort( 0xfffffc3a ),	/* Offset= -966 (14) */
/* 982 */	
			0x11, 0x0,	/* FC_RP */
/* 984 */	NdrFcShort( 0x6 ),	/* Offset= 6 (990) */
/* 986 */	
			0x13, 0x0,	/* FC_OP */
/* 988 */	NdrFcShort( 0xfffffd5a ),	/* Offset= -678 (310) */
/* 990 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 992 */	NdrFcShort( 0x1 ),	/* 1 */
/* 994 */	NdrFcShort( 0x4 ),	/* 4 */
/* 996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 998 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (986) */
/* 1000 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 1002 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1004) */
/* 1004 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1006 */	NdrFcLong( 0x55b2c551 ),	/* 1437779281 */
/* 1010 */	NdrFcShort( 0x69f1 ),	/* 27121 */
/* 1012 */	NdrFcShort( 0x43d7 ),	/* 17367 */
/* 1014 */	0x9d,		/* 157 */
			0xca,		/* 202 */
/* 1016 */	0x59,		/* 89 */
			0x98,		/* 152 */
/* 1018 */	0x9c,		/* 156 */
			0x3b,		/* 59 */
/* 1020 */	0x18,		/* 24 */
			0x8,		/* 8 */
/* 1022 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1024 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1026 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1028 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1034) */
/* 1030 */	
			0x13, 0x0,	/* FC_OP */
/* 1032 */	NdrFcShort( 0xffffffb0 ),	/* Offset= -80 (952) */
/* 1034 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1038 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1042 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1030) */
/* 1044 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1046 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1048 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1050 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1052 */	NdrFcShort( 0xfffffd0c ),	/* Offset= -756 (296) */
/* 1054 */	
			0x11, 0x10,	/* FC_RP */
/* 1056 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1058) */
/* 1058 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1060 */	NdrFcLong( 0xeb26427b ),	/* -349814149 */
/* 1064 */	NdrFcShort( 0x82ac ),	/* -32084 */
/* 1066 */	NdrFcShort( 0x45fa ),	/* 17914 */
/* 1068 */	0x80,		/* 128 */
			0xaf,		/* 175 */
/* 1070 */	0xf9,		/* 249 */
			0x3c,		/* 60 */
/* 1072 */	0x8a,		/* 138 */
			0x31,		/* 49 */
/* 1074 */	0x89,		/* 137 */
			0xad,		/* 173 */
/* 1076 */	
			0x11, 0x0,	/* FC_RP */
/* 1078 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (1044) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _StageRace_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ISRHalfStageProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IStageRaceDocProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IStageRaceServerProxyVtbl,
    0
};

const CInterfaceStubVtbl * _StageRace_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ISRHalfStageStubVtbl,
    ( CInterfaceStubVtbl *) &_IStageRaceDocStubVtbl,
    ( CInterfaceStubVtbl *) &_IStageRaceServerStubVtbl,
    0
};

PCInterfaceName const _StageRace_InterfaceNamesList[] = 
{
    "ISRHalfStage",
    "IStageRaceDoc",
    "IStageRaceServer",
    0
};


#define _StageRace_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _StageRace, pIID, n)

int __stdcall _StageRace_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _StageRace, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _StageRace, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _StageRace, 3, *pIndex )
    
}

const ExtendedProxyFileInfo StageRace_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _StageRace_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _StageRace_StubVtblList,
    (const PCInterfaceName * ) & _StageRace_InterfaceNamesList,
    0, // no delegation
    & _StageRace_IID_Lookup, 
    3,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
