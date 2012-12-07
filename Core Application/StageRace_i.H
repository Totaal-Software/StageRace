

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __StageRace_i_h__
#define __StageRace_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISRHalfStage_FWD_DEFINED__
#define __ISRHalfStage_FWD_DEFINED__
typedef interface ISRHalfStage ISRHalfStage;
#endif 	/* __ISRHalfStage_FWD_DEFINED__ */


#ifndef __IStageRaceDoc_FWD_DEFINED__
#define __IStageRaceDoc_FWD_DEFINED__
typedef interface IStageRaceDoc IStageRaceDoc;
#endif 	/* __IStageRaceDoc_FWD_DEFINED__ */


#ifndef __IStageRaceServer_FWD_DEFINED__
#define __IStageRaceServer_FWD_DEFINED__
typedef interface IStageRaceServer IStageRaceServer;
#endif 	/* __IStageRaceServer_FWD_DEFINED__ */


#ifndef __StageRaceServer_FWD_DEFINED__
#define __StageRaceServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class StageRaceServer StageRaceServer;
#else
typedef struct StageRaceServer StageRaceServer;
#endif /* __cplusplus */

#endif 	/* __StageRaceServer_FWD_DEFINED__ */


#ifndef __StageRaceDoc_FWD_DEFINED__
#define __StageRaceDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class StageRaceDoc StageRaceDoc;
#else
typedef struct StageRaceDoc StageRaceDoc;
#endif /* __cplusplus */

#endif 	/* __StageRaceDoc_FWD_DEFINED__ */


#ifndef __SRHalfStage_FWD_DEFINED__
#define __SRHalfStage_FWD_DEFINED__

#ifdef __cplusplus
typedef class SRHalfStage SRHalfStage;
#else
typedef struct SRHalfStage SRHalfStage;
#endif /* __cplusplus */

#endif 	/* __SRHalfStage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISRHalfStage_INTERFACE_DEFINED__
#define __ISRHalfStage_INTERFACE_DEFINED__

/* interface ISRHalfStage */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISRHalfStage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("55B2C551-69F1-43D7-9DCA-59989C3B1808")
    ISRHalfStage : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetArrivalByTime( 
            unsigned short nStaNo,
            unsigned long nUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetArrivalByRank( 
            unsigned short nStaNo,
            unsigned short nRank) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetArrival( 
            unsigned short nStaNo,
            unsigned short nRank,
            unsigned long nUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetArrivalByRank( 
            unsigned short nRank,
            unsigned short *nStaNo,
            unsigned long *nUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetArrivalByStaNo( 
            unsigned short nStaNo,
            unsigned short *nRank,
            unsigned long *nUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetArrivalByTime( 
            unsigned long nUnits,
            unsigned short *nStaNo,
            unsigned short *nRank,
            unsigned long *pnUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStart( 
            unsigned short nStaNo,
            unsigned short *nOrder,
            unsigned long *nUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetArrival( 
            unsigned int nStaNo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumerateStarts( 
            VARIANT *pStarts) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTimingIdle( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISRHalfStageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISRHalfStage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISRHalfStage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISRHalfStage * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetArrivalByTime )( 
            ISRHalfStage * This,
            unsigned short nStaNo,
            unsigned long nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetArrivalByRank )( 
            ISRHalfStage * This,
            unsigned short nStaNo,
            unsigned short nRank);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetArrival )( 
            ISRHalfStage * This,
            unsigned short nStaNo,
            unsigned short nRank,
            unsigned long nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetArrivalByRank )( 
            ISRHalfStage * This,
            unsigned short nRank,
            unsigned short *nStaNo,
            unsigned long *nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetArrivalByStaNo )( 
            ISRHalfStage * This,
            unsigned short nStaNo,
            unsigned short *nRank,
            unsigned long *nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetArrivalByTime )( 
            ISRHalfStage * This,
            unsigned long nUnits,
            unsigned short *nStaNo,
            unsigned short *nRank,
            unsigned long *pnUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetStart )( 
            ISRHalfStage * This,
            unsigned short nStaNo,
            unsigned short *nOrder,
            unsigned long *nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetArrival )( 
            ISRHalfStage * This,
            unsigned int nStaNo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumerateStarts )( 
            ISRHalfStage * This,
            VARIANT *pStarts);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTimingIdle )( 
            ISRHalfStage * This);
        
        END_INTERFACE
    } ISRHalfStageVtbl;

    interface ISRHalfStage
    {
        CONST_VTBL struct ISRHalfStageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISRHalfStage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISRHalfStage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISRHalfStage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISRHalfStage_SetArrivalByTime(This,nStaNo,nUnits)	\
    ( (This)->lpVtbl -> SetArrivalByTime(This,nStaNo,nUnits) ) 

#define ISRHalfStage_SetArrivalByRank(This,nStaNo,nRank)	\
    ( (This)->lpVtbl -> SetArrivalByRank(This,nStaNo,nRank) ) 

#define ISRHalfStage_SetArrival(This,nStaNo,nRank,nUnits)	\
    ( (This)->lpVtbl -> SetArrival(This,nStaNo,nRank,nUnits) ) 

#define ISRHalfStage_GetArrivalByRank(This,nRank,nStaNo,nUnits)	\
    ( (This)->lpVtbl -> GetArrivalByRank(This,nRank,nStaNo,nUnits) ) 

#define ISRHalfStage_GetArrivalByStaNo(This,nStaNo,nRank,nUnits)	\
    ( (This)->lpVtbl -> GetArrivalByStaNo(This,nStaNo,nRank,nUnits) ) 

#define ISRHalfStage_GetArrivalByTime(This,nUnits,nStaNo,nRank,pnUnits)	\
    ( (This)->lpVtbl -> GetArrivalByTime(This,nUnits,nStaNo,nRank,pnUnits) ) 

#define ISRHalfStage_GetStart(This,nStaNo,nOrder,nUnits)	\
    ( (This)->lpVtbl -> GetStart(This,nStaNo,nOrder,nUnits) ) 

#define ISRHalfStage_ResetArrival(This,nStaNo)	\
    ( (This)->lpVtbl -> ResetArrival(This,nStaNo) ) 

#define ISRHalfStage_EnumerateStarts(This,pStarts)	\
    ( (This)->lpVtbl -> EnumerateStarts(This,pStarts) ) 

#define ISRHalfStage_SetTimingIdle(This)	\
    ( (This)->lpVtbl -> SetTimingIdle(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISRHalfStage_INTERFACE_DEFINED__ */


#ifndef __IStageRaceDoc_INTERFACE_DEFINED__
#define __IStageRaceDoc_INTERFACE_DEFINED__

/* interface IStageRaceDoc */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IStageRaceDoc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EB26427B-82AC-45FA-80AF-F93C8A3189AD")
    IStageRaceDoc : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCountHalfStages( 
            /* [in] */ int nFS,
            /* [out][in] */ int *pnCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCountFullStages( 
            /* [out][in] */ int *pnCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHalfStageName( 
            /* [in] */ int nFS,
            /* [in] */ int nHS,
            /* [out][in] */ BSTR *pname) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFullStageName( 
            /* [in] */ int nFS,
            /* [out][in] */ BSTR *pname) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHalfStage( 
            /* [in] */ int nFS,
            /* [in] */ int nHS,
            /* [out][in] */ ISRHalfStage **ppHS) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CompetitorExists( 
            /* [in] */ unsigned short nStaNo,
            /* [out] */ BOOL *bExists) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCompetitor( 
            /* [in] */ unsigned short nStaNo,
            /* [out][in] */ BSTR *pname,
            /* [out][in] */ BSTR *pteam) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStageRaceDocVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStageRaceDoc * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStageRaceDoc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStageRaceDoc * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCountHalfStages )( 
            IStageRaceDoc * This,
            /* [in] */ int nFS,
            /* [out][in] */ int *pnCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCountFullStages )( 
            IStageRaceDoc * This,
            /* [out][in] */ int *pnCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHalfStageName )( 
            IStageRaceDoc * This,
            /* [in] */ int nFS,
            /* [in] */ int nHS,
            /* [out][in] */ BSTR *pname);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFullStageName )( 
            IStageRaceDoc * This,
            /* [in] */ int nFS,
            /* [out][in] */ BSTR *pname);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHalfStage )( 
            IStageRaceDoc * This,
            /* [in] */ int nFS,
            /* [in] */ int nHS,
            /* [out][in] */ ISRHalfStage **ppHS);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CompetitorExists )( 
            IStageRaceDoc * This,
            /* [in] */ unsigned short nStaNo,
            /* [out] */ BOOL *bExists);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCompetitor )( 
            IStageRaceDoc * This,
            /* [in] */ unsigned short nStaNo,
            /* [out][in] */ BSTR *pname,
            /* [out][in] */ BSTR *pteam);
        
        END_INTERFACE
    } IStageRaceDocVtbl;

    interface IStageRaceDoc
    {
        CONST_VTBL struct IStageRaceDocVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStageRaceDoc_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStageRaceDoc_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStageRaceDoc_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStageRaceDoc_GetCountHalfStages(This,nFS,pnCount)	\
    ( (This)->lpVtbl -> GetCountHalfStages(This,nFS,pnCount) ) 

#define IStageRaceDoc_GetCountFullStages(This,pnCount)	\
    ( (This)->lpVtbl -> GetCountFullStages(This,pnCount) ) 

#define IStageRaceDoc_GetHalfStageName(This,nFS,nHS,pname)	\
    ( (This)->lpVtbl -> GetHalfStageName(This,nFS,nHS,pname) ) 

#define IStageRaceDoc_GetFullStageName(This,nFS,pname)	\
    ( (This)->lpVtbl -> GetFullStageName(This,nFS,pname) ) 

#define IStageRaceDoc_GetHalfStage(This,nFS,nHS,ppHS)	\
    ( (This)->lpVtbl -> GetHalfStage(This,nFS,nHS,ppHS) ) 

#define IStageRaceDoc_CompetitorExists(This,nStaNo,bExists)	\
    ( (This)->lpVtbl -> CompetitorExists(This,nStaNo,bExists) ) 

#define IStageRaceDoc_GetCompetitor(This,nStaNo,pname,pteam)	\
    ( (This)->lpVtbl -> GetCompetitor(This,nStaNo,pname,pteam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStageRaceDoc_INTERFACE_DEFINED__ */


#ifndef __IStageRaceServer_INTERFACE_DEFINED__
#define __IStageRaceServer_INTERFACE_DEFINED__

/* interface IStageRaceServer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IStageRaceServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("31AC26B2-80B3-4ACF-BBB9-686CA55EDA44")
    IStageRaceServer : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumerateDocuments( 
            /* [out] */ VARIANT *pDocs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendMessage( 
            /* [in] */ BSTR user,
            /* [in] */ BSTR message) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDocument( 
            /* [in] */ BSTR title,
            /* [out] */ IStageRaceDoc **ppDoc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActiveDocName( 
            BSTR *pTitle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStageRaceServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStageRaceServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStageRaceServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStageRaceServer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumerateDocuments )( 
            IStageRaceServer * This,
            /* [out] */ VARIANT *pDocs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendMessage )( 
            IStageRaceServer * This,
            /* [in] */ BSTR user,
            /* [in] */ BSTR message);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDocument )( 
            IStageRaceServer * This,
            /* [in] */ BSTR title,
            /* [out] */ IStageRaceDoc **ppDoc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetActiveDocName )( 
            IStageRaceServer * This,
            BSTR *pTitle);
        
        END_INTERFACE
    } IStageRaceServerVtbl;

    interface IStageRaceServer
    {
        CONST_VTBL struct IStageRaceServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStageRaceServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStageRaceServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStageRaceServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStageRaceServer_EnumerateDocuments(This,pDocs)	\
    ( (This)->lpVtbl -> EnumerateDocuments(This,pDocs) ) 

#define IStageRaceServer_SendMessage(This,user,message)	\
    ( (This)->lpVtbl -> SendMessage(This,user,message) ) 

#define IStageRaceServer_GetDocument(This,title,ppDoc)	\
    ( (This)->lpVtbl -> GetDocument(This,title,ppDoc) ) 

#define IStageRaceServer_GetActiveDocName(This,pTitle)	\
    ( (This)->lpVtbl -> GetActiveDocName(This,pTitle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStageRaceServer_INTERFACE_DEFINED__ */



#ifndef __StageRaceLib_LIBRARY_DEFINED__
#define __StageRaceLib_LIBRARY_DEFINED__

/* library StageRaceLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_StageRaceLib;

EXTERN_C const CLSID CLSID_StageRaceServer;

#ifdef __cplusplus

class DECLSPEC_UUID("5AD7E1A3-B139-4A1B-83E0-117F2F3831D0")
StageRaceServer;
#endif

EXTERN_C const CLSID CLSID_StageRaceDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("C8B27B99-DDC6-457E-B7DC-8DC35079A9C6")
StageRaceDoc;
#endif

EXTERN_C const CLSID CLSID_SRHalfStage;

#ifdef __cplusplus

class DECLSPEC_UUID("6612404C-66ED-4CAB-8506-4B8B5967F18C")
SRHalfStage;
#endif
#endif /* __StageRaceLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


