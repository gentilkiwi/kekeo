/*****************************************************************************/
/* Copyright (C) 2013 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.                    */
/* AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.             */
/* THIS FILE MAY NOT BE DISTRIBUTED.                                         */
/*****************************************************************************/
/* FILE: @(#)ossasn1.hh	16.140  13/02/25                                     */
/*****************************************************************************/


/*****************************************************************************/
/*  NON-PUBLIC section: common includes etc.                                 */
/*****************************************************************************/


#if !defined(OSSASN1_H)


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include <limits.h>
#include <setjmp.h>


/*****************************************************************************/
/*  PUBLIC section: platform-specific constants                              */
/*****************************************************************************/

#ifdef __BORLANDC__
#undef FLT_MAX
#undef DBL_MAX
#include <values.h>
#define FLT_MAX MAXFLOAT
#define DBL_MAX MAXDOUBLE
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif

#ifndef DBL_MAX
#ifdef  HUGE_VAL
#define DBL_MAX HUGE_VAL
#else
#ifdef  HUGE
#define DBL_MAX HUGE
#endif
#endif
#endif
#ifndef FLT_MAX
#define FLT_MAX DBL_MAX
#endif

#ifndef FLT_RADIX
#ifdef  u370
#define FLT_RADIX 16
#else
#define FLT_RADIX 2
#endif
#endif

#ifndef OSS_NAN_PRESENT
#define OSS_NAN_PRESENT
#define OSS_NAN_DOUBLE "\x00\x00\x00\x00\x00\x00\xf8\xff"
#define OSS_NAN_FLOAT "\x00\x00\xc0\xff"
#endif

#ifndef OSS_MINUS_ZERO_PRESENT
#define OSS_MINUS_ZERO_PRESENT
#define OSS_MINUS_ZERO_DOUBLE "\x00\x00\x00\x00\x00\x00\x00\x80"
#define OSS_MINUS_ZERO_FLOAT "\x00\x00\x00\x80"
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

/*****************************************************************************/
/*  PUBLIC section: type definitions used in the compiler-generated .h file  */
/*****************************************************************************/


#ifndef OSS_INT16
#define OSS_INT16 short
#endif

#define OSS_UINT16 unsigned OSS_INT16

#ifndef OSS_INT32
#define OSS_INT32 int
#endif

#ifndef OSSNAS_H
#define OSS_UINT32 unsigned OSS_INT32
typedef char ossBoolean;
#endif

#if !defined(__cplusplus) && !defined(_union)
#define _union
#endif

#ifndef LONG_LONG
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define LONG_LONG __int64
#define LLONG_FMT "%I64d"
#elif defined(__IBMC__)
#define LONG_LONG long long
#define LLONG_FMT "%lld"
#else
#define LONG_LONG long
#define LLONG_FMT "%ld"
#endif
#endif

#ifndef ULONG_LONG
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define ULONG_LONG unsigned __int64
#define ULLONG_FMT "%I64u"
#elif defined(__IBMC__)
#define ULONG_LONG unsigned long long
#define ULLONG_FMT "%llu"
#else
#define ULONG_LONG unsigned long
#define ULLONG_FMT "%lu"
#endif
#endif

#ifndef LLONG_MAX
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define LLONG_MAX _I64_MAX
#elif defined(__IBMC__)
#define LLONG_MAX LONGLONG_MAX
#else
#define LLONG_MAX LONG_MAX
#endif
#endif

#ifndef LLONG_MIN
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define LLONG_MIN _I64_MIN
#elif defined(__IBMC__)
#define LLONG_MIN LONGLONG_MIN
#else
#define LLONG_MIN LONG_MIN
#endif
#endif

#ifndef ULLONG_MAX
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define ULLONG_MAX _UI64_MAX
#elif defined(__IBMC__)
#define ULLONG_MAX ULONGLONG_MAX
#else
#define ULLONG_MAX ULONG_MAX
#endif
#endif

#ifndef LLONG_MIN
#define LLONG_MIN (-2147483647i64-1i64)
#endif
#ifndef LLONG_MAX
#define LLONG_MAX (2147483647i64)
#endif
#ifndef ULLONG_MAX
#define ULLONG_MAX (4294967295ui64)
#endif

#ifndef OSS_PTR_MAX
#define OSS_PTR_MAX ((char*)UINT_MAX)
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef _NULLTYPE_
#define _NULLTYPE_
typedef char Nulltype;
#endif

typedef struct {
  short          year;         /* YYYY format when used for GeneralizedTime */
                               /* YY format when used for UTCTime */
  short          month;
  short          day;
  short          hour;
  short          minute;
  short          second;
  short          millisec;
  short          mindiff;      /* UTC +/- minute differential     */  
  ossBoolean     utc;          /* TRUE means UTC time             */  
} GeneralizedTime; 

typedef GeneralizedTime UTCTime;

typedef struct {
  int            pduNum;
  long           length;       /* length of encoded */
  void          *encoded;
  void          *decoded;
#ifdef OSS_OPENTYPE_HAS_USERFIELD
  void          *userField;
#endif
} OpenType;

typedef struct {
  int            pduNum;
  long           length;       /* length of encoded */
  void          *encoded;
  void          *decoded;
  unsigned long  byteOffset;
  unsigned short bitOffset;    /* Used only for PER */
  unsigned short residualBits; /* Used only for PER */
#ifdef OSS_OPENTYPE_HAS_USERFIELD
  void          *userField;
#endif /* OSS_OPENTYPE_HAS_USERFIELD */
} OpenTypeExtended;

enum MixedReal_kind {OSS_BINARY, OSS_DECIMAL};

typedef struct {
  enum MixedReal_kind kind;
  union {
      double base2;
      char  *base10;
  } u;
} MixedReal;

typedef struct ObjectSetEntry {
  struct ObjectSetEntry *next;
  void                  *object;
  struct ObjectSetEntry *prev;
  char                  *object_name;
} ObjectSetEntry;


/* open type structure for ASN.1/C++ */
typedef struct {
    int		pduNum;
    long	length;
    void       *encoded;
    void       *decoded;
    void       *cppPointer;
} OpenTypeCPP;

/*****************************************************************************/
/*  PUBLIC section: type definitions supported by LEAN                       */
/*****************************************************************************/
#define OSS_UINT16_MAX  65535
#define OSS_UINT32_MAX  UINT_MAX
#define OSS_INT32_MAX   2147483647
#define OSS_INT32_MIN   (-2147483647 - 1)
#define OSS_INT64       LONG_LONG
#define OSS_UINT64      ULONG_LONG
#define OSS_INT64_MAX   LLONG_MAX
#define OSS_INT64_MIN   LLONG_MIN
#define OSS_UINT64_MAX  ULLONG_MAX
#define OSS_LENGTH_MAX  OSS_UINT32_MAX
#define OSS_FLOAT_MAX   DBL_MAX
#define OSS_FLOAT_MIN   DBL_MIN
#define OSS_FLOAT_PRINT_FORMAT OSS_DBL_FMT

typedef OSS_UINT32 OSS_LENGTH;

typedef OSS_INT32  OSS_ENUM;

typedef OSS_UINT32 OSS_UENUM;

typedef double     ossReal;
#ifndef OSSNAS_H
typedef struct ossBitString {
    OSS_UINT32     length; /* number of significant bits */
    unsigned char  *value;
} ossBitString;

typedef struct ossOctetString {
    OSS_UINT32     length;
    unsigned char  *value;
} ossOctetString;

typedef struct ossCharString {
    OSS_UINT32     length;
    char           *value;
} ossCharString;
#endif /* !OSSNAS_H */
typedef struct ossBMPString {
    OSS_UINT32     length;
    OSS_UINT16     *value;
} ossBMPString;

typedef struct ossUniversalString {
    OSS_UINT32     length;
    OSS_INT32      *value;
} ossUniversalString;

typedef struct ossContentsConstr {
    ossOctetString encoded;
    void	   *decoded;	
} ossContentsConstr;

typedef struct ossHugeInt {
    OSS_UINT32     length;
    unsigned char  *value;
} ossHugeInt;

typedef struct ossObjectID {
    OSS_UINT32     length;
    unsigned char  *value;
} ossObjectID;
typedef struct ossAny {
    OSS_UINT32     length;
    unsigned char  *value;
} ossAny;

/* struct ossExtensions keeps unknown extension additions for -relaySafe *
 * in case of extensible SET or SEQUENCE                                  */

#define ossExtensionsDefined
#define _ossExtMask      ossBitString
#define _ossExtension    ossOctetString
#define _ossAltExtension ossOctetString

#ifndef __cplusplus
#define ossExtensions_ ossExtensions
#endif

typedef struct ossExtensions_ {
    _ossExtMask      extMask;
    struct _ossExtList {
	OSS_UINT32       count;
	_ossExtension    *value;
    } extList;
} *ossExtensions;

/* struct ossExtAlternative keeps unknown extension additions for -relaySafe *
 * in case of extensible CHOICE                                              */

#define ossExtAlternativeDefined

typedef struct ossExtAlternative {
    OSS_UINT32       idx;
    _ossAltExtension data;
} ossExtAlternative;

/*****************************************************************************/
/*  PUBLIC section: OSS encoding rules                                       */
/*****************************************************************************/

#ifndef OSSNAS_H
typedef enum  {
    OSS_BER = 0,
    OSS_PER_ALIGNED,
    OSS_PER_UNALIGNED,
    OSS_DER,
    OSS_ECN,
    OSS_XER,
    OSS_CXER,
    OSS_CER,
    OSS_EXER
    , OSS_OER
} ossEncodingRules;
#endif /* !OSSNAS_H */

/*****************************************************************************/
/*  NON-PUBLIC section: data alignment section for platforms with multiple   */
/*  alignment options (OSS data structures should use the same setting as    */
/*  OSS runtime does)                                                        */
/*****************************************************************************/

#ifdef macintosh
#pragma options align=mac68k
#endif
#if defined(_MSC_VER) && (defined(WINCE) || defined(_WIN64))
#pragma pack(push, ossPacking, 8)
#elif defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32))
#pragma pack(push, ossPacking, 4)
#elif defined(_MSC_VER) && (defined(_WINDOWS) || defined(_MSDOS))
#pragma pack(1)
#elif defined(__BORLANDC__) && defined(__MSDOS__)
#ifdef _BC31
#pragma option -a-
#else
#pragma option -a1
#endif /* _BC31 */
#elif defined(__BORLANDC__) && defined(__WIN32__)
#pragma option -a4
#elif defined(__IBMC__) && defined(__WIN32__)
#pragma pack(4)
#elif defined(__WATCOMC__) && defined(__NT__)
#pragma pack(push, 4)
#elif defined(__WATCOMC__) && (defined(__WINDOWS__) || defined(__DOS__))
#pragma pack(push, 1)
#endif /* _MSC_VER && (WINCE || _WIN64) */

#if defined(macintosh) && defined(__CFM68K__)
#pragma import on
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/*  NON-PUBLIC section: DLL definitions (users may skip them)                */
/*****************************************************************************/


#undef DLL_LINKAGE
#undef SERIALIZE_GLOBAL_ACCESS
#undef CDECL_ENTRY
#undef CDECL_ENTRY_FDEF
#undef CDECL_ENTRY_FPTR
#define CDECL_ENTRY
#define CDECL_ENTRY_FDEF
#define CDECL_ENTRY_FPTR

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__)

#if defined(_DLL) && !defined(ONE_DLL) && !defined(WIN32_DRIVER) && \
    !defined(OSS_SOED_BER) && !defined(OSS_SOED_PER) && \
    !defined(OSS_SOED_XER) && !defined(OSS_SOED_EXER) && \
    !defined(_OSS_CODE_FILE) && !defined(_OSS_CONTROL_FILE)
#define DLL_LINKAGE
#endif /* _DLL && !ONE_DLL && ... */

#if !defined(WIN32_SIMPLE)
#define SERIALIZE_GLOBAL_ACCESS
#endif 

typedef struct memblock MEMBLOCK;

#include <stdarg.h>
#if !defined(WIN32_SIMPLE) && !defined(_NTSDK)
#include <windows.h>
#endif

#ifndef OSSNAS_H
#ifndef DLL_ENTRY
#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
#ifdef __BORLANDC__
#if defined(__cplusplus) && defined(_DLL) && !defined(ONE_DLL)
#define PUBLIC         __declspec(dllimport)
#else
#define PUBLIC
#endif /* __cplusplus && _DLL && !ONE_DLL */
#define DLL_ENTRY      __stdcall
#define DLL_ENTRY_FDEF __stdcall
#define DLL_ENTRY_FPTR __stdcall
#ifndef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA  __declspec(dllexport)
#endif /* OSS_EXPORT_DLL_DATA */
#elif defined(__IBMC__)
#define PUBLIC
#define DLL_ENTRY      WINAPI
#define DLL_ENTRY_FDEF WINAPI __export
#define DLL_ENTRY_FPTR WINAPI
#elif defined(__WATCOMC__)
#define PUBLIC
#define DLL_ENTRY      WINAPI __export
#define DLL_ENTRY_FDEF WINAPI __export
#define DLL_ENTRY_FPTR WINAPI __export
#ifndef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA  __declspec(dllexport)
#endif /* OSS_EXPORT_DLL_DATA */
#elif defined(_NTSDK)
typedef int            BOOL;
typedef void *         HWND;
typedef void *         HINSTANCE;
typedef long           LONG;
#define PUBLIC         __declspec(dllexport)
#define DLL_ENTRY
#define DLL_ENTRY_FDEF
#define DLL_ENTRY_FPTR
#ifndef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA
#endif /* OSS_EXPORT_DLL_DATA */
#else
#ifdef WIN32_SIMPLE
#include <ril.h>
typedef void *         HWND;
typedef void *         HINSTANCE;
typedef long           LONG;
#define WINAPI __stdcall
#undef PUBLIC
#endif /* WIN32_SIMPLE */
#if defined(__cplusplus) && defined(_DLL) && !defined(ONE_DLL)
#define PUBLIC         __declspec(dllimport)
#else
#define PUBLIC
#endif /* __cplusplus && _DLL && !ONE_DLL */

#undef CDECL_ENTRY     
#undef CDECL_ENTRY_FDEF
#undef CDECL_ENTRY_FPTR
#define CDECL_ENTRY      __cdecl
#define CDECL_ENTRY_FDEF __cdecl
#define CDECL_ENTRY_FPTR __cdecl

#define DLL_ENTRY      WINAPI
#define DLL_ENTRY_FDEF WINAPI
#define DLL_ENTRY_FPTR WINAPI
#ifndef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA __declspec(dllexport)
#endif /* OSS_EXPORT_DLL_DATA */
#endif /* __BORLANDC__ */
#define _System
#elif defined(_WINDOWS)
#define PUBLIC
#undef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA
#ifdef DPMI_DLL
#define DLL_ENTRY      FAR PASCAL __export
#define DLL_ENTRY_FDEF FAR PASCAL __export
#define DLL_ENTRY_FPTR FAR PASCAL __export
#else
#define DLL_ENTRY      far pascal _export
#define DLL_ENTRY_FDEF far pascal _export
#define DLL_ENTRY_FPTR far pascal _export
#endif /* DPMI_DLL */
#define _System
#endif /* _WIN32 || WIN32 || __WIN32__ */
#endif /* DLL_ENTRY */
#endif /* !OSSNAS_H */
#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ */

#if defined(_WINDOWS) || defined(_WIN32)

/* The structure "functionTables" is used to store DLL-related information. */
typedef struct functionTables {
    HWND        hWnd;           /* Handle of the window */
    LONG        index;          /* Current index into the file pointer array;
				 * it indicates the number of lines written */
    MEMBLOCK   *memBlock;       /* Pointer to a current node of a memory
				 * handling linked list of MEMBLOCKs */
    MEMBLOCK   *startBlock;     /* Pointer to the first node of a memory
				 * handling linked list of MEMBLOCKs */
    short       length;         /* Length of a line that is written only
				 * in part and no '\n' symbol was reached yet */
    short       blockNumber;    /* Current MEMBLOCK number */
    FILE       *tmpfp;          /* Temporary output file with tracing info */
    char        tmpfn[16];      /* Temporary output file name */
    BOOL        endSwitch;      /* Indicates if a '\n' symbol was reached or
				 * not when writing a tracing info file to
				 * a window */
    BOOL        conSwitch;      /* If FALSE, the output goes to a console,
				 * otherwise to a window */
    BOOL	ossEncoderDecoderType; /* SOED vs. TOED */
    BOOL	cstrainNeeded;  /* If TRUE, constraint checking is needed */
    void       *cstrainTbl;     /* Constraint checker DLL function table */
    void       *berTbl;         /* BER & DER DLL function table */
    void       *perTbl;         /* PER DLL function table */
    void       *apiTbl;         /* API DLL function table */
    void       *cpyvalTbl;      /* Value copier DLL function table */
    void       *cmpvalTbl;      /* Value comparator DLL function table */
    void       *berrealTbl;     /* BER/DER encoder/decoder real DLL function
				 * table */
    void       *berpdvTbl;      /* PER encoder/decoder EMBEDDED PDV DLL
				 * function table */
    void       *perrealTbl;     /* PER encoder/decoder real DLL function table */
    void       *perpdvTbl;      /* BER encoder/decoder EMBEDDED PDV DLL
				 * function table */
    void       *oidTbl;         /* OBJECT IDENTIFIER converter DLL
				 * function table */
    HINSTANCE   hBerDLL;        /* Handle of BER/DER encoder/decoder DLL */
    HINSTANCE   hPerDLL;        /* Handle of PER DLL */
    HINSTANCE   hCtlDLL;        /* Handle of control table/code file DLL */
    HINSTANCE   hMemDLL;        /* Handle of memory manager DLL */
    HINSTANCE   hCstrainDLL;    /* Handle of constraint checker DLL */
    HINSTANCE   hApiDLL;        /* Handle of API DLL */
    HINSTANCE   hCpyvalDLL;     /* Handle of value copier DLL */
    HINSTANCE   hCmpvalDLL;     /* Handle of value comparator DLL */
    HINSTANCE   hBerrealDLL;    /* Handle of BER/DER encoder/decoder real DLL */
    HINSTANCE   hBerpdvDLL;     /* Handle of BER encoder/decoder EMBEDDED PDV
				 * DLL */
    HINSTANCE   hPerrealDLL;    /* Handle of PER encoder/decoder real DLL */
    HINSTANCE   hPerpdvDLL;     /* Handle of PER encoder/decoder EMBEDDED PDV
				 * DLL */
    HINSTANCE   hOidDLL;        /* Handle of OBJID converter DLL */
    struct memManagerTbl *memMgrTbl; /* Memory manager DLL function table */
    void       *xerTbl;        /* XER & CXER DLL function table */
    HINSTANCE   hXerDLL;        /* Handle of XER/CXER encoder/decoder DLL */
    void       *exerTbl;       /* EXER function table */
    void       *reserved[7];    /* Reserved for possible future use */
} FunctionTables;
#elif !defined(DLL_ENTRY) /* _WINDOWS || _WIN32 */

#include <stdarg.h>
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#define DLL_ENTRY      WINAPI
#define DLL_ENTRY_FDEF WINAPI
#define DLL_ENTRY_FPTR WINAPI
#elif defined(__WATCOMC__) && defined(__DOS__)
#define DLL_ENTRY __cdecl
#define DLL_ENTRY_FDEF __cdecl
#define DLL_ENTRY_FPTR __cdecl
#define PUBLIC
#else
#define DLL_ENTRY
#define DLL_ENTRY_FDEF
#define DLL_ENTRY_FPTR
#define PUBLIC
#undef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA
#endif /* _WIN32 || WIN32 */
#undef  _System
#define _System

#endif /* _WINDOWS || _WIN32 */

/*****************************************************************************/
/*  PUBLIC section: auxiliary data structures used by OSS API functions      */
/*****************************************************************************/

/* Common function pointer */
typedef void (CDECL_ENTRY_FPTR *OssStubFuncp)(void);

#ifndef ERR_MSG_LENGTH 
#define ERR_MSG_LENGTH 512      /* length of error messages to be output */
#endif 

typedef enum  {
    OSS_BASIC = 0,
    OSS_SPARTAN
} OssAPI;

#ifndef OSSNAS_H
typedef struct {
    long           length;
    unsigned char *value;
} OssBuf;
#endif /* !OSSNAS_H */
typedef struct {
    long           length;
    unsigned char *value; 
    long           byteOffset;
} OssBufExtended;

/*****************************************************************************/
/* Definitions of the ISO 8601 time API structures                           */
/*****************************************************************************/

typedef struct ossTimePoint {
    unsigned short  bit_mask;
#       define      OSS_tp_centuries_present 0x8000
#       define      OSS_tp_years_present 0x4000
#       define      OSS_tp_weeks_present 0x2000
#       define      OSS_tp_months_present 0x1000
#       define      OSS_tp_days_present 0x0800
#       define      OSS_tp_hours_present 0x0400
#       define      OSS_tp_minutes_present 0x0200
#       define      OSS_tp_seconds_present 0x0100
#       define      OSS_tp_utc_present 0x0080
#       define      OSS_tp_fractional_part_present 0x0040
#       define      OSS_tp_time_diff_present 0x0020
    int centuries;  /* optional; set in bit_mask OSS_tp_centuries_present
    		     * if present */
    int years;  /* optional; set in bit_mask OSS_tp_years_present if
    		 * present */
    unsigned short weeks;  /* optional; set in bit_mask OSS_tp_weeks_present if
                	    * present */
    unsigned short months; /* optional; set in bit_mask OSS_tp_months_present if
            		    * present */
    unsigned short days;   /* optional; set in bit_mask OSS_tp_days_present if
                	    * present */
    unsigned short hours;  /* optional; set in bit_mask OSS_tp_hours_present if
			    * present */
    unsigned short minutes; /* optional; set in bit_mask
            		     *  OSS_tp_minutes_present if present */
    unsigned short seconds; /* optional; set in bit_mask OSS_tp_seconds_present if
            		     * present */
    Nulltype utc; /* optional; set in bit_mask OSS_tp_utc_present if present */
    struct {
        unsigned int number_of_digits;
        unsigned int fractional_value;
    } fractional_part; /* optional; set in bit_mask OSS_tp_fractional_part_present if
			* present */
    struct {
	unsigned char bit_mask;
#           define      OSS_tp_time_diff_minutes_present 0x80
	unsigned short hours;
	unsigned short minutes;  /* optional; set in bit_mask
				  * OSS_tp_time_diff_minutes_present if present */
	ossBoolean     isNegative; 
    } time_diff; /* optional; set in bit_mask OSS_tp_time_diff_present if present */
} ossTimePoint;

/* gets "centuries" field value */
#define oss_TimePoint_centuries_get(inp) \
    ((inp)->centuries)

/* sets "centuries" field value */
#define ossTimePoint_centuries_set(outp, centuries_) \
    { \
	(outp)->bit_mask |= OSS_tp_centuries_present; \
	(outp)->centuries = (centuries_); \
    }

/* checks if "centuries" field value is present */
#define ossTimePoint_centuries_is_present(inp) \
    ((inp)->bit_mask & OSS_tp_centuries_present)

/* indicates that "centuries" field value is absent */
#define ossTimePoint_centuries_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_centuries_present)

/* gets "years" field value */
#define ossTimePoint_years_get(inp) \
    ((inp)->years)

/* sets "years" field value */
#define ossTimePoint_years_set(outp, years_) \
    { \
	(outp)->bit_mask |= OSS_tp_years_present; \
	(outp)->years = (years_); \
    }

/* checks if "years" field value is present */
#define ossTimePoint_years_is_present(inp) \
    ((inp)->bit_mask & OSS_tp__years_present)

/* indicates that "years" field value is absent */
#define ossTimePoint_years_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_years_present)

/* gets "weeks" field value */
#define ossTimePoint_weeks_get(inp) \
    ((inp)->weeks)

/* sets "weeks" field value */
#define ossTimePoint_weeks_set(outp, weeks_) \
    { \
	(outp)->bit_mask |= OSS_tp_weeks_present; \
	(outp)->weeks = (weeks_); \
    }

/* checks if "weeks" field value is present */
#define ossTimePoint_weeks_is_present(inp) \
    ((inp)->bit_mask & OSS_tp_weeks_present)

/* indicates that "weeks" field value is absent */
#define ossTimePoint_weeks_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_weeks_present)

/* gets "months" field value */
#define ossTimePoint_months_get(inp) \
    ((inp)->months)

/* sets "months" field value */
#define ossTimePoint_months_set(outp, months_) \
    { \
	(outp)->bit_mask |= OSS_tp_months_present; \
	(outp)->months = (months_); \
    }

/* checks if "months" field value is present */
#define ossTimePoint_months_is_present(inp) \
    ((inp)->bit_mask & OSS_tp_months_present)

/* indicates that "months" field value is absent */
#define ossTimePoint_months_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_months_present)

/* gets "days" field value */
#define ossTimePoint_days_get(inp) \
    ((inp)->days)

/* sets "days" field value */
#define ossTimePoint_days_set(outp, days_) \
    { \
	(outp)->bit_mask |= OSS_tp_days_present; \
	(outp)->days = (days_); \
    }

/* checks if "days" field value is present */
#define ossTimePoint_days_is_present(inp) \
    ((inp)->bit_mask & OSS_tp_days_present)

/* indicates that "days" field value is absent */
#define ossTimePoint_days_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_days_present)

/* gets "hours" field value */
#define ossTimePoint_hours_get(inp) \
    ((inp)->hours)

/* sets "hours" field value */
#define ossTimePoint_hours_set(outp, hours_) \
    { \
	(outp)->bit_mask |= OSS_tp_hours_present; \
	(outp)->hours = (hours_); \
    }

/* checks if "hours" field value is present */
#define ossTimePoint_hours_is_present(inp) \
    ((inp)->bit_mask & OSS_tp_hours_present)

/* indicates that "hours" field value is absent */
#define ossTimePoint_hours_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_hours_present)

/* gets "minutes" field value */
#define ossTimePoint_minutes_get(inp) \
    ((inp)->minutes)

/* sets "minutes" field value */
#define ossTimePoint_minutes_set(outp, minutes_) \
    { \
	(outp)->bit_mask |= OSS_tp_minutes_present; \
	(outp)->minutes = (minutes_); \
    }

/* checks if "minutes" field value is present */
#define ossTimePoint_minutes_is_present(inp) \
    ((inp)->bit_mask & OSS_tp_minutes_present)

/* indicates that "minutes" field value is absent */
#define ossTimePoint_minutes_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_minutes_present)

/* gets "seconds" field value */
#define ossTimePoint_seconds_get(inp) \
    ((inp)->seconds)

/* sets "seconds" field value */
#define ossTimePoint_seconds_set(outp, seconds_) \
    { \
	(outp)->bit_mask |= OSS_tp_seconds_present; \
	(outp)->seconds = (seconds_); \
    }

/* checks if "seconds" field value is present */
#define ossTimePoint_seconds_is_present(inp) \
    ((inp)->bit_mask & OSS_tp_seconds_present)

/* indicates that "seconds" field value is absent */
#define ossTimePoint_seconds_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_seconds_present)

/* gets "utc" field value */
#define ossTimePoint_utc_get(inp) \
    ((inp)->utc)

/* sets "utc" field value */
#define ossTimePoint_utc_set(outp, utc_) \
    { \
	(outp)->bit_mask |= OSS_tp_utc_present; \
	(outp)->utc = (utc_); \
    }

/* checks if "utc" field value is present */
#define ossTimePoint_utc_is_present(inp) \
    ((inp)->bit_mask & OSS_tp_utc_present)

/* indicates that "utc" field value is absent */
#define ossTimePoint_utc_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_utc_present)

/* gets "fractional_part.fractional_value" field value */
#define ossTimePoint_fraction_value_get(inp) \
    ((inp)->fractional_part.fractional_value)

/* gets "fractional_part.number_of_digits" field value */
#define ossTimePoint_fraction_digits_get(inp) \
    ((inp)->fractional_part.number_of_digits)

/* sets "fractional_part" fields */
#define ossTimePoint_fraction_set(outp, fraction_, digits_) \
    { \
	(outp)->bit_mask |= OSS_tp_fractional_part_present; \
	(outp)->fractional_part.fractional_value = (fraction_); \
	(outp)->fractional_part.number_of_digits = (digits_); \
    }

/* sets "fractional_part.fractional_value" field value */
#define ossTimePoint_fraction_value_set(outp, fraction_) \
    { \
	(outp)->bit_mask |= OSS_tp_fractional_part_present; \
	(outp)->fractional_part.fractional_value = (fraction_); \
    }

/* sets "fractional_part.number_of_digits field value */
#define ossTimePoint_fraction_digits_set(outp, digits_) \
    { \
	(outp)->fractional_part.number_of_digits = (digits_); \
    }

/* checks if "fractional_part" field value is present */
#define ossTimePoint_fractional_part_is_present(inp) \
    ((inp)->bit_maske & OSS_tp_fractional_part_present)

/* indicates that "fractional_part" field value is absent */
#define ossTimePoint_fractional_part_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_fractional_part_present)

/* gets "time_diff.hours" field value */
#define ossTimePoint_time_diff_hours_get(inp) \
    ((inp)->time_diff.hours)

/* gets "time_diff.minutes" field value */
#define ossTimePoint_time_diff_minutes_get(inp) \
    ((inp)->time_diff.minutes)

/* sets "time_diff" fields */
#define ossTimePoint_time_diff_set(outp, hours_, minutes_, isNegative_) \
    { \
	(outp)->bit_mask |= OSS_tp_time_diff_present; \
	(outp)->time_diff.hours = (hours_); \
	(outp)->time_diff.bit_mask |= OSS_tp_time_diff_minutes_present; \
	(outp)->time_diff.minutes = (minutes_); \
	(outp)->time_diff.isNegative = (isNegative_); \
    }

/* sets "time_diff.hours" field value */
#define ossTimePoint_time_diff_hours_set(outp, hours_) \
    { \
	(outp)->bit_mask |= OSS_tp_time_diff_present; \
	(outp)->time_diff.hours = (hours_); \
    }

/* sets "time_diff.minutes" field value */
#define ossTimePoint_time_diff_minutes_set(outp, minutes_) \
    { \
	(outp)->bit_mask |= OSS_tp_time_diff_present; \
	(outp)->time_diff.bit_mask |= OSS_tp_time_diff_minutes_present; \
	(outp)->time_diff.minutes = (minutess_); \
    }

/* checks if "time_diff.minutes" field value is present */
#define ossTimePoint_time_diff_minutes_is_present(inp) \
    ((inp)->time_diff.bit_mask & OSS_tp_time_diff_minutes_present)

/* indicates that "time_diff.minutes" field value is absent */
#define ossTimePoint_time_diff_minutes_omit(inp) \
    ((inp)->time_diff.bit_mask &= ~OSS_tp_time_diff_minutes_present)

/* checks if "time_diff" field value is present */
#define ossTimePoint_time_diff_is_present(inp) \
    ((inp)->bit_mask & OSS_tp_time_diff_present)

/* indicates that "time_diff" field value is absent */
#define ossTimePoint_time_diff_omit(outp) \
    ((outp)->bit_mask &= ~OSS_tp_time_diff_present)

/* gets "get time_dif.isNegative" field value */
#define ossTimePoint_time_diff_isNegative_get(inp) \
    ((inp)->time_diff.isNegative)

/* sets "time_diff.isNegative" field value */
#define ossTimePoint_time_diff_isNegative_set(outp, isNegative_) \
    ((outp)->time_diff.isNegative = (isNegative_))

#define ossTimePoint_date_set(outp, years_, months_, days_) \
    {\
	ossTimePoint_years_set(outp, years_) \
	ossTimePoint_months_set(outp, months_) \
	ossTimePoint_days_set(outp, days_) \
    }

#define ossTimePoint_time_set(outp, hours_, minutes_, seconds_) \
    {\
	ossTimePoint_hours_set(outp, hours_) \
	ossTimePoint_minutes_set(outp, minutes_) \
	ossTimePoint_seconds_set(outp, seconds_) \
    }

typedef struct ossDuration { /* 8 bits for optionality */
    OSS_UINT32 bit_mask;
#       define      OSS_de_years_present 0x80000000
#       define      OSS_de_months_present 0x40000000
#       define      OSS_de_weeks_present 0x20000000
#       define      OSS_de_days_present 0x10000000
#       define      OSS_de_hours_present 0x08000000
#       define      OSS_de_minutes_present 0x04000000
#       define      OSS_de_seconds_present 0x02000000
#       define      OSS_de_fractional_part_present 0x01000000
    OSS_UINT32 years;   /* optional; set in bit_mask years_present if
                           * present */
    OSS_UINT32 months;  /* optional; set in bit_mask months_present if
                           * present */
    OSS_UINT32 weeks;   /* optional; set in bit_mask weeks_present if
                           * present */
    OSS_UINT32 days;    /* optional; set in bit_mask days_present if
                           * present */
    OSS_UINT32 hours;   /* optional; set in bit_mask hours_present if
                           * present */
    OSS_UINT32 minutes; /* optional; set in bit_mask minutes_present if
                           * present */
    OSS_UINT32 seconds; /* optional; set in bit_mask seconds_present if
                           * present */
    struct {
	OSS_UINT32 number_of_digits;
        OSS_UINT32 fractional_value;
    } fractional_part;  /* optional; set in bit_mask fractional_part_present if
			 * present */
} ossDuration;

/* gets "years" field value */
#define oss_Duration_years_get(inp) \
    ((inp)->years)

/* sets "years" field value */
#define oss_Duration_years_set(outp, years_) \
    { \
	(outp)->bit_mask |= OSS_de_years_present; \
	(outp)->years = (years_); \
    }

/* checks if "years" field value is present */
#define oss_Duration_years_is_present(inp) \
    ((inp)->bit_mask & OSS_de_years_present)

/* indicates that "years" field value is absent */
#define oss_Duration_years_omit(outp) \
    ((outp)->bit_mask &= ~OSS_de_years_present)

/* gets "months" field value */
#define oss_Duration_months_get(inp) \
    ((inp)->months)

/* sets "months" field value */
#define oss_Duration_months_set(outp, months_) \
    { \
	(outp)->bit_mask |= OSS_de_months_present; \
	(outp)->months = (months_); \
    }

/* checks if "months" field value is present */
#define oss_Duration_months_is_present(inp) \
    ((inp)->bit_mask & OSS_de_months_present)

/* indicates that "months" field value is absent */
#define oss_Duration_months_omit(outp) \
    ((outp)->bit_mask &= ~OSS_de_months_present)

/* gets "weeks" field value */
#define oss_Duration_weeks_get(inp) \
    ((inp)->weeks)

/* sets "weeks" field value */
#define oss_Duration_weeks_set(outp, weeks_) \
    { \
	(outp)->bit_mask |= OSS_de_weeks_present; \
	(outp)->weeks = (weeks_); \
    }

/* checks if "weeks" field value is present */
#define oss_Duration_weeks_is_present(inp) \
    ((inp)->bit_mask & OSS_de_weeks_present)

/* indicates that "weeks" field value is absent */
#define oss_Duration_weeks_omit(outp) \
    ((outp)->bit_mask &= ~OSS_de_weeks_present)

/* gets "days" field value */
#define oss_Duration_days_get(inp) \
    ((inp)->days)

/* sets "days" field value */
#define oss_Duration_days_set(outp, days_) \
    { \
	(outp)->bit_mask |= OSS_de_days_present; \
	(outp)->days = (days_); \
    }

/* checks if "days" field value is present */
#define oss_Duration_days_is_present(inp) \
    ((inp)->bit_mask & OSS_de_days_present)

/* indicates that "days" field value is absent */
#define oss_Duration_days_omit(outp) \
    ((outp)->bit_mask &= ~OSS_de_days_present)

/* gets "hours" field value */
#define oss_Duration_hours_get(inp) \
    ((inp)->hours)

/* sets "hours" field value */
#define oss_Duration_hours_set(outp, hours_) \
    { \
	(outp)->bit_mask |= OSS_de_hours_present; \
	(outp)->hours = (hours_); \
    }

/* checks if "hours" field value is present */
#define oss_Duration_hours_is_present(inp) \
    ((inp)->bit_mask & OSS_de_hours_present)

/* indicates that "hours" field value is absent */
#define oss_Duration_hours_omit(outp) \
    ((outp)->bit_mask &= ~OSS_de_hours_present)

/* gets "minutes" field value */
#define oss_Duration_minutes_get(inp) \
    ((inp)->minutes)

/* sets "minutes" field value */
#define oss_Duration_minutes_set(outp, minutes_) \
    { \
	(outp)->bit_mask |= OSS_de_minutes_present; \
	(outp)->minutes = (minutes_); \
    }

/* checks if "minutes" field value is present */
#define oss_Duration_minutes_is_present(inp) \
    ((inp)->bit_mask & OSS_de_minutes_present)

/* indicates that "minutes" field value is absent */
#define oss_Duration_minutes_omit(outp) \
    ((outp)->bit_mask &= ~OSS_de_minutes_present)

/* gets "seconds" field value */
#define oss_Duration_seconds_get(inp) \
    ((inp)->seconds)

/* sets "seconds" field value */
#define oss_Duration_seconds_set(outp, seconds_) \
    { \
	(outp)->bit_mask |= OSS_de_seconds_present; \
	(outp)->seconds = (seconds_); \
    }

/* checks if "seconds" field value is present */
#define oss_Duration_seconds_is_present(inp) \
    ((inp)->bit_mask & OSS_de_seconds_present)

/* indicates that "seconds" field value is absent */
#define oss_Duration_seconds_omit(outp) \
    ((outp)->bit_mask &= ~OSS_de_seconds_present)

/* gets "fractional_part.fractional_value" field value */
#define oss_Duration_fraction_value_get(inp) \
    ((inp)->fractional_part.fractional_value)

/* gets "fractional_part.number_of_digits" field value */
#define oss_Duration_fraction_digits_get(inp) \
    ((inp)->fractional_part.number_of_digits)

/* sets "fractional_part" fields */
#define oss_Duration_fraction_set(outp, fraction_, digits_) \
    { \
	(outp)->bit_mask |= OSS_de_fractional_part_present; \
	(outp)->fractional_part.fractional_value = (fraction_); \
	(outp)->fractional_part.number_of_digits = (digits_); \
    }

/* sets "fractional_part.fractional_value" field value */
#define oss_Duration_fraction_value_set(outp, fraction_) \
    { \
	(outp)->bit_mask |= OSS_de_fractional_part_present; \
	(outp)->fractional_part.fractional_value = (fraction_); \
    }

/* sets "fractional_part.number_of_digits field value */
#define oss_Duration_fraction_digits_set(outp, digits_) \
    { \
	(outp)->fractional_part.number_of_digits = (digits_); \
    }

/* checks if "fractional_part" field value is present */
#define oss_Duration_fractional_part_is_present(inp) \
    ((inp)->bit_maske & OSS_de_fractional_part_present)

/* indicates that "fractional_part" field value is absent */
#define oss_Duration_fractional_part_omit(outp) \
    ((outp)->bit_mask &= ~OSS_de_fractional_part_present)

typedef enum {
    oss_tk_TimePoint,
    oss_tk_DurationInterval,
    oss_tk_StartPointEndPointInterval,
    oss_tk_StartPointDurationInterval,
    oss_tk_DurationEndPointInterval,
    oss_tk_DurationRecInterval,
    oss_tk_StartPointEndPointRecInterval,
    oss_tk_StartPointDurationRecInterval,
    oss_tk_DurationEndPointRecInterval,
    oss_tk_BadTime
} ossTimeKind;
/* Runtime support for encoded OBJECT IDENTIFIERs */
typedef struct {
    unsigned short length;
    unsigned char *value;
} OssEncodedOID;

/* Runtime support for encoded RELATIVE-OID */
typedef OssEncodedOID OssEncodedRelOID;





/*****************************************************************************/
/*  PUBLIC section: ossGlobal structure (OSS environment variable). It is    */
/*  recommended to use accessor functions when working with ossGlobal.       */
/*****************************************************************************/


#ifndef ossMemMgrVarLen
#ifdef OS400
#define ossMemMgrVarLen 100
#define ossEncDecVarLen 500    /* The size of the
				  encDecVar array shouldn't be less than
				  the sizeof(world->c) since the latter
				  structure overlays encDecVar.  The same
				  is true for the ossMemMgrVar array since
				  it is overlaid by world->t */
#elif defined(WINDOWS_X64) || defined(_M_X64)
#define ossMemMgrVarLen 74 + 8	/* 74 for the largest world->t in the C++
				 * memory manager plus a slack of 8 */
#define ossEncDecVarLen 356 + 8 /* 356 to hold the largest TOED world->c plus
				 * a slack of 8 */
#elif defined(__vms) && (__INITIAL_POINTER_SIZE + 0) == 64  /* OpenVMS 64bit */
#define ossMemMgrVarLen 64 + 8	/* 64 for the largest world->t in the socket
				 * memory manager plus a slack of 8 */
#define ossEncDecVarLen 356 + 8 /* 356 to hold the largest TOED world->c plus
				 * a slack of 8 */
#else
#define ossMemMgrVarLen 48
#define ossEncDecVarLen 196     /* The size of the
				  encDecVar array shouldn't be less than
				  the sizeof(world->c) since the latter
				  structure overlays encDecVar */
#endif /* OS400 */
#endif /* ossMemMgrVarLen */

struct ossGlobal {
    /*
     * used for communicating with the memory manager and the tracing-routine
     */
				/* low-level memory allocator */
    void       *(DLL_ENTRY_FPTR *_System mallocp)(size_t p);
				/* memory re-allocator */
    void       *(DLL_ENTRY_FPTR *_System reallocp)(void *p, size_t s);
				/* low-level memory freer */
    void        (DLL_ENTRY_FPTR *_System freep)(void *p);
    size_t      asn1chop;       /* 0 means do not truncate strings; greater 
				 * value means truncate long output strings 
				 * (OCTET STRING, BIT STRING, Character String)
				 * to be "asn1chop" bytes long.  Read by
				 * encoder&decoder tracing and "printPDU"
				 */
    size_t      ossblock;       /* if not 0, size of largest block
				 * to allocate */
    size_t      ossprefx;       /* # bytes to leave before OSAK data buffer */

    FILE        *asn1out;       /* tracing output file */

    /* low-level tracing-output function; default is fprintf() */
    int         (DLL_ENTRY_FPTR *asn1prnt)(FILE *stream, const char *format,
			...);

	/*
	 * available for use by user application
	 */
    void        *userVar;

	/*
	 * used for storing DLL- & library NLMs-related parameters
	 */
#if defined(_WINDOWS) || defined(_WIN32)
    FunctionTables    ft;
#endif

	/*
	 * related to the new API; not for direct reference by user code
	 */
    void             *ctlTbl;
    int               api;
    int               encRules;
    unsigned long     encodingFlags;
    unsigned long     decodingFlags;
    long              decodingLength;
    char              errMsg[ERR_MSG_LENGTH];

	/*
	 * reserved for use by the encoder/decoder
	 */
	double            reserved[4];


	/*
	 * reserved for use by the memory manager and the tracing-routine
	 */
#ifdef storing
    struct storHandling t;
#else /* not storing */
    long int    memMgrVar[ossMemMgrVarLen];
#endif

    long int encDecVar[ossEncDecVarLen];
};


typedef struct ossGlobal OssGlobal;

/*****************************************************************************/
/*  PUBLIC section: memory manager DLL data structure                        */
/*****************************************************************************/

typedef enum {
    OSS_DEFAULT_MEMMGR = 0, /* memory is malloc'ed for each pointer in
			     * data tree */
    OSS_FILE_MEMMGR,        /* file memory manager with memory malloc'ed
			     * for each pointer in data tree */
    OSS_SOCKET_MEMMGR,      /* TCP/IP socket and file memory manager with memory
			     * malloc'ed for each pointer in data tree */
    OSS_FLAT_MEMMGR,        /* memory is malloc'ed in large blocks */
    OSS_OSAK_MEMMGR,        /* OSAK-buffer memory manager */
    OSS_USER_MEMMGR,        /* user memory manager */
    OSS_CPP_MEMMGR          /* fsream, TCP/IP socket and file memory
			     * manager with memory malloc'ed for each
			     * pointer in data tree */
} OssMemMgrType;

typedef enum {
    OSS_UNKNOWN_OBJECT = 0,
    OSS_FILE,
    OSS_SOCKET,
    OSS_OSAK_BUFFER,
    OSS_FSTREAM,
    OSS_MEMORY
} OssObjType;

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
typedef struct memManagerTbl {
    int			 (DLL_ENTRY_FPTR *_System ossMinitp)(void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System dopenInp)(void *,
						void **, unsigned long *);
    unsigned long	 (DLL_ENTRY_FPTR *_System dclosInp)(void *,
						void **, size_t);
    unsigned char	*(DLL_ENTRY_FPTR *_System dswapInp)(void *,
						void **, size_t *);
    void		 (DLL_ENTRY_FPTR *_System dopenOutp)(void *, void *,
						unsigned long, unsigned long);
    unsigned char	*(DLL_ENTRY_FPTR *_System dxferObjp)(void *,
						void **inn, void **out,
						size_t *, unsigned long *);
    unsigned char	*(DLL_ENTRY_FPTR *_System dxferDeferObjp)(void *,
						void **inn, void **out, size_t *,
						unsigned long *, unsigned long *);
    int			(DLL_ENTRY_FPTR *_System dxferEndp)(void *, void **out);
    unsigned long	 (DLL_ENTRY_FPTR *_System dclosOutp)(void *, void **);
    void		*(DLL_ENTRY_FPTR *_System dallcOutp)(void *, size_t,
								char root);
    void		 (DLL_ENTRY_FPTR *_System openWorkp)(void *);
    void		 (DLL_ENTRY_FPTR *_System pushHndlp)(void *, void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System popHndlp)(void *,
							void **, size_t);
    void		 (DLL_ENTRY_FPTR *_System closWorkp)(void *);
    void		*(DLL_ENTRY_FPTR *_System allcWorkp)(void *, size_t);
    unsigned char	*(DLL_ENTRY_FPTR *_System lockMemp)(void *, void *);
    void		 (DLL_ENTRY_FPTR *_System unlokMemp)(void *, void *,
								char);
    void		 (DLL_ENTRY_FPTR *_System ossFreerp)(void *, void *);
    int			 (DLL_ENTRY_FPTR *_System freePDUp)(void *, int,
							void *, void *);
    void		 (DLL_ENTRY_FPTR *_System drcovObjp)(void *, int,
							void *, void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System eopenInp)(void *, void *,
								size_t);
    unsigned char	*(DLL_ENTRY_FPTR *_System eswapInp)(void *, void *,
							void *, size_t);
    void		 (DLL_ENTRY_FPTR *_System eclosInp)(void *, void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System eopenOutp)(void *, void **,
							size_t *, char);
    unsigned char	*(DLL_ENTRY_FPTR *_System eswapOutp)(void *, void **,
							size_t, size_t *);
    unsigned char	*(DLL_ENTRY_FPTR *_System exferObjp)(void *, void **,
				void **, unsigned long *, unsigned long);
    unsigned long	 (DLL_ENTRY_FPTR *_System eclosOutp)(void *, void **,
							size_t, char);
    void		 (DLL_ENTRY_FPTR *_System ercovObjp)(void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System asideBeginp)(void *,
						void **, size_t, size_t *);
    unsigned char	*(DLL_ENTRY_FPTR *_System asideSwapp)(void *,
						void **, size_t, size_t *);
    void		*(DLL_ENTRY_FPTR *_System asideEndp)(void *,
							void *, size_t);
    unsigned char	*(DLL_ENTRY_FPTR *_System setDumpp)(void *, void **,
							void *, size_t *);
    void		 (DLL_ENTRY_FPTR *_System ossSetSortp)(void *, void *,
							unsigned char);
    void		 (DLL_ENTRY_FPTR *_System freeBUFp)(void *, void *);
    unsigned char	 (DLL_ENTRY_FPTR *_System egetBytep)(void *, void *,
							unsigned long);
    void		*(DLL_ENTRY_FPTR *_System _ossMarkObjp)(void *,
								int, void *);
    void		*(DLL_ENTRY_FPTR *_System _ossUnmarkObjp)(void *,
								void *);
    void		*(DLL_ENTRY_FPTR *_System _ossGetObjp)(void *,
								void *);
    int			(DLL_ENTRY_FPTR *_System _ossTestObjp)(void *,
								void *);
    void		(DLL_ENTRY_FPTR *_System _ossFreeObjectStackp)(void *);
    void		(DLL_ENTRY_FPTR *_System ossMtermp)(void *);
    void		(DLL_ENTRY_FPTR *_System _ossSetTimeoutp)(void *, long);
    int			(DLL_ENTRY_FPTR *_System _ossGetBufferp)(void *, void *);
    int			(DLL_ENTRY_FPTR *_System _ossSetBufferp)(void *, void *);
    int			(DLL_ENTRY_FPTR *_System _ossOpenDecoderInputFilep)(void *, char *);
    int			(DLL_ENTRY_FPTR *_System _ossCloseDecoderInputFilep)(void *);
    int			(DLL_ENTRY_FPTR *_System _ossOpenEncoderOutputFilep)(void *, char *);
    int			(DLL_ENTRY_FPTR *_System _ossCloseEncoderOutputFilep)(void *);
    long		(DLL_ENTRY_FPTR *_System _ossSetMinFileSizep)(void *, long);
    long		(DLL_ENTRY_FPTR *_System _ossGetMinFileSizep)(void *);
    void		(DLL_ENTRY_FPTR *_System _ossSetUserMallocFreeReallocp)(void *,
					void *(CDECL_ENTRY_FPTR *)(struct ossGlobal *, size_t),
					void  (CDECL_ENTRY_FPTR *)(struct ossGlobal *, void *),
					void *(CDECL_ENTRY_FPTR *)(struct ossGlobal *, void *, size_t));
    void		(DLL_ENTRY_FPTR *_System _ossGetUserMallocFreeReallocp)(void *,
					void *(CDECL_ENTRY_FPTR **)(struct ossGlobal *, size_t),
					void  (CDECL_ENTRY_FPTR **)(struct ossGlobal *, void *),
					void *(CDECL_ENTRY_FPTR **)(struct ossGlobal *, void *, size_t));
    int			(DLL_ENTRY_FPTR *_System unused1)(void *);
    int			(DLL_ENTRY_FPTR *_System unused2)(void *);
#if defined(DLL_LINKAGE)
    void		*(DLL_ENTRY_FPTR *_System ossGetMemp)(size_t);
    void		(DLL_ENTRY_FPTR  *_System ossReleaseMemp)(void *);
    void		*(DLL_ENTRY_FPTR *_System ossReallocMemp)(void *, size_t);
    void		(DLL_ENTRY_FPTR  *_System handlerrp)(void *, enum errcode, void *);
    int			(DLL_ENTRY_FPTR  *_System ossGetCompressDecompressInfop)(void *, void **);
    int			(DLL_ENTRY_FPTR  *_System ossGetCompressDecompressFunctionsp)(void *, void *, void *);
    unsigned long	(DLL_ENTRY_FPTR  *_System ossGetByteOffsetp)(void *);
    int			(DLL_ENTRY_FPTR  *_System dpduWalkp)(void *, int, void *, void *, void *);
    int			(DLL_ENTRY_FPTR  *_System ossGetCompSizeEstimatorp)(void *, void *);
#endif /* DLL_LINKAGE */
    int			memMgrType;	/* must be the last */
} MemManagerTbl;

typedef struct etype *etypep;
typedef struct pointerTbl {
    int		(DLL_ENTRY_FPTR  *_System ossConstrainp)(void *, int, void *, void *);
    void	(DLL_ENTRY_FPTR  *_System ossPrintRealp)(void *, void *, unsigned char *);
    long	(DLL_ENTRY_FPTR  *_System ossBerEncodeRealp)(void *, void *, unsigned char *);
    long	(DLL_ENTRY_FPTR  *_System ossBerDecodeRealp)(void *, void *, long, char);
    void	(DLL_ENTRY_FPTR  *_System ossPerEncodeRealp)(void *, void *);
    void	(DLL_ENTRY_FPTR  *_System ossPerDecodeRealp)(void *, void *);
    ossBoolean	(DLL_ENTRY_FPTR  *_System ossCmpObjectsp)(void *, void *, etypep, void *, ossBoolean);
} PointerTbl;

#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ */
/*****************************************************************************/
/*  PUBLIC section: OSS decoder/encoder runtime flags                        */
/*****************************************************************************/

    /*************************************************************************/
    /*      GENERAL FLAGS                                                    */
    /*************************************************************************/

#define DEBUGPDU           0x02 /* produce tracing output */
#define BUFFER_PROVIDED    0x04 /* use caller-provided buffer */
#define RESTRAIN           0x08 /* limit output buffer to user-specified size*/
#define NOTRAPPING        0x200 /* do no signal trapping */
#define OSS_TRAPPING      0x20000  /* do signal trapping */
#define NOCONSTRAIN       0x800 /* ignore calling constraint checker */
#define AUTOMATIC_ENCDEC 0x2000 /* do automatic encoding/decoding of
				 * open types */
#define IGNORE_DEFER_DECODING 0x400000 /* force runtime to automatically process
				* values with DeferDecoding directive applied */
#define STRICT_CONSTRAINT_CHECKING 0x800000 /* to force strict checking
					     * of constraints */
#define STRICT_ENCODING_DECODING_RULES 0x20000000 /* force a strict checking
				 * of encoding data, e.g.:
				 * - zero length extension check
				 * - illegal fragmentation check */
#define USE_COMPRESSION 0x40000000 /* (un)compress encoding */

    /*************************************************************************/
    /*      ENCODER-SPECIFIC FLAGS                                           */
    /*************************************************************************/

#define DEFAULT_ALIGN           0 /* use most efficient align (back or front) */
#define DEFINITE             0x10 /* force definite-length encoding */
#define INDEFINITE           0x20 /* force indefinite-length encoding */
#define DETERMINE_ENC_LENGTH 0x40 /* generate only total encoding length
				   * (for use in user memory managers) */
#define FRONT_ALIGN          0x80 /* align output to front of output buffer */
#define BACK_ALIGN          0x100 /* align output to back of output buffer */
#define OSS_AUTO_ENCODE_WITHOUT_CHECKING_CONSTRAINT 0x1000000

#define COMPACT_XER_ENCODING    0x2000000
#define NO_XML_DECLARATION      0x4000000
#define STRICT_PER_ENCODING_OF_DEFAULT_VALUES 0x8000000
#define RELAY_OPEN_TYPE_IN_HEX 0x10000000 /* XER-encode undecoded BER/PER/...
					   * OpenTypes in HEX, not in binary */
#define DONT_OPTIMIZE_XMLNS    0x80000000

    /*************************************************************************/
    /*      DECODER-SPECIFIC FLAGS                                           */
    /*************************************************************************/

#define IGNORE_PDU_TAG   0x1    /* on second decoding do not issue an error
				 * but ignore an invalid PDU tag in an open
				 * type encoding of a field with IMPLICIT tag
				 * marked with the directive DeferDecoding */
#define DEBUG_ERRORS    0x4000	/* same as DEBUGPDU */
#define RELAXBER OSS_RELAXED    /* use relaxed BER */
#define RELAXPER OSS_RELAXED    /* use relaxed PER */
#define OSS_RELAXED    0x400    /* use relaxed decoding rules */
#define OBJECT_HANDLE 0x1000    /* temporarily mark object of type with
				 * NOCOPY directive to not free it by
				 * ossFreePDU() (for use in user memory
				 * managers) */
#define OSS_SKIP_UNKNOWN_CONTENT  0x010000 /* instructs E-XER and Fast Infoset 
				 * (FINF) decoders to skip unknown elements and 
				 * attributes; when this flag is not set, 
				 * the decoders give an error for such unknown 
				 * content */
#define DONT_FREE_ENCODED 0x40000 /* when automatically decoding, don't free
				 * memory allocated for encoded OpenType values
				 * by the first outermost call of the decoder
				 * for enclosing PDU */
#define SMART_POINTER 0x200000   /* temporarily set to inform memory manager
				  * that it is supposed to treat input handle
				  * (or to return output handle) as smart
				  * pointer rather than plain memory address
				  * (for use in custom memory manager) */ 

    /*************************************************************************/
    /*      OTHER FLAGS                                                      */
    /*************************************************************************/

#define DONT_DO_ENCODED  0x80000 /* when calling ossCpyValue()/ossCmpValue(),
				 * don't copy/compare encoded OpenType values */
#define DONT_DO_DECODED 0x100000 /* when calling ossCpyValue()/ossCmpValue(),
				 * don't copy/compare decoded OpenType values */


/*****************************************************************************/
/*  PUBLIC section: OSS API return codes                                     */
/*****************************************************************************/

    /*************************************************************************/
    /*      GENERAL RETURN CODES                                             */
    /*************************************************************************/

#define MORE_BUF                    1 /* user-provided outbut buffer
				       * too small */
#define PDU_RANGE                   3 /* pdu specified out of range */
#define BAD_ARG                     6 /* something weird was passed - probably
				       * a NULL pointer */
#define BAD_VERSION                 7 /* versions of encoder/decoder and
				       * control-table do not match */
#define OUT_MEMORY                  8 /* memory-allocation error */
#define BAD_OBJID                  10 /* object identifier conflicts with
				       * X.680 */
#define MEM_ERROR                  14 /* memory violation signal trapped */
#define CONSTRAINT_VIOLATED        17 /* constraint violation error occured */
#define FATAL_ERROR                18 /* *serious* error, could not free memory,
				       * &etc */
#define ACCESS_SERIALIZATION_ERROR 19 /* error occured during access to
				       * global data in a multi-threaded
				       * environment */
#define NULL_TBL                   20 /* attempt was made to pass a NULL
				       * control table pointer */
#define NULL_FCN                   21 /* attempt was made to call the
				       * encoder/decoder via a NULL pointer */
#define BAD_ENCRULES               22 /* unknown encoding rules set in the
				       * ossGlobal structure */
#define UNAVAIL_ENCRULES           23 /* the encoding rules requested are
				       * not implemented yet or were not
				       * linked because the encoder/decoder
				       * function pointers were not
				       * initialized by a call to ossinit() */
#define CANT_OPEN_TRACE_WINDOW     24 /* error when opening a trace window */
#define UNIMPLEMENTED              25 /* unimplemented type or feature */
#define OID_DLL_NOT_LINKED         26 /* OBJECT IDENTIFIER DLL was not linked */
#define CANT_OPEN_TRACE_FILE       27 /* error when opening a trace file */
#define TRACE_FILE_ALREADY_OPEN    28 /* the trace file has been opened */
#define TABLE_MISMATCH             29 /* C++ API: PDUcls function called with
				       * a ossControl object which refers to
				       * control table different from one the
				       * PDU was defined in */
#define TYPE_NOT_SUPPORTED         30 /* ASN.1 type is not supported */
#define REAL_DLL_NOT_LINKED        31 /* REAL DLL was not linked */
#define REAL_CODE_NOT_LINKED       32 /* REAL code was not linked */
#define OUT_OF_RANGE               33 /* parameter value range error */
#define COPIER_DLL_NOT_LINKED      34 /* value copier DLL was not linked */
#define CONSTRAINT_DLL_NOT_LINKED  35 /* constraint checker DLL was not
				       * linked */
#define COMPARATOR_DLL_NOT_LINKED  36 /* value comparator DLL was not linked */
#define COMPARATOR_CODE_NOT_LINKED 37 /* value comparator code was not linked */
#define MEM_MGR_DLL_NOT_LINKED     38 /* memory manager DLL was not linked */
#define TRACING_CODE_NOT_LINKED    39 /* tracing code not linked or
				       * initialized */
#define OPEN_TYPE_USER_FIELD_ERROR 40 /* error was returned by a user-defined
				       * user field copying/comparing
				       * function */
#define API_DLL_NOT_LINKED         41 /* API DLL was not linked */
#define BERDER_DLL_NOT_LINKED      42 /* BER/DER DLL was not linked */
#define PER_DLL_NOT_LINKED         43 /* PER DLL was not linked */
#define OPEN_TYPE_ERROR            44 /* error in automatic encoding/decoding/
                                       * copying an open type */
#define MUTEX_NOT_CREATED          45 /* mutex was not created */
#define CANT_CLOSE_TRACE_FILE      46 /* error when closing a trace file */
#define CANT_SET_START_BUF         47 /* initial buffer to start decoding from
                                       * cannot be set */
#define START_BUF_NOT_SET          48 /* initial buffer to start decoding from
                                       * is not set */

#define INFO_OBJECT_SET_TABLE_COPY_ERROR      49 /* error when copying informa-
						  * tion object set table */
#define INFO_OBJECT_ALREADY_EXISTS            50 /* object already exists */
#define INFO_OBJECT_UNIQUE_FIELD_NOT_FOUND    51 /* unique field was not found
						  * in information object set */
#define INFO_OBJECT_NOT_FOUND                 52 /* information object was not
						  * found */
#define INFO_OBJECT_SET_NOT_EXTENSIBLE        53 /* information object set is
						  * not extensible */
#define ERROR_READING_FROM_DECODER_INPUT_FILE 54 /* error reading from decoder
						  * input file */
#define DECODER_INPUT_FILE_ALREADY_OPEN       55 /* decoder input file is
						  * already opened */
#define CANT_CLOSE_DECODER_INPUT_FILE         56 /* error when closing decoder
						  * input file */
#define CANT_OPEN_DECODER_INPUT_FILE          57 /* error when opening decoder
						  * input file */
#define ENCODER_OUTPUT_FILE_ALREADY_OPEN      58 /* encoder output file is
						  * already opened */
#define CANT_CLOSE_ENCODER_OUTPUT_FILE        59 /* error when closing encoder
						  * output file */
#define CANT_OPEN_ENCODER_OUTPUT_FILE         60 /* error when opening encoder
						  * output file */
#define CANT_CLOSE_FROM_ASCII      61 /* error when closing iconv tables */
#define CANT_CLOSE_TO_ASCII        62 /* error when closing iconv tables */
#define ASCII_EBCDIC_CONV_ERROR    63 /* error in iconv call */
#define CANT_OPEN_FROM_ASCII       64 /* error when opening iconv tables */
#define CANT_OPEN_TO_ASCII         65 /* error when opening iconv tables */
#define PRINTPER_DLL_NOT_LINKED    84 /* PER tracing DLL was not linked */ 
#define CANT_OPEN_INPUT_FILE       86 /* error while opening input file */
#define XER_DLL_NOT_LINKED         99 /* XER DLL was not linked or found */
#define PATTERN_CONSTRAINT_NOT_LINKED 101 /* Pattern constraint code was
					   * not linked */
#define BAD_OBJIDNODE                 103 /* object identifier conflicts
					   * with X.680 */
#define EXER_DLL_NOT_LINKED           110 /* EXER DLL was not linked or found */

    /*************************************************************************/
    /*      ENCODER-SPECIFIC RETURN CODES                                    */
    /*************************************************************************/

#define PDU_ENCODED       0  /* PDU successfully encoded */
#define BAD_CHOICE        9  /* unknown selector for a choice */
#define BAD_PTR          11  /* unexpected NULL pointer in input buffer */
#define BAD_TIME         12  /* bad value in time type */
#define INDEFINITE_NOT_SUPPORTED 13 /* BER indefinite-length encoding is not
				     * supported for Spartan or time-optimized
				     * encoder/decoder */
#define BAD_TABLE         15 /* table was bad, but not NULL */
#define TOO_LONG          16 /* type was longer than shown in SIZE constraint */
#define NOCOPY_FRAGMENTED 102 /* NOCOPY directive is specified for an item
			       * which must be encoded in fragmented manner
			       * (usually for CER) */

    /*************************************************************************/
    /*      DECODER-SPECIFIC RETURN CODES                                    */
    /*************************************************************************/

#define PDU_DECODED       0  /* PDU successfully decoded */
#define NEGATIVE_UINTEGER 2  /* the first bit of the encoding is encountered
                              * set to 1 while decoding an unsigned integer */
#define MORE_INPUT        4  /* the PDU is not fully decoded, but the end
			      * of the input buffer has been reached */
#define DATA_ERROR        5  /* an error exists in the encoded data */
#define PDU_MISMATCH      9  /* the PDU tag that the user specified was diffe-
			      * rent from the tag found in the encoded data */
#define LIMITED          10  /* implementation limit exceeded. eg:
			      * integer value too great */
#define EOF_INPUT_FILE   85  /* EOF decoder input file, no PDU was decoded */

    /*************************************************************************/
    /*      MEMORY MANAGER-SPECIFIC RETURN CODES                                    */
    /*************************************************************************/
#define OSS_TIMEOUT_EXPIRED 		130 /* unable to read due to an exceeded timeout */
#define CANT_CLOSE_INPUT_FILE		133
#define CANT_OPEN_OUTPUT_FILE		134
#define CANT_CLOSE_OUTPUT_FILE		135
#define ERROR_WRITING_TO_FILE		136
#define ERROR_READING_FROM_FILE		137
#define CANT_OPEN_TEMPORARY_FILE	138
#define UNRECOGNIZED_MEMORY_OBJECT	139
#define DEFERRED_VALUE_IN_BUFFER	140
#define INCORRECT_DEFERRED_VALUE	141
#define ERROR_WRITING_TO_SOCKET		142
#define ERROR_READING_FROM_SOCKET	143
#define CANT_LOAD_SOCKET_DLL		144
#define CANT_GET_PROC_ADDRESS		145
#define INVALID_SOCKET_HANDLE		146
#define TIMEOUT_WRITING_TO_SOCKET	147
#define TIMEOUT_READING_FROM_SOCKET	OSS_TIMEOUT_EXPIRED


    /*************************************************************************/
    /*      STANDALONE CONSTRAINT CHECKER RETURN CODES                       */
    /*************************************************************************/

#define TYPE_CONSTRAINT                              66
#define VALUE_NOT_AMONG_ENUMERATED_CONSTRAINT        67
#define COMPONENT_RELATION_CONSTRAINT                68
#define TABLE_CONSTRAINT                             69
#define PRESENCE_CONSTRAINT                          70
#define ABSENCE_CONSTRAINT                           71
#define PERMITTED_ALPHABET_CONSTRAINT                72
#define SIZE_CONSTRAINT_SETOF_SEQOF                  73
#define SIZE_CONSTRAINT_STRING                       74
#define VALUE_RANGE_CONSTRAINT_REAL                  75
#define VALUE_RANGE_CONSTRAINT_UNSIGNED_INTEGER      76
#define VALUE_RANGE_CONSTRAINT_SIGNED_INTEGER        77
#define SINGLE_VALUE_CONSTRAINT_COMPLEX_TYPE         78
#define SINGLE_VALUE_CONSTRAINT_STRING               79
#define SINGLE_VALUE_CONSTRAINT_REAL                 80
#define SINGLE_VALUE_CONSTRAINT_UNSIGNED_INTEGER     81
#define SINGLE_VALUE_CONSTRAINT_SIGNED_INTEGER       82
#define USER_CONSTRAINT_FUNCTION_ERROR               83
#define PATTERN_CONSTRAINT                          100
#define BAD_OID_IRI				    122
#define SINGLE_VALUE_CONSTRAINT                     123
    /*************************************************************************/
    /*      LEAN DECODER/ENCODER INCOMPATIBILITY RETURN CODES                */
    /*      Indicate that the current build of the LEAN endoder/decoder      */
    /*      does not support a feature                                       */
    /*************************************************************************/

#define OSS_LEAN_BAD_VERSION                    87 /* The versions of LEAN   *
			    * encoder/decoder and control-table do not match */
#define OSS_LEAN_AUTOMATIC_ENCDEC_NOT_SUPPORTED 88 /* Automatic encoding and *
						    * decoding of open types */
#define OSS_LEAN_RELAYSAFE_NOT_SUPPORTED        89 /* relaySafe mode         */
#define OSS_LEAN_DER_ENCODER_NOT_SUPPORTED      90 /* DER encoding rules     */
#define OSS_LEAN_REALTYPE_NOT_SUPPORTED         91 /* REAL type              */
#define OSS_LEAN_REMOVE_NOT_SUPPORTED           92 /* REMOVE directive       */
#define OSS_LEAN_NOCOPY_NOT_SUPPORTED           93 /* NOCOPY directive       */
#define OSS_LEAN_DEFERDECODING_NOT_SUPPORTED    94 /* DeferDecoding directive*/
#define OSS_LEAN_USERHOOKS_NOT_SUPPORTED        95 /* reserved               */
#define OSS_LEAN_TRUNCATE_SOF_NOT_SUPPORTED     96 /* Truncate directive     */
#define OSS_LEAN_POINTER_NOT_SUPPORTED		97 /* POINTER directive      */
#define OSS_LEAN_LONGLONG_NOT_SUPPORTED        107 /* LONGLONG directive     */
#define OSS_LEAN_COMPRESSION_NOT_SUPPORTED     117 /* Compression            */
#define OSS_LEAN_ZLIB_NOT_SUPPORTED	       120 /* zlib 		     */
    /*************************************************************************/
    /*      OTHER RETURN CODES                                               */
    /*************************************************************************/

#define CANT_LOAD_DYNLIBRARY            97 /* unable to open dynamic library */
#define CANT_UNLOAD_DYNLIBRARY          98 /* unable to close dynamic library */
#define CONSTRUCTED_NESTING_LIMIT_EXCEEDED 108 /* nesting level of constructed
						* string encodings exceeds
						* the limit */
#define SEQ_SET_NESTING_LIMIT_EXCEEDED 109 /* nesting level of encoding of SET,
					    * SEQUENCE, SET OF, SEQUENCE OF or
					    * CHOICE exceeded the limit */
#define DEFAULT_PREFIX_NOT_ALLOWED     111
#define UNKNOWN_NAMESPACE_URI          112
#define INVALID_PREFIX                 113
#define PREFIX_ALREADY_ASSIGNED        114
#define COMPRESS_ERROR                 115
#define CANT_LOAD_ZLIB_DLL             121 /* unable to open zlib1.dll */


/*****************************************************************************/
/*  PUBLIC section: OSS compatibility flags                                  */
/*****************************************************************************/

/*** compatibility flags ***/
#define OSS_V412_TIME_AND_WIDE_CHAR_STRINGS          0x01
#define OSS_TRUNCATE_0_SECONDS_FROM_GENERALIZED_TIME 0x02
#define OSS_TRUNCATE_0_SECONDS_FROM_UTC_TIME         0x04
#define OSS_EXTENDED_UNRESTRICTED_CHAR_STRINGS       0x08
#define OSS_ALLOW_ZERO_LENGTH_OPENTYPE_STRINGS	     0x10
#define OSS_ALLOW_TIME_DIFFERENTIAL_IN_UTC_TIME      0x20
#define OSS_ALLOW_TIME_DIFFERENTIAL                  0x20
#define OSS_PACK_WIDE_STRINGS                        0x40
#define OSS_ALLOW_NULL_IN_TIME			     0x80

#define OSS_MANTISSA_EXPONENT_REAL_FORMAT            0x100
#define OSS_ALLOW_ZERO_LENGTH_EXTENSIONS	     0x200
#define OSS_ALLOW_NON_NR3_DER_REAL		     0x400
#define OSS_PER_VISIBLE_EXCEPTIONS		     0x800
#define OSS_EXTENDED_RESTRICTED_KMC_STRING_AS_OCTETS 0x1000
#define OSS_PER_NULLTERM_TIME_8BIT_CHARS	     0x2000
#define OSS_ALLOW_MISPLACED_EXTENSION_FIELDS	     0x4000

#define OSS_ALLOW_ABSENT_OR_BAD_SECONDS_OR_ABSENT_Z  0x8000
#define OSS_KEEP_MEMORY_MANAGER_TEMPORARY_FILES      0x10000
#define OSS_PER_ALLOW_TRAILING_ZEROS		     0x20000
#define OSS_V85_TABLE_CONSTRAINT_FOR_EXTENSIBLE_OBJECT_SETS	0x80000
#define OSS_V90_ARRAY_AND_VARYING_SIZE		    0x100000

#define OSS_USE_TYPE_IDENTIFICATION_ATTRIBUTE_FOR_UNION		0x200000
#define OSS_NO_DETAIL_MM_ERROR_CODES		    0x400000

/* compatibility flags added after V.412 */
#define OSS_VERSION_412_FL	OSS_V412_TIME_AND_WIDE_CHAR_STRINGS

/* compatibility flags added after V.419 */
#define OSS_VERSION_419_FL (\
			    OSS_TRUNCATE_0_SECONDS_FROM_GENERALIZED_TIME |\
			    OSS_TRUNCATE_0_SECONDS_FROM_UTC_TIME |\
			    OSS_EXTENDED_UNRESTRICTED_CHAR_STRINGS |\
            		    OSS_ALLOW_ZERO_LENGTH_OPENTYPE_STRINGS |\
            		    OSS_ALLOW_TIME_DIFFERENTIAL_IN_UTC_TIME |\
			    OSS_PACK_WIDE_STRINGS)

/* compatibility flags added after V.540 */
#define OSS_VERSION_540_FL	OSS_ALLOW_NULL_IN_TIME

/* compatibility flags added after V.811 */
#define OSS_VERSION_811_FL	OSS_ALLOW_ABSENT_OR_BAD_SECONDS_OR_ABSENT_Z

/* compatibility flags added after V.840 */
#define OSS_VERSION_840_FL	OSS_PER_ALLOW_TRAILING_ZEROS

/* List of supported compatibility modes */
typedef enum {
    OSS_CUSTOM_COMPATIBILITY = -2, /* Any combination of compatibility
                                    * flags set by a call to the function
                                    * ossSetCompatibilityFlags() */
    OSS_CURRENT_VERSION = 0,       /* Current version */
    OSS_VERSION_412,         /* Includes the following compatibility flags:
                              * OSS_V412_TIME_AND_WIDE_CHAR_STRINGS 
			      * and all the below
			      */
    OSS_VERSION_419,         /* Includes the following compatibiity flags:
                              * OSS_TRUNCATE_0_SECONDS_FROM_GENERALIZED_TIME
                              * OSS_TRUNCATE_0_SECONDS_FROM_UTC_TIME
                              * OSS_EXTENDED_UNRESTRICTED_CHAR_STRINGS 
			      * OSS_ALLOW_ZERO_LENGTH_OPENTYPE_STRINGS
                              * OSS_ALLOW_TIME_DIFFERENTIAL_IN_UTC_TIME
			      * OSS_PACK_WIDE_STRINGS
			      * and all the below
			      */
    OSS_VERSION_540, 	     /* Includes the following compatibiity flags:
			      * OSS_ALLOW_NULL_IN_TIME
			      * and all the below
			      */
    OSS_VERSION_811,	     /* Includes the following compatibiity flags:
			      * OSS_ALLOW_ABSENT_OR_BAD_SECONDS_OR_ABSENT_Z
			      * and all the below
			      */		      
    OSS_VERSION_840	     /* Includes the following compatibiity flags:
			      * OSS_PER_ALLOW_TRAILING_ZEROS
			      * and all the below
			      */		      
    
} OssRuntimeVersion;


/*****************************************************************************/
/*  PUBLIC section: variables and declarations provided for backward         */
/*  compatibility with previous versions (deprecated - new applications      */
/*  should not use them)                                                     */
/*****************************************************************************/
extern int ossFreeOpenTypeEncoding;

#define INITIALIZATION_SUCCESSFUL 0

extern int asn1chop;         /* 0 means don't truncate strings; non-zero
			      * value means truncate long input strings
			      * (OCTET STRING, BIT STRING, CharacterStrings)
			      * to be asn1chop bytes long. Used by printPDU. */

extern size_t ossblock;      /* if > 0, size of largest block to allocate */
extern size_t ossprefx;      /* size of reserved OSAK buffer prefix */
#ifdef EOF
extern FILE *asn1out;
/* pointer to output function used by printPDU; default to fprintf. */
extern int (DLL_ENTRY_FPTR *asn1prnt) (FILE *stream, const char *format, ...);
#endif /* EOF */

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
extern void * const    ctl_tbl;
extern HINSTANCE hInst;
#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ */

extern void *(CDECL_ENTRY_FPTR *mallocp)(size_t p);  /* function which allocates memory */
extern void  (CDECL_ENTRY_FPTR *freep)(void *p);     /* function which frees memory */
/* used in codefile generated only */
#define PDU_FREED   0
#define PDU_PRINTED 0

#define DISP_PLUS_INFINITY  "PLUS-INFINITY"
#define DISP_MINUS_INFINITY "MINUS-INFINITY"
#define DISP_NOT_A_NUMBER   "NOT-A-NUMBER"
#define ossNaN		    OSS_NOT_A_NUMBER	/* for backward compatibility */

/*****************************************************************************/
/*  PUBLIC section: non-API functions defined in examples or generated files */
/*****************************************************************************/

#if defined(_WINDOWS) && !defined(_WIN32) && !defined(WIN32)
#define GWL_USERDATA 0
#endif /* _WINDOWS && !_WIN32 && !WIN32 */

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
extern int CDECL_ENTRY	ossGeneric(struct ossGlobal *, HWND);
extern int DLL_ENTRY oss_test(struct ossGlobal *);
#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ */

/*****************************************************************************/
/*  PUBLIC section: OSS API FUNCTIONS                                        */
/*****************************************************************************/

    /*************************************************************************/
    /*      OBSOLETE FUNCTIONS                                               */
    /*************************************************************************/

PUBLIC extern int DLL_ENTRY encode(struct ossGlobal *world,
		int pdunum, void *inbuf, char **outbuf, long *outlen,
		void *ctl_tbl, unsigned flags, char errmsg[ERR_MSG_LENGTH]);

PUBLIC extern int DLL_ENTRY decode(struct ossGlobal *world,
		int *pdunum, char **inbuf, long *inlen, void **outbuf,
			long *outlen, void *ctl_tbl, unsigned flags,
						char errmsg[ERR_MSG_LENGTH]);

PUBLIC void DLL_ENTRY freeBUF(struct ossGlobal *world, void *data);
PUBLIC int  DLL_ENTRY freePDU(struct ossGlobal *world, int pdunum, void *data,
				void *ctl_tbl);
PUBLIC int  DLL_ENTRY printPDU(struct ossGlobal *world, int pdunum, void *data,
				void *ctl_tbl);

    /*************************************************************************/
    /*      CORE-ESSENTIAL FUNCTIONS                                         */
    /*************************************************************************/

PUBLIC int DLL_ENTRY         ossDecode(struct ossGlobal *world,
					int             *pdunum,
					OssBuf          *input,
					void           **output);
PUBLIC int DLL_ENTRY         ossEncode(struct ossGlobal *world,
					int              pdunum,
					void            *input,
					OssBuf          *output);
PUBLIC void DLL_ENTRY        ossFreeBuf(struct ossGlobal *world,
					void            *data);
PUBLIC int DLL_ENTRY         ossFreePDU(struct ossGlobal *world,
					int              pdunum,
					void            *data);
PUBLIC int DLL_ENTRY         ossinit(struct ossGlobal *world, void *ctl_tbl);
PUBLIC void DLL_ENTRY        ossterm(struct ossGlobal *world);
PUBLIC void DLL_ENTRY	     free_ext_errMsg(struct ossGlobal *world);


#if defined(DLL_LINKAGE)
/*
 * To correctly import data like the below, the code must explicitly
 * do import.  Otherwise garbage is imported.
 */
__declspec(dllimport) extern int _ossSetGlobalUserVar;
#else
PUBLIC extern int _ossSetGlobalUserVar;
#endif /* DLL_LINKAGE */

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
#define osswinit ossWinit
PUBLIC extern int DLL_ENTRY  ossWinit(struct ossGlobal *, void *, char *, HWND);
PUBLIC extern void DLL_ENTRY ossWterm(struct ossGlobal *);
/* Mappings and definitions provided for compatibility for other platforms */
#elif !defined(__IBMC__)
#define osswinit(world, ctl_tbl, dll_name, hwnd) ossinit(world, ctl_tbl)
#define ossWinit(world, ctl_tbl, dll_name, hwnd) ossinit(world, ctl_tbl)
#define ossWterm(world) ossterm(world)
#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ */

#if !(defined(__IBMC__) && defined(__WIN32__))  \
	&& !defined(DYNAMICLINKING_NOTSUPPORTED)
int                          ossUinit(struct ossGlobal *world, void *ctl_tbl,
					char *ctl_dll);
void                         ossUterm(struct ossGlobal *world);
#endif /* !(__IBMC__ ...) && !DYNAMICLINKING_NOTSUPPORTED && !TOED_LED */

    /*************************************************************************/
    /*      USEFUL NON-ESSENTIAL FUNCTIONS                                   */
    /*************************************************************************/
PUBLIC int DLL_ENTRY        ossCloseTraceFile(struct ossGlobal *world);

PUBLIC unsigned long DLL_ENTRY ossGetDecodingFlags(struct ossGlobal *world);
PUBLIC unsigned long DLL_ENTRY ossGetEncodingFlags(struct ossGlobal *world);
PUBLIC int DLL_ENTRY        ossGetEncodingRules(struct ossGlobal *world);
PUBLIC char *DLL_ENTRY      ossGetErrMsg(struct ossGlobal *world);
PUBLIC char *DLL_ENTRY ossDescribeReturnCode(OssGlobal *in_world, int in_rc);
PUBLIC unsigned long DLL_ENTRY ossGetFlags(struct ossGlobal *world);

PUBLIC int DLL_ENTRY        ossOpenTraceFile(struct ossGlobal *world,
					char          *fileName);

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
PUBLIC extern int DLL_ENTRY ossOpenTraceWindow(struct ossGlobal *);
#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ */

extern int                  ossPrint(struct ossGlobal *, const char *, ...);
PUBLIC void DLL_ENTRY       ossPrintHex(struct ossGlobal *world,
					char          *encodedData,
					long           length);
PUBLIC void DLL_ENTRY       ossPrintOctetAsASCII(struct ossGlobal *world,
					char          *display);
PUBLIC void DLL_ENTRY       ossPrintOctetAsIPAddress(struct ossGlobal *world,
					char          *display);
PUBLIC int DLL_ENTRY        ossPrintPDU(struct ossGlobal *world,
					int            pdunum,
					void          *data);
PUBLIC int DLL_ENTRY        ossPrintPDUToBuffer(struct ossGlobal *world,
					int            pdunum,
					void          *data,
					OssBuf	      *output);
PUBLIC long DLL_ENTRY       ossDeterminePDUBufferLength(struct ossGlobal *world,
					int            pdunum,
					void          *data);

PUBLIC int DLL_ENTRY        ossSetDecodingFlags(struct ossGlobal *world,
					unsigned long flags);
PUBLIC int DLL_ENTRY	    ossIdentifyPDUByEXERName(struct ossGlobal *world,
					unsigned char *uri,
					unsigned char *name, int *pdu);
PUBLIC int DLL_ENTRY        ossSetEncodingFlags(struct ossGlobal *world,
					unsigned long flags);
PUBLIC int DLL_ENTRY        ossSetEncodingRules(struct ossGlobal *world,
					ossEncodingRules rules);
PUBLIC int DLL_ENTRY        ossSetFlags(struct ossGlobal *world,
					unsigned long flags);
extern int DLL_ENTRY        ossTest(struct ossGlobal *world,
					int            pdunum,
					void          *data);
    /*************************************************************************/
    /*      ADVANCED-USER FUNCTIONS                                          */
    /*************************************************************************/

PUBLIC int DLL_ENTRY        ossCloseDecoderInputFile(struct ossGlobal *world);
PUBLIC int DLL_ENTRY        ossCloseEncoderOutputFile(struct ossGlobal *world);
PUBLIC long DLL_ENTRY       ossDetermineEncodingLength(struct ossGlobal *world,
							int        pdunum,
							void      *data);
PUBLIC unsigned long DLL_ENTRY ossDetermineMessageLength(
						    struct ossGlobal *world,
						    OssBuf           *buf);

PUBLIC int DLL_ENTRY        ossDetermineNumberOfPadBits(struct ossGlobal *);


/* ==================== Data conversion function ================ */
PUBLIC int DLL_ENTRY ossConvertData(struct ossGlobal *world,
			OssBuf *fromData, unsigned int fromFormat,
			OssBuf *toData, unsigned int toFormat);
/* Input and Output data format */
#define OSS_BIN_DATA		0x01
#define OSS_HEX_DATA		0x02
#define OSS_BASE64_DATA		0x04

#define ossBinary2Base64(w, i, o) \
	    ossConvertData(w, i, OSS_BIN_DATA, o, OSS_BASE64_DATA)
#define ossBase642Binary(w, i, o) \
	    ossConvertData(w, i, OSS_BASE64_DATA, o, OSS_BIN_DATA)
#define ossBinary2Hex(w, i, o) \
	    ossConvertData(w, i, OSS_BIN_DATA, o, OSS_HEX_DATA)
#define ossHex2Binary(w, i, o) \
	    ossConvertData(w, i, OSS_HEX_DATA, o, OSS_BIN_DATA)

PUBLIC int DLL_ENTRY        ossGetBuffer(struct ossGlobal *world,
					    OssBufExtended *buf);

PUBLIC long DLL_ENTRY       ossGetBytesReadByDecoder(struct ossGlobal *world);
PUBLIC long DLL_ENTRY       ossGetDecodingLength(struct ossGlobal *world);
PUBLIC long DLL_ENTRY       ossGetMinFileSize(struct ossGlobal *world);
PUBLIC void *DLL_ENTRY      ossGetObj(struct ossGlobal *world, void *objHndl);

PUBLIC void DLL_ENTRY       ossGetUserMallocFreeRealloc(struct ossGlobal *world,
		void *(CDECL_ENTRY_FPTR **ossUserMalloc)(struct ossGlobal *world, size_t size),
		void  (CDECL_ENTRY_FPTR **ossUserFree)(struct ossGlobal *world, void *buf),
		void *(CDECL_ENTRY_FPTR **ossUserRealloc)(struct ossGlobal *world, void *buf,
					    size_t size));
#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
PUBLIC extern HINSTANCE DLL_ENTRY ossLoadMemoryManager(struct ossGlobal *,
							int, char *);
#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ */

PUBLIC void *DLL_ENTRY      ossMarkObj(struct ossGlobal *world,
					    OssObjType objType, void *object);
PUBLIC int DLL_ENTRY        ossOpenDecoderInputFile(struct ossGlobal *world,
					    char *fname);
PUBLIC int DLL_ENTRY        ossOpenEncoderOutputFile(struct ossGlobal *world,
					    char *fname);
PUBLIC int DLL_ENTRY        ossSetBuffer(struct ossGlobal *world,
					    OssBufExtended *buf);
PUBLIC int DLL_ENTRY        ossSetDecodingLength(struct ossGlobal *world,
						    long bufferLength);
PUBLIC long DLL_ENTRY       ossSetMinFileSize(struct ossGlobal *world,
					    long minsize);
PUBLIC void DLL_ENTRY       ossSetTimeout(struct ossGlobal *world,
					    long timeout);

PUBLIC void DLL_ENTRY       ossSetUserMallocFreeRealloc(struct ossGlobal *world,
		void *(CDECL_ENTRY_FPTR *ossUserMalloc)(struct ossGlobal *world, size_t size),
		void  (CDECL_ENTRY_FPTR *ossUserFree)(struct ossGlobal *world, void *buf),
		void *(CDECL_ENTRY_FPTR *ossUserRealloc)(struct ossGlobal *world, void *buf,
					size_t size));
PUBLIC int DLL_ENTRY        ossSkipPadBytes(struct ossGlobal *world,
					OssBuf *input, unsigned char pad_byte);
PUBLIC OssObjType DLL_ENTRY ossTestObj(struct ossGlobal *world, void *objHndl);
PUBLIC void *DLL_ENTRY      ossUnmarkObj(struct ossGlobal *world,
					    void *objHndl);
    /*************************************************************************/
    /*      SPECIALIZED-TASK FUNCTIONS                                       */
    /*************************************************************************/

PUBLIC int DLL_ENTRY        ossAddInfoObject(struct ossGlobal *world,
				int objSetIndex, void *object);
PUBLIC int DLL_ENTRY        ossAsnValToEncodedOid(struct ossGlobal *world,
				const char *valOID, OssEncodedOID *encodedOID);
PUBLIC int DLL_ENTRY        ossAsnValToEncodedRelOid(struct ossGlobal *world,
				const char *valROID,
				OssEncodedRelOID *encodedROID);

PUBLIC int DLL_ENTRY        ossCallerIsDecoder(struct ossGlobal *world);

PUBLIC int DLL_ENTRY        ossCalTimeToGenTimeString(OssGlobal *world,
				time_t in, int mindiff, char **out);
PUBLIC int DLL_ENTRY        ossCalTimeToGenTimeStruct(OssGlobal *world,
				time_t in, int mindiff, GeneralizedTime **out);
PUBLIC int DLL_ENTRY        ossCalTimeToUTCTimeString(OssGlobal *world,
				time_t in, int mindiff, char **out);
PUBLIC int DLL_ENTRY        ossCalTimeToUTCTimeStruct(OssGlobal *world,
				time_t in, int mindiff, UTCTime **out);

PUBLIC int  DLL_ENTRY       ossCheckConstraints(struct ossGlobal *world,
				int          pdunum,
				void        *data);
#define VALUE_COPIED      0
#define VALUES_EQUAL      0  /* The values are the same */
#define VALUES_NOT_EQUAL  1  /* The values are not the same */

PUBLIC extern int DLL_ENTRY ossCmpValue (struct ossGlobal *world, int pdunum,
				void *originalData,void *copiedData);
PUBLIC extern int DLL_ENTRY ossCpyValue (struct ossGlobal *world, int pdunum,
				void *source, void **destination);
PUBLIC int DLL_ENTRY        ossDotValToEncodedOid(struct ossGlobal *world,
				const char *dotOID, OssEncodedOID *encodedOID);
PUBLIC int DLL_ENTRY        ossDotValToEncodedRelOid(struct ossGlobal *world,
				const char *dotROID,
				OssEncodedRelOID *encodedROID);
PUBLIC int DLL_ENTRY        ossDupWorld(struct ossGlobal *org_world, 
				struct ossGlobal *dup_world);
PUBLIC int DLL_ENTRY        ossEncodedOidToAsnVal(struct ossGlobal *world,
				const OssEncodedOID *encodedOID,
				OssBuf *valOID);
PUBLIC int DLL_ENTRY        ossEncodedOidToDotVal(struct ossGlobal *world,
				const OssEncodedOID *encodedOID,
				OssBuf *dotOID);
PUBLIC int DLL_ENTRY        ossEncodedRelOidToAsnVal(struct ossGlobal *world,
				const OssEncodedRelOID *encodedROID,
				OssBuf *valROID);
PUBLIC int DLL_ENTRY        ossEncodedRelOidToDotVal(struct ossGlobal *world,
				const OssEncodedRelOID *encodedROID,
				OssBuf *dotROID);

PUBLIC void DLL_ENTRY       ossFreeMemory(struct ossGlobal *g, void *p);

PUBLIC int DLL_ENTRY        ossGeneralizedTimeToInts(struct ossGlobal *world,
				char *timeString, unsigned int *year,
				unsigned int *month, unsigned int *day,
				unsigned int *hour, unsigned int *minute,
				unsigned int *second, unsigned int *fraction, 
				unsigned short *precision,
				int *local_uts_mindiff);
PUBLIC int DLL_ENTRY        ossGeneralizedTimeToShorts(struct ossGlobal *,
				char *timeString, unsigned short *year,
				unsigned short *month, unsigned short *day,
				unsigned short *hour, unsigned short *minute,
				unsigned short *second, unsigned int *fraction,
				unsigned short *precision,
				int *local_utc_mindiff);
PUBLIC int DLL_ENTRY        ossGenTimeStringToCalTime(OssGlobal *world,
				char *in, time_t *out);
PUBLIC int DLL_ENTRY        ossGenTimeStructToCalTime(OssGlobal *world,
				GeneralizedTime *in, time_t *out);

PUBLIC unsigned long DLL_ENTRY ossGetCompatibilityFlags(
				struct ossGlobal *world);
PUBLIC int DLL_ENTRY        ossGetConstructedNestingLimit(
				struct ossGlobal *world);
PUBLIC int DLL_ENTRY        ossGetExtensionAddition(struct ossGlobal *world, 
				void *ext, unsigned int extNum, OssBuf *b);
PUBLIC void *DLL_ENTRY      ossGetInfoObject(struct ossGlobal *world,
				int objSetIndex, void *uniquValue);
PUBLIC void *DLL_ENTRY      ossGetInfoObjectSet(struct ossGlobal *,
				int objSetIndex);

PUBLIC void *DLL_ENTRY      ossGetMemory(struct ossGlobal *g, size_t size);
PUBLIC void * DLL_ENTRY     ossGetInitializedMemory(struct ossGlobal *g,
				size_t size);
PUBLIC int DLL_ENTRY        ossGetOssGlobalSize(void);

PUBLIC int DLL_ENTRY        ossGetPrintIndent(struct ossGlobal *world);
PUBLIC int DLL_ENTRY        ossGetRuntimeVersion(struct ossGlobal *world);

PUBLIC int DLL_ENTRY        ossGetSeqSetNestingLimit(struct ossGlobal *world);

PUBLIC void DLL_ENTRY       ossGetUserFieldCpyCmp(struct ossGlobal *world,
				int (CDECL_ENTRY_FPTR **ossUserFieldCpy)(struct ossGlobal *world,
				    OpenType *src, OpenType *dest),
				int (CDECL_ENTRY_FPTR **ossUserFieldCmp)(struct ossGlobal *world,
				    OpenType *src, OpenType *dest));

PUBLIC void DLL_ENTRY       ossGetUserPrint(struct ossGlobal *world,
				FILE **stream,
				int (DLL_ENTRY_FPTR **ossUserPrint)(
				    struct ossGlobal *world, const char *format,
				    ...));
PUBLIC void DLL_ENTRY       ossGetUserVprint(struct ossGlobal *world,
				FILE **stream,
				int (DLL_ENTRY_FPTR **ossUserVprint)(
				    struct ossGlobal *world, const char *fmt,
				    va_list ap));
PUBLIC int DLL_ENTRY        ossInitSync(void);

PUBLIC int DLL_ENTRY        ossIntsToGeneralizedTime(struct ossGlobal *world,
				unsigned int year, unsigned int month,
				unsigned int day, unsigned int hour,
				unsigned int minute, unsigned int second,
				unsigned int fraction, unsigned short precision,
				int local_utc_mindiff, char *timeString); 
PUBLIC int DLL_ENTRY        ossIntsToUTCTime(struct ossGlobal *world,
				unsigned int year, unsigned int month,
				unsigned int day, unsigned int hour,
				unsigned int minute, unsigned int second,
				int local_utc_mindiff, char *timeString); 
PUBLIC int DLL_ENTRY        ossRemoveInfoObject(struct ossGlobal *world,
				int objSetIndex, void *object);

PUBLIC int DLL_ENTRY        ossSetCompatibilityFlags(struct ossGlobal *world,
				unsigned long flag);
PUBLIC int DLL_ENTRY        ossSetConstructedNestingLimit(
				struct ossGlobal *world, int limit);
PUBLIC void DLL_ENTRY       ossSetPrintIndent(struct ossGlobal *world,
				int indent_level);
PUBLIC int DLL_ENTRY        ossSetRuntimeVersion(struct ossGlobal *world,
				OssRuntimeVersion version);

PUBLIC int DLL_ENTRY        ossSetSeqSetNestingLimit(struct ossGlobal *world,
				int limit);
PUBLIC int DLL_ENTRY        ossSetTemporaryBuffer(struct ossGlobal *world,
				OssBuf *buf);

PUBLIC void DLL_ENTRY       ossSetUserFieldCpyCmp(struct ossGlobal *world,
				int (CDECL_ENTRY_FPTR *ossUserFieldCpy)(struct ossGlobal *world,
				    OpenType *src, OpenType *dest),
				int (CDECL_ENTRY_FPTR *ossUserFieldCmp)(struct ossGlobal *world,
				    OpenType *src, OpenType *dest));


PUBLIC void DLL_ENTRY       ossSetUserPrint(struct ossGlobal *world,
				FILE *stream,
				int (DLL_ENTRY_FPTR *ossUserPrint)(
				    struct ossGlobal *world, const char *format,
				    ...));
PUBLIC int DLL_ENTRY        ossSetUserStack(struct ossGlobal *world,
				OssBuf *buf);

PUBLIC void DLL_ENTRY       ossSetUserVprint(struct ossGlobal *world,
				FILE *stream,
				int (DLL_ENTRY_FPTR *ossUserVprint)(
				    struct ossGlobal *world, const char *fmt,
				    va_list ap));

PUBLIC void DLL_ENTRY       ossTermSync(void);

PUBLIC int DLL_ENTRY        ossUTCTimeStringToCalTime(OssGlobal *world,
				char *in, time_t *out);
PUBLIC int DLL_ENTRY        ossUTCTimeStructToCalTime(OssGlobal *world,
				UTCTime *in, time_t *out);
PUBLIC int DLL_ENTRY        ossUTCTimeToInts(struct ossGlobal *world,
				char *timeString, unsigned int *year,
				unsigned int *month, unsigned int *day,
				unsigned int *hour, unsigned int *minute,
				unsigned int *second, int *uts_mindiff);
PUBLIC int DLL_ENTRY        ossUTCTimeToShorts(struct ossGlobal *world,
				char *timeString, unsigned short *year,
				unsigned short *month, unsigned short *day,
				unsigned short *hour, unsigned short *minute,
				unsigned short *second, int *utc_mindiff);

PUBLIC int DLL_ENTRY        ossTimePointToString(OssGlobal *world,
				ossTimePoint *inp, char **dest);
PUBLIC int DLL_ENTRY        ossStringToTimePoint(OssGlobal *world,
				char *inp, ossTimePoint *dest);
PUBLIC ossTimeKind DLL_ENTRY ossGetTimeKind(OssGlobal *world, char *str);
PUBLIC int DLL_ENTRY        ossDurationIntervalToString(OssGlobal *world,
				ossDuration *inp, char **dest);
PUBLIC int DLL_ENTRY        ossStringToDurationInterval(OssGlobal *world,
				char *inp, ossDuration *dest);
PUBLIC int DLL_ENTRY        ossStartPointEndPointIntervalToString(OssGlobal *world,
				ossTimePoint *start, ossTimePoint *end, char **dest);
PUBLIC int DLL_ENTRY        ossStringToStartPointEndPointInterval(OssGlobal *world,
				char *inp, ossTimePoint *start, ossTimePoint *end);
PUBLIC int DLL_ENTRY        ossStartPointDurationIntervalToString(OssGlobal *world,
				ossTimePoint *start, ossDuration *dur, char **dest);
PUBLIC int DLL_ENTRY        ossStringToStartPointDurationInterval(OssGlobal *world,
				char *inp, ossTimePoint *start, ossDuration *dur);
PUBLIC int DLL_ENTRY        ossDurationEndPointIntervalToString(OssGlobal *world,
				ossDuration *dur, ossTimePoint *end, char **dest) ;
PUBLIC int DLL_ENTRY        ossStringToDurationEndPointInterval(OssGlobal *world,
				char *inp, ossDuration *dur, ossTimePoint *end);
PUBLIC int DLL_ENTRY        ossDurationRecIntervalToString(OssGlobal *world,
				ossDuration *dur, int rec, char **dest);
PUBLIC int DLL_ENTRY        ossStringToDurationRecInterval(OssGlobal *world,
				char *inp, ossDuration *dur, int *rec);
PUBLIC int DLL_ENTRY        ossStartPointEndPointRecIntervalToString(OssGlobal *world,
				ossTimePoint *start, ossTimePoint *end, int rec, char **dest);
PUBLIC int DLL_ENTRY        ossStringToStartPointEndPointRecInterval(OssGlobal *world,
				char *inp, ossTimePoint *start, ossTimePoint *end, int *rec);
PUBLIC int DLL_ENTRY        ossStringToStartPointDurationRecInterval(OssGlobal *world,
				char *inp, ossTimePoint *start, ossDuration *dur, int *rec);
PUBLIC int DLL_ENTRY        ossStartPointDurationRecIntervalToString(OssGlobal *world,
				ossTimePoint *start, ossDuration *dur, int rec, char **dest);
PUBLIC int DLL_ENTRY        ossDurationEndPointRecIntervalToString(OssGlobal *world,
				ossDuration *dur, ossTimePoint *end, int rec, char **dest);
PUBLIC int DLL_ENTRY        ossStringToDurationEndPointRecInterval(OssGlobal *world,
				char *inp, ossDuration *dur, ossTimePoint *end, int *rec);
    /*************************************************************************/
    /*      XML-RELATED FUNCTIONS                                            */
    /*************************************************************************/

#define OSS_UTC_DIFF_Z       INT_MAX
#define OSS_UTC_DIFF_ABSENT (INT_MAX - 1)

PUBLIC int DLL_ENTRY        ossBinary2XML(struct ossGlobal *world,
				int               pdunum,
				ossEncodingRules  r_from,
				OssBuf           *b_from, 
				OssBuf           *b_xml);
PUBLIC int DLL_ENTRY        ossDateTimeToInts (struct ossGlobal *world,
				char *dateTimeString, int *year,
				unsigned int *month, unsigned int *day,
				unsigned int *hours, unsigned int *minutes,
				unsigned int *seconds, char **fraction,
				unsigned int *precision,
				int *local_utc_mindiff);
PUBLIC int DLL_ENTRY        ossDateToInts(struct ossGlobal *world,
				char *dateString, int *year,
				unsigned int *month,
				unsigned int *day, int *local_utc_mindiff);
PUBLIC int DLL_ENTRY        ossDurationToInts (struct ossGlobal *world,
				char *durationString,
				ossBoolean *negative,
				unsigned int *year, unsigned int *months,
				unsigned int *days, unsigned int *hours,
				unsigned int *minutes, unsigned int *seconds,
				char **fraction, unsigned int *precision);
PUBLIC int DLL_ENTRY        ossGDayToInts(struct ossGlobal *world,
				char *gDayString, unsigned int *day,
				int *local_utc_mindiff);
PUBLIC int DLL_ENTRY        ossGMonthDayToInts(struct ossGlobal *world,
				char *gMonthDayString, unsigned int *month,
				unsigned int *day, int *local_utc_mindiff);
PUBLIC int DLL_ENTRY        ossGMonthToInts(struct ossGlobal *world,
				char *gMonthString, unsigned int *month,
				int *local_utc_mindiff);
PUBLIC int DLL_ENTRY        ossGYearMonthToInts (struct ossGlobal *world,
				char *gYearMonthString, int *year,
				unsigned int *month, int *local_utc_mindiff);
PUBLIC int DLL_ENTRY        ossGYearToInts(struct ossGlobal *world,
				char *gYearString, int *year,
				int *local_utc_mindiff);
PUBLIC int DLL_ENTRY        ossGetNamespacePrefix(struct ossGlobal *world,
				char *ns, char **prefix);

PUBLIC int DLL_ENTRY        ossGetXMLEncodingRules(struct ossGlobal *world);

PUBLIC int DLL_ENTRY        ossIntsToDate(struct ossGlobal *world, int year,
				unsigned int month, unsigned int day,
				int local_utc_mindiff, char **dateString);
PUBLIC int DLL_ENTRY        ossIntsToDateTime(struct ossGlobal *world, int year,
				unsigned int month, unsigned int day,
				unsigned int hours, unsigned int minutes,
				unsigned int seconds, char *fraction,
				unsigned int precision, int local_utc_mindiff,
				char ** dateTimeString);
PUBLIC int DLL_ENTRY        ossIntsToDuration(struct ossGlobal *world,
				ossBoolean negative, unsigned int year,
				unsigned int months, unsigned int days,
				unsigned int hours, unsigned int minutes,
				unsigned int seconds, char *fraction,
				unsigned int precision, char ** durationString);
PUBLIC int DLL_ENTRY        ossIntsToGDay(struct ossGlobal *world,
				unsigned int day, int local_utc_mindiff,
				char **gDayString);
PUBLIC int DLL_ENTRY        ossIntsToGMonth(struct ossGlobal *world,
				unsigned int month, int local_utc_mindiff,
				char **gMonthString);
PUBLIC int DLL_ENTRY        ossIntsToGMonthDay(struct ossGlobal *world,
				unsigned int month, unsigned int day,
				int local_utc_mindiff, char **gMonthDayString);
PUBLIC int DLL_ENTRY        ossIntsToGYear(struct ossGlobal *world,
				int year, int local_utc_mindiff,
				char **gYearString);
PUBLIC int DLL_ENTRY        ossIntsToGYearMonth(struct ossGlobal *world,
				int year, unsigned int month,
				int local_utc_mindiff, char **gYearMonthString);
PUBLIC int DLL_ENTRY        ossIntsToTime(struct ossGlobal *world,
				unsigned int hours, unsigned int minutes,
				unsigned int seconds, char *fraction,
				unsigned int precision, int local_utc_mindiff,
				char **timeString);
PUBLIC void DLL_ENTRY       ossPrintXML(struct ossGlobal *world,
				char             *encodedData,
				long              length,
				ossBoolean        pretty_print);
PUBLIC int DLL_ENTRY        ossSetNamespacePrefix(struct ossGlobal *world,
				char *ns, char *prefix);
/* Valid DTD kinds */
#define OSS_XDTD_NONE       0 /* use to disable DTD generation */
#define OSS_XDTD_SYSTEM     1
#define OSS_XDTD_PUBLIC     2

PUBLIC int DLL_ENTRY        ossSetXmlDTD(struct ossGlobal *world, char *name,
				char *ExternalID, short dtd_kind);

PUBLIC int DLL_ENTRY        ossSetXMLEncodingRules(struct ossGlobal *world,
				ossEncodingRules rule);

PUBLIC int DLL_ENTRY        ossSetXmlStylesheet(struct ossGlobal *world,
				char *name);
PUBLIC int DLL_ENTRY        ossTimeToInts(struct ossGlobal *world,
				char *timeString,
				unsigned int *hours, unsigned int *minutes,
				unsigned int *seconds, char **fraction,
				unsigned int *precision,
				int *local_utc_mindiff);
PUBLIC int DLL_ENTRY        ossXML2Binary(struct ossGlobal *world,
				int               pdunum,
				ossEncodingRules  r_to,
				OssBuf           *b_xml,
				OssBuf           *b_to);

    /*************************************************************************/
    /*      ENCODING COMPRESSION ROUTINES                                    */
    /*************************************************************************/

typedef int (DLL_ENTRY_FPTR *_System ossCompFcnPtr)(struct ossGlobal *world,
              			unsigned char *outbuf, unsigned long *outlen,
            			unsigned char *inbuf, unsigned long inlen,
				void *data);
typedef unsigned long (DLL_ENTRY_FPTR *_System ossCompEstFcnPtr)(
				unsigned char *inbuf,
				unsigned long inlen, void *info);
PUBLIC int DLL_ENTRY        ossGetCompressDecompressFunctions(
				struct ossGlobal *world,
				ossCompFcnPtr *ossCompressFp,
				ossCompFcnPtr *ossUnCompressFp);
PUBLIC int DLL_ENTRY        ossGetCompressDecompressInfo(
				struct ossGlobal *world, void **info);
PUBLIC int DLL_ENTRY        ossGetCompSizeEstimator(struct ossGlobal *world,
				ossCompEstFcnPtr *ossCompEstFp);
PUBLIC int DLL_ENTRY        ossSetCompressDecompressFunctions(
				struct ossGlobal *world,
				ossCompFcnPtr ossCompressFp,
				ossCompFcnPtr ossUnCompressFp);
PUBLIC int DLL_ENTRY        ossSetCompressDecompressInfo(
				struct ossGlobal *world, void *info);
PUBLIC int DLL_ENTRY        ossSetCompSizeEstimator(struct ossGlobal *world,
				ossCompEstFcnPtr ossCompEstFp);

PUBLIC int DLL_ENTRY        ossCompress(OssGlobal *world, OssBuf *input,
				OssBuf *output, long prefix_len);
PUBLIC int DLL_ENTRY        ossUnCompress(OssGlobal *world, OssBuf *input,
				OssBuf *output, ossBoolean prefix);
PUBLIC int DLL_ENTRY	    ossSkipCompressionPrefix(OssGlobal *world, 
				OssBuf *input, 
				long *orig_len, long *compress_len);
    /*************************************************************************/
    /*      DEBUG FLAGS FUNCTIONS                                            */
    /*************************************************************************/

/* Debug flags controlled by ossSetDebugFlags() and ossGetDebugFlags() */
#define PRINT_DECODING_DETAILS	0x01
#define PRINT_ENCODING_DETAILS	0x02
#define PRINT_DECODER_OUTPUT	0x04
#define PRINT_DECODER_INPUT	0x08
#define PRINT_ENCODER_OUTPUT	0x10
#define PRINT_ENCODER_INPUT	0x20
#define PRINT_ERROR_MESSAGES	0x40
#define PRINT_HEX_WITH_ASCII	0x80

/* the LED trace levels */
#define LTRACE_LEVEL_1		0x100
#define LTRACE_LEVEL_2		0x200
#define LTRACE_LEVEL_3		0x300
#define LTRACE_LEVEL_4		0x400
#define LTRACE_LEVEL_5		0x500
#define LTRACE_LEVEL_6		0x600
#define LTRACE_LEVEL_0		0x700
/* the LED trace mask */
#define LTRACE_LEVEL		0x700
/* Do not trace ISO 8601 time types */
#define LTRACE_NO_TIME_DETAILS	0x800

#define DEBUG_DATA_RESERVED1	0x8000

/*
 * The following defines diagnostic levels by combining the above debug flags
 * into five commonly used groups.
 */

#define OSS_DEBUG_LEVEL_0  0

#define OSS_DEBUG_LEVEL_1       PRINT_ERROR_MESSAGES

#define OSS_DEBUG_LEVEL_2       (PRINT_ERROR_MESSAGES | \
				 PRINT_ENCODER_INPUT  | \
				 PRINT_DECODER_OUTPUT)

#define OSS_DEBUG_LEVEL_3       (PRINT_ERROR_MESSAGES | \
				 PRINT_ENCODER_INPUT  | \
				 PRINT_DECODER_INPUT  | \
				 PRINT_ENCODER_OUTPUT | \
				 PRINT_DECODER_OUTPUT | \
				 PRINT_HEX_WITH_ASCII)

#define OSS_DEBUG_LEVEL_4       (PRINT_ERROR_MESSAGES   | \
				 PRINT_ENCODER_INPUT    | \
				 PRINT_DECODER_INPUT    | \
				 PRINT_ENCODER_OUTPUT   | \
				 PRINT_DECODER_OUTPUT   | \
				 PRINT_HEX_WITH_ASCII   | \
				 PRINT_DECODING_DETAILS | \
				 PRINT_ENCODING_DETAILS)

PUBLIC unsigned long DLL_ENTRY ossGetDebugFlags(struct ossGlobal *world);
PUBLIC int DLL_ENTRY           ossSetDebugFlags(struct ossGlobal *world,
						unsigned long flags);

    /*************************************************************************/
    /*      MEMORY HANDLES FUNCTIONS                                         */
    /*      (OSS API providing optimized dynamic memory management)          */
    /*************************************************************************/

typedef struct ossMemoryHandle OssMemoryHandle;

PUBLIC int DLL_ENTRY         ossCleanMemoryHandle(struct ossGlobal *world,
						    OssMemoryHandle *hdl);
PUBLIC OssMemoryHandle *DLL_ENTRY ossCreateMemoryHandle(struct ossGlobal *world,
						    size_t chunkLength);
PUBLIC int DLL_ENTRY         ossDeleteMemoryHandle(struct ossGlobal *world,
						    OssMemoryHandle *hdl);
PUBLIC OssMemoryHandle *DLL_ENTRY ossGetActiveMemoryHandle(
						    struct ossGlobal *world);
typedef struct ossMemoryHandleStat {
    unsigned int	nodes;			/* number of memory 'pages' */
    size_t		system_allocated;	/* total amount of memory in
						 * all memory pages */
    struct {
	size_t		used_internally;	/* total amount of memory used
						 * by the memory manager */
	size_t		user_allocated;		/* total amount of used memory 
						 * in all memory pages */
	size_t		user_free;		/* total amount of available 
						 * memory */
    } detail;
} OssMemoryHandleStat;

/* Flag settings for ossGetMemoryHandleStat() function */

#define OSS_MH_BRIEF			0 /* do not fill stat.detail     */
#define OSS_MH_DETAIL			1 /* fill stat.detail            */
#define OSS_MH_DETAIL_TRACE_HANDLE	2 /* + tracing for the handle    */
#define OSS_MH_DETAIL_TRACE_BLOCKS	3 /* + tracing for each block    */
#define OSS_MH_DETAIL_TRACE_FRAGMENTS	4 /* + tracing for each fragment *
					   *   allocated within a block  */

#define OSS_MH_NO_PTR_IN_TRACE	0x20	  /* don't print pointer values  *
					   * that change from run to run */

PUBLIC int DLL_ENTRY         ossGetMemoryHandleStat(struct ossGlobal *world,
						    OssMemoryHandle *hdl,
						    OssMemoryHandleStat *stat,
						    unsigned int flags);

PUBLIC int DLL_ENTRY         ossSetActiveMemoryHandle(struct ossGlobal *world,
						    OssMemoryHandle *hdl);
    /*************************************************************************/
    /*      HELPER MACROS FUNCTIONS                                          */
    /*************************************************************************/


#define OSS_STR(value_) \
	oss__CharStr_copy(world, value_)

#define OSS_USTR(value_) \
	(unsigned char *)oss__CharStr_copy(world, (char *)value_)

PUBLIC void *DLL_ENTRY      oss__BitStrCC_copy_encoded(struct ossGlobal *world,
				    unsigned char *value, size_t length);
PUBLIC void *DLL_ENTRY      oss__BmpString_copy(struct ossGlobal *world,
				    unsigned short *value, unsigned int length);
PUBLIC ossBoolean *DLL_ENTRY oss__Bool_copy(struct ossGlobal *world,
				    ossBoolean value);
PUBLIC void *DLL_ENTRY      oss__CC_copy_decoded(struct ossGlobal *world,
				    void *decoded, int pdunum);
PUBLIC char *DLL_ENTRY      oss__CharStr_copy(struct ossGlobal *world,
				    char *value);
PUBLIC char *DLL_ENTRY      oss__CharStr_new(struct ossGlobal *world,
				    unsigned int length);
PUBLIC char *DLL_ENTRY      oss__Char_copy(struct ossGlobal *world, char value);
PUBLIC double *DLL_ENTRY    oss__Double_copy(struct ossGlobal *world,
				    double value);
PUBLIC float *DLL_ENTRY     oss__Float_copy(struct ossGlobal *world,
				    float value);
PUBLIC GeneralizedTime *DLL_ENTRY oss__GeneralizedTime_copy_nullterm(
				    struct ossGlobal *world, char *timestring);
PUBLIC int DLL_ENTRY        oss__GeneralizedTime_setv_nullterm(
				    struct ossGlobal *world,
				    GeneralizedTime *outp, char *timestring);
PUBLIC int *DLL_ENTRY       oss__Int_copy(struct ossGlobal *world, int value);
PUBLIC LONG_LONG *DLL_ENTRY oss__LongLong_copy(struct ossGlobal *world,
				    LONG_LONG value);
PUBLIC long *DLL_ENTRY      oss__Long_copy(struct ossGlobal *world, long value);
PUBLIC void *DLL_ENTRY      oss__OctStrCC_copy_encoded(struct ossGlobal *world,
				    unsigned char *value, size_t length);
PUBLIC void *DLL_ENTRY      oss__OpenType_copy_decoded(struct ossGlobal *world,
				    void *decoded, int pdunum,
				    size_t struct_sz);
PUBLIC void *DLL_ENTRY      oss__OpenType_copy_encoded(struct ossGlobal *world,
				    void *value, long length, size_t struct_sz);
PUBLIC void *DLL_ENTRY      oss__NewOpenType_copy_decoded(struct ossGlobal *world,
				    void *decoded, int pdunum, size_t struct_sz,
				    size_t pdunum_sz, int decoded_offset);
PUBLIC void *DLL_ENTRY      oss__NewOpenType_copy_encoded(struct ossGlobal *world,
				    void *value, long length, size_t struct_sz,
				    int encoded_offset);
PUBLIC void *DLL_ENTRY      oss__Ptr_copy(struct ossGlobal *world, void *ptr);
PUBLIC short *DLL_ENTRY     oss__Short_copy(struct ossGlobal *world,
				    short value);
PUBLIC unsigned char *DLL_ENTRY  oss__UChar_copy(struct ossGlobal *world,
				    unsigned char value);
PUBLIC unsigned int *DLL_ENTRY   oss__UInt_copy(struct ossGlobal *world,
				    unsigned int value);
PUBLIC ULONG_LONG *DLL_ENTRY     oss__ULongLong_copy(struct ossGlobal *world,
				    ULONG_LONG value);
PUBLIC unsigned long *DLL_ENTRY  oss__ULong_copy(struct ossGlobal *world,
				    unsigned long value);
PUBLIC unsigned short *DLL_ENTRY oss__UShort_copy(struct ossGlobal *world,
				    unsigned short value);
PUBLIC UTCTime *DLL_ENTRY   oss__UTCTime_copy_nullterm(struct ossGlobal *world,
				    char *timestring);
PUBLIC int DLL_ENTRY        oss__UTCTime_setv_nullterm(struct ossGlobal *world,
				    UTCTime *outp, char *timestring);
PUBLIC void *DLL_ENTRY      oss__UnbBitStr_copy(struct ossGlobal *world,
				    unsigned char *value, unsigned int length);
PUBLIC void *DLL_ENTRY      oss__UnbCharString_copy(struct ossGlobal *world,
				    char *value, unsigned int length);
PUBLIC void *DLL_ENTRY      oss__UnbCharString_copy_nullterm(
				    struct ossGlobal *world, char *value);
PUBLIC void *DLL_ENTRY      oss__UnbSeqOf_copy(struct ossGlobal *world,
				    void *value, unsigned int length,
				    size_t item_sz);
PUBLIC void *DLL_ENTRY      oss__UnbSeqOf_new(struct ossGlobal *world,
				    unsigned int length, size_t item_sz,
				    ossBoolean do_memset);
PUBLIC void *DLL_ENTRY      oss__UnivString_copy(struct ossGlobal *world,
				    int *value, unsigned int length);

    /*************************************************************************/
    /*      OTHER FUNCTIONS                                                  */
    /*************************************************************************/

#define OSS_PLUS_INFINITY   "PLUS_INFINITY"
#define OSS_MINUS_INFINITY  "MINUS_INFINITY"
#define OSS_NOT_A_NUMBER    "NOT_A_NUMBER"

#define OSS_FORMAT_OK_STATIC (-1) /* returned encoding is some static data */
#define OSS_FORMAT_OK          0  /* encoding is returned in memory allocated
				   * by OssSafeMalloc() */
/* #define OSS_FORMAT_ERROR	any positive ineteger */

typedef unsigned char * (DLL_ENTRY_FPTR *_System OssSafeMallocp)
					(struct ossGlobal *world, OssBuf *buf);

extern int DLL_ENTRY        ossEcnTestMultipleEncodings(struct ossGlobal *world,
				    int            pdunum,
				    OssBuf        *encoded_messages,
				    int            number_of_encoded_messages,
				    unsigned char *padding_bits);

PUBLIC void DLL_ENTRY       ossFreeObjectStack(struct ossGlobal *world);
PUBLIC unsigned long DLL_ENTRY ossGetFormatterBufferSize(
				    struct ossGlobal *world);

/* ossTest()'s helper functions */
PUBLIC char *DLL_ENTRY      ossGetTestFlags(void);
PUBLIC OSS_UINT32 DLL_ENTRY ossGetTestEnv(int *, int *, void **);
PUBLIC int DLL_ENTRY        ossParseString(char *);

PUBLIC int DLL_ENTRY        ossParseEnvironment(void);
PUBLIC int DLL_ENTRY        ossSetFormatterBufferSize(struct ossGlobal *world,
				    unsigned long size);
PUBLIC void DLL_ENTRY       ossSetPaddingBits(struct ossGlobal *,
				    unsigned char);

PUBLIC int DLL_ENTRY        ossSetTestFlags(char *);

#if defined(__vms) && (__INITIAL_POINTER_SIZE + 0) == 64
#pragma pointer_size 32
#endif
PUBLIC int DLL_ENTRY        ossSetTestFlagsEx(int, char *[]);
#if defined(__vms) && (__INITIAL_POINTER_SIZE + 0) == 64
#pragma pointer_size 64
#endif
extern int DLL_ENTRY        ossTestConcatenatedEncodings(struct ossGlobal *world,
					    int            pdunum,
					    OssBuf        *encoded_message);
extern int DLL_ENTRY        ossTestEncoding(struct ossGlobal *world,
					    int            pdunum,
					    OssBuf        *encodedData);
extern int DLL_ENTRY        ossTestMultipleEncodings(struct ossGlobal *world,
				    int            pdunum,
				    OssBuf        *encoded_messages,
				    int            number_of_encoded_messages);
#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
PUBLIC extern int DLL_ENTRY ossVprintWin(struct ossGlobal *, const char *,
					    va_list ap);
#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ */

/*****************************************************************************/
/*  PUBLIC section: osstrace()                                               */
/*****************************************************************************/
/*  When tracing is in effect in the OSS ASN.1 Tools encoder/decoder the     */
/*  user user-replaceable trace routine, osstrace(), is called to trace      */
/*  the value that is being encoded/decoded.  This header file describes     */
/*  the parameters passed to osstrace().                                     */
/*                                                                           */
/*  Detailed descriptions appear after the declarations.                     */
/*****************************************************************************/

/* traceKind: describes the type of TraceRecord */

enum traceKind
{
	endOfContentsTrace = 0, /* end-of-contents octets */
	valueTrace,             /* traceRecord contains a traced value */
	skippedFieldTrace,      /* a value whose type is not recognized
				 * is being skipped */
	messageTrace            /* error message is in the field "value" */
};


/* fieldKind: describes the contents of "fieldNumber".  "fieldKind" is
 *            meaningful only if "fieldNumber" is not 0
 */

enum fieldKind
{
	setOrSequenceField = 0, /* "fieldNumber" is the position of the
				 * component within a SET or SEQUENCE */
	pduNumber,              /* "fieldNumber" is a PDU number */
	setOrSequenceOfElement, /* "fieldNumber" is the position of the
				 * component within a SET OF or SEQUENCE OF
				 * components */
	stringElement           /* "fieldNumber" is the position of the
				 * substring within a constructed STRING */
};

enum prtType
{
	seqsetType = 0,		/* SEQUENCE and SET uses [fieldcount =  n] */
	seqofType,		/* SEQUENCE OF and SET OF use [length = n] */
	choiceType,		/* CHOICE type uses format [index = n] 	   */
	pseudoType,		/* No length info is printed or [not encoded] */
	primeType,		/* All other types use the format	   */
				/* [length = [(not encoded)] nbytes.nbits] */
				/* fragmentation is printed for OCTET	   */
				/* STRING and BIT STRING.		   */
	closeType,		/* Trace message at the end of encoding.   */
	ccType,			/* value is XER encoding ( for CXER only)  */
	usrType			/* value is user formatted XER encoding    */
};

/* tag_length: specifies the tag and length of a value. */

struct tag_length
{
	unsigned long int length;  /* length of type, if definite */
	unsigned short int tag;    /* 16 bits of the form CCTTTTTTTTTTTTTT,
				    * with "CC" the class number, and "T...T"
				    * the tag. (If tag is 0, then "length",
				    * "primitive" and "definite" are
				    * not significant). */
	unsigned int      definite: 1;  /* 1: definite-length encoding */
};

/* traceRecord: OSS ASN.1 Tools trace record */

struct traceRecord
{
	enum traceKind   kind;          /* kind of trace record */
	void             *p;            /* reserved for OSS */
	char             *identifier,   /* SET/SEQUENCE/CHOICE component name*/
			 *typeReference,/* defined type name                 */
			 *builtinTypeName;  /* ASN.1 builtin type defined in *
					     * ISO 8824 or "Character String"*/

	void             *valueName;    /* reserved for future use */

	unsigned         taggingCount;  /* number of entries in the tag&length
					 * or content-end-octet array */

	union            /* tag&length or end-of-contents-octets array. */
	{
		struct tag_length *tag_length;
		int               *depth;
	}                 tagging;

	enum prtType      prtType;	/* Refer to prtType above for details */
	char           	  lenEncoded;	/* Indicate whether length is encoded */
	long              length;	/* Length in bits for all prime types */
					/* fieldcount for SET and SEQUENCE    */
					/* length of components for SET OF    */
					/* choice index for type CHOICE	      */
	int               fragment;	/* Fragment for OCTET STRING and BIT  */
					/* STRING, PER fragment when too long */

	enum fieldKind    fieldKind;   /* kind of value in "fieldNumber" */
	unsigned int      fieldNumber; /* component number, 0 if not
					*  applicable */

	unsigned int      depth;    /* the depth of this value, from 0 on up */

	unsigned int      primitive: 1, /* indicates structure of encoding */
			  implicit;	/* indicate whether tag is implicit */

	char              value[1];     /* the formatted value for simple
					 * type and ANY. If the first byte
					 * is 0, no value is present. */
};


extern void DLL_ENTRY       osstrace(struct ossGlobal *g, struct traceRecord *p,
					size_t traceRecordLen);

/* osstrace(): User-replaceable trace routine.
 *
 * Parameters:
 *   g      - Reserved.  This is always set to NULL for now.
 *   p      - traceRecord, described below.
 *   traceRecordLen - True length of traceRecord, including first \0 in "value"
 *
 * osstrace() is called:
 *
 *      - once for each builtin ASN.1 type, regardless of tagging, with the
 *        field "kind" set to valueTrace.  So given a PDU of value "fooBar":
 *
 *           Sample DEFINITIONS EXPLICIT TAGS ::= BEGIN
 *               fooBar Foo ::= {age 6, living TRUE}
 *               Foo ::= SET {age INTEGER, living [1] [2] Alive}
 *               Alive ::= BOOLEAN
 *           END
 *
 *        it is called called three times with "kind" set to valueTrace - once
 *        for the SET, once for the INTEGER, and once for the BOOLEAN.
 *
 *        When the traceRecord "kind" field is set to valueTrace ...
 *
 *        The field "identifier" contains the component identifier of
 *        the type if one is present in the ASN.1 definition.  So in
 *        the above example, "identifier" will be empty on the call for
 *        the SET, while on the call for the INTEGER it will contain "age",
 *        and "living" on the call for the BOOLEAN.
 *
 *        The field "typeReference" contains the name of the associated ASN.1
 *        typereference, if any.  So in the above example, "typeReference"
 *        will contain "Foo" on the call for the SET, "Alive" on the call
 *        for the BOOLEAN, and will be empty on the call for the INTEGER.
 *
 *        The field "builtinTypeName" contains the name of the ASN.1 builtin
 *        type.  So in the above example, "builtinTypeName" will contain
 *        "SET", "INTEGER", and "BOOLEAN" on the calls as appropriate.
 *        Note that for all character string types "builtinTypeName" is
 *        set to "Character String".  This will be changed in the near future
 *        to reflect the true character string type.
 *
 *        The field "taggingCount" contains the number of entries in the array
 *        of tag_length structs pointed to by tagging.tag_length, and reflects
 *        the number of tags present in the encoding.  Note that an entry
 *        exists in the tag_length array for each ANY and CHOICE value as
 *        though they had tags defined for them in the ASN.1 Standard.  So in
 *        the above example, "taggingCount" is 1 on the calls for the SET and
 *        INTEGER, and on the call for the BOOLEAN "taggingCount" is 3 since
 *        EXPLICIT TAGS is in effect.
 *
 *        The field "tagging.tag_length" points to an array of tag_length
 *        structs.
 *
 *              The field "tagging.tag_length->tag" is the BER tag represented
 *              in the form CCTTTTTTTTTTTTTT with "CC" the class number, and
 *              "TTTTTTTTTTTTTT" the tag number.  Since the ANY and CHOICE
 *              types do not have tags of their own, the last entry in the
 *              tag_length array for these types always has 0 as the value of
 *              the "tag" field.  So in the above example, "tag" is 0x11 on the
 *              call for the the SET.
 *
 *              The field "tagging.tag_length->length" is the length of the
 *              encoded value if the length is of definite form (i.e.,
 *              "definite" is 1).
 *
 *              The field "tagging.tag_length->definite" indicates when the
 *              length is definite or indefinite.  This field is significant
 *              only if "tag" is non-zero.
 *
 *        The field "fieldKind" indicates whether the number in "field" is:
 *        -- the position of a component within a SET or SEQUENCE, or
 *        -- the PDU number assigned by the ASN.1 compiler, or
 *        -- the position of a component within a SET OF or SEQUENCE OF, or
 *        -- the position of a substring within a constructed string.
 *        "fieldKind" is significant only if "field" is non-zero.  So in
 *        the example above, "fieldKind" has a value of pduNumber on the
 *        call for the SET, and a value of setOrSequenceField on the calls for
 *        the INTEGER and BOOLEAN.
 *
 *        The field "fieldNumber" is a ordinal number indicating the position
 *        of a component within a SET, SEQUENCE, SET OF, SEQUENCE OF, or
 *        constructed string, or the PDU number assigned by the ASN.1 compiler.
 *        So in the above example, "fieldNumber" is 1 (the PDU number) on the
 *        call for the SET, 1 (the position of the component "age") on the
 *        call for the INTEGER, and 2 (the position of the component "living"
 *        on the call for the BOOLEAN.
 *
 *        The field "depth" is the level of nesting of the value relative to
 *        the outermost type, which has a "depth" value of 0.  So in the above
 *        example, "depth" is 0 on the call for the SET, and 1 on the calls
 *        for the INTEGER and BOOLEAN.
 *
 *        The field "primitive" is set to 1 if the builtin ASN.1 type is
 *        simple (i.e., the primitive/constructed bit in the identifier
 *        octet is set to 0), so it is 0 for SET, SEQUENCE, SET OF, SEQUENCE
 *        OF, and CHOICE because they are structured. It is also set to 0 if
 *        the type is an ANY.  It is 1 for all other builtin types.
 *
 *        The field "value" contains formatted data if the builtin type
 *        is simple or ANY, regardless of tagging.  Hence, in the above
 *        example the call for SET will not contain any data in "value"
 *        (because the builtin type is a constructed type), while for the
 *        INTEGER and BOOLEAN types "value" will contain formatted data.
 *        The maximum number of bytes of formatted data placed into "value"
 *        is controlled by the external variable "asn1chop".  If "asn1chop"
 *        is set to 0 the maximum length of the traced value is determined
 *        by the maximum internal buffer size variable, "ossblock".
 *
 *      - once for each end-of-contents octets pair that is generated/
 *        encountered while encoding/decoding a constructed value whose
 *        length is of the indefinite-length form.  A call with a "valueTrace"
 *        record is always made to osstrace() before one is made with an
 *        "endOfContentsTrace" record.
 *
 *        A single "endOfContentsTrace" call is made to osstrace() for each
 *        builtin type that is processed if the indefinite-length form of
 *        encoding is used.  If the builtin type is a structured type (CHOICE,
 *        SET, SEQUENCE, SET OF, SEQUENCE OF) then there may be multiple
 *        "valueTrace" and possible "endOfContentsTrace" calls made to
 *        osstrace() before the matching "endOfContentsTrace" call is made.
 *
 *        When the traceRecord "kind" field is set to endOfContentsTrace ...
 *
 *        The field "taggingCount" contains the number of entries in the array
 *        of "depth" indicators pointed to by tagging.depth, and reflects
 *        the nesting of each pair of end-of-contents-octets associated with
 *        the builtin type being encoded/decoded.  So in the above example,
 *        if indefinite-length encoding is being used, "taggingCount" will
 *        be 1 on the call for the SET (since it has a single constructed
 *        tag), and 2 on the call for the BOOLEAN (since it has two explicit
 *        tags, for which the "constructed" bit in the encoding must be set).
 *
 *        The field "tagging.depth" points to an array of "depth" indicators
 *        that reflect the nesting of each pair of end-of-contents-octets
 *        associated with a builtin type.  So in the above example, if
 *        indefinite-length encoding is being used, "tagging.depth" will point
 *        to a single 0 on the call for the SET since it has a single tag for
 *        which the constructed bit is set; while on the call for the BOOLEAN
 *        "tagging.depth" will point to an array whose two entries are 1 and 2
 *        since there are two explicit tags on the BOOLEAN.
 *
 *        All other fields in the traceRecord are insignificant for an
 *        endOfContentsTrace record.
 *
 *      - once for each value that is skipped while decoding, with a "kind"
 *        value of skippedFieldTrace.  The skippedFieldTrace "kind" is just
 *        means of indicating that an unexpected value was encountered in the
 *        message and is being skipped.  This is not an error if the type is
 *        extensible.
 *
 *        When the traceRecord "kind" field is set to skippedFieldTrace ...
 *
 *        The field of the traceRecord are the same as when "kind" is set to
 *        valueTrace, except that:
 *        -- the skipped value is always reported as having one tag, hence
 *        -- there is only one entry in the tag_length array.
 *        -- the content of the field "value" is always "<skipped>", and
 *        -- "typeReference" is always NULL.
 *
 *      - once for each error message issued, in which case the "kind" field
 *        is set to messageTrace.
 *
 *        When the traceRecord "kind" field is set to messageTrace the "value"
 *        field contains the error message, and other fields are
 *        insignificant.
 */

/* tag_length: describes the tag and length of a value.
 *
 *            "tag" is 0 if the value is an ANY or CHOICE value, in which
 *             case "definite" is not significant since ANY and CHOICE do
 *             not have a tag of their own.
 *
 *             If "tag" is not 0, "definite" indicates whether the value
 *             is encoded using definite- or indefinite-length form.
 *
 *             If "definite" is 1, "length" is the length of the value, else
 *             it is not significant (indefinite-length encoding was used).
 */

/* tagging: tag&length or end-of-contents-octets array.
 *
 *      The tag and length array, tag_length, is present if this
 *      is a valueTrace or skippedFieldTrace record.  There is one array
 *      entry for each tag present in the encoding of a given value, so
 *      "[1] EXPLICIT [2] EXPLICIT INTEGER" gets three tag_length
 *      array entries, where each entry describes the tag and length
 *      information that precedes the value.
 *
 *      The depth array, "depth", is present only if this is a
 *      endOfContentsTrace record.  There is one array entry for each
 *      indefinite length present in the encoding of a value, so
 *      "[1] EXPLICIT [2] EXPLICIT INTEGER" gets two "depth" entries
 *      corresponding to the two explicit tags, where the value of each
 *      tag indicates the depth of the tagged value relative to outmost type
 *      that contains the INTEGER (e.g., relative to the containing SET).
 */

/* Odds and ends:
 *
 * - When the value of a field is not significant the field is set to 0.
 */

/* Augmenting for Packed Encoding Rule (PER) tracing.
 * 
 * PER does not encode tag for any ASN.1 type. For some types, length
 * may or may not be encoded. PER does not always use octet aligned
 * encoding, therefore, the length should be in unit of bit. 
 *
 * We classified ASN.1 types in to the following:
 *
 * (1). For all primitive types (including ANY), the prtType in traceRecord
 * 	is set to primeType, length is the total length of the content
 *	in bits. The file osstrace.c prints length in the format
 *	length = nbytes.nbits, and the total length should be 8*nbytes+nbits.
 *	If the length is not encoded, "(not encoded)" will be added to the
 *	output string. For BIT STRING with length longer than 64K (bits), and
 *	for OCTET STRING longer that 16K (bytes), fragmentation is needed 
 *	and this is indicated by the string "fragment = n" after the length.
 *	The fragmentation index is field fragment in traceRecord.
 * (2). For SEQUENCE and SET, prtType is seqsetType. In this case, the length
 *	in traceRecord is the fieldcount of the SEQUENCE or SET.
 * (3). For SEQUENCE OF and SET OF, prtType is seqofType, and the length
 *	in traceRecord is the count of components in the SEQUENCE OF (SET OF).
 * (4). For CHOICE, prtType is choiceType, and the length field in
 *	traceRecord indicates the choice index.
 * (5). Total number of bits for the entire encoding is reported at the end
 *	of encoding and decoding. The prtType for this trace is closeType.
 */

/*****************************************************************************/
/*  NON-PUBLIC section: apiTbl DLL definition                                */
/*****************************************************************************/

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
#if defined(__alpha)
#define ossArg LONG_LONG
#elif defined(WINDOWS_X64) || defined(WINDOWS_ITANIUM_64BIT)
#define ossArg void *
#else
#define ossArg int
#endif /* __alpha */
#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ */

#if defined(_WINDOWS) || defined(_WIN32)
struct _string_data;
#endif /* _WINDOWS || _WIN32 */





#if !defined(OSSASN1_H)
/*****************************************************************************/
/*  PUBLIC section: C SAX (Simple API for XML) interface definitions         */
/*****************************************************************************/
/* SAX flags */

#define OSS_SAX_NO_NAMESPACES	1
#define OSS_SAX_NULLTERM_DATA	2
#define OSS_SAX_GET_USER_ERRORS 4
/* Error severity enumeration passed to the error() callbacks */

typedef enum { OssWarning, OssError, OssFatal } OssErrSeverity;

/* SAX structures used by the callback functions */

typedef struct {
    unsigned char *uri;
    unsigned char *localname;
    unsigned char *qname;
    /* Index fields are only populated by ossxDecodeFastInfoset() */
    OSS_UINT32 uri_idx;
    OSS_UINT32 localname_idx;
    OSS_UINT32 prefix_idx;
    OSS_UINT32 qname_idx;
} OssXMLName;

typedef struct _OssXMLAttributes {
    OssXMLName    name;
    unsigned char *value;
    unsigned int  length;
    struct _OssXMLAttributes *next;
    OSS_UINT32    format;	/* encoding algorithm, restricted alphabet or
				 * encoding format */
    /* Index field is only populated by ossxDecodeFastInfoset() when value
     * is added to the vocabulary, in all other cases it is zero */
    OSS_UINT32 value_idx;
} OssXMLAttributes;

typedef enum { OssStAbsent, OssStYes, OssStNo } OssStandalone;
typedef enum { OssSAXOK, OssSAXDecoderError, OssSAXUserCancel } OssSAXStatus;

/* SAX event table - unused events may be left NULL */

typedef struct {
    unsigned int version;
    int (CDECL_ENTRY_FPTR *error)(void *user_data, int errorcode, const unsigned char *msg,
	    OssErrSeverity severity);
/* Document */
    int (CDECL_ENTRY_FPTR *startDocument)(void *user_data);
    int (CDECL_ENTRY_FPTR *endDocument)(void *user_data);
/* XML declaration */
    int (CDECL_ENTRY_FPTR *xmlDecl)(void *data, const unsigned char *version, 
			const unsigned char *encoding,
			OssStandalone standalone);
/* DTD */
    int (CDECL_ENTRY_FPTR *startDoctypeDecl)(void *data, const unsigned char *name,
			const unsigned char *sysid,
			const unsigned char *pubid, int has_internal_subset);
    int (CDECL_ENTRY_FPTR *endDoctypeDecl)(void *data, const unsigned char *name);
    int (CDECL_ENTRY_FPTR *unparsedEntityDecl)(void *data, const unsigned char *entityName, 
			const unsigned char *sysid, const unsigned char *pubid,
			const unsigned char *notationName);
    int (CDECL_ENTRY_FPTR *notationDecl)(void *data, const unsigned char *notationName, 
			const unsigned char *sysid, const unsigned char *pubid);
/* Content */
    int (CDECL_ENTRY_FPTR *startElement)(void *user_data, const OssXMLName *name,
			const OssXMLAttributes *attr);
    int (CDECL_ENTRY_FPTR *endElement)(void *user_data, const OssXMLName *name);
    int (CDECL_ENTRY_FPTR *characters)(void *user_data, const unsigned char *chars, 
			unsigned int length);
    int (CDECL_ENTRY_FPTR *startPrefixMapping)(void *user_data, const unsigned char *prefix,
			const unsigned char *uri);
    int (CDECL_ENTRY_FPTR *endPrefixMapping)(void *user_data, const unsigned char *prefix);
    int (CDECL_ENTRY_FPTR *processingInstruction)(void *user_data, const unsigned char *target,
			const unsigned char *chars, unsigned int length);
    int (CDECL_ENTRY_FPTR *comment)(void *user_data, const unsigned char *chars,
			unsigned int length);
    int (CDECL_ENTRY_FPTR *startCDATA)(void *user_data);
    int (CDECL_ENTRY_FPTR *endCDATA)(void *user_data);
    int (CDECL_ENTRY_FPTR *startEntity)(void *user_data, const unsigned char *name);
    int (CDECL_ENTRY_FPTR *endEntity)(void *user_data, const unsigned char *name);
    int (CDECL_ENTRY_FPTR *unexpEntityRef)(void *data, const unsigned char *entityName, 
			const unsigned char *sysid, const unsigned char *pubid);
    int (CDECL_ENTRY_FPTR *characters_binary)(void *user_data, const unsigned char *in_str_bin,
                	unsigned int in_length, OSS_UINT32 in_format);
} OssSAXEventTable;



PUBLIC int DLL_ENTRY ossSAXParseXML(OssGlobal *in_ctx, OssBuf *in_msg, 
			void *in_data, OssSAXEventTable *in_handler);

PUBLIC int DLL_ENTRY ossSAXGetPosition(OssGlobal *env, unsigned int *fragment,
	unsigned int *offset);
PUBLIC int DLL_ENTRY ossSAXCleanup(OssGlobal *world);
PUBLIC int DLL_ENTRY ossSAXSetFeatureFlags(OssGlobal *world, OSS_UINT32 flags);
PUBLIC OSS_UINT32 DLL_ENTRY ossSAXGetFeatureFlags(OssGlobal *world);
PUBLIC int DLL_ENTRY ossSAXFeatureSupported(OssGlobal *world, OSS_UINT32 flags);
PUBLIC OssSAXStatus DLL_ENTRY ossSAXGetStatus(OssGlobal *world);

/*****************************************************************************/
#endif /* OSSASN1_H */

/*****************************************************************************/
/*  NON-PUBLIC section: data alignment section - revert to user-defined data */
/*  alignment                                                                */
/*****************************************************************************/

#ifdef __cplusplus
}
#endif

#if defined(macintosh) && defined(__CFM68K__)
#pragma import reset
#endif

#if defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32) \
			|| defined(WINCE) || defined(_WIN64))
#pragma pack(pop, ossPacking)
#elif defined(_MSC_VER) && (defined(_WINDOWS) || defined(_MSDOS))
#pragma pack()
#elif defined(__BORLANDC__) && (defined(__WIN32__) || defined(__MSDOS__))
#pragma option -a.
#elif defined(__IBMC__) && defined(__WIN32__)
#pragma pack()
#elif defined(__WATCOMC__) && (defined(__NT__) || defined(__WINDOWS__) \
			|| defined(__DOS__))
#pragma pack(pop)
#endif /* _MSC_VER && _WIN32 */

/*****************************************************************************/
/*  PUBLIC section: type definition used in osak memory manager              */
/*****************************************************************************/
#ifndef _OSAK_BUFFER_
#define _OSAK_BUFFER_

typedef struct osak_buffer {
    struct osak_buffer *next;          /* next element in list */
    unsigned char      *buffer_ptr;    /* start of actual buffer */
    unsigned long int   buffer_length; /* size of actual buffer */
    unsigned char      *data_ptr;      /* start of user data */
    unsigned long int   data_length;   /* length of user data */
    unsigned long int   reserved [4];
} osak_buffer;

#endif /* !_OSAK_BUFFER_ */


#define OSSASN1_H
#endif /* !OSSASN1_H ... */

