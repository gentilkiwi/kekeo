/*****************************************************************************/
/* Copyright (C) 2013 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/*************************************************************************/
/* FILE: @(#)ossmmgmt.h	16.7  13/02/25       */
/*************************************************************************/
/** @file
 *  @brief  Declarations and prototypes needed for SOED Memory Managers.
 *
 *****************************************************************************/


#ifndef OSSMMGMT_H
#define OSSMMGMT_H

#include "ossasn1.h"

enum errcode {
    moreInput,          /* input is exhausted and more was requested;
			   context indicates number of bytes requested */
			/* decode returns MORE_INPUT (not a negative
			   error code) */
    moreOutput,         /* requests for output exceed restraint
			   or space provided by user buffer;
			   context indicates bytes allocated so far
			   plus amount requested */
			/* decode returns MORE_BUF */
    zeroBytesRequested, /* memory request for zero bytes.
			   This should not happen; report error to OSS;
			   context ignored */
			/* decode returns FATAL_ERROR */
    sizeTooBig,         /* request to allocate more than 'ossblock' bytes;
			   context indicates number of bytes requested;
			   This should not happen; report error to OSS */
			/* decode returns FATAL_ERROR */
    outOfMemory,        /* memory allocation failure; context indicates
			   number of bytes requested */
			/* decode returns OUT_MEMORY */
    invalidObject,      /* unrecognized memory object passed in argument
			   to function; context 0 means object not recognized,
			   1 means control information within object is flawed */
			/* decode returns FATAL_ERROR */
    memmgrUndefinedErr, /* error OSS has not anticipated; e.g., I/O Error;
			   handlerr prints context.
			   (I cannot print context as a hex value
			   with the current error message code <---) */
			/* decode returns FATAL_ERROR */
    decoderInputEOF,	/* decoder input file EOF detected while
			   initializing decoder input stream --> no data
			   to proceed.
			   decode returns EOF_INPUT_FILE */
    inputFileOpen,	/* decoder/encoder cann't open input file */
    compressInit,	/* an error was occured while accessing compressor stuff */
    compressError,	/* an error was occured while compressing output or unpacking *
			   input data, context is a compressor own error code */
    badEncoding,	/* decoder input is bad or corrupted */
    ossMemmgrErr 	/* same as memmgrUndefinedErr but with return codes 130-150
			   instead of 18 (FATAL_ERROR) */
};

/* Context information for OSS memory managers errors */
#define cantOpenInputFile             1L
#define cantCloseInputFile            2L
#define cantOpenOutputFile            3L
#define cantCloseOutputFile           4L
#define errorWritingToFile            5L
#define errorReadingFromFile          6L
#define cantOpenTemporaryFile         7L
#define cantCloseTemporaryFile        8L
#define cantRemoveTemporaryFile       9L
#define objectTypeNotRecognized      10L
#define deferedValueInInitialBuffer  11L
#define incorrectOffsetToDeferedValue 12L
#define endOfInputFile               13L
#define errorWritingToSocket         14L
#define errorReadingFromSocket       15L
#define cantLoadSocketDLL            16L
#define cantGetProcAddress           17L
#define invalidSocketHandle          18L
#define cannotMarkOutputBuffer	     19L
#define cannotSwapInputObject	     20L
#define timeoutWritingToSocket       21L
#define timeoutReadingFromSocket     22L

extern void     DLL_ENTRY handlerr(struct ossGlobal *, enum errcode err, void * context);
extern int      DLL_ENTRY dpduWalk(struct ossGlobal *, int, void *, void *,
			void (DLL_ENTRY_FPTR *_System freer)(struct ossGlobal *, void *));
extern unsigned long DLL_ENTRY ossGetByteOffset(struct ossGlobal *world);
void  DLL_ENTRY ossFreer(struct ossGlobal *, void *);

int             DLL_ENTRY ossMemMgrId(struct ossGlobal *); 

unsigned char  *DLL_ENTRY dopenIn(struct ossGlobal *, void **p_hdl, unsigned long *inlen);
unsigned long   DLL_ENTRY dclosIn(struct ossGlobal *, void **p_hdl, size_t bytes_decoded);
unsigned char  *DLL_ENTRY dswapIn(struct ossGlobal *, void **p_hdl, size_t *inlen);
void            DLL_ENTRY dopenOut(struct ossGlobal *, void *hdl, unsigned long length,
                        unsigned long limit);
unsigned long   DLL_ENTRY dclosOut(struct ossGlobal *, void **p_hdl);
void           *DLL_ENTRY dallcOut(struct ossGlobal *, size_t size, char root);
void            DLL_ENTRY openWork(struct ossGlobal *);
void            DLL_ENTRY closWork(struct ossGlobal *);
void           *DLL_ENTRY allcWork(struct ossGlobal *, size_t size);
unsigned char  *DLL_ENTRY lockMem(struct ossGlobal *, void *hdl);
void            DLL_ENTRY unlokMem(struct ossGlobal *, void *hdl, char free);
void            DLL_ENTRY pushHndl(struct ossGlobal *, void *);
unsigned char  *DLL_ENTRY popHndl(struct ossGlobal *, void **handl, size_t length);
void            DLL_ENTRY drcovObj(struct ossGlobal *, int pdu_num, void * hdl, void *ctl_tbl);

unsigned char  *DLL_ENTRY eopenIn(struct ossGlobal *, void *lock, size_t length);	/* Clear encoder input-memory resources */
unsigned char  *DLL_ENTRY eswapIn(struct ossGlobal *, void *unlock, void *lock, size_t length);	/* Swap new data into input memory */
void            DLL_ENTRY eclosIn(struct ossGlobal *, void * unlock); /* Free encoder input-memory resources */

unsigned char  *DLL_ENTRY eopenOut(struct ossGlobal *, void **object, size_t *outlen, char queue);   /* Clear encoder output-memory resources */
unsigned char  *DLL_ENTRY eswapOut(struct ossGlobal *, void **object, size_t used, size_t *outlen);  /* Dispose of output data and get memory */
unsigned char  *DLL_ENTRY exferObj(struct ossGlobal *, void **, void **, unsigned long *, unsigned long);
unsigned char  *DLL_ENTRY dxferObj(struct ossGlobal *world, void **inn, void **out, size_t *tOffset, unsigned long *toLength);
unsigned char  *DLL_ENTRY dxferDeferObj(struct ossGlobal *world, void **in, void **out, size_t *bufpos, unsigned long *length, unsigned long *offset);
OssObjType      DLL_ENTRY dxferEnd(struct ossGlobal *world, void **out);
unsigned char  *DLL_ENTRY asideBegin(struct ossGlobal *world, void **objectTo, size_t used, size_t *lengthTo);
unsigned char  *DLL_ENTRY asideSwap(struct ossGlobal *world, void **objectTo, size_t used, size_t *lengthTo);
void           *DLL_ENTRY asideEnd(struct ossGlobal *world, void *object, size_t used);
unsigned char  *DLL_ENTRY setDump(struct ossGlobal *world, void **objectTo, void *set, size_t *lengthTo);
unsigned long   DLL_ENTRY eclosOut(struct ossGlobal *, void **object, size_t used, char low);        /* Free encoder output-memory resources */
void            DLL_ENTRY ercovObj(struct ossGlobal *);	/* Free all encoder memory resources */
void            DLL_ENTRY ossSetSort(struct ossGlobal *, void *, unsigned char ct);	/* Order set by comparing through "ossObjCmp" */
unsigned char   DLL_ENTRY egetByte(struct ossGlobal *world, void *inn, unsigned long offset);
extern int      DLL_ENTRY ossMinit(struct ossGlobal *world);
extern void     DLL_ENTRY ossMterm(struct ossGlobal *world);
void *DLL_ENTRY _ossMarkObj(struct ossGlobal *world, OssObjType objType, void *object);
void *DLL_ENTRY _ossUnmarkObj(struct ossGlobal *world, void *objHndl);
void *DLL_ENTRY _ossGetObj(struct ossGlobal *world, void *objHndl);
OssObjType DLL_ENTRY _ossTestObj(struct ossGlobal *world, void *objHndl);
void  DLL_ENTRY _ossFreeObjectStack(struct ossGlobal *world);
void  DLL_ENTRY _ossSetTimeout(struct ossGlobal *world, long timeout);
int   DLL_ENTRY _ossGetBuffer(struct ossGlobal *world, OssBufExtended *buf);
int   DLL_ENTRY _ossSetBuffer(struct ossGlobal *world, OssBufExtended *buf);
int   DLL_ENTRY _ossOpenDecoderInputFile(struct ossGlobal *world, char *fname);
int   DLL_ENTRY _ossCloseDecoderInputFile(struct ossGlobal *world);
int   DLL_ENTRY _ossOpenEncoderOutputFile(struct ossGlobal *world, char *fname);
int   DLL_ENTRY _ossCloseEncoderOutputFile(struct ossGlobal *world);
long  DLL_ENTRY _ossSetMinFileSize(struct ossGlobal *world, long minsize);
long  DLL_ENTRY _ossGetMinFileSize(struct ossGlobal *world);
void  DLL_ENTRY _ossSetUserMallocFreeRealloc(struct ossGlobal *world,
		void *(CDECL_ENTRY_FPTR *ossUserMalloc)(struct ossGlobal *world, size_t size),
		void  (CDECL_ENTRY_FPTR *ossUserFree)(struct ossGlobal *world, void *buf),
		void *(CDECL_ENTRY_FPTR *ossUserRealloc)(struct ossGlobal *world, void *buf, size_t size));
void  DLL_ENTRY _ossGetUserMallocFreeRealloc(struct ossGlobal *world,
		void *(CDECL_ENTRY_FPTR **ossUserMalloc)(struct ossGlobal *world, size_t size),
		void  (CDECL_ENTRY_FPTR **ossUserFree)(struct ossGlobal *world, void *buf),
		void *(CDECL_ENTRY_FPTR **ossUserRealloc)(struct ossGlobal *world, void *buf, size_t size));

#endif /* !OSSMMGMT_H */
