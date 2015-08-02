

/* this ALWAYS GENERATED file contains the RPC client stubs */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Aug 02 15:26:13 2015
 */
/* Compiler settings for ms-drsr.idl:
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
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#include <string.h>

#include "ms-drsr_h.h"

#define TYPE_FORMAT_STRING_SIZE   8727                              
#define PROC_FORMAT_STRING_SIZE   2047                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _ms2Ddrsr_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } ms2Ddrsr_MIDL_TYPE_FORMAT_STRING;

typedef struct _ms2Ddrsr_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } ms2Ddrsr_MIDL_PROC_FORMAT_STRING;

typedef struct _ms2Ddrsr_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } ms2Ddrsr_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const ms2Ddrsr_MIDL_TYPE_FORMAT_STRING ms2Ddrsr__MIDL_TypeFormatString;
extern const ms2Ddrsr_MIDL_PROC_FORMAT_STRING ms2Ddrsr__MIDL_ProcFormatString;
extern const ms2Ddrsr_MIDL_EXPR_FORMAT_STRING ms2Ddrsr__MIDL_ExprFormatString;

#define GENERIC_BINDING_TABLE_SIZE   0            


/* Standard interface: drsuapi, ver. 4.0,
   GUID={0xe3514235,0x4b06,0x11d1,{0xab,0x04,0x00,0xc0,0x4f,0xc2,0xdc,0xd2}} */



static const RPC_CLIENT_INTERFACE drsuapi___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0xe3514235,0x4b06,0x11d1,{0xab,0x04,0x00,0xc0,0x4f,0xc2,0xdc,0xd2}},{4,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0x00000000
    };
RPC_IF_HANDLE drsuapi_v4_0_c_ifspec = (RPC_IF_HANDLE)& drsuapi___RpcClientInterface;

extern const MIDL_STUB_DESC drsuapi_StubDesc;

static RPC_BINDING_HANDLE drsuapi__MIDL_AutoBindHandle;


ULONG IDL_DRSBind( 
    /* [in] */ handle_t rpc_handle,
    /* [unique][in] */ UUID *puuidClientDsa,
    /* [unique][in] */ DRS_EXTENSIONS *pextClient,
    /* [out] */ DRS_EXTENSIONS **ppextServer,
    /* [ref][out] */ DRS_HANDLE *phDrs)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[0],
                  ( unsigned char * )&rpc_handle);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSUnbind( 
    /* [ref][out][in] */ DRS_HANDLE *phDrs)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[58],
                  ( unsigned char * )&phDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSReplicaSync( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwVersion,
    /* [switch_is][ref][in] */ DRS_MSG_REPSYNC *pmsgSync)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[100],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSGetNCChanges( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_GETCHGREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_GETCHGREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[154],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSUpdateRefs( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwVersion,
    /* [switch_is][ref][in] */ DRS_MSG_UPDREFS *pmsgUpdRefs)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[220],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSReplicaAdd( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwVersion,
    /* [switch_is][ref][in] */ DRS_MSG_REPADD *pmsgAdd)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[274],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSReplicaDel( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwVersion,
    /* [switch_is][ref][in] */ DRS_MSG_REPDEL *pmsgDel)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[328],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSReplicaModify( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwVersion,
    /* [switch_is][ref][in] */ DRS_MSG_REPMOD *pmsgMod)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[382],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSVerifyNames( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_VERIFYREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_VERIFYREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[436],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSGetMemberships( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_REVMEMB_REQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_REVMEMB_REPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[502],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSInterDomainMove( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_MOVEREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_MOVEREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[568],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSGetNT4ChangeLog( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_NT4_CHGLOG_REQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_NT4_CHGLOG_REPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[634],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSCrackNames( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_CRACKREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_CRACKREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[700],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSWriteSPN( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_SPNREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_SPNREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[766],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSRemoveDsServer( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_RMSVRREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_RMSVRREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[832],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSRemoveDsDomain( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_RMDMNREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_RMDMNREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[898],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSDomainControllerInfo( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_DCINFOREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_DCINFOREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[964],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSAddEntry( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_ADDENTRYREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_ADDENTRYREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1030],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSExecuteKCC( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_KCC_EXECUTE *pmsgIn)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1096],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSGetReplInfo( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_GETREPLINFO_REQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_GETREPLINFO_REPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1150],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSAddSidHistory( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_ADDSIDREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_ADDSIDREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1216],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSGetMemberships2( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_GETMEMBERSHIPS2_REQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_GETMEMBERSHIPS2_REPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1282],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSReplicaVerifyObjects( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwVersion,
    /* [switch_is][ref][in] */ DRS_MSG_REPVERIFYOBJ *pmsgVerify)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1348],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSGetObjectExistence( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_EXISTREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_EXISTREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1402],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSQuerySitesByCost( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_QUERYSITESREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_QUERYSITESREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1468],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSInitDemotion( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_INIT_DEMOTIONREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_INIT_DEMOTIONREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1534],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSReplicaDemotion( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_REPLICA_DEMOTIONREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_REPLICA_DEMOTIONREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1600],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSFinishDemotion( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_FINISH_DEMOTIONREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_FINISH_DEMOTIONREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1666],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSAddCloneDC( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_ADDCLONEDCREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_ADDCLONEDCREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1732],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSWriteNgcKey( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_WRITENGCKEYREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_WRITENGCKEYREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1798],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DRSReadNgcKey( 
    /* [ref][in] */ DRS_HANDLE hDrs,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DRS_MSG_READNGCKEYREQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DRS_MSG_READNGCKEYREPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&drsuapi_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1864],
                  ( unsigned char * )&hDrs);
    return ( ULONG  )_RetVal.Simple;
    
}


/* Standard interface: dsaop, ver. 1.0,
   GUID={0x7c44d7d4,0x31d5,0x424c,{0xbd,0x5e,0x2b,0x3e,0x1f,0x32,0x3d,0x22}} */



static const RPC_CLIENT_INTERFACE dsaop___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x7c44d7d4,0x31d5,0x424c,{0xbd,0x5e,0x2b,0x3e,0x1f,0x32,0x3d,0x22}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0x00000000
    };
RPC_IF_HANDLE dsaop_v1_0_c_ifspec = (RPC_IF_HANDLE)& dsaop___RpcClientInterface;

extern const MIDL_STUB_DESC dsaop_StubDesc;

static RPC_BINDING_HANDLE dsaop__MIDL_AutoBindHandle;


ULONG IDL_DSAPrepareScript( 
    /* [in] */ handle_t hRpc,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DSA_MSG_PREPARE_SCRIPT_REQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DSA_MSG_PREPARE_SCRIPT_REPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&dsaop_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1930],
                  ( unsigned char * )&hRpc);
    return ( ULONG  )_RetVal.Simple;
    
}


ULONG IDL_DSAExecuteScript( 
    /* [in] */ handle_t hRpc,
    /* [in] */ DWORD dwInVersion,
    /* [switch_is][ref][in] */ DSA_MSG_EXECUTE_SCRIPT_REQ *pmsgIn,
    /* [ref][out] */ DWORD *pdwOutVersion,
    /* [switch_is][ref][out] */ DSA_MSG_EXECUTE_SCRIPT_REPLY *pmsgOut)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&dsaop_StubDesc,
                  (PFORMAT_STRING) &ms2Ddrsr__MIDL_ProcFormatString.Format[1988],
                  ( unsigned char * )&hRpc);
    return ( ULONG  )_RetVal.Simple;
    
}


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif
#if !(TARGET_IS_NT60_OR_LATER)
#error You need Windows Vista or later to run this stub because it uses these features:
#error   forced complex structure or array, new range semantics.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const ms2Ddrsr_MIDL_PROC_FORMAT_STRING ms2Ddrsr__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure IDL_DRSBind */

			0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 10 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 12 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 14 */	NdrFcShort( 0x44 ),	/* 68 */
/* 16 */	NdrFcShort( 0x40 ),	/* 64 */
/* 18 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 20 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 22 */	NdrFcShort( 0x1 ),	/* 1 */
/* 24 */	NdrFcShort( 0x1 ),	/* 1 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter rpc_handle */

/* 28 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
/* 30 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 32 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Parameter puuidClientDsa */

/* 34 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 36 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 38 */	NdrFcShort( 0x18 ),	/* Type Offset=24 */

	/* Parameter pextClient */

/* 40 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 42 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 44 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */

	/* Parameter ppextServer */

/* 46 */	NdrFcShort( 0x110 ),	/* Flags:  out, simple ref, */
/* 48 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 50 */	NdrFcShort( 0x42 ),	/* Type Offset=66 */

	/* Parameter phDrs */

/* 52 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 54 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 56 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSUnbind */


	/* Return value */

/* 58 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 60 */	NdrFcLong( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x1 ),	/* 1 */
/* 66 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 68 */	0x30,		/* FC_BIND_CONTEXT */
			0xe0,		/* Ctxt flags:  via ptr, in, out, */
/* 70 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 72 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 74 */	NdrFcShort( 0x38 ),	/* 56 */
/* 76 */	NdrFcShort( 0x40 ),	/* 64 */
/* 78 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 80 */	0x8,		/* 8 */
			0x41,		/* Ext Flags:  new corr desc, has range on conformance */
/* 82 */	NdrFcShort( 0x0 ),	/* 0 */
/* 84 */	NdrFcShort( 0x0 ),	/* 0 */
/* 86 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phDrs */

/* 88 */	NdrFcShort( 0x118 ),	/* Flags:  in, out, simple ref, */
/* 90 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 92 */	NdrFcShort( 0x4a ),	/* Type Offset=74 */

	/* Return value */

/* 94 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 96 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 98 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSReplicaSync */

/* 100 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 102 */	NdrFcLong( 0x0 ),	/* 0 */
/* 106 */	NdrFcShort( 0x2 ),	/* 2 */
/* 108 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 110 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 112 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 114 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 116 */	NdrFcShort( 0x2c ),	/* 44 */
/* 118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 120 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 122 */	0x8,		/* 8 */
			0x45,		/* Ext Flags:  new corr desc, srv corr check, has range on conformance */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x1 ),	/* 1 */
/* 128 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 130 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 132 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 134 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwVersion */

/* 136 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 138 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 140 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgSync */

/* 142 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 144 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 146 */	NdrFcShort( 0x56 ),	/* Type Offset=86 */

	/* Return value */

/* 148 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 150 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 152 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSGetNCChanges */

/* 154 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 156 */	NdrFcLong( 0x0 ),	/* 0 */
/* 160 */	NdrFcShort( 0x3 ),	/* 3 */
/* 162 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 164 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 166 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 168 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 170 */	NdrFcShort( 0x2c ),	/* 44 */
/* 172 */	NdrFcShort( 0x24 ),	/* 36 */
/* 174 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 176 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 178 */	NdrFcShort( 0x1 ),	/* 1 */
/* 180 */	NdrFcShort( 0x1 ),	/* 1 */
/* 182 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 184 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 186 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 188 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 190 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 192 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 196 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 198 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 200 */	NdrFcShort( 0xd6 ),	/* Type Offset=214 */

	/* Parameter pdwOutVersion */

/* 202 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 204 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 206 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 208 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 210 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 212 */	NdrFcShort( 0x306 ),	/* Type Offset=774 */

	/* Return value */

/* 214 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 216 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 218 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSUpdateRefs */

/* 220 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 222 */	NdrFcLong( 0x0 ),	/* 0 */
/* 226 */	NdrFcShort( 0x4 ),	/* 4 */
/* 228 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 230 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 232 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 234 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 236 */	NdrFcShort( 0x2c ),	/* 44 */
/* 238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 240 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 242 */	0x8,		/* 8 */
			0x45,		/* Ext Flags:  new corr desc, srv corr check, has range on conformance */
/* 244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 246 */	NdrFcShort( 0x1 ),	/* 1 */
/* 248 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 250 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 252 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 254 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwVersion */

/* 256 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 258 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 260 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgUpdRefs */

/* 262 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 264 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 266 */	NdrFcShort( 0x626 ),	/* Type Offset=1574 */

	/* Return value */

/* 268 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 270 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 272 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSReplicaAdd */

/* 274 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 276 */	NdrFcLong( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x5 ),	/* 5 */
/* 282 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 284 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 286 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 288 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 290 */	NdrFcShort( 0x2c ),	/* 44 */
/* 292 */	NdrFcShort( 0x8 ),	/* 8 */
/* 294 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 296 */	0x8,		/* 8 */
			0x45,		/* Ext Flags:  new corr desc, srv corr check, has range on conformance */
/* 298 */	NdrFcShort( 0x0 ),	/* 0 */
/* 300 */	NdrFcShort( 0x1 ),	/* 1 */
/* 302 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 304 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 306 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 308 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwVersion */

/* 310 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 312 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 314 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgAdd */

/* 316 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 318 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 320 */	NdrFcShort( 0x66e ),	/* Type Offset=1646 */

	/* Return value */

/* 322 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 324 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSReplicaDel */

/* 328 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 330 */	NdrFcLong( 0x0 ),	/* 0 */
/* 334 */	NdrFcShort( 0x6 ),	/* 6 */
/* 336 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 338 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 340 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 342 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 344 */	NdrFcShort( 0x2c ),	/* 44 */
/* 346 */	NdrFcShort( 0x8 ),	/* 8 */
/* 348 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 350 */	0x8,		/* 8 */
			0x45,		/* Ext Flags:  new corr desc, srv corr check, has range on conformance */
/* 352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 354 */	NdrFcShort( 0x1 ),	/* 1 */
/* 356 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 358 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 360 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 362 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwVersion */

/* 364 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 366 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 368 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgDel */

/* 370 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 372 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 374 */	NdrFcShort( 0x706 ),	/* Type Offset=1798 */

	/* Return value */

/* 376 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 378 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 380 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSReplicaModify */

/* 382 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 384 */	NdrFcLong( 0x0 ),	/* 0 */
/* 388 */	NdrFcShort( 0x7 ),	/* 7 */
/* 390 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 392 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 394 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 396 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 398 */	NdrFcShort( 0x2c ),	/* 44 */
/* 400 */	NdrFcShort( 0x8 ),	/* 8 */
/* 402 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 404 */	0x8,		/* 8 */
			0x45,		/* Ext Flags:  new corr desc, srv corr check, has range on conformance */
/* 406 */	NdrFcShort( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0x1 ),	/* 1 */
/* 410 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 412 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 414 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 416 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwVersion */

/* 418 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 420 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 422 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgMod */

/* 424 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 426 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 428 */	NdrFcShort( 0x74a ),	/* Type Offset=1866 */

	/* Return value */

/* 430 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 432 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 434 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSVerifyNames */

/* 436 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 438 */	NdrFcLong( 0x0 ),	/* 0 */
/* 442 */	NdrFcShort( 0x8 ),	/* 8 */
/* 444 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 446 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 448 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 450 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 452 */	NdrFcShort( 0x2c ),	/* 44 */
/* 454 */	NdrFcShort( 0x24 ),	/* 36 */
/* 456 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 458 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 460 */	NdrFcShort( 0x1 ),	/* 1 */
/* 462 */	NdrFcShort( 0x1 ),	/* 1 */
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 466 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 468 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 470 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 472 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 474 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 476 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 478 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 480 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 482 */	NdrFcShort( 0x798 ),	/* Type Offset=1944 */

	/* Parameter pdwOutVersion */

/* 484 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 486 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 488 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 490 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 492 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 494 */	NdrFcShort( 0x840 ),	/* Type Offset=2112 */

	/* Return value */

/* 496 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 498 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 500 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSGetMemberships */

/* 502 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 504 */	NdrFcLong( 0x0 ),	/* 0 */
/* 508 */	NdrFcShort( 0x9 ),	/* 9 */
/* 510 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 512 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 514 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 516 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 518 */	NdrFcShort( 0x2c ),	/* 44 */
/* 520 */	NdrFcShort( 0x24 ),	/* 36 */
/* 522 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 524 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 526 */	NdrFcShort( 0x1 ),	/* 1 */
/* 528 */	NdrFcShort( 0x1 ),	/* 1 */
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 532 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 534 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 536 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 538 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 540 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 542 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 544 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 546 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 548 */	NdrFcShort( 0x932 ),	/* Type Offset=2354 */

	/* Parameter pdwOutVersion */

/* 550 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 552 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 554 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 556 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 558 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 560 */	NdrFcShort( 0x9a4 ),	/* Type Offset=2468 */

	/* Return value */

/* 562 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 564 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 566 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSInterDomainMove */

/* 568 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 570 */	NdrFcLong( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0xa ),	/* 10 */
/* 576 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 578 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 580 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 582 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 584 */	NdrFcShort( 0x2c ),	/* 44 */
/* 586 */	NdrFcShort( 0x24 ),	/* 36 */
/* 588 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 590 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 592 */	NdrFcShort( 0x1 ),	/* 1 */
/* 594 */	NdrFcShort( 0x1 ),	/* 1 */
/* 596 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 598 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 600 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 602 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 604 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 606 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 608 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 610 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 612 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 614 */	NdrFcShort( 0xa5e ),	/* Type Offset=2654 */

	/* Parameter pdwOutVersion */

/* 616 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 618 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 620 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 622 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 624 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 626 */	NdrFcShort( 0xb78 ),	/* Type Offset=2936 */

	/* Return value */

/* 628 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 630 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 632 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSGetNT4ChangeLog */

/* 634 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 636 */	NdrFcLong( 0x0 ),	/* 0 */
/* 640 */	NdrFcShort( 0xb ),	/* 11 */
/* 642 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 644 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 646 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 648 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 650 */	NdrFcShort( 0x2c ),	/* 44 */
/* 652 */	NdrFcShort( 0x24 ),	/* 36 */
/* 654 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 656 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 658 */	NdrFcShort( 0x1 ),	/* 1 */
/* 660 */	NdrFcShort( 0x1 ),	/* 1 */
/* 662 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 664 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 666 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 668 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 670 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 672 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 674 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 676 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 678 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 680 */	NdrFcShort( 0xc10 ),	/* Type Offset=3088 */

	/* Parameter pdwOutVersion */

/* 682 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 684 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 686 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 688 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 690 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 692 */	NdrFcShort( 0xc60 ),	/* Type Offset=3168 */

	/* Return value */

/* 694 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 696 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 698 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSCrackNames */

/* 700 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 702 */	NdrFcLong( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0xc ),	/* 12 */
/* 708 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 710 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 712 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 714 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 716 */	NdrFcShort( 0x2c ),	/* 44 */
/* 718 */	NdrFcShort( 0x24 ),	/* 36 */
/* 720 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 722 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 724 */	NdrFcShort( 0x1 ),	/* 1 */
/* 726 */	NdrFcShort( 0x1 ),	/* 1 */
/* 728 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 730 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 732 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 734 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 736 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 738 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 740 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 742 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 744 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 746 */	NdrFcShort( 0xcea ),	/* Type Offset=3306 */

	/* Parameter pdwOutVersion */

/* 748 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 750 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 752 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 754 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 756 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 758 */	NdrFcShort( 0xd52 ),	/* Type Offset=3410 */

	/* Return value */

/* 760 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 762 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 764 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSWriteSPN */

/* 766 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 768 */	NdrFcLong( 0x0 ),	/* 0 */
/* 772 */	NdrFcShort( 0xd ),	/* 13 */
/* 774 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 776 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 778 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 780 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 782 */	NdrFcShort( 0x2c ),	/* 44 */
/* 784 */	NdrFcShort( 0x24 ),	/* 36 */
/* 786 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 788 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 790 */	NdrFcShort( 0x1 ),	/* 1 */
/* 792 */	NdrFcShort( 0x1 ),	/* 1 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 796 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 798 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 800 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 802 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 804 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 806 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 808 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 810 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 812 */	NdrFcShort( 0xdf2 ),	/* Type Offset=3570 */

	/* Parameter pdwOutVersion */

/* 814 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 816 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 818 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 820 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 822 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 824 */	NdrFcShort( 0xe62 ),	/* Type Offset=3682 */

	/* Return value */

/* 826 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 828 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 830 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSRemoveDsServer */

/* 832 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 834 */	NdrFcLong( 0x0 ),	/* 0 */
/* 838 */	NdrFcShort( 0xe ),	/* 14 */
/* 840 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 842 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 844 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 846 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 848 */	NdrFcShort( 0x2c ),	/* 44 */
/* 850 */	NdrFcShort( 0x24 ),	/* 36 */
/* 852 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 854 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 856 */	NdrFcShort( 0x1 ),	/* 1 */
/* 858 */	NdrFcShort( 0x1 ),	/* 1 */
/* 860 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 862 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 864 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 866 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 868 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 870 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 872 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 874 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 876 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 878 */	NdrFcShort( 0xe8c ),	/* Type Offset=3724 */

	/* Parameter pdwOutVersion */

/* 880 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 882 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 884 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 886 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 888 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 890 */	NdrFcShort( 0xed0 ),	/* Type Offset=3792 */

	/* Return value */

/* 892 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 894 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 896 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSRemoveDsDomain */

/* 898 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 900 */	NdrFcLong( 0x0 ),	/* 0 */
/* 904 */	NdrFcShort( 0xf ),	/* 15 */
/* 906 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 908 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 910 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 912 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 914 */	NdrFcShort( 0x2c ),	/* 44 */
/* 916 */	NdrFcShort( 0x24 ),	/* 36 */
/* 918 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 920 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 922 */	NdrFcShort( 0x1 ),	/* 1 */
/* 924 */	NdrFcShort( 0x1 ),	/* 1 */
/* 926 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 928 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 930 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 932 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 934 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 936 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 938 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 940 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 942 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 944 */	NdrFcShort( 0xef4 ),	/* Type Offset=3828 */

	/* Parameter pdwOutVersion */

/* 946 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 948 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 950 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 952 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 954 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 956 */	NdrFcShort( 0xf2c ),	/* Type Offset=3884 */

	/* Return value */

/* 958 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 960 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 962 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSDomainControllerInfo */

/* 964 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 966 */	NdrFcLong( 0x0 ),	/* 0 */
/* 970 */	NdrFcShort( 0x10 ),	/* 16 */
/* 972 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 974 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 976 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 978 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 980 */	NdrFcShort( 0x2c ),	/* 44 */
/* 982 */	NdrFcShort( 0x24 ),	/* 36 */
/* 984 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 986 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 988 */	NdrFcShort( 0x1 ),	/* 1 */
/* 990 */	NdrFcShort( 0x1 ),	/* 1 */
/* 992 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 994 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 996 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 998 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1000 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1002 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1004 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1006 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1008 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1010 */	NdrFcShort( 0xf50 ),	/* Type Offset=3920 */

	/* Parameter pdwOutVersion */

/* 1012 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1014 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1016 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1018 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1020 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1022 */	NdrFcShort( 0xf88 ),	/* Type Offset=3976 */

	/* Return value */

/* 1024 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1026 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1028 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSAddEntry */

/* 1030 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1032 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1036 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1038 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1040 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1042 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1044 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1046 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1048 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1050 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1052 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1054 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1056 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1058 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1060 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1062 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1064 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1066 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1068 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1070 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1072 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1074 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1076 */	NdrFcShort( 0x126c ),	/* Type Offset=4716 */

	/* Parameter pdwOutVersion */

/* 1078 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1080 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1082 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1084 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 1086 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1088 */	NdrFcShort( 0x134a ),	/* Type Offset=4938 */

	/* Return value */

/* 1090 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1092 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1094 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSExecuteKCC */

/* 1096 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1098 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1102 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1104 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1106 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1108 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1110 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1112 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1114 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1116 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1118 */	0x8,		/* 8 */
			0x45,		/* Ext Flags:  new corr desc, srv corr check, has range on conformance */
/* 1120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1122 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1124 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1126 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1128 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1130 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1132 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1136 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1138 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1140 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1142 */	NdrFcShort( 0x1586 ),	/* Type Offset=5510 */

	/* Return value */

/* 1144 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1146 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1148 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSGetReplInfo */

/* 1150 */	0x0,		/* 0 */
			0x49,		/* Old Flags:  full ptr, */
/* 1152 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1156 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1158 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1160 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1162 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1164 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1166 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1168 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1170 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1172 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1174 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1176 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1178 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1180 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1182 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1184 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1186 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1188 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1192 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1194 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1196 */	NdrFcShort( 0x15b2 ),	/* Type Offset=5554 */

	/* Parameter pdwOutVersion */

/* 1198 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1200 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1204 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1206 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1208 */	NdrFcShort( 0x1624 ),	/* Type Offset=5668 */

	/* Return value */

/* 1210 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1212 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSAddSidHistory */

/* 1216 */	0x0,		/* 0 */
			0x49,		/* Old Flags:  full ptr, */
/* 1218 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1222 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1224 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1226 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1228 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1230 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1232 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1234 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1236 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1238 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1240 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1242 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1244 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1246 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1248 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1250 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1252 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1254 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1258 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1260 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1262 */	NdrFcShort( 0x1ad6 ),	/* Type Offset=6870 */

	/* Parameter pdwOutVersion */

/* 1264 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1266 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1268 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1270 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1272 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1274 */	NdrFcShort( 0x1ba0 ),	/* Type Offset=7072 */

	/* Return value */

/* 1276 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1278 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1280 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSGetMemberships2 */

/* 1282 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1284 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1288 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1290 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1292 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1294 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1296 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1298 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1300 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1302 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1304 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1306 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1308 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1310 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1312 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1314 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1316 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1318 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1320 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1322 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1324 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1326 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1328 */	NdrFcShort( 0x1bc4 ),	/* Type Offset=7108 */

	/* Parameter pdwOutVersion */

/* 1330 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1332 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1334 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1336 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1338 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1340 */	NdrFcShort( 0x1c26 ),	/* Type Offset=7206 */

	/* Return value */

/* 1342 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1344 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSReplicaVerifyObjects */

/* 1348 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1350 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1354 */	NdrFcShort( 0x16 ),	/* 22 */
/* 1356 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1358 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1360 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1362 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1364 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1366 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1368 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1370 */	0x8,		/* 8 */
			0x45,		/* Ext Flags:  new corr desc, srv corr check, has range on conformance */
/* 1372 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1374 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1376 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1378 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1380 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1382 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwVersion */

/* 1384 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1386 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgVerify */

/* 1390 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1392 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1394 */	NdrFcShort( 0x1c9a ),	/* Type Offset=7322 */

	/* Return value */

/* 1396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1398 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSGetObjectExistence */

/* 1402 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1408 */	NdrFcShort( 0x17 ),	/* 23 */
/* 1410 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1412 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1414 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1416 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1418 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1420 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1422 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1424 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1426 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1428 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1430 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1432 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1434 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1436 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1438 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1440 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1442 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1444 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1446 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1448 */	NdrFcShort( 0x1cd6 ),	/* Type Offset=7382 */

	/* Parameter pdwOutVersion */

/* 1450 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1452 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1454 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1456 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1458 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1460 */	NdrFcShort( 0x1d28 ),	/* Type Offset=7464 */

	/* Return value */

/* 1462 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1464 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1466 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSQuerySitesByCost */

/* 1468 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1470 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1474 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1476 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1478 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1480 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1482 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1484 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1486 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1488 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1490 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1492 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1494 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1496 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1498 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1500 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1502 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1504 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1506 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1508 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1510 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1512 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1514 */	NdrFcShort( 0x1d7c ),	/* Type Offset=7548 */

	/* Parameter pdwOutVersion */

/* 1516 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1518 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1520 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1522 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1524 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1526 */	NdrFcShort( 0x1dea ),	/* Type Offset=7658 */

	/* Return value */

/* 1528 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1530 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1532 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSInitDemotion */

/* 1534 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1536 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1540 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1542 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1544 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1546 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1548 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1550 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1552 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1554 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1556 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1558 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1560 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1562 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1564 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1566 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1568 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1570 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1572 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1576 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1578 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1580 */	NdrFcShort( 0x1e3e ),	/* Type Offset=7742 */

	/* Parameter pdwOutVersion */

/* 1582 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1584 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1586 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1588 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1590 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1592 */	NdrFcShort( 0x1e62 ),	/* Type Offset=7778 */

	/* Return value */

/* 1594 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1596 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSReplicaDemotion */

/* 1600 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1602 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1606 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1608 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1610 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1612 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1614 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1616 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1618 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1620 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1622 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1624 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1626 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1628 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1630 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1632 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1634 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1636 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1638 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1640 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1642 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1644 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1646 */	NdrFcShort( 0x1e86 ),	/* Type Offset=7814 */

	/* Parameter pdwOutVersion */

/* 1648 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1650 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1652 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1654 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1656 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1658 */	NdrFcShort( 0x1ec2 ),	/* Type Offset=7874 */

	/* Return value */

/* 1660 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1662 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1664 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSFinishDemotion */

/* 1666 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1668 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1672 */	NdrFcShort( 0x1b ),	/* 27 */
/* 1674 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1676 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1678 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1680 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1682 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1684 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1686 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1688 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1690 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1692 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1694 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1696 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1698 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1700 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1702 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1704 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1706 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1708 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1710 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1712 */	NdrFcShort( 0x1ee6 ),	/* Type Offset=7910 */

	/* Parameter pdwOutVersion */

/* 1714 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1716 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1720 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1722 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1724 */	NdrFcShort( 0x1f22 ),	/* Type Offset=7970 */

	/* Return value */

/* 1726 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1728 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1730 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSAddCloneDC */

/* 1732 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1734 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1738 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1740 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1742 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1744 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1746 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1748 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1750 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1752 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1754 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1756 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1758 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1760 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1762 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1764 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1766 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1768 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1770 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1772 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1774 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1776 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1778 */	NdrFcShort( 0x1f4e ),	/* Type Offset=8014 */

	/* Parameter pdwOutVersion */

/* 1780 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1782 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1784 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1786 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1788 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1790 */	NdrFcShort( 0x1f90 ),	/* Type Offset=8080 */

	/* Return value */

/* 1792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1794 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSWriteNgcKey */

/* 1798 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1804 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1806 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1808 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1810 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1812 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1814 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1816 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1818 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1820 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1822 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1824 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1826 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1828 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1830 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1832 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1834 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1836 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1838 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1840 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1842 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1844 */	NdrFcShort( 0x1ff4 ),	/* Type Offset=8180 */

	/* Parameter pdwOutVersion */

/* 1846 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1848 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1850 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1852 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1854 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1856 */	NdrFcShort( 0x204e ),	/* Type Offset=8270 */

	/* Return value */

/* 1858 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1860 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1862 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DRSReadNgcKey */

/* 1864 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1866 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1870 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1872 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1874 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1876 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1878 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1880 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1882 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1884 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1886 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1888 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1890 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1892 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hDrs */

/* 1894 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1896 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1898 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Parameter dwInVersion */

/* 1900 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1902 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgIn */

/* 1906 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1908 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1910 */	NdrFcShort( 0x2072 ),	/* Type Offset=8306 */

	/* Parameter pdwOutVersion */

/* 1912 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1914 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1916 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pmsgOut */

/* 1918 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1920 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1922 */	NdrFcShort( 0x2096 ),	/* Type Offset=8342 */

	/* Return value */

/* 1924 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1926 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1928 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DSAPrepareScript */

/* 1930 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1932 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1938 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1940 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 1942 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1944 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1946 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1948 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1950 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 1952 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1954 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1956 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hRpc */

/* 1958 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1960 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1962 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter dwInVersion */

/* 1964 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1966 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1968 */	NdrFcShort( 0x20d0 ),	/* Type Offset=8400 */

	/* Parameter pmsgIn */

/* 1970 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1972 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1974 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pdwOutVersion */

/* 1976 */	NdrFcShort( 0x8113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=32 */
/* 1978 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1980 */	NdrFcShort( 0x20f4 ),	/* Type Offset=8436 */

	/* Parameter pmsgOut */

/* 1982 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1984 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1986 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IDL_DSAExecuteScript */


	/* Return value */

/* 1988 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1990 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1994 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1996 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1998 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 2000 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2002 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2004 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2006 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 2008 */	0x8,		/* 8 */
			0x47,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, has range on conformance */
/* 2010 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2012 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2014 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hRpc */

/* 2016 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2018 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2020 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter dwInVersion */

/* 2022 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2024 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2026 */	NdrFcShort( 0x2192 ),	/* Type Offset=8594 */

	/* Parameter pmsgIn */

/* 2028 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2030 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pdwOutVersion */

/* 2034 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2036 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2038 */	NdrFcShort( 0x21e2 ),	/* Type Offset=8674 */

	/* Parameter pmsgOut */

/* 2040 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2042 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2044 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const ms2Ddrsr_MIDL_TYPE_FORMAT_STRING ms2Ddrsr__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0x8 ),	/* Offset= 8 (12) */
/*  6 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/*  8 */	NdrFcShort( 0x8 ),	/* 8 */
/* 10 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 12 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 14 */	NdrFcShort( 0x10 ),	/* 16 */
/* 16 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 18 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 20 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (6) */
			0x5b,		/* FC_END */
/* 24 */	
			0x12, 0x0,	/* FC_UP */
/* 26 */	NdrFcShort( 0x18 ),	/* Offset= 24 (50) */
/* 28 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 30 */	NdrFcShort( 0x1 ),	/* 1 */
/* 32 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 34 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 36 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 38 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 40 */	NdrFcLong( 0x1 ),	/* 1 */
/* 44 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 48 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 50 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 52 */	NdrFcShort( 0x4 ),	/* 4 */
/* 54 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (28) */
/* 56 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 58 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 60 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (24) */
/* 62 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 64 */	NdrFcShort( 0x2 ),	/* Offset= 2 (66) */
/* 66 */	0x30,		/* FC_BIND_CONTEXT */
			0xa0,		/* Ctxt flags:  via ptr, out, */
/* 68 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 70 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 72 */	NdrFcShort( 0x2 ),	/* Offset= 2 (74) */
/* 74 */	0x30,		/* FC_BIND_CONTEXT */
			0xe1,		/* Ctxt flags:  via ptr, in, out, can't be null */
/* 76 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 78 */	0x30,		/* FC_BIND_CONTEXT */
			0x41,		/* Ctxt flags:  in, can't be null */
/* 80 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 82 */	
			0x11, 0x0,	/* FC_RP */
/* 84 */	NdrFcShort( 0x2 ),	/* Offset= 2 (86) */
/* 86 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 88 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 90 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 92 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 94 */	0x0 , 
			0x0,		/* 0 */
/* 96 */	NdrFcLong( 0x0 ),	/* 0 */
/* 100 */	NdrFcLong( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x2 ),	/* Offset= 2 (106) */
/* 106 */	NdrFcShort( 0x1c ),	/* 28 */
/* 108 */	NdrFcShort( 0x1 ),	/* 1 */
/* 110 */	NdrFcLong( 0x1 ),	/* 1 */
/* 114 */	NdrFcShort( 0x3c ),	/* Offset= 60 (174) */
/* 116 */	NdrFcShort( 0xffff ),	/* Offset= -1 (115) */
/* 118 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 120 */	NdrFcShort( 0x1c ),	/* 28 */
/* 122 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 124 */	
			0x15,		/* FC_STRUCT */
			0x0,		/* 0 */
/* 126 */	NdrFcShort( 0x1c ),	/* 28 */
/* 128 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 130 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (118) */
/* 132 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 134 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 136 */	NdrFcShort( 0x2 ),	/* 2 */
/* 138 */	0x9,		/* Corr desc: FC_ULONG */
			0x57,		/* FC_ADD_1 */
/* 140 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 142 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 144 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 146 */	NdrFcLong( 0x0 ),	/* 0 */
/* 150 */	NdrFcLong( 0xa00001 ),	/* 10485761 */
/* 154 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 156 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 158 */	NdrFcShort( 0x38 ),	/* 56 */
/* 160 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (134) */
/* 162 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 164 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 166 */	NdrFcShort( 0xff66 ),	/* Offset= -154 (12) */
/* 168 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 170 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (124) */
/* 172 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 174 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 176 */	NdrFcShort( 0x1c ),	/* 28 */
/* 178 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 180 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 182 */	NdrFcShort( 0x0 ),	/* 0 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 186 */	0x11, 0x0,	/* FC_RP */
/* 188 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (156) */
/* 190 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 192 */	NdrFcShort( 0x14 ),	/* 20 */
/* 194 */	NdrFcShort( 0x14 ),	/* 20 */
/* 196 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 198 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 200 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 202 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 204 */	NdrFcShort( 0xff40 ),	/* Offset= -192 (12) */
/* 206 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 208 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 210 */	
			0x11, 0x0,	/* FC_RP */
/* 212 */	NdrFcShort( 0x2 ),	/* Offset= 2 (214) */
/* 214 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 216 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 218 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 220 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 222 */	0x0 , 
			0x0,		/* 0 */
/* 224 */	NdrFcLong( 0x0 ),	/* 0 */
/* 228 */	NdrFcLong( 0x0 ),	/* 0 */
/* 232 */	NdrFcShort( 0x2 ),	/* Offset= 2 (234) */
/* 234 */	NdrFcShort( 0x88 ),	/* 136 */
/* 236 */	NdrFcShort( 0x5 ),	/* 5 */
/* 238 */	NdrFcLong( 0x4 ),	/* 4 */
/* 242 */	NdrFcShort( 0x12c ),	/* Offset= 300 (542) */
/* 244 */	NdrFcLong( 0x5 ),	/* 5 */
/* 248 */	NdrFcShort( 0x144 ),	/* Offset= 324 (572) */
/* 250 */	NdrFcLong( 0x7 ),	/* 7 */
/* 254 */	NdrFcShort( 0x168 ),	/* Offset= 360 (614) */
/* 256 */	NdrFcLong( 0x8 ),	/* 8 */
/* 260 */	NdrFcShort( 0x188 ),	/* Offset= 392 (652) */
/* 262 */	NdrFcLong( 0xa ),	/* 10 */
/* 266 */	NdrFcShort( 0x1ba ),	/* Offset= 442 (708) */
/* 268 */	NdrFcShort( 0xffff ),	/* Offset= -1 (267) */
/* 270 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 272 */	NdrFcShort( 0x18 ),	/* 24 */
/* 274 */	0xb,		/* FC_HYPER */
			0xb,		/* FC_HYPER */
/* 276 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 278 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 280 */	NdrFcShort( 0x1 ),	/* 1 */
/* 282 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 284 */	NdrFcShort( 0x4 ),	/* 4 */
/* 286 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 288 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 290 */	NdrFcLong( 0x0 ),	/* 0 */
/* 294 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 298 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 300 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 302 */	NdrFcShort( 0xc ),	/* 12 */
/* 304 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 306 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 308 */	NdrFcShort( 0x8 ),	/* 8 */
/* 310 */	NdrFcShort( 0x8 ),	/* 8 */
/* 312 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 314 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (278) */
/* 316 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 318 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 320 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 322 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 324 */	NdrFcShort( 0xc ),	/* 12 */
/* 326 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 330 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 332 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 338 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 342 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 344 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 346 */	NdrFcShort( 0xc ),	/* 12 */
/* 348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 350 */	NdrFcShort( 0x1 ),	/* 1 */
/* 352 */	NdrFcShort( 0x8 ),	/* 8 */
/* 354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 356 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 358 */	NdrFcShort( 0xffb0 ),	/* Offset= -80 (278) */
/* 360 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 362 */	0x0,		/* 0 */
			NdrFcShort( 0xffc1 ),	/* Offset= -63 (300) */
			0x5b,		/* FC_END */
/* 366 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 368 */	NdrFcShort( 0x8 ),	/* 8 */
/* 370 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 372 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 374 */	NdrFcShort( 0x4 ),	/* 4 */
/* 376 */	NdrFcShort( 0x4 ),	/* 4 */
/* 378 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 380 */	NdrFcShort( 0xffc6 ),	/* Offset= -58 (322) */
/* 382 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 384 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 386 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 388 */	NdrFcShort( 0x18 ),	/* 24 */
/* 390 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 392 */	NdrFcShort( 0xfe84 ),	/* Offset= -380 (12) */
/* 394 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 396 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 398 */	NdrFcShort( 0x18 ),	/* 24 */
/* 400 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 402 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 404 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 406 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 408 */	NdrFcLong( 0x0 ),	/* 0 */
/* 412 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 416 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 418 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (386) */
/* 420 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 422 */	
			0x17,		/* FC_CSTRUCT */
			0x7,		/* 7 */
/* 424 */	NdrFcShort( 0x10 ),	/* 16 */
/* 426 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (396) */
/* 428 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 430 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 432 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 434 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 436 */	NdrFcShort( 0x4 ),	/* 4 */
/* 438 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 440 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 442 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 444 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 446 */	NdrFcLong( 0x1 ),	/* 1 */
/* 450 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 454 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 456 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 458 */	NdrFcShort( 0xc ),	/* 12 */
/* 460 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (434) */
/* 462 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 464 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 466 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 468 */	NdrFcShort( 0x60 ),	/* 96 */
/* 470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 472 */	NdrFcShort( 0x1c ),	/* Offset= 28 (500) */
/* 474 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 476 */	NdrFcShort( 0xfe30 ),	/* Offset= -464 (12) */
/* 478 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 480 */	NdrFcShort( 0xfe2c ),	/* Offset= -468 (12) */
/* 482 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 484 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 486 */	NdrFcShort( 0xff28 ),	/* Offset= -216 (270) */
/* 488 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 490 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 492 */	NdrFcShort( 0xff82 ),	/* Offset= -126 (366) */
/* 494 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 496 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 498 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 500 */	
			0x11, 0x0,	/* FC_RP */
/* 502 */	NdrFcShort( 0xfea6 ),	/* Offset= -346 (156) */
/* 504 */	
			0x12, 0x0,	/* FC_UP */
/* 506 */	NdrFcShort( 0xffac ),	/* Offset= -84 (422) */
/* 508 */	
			0x12, 0x0,	/* FC_UP */
/* 510 */	NdrFcShort( 0xffca ),	/* Offset= -54 (456) */
/* 512 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 514 */	NdrFcShort( 0x1 ),	/* 1 */
/* 516 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 518 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 520 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 522 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 524 */	NdrFcLong( 0x1 ),	/* 1 */
/* 528 */	NdrFcLong( 0x100 ),	/* 256 */
/* 532 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 534 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 536 */	NdrFcShort( 0x4 ),	/* 4 */
/* 538 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (512) */
/* 540 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 542 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 544 */	NdrFcShort( 0x78 ),	/* 120 */
/* 546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 548 */	NdrFcShort( 0xe ),	/* Offset= 14 (562) */
/* 550 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 552 */	NdrFcShort( 0xfde4 ),	/* Offset= -540 (12) */
/* 554 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 556 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 558 */	NdrFcShort( 0xffa4 ),	/* Offset= -92 (466) */
/* 560 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 562 */	
			0x11, 0x0,	/* FC_RP */
/* 564 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (534) */
/* 566 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 568 */	NdrFcShort( 0x8 ),	/* 8 */
/* 570 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 572 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 574 */	NdrFcShort( 0x60 ),	/* 96 */
/* 576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 578 */	NdrFcShort( 0x1c ),	/* Offset= 28 (606) */
/* 580 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 582 */	NdrFcShort( 0xfdc6 ),	/* Offset= -570 (12) */
/* 584 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 586 */	NdrFcShort( 0xfdc2 ),	/* Offset= -574 (12) */
/* 588 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 590 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 592 */	NdrFcShort( 0xfebe ),	/* Offset= -322 (270) */
/* 594 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 596 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 598 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 600 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 602 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (566) */
/* 604 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 606 */	
			0x11, 0x0,	/* FC_RP */
/* 608 */	NdrFcShort( 0xfe3c ),	/* Offset= -452 (156) */
/* 610 */	
			0x12, 0x0,	/* FC_UP */
/* 612 */	NdrFcShort( 0xff42 ),	/* Offset= -190 (422) */
/* 614 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 616 */	NdrFcShort( 0x88 ),	/* 136 */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x14 ),	/* Offset= 20 (640) */
/* 622 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 624 */	NdrFcShort( 0xfd9c ),	/* Offset= -612 (12) */
/* 626 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 628 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 630 */	NdrFcShort( 0xff5c ),	/* Offset= -164 (466) */
/* 632 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 634 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 636 */	NdrFcShort( 0xfef2 ),	/* Offset= -270 (366) */
/* 638 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 640 */	
			0x11, 0x0,	/* FC_RP */
/* 642 */	NdrFcShort( 0xff94 ),	/* Offset= -108 (534) */
/* 644 */	
			0x12, 0x0,	/* FC_UP */
/* 646 */	NdrFcShort( 0xff42 ),	/* Offset= -190 (456) */
/* 648 */	
			0x12, 0x0,	/* FC_UP */
/* 650 */	NdrFcShort( 0xff3e ),	/* Offset= -194 (456) */
/* 652 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 654 */	NdrFcShort( 0x70 ),	/* 112 */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	NdrFcShort( 0x22 ),	/* Offset= 34 (692) */
/* 660 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 662 */	NdrFcShort( 0xfd76 ),	/* Offset= -650 (12) */
/* 664 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 666 */	NdrFcShort( 0xfd72 ),	/* Offset= -654 (12) */
/* 668 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 670 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 672 */	NdrFcShort( 0xfe6e ),	/* Offset= -402 (270) */
/* 674 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 676 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 678 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 680 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 682 */	NdrFcShort( 0xff8c ),	/* Offset= -116 (566) */
/* 684 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 686 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 688 */	NdrFcShort( 0xfebe ),	/* Offset= -322 (366) */
/* 690 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 692 */	
			0x11, 0x0,	/* FC_RP */
/* 694 */	NdrFcShort( 0xfde6 ),	/* Offset= -538 (156) */
/* 696 */	
			0x12, 0x0,	/* FC_UP */
/* 698 */	NdrFcShort( 0xfeec ),	/* Offset= -276 (422) */
/* 700 */	
			0x12, 0x0,	/* FC_UP */
/* 702 */	NdrFcShort( 0xff0a ),	/* Offset= -246 (456) */
/* 704 */	
			0x12, 0x0,	/* FC_UP */
/* 706 */	NdrFcShort( 0xff06 ),	/* Offset= -250 (456) */
/* 708 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 710 */	NdrFcShort( 0x78 ),	/* 120 */
/* 712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 714 */	NdrFcShort( 0x24 ),	/* Offset= 36 (750) */
/* 716 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 718 */	NdrFcShort( 0xfd3e ),	/* Offset= -706 (12) */
/* 720 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 722 */	NdrFcShort( 0xfd3a ),	/* Offset= -710 (12) */
/* 724 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 726 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 728 */	NdrFcShort( 0xfe36 ),	/* Offset= -458 (270) */
/* 730 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 732 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 734 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 736 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 738 */	NdrFcShort( 0xff54 ),	/* Offset= -172 (566) */
/* 740 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 742 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 744 */	NdrFcShort( 0xfe86 ),	/* Offset= -378 (366) */
/* 746 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 748 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 750 */	
			0x11, 0x0,	/* FC_RP */
/* 752 */	NdrFcShort( 0xfdac ),	/* Offset= -596 (156) */
/* 754 */	
			0x12, 0x0,	/* FC_UP */
/* 756 */	NdrFcShort( 0xfeb2 ),	/* Offset= -334 (422) */
/* 758 */	
			0x12, 0x0,	/* FC_UP */
/* 760 */	NdrFcShort( 0xfed0 ),	/* Offset= -304 (456) */
/* 762 */	
			0x12, 0x0,	/* FC_UP */
/* 764 */	NdrFcShort( 0xfecc ),	/* Offset= -308 (456) */
/* 766 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 768 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 770 */	
			0x11, 0x0,	/* FC_RP */
/* 772 */	NdrFcShort( 0x2 ),	/* Offset= 2 (774) */
/* 774 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 776 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 778 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 780 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 782 */	0x0 , 
			0x0,		/* 0 */
/* 784 */	NdrFcLong( 0x0 ),	/* 0 */
/* 788 */	NdrFcLong( 0x0 ),	/* 0 */
/* 792 */	NdrFcShort( 0x2 ),	/* Offset= 2 (794) */
/* 794 */	NdrFcShort( 0x90 ),	/* 144 */
/* 796 */	NdrFcShort( 0x5 ),	/* 5 */
/* 798 */	NdrFcLong( 0x1 ),	/* 1 */
/* 802 */	NdrFcShort( 0x13e ),	/* Offset= 318 (1120) */
/* 804 */	NdrFcLong( 0x2 ),	/* 2 */
/* 808 */	NdrFcShort( 0x180 ),	/* Offset= 384 (1192) */
/* 810 */	NdrFcLong( 0x6 ),	/* 6 */
/* 814 */	NdrFcShort( 0x214 ),	/* Offset= 532 (1346) */
/* 816 */	NdrFcLong( 0x7 ),	/* 7 */
/* 820 */	NdrFcShort( 0x24a ),	/* Offset= 586 (1406) */
/* 822 */	NdrFcLong( 0x9 ),	/* 9 */
/* 826 */	NdrFcShort( 0x2ac ),	/* Offset= 684 (1510) */
/* 828 */	NdrFcShort( 0xffff ),	/* Offset= -1 (827) */
/* 830 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 832 */	NdrFcShort( 0x1 ),	/* 1 */
/* 834 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 838 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 840 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 842 */	NdrFcLong( 0x0 ),	/* 0 */
/* 846 */	NdrFcLong( 0x1900000 ),	/* 26214400 */
/* 850 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 852 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 854 */	NdrFcShort( 0x8 ),	/* 8 */
/* 856 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 858 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 860 */	NdrFcShort( 0x4 ),	/* 4 */
/* 862 */	NdrFcShort( 0x4 ),	/* 4 */
/* 864 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 866 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (830) */
/* 868 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 870 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 872 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 874 */	NdrFcShort( 0x8 ),	/* 8 */
/* 876 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 878 */	NdrFcShort( 0x4 ),	/* 4 */
/* 880 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 882 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 884 */	NdrFcLong( 0x0 ),	/* 0 */
/* 888 */	NdrFcLong( 0xa00000 ),	/* 10485760 */
/* 892 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 894 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 896 */	NdrFcShort( 0x8 ),	/* 8 */
/* 898 */	NdrFcShort( 0x0 ),	/* 0 */
/* 900 */	NdrFcShort( 0x1 ),	/* 1 */
/* 902 */	NdrFcShort( 0x4 ),	/* 4 */
/* 904 */	NdrFcShort( 0x4 ),	/* 4 */
/* 906 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 908 */	NdrFcShort( 0xffb2 ),	/* Offset= -78 (830) */
/* 910 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 912 */	0x0,		/* 0 */
			NdrFcShort( 0xffc3 ),	/* Offset= -61 (852) */
			0x5b,		/* FC_END */
/* 916 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 918 */	NdrFcShort( 0xc ),	/* 12 */
/* 920 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 922 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 926 */	NdrFcShort( 0x8 ),	/* 8 */
/* 928 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 930 */	NdrFcShort( 0xffc6 ),	/* Offset= -58 (872) */
/* 932 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 934 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 936 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 938 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 940 */	NdrFcShort( 0xc ),	/* 12 */
/* 942 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 944 */	NdrFcShort( 0xc ),	/* 12 */
/* 946 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 948 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 950 */	NdrFcLong( 0x0 ),	/* 0 */
/* 954 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 958 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 960 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 962 */	NdrFcShort( 0xc ),	/* 12 */
/* 964 */	NdrFcShort( 0x0 ),	/* 0 */
/* 966 */	NdrFcShort( 0x1 ),	/* 1 */
/* 968 */	NdrFcShort( 0x8 ),	/* 8 */
/* 970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 972 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 974 */	NdrFcShort( 0xff9a ),	/* Offset= -102 (872) */
/* 976 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 978 */	0x0,		/* 0 */
			NdrFcShort( 0xffc1 ),	/* Offset= -63 (916) */
			0x5b,		/* FC_END */
/* 982 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 984 */	NdrFcShort( 0x28 ),	/* 40 */
/* 986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 988 */	NdrFcShort( 0x0 ),	/* Offset= 0 (988) */
/* 990 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 992 */	0xb,		/* FC_HYPER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 994 */	0x0,		/* 0 */
			NdrFcShort( 0xfc29 ),	/* Offset= -983 (12) */
			0xb,		/* FC_HYPER */
/* 998 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1000 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x7,		/* 7 */
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 1006 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 1008 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 1010 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 1012 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1016 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 1020 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1024 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1026 */	0x0 , 
			0x0,		/* 0 */
/* 1028 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1032 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1036 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1038 */	NdrFcShort( 0xffc8 ),	/* Offset= -56 (982) */
/* 1040 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1042 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1044 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1046 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (1000) */
/* 1048 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1048) */
/* 1050 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1052 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1054 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1056 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1058 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1060 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1062 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1064 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1066 */	0x12, 0x0,	/* FC_UP */
/* 1068 */	NdrFcShort( 0xfff2 ),	/* Offset= -14 (1054) */
/* 1070 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1072 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1074 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1076 */	0x12, 0x0,	/* FC_UP */
/* 1078 */	NdrFcShort( 0xfc66 ),	/* Offset= -922 (156) */
/* 1080 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1082 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1084 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1086 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1088 */	NdrFcShort( 0xff6a ),	/* Offset= -150 (938) */
/* 1090 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1092 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1094 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1096 */	0x12, 0x0,	/* FC_UP */
/* 1098 */	NdrFcShort( 0xfbc2 ),	/* Offset= -1086 (12) */
/* 1100 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1102 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1104 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1106 */	0x12, 0x0,	/* FC_UP */
/* 1108 */	NdrFcShort( 0xffbe ),	/* Offset= -66 (1042) */
/* 1110 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1112 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1114 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1116 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1118 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1120 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1122 */	NdrFcShort( 0x78 ),	/* 120 */
/* 1124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1126 */	NdrFcShort( 0x20 ),	/* Offset= 32 (1158) */
/* 1128 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1130 */	NdrFcShort( 0xfba2 ),	/* Offset= -1118 (12) */
/* 1132 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1134 */	NdrFcShort( 0xfb9e ),	/* Offset= -1122 (12) */
/* 1136 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 1138 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1140 */	NdrFcShort( 0xfc9a ),	/* Offset= -870 (270) */
/* 1142 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1144 */	NdrFcShort( 0xfc96 ),	/* Offset= -874 (270) */
/* 1146 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1148 */	0x0,		/* 0 */
			NdrFcShort( 0xfcf1 ),	/* Offset= -783 (366) */
			0x8,		/* FC_LONG */
/* 1152 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1154 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 1156 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1158 */	
			0x12, 0x0,	/* FC_UP */
/* 1160 */	NdrFcShort( 0xfc14 ),	/* Offset= -1004 (156) */
/* 1162 */	
			0x12, 0x0,	/* FC_UP */
/* 1164 */	NdrFcShort( 0xfd1a ),	/* Offset= -742 (422) */
/* 1166 */	
			0x12, 0x0,	/* FC_UP */
/* 1168 */	NdrFcShort( 0xff8e ),	/* Offset= -114 (1054) */
/* 1170 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1172 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1174 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1176 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1178 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1180 */	0x0 , 
			0x0,		/* 0 */
/* 1182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1190 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 1192 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1194 */	NdrFcShort( 0xc ),	/* 12 */
/* 1196 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1198 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1200 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1202 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1204 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1206 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1170) */
/* 1208 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1210 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1212 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1214 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1216 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1218 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1220 */	NdrFcShort( 0xfb48 ),	/* Offset= -1208 (12) */
/* 1222 */	0xb,		/* FC_HYPER */
			0xb,		/* FC_HYPER */
/* 1224 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1226 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 1228 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1230 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 1232 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 1234 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 1236 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 1238 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1242 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 1246 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1248 */	NdrFcShort( 0xffde ),	/* Offset= -34 (1214) */
/* 1250 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1252 */	
			0x17,		/* FC_CSTRUCT */
			0x7,		/* 7 */
/* 1254 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1256 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (1226) */
/* 1258 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1260 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1262 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1264 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1266 */	NdrFcShort( 0x30 ),	/* 48 */
/* 1268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1270 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1270) */
/* 1272 */	0xb,		/* FC_HYPER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1274 */	0x0,		/* 0 */
			NdrFcShort( 0xfedb ),	/* Offset= -293 (982) */
			0x5b,		/* FC_END */
/* 1278 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1280 */	NdrFcShort( 0x48 ),	/* 72 */
/* 1282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1284 */	NdrFcShort( 0x10 ),	/* Offset= 16 (1300) */
/* 1286 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 1288 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1290 */	NdrFcShort( 0xfe4a ),	/* Offset= -438 (852) */
/* 1292 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1294 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1296 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (1264) */
/* 1298 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1300 */	
			0x12, 0x0,	/* FC_UP */
/* 1302 */	NdrFcShort( 0xfb86 ),	/* Offset= -1146 (156) */
/* 1304 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x7,		/* 7 */
/* 1306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1308 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1310 */	NdrFcShort( 0x80 ),	/* 128 */
/* 1312 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 1314 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 1316 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1320 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 1324 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1328 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1330 */	0x0 , 
			0x0,		/* 0 */
/* 1332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1336 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1340 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1342 */	NdrFcShort( 0xffc0 ),	/* Offset= -64 (1278) */
/* 1344 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1346 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1348 */	NdrFcShort( 0x90 ),	/* 144 */
/* 1350 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1352 */	NdrFcShort( 0x26 ),	/* Offset= 38 (1390) */
/* 1354 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1356 */	NdrFcShort( 0xfac0 ),	/* Offset= -1344 (12) */
/* 1358 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1360 */	NdrFcShort( 0xfabc ),	/* Offset= -1348 (12) */
/* 1362 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 1364 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1366 */	NdrFcShort( 0xfbb8 ),	/* Offset= -1096 (270) */
/* 1368 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1370 */	NdrFcShort( 0xfbb4 ),	/* Offset= -1100 (270) */
/* 1372 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1374 */	0x0,		/* 0 */
			NdrFcShort( 0xfc0f ),	/* Offset= -1009 (366) */
			0x8,		/* FC_LONG */
/* 1378 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1380 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 1382 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1384 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 1386 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1388 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1390 */	
			0x12, 0x0,	/* FC_UP */
/* 1392 */	NdrFcShort( 0xfb2c ),	/* Offset= -1236 (156) */
/* 1394 */	
			0x12, 0x0,	/* FC_UP */
/* 1396 */	NdrFcShort( 0xff70 ),	/* Offset= -144 (1252) */
/* 1398 */	
			0x12, 0x0,	/* FC_UP */
/* 1400 */	NdrFcShort( 0xfea6 ),	/* Offset= -346 (1054) */
/* 1402 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1404 */	NdrFcShort( 0xff9c ),	/* Offset= -100 (1304) */
/* 1406 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1408 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1410 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1412 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1412) */
/* 1414 */	0x8,		/* FC_LONG */
			0xd,		/* FC_ENUM16 */
/* 1416 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1418 */	NdrFcShort( 0xff1e ),	/* Offset= -226 (1192) */
/* 1420 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1422 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1424 */	NdrFcShort( 0x48 ),	/* 72 */
/* 1426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1428 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1428) */
/* 1430 */	0xb,		/* FC_HYPER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1432 */	0x0,		/* 0 */
			NdrFcShort( 0xfe3d ),	/* Offset= -451 (982) */
			0x8,		/* FC_LONG */
/* 1436 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1438 */	0x40,		/* FC_STRUCTPAD4 */
			0xb,		/* FC_HYPER */
/* 1440 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1442 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1444 */	NdrFcShort( 0x60 ),	/* 96 */
/* 1446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1448 */	NdrFcShort( 0x10 ),	/* Offset= 16 (1464) */
/* 1450 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 1452 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1454 */	NdrFcShort( 0xfda6 ),	/* Offset= -602 (852) */
/* 1456 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1458 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1460 */	NdrFcShort( 0xffda ),	/* Offset= -38 (1422) */
/* 1462 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1464 */	
			0x12, 0x0,	/* FC_UP */
/* 1466 */	NdrFcShort( 0xfae2 ),	/* Offset= -1310 (156) */
/* 1468 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x7,		/* 7 */
/* 1470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1472 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1474 */	NdrFcShort( 0x80 ),	/* 128 */
/* 1476 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 1478 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 1480 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1484 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 1488 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1492 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1494 */	0x0 , 
			0x0,		/* 0 */
/* 1496 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1500 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1504 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1506 */	NdrFcShort( 0xffc0 ),	/* Offset= -64 (1442) */
/* 1508 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1510 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1512 */	NdrFcShort( 0x90 ),	/* 144 */
/* 1514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1516 */	NdrFcShort( 0x26 ),	/* Offset= 38 (1554) */
/* 1518 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1520 */	NdrFcShort( 0xfa1c ),	/* Offset= -1508 (12) */
/* 1522 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1524 */	NdrFcShort( 0xfa18 ),	/* Offset= -1512 (12) */
/* 1526 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 1528 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1530 */	NdrFcShort( 0xfb14 ),	/* Offset= -1260 (270) */
/* 1532 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1534 */	NdrFcShort( 0xfb10 ),	/* Offset= -1264 (270) */
/* 1536 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1538 */	0x0,		/* 0 */
			NdrFcShort( 0xfb6b ),	/* Offset= -1173 (366) */
			0x8,		/* FC_LONG */
/* 1542 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1544 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 1546 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1548 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 1550 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1552 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1554 */	
			0x12, 0x0,	/* FC_UP */
/* 1556 */	NdrFcShort( 0xfa88 ),	/* Offset= -1400 (156) */
/* 1558 */	
			0x12, 0x0,	/* FC_UP */
/* 1560 */	NdrFcShort( 0xfecc ),	/* Offset= -308 (1252) */
/* 1562 */	
			0x12, 0x0,	/* FC_UP */
/* 1564 */	NdrFcShort( 0xfe02 ),	/* Offset= -510 (1054) */
/* 1566 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1568 */	NdrFcShort( 0xff9c ),	/* Offset= -100 (1468) */
/* 1570 */	
			0x11, 0x0,	/* FC_RP */
/* 1572 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1574) */
/* 1574 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 1576 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 1578 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1580 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1582 */	0x0 , 
			0x0,		/* 0 */
/* 1584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1588 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1592 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1594) */
/* 1594 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1596 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1598 */	NdrFcLong( 0x1 ),	/* 1 */
/* 1602 */	NdrFcShort( 0x4 ),	/* Offset= 4 (1606) */
/* 1604 */	NdrFcShort( 0xffff ),	/* Offset= -1 (1603) */
/* 1606 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1608 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1610 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1612 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1618 */	0x11, 0x0,	/* FC_RP */
/* 1620 */	NdrFcShort( 0xfa48 ),	/* Offset= -1464 (156) */
/* 1622 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1624 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1626 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1628 */	0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 1630 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1632 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1634 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1636 */	0x0,		/* 0 */
			NdrFcShort( 0xf9a7 ),	/* Offset= -1625 (12) */
			0x8,		/* FC_LONG */
/* 1640 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1642 */	
			0x11, 0x0,	/* FC_RP */
/* 1644 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1646) */
/* 1646 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 1648 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 1650 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1652 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1654 */	0x0 , 
			0x0,		/* 0 */
/* 1656 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1660 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1664 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1666) */
/* 1666 */	NdrFcShort( 0x68 ),	/* 104 */
/* 1668 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1670 */	NdrFcLong( 0x1 ),	/* 1 */
/* 1674 */	NdrFcShort( 0x1a ),	/* Offset= 26 (1700) */
/* 1676 */	NdrFcLong( 0x2 ),	/* 2 */
/* 1680 */	NdrFcShort( 0x38 ),	/* Offset= 56 (1736) */
/* 1682 */	NdrFcShort( 0xffff ),	/* Offset= -1 (1681) */
/* 1684 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 1686 */	NdrFcShort( 0x54 ),	/* 84 */
/* 1688 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 1690 */	
			0x15,		/* FC_STRUCT */
			0x0,		/* 0 */
/* 1692 */	NdrFcShort( 0x54 ),	/* 84 */
/* 1694 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1696 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1684) */
/* 1698 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1700 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1702 */	NdrFcShort( 0x60 ),	/* 96 */
/* 1704 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1706 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1712 */	0x11, 0x0,	/* FC_RP */
/* 1714 */	NdrFcShort( 0xf9ea ),	/* Offset= -1558 (156) */
/* 1716 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1718 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1720 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1722 */	0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 1724 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1726 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1728 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1730 */	0x0,		/* 0 */
			NdrFcShort( 0xffd7 ),	/* Offset= -41 (1690) */
			0x8,		/* FC_LONG */
/* 1734 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1736 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1738 */	NdrFcShort( 0x68 ),	/* 104 */
/* 1740 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1742 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1748 */	0x11, 0x0,	/* FC_RP */
/* 1750 */	NdrFcShort( 0xf9c6 ),	/* Offset= -1594 (156) */
/* 1752 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1754 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1756 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1758 */	0x12, 0x0,	/* FC_UP */
/* 1760 */	NdrFcShort( 0xf9bc ),	/* Offset= -1604 (156) */
/* 1762 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1764 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1766 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1768 */	0x12, 0x0,	/* FC_UP */
/* 1770 */	NdrFcShort( 0xf9b2 ),	/* Offset= -1614 (156) */
/* 1772 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1774 */	NdrFcShort( 0xc ),	/* 12 */
/* 1776 */	NdrFcShort( 0xc ),	/* 12 */
/* 1778 */	0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 1780 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1782 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1784 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1786 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1788 */	0x0,		/* 0 */
			NdrFcShort( 0xff9d ),	/* Offset= -99 (1690) */
			0x8,		/* FC_LONG */
/* 1792 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1794 */	
			0x11, 0x0,	/* FC_RP */
/* 1796 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1798) */
/* 1798 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 1800 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 1802 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1804 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1806 */	0x0 , 
			0x0,		/* 0 */
/* 1808 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1812 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1816 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1818) */
/* 1818 */	NdrFcShort( 0xc ),	/* 12 */
/* 1820 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1822 */	NdrFcLong( 0x1 ),	/* 1 */
/* 1826 */	NdrFcShort( 0x4 ),	/* Offset= 4 (1830) */
/* 1828 */	NdrFcShort( 0xffff ),	/* Offset= -1 (1827) */
/* 1830 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1832 */	NdrFcShort( 0xc ),	/* 12 */
/* 1834 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1836 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1842 */	0x11, 0x0,	/* FC_RP */
/* 1844 */	NdrFcShort( 0xf968 ),	/* Offset= -1688 (156) */
/* 1846 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1848 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1850 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1852 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1854 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1856 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1858 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1860 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1862 */	
			0x11, 0x0,	/* FC_RP */
/* 1864 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1866) */
/* 1866 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 1868 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 1870 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1872 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1874 */	0x0 , 
			0x0,		/* 0 */
/* 1876 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1880 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1884 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1886) */
/* 1886 */	NdrFcShort( 0x78 ),	/* 120 */
/* 1888 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1890 */	NdrFcLong( 0x1 ),	/* 1 */
/* 1894 */	NdrFcShort( 0x4 ),	/* Offset= 4 (1898) */
/* 1896 */	NdrFcShort( 0xffff ),	/* Offset= -1 (1895) */
/* 1898 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1900 */	NdrFcShort( 0x78 ),	/* 120 */
/* 1902 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1904 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1906 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1910 */	0x11, 0x0,	/* FC_RP */
/* 1912 */	NdrFcShort( 0xf924 ),	/* Offset= -1756 (156) */
/* 1914 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1916 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1918 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1920 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1922 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1924 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1926 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1928 */	NdrFcShort( 0xf884 ),	/* Offset= -1916 (12) */
/* 1930 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1932 */	0x0,		/* 0 */
			NdrFcShort( 0xff0d ),	/* Offset= -243 (1690) */
			0x8,		/* FC_LONG */
/* 1936 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1938 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1940 */	
			0x11, 0x0,	/* FC_RP */
/* 1942 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1944) */
/* 1944 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 1946 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 1948 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1950 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1952 */	0x0 , 
			0x0,		/* 0 */
/* 1954 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1958 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1962 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1964) */
/* 1964 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1966 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1968 */	NdrFcLong( 0x1 ),	/* 1 */
/* 1972 */	NdrFcShort( 0x5a ),	/* Offset= 90 (2062) */
/* 1974 */	NdrFcShort( 0xffff ),	/* Offset= -1 (1973) */
/* 1976 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1978 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1980 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1982 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1984 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 1986 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 1988 */	NdrFcLong( 0x1 ),	/* 1 */
/* 1992 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 1996 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1998 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 2000 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2004 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2010 */	0x12, 0x0,	/* FC_UP */
/* 2012 */	NdrFcShort( 0xf8c0 ),	/* Offset= -1856 (156) */
/* 2014 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2016 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2018 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2020 */	NdrFcShort( 0xc ),	/* 12 */
/* 2022 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2024 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2026 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2028 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2030 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2034 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 2038 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2040 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 2042 */	NdrFcShort( 0xc ),	/* 12 */
/* 2044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2046 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2048 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2050 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2052 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2054 */	NdrFcShort( 0xf910 ),	/* Offset= -1776 (278) */
/* 2056 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2058 */	0x0,		/* 0 */
			NdrFcShort( 0xf921 ),	/* Offset= -1759 (300) */
			0x5b,		/* FC_END */
/* 2062 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2064 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2066 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2068 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2070 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2072 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2074 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2076 */	NdrFcShort( 0xff9c ),	/* Offset= -100 (1976) */
/* 2078 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2080 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2082 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2084 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2086 */	NdrFcShort( 0xfb84 ),	/* Offset= -1148 (938) */
/* 2088 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2090 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2092 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2094 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2096 */	NdrFcShort( 0xffb2 ),	/* Offset= -78 (2018) */
/* 2098 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2100 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2102 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2104 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2106 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2108 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 2110 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2112) */
/* 2112 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 2114 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 2116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2118 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 2120 */	0x0 , 
			0x0,		/* 0 */
/* 2122 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2126 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2130 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2132) */
/* 2132 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2134 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2136 */	NdrFcLong( 0x1 ),	/* 1 */
/* 2140 */	NdrFcShort( 0xb0 ),	/* Offset= 176 (2316) */
/* 2142 */	NdrFcShort( 0xffff ),	/* Offset= -1 (2141) */
/* 2144 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2146 */	NdrFcShort( 0xc ),	/* 12 */
/* 2148 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2150 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2152 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2154 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2156 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2160 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 2164 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2166 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 2168 */	NdrFcShort( 0xc ),	/* 12 */
/* 2170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2172 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2174 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2176 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2178 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2180 */	NdrFcShort( 0xfae4 ),	/* Offset= -1308 (872) */
/* 2182 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2184 */	0x0,		/* 0 */
			NdrFcShort( 0xfb0b ),	/* Offset= -1269 (916) */
			0x5b,		/* FC_END */
/* 2188 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2190 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2192 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2194 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2200 */	0x12, 0x0,	/* FC_UP */
/* 2202 */	NdrFcShort( 0xf802 ),	/* Offset= -2046 (156) */
/* 2204 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2206 */	NdrFcShort( 0xc ),	/* 12 */
/* 2208 */	NdrFcShort( 0xc ),	/* 12 */
/* 2210 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2212 */	NdrFcShort( 0xffbc ),	/* Offset= -68 (2144) */
/* 2214 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2216 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2218 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2220 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2222 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2224 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2226 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2228 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2230 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2232 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2236 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 2240 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2242 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 2244 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2248 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2254 */	0x12, 0x0,	/* FC_UP */
/* 2256 */	NdrFcShort( 0xf7cc ),	/* Offset= -2100 (156) */
/* 2258 */	NdrFcShort( 0xc ),	/* 12 */
/* 2260 */	NdrFcShort( 0xc ),	/* 12 */
/* 2262 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2264 */	NdrFcShort( 0xff88 ),	/* Offset= -120 (2144) */
/* 2266 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2268 */	0x0,		/* 0 */
			NdrFcShort( 0xffaf ),	/* Offset= -81 (2188) */
			0x5b,		/* FC_END */
/* 2272 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2274 */	NdrFcShort( 0xc ),	/* 12 */
/* 2276 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2278 */	NdrFcShort( 0xc ),	/* 12 */
/* 2280 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2282 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2284 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2288 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 2292 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2294 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 2296 */	NdrFcShort( 0xc ),	/* 12 */
/* 2298 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2300 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2302 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2306 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2308 */	NdrFcShort( 0xf812 ),	/* Offset= -2030 (278) */
/* 2310 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2312 */	0x0,		/* 0 */
			NdrFcShort( 0xf823 ),	/* Offset= -2013 (300) */
			0x5b,		/* FC_END */
/* 2316 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2318 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2320 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2322 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2324 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2326 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2328 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2330 */	NdrFcShort( 0xff92 ),	/* Offset= -110 (2220) */
/* 2332 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2334 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2336 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2338 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2340 */	NdrFcShort( 0xffbc ),	/* Offset= -68 (2272) */
/* 2342 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2344 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2346 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2348 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2350 */	
			0x11, 0x0,	/* FC_RP */
/* 2352 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2354) */
/* 2354 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 2356 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 2358 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2360 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 2362 */	0x0 , 
			0x0,		/* 0 */
/* 2364 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2368 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2372 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2374) */
/* 2374 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2376 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2378 */	NdrFcLong( 0x1 ),	/* 1 */
/* 2382 */	NdrFcShort( 0x38 ),	/* Offset= 56 (2438) */
/* 2384 */	NdrFcShort( 0xffff ),	/* Offset= -1 (2383) */
/* 2386 */	0xb7,		/* FC_RANGE */
			0xd,		/* 13 */
/* 2388 */	NdrFcLong( 0x1 ),	/* 1 */
/* 2392 */	NdrFcLong( 0x7 ),	/* 7 */
/* 2396 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2398 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2400 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2404 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2406 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2408 */	NdrFcLong( 0x1 ),	/* 1 */
/* 2412 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 2416 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2418 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 2420 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2424 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2430 */	0x12, 0x0,	/* FC_UP */
/* 2432 */	NdrFcShort( 0xf71c ),	/* Offset= -2276 (156) */
/* 2434 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2436 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2438 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 2440 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2444 */	NdrFcShort( 0xc ),	/* Offset= 12 (2456) */
/* 2446 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 2448 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2450 */	0x0,		/* 0 */
			NdrFcShort( 0xffbf ),	/* Offset= -65 (2386) */
			0x36,		/* FC_POINTER */
/* 2454 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2456 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2458 */	NdrFcShort( 0xffc2 ),	/* Offset= -62 (2396) */
/* 2460 */	
			0x12, 0x0,	/* FC_UP */
/* 2462 */	NdrFcShort( 0xf6fe ),	/* Offset= -2306 (156) */
/* 2464 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 2466 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2468) */
/* 2468 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 2470 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 2472 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2474 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 2476 */	0x0 , 
			0x0,		/* 0 */
/* 2478 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2482 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2486 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2488) */
/* 2488 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2490 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2492 */	NdrFcLong( 0x1 ),	/* 1 */
/* 2496 */	NdrFcShort( 0x6e ),	/* Offset= 110 (2606) */
/* 2498 */	NdrFcShort( 0xffff ),	/* Offset= -1 (2497) */
/* 2500 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2502 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2504 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2506 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2508 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2510 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2512 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2516 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 2520 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2522 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 2524 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2528 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2534 */	0x12, 0x0,	/* FC_UP */
/* 2536 */	NdrFcShort( 0xf6b4 ),	/* Offset= -2380 (156) */
/* 2538 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2540 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2542 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2544 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2546 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2548 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2550 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2552 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2554 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2558 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 2562 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2564 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2566 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2568 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2570 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2572 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2574 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2576 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2580 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 2584 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2586 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 2588 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2592 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2598 */	0x12, 0x0,	/* FC_UP */
/* 2600 */	NdrFcShort( 0xf654 ),	/* Offset= -2476 (124) */
/* 2602 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2604 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2606 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2608 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2610 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2612 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2614 */	NdrFcShort( 0xc ),	/* 12 */
/* 2616 */	NdrFcShort( 0xc ),	/* 12 */
/* 2618 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2620 */	NdrFcShort( 0xff88 ),	/* Offset= -120 (2500) */
/* 2622 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2624 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2626 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2628 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2630 */	NdrFcShort( 0xffa8 ),	/* Offset= -88 (2542) */
/* 2632 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2634 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2636 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2638 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2640 */	NdrFcShort( 0xffb4 ),	/* Offset= -76 (2564) */
/* 2642 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2644 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2646 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2648 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2650 */	
			0x11, 0x0,	/* FC_RP */
/* 2652 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2654) */
/* 2654 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 2656 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 2658 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2660 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 2662 */	0x0 , 
			0x0,		/* 0 */
/* 2664 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2668 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2672 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2674) */
/* 2674 */	NdrFcShort( 0x20 ),	/* 32 */
/* 2676 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2678 */	NdrFcLong( 0x1 ),	/* 1 */
/* 2682 */	NdrFcShort( 0xa ),	/* Offset= 10 (2692) */
/* 2684 */	NdrFcLong( 0x2 ),	/* 2 */
/* 2688 */	NdrFcShort( 0xa8 ),	/* Offset= 168 (2856) */
/* 2690 */	NdrFcShort( 0xffff ),	/* Offset= -1 (2689) */
/* 2692 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2694 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2696 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2698 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2704 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2706 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 2708 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2710 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2712 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2714 */	0x12, 0x0,	/* FC_UP */
/* 2716 */	NdrFcShort( 0xfdf0 ),	/* Offset= -528 (2188) */
/* 2718 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2720 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2722 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2724 */	0x12, 0x0,	/* FC_UP */
/* 2726 */	NdrFcShort( 0xf566 ),	/* Offset= -2714 (12) */
/* 2728 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2730 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2732 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2734 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2736 */	NdrFcShort( 0xfe30 ),	/* Offset= -464 (2272) */
/* 2738 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2740 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2742 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2744 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2746 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 2748 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2750 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2754 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2756 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2762 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 2766 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 2768 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2770 */	NdrFcShort( 0xc ),	/* 12 */
/* 2772 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2774 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2776 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2778 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2780 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2782 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (2746) */
/* 2784 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2786 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2788 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2790 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2792 */	NdrFcShort( 0xc ),	/* 12 */
/* 2794 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2796 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2798 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2800 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2802 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2806 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 2810 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2812 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 2814 */	NdrFcShort( 0xc ),	/* 12 */
/* 2816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2818 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2820 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2822 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2824 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2826 */	NdrFcShort( 0xffb0 ),	/* Offset= -80 (2746) */
/* 2828 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2830 */	0x0,		/* 0 */
			NdrFcShort( 0xffc1 ),	/* Offset= -63 (2768) */
			0x5b,		/* FC_END */
/* 2834 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2836 */	NdrFcShort( 0xc ),	/* 12 */
/* 2838 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2840 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2842 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2844 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2846 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2848 */	NdrFcShort( 0xffc6 ),	/* Offset= -58 (2790) */
/* 2850 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2852 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2854 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2856 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2858 */	NdrFcShort( 0x20 ),	/* 32 */
/* 2860 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2862 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2868 */	0x12, 0x0,	/* FC_UP */
/* 2870 */	NdrFcShort( 0xf566 ),	/* Offset= -2714 (156) */
/* 2872 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2874 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2876 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2878 */	0x12, 0x0,	/* FC_UP */
/* 2880 */	NdrFcShort( 0xfd4c ),	/* Offset= -692 (2188) */
/* 2882 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2884 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2886 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2888 */	0x12, 0x0,	/* FC_UP */
/* 2890 */	NdrFcShort( 0xf552 ),	/* Offset= -2734 (156) */
/* 2892 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2894 */	NdrFcShort( 0xc ),	/* 12 */
/* 2896 */	NdrFcShort( 0xc ),	/* 12 */
/* 2898 */	0x12, 0x0,	/* FC_UP */
/* 2900 */	NdrFcShort( 0xf548 ),	/* Offset= -2744 (156) */
/* 2902 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2904 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2906 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2908 */	0x12, 0x0,	/* FC_UP */
/* 2910 */	NdrFcShort( 0xffb4 ),	/* Offset= -76 (2834) */
/* 2912 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2914 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2916 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2918 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 2920 */	NdrFcShort( 0xfc7a ),	/* Offset= -902 (2018) */
/* 2922 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2924 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2926 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2928 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2930 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2932 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 2934 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2936) */
/* 2936 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 2938 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 2940 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2942 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 2944 */	0x0 , 
			0x0,		/* 0 */
/* 2946 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2950 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2954 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2956) */
/* 2956 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2958 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2960 */	NdrFcLong( 0x1 ),	/* 1 */
/* 2964 */	NdrFcShort( 0x3a ),	/* Offset= 58 (3022) */
/* 2966 */	NdrFcLong( 0x2 ),	/* 2 */
/* 2970 */	NdrFcShort( 0x5e ),	/* Offset= 94 (3064) */
/* 2972 */	NdrFcShort( 0xffff ),	/* Offset= -1 (2971) */
/* 2974 */	
			0x12, 0x0,	/* FC_UP */
/* 2976 */	NdrFcShort( 0xfcec ),	/* Offset= -788 (2188) */
/* 2978 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2980 */	NdrFcShort( 0xc ),	/* 12 */
/* 2982 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 2984 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2986 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 2988 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 2990 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2994 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 2998 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3000 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 3002 */	NdrFcShort( 0xc ),	/* 12 */
/* 3004 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3006 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3008 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3010 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3012 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 3014 */	NdrFcShort( 0xf550 ),	/* Offset= -2736 (278) */
/* 3016 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 3018 */	0x0,		/* 0 */
			NdrFcShort( 0xf561 ),	/* Offset= -2719 (300) */
			0x5b,		/* FC_END */
/* 3022 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3024 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3026 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3028 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3030 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3034 */	0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 3036 */	NdrFcShort( 0xffc2 ),	/* Offset= -62 (2974) */
/* 3038 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3040 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3042 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3044 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 3046 */	NdrFcShort( 0xffbc ),	/* Offset= -68 (2978) */
/* 3048 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3050 */	NdrFcShort( 0xc ),	/* 12 */
/* 3052 */	NdrFcShort( 0xc ),	/* 12 */
/* 3054 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3056 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 3058 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3060 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3062 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 3064 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3066 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3068 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3070 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3072 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3074 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3076 */	0x12, 0x0,	/* FC_UP */
/* 3078 */	NdrFcShort( 0xf496 ),	/* Offset= -2922 (156) */
/* 3080 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3082 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 3084 */	
			0x11, 0x0,	/* FC_RP */
/* 3086 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3088) */
/* 3088 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3090 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 3092 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3094 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3096 */	0x0 , 
			0x0,		/* 0 */
/* 3098 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3102 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3106 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3108) */
/* 3108 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3110 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3112 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3116 */	NdrFcShort( 0x1a ),	/* Offset= 26 (3142) */
/* 3118 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3117) */
/* 3120 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 3122 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3124 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 3126 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3128 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 3130 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 3132 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3136 */	NdrFcLong( 0xa00000 ),	/* 10485760 */
/* 3140 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 3142 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3144 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3146 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3148 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3150 */	NdrFcShort( 0xc ),	/* 12 */
/* 3152 */	NdrFcShort( 0xc ),	/* 12 */
/* 3154 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 3156 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (3120) */
/* 3158 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3160 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3162 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 3164 */	
			0x11, 0x0,	/* FC_RP */
/* 3166 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3168) */
/* 3168 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3170 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 3172 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3174 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3176 */	0x0 , 
			0x0,		/* 0 */
/* 3178 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3186 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3188) */
/* 3188 */	NdrFcShort( 0x48 ),	/* 72 */
/* 3190 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3192 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3196 */	NdrFcShort( 0x4e ),	/* Offset= 78 (3274) */
/* 3198 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3197) */
/* 3200 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 3202 */	NdrFcShort( 0x30 ),	/* 48 */
/* 3204 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 3206 */	NdrFcShort( 0xf5b0 ),	/* Offset= -2640 (566) */
/* 3208 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 3210 */	NdrFcShort( 0xf5ac ),	/* Offset= -2644 (566) */
/* 3212 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 3214 */	NdrFcShort( 0xf5a8 ),	/* Offset= -2648 (566) */
/* 3216 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 3218 */	NdrFcShort( 0xf5a4 ),	/* Offset= -2652 (566) */
/* 3220 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 3222 */	NdrFcShort( 0xf5a0 ),	/* Offset= -2656 (566) */
/* 3224 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 3226 */	NdrFcShort( 0xf59c ),	/* Offset= -2660 (566) */
/* 3228 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3230 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 3232 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3234 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 3236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3238 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 3240 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 3242 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3246 */	NdrFcLong( 0xa00000 ),	/* 10485760 */
/* 3250 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 3252 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 3254 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3256 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 3258 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3260 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 3262 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 3264 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3268 */	NdrFcLong( 0xa00000 ),	/* 10485760 */
/* 3272 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 3274 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 3276 */	NdrFcShort( 0x48 ),	/* 72 */
/* 3278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3280 */	NdrFcShort( 0xe ),	/* Offset= 14 (3294) */
/* 3282 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3284 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 3286 */	NdrFcShort( 0xffaa ),	/* Offset= -86 (3200) */
/* 3288 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 3290 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 3292 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3294 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 3296 */	NdrFcShort( 0xffbe ),	/* Offset= -66 (3230) */
/* 3298 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 3300 */	NdrFcShort( 0xffd0 ),	/* Offset= -48 (3252) */
/* 3302 */	
			0x11, 0x0,	/* FC_RP */
/* 3304 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3306) */
/* 3306 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3308 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 3310 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3312 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3314 */	0x0 , 
			0x0,		/* 0 */
/* 3316 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3320 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3324 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3326) */
/* 3326 */	NdrFcShort( 0x1c ),	/* 28 */
/* 3328 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3330 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3334 */	NdrFcShort( 0x2e ),	/* Offset= 46 (3380) */
/* 3336 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3335) */
/* 3338 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 3340 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3342 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 3344 */	NdrFcShort( 0x14 ),	/* 20 */
/* 3346 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 3348 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 3350 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3354 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 3358 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3360 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 3362 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3366 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3372 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3374 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3376 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3378 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3380 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3382 */	NdrFcShort( 0x1c ),	/* 28 */
/* 3384 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3386 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3388 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3390 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3392 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 3394 */	NdrFcShort( 0xffc8 ),	/* Offset= -56 (3338) */
/* 3396 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3398 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3400 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3402 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3404 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3406 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 3408 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3410) */
/* 3410 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3412 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 3414 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3416 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3418 */	0x0 , 
			0x0,		/* 0 */
/* 3420 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3424 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3428 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3430) */
/* 3430 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3432 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3434 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3438 */	NdrFcShort( 0x6c ),	/* Offset= 108 (3546) */
/* 3440 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3439) */
/* 3442 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3444 */	NdrFcShort( 0xc ),	/* 12 */
/* 3446 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3448 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3450 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3452 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3454 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3456 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3458 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3460 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3462 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3464 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3466 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3468 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3470 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3472 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3474 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 3476 */	NdrFcShort( 0xc ),	/* 12 */
/* 3478 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 3480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3482 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3484 */	0x0 , 
			0x0,		/* 0 */
/* 3486 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3490 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3494 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3496 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 3498 */	NdrFcShort( 0xc ),	/* 12 */
/* 3500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3502 */	NdrFcShort( 0x2 ),	/* 2 */
/* 3504 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3506 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3508 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3510 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3512 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3514 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3516 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3518 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3520 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 3522 */	0x0,		/* 0 */
			NdrFcShort( 0xffaf ),	/* Offset= -81 (3442) */
			0x5b,		/* FC_END */
/* 3526 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3528 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3530 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3532 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3534 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3536 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3538 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 3540 */	NdrFcShort( 0xffbe ),	/* Offset= -66 (3474) */
/* 3542 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3544 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 3546 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3548 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3550 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3552 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3558 */	0x12, 0x0,	/* FC_UP */
/* 3560 */	NdrFcShort( 0xffde ),	/* Offset= -34 (3526) */
/* 3562 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3564 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3566 */	
			0x11, 0x0,	/* FC_RP */
/* 3568 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3570) */
/* 3570 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3572 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 3574 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3576 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3578 */	0x0 , 
			0x0,		/* 0 */
/* 3580 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3588 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3590) */
/* 3590 */	NdrFcShort( 0x14 ),	/* 20 */
/* 3592 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3594 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3598 */	NdrFcShort( 0x2e ),	/* Offset= 46 (3644) */
/* 3600 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3599) */
/* 3602 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 3604 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3606 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 3608 */	NdrFcShort( 0xc ),	/* 12 */
/* 3610 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 3612 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 3614 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3618 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 3622 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3624 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 3626 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3630 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3636 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3638 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3640 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3642 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3644 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3646 */	NdrFcShort( 0x14 ),	/* 20 */
/* 3648 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3650 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3652 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3654 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3656 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3658 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3660 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3662 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3664 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3666 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 3668 */	NdrFcShort( 0xffbe ),	/* Offset= -66 (3602) */
/* 3670 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3672 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3674 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3676 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3678 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 3680 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3682) */
/* 3682 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3684 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 3686 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3688 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3690 */	0x0 , 
			0x0,		/* 0 */
/* 3692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3700 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3702) */
/* 3702 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3704 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3706 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3710 */	NdrFcShort( 0x4 ),	/* Offset= 4 (3714) */
/* 3712 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3711) */
/* 3714 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 3716 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3718 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 3720 */	
			0x11, 0x0,	/* FC_RP */
/* 3722 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3724) */
/* 3724 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3726 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 3728 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3730 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3732 */	0x0 , 
			0x0,		/* 0 */
/* 3734 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3738 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3742 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3744) */
/* 3744 */	NdrFcShort( 0xc ),	/* 12 */
/* 3746 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3748 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3752 */	NdrFcShort( 0x4 ),	/* Offset= 4 (3756) */
/* 3754 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3753) */
/* 3756 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3758 */	NdrFcShort( 0xc ),	/* 12 */
/* 3760 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3762 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3768 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3770 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3772 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3774 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3776 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3778 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3780 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3782 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3784 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 3786 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3788 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 3790 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3792) */
/* 3792 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3794 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 3796 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3798 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3800 */	0x0 , 
			0x0,		/* 0 */
/* 3802 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3806 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3810 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3812) */
/* 3812 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3814 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3816 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3820 */	NdrFcShort( 0xff96 ),	/* Offset= -106 (3714) */
/* 3822 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3821) */
/* 3824 */	
			0x11, 0x0,	/* FC_RP */
/* 3826 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3828) */
/* 3828 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3830 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 3832 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3834 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3836 */	0x0 , 
			0x0,		/* 0 */
/* 3838 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3842 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3846 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3848) */
/* 3848 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3850 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3852 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3856 */	NdrFcShort( 0x4 ),	/* Offset= 4 (3860) */
/* 3858 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3857) */
/* 3860 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3862 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3864 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3866 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3870 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3872 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3874 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3876 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3878 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 3880 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 3882 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3884) */
/* 3884 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3886 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 3888 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3890 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3892 */	0x0 , 
			0x0,		/* 0 */
/* 3894 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3898 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3902 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3904) */
/* 3904 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3906 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3908 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3912 */	NdrFcShort( 0xff3a ),	/* Offset= -198 (3714) */
/* 3914 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3913) */
/* 3916 */	
			0x11, 0x0,	/* FC_RP */
/* 3918 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3920) */
/* 3920 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3922 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 3924 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3926 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3928 */	0x0 , 
			0x0,		/* 0 */
/* 3930 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3934 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3938 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3940) */
/* 3940 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3942 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3944 */	NdrFcLong( 0x1 ),	/* 1 */
/* 3948 */	NdrFcShort( 0x4 ),	/* Offset= 4 (3952) */
/* 3950 */	NdrFcShort( 0xffff ),	/* Offset= -1 (3949) */
/* 3952 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 3954 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3956 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 3958 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 3960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3964 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 3966 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 3968 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 3970 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 3972 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 3974 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3976) */
/* 3976 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 3978 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 3980 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3982 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 3984 */	0x0 , 
			0x0,		/* 0 */
/* 3986 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3990 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3994 */	NdrFcShort( 0x2 ),	/* Offset= 2 (3996) */
/* 3996 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3998 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4000 */	NdrFcLong( 0x1 ),	/* 1 */
/* 4004 */	NdrFcShort( 0xa4 ),	/* Offset= 164 (4168) */
/* 4006 */	NdrFcLong( 0x2 ),	/* 2 */
/* 4010 */	NdrFcShort( 0x176 ),	/* Offset= 374 (4384) */
/* 4012 */	NdrFcLong( 0x3 ),	/* 3 */
/* 4016 */	NdrFcShort( 0x24a ),	/* Offset= 586 (4602) */
/* 4018 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 4022 */	NdrFcShort( 0x29e ),	/* Offset= 670 (4692) */
/* 4024 */	NdrFcShort( 0xffff ),	/* Offset= -1 (4023) */
/* 4026 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4028 */	NdrFcShort( 0x1c ),	/* 28 */
/* 4030 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4032 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4038 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4040 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4042 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4044 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4046 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4048 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4050 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4052 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4054 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4056 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4058 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4060 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4062 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4064 */	NdrFcShort( 0xc ),	/* 12 */
/* 4066 */	NdrFcShort( 0xc ),	/* 12 */
/* 4068 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4070 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4072 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4074 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4076 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4078 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4080 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4082 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4084 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4086 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4088 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4090 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 4092 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 4094 */	NdrFcShort( 0x1c ),	/* 28 */
/* 4096 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 4098 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4100 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 4102 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 4104 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4108 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 4112 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4114 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 4116 */	NdrFcShort( 0x1c ),	/* 28 */
/* 4118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4120 */	NdrFcShort( 0x5 ),	/* 5 */
/* 4122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4126 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4128 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4130 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4132 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4134 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4136 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4140 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4142 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4144 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4146 */	NdrFcShort( 0xc ),	/* 12 */
/* 4148 */	NdrFcShort( 0xc ),	/* 12 */
/* 4150 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4152 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4154 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4156 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4158 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4160 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4162 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 4164 */	0x0,		/* 0 */
			NdrFcShort( 0xff75 ),	/* Offset= -139 (4026) */
			0x5b,		/* FC_END */
/* 4168 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4170 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4172 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4174 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4176 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4178 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4180 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 4182 */	NdrFcShort( 0xffa6 ),	/* Offset= -90 (4092) */
/* 4184 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4186 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 4188 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4190 */	NdrFcShort( 0x68 ),	/* 104 */
/* 4192 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4194 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4200 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4202 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4204 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4206 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4208 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4210 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4212 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4214 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4216 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4218 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4220 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4222 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4224 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4226 */	NdrFcShort( 0xc ),	/* 12 */
/* 4228 */	NdrFcShort( 0xc ),	/* 12 */
/* 4230 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4232 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4234 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4236 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4238 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4240 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4242 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4244 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4246 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4248 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4250 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4252 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4254 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4256 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4258 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4260 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4262 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4264 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4266 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4268 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4270 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4272 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4274 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 4276 */	0x0,		/* 0 */
			NdrFcShort( 0xef57 ),	/* Offset= -4265 (12) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 4280 */	0x0,		/* 0 */
			NdrFcShort( 0xef53 ),	/* Offset= -4269 (12) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 4284 */	0x0,		/* 0 */
			NdrFcShort( 0xef4f ),	/* Offset= -4273 (12) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 4288 */	0x0,		/* 0 */
			NdrFcShort( 0xef4b ),	/* Offset= -4277 (12) */
			0x5b,		/* FC_END */
/* 4292 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 4294 */	NdrFcShort( 0x68 ),	/* 104 */
/* 4296 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 4298 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4300 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 4302 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 4304 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4308 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 4312 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4314 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 4316 */	NdrFcShort( 0x68 ),	/* 104 */
/* 4318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4320 */	NdrFcShort( 0x7 ),	/* 7 */
/* 4322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4326 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4328 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4330 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4332 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4334 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4336 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4338 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4342 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4344 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4346 */	NdrFcShort( 0xc ),	/* 12 */
/* 4348 */	NdrFcShort( 0xc ),	/* 12 */
/* 4350 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4352 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4354 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4356 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4358 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4360 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4362 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4364 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4366 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4368 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4370 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4372 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4374 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4376 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4378 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 4380 */	0x0,		/* 0 */
			NdrFcShort( 0xff3f ),	/* Offset= -193 (4188) */
			0x5b,		/* FC_END */
/* 4384 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4386 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4388 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4390 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4392 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4394 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4396 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 4398 */	NdrFcShort( 0xff96 ),	/* Offset= -106 (4292) */
/* 4400 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4402 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 4404 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4406 */	NdrFcShort( 0x6c ),	/* 108 */
/* 4408 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4410 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4414 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4416 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4418 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4420 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4422 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4424 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4426 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4428 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4430 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4434 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4436 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4438 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4440 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4442 */	NdrFcShort( 0xc ),	/* 12 */
/* 4444 */	NdrFcShort( 0xc ),	/* 12 */
/* 4446 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4448 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4450 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4452 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4454 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4456 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4458 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4460 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4462 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4464 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4466 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4468 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4470 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4472 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4474 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4476 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4478 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4480 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4482 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4484 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4486 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4488 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4490 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4492 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 4494 */	NdrFcShort( 0xee7e ),	/* Offset= -4482 (12) */
/* 4496 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 4498 */	NdrFcShort( 0xee7a ),	/* Offset= -4486 (12) */
/* 4500 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 4502 */	NdrFcShort( 0xee76 ),	/* Offset= -4490 (12) */
/* 4504 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 4506 */	NdrFcShort( 0xee72 ),	/* Offset= -4494 (12) */
/* 4508 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 4510 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 4512 */	NdrFcShort( 0x6c ),	/* 108 */
/* 4514 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 4516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4518 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 4520 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 4522 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4526 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 4530 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4532 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 4534 */	NdrFcShort( 0x6c ),	/* 108 */
/* 4536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4538 */	NdrFcShort( 0x7 ),	/* 7 */
/* 4540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4544 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4546 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4548 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4550 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4552 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4554 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4556 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4558 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4560 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4562 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4564 */	NdrFcShort( 0xc ),	/* 12 */
/* 4566 */	NdrFcShort( 0xc ),	/* 12 */
/* 4568 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4570 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4572 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4574 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4576 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4578 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4580 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4582 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4584 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4586 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4588 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4590 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4592 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4594 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4596 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 4598 */	0x0,		/* 0 */
			NdrFcShort( 0xff3d ),	/* Offset= -195 (4404) */
			0x5b,		/* FC_END */
/* 4602 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4604 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4606 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4608 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4610 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4612 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4614 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 4616 */	NdrFcShort( 0xff96 ),	/* Offset= -106 (4510) */
/* 4618 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4620 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 4622 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4624 */	NdrFcShort( 0x1c ),	/* 28 */
/* 4626 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4628 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4630 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4632 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4634 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4636 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4638 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4640 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4642 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4644 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4646 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 4648 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 4650 */	NdrFcShort( 0x1c ),	/* 28 */
/* 4652 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 4654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4656 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 4658 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 4660 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4664 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 4668 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4670 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 4672 */	NdrFcShort( 0x1c ),	/* 28 */
/* 4674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4676 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4678 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4680 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4682 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 4684 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 4686 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 4688 */	0x0,		/* 0 */
			NdrFcShort( 0xffbd ),	/* Offset= -67 (4622) */
			0x5b,		/* FC_END */
/* 4692 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4694 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4696 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4698 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4700 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4702 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4704 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 4706 */	NdrFcShort( 0xffc6 ),	/* Offset= -58 (4648) */
/* 4708 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4710 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 4712 */	
			0x11, 0x0,	/* FC_RP */
/* 4714 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4716) */
/* 4716 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 4718 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 4720 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4722 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 4724 */	0x0 , 
			0x0,		/* 0 */
/* 4726 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4730 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4734 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4736) */
/* 4736 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4738 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4740 */	NdrFcLong( 0x1 ),	/* 1 */
/* 4744 */	NdrFcShort( 0x3c ),	/* Offset= 60 (4804) */
/* 4746 */	NdrFcLong( 0x2 ),	/* 2 */
/* 4750 */	NdrFcShort( 0x56 ),	/* Offset= 86 (4836) */
/* 4752 */	NdrFcLong( 0x3 ),	/* 3 */
/* 4756 */	NdrFcShort( 0x7c ),	/* Offset= 124 (4880) */
/* 4758 */	NdrFcShort( 0xffff ),	/* Offset= -1 (4757) */
/* 4760 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 4762 */	NdrFcShort( 0xc ),	/* 12 */
/* 4764 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 4766 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4768 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 4770 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 4772 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4776 */	NdrFcLong( 0x100000 ),	/* 1048576 */
/* 4780 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4782 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 4784 */	NdrFcShort( 0xc ),	/* 12 */
/* 4786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4788 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4790 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4792 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4794 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 4796 */	NdrFcShort( 0xf0ac ),	/* Offset= -3924 (872) */
/* 4798 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 4800 */	0x0,		/* 0 */
			NdrFcShort( 0xf0d3 ),	/* Offset= -3885 (916) */
			0x5b,		/* FC_END */
/* 4804 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4806 */	NdrFcShort( 0xc ),	/* 12 */
/* 4808 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4810 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4816 */	0x11, 0x0,	/* FC_RP */
/* 4818 */	NdrFcShort( 0xedca ),	/* Offset= -4662 (156) */
/* 4820 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4822 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4826 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 4828 */	NdrFcShort( 0xffbc ),	/* Offset= -68 (4760) */
/* 4830 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4832 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4834 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 4836 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4838 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4840 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4842 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4848 */	0x12, 0x0,	/* FC_UP */
/* 4850 */	NdrFcShort( 0xfff2 ),	/* Offset= -14 (4836) */
/* 4852 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4854 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4856 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4858 */	0x12, 0x0,	/* FC_UP */
/* 4860 */	NdrFcShort( 0xeda0 ),	/* Offset= -4704 (156) */
/* 4862 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4864 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4866 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4868 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 4870 */	NdrFcShort( 0xf0a4 ),	/* Offset= -3932 (938) */
/* 4872 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4874 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4876 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4878 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 4880 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 4882 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4884 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 4886 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4892 */	0x12, 0x0,	/* FC_UP */
/* 4894 */	NdrFcShort( 0xffc6 ),	/* Offset= -58 (4836) */
/* 4896 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4898 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4900 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4902 */	0x12, 0x0,	/* FC_UP */
/* 4904 */	NdrFcShort( 0xed74 ),	/* Offset= -4748 (156) */
/* 4906 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4908 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4910 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4912 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 4914 */	NdrFcShort( 0xf078 ),	/* Offset= -3976 (938) */
/* 4916 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 4918 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4920 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4922 */	0x12, 0x0,	/* FC_UP */
/* 4924 */	NdrFcShort( 0xf7d6 ),	/* Offset= -2090 (2834) */
/* 4926 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 4928 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4930 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 4932 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 4934 */	
			0x11, 0x0,	/* FC_RP */
/* 4936 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4938) */
/* 4938 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 4940 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 4942 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4944 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 4946 */	0x0 , 
			0x0,		/* 0 */
/* 4948 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4952 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4956 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4958) */
/* 4958 */	NdrFcShort( 0x40 ),	/* 64 */
/* 4960 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4962 */	NdrFcLong( 0x1 ),	/* 1 */
/* 4966 */	NdrFcShort( 0x10 ),	/* Offset= 16 (4982) */
/* 4968 */	NdrFcLong( 0x2 ),	/* 2 */
/* 4972 */	NdrFcShort( 0x4a ),	/* Offset= 74 (5046) */
/* 4974 */	NdrFcLong( 0x3 ),	/* 3 */
/* 4978 */	NdrFcShort( 0x1e4 ),	/* Offset= 484 (5462) */
/* 4980 */	NdrFcShort( 0xffff ),	/* Offset= -1 (4979) */
/* 4982 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 4984 */	NdrFcShort( 0x40 ),	/* 64 */
/* 4986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4988 */	NdrFcShort( 0x0 ),	/* Offset= 0 (4988) */
/* 4990 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 4992 */	NdrFcShort( 0xec8c ),	/* Offset= -4980 (12) */
/* 4994 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 4996 */	NdrFcShort( 0xecf8 ),	/* Offset= -4872 (124) */
/* 4998 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5000 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5002 */	0x6,		/* FC_SHORT */
			0x3e,		/* FC_STRUCTPAD2 */
/* 5004 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5006 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 5008 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5010 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 5012 */	NdrFcShort( 0xec78 ),	/* Offset= -5000 (12) */
/* 5014 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 5016 */	NdrFcShort( 0xece4 ),	/* Offset= -4892 (124) */
/* 5018 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5020 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 5022 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5024 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 5026 */	NdrFcShort( 0x18 ),	/* 24 */
/* 5028 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 5030 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 5032 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5036 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 5040 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 5042 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (5006) */
/* 5044 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5046 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 5048 */	NdrFcShort( 0x20 ),	/* 32 */
/* 5050 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5052 */	NdrFcShort( 0xc ),	/* Offset= 12 (5064) */
/* 5054 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 5056 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5058 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 5060 */	0x3e,		/* FC_STRUCTPAD2 */
			0x8,		/* FC_LONG */
/* 5062 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 5064 */	
			0x12, 0x0,	/* FC_UP */
/* 5066 */	NdrFcShort( 0xecd2 ),	/* Offset= -4910 (156) */
/* 5068 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 5070 */	NdrFcShort( 0xffce ),	/* Offset= -50 (5020) */
/* 5072 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 5074 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 5076 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5078 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 5080 */	0x0 , 
			0x0,		/* 0 */
/* 5082 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5086 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5090 */	NdrFcShort( 0x2 ),	/* Offset= 2 (5092) */
/* 5092 */	NdrFcShort( 0xc ),	/* 12 */
/* 5094 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5096 */	NdrFcLong( 0x1 ),	/* 1 */
/* 5100 */	NdrFcShort( 0x13a ),	/* Offset= 314 (5414) */
/* 5102 */	NdrFcShort( 0xffff ),	/* Offset= -1 (5101) */
/* 5104 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 5106 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 5108 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5110 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 5112 */	0x0 , 
			0x0,		/* 0 */
/* 5114 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5118 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5122 */	NdrFcShort( 0x2 ),	/* Offset= 2 (5124) */
/* 5124 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5126 */	NdrFcShort( 0x7 ),	/* 7 */
/* 5128 */	NdrFcLong( 0x1 ),	/* 1 */
/* 5132 */	NdrFcShort( 0x4e ),	/* Offset= 78 (5210) */
/* 5134 */	NdrFcLong( 0x2 ),	/* 2 */
/* 5138 */	NdrFcShort( 0x5c ),	/* Offset= 92 (5230) */
/* 5140 */	NdrFcLong( 0x3 ),	/* 3 */
/* 5144 */	NdrFcShort( 0xf0 ),	/* Offset= 240 (5384) */
/* 5146 */	NdrFcLong( 0x4 ),	/* 4 */
/* 5150 */	NdrFcShort( 0xfa ),	/* Offset= 250 (5400) */
/* 5152 */	NdrFcLong( 0x5 ),	/* 5 */
/* 5156 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (5400) */
/* 5158 */	NdrFcLong( 0x6 ),	/* 6 */
/* 5162 */	NdrFcShort( 0xee ),	/* Offset= 238 (5400) */
/* 5164 */	NdrFcLong( 0x7 ),	/* 7 */
/* 5168 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (5400) */
/* 5170 */	NdrFcShort( 0xffff ),	/* Offset= -1 (5169) */
/* 5172 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 5174 */	NdrFcShort( 0x20 ),	/* 32 */
/* 5176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5178 */	NdrFcShort( 0x0 ),	/* Offset= 0 (5178) */
/* 5180 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5182 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 5184 */	0x3e,		/* FC_STRUCTPAD2 */
			0x8,		/* FC_LONG */
/* 5186 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5188 */	0x0,		/* 0 */
			NdrFcShort( 0xef0f ),	/* Offset= -4337 (852) */
			0x5b,		/* FC_END */
/* 5192 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 5194 */	NdrFcShort( 0x24 ),	/* 36 */
/* 5196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5198 */	NdrFcShort( 0x8 ),	/* Offset= 8 (5206) */
/* 5200 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5202 */	0x0,		/* 0 */
			NdrFcShort( 0xffe1 ),	/* Offset= -31 (5172) */
			0x5b,		/* FC_END */
/* 5206 */	
			0x12, 0x0,	/* FC_UP */
/* 5208 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (5192) */
/* 5210 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 5212 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5216 */	NdrFcShort( 0xa ),	/* Offset= 10 (5226) */
/* 5218 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 5220 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 5222 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (5192) */
/* 5224 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5226 */	
			0x12, 0x0,	/* FC_UP */
/* 5228 */	NdrFcShort( 0xec30 ),	/* Offset= -5072 (156) */
/* 5230 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 5232 */	NdrFcShort( 0x14 ),	/* 20 */
/* 5234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5236 */	NdrFcShort( 0xa ),	/* Offset= 10 (5246) */
/* 5238 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5240 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 5242 */	0x3e,		/* FC_STRUCTPAD2 */
			0x36,		/* FC_POINTER */
/* 5244 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5246 */	
			0x12, 0x0,	/* FC_UP */
/* 5248 */	NdrFcShort( 0xec1c ),	/* Offset= -5092 (156) */
/* 5250 */	
			0x15,		/* FC_STRUCT */
			0x1,		/* 1 */
/* 5252 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5254 */	0x2,		/* FC_CHAR */
			0x2,		/* FC_CHAR */
/* 5256 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 5258 */	
			0x1c,		/* FC_CVARRAY */
			0x1,		/* 1 */
/* 5260 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5262 */	0x17,		/* Corr desc:  field pointer, FC_USHORT */
			0x55,		/* FC_DIV_2 */
/* 5264 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5266 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 5268 */	0x0 , 
			0x0,		/* 0 */
/* 5270 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5274 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5278 */	0x17,		/* Corr desc:  field pointer, FC_USHORT */
			0x55,		/* FC_DIV_2 */
/* 5280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5282 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 5284 */	0x0 , 
			0x0,		/* 0 */
/* 5286 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5290 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5294 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 5296 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 5298 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5300 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 5302 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5304 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5306 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5308 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 5310 */	NdrFcShort( 0xffcc ),	/* Offset= -52 (5258) */
/* 5312 */	
			0x5b,		/* FC_END */

			0x6,		/* FC_SHORT */
/* 5314 */	0x6,		/* FC_SHORT */
			0x8,		/* FC_LONG */
/* 5316 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5318 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 5320 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5322 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 5324 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5330 */	0x12, 0x0,	/* FC_UP */
/* 5332 */	NdrFcShort( 0xfff2 ),	/* Offset= -14 (5318) */
/* 5334 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5336 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5338 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5340 */	0x12, 0x0,	/* FC_UP */
/* 5342 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (5296) */
/* 5344 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 5346 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 5348 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 5350 */	NdrFcShort( 0x20 ),	/* 32 */
/* 5352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5354 */	NdrFcShort( 0x12 ),	/* Offset= 18 (5372) */
/* 5356 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5358 */	0x0,		/* 0 */
			NdrFcShort( 0xff93 ),	/* Offset= -109 (5250) */
			0x6,		/* FC_SHORT */
/* 5362 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 5364 */	0x6,		/* FC_SHORT */
			0x36,		/* FC_POINTER */
/* 5366 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 5368 */	0x2,		/* FC_CHAR */
			0x3f,		/* FC_STRUCTPAD3 */
/* 5370 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5372 */	
			0x12, 0x0,	/* FC_UP */
/* 5374 */	NdrFcShort( 0xeb9e ),	/* Offset= -5218 (156) */
/* 5376 */	
			0x12, 0x0,	/* FC_UP */
/* 5378 */	NdrFcShort( 0xffc4 ),	/* Offset= -60 (5318) */
/* 5380 */	
			0x12, 0x0,	/* FC_UP */
/* 5382 */	NdrFcShort( 0xffde ),	/* Offset= -34 (5348) */
/* 5384 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 5386 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5390 */	NdrFcShort( 0x0 ),	/* Offset= 0 (5390) */
/* 5392 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5394 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5396 */	0x0,		/* 0 */
			NdrFcShort( 0xffcf ),	/* Offset= -49 (5348) */
			0x5b,		/* FC_END */
/* 5400 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 5402 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5406 */	NdrFcShort( 0x0 ),	/* Offset= 0 (5406) */
/* 5408 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5410 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 5412 */	0x3e,		/* FC_STRUCTPAD2 */
			0x5b,		/* FC_END */
/* 5414 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 5416 */	NdrFcShort( 0xc ),	/* 12 */
/* 5418 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 5420 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5422 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5424 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5426 */	0x12, 0x0,	/* FC_UP */
/* 5428 */	NdrFcShort( 0xfebc ),	/* Offset= -324 (5104) */
/* 5430 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 5432 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5434 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5436 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 5438 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5440 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 5442 */	NdrFcShort( 0xc ),	/* 12 */
/* 5444 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 5446 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 5448 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5452 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 5456 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 5458 */	NdrFcShort( 0xfe3c ),	/* Offset= -452 (5006) */
/* 5460 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5462 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 5464 */	NdrFcShort( 0x14 ),	/* 20 */
/* 5466 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 5468 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5474 */	0x12, 0x0,	/* FC_UP */
/* 5476 */	NdrFcShort( 0xeb38 ),	/* Offset= -5320 (156) */
/* 5478 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5480 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5482 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5484 */	0x12, 0x0,	/* FC_UP */
/* 5486 */	NdrFcShort( 0xfe62 ),	/* Offset= -414 (5072) */
/* 5488 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5490 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5492 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5494 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 5496 */	NdrFcShort( 0xffc4 ),	/* Offset= -60 (5436) */
/* 5498 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 5500 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5502 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5504 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5506 */	
			0x11, 0x0,	/* FC_RP */
/* 5508 */	NdrFcShort( 0x2 ),	/* Offset= 2 (5510) */
/* 5510 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 5512 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 5514 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5516 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 5518 */	0x0 , 
			0x0,		/* 0 */
/* 5520 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5524 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5528 */	NdrFcShort( 0x2 ),	/* Offset= 2 (5530) */
/* 5530 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5532 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5534 */	NdrFcLong( 0x1 ),	/* 1 */
/* 5538 */	NdrFcShort( 0x4 ),	/* Offset= 4 (5542) */
/* 5540 */	NdrFcShort( 0xffff ),	/* Offset= -1 (5539) */
/* 5542 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 5544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5546 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5548 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5550 */	
			0x11, 0x0,	/* FC_RP */
/* 5552 */	NdrFcShort( 0x2 ),	/* Offset= 2 (5554) */
/* 5554 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 5556 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 5558 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5560 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 5562 */	0x0 , 
			0x0,		/* 0 */
/* 5564 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5568 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5572 */	NdrFcShort( 0x2 ),	/* Offset= 2 (5574) */
/* 5574 */	NdrFcShort( 0x28 ),	/* 40 */
/* 5576 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5578 */	NdrFcLong( 0x1 ),	/* 1 */
/* 5582 */	NdrFcShort( 0xa ),	/* Offset= 10 (5592) */
/* 5584 */	NdrFcLong( 0x2 ),	/* 2 */
/* 5588 */	NdrFcShort( 0x1c ),	/* Offset= 28 (5616) */
/* 5590 */	NdrFcShort( 0xffff ),	/* Offset= -1 (5589) */
/* 5592 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 5594 */	NdrFcShort( 0x18 ),	/* 24 */
/* 5596 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 5598 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5600 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5602 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5604 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5606 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5608 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 5610 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5612 */	0x0,		/* 0 */
			NdrFcShort( 0xea1f ),	/* Offset= -5601 (12) */
			0x5b,		/* FC_END */
/* 5616 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 5618 */	NdrFcShort( 0x28 ),	/* 40 */
/* 5620 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 5622 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5624 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5626 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5628 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5630 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5632 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5634 */	NdrFcShort( 0x1c ),	/* 28 */
/* 5636 */	NdrFcShort( 0x1c ),	/* 28 */
/* 5638 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5640 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5642 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5644 */	NdrFcShort( 0x20 ),	/* 32 */
/* 5646 */	NdrFcShort( 0x20 ),	/* 32 */
/* 5648 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5650 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5652 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 5654 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5656 */	0x0,		/* 0 */
			NdrFcShort( 0xe9f3 ),	/* Offset= -5645 (12) */
			0x8,		/* FC_LONG */
/* 5660 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5662 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 5664 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 5666 */	NdrFcShort( 0x2 ),	/* Offset= 2 (5668) */
/* 5668 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 5670 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 5672 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5674 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 5676 */	0x0 , 
			0x0,		/* 0 */
/* 5678 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5682 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5686 */	NdrFcShort( 0x2 ),	/* Offset= 2 (5688) */
/* 5688 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5690 */	NdrFcShort( 0xf ),	/* 15 */
/* 5692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5696 */	NdrFcShort( 0x58 ),	/* Offset= 88 (5784) */
/* 5698 */	NdrFcLong( 0x1 ),	/* 1 */
/* 5702 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (5948) */
/* 5704 */	NdrFcLong( 0x2 ),	/* 2 */
/* 5708 */	NdrFcShort( 0x118 ),	/* Offset= 280 (5988) */
/* 5710 */	NdrFcLong( 0x3 ),	/* 3 */
/* 5714 */	NdrFcShort( 0x16a ),	/* Offset= 362 (6076) */
/* 5716 */	NdrFcLong( 0x4 ),	/* 4 */
/* 5720 */	NdrFcShort( 0x164 ),	/* Offset= 356 (6076) */
/* 5722 */	NdrFcLong( 0x5 ),	/* 5 */
/* 5726 */	NdrFcShort( 0x1b6 ),	/* Offset= 438 (6164) */
/* 5728 */	NdrFcLong( 0x6 ),	/* 6 */
/* 5732 */	NdrFcShort( 0x214 ),	/* Offset= 532 (6264) */
/* 5734 */	NdrFcLong( 0x7 ),	/* 7 */
/* 5738 */	NdrFcShort( 0x28c ),	/* Offset= 652 (6390) */
/* 5740 */	NdrFcLong( 0x8 ),	/* 8 */
/* 5744 */	NdrFcShort( 0x2bc ),	/* Offset= 700 (6444) */
/* 5746 */	NdrFcLong( 0x9 ),	/* 9 */
/* 5750 */	NdrFcShort( 0x308 ),	/* Offset= 776 (6526) */
/* 5752 */	NdrFcLong( 0xa ),	/* 10 */
/* 5756 */	NdrFcShort( 0x35c ),	/* Offset= 860 (6616) */
/* 5758 */	NdrFcLong( 0xfffffffa ),	/* -6 */
/* 5762 */	NdrFcShort( 0x3c4 ),	/* Offset= 964 (6726) */
/* 5764 */	NdrFcLong( 0xfffffffb ),	/* -5 */
/* 5768 */	NdrFcShort( 0x40e ),	/* Offset= 1038 (6806) */
/* 5770 */	NdrFcLong( 0xfffffffc ),	/* -4 */
/* 5774 */	NdrFcShort( 0x40c ),	/* Offset= 1036 (6810) */
/* 5776 */	NdrFcLong( 0xfffffffe ),	/* -2 */
/* 5780 */	NdrFcShort( 0x4 ),	/* Offset= 4 (5784) */
/* 5782 */	NdrFcShort( 0xffff ),	/* Offset= -1 (5781) */
/* 5784 */	
			0x12, 0x0,	/* FC_UP */
/* 5786 */	NdrFcShort( 0x6e ),	/* Offset= 110 (5896) */
/* 5788 */	
			0x16,		/* FC_PSTRUCT */
			0x7,		/* 7 */
/* 5790 */	NdrFcShort( 0x80 ),	/* 128 */
/* 5792 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 5794 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5796 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5798 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5800 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5802 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5804 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5806 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5808 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5810 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5812 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5814 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5816 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5818 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5820 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5822 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5824 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 5826 */	NdrFcShort( 0xc ),	/* 12 */
/* 5828 */	NdrFcShort( 0xc ),	/* 12 */
/* 5830 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5832 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5834 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 5836 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5838 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5840 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5842 */	0x0,		/* 0 */
			NdrFcShort( 0xe939 ),	/* Offset= -5831 (12) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5846 */	0x0,		/* 0 */
			NdrFcShort( 0xe935 ),	/* Offset= -5835 (12) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5850 */	0x0,		/* 0 */
			NdrFcShort( 0xe931 ),	/* Offset= -5839 (12) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5854 */	0x0,		/* 0 */
			NdrFcShort( 0xe92d ),	/* Offset= -5843 (12) */
			0xb,		/* FC_HYPER */
/* 5858 */	0xb,		/* FC_HYPER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5860 */	0x0,		/* 0 */
			NdrFcShort( 0xfec1 ),	/* Offset= -319 (5542) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 5864 */	0x0,		/* 0 */
			NdrFcShort( 0xfebd ),	/* Offset= -323 (5542) */
			0x8,		/* FC_LONG */
/* 5868 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 5870 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 5872 */	NdrFcShort( 0x80 ),	/* 128 */
/* 5874 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 5876 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 5878 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 5880 */	0x0 , 
			0x0,		/* 0 */
/* 5882 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5886 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5890 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 5892 */	NdrFcShort( 0xff98 ),	/* Offset= -104 (5788) */
/* 5894 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5896 */	
			0x18,		/* FC_CPSTRUCT */
			0x7,		/* 7 */
/* 5898 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5900 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (5870) */
/* 5902 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 5904 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 5906 */	NdrFcShort( 0x80 ),	/* 128 */
/* 5908 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5910 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5912 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5914 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5916 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5918 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5920 */	NdrFcShort( 0xc ),	/* 12 */
/* 5922 */	NdrFcShort( 0xc ),	/* 12 */
/* 5924 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5926 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5928 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5930 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5932 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5934 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5936 */	NdrFcShort( 0x14 ),	/* 20 */
/* 5938 */	NdrFcShort( 0x14 ),	/* 20 */
/* 5940 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 5942 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 5944 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 5946 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 5948 */	
			0x12, 0x0,	/* FC_UP */
/* 5950 */	NdrFcShort( 0x1c ),	/* Offset= 28 (5978) */
/* 5952 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 5954 */	NdrFcShort( 0x18 ),	/* 24 */
/* 5956 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 5958 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 5960 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 5962 */	0x0 , 
			0x0,		/* 0 */
/* 5964 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5968 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5972 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 5974 */	NdrFcShort( 0xea2c ),	/* Offset= -5588 (386) */
/* 5976 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5978 */	
			0x17,		/* FC_CSTRUCT */
			0x7,		/* 7 */
/* 5980 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5982 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (5952) */
/* 5984 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 5986 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 5988 */	
			0x12, 0x0,	/* FC_UP */
/* 5990 */	NdrFcShort( 0x3a ),	/* Offset= 58 (6048) */
/* 5992 */	
			0x16,		/* FC_PSTRUCT */
			0x7,		/* 7 */
/* 5994 */	NdrFcShort( 0x30 ),	/* 48 */
/* 5996 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 5998 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 6000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6004 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6006 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6008 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 6010 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6012 */	0x0,		/* 0 */
			NdrFcShort( 0xfe29 ),	/* Offset= -471 (5542) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6016 */	0x0,		/* 0 */
			NdrFcShort( 0xe88b ),	/* Offset= -6005 (12) */
			0xb,		/* FC_HYPER */
/* 6020 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 6022 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 6024 */	NdrFcShort( 0x30 ),	/* 48 */
/* 6026 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6028 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 6030 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6032 */	0x0 , 
			0x0,		/* 0 */
/* 6034 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6038 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6042 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6044 */	NdrFcShort( 0xffcc ),	/* Offset= -52 (5992) */
/* 6046 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6048 */	
			0x18,		/* FC_CPSTRUCT */
			0x7,		/* 7 */
/* 6050 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6052 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (6022) */
/* 6054 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 6056 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 6058 */	NdrFcShort( 0x30 ),	/* 48 */
/* 6060 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6062 */	NdrFcShort( 0x1 ),	/* 1 */
/* 6064 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6066 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6068 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6070 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6072 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 6074 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 6076 */	
			0x12, 0x0,	/* FC_UP */
/* 6078 */	NdrFcShort( 0x3a ),	/* Offset= 58 (6136) */
/* 6080 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 6082 */	NdrFcShort( 0x24 ),	/* 36 */
/* 6084 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 6086 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 6088 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6092 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6094 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6096 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 6098 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6100 */	NdrFcShort( 0xe838 ),	/* Offset= -6088 (12) */
/* 6102 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6104 */	NdrFcShort( 0xfdce ),	/* Offset= -562 (5542) */
/* 6106 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6108 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6110 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 6112 */	NdrFcShort( 0x24 ),	/* 36 */
/* 6114 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6116 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 6118 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6120 */	0x0 , 
			0x0,		/* 0 */
/* 6122 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6126 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6130 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6132 */	NdrFcShort( 0xffcc ),	/* Offset= -52 (6080) */
/* 6134 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6136 */	
			0x18,		/* FC_CPSTRUCT */
			0x3,		/* 3 */
/* 6138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6140 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (6110) */
/* 6142 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 6144 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 6146 */	NdrFcShort( 0x24 ),	/* 36 */
/* 6148 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6150 */	NdrFcShort( 0x1 ),	/* 1 */
/* 6152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6154 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6156 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6158 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6160 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 6162 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 6164 */	
			0x12, 0x0,	/* FC_UP */
/* 6166 */	NdrFcShort( 0x54 ),	/* Offset= 84 (6250) */
/* 6168 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 6170 */	NdrFcShort( 0x44 ),	/* 68 */
/* 6172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6174 */	NdrFcShort( 0x16 ),	/* Offset= 22 (6196) */
/* 6176 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6178 */	NdrFcShort( 0xfd84 ),	/* Offset= -636 (5542) */
/* 6180 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6182 */	0xd,		/* FC_ENUM16 */
			0x8,		/* FC_LONG */
/* 6184 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 6186 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6188 */	0x0,		/* 0 */
			NdrFcShort( 0xe7df ),	/* Offset= -6177 (12) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6192 */	0x0,		/* 0 */
			NdrFcShort( 0xe7db ),	/* Offset= -6181 (12) */
			0x5b,		/* FC_END */
/* 6196 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6198 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6200 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6202 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6204 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6206 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6208 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 6210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6212 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6214 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 6216 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6218 */	0x0 , 
			0x0,		/* 0 */
/* 6220 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6224 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6228 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 6232 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 6234 */	0x0 , 
			0x0,		/* 0 */
/* 6236 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6240 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6244 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6246 */	NdrFcShort( 0xffb2 ),	/* Offset= -78 (6168) */
/* 6248 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6250 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 6252 */	NdrFcShort( 0xc ),	/* 12 */
/* 6254 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (6208) */
/* 6256 */	NdrFcShort( 0x0 ),	/* Offset= 0 (6256) */
/* 6258 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6260 */	NdrFcShort( 0xfd32 ),	/* Offset= -718 (5542) */
/* 6262 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 6264 */	
			0x12, 0x0,	/* FC_UP */
/* 6266 */	NdrFcShort( 0x70 ),	/* Offset= 112 (6378) */
/* 6268 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 6270 */	NdrFcShort( 0x1 ),	/* 1 */
/* 6272 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 6274 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6276 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6278 */	0x0 , 
			0x0,		/* 0 */
/* 6280 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6284 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6288 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 6290 */	0xb1,		/* FC_FORCED_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6292 */	NdrFcShort( 0x50 ),	/* 80 */
/* 6294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6296 */	NdrFcShort( 0x1c ),	/* Offset= 28 (6324) */
/* 6298 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 6300 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 6302 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6304 */	NdrFcShort( 0xfd06 ),	/* Offset= -762 (5542) */
/* 6306 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6308 */	NdrFcShort( 0xfd02 ),	/* Offset= -766 (5542) */
/* 6310 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6312 */	0x0,		/* 0 */
			NdrFcShort( 0xfcfd ),	/* Offset= -771 (5542) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6316 */	0x0,		/* 0 */
			NdrFcShort( 0xe75f ),	/* Offset= -6305 (12) */
			0x40,		/* FC_STRUCTPAD4 */
/* 6320 */	0xb,		/* FC_HYPER */
			0xb,		/* FC_HYPER */
/* 6322 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6324 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6326 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6328 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6330 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6332 */	
			0x14, 0x20,	/* FC_FP [maybenull_sizeis] */
/* 6334 */	NdrFcShort( 0xffbe ),	/* Offset= -66 (6268) */
/* 6336 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x7,		/* 7 */
/* 6338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6340 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6342 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 6344 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6346 */	0x0 , 
			0x0,		/* 0 */
/* 6348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6352 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6356 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 6360 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 6362 */	0x0 , 
			0x0,		/* 0 */
/* 6364 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6368 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6372 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6374 */	NdrFcShort( 0xffac ),	/* Offset= -84 (6290) */
/* 6376 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6378 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6380 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6382 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (6336) */
/* 6384 */	NdrFcShort( 0x0 ),	/* Offset= 0 (6384) */
/* 6386 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6388 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6390 */	
			0x12, 0x0,	/* FC_UP */
/* 6392 */	NdrFcShort( 0x2a ),	/* Offset= 42 (6434) */
/* 6394 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 6396 */	NdrFcShort( 0x20 ),	/* 32 */
/* 6398 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6400 */	NdrFcShort( 0xe70c ),	/* Offset= -6388 (12) */
/* 6402 */	0xb,		/* FC_HYPER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6404 */	0x0,		/* 0 */
			NdrFcShort( 0xfca1 ),	/* Offset= -863 (5542) */
			0x5b,		/* FC_END */
/* 6408 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 6410 */	NdrFcShort( 0x20 ),	/* 32 */
/* 6412 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6414 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 6416 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6418 */	0x0 , 
			0x0,		/* 0 */
/* 6420 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6424 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6428 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6430 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (6394) */
/* 6432 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6434 */	
			0x17,		/* FC_CSTRUCT */
			0x7,		/* 7 */
/* 6436 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6438 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (6408) */
/* 6440 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6442 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6444 */	
			0x12, 0x0,	/* FC_UP */
/* 6446 */	NdrFcShort( 0x44 ),	/* Offset= 68 (6514) */
/* 6448 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6450 */	NdrFcShort( 0x28 ),	/* 40 */
/* 6452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6454 */	NdrFcShort( 0xe ),	/* Offset= 14 (6468) */
/* 6456 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6458 */	NdrFcShort( 0xe6d2 ),	/* Offset= -6446 (12) */
/* 6460 */	0xb,		/* FC_HYPER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6462 */	0x0,		/* 0 */
			NdrFcShort( 0xfc67 ),	/* Offset= -921 (5542) */
			0x36,		/* FC_POINTER */
/* 6466 */	0x40,		/* FC_STRUCTPAD4 */
			0x5b,		/* FC_END */
/* 6468 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6470 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6472 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x7,		/* 7 */
/* 6474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6476 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6478 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 6480 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6482 */	0x0 , 
			0x0,		/* 0 */
/* 6484 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6488 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6492 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 6496 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 6498 */	0x0 , 
			0x0,		/* 0 */
/* 6500 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6504 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6508 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6510 */	NdrFcShort( 0xffc2 ),	/* Offset= -62 (6448) */
/* 6512 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6514 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6516 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6518 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (6472) */
/* 6520 */	NdrFcShort( 0x0 ),	/* Offset= 0 (6520) */
/* 6522 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6524 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6526 */	
			0x12, 0x0,	/* FC_UP */
/* 6528 */	NdrFcShort( 0x4c ),	/* Offset= 76 (6604) */
/* 6530 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6532 */	NdrFcShort( 0x38 ),	/* 56 */
/* 6534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6536 */	NdrFcShort( 0x12 ),	/* Offset= 18 (6554) */
/* 6538 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 6540 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6542 */	NdrFcShort( 0xfc18 ),	/* Offset= -1000 (5542) */
/* 6544 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6546 */	NdrFcShort( 0xe67a ),	/* Offset= -6534 (12) */
/* 6548 */	0xb,		/* FC_HYPER */
			0xb,		/* FC_HYPER */
/* 6550 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 6552 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6554 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6556 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6558 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6560 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6562 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x7,		/* 7 */
/* 6564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6566 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6568 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 6570 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6572 */	0x0 , 
			0x0,		/* 0 */
/* 6574 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6578 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6582 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 6586 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 6588 */	0x0 , 
			0x0,		/* 0 */
/* 6590 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6594 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6598 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6600 */	NdrFcShort( 0xffba ),	/* Offset= -70 (6530) */
/* 6602 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6604 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6606 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6608 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (6562) */
/* 6610 */	NdrFcShort( 0x0 ),	/* Offset= 0 (6610) */
/* 6612 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6614 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6616 */	
			0x12, 0x0,	/* FC_UP */
/* 6618 */	NdrFcShort( 0x60 ),	/* Offset= 96 (6714) */
/* 6620 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6622 */	NdrFcShort( 0x58 ),	/* 88 */
/* 6624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6626 */	NdrFcShort( 0x1e ),	/* Offset= 30 (6656) */
/* 6628 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 6630 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 6632 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6634 */	NdrFcShort( 0xfbbc ),	/* Offset= -1092 (5542) */
/* 6636 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6638 */	NdrFcShort( 0xfbb8 ),	/* Offset= -1096 (5542) */
/* 6640 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6642 */	0x0,		/* 0 */
			NdrFcShort( 0xfbb3 ),	/* Offset= -1101 (5542) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6646 */	0x0,		/* 0 */
			NdrFcShort( 0xe615 ),	/* Offset= -6635 (12) */
			0x40,		/* FC_STRUCTPAD4 */
/* 6650 */	0xb,		/* FC_HYPER */
			0xb,		/* FC_HYPER */
/* 6652 */	0x36,		/* FC_POINTER */
			0x40,		/* FC_STRUCTPAD4 */
/* 6654 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6656 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6658 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6660 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6662 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6664 */	
			0x14, 0x20,	/* FC_FP [maybenull_sizeis] */
/* 6666 */	NdrFcShort( 0xfe72 ),	/* Offset= -398 (6268) */
/* 6668 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6670 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6672 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x7,		/* 7 */
/* 6674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6676 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6678 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 6680 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6682 */	0x0 , 
			0x0,		/* 0 */
/* 6684 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6688 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6692 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 6696 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 6698 */	0x0 , 
			0x0,		/* 0 */
/* 6700 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6704 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6708 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6710 */	NdrFcShort( 0xffa6 ),	/* Offset= -90 (6620) */
/* 6712 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6714 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6716 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6718 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (6672) */
/* 6720 */	NdrFcShort( 0x0 ),	/* Offset= 0 (6720) */
/* 6722 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6724 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6726 */	
			0x12, 0x0,	/* FC_UP */
/* 6728 */	NdrFcShort( 0x42 ),	/* Offset= 66 (6794) */
/* 6730 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6732 */	NdrFcShort( 0x28 ),	/* 40 */
/* 6734 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6736 */	NdrFcShort( 0xc ),	/* Offset= 12 (6748) */
/* 6738 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 6740 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6742 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6744 */	0xb,		/* FC_HYPER */
			0x8,		/* FC_LONG */
/* 6746 */	0x40,		/* FC_STRUCTPAD4 */
			0x5b,		/* FC_END */
/* 6748 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6750 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6752 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x7,		/* 7 */
/* 6754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6756 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6758 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 6760 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 6762 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 6764 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6768 */	NdrFcLong( 0x100 ),	/* 256 */
/* 6772 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 6776 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 6778 */	0x0 , 
			0x0,		/* 0 */
/* 6780 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6784 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6788 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6790 */	NdrFcShort( 0xffc4 ),	/* Offset= -60 (6730) */
/* 6792 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6794 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 6796 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6798 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (6752) */
/* 6800 */	NdrFcShort( 0x0 ),	/* Offset= 0 (6800) */
/* 6802 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6804 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6806 */	
			0x12, 0x0,	/* FC_UP */
/* 6808 */	NdrFcShort( 0xe70e ),	/* Offset= -6386 (422) */
/* 6810 */	
			0x12, 0x0,	/* FC_UP */
/* 6812 */	NdrFcShort( 0x2c ),	/* Offset= 44 (6856) */
/* 6814 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 6816 */	NdrFcShort( 0x30 ),	/* 48 */
/* 6818 */	0xb,		/* FC_HYPER */
			0x8,		/* FC_LONG */
/* 6820 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 6822 */	0x0,		/* 0 */
			NdrFcShort( 0xe565 ),	/* Offset= -6811 (12) */
			0xb,		/* FC_HYPER */
/* 6826 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6828 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6830 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 6832 */	NdrFcShort( 0x30 ),	/* 48 */
/* 6834 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 6836 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 6838 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 6840 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 6842 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6846 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 6850 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 6852 */	NdrFcShort( 0xffda ),	/* Offset= -38 (6814) */
/* 6854 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6856 */	
			0x17,		/* FC_CSTRUCT */
			0x7,		/* 7 */
/* 6858 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6860 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (6830) */
/* 6862 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 6864 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 6866 */	
			0x11, 0x0,	/* FC_RP */
/* 6868 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6870) */
/* 6870 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 6872 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 6874 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6876 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 6878 */	0x0 , 
			0x0,		/* 0 */
/* 6880 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6884 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6888 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6890) */
/* 6890 */	NdrFcShort( 0x30 ),	/* 48 */
/* 6892 */	NdrFcShort( 0x1 ),	/* 1 */
/* 6894 */	NdrFcLong( 0x1 ),	/* 1 */
/* 6898 */	NdrFcShort( 0x46 ),	/* Offset= 70 (6968) */
/* 6900 */	NdrFcShort( 0xffff ),	/* Offset= -1 (6899) */
/* 6902 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 6904 */	NdrFcShort( 0x2 ),	/* 2 */
/* 6906 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 6908 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6910 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 6912 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 6914 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6918 */	NdrFcLong( 0x100 ),	/* 256 */
/* 6922 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 6924 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 6926 */	NdrFcShort( 0x2 ),	/* 2 */
/* 6928 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 6930 */	NdrFcShort( 0x18 ),	/* 24 */
/* 6932 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 6934 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 6936 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6940 */	NdrFcLong( 0x100 ),	/* 256 */
/* 6944 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 6946 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 6948 */	NdrFcShort( 0x2 ),	/* 2 */
/* 6950 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 6952 */	NdrFcShort( 0x20 ),	/* 32 */
/* 6954 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 6956 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 6958 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6962 */	NdrFcLong( 0x100 ),	/* 256 */
/* 6966 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 6968 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 6970 */	NdrFcShort( 0x30 ),	/* 48 */
/* 6972 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 6974 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 6976 */	NdrFcShort( 0x4 ),	/* 4 */
/* 6978 */	NdrFcShort( 0x4 ),	/* 4 */
/* 6980 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6982 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6984 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 6986 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6988 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6990 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 6992 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 6994 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 6996 */	NdrFcShort( 0xc ),	/* 12 */
/* 6998 */	NdrFcShort( 0xc ),	/* 12 */
/* 7000 */	0x14, 0x8,	/* FC_FP [simple_pointer] */
/* 7002 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 7004 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7006 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7008 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7010 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7012 */	NdrFcShort( 0xff92 ),	/* Offset= -110 (6902) */
/* 7014 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7016 */	NdrFcShort( 0x1c ),	/* 28 */
/* 7018 */	NdrFcShort( 0x1c ),	/* 28 */
/* 7020 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7022 */	NdrFcShort( 0xff9e ),	/* Offset= -98 (6924) */
/* 7024 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7026 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7028 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7030 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7032 */	NdrFcShort( 0xffaa ),	/* Offset= -86 (6946) */
/* 7034 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7036 */	NdrFcShort( 0x28 ),	/* 40 */
/* 7038 */	NdrFcShort( 0x28 ),	/* 40 */
/* 7040 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 7042 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 7044 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7046 */	NdrFcShort( 0x2c ),	/* 44 */
/* 7048 */	NdrFcShort( 0x2c ),	/* 44 */
/* 7050 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 7052 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 7054 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7056 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 7058 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 7060 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 7062 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 7064 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 7066 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 7068 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 7070 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7072) */
/* 7072 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7074 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 7076 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7078 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7080 */	0x0 , 
			0x0,		/* 0 */
/* 7082 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7086 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7090 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7092) */
/* 7092 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7094 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7096 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7100 */	NdrFcShort( 0xf2c6 ),	/* Offset= -3386 (3714) */
/* 7102 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7101) */
/* 7104 */	
			0x11, 0x0,	/* FC_RP */
/* 7106 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7108) */
/* 7108 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7110 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 7112 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7114 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7116 */	0x0 , 
			0x0,		/* 0 */
/* 7118 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7122 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7126 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7128) */
/* 7128 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7130 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7132 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7136 */	NdrFcShort( 0x2e ),	/* Offset= 46 (7182) */
/* 7138 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7137) */
/* 7140 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 7142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7144 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 7146 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7148 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 7150 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 7152 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7156 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 7160 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 7164 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 7166 */	0x0 , 
			0x0,		/* 0 */
/* 7168 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7172 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7176 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 7178 */	NdrFcShort( 0xed7c ),	/* Offset= -4740 (2438) */
/* 7180 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 7182 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 7184 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7186 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7188 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7190 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7192 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7194 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7196 */	NdrFcShort( 0xffc8 ),	/* Offset= -56 (7140) */
/* 7198 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7200 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 7202 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 7204 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7206) */
/* 7206 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7208 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 7210 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7212 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7214 */	0x0 , 
			0x0,		/* 0 */
/* 7216 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7220 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7224 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7226) */
/* 7226 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7228 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7230 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7234 */	NdrFcShort( 0x40 ),	/* Offset= 64 (7298) */
/* 7236 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7235) */
/* 7238 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 7240 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7242 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 7244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7246 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 7248 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 7250 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7254 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 7258 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7260 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 7262 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7264 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7266 */	NdrFcShort( 0x3 ),	/* 3 */
/* 7268 */	NdrFcShort( 0xc ),	/* 12 */
/* 7270 */	NdrFcShort( 0xc ),	/* 12 */
/* 7272 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7274 */	NdrFcShort( 0xed5a ),	/* Offset= -4774 (2500) */
/* 7276 */	NdrFcShort( 0x10 ),	/* 16 */
/* 7278 */	NdrFcShort( 0x10 ),	/* 16 */
/* 7280 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7282 */	NdrFcShort( 0xed7c ),	/* Offset= -4740 (2542) */
/* 7284 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7286 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7288 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7290 */	NdrFcShort( 0xed8a ),	/* Offset= -4726 (2564) */
/* 7292 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 7294 */	0x0,		/* 0 */
			NdrFcShort( 0xedaf ),	/* Offset= -4689 (2606) */
			0x5b,		/* FC_END */
/* 7298 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 7300 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7302 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7304 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7306 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7308 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7310 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7312 */	NdrFcShort( 0xffb6 ),	/* Offset= -74 (7238) */
/* 7314 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7316 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 7318 */	
			0x11, 0x0,	/* FC_RP */
/* 7320 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7322) */
/* 7322 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7324 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 7326 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7328 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7330 */	0x0 , 
			0x0,		/* 0 */
/* 7332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7336 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7340 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7342) */
/* 7342 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7344 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7346 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7350 */	NdrFcShort( 0x4 ),	/* Offset= 4 (7354) */
/* 7352 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7351) */
/* 7354 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 7356 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7358 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7360 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7366 */	0x11, 0x0,	/* FC_RP */
/* 7368 */	NdrFcShort( 0xe3d4 ),	/* Offset= -7212 (156) */
/* 7370 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7372 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 7374 */	NdrFcShort( 0xe33e ),	/* Offset= -7362 (12) */
/* 7376 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 7378 */	
			0x11, 0x0,	/* FC_RP */
/* 7380 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7382) */
/* 7382 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7384 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 7386 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7388 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7390 */	0x0 , 
			0x0,		/* 0 */
/* 7392 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7396 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7400 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7402) */
/* 7402 */	NdrFcShort( 0x2c ),	/* 44 */
/* 7404 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7406 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7410 */	NdrFcShort( 0xa ),	/* Offset= 10 (7420) */
/* 7412 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7411) */
/* 7414 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 7416 */	NdrFcShort( 0x10 ),	/* 16 */
/* 7418 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 7420 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 7422 */	NdrFcShort( 0x2c ),	/* 44 */
/* 7424 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7426 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7428 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7430 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7432 */	0x12, 0x0,	/* FC_UP */
/* 7434 */	NdrFcShort( 0xe392 ),	/* Offset= -7278 (156) */
/* 7436 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7438 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7440 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7442 */	0x12, 0x0,	/* FC_UP */
/* 7444 */	NdrFcShort( 0xe492 ),	/* Offset= -7022 (422) */
/* 7446 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 7448 */	0x0,		/* 0 */
			NdrFcShort( 0xe2f3 ),	/* Offset= -7437 (12) */
			0x8,		/* FC_LONG */
/* 7452 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 7454 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 7456 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (7414) */
/* 7458 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 7460 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 7462 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7464) */
/* 7464 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7466 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 7468 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7470 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7472 */	0x0 , 
			0x0,		/* 0 */
/* 7474 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7478 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7482 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7484) */
/* 7484 */	NdrFcShort( 0xc ),	/* 12 */
/* 7486 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7488 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7492 */	NdrFcShort( 0x1e ),	/* Offset= 30 (7522) */
/* 7494 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7493) */
/* 7496 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 7498 */	NdrFcShort( 0x10 ),	/* 16 */
/* 7500 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 7502 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7504 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 7506 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 7508 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7512 */	NdrFcLong( 0xa00000 ),	/* 10485760 */
/* 7516 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 7518 */	NdrFcShort( 0xe2ae ),	/* Offset= -7506 (12) */
/* 7520 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 7522 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 7524 */	NdrFcShort( 0xc ),	/* 12 */
/* 7526 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7528 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7530 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7532 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7534 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7536 */	NdrFcShort( 0xffd8 ),	/* Offset= -40 (7496) */
/* 7538 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7540 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 7542 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 7544 */	
			0x11, 0x0,	/* FC_RP */
/* 7546 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7548) */
/* 7548 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7550 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 7552 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7554 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7556 */	0x0 , 
			0x0,		/* 0 */
/* 7558 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7562 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7566 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7568) */
/* 7568 */	NdrFcShort( 0x10 ),	/* 16 */
/* 7570 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7572 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7576 */	NdrFcShort( 0x2e ),	/* Offset= 46 (7622) */
/* 7578 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7577) */
/* 7580 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 7582 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7584 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 7586 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7588 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 7590 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 7592 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7596 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 7600 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7602 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 7604 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7608 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7614 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 7616 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 7618 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7620 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 7622 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 7624 */	NdrFcShort( 0x10 ),	/* 16 */
/* 7626 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7628 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7634 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 7636 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 7638 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7640 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7642 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7644 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7646 */	NdrFcShort( 0xffbe ),	/* Offset= -66 (7580) */
/* 7648 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7650 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 7652 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 7654 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 7656 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7658) */
/* 7658 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7660 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 7662 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7664 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7666 */	0x0 , 
			0x0,		/* 0 */
/* 7668 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7672 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7676 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7678) */
/* 7678 */	NdrFcShort( 0xc ),	/* 12 */
/* 7680 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7682 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7686 */	NdrFcShort( 0x1e ),	/* Offset= 30 (7716) */
/* 7688 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7687) */
/* 7690 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 7692 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7694 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 7696 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7698 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 7700 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 7702 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7706 */	NdrFcLong( 0x2710 ),	/* 10000 */
/* 7710 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 7712 */	NdrFcShort( 0xf786 ),	/* Offset= -2170 (5542) */
/* 7714 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 7716 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 7718 */	NdrFcShort( 0xc ),	/* 12 */
/* 7720 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7722 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7724 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7726 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7728 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 7730 */	NdrFcShort( 0xffd8 ),	/* Offset= -40 (7690) */
/* 7732 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7734 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 7736 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 7738 */	
			0x11, 0x0,	/* FC_RP */
/* 7740 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7742) */
/* 7742 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7744 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 7746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7748 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7750 */	0x0 , 
			0x0,		/* 0 */
/* 7752 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7756 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7760 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7762) */
/* 7762 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7764 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7766 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7770 */	NdrFcShort( 0xf028 ),	/* Offset= -4056 (3714) */
/* 7772 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7771) */
/* 7774 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 7776 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7778) */
/* 7778 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7780 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 7782 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7784 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7786 */	0x0 , 
			0x0,		/* 0 */
/* 7788 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7792 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7796 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7798) */
/* 7798 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7800 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7802 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7806 */	NdrFcShort( 0xf004 ),	/* Offset= -4092 (3714) */
/* 7808 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7807) */
/* 7810 */	
			0x11, 0x0,	/* FC_RP */
/* 7812 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7814) */
/* 7814 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7816 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 7818 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7820 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7822 */	0x0 , 
			0x0,		/* 0 */
/* 7824 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7828 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7832 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7834) */
/* 7834 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7836 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7838 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7842 */	NdrFcShort( 0x4 ),	/* Offset= 4 (7846) */
/* 7844 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7843) */
/* 7846 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 7848 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7850 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7852 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7854 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7856 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7858 */	0x11, 0x0,	/* FC_RP */
/* 7860 */	NdrFcShort( 0xe1e8 ),	/* Offset= -7704 (156) */
/* 7862 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7864 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 7866 */	NdrFcShort( 0xe152 ),	/* Offset= -7854 (12) */
/* 7868 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 7870 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 7872 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7874) */
/* 7874 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7876 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 7878 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7880 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7882 */	0x0 , 
			0x0,		/* 0 */
/* 7884 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7888 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7892 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7894) */
/* 7894 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7896 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7898 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7902 */	NdrFcShort( 0xefa4 ),	/* Offset= -4188 (3714) */
/* 7904 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7903) */
/* 7906 */	
			0x11, 0x0,	/* FC_RP */
/* 7908 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7910) */
/* 7910 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7912 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 7914 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7916 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7918 */	0x0 , 
			0x0,		/* 0 */
/* 7920 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7924 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7928 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7930) */
/* 7930 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7932 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7934 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7938 */	NdrFcShort( 0x4 ),	/* Offset= 4 (7942) */
/* 7940 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7939) */
/* 7942 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 7944 */	NdrFcShort( 0x18 ),	/* 24 */
/* 7946 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 7948 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 7950 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7952 */	NdrFcShort( 0x14 ),	/* 20 */
/* 7954 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 7956 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 7958 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 7960 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 7962 */	NdrFcShort( 0xe0f2 ),	/* Offset= -7950 (12) */
/* 7964 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 7966 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 7968 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7970) */
/* 7970 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 7972 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 7974 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7976 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 7978 */	0x0 , 
			0x0,		/* 0 */
/* 7980 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7984 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7988 */	NdrFcShort( 0x2 ),	/* Offset= 2 (7990) */
/* 7990 */	NdrFcShort( 0xc ),	/* 12 */
/* 7992 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7994 */	NdrFcLong( 0x1 ),	/* 1 */
/* 7998 */	NdrFcShort( 0x4 ),	/* Offset= 4 (8002) */
/* 8000 */	NdrFcShort( 0xffff ),	/* Offset= -1 (7999) */
/* 8002 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 8004 */	NdrFcShort( 0xc ),	/* 12 */
/* 8006 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 8008 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 8010 */	
			0x11, 0x0,	/* FC_RP */
/* 8012 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8014) */
/* 8014 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8016 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 8018 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8020 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8022 */	0x0 , 
			0x0,		/* 0 */
/* 8024 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8028 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8032 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8034) */
/* 8034 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8036 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8038 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8042 */	NdrFcShort( 0x4 ),	/* Offset= 4 (8046) */
/* 8044 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8043) */
/* 8046 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 8048 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8050 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 8052 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8058 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 8060 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 8062 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8064 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8066 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8068 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 8070 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 8072 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 8074 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 8076 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 8078 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8080) */
/* 8080 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8082 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 8084 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8086 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8088 */	0x0 , 
			0x0,		/* 0 */
/* 8090 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8094 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8098 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8100) */
/* 8100 */	NdrFcShort( 0x10 ),	/* 16 */
/* 8102 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8104 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8108 */	NdrFcShort( 0x1a ),	/* Offset= 26 (8134) */
/* 8110 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8109) */
/* 8112 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 8114 */	NdrFcShort( 0x2 ),	/* 2 */
/* 8116 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 8118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8120 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 8122 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 8124 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8128 */	NdrFcLong( 0x400 ),	/* 1024 */
/* 8132 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 8134 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 8136 */	NdrFcShort( 0x10 ),	/* 16 */
/* 8138 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 8140 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8146 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 8148 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 8150 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8152 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8154 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8156 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 8158 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 8160 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8162 */	NdrFcShort( 0xc ),	/* 12 */
/* 8164 */	NdrFcShort( 0xc ),	/* 12 */
/* 8166 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 8168 */	NdrFcShort( 0xffc8 ),	/* Offset= -56 (8112) */
/* 8170 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 8172 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 8174 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 8176 */	
			0x11, 0x0,	/* FC_RP */
/* 8178 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8180) */
/* 8180 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8182 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 8184 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8186 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8188 */	0x0 , 
			0x0,		/* 0 */
/* 8190 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8194 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8198 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8200) */
/* 8200 */	NdrFcShort( 0xc ),	/* 12 */
/* 8202 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8204 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8208 */	NdrFcShort( 0x1a ),	/* Offset= 26 (8234) */
/* 8210 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8209) */
/* 8212 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 8214 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8216 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 8218 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8220 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 8222 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 8224 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8228 */	NdrFcLong( 0xffff ),	/* 65535 */
/* 8232 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 8234 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 8236 */	NdrFcShort( 0xc ),	/* 12 */
/* 8238 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 8240 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8246 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 8248 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 8250 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8252 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8254 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8256 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 8258 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (8212) */
/* 8260 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 8262 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 8264 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 8266 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 8268 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8270) */
/* 8270 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8272 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 8274 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8276 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8278 */	0x0 , 
			0x0,		/* 0 */
/* 8280 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8284 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8288 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8290) */
/* 8290 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8292 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8294 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8298 */	NdrFcShort( 0xee18 ),	/* Offset= -4584 (3714) */
/* 8300 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8299) */
/* 8302 */	
			0x11, 0x0,	/* FC_RP */
/* 8304 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8306) */
/* 8306 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8308 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 8310 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8312 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8314 */	0x0 , 
			0x0,		/* 0 */
/* 8316 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8320 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8324 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8326) */
/* 8326 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8328 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8330 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8334 */	NdrFcShort( 0xee86 ),	/* Offset= -4474 (3860) */
/* 8336 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8335) */
/* 8338 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 8340 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8342) */
/* 8342 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8344 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 8346 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8348 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8350 */	0x0 , 
			0x0,		/* 0 */
/* 8352 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8356 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8360 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8362) */
/* 8362 */	NdrFcShort( 0xc ),	/* 12 */
/* 8364 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8366 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8370 */	NdrFcShort( 0x4 ),	/* Offset= 4 (8374) */
/* 8372 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8371) */
/* 8374 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 8376 */	NdrFcShort( 0xc ),	/* 12 */
/* 8378 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 8380 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8382 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8384 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8386 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 8388 */	NdrFcShort( 0xff50 ),	/* Offset= -176 (8212) */
/* 8390 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 8392 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 8394 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 8396 */	
			0x11, 0x0,	/* FC_RP */
/* 8398 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8400) */
/* 8400 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8402 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 8404 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8406 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8408 */	0x0 , 
			0x0,		/* 0 */
/* 8410 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8414 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8418 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8420) */
/* 8420 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8422 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8424 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8428 */	NdrFcShort( 0xed96 ),	/* Offset= -4714 (3714) */
/* 8430 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8429) */
/* 8432 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 8434 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8436) */
/* 8436 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8438 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 8440 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8442 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8444 */	0x0 , 
			0x0,		/* 0 */
/* 8446 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8450 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8454 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8456) */
/* 8456 */	NdrFcShort( 0x20 ),	/* 32 */
/* 8458 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8460 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8464 */	NdrFcShort( 0x46 ),	/* Offset= 70 (8534) */
/* 8466 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8465) */
/* 8468 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 8470 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8472 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 8474 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8476 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 8478 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 8480 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8484 */	NdrFcLong( 0x400 ),	/* 1024 */
/* 8488 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 8490 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 8492 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8494 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 8496 */	NdrFcShort( 0x10 ),	/* 16 */
/* 8498 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 8500 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 8502 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8506 */	NdrFcLong( 0xa00000 ),	/* 10485760 */
/* 8510 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 8512 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 8514 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8516 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 8518 */	NdrFcShort( 0x18 ),	/* 24 */
/* 8520 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 8522 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 8524 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8528 */	NdrFcLong( 0xa00000 ),	/* 10485760 */
/* 8532 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 8534 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 8536 */	NdrFcShort( 0x20 ),	/* 32 */
/* 8538 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 8540 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8542 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8544 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8546 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 8548 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 8550 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8552 */	NdrFcShort( 0xc ),	/* 12 */
/* 8554 */	NdrFcShort( 0xc ),	/* 12 */
/* 8556 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 8558 */	NdrFcShort( 0xffa6 ),	/* Offset= -90 (8468) */
/* 8560 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8562 */	NdrFcShort( 0x14 ),	/* 20 */
/* 8564 */	NdrFcShort( 0x14 ),	/* 20 */
/* 8566 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 8568 */	NdrFcShort( 0xffb2 ),	/* Offset= -78 (8490) */
/* 8570 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8572 */	NdrFcShort( 0x1c ),	/* 28 */
/* 8574 */	NdrFcShort( 0x1c ),	/* 28 */
/* 8576 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 8578 */	NdrFcShort( 0xffbe ),	/* Offset= -66 (8512) */
/* 8580 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 8582 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 8584 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 8586 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 8588 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 8590 */	
			0x11, 0x0,	/* FC_RP */
/* 8592 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8594) */
/* 8594 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8596 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 8598 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8600 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8602 */	0x0 , 
			0x0,		/* 0 */
/* 8604 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8608 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8612 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8614) */
/* 8614 */	NdrFcShort( 0xc ),	/* 12 */
/* 8616 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8618 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8622 */	NdrFcShort( 0x1a ),	/* Offset= 26 (8648) */
/* 8624 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8623) */
/* 8626 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 8628 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8630 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 8632 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8634 */	NdrFcShort( 0x11 ),	/* Corr flags:  early, */
/* 8636 */	0x1 , /* correlation range */
			0x0,		/* 0 */
/* 8638 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8642 */	NdrFcLong( 0x400 ),	/* 1024 */
/* 8646 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 8648 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 8650 */	NdrFcShort( 0xc ),	/* 12 */
/* 8652 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 8654 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8656 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8658 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8660 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 8662 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (8626) */
/* 8664 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 8666 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 8668 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 8670 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 8672 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8674) */
/* 8674 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 8676 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 8678 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8680 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 8682 */	0x0 , 
			0x0,		/* 0 */
/* 8684 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8688 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8692 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8694) */
/* 8694 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8696 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8698 */	NdrFcLong( 0x1 ),	/* 1 */
/* 8702 */	NdrFcShort( 0x4 ),	/* Offset= 4 (8706) */
/* 8704 */	NdrFcShort( 0xffff ),	/* Offset= -1 (8703) */
/* 8706 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 8708 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8710 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 8712 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 8714 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8716 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8718 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 8720 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 8722 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 8724 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */

			0x0
        }
    };

static const unsigned short drsuapi_FormatStringOffsetTable[] =
    {
    0,
    58,
    100,
    154,
    220,
    274,
    328,
    382,
    436,
    502,
    568,
    634,
    700,
    766,
    832,
    898,
    964,
    1030,
    1096,
    1150,
    1216,
    1282,
    1348,
    1402,
    1468,
    1534,
    1600,
    1666,
    1732,
    1798,
    1864
    };


static const MIDL_STUB_DESC drsuapi_StubDesc = 
    {
    (void *)& drsuapi___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &drsuapi__MIDL_AutoBindHandle,
    0,
    0,
    0,
    0,
    ms2Ddrsr__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

static const unsigned short dsaop_FormatStringOffsetTable[] =
    {
    1930,
    1988
    };


static const MIDL_STUB_DESC dsaop_StubDesc = 
    {
    (void *)& dsaop___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &dsaop__MIDL_AutoBindHandle,
    0,
    0,
    0,
    0,
    ms2Ddrsr__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

