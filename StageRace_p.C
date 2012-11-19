

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Nov 18 18:17:47 2012
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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "StageRace_i.h"

#define TYPE_FORMAT_STRING_SIZE   1145                              
#define PROC_FORMAT_STRING_SIZE   895                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _StageRace_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } StageRace_MIDL_TYPE_FORMAT_STRING;

typedef struct _StageRace_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } StageRace_MIDL_PROC_FORMAT_STRING;

typedef struct _StageRace_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } StageRace_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const StageRace_MIDL_TYPE_FORMAT_STRING StageRace__MIDL_TypeFormatString;
extern const StageRace_MIDL_PROC_FORMAT_STRING StageRace__MIDL_ProcFormatString;
extern const StageRace_MIDL_EXPR_FORMAT_STRING StageRace__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISRHalfStage_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISRHalfStage_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IStageRaceDoc_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IStageRaceDoc_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IStageRaceServer_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IStageRaceServer_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const StageRace_MIDL_PROC_FORMAT_STRING StageRace__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SetArrivalByTime */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 10 */	NdrFcShort( 0xe ),	/* 14 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nStaNo */

/* 24 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 30 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 36 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 38 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 40 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetArrivalByRank */

/* 42 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 44 */	NdrFcLong( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x4 ),	/* 4 */
/* 50 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 52 */	NdrFcShort( 0xc ),	/* 12 */
/* 54 */	NdrFcShort( 0x8 ),	/* 8 */
/* 56 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 58 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nStaNo */

/* 66 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 68 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 70 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nRank */

/* 72 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 74 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 76 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 80 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetArrival */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x5 ),	/* 5 */
/* 92 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 94 */	NdrFcShort( 0x14 ),	/* 20 */
/* 96 */	NdrFcShort( 0x8 ),	/* 8 */
/* 98 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 100 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nStaNo */

/* 108 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 110 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 112 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nRank */

/* 114 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 116 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 118 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 120 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 122 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 126 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 128 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetArrivalByRank */

/* 132 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 134 */	NdrFcLong( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x6 ),	/* 6 */
/* 140 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 142 */	NdrFcShort( 0x3c ),	/* 60 */
/* 144 */	NdrFcShort( 0x8 ),	/* 8 */
/* 146 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 148 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nRank */

/* 156 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 158 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 160 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nStaNo */

/* 162 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 164 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 166 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 168 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 170 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 174 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 176 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetArrivalByStaNo */

/* 180 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0x7 ),	/* 7 */
/* 188 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 190 */	NdrFcShort( 0x3c ),	/* 60 */
/* 192 */	NdrFcShort( 0x8 ),	/* 8 */
/* 194 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 196 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nStaNo */

/* 204 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 206 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 208 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nRank */

/* 210 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 212 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 214 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 216 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 218 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 220 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 222 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 224 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetArrivalByTime */

/* 228 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 230 */	NdrFcLong( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x8 ),	/* 8 */
/* 236 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 238 */	NdrFcShort( 0x58 ),	/* 88 */
/* 240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 242 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x5,		/* 5 */
/* 244 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nUnits */

/* 252 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 254 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nStaNo */

/* 258 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 260 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 262 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nRank */

/* 264 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 266 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 268 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pnUnits */

/* 270 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 272 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 274 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 276 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 278 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 280 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetStart */

/* 282 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 284 */	NdrFcLong( 0x0 ),	/* 0 */
/* 288 */	NdrFcShort( 0x9 ),	/* 9 */
/* 290 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 292 */	NdrFcShort( 0x3c ),	/* 60 */
/* 294 */	NdrFcShort( 0x8 ),	/* 8 */
/* 296 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 298 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 300 */	NdrFcShort( 0x0 ),	/* 0 */
/* 302 */	NdrFcShort( 0x0 ),	/* 0 */
/* 304 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nStaNo */

/* 306 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 308 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 310 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nOrder */

/* 312 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 314 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 316 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter nUnits */

/* 318 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 320 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 322 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 324 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 326 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ResetArrival */

/* 330 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 336 */	NdrFcShort( 0xa ),	/* 10 */
/* 338 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 342 */	NdrFcShort( 0x8 ),	/* 8 */
/* 344 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 346 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 350 */	NdrFcShort( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nStaNo */

/* 354 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 356 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 358 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 360 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 362 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 364 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateStarts */

/* 366 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 368 */	NdrFcLong( 0x0 ),	/* 0 */
/* 372 */	NdrFcShort( 0xb ),	/* 11 */
/* 374 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 376 */	NdrFcShort( 0x0 ),	/* 0 */
/* 378 */	NdrFcShort( 0x8 ),	/* 8 */
/* 380 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 382 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 386 */	NdrFcShort( 0x1 ),	/* 1 */
/* 388 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pStarts */

/* 390 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 392 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 394 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 398 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetTimingIdle */

/* 402 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0xc ),	/* 12 */
/* 410 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 416 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 418 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 424 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 426 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 428 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCountHalfStages */

/* 432 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 434 */	NdrFcLong( 0x0 ),	/* 0 */
/* 438 */	NdrFcShort( 0x3 ),	/* 3 */
/* 440 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 442 */	NdrFcShort( 0x24 ),	/* 36 */
/* 444 */	NdrFcShort( 0x24 ),	/* 36 */
/* 446 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 448 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nFS */

/* 456 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 458 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 460 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pnCount */

/* 462 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 464 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 466 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 468 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 470 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCountFullStages */

/* 474 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 476 */	NdrFcLong( 0x0 ),	/* 0 */
/* 480 */	NdrFcShort( 0x4 ),	/* 4 */
/* 482 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 484 */	NdrFcShort( 0x1c ),	/* 28 */
/* 486 */	NdrFcShort( 0x24 ),	/* 36 */
/* 488 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 490 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x0 ),	/* 0 */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pnCount */

/* 498 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 500 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 502 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 504 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 506 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 508 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetHalfStageName */

/* 510 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 512 */	NdrFcLong( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x5 ),	/* 5 */
/* 518 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 520 */	NdrFcShort( 0x10 ),	/* 16 */
/* 522 */	NdrFcShort( 0x8 ),	/* 8 */
/* 524 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 526 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 528 */	NdrFcShort( 0x1 ),	/* 1 */
/* 530 */	NdrFcShort( 0x1 ),	/* 1 */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nFS */

/* 534 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 536 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 538 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nHS */

/* 540 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 542 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 544 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pname */

/* 546 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 548 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 550 */	NdrFcShort( 0x41e ),	/* Type Offset=1054 */

	/* Return value */

/* 552 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 554 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 556 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetFullStageName */

/* 558 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 560 */	NdrFcLong( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x6 ),	/* 6 */
/* 566 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 568 */	NdrFcShort( 0x8 ),	/* 8 */
/* 570 */	NdrFcShort( 0x8 ),	/* 8 */
/* 572 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 574 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 576 */	NdrFcShort( 0x1 ),	/* 1 */
/* 578 */	NdrFcShort( 0x1 ),	/* 1 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nFS */

/* 582 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 584 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 586 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pname */

/* 588 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 590 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 592 */	NdrFcShort( 0x41e ),	/* Type Offset=1054 */

	/* Return value */

/* 594 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 596 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetHalfStage */

/* 600 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 602 */	NdrFcLong( 0x0 ),	/* 0 */
/* 606 */	NdrFcShort( 0x7 ),	/* 7 */
/* 608 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 610 */	NdrFcShort( 0x10 ),	/* 16 */
/* 612 */	NdrFcShort( 0x8 ),	/* 8 */
/* 614 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 616 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x0 ),	/* 0 */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nFS */

/* 624 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 626 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 628 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nHS */

/* 630 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 632 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 634 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppHS */

/* 636 */	NdrFcShort( 0x201b ),	/* Flags:  must size, must free, in, out, srv alloc size=8 */
/* 638 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 640 */	NdrFcShort( 0x428 ),	/* Type Offset=1064 */

	/* Return value */

/* 642 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 644 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 646 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CompetitorExists */

/* 648 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 650 */	NdrFcLong( 0x0 ),	/* 0 */
/* 654 */	NdrFcShort( 0x8 ),	/* 8 */
/* 656 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 658 */	NdrFcShort( 0x6 ),	/* 6 */
/* 660 */	NdrFcShort( 0x24 ),	/* 36 */
/* 662 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 664 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nStaNo */

/* 672 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 674 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 676 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter bExists */

/* 678 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 680 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 684 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 686 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 688 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCompetitor */

/* 690 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 696 */	NdrFcShort( 0x9 ),	/* 9 */
/* 698 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 700 */	NdrFcShort( 0x6 ),	/* 6 */
/* 702 */	NdrFcShort( 0x8 ),	/* 8 */
/* 704 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 706 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 708 */	NdrFcShort( 0x1 ),	/* 1 */
/* 710 */	NdrFcShort( 0x1 ),	/* 1 */
/* 712 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nStaNo */

/* 714 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 716 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 718 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pname */

/* 720 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 722 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 724 */	NdrFcShort( 0x41e ),	/* Type Offset=1054 */

	/* Parameter pteam */

/* 726 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 728 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 730 */	NdrFcShort( 0x41e ),	/* Type Offset=1054 */

	/* Return value */

/* 732 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 734 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 736 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateDocuments */

/* 738 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 740 */	NdrFcLong( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0x3 ),	/* 3 */
/* 746 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 750 */	NdrFcShort( 0x8 ),	/* 8 */
/* 752 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 754 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 756 */	NdrFcShort( 0x1 ),	/* 1 */
/* 758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDocs */

/* 762 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 764 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 766 */	NdrFcShort( 0x44a ),	/* Type Offset=1098 */

	/* Return value */

/* 768 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 770 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 772 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SendMessage */

/* 774 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 776 */	NdrFcLong( 0x0 ),	/* 0 */
/* 780 */	NdrFcShort( 0x4 ),	/* 4 */
/* 782 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 784 */	NdrFcShort( 0x0 ),	/* 0 */
/* 786 */	NdrFcShort( 0x8 ),	/* 8 */
/* 788 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 790 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x1 ),	/* 1 */
/* 796 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter user */

/* 798 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 800 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 802 */	NdrFcShort( 0x454 ),	/* Type Offset=1108 */

	/* Parameter message */

/* 804 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 806 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 808 */	NdrFcShort( 0x454 ),	/* Type Offset=1108 */

	/* Return value */

/* 810 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 812 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 814 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDocument */

/* 816 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 818 */	NdrFcLong( 0x0 ),	/* 0 */
/* 822 */	NdrFcShort( 0x5 ),	/* 5 */
/* 824 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 828 */	NdrFcShort( 0x8 ),	/* 8 */
/* 830 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 832 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 836 */	NdrFcShort( 0x1 ),	/* 1 */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter title */

/* 840 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 842 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 844 */	NdrFcShort( 0x454 ),	/* Type Offset=1108 */

	/* Parameter ppDoc */

/* 846 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 848 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 850 */	NdrFcShort( 0x45e ),	/* Type Offset=1118 */

	/* Return value */

/* 852 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 854 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 856 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetActiveDocName */

/* 858 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 860 */	NdrFcLong( 0x0 ),	/* 0 */
/* 864 */	NdrFcShort( 0x6 ),	/* 6 */
/* 866 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 872 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 874 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 878 */	NdrFcShort( 0x1 ),	/* 1 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pTitle */

/* 882 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 884 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 886 */	NdrFcShort( 0x454 ),	/* Type Offset=1108 */

	/* Return value */

/* 888 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 890 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 892 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const StageRace_MIDL_TYPE_FORMAT_STRING StageRace__MIDL_TypeFormatString =
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
/* 12 */	NdrFcShort( 0x400 ),	/* Offset= 1024 (1036) */
/* 14 */	
			0x12, 0x0,	/* FC_UP */
/* 16 */	NdrFcShort( 0x3e8 ),	/* Offset= 1000 (1016) */
/* 18 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 20 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 22 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 24 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 26 */	NdrFcShort( 0x2 ),	/* Offset= 2 (28) */
/* 28 */	NdrFcShort( 0x10 ),	/* 16 */
/* 30 */	NdrFcShort( 0x2f ),	/* 47 */
/* 32 */	NdrFcLong( 0x14 ),	/* 20 */
/* 36 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 38 */	NdrFcLong( 0x3 ),	/* 3 */
/* 42 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 44 */	NdrFcLong( 0x11 ),	/* 17 */
/* 48 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 50 */	NdrFcLong( 0x2 ),	/* 2 */
/* 54 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 56 */	NdrFcLong( 0x4 ),	/* 4 */
/* 60 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 62 */	NdrFcLong( 0x5 ),	/* 5 */
/* 66 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 68 */	NdrFcLong( 0xb ),	/* 11 */
/* 72 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 74 */	NdrFcLong( 0xa ),	/* 10 */
/* 78 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 80 */	NdrFcLong( 0x6 ),	/* 6 */
/* 84 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (316) */
/* 86 */	NdrFcLong( 0x7 ),	/* 7 */
/* 90 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 92 */	NdrFcLong( 0x8 ),	/* 8 */
/* 96 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (322) */
/* 98 */	NdrFcLong( 0xd ),	/* 13 */
/* 102 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (348) */
/* 104 */	NdrFcLong( 0x9 ),	/* 9 */
/* 108 */	NdrFcShort( 0x102 ),	/* Offset= 258 (366) */
/* 110 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 114 */	NdrFcShort( 0x10e ),	/* Offset= 270 (384) */
/* 116 */	NdrFcLong( 0x24 ),	/* 36 */
/* 120 */	NdrFcShort( 0x336 ),	/* Offset= 822 (942) */
/* 122 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 126 */	NdrFcShort( 0x330 ),	/* Offset= 816 (942) */
/* 128 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 132 */	NdrFcShort( 0x32e ),	/* Offset= 814 (946) */
/* 134 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 138 */	NdrFcShort( 0x32c ),	/* Offset= 812 (950) */
/* 140 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 144 */	NdrFcShort( 0x32a ),	/* Offset= 810 (954) */
/* 146 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 150 */	NdrFcShort( 0x328 ),	/* Offset= 808 (958) */
/* 152 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 156 */	NdrFcShort( 0x326 ),	/* Offset= 806 (962) */
/* 158 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 162 */	NdrFcShort( 0x324 ),	/* Offset= 804 (966) */
/* 164 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 168 */	NdrFcShort( 0x30e ),	/* Offset= 782 (950) */
/* 170 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 174 */	NdrFcShort( 0x30c ),	/* Offset= 780 (954) */
/* 176 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 180 */	NdrFcShort( 0x316 ),	/* Offset= 790 (970) */
/* 182 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 186 */	NdrFcShort( 0x30c ),	/* Offset= 780 (966) */
/* 188 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 192 */	NdrFcShort( 0x30e ),	/* Offset= 782 (974) */
/* 194 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 198 */	NdrFcShort( 0x30c ),	/* Offset= 780 (978) */
/* 200 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 204 */	NdrFcShort( 0x30a ),	/* Offset= 778 (982) */
/* 206 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 210 */	NdrFcShort( 0x308 ),	/* Offset= 776 (986) */
/* 212 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 216 */	NdrFcShort( 0x306 ),	/* Offset= 774 (990) */
/* 218 */	NdrFcLong( 0x10 ),	/* 16 */
/* 222 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 224 */	NdrFcLong( 0x12 ),	/* 18 */
/* 228 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 230 */	NdrFcLong( 0x13 ),	/* 19 */
/* 234 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 236 */	NdrFcLong( 0x15 ),	/* 21 */
/* 240 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 242 */	NdrFcLong( 0x16 ),	/* 22 */
/* 246 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 248 */	NdrFcLong( 0x17 ),	/* 23 */
/* 252 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 254 */	NdrFcLong( 0xe ),	/* 14 */
/* 258 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (998) */
/* 260 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 264 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (1008) */
/* 266 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 270 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (1012) */
/* 272 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 276 */	NdrFcShort( 0x2a2 ),	/* Offset= 674 (950) */
/* 278 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 282 */	NdrFcShort( 0x2a0 ),	/* Offset= 672 (954) */
/* 284 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 288 */	NdrFcShort( 0x29e ),	/* Offset= 670 (958) */
/* 290 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 294 */	NdrFcShort( 0x294 ),	/* Offset= 660 (954) */
/* 296 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 300 */	NdrFcShort( 0x28e ),	/* Offset= 654 (954) */
/* 302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 306 */	NdrFcShort( 0x0 ),	/* Offset= 0 (306) */
/* 308 */	NdrFcLong( 0x1 ),	/* 1 */
/* 312 */	NdrFcShort( 0x0 ),	/* Offset= 0 (312) */
/* 314 */	NdrFcShort( 0xffff ),	/* Offset= -1 (313) */
/* 316 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 318 */	NdrFcShort( 0x8 ),	/* 8 */
/* 320 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 322 */	
			0x12, 0x0,	/* FC_UP */
/* 324 */	NdrFcShort( 0xe ),	/* Offset= 14 (338) */
/* 326 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 328 */	NdrFcShort( 0x2 ),	/* 2 */
/* 330 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 332 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 334 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 336 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 338 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 342 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (326) */
/* 344 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 346 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 348 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 350 */	NdrFcLong( 0x0 ),	/* 0 */
/* 354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 358 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 360 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 362 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 364 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 366 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 368 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 372 */	NdrFcShort( 0x0 ),	/* 0 */
/* 374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 376 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 378 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 380 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 382 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 384 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 386 */	NdrFcShort( 0x2 ),	/* Offset= 2 (388) */
/* 388 */	
			0x12, 0x0,	/* FC_UP */
/* 390 */	NdrFcShort( 0x216 ),	/* Offset= 534 (924) */
/* 392 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 394 */	NdrFcShort( 0x18 ),	/* 24 */
/* 396 */	NdrFcShort( 0xa ),	/* 10 */
/* 398 */	NdrFcLong( 0x8 ),	/* 8 */
/* 402 */	NdrFcShort( 0x5a ),	/* Offset= 90 (492) */
/* 404 */	NdrFcLong( 0xd ),	/* 13 */
/* 408 */	NdrFcShort( 0x7e ),	/* Offset= 126 (534) */
/* 410 */	NdrFcLong( 0x9 ),	/* 9 */
/* 414 */	NdrFcShort( 0x9e ),	/* Offset= 158 (572) */
/* 416 */	NdrFcLong( 0xc ),	/* 12 */
/* 420 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (620) */
/* 422 */	NdrFcLong( 0x24 ),	/* 36 */
/* 426 */	NdrFcShort( 0x124 ),	/* Offset= 292 (718) */
/* 428 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 432 */	NdrFcShort( 0x140 ),	/* Offset= 320 (752) */
/* 434 */	NdrFcLong( 0x10 ),	/* 16 */
/* 438 */	NdrFcShort( 0x15a ),	/* Offset= 346 (784) */
/* 440 */	NdrFcLong( 0x2 ),	/* 2 */
/* 444 */	NdrFcShort( 0x174 ),	/* Offset= 372 (816) */
/* 446 */	NdrFcLong( 0x3 ),	/* 3 */
/* 450 */	NdrFcShort( 0x18e ),	/* Offset= 398 (848) */
/* 452 */	NdrFcLong( 0x14 ),	/* 20 */
/* 456 */	NdrFcShort( 0x1a8 ),	/* Offset= 424 (880) */
/* 458 */	NdrFcShort( 0xffff ),	/* Offset= -1 (457) */
/* 460 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 462 */	NdrFcShort( 0x4 ),	/* 4 */
/* 464 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 468 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 470 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 472 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 474 */	NdrFcShort( 0x4 ),	/* 4 */
/* 476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 478 */	NdrFcShort( 0x1 ),	/* 1 */
/* 480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 484 */	0x12, 0x0,	/* FC_UP */
/* 486 */	NdrFcShort( 0xff6c ),	/* Offset= -148 (338) */
/* 488 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 490 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 492 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 494 */	NdrFcShort( 0x8 ),	/* 8 */
/* 496 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 498 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 500 */	NdrFcShort( 0x4 ),	/* 4 */
/* 502 */	NdrFcShort( 0x4 ),	/* 4 */
/* 504 */	0x11, 0x0,	/* FC_RP */
/* 506 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (460) */
/* 508 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 510 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 512 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 520 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 522 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 526 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 528 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 530 */	NdrFcShort( 0xff4a ),	/* Offset= -182 (348) */
/* 532 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 534 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 536 */	NdrFcShort( 0x8 ),	/* 8 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	NdrFcShort( 0x6 ),	/* Offset= 6 (546) */
/* 542 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 544 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 546 */	
			0x11, 0x0,	/* FC_RP */
/* 548 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (512) */
/* 550 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 558 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 560 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 564 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 566 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 568 */	NdrFcShort( 0xff36 ),	/* Offset= -202 (366) */
/* 570 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 572 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 574 */	NdrFcShort( 0x8 ),	/* 8 */
/* 576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 578 */	NdrFcShort( 0x6 ),	/* Offset= 6 (584) */
/* 580 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 582 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 584 */	
			0x11, 0x0,	/* FC_RP */
/* 586 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (550) */
/* 588 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 590 */	NdrFcShort( 0x4 ),	/* 4 */
/* 592 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 596 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 598 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 600 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 602 */	NdrFcShort( 0x4 ),	/* 4 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */
/* 606 */	NdrFcShort( 0x1 ),	/* 1 */
/* 608 */	NdrFcShort( 0x0 ),	/* 0 */
/* 610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 612 */	0x12, 0x0,	/* FC_UP */
/* 614 */	NdrFcShort( 0x192 ),	/* Offset= 402 (1016) */
/* 616 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 618 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 620 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 622 */	NdrFcShort( 0x8 ),	/* 8 */
/* 624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 626 */	NdrFcShort( 0x6 ),	/* Offset= 6 (632) */
/* 628 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 630 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 632 */	
			0x11, 0x0,	/* FC_RP */
/* 634 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (588) */
/* 636 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 638 */	NdrFcLong( 0x2f ),	/* 47 */
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 646 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 648 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 650 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 652 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 654 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 656 */	NdrFcShort( 0x1 ),	/* 1 */
/* 658 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 660 */	NdrFcShort( 0x4 ),	/* 4 */
/* 662 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 664 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 666 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 668 */	NdrFcShort( 0x10 ),	/* 16 */
/* 670 */	NdrFcShort( 0x0 ),	/* 0 */
/* 672 */	NdrFcShort( 0xa ),	/* Offset= 10 (682) */
/* 674 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 676 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 678 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (636) */
/* 680 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 682 */	
			0x12, 0x0,	/* FC_UP */
/* 684 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (654) */
/* 686 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 688 */	NdrFcShort( 0x4 ),	/* 4 */
/* 690 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 694 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 696 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 698 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 700 */	NdrFcShort( 0x4 ),	/* 4 */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x1 ),	/* 1 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	0x12, 0x0,	/* FC_UP */
/* 712 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (666) */
/* 714 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 716 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 718 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 720 */	NdrFcShort( 0x8 ),	/* 8 */
/* 722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 724 */	NdrFcShort( 0x6 ),	/* Offset= 6 (730) */
/* 726 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 728 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 730 */	
			0x11, 0x0,	/* FC_RP */
/* 732 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (686) */
/* 734 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 736 */	NdrFcShort( 0x8 ),	/* 8 */
/* 738 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 740 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 742 */	NdrFcShort( 0x10 ),	/* 16 */
/* 744 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 746 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 748 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (734) */
			0x5b,		/* FC_END */
/* 752 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 754 */	NdrFcShort( 0x18 ),	/* 24 */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 758 */	NdrFcShort( 0xa ),	/* Offset= 10 (768) */
/* 760 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 762 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 764 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (740) */
/* 766 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 768 */	
			0x11, 0x0,	/* FC_RP */
/* 770 */	NdrFcShort( 0xfefe ),	/* Offset= -258 (512) */
/* 772 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 774 */	NdrFcShort( 0x1 ),	/* 1 */
/* 776 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 780 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 782 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 784 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 786 */	NdrFcShort( 0x8 ),	/* 8 */
/* 788 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 790 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 792 */	NdrFcShort( 0x4 ),	/* 4 */
/* 794 */	NdrFcShort( 0x4 ),	/* 4 */
/* 796 */	0x12, 0x0,	/* FC_UP */
/* 798 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (772) */
/* 800 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 802 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 804 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 806 */	NdrFcShort( 0x2 ),	/* 2 */
/* 808 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 814 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 816 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 818 */	NdrFcShort( 0x8 ),	/* 8 */
/* 820 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 822 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 824 */	NdrFcShort( 0x4 ),	/* 4 */
/* 826 */	NdrFcShort( 0x4 ),	/* 4 */
/* 828 */	0x12, 0x0,	/* FC_UP */
/* 830 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (804) */
/* 832 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 834 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 836 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 838 */	NdrFcShort( 0x4 ),	/* 4 */
/* 840 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 842 */	NdrFcShort( 0x0 ),	/* 0 */
/* 844 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 846 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 848 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 850 */	NdrFcShort( 0x8 ),	/* 8 */
/* 852 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 854 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 856 */	NdrFcShort( 0x4 ),	/* 4 */
/* 858 */	NdrFcShort( 0x4 ),	/* 4 */
/* 860 */	0x12, 0x0,	/* FC_UP */
/* 862 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (836) */
/* 864 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 866 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 868 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 872 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 874 */	NdrFcShort( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 878 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 880 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 882 */	NdrFcShort( 0x8 ),	/* 8 */
/* 884 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 886 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 888 */	NdrFcShort( 0x4 ),	/* 4 */
/* 890 */	NdrFcShort( 0x4 ),	/* 4 */
/* 892 */	0x12, 0x0,	/* FC_UP */
/* 894 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (868) */
/* 896 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 898 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 900 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 902 */	NdrFcShort( 0x8 ),	/* 8 */
/* 904 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 906 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 908 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 910 */	NdrFcShort( 0x8 ),	/* 8 */
/* 912 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 914 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 916 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 918 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 920 */	NdrFcShort( 0xffec ),	/* Offset= -20 (900) */
/* 922 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 924 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 926 */	NdrFcShort( 0x28 ),	/* 40 */
/* 928 */	NdrFcShort( 0xffec ),	/* Offset= -20 (908) */
/* 930 */	NdrFcShort( 0x0 ),	/* Offset= 0 (930) */
/* 932 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 934 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 936 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 938 */	NdrFcShort( 0xfdde ),	/* Offset= -546 (392) */
/* 940 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 942 */	
			0x12, 0x0,	/* FC_UP */
/* 944 */	NdrFcShort( 0xfeea ),	/* Offset= -278 (666) */
/* 946 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 948 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 950 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 952 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 954 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 956 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 958 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 960 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 962 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 964 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 966 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 968 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 970 */	
			0x12, 0x0,	/* FC_UP */
/* 972 */	NdrFcShort( 0xfd70 ),	/* Offset= -656 (316) */
/* 974 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 976 */	NdrFcShort( 0xfd72 ),	/* Offset= -654 (322) */
/* 978 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 980 */	NdrFcShort( 0xfd88 ),	/* Offset= -632 (348) */
/* 982 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 984 */	NdrFcShort( 0xfd96 ),	/* Offset= -618 (366) */
/* 986 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 988 */	NdrFcShort( 0xfda4 ),	/* Offset= -604 (384) */
/* 990 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 992 */	NdrFcShort( 0x2 ),	/* Offset= 2 (994) */
/* 994 */	
			0x12, 0x0,	/* FC_UP */
/* 996 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1016) */
/* 998 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1000 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1002 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1004 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1006 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1008 */	
			0x12, 0x0,	/* FC_UP */
/* 1010 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (998) */
/* 1012 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1014 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1016 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1018 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1020 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1022 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1022) */
/* 1024 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1026 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1028 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1030 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1032 */	NdrFcShort( 0xfc0a ),	/* Offset= -1014 (18) */
/* 1034 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1036 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1040 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0xfbfa ),	/* Offset= -1030 (14) */
/* 1046 */	
			0x11, 0x0,	/* FC_RP */
/* 1048 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1054) */
/* 1050 */	
			0x13, 0x0,	/* FC_OP */
/* 1052 */	NdrFcShort( 0xfd36 ),	/* Offset= -714 (338) */
/* 1054 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1056 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1058 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1060 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1062 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1050) */
/* 1064 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 1066 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1068) */
/* 1068 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1070 */	NdrFcLong( 0x55b2c551 ),	/* 1437779281 */
/* 1074 */	NdrFcShort( 0x69f1 ),	/* 27121 */
/* 1076 */	NdrFcShort( 0x43d7 ),	/* 17367 */
/* 1078 */	0x9d,		/* 157 */
			0xca,		/* 202 */
/* 1080 */	0x59,		/* 89 */
			0x98,		/* 152 */
/* 1082 */	0x9c,		/* 156 */
			0x3b,		/* 59 */
/* 1084 */	0x18,		/* 24 */
			0x8,		/* 8 */
/* 1086 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1088 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1090 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1092 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1098) */
/* 1094 */	
			0x13, 0x0,	/* FC_OP */
/* 1096 */	NdrFcShort( 0xffb0 ),	/* Offset= -80 (1016) */
/* 1098 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1102 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1106 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1094) */
/* 1108 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1110 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1112 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1116 */	NdrFcShort( 0xfce6 ),	/* Offset= -794 (322) */
/* 1118 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1120 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1122) */
/* 1122 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1124 */	NdrFcLong( 0xeb26427b ),	/* -349814149 */
/* 1128 */	NdrFcShort( 0x82ac ),	/* -32084 */
/* 1130 */	NdrFcShort( 0x45fa ),	/* 17914 */
/* 1132 */	0x80,		/* 128 */
			0xaf,		/* 175 */
/* 1134 */	0xf9,		/* 249 */
			0x3c,		/* 60 */
/* 1136 */	0x8a,		/* 138 */
			0x31,		/* 49 */
/* 1138 */	0x89,		/* 137 */
			0xad,		/* 173 */
/* 1140 */	
			0x11, 0x0,	/* FC_RP */
/* 1142 */	NdrFcShort( 0xffde ),	/* Offset= -34 (1108) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
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



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISRHalfStage, ver. 0.0,
   GUID={0x55B2C551,0x69F1,0x43D7,{0x9D,0xCA,0x59,0x98,0x9C,0x3B,0x18,0x08}} */

#pragma code_seg(".orpc")
static const unsigned short ISRHalfStage_FormatStringOffsetTable[] =
    {
    0,
    42,
    84,
    132,
    180,
    228,
    282,
    330,
    366,
    402
    };

static const MIDL_STUBLESS_PROXY_INFO ISRHalfStage_ProxyInfo =
    {
    &Object_StubDesc,
    StageRace__MIDL_ProcFormatString.Format,
    &ISRHalfStage_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISRHalfStage_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    StageRace__MIDL_ProcFormatString.Format,
    &ISRHalfStage_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _ISRHalfStageProxyVtbl = 
{
    &ISRHalfStage_ProxyInfo,
    &IID_ISRHalfStage,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::SetArrivalByTime */ ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::SetArrivalByRank */ ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::SetArrival */ ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::GetArrivalByRank */ ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::GetArrivalByStaNo */ ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::GetArrivalByTime */ ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::GetStart */ ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::ResetArrival */ ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::EnumerateStarts */ ,
    (void *) (INT_PTR) -1 /* ISRHalfStage::SetTimingIdle */
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

#pragma code_seg(".orpc")
static const unsigned short IStageRaceDoc_FormatStringOffsetTable[] =
    {
    432,
    474,
    510,
    558,
    600,
    648,
    690
    };

static const MIDL_STUBLESS_PROXY_INFO IStageRaceDoc_ProxyInfo =
    {
    &Object_StubDesc,
    StageRace__MIDL_ProcFormatString.Format,
    &IStageRaceDoc_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IStageRaceDoc_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    StageRace__MIDL_ProcFormatString.Format,
    &IStageRaceDoc_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IStageRaceDocProxyVtbl = 
{
    &IStageRaceDoc_ProxyInfo,
    &IID_IStageRaceDoc,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IStageRaceDoc::GetCountHalfStages */ ,
    (void *) (INT_PTR) -1 /* IStageRaceDoc::GetCountFullStages */ ,
    (void *) (INT_PTR) -1 /* IStageRaceDoc::GetHalfStageName */ ,
    (void *) (INT_PTR) -1 /* IStageRaceDoc::GetFullStageName */ ,
    (void *) (INT_PTR) -1 /* IStageRaceDoc::GetHalfStage */ ,
    (void *) (INT_PTR) -1 /* IStageRaceDoc::CompetitorExists */ ,
    (void *) (INT_PTR) -1 /* IStageRaceDoc::GetCompetitor */
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

#pragma code_seg(".orpc")
static const unsigned short IStageRaceServer_FormatStringOffsetTable[] =
    {
    738,
    774,
    816,
    858
    };

static const MIDL_STUBLESS_PROXY_INFO IStageRaceServer_ProxyInfo =
    {
    &Object_StubDesc,
    StageRace__MIDL_ProcFormatString.Format,
    &IStageRaceServer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IStageRaceServer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    StageRace__MIDL_ProcFormatString.Format,
    &IStageRaceServer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IStageRaceServerProxyVtbl = 
{
    &IStageRaceServer_ProxyInfo,
    &IID_IStageRaceServer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IStageRaceServer::EnumerateDocuments */ ,
    (void *) (INT_PTR) -1 /* IStageRaceServer::SendMessage */ ,
    (void *) (INT_PTR) -1 /* IStageRaceServer::GetDocument */ ,
    (void *) (INT_PTR) -1 /* IStageRaceServer::GetActiveDocName */
};

const CInterfaceStubVtbl _IStageRaceServerStubVtbl =
{
    &IID_IStageRaceServer,
    &IStageRaceServer_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

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
    StageRace__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _StageRace_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ISRHalfStageProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IStageRaceDocProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IStageRaceServerProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _StageRace_StubVtblList[] = 
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
    0, /* no delegation */
    & _StageRace_IID_Lookup, 
    3,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

