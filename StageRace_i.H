/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 11 20:45:19 2006
 */
/* Compiler settings for D:\Projects\StageRace\trunk\StageRace.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifdef __cplusplus
extern "C"{
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

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

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
            unsigned short __RPC_FAR *nStaNo,
            unsigned long __RPC_FAR *nUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetArrivalByStaNo( 
            unsigned short nStaNo,
            unsigned short __RPC_FAR *nRank,
            unsigned long __RPC_FAR *nUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetArrivalByTime( 
            unsigned long nUnits,
            unsigned short __RPC_FAR *nStaNo,
            unsigned short __RPC_FAR *nRank,
            unsigned long __RPC_FAR *pnUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStart( 
            unsigned short nStaNo,
            unsigned short __RPC_FAR *nOrder,
            unsigned long __RPC_FAR *nUnits) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetArrival( 
            unsigned int nStaNo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumerateStarts( 
            VARIANT __RPC_FAR *pStarts) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTimingIdle( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISRHalfStageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISRHalfStage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISRHalfStage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISRHalfStage __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetArrivalByTime )( 
            ISRHalfStage __RPC_FAR * This,
            unsigned short nStaNo,
            unsigned long nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetArrivalByRank )( 
            ISRHalfStage __RPC_FAR * This,
            unsigned short nStaNo,
            unsigned short nRank);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetArrival )( 
            ISRHalfStage __RPC_FAR * This,
            unsigned short nStaNo,
            unsigned short nRank,
            unsigned long nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetArrivalByRank )( 
            ISRHalfStage __RPC_FAR * This,
            unsigned short nRank,
            unsigned short __RPC_FAR *nStaNo,
            unsigned long __RPC_FAR *nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetArrivalByStaNo )( 
            ISRHalfStage __RPC_FAR * This,
            unsigned short nStaNo,
            unsigned short __RPC_FAR *nRank,
            unsigned long __RPC_FAR *nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetArrivalByTime )( 
            ISRHalfStage __RPC_FAR * This,
            unsigned long nUnits,
            unsigned short __RPC_FAR *nStaNo,
            unsigned short __RPC_FAR *nRank,
            unsigned long __RPC_FAR *pnUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStart )( 
            ISRHalfStage __RPC_FAR * This,
            unsigned short nStaNo,
            unsigned short __RPC_FAR *nOrder,
            unsigned long __RPC_FAR *nUnits);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetArrival )( 
            ISRHalfStage __RPC_FAR * This,
            unsigned int nStaNo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateStarts )( 
            ISRHalfStage __RPC_FAR * This,
            VARIANT __RPC_FAR *pStarts);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimingIdle )( 
            ISRHalfStage __RPC_FAR * This);
        
        END_INTERFACE
    } ISRHalfStageVtbl;

    interface ISRHalfStage
    {
        CONST_VTBL struct ISRHalfStageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISRHalfStage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISRHalfStage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISRHalfStage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISRHalfStage_SetArrivalByTime(This,nStaNo,nUnits)	\
    (This)->lpVtbl -> SetArrivalByTime(This,nStaNo,nUnits)

#define ISRHalfStage_SetArrivalByRank(This,nStaNo,nRank)	\
    (This)->lpVtbl -> SetArrivalByRank(This,nStaNo,nRank)

#define ISRHalfStage_SetArrival(This,nStaNo,nRank,nUnits)	\
    (This)->lpVtbl -> SetArrival(This,nStaNo,nRank,nUnits)

#define ISRHalfStage_GetArrivalByRank(This,nRank,nStaNo,nUnits)	\
    (This)->lpVtbl -> GetArrivalByRank(This,nRank,nStaNo,nUnits)

#define ISRHalfStage_GetArrivalByStaNo(This,nStaNo,nRank,nUnits)	\
    (This)->lpVtbl -> GetArrivalByStaNo(This,nStaNo,nRank,nUnits)

#define ISRHalfStage_GetArrivalByTime(This,nUnits,nStaNo,nRank,pnUnits)	\
    (This)->lpVtbl -> GetArrivalByTime(This,nUnits,nStaNo,nRank,pnUnits)

#define ISRHalfStage_GetStart(This,nStaNo,nOrder,nUnits)	\
    (This)->lpVtbl -> GetStart(This,nStaNo,nOrder,nUnits)

#define ISRHalfStage_ResetArrival(This,nStaNo)	\
    (This)->lpVtbl -> ResetArrival(This,nStaNo)

#define ISRHalfStage_EnumerateStarts(This,pStarts)	\
    (This)->lpVtbl -> EnumerateStarts(This,pStarts)

#define ISRHalfStage_SetTimingIdle(This)	\
    (This)->lpVtbl -> SetTimingIdle(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_SetArrivalByTime_Proxy( 
    ISRHalfStage __RPC_FAR * This,
    unsigned short nStaNo,
    unsigned long nUnits);


void __RPC_STUB ISRHalfStage_SetArrivalByTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_SetArrivalByRank_Proxy( 
    ISRHalfStage __RPC_FAR * This,
    unsigned short nStaNo,
    unsigned short nRank);


void __RPC_STUB ISRHalfStage_SetArrivalByRank_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_SetArrival_Proxy( 
    ISRHalfStage __RPC_FAR * This,
    unsigned short nStaNo,
    unsigned short nRank,
    unsigned long nUnits);


void __RPC_STUB ISRHalfStage_SetArrival_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_GetArrivalByRank_Proxy( 
    ISRHalfStage __RPC_FAR * This,
    unsigned short nRank,
    unsigned short __RPC_FAR *nStaNo,
    unsigned long __RPC_FAR *nUnits);


void __RPC_STUB ISRHalfStage_GetArrivalByRank_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_GetArrivalByStaNo_Proxy( 
    ISRHalfStage __RPC_FAR * This,
    unsigned short nStaNo,
    unsigned short __RPC_FAR *nRank,
    unsigned long __RPC_FAR *nUnits);


void __RPC_STUB ISRHalfStage_GetArrivalByStaNo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_GetArrivalByTime_Proxy( 
    ISRHalfStage __RPC_FAR * This,
    unsigned long nUnits,
    unsigned short __RPC_FAR *nStaNo,
    unsigned short __RPC_FAR *nRank,
    unsigned long __RPC_FAR *pnUnits);


void __RPC_STUB ISRHalfStage_GetArrivalByTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_GetStart_Proxy( 
    ISRHalfStage __RPC_FAR * This,
    unsigned short nStaNo,
    unsigned short __RPC_FAR *nOrder,
    unsigned long __RPC_FAR *nUnits);


void __RPC_STUB ISRHalfStage_GetStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_ResetArrival_Proxy( 
    ISRHalfStage __RPC_FAR * This,
    unsigned int nStaNo);


void __RPC_STUB ISRHalfStage_ResetArrival_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_EnumerateStarts_Proxy( 
    ISRHalfStage __RPC_FAR * This,
    VARIANT __RPC_FAR *pStarts);


void __RPC_STUB ISRHalfStage_EnumerateStarts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISRHalfStage_SetTimingIdle_Proxy( 
    ISRHalfStage __RPC_FAR * This);


void __RPC_STUB ISRHalfStage_SetTimingIdle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [out][in] */ int __RPC_FAR *pnCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCountFullStages( 
            /* [out][in] */ int __RPC_FAR *pnCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHalfStageName( 
            /* [in] */ int nFS,
            /* [in] */ int nHS,
            /* [out][in] */ BSTR __RPC_FAR *pname) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFullStageName( 
            /* [in] */ int nFS,
            /* [out][in] */ BSTR __RPC_FAR *pname) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHalfStage( 
            /* [in] */ int nFS,
            /* [in] */ int nHS,
            /* [out][in] */ ISRHalfStage __RPC_FAR *__RPC_FAR *ppHS) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CompetitorExists( 
            /* [in] */ unsigned short nStaNo,
            /* [out] */ BOOL __RPC_FAR *bExists) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCompetitor( 
            /* [in] */ unsigned short nStaNo,
            /* [out][in] */ BSTR __RPC_FAR *pname,
            /* [out][in] */ BSTR __RPC_FAR *pteam) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStageRaceDocVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStageRaceDoc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStageRaceDoc __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStageRaceDoc __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCountHalfStages )( 
            IStageRaceDoc __RPC_FAR * This,
            /* [in] */ int nFS,
            /* [out][in] */ int __RPC_FAR *pnCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCountFullStages )( 
            IStageRaceDoc __RPC_FAR * This,
            /* [out][in] */ int __RPC_FAR *pnCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHalfStageName )( 
            IStageRaceDoc __RPC_FAR * This,
            /* [in] */ int nFS,
            /* [in] */ int nHS,
            /* [out][in] */ BSTR __RPC_FAR *pname);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFullStageName )( 
            IStageRaceDoc __RPC_FAR * This,
            /* [in] */ int nFS,
            /* [out][in] */ BSTR __RPC_FAR *pname);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHalfStage )( 
            IStageRaceDoc __RPC_FAR * This,
            /* [in] */ int nFS,
            /* [in] */ int nHS,
            /* [out][in] */ ISRHalfStage __RPC_FAR *__RPC_FAR *ppHS);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CompetitorExists )( 
            IStageRaceDoc __RPC_FAR * This,
            /* [in] */ unsigned short nStaNo,
            /* [out] */ BOOL __RPC_FAR *bExists);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCompetitor )( 
            IStageRaceDoc __RPC_FAR * This,
            /* [in] */ unsigned short nStaNo,
            /* [out][in] */ BSTR __RPC_FAR *pname,
            /* [out][in] */ BSTR __RPC_FAR *pteam);
        
        END_INTERFACE
    } IStageRaceDocVtbl;

    interface IStageRaceDoc
    {
        CONST_VTBL struct IStageRaceDocVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStageRaceDoc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStageRaceDoc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStageRaceDoc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStageRaceDoc_GetCountHalfStages(This,nFS,pnCount)	\
    (This)->lpVtbl -> GetCountHalfStages(This,nFS,pnCount)

#define IStageRaceDoc_GetCountFullStages(This,pnCount)	\
    (This)->lpVtbl -> GetCountFullStages(This,pnCount)

#define IStageRaceDoc_GetHalfStageName(This,nFS,nHS,pname)	\
    (This)->lpVtbl -> GetHalfStageName(This,nFS,nHS,pname)

#define IStageRaceDoc_GetFullStageName(This,nFS,pname)	\
    (This)->lpVtbl -> GetFullStageName(This,nFS,pname)

#define IStageRaceDoc_GetHalfStage(This,nFS,nHS,ppHS)	\
    (This)->lpVtbl -> GetHalfStage(This,nFS,nHS,ppHS)

#define IStageRaceDoc_CompetitorExists(This,nStaNo,bExists)	\
    (This)->lpVtbl -> CompetitorExists(This,nStaNo,bExists)

#define IStageRaceDoc_GetCompetitor(This,nStaNo,pname,pteam)	\
    (This)->lpVtbl -> GetCompetitor(This,nStaNo,pname,pteam)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceDoc_GetCountHalfStages_Proxy( 
    IStageRaceDoc __RPC_FAR * This,
    /* [in] */ int nFS,
    /* [out][in] */ int __RPC_FAR *pnCount);


void __RPC_STUB IStageRaceDoc_GetCountHalfStages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceDoc_GetCountFullStages_Proxy( 
    IStageRaceDoc __RPC_FAR * This,
    /* [out][in] */ int __RPC_FAR *pnCount);


void __RPC_STUB IStageRaceDoc_GetCountFullStages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceDoc_GetHalfStageName_Proxy( 
    IStageRaceDoc __RPC_FAR * This,
    /* [in] */ int nFS,
    /* [in] */ int nHS,
    /* [out][in] */ BSTR __RPC_FAR *pname);


void __RPC_STUB IStageRaceDoc_GetHalfStageName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceDoc_GetFullStageName_Proxy( 
    IStageRaceDoc __RPC_FAR * This,
    /* [in] */ int nFS,
    /* [out][in] */ BSTR __RPC_FAR *pname);


void __RPC_STUB IStageRaceDoc_GetFullStageName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceDoc_GetHalfStage_Proxy( 
    IStageRaceDoc __RPC_FAR * This,
    /* [in] */ int nFS,
    /* [in] */ int nHS,
    /* [out][in] */ ISRHalfStage __RPC_FAR *__RPC_FAR *ppHS);


void __RPC_STUB IStageRaceDoc_GetHalfStage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceDoc_CompetitorExists_Proxy( 
    IStageRaceDoc __RPC_FAR * This,
    /* [in] */ unsigned short nStaNo,
    /* [out] */ BOOL __RPC_FAR *bExists);


void __RPC_STUB IStageRaceDoc_CompetitorExists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceDoc_GetCompetitor_Proxy( 
    IStageRaceDoc __RPC_FAR * This,
    /* [in] */ unsigned short nStaNo,
    /* [out][in] */ BSTR __RPC_FAR *pname,
    /* [out][in] */ BSTR __RPC_FAR *pteam);


void __RPC_STUB IStageRaceDoc_GetCompetitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [out] */ VARIANT __RPC_FAR *pDocs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendMessage( 
            /* [in] */ BSTR user,
            /* [in] */ BSTR message) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDocument( 
            /* [in] */ BSTR title,
            /* [out] */ IStageRaceDoc __RPC_FAR *__RPC_FAR *ppDoc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActiveDocName( 
            BSTR __RPC_FAR *pTitle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStageRaceServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStageRaceServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStageRaceServer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStageRaceServer __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateDocuments )( 
            IStageRaceServer __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pDocs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessage )( 
            IStageRaceServer __RPC_FAR * This,
            /* [in] */ BSTR user,
            /* [in] */ BSTR message);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDocument )( 
            IStageRaceServer __RPC_FAR * This,
            /* [in] */ BSTR title,
            /* [out] */ IStageRaceDoc __RPC_FAR *__RPC_FAR *ppDoc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActiveDocName )( 
            IStageRaceServer __RPC_FAR * This,
            BSTR __RPC_FAR *pTitle);
        
        END_INTERFACE
    } IStageRaceServerVtbl;

    interface IStageRaceServer
    {
        CONST_VTBL struct IStageRaceServerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStageRaceServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStageRaceServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStageRaceServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStageRaceServer_EnumerateDocuments(This,pDocs)	\
    (This)->lpVtbl -> EnumerateDocuments(This,pDocs)

#define IStageRaceServer_SendMessage(This,user,message)	\
    (This)->lpVtbl -> SendMessage(This,user,message)

#define IStageRaceServer_GetDocument(This,title,ppDoc)	\
    (This)->lpVtbl -> GetDocument(This,title,ppDoc)

#define IStageRaceServer_GetActiveDocName(This,pTitle)	\
    (This)->lpVtbl -> GetActiveDocName(This,pTitle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceServer_EnumerateDocuments_Proxy( 
    IStageRaceServer __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pDocs);


void __RPC_STUB IStageRaceServer_EnumerateDocuments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceServer_SendMessage_Proxy( 
    IStageRaceServer __RPC_FAR * This,
    /* [in] */ BSTR user,
    /* [in] */ BSTR message);


void __RPC_STUB IStageRaceServer_SendMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceServer_GetDocument_Proxy( 
    IStageRaceServer __RPC_FAR * This,
    /* [in] */ BSTR title,
    /* [out] */ IStageRaceDoc __RPC_FAR *__RPC_FAR *ppDoc);


void __RPC_STUB IStageRaceServer_GetDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStageRaceServer_GetActiveDocName_Proxy( 
    IStageRaceServer __RPC_FAR * This,
    BSTR __RPC_FAR *pTitle);


void __RPC_STUB IStageRaceServer_GetActiveDocName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
