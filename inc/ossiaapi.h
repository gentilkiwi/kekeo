/*
 * Copyright (C) 2013 OSS Nokalva, Inc.  All rights reserved.
 *
 * FILE: @(#)ossiaapi.h	16.36  13/01/29
*/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC. AND
 * MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/*****************************************************************************/
/*                                                                           */
/*           Declare the types used in the Interpretive ASN.1 API            */
/*                                                                           */
/*****************************************************************************/
#ifndef OSSIAAPI_H
#define OSSIAAPI_H

#include "ossasn1.h"

/* Short aliases for platforms where C compiler truncates 30+ names */
#ifdef __vms
#define ossPrintASN1DescriptionOfInfoObjSet ossPrintASN1DescOfInfoObjSet
#define ossPrintASN1DescriptionOfInfoObject ossPrintASN1DescOfInfoObject
#define ossReferencedComponentFieldHandle   ossRefComponentFieldHandle
#define ossReferencedComponentFieldHandleByTypeHandle ossRefComponentFieldHandleByTypeHandle
#define ossGetTypeHandleOfActualTypeCarriedByOpenType ossGetTHdlOfActTCarriedByOOT
#define ossGetTypeHandleOfActualTypeCarriedByOpenTypeHandle ossGetTHdlOfActTCarriedByOTHandle
#define ossNumberOfReferencedComponents ossNumberOfRefdComponents
#define ossNumberOfReferencedComponentsByTypeHandle ossNumberOfRefdComponentsByTypeHandle
#endif

typedef void *TypeHndl;		/* handle used in referencing types */
typedef void *FieldHndl;

#define INDEFLENGTH   -1       /* This value is returned by ossEncodingLength()
                                * for INDEFINITE length encoded values. */

#define BADLENGTH     -2       /* This value is returned by ossEncodingLength(),
                                * ossEncodingIdentifierLength(), and
				* ossEncodingHeaderLength() in the case of a
				* misencoded value or zero length encoding */

/* ASN.1 builtin types sorted alphabetically and assigned an enumerator */


typedef enum ASN1Type { 
	asn1UnknownType       = 0,
	asn1ANY               = 1,
	asn1BIT_STRING        = 2,
	asn1BMPString         = 3,
	asn1BOOLEAN           = 4,
	asn1CHARACTER_STRING  = 5,
	asn1CHOICE            = 6,
	asn1CLASS             = 7,
	asn1DATE              = 8,
	asn1DATE_TIME         = 9,
	asn1DURATION          = 10,
	asn1EMBEDDED_PDV      = 11,
	asn1ENUMERATED        = 12,
	asn1EXTERNAL          = 13,
	asn1GeneralizedTime   = 14,
	asn1GeneralString     = 15,
	asn1GraphicString     = 16,
	asn1IA5String         = 17,
	asn1INSTANCE_OF       = 18,
	asn1INTEGER           = 19,
	asn1NULL              = 20,
	asn1NumericString     = 21,
	asn1ObjectDescriptor  = 22,
	asn1OBJECT_IDENTIFIER = 23,
	asn1OCTET_STRING      = 24,
	asn1OID_IRI           = 25,
	asn1OpenType          = 26,
	asn1PrintableString   = 27,
	asn1REAL              = 28,
	asn1RELATIVE_OID      = 29,
	asn1RELATIVE_OID_IRI  = 30,
	asn1SEQUENCE          = 31,
	asn1SEQUENCE_OF       = 32,
	asn1SET               = 33,
	asn1SET_OF            = 34,
	asn1TeletexString     = 35,
	asn1TIME              = 36,
	asn1TIME_OF_DAY       = 37,
	asn1UniversalString   = 38,
	asn1UTCTime           = 39,
	asn1UTF8String        = 40,
	asn1VideotexString    = 41,
	asn1VisibleString     = 42,
	asn1ArbitraryType     = 43
} ASN1Type;

#define IAAPI_LAST_ASN1Type  asn1ArbitraryType

/* Types compatible codes */
typedef enum TypesCompatibilityCodes {
    compatible = 0,                  /* Types are compatible */
    differentTypes = 1,              /* Types are not identical */
    defaultsDifferent = 2,           /* Default values are not the same */
    onlyOneHasDefault = 3,           /* Only one type has a default value */
    oneHasPointerOtherDoesnt = 4,    /* Only one type has a POINTER directive */
    numberOfComponentsDifferent = 5, /* Different number of components */
    oneIsOptionalOtherIsnt = 6,      /* Only one type is OPTIONAL */
    oneIsExtensibleOtherIsnt = 7,    /* Only one type is extensible */
    differentNamedItems = 8,         /* Different component identifiers */
    differentKinds = 9,              /* Different type representations */
    componentsHaveDifferentKinds = 10,/* Different component representations */
    differentSubIdNumber = 11,       /* Different number of sub-identifiers in
                                      * an OBJECT IDENTIFIER with the OBJECTID
                                      * directive */
    differentSubIdTypes = 12,        /* Different types of sub-identifiers in
                                      * an OBJECT IDENTIFIER with the OBJECTID
                                      * directive */
    differentSize = 13,              /* Different size of INTEGER or REAL values */
    type1IsPointerOfTypeRef2 = 14,   /* Two types reference the other
                                      * type but the first one has the
                                      * POINTER directive */
    type2IsPointerOfTypeRef1 = 15,   /* Two types reference the other type
                                      * but the second one has the POINTER
                                      * directive */
    differentSizeOfLengthField = 16, /* Different sizes of the length field in
                                      * type representations */
    differentRulesInEncodedBy = 17,  /* Different encoding rules specified in
                                      * ENCODED BY of ContentsConstraint. */
    differentContainedTypes = 18,     /* Different contained types in
                                      * ContentsConstraint. */
    onlyOneWasRemoved = 19           /* A field in only one type has been removed with ASN1.Remove. */
} TypesCompatibilityCodes;


/* ASN.1 tag classes */
typedef enum ASN1TagClass {
	UNIVERSAL, APPLICATION, CONTEXT_SPECIFIC, PRIVATE, NULLENCODING
} ASN1TagClass;


typedef int IAAPI_ERRTYPE;     /* Datatype for IAAPI error codes */

/* IAAPI ERROR CODES */
#define IAAPI_NOERROR      0   /* No error occurred */
#define IAAPI_OUTMEMORY    1   /* No more memory can be allocated */
#define IAAPI_MEM_ERROR    2   /* Memory violation error occurred */
#define IAAPI_ACCESS_SERIALIZATION 3 /* Access serialization error occurred */
#define IAAPI_BADNULL      4   /* Not "NULL" value */
#define IAAPI_TOOBIG       5   /* Value exceeds size constraint */
#define IAAPI_BADREAL      6   /* Not a valid REAL value */
#define IAAPI_BADTIME      7   /* Not a valid UTCTime, GeneralizedTime or 8601 time value */
#define IAAPI_BADOBJID     8   /* Not a valid OBJECT IDENTIFIER value */
#define IAAPI_BADANY       9   /* Bad ANY or OpenType value */
#define IAAPI_BADNAME     10   /* Bad INTEGER or ENUMERATED name */
#define IAAPI_BADNMD      11   /* Bad BIT STRING NAMED NUMBER value */
#define IAAPI_NOTSUP      12   /* Type not supported */
#define IAAPI_BADNUM      13   /* Bad INTEGER or ENUMERATED number */
#define IAAPI_BADINDX     14   /* Bad component index into a structured type */
#define IAAPI_BADDEC      15   /* Bad decoded value, possibly NULL */
#define IAAPI_ENCFAL      16   /* Failure to encode value */
#define IAAPI_NLENC       17   /* Null encoding or length is 0 */
#define IAAPI_DECFAL      18   /* Decoding failed */
#define IAAPI_BADTGINDX   19   /* Bad tag number index into encoded value */
#define IAAPI_BADTYPE     20   /* Incorrect type handle for the function */
#define IAAPI_CPYFAIL     21   /* Copying a decoded value failed */
#define IAAPI_NOTCOMPATIBLE   22 /* Types are not compatible */
#define IAAPI_BADDISPLAYVALUE 23 /* Failure to parse a PDU display value */
#define IAAPI_BADIDENTIFIER   24 /* Bad identifier in a parsing display value */
#define IAAPI_DUPLCOMPVALUE   25 /* Duplicate value for one component in a parsing value*/
#define IAAPI_ENCOPENTYPEORANYFAILED 26 /* Encoding failed for ANY or open type value*/
#define IAAPI_FREETPFAL   27   /* Failure to free decoded value */
#define IAAPI_BADCHOICE   28   /* Invalid value notation of CHOICE type */
#define IAAPI_BADHINT     29   /* Bad HUGE INTEGER value */
#define IAAPI_BADENCOID   30   /* Bad ENCODED OBJECT IDENTIFIER value */
#define IAAPI_BADOBJ      31   /* Object can not be marked */
#define IAAPI_UNKNOWNOBJ  32   /* Invalid object handle */
#define IAAPI_BADBIT      33   /* Bad bit string or hex string */
#define IAAPI_BADBOOLEAN  34   /* Not TRUE or FALSE value */
#define IAAPI_LENTOOLONG  35   /* Length of encoding too long */
#define IAAPI_NOEOC       36   /* EOC not found for indefinite length encoding */
#define IAAPI_BADEOC      37   /* EOC with non-zero second octet */
#define IAAPI_BADHEADER   38   /* Length of tag-length pair exceeds remaining
				* data length */
#define IAAPI_BADSTRUCTVALUE 39/* Value notation of SET or SEQUENCE or SET OF or
				* SEQUENCE OF has no opening or closing brace */
#define IAAPI_BADCSTRINGLIST 40/* Bad CharacterStringList or control char value */
#define IAAPI_NOMANDATORY    41/* Not all values of mandatory components are
				* present in the value notation of SET or
				* SEQUENCE type */
#define IAAPI_ABSENT_IDENTIFIER 42 /* Identifier is missing in value notation
				* of SET or SEQUENCE type */
#define IAAPI_NOTYPEREF	     43/* Missing type reference name in ANY or opentype */
#define IAAPI_BADOBJVALUE    44/* Invalid display value of a marked object */
#define IAAPI_CANT_OPEN_FILE 45/* Input file cannot be opened */
#define IAAPI_ERROR_READING_FROM_FILE 46 /* Error reading from input file */
#define IAAPI_BADOFFSET   47   /* Invalid offset into input file */
#define IAAPI_BADSIZE     48   /* Invalid number of bytes to be read from input
                                * file */
#define IAAPI_NONHEX      49   /* Input text file with encoding contains 
                                * non-hexadecimal characters */
#define IAAPI_INT_TOO_LONG 50  /* Interger value is out of range */
#define IAAPI_BAD_ABSREF 	51  /* Bad absolute reference format */
#define IAAPI_BAD_TYPEREF_NAME	52  /* Bad type reference name */
#define IAAPI_BAD_COMPID	53  /* Bad identifier in SET, SEQUENCE, or CHOICE */
#define IAAPI_BAD_PARENT_TYPE	54  /* Bad type handle of parent type */
#define IAAPI_BAD_COMP_TYPE	55  /* Bad type handle of component */
#define IAAPI_BAD_COMP_VALUE	56  /* Bad component value, possibly NULL */
#define IAAPI_BADENCRELOID	57  /* Bad ENCODED Relative OID value */
#define IAAPI_NODEBUG           58  /* nodebug was specified */
#define IAAPI_BAD_INFO_OBJ_NAME     59  /* invalid input object name */
#define IAAPI_NO_TABLE_CONSTRAINT   60  /* field has not table constraint */
#define IAAPI_INFO_OBJECT_NOT_FOUND 61  /* info object was not found */
#define IAAPI_INFO_OBJSET_NOT_FOUND 62  /* info object set was not found */
#define IAAPI_INFO_OBJSET_NOT_EXTENSIBLE  63 /* info object set is not extensible */
#define IAAPI_BADARG                      64 /* bad argument, possibly a NULL value */
#define IAAPI_INFO_OBJ_NOT_SUPPORTED      65 /* control tables generated by the old
                                              * compiler without support for info
                                              * object classes, sets and objects */
#define IAAPI_CANT_REMOVE_ROOT_INFO_OBJ   66 /* only info objects that appear 
                                              * after extension marker caan be
                                              * removed */
#define IAAPI_CANT_COPY_INFO_OBJSET_TABLE 67 /* cannot create a copy of info 
                                              * object set table */
#define IAAPI_INFO_OBJ_UNIQUE_FIELD_NOT_FOUND 68 /* no UNIQUE field found */
#define IAAPI_INFO_OBJECT_ALREADY_EXISTS      69 /* object already exists */
#define IAAPI_CMPFAIL                         70 /* Comparing values failed */
#define IAAPI_IMPLEMENTATION_LIMIT_EXCEEDED   71 /* internal buffer exhausted */
#define IAAPI_ERROR_WRITING_TO_FILE           72 /* Error writing to output file */
#define IAAPI_BAD_ZERO_TAG                    73 /* "00" tag is detected */
#define IAAPI_CONSTRAINT_VIOLATION            74 /* more precise code from ValueIsValid() */
#define IAAPI_BAD_OID_IRI    75   /* Bad OID-IRI type value */
#define IAAPI_BAD_RELOID_IRI 76   /* Bad RELATIVE-OID-IRI type value */
#define IAAPI_BAD_CHARSTRING 77 /* Missing a quote in a char string values of a nested component.  */

#if defined(_MSC_VER) && (defined(WINCE) || defined(_WIN64))
#pragma pack(push, ossPacking, 8)
#elif defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32))
#pragma pack(push, ossPacking, 4)
#elif defined(_MSC_VER) && (defined(_WINDOWS) || defined(_MSDOS))
#pragma pack(1)
#elif defined(__BORLANDC__) && defined(__MSDOS__)
#pragma option -a1
#elif defined(__BORLANDC__) && defined(__WIN32__)
#pragma option -a4
#elif defined(__IBMC__) && (defined(__WIN32__) || defined(__OS2__))
#pragma pack(4)
#elif defined(__WATCOMC__) && defined(__NT__)
#pragma pack(push, 4)
#elif defined(__WATCOMC__) && (defined(__WINDOWS__) || defined(__DOS__))
#pragma pack(push, 1)
#endif /* _MSC_VER && _WIN32 */

#ifdef macintosh
#pragma options align=mac68k
#endif


/* Structure for holding values of type INTEGER */
typedef struct IntValue {
    enum {signedNumber, unsignedNumber} sign;
    union {
	LONG_LONG       signedInt;
	ULONG_LONG      unsignedInt;
    } value;
} IntValue;


/* Structure for IAAPI initialization values */
typedef struct IAAPI_initializers {
           char         charInitializer;
           short        shortInitializer;
           int          intInitializer;
           long         longInitializer;
           LONG_LONG    llongInitializer;
           void       * pointerInitializer;
           char       * floatInitializer;
           char       * doubleInitializer;
} IAAPI_initializers;

/*
 * Type definition for a value reference structure.
 */
typedef struct ValRef {
   char *name;            /* value reference name */
   void *address;         /* pointer to decoded value */
   unsigned short etype;  /* index into etype array */
} ValRef;

/*
 * Structure used in determining if a type is a PDU or a referenced type.
 */
typedef struct ReferencedType {
    struct ReferencedType *next;
    TypeHndl		  type;
} ReferencedType;

#if defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32) || defined(WINCE) || defined(_WIN64))
#pragma pack(pop, ossPacking)
#elif defined(_MSC_VER) && (defined(_WINDOWS) || defined(_MSDOS))
#pragma pack()
#elif defined(__BORLANDC__) && (defined(__WIN32__) || defined(__MSDOS__))
#pragma option -a.
#elif defined(__IBMC__) && (defined(__WIN32__) || defined(__OS2__))
#pragma pack()
#elif defined(__WATCOMC__) && (defined(__NT__) || defined(__WINDOWS__) || defined(__DOS__))
#pragma pack(pop)
#endif /* _MSC_VER && _WIN32 */

#ifdef macintosh
#pragma options align=reset
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if defined(macintosh) && defined(__CFM68K__)
#pragma import on
#endif


/***************************************************/
/* Functions defined by the Interpretive ASN.1 API */
/***************************************************/

extern int   DLL_ENTRY ossDefaultIAAPI_ERR(OssGlobal *world, int err_code,
					char *parm, long num);
extern int   DLL_ENTRY ossIaapiErrMsgHandle(OssGlobal *world, int err_code,
					    char *parm, long num);
extern void *DLL_ENTRY ossGetIaapiErrorHandlingFunction(OssGlobal *world);
extern void  DLL_ENTRY ossSetIaapiErrorHandlingFunction(OssGlobal *world,
					int (DLL_ENTRY_FPTR *_System func)
					(OssGlobal *, int, char *, long));
extern char *DLL_ENTRY ossGetIaapiErrMsg(OssGlobal *world);
extern char *DLL_ENTRY ossDescribeIaapiReturnCode(OssGlobal *in_world, int in_rc);

extern void  DLL_ENTRY ossSetInitializationValues(OssGlobal *world,
					IAAPI_initializers *initStruct);
extern void  DLL_ENTRY ossTermIAAPI(OssGlobal *world);

extern unsigned short DLL_ENTRY ossCtlTblVersionNumber(OssGlobal *world);
extern ossBoolean  DLL_ENTRY ossCtlTblUsableOnlyByPER(OssGlobal *world);
extern ossBoolean  DLL_ENTRY ossCtlTblUsableOnlyByBER(OssGlobal *world);
extern ossBoolean  DLL_ENTRY ossDebugWasSpecified(OssGlobal *world);
extern ossBoolean  DLL_ENTRY ossConstrainWasSpecified(OssGlobal *world);

extern int         DLL_ENTRY ossNumberOfPDUs(OssGlobal *world);
extern int	   DLL_ENTRY ossNumberOfArtificialPDUs(OssGlobal *world);
extern TypeHndl    DLL_ENTRY ossTypeHandleOfPDU(OssGlobal *world, int pduNum);
extern TypeHndl    DLL_ENTRY ossPduTypeHandleByName(OssGlobal *world, const char *name);
extern int         DLL_ENTRY ossPduNumberByType(OssGlobal *world, TypeHndl type);
extern ossBoolean  DLL_ENTRY ossTypeIsConstrained(OssGlobal *world, TypeHndl type);
extern int         DLL_ENTRY ossAsn1TypeId(OssGlobal *world, TypeHndl type);
extern const char *DLL_ENTRY ossBuiltinTypeName(OssGlobal *world, ASN1Type typeId);
extern const char *DLL_ENTRY ossTypeReferenceName(OssGlobal *world, TypeHndl type);
extern int         DLL_ENTRY ossTypesCompatible(OssGlobal *world,
					TypeHndl type1, TypeHndl type2);

extern int         DLL_ENTRY ossNumberOfNamedItems(OssGlobal *world, TypeHndl type);
extern TypeHndl    DLL_ENTRY ossTypeHandleOfComponent(OssGlobal *world,
					TypeHndl parent, unsigned int ix);
extern TypeHndl    DLL_ENTRY ossDeferTypeHandle(OssGlobal *world, TypeHndl type);
extern ossBoolean  DLL_ENTRY ossTypeIsDeferDecoding(OssGlobal *world,TypeHndl type);
extern ossBoolean  DLL_ENTRY ossComponentIsOptional(OssGlobal *world,
					TypeHndl type, unsigned int ix);
extern ossBoolean  DLL_ENTRY ossComponentHasDefaultValue(OssGlobal *world,
					TypeHndl parentType, unsigned int ix);
extern void       *DLL_ENTRY ossComponentDefaultValue(OssGlobal *world,
					TypeHndl parentType, unsigned int ix);
extern ossBoolean  DLL_ENTRY ossComponentValueIsPresent(OssGlobal *world,
					TypeHndl parentType, unsigned int ix,
					void *parentValue);
extern ossBoolean  DLL_ENTRY ossComponentIsInitializationValue(OssGlobal *world,
					TypeHndl chldType, void *compAddress);
extern ossBoolean  DLL_ENTRY ossComponentWasRemoved(OssGlobal *world,
					TypeHndl type, unsigned int ix);
extern unsigned int DLL_ENTRY ossItemIndexByName(OssGlobal *world,
					TypeHndl type, const char *name);
extern const char *DLL_ENTRY ossAsn1ItemName(OssGlobal *world, TypeHndl type,
						unsigned int ix);
extern long        DLL_ENTRY ossItemIntValue(OssGlobal *world, TypeHndl type,
						unsigned int ix);
extern LONG_LONG   DLL_ENTRY ossItemIntValueLL(OssGlobal *world, TypeHndl type,
						unsigned int ix);

extern ossBoolean  DLL_ENTRY ossExtensionMarkerIsPresent(OssGlobal *world,
						TypeHndl type);
extern int         DLL_ENTRY ossNumberOfRootItems(OssGlobal *world, TypeHndl type);
extern ossBoolean  DLL_ENTRY ossCompAppearsAfterExtensionMarker(OssGlobal *world,
						TypeHndl type, unsigned int ix);
extern int         DLL_ENTRY ossNumberOfTags(OssGlobal *world, TypeHndl type);
extern int         DLL_ENTRY ossAsn1TagNumber(OssGlobal *world, TypeHndl type,
						unsigned int ix);
extern int         DLL_ENTRY ossAsn1TagClass(OssGlobal *world, TypeHndl type,
						unsigned int ix);

extern ossBoolean  DLL_ENTRY ossUpperBoundIsPresent(OssGlobal *world, TypeHndl type);
extern ossBoolean  DLL_ENTRY ossLowerBoundIsPresent(OssGlobal *world, TypeHndl type);
extern unsigned long DLL_ENTRY ossLowerBoundOfSizeConstraint(OssGlobal *world,
							TypeHndl type);
extern unsigned long DLL_ENTRY ossUpperBoundOfSizeConstraint(OssGlobal *world,
							TypeHndl type);

extern ossBoolean DLL_ENTRY ossMinValueOfInteger(OssGlobal *world, TypeHndl type,
							IntValue *val);
extern ossBoolean DLL_ENTRY ossMaxValueOfInteger(OssGlobal *world, TypeHndl type,
							IntValue *val);

extern unsigned long DLL_ENTRY ossPermittedAlphabetLength(OssGlobal *world,
							TypeHndl type);
extern const long   *DLL_ENTRY ossPermittedAlphabetConstraint(OssGlobal *world,
							TypeHndl type);
extern unsigned long *DLL_ENTRY ossWidePermittedAlphabet(OssGlobal *world,
					   TypeHndl type, unsigned long *length);

extern unsigned short DLL_ENTRY ossGetNumberOfValueReferences(OssGlobal *world);
extern const char *DLL_ENTRY ossGetNameOfValueReference(OssGlobal *world,
						unsigned short int compIndex);
extern const void *DLL_ENTRY ossGetDecodedValueOfValueReference(OssGlobal *world,
						unsigned short int compIndex);
extern TypeHndl    DLL_ENTRY ossGetTypeHandleOfValueReference(OssGlobal *world,
						unsigned short int compIndex);

extern IAAPI_ERRTYPE DLL_ENTRY ossDecodeValueNotationOfPDU( OssGlobal  *world,
				int pduNum, OssBuf *asnValue, void **decValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossDecodeValueNotationOfType(OssGlobal *world,
				TypeHndl type, OssBuf *asnValue, void **decValue);

extern char *DLL_ENTRY ossGetValueNotationOfPDU(OssGlobal *world,
				int pduNum, void *decodedValue);
extern char *DLL_ENTRY ossGetValueNotationOfType(OssGlobal *world,
				TypeHndl type, void *decodedValue);

extern IAAPI_ERRTYPE DLL_ENTRY ossPutDecodedValueOfPDU(OssGlobal *world,
				int pduNum, char *remainingBuf, void **pduVal);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutSimpleTypeValue(OssGlobal *world,
				TypeHndl type, char *userTypedvalue,
				void **decodedValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutStructTypeValue(OssGlobal *world,
				TypeHndl parent, void *compValue,
				unsigned int compIndex, void **structToUpdate);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutStructTypeValueByComponentAbsRef(
				OssGlobal *world, TypeHndl outerType,
				void *compValue, char *compAbsref, 
				void **outerStructToUpdate);
extern IAAPI_ERRTYPE DLL_ENTRY ossDeleteComponent(OssGlobal *world,
				TypeHndl parentType, unsigned int compIndex,
				void **parentValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutOpenTypeDecodedValue(OssGlobal *world,
				TypeHndl type, int pduNum, void *decodedValue,
				void **openValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutEncodedValue(OssGlobal *world,
				TypeHndl type, OssBuf encodedValue,
				void **decodedValue);

extern char *DLL_ENTRY ossGetValueOfSimpleType(OssGlobal *world, TypeHndl type,
				void *decodedValue);
extern void *DLL_ENTRY ossUpdateValueOfSimpleType(OssGlobal *world,TypeHndl type,
				char *userTypedValue, void *oldValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetDecodedValueOfComponent(OssGlobal *world,
				TypeHndl parentType, void *parentDecodedValue,
				unsigned int compIndex, void **componentValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetComponentByAbsRef(OssGlobal *world, 
				char *compAbsref, void *parentValue,
				TypeHndl *compType, void **compValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutComponentByAbsRef(OssGlobal *world, 
				char *compAbsref, void *parentValue,
				void *compValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetOpenTypeValue(OssGlobal *world,
				TypeHndl type, void *openValue, int *pduNum,
				void **decodedValue, OssBuf *encodedValue);

extern IAAPI_ERRTYPE DLL_ENTRY ossIaapiMarkObject(OssGlobal *world, TypeHndl type,
				OssObjType objectType, void *object);
extern OssObjType    DLL_ENTRY ossGetObjectType(OssGlobal *world,
				TypeHndl type, void *object);
extern ossBoolean    DLL_ENTRY ossTypeIsExternalObject(OssGlobal *world,
				TypeHndl type);
extern IAAPI_ERRTYPE DLL_ENTRY ossSetTypeAsExternalObject(OssGlobal *world,
				TypeHndl type, ossBoolean marked);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutObjectValue(OssGlobal *world, TypeHndl type,
				OssBufExtended *objectValue, 
				OssObjType objectType, void **decodedValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetObjectValue(OssGlobal *world, TypeHndl type,
				void *decodedValue, OssBufExtended *objValue);

extern ossBoolean    DLL_ENTRY ossValueIsValid(OssGlobal *world,
					TypeHndl type, void *value);
extern unsigned long DLL_ENTRY ossGetValueLength(OssGlobal *world,
					TypeHndl type, void *value);
extern IAAPI_ERRTYPE DLL_ENTRY ossCopyTypeValue(OssGlobal *world, TypeHndl type,
					void *valueIn, void **valueOut);
extern IAAPI_ERRTYPE DLL_ENTRY ossCmpTypeValue(OssGlobal *world, TypeHndl type,
					void *value1, void *value2);

extern IAAPI_ERRTYPE DLL_ENTRY ossValueEncode(OssGlobal *world, TypeHndl type,
					void *value, OssBuf *encodedValue);

extern IAAPI_ERRTYPE DLL_ENTRY ossFreeDecodedValue(OssGlobal *world,
					TypeHndl type, void *valPtr);
extern void DLL_ENTRY ossFreeDisplayString(OssGlobal *world, char *dsplString);

extern ossBoolean     DLL_ENTRY ossEncodingIsConstructed(OssGlobal *world,
				unsigned char *curEnc, long bufLength);
extern unsigned char *DLL_ENTRY ossGetNextBEREncoding(OssGlobal *world,
				unsigned char *curEnc, long *remBufLen);
extern unsigned char *DLL_ENTRY ossGetNestedBEREncoding(OssGlobal *world,
				unsigned char *curEnc, long *remBufLen);
extern long           DLL_ENTRY ossNumberOfEncodingTags(OssGlobal *world,
				unsigned char *curEnc, long bufLength);
extern ASN1TagClass   DLL_ENTRY ossEncodingASN1Class(OssGlobal *world, 
				unsigned char *curEnc, long bufLength, int ix);
extern long           DLL_ENTRY ossEncodingASN1Tag(OssGlobal *world,
				unsigned char *curEnc, long bufLength, int ix);
extern char          *DLL_ENTRY ossEncodingASN1Type(OssGlobal *world,
				unsigned char *curEnc, long bufLength);
extern int	      DLL_ENTRY ossEncodingIdentifierLength(OssGlobal *world,
                                unsigned char *curEnc, long bufLength);
extern int	      DLL_ENTRY ossEncodingHeaderLength(OssGlobal *world, 
				unsigned char *curEnc, long remBufLength);
extern long           DLL_ENTRY ossEncodingLength(OssGlobal *world,
				unsigned char *curEnc, long bufLength);
extern char          *DLL_ENTRY ossEncodingContents(OssGlobal *world,
				unsigned char *curEnc, long bufLength);

extern char  *DLL_ENTRY ossConvertEncodingIntoDisplayHexFmt(OssGlobal *world,
				unsigned char *encodedBufin, long bufLength);
extern char  *DLL_ENTRY ossConvertEncodingIntoDisplayBinFmt(OssGlobal *world,
				unsigned char *encodedBufin, long bufLength);
extern IAAPI_ERRTYPE DLL_ENTRY ossConvertHexFmtToEncoding(OssGlobal *world,
				char *hexBufin, long bufLength, OssBuf*encVal);
extern IAAPI_ERRTYPE DLL_ENTRY ossConvertBinFmtToEncoding(OssGlobal *world,
				char *binBufin, long bufLength, OssBuf *encVal);

/* 
 * Functions for BIT STRING, OCTET STRING types with ContentsConstraint
 */
extern ossBoolean    DLL_ENTRY ossTypeHasContentsConstraint(OssGlobal *world,
				TypeHndl type);
extern int           DLL_ENTRY ossContainedTypeEncodingRule(OssGlobal *world,
				TypeHndl type);
extern int           DLL_ENTRY ossContainedTypePduNumber(OssGlobal *world,
				TypeHndl type);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetContainedTypeValue(OssGlobal *world,
				TypeHndl type, void *containingValue,
				void **decodedValue, OssBuf *encodedValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutContainedTypeDecodedValue(OssGlobal *world,
				TypeHndl type, void *decodedValue,
				void **containingValue);
extern const char *DLL_ENTRY   ossEncodingRuleObjid(OssGlobal *world, int ruleId);


/******************************************************************/
/* New functions defined by the Interpretive ASN.1 API used to get*/
/* information about component relation constraints, to work with */
/* information classes, object sets and objects			  */
/*****************************************************************/

/*
 * Enumeration identifies a type of the field in an information object class.
 */
typedef enum IAAPI_ClassFieldType {
    ia_ordinaryField,
    ia_typeField,
    ia_variableTypeValueField,
    ia_fixedTypeValueSetField,
    ia_variableTypeValueSetField,
    ia_objectField,
    ia_objectSetField
} IAAPI_ClassFieldType;


extern int         DLL_ENTRY ossNumberOfInfoObjClasses(OssGlobal *world);
extern TypeHndl    DLL_ENTRY ossInfoObjClassTypeHandleByIndex(OssGlobal *world,
				 			unsigned int ix);
extern TypeHndl    DLL_ENTRY ossInfoObjClassTypeHandleByName(OssGlobal *world,
							const char *name);
extern ossBoolean  DLL_ENTRY ossInfoObjClassFieldIsUnique(OssGlobal *world,
							FieldHndl field);
extern int         DLL_ENTRY ossInfoObjClassFieldId(OssGlobal *world,
							FieldHndl field);
extern FieldHndl   DLL_ENTRY ossTypeFieldHandleRelativeToVariableTypeField(OssGlobal *world,
							FieldHndl field);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetTypeHandleCarriedByClassFieldValue(OssGlobal *world,
				FieldHndl field, TypeHndl *type, void *fieldValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutTypeHandleCarriedByClassFieldValue(OssGlobal *world,
				FieldHndl field, TypeHndl type, void **fieldValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetInfoObjSetCarriedByClassFieldValue(OssGlobal *world,
				FieldHndl field, void **oset, void *fieldValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossPutInfoObjSetCarriedByClassFieldValue(OssGlobal *world,
				FieldHndl field, void *oset, void **fieldValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetValueFromValueSet(OssGlobal *world,
				TypeHndl type, unsigned int ix, void **value);
extern ossBoolean  DLL_ENTRY ossValuesFromValueSetNeedPointer(OssGlobal *world,
				TypeHndl type);
extern int         DLL_ENTRY ossNumberOfValuesInValueSet(OssGlobal *world,
							TypeHndl type);
extern int         DLL_ENTRY ossNumberOfRootValuesInValueSet(OssGlobal *world,
							TypeHndl type);

extern int         DLL_ENTRY ossNumberOfInfoObjSets(OssGlobal *world);
/* The OSS API function ossGetInfoObjectSet() may be used to extract the
 * information object set, identified by its index in the list of all 
 * information object sets. */
extern TypeHndl     DLL_ENTRY ossInfoObjSetTypeHandle(OssGlobal *world,
							unsigned int ix);
extern void        *DLL_ENTRY ossInfoObjSetHandle(OssGlobal *world,
							unsigned int ix);
extern unsigned int DLL_ENTRY ossInfoObjSetIndexByName(OssGlobal *world, 
							const char *name);
extern unsigned int DLL_ENTRY ossInfoObjSetIndex(OssGlobal *world, void *oset);
extern ossBoolean   DLL_ENTRY ossInfoObjSetIsExtensible(OssGlobal *world,
							unsigned int ix);
extern const char * DLL_ENTRY ossInfoObjSetName(OssGlobal *world, 
							unsigned int ix);

extern int          DLL_ENTRY ossNumberOfInfoObjects(OssGlobal *world,
							unsigned int oset_ix);
extern int          DLL_ENTRY ossNumberOfRootInfoObjects(OssGlobal *world,
							unsigned int oset_ix);
extern const char * DLL_ENTRY ossInfoObjectName(OssGlobal *world, 
				unsigned int oset_ix, unsigned int obj_ix);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetInfoObjectByName(OssGlobal *world, 
				char *osetName, const char *objName,
				void **object);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetInfoObjectByIndex(OssGlobal *world,
				unsigned int oset_ix, unsigned int obj_ix,
				void **object);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetNextInfoObject(OssGlobal *world, 
						void *oset, void **object);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetNextInfoObjectAndName(OssGlobal *world, 
				void *oset_addr, void **object, const char **name);

extern FieldHndl    DLL_ENTRY ossComponentFieldHandle(OssGlobal *world, 
				TypeHndl type, unsigned int ix);
extern unsigned int DLL_ENTRY ossComponentIndexByFieldHandle(OssGlobal *world,
							FieldHndl field);
extern TypeHndl     DLL_ENTRY ossComponentParentTypeHandle(OssGlobal *world, 
							FieldHndl field);
extern const char  *DLL_ENTRY ossFieldNameByFieldHandle(OssGlobal *world,
							FieldHndl field);
extern TypeHndl     DLL_ENTRY ossTypeHandleByFieldHandle(OssGlobal *world,
							FieldHndl field);
extern unsigned int DLL_ENTRY ossComponentInfoObjSetIndex(OssGlobal *world,
							FieldHndl field);
extern TypeHndl     DLL_ENTRY ossComponentInfoObjClassTypeHandle(OssGlobal *world,
							FieldHndl fieldHndl);
extern FieldHndl    DLL_ENTRY ossComponentInfoObjClassFieldHandle(OssGlobal *world,
							FieldHndl field);
extern unsigned int DLL_ENTRY ossConstrainingInfoObjSetIndex(OssGlobal *world,
							TypeHndl type);
extern TypeHndl     DLL_ENTRY ossInfoObjClassTypeHandleOfObjClassFieldType(OssGlobal *world,
							TypeHndl type);
extern FieldHndl    DLL_ENTRY ossInfoObjClassFieldHandleOfObjClassFieldType(OssGlobal *world,
							TypeHndl type);

extern ossBoolean   DLL_ENTRY ossHasComponentRelationConstraint(OssGlobal *world, 
				TypeHndl type, unsigned int ix);
extern ossBoolean   DLL_ENTRY ossHasTableConstraint(OssGlobal  *world,
				TypeHndl type, unsigned int ix);
extern ossBoolean   DLL_ENTRY ossReferencedInComponentRelationConstraint(OssGlobal *world,
				TypeHndl type, unsigned int ix);
extern int          DLL_ENTRY ossNumberOfReferencedComponents(OssGlobal *world, 
							FieldHndl field);
extern int          DLL_ENTRY ossNumberOfReferencedComponentsByTypeHandle(OssGlobal *world, 
							TypeHndl type);
extern int          DLL_ENTRY ossNumberOfReferencingComponents(OssGlobal *world, 
							FieldHndl field);
extern FieldHndl    DLL_ENTRY ossReferencedComponentFieldHandle(OssGlobal *world, 
				FieldHndl field, unsigned int ix);
extern FieldHndl    DLL_ENTRY ossReferencingComponentFieldHandle(OssGlobal *world, 
				FieldHndl fieldHndl, unsigned int ix);
extern ossBoolean   DLL_ENTRY ossReferencedComponentIsInner(OssGlobal *world, 
				FieldHndl field, unsigned int ix);
extern FieldHndl    DLL_ENTRY ossReferencedComponentFieldHandleByTypeHandle(OssGlobal *world, 
				TypeHndl type, unsigned int ref_ix);
extern ossBoolean   DLL_ENTRY ossReferencedComponentByTypeHandleIsInner(OssGlobal *world, 
				TypeHndl type, unsigned int ref_ix);
extern char	   *DLL_ENTRY ossObjectClassFieldTypeNotationOfConstrainedType(OssGlobal *world,
							       TypeHndl type);

extern IAAPI_ERRTYPE DLL_ENTRY ossGetInfoObjectByFieldValue(OssGlobal *world,
				FieldHndl field, void *fieldVal, void **prevObj);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetInfoObjectByFieldValueAndTypeHandle(OssGlobal *world,
				TypeHndl fld_type, void *fld_value, void **prev_obj);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetTypeHandleOfActualTypeCarriedByOpenType(OssGlobal *world, 
				FieldHndl constr_field, FieldHndl ref_field,
				void *ref_field_value, TypeHndl *actual_type);
extern IAAPI_ERRTYPE DLL_ENTRY ossGetTypeHandleOfActualTypeCarriedByOpenTypeHandle(OssGlobal *world, 
				TypeHndl open_type, FieldHndl ref_field,
				void *ref_field_value, TypeHndl *actual_type);
extern IAAPI_ERRTYPE DLL_ENTRY ossRemoveInfoObjectByName(OssGlobal *world, 
				const char *oset_name, const char *obj_name);
extern IAAPI_ERRTYPE DLL_ENTRY ossRemoveInfoObjectByIndex(OssGlobal *world, 
				unsigned int oset_ix, unsigned int obj_ix);
extern IAAPI_ERRTYPE DLL_ENTRY ossAddInfoObjectByName(OssGlobal *world,
				const char *oset_name, const char *obj_name);
extern IAAPI_ERRTYPE DLL_ENTRY ossAddInfoObjectByIndex(OssGlobal *world, unsigned int from_oset_ix,
				unsigned int to_oset_ix, unsigned int obj_ix);
extern int           DLL_ENTRY ossReferencedComponentScope(OssGlobal *world,
				FieldHndl field, unsigned int ix);	
extern int           DLL_ENTRY ossReferencedComponentScopeByTypeHandle(OssGlobal *world,
				TypeHndl type, unsigned int ix);

/***************************************************************************
 * Functions for ISO 8601 time types                                       *
 ***************************************************************************/
#define IAAPI_CENTURY		0x01
#define IAAPI_YEAR		0x02
#define IAAPI_MONTH		0x04
#define IAAPI_WEEK		0x08
#define IAAPI_DAY		0x10
#define IAAPI_YEAR_BASIC	0x20	/* may be set along with IAAPI_YEAR_PROLEPTIC */
#define IAAPI_YEAR_PROLEPTIC	0x40	/* may be set along with IAAPI_YEAR_BASIC */
#define IAAPI_YEAR_NEGATIVE	0x80	/* may be set along with IAAPI_YEAR_LARGE */
#define IAAPI_YEAR_LARGE	0x100	/* may be set along with IAAPI_YEAR_NEGATIVE */
#define IAAPI_TIME_FRACTION	0x200	/* Time=HF*, HMF*, HMSF* */
#define IAAPI_HOURS		0x400
#define IAAPI_MINUTES		0x800
#define IAAPI_SECONDS		0x1000
#define IAAPI_TIME_LOCAL	0x2000	/* Local-or-UTC=L */
#define IAAPI_TIME_UTC		0x4000	/* Local-or-UTC=Z */
#define IAAPI_TIME_DIFF		0x8000	/* Local-or-UTC=LD */
#define IAAPI_DURATION		0x10000 
#define IAAPI_START_POINT	0x20000
#define IAAPI_END_POINT		0x40000
#define IAAPI_REC_INTERVAL	0x80000
#define IAAPI_REC_UNLIMITED	0x100000	/* Recurrence=Unlimited */

extern ossBoolean   DLL_ENTRY ossTimeHasNonMixedPEREncoding(OssGlobal *world,
				TypeHndl type);
extern unsigned int DLL_ENTRY ossIntervalPropertySettingsForPER(OssGlobal *world,
				TypeHndl type, unsigned int *min_rec_digits);
extern unsigned int DLL_ENTRY ossDatePropertySettingsForPER(OssGlobal *world,
				TypeHndl type, unsigned int *min_year_digits);
extern unsigned int DLL_ENTRY ossTimeOfDayPropertySettingsForPER(OssGlobal *world,
				TypeHndl type, unsigned int *fraction_digits);


extern ossBoolean DLL_ENTRY    ossCheck8601Time(OssGlobal *world, TypeHndl type,
				char *tvalue, int *err_pos);

extern IAAPI_ERRTYPE DLL_ENTRY ossCreateUnencodedValueOfPDU(OssGlobal *world,
				int pduNum, void **pduValue);
extern IAAPI_ERRTYPE DLL_ENTRY ossCreateUnencodedValueOfType(OssGlobal *world,
				TypeHndl type, void **value);

/****************************************************/
/* Functions for syntaxes with EXTENDED XER support */
/****************************************************/
extern unsigned int DLL_ENTRY	ossNumberOfNamespaces(OssGlobal *world);
extern char	   *DLL_ENTRY	ossNamespaceURI(OssGlobal *world, unsigned int ix);

/***************************************************************************
 * Functions to support user-allocated memory and to disable calls to      *
 * signal(), setjmp(), longjmp() and constraint checking in the IAAPI      *
 * functions.                                                              *
 ***************************************************************************/
extern IAAPI_ERRTYPE DLL_ENTRY	ossPutStructTypeUserValue(OssGlobal *world,
				TypeHndl parentType, void *userValue,
				unsigned int compIndex, void **structToUpdate);
extern IAAPI_ERRTYPE DLL_ENTRY	ossUpdateStructTypeUserValue(OssGlobal *world,
				TypeHndl parentType, void *userValue,
				unsigned int compIndex, void **structToUpdate);
extern IAAPI_ERRTYPE DLL_ENTRY	ossFreeNonUserDecodedValue(OssGlobal *world,
					TypeHndl type, void *valPtr);
extern void DLL_ENTRY		ossRemoveUserValue(OssGlobal *world, void *valPtr);
extern void DLL_ENTRY		ossRemoveUserValues(OssGlobal *world);
extern unsigned long DLL_ENTRY	ossGetIAAPIFlags(OssGlobal *world);
extern int DLL_ENTRY		ossSetIAAPIFlags(OssGlobal *world, 
				unsigned long flags);

/* Enumeration identifies internal C representations of ASN.1 types.
 * Note that enumerators  should be in sync with etype kinds. */
typedef enum iaapiCtype {
   ia_int         = 0,
   ia_pad_bit     = 1,
   ia_big_pad_bit = 2,
   ia_unbnd_bit   = 3,
   ia_vary_bit    = 4,
   ia_null        = 5,
   ia_enum        = 6,
   ia_real        = 7,
   ia_bool        = 8,
   ia_any         = 10,
   ia_set         = 11,
   ia_seq         = 12,
   ia_choice      = 13,
   ia_setof       = 16,
   ia_seqof       = 19,
   ia_unbnd_octet = 20,
   ia_vary_octet  = 21,
   ia_pad_char    = 22,
   ia_vary_char   = 23,
   ia_nlltrm_char = 24,
   ia_unbnd_char  = 25,
   ia_array_objid = 26,
   ia_unbnd_objid = 28,
   ia_utc_time    = 29,
   ia_gen_time    = 30,
   ia_opentype    = 51, 
   ia_2byte_char  = 53,
   ia_4byte_char  = 54,
   ia_uint        = 55,
   ia_uenum       = 58,
   ia_char_real   = 59,
   ia_mixed_real  = 60,
   ia_huge_int    = 62,
   ia_encoded_objid    = 63,
   ia_encoded_reloid   = 74,
   ia_nlltrm_date_time = 78,
   ia_unknown_ctype    = 84
} iaapiCtype;

extern int DLL_ENTRY        ossCtypeId(OssGlobal *world, TypeHndl type);
extern ossBoolean DLL_ENTRY ossTypeHasPointerDirective(OssGlobal *world,
							TypeHndl type);
extern unsigned short DLL_ENTRY ossCtypeLengthSize(OssGlobal *world,
							TypeHndl type);


/***************************************************************************
 * Functions for printing ASN.1 PDUs, referenced types and ASN.1 values    *
 ***************************************************************************/
extern void DLL_ENTRY ossPrintPDUs(OssGlobal *world);
extern void DLL_ENTRY ossPrintRemainingReferencedTypes(OssGlobal *world);
extern void DLL_ENTRY ossPrintASN1DescriptionOfPDU(OssGlobal *world,
					int pduNum, ossBoolean refTypes);
extern void DLL_ENTRY ossPrintASN1DescriptionOfType(OssGlobal *world,
				TypeHndl type, ossBoolean refTypes);
extern void DLL_ENTRY ossPrintDecodedValuesOfPDUs(OssGlobal *world);
extern void DLL_ENTRY ossPrintDecodedValueOfPDU(OssGlobal *world, int pduNum,
				 void *decodedValue);
extern void DLL_ENTRY ossPrintDecodedValueOfPDUByName(OssGlobal *world,
				TypeHndl type, char *name, void *decodedValue);
extern void DLL_ENTRY ossPrintDecodedValueOfType(OssGlobal *world,
				TypeHndl type, void *decodedValue);

/***************************************************************************
 * Functions for printing ASN.1 info object classes, sets and objects      *
 ***************************************************************************/
extern void DLL_ENTRY ossPrintInfoObjClasses(OssGlobal *world);
extern void DLL_ENTRY ossPrintASN1DescriptionOfCLASS(OssGlobal *world,
					unsigned int class_ix, ossBoolean refTypes);
extern void DLL_ENTRY ossPrintInfoObjectSets(OssGlobal *world);
extern void DLL_ENTRY ossPrintASN1DescriptionOfInfoObjSet(OssGlobal *world,
					unsigned int oset_ix);
extern void DLL_ENTRY ossPrintInfoObjects(OssGlobal *world);
extern void DLL_ENTRY ossPrintASN1DescriptionOfInfoObject(OssGlobal *world,
					unsigned int oset_ix, unsigned int obj_ix);
extern void DLL_ENTRY ossPrintInfoObjSet(OssGlobal *world, TypeHndl classType,
					void *objSet, int indentLvl);
extern void DLL_ENTRY ossPrintInfoObject(OssGlobal *world, TypeHndl classType,
					void *object, int indentLvl);
extern void DLL_ENTRY ossPrintValueSet(OssGlobal *world, TypeHndl type,
					int indentLvl);
extern void DLL_ENTRY ossGetTypeLists(OssGlobal *world, 
					ReferencedType ***pList, 
					ReferencedType ***rList, int add);

/* IAAPI flags used to control printing in different formats in the function
 * ossPrintEncodingInTLV() */
#define TLV_DECOMPOSED     0x01
#define TLV_SYNTAX         0x02
#define TLV_TEXT           0x04
#define TLV_NOSHORT        0x08
#define TLV_NOADDITION     0x10
#define TLV_NOTITLES       0x20


/* IAAPI flags to control signal, setjmp, longjmp, IAAPI constraint checking
 * handling. */
#define IAAPI_NOSIGNAL     0x2000
#define IAAPI_NOSETJMP     0x4000
#define IAAPI_NOCONSTRAIN  0x8000
#define IAAPI_PRINT_REAL_VALUES_USING_BRACE_NOTATION 0x10000
#define IAAPI_DONT_PRINT_REFERENCED_TYPES 0x20000

/* IAAPI flags used by ossCreateUnencodedValuePDU/Type() to control unencoded 
 * values initialization. The IAAPI_NOCONSTRAIN flag can be used to suppress
 * using constraints applied to types during values inititialization. */
#define IAAPI_INIT_OPTIONALS   0x40000
#define IAAPI_NODEFAULT_VALUES 0x80000
#define IAAPI_NONAMED_ITEMS    0x100000


/* Flag used to handle non-IAAPI values with NOCOPY. */
#define IAAPI_NON_IAAPI_VALUE_WITH_NOCOPY 0x4000000
/* Flag instructs the IAAPI error handling functions, that is used to obtain
 * an error message as a string, to print the same string also with ossPrint()
 * function to either stdout or trace file. */
#define IAAPI_PRINT_ERRMSG                0x8000000
#define IAAPI_IGNORE_COMPLEX_CONSTRAINTS  0x10000000
/*#define UNUSED 0x20000000 */



extern void DLL_ENTRY ossPrintEncodingInTLV(OssGlobal *world,
				unsigned long flags, OssBufExtended *inbuf);
extern void DLL_ENTRY ossPrintEncodingInDecomposedTLV(OssGlobal *world,
				OssBuf *encValue);
extern void DLL_ENTRY ossPrintEncodingInSyntaxTLV(OssGlobal *world, OssBuf *encValue);
extern void DLL_ENTRY ossPrintEncodingInHexTLV(OssGlobal *world, OssBuf *encValue);

#define ossPrintBEREncoding      ossPrintEncodingInDecomposedTLV
#define ossPrintBEREncodingInTLV ossPrintEncodingInSyntaxTLV



#ifdef __cplusplus
}
#endif /* __cplusplus */

#if defined(macintosh) && defined(__CFM68K__)
#pragma import reset
#endif


#endif /* #ifndef OSSIAAPI_H */
