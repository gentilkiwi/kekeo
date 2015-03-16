/*****************************************************************************/
/* Copyright (C) 2014 OSS Nokalva, Inc.  All rights reserved.                */ 
/*****************************************************************************/
/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.                    */
/* AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.             */
/* THIS FILE MAY NOT BE DISTRIBUTED.                                         */
/* THIS COPYRIGHT STATEMENT MAY NOT BE REMOVED.                              */
/*****************************************************************************/
/* FILE: @(#)osstype.hh	17.19  14/07/29                                      */
/*****************************************************************************/

/*****************************************************************************/
/* NOTE: this header file does not contain public definitions. It is used by */
/* generated control tables and code files only. Applications using OSS      */
/* tools should not include this file, neither users should be concerned     */
/* with its content.                                                         */
/*****************************************************************************/

#ifndef OSSTYPE_H
#define OSSTYPE_H

#include "ossasn1.h"
#include <stdarg.h>

/*****************************************************************************/
/*  NON-PUBLIC section: include all sections if none of them is explicitly   */
/*  specified                                                                */
/*****************************************************************************/

#ifdef _OSS_CODE_FILE
#if !defined(OSS_TOED_BER) && !defined(OSS_TOED_PER)\
	&& !defined(OSS_TOED_XER) && !defined(OSS_TOED_EXER)\
	&& !defined(OSS_TOED_OER)
#define OSS_TOED_BER
#define OSS_TOED_PER
#define OSS_TOED_XER
#define OSS_TOED_EXER
#define OSS_TOED_OER
#endif /* !OSS_TOED_BER && !OSS_TOED_PER && !OSS_TOED_XER && !OSS_TOED_EXER && !OSS_TOED_OER */
#else /* _OSS_CODE_FILE */
#if !defined(OSS_SOED_BER) && !defined(OSS_SOED_PER)\
	&& !defined(OSS_SOED_XER) && !defined(OSS_SOED_EXER)\
	&& !defined(OSS_SOED_OER)
#define OSS_SOED_BER
#define OSS_SOED_PER
#define OSS_SOED_XER
#define OSS_SOED_EXER
#define OSS_SOED_OER
#endif /* !OSS_SOED_BER && !OSS_SOED_PER && !OSS_SOED_XER && !OSS_SOED_EXER && !OSS_SOED_OER */
#endif /* _OSS_CODE_FILE */

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
#elif defined(__BORLANDC__) && defined(__WIN32__)
#pragma option -a4
#elif defined(__IBMC__) && defined(__WIN32__)
#pragma pack(4)
#elif defined(__WATCOMC__) && defined(__NT__)
#pragma pack(push, 4)
#endif /* _MSC_VER && (WINCE || _WIN64) */

#if defined(macintosh) && defined(__CFM68K__)
#pragma import on
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/*  General section                                                          */
/*****************************************************************************/

typedef struct {
  struct ObjectSetEntry *oset;
  struct ObjectSetEntry *xoset;
  unsigned char *        flags;
  unsigned int           count;
} XOSetInfoEntry;

#if defined(_OSS_CODE_FILE)
typedef struct ossDebugData {
    unsigned long flags;
    char *bufpos;
    long buflen;
    int  (DLL_ENTRY_FPTR *_System oss_print_pdu_ptr)(struct ossGlobal *,
					    int, void *);
    void (DLL_ENTRY_FPTR *_System oss_print_hex_ptr)(struct ossGlobal *,
					    char *, long);
    void (DLL_ENTRY_FPTR *_System oss_print_xml_ptr)(struct ossGlobal *,
					    char *, long, ossBoolean);
} ossDebugData;
#endif /* _OSS_CODE_FILE ... */

/* ossSetPresetDecFlags() flags */
#define UPDATE_INPUT_ADDRESS 0x1 /* Decoder updates the address and the length
				  * of input buffer on return */
#define USE_ETYPE_INDICES    0x2 /* All PDU numbers are treated by the runtime
				  * as etype indices */
#define USE_CPP_OPENTYPES    0x4 /* Decoder generates OpenTypeCPP instead of
				  * OpenType and OpenTypeExtendedCPP instead of
				  * OpenTypeExtended */




#ifdef _OSS_CODE_FILE
/* Error Handling */

/* The index to the error messages.  NOTE:  The enumerated constants here
   must match those in coderror.h. */

enum _err_index {
/*
 * FILE: @(#)coderror.h	17.4  13/11/07
 */
_no_msg,_small_buffer,_type_not_impl,_pdu_range,_bad_argument,
_runtime_version_mismatch,_out_stor,_bad_choice,_bad_der_time,
_stor_error,_int_too_long,_uint_too_long,_bit_str_comp,
_access_serialization,_constrainedBy,_singleValue_integer,
_singleValue_uinteger,_singleValue_real,_singleValue_decreal,
_singleValue_string,_singleValue_constraint,_singleValue_void,
_valueRange_integer,_valueRange_uinteger,_valueRange_real,
_valueRange_decreal,_durationComponentRange_string,
_sizeConstraint_length,_sizeConstraint_number,_oPA_constraint,
_absence_constraint,_presence_constraint,_openType_error,
_openType_user_field_error,_tableConstraint,_componentRelation,
_not_enumerated,_null_tbl,_null_fcn,_corrupted_tbl,_neg_uinteger,
_typeConstraint,_bit_str_too_long,_pdu_range_recursive,
_enc_oid_too_long,_more_input,_zero_bytes_requested,
_size_too_big,_out_of_memory,_invalid_object,
_memmgr_undefined_err,_bad_encrules_err,_toed_rules_not_impl_err,
_unlinked_encrules_err,_table_mismatch,_type_not_supported,
_real_dll_failed,_indef_length_not_supported,_cstrain_dll_failed,
_cmp_dll_failed,_cmp_code_not_linked,_real_code_not_linked,
_tracing_code_not_linked,_oid_dll_failed,
_type_not_supported_der_toed,_toed_rules_not_supp_err,
_load_library_failed,_unload_library_failed,_mandatory_field,
_input_file_open,_bad_objid,_bad_pointer,_bad_time,
_time_bad_month,_time_bad_day,_time_bad_hour,_time_bad_minute,
_time_bad_second,_time_bad_millisec,_too_long,_toom_field,
_zero_length_ANY,_zero_length_OpenType,_inval_dec_real,
_inval_mixed_real,_per_mandatory_field_in_group,
_ber_mandatory_field_in_group,_UTF8_bad_conversion,
_AUTOMATIC_ENCDEC_is_not_specified,_pduNum_is_not_initialized,
_length_is_not_initialized,_tag_long_nec,_tag_too_long,
_exp_long_nec,_exp_too_long,_int_long_nec,_subid_long_nec,
_subid_too_long,_length_too_long,_size_too_long,_non_std_eoc,
_unknown_size,_inconsis_len,_tag_mismatch,_pdu_mismatch,
_extra_bits,_inval_enc,_no_dec_dig,_no_exp_dig,_inval_nr1,
_inval_nr2,_inval_nr3,_real_long_zero,_undef_enc,_null_in_nlltrm,
_unknown_field,_field_repeat,_field_omit,_expec_eoc,
_indef_len_prim,_expec_constr_fnd_prim,_expec_prim_fnd_constr,
_unknown_pdu_type,_enc_too_long,_cannot_happen,_neg_not_allowed,
_expect_tag,_more_value,_real_too_large,_too_many_subids,
_too_many_optional_fields,_too_many_ext_additions,
_too_many_optional_in_group,_extension_encode_error,
_indef_length_der,_bad_UTF8_char,_ber_field_removed,
_per_field_removed,_unexpected_end_of_pdu,_input_file_eof,
_not_multiple_charwidth,_objid_is_constructed,_small_stack,
_stack_sharing,_printper_dll_failed,_constraint_violated,
_small_tmp_buffer,_bad_tmp_buf_free,_int_len_too_long,
_uint_len_too_long,_pattern_constraint_string,
_pattern_constraint,_pattern_constraint_not_linked,
_nocopy_fragmented,_xml_start_tag_expected,
_xml_start_or_empty_tag_expected,_xml_invalid_start_tag,
_xml_zero_pdu,_xml_tags_mismatch,_xml_end_tag_expected,
_xml_item_mismatch,_xml_invalid_bool,_xml_unknown_field,
_xml_not_named_value,_xml_space_expected,_xml_no_debug_info,
_xml_exp_name,_xml_bad_tag,_xml_inv_name,_xml_long_name,
_xml_inv_comment,_xml_inv_ch_seq,_xml_unexp_comment,
_xml_cxer_restriction,_xml_inv_cstr_char,_xml_invalid_element,
_xml_empty_tag_expected,_xml_invalid_tag,_xml_inv_form,
_xml_exp_eq,_bad_objid_node,_constructed_nesting_limit_exceeded,
_seq_set_nesting_limit_exceeded,_api_dll_failed,
_no_valueset_cnst_support,_segment_length_is_not_0_modulo_8,
_xml_bad_char_ref,_xml_big_char_ref,_xml_entity_not_found,
_xml_bad_entity_ref,_xml_undef_prefix,_xml_bad_cdata,
_xml_cdata_exp,_xml_ill_char,_xml_too_deeply,_xml_unsupp_entity,
_xml_small_buffer,_xml_ill_entity,_xml_ill_formed_entity,
_xml_ill_start,_xml_ill_dtd,_xml_duplicate_dtd,
_xml_ill_notation_def,_xml_ill_char_in_name,
_xml_utf8_not_started,_xml_utf8_unfinished,_xml_no_local_part,
_xml_no_prefix,_xml_colon_in_local_part,_xml_duplicate_ns,
_xml_duplicate_default_ns,_xml_tag_expected,_xml_named_value,
_xml_name_forbidden,_xml_boolean_value,_xml_attr_repeated,
_xml_sign_plus_forbidden,_xml_neg_zero,
_xml_leading_zeros_forbidden,_xml_ws_found,
_xml_too_many_named_values,_xml_bad_base64,_xml_end_expected,
_xml_time_length,_xml_bad_bool,_xml_unknown_attribute,
_xml_uri_invalid,_xml_uri_wrong,_xml_prefix_wrong,
_xml_uname_wrong,_xml_embed_size,_xml_embed_size_sax,
_xml_alt_name,_xml_empty_enc,_xml_empty_list_enc,_xml_list_ws,
_xml_wrong_order,_xml_order_size,_xml_empty_real_modified,
_xml_exp_decimal,_xml_neg_zero_decimal,_xml_inf_nan_decimal,
_xml_txt_real_forbidden,_xml_leading_zeros_exponent,
_xml_dubl_val,_xml_anyattr_wrong,_xml_name_expected,
_xml_collapse_ws,_xml_inv_char,_xml_nil_forbidden,
_xml_unknown_type_attr,_xml_xml_ns,_compress_init,
_compress_error,_xml_anyel_wrong,_invalid_fragmentation,
_user_fun_error,_zero_length_ContentsConst,_char_too_big,
_inval_time,_nonzero_pad_bits_1,_nonzero_pad_bits_2,
_nonzero_pad_bits_3,_xml_DTD_forbidden,_sax_not_supported,
_sax_internal,_xml_invalid_pi,_xml_pi_forbidden,
_xml_parser_not_linked,_xml_ill_xmldecl,_alternative_notfound,
_property_settings_constraint,_duration_range_constraint,
_timepoint_range_constraint,_timepoint_range_constraint_1,
_recurrence_range_constraint,_recurrence_range_constraint_s,
_canonical_restriction,_time_bad_week,_time_bad_century,
_time_bad_year,_xml_root_name,_recurrence_range_constraint_unlim,
_xml_enc_format,_componentRelation_uniq,
_absence_constraint_string,_presence_constraint_string,
_iri_oid_invalid,_iri_arc_invalid,_bad_encrules_ppr,
_oer_unsupported_feature,_cl_input_file,_op_output_file,
_cl_output_file,_err_write_file,_err_read_file,_op_tmp_file,
_val_in_buf,_incorr_value,_err_wtite_socket,_err_read_socket,
_cant_load_socket,_cant_get_proc,_inval_socket,_writing_timeout,
_reading_timeout,_unknown_mobject,_container_not_match,
_hindmost_error
};
#endif

    /*************************************************************************/
    /*  DLL section (Windows and similar platforms only)                     */
    /*************************************************************************/
#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
struct memblock {
    struct memblock     *_prev;
    struct memblock     *_next;
    LONG                *fileOffset;
    short               *lineLength;
    short                blockNumber;
};
#if defined(DLL_LINKAGE)
    /*
     * The below import is needed only for running the internal testing
     * of the one SOED/TOED DLL with apitest.c.
     */
__declspec(dllimport) extern const int ossEncoderDecoderType;
#else
extern                       const int ossEncoderDecoderType;
#endif /* DLL_LINKAGE */
#endif /* _WIN32 || WIN32 || __WIN32__ */

#if defined(_WIN32)

#define CHECK_UNINITIALIZED_FPTR_FIELDS(tbl)
#endif /* _WIN32 */



    /*************************************************************************/
    /*      General functions section                                        */
    /*************************************************************************/

extern void *DLL_ENTRY ossGetHeader(void);
PUBLIC void DLL_ENTRY ossInitRootContext(struct ossGlobal *, unsigned char *);
PUBLIC void DLL_ENTRY ossInitRootContext1(struct ossGlobal *, unsigned char *);
PUBLIC void DLL_ENTRY ossInitRootContext2(struct ossGlobal *, unsigned char *);

#if defined(_DLL)
PUBLIC void DLL_ENTRY ossLinkAPI(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkOid(struct ossGlobal *);
#endif /* _DLL */

PUBLIC void DLL_ENTRY ossLinkBer(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkDer(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkPer(struct ossGlobal *);

PUBLIC void DLL_ENTRY ossLinkXer (struct ossGlobal *);

PUBLIC void DLL_ENTRY ossLink_Exer (OssGlobal *, void *);

PUBLIC void DLL_ENTRY ossLinkOerE(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkOerD(struct ossGlobal *);

PUBLIC unsigned long DLL_ENTRY ossGetPresetDecFlags(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossSetPresetDecFlags(struct ossGlobal *, unsigned long);
PUBLIC void DLL_ENTRY ossPrivateSetMoreFlags(struct ossGlobal *, int,
							unsigned char *);
PUBLIC void DLL_ENTRY ossPrivateGetMoreFlags(struct ossGlobal *world, int *,
							unsigned char **);
extern int   DLL_ENTRY _oss_cmp_date_time(OssGlobal *, char *, char *);
extern char *DLL_ENTRY _oss_parse_duration(char *, ossDuration *, ossBoolean);
extern char *DLL_ENTRY _ossStrToUintUnlimited(char *, OSS_UINT32 *);
extern char *DLL_ENTRY _ossStrToUintLimited(char *, OSS_UINT32, OSS_UINT32 *);
extern char *DLL_ENTRY _ossUintToStrUnlimited(char *, OSS_UINT32, OSS_UINT32);
extern char *DLL_ENTRY _ossUintToStrLimited(char *, OSS_UINT32, OSS_UINT32);

PUBLIC int DLL_ENTRY ossSetInternalFlags(struct ossGlobal *world, unsigned long flags);
PUBLIC unsigned long DLL_ENTRY ossGetInternalFlags(struct ossGlobal *world);
PUBLIC unsigned int DLL_ENTRY ossGetCompilerVersion(struct ossGlobal *world);


PUBLIC void DLL_ENTRY _oss_db_e_pre(struct ossGlobal *world,
	int pdunum, void *input, unsigned int *encFlags,
	char *bufpos, long buflen);
PUBLIC void DLL_ENTRY _oss_db_e_post(struct ossGlobal *world,
	int ret_code, char *outbuf, long outlen);
PUBLIC void DLL_ENTRY _oss_db_d_pre(struct ossGlobal *world,
	char *inbuf, long inlen, unsigned int *decFlags);
PUBLIC void DLL_ENTRY _oss_db_d_post(struct ossGlobal *world,
	int ret_code, int pdunum, void **output);

#if defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32) || defined(WINCE) || defined(_WIN64))
#pragma pack(push, align, 8)
#endif /* _MSC_VER && _WIN32 */
typedef struct {
    char _oss_a;
    double _oss_b;
} _oss_amax;
#if defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32) || defined(WINCE) || defined(_WIN64))
#pragma pack(pop, align)
#endif /* _MSC_VER && _WIN32 */

#define _oss_asize ((unsigned)((char *)&((_oss_amax *)NULL)->_oss_b - (char *)&((_oss_amax *)NULL)->_oss_a))
#define _oss_mem_align(a) ((_oss_asize - (a)%_oss_asize) % _oss_asize)

/*****************************************************************************/
/*  COMMON EXER section                                                        */
/*****************************************************************************/

typedef struct {
    OSS_UINT16 _oss_qJ;
    void *_oss_WJ;			
} exer_search;
typedef struct {
    unsigned char *_oss_QJ;
    OSS_UINT16 _oss_w;	    
} exer_table_entry;
typedef struct {
    OSS_UINT16 _oss_W;
    exer_table_entry *_oss_J;	
} exer_binary_table;
typedef struct {
    unsigned char *_oss_JJ;
    OSS_UINT16 _oss_wJ;		
    OSS_UINT16 _oss_w;
} exer_hash_table_entry;
typedef struct {
    exer_hash_table_entry *_oss_J;
    OSS_UINT32 _oss_q;
    OSS_UINT16 _oss_W;
} exer_hash_table;
typedef struct {
    OSS_UINT16 flags;
    unsigned char *uri;
    unsigned char *prefix;
} exer_namespace;

typedef struct {
    void         *_oss_Qj;
    OSS_UINT32    _oss_WjJ;
} exer_extensions_list;
typedef struct {
    OSS_UINT32 _oss_JW;
    void *_oss_wjJ;		
    unsigned char *_oss_WwJ;	
    OSS_UINT16 _oss_HWW;		
    OSS_UINT16 _oss_HQW;	
} exer_tag_decoder;
typedef struct {
    OSS_UINT32 _oss_JW;
    exer_tag_decoder *_oss_JQW;
    OSS_UINT32 _oss_QwW;		
} exer_decode_position;
typedef struct {
    unsigned char *_oss_wq;
    OSS_UINT16 _oss_Hj;
} exer_uri_test;
typedef struct {
    exer_search _oss_jJJ;		
    exer_uri_test *_oss_QqJ;	
} exer_qname_table;
typedef struct {
    unsigned char *_oss_wq;
    OSS_UINT16 _oss_wj;
    OSS_UINT16 _oss_Hj;		
} exer_uri_table_entry;
typedef struct {
    OSS_UINT32 _oss_JJJ;		    
    exer_uri_table_entry *_oss_Qj;    
    exer_search *_oss_wQW;	    
} exer_uri_table;
typedef struct {
    OSS_UINT16 _oss_wj;
    OSS_UINT16 _oss_JJJ;	
    void *_oss_wWJ;		
} exer_enum_table;
typedef struct {
    exer_enum_table _oss_WWW;	
    exer_search _oss_QjJ;	
    OSS_UINT32 _oss_QwJ;         
} exer_enum_data;
typedef struct {
    OSS_INT32 _oss_HWJ;		
    unsigned char *_oss_qW;	
} exer_enum_value;
typedef struct {
    LONG_LONG _oss_HWJ;		
    unsigned char *_oss_qW;	
} exer_long_enum_value;
typedef struct {
    OSS_UINT16 _oss_JW;
    exer_search _oss_jJJ;		
} exer_wild_data;
typedef struct {
    OSS_UINT32		_oss_JW;
    exer_enum_data	*_oss_jw;
} exer_bool;
typedef struct {
    OSS_UINT32		_oss_JW;
    exer_enum_data	*_oss_jw;
    unsigned int	_oss_jwW;
    unsigned int	_oss_WJW;
} exer_int;
typedef struct {
    OSS_UINT32		_oss_JW;
    exer_enum_data	*_oss_jw;
} exer_int_ll;
typedef struct {
    OSS_UINT32		_oss_JW;
} exer_int_huge;
typedef struct {
    OSS_UINT32		_oss_JW;
    exer_enum_data	*_oss_jw;
    exer_enum_value 	*_oss_qJW;
} exer_enum;
typedef struct {
    OSS_UINT32		_oss_JW;
    exer_enum_data	*_oss_jw;
    unsigned long	_oss_HqJ;
    unsigned long	max_length;
    unsigned int	_offset;
    unsigned long       _oss_JjJ;
} exer_bit;
typedef struct {
    OSS_UINT32		_oss_JW;
    unsigned long	max_length;
    unsigned int	_offset;
} exer_oct;
typedef struct {
    OSS_UINT32		_oss_JW;
    unsigned long	max_length;
    unsigned int  	_oss_wJW;
    unsigned int	_offset;
} exer_oid;
typedef struct {
    OSS_UINT32		_oss_JW;
    unsigned long	max_length;
    unsigned int	_offset;
} exer_char1;
typedef struct {
    OSS_UINT32		_oss_JW;
    unsigned long	max_length;
} exer_char2;
typedef struct {
    OSS_UINT32		_oss_JW;
    unsigned long	max_length;
} exer_char4;
typedef struct {
    OSS_UINT32		_oss_JW;
} exer_time;
typedef struct {
    OSS_UINT32		_oss_JW;
    int			_oss_wj;
} exer_iso_time;
typedef struct {
    OSS_UINT32		_oss_JW;
} exer_otyp;
typedef struct {
    OSS_UINT32		_oss_JW;
} exer_real;
#define OSS_EX_LIST              	0x00000001
#define OSS_EX_ATTRIBUTE 		0x00000002
#define OSS_EX_DYNAMIC_BUF 		0x00000004
#define OSS_EX_UNION	 		0x00000008
#define OSS_EX_KEEP_ATTR		0x00000010
#define OSS_EX_EXPLICIT_PDUNUM		0x00000020
#define OSS_EX_DFE			0x00000040
#define OSS_EX_OPTIMIZE_XMLNS		0x00000080
#define OSS_EX_FSA_PPTR_REF		0x00000100
#define OSS_EX_FSA_CNS_OFF		0x00000200
#define OSS_EX_SKIP_ELEMENT		0x00000400
#define OSS_EX_SKIP_CONTENT		0x00000800
#define OSS_EX_IN_TYPE_ATTR		0x00001000
#define OSS_EX_REREAD_TAG		0x00002000
#define OSS_EX_UPDATE_ADDRS		0x00004000
#define OSS_EX_UNKNOWN_ATTR		0x00008000
#define OSS_EX_NS_USED			0x00000001
#define OSS_EX_VALUE_IN_QUOTE		0x00000001
#define OSS_EX_ATTR_HANDLED		0x00000002
#define OSS_EX_ATTR_IN_EXT_TYPE		0x00000004
#define OSS_EX_TYPE_ATTR_HANDLED	0x00000008
#ifdef _OSS_CODE_FILE
#define OSS_EX_AS_LONG			0x00000000
#define OSS_EX_AS_BYTE			0x00000001
#define OSS_EX_AS_INT32			0x00000002
#define OSS_EX_AS_LLONG			0x00000004
#define OSS_EX_AS_NULLTERM		0x00000008
#define OSS_EX_AS_NAME			0x00000010
#define OSS_EX_AS_BUF			0x00000020
#define OSS_EX_NO_CHECK			0x00000040
#define OSS_EX_NAME_IS_LOCAL(name, nm, nm_len) \
    (name._uri == NULL && name._name._buflen == (nm_len) && \
	!memcmp(name._name._buf_store, nm, nm_len))
#define OSS_EX_NAME_IS_QUAL(name, uri, nm, nm_len) \
    (name._uri == uri && \
	(name._name._buflen - (name._colon_pos + 1)) == (nm_len) && \
	    !memcmp(name._name._buf_store +(name._colon_pos + 1), nm, nm_len))
#define OSS_EX_IS_PRESENT(mask, bit, erridx, edata, edtype) \
    if ((mask) & (bit)) \
	_oss_tdex_error(_env, erridx, edata, edtype); \
    (mask) |= (bit);
#define OSS_EX_FLD_IS_PRESENT(mask, bit) \
    OSS_EX_IS_PRESENT(mask, bit, _field_repeat, NULL, 0)
#define OSS_EX_ATTR_IS_PRESENT(mask, bit) \
    OSS_EX_IS_PRESENT(mask, bit, _xml_attr_repeated, &_attr->_name, OSS_EX_AS_NAME)
#define OSS_EX_IS_PRESENT_ARR(mask, n, bit, erridx, edata, edtype) \
    if ((mask)[n] & (bit)) \
	_oss_tdex_error(_env, erridx, edata, edtype); \
    (mask)[n] |= (bit);
#define OSS_EX_FLD_IS_PRESENT_ARR(mask, n, bit) \
    OSS_EX_IS_PRESENT_ARR(mask, n, bit, _field_repeat, NULL, 0)
#define OSS_EX_ATTR_IS_PRESENT_ARR(mask, n, bit) \
    OSS_EX_IS_PRESENT_ARR(mask, n, bit, _xml_attr_repeated, &_attr->_name, OSS_EX_AS_NAME)
#define OSS_EX_IS_PRESENT_UNT(mask, bit) \
    if ((mask) & (bit)) { \
	_f_idx = 0xffff; \
	break; \
    } \
    (mask) |= (bit);
#define OSS_EX_IS_PRESENT_ARR_UNT(mask, n, bit) \
    if ((mask)[n] & (bit)) { \
	_f_idx = 0xffff; \
	break; \
    } \
    (mask)[n] |= (bit);
#define OSS_EX_LOCAL_NAME(q) \
    ((q)._name._buf_store + ((q)._colon_pos + 1)), \
                              ((q)._name._buflen - ((q)._colon_pos + 1))
#define OSS_EX_IS_WS(c) \
    ((c) == ' '|| (c) == '\t' || (c) == '\n' || (c) == '\r')
#define OSS_EX_EXT_USE_TYPE_MODE	TRUE
struct st_OssToedDecmem {
    void *_oss_wWW;
    unsigned char *_oss_HwW;
    long _oss_jQW;
};
typedef struct st_OssEmbedData _oss_JWW;
#define OSS_EX_CONTENT \
    (_env->_lex_kind != EXER_END && \
	(_env->_lex_kind != EXER_TAG || _env->_tag->_kind != EXER_END_TAG))
#define OSS_EX_CONTENT_CPX \
    (_env->_lex_kind != EXER_END && _env->_tag->_kind != EXER_END_TAG)
#define OSS_EX_ADVANCE_LEX_EMP \
    if (_env->_start_tag->_kind == EXER_START_TAG) \
        _oss_tlex_get_lex(_env); \
    else \
        _env->_lex_kind = EXER_END; 
#define OSS_EX_ADVANCE_LEX_NONEMP \
    if (_env->_start_tag->_kind == EXER_START_TAG) \
        _oss_tlex_get_lex(_env); \
    else \
        _oss_tdex_error(_env, _xml_start_tag_expected, NULL, 0);
#define OSS_EX_ADVANCE_LEXC_EMP \
    if (_env->_start_tag->_kind == EXER_START_TAG) \
        _oss_tlex_get_lex_collapse(_env); \
    else \
        _env->_lex_kind = EXER_END; 
#define OSS_EX_ADVANCE_LEXC_NONEMP \
    if (_env->_start_tag->_kind == EXER_START_TAG) \
        _oss_tlex_get_lex_collapse(_env); \
    else \
        _oss_tdex_error(_env, _xml_start_tag_expected, NULL, 0);
#define OSS_EX_ADVANCE_TAG_EMP \
    if (_env->_start_tag->_kind == EXER_START_TAG) \
        _oss_tlex_get_tag(_env); \
    else \
        _env->_lex_kind = EXER_END;
#define OSS_EX_ADVANCE_TAG_NONEMP \
    if (_env->_start_tag->_kind == EXER_START_TAG) \
        _oss_tlex_get_tag(_env); \
    else \
        _oss_tdex_error(_env, _xml_start_tag_expected, NULL, 0);
#define OSS_EX_ADVANCE_LEX_DFE \
    if (_env->_start_tag->_kind == EXER_START_TAG) { \
        _oss_tlex_get_lex(_env); \
        if (_env->_lex_kind == EXER_TAG && _env->_tag->_kind == EXER_END_TAG) \
            _env->_flags |= OSS_EX_DFE; \
    } else \
        _env->_flags |= OSS_EX_DFE;
#define OSS_EX_ADVANCE_LEX_DFE_LOCAL \
    if (_env->_start_tag->_kind == EXER_START_TAG) { \
        _oss_tlex_get_lex(_env); \
        if (!(_env->_lex_kind == EXER_TAG && _env->_tag->_kind == EXER_END_TAG)) \
            _content = 1; \
    }
#define OSS_EX_FIELD_IS_PRESENT(mask, bit, fname) \
	if ((mask) & (bit)) \
		_oss_toed_error(_g, _xml_dubl_val, fname); \
	(mask) |= (bit);

typedef struct st_OssToedDecmem OssToedDecmem;

/* lexeme kind */
typedef enum {
    EXER_END, EXER_TAG, EXER_UTF8, EXER_UNICODE
} exer_lex_kind;

/* tag kind */
typedef enum {
/* EXER_SKIP_TAG - is unknown tag to skip */
    EXER_SKIP_TAG, EXER_START_TAG, EXER_END_TAG, EXER_EMPTY_TAG
} exer_tag_kind;

typedef struct exer_buf {
    unsigned char	*_buf_store;
    unsigned long 	_buflen;
    unsigned long	_global_offset;
} exer_buf;

typedef struct exer_entity {
    struct exer_entity  *_next;
    exer_buf		_name;
    exer_buf      	_value;
    OSS_UINT32		_flags;
} exer_entity;

/* qualified name structure */
typedef struct {
    exer_buf		_name;
    long 		_colon_pos; /* separator position */
    unsigned char	*_uri;	    /* unique URI pointer */
} exer_name;

/* attribute structure */
typedef struct exer_attribute {
    struct exer_attribute *_next;	/* next attribute */
    exer_name 		  _name;	/* attribute name */
    exer_buf		  _value;
    OSS_UINT32 		  _flags;
} exer_attribute;

struct exer_denv;
typedef struct exer_denv exer_denv;

struct exer_embed;
typedef struct exer_embed exer_embed;

typedef void (CDECL_ENTRY_FPTR *exer_embed_decoder)(exer_denv *, exer_embed *);

struct exer_embed {
    exer_embed_decoder  _dec;	    /* pointer to the EMBED decoding function */
    unsigned long       _count;     /* number of elements */
    void		*_data;     /* pointer to decoded data */
    void		*_data_end; /* current position - only for UNBOUNDED */
};

/* tag structure */
typedef struct exer_tag {
    exer_name		_name;      /* tag name */
    exer_attribute 	*_attrs;    /* pointer to the first attribute */
    exer_embed          *_embed;    /* if not NULL, type has EMBED-VALUES */
    unsigned char       *_mem_ns;   /* pointer to start of stack */
    unsigned char 	*_mem_attr; /* pointer to start of stack */
    exer_tag_kind 	_kind;	    /* tag kind */
} exer_tag;

/* the lexer status */
#define MAX_LEX_NESTING 	8
typedef struct {
    unsigned char       *_inbufpos;      /* current encoding */
    unsigned long       _inbuflen;	/* current length */
    unsigned long	_totallen;	/* total length */
    unsigned long	_global_offset;  /* encoding global offset */	
    OSS_UINT32 		_flags;	    	/* flag word */
    OSS_UINT32 		_nesting;    	/* current nesting level */
} exer_input;

typedef struct exer_ns {
    struct exer_ns      *_next;     /* previous namespace */
    exer_buf		_prefix;
    unsigned char	*_uri;	    /* unique URI pointer */
    unsigned long	_uri_len;
    OSS_UINT32          _flags;     /* flag word */
    OSS_UINT32 		_scope;	    /* nesting level */
} exer_ns;

/* data structure to keep a lexeme */
typedef struct exer_save_lexeme {
    exer_lex_kind	_lex_kind;	/* kind */
    unsigned long	_tag_start, 
			_tag_end;	/* start/end positions of a tag */
    union {
       exer_tag 	*_tag;		/* a tag */
       unsigned char	_utf8[5];	/* Utf8 character (4 bytes) */
       OSS_UINT32 	_unicode;	/* Unicode value */
    } _u;
} exer_save_lexeme;

typedef struct exer_save_cc_lex {
    exer_tag		_cur_tag,
			*_start_tag,
			*_tag;
    exer_save_lexeme    _lex;
    exer_ns		*_ns;
    unsigned char       *_stk_ptr;
} exer_save_cc_lex;

/* rescan data structure */
typedef struct exer_rescan {
    jmp_buf		_errorBuf;
    jmp_buf		*_old_errorBuf;
    exer_save_lexeme	_lex;		/* current lexeme */
    exer_input		_input;		/* current encoding */
    exer_input 		_lexstack[/*MAX_LEX_NESTING*/8];
    OSS_UINT32		_lexstacksize;
    unsigned long	_num_fields;
    unsigned long	_alt_idx;
    OssToedDecmem 	_outmem;
    unsigned char       *_stk_ptr;
    int			_ret_code;
} exer_rescan;     

struct exer_denv {
    OssGlobal 		*_g;
    exer_namespace 	*_ns_array;	/* points to the structure which represents
					 * an XML namespace in the E-XER control table */
    OSS_INT32		_namespace_count;
    unsigned char	*_xml_uri;	/* URI for "xml" prefix */
    unsigned char	*_ctrl_uri;	/* URI for control NS */
    unsigned char	*_asn1_uri;	/* ASN1 URI or NULL */
    exer_tag 		*_tag;		/* a pointer to the current tag */
    exer_tag            *_start_tag;	/* a pointer to the previous tag */
    exer_entity     	*_entities;		/* the list of entities */
    exer_ns  	    	*_ns;		/* the stack of NS */
    exer_input	    	_lexstack[MAX_LEX_NESTING];	/* the encoding stack */
    exer_input		_input;
    union {				
	OSS_UINT32  	_unicode;
	unsigned char   _utf8[5];		/* utf8[4]-keeps the length of UTF8 char */
    } _cur_char;
    unsigned long	_tag_start, 
			_tag_end;	/* start/end positions of a tag */
    unsigned long	_cc_pos; 
    unsigned long	*_size;		/* to error reporting */
    OSS_UINT16      	_lexstacksize;	/* stack counter */
    exer_lex_kind   	_lex_kind;	/* kind of a curremt lexeme */
    OSS_UINT32		_flags;
};
/* end of TOED EXER Decoder section */


typedef struct exer_qname {
    unsigned char	*_oss_WjW;
    unsigned int	_oss_JHH;
    OSS_UINT16        	_oss_wQj;	
} exer_qname;
#if 0
typedef struct _exer_ns {
    struct _exer_ns	*_oss_qWH;
    struct _exer_ns	*_oss_qJw;
    unsigned char	*_oss_wJH;
    unsigned char	*_oss_WjW;
    unsigned long	_oss_WQw;
    unsigned long	_oss_JHH;
} _exer_ns;
#endif
typedef struct exer_uri_list exer_uri_list;
typedef struct exer_attr_list exer_attr_list;
struct exer_attr_list {
    exer_attr_list	*_oss_qWH;
    unsigned char	*_oss_wJH;
    unsigned char	*_oss_WjW;
    unsigned int	_oss_WQw;
    unsigned int	_oss_JHH;
};
struct exer_eenv;
typedef struct exer_eenv exer_eenv;
typedef void (CDECL_ENTRY_FPTR *exer_embed_encoder)(exer_eenv *);

struct exer_uri_list {
    exer_uri_list	*_next;
    unsigned char	*_uri;
    unsigned int	_uri_len;
};

typedef struct teex_embed {
    struct teex_embed		*_prev;
    exer_embed_encoder		_enc;
    void			*_data;
    unsigned long		_idx;
    unsigned long		_count;
    OSS_UINT32          	_nesting;
} teex_embed;

struct exer_eenv {
    /* Common encoder/decoder data */
    struct ossGlobal	*_g;
    /* Pointers to the list of declared attributes and URIs */
    exer_uri_list	*_uris;
    exer_attr_list	*_attrs;
    /* Local context */
    teex_embed	        *_embed;
    teex_embed	        *_embed_prev;
    /* Specific data */
    long                _linepos;/* start position at current output line */
    long                _taglen; /* length of last encoded 'prefix:tag' string */
    long		_curlen; /* estimated size of currently encoded string value */
    unsigned int    	_indent; /* number of indentation spaces for value */
    /* Dynamic flags */
#define OSS_EX_CANCEL_FORMATTING		0x00000010
#define OSS_EX_UNTAGGED_SET_OF_EL		0x00000020
#define OSS_EX_DISABLE_ATTRS			0x00000040
#define OSS_EX_URI_FOUND			0x80000000
#define OSS_EX_DEFAULT_NS			OSS_EX_URI_FOUND
    OSS_UINT32          _nesting;
    OSS_UINT32          _embed_nesting;
    OSS_UINT32         	_flags;
    /* --- The fields below should be moved to the OssGlobal structure --- */
    exer_namespace 	*_ns_array;	/* namespace array in the control table or  *
					 * its copy created by namespace prefix API */
    OSS_INT32		_ns_count;
    exer_search		*_ns_search;
    unsigned char	*_reserved_prefix;
    OSS_UINT16		_asn1NsIndex;
    OSS_UINT16		_dns_idx;	/* default namespace index */
/*
    OSS_UINT16		_controlNsIndex;
*/
    /* ------------------------------------------------------------------- */
};
/* end of TOED EXER Encoder section */

/*****************************************************************************/
/*  TOED general section                                                     */
/*****************************************************************************/

#ifdef EBCDIC
#include <iconv.h>
#endif
#include <setjmp.h>

/* The _MEM_ARRAY_SIZE size should be such that the size of the encDecVar
 * field be equal or greater than that of the world->c structure */

#ifdef __hp9000s300
#define _MEM_ARRAY_SIZE	34
#endif

#ifdef __alpha
#ifdef __osf__
#define _MEM_ARRAY_SIZE	43
#endif	/* __osf__ */
#endif	/* __alpha */

#ifdef _AIX
#define _MEM_ARRAY_SIZE	52
#endif
#ifdef __hp9000s700
#define _MEM_ARRAY_SIZE	60
#endif

#ifdef __NeXT__
#define _MEM_ARRAY_SIZE	66
#endif

#ifdef VAXC
#define _MEM_ARRAY_SIZE	78
#endif

#ifdef __mips
#	define _MEM_ARRAY_SIZE       70
#endif	/* __mips */

#ifdef _FTX	/* Stratus's Fault-Tolerant Unix */
#define _MEM_ARRAY_SIZE  84
#endif

#ifdef __HIGHC__
#define _MEM_ARRAY_SIZE       52
#endif	/* __HIGHC__ */

#ifdef __arm
#define _MEM_ARRAY_SIZE       60
#endif	/* __arm */

#if defined(_WIN32)
#define _MEM_ARRAY_SIZE 52
#endif /* _WIN32 */

#ifdef _MCCPPC
#define _MEM_ARRAY_SIZE       72
#endif	/* _MCCPPC */

#if defined(__vms) && (__INITIAL_POINTER_SIZE + 0) == 64
#define _MEM_ARRAY_SIZE 40
#endif

#ifndef _MEM_ARRAY_SIZE
#define _MEM_ARRAY_SIZE 60
#endif

typedef struct _mem_array_ {
    short           _used;	                /* Next available entry */
    void           *_entry[_MEM_ARRAY_SIZE];	/* Pointers to allocated
						 * memory */
    struct _mem_array_ *_next;	/* Pointer to additional mem_array */
} _mem_array;

struct st_OssMemoryBlockBounds {
    unsigned char *left;
    unsigned char *right;
};

struct st_OssMemoryBlockHeader {
    struct st_OssMemoryBlockHeader *prev;
    unsigned char *block_end;
};

struct st_OssMemoryBlockHeaderEx {
    struct st_OssMemoryBlockHeaderEx *prev;
    unsigned char *block_end;
    unsigned char *data_end;
};

typedef struct st_OssMemoryBlockBounds OssMemoryBlockBounds;
typedef struct st_OssMemoryBlockHeader OssMemoryBlockHeader;
typedef struct st_OssMemoryBlockHeaderEx OssMemoryBlockHeaderEx;


#ifndef OSSDEBUG
#define OSSDEBUG 2
#endif /* OSSDEBUG */

typedef struct _encoding_ {
	       long   length;           /* length of the encoding */
	       char   *value;           /* pointer to encoding octets */
} _encoding;

typedef struct _enc_block_ {
    struct _enc_block_ *_next;        /* nested setofs form a list of these */
    long   size;                     /* size of the encodings array */
    long   used;                     /* number of items used in the array */
    _encoding       *enc;            /* pointer to array of encodings */
    _mem_array      mem;             /* previous encoding saved*/
    _mem_array      *mem_tail;
    char            *pos;
    long            max_len;
    ossBoolean           buffer_provided;
    long            _encoding_length;
    ossBoolean	    queue;	/* memory storage arrangement: stack or queue */
} _enc_block;

struct _enum_data {
	int         num;     /* number of enumerations */
	OSS_INT32   *enums;  /* pointer to sorted array of enumerations */
};

struct _char_data {
	int      num;  /* number of characters in PermittedAlphabet */
	void     *pa;  /* pointer to PermittedAlphabet char string */
	void     *ia;  /* pointer to inverted indices string */
};

struct st_tree_char_data {
    unsigned int length;
    const OSS_UINT32 *pa;
};

struct st_char_data {
    unsigned int length;
    const char *pa;		/* pointer to PermittedAlphabet char string */
    const unsigned char *inv_pa;/* pointer to inverted indices string */
};

struct st_wide_char_data {
    unsigned int length;
    const char *pa;		/* pointer to PermittedAlphabet char string */
    const unsigned char *inv_pa;/* pointer to inverted indices string */
    unsigned int base_value;
};

#define OSS_PSD_ENCODE_ALIGNED_VALUE	0x80
#define OSS_PSD_ENCODE_UNALIGNED_VALUE	0x8000
#define OSS_PSD_TIME_TYPE		0x10000
#define OSS_PSD_EXTENSIBLE		0x20000
#define OSS_PSD_MULTI_PLANE_PA		0x40000
#define OSS_PSD_ALWAYS_IN_ROOT		0x80000
#define OSS_PSD_IN_EXTENSION		0x80

struct st_PER_String_Data {   
    const void *ppa;
    unsigned long lb;
    unsigned long ub;
    unsigned long full_ub;
    unsigned int flags;
};

typedef struct st_PER_String_Data PER_String_Data;

/* The following structures are used by XER decoder to perform effective
 * search in character string array (SET/SEQUENCE/CHOICE/ENUMERATED).
 *
 * Implementation comments:
 *        - if hashes are present, it is assumed their array is sorted
 * (least value first), string array is assumed unsorted
 *        - if hashes are absent, the string data array is assumed sorted
 * (lexicographically, the 'least' string goes first)
 */
struct _string_data {
    const char * value;		/* string value */
    size_t        slen;		/* string length */
    unsigned char lmask;	/* kinds of acceptable tags */
    OSS_INT32  src;		/* return value if string matched */
};

struct _string_search_data {
    size_t              alen;	/* arrays length */
    OSS_INT32           unknown_rc; /* is returned when no match occurs */
    const struct _string_data * sa; /* string data array */
    const OSS_UINT32    * ha;	/* hashes array; may be NULL - no hashes */
};

/* The following structure are used by XER encoder to perform effective
 * search in character string array (ENUMERATED).
 * It's used as array. And for the first value of this array the field
 * 'count' contains quantity of array records, and the field 'nm' is NULL
 * for unextensible enum, or is "unknown_enum" differently.
 */
typedef struct {
     long    count; /* enum value */
     char *  nm; /* value name */
} _oss_enumInfo;

typedef struct _mem_block_ {
   void               *_data;
   struct _mem_block_ *_prev;
} _mem_block_;

typedef struct _st_print_pdu_ {
    int (*_pf)(struct ossGlobal *, void *);
    const char *_name;
} _print_pdu_;

#define _oss_mem_bsize(tsize, msize) \
		(tsize > 1024 ? tsize : \
		(tsize * msize) < 1024 ? tsize * (msize ? msize : 1) : 1024)

#define _oss_mem_bsize_unconstr(tsize) \
		(tsize > 1024 ? tsize : 1024)

#define _oss_mem_bcount(tsize, msize) \
		(tsize > 1024 ? 1 : \
		(tsize * msize) < 1024 ? (msize ? msize : 1) : 1024 / tsize)

#define _oss_mem_bcount_unconstr(tsize) \
		(tsize > 1024 ? 1 : 1024 / tsize)

#define OSS_TOED_API_LEVEL 32

#define _dstd_parms_def char **_pos, long *_buf_len, long _length
#define _dstd_parms _pos, _buf_len, _length
#define _sdstd_parms_def char **_pos, long *_buf_len
#define _sdstd_parms _pos, _buf_len

/*
 * std_parms_def and std_parms.
 * These parameters are passed to most TOED encoding functions.
 * They are:
 *
 * char **pos:  this varies slightly depending upon the
 *   kind of encoding.  For DEFINITE encoding, this is
 *   a pointer to a pointer to the place where data
 *   was last written into memory.  For INDEFINITE encoding
 *   this is a pointer to a pointer to the place where
 *   data is next to be written.
 *
 *   Any function which writes encoded data updates *pos
 *   to stay current.
 *
 * long *max_len:  *max_len is the number of bytes left
 *   in the current memory buffer.  (The buffer into
 *   which encoded data is being written.)  If we are using
 *   memory pages, this is the number of bytes left before
 *   we need to allocate a new page.  If we are using the
 *   user's buffer, this is the number of bytes left before
 *   we'll need to complain violently.
 */
#define _std_parms_def char **_pos, long *_max_len
#define _std_parms _pos, _max_len

/* Entry Points for the Interface Routines */

typedef    void       (DLL_ENTRY_FPTR *_System _Encode_function)
			(struct ossGlobal *world, int pdunum,
			void *inbuf);

typedef    void      (DLL_ENTRY_FPTR *_System _Decode_function)
			(struct ossGlobal *world, int *pduNum,
			void **outbuf);

typedef    int       (DLL_ENTRY_FPTR *_System _FreePDU_function)
			(struct ossGlobal *world, int pdunum,
			void *data);

typedef    void      (DLL_ENTRY_FPTR *_System _Ossinit_function)(struct ossGlobal *);

typedef    void       (DLL_ENTRY_FPTR *_System _Encode_EXER_function)
			(exer_eenv *env, int pdunum,
			void *inbuf);

typedef    void       (DLL_ENTRY_FPTR *_System _Decode_EXER_function)
			(exer_denv *env, int *pduNum,
			void **outbuf);

typedef    void *     (DLL_ENTRY_FPTR *_System _Decode_OER_function)
			(struct ossGlobal *world, int pduNum);

typedef    int	     (DLL_ENTRY_FPTR *_System _PrintPDU_function)
			(struct ossGlobal *, int pdunum,
			void *data);
typedef    int       (DLL_ENTRY_FPTR *_System _CopyPDU_function)(struct ossGlobal *, int pdunum,
			void *src, void **dst);
typedef    int       (DLL_ENTRY_FPTR *_System _CmpPDU_function)(struct ossGlobal *, int pdunum,
			void *odata, void *cdata);
typedef    void	     (DLL_ENTRY_FPTR *_System _ChkCstrPDU_function)(struct ossGlobal *, int pdunum,
			void *data);
typedef    int	     (DLL_ENTRY_FPTR *_System _GetExtAdd_function)(struct ossGlobal *, void *_ext,
			unsigned int _extnumb, OssBuf *_data);

typedef struct _entry_point_struct_ {
	_Ossinit_function	_ossinit_function;
	_Encode_function        _ber_encode_function;
	_Decode_function        _ber_decode_function;
	_FreePDU_function	_freePDU_function;
	unsigned short int      _oss_ber_version_number;
	_Encode_function        _per_encode_function;
	_Decode_function        _per_decode_function;
	unsigned short int      _oss_per_version_number;
	unsigned int            _oss_pa_count;
	struct _char_data       *_chars_ptr;
	_PrintPDU_function      _printPDU_function;
}               _entry_point_struct;

typedef struct _mixed_real_internal_ {
    double base2;
    char  *base10;
} _mixed_real_internal;

typedef struct _oss_xapi_entries_struct_ {
    unsigned short		_api_lvl;
    _CopyPDU_function		_copy_pdu_function;
    _CmpPDU_function            _cmp_pdu_function;
    _Encode_function            _xer_encode_function;
    _Decode_function            _xer_decode_function;
    unsigned short int          _oss_xer_version_number;
    _ChkCstrPDU_function         _chk_cstr_pdu_function;
    _GetExtAdd_function		_get_ext_add_function;
    _Encode_EXER_function       _exer_encode_function;
    _Decode_EXER_function       _exer_decode_function;
    unsigned short int          _oss_exer_version_number;
    unsigned short int          _oss_oer_version_number;
    _Encode_function            _oer_encode_function;
    _Decode_OER_function	_oer_decode_function;
} _oss_xapi_entries_struct;

/* typedef's for the context information */

typedef enum _context_type {
    _boolean_type, _integer_type, _enumerated_type, _real_type,
    _bitstring_type, _octetstring_type, _null_type, _sequence_type,
    _sequence_of_type, _set_type, _set_of_type, _choice_type,
    _charstring_type, _object_identifier_type, _time_type, _any_type,
    _opentype, _embedded_pdv_type, _unrestr_charstring_type,
    _relative_oid_type, _contconstr_type, _defered_type, _unknown_type
}               _Context_Type;

typedef struct _context_id {
    char           *_element_name;
    char           *_element_type;
    _Context_Type   _type;
}               _Context_Id;


typedef struct _context_element {
    struct _context_element *_parent;
    _Context_Id    *_id;
    long            _occurrence;/* For SET OF or SEQUENCE OF */
}               _Context_Element;

typedef enum _context_state {
    _encoding_tag, _encoding_length, _encoding_data,
    _decoding_tag, _decoding_length, _decoding_data,
    _checking_cnstrnts
}               _Context_State;

typedef struct _context_anchor {
    _Context_Element *_last;
    int             _pdu_number;
    _Context_Id    *_pdu_id;
    _Context_State  _state;
}               _Context_Anchor;


typedef  char _Per_Inverted_Index[128];

extern _Context_Anchor _oss_context_anchor;

typedef struct _ossDTDate {
    unsigned char bit_mask;
#define _ossDTDateCenturyBit       0x80
#define _ossDTDateYearBit          0x40
#define _ossDTDateWeekBit          0x20
#define _ossDTDateMonthBit         0x10
#define _ossDTDateDayBit           0x08
#define _ossDTDateBasicYearBit     0x04
#define _ossDTDateProlepticYearBit 0x02
#define _ossDTDateNegativeYearBit  0x01
    unsigned short number_of_yc_digits;
    int            year_or_century;
    unsigned short week;
    unsigned short month;
    unsigned short day;
} _ossDTDate;

typedef struct _ossDTTimeFraction {
    unsigned short number_of_digits;
    unsigned int value;
} _ossDTTimeFraction;

typedef struct _ossDTTime {
    unsigned char bit_mask;
#define _ossDTTimeHoursBit    0x80
#define _ossDTTimeMinutesBit  0x40
#define _ossDTTimeSecondsBit  0x20
#define _ossDTTimeFractionBit 0x10
#define _ossDTTimeUtcBit      0x08
#define _ossDTTimeDiffBit     0x04
    unsigned short hours;
    unsigned short minutes;
    unsigned short seconds;
    struct _ossDTTimeFraction fraction;
    struct _ossDTTimeDifference {
#define _ossDTTimeDiffMinusBit   0x80
#define _ossDTTimeDiffMinutesBit 0x40
	unsigned char  bit_mask;
	unsigned short hours;
	unsigned short minutes;
    } diff;
} _ossDTTime;

typedef struct _ossDTPoint {
    _ossDTDate date;
    _ossDTTime time;
} _ossDTPoint;

typedef struct _ossDTDuration {
    unsigned char bit_mask;
    unsigned char accuracy_bit;
#define _ossDTDurationYearsBit    0x80
#define _ossDTDurationMonthsBit   0x40
#define _ossDTDurationWeeksBit    0x20
#define _ossDTDurationDaysBit     0x10
#define _ossDTDurationHoursBit    0x08
#define _ossDTDurationMinutesBit  0x04
#define _ossDTDurationSecondsBit  0x02
#define _ossDTDurationFractionBit 0x01
    unsigned int years;
    unsigned int months;
    unsigned int weeks;
    unsigned int days;
    unsigned int hours; 
    unsigned int minutes;
    unsigned int seconds;
    struct _ossDTTimeFraction fraction;
} _ossDTDuration;

#define _ossDuration_years_present    _ossDTDurationYearsBit
#define _ossDuration_months_present   _ossDTDurationMonthsBit
#define _ossDuration_weeks_present    _ossDTDurationWeeksBit
#define _ossDuration_days_present     _ossDTDurationDaysBit
#define _ossDuration_hours_present    _ossDTDurationHoursBit
#define _ossDuration_minutes_present  _ossDTDurationMinutesBit
#define _ossDuration_seconds_present  _ossDTDurationSecondsBit
#define _ossDuration_fraction_present _ossDTDurationFractionBit

typedef struct _ossDTInterval {
    unsigned char bit_mask;
#define _ossDTIntRecurrenceBit    0x80
#define _ossDTIntStartPointBit    0x40
#define _ossDTIntEndPointBit      0x20
#define _ossDTIntStartDurationBit 0x10
#define _ossDTIntEndDurationBit   0x08
    unsigned short number_of_r_digits;
    unsigned int recurrence;
    union _ossDTIntervalPoint {
	_ossDTPoint point;
	_ossDTDuration duration;
    } start;
    union _ossDTIntervalPoint end;
} _ossDTInterval;

#define _ossDateTimeIsEmpty(v) (!(v).bit_mask)
#define _ossDuration(v)        ((v).start.duration)

typedef _ossDTInterval _ossDateTime;


typedef struct _Xml_Enc_Env {
    struct _Xml_Enc_Env * _prev;
    /* Common encoder/decoder data */
    struct ossGlobal *_g;
    /* Specific data */
    unsigned int	indent; /* number of indentation spaces for value */
    long		linepos;/* start position at current output line */
    long		taglen;	/* length of last encoded tag */
    long		totallen; /* summary length of encoder's output memory blocks */
} _Xml_Enc_Env;

typedef struct _Xml_Dec_Env {
    /* Common encoder/decoder data */
    struct ossGlobal *_g;
    /* Specific data */
    char		* inbuf;
    unsigned char	byte;
    unsigned char	lkind;
    char		* name;
    size_t		nlen;
#   define _FSA_PPTR_REF 0x01
#   define _FSA_CNS_OFF  0x02
    OSS_UINT32		_flags;
} _Xml_Dec_Env;

struct ossExtStackElement {
    unsigned char *_bufpos;
    unsigned long _buflen;
    void *buffer;
    union {
	unsigned char *_allocated_buffer;
	unsigned int _used;
    } u;
    unsigned int _bitpos;
};

#define EXT_STACK_SIZE 4

struct ossExtStack {
    struct ossExtStack *_next;
    struct ossExtStackElement st[EXT_STACK_SIZE];
    unsigned int sp;
};

typedef struct _oss_mem_link {
    struct _oss_mem_link *_next, *_prev;
} _oss_mem_link;

/* TOED Control table header */
typedef struct {
    OSS_UINT32          table_flags;
    OSS_UINT16          table_version;
    OSS_UINT16          table_compat_version;
    OSS_INT32           namespace_count;
    exer_namespace      *namespace_array;
    exer_search         *namespace_search;
    exer_decode_position root_decoder;
    unsigned char       *reserved_prefix;
    OSS_UINT16      	control_ns;
    OSS_UINT16          asn1_ns;
    exer_search		*esa;
    exer_tag_decoder    *tda;
    exer_qname_table    *qta;
    exer_bool		*boola;
    exer_int		*inta;
    exer_int_ll		*int_lla;
    exer_int_huge	*int_hugea;
    exer_enum		*enuma;
    exer_bit		*bita;
    exer_oct		*octa;
    exer_oid		*oida;
    exer_char1		*char1a;
    exer_char2		*char2a;
    exer_char4		*char4a;
    exer_time		*timea;
    exer_iso_time	*iso_timea;
    exer_otyp		*otypa;
    exer_real		*reala;
    OSS_INT32           ext_count;
    void                **ext_array;
    OSS_INT32           ext_list_count;
    exer_extensions_list *ext_list_array;
} exer_toed_table;
                                        
typedef struct ToedExerData {
    exer_toed_table	*exer_table;
    unsigned char 	reserved_prefix[16];
    void        	*_ex_nsa;
    unsigned int 	has_default_namespace : 1;
} ToedExerData;

typedef struct ToedDataExt {
    long      bytes_read_by_decoder;
    int         (DLL_ENTRY_FPTR *ossUserVprint)(struct ossGlobal *,
			const char *format, va_list ap);
    void     *(DLL_ENTRY_FPTR *_System mallocpSaved)(size_t sz);
    void      (DLL_ENTRY_FPTR *_System freepSaved)(void *p);
    OssBuf    tmpBuffer;
    _mem_array	   _oss_stack;
    _mem_array*	   _oss_stack_tail;
    unsigned char  padding_bits;
    unsigned int    _iOsetNum;	   /* total number of objectsets */
    void	   *_piOsetInfo;   /* Inextensible objectsets info */
    unsigned int    _xOsetNum;	   /* number of extensible object sets */
    XOSetInfoEntry * _pxOsetInfo;  /* Extensible objectsets info */
    int		   (CDECL_ENTRY_FPTR *pcmpInfoObj)(struct ossGlobal *, int , void *, void *, int);
    void           *so_handle;
    _oss_xapi_entries_struct *_xapi_ent;
    _Xml_Enc_Env   *_xee;	   /* XER encoder specific fields */
    _Xml_Dec_Env   *_xde;	   /* XER decoder specific fields */
    char           *XSL_name;      /* XSL file name to be used by encoder */
    char           *DTD_name;      /* DTD name (root element) */
    short          DTD_kind;       /* SYSTEM/PUBLUC/NONE */
    char           *DTD_ExternalID;/* dtd file name to be used by encoder */
    void	   *xtmpbuf;	   /* XER runtime temporary buffer *
				    * for error recovery purposes  */
/* For additional flags-related information */
    int            fl_count;
    unsigned char  fl_mask_default;
    unsigned char *fl_mask;
    unsigned long  compat_flags; /* Compatibility flags for TOED */
    /* limit and counter of nesting level for constructed string encodings */
    int         constructedNestingLimit;
    int         constructedNestingCounter;
    /*
     * limit and counter of nesting level of encoding of SET, SEQUENCE, SET OF,
     * SEQUENCE OF and CHOICE
     */
    int         seqSetNestingLimit;
    int         seqSetNestingCounter;
    struct ossExtStack _oss_ext_stack;
    ossBoolean  dtemp_mem;
    int         xmlEncRule; /* used by ossBinary2XML()/ossXML2Binary() */
    int		(CDECL_ENTRY_FPTR *ossUserFieldCpyp)(struct ossGlobal *world, OpenType *src, OpenType *dest);
    int		(CDECL_ENTRY_FPTR *ossUserFieldCmpp)(struct ossGlobal *world, OpenType *src, OpenType *dest);
    unsigned long debug_flags; /* Debug flags for use with ossSetDebugFlags */
    ossDebugData debug_data;
    void	*mem_handle;
    void	*(CDECL_ENTRY_FPTR *ossUserMallocp_saved)(void *, size_t);
    void	*(CDECL_ENTRY_FPTR *ossUserReallocp_saved)(void *, void *, size_t);
    void	 (CDECL_ENTRY_FPTR *ossUserFreep_saved)(void *, void *);
    /* for Lean ASN.1/C++; needed for opentypes support */
    void	*cppPointer;
    /* to mark using of time interval start-end points */
    unsigned int timeSEPointsInUse: 2,
		timeDiffSign : 1,
		timeDiffHours : 4,
		timeDiffMinutes : 6;
    ToedExerData exd;
    char	*ext_errMsg;
} ToedDataExt;

typedef struct _EncDecGlobals {

   jmp_buf	  *_oss_err_env;
   void		 (CDECL_ENTRY_FPTR *_old_sigsegv)(int);
   void		 (CDECL_ENTRY_FPTR *_old_sigbus)(int);
   int		   _oss_asn1err;
   char		  *_oss_err_msg;
  ossBoolean            _buffer_provided;
  ossBoolean            _tag_decoded;
  ossBoolean            _restrain_mode;
   long		   _restrain_size;
  _Context_Anchor  _oss_context_anchor;
   char		  *_oss_outbufpos;
   long		   _oss_outbuflen;
  _mem_array	   _oss_mem;
  _mem_array	  *_oss_mem_tail;
    union {
	struct {
	    _mem_array	*_oss_temp_tail;
	    _mem_array	_oss_temp_mem;
	} mem_array; /* obsolete */
	struct {
	    OssMemoryBlockHeaderEx *last_block;
	    unsigned char *first_avail;
	    OssMemoryBlockBounds bounds;
	    OssMemoryBlockHeader *last_altblock;
	} stack;
    } tmp_mem;
   long		   _oss_mem_alloc;
   long		   _oss_out_alloc;
   unsigned int     relax_ber: 1;
   unsigned int     der: 1;
   unsigned int     _cxer: 1; /* TRUE when CXER encode/decode is requested */
   unsigned int     _coer: 1; /* TRUE when COER encode/decode is requested */
    OSS_UINT32	    _genflags; /* flags for usage by generated routines */
    ossBoolean            _aligned;
    int             _bitpos;
    struct ossGlobal *_prev;
    char           *_oss_inbufpos;
    long            _oss_inbuflen;
    void           *_prevbuf;
    long             encoding_length;
    void           *_blockptr;
    struct ossGlobal *_next;
    FILE           *asn1outSaved;
    int         (DLL_ENTRY_FPTR *asn1prntSaved)(FILE *stream,
			const char *format, ...);
    int         (DLL_ENTRY_FPTR *ossUserPrintp)(struct ossGlobal *,
			const char *format, ...);
    void	*(CDECL_ENTRY_FPTR *ossUserMallocp)(void *, size_t);
    void	*(CDECL_ENTRY_FPTR *ossUserReallocp)(void *, void *, size_t);
    void	 (CDECL_ENTRY_FPTR *ossUserFreep)(void *, void *);

#ifdef EBCDIC
    /* The following fields contain the default permitted alphabets for
     * IA5String, NumericString, PrintableString, and VisibleString */
    char                *ia5chars;
    char                *numchars;
    char                *prichars;
    char                *vischars;
#ifdef ICONV_AVAILABLE
    /* The following fields contain the iconv() conversion tables */
    iconv_t              toAscii;
    iconv_t              toEbcdic;
#endif /* ICONV_AVAILABLE */
    int                  semaphoreId;   /* For mutex on EBCDIC machines */
#endif
    int indent_level;

    union {
	void *pointer;
	double size[4];
	struct {
	    unsigned short preset_flags;
	    ToedDataExt   *ext;
	    char  *rsf_tagpos;
	    long   rsf_taglen;
	} fields;
    } reserved;

#if defined(_WIN32)
#endif /* _WIN32 */
} _EncDecGlobals;

#ifndef relax_per
#define relax_per relax_ber
#endif /* relax_per */

    /*************************************************************************/
    /*      TOED general functions section                                   */
    /*************************************************************************/

#if defined(_WIN32)
extern BOOL CDECL_ENTRY oss_globlist(struct ossGlobal *, struct globalInfo *,
		     struct globalInfo **);
extern BOOL CDECL_ENTRY oss_serializeGlobalAccess(struct ossGlobal *, struct globalInfo *,
				  struct globalInfo **);
#endif /* _WIN32 */

extern void *DLL_ENTRY _oss_enc_getmem(struct ossGlobal *g);
extern void *DLL_ENTRY _oss_dec_getmem(struct ossGlobal *g, long _size);
extern void *DLL_ENTRY _oss_dec_getmem_internal(struct ossGlobal *g, long size);

extern void *DLL_ENTRY _oss_dec_getfixmem(struct ossGlobal *g, size_t size);
#define _oss_dec_const_alloc(g,s) _oss_dec_getfixmem((g),(s)+_oss_mem_align(s))
#define _oss_dec_const_init_alloc(g,s) memset(_oss_dec_getfixmem((g),(s)+_oss_mem_align(s)),0,(s)+_oss_mem_align(s))

void *DLL_ENTRY _oss_dec_gettempmem( OssGlobal *g, size_t size );
void DLL_ENTRY _oss_dec_freetempmem( OssGlobal *g, void *ptr );
extern void *DLL_ENTRY _oss_dec_realloctempmem(struct ossGlobal *g, void *p,
					size_t old_size, size_t size);
extern void  DLL_ENTRY _oss_dec_free(struct ossGlobal *g, void *p);
extern void  DLL_ENTRY _oss_enc_push(struct ossGlobal *g,void *_p);
extern void *DLL_ENTRY _oss_enc_pop(struct ossGlobal *g);
extern void  DLL_ENTRY _oss_check_nullterm_time(struct ossGlobal *g, char *value, short kind);
extern int   DLL_ENTRY _oss_check_oid_iri(struct ossGlobal *g, char *value, unsigned int length, unsigned int flags);
extern int   DLL_ENTRY _oss_format_new_time(OssGlobal *g, char *value, char *dest);
extern int   DLL_ENTRY _oss_canonicalCheckTime(OssGlobal *g, char *str);
extern void **DLL_ENTRY _oss_load_enc_stack(struct ossGlobal *g, OSS_UINT32 *sp);
extern void DLL_ENTRY _oss_save_enc_stack(struct ossGlobal *g, OSS_UINT32 sp);
extern void **DLL_ENTRY _oss_increment_enc_stack(struct ossGlobal *g);
extern void **DLL_ENTRY _oss_decrement_enc_stack(struct ossGlobal *g);
extern void  DLL_ENTRY _oss_freeMem(struct ossGlobal *g, 
	void (CDECL_ENTRY_FPTR *freep)(void *, void *));
extern void  DLL_ENTRY _oss_freetempMem(struct ossGlobal *g);
extern void  DLL_ENTRY _oss_releaseMem(struct ossGlobal *g);
extern void  DLL_ENTRY _ossFreeEncMemory(struct ossGlobal *world);
extern void  DLL_ENTRY _ossSetOutMemQueue(struct ossGlobal *world, long *outlen, char **outbuf, unsigned flags);
extern struct ossGlobal *  DLL_ENTRY _oss_epop_global(struct ossGlobal *world);
extern void DLL_ENTRY  _oss_set_outmem_d(struct ossGlobal *g, long _final_max_len,
					long *_totalsize, char **_outbuf);
extern void DLL_ENTRY  _oss_set_outmem_i(struct ossGlobal *g,long _final_max_len,
					long *_totalsize,char **_outbuf);
extern void DLL_ENTRY  _oss_set_outmem_p(struct ossGlobal *g,
					long *_totalsize,char **_outbuf);
extern void DLL_ENTRY  _oss_set_outmem_pb(struct ossGlobal *g,
			long *_totalsize, char **_outbuf, unsigned flags);
extern void CDECL_ENTRY _oss_hdl_signal(int _signal);
extern void DLL_ENTRY _oss_free_creal(struct ossGlobal *g, char *p);
extern int  DLL_ENTRY ossMinit(struct ossGlobal *g);
extern void DLL_ENTRY _oss_beginBlock(struct ossGlobal *g, long count,
    char **pos, long *max_len);
extern void DLL_ENTRY _oss_nextItem(struct ossGlobal *g, long *max_len);
extern void DLL_ENTRY _oss_endBlock(struct ossGlobal *g, char **pos, long *max_len,
    unsigned char ct);
extern void DLL_ENTRY _oss_freeGlobals(struct ossGlobal *g, ossBoolean decoding);
extern void DLL_ENTRY _oss_tstk_add_block( OssGlobal *g, size_t size );
extern void DLL_ENTRY _oss_tstk_free_blocks( OssGlobal *g, void *ptr );

/* The error routines */
extern void DLL_ENTRY _oss_enc_error( struct ossGlobal *g,
	enum _err_index error_code, long data );
void DLL_ENTRY _oss_enc_llerror( struct ossGlobal *g,
	enum _err_index error_code, LONG_LONG data );
extern void DLL_ENTRY _oss_toed_error( struct ossGlobal *g,
	enum _err_index error_code, const char *data );
extern void DLL_ENTRY _oss_toed_real_error( struct ossGlobal *g,
        enum _err_index error_code, double data );
extern void DLL_ENTRY _oss_toed_api_error( struct ossGlobal *g,
	enum _err_index error_code, long data );
#define _oss_dec_error _oss_enc_error
#define _oss_dec_llerror _oss_enc_llerror
extern void DLL_ENTRY _oss_unbnd_error( struct ossGlobal *g, 
		enum _err_index error_code, void *value, size_t length );

/* called to perform limited check for default value */
extern ossBoolean DLL_ENTRY _oss_not_dflt_ia(struct ossGlobal *g,
    void *data, void *dflt, long totalsize, unsigned int offset,
    long max_length, int kind);
extern void DLL_ENTRY _oss_chk_enum(struct ossGlobal *g, long data,
	 struct _enum_data *enums);
extern void DLL_ENTRY _oss_chk_uenum(struct ossGlobal *g, unsigned long data,
	 struct _enum_data *enums);

extern void DLL_ENTRY _oss_chk_pac( struct ossGlobal *g,
    char *value, unsigned long length,
    const struct st_char_data *ppa );
extern void DLL_ENTRY _oss_chk_pac2( struct ossGlobal *g,
    unsigned short *value, unsigned long length,
    const struct st_wide_char_data *ppa );
extern void DLL_ENTRY _oss_chk_pac4( struct ossGlobal *g,
    OSS_INT32 *value, unsigned long length,
    const struct st_wide_char_data *ppa );

extern void DLL_ENTRY _oss_prt_bin(struct ossGlobal *world, char *before,
    unsigned char *s, long l, char *after);
extern void DLL_ENTRY _oss_prt_bit(struct ossGlobal *g, void *data,
    unsigned long length);
extern void DLL_ENTRY _oss_prt_char(struct ossGlobal *g, char *data,
    unsigned long length);
extern void DLL_ENTRY _oss_prt_creal(struct ossGlobal *g, char *data);
extern void DLL_ENTRY _oss_prt_gentime(struct ossGlobal *world,
    GeneralizedTime *gt);
extern void DLL_ENTRY _oss_prt_hex(struct ossGlobal *world, const char *before,
    unsigned char *s, long l, const char *after);
extern void DLL_ENTRY _oss_prt_nchar(struct ossGlobal *g, char *data);
extern void DLL_ENTRY _oss_prt_oct(struct ossGlobal *g, void *data,
    unsigned long length);
extern void DLL_ENTRY _oss_prt_opentype(struct ossGlobal *world,
    OpenType *data);
extern void DLL_ENTRY _oss_prt_new_opentype(struct ossGlobal *world,
    int pduNum, void *decoded, OssBuf *data);
extern void DLL_ENTRY _oss_prt_pbit(struct ossGlobal *g, void *data,
    unsigned long totalsize, unsigned long max_length);
extern void DLL_ENTRY _oss_prt_real(struct ossGlobal *g, double d);
extern void DLL_ENTRY _oss_prt_dreal(struct ossGlobal *g, double d);
extern void DLL_ENTRY _oss_prt_utctime(struct ossGlobal *world,
    UTCTime *ut);
extern void DLL_ENTRY _oss_indent(struct ossGlobal *g, int change);
extern void DLL_ENTRY _oss_prt_mbchar(struct ossGlobal *world,
     unsigned char *s, long l, unsigned short width);
extern void DLL_ENTRY _oss_prt_enum(struct ossGlobal *_g, ULONG_LONG _data_ptr,
     struct _string_data const *sd, int len);
extern char* DLL_ENTRY _oss_getdisp_bin(struct ossGlobal *world, char *before,
    unsigned char *s, long l, char *after);
extern char* DLL_ENTRY _oss_getdisp_bit(struct ossGlobal *g, void *data,
    unsigned long length);
extern char* DLL_ENTRY _oss_getdisp_char(struct ossGlobal *g, char *data,
    unsigned long length);
extern char* DLL_ENTRY _oss_getdisp_creal(struct ossGlobal *g, char *data);
extern char* DLL_ENTRY _oss_getdisp_gentime(struct ossGlobal *world,
    GeneralizedTime *gt);
extern char* DLL_ENTRY _oss_getdisp_hex(struct ossGlobal *world,
    const char *before, unsigned char *s, long l, const char *after);
extern char* DLL_ENTRY _oss_getdisp_nchar(struct ossGlobal *g, char *data);
extern char* DLL_ENTRY _oss_getdisp_oct(struct ossGlobal *g, void *data,
    unsigned long length);
extern char* DLL_ENTRY _oss_getdisp_pbit(struct ossGlobal *g, void *data,
    unsigned long totalsize, unsigned long max_length);
extern char* DLL_ENTRY _oss_getdisp_real(struct ossGlobal *g, double d);
extern char* DLL_ENTRY _oss_getdisp_dreal(struct ossGlobal *g, double d);
extern char* DLL_ENTRY _oss_getdisp_utctime(struct ossGlobal *world,
    UTCTime *ut);
extern char* DLL_ENTRY _oss_getdisp_mbchar(struct ossGlobal *world,
     unsigned char *s, long l, unsigned short width);
extern char* DLL_ENTRY _oss_getdisp_int(struct ossGlobal *world,
     LONG_LONG l);
extern char* DLL_ENTRY _oss_getdisp_uint(struct ossGlobal *world,
     ULONG_LONG l);
extern void DLL_ENTRY _oss_free_disp(struct ossGlobal *world,
     void *s);
extern ossBoolean DLL_ENTRY _ossCmpPrimitiveValue(struct ossGlobal *, void *,
                          void *, long, long, int);
#if defined(OSS_COMPILER_API_LEVEL)
extern int  DLL_ENTRY ossInitXObjectSetTable(struct ossGlobal *, const void * ,
				unsigned int , const void * , unsigned int,
		    int (CDECL_ENTRY_FPTR *)(struct ossGlobal *, int , void *, void *, int));
#else
extern int  DLL_ENTRY ossInitXObjectSetTable(struct ossGlobal *, const void * ,
				unsigned int , const void * , unsigned int, void *);
#endif
extern void DLL_ENTRY	 ossInitXAPIentries (struct ossGlobal *world, const void * _xent);
extern void * DLL_ENTRY	 _oss_cpy_unbnd_octet_ia (struct ossGlobal * world, void *src, void *pdst,
						 short len_sz, long item_sz, unsigned int offset);
extern void ** DLL_ENTRY _oss_cpy_dlink_obj (struct ossGlobal * world, void **psrc,
						void **pdst, long obj_sz);
extern void *  DLL_ENTRY _oss_cpy_dlink_plus (struct ossGlobal * _g, void *psrc, void *pdst,
                                              long obj_sz);
extern void ** DLL_ENTRY _oss_cpy_link_obj (struct ossGlobal * world, void **psrc,
						void **pdst, long obj_sz);
extern char * DLL_ENTRY	 _oss_cpy_char_real (struct ossGlobal * _g, char *src);
extern OpenType * DLL_ENTRY _oss_cpy_open_type (struct ossGlobal * _g, OpenType *src, OpenType *dst);
extern int  DLL_ENTRY    _oss_cmp_membits (unsigned char *data1, unsigned char *data2, long bitlen);
extern int  DLL_ENTRY    _oss_cmp_arrbits (unsigned char *data1, unsigned char *data2, long len1, long len2);
extern int  DLL_ENTRY    _oss_cmp_unbnd_octet_ia (void *data1, void *data2,
				short len_sz, long item_sz, unsigned int offset);
extern int  DLL_ENTRY    _oss_cmp_huge_int_ia (void *data1, void *data2,
				short len_sz, int sign, unsigned int offset);
extern int  DLL_ENTRY    _oss_cmp_link_obj (void **data1, void **data2, long val_sz);
extern int  DLL_ENTRY    _oss_cmp_link_objid (void *data1, void *data2, unsigned int val_sz);
extern int  DLL_ENTRY    _oss_cmp_date_time(OssGlobal *g, char *str1, char *str2);
extern void DLL_ENTRY    _ossGetDateTimeValue(OssGlobal *g, char *data, _ossDateTime *v);
extern int  DLL_ENTRY    _ossDTIntervalsRelation(_ossDTInterval *v1, _ossDTInterval *v2);
extern int  DLL_ENTRY    _ossCmpDTIntervals(_ossDTInterval *v1, _ossDTInterval *v2);
#define _ossCmpDateTimes      _ossCmpDTIntervals
#define _ossDateTimesRelation _ossDTIntervalsRelation
extern int  DLL_ENTRY _ossChkNoBasicIntervalSettings(_ossDTInterval *v,
	unsigned int settings, unsigned short recur_digits_num, char **errmsg);
extern int  DLL_ENTRY _ossChkNoBasicDateSettings(_ossDTInterval *v,
	unsigned int settings, unsigned short year_digits_num, char **errmsg);
extern int  DLL_ENTRY _ossChkNoBasicTimeSettings(_ossDTInterval *v,
	unsigned int settings, unsigned short fract_digits_num, char **errmsg);
extern int  DLL_ENTRY _ossChkRecIntervalSettings(_ossDTInterval *v,
	unsigned int settings, unsigned short recur_digits_num, char **errmsg);
extern int  DLL_ENTRY _ossChkIntervalSettings(_ossDTInterval *v,
				    unsigned int settings, char **errmsg);
extern enum _err_index DLL_ENTRY _ossChkDurationComponents(_ossDTInterval *v,
				    unsigned char present, unsigned char absent,
				    char **errmsg);
extern int  DLL_ENTRY _ossChkDateSettings(_ossDTInterval *v,
	unsigned int settings, unsigned short year_digits_num, char **errmsg);
extern int  DLL_ENTRY _ossChkTimeSettings(_ossDTInterval *v,
	unsigned int settings, unsigned short fract_digits_num, char **errmsg);
extern int  DLL_ENTRY _ossChkDateTimeSettings(_ossDTInterval *v, char **errmsg);
extern int  DLL_ENTRY _ossChkRecurrenceRange(_ossDTInterval *v,
	    unsigned short min_number, unsigned short max_number, char **errmsg);
extern int  DLL_ENTRY    _oss_cmp_open_type (struct ossGlobal * _g, OpenType *data1, OpenType *data2);
extern int  DLL_ENTRY    compare_char_real(struct ossGlobal *world, char *src1, char *src2);
extern short DLL_ENTRY _oss_cmp_str2time (char *data1, char *data2, char utc);
extern short DLL_ENTRY _oss_str2gtime(unsigned char *p, size_t *len, GeneralizedTime * tm, char utc);
extern int DLL_ENTRY oss_get_float_special_value_kind(void *vl, int vl_sizeof);

extern struct ossGlobal *DLL_ENTRY _oss_push_global(struct ossGlobal *g);
extern void *DLL_ENTRY _oss_getdispmem(struct ossGlobal *g, long size);
extern void DLL_ENTRY _oss_freedispmem(struct ossGlobal *g, void *p);
extern unsigned char DLL_ENTRY ossCharIsPermitted( const OSS_UINT32 *pat,
	OSS_UINT32 character );
extern void DLL_ENTRY _oss_free_rsf_ext(struct ossGlobal *g, void *_data);
unsigned char *DLL_ENTRY _oss_itoUTF8Char( unsigned char *value, OSS_UINT32 ch );
unsigned int DLL_ENTRY _oss_countUTF8Char( OSS_UINT32 ch );
long DLL_ENTRY _oss_count_bits(unsigned char *value, long bit_len);
long DLL_ENTRY _oss_count_chars(char *value, long length);
int DLL_ENTRY _oss_nmbit_lfit(unsigned char *value, unsigned int *plength,
				    unsigned int lb, unsigned int ub);
unsigned int DLL_ENTRY _oss_chop_zero_bits(unsigned char *value,
    unsigned int length, unsigned int lb);

extern void DLL_ENTRY _oss_check_container(OssGlobal *g, long cur_length,
			    int info, unsigned char *buf, unsigned long length);

#ifdef OSS_TOED_BER
/*****************************************************************************/
/*  TOED BER section                                                         */
/*****************************************************************************/
    /*************************************************************************/
    /*      TOED BER functions section                                       */
    /*************************************************************************/


/* Encode Routines */

extern long DLL_ENTRY _oss_encd_length(struct ossGlobal *g, _std_parms_def,
				 unsigned long _data);
extern long DLL_ENTRY _oss_encd_tag(struct ossGlobal *g, _std_parms_def,
			      unsigned short _data, ossBoolean _constructed);
long DLL_ENTRY _oss_encd_tag_length(struct ossGlobal *g, _sdstd_parms_def,
	long length, OSS_UINT32 tag);
long DLL_ENTRY _oss_encd_tag_length2(struct ossGlobal *g, _sdstd_parms_def,
	long length, OSS_UINT32 tag1, OSS_UINT32 tag2);
extern long DLL_ENTRY _oss_encd_bool(struct ossGlobal *g, _std_parms_def,
			       ossBoolean _data);
long DLL_ENTRY _oss_encd_bool_tl(struct ossGlobal *g, _sdstd_parms_def,
    OSS_UINT32 tag, ossBoolean value);
extern long DLL_ENTRY _oss_encd_int(struct ossGlobal *g, _std_parms_def,
				LONG_LONG _data);
long DLL_ENTRY _oss_encd_int_tl(struct ossGlobal *g, _sdstd_parms_def,
	long value, OSS_UINT32 tag);
long DLL_ENTRY _oss_encd_uint_tl(struct ossGlobal *g, _sdstd_parms_def,
	unsigned long value, OSS_UINT32 tag);
long DLL_ENTRY _oss_encd_llint_tl(struct ossGlobal *g, _sdstd_parms_def,
	LONG_LONG value, OSS_UINT32 tag);
long DLL_ENTRY _oss_encd_ullint_tl(struct ossGlobal *g, _sdstd_parms_def,
	ULONG_LONG value, OSS_UINT32 tag);
extern long DLL_ENTRY _oss_encd_uint(struct ossGlobal *g, _std_parms_def,
				ULONG_LONG _data);
extern long DLL_ENTRY _oss_encd_huge_int_ia(struct ossGlobal *g,
    _std_parms_def, unsigned char *value, unsigned long length);
extern long DLL_ENTRY _oss_encd_uhuge_int_ia(struct ossGlobal *g,
    _std_parms_def, unsigned char *value, unsigned long length);

extern long DLL_ENTRY _oss_encd_real(struct ossGlobal *g, _std_parms_def,
			       double _data);
extern long DLL_ENTRY _oss_encd_creal(struct ossGlobal *g, _std_parms_def,
			       char *_data);
extern long DLL_ENTRY _oss_encd_mreal_ia(struct ossGlobal *g, _std_parms_def,
    enum MixedReal_kind kind, void *data);
extern long DLL_ENTRY _oss_encd_alobjid(struct ossGlobal *g, _std_parms_def,
				  void *_data, short _array_size);
extern long DLL_ENTRY _oss_encd_asobjid(struct ossGlobal *g, _std_parms_def,
				  void *_data, short _array_size);
extern long DLL_ENTRY _oss_encd_aiobjid(struct ossGlobal *g, _std_parms_def,
				  void *_data, short _array_size);
extern long DLL_ENTRY _oss_encd_llobjid_ia(struct ossGlobal *g, _std_parms_def,
    void *data, long size_c, unsigned int offset);
extern long DLL_ENTRY _oss_encd_lsobjid(struct ossGlobal *g, _std_parms_def,
				  void *_data, long _size_c);
extern long DLL_ENTRY _oss_encd_liobjid(struct ossGlobal *g, _std_parms_def,
				  void *_data, long _size_c);
extern long DLL_ENTRY _oss_encd_ulobjid_ia(struct ossGlobal *g, _std_parms_def,
    unsigned long *value, unsigned int length, long size_c);
extern long DLL_ENTRY _oss_encd_usobjid_ia(struct ossGlobal *g, _std_parms_def,
    unsigned short *value, unsigned int length, long size_c);
extern long DLL_ENTRY _oss_encd_uiobjid_ia(struct ossGlobal *g, _std_parms_def,
    unsigned int *value, unsigned int length, long size_c);
extern long DLL_ENTRY _oss_encd_pbit(struct ossGlobal *g, _std_parms_def,
			       void *_data, long _bit_count);
extern long DLL_ENTRY _oss_encd_pbit_tl(struct ossGlobal *g, _sdstd_parms_def,
    OSS_UINT32 value, unsigned int length, OSS_UINT32 tag);
extern long DLL_ENTRY _oss_encb_pbit(struct ossGlobal *g, _std_parms_def,
			       void *_data, long _bit_count);
extern long DLL_ENTRY _oss_encb_pbit_tl(struct ossGlobal *g, _sdstd_parms_def,
    OSS_UINT32 value, unsigned int length, OSS_UINT32 tag);
extern long DLL_ENTRY _oss_encd_vbit_ia(struct ossGlobal *g, _std_parms_def,
    unsigned char *value, unsigned long length, long size_c);

long DLL_ENTRY _oss_encd_ubit_ia(struct ossGlobal *g, _std_parms_def,
    unsigned char *value, unsigned long length, long size_c);

extern long DLL_ENTRY _oss_encd_nstr(struct ossGlobal *g, _std_parms_def,
			       char *_data, long _size_c);
extern long DLL_ENTRY _oss_encd_pstr(struct ossGlobal *g, _std_parms_def,
			       char *_data, long _byte_count);
extern long DLL_ENTRY _oss_encd_voct_ia(struct ossGlobal *g, _std_parms_def,
    unsigned char *value, unsigned long length, long size_c);
extern long DLL_ENTRY _oss_encd_vstr_ia(struct ossGlobal *g, _std_parms_def,
    char *value, unsigned long length, long size_c);

extern long DLL_ENTRY _oss_encd_gtime(struct ossGlobal *g, _std_parms_def,
				GeneralizedTime*_data);
extern long DLL_ENTRY _oss_encd_utime(struct ossGlobal *g, _std_parms_def,
				UTCTime *_data);
extern long DLL_ENTRY _oss_encd_date_time(OssGlobal *g, _std_parms_def,
				char *data, int kind);
extern void DLL_ENTRY _oss_dec_date_time(OssGlobal *g, _dstd_parms_def,
				char **data, int kind);

extern long DLL_ENTRY _oss_encd_uoct_ia(struct ossGlobal *g, _std_parms_def,
    unsigned char *value, unsigned long length, long size_c);
extern long DLL_ENTRY _oss_encd_ustr_ia(struct ossGlobal *g, _std_parms_def,
    char *value, unsigned long length, long size_c);

extern long DLL_ENTRY _oss_encd_untime(struct ossGlobal *g, _std_parms_def,
				char *_data, long _size_c, short kind);

long DLL_ENTRY _oss_encd_uany(struct ossGlobal *g, _std_parms_def,
	unsigned char *value, unsigned long length);

extern long DLL_ENTRY _oss_encd_opentype(struct ossGlobal *g, _std_parms_def,
			       void *_data);
extern long DLL_ENTRY _oss_encd_defer(struct ossGlobal *g, _std_parms_def,
				void *data);
long DLL_ENTRY _oss_encd_bmpstr_ia(struct ossGlobal *g, _std_parms_def,
	unsigned short *value, unsigned long length, long size_c);

long DLL_ENTRY _oss_encd_unistr_ia(struct ossGlobal *g, _std_parms_def,
    OSS_INT32 *value, unsigned long length, long size_c);

long DLL_ENTRY _oss_encd_eobjid_ia(struct ossGlobal *g, _std_parms_def,
    unsigned char *value, unsigned int length, long size_c);
long DLL_ENTRY _oss_encd_ereloid_ia(struct ossGlobal *g, _std_parms_def,
    unsigned char *value, unsigned int length, long size_c);

extern long DLL_ENTRY _oss_encd_dubit_ia(struct ossGlobal *g,
    _std_parms_def, unsigned char *value, unsigned long length,
    long size_c, ossBoolean named_bits);

extern long DLL_ENTRY _oss_encd_dvbit_ia(struct ossGlobal *g,
    _std_parms_def, unsigned char *value, unsigned long length,
    long size_c, ossBoolean named_bits);

extern long DLL_ENTRY _oss_encd_utf8unistr_ia(struct ossGlobal *g,
    _std_parms_def, OSS_INT32 *value, unsigned long length, long size_c);

extern long DLL_ENTRY _oss_encd_utf8bmpstr_ia(struct ossGlobal *g,
    _std_parms_def, unsigned short *value, unsigned long length, long size_c);

extern long DLL_ENTRY _oss_encd_utf8unbound_ia(struct ossGlobal *g,
    _std_parms_def, unsigned char *value, unsigned long length, long size_c);

extern long DLL_ENTRY _oss_write_bytes_d(struct ossGlobal *g, _std_parms_def,
		    unsigned char *value, long num_bytes);

/* Decode Routines */
/* these return values */
extern unsigned int DLL_ENTRY _oss_dec_tag( struct ossGlobal *g,
	_sdstd_parms_def );			     
extern long DLL_ENTRY _oss_dec_length(struct ossGlobal *g, _sdstd_parms_def);
extern long DLL_ENTRY _oss_dec_tag_length(struct ossGlobal *g,
	_sdstd_parms_def, unsigned long tag_encoding);

extern ossBoolean DLL_ENTRY _oss_dec_bool(struct ossGlobal *g, _dstd_parms_def);
extern LONG_LONG DLL_ENTRY _oss_dec_llint(struct ossGlobal *g, _dstd_parms_def);
extern long DLL_ENTRY _oss_dec_lint(struct ossGlobal *g, _dstd_parms_def);
extern int  DLL_ENTRY _oss_dec_iint(struct ossGlobal *g, _dstd_parms_def);
extern short DLL_ENTRY _oss_dec_sint(struct ossGlobal *g, _dstd_parms_def);

extern unsigned long DLL_ENTRY _oss_dec_hint_ia(struct ossGlobal *g,
	_dstd_parms_def, void *data);

extern ULONG_LONG DLL_ENTRY _oss_dec_ullint(struct ossGlobal *g, _dstd_parms_def);
extern unsigned long DLL_ENTRY _oss_dec_ulint(struct ossGlobal *g, _dstd_parms_def);
extern unsigned int DLL_ENTRY _oss_dec_uiint(struct ossGlobal *g, _dstd_parms_def);
extern unsigned short DLL_ENTRY _oss_dec_usint(struct ossGlobal *g, _dstd_parms_def);

/* The code for this one is so huge that it would be criminal to
 * repeat it three times.  Caller should cast the returned value
 * to what she wants.
 */
extern void DLL_ENTRY _oss_dec_real(struct ossGlobal *g, _dstd_parms_def,
				double *data);
extern void DLL_ENTRY _oss_dec_freal(struct ossGlobal *g, _dstd_parms_def,
				float *data);
extern void DLL_ENTRY _oss_dec_creal(struct ossGlobal *g, _dstd_parms_def,
				  char **_data);
extern enum MixedReal_kind DLL_ENTRY _oss_dec_mreal_ia
	(struct ossGlobal *g, _dstd_parms_def,
		void *data);

/* Two versions of these functions.  If the type has the pointer
 * directive, then its size is not fixed--the function will allocate
 * the memory.  Otherwise the caller allocates the memory.  (Actually,
 * the type will probably be enclosed in another type, and therefore
 * the memory has already been allocated.)
 */
extern void * DLL_ENTRY _oss_dec_alobjid_ptr_ia(struct ossGlobal *g,
    _dstd_parms_def,
    short size_c, unsigned int offset);

extern unsigned short DLL_ENTRY _oss_dec_alobjid_ia(struct ossGlobal *g,
    _dstd_parms_def, unsigned long *value, short size_c);

extern void * DLL_ENTRY _oss_dec_aiobjid_ptr_ia(struct ossGlobal *g,
    _dstd_parms_def,
    short size_c, unsigned int offset);

extern unsigned short DLL_ENTRY _oss_dec_aiobjid_ia(struct ossGlobal *g,
    _dstd_parms_def, unsigned int *value, short size_c);

extern void * DLL_ENTRY _oss_dec_asobjid_ptr_ia(struct ossGlobal *g,
    _dstd_parms_def,
    short size_c, unsigned int offset);

extern unsigned short DLL_ENTRY _oss_dec_asobjid_ia(struct ossGlobal *g,
    _dstd_parms_def, unsigned short *value, short size_c);

/* These allocate all their own memory.  */
extern void * DLL_ENTRY _oss_dec_llobjid_ia(struct ossGlobal *g,
    _dstd_parms_def, long size_c, unsigned int offset);
extern void DLL_ENTRY _oss_dec_liobjid(struct ossGlobal *g, _dstd_parms_def,
				 void **_data, long _size_c);
extern void DLL_ENTRY _oss_dec_lsobjid(struct ossGlobal *g, _dstd_parms_def,
				 void **_data, long _size_c);

/*  These are passed the structure containing the count, but allocate
  *  space for the data itself. */
extern unsigned short DLL_ENTRY _oss_dec_ulobjid_ia(struct ossGlobal *g,
    _dstd_parms_def, void *data, short size_c);
extern unsigned short DLL_ENTRY _oss_dec_uiobjid_ia(struct ossGlobal *g,
    _dstd_parms_def, void *data, short size_c);
extern unsigned short DLL_ENTRY _oss_dec_usobjid_ia(struct ossGlobal *g,
    _dstd_parms_def, void *data, short size_c);
/* Caller allocates memory for this one.  Call for both e_pad & e_big_pad. */
extern void DLL_ENTRY _oss_dec_pbit(struct ossGlobal *g, _dstd_parms_def,
			      void *_data, long _bit_count,
				ossBoolean _named_bits);

/* See comment before dec_ulobjid. */
extern unsigned long DLL_ENTRY _oss_dec_ubit_ia(struct ossGlobal *g,
	_dstd_parms_def, void *data, long size_c, unsigned int flags);

/* Two versions of this one too.  */
extern unsigned long DLL_ENTRY _oss_dec_vbit_ptr_ia(struct ossGlobal *g,
	_dstd_parms_def,
	void *data, unsigned int offset,
	long size_c);

extern unsigned long DLL_ENTRY _oss_dec_vbit_ptr_nz(struct ossGlobal *g,
	_dstd_parms_def,
	void *data, unsigned int offset,
	long size_c, unsigned int flags);

extern unsigned long DLL_ENTRY _oss_dec_vbit_ia(struct ossGlobal *g,
	_dstd_parms_def, void *data,
	long size_c);

extern unsigned long DLL_ENTRY _oss_dec_vbit_nz(struct ossGlobal *g,
	_dstd_parms_def, void *data,
	long size_c, unsigned int flags);


extern void DLL_ENTRY _oss_dec_nstr_ptr(struct ossGlobal *g, _dstd_parms_def,
				  char **_data, long _size_c);
extern void DLL_ENTRY _oss_dec_nstr(struct ossGlobal *g, _dstd_parms_def,
			      char *_data, long _size_c);

extern void DLL_ENTRY _oss_dec_pstr(struct ossGlobal *g, _dstd_parms_def,
			      char *_data, long _byte_count);

extern unsigned long DLL_ENTRY _oss_dec_ustr_ia(struct ossGlobal *g, _dstd_parms_def,
		    void *data, long size_c);

extern unsigned long DLL_ENTRY _oss_dec_vstr_ptr_ia(struct ossGlobal *g,
	_dstd_parms_def,
	void *data, unsigned int offset,
	long size_c);

extern unsigned long DLL_ENTRY _oss_dec_vstr_ia(struct ossGlobal *g,
	_dstd_parms_def, void *data,
	long size_c);

extern unsigned long DLL_ENTRY _oss_dec_uoct_ia(struct ossGlobal *g, _dstd_parms_def,
		    void *data, long size_c);

extern unsigned long DLL_ENTRY _oss_dec_voct_ptr_ia(struct ossGlobal *g,
	_dstd_parms_def,
	void *data, unsigned int offset,
	long size_c);

extern unsigned long DLL_ENTRY _oss_dec_voct_ia(struct ossGlobal *g,
	_dstd_parms_def, void *data,
	long size_c);

extern void DLL_ENTRY_FDEF _oss_dec_fixed_oct(struct ossGlobal *g,
	_dstd_parms_def, void *data, long size_c);

extern void DLL_ENTRY _oss_dec_gtime(struct ossGlobal *g, _dstd_parms_def,
			       GeneralizedTime *_data);
extern void DLL_ENTRY _oss_dec_utime(struct ossGlobal *g, _dstd_parms_def,
			       UTCTime *_data);
extern void DLL_ENTRY _oss_dec_untime(struct ossGlobal *g, _dstd_parms_def,
				  char **data,
				  long size_c, short kind);
extern unsigned long DLL_ENTRY _oss_dec_uany(struct ossGlobal *g, _dstd_parms_def,
			      void *data);

extern void DLL_ENTRY _oss_dec_opentype(struct ossGlobal *g, _dstd_parms_def,
			      void *_data);

extern void DLL_ENTRY _oss_dec_new_opentype(struct ossGlobal *g,
		    _dstd_parms_def, OssBuf *encoded);

extern void DLL_ENTRY _oss_dec_defer(struct ossGlobal *g, _dstd_parms_def,
		    void *data,
		    unsigned short tag, ossBoolean constructed);

extern unsigned long DLL_ENTRY _oss_dec_bmpstr_ia(struct ossGlobal *g,
	_dstd_parms_def, void *data,
	long size_c);

extern unsigned long DLL_ENTRY _oss_dec_unistr_ia(struct ossGlobal *g, _dstd_parms_def,
		    void *data, long size_c);

extern unsigned int DLL_ENTRY _oss_dec_eobjid_ia(struct ossGlobal *g, _dstd_parms_def,
			void *data, long size_c);
extern unsigned int DLL_ENTRY _oss_dec_ereloid_ia(struct ossGlobal *g, _dstd_parms_def,
			void *data, long size_c);

extern unsigned long DLL_ENTRY _oss_dec_utf8bmpstr_ia(struct ossGlobal *g, _dstd_parms_def,
		    void *data, long size_c);

extern void DLL_ENTRY _oss_dec_utf8unbound(struct ossGlobal *g, _dstd_parms_def,
		    void *data,
		    char lengthsize,
		    long size_c);

extern unsigned long DLL_ENTRY _oss_dec_utf8unbound_ia(struct ossGlobal *g, _dstd_parms_def,
		    void *data,
		    long size_c);

extern unsigned long DLL_ENTRY _oss_dec_utf8unistr_ia(struct ossGlobal *g, _dstd_parms_def,
		    void *data, long size_c);

/* Other functions */

/* called to decode unknown extension additions in relaysafe-mode */
extern void DLL_ENTRY _oss_dec_rsf_ext(struct ossGlobal *g, _dstd_parms_def,
    void **_data, char **rsf_pos, long *rsf_len,
    unsigned int *count);

/* called to count the items for set of or sequence of. */
extern long DLL_ENTRY _oss_count_setof_items(struct ossGlobal *g, _dstd_parms_def);

/* called to skip past items for the EXTENSIBLE directive */
extern void DLL_ENTRY _oss_skip_past_item(struct ossGlobal *g, _dstd_parms_def);

    /*************************************************************************/
    /*      TOED BER DLL table defines section                               */
    /*************************************************************************/

#endif /* OSS_TOED_BER */

#ifdef OSS_TOED_PER
/*****************************************************************************/
/*  TOED PER section                                                         */
/*****************************************************************************/

#define Aligned   1
#define Unaligned 0

    /*************************************************************************/
    /*      TOED PER functions section                                       */
    /*************************************************************************/

extern void DLL_ENTRY _oss_append(struct ossGlobal *g, unsigned char *field, unsigned long length,
			int align);

extern void DLL_ENTRY _oss_append_1bit_unaligned
	(struct ossGlobal *g, unsigned char field);

extern void DLL_ENTRY _oss_append_2bit_unaligned
	(struct ossGlobal *g, unsigned char field);

extern void DLL_ENTRY _oss_append_3bit_unaligned
	(struct ossGlobal *g, unsigned char field);

extern void DLL_ENTRY _oss_append_4bit_unaligned
	(struct ossGlobal *g, unsigned char field);

extern void DLL_ENTRY _oss_append_5bit_unaligned
	(struct ossGlobal *g, unsigned char field);

extern void DLL_ENTRY _oss_append_6bit_unaligned
	(struct ossGlobal *g, unsigned char field);

extern void DLL_ENTRY _oss_append_7bit_unaligned
	(struct ossGlobal *g, unsigned char field);

extern void DLL_ENTRY _oss_append_8bit_unaligned
	(struct ossGlobal *g, unsigned char field);

extern void DLL_ENTRY _oss_penc_unconstr_int(struct ossGlobal *g,
	    LONG_LONG value);

extern void DLL_ENTRY _oss_penc_semicon_int(struct ossGlobal *g,
	    LONG_LONG value, LONG_LONG lower_bound);

extern void DLL_ENTRY _oss_penc_semicon_uint(struct ossGlobal *g,
	    ULONG_LONG value, ULONG_LONG lower_bound);

extern void DLL_ENTRY _oss_penc_nonneg_int(struct ossGlobal *g,
	    ULONG_LONG value, ULONG_LONG range);

extern void DLL_ENTRY _oss_penc_nonneg_1int
	(struct ossGlobal *g, unsigned int field);

extern void DLL_ENTRY _oss_penc_nonneg_2int
	(struct ossGlobal *g, unsigned int field);

extern void DLL_ENTRY _oss_penc_nonneg_3int
	(struct ossGlobal *g, unsigned int field);

extern void DLL_ENTRY _oss_penc_nonneg_4int
	(struct ossGlobal *g, unsigned int field);

extern void DLL_ENTRY _oss_penc_nonneg_5int
	(struct ossGlobal *g, unsigned int field);

extern void DLL_ENTRY _oss_penc_nonneg_6int
	(struct ossGlobal *g, unsigned int field);

extern void DLL_ENTRY _oss_penc_nonneg_7int
	(struct ossGlobal *g, unsigned int field);

extern void DLL_ENTRY _oss_penc_nonneg_8int
	(struct ossGlobal *g, unsigned int field);

extern void DLL_ENTRY _oss_penc_indeflen_int(struct ossGlobal *g,
	    ULONG_LONG value, ULONG_LONG range);

extern void DLL_ENTRY _oss_penc_small_int(struct ossGlobal *g, ULONG_LONG value);

extern void DLL_ENTRY _oss_penc_enum(struct ossGlobal *g, long data,
	 struct _enum_data *root,
	 struct _enum_data *extension);

extern void DLL_ENTRY _oss_penc_uenum(struct ossGlobal *g, unsigned long data,
	 struct _enum_data *root,
	 struct _enum_data *extension);

extern void DLL_ENTRY _oss_penc_real(struct ossGlobal *g, double value);
extern void DLL_ENTRY _oss_penc_creal(struct ossGlobal *g, char *value);
extern void DLL_ENTRY _oss_penc_mreal_ia(struct ossGlobal *g,
    enum MixedReal_kind kind, void *data);

extern void DLL_ENTRY _oss_penc_constr_bpbit(struct ossGlobal *g, void *value,
	ULONG_LONG lb, ULONG_LONG ub, ossBoolean NamedBits,
	ossBoolean Ext);

extern void DLL_ENTRY _oss_penc_constr_bpbit_l(struct ossGlobal *g,
    void *data, unsigned long lb, unsigned long ub,
    ossBoolean NamedBits, ossBoolean Ext);

extern void DLL_ENTRY _oss_penc_constr_pbit(struct ossGlobal *g, ULONG_LONG value,
	ULONG_LONG size, ULONG_LONG lb, ULONG_LONG ub, ossBoolean NamedBits,
	ossBoolean Ext);

extern void DLL_ENTRY _oss_penc_constr_pbit_l(struct ossGlobal *g,
    unsigned long value, unsigned long size, unsigned long lb,
    unsigned long ub, ossBoolean NamedBits, ossBoolean Ext);

extern void DLL_ENTRY _oss_penc_unconstr_pbit(struct ossGlobal *g, ULONG_LONG value,
	ULONG_LONG length, ULONG_LONG size, ossBoolean NamedBits);

extern unsigned long DLL_ENTRY _oss_penc_length(struct ossGlobal *g, ULONG_LONG length,
		  ULONG_LONG lb, ULONG_LONG ub, ossBoolean ext);

extern void DLL_ENTRY _oss_penc_unconstr_pbit_l(struct ossGlobal *g,
    unsigned long value, unsigned long length, unsigned long size,
    ossBoolean NamedBits);

extern void DLL_ENTRY _oss_penc_unconstr_bit_l(struct ossGlobal *g,
    unsigned char *value, unsigned long length, ossBoolean NamedBits);

extern unsigned long DLL_ENTRY _oss_penc_length_l(struct ossGlobal *g,
    unsigned long length, unsigned long lb, unsigned long ub, ossBoolean ext);

void DLL_ENTRY _oss_penc_lrang(OssGlobal *g,
	   unsigned int length, unsigned int lb, unsigned int ub);

unsigned int DLL_ENTRY _oss_penc_lfrag(OssGlobal *g,
				unsigned int length);

ULONG_LONG DLL_ENTRY _oss_penc_lfrag_ll(OssGlobal *g,
				ULONG_LONG length);

void DLL_ENTRY _oss_penc_fix_bit(OssGlobal *g, unsigned char *value,
					 unsigned int ub);

void DLL_ENTRY _oss_penc_uncon_oct(OssGlobal *g, unsigned char *value,
			unsigned int length);

void DLL_ENTRY _oss_penc_uncon_oct_ll(OssGlobal *g, unsigned char *value,
			ULONG_LONG length);

int DLL_ENTRY _oss_nmbit_lfit_ll(unsigned char *value,
	ULONG_LONG *plength,
	ULONG_LONG lb, ULONG_LONG ub);

ULONG_LONG DLL_ENTRY _oss_chop_zero_bits_ll(unsigned char *value,
    ULONG_LONG length, ULONG_LONG lb);

void DLL_ENTRY _oss_penc_uncon_bit(OssGlobal *g, unsigned char *value,
			unsigned int length);

void DLL_ENTRY _oss_penc_uncon_bit_ll(OssGlobal *g, unsigned char *value,
			ULONG_LONG length);

extern void DLL_ENTRY _oss_penc_constr_bit_l(struct ossGlobal *g,
    unsigned char *value, unsigned long length, unsigned long lb,
    unsigned long ub, ossBoolean NamedBits, unsigned long new_length);

extern unsigned long DLL_ENTRY _oss_pdec_small_len(struct ossGlobal *g);

extern void DLL_ENTRY _oss_penc_small_len_l(struct ossGlobal *g,
    unsigned long length);

extern void DLL_ENTRY _oss_penc_unconstr_oct_l(struct ossGlobal *g,
    unsigned char *value, unsigned long length);

void DLL_ENTRY _oss_append_8bit_aligned(struct ossGlobal *g,
    unsigned int field);
void DLL_ENTRY _oss_penc_int16_aligned(struct ossGlobal *g, unsigned int value);
extern void          DLL_ENTRY _oss_penc_small_len(struct ossGlobal *g,
							ULONG_LONG length);
extern void DLL_ENTRY _oss_penc_unconstr_oct(struct ossGlobal *g, unsigned char *value,
	 ULONG_LONG length);

extern void DLL_ENTRY _oss_penc_constr_oct(struct ossGlobal *g, unsigned char *value,
	 ULONG_LONG length, ULONG_LONG lb, ULONG_LONG ub);
extern void DLL_ENTRY _oss_fast_pop_global(struct ossGlobal *g);
extern void DLL_ENTRY _oss_fast_push_global(struct ossGlobal *g);
extern void DLL_ENTRY _oss_end_otype_or_ext(struct ossGlobal *g,
					struct ossExtStackElement *st);
extern void DLL_ENTRY _oss_begin_otype_or_ext(struct ossGlobal *g,
					struct ossExtStackElement *st);

extern void DLL_ENTRY _oss_penc_objids(struct ossGlobal *g, unsigned short *value,
   unsigned long length);
extern void DLL_ENTRY _oss_penc_objidi(struct ossGlobal *g, unsigned int *value,
   unsigned long length);
extern void DLL_ENTRY _oss_penc_objidl(struct ossGlobal *g, unsigned long *value,
   unsigned long length);
extern void DLL_ENTRY _oss_penc_link_objids(struct ossGlobal *g, void *value);
extern void DLL_ENTRY _oss_penc_link_objidi(struct ossGlobal *g, void *value);
extern void DLL_ENTRY _oss_penc_link_objidl_ia(struct ossGlobal *g,
    void *value, unsigned int offset);

extern void DLL_ENTRY _oss_penc_opentype(struct ossGlobal *g, void *value);
extern void DLL_ENTRY _oss_penc_nkmstr(struct ossGlobal *g, char *value, ULONG_LONG length);
extern void DLL_ENTRY _oss_penc_gtime(struct ossGlobal *g, GeneralizedTime *time);
extern void DLL_ENTRY _oss_penc_utime(struct ossGlobal *g, UTCTime *time);

extern void DLL_ENTRY _oss_penc_nkmstr_l(struct ossGlobal *g, char *value,
    unsigned long length);

extern void DLL_ENTRY _oss_penc_kmstr( struct ossGlobal *g,
    char *value,
    unsigned long length, const struct st_PER_String_Data *psd,
    unsigned int ext );
extern void DLL_ENTRY _oss_penc_bmpstr( struct ossGlobal *g,
    unsigned short *value,
    unsigned long length, const struct st_PER_String_Data *psd,
    unsigned int ext );
extern void DLL_ENTRY _oss_penc_unistr( struct ossGlobal *g,
    OSS_INT32 *value,
    unsigned long length, const struct st_PER_String_Data *psd,
    unsigned int ext );

extern void DLL_ENTRY _oss_penc_uany(struct ossGlobal *g, void *data );

extern void DLL_ENTRY _oss_penc_unconstr_huge_ia(struct ossGlobal *g,
    unsigned char *value,
    unsigned long length);

extern void DLL_ENTRY _oss_penc_semicon_huge_ia(struct ossGlobal *g,
    unsigned char *value,
    unsigned long length, long lb);

extern void DLL_ENTRY _oss_penc_eobjid_ia(struct ossGlobal *g,
    unsigned char *value, unsigned int length, long size_c);
extern void DLL_ENTRY _oss_penc_ereloid_ia(struct ossGlobal *g,
    unsigned char *value, unsigned int length, long size_c);

extern void DLL_ENTRY _oss_penc_utf8bmpstr(struct ossGlobal *g, unsigned short *value, ULONG_LONG length);
extern void DLL_ENTRY _oss_penc_utf8unistr(struct ossGlobal *g, OSS_INT32 *value, ULONG_LONG length);

extern void DLL_ENTRY _oss_penc_utf8bmpstr_l(struct ossGlobal *g,
    unsigned short *value, unsigned long length);
extern void DLL_ENTRY _oss_penc_utf8unistr_l(struct ossGlobal *g,
    OSS_INT32 *value, unsigned long length);
extern void DLL_ENTRY _oss_penc_indeflen_int_l(struct ossGlobal *g,
	    unsigned long value, unsigned long range);
extern void DLL_ENTRY _oss_penc_nonneg_int_l(struct ossGlobal *g,
	    unsigned long value, unsigned int range);
extern void DLL_ENTRY _oss_penc_semicon_int_l(struct ossGlobal *g,
	    long value, long lower_bound);
extern void DLL_ENTRY _oss_penc_small_int_l(struct ossGlobal *g, unsigned long value);
extern void DLL_ENTRY _oss_penc_unconstr_int_l(struct ossGlobal *g,
	    long value);
extern void DLL_ENTRY _oss_penc_constr_oct_l(struct ossGlobal *g, unsigned char *value,
	    unsigned long length, unsigned long lb, unsigned long ub);
extern void DLL_ENTRY _oss_penc_semicon_uint_l(struct ossGlobal *g,
	    unsigned long value, unsigned long lower_bound);

#define _oss_pe_t_utc(g, data, in) \
   ((*(data = in) == 'Z') ? data + 1 : (_oss_enc_error(g, _bad_time, 0L), data))
extern char * DLL_ENTRY _oss_pe_t_any_century(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pe_t_day_of_month(OssGlobal *g, char *data);
#define _oss_pe_t_any_date(g, data) \
	_oss_pe_t_day_of_month(g, _oss_pe_t_any_year_month(g, data))
extern char * DLL_ENTRY _oss_pe_t_any_year(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pe_t_day_of_year(OssGlobal *g, char *data);
#define _oss_pe_t_any_year_day(g, data) \
	_oss_pe_t_day_of_year(g, _oss_pe_t_any_year(g, data))
extern char * DLL_ENTRY _oss_pe_t_month(OssGlobal *g, char *data);
#define _oss_pe_t_any_year_month(g, data) \
	_oss_pe_t_month(g, _oss_pe_t_any_year(g, data))
extern char * DLL_ENTRY _oss_pe_t_week(OssGlobal *g, char *data);
#define _oss_pe_t_any_year_week(g, data) \
	_oss_pe_t_week(g, _oss_pe_t_any_year(g, data))
extern char * DLL_ENTRY _oss_pe_t_day_of_week(OssGlobal *g, char *data);
#define _oss_pe_t_any_year_week_day(g, data) \
	_oss_pe_t_day_of_week(g, _oss_pe_t_any_year_week(g, data))
extern char * DLL_ENTRY _oss_pe_t_century(OssGlobal *g, char *data);
#define _oss_pe_t_date(g, data) \
	_oss_pe_t_day_of_month(g, _oss_pe_t_year_month(g, data))
extern char * DLL_ENTRY _oss_pe_t_duration_interval(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pe_t_hours(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pe_t_time_diff(OssGlobal *g, char *data);
#define _oss_pe_t_hours_diff(g, data) \
	_oss_pe_t_time_diff(g, _oss_pe_t_hours(g, data))
#define _oss_pe_t_hours_diff_fraction(g, data, accuracy) \
	_oss_pe_t_time_diff(g, _oss_pe_t_hours_fraction(g, data, accuracy))
extern char * DLL_ENTRY _oss_pe_t_time_fraction(OssGlobal *g, char *data,
				unsigned int accuracy);
#define _oss_pe_t_hours_fraction(g, data, accuracy) \
	_oss_pe_t_time_fraction(g, _oss_pe_t_hours(g, data), accuracy)
#define _oss_pe_t_hours_utc(g, data) \
	_oss_pe_t_utc(g, data, _oss_pe_t_hours(g, data))
#define _oss_pe_t_hours_utc_fraction(g, data, accuracy) \
	_oss_pe_t_utc(g, data, _oss_pe_t_hours_fraction(g, data, accuracy))
extern char * DLL_ENTRY _oss_pe_t_mins_or_secs(OssGlobal *g, char *data,
				unsigned int bound);
#define _oss_pe_t_minutes(g, data) \
	_oss_pe_t_mins_or_secs(g, _oss_pe_t_hours(g, data), 59)
#define _oss_pe_t_minutes_diff(g, data) \
	_oss_pe_t_time_diff(g, _oss_pe_t_minutes(g, data))
#define _oss_pe_t_minutes_diff_fraction(g, data, accuracy) \
	_oss_pe_t_time_diff(g, _oss_pe_t_minutes_fraction(g, data, accuracy))
#define _oss_pe_t_minutes_fraction(g, data, accuracy) \
	_oss_pe_t_time_fraction(g, _oss_pe_t_minutes(g, data), accuracy)
#define _oss_pe_t_minutes_utc(g, data) \
	_oss_pe_t_utc(g, data, _oss_pe_t_minutes(g, data))
#define _oss_pe_t_minutes_utc_fraction(g, data, accuracy) \
	_oss_pe_t_utc(g, data, _oss_pe_t_minutes_fraction(g, data, accuracy))
extern char * DLL_ENTRY _oss_pe_t_mixed(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pe_t_recurrence(OssGlobal *g, char *data);
#define _oss_pe_t_daytime(g, data) \
	_oss_pe_t_mins_or_secs(g, _oss_pe_t_minutes(g, data), 60)
#define _oss_pe_t_daytime_diff(g, data) \
	_oss_pe_t_time_diff(g, _oss_pe_t_daytime(g, data))
#define _oss_pe_t_daytime_diff_fraction(g, data, accuracy) \
	_oss_pe_t_time_diff(g, _oss_pe_t_daytime_fraction(g, data, accuracy))
#define _oss_pe_t_daytime_fraction(g, data, accuracy) \
	_oss_pe_t_time_fraction(g, _oss_pe_t_daytime(g, data), accuracy)
#define _oss_pe_t_daytime_utc(g, data) \
	_oss_pe_t_utc(g, data, _oss_pe_t_daytime(g, data))
#define _oss_pe_t_daytime_utc_fraction(g, data, accuracy) \
	_oss_pe_t_utc(g, data, _oss_pe_t_daytime_fraction(g, data, accuracy))
extern char * DLL_ENTRY _oss_pe_t_year(OssGlobal *g, char *data);
#define _oss_pe_t_year_day(g, data) \
	_oss_pe_t_day_of_year(g, _oss_pe_t_year(g, data))
#define _oss_pe_t_year_month(g, data) \
	_oss_pe_t_month(g, _oss_pe_t_year(g, data))
#define _oss_pe_t_year_week(g, data) \
	_oss_pe_t_week(g, _oss_pe_t_year(g, data))
#define _oss_pe_t_year_week_day(g, data) \
	_oss_pe_t_day_of_week(g, _oss_pe_t_year_week(g, data))
#define _oss_set_t_se_points_in_use(c, v) \
	(c).reserved.fields.ext->timeSEPointsInUse = v

/* decoding functions */

extern unsigned char DLL_ENTRY _oss_get_bit(struct ossGlobal *g, int align);

extern void DLL_ENTRY _oss_get_bits(struct ossGlobal *g, unsigned char *field,
			unsigned long length, int align);

extern unsigned char DLL_ENTRY _oss_get_1bit_unaligned(struct ossGlobal *g);
extern unsigned char DLL_ENTRY _oss_get_2bit_unaligned(struct ossGlobal *g);
extern unsigned char DLL_ENTRY _oss_get_3bit_unaligned(struct ossGlobal *g);
extern unsigned char DLL_ENTRY _oss_get_4bit_unaligned(struct ossGlobal *g);
extern unsigned char DLL_ENTRY _oss_get_5bit_unaligned(struct ossGlobal *g);
extern unsigned char DLL_ENTRY _oss_get_6bit_unaligned(struct ossGlobal *g);
extern unsigned char DLL_ENTRY _oss_get_7bit_unaligned(struct ossGlobal *g);
extern unsigned char DLL_ENTRY _oss_get_8bit_unaligned(struct ossGlobal *g);

extern unsigned char DLL_ENTRY _oss_get_octet(struct ossGlobal *g, int align);

extern LONG_LONG DLL_ENTRY _oss_pdec_unconstr_int(struct ossGlobal *g);

extern LONG_LONG DLL_ENTRY _oss_pdec_semicon_int(struct ossGlobal *g,
	    LONG_LONG lower_bound);

extern ULONG_LONG DLL_ENTRY _oss_pdec_semicon_uint(struct ossGlobal *g,
	    ULONG_LONG lower_bound);

extern ULONG_LONG DLL_ENTRY _oss_pdec_nonneg_int(struct ossGlobal *g,
	    ULONG_LONG range);

extern ULONG_LONG DLL_ENTRY _oss_pdec_indeflen_int(struct ossGlobal *g,
	    ULONG_LONG range);

extern ULONG_LONG DLL_ENTRY _oss_pdec_small_int(struct ossGlobal *g);

extern LONG_LONG DLL_ENTRY _oss_pdec_unconstr_limited_int(struct ossGlobal *g,
	LONG_LONG lower_limit, LONG_LONG upper_limit);

extern LONG_LONG DLL_ENTRY _oss_pdec_semicon_limited_int(struct ossGlobal *g,
	LONG_LONG lower_bound, LONG_LONG lower_limit, LONG_LONG upper_limit);

extern ULONG_LONG DLL_ENTRY _oss_pdec_nonneg_limited_int(struct ossGlobal *g,
	ULONG_LONG range, LONG_LONG lower_limit, LONG_LONG upper_limit);

extern unsigned int DLL_ENTRY _oss_pdec_nonneg_1int(struct ossGlobal *g);
extern unsigned int DLL_ENTRY _oss_pdec_nonneg_2int(struct ossGlobal *g);
extern unsigned int DLL_ENTRY _oss_pdec_nonneg_3int(struct ossGlobal *g);
extern unsigned int DLL_ENTRY _oss_pdec_nonneg_4int(struct ossGlobal *g);
extern unsigned int DLL_ENTRY _oss_pdec_nonneg_5int(struct ossGlobal *g);
extern unsigned int DLL_ENTRY _oss_pdec_nonneg_6int(struct ossGlobal *g);
extern unsigned int DLL_ENTRY _oss_pdec_nonneg_7int(struct ossGlobal *g);
extern unsigned int DLL_ENTRY _oss_pdec_nonneg_8int(struct ossGlobal *g);

extern ULONG_LONG DLL_ENTRY _oss_pdec_indeflen_limited_int(struct ossGlobal *g,
	ULONG_LONG range, LONG_LONG lower_bound, LONG_LONG lower_limit,
	LONG_LONG upper_limit);

extern long DLL_ENTRY _oss_pdec_enum(struct ossGlobal *g,
	 struct _enum_data *root,
	 struct _enum_data *extension);

extern unsigned long DLL_ENTRY _oss_pdec_uenum(struct ossGlobal *g,
	 struct _enum_data *root,
	 struct _enum_data *extension);

extern double DLL_ENTRY _oss_pdec_binreal(struct ossGlobal *g, unsigned char s, long len);
extern void DLL_ENTRY _oss_pdec_chrreal(struct ossGlobal *g, unsigned char s, long len,
     double *num_out, unsigned char *str_out);

extern float     DLL_ENTRY _oss_pdec_freal(struct ossGlobal *g);
extern double    DLL_ENTRY _oss_pdec_real(struct ossGlobal *g);
extern char *    DLL_ENTRY _oss_pdec_creal(struct ossGlobal *g);
extern enum MixedReal_kind DLL_ENTRY _oss_pdec_mreal_ia
	(struct ossGlobal *g, void *data);

extern unsigned long DLL_ENTRY _oss_pdec_length(struct ossGlobal *g,
	unsigned long lb, unsigned long ub, ossBoolean *last);

extern unsigned long DLL_ENTRY _oss_pdec_unconstr_ubit_ia(struct ossGlobal *g,
	unsigned char **value);

extern unsigned long DLL_ENTRY _oss_pdec_unconstr_vbit_ptr_ia
	(struct ossGlobal *g, void *ptr, unsigned int offset);

extern unsigned long  DLL_ENTRY _oss_pdec_unconstr_vbit_ia
    (struct ossGlobal *g, unsigned char *value, unsigned long datasize);

extern void DLL_ENTRY _oss_pdec_unconstr_pbit(struct ossGlobal *g, void *value,
	int size);

extern void DLL_ENTRY _oss_pdec_unconstr_bpbit(struct ossGlobal *g, unsigned char *value,
	long size);

extern unsigned long DLL_ENTRY _oss_pdec_constr_ubit_ia(struct ossGlobal *g,
	unsigned char **value, unsigned long lb, unsigned long ub);

extern unsigned long DLL_ENTRY _oss_pdec_constr_vbit_ia
    (struct ossGlobal *g,
	unsigned char *value, unsigned long lb, unsigned long ub);

extern unsigned long DLL_ENTRY _oss_pdec_constr_vbit_ptr_ia
	(struct ossGlobal *g, void *ptr, unsigned int offset,
		unsigned long lb, unsigned long ub);

extern void DLL_ENTRY _oss_pdec_constr_pbit_l(struct ossGlobal *g,
	void *value, int size, unsigned long lb, unsigned long ub);

extern void DLL_ENTRY _oss_pdec_constr_bpbit(struct ossGlobal *g, unsigned char *value,
	int size, ULONG_LONG lb, ULONG_LONG ub);

extern void DLL_ENTRY _oss_pdec_constr_bpbit_l(struct ossGlobal *g,
	unsigned char *value, int size, unsigned long lb, unsigned long ub);

extern unsigned long DLL_ENTRY _oss_pdec_unconstr_uoct_ia(struct ossGlobal *g,
	unsigned char **value);

extern unsigned long DLL_ENTRY _oss_pdec_unconstr_voct_ptr_ia
	(struct ossGlobal *g, void *ptr, unsigned int offset);

extern unsigned long DLL_ENTRY _oss_pdec_constr_voct_ptr_ia
	(struct ossGlobal *g, void *ptr, unsigned int offset,
		unsigned long lb, unsigned long ub);

extern unsigned long DLL_ENTRY _oss_pdec_constr_uoct_ia(struct ossGlobal *g,
	unsigned char **value, unsigned long lb, unsigned long ub);

extern unsigned long DLL_ENTRY _oss_pdec_constr_voct_ia
	(struct ossGlobal *g,
	unsigned char *value, unsigned long lb, unsigned long ub);

extern unsigned long DLL_ENTRY _oss_pdec_unconstr_voct_ia
	(struct ossGlobal *g, unsigned char *value, unsigned long ub);

extern void DLL_ENTRY_FDEF _oss_pdec_fixed_oct(struct ossGlobal *g,
	void *value, unsigned long sz);

extern void DLL_ENTRY _oss_pdec_push(struct ossGlobal *g);
extern void DLL_ENTRY _oss_pdec_pop(struct ossGlobal *g);

extern unsigned long DLL_ENTRY _oss_pdec_eap(struct ossGlobal *g, unsigned char **ext);
extern void DLL_ENTRY _oss_pdec_eas(struct ossGlobal *g, unsigned char *ext,
	 unsigned long count, unsigned long ea_num);

extern void DLL_ENTRY _oss_pdec_lsof(struct ossGlobal *g, unsigned long *count,
    ULONG_LONG lb, ULONG_LONG ub, unsigned char ext,
    ossBoolean *last);

extern void DLL_ENTRY _oss_pdec_usof(struct ossGlobal *g, unsigned long *count,
    unsigned char **value, int lengthsize, long itemsize,
    ULONG_LONG lb, ULONG_LONG ub, unsigned char ext,
    ossBoolean *last);

extern void DLL_ENTRY _oss_pdec_lsof_l(struct ossGlobal *g,
    unsigned long *count, unsigned long lb, unsigned long ub,
			unsigned char ext, ossBoolean *last);
extern void DLL_ENTRY _oss_pdec_unbnd_frg(OssGlobal *g,
	void *ptr, unsigned long new_size, unsigned long old_size,
	ossBoolean *last);
extern void DLL_ENTRY _oss_pdec_asof(struct ossGlobal *g, unsigned long *count,
    int lengthsize,
    ULONG_LONG lb, ULONG_LONG ub, unsigned char ext,
    ossBoolean *last);

extern void DLL_ENTRY _oss_pdec_asof_ptr_ia(struct ossGlobal *g,
    void *ptr, int lengthsize, long itemsize, unsigned int offset,
    ossBoolean *last);

extern void DLL_ENTRY _oss_pdec_aobjids(struct ossGlobal *g, unsigned short *value,
    unsigned short *count, unsigned short array_size);

extern void DLL_ENTRY _oss_pdec_aobjidi(struct ossGlobal *g, unsigned int   *value,
    unsigned short *count, unsigned short array_size);

extern void DLL_ENTRY _oss_pdec_aobjidl(struct ossGlobal *g, unsigned long  *value,
    unsigned short *count, unsigned short array_size);

extern void * DLL_ENTRY _oss_pdec_aobjids_ptr_ia(struct ossGlobal *g,
    unsigned int offset);
extern void * DLL_ENTRY _oss_pdec_aobjidi_ptr_ia(struct ossGlobal *g,
    unsigned int offset);
extern void * DLL_ENTRY _oss_pdec_aobjidl_ptr_ia(struct ossGlobal *g,
    unsigned int offset);

extern void DLL_ENTRY _oss_pdec_uobjids(struct ossGlobal *g, unsigned short **value,
	 unsigned short *count);
extern void DLL_ENTRY _oss_pdec_uobjidi(struct ossGlobal *g, unsigned int **value,
	 unsigned short *count);
extern void DLL_ENTRY _oss_pdec_uobjidl(struct ossGlobal *g, unsigned long **value,
	 unsigned short *count);

extern void DLL_ENTRY _oss_pdec_link_objids(struct ossGlobal *g, void **ptr);
extern void DLL_ENTRY _oss_pdec_link_objidi(struct ossGlobal *g, void **ptr);
extern void * DLL_ENTRY _oss_pdec_link_objidl_ia(struct ossGlobal *g,
    unsigned int offset);

extern void DLL_ENTRY _oss_pdec_nt_kmstr( struct ossGlobal *g, void *ptr,
    const struct st_PER_String_Data *psd ); 

extern unsigned long DLL_ENTRY _oss_pdec_vap_kmstr( struct ossGlobal *g,
    void *ptr, unsigned int offset,
    const struct st_PER_String_Data *psd );

extern unsigned long DLL_ENTRY _oss_pdec_va_kmstr( struct ossGlobal *g,
    char *ptr, const struct st_PER_String_Data *psd );

extern void DLL_ENTRY _oss_pdec_ntp_kmstr( struct ossGlobal *g, char **ptr,
    const struct st_PER_String_Data *psd );

extern unsigned long DLL_ENTRY _oss_pdec_ub_kmstr( struct ossGlobal *g, char **ptr,
    const struct st_PER_String_Data *psd );

extern unsigned long DLL_ENTRY _oss_pdec_bmpstr( struct ossGlobal *g, unsigned short **ptr,
    const struct st_PER_String_Data *psd );

extern unsigned long DLL_ENTRY _oss_pdec_unistr( struct ossGlobal *g, OSS_INT32 **ptr,
    const struct st_PER_String_Data *psd );

extern void DLL_ENTRY _oss_pdec_ntp_nkmstr(struct ossGlobal *g, char **ptr);
extern void DLL_ENTRY _oss_pdec_nt_nkmstr(struct ossGlobal *g, char *value, unsigned long ub);
extern void DLL_ENTRY _oss_pdec_pad_nkmstr(struct ossGlobal *g, char *value, unsigned long ub);
extern unsigned long DLL_ENTRY _oss_pdec_vap_nkmstr_ia
	(struct ossGlobal *g, void *ptr, unsigned int offset);
extern unsigned long DLL_ENTRY _oss_pdec_va_nkmstr_ia
    (struct ossGlobal *g, char *value, unsigned long ub);
extern unsigned long DLL_ENTRY _oss_pdec_ub_nkmstr_ia(struct ossGlobal *g, char **ptr);

extern void DLL_ENTRY _oss_pdec_pad_kmstr( struct ossGlobal *g, void *ptr,
    const struct st_PER_String_Data *psd );

extern void DLL_ENTRY _oss_pdec_opentype(struct ossGlobal *g, void *data );
extern void DLL_ENTRY _oss_pdec_uany(struct ossGlobal *g, void *data );

extern void DLL_ENTRY _oss_pdec_gtime(struct ossGlobal *g, GeneralizedTime *data);
extern void DLL_ENTRY _oss_pdec_utime(struct ossGlobal *g, UTCTime *data);

extern struct _char_data * CDECL_ENTRY _oss_get_char_data(struct ossGlobal *g, int index);

extern unsigned int DLL_ENTRY _oss_pdec_unconstr_huge_ia(struct ossGlobal *g,
	void *data);

extern unsigned int DLL_ENTRY _oss_pdec_semicon_huge_ia(struct ossGlobal *g,
	void *data, long lb);
extern unsigned int DLL_ENTRY _oss_pdec_limited_huge(struct ossGlobal *g, 
			    unsigned char **v,
			    unsigned char *lb, unsigned int lb_len,
			    unsigned int flags);
extern void DLL_ENTRY _oss_penc_limited_huge(struct ossGlobal *g, 
			    unsigned char *v, unsigned int v_len,
			    unsigned char *lb, unsigned int lb_len,
			    unsigned int flags);

extern unsigned int DLL_ENTRY _oss_pdec_eobjid_ia(struct ossGlobal *g,
			    void *data, long size_c);
extern 	unsigned int DLL_ENTRY _oss_pdec_ereloid_ia(struct ossGlobal *g,
			    void *data, long size_c);

extern void DLL_ENTRY _oss_pdec_sot(struct ossGlobal *g);

extern ossBoolean DLL_ENTRY _oss_lnchk(unsigned char *value,
	ULONG_LONG *lenptr, unsigned short endpoint, ULONG_LONG lb,
	ULONG_LONG ub);

extern unsigned long DLL_ENTRY _oss_pdec_utf8bmpstr_ia(struct ossGlobal *g,
	unsigned short **ptr);

extern unsigned long DLL_ENTRY _oss_pdec_utf8unistr_ia(struct ossGlobal *g,
	OSS_INT32 **ptr);

extern unsigned long DLL_ENTRY _oss_pdec_indeflen_int_l(struct ossGlobal *g,
	    unsigned long range);
extern unsigned long DLL_ENTRY _oss_pdec_indeflen_limited_int_l(struct ossGlobal *g,
	    unsigned long range, long lower_bound, long lower_limit,
	    long upper_limit);
extern unsigned long DLL_ENTRY _oss_pdec_nonneg_int_l(struct ossGlobal *g,
	    unsigned int range);
extern unsigned long DLL_ENTRY _oss_pdec_nonneg_limited_int_l(struct ossGlobal *g,
	    unsigned int range, long lower_limit, long upper_limit);
extern long DLL_ENTRY _oss_pdec_semicon_int_l(struct ossGlobal *g,
	    long lower_bound);
extern long DLL_ENTRY _oss_pdec_semicon_limited_int_l(struct ossGlobal *g,
	    long lower_bound, long lower_limit, long upper_limit);
extern unsigned long DLL_ENTRY _oss_pdec_semicon_uint_l(struct ossGlobal *g,
	    unsigned long lower_bound);
extern unsigned long DLL_ENTRY _oss_pdec_small_int_l(struct ossGlobal *g);
extern long DLL_ENTRY _oss_pdec_unconstr_int_l(struct ossGlobal *g);
extern long DLL_ENTRY _oss_pdec_unconstr_limited_int_l(struct ossGlobal *g,
	    long lower_limit, long upper_limit);
extern void DLL_ENTRY _oss_pdec_array_frg (OssGlobal *g,
		 void *ptr, unsigned long frgSz, unsigned long arrSz,
				unsigned int offset, ossBoolean *last);
extern unsigned char _oss_log2table[257];

extern char * DLL_ENTRY _oss_pd_t_century(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_any_century(OssGlobal *g, char *data,
							unsigned int max_d_num);
extern char * DLL_ENTRY _oss_pd_t_year(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_any_year(OssGlobal *g, char *data,
							unsigned int max_d_num);
extern char * DLL_ENTRY _oss_pd_t_month(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_day_of_month(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_day_of_year(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_week(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_day_of_week(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_hours(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_time_diff(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_mins_or_secs(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_time_fraction(OssGlobal *g, char *data,
							unsigned int accuracy);
extern char * DLL_ENTRY _oss_pd_t_recurrence(OssGlobal *g, char *data,
							unsigned int max_r_num);
extern char * DLL_ENTRY _oss_pd_t_duration_interval(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_pd_t_mixed(OssGlobal *g, char *data);
#define _oss_pd_t_year_month(g, data) \
	_oss_pd_t_month(g, _oss_pd_t_year(g, data))
#define _oss_pd_t_any_year_month(g, data, max_yd_num) \
	_oss_pd_t_month(g, _oss_pd_t_any_year(g, data, max_yd_num))
#define _oss_pd_t_date(g, data) \
	_oss_pd_t_day_of_month(g, _oss_pd_t_year_month(g, data))
#define _oss_pd_t_any_date(g, data, max_yd_num) \
	_oss_pd_t_day_of_month(g, _oss_pd_t_any_year_month(g, data, max_yd_num))
#define _oss_pd_t_year_day(g, data) \
	_oss_pd_t_day_of_year(g, _oss_pd_t_year(g, data))
#define _oss_pd_t_any_year_day(g, data, max_yd_num) \
	_oss_pd_t_day_of_year(g, _oss_pd_t_any_year(g, data, max_yd_num))
#define _oss_pd_t_year_week(g, data) \
	_oss_pd_t_week(g, _oss_pd_t_year(g, data))
#define _oss_pd_t_any_year_week(g, data, max_yd_num) \
	_oss_pd_t_week(g, _oss_pd_t_any_year(g, data, max_yd_num))
#define _oss_pd_t_year_week_day(g, data) \
	_oss_pd_t_day_of_week(g, _oss_pd_t_year_week(g, data))
#define _oss_pd_t_any_year_week_day(g, data, max_yd_num) \
	_oss_pd_t_day_of_week(g, _oss_pd_t_any_year_week(g, data, max_yd_num))
#define _oss_pd_t_utc(data, in) (*(data = in) = 'Z', data + 1)
#define _oss_pd_t_hours_utc(g, data) \
	_oss_pd_t_utc(data, _oss_pd_t_hours(g, data))
#define _oss_pd_t_hours_diff(g, data) \
	_oss_pd_t_time_diff(g, _oss_pd_t_hours(g, data))
#define _oss_pd_t_minutes(g, data) \
	_oss_pd_t_mins_or_secs(g, _oss_pd_t_hours(g, data))
#define _oss_pd_t_minutes_utc(g, data) \
	_oss_pd_t_utc(data, _oss_pd_t_minutes(g, data))
#define _oss_pd_t_minutes_diff(g, data) \
	_oss_pd_t_time_diff(g, _oss_pd_t_minutes(g, data))
#define _oss_pd_t_daytime(g, data) \
	_oss_pd_t_mins_or_secs(g, _oss_pd_t_minutes(g, data))
#define _oss_pd_t_daytime_utc(g, data) \
	_oss_pd_t_utc(data, _oss_pd_t_daytime(g, data))
#define _oss_pd_t_daytime_diff(g, data) \
	_oss_pd_t_time_diff(g, _oss_pd_t_daytime(g, data))
#define _oss_pd_t_hours_fraction(g, data, accuracy) \
	_oss_pd_t_time_fraction(g, _oss_pd_t_hours(g, data), accuracy)
#define _oss_pd_t_hours_utc_fraction(g, data, accuracy) \
	_oss_pd_t_utc(data, _oss_pd_t_hours_fraction(g, data, accuracy))
#define _oss_pd_t_hours_diff_fraction(g, data, accuracy) \
	_oss_pd_t_time_diff(g, _oss_pd_t_hours_fraction(g, data, accuracy))
#define _oss_pd_t_minutes_fraction(g, data, accuracy) \
	_oss_pd_t_time_fraction(g, _oss_pd_t_minutes(g, data), accuracy)
#define _oss_pd_t_minutes_utc_fraction(g, data, accuracy) \
	_oss_pd_t_utc(data, _oss_pd_t_minutes_fraction(g, data, accuracy))
#define _oss_pd_t_minutes_diff_fraction(g, data, accuracy) \
	_oss_pd_t_time_diff(g, _oss_pd_t_minutes_fraction(g, data, accuracy))
#define _oss_pd_t_daytime_fraction(g, data, accuracy) \
	_oss_pd_t_time_fraction(g, _oss_pd_t_daytime(g, data), accuracy)
#define _oss_pd_t_daytime_utc_fraction(g, data, accuracy) \
	_oss_pd_t_utc(data, _oss_pd_t_daytime_fraction(g, data, accuracy))
#define _oss_pd_t_daytime_diff_fraction(g, data, accuracy) \
	_oss_pd_t_time_diff(g, _oss_pd_t_daytime_fraction(g, data, accuracy))

#endif /* OSS_TOED_PER */
#if defined(OSS_TOED_PER) || defined(OSS_TOED_OER)
extern unsigned int DLL_ENTRY _oss_copy_preamble(struct ossGlobal *g,
	 unsigned char *ext, unsigned long count, unsigned long ea_num,
	void *un_ea_num, unsigned char **un_ea_pr, unsigned int length_size);
#endif

#if defined(OSS_TOED_XER) || defined(OSS_TOED_EXER)
long	DLL_ENTRY _oss_tex_count_bits (unsigned char *value, long bit_len);
long	DLL_ENTRY _oss_tex_count_chars (char *value, long max_len);
#endif

#ifdef OSS_TOED_XER
/*****************************************************************************/
/*  TOED XER section                                                         */
/*****************************************************************************/
    /*************************************************************************/
    /*      TOED XER functions section                                       */
    /*************************************************************************/

extern void DLL_ENTRY _oss_allocate_memblock(struct ossGlobal *g,
			struct _mem_block_ **tmp_mem, void **value, long used);
extern void DLL_ENTRY _oss_consolidate_memblock(struct ossGlobal *g,
			void **value, long itemsize, long ecount,
			struct _mem_block_ *tmp_mem,long bcnt,long bcount,
			long bindex, int offset, OSS_UINT32 ubound,
			OSS_UINT32 flags);
extern void * DLL_ENTRY _oss_consolidate_memblock_fast(struct ossGlobal *g,
			long itemsize, long ecount, struct _mem_block_ *tmp_mem,
			long bcnt, long bcount, long bindex, int offset);

/* TOED XER encoder definitions and declarations */
void	DLL_ENTRY _oss_tex_open_tag (OssGlobal * _g, char * tag);
void	DLL_ENTRY _oss_tex_close_tag (OssGlobal * _g, char * tag);
void	DLL_ENTRY _oss_tex_empty_or_id_tag (OssGlobal * _g, const char * tag);
void	DLL_ENTRY _oss_tex_open_tagN (OssGlobal * _g, char * tag, int taglen);
void	DLL_ENTRY _oss_tex_close_tagN (OssGlobal * _g, char * tag, int taglen);
void	DLL_ENTRY _oss_tex_empty_or_id_tagN (OssGlobal * _g, const char * tag, int taglen);
void	DLL_ENTRY _oss_tex_format_tagN (OssGlobal *g, char *tag, int taglen);
long	DLL_ENTRY _oss_tex_curr_enclen (OssGlobal * _g);
void	DLL_ENTRY _oss_tex_format_tag (OssGlobal *g, char *tag);
void	DLL_ENTRY _oss_tex_indent_dlt (OssGlobal * _g, int dlt);
void	DLL_ENTRY _oss_tex_indent (OssGlobal * _g);
void	DLL_ENTRY _oss_tex_lint (OssGlobal *_g, long value);
void	DLL_ENTRY _oss_tex_ulint (OssGlobal *_g, unsigned long value);
void	DLL_ENTRY _oss_tex_llint (OssGlobal *_g, LONG_LONG value);
void	DLL_ENTRY _oss_tex_ullint (OssGlobal *_g, ULONG_LONG value);
void	DLL_ENTRY _oss_tex_hint (OssGlobal *g, unsigned char *value,
		long length);
void	DLL_ENTRY _oss_tex_ntime (OssGlobal *_g, char *data, size_t inlen, ossBoolean is_utc);

void	DLL_ENTRY _oss_tex_time (OssGlobal *_g, GeneralizedTime *data,
		ossBoolean is_utc);
void	DLL_ENTRY _oss_tex_date_time(OssGlobal *_g, char *data, int kind);
void	DLL_ENTRY _oss_tex_enum(OssGlobal *_g, _oss_enumInfo *_vN, long value, int mode);
void	DLL_ENTRY _oss_tex_format_enum(OssGlobal *_g, char * name, int mode);

void	DLL_ENTRY _oss_tex_dreal (OssGlobal *_g, double value);
void	DLL_ENTRY _oss_tex_freal (OssGlobal *_g, float value);
void	DLL_ENTRY _oss_tex_creal (OssGlobal *_g, char *value);

void	DLL_ENTRY _oss_tex_eobjid (OssGlobal *_g, unsigned char * value, long length,
		long max_count, ossBoolean relative);
void	DLL_ENTRY _oss_tex_aobjids(OssGlobal *_g, unsigned short * value, long count,
		long max_count);
void	DLL_ENTRY _oss_tex_aobjidi(OssGlobal *_g, unsigned int * value, long count,
		long max_count);
void	DLL_ENTRY _oss_tex_aobjidl(OssGlobal *_g, unsigned long * value, long count,
		long max_count);
void	DLL_ENTRY _oss_tex_lobjids(OssGlobal *_g, void * value, long max_count);
void	DLL_ENTRY _oss_tex_lobjidi(OssGlobal *_g, void * value, long max_count);
void	DLL_ENTRY _oss_tex_lobjidl(OssGlobal *_g, void * value, long max_count);

void	DLL_ENTRY _oss_tex_format_char (OssGlobal *_g, unsigned char *value, long len);
void	DLL_ENTRY _oss_tex_format_char_t (OssGlobal *_g, unsigned char *value, long len);
void	DLL_ENTRY _oss_tex_format_bit (OssGlobal *_g, unsigned char *value, long bit_len);
void	DLL_ENTRY _oss_tex_format_pbit (OssGlobal *g, OSS_UINT32 value, long bit_len);
void	DLL_ENTRY _oss_tex_format_octet (OssGlobal *_g, unsigned char *value, unsigned long length);
void	DLL_ENTRY _oss_tex_prolog (OssGlobal *_g);
void	DLL_ENTRY _oss_tex_opentype (OssGlobal *_g, void *data);
void	DLL_ENTRY _oss_tex_anyopentype (OssGlobal *_g, unsigned char *data, long length);

void	DLL_ENTRY _oss_tex_2byte_char (OssGlobal *_g, unsigned short *value, long length);
void	DLL_ENTRY _oss_tex_4byte_char (OssGlobal *_g, OSS_UINT32 *value, long length);

/* TOED XER decoder definitions and declarations */

/* kinds of lexem */
#define L_BYTE		0
#define L_START		1
#define L_STARTEND	2
#define L_END		4
#define L_COMMENT	5
#define L_HEX_BYTE	0x10
#define L_KEEP		0x80

#define _oss_tdx_present_field(mask)	\
		if (_present_fields & mask) \
		    _oss_dec_error(_g, _field_repeat, 0L); \
		_present_fields |= mask;

#define _oss_tdx_present_field_arr(n, mask)	\
		if (_present_fields[n] & mask) \
		    _oss_dec_error(_g, _field_repeat, 0L); \
		_present_fields[n] |= mask;

long		DLL_ENTRY _oss_tex_append (OssGlobal *g, unsigned char * data, long num);
void 		DLL_ENTRY _oss_tdx_open_tag(_Xml_Dec_Env *env, char *tagname);
    /* read open tag with the specified name */
void 		DLL_ENTRY _oss_tdx_empty_tag(_Xml_Dec_Env *env, char *tagname);
    /* read empty tag with the specified name */
void 		DLL_ENTRY _oss_tdx_close_tag(_Xml_Dec_Env *env, char *tagname);
    /* read close tag with the specified name */
ossBoolean	DLL_ENTRY _oss_tdx_open_or_empty_tag(_Xml_Dec_Env *env,
			char *tagname);
    /* read open or empty tag with the specified name (TRUE if empty) */
ossBoolean	DLL_ENTRY _oss_tdx_open_field(_Xml_Dec_Env *env,
			struct _string_search_data *f,	short *f_idx);
void		DLL_ENTRY _oss_tdx_skip_block(_Xml_Dec_Env  *env);
unsigned long 	DLL_ENTRY _oss_tdx_rsf_alt(_Xml_Dec_Env  *env, void **_data);
void            DLL_ENTRY _oss_tdx_rsf_ext(_Xml_Dec_Env  *env, 
			void **_data, unsigned int *count);
void		DLL_ENTRY _oss_tdx_prolog(_Xml_Dec_Env  *env);
unsigned char	DLL_ENTRY _oss_tdx_lexem_lookahead(_Xml_Dec_Env  *env);
unsigned long	DLL_ENTRY _oss_tdx_allocate_array_sof(_Xml_Dec_Env  *_env,
			void **data, int offset, long itemsize);
unsigned long	DLL_ENTRY _oss_tdx_allocate_unbounded_sof(_Xml_Dec_Env  *_env,
			void **value, long itemsize, OSS_UINT32 ubound,
			OSS_UINT32 flags);
void		DLL_ENTRY _oss_tdx_opentype(_Xml_Dec_Env  *_env, void *data,
			OSS_UINT32 flags);
void            DLL_ENTRY _oss_tdx_new_opentype(_Xml_Dec_Env *env,
			OssBuf *encoded);

ossBoolean 	DLL_ENTRY _oss_tdx_bool(_Xml_Dec_Env *env);
OSS_INT32 	DLL_ENTRY _oss_tdx_enum(_Xml_Dec_Env *env,
			struct _string_search_data * data);

LONG_LONG	DLL_ENTRY _oss_tdx_llint(_Xml_Dec_Env *env);
ULONG_LONG	DLL_ENTRY _oss_tdx_ullint(_Xml_Dec_Env *env);
long		DLL_ENTRY _oss_tdx_lint(_Xml_Dec_Env *env, long lb, long ub);
unsigned long	DLL_ENTRY _oss_tdx_ulint(_Xml_Dec_Env *env, unsigned long lb);
unsigned long	DLL_ENTRY _oss_tdx_hint(_Xml_Dec_Env *env, void **value,
			OSS_UINT32 flags);

double		DLL_ENTRY _oss_tdx_dreal(_Xml_Dec_Env *env);
float		DLL_ENTRY _oss_tdx_freal(_Xml_Dec_Env *env);
char *		DLL_ENTRY _oss_tdx_creal(_Xml_Dec_Env *env);
enum MixedReal_kind DLL_ENTRY _oss_tdx_mreal_ia(_Xml_Dec_Env *env, void *data);

void		DLL_ENTRY _oss_tdx_char1_nullterm(_Xml_Dec_Env *env,
			void *storage, OSS_UINT32 ubound, OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_char1_unbounded(_Xml_Dec_Env *env,
			void **value, OSS_UINT32 ubound, OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_char1_pvarying(_Xml_Dec_Env *env,
			void **data, int offset, OSS_UINT32 ubound,
			OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_char1_varying(_Xml_Dec_Env *env,
			void *value, OSS_UINT32 ubound, OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_char2(_Xml_Dec_Env *env, void **value,
			OSS_UINT32 ubound, OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_char4(_Xml_Dec_Env *env, void **value,
			OSS_UINT32 ubound, OSS_UINT32 flags);

unsigned long	DLL_ENTRY _oss_tdx_octets_unbounded(_Xml_Dec_Env *env,
			void **value, OSS_UINT32 ubound, OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_octets_pvarying(_Xml_Dec_Env *env,
			void **data, int offset, OSS_UINT32 ubound,
			OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_octets_varying(_Xml_Dec_Env *env,
			void *value, OSS_UINT32 ubound, OSS_UINT32 flags);

void DLL_ENTRY_FDEF _oss_tdx_octets_fixed(_Xml_Dec_Env *env,
			void *value, OSS_UINT32 size);

unsigned long	DLL_ENTRY _oss_tdx_bits_unbounded(_Xml_Dec_Env *env,
			void **value, OSS_UINT32 ubound, OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_bits_pvarying(_Xml_Dec_Env *env,
			void **data, int offset, OSS_UINT32 ubound,
			OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_bits_varying(_Xml_Dec_Env *env,
			void *value, OSS_UINT32 ubound, OSS_UINT32 flags);
unsigned long	DLL_ENTRY _oss_tdx_bits_padded(_Xml_Dec_Env *env,
			int lengthsize, OSS_UINT32 flags);

OSS_UINT32	DLL_ENTRY _oss_tdx_objid_encoded(_Xml_Dec_Env *env,
			void *data, OSS_UINT32 ubound, OSS_UINT32 flags);
void		DLL_ENTRY _oss_tdx_objid_linked(_Xml_Dec_Env *env,
			void **data, unsigned short nodesize,
			OSS_UINT32 ubound, OSS_UINT32 flags);
unsigned short	DLL_ENTRY _oss_tdx_objid_unbounded(_Xml_Dec_Env *env,
			void **value, unsigned short nodesize,
			OSS_UINT32 ubound, OSS_UINT32 flags);
unsigned short	DLL_ENTRY _oss_tdx_objid_array(_Xml_Dec_Env *env, void *value,
			OSS_UINT32 ubound, unsigned short nodesize);
unsigned short	DLL_ENTRY _oss_tdx_objid_parray(_Xml_Dec_Env *env, void **data,
			int offset, unsigned short nodesize);

void		DLL_ENTRY _oss_tdx_gtime(_Xml_Dec_Env *env, void *storage);
void		DLL_ENTRY _oss_tdx_utime(_Xml_Dec_Env *env, void *storage);
void	        DLL_ENTRY _oss_tdx_date_time(_Xml_Dec_Env *env, char **data,
			int kind);
#endif /* OSS_TOED_XER */

#ifdef OSS_TOED_EXER
/*****************************************************************************/
/*  TOED EXER section                                                        */
/*****************************************************************************/

#define OSS_SOF_LENGTH 64

#define OSS_TSTK_NEW_FRAGMENT(g, c, size) \
  { if ((c)->tmp_mem.stack.bounds.left + (size) > (c)->tmp_mem.stack.bounds.right) \
	_oss_tstk_add_block(g, size); \
    _buf = (unsigned char *)(c)->tmp_mem.stack.bounds.left; \
    (c)->tmp_mem.stack.bounds.left += (size); }

#define OSS_TSTK_CONSOLIDATE_ARRAY(g, c, out, size) \
    _oss_tstk_consolidate_array_tag(_env, _first_buf, (void *)out, size) 

#define _oss_tstk_tell(g) (((_EncDecGlobals *)(g)->encDecVar)->tmp_mem.stack.bounds.left)

#define _oss_tdex_iso_time_list	_oss_tdex_iso_time

void DLL_ENTRY _oss_tstk_consolidate_outmem( OssGlobal *g, void *out, void *ptr, size_t size );
unsigned char *DLL_ENTRY _oss_tstk_get_altdecmem( OssGlobal *g, size_t size );
void DLL_ENTRY _oss_tstk_consolidate_altdecmem( OssGlobal *g,
    void *out, size_t size, size_t block_size );
void DLL_ENTRY _oss_tstk_free_altdecmem( OssGlobal *g, void *ptr );
unsigned char *DLL_ENTRY _oss_tstk_new_fragment_tag( exer_denv *env,
    size_t size );
void DLL_ENTRY _oss_tstk_consolidate_array_tag( exer_denv *env,
    unsigned char *first_buf, void *out, size_t size );

void DLL_ENTRY _oss_tell_dec_outmem( OssGlobal *g, OssToedDecmem *dm );
void DLL_ENTRY _oss_free_dec_outmem( OssGlobal *g, OssToedDecmem *dm );

void *DLL_ENTRY _oss_tstk_alloc( OssGlobal *g, size_t size );
void DLL_ENTRY _oss_tstk_free( OssGlobal *g, void *p );

    /*************************************************************************/
    /*      TOED EXER functions section                                      */
    /*************************************************************************/
int		DLL_ENTRY find_PDU_by_exer_tag_name(OssGlobal *world,
				exer_toed_table *etable,
        			unsigned char *uri, OSS_LENGTH ulen,
				unsigned char *name, OSS_LENGTH len);
void 		DLL_ENTRY _oss_tdex_init_env(exer_denv *env, 
				unsigned char *buf, unsigned long length);
void 		DLL_ENTRY _oss_tlex_get_lex(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_get_lex_collapse(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_get_tag(exer_denv *env);
void 		DLL_ENTRY _oss_tdex_error(exer_denv *env, 
				enum _err_index error_code, void *data, 
				OSS_UINT32 flags);
int 		DLL_ENTRY _oss_tlex_prolog_and_tag(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_check_close_tag(exer_denv *env);
unsigned long 	DLL_ENTRY _oss_tdex_char1_list(exer_denv *env, 
				void *value, exer_char1 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char2_list(exer_denv *env, 
				OSS_UINT16 **value, exer_char2 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char4_list(exer_denv *env, 
				OSS_INT32 **value, exer_char4 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char1_collapse(exer_denv *env, 
				void *value, exer_char1 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char2_collapse(exer_denv *env, 
				OSS_UINT16 **value, exer_char2 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char4_collapse(exer_denv *env, 
				OSS_INT32 **value, exer_char4 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char1_replace(exer_denv *env, 
				void *value, exer_char1 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char2_replace(exer_denv *env, 
				OSS_UINT16 **value, exer_char2 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char4_replace(exer_denv *env, 
				OSS_INT32 **value, exer_char4 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char1_preserve(exer_denv *env, 
				void *value, exer_char1 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char2_preserve(exer_denv *env, 
				OSS_UINT16 **value, exer_char2 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char4_preserve(exer_denv *env, 
				OSS_INT32 **value, exer_char4 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char1_64(exer_denv *env, 
				void *value, exer_char1 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char2_64(exer_denv *env, 
				OSS_UINT16 **value, exer_char2 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_char4_64(exer_denv *env, 
				OSS_INT32 **value, exer_char4 *ctx);
unsigned int 	DLL_ENTRY _oss_tdex_int(exer_denv *env, exer_int *ctx);
ULONG_LONG 	DLL_ENTRY _oss_tdex_int_ll(exer_denv *env, exer_int_ll *ctx);
ossBoolean 	DLL_ENTRY _oss_tdex_bool(exer_denv *env, exer_bool *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_int_huge(exer_denv *env,
				unsigned char **value, exer_int_huge *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_oct(exer_denv *env, 
				void *value, exer_oct *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_oct_64(exer_denv *env, 
				void  *value, exer_oct *ctx);
unsigned long	DLL_ENTRY _oss_tdex_otyp_64(exer_denv *env, 
				unsigned char **data, exer_otyp *ctx);
unsigned long	DLL_ENTRY _oss_tdex_otyp(exer_denv *env, 
				unsigned char **data, exer_otyp *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_bit(exer_denv  *env, 
				void *value, exer_bit *ctx);
unsigned int 	DLL_ENTRY _oss_tdex_enum(exer_denv  *env, exer_enum *ctx);
int 		DLL_ENTRY _oss_tdex_nil(exer_denv *env);
int 		DLL_ENTRY _oss_tdex_find_type(exer_denv *env, exer_name *qname);
void		DLL_ENTRY _oss_tdex_mark_type(exer_denv *env);
void		DLL_ENTRY _oss_tdex_error_type(exer_denv *env, exer_name *qname);
int 		DLL_ENTRY _oss_tlex_match_tag(exer_denv *env, 
				unsigned char *nm, unsigned long nm_len);
int 		DLL_ENTRY _oss_tlex_match_qtag(exer_denv *env, 
				unsigned char *uri, 
				unsigned char *nm, unsigned long nm_len);
int 		DLL_ENTRY _oss_tlex_match_wtag(exer_denv *env, 
				exer_wild_data *ctx);
void 		DLL_ENTRY _oss_tdex_match_tag_error(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_read_word(exer_denv *env, exer_name *name);
void 		DLL_ENTRY _oss_tlex_check_end(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_check_end_union(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_skip_ws(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_check_ws(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_free_attrs(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_store_input(exer_denv *env, 
				exer_save_lexeme *lex);
void 		DLL_ENTRY _oss_tlex_set_attr_input(exer_denv *env, 
				exer_attribute *attr);
void 		DLL_ENTRY _oss_tlex_restore_input(exer_denv *env, 
				exer_save_lexeme *lex);
void 		DLL_ENTRY _oss_tlex_set_embed(exer_denv *env,
				exer_embed *embed);
void 		DLL_ENTRY _oss_tlex_read_text(exer_denv *env,
				exer_name *name, OSS_UINT32 flags);
unsigned long 	DLL_ENTRY _oss_tlex_resolve_prefix(exer_denv *env, 
				exer_name *name);
unsigned long 	DLL_ENTRY _oss_tlex_copy_char1(exer_denv *env, 
				unsigned char **value,
				unsigned char *src, unsigned long src_length, 
				exer_char1 *ctx);
void 		DLL_ENTRY _oss_tlex_free_name(exer_denv *env);
OSS_UINT16 	DLL_ENTRY _oss_tlex_find_idx(exer_denv *env, exer_name *ename, 
				exer_tag_decoder *td);
OSS_UINT16 	DLL_ENTRY _oss_tlex_find_tag_idx(exer_denv *env, 
				exer_tag_decoder *td);
void 		DLL_ENTRY _oss_tlex_start_union(exer_denv *env, 
				exer_rescan *lex, unsigned long num);
void 		DLL_ENTRY _oss_tlex_retry_union(exer_denv *env, 
				exer_rescan *lex);
void 		DLL_ENTRY _oss_tlex_finish_union(exer_denv *env, 
				exer_rescan *lex);
int 		DLL_ENTRY _oss_tlex_wildcard_match(exer_denv *env, 
				unsigned char *uri, exer_wild_data *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_anyel(exer_denv *env, void *data, exer_char1 *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_anyattr(exer_denv *env, void *data,
				exer_attribute *attr, exer_char1 *ctx);
void		DLL_ENTRY _oss_tdex_time(exer_denv  *env, void *storage,
				exer_time *ctx);
unsigned long 	DLL_ENTRY _oss_tdex_oid_enc(exer_denv  *env, 
				void *value, exer_oid *ctx);
void		DLL_ENTRY _oss_tdex_oid_lnk(exer_denv  *env, 
				void **value, exer_oid *ctx);
unsigned short 	DLL_ENTRY _oss_tdex_oid(exer_denv  *env, 
				void *value, exer_oid *ctx);
float  		DLL_ENTRY _oss_tdex_real_float(exer_denv *env, exer_real *ctx);
double  	DLL_ENTRY _oss_tdex_real_double(exer_denv *env, exer_real *ctx);
char 	       *DLL_ENTRY _oss_tdex_real_char(exer_denv *env, exer_real *ctx);
enum MixedReal_kind DLL_ENTRY _oss_tdex_real_mixed(exer_denv *env, 
				_mixed_real_internal *data, exer_real *ctx);
void 		DLL_ENTRY _oss_tlex_skip_type(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_skip_content(exer_denv *env);
void 		DLL_ENTRY _oss_tlex_push_input(exer_denv *env, 
				exer_save_cc_lex *lex,
				unsigned char *enc, unsigned long len);
void 		DLL_ENTRY _oss_tlex_pop_input(exer_denv *env, 
				exer_save_cc_lex *lex);
void 		DLL_ENTRY _oss_tlex_mark_ext_attr(exer_denv *env);
void		DLL_ENTRY _oss_tdex_iso_time(exer_denv *env, 
				char **value, exer_iso_time *ctx);

void    	DLL_ENTRY _oss_teex_prolog(exer_eenv *env);
void		DLL_ENTRY _oss_teex_init_env(OssGlobal *world, exer_eenv *env);
void		DLL_ENTRY _oss_teex_append(exer_eenv *env, unsigned char *data,
				long num);
void		DLL_ENTRY _oss_teex_append_byte(exer_eenv *env,
				unsigned int byte);
char *		DLL_ENTRY _oss_teex_seal_tag(exer_eenv *env);
void		DLL_ENTRY _oss_teex_open_qtag(exer_eenv *env, exer_qname *qn,
				int right_bracket);
void		DLL_ENTRY _oss_teex_open_tag(exer_eenv *env,
				unsigned char *name, long name_len,
				int right_bracket);
void		DLL_ENTRY _oss_teex_close_qtag(exer_eenv *env, exer_qname *qn);
void		DLL_ENTRY _oss_teex_close_tag(exer_eenv *env,
				unsigned char *name, long name_len);
void		DLL_ENTRY _oss_teex_empty_qtag(exer_eenv *env, exer_qname *qn);
void		DLL_ENTRY _oss_teex_id_or_empty_tag(exer_eenv *env,
				unsigned char *name, unsigned int name_len);
void		DLL_ENTRY _oss_teex_end_tag(exer_eenv *env);
void		DLL_ENTRY _oss_teex_qattr_begin(exer_eenv *env, exer_qname *qn);
void		DLL_ENTRY _oss_teex_attr_begin(exer_eenv *env,
				unsigned char *name, long name_len);
void		DLL_ENTRY _oss_teex_indent(exer_eenv *env);
void		DLL_ENTRY _oss_teex_type_attr(exer_eenv *env,
			unsigned int control_idx,
			unsigned char *type_name,
				exer_qname *qn);
void		DLL_ENTRY _oss_teex_set_dns(exer_eenv *env,
				unsigned int ns_idx);
void		DLL_ENTRY _oss_teex_xmlns_attr(exer_eenv *env,
				unsigned int ns_idx);
void		DLL_ENTRY _oss_teex_nil_attr(exer_eenv *env,
				unsigned int control_idx);
void		DLL_ENTRY _oss_teex_set_embed(exer_eenv *env,
				teex_embed *embed, exer_embed_encoder enc);
void		DLL_ENTRY _oss_teex_chklst_char1(exer_eenv *env, 
				unsigned char *value, unsigned long length);
void 		DLL_ENTRY _oss_teex_char1_collapse(exer_eenv *env, 
				unsigned char *value, unsigned long length,
				exer_char1 *sdata);
void 		DLL_ENTRY _oss_teex_char1_replace(exer_eenv *env, 
				unsigned char *value, unsigned long length,
				exer_char1 *sdata);
void 		DLL_ENTRY _oss_teex_char1(exer_eenv *env, 
				unsigned char *value, unsigned long length,
				exer_char1 *sdata);
void		DLL_ENTRY _oss_teex_char2(exer_eenv *env, OSS_UINT16 *value,
				unsigned long length, exer_char2 *sdata);
void		DLL_ENTRY _oss_teex_char4(exer_eenv *env, OSS_INT32 *value,
				unsigned long length, exer_char4 *sdata);
void		DLL_ENTRY _oss_teex_char1_64(exer_eenv *env,
				unsigned char *value, unsigned long length,
				exer_char1 *sdata);
void		DLL_ENTRY _oss_teex_char2_64(exer_eenv *env,
				OSS_UINT16 *value, unsigned long length,
				exer_char2 *sdata);
void		DLL_ENTRY _oss_teex_char4_64(exer_eenv *env,
				OSS_INT32 *value, unsigned long length,
				exer_char4 *sdata);
void	DLL_ENTRY _oss_teex_char2_collapse(exer_eenv *env,
		OSS_UINT16 *value, unsigned long length, exer_char2 *sdata);
void	DLL_ENTRY _oss_teex_char2_replace(exer_eenv *env,
		OSS_UINT16 *value, unsigned long length, exer_char2 *sdata);
void	DLL_ENTRY _oss_teex_chklst_char2(exer_eenv *env,
		OSS_UINT16 *value, unsigned long length);
void	DLL_ENTRY _oss_teex_char4_collapse(exer_eenv *env,
		OSS_INT32 *value, unsigned long length, exer_char4 *sdata);
void	DLL_ENTRY _oss_teex_char4_replace(exer_eenv *env,
		OSS_INT32 *value, unsigned long length, exer_char4 *sdata);
void	DLL_ENTRY _oss_teex_chklst_char4(exer_eenv *env,
		OSS_INT32 *value, unsigned long length);
void		DLL_ENTRY _oss_teex_bool(exer_eenv *env, int value,
				exer_bool *sdata);
void		DLL_ENTRY _oss_teex_int(exer_eenv *env, unsigned int value,
				exer_int *sdata);
void		DLL_ENTRY _oss_teex_int_ll(exer_eenv *env, ULONG_LONG value,
				exer_int_ll *sdata);
void 		DLL_ENTRY _oss_teex_int_huge(exer_eenv *env,
				unsigned char *value, unsigned long length,
				exer_int_huge *sdata);
void		DLL_ENTRY _oss_teex_enum(exer_eenv *env, unsigned int value,
				exer_enum *sdata);
void		DLL_ENTRY _oss_teex_oct(exer_eenv *env, unsigned char *value,
				unsigned long length, exer_oct *sdata);
void		DLL_ENTRY _oss_teex_oct_64(exer_eenv *env,
				unsigned char *value, unsigned long length,
				exer_oct *sdata);
void		DLL_ENTRY _oss_teex_enc_base64_string(exer_eenv *env,
				unsigned char *value, unsigned long length);
void		DLL_ENTRY _oss_teex_bit(exer_eenv *env,  unsigned char *value,
				unsigned long bit_len, exer_bit *sdata);
void		DLL_ENTRY _oss_teex_bit_pad(exer_eenv *env,  OSS_UINT32 value,
					unsigned int bit_len, exer_bit *sdata);
unsigned int	DLL_ENTRY _oss_teex_check_uri(exer_eenv *env,
				unsigned char *value, unsigned int len);
void		DLL_ENTRY _oss_teex_check_attr(exer_eenv *env,
				unsigned char *uri, unsigned int uri_len,
				unsigned char *name, unsigned int name_len,
				int check);
void		DLL_ENTRY _oss_teex_error(exer_eenv *env,
				enum _err_index error_code,
				long num, char *data);
unsigned char *	DLL_ENTRY _oss_teex_qname_prefix(exer_eenv *env,
				unsigned char *value, size_t length,
				int *num);
void		DLL_ENTRY _oss_teex_qname_name(exer_eenv *env,
				unsigned char *value, size_t length,
				unsigned char *prefix, int num);
void		DLL_ENTRY _oss_teex_anyel(exer_eenv *env,
				unsigned char * value, unsigned long length,
				exer_wild_data *w_data);
void		DLL_ENTRY _oss_teex_anyattr(exer_eenv *env,
				unsigned char *value, unsigned long length,
				exer_wild_data *w_data);
void 		DLL_ENTRY _oss_teex_time(exer_eenv *env, void *data,
				exer_time *sdata);
void		DLL_ENTRY _oss_teex_time_nullt(exer_eenv *env, char *data,
				size_t inlen, exer_time *sdata);
void		DLL_ENTRY _oss_teex_iso_time(exer_eenv *env, char *data,
				exer_iso_time *sdata);
void		DLL_ENTRY _oss_teex_anyopentype(exer_eenv *env,
				unsigned char *data, long length);
void		DLL_ENTRY _oss_teex_otyp(exer_eenv *env, void *data,
				exer_otyp *sdata);
void		DLL_ENTRY _oss_teex_otyp_64(exer_eenv *env, void *data,
				exer_otyp *sdata);
void		DLL_ENTRY _oss_teex_oid_enc(exer_eenv *env, unsigned char *value,
				unsigned long length, exer_oid *sdata);
void		DLL_ENTRY _oss_teex_oid_unb_s(exer_eenv *env,
				unsigned short *value, unsigned long count,
				exer_oid *sdata);
void		DLL_ENTRY _oss_teex_oid_unb_i(exer_eenv *env,
				unsigned int *value, unsigned long count,
				exer_oid *sdata);
void		DLL_ENTRY _oss_teex_oid_unb_l(exer_eenv *env,
				unsigned long *value, unsigned long count,
				exer_oid *sdata);
void		DLL_ENTRY _oss_teex_oid_lnk_s(exer_eenv *env, void *value,
				exer_oid *sdata);
void		DLL_ENTRY _oss_teex_oid_lnk_i(exer_eenv *env, void *value,
				exer_oid *sdata);
void		DLL_ENTRY _oss_teex_oid_lnk_l(exer_eenv *env, void *value,
				exer_oid *sdata);
void		DLL_ENTRY _oss_teex_real_char(exer_eenv *env, char *value,
				exer_real *sdata);
void		DLL_ENTRY _oss_teex_real_decimal(exer_eenv *env,
				char *value, exer_real *sdata);
void		DLL_ENTRY _oss_teex_real_char_mod(exer_eenv *env,
				char *value, exer_real *sdata);
void		DLL_ENTRY _oss_teex_real_double(exer_eenv *env, double value,
				exer_real *sdata);
void		DLL_ENTRY _oss_teex_real_float(exer_eenv *env, float value,
				exer_real *sdata);
void		DLL_ENTRY _oss_teex_real_double_mod(exer_eenv *env, double value,
				exer_real *sdata);
void		DLL_ENTRY _oss_teex_real_float_mod(exer_eenv *env, float value,
				exer_real *sdata);
unsigned long	DLL_ENTRY _oss_teex_curr_enclen(exer_eenv *env);
void		DLL_ENTRY _oss_teex_db_e_pre(exer_eenv *env,int pdunum, void *input,
				char *bufpos, long buflen );
#endif /* OSS_TOED_EXER */

#ifdef OSS_TOED_OER
/*****************************************************************************/
/*  TOED OER section                                                         */
/*****************************************************************************/
/* TOED OER encoder definitions and declarations */
extern void DLL_ENTRY _oss_oenc_append_byte(OssGlobal *g, unsigned int byte);
extern void DLL_ENTRY _oss_oenc_append_2bytes(OssGlobal *g,
				unsigned int byte1, unsigned int byte2);
extern void DLL_ENTRY _oss_oenc_append_3bytes(OssGlobal *g,
				unsigned int byte1, unsigned int byte2,
				unsigned int byte3);
extern void DLL_ENTRY _oss_oenc_append_bytes(OssGlobal *g,
				unsigned char *field, unsigned long length);
extern int DLL_ENTRY _oss_oenc_enc_length(unsigned long value,
				unsigned char *buf);
extern void DLL_ENTRY _oss_oenc_not_supported(struct ossGlobal *g,
				void *value, char *detail);

/* OER Encoding of an BOOLEAN Value */
#define _oss_oenc_bool(g, v)		_oss_oenc_append_byte(g, v)

/* OER Encoding of an INTEGER value */
extern void DLL_ENTRY _oss_oenc_int_1byte(OssGlobal *g, int value);
extern void DLL_ENTRY _oss_oenc_int_2byte(OssGlobal *g, int value);
extern void DLL_ENTRY _oss_oenc_int_4byte(OssGlobal *g, OSS_INT32 value);
extern void DLL_ENTRY _oss_oenc_int(OssGlobal *g, long value);

#define _oss_oenc_int_ll_1byte(g, v)	_oss_oenc_append_byte(g, v)
#define _oss_oenc_int_ll_2byte(g, v)	_oss_oenc_int_2byte(g, (int)v)
#define _oss_oenc_int_ll_4byte(g, v)	_oss_oenc_int_4byte(g, (OSS_INT32)v)
extern void DLL_ENTRY _oss_oenc_int_ll(OssGlobal *g, LONG_LONG value);

extern void DLL_ENTRY _oss_oenc_uint_1byte(OssGlobal *g, unsigned int value);
extern void DLL_ENTRY _oss_oenc_uint_2byte(OssGlobal *g, unsigned int value);
extern void DLL_ENTRY _oss_oenc_uint_3byte(OssGlobal *g, OSS_UINT32 value);
extern void DLL_ENTRY _oss_oenc_uint_4byte(OssGlobal *g, OSS_UINT32 value);
extern void DLL_ENTRY _oss_oenc_uint(OssGlobal *g, unsigned long value);

#define _oss_oenc_uint_ll_1byte(g, v)	_oss_oenc_append_byte(g, v)
#define _oss_oenc_uint_ll_2byte(g, v)	_oss_oenc_uint_2byte(g, (unsigned int)v)
#define _oss_oenc_uint_ll_4byte(g, v)	_oss_oenc_uint_4byte(g, (OSS_UINT32)v)
extern void DLL_ENTRY _oss_oenc_uint_ll(OssGlobal *g, ULONG_LONG value);

extern void DLL_ENTRY _oss_oenc_int_h(struct ossGlobal *g,
				unsigned char *value, unsigned long length);
extern void DLL_ENTRY _oss_oenc_uint_h(struct ossGlobal *g,
				unsigned char *value, unsigned long length);

/* OER Encoding of an ENUMERATED Value */
extern void DLL_ENTRY _oss_oenc_enum(OssGlobal *g, long value);
extern void DLL_ENTRY _oss_oenc_uenum(OssGlobal *g, unsigned long value);

/* OER Encoding of an REAL Value 2.3.4 */
extern void DLL_ENTRY _oss_oenc_real(struct ossGlobal *g,
				double value);
extern void DLL_ENTRY _oss_oenc_real_decimal(struct ossGlobal *g,
			        char *value);

/* OER Encoding of a BIT STRING Value 2.3.5 */
extern void DLL_ENTRY _oss_oenc_bit_unbounded(struct ossGlobal *g,
				unsigned char *value, unsigned long length);
extern void DLL_ENTRY _oss_oenc_bit_unbounded_fixed(struct ossGlobal *g,
				unsigned char *value, unsigned long length,
				unsigned long new_length);
extern void DLL_ENTRY _oss_oenc_bit_padded(struct ossGlobal *g,
			    	void *data, unsigned long length);

/* OER Encoding of an OCTET STRING Value 2.3.6 */
extern void DLL_ENTRY _oss_oenc_octet_length(OssGlobal *g,
				unsigned long value);

/* OER Encoding of a NULL Value 2.3.7 */
/* OER Encoding of a SEQUENCE/EMBEDDED-PDV/UNRESTRICTED CHARACTER STRING Value 2.3.8, 2.3.14, 2.3.16 */
extern void DLL_ENTRY _oss_oenc_begin_ext(struct ossGlobal *g,
				struct ossExtStackElement *st);
extern unsigned long DLL_ENTRY _oss_oenc_end_ext(struct ossGlobal *g,
				struct ossExtStackElement *st);
extern void DLL_ENTRY _oss_oenc_store_encpos(struct ossGlobal *g,
				struct ossExtStackElement *st);
extern unsigned long DLL_ENTRY _oss_oenc_calc_enclen(struct ossGlobal *g,
				struct ossExtStackElement *st);

/* OER Encoding of the SEQUENCE/SET OF Type 2.3.9, 2.3.11 */
extern void DLL_ENTRY _oss_oenc_rsf_ext_bitmask(struct ossGlobal *g,
				unsigned char *val_ex, unsigned long len_ex,
				unsigned char *val_rs, unsigned long len_rs);
/* OER Encoding of the SET Type 2.3.10 */
/* OER Encoding of the CHOICE Type 2.3.12 */
extern void DLL_ENTRY _oss_oenc_rsf_ext(OssGlobal *g,
				OSS_UINT32 tag, unsigned long length,
				unsigned char *value);
/* OER Encoding of the OBJECT IDENTIFIER (OID) Type 2.3.13 */
extern void DLL_ENTRY _oss_oenc_oid_array_s(struct ossGlobal *g,
				unsigned short *value, unsigned int count);
extern void DLL_ENTRY _oss_oenc_oid_array_i(struct ossGlobal *g,
				unsigned int *value, unsigned int count);
extern void DLL_ENTRY _oss_oenc_oid_array_l(struct ossGlobal *g,
				unsigned long *value, unsigned int count);
extern void DLL_ENTRY _oss_oenc_oid_linked_s(struct ossGlobal *g,
				void *value, unsigned int offset);
extern void DLL_ENTRY _oss_oenc_oid_linked_i(struct ossGlobal *g,
				void *value, unsigned int offset);
extern void DLL_ENTRY _oss_oenc_oid_linked_l(struct ossGlobal *g,
				void *value, unsigned int offset);
extern void DLL_ENTRY _oss_oenc_oid_unbounded_s(struct ossGlobal *g,
				unsigned short *value, unsigned int count);
extern void DLL_ENTRY _oss_oenc_oid_unbounded_i(struct ossGlobal *g,
				unsigned int *value, unsigned int count);
extern void DLL_ENTRY _oss_oenc_oid_unbounded_l(struct ossGlobal *g,
				unsigned long *value, unsigned int count);

/* OER Encoding of the RESTRICTED CHARACTER STRING Types 2.3.15 */
extern void DLL_ENTRY _oss_oenc_bmpstr(struct ossGlobal *g,
		unsigned short *value, unsigned long length);
extern void DLL_ENTRY _oss_oenc_unistr(struct ossGlobal *g,
		OSS_INT32 *value, unsigned long length);
extern void DLL_ENTRY _oss_oenc_utf8_string_bmp(OssGlobal *g,
		unsigned short *value, unsigned long length);
extern void DLL_ENTRY _oss_oenc_utf8_string_universal(OssGlobal *g,
		OSS_INT32 *value, unsigned long length);

/* OER Encoding of the UTCTime/GeneralizedTime Types */
extern void DLL_ENTRY _oss_oenc_utime(struct ossGlobal *g,
		UTCTime *data);
extern void DLL_ENTRY _oss_oenc_gtime(struct ossGlobal *g,
		GeneralizedTime *data);

/* OER Encoding of the TIME Type */
extern char * DLL_ENTRY _oss_oenc_t_hours(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_minutes(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_daytime(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_duration_interval(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_hours_diff(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_daytime_diff(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_minutes_diff(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_daytime_fraction(OssGlobal *g, char *data,
			unsigned int accuracy);
extern char * DLL_ENTRY _oss_oenc_t_daytime_diff_fraction(OssGlobal *g,
			char *data, unsigned int accuracy);
extern char * DLL_ENTRY _oss_oenc_t_date(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_year_month(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_year(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_any_year(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_any_year_month(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_oenc_t_any_date(OssGlobal *g, char *data);
extern void   DLL_ENTRY _oss_oenc_nlltrm_date_time(OssGlobal *g, char *data);
extern void   DLL_ENTRY _oss_oenc_int_8byte(OssGlobal *g, OSS_INT64 value);
extern void   DLL_ENTRY _oss_oenc_uint_8byte(OssGlobal *g, OSS_UINT64 value);
extern void   DLL_ENTRY _oss_oenc_real_4byte(OssGlobal *g, float value);
extern void   DLL_ENTRY _oss_oenc_real_8byte(OssGlobal *g, double value);
extern void   DLL_ENTRY _oss_oenc_real_4decimal(struct ossGlobal *g, char *value);
extern void   DLL_ENTRY _oss_oenc_real_8decimal(struct ossGlobal *g, char *value);

#define _oss_oenc_t_utc(g, data, in) \
   ((*(data = in) == 'Z') ? data + 1 : (_oss_enc_error(g, _bad_time, 0L), data))
#define _oss_oenc_t_hours_utc(g, data) \
	_oss_oenc_t_utc(g, data, _oss_oenc_t_hours(g, data))
#define _oss_oenc_t_minutes_utc(g, data) \
	_oss_oenc_t_utc(g, data, _oss_oenc_t_minutes(g, data))
#define _oss_oenc_t_daytime_utc(g, data) \
	_oss_oenc_t_utc(g, data, _oss_oenc_t_daytime(g, data))
#define _oss_oenc_t_daytime_utc_fraction(g, data, accuracy) \
	_oss_oenc_t_utc(g, data, _oss_oenc_t_daytime_fraction(g, data, accuracy))

/* TOED OER decoder definitions and declarations */
extern void DLL_ENTRY _oss_checkUtf8String(OssGlobal *g,
			unsigned char *str, unsigned long length);
extern void DLL_ENTRY _oss_checkUtf8String_nlltrm(OssGlobal *g,
				    unsigned char *str);

extern unsigned int DLL_ENTRY _oss_odec_length(OssGlobal *g);
extern void DLL_ENTRY _oss_odec_read_octets(OssGlobal *g,
				char *value, unsigned int length);
extern void DLL_ENTRY _oss_odec_check_bytes(OssGlobal *g,
				char *start, unsigned int length);
extern void DLL_ENTRY _oss_odec_check_eapb(OssGlobal *g,
				unsigned char *bitmap, unsigned int length);
extern void DLL_ENTRY _oss_odec_not_supported(struct ossGlobal *g,
				void **value, char *detail);

/* OER Decoding of an INTEGER value */
extern int DLL_ENTRY _oss_odec_int_1byte(OssGlobal *g);
extern int DLL_ENTRY _oss_odec_int_2byte(OssGlobal *g);
extern OSS_INT32 DLL_ENTRY _oss_odec_int_4byte(OssGlobal *g);
extern short DLL_ENTRY _oss_odec_int_s(OssGlobal *g);
extern int DLL_ENTRY _oss_odec_int(OssGlobal *g);
extern LONG_LONG DLL_ENTRY _oss_odec_int_ll(OssGlobal *g);
extern unsigned int DLL_ENTRY _oss_odec_uint_1byte(OssGlobal *g);
extern unsigned int DLL_ENTRY _oss_odec_uint_2byte(OssGlobal *g);
extern unsigned int DLL_ENTRY _oss_odec_uint_3byte(OssGlobal *g);
extern OSS_UINT32 DLL_ENTRY _oss_odec_uint_4byte(OssGlobal *g);
extern unsigned int DLL_ENTRY _oss_odec_uint(OssGlobal *g);
extern unsigned short DLL_ENTRY _oss_odec_uint_s(OssGlobal *g);
extern ULONG_LONG DLL_ENTRY _oss_odec_uint_ll(OssGlobal *g);
extern unsigned int DLL_ENTRY _oss_odec_int_h(OssGlobal *g,
		    unsigned char **value, unsigned int size);
extern unsigned int DLL_ENTRY _oss_odec_uint_h(OssGlobal *g,
		    unsigned char **value, unsigned int size);

/* OER Decoding of an ENUMERATED Value */
extern int DLL_ENTRY _oss_odec_enum(OssGlobal *g);
extern unsigned int DLL_ENTRY _oss_odec_uenum(OssGlobal *g);
extern unsigned int DLL_ENTRY _oss_odec_tag(OssGlobal *g);

/* OER Decoding of an REAL Value 2.3.4 */
extern float DLL_ENTRY _oss_odec_real_float(OssGlobal *g);
extern double DLL_ENTRY _oss_odec_real_double(OssGlobal *g);
extern char * DLL_ENTRY _oss_odec_real_decimal(OssGlobal *g);
extern enum MixedReal_kind DLL_ENTRY _oss_odec_real_mixed(OssGlobal *g,
				void *data);

/* OER Decoding of a BIT STRING Value 2.3.5 */
/* all fixed size bit string - will be generated by ASN.1 compiler */
extern unsigned int DLL_ENTRY _oss_odec_bit_unbounded(OssGlobal *g,
				unsigned char **value);
extern unsigned int DLL_ENTRY _oss_odec_named_bit_unbounded(OssGlobal *g,
				unsigned char **value, unsigned int size_c);
/* For PADDED representation memset() will be generated by ASN.1 compiler */
extern unsigned int DLL_ENTRY _oss_odec_bit_padded(OssGlobal *g,
				unsigned int size_c);
extern unsigned int DLL_ENTRY _oss_odec_named_bit_padded(OssGlobal *g,
				unsigned int size_c);
extern void DLL_ENTRY _oss_odec_bit_big_padded(OssGlobal *g,
				unsigned char *value, unsigned int size_c);
extern void DLL_ENTRY _oss_odec_named_bit_big_padded(OssGlobal *g,
				unsigned char *value, unsigned int size_c);
extern unsigned int DLL_ENTRY _oss_odec_named_bit_varying(OssGlobal *g,
				unsigned char *value, unsigned int size_c);
extern unsigned int DLL_ENTRY _oss_odec_named_bit_varying_ptr(OssGlobal *g,
				unsigned char **value, unsigned int offset,
				unsigned int size_c);
extern unsigned int DLL_ENTRY _oss_odec_bits_by_len(OssGlobal *g,
				unsigned char *value, unsigned int length);

extern ossBoolean DLL_ENTRY _oss_odec_skip_unknown(OssGlobal *g,
				unsigned char *ext, unsigned long count,
				unsigned long ea_num);

/* OER Decoding of the OBJECT IDENTIFIER (OID) Type 2.3.13 */
extern unsigned short DLL_ENTRY _oss_odec_oid_encoded(OssGlobal *g,
				unsigned char *value, unsigned int size_c);
#define  _oss_odec_roid_encoded(g, v, s)	_oss_odec_oid_encoded(g, v, s)
extern void DLL_ENTRY _oss_odec_oid_linked_s(OssGlobal *g, void **value,
				unsigned int size_c);
extern void DLL_ENTRY _oss_odec_oid_linked_i(OssGlobal *g, void **value,
				unsigned int size_c);
extern void DLL_ENTRY _oss_odec_oid_linked_l(OssGlobal *g, void **value,
				unsigned int size_c);
extern unsigned short DLL_ENTRY _oss_odec_oid_unbounded_s(OssGlobal *g,
				unsigned short **value);
extern unsigned short DLL_ENTRY _oss_odec_oid_unbounded_i(OssGlobal *g,
				unsigned int **value);
extern unsigned short DLL_ENTRY _oss_odec_oid_unbounded_l(OssGlobal *g,
				unsigned long **value);
extern unsigned short DLL_ENTRY _oss_odec_oid_array_s(OssGlobal *g,
		    unsigned short *value, unsigned int size_c);
extern unsigned short DLL_ENTRY _oss_odec_oid_array_i(OssGlobal *g,
		    unsigned int *value, unsigned int size_c);
extern unsigned short DLL_ENTRY _oss_odec_oid_array_l(OssGlobal *g,
		    unsigned long *value, unsigned int size_c);
extern void * DLL_ENTRY _oss_odec_oid_array_s_ptr(OssGlobal *g,
		    unsigned int offset);
extern void * DLL_ENTRY _oss_odec_oid_array_i_ptr(OssGlobal *g,
		    unsigned int offset);
extern void * DLL_ENTRY _oss_odec_oid_array_l_ptr(OssGlobal *g,
		    unsigned int offset);

/* OER Decoding of the RESTRICTED CHARACTER STRING Types 2.3.15 */
extern unsigned int DLL_ENTRY _oss_odec_string_unbounded(OssGlobal *g,
					char **value);
extern void DLL_ENTRY _oss_odec_string_padded(OssGlobal *g,
					char *value, unsigned int size_c);
extern unsigned int DLL_ENTRY _oss_odec_bmp_string(OssGlobal *g,
			unsigned short **value);
extern void DLL_ENTRY _oss_odec_fixed_bmp_string(OssGlobal *g,
			unsigned short *value, unsigned int size_c);
extern unsigned int DLL_ENTRY _oss_odec_universal_string(OssGlobal *g,
			int **value);
extern void DLL_ENTRY _oss_odec_fixed_universal_string(OssGlobal *g,
			int *value, unsigned int size_c);
extern unsigned int DLL_ENTRY _oss_odec_utf8_string_bmp(OssGlobal *g,
			unsigned short **value);
extern unsigned int DLL_ENTRY _oss_odec_utf8_string_universal(OssGlobal *g,
			int **value);
extern void DLL_ENTRY _oss_odec_gtime(struct ossGlobal *g,
			GeneralizedTime *value);
extern void DLL_ENTRY _oss_odec_utime(struct ossGlobal *g, UTCTime *value);

extern char * DLL_ENTRY _oss_odec_t_hours(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_minutes(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_daytime(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_duration_interval(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_hours_diff(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_daytime_diff(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_minutes_diff(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_daytime_fraction(OssGlobal *g, char *data,
			unsigned int accuracy);
extern char * DLL_ENTRY _oss_odec_t_daytime_diff_fraction(OssGlobal *g,
			char *data, unsigned int accuracy);
extern char * DLL_ENTRY _oss_odec_t_date(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_year_month(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_year(OssGlobal *g, char *data);
extern char * DLL_ENTRY _oss_odec_t_any_year(OssGlobal *g, char *data,
			unsigned int max_d_num);
extern char * DLL_ENTRY _oss_odec_t_any_year_month(OssGlobal *g, char *data,
			unsigned int max_d_num);
extern char * DLL_ENTRY _oss_odec_t_any_date(OssGlobal *g, char *data,
			unsigned int max_d_num);
extern OSS_INT64  DLL_ENTRY _oss_odec_int_8byte(OssGlobal *g);
extern OSS_UINT64 DLL_ENTRY _oss_odec_uint_8byte(OssGlobal *g);
extern float  DLL_ENTRY _oss_odec_real_4byte(OssGlobal *g);
extern double DLL_ENTRY _oss_odec_real_8byte(OssGlobal *g);
extern char * DLL_ENTRY _oss_odec_real_4decimal(OssGlobal *g);
extern char * DLL_ENTRY _oss_odec_real_8decimal(OssGlobal *g);
extern unsigned char DLL_ENTRY _oss_odec_bool(OssGlobal *g);

#define _oss_odec_t_utc(data, in) (*(data = in) = 'Z', data + 1)
#define _oss_odec_t_hours_utc(g, data) \
	_oss_odec_t_utc(data, _oss_odec_t_hours(g, data))
#define _oss_odec_t_minutes_utc(g, data) \
	_oss_odec_t_utc(data, _oss_odec_t_minutes(g, data))
#define _oss_odec_t_daytime_utc(g, data) \
	_oss_odec_t_utc(data, _oss_odec_t_daytime(g, data))
#define _oss_odec_t_daytime_utc_fraction(g, data, accuracy) \
	_oss_odec_t_utc(data, _oss_odec_t_daytime_fraction(g, data, accuracy))

#define USE_OUTBUF_LEN
#define USE_INBUF_LEN
#ifndef USE_OUTBUF_LEN
#define OSS_outbuf_getlen(_oss_c) 	((long)((char *)_oss_c->_oss_inbufpos - _oss_c->_oss_outbufpos))
#else
#define OSS_outbuf_getlen(_oss_c) 	_oss_c->_oss_outbuflen
#endif
#ifndef USE_INBUF_LEN
#define OSS_inbuf_advance(_oss_c, len)
#define OSS_inbuf_overrun(_oss_c, len)	(_oss_c->_oss_inbufpos + (len) > (char *)_oss_c->_blockptr)
#define OSS_inbuf_getlen(_oss_c) 	((unsigned int)((char *)_oss_c->_blockptr - _oss_c->_oss_inbufpos))
#define OSS_inbuf_setend(_oss_c, len)	_oss_c->_blockptr = (void *)(_oss_c->_oss_inbufpos + (len))
#else
#define OSS_inbuf_advance(_oss_c, len)	_oss_c->_oss_inbuflen -= (len)
#define OSS_inbuf_overrun(_oss_c, len)	((len) > _oss_c->_oss_inbuflen)
#define OSS_inbuf_getlen(_oss_c) 	(unsigned int)_oss_c->_oss_inbuflen
#define OSS_inbuf_setend(_oss_c, len)	_oss_c->_oss_inbuflen = ((long)len)
#endif
#endif /* OSS_TOED_OER */

#else /* _OSS_CODE_FILE */

/*****************************************************************************/
/*  SOED general section                                                     */
/*****************************************************************************/


#ifndef OSS_SPARTAN_AWARE
#define OSS_SPARTAN_AWARE 23
#endif
typedef unsigned short Etag;
typedef struct efield *_oss_qqq;
typedef struct etype *_oss_jHq;
typedef struct eheader *Eheader;
struct etype {
    long            max_length;
    size_t          _oss_QJq;
    size_t          _oss_QHQJ;
    char           *_oss_WWj;
    size_t          _oss_WJq;
    size_t          _oss_wJJJ;
    unsigned short int _oss_qwJJ;
    unsigned short int _oss_WjQJ;
    unsigned short int _oss_QqQJ;
    unsigned short int _oss_HJJJ;
    int                _oss_Hwj;	    
    unsigned short int _oss_Hwq;
};
struct efield {
    size_t          _oss_wqq;	
    unsigned short int _oss_Qwj;	
    short int       _oss_jwQJ;	
    unsigned short int _oss_qQQJ;	
    unsigned char   _oss_wHQJ;	
};
struct ConstraintEntry {
    char            _oss_wHJJ;
    char            _oss_WHJJ;
    void           *_oss_HJq;
};
struct InnerSubtypeEntry {
    char		_oss_JQQJ;
    unsigned char	_oss_jJj;
    unsigned short	_oss_wQq;	     
    unsigned short	_oss_HJq;  
};
struct eValRef {
    char           *_oss_WWj;
    const void     *_oss_qWq;
    unsigned short  _oss_Qwj;	
};
typedef struct OSetTableEntry {
    void		*_oss_qWq;
    unsigned short	_oss_Qwj;
    void		*_oss_qJJJ;
    unsigned short	_oss_HJQJ;
    char		*_oss_WQJJ;
    int			_oss_HHJJ;
    int			_oss_WJJJ;
} OSetTableEntry;
typedef struct WideAlphabet {
    OSS_UINT32  _oss_wqq; 
    struct {
	short _oss_qWQJ;   
	const char  *_oss_JQq;   
    } _oss_HQQJ;
    void *        _oss_qHJJ; 
} WideAlphabet;
typedef struct eda_table {
    unsigned int _oss_JWq;
    unsigned char *_oss_jJj;
} eda_table;
typedef struct midRelation {
    unsigned short _oss_HqQJ;
    unsigned short _oss_QwJJ;
    unsigned short _oss_JqJJ;
    unsigned short _oss_jQJJ;
} MidRelation;
struct eheader {
    void (DLL_ENTRY_FPTR *_System _oss_WwQJ)(struct ossGlobal *); 
    long            pdudecoder;	
    unsigned short int _oss_JWq;	
    unsigned short int _oss_jJj;	
    unsigned short int _oss_qJQJ,
                    _oss_JJJJ;	
    unsigned short *pduarray;	
    _oss_jHq           etypes;	
    _oss_qqq          _oss_wjQJ;	
    void          **_oss_QjJJ;	
    unsigned short *_oss_QJq;	
    struct ConstraintEntry *_oss_Hwq;
    struct InnerSubtypeEntry *_oss_HHQJ;	
    void           *_oss_WqQJ;	
    unsigned short int _oss_jHQJ; 
    void           *_oss_QqJJ;
    unsigned short  _oss_qwQJ;
};


    /*************************************************************************/
    /*      SOED general functions section                                   */
    /*************************************************************************/

PUBLIC void DLL_ENTRY ossLinkConstraint(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossEDLinkPer(struct ossGlobal *world, void *eda_table);
PUBLIC void DLL_ENTRY ossLinkSAX(struct ossGlobal *world, void *exer_table, 
	void *sax_data);
PUBLIC void DLL_ENTRY ossLinkSAXParser(struct ossGlobal *world);
PUBLIC void DLL_ENTRY ossLinkUserConstraint(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkPrintPer(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkPerPDV(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossInitObjectSetInfo(struct ossGlobal *,
					    unsigned short *);
PUBLIC void DLL_ENTRY ossLinkUserConstraintSpartanAware8(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossSetExtParms(struct ossGlobal *world, void  *arg);
PUBLIC void DLL_ENTRY ossLinkConstraintSpartanAware8(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkCmpValue(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkCpyValue(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkZlib(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkPropertySettingsConstraint(struct ossGlobal *,
					    unsigned int *);

PUBLIC void DLL_ENTRY ossInitPrintFunctions(struct ossGlobal *, void *);
PUBLIC void DLL_ENTRY ossInitUserFunctions(struct ossGlobal *, void *);

PUBLIC void DLL_ENTRY ossLinkBerReal(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkConstraintReal(struct ossGlobal *);
PUBLIC void DLL_ENTRY ossLinkPatternConstraint(struct ossGlobal *);
extern short DLL_ENTRY _oss_str2gtime(unsigned char *p, size_t *len, void* tm, char utc);

#ifdef OSS_SOED_BER
/*****************************************************************************/
/*  SOED BER section                                                         */
/*****************************************************************************/
    /*************************************************************************/
    /*      SOED BER functions section                                       */
    /*************************************************************************/

PUBLIC void DLL_ENTRY ossLinkCer(struct ossGlobal *);

#endif /* OSS_SOED_BER */

#ifdef OSS_SOED_PER
/*****************************************************************************/
/*  SOED PER section                                                         */
/*****************************************************************************/
    /*************************************************************************/
    /*      SOED PER functions section                                       */
    /*************************************************************************/

PUBLIC void DLL_ENTRY ossLinkPerReal(struct ossGlobal *);

	/********************************************************************/
	/*      SOED PER time functions section                             */
	/********************************************************************/

typedef void (CDECL_ENTRY_FPTR *ossPERTimeEncodefp)(struct ossGlobal  *);
typedef void (CDECL_ENTRY_FPTR *ossPERTimeDecodefp)(struct ossGlobal  *);

 
/* ossLink_[E|D]PERTime routines should never be used with DLLs */
PUBLIC void DLL_ENTRY ossLink_EPerTime (struct ossGlobal *,
 	unsigned short , int const * , ossPERTimeEncodefp *);
PUBLIC void DLL_ENTRY ossLink_DPerTime (struct ossGlobal *,
 	unsigned short , int const * , ossPERTimeDecodefp *);

#ifdef __vms
#define _oss_ept_rec_duration_end_date_time_interval _oss_ept_rec_duration_end_dt_time_interval
#define _oss_dpt_rec_duration_end_date_time_interval _oss_dpt_rec_duration_end_dt_time_interval
#endif

/* ************************************************************* *
 * PER TIME Encoding functions:				         *
 * ************************************************************* */
extern void CDECL_ENTRY _oss_ept_century(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_any_century(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_year(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_any_year(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_year_month(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_any_year_month(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_date(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_any_date(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_year_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_any_year_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_year_week(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_any_year_week(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_year_week_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_any_year_week_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_hours(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_hours_utc(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_hours_and_diff(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_minutes(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_minutes_utc(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_minutes_and_diff(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_minutes_and_diff_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_time_of_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_time_of_day_utc(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_time_of_day_and_diff(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_hours_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_hours_utc_and_fraction(OssGlobal *world);
extern void CDECL_ENTRY _oss_ept_hours_and_diff_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_minutes_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_minutes_utc_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_time_of_day_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_time_of_day_utc_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_time_of_day_and_diff_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_date_time(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_start_end_date_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_start_end_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_start_end_date_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_start_date_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_start_time_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_start_date_time_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_duration_end_date_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_duration_end_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_duration_end_date_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_rec_start_end_date_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_rec_start_end_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_rec_start_end_date_time_interval(struct ossGlobal *);
extern void CDECL_ENTRY _oss_ept_rec_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_rec_start_date_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_rec_start_time_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_rec_start_date_time_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_rec_duration_end_date_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_rec_duration_end_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_rec_duration_end_date_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_mixed(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_ept_not_supported (struct ossGlobal  *);

/* ************************************************************* *
 * PER TIME decoding functions:					 *
 * ************************************************************* */
extern void CDECL_ENTRY _oss_dpt_century(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_any_century(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_year(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_any_year(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_year_month(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_any_year_month(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_date(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_any_date(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_year_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_any_year_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_year_week(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_any_year_week(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_year_week_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_any_year_week_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_hours(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_hours_utc(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_hours_and_diff(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_minutes(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_minutes_utc(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_minutes_and_diff(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_minutes_and_diff_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_time_of_day(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_time_of_day_utc(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_time_of_day_and_diff(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_hours_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_hours_utc_and_fraction(OssGlobal *world);
extern void CDECL_ENTRY _oss_dpt_hours_and_diff_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_minutes_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_minutes_utc_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_time_of_day_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_time_of_day_utc_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_time_of_day_and_diff_and_fraction(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_date_time(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_start_end_date_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_start_end_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_start_end_date_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_start_date_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_start_time_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_start_date_time_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_duration_end_date_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_duration_end_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_duration_end_date_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_rec_start_end_date_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_rec_start_end_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_rec_start_end_date_time_interval(struct ossGlobal *);
extern void CDECL_ENTRY _oss_dpt_rec_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_rec_start_date_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_rec_start_time_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_rec_start_date_time_duration_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_rec_duration_end_date_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_rec_duration_end_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_rec_duration_end_date_time_interval(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_mixed(struct ossGlobal  *);
extern void CDECL_ENTRY _oss_dpt_not_supported (struct ossGlobal  *);

#endif /* OSS_SOED_PER */


#if defined(OSS_SOED_XER)
/*****************************************************************************/
/*  SOED XER section                                                         */
/*****************************************************************************/
#ifndef OSS_VOIDE
#define OSS_VOIDE void
#endif
#ifndef OSS_VOIDD
#define OSS_VOIDD void
#endif

    /*************************************************************************/
    /*      SOED XER functions section                                       */
    /*************************************************************************/

typedef void	(CDECL_ENTRY_FPTR * ossXERencodefp)(void *);
typedef void	(CDECL_ENTRY_FPTR * ossXERdecodefp)(void *);

/* DLL-related functions defined at xerfp.c; also used for ASN1Step */

/* ossLink[E|D]Xer routines should never be used with DLLs */
PUBLIC void DLL_ENTRY ossLinkEXer (OssGlobal *, unsigned short,
					int const *, ossXERencodefp *);
PUBLIC void DLL_ENTRY ossLinkDXer (OssGlobal *, unsigned short,
					int const *, ossXERdecodefp *);
PUBLIC void DLL_ENTRY ossLinkXerReal(OssGlobal *);
/* In contrast, ossLinkXer handles DLL SOED XER linkage */
PUBLIC void DLL_ENTRY ossLinkXer (OssGlobal *);
#endif /* (OSS_SOED_XER || !SHIPPING) && !OSS_XSD */

#if defined(OSS_SOED_XER)
/* ************************************************************* *
 * Encoding functions:						 *
 * ************************************************************* */
extern void CDECL_ENTRY		_oss_ex_int (OSS_VOIDE * ctx);
#define _oss_ex_uint		_oss_ex_int
extern void CDECL_ENTRY		_oss_ex_enum (OSS_VOIDE * ctx);
#define _oss_ex_uenum		_oss_ex_enum
extern void CDECL_ENTRY		_oss_ex_pad_bit (OSS_VOIDE * ctx);
#define _oss_ex_big_pad_bit	_oss_ex_pad_bit
extern void CDECL_ENTRY		_oss_ex_unbnd_bit (OSS_VOIDE * ctx);
#define _oss_ex_vary_bit	_oss_ex_unbnd_bit
/* there is no separate encoding function for NULL type */
#define _oss_ex_null		_oss_ex_not_supported
extern void CDECL_ENTRY		_oss_ex_real (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_char_real (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_mixed_real (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_bool (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_unbnd_any (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_seq (OSS_VOIDE * ctx);
#define _oss_ex_set		_oss_ex_seq
#define _oss_ex_embedded_pdv	_oss_ex_seq
#define _oss_ex_char_string	_oss_ex_seq
extern void CDECL_ENTRY		_oss_ex_choice (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_link_seqof (OSS_VOIDE * ctx);
#define _oss_ex_link_setof	_oss_ex_link_seqof
extern void CDECL_ENTRY		_oss_ex_dlink_seqof (OSS_VOIDE * ctx);
#define _oss_ex_dlink_setof	_oss_ex_dlink_seqof
#define _oss_ex_dlink_plus_seqof _oss_ex_link_seqof
#define _oss_ex_dlink_plus_setof _oss_ex_dlink_plus_seqof
extern void CDECL_ENTRY		_oss_ex_unbnd_seqof (OSS_VOIDE * ctx);
#define _oss_ex_unbnd_setof	_oss_ex_unbnd_seqof
#define _oss_ex_array_seqof	_oss_ex_unbnd_seqof
#define _oss_ex_array_setof	_oss_ex_unbnd_seqof
extern void CDECL_ENTRY		_oss_ex_unbnd_octet (OSS_VOIDE * ctx);
#define _oss_ex_vary_octet	_oss_ex_unbnd_octet
extern void CDECL_ENTRY         _oss_ex_fixed_octet (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_ex_unbnd_char (OSS_VOIDE * ctx);
#define _oss_ex_vary_char	_oss_ex_unbnd_char
extern void CDECL_ENTRY         _oss_ex_nlltrm_char (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_pad_char (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_link_objid (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_unbnd_objid (OSS_VOIDE * ctx);
#define _oss_ex_array_objid	_oss_ex_unbnd_objid
extern void CDECL_ENTRY		_oss_ex_utc_time (OSS_VOIDE * ctx);
#define _oss_ex_gen_time	_oss_ex_utc_time
extern void CDECL_ENTRY		_oss_ex_opentype (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_4byte_char (OSS_VOIDE * ctx);
#define _oss_ex_2byte_char	_oss_ex_4byte_char
extern void CDECL_ENTRY		_oss_ex_huge_int (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_ex_encoded_objid (OSS_VOIDE * ctx);
#define _oss_ex_encoded_reloid	_oss_ex_encoded_objid
extern void CDECL_ENTRY		_oss_ex_defer (OSS_VOIDE * ctx);
#define _oss_ex_defer_obj	_oss_ex_defer
extern void CDECL_ENTRY		_oss_ex_containing (OSS_VOIDE * ctx);
extern void CDECL_ENTRY 	_oss_ex_not_supported (OSS_VOIDE * ctx);

#define _oss_ex_nlltrm_date_time	_oss_ex_nlltrm_char

/* No support for the below C representations */
#define _oss_ex_vary_any		_oss_ex_not_supported
#define _oss_ex_unbnd_link_octet	_oss_ex_not_supported
#define _oss_ex_vary_link_octet		_oss_ex_not_supported
#define _oss_ex_unbnd_link_bit		_oss_ex_not_supported
#define _oss_ex_vary_link_bit		_oss_ex_not_supported
#define _oss_ex_vary_link_char		_oss_ex_not_supported
#define _oss_ex_nlltrm_link_char	_oss_ex_not_supported
#define _oss_ex_unbnd_link_char		_oss_ex_not_supported
#define _oss_ex_unbnd_dlink_octet	_oss_ex_not_supported
#define _oss_ex_vary_dlink_octet	_oss_ex_not_supported
#define _oss_ex_unbnd_dlink_bit		_oss_ex_not_supported
#define _oss_ex_vary_dlink_bit		_oss_ex_not_supported
#define _oss_ex_vary_dlink_char		_oss_ex_not_supported
#define _oss_ex_nlltrm_dlink_char	_oss_ex_not_supported
#define _oss_ex_unbnd_dlink_char	_oss_ex_not_supported
#define _oss_ex_unbnd_link_any		_oss_ex_not_supported
#define _oss_ex_unbnd_dlink_any		_oss_ex_not_supported
#define _oss_ex_one_char		_oss_ex_not_supported

/* ************************************************************* *
 * Decoding functions:						 *
 * ************************************************************* */
extern void CDECL_ENTRY		_oss_dx_int (OSS_VOIDD * ctx);
#define _oss_dx_uint		_oss_dx_int
extern void CDECL_ENTRY		_oss_dx_enum (OSS_VOIDD * ctx);
#define _oss_dx_uenum		_oss_dx_enum
extern void CDECL_ENTRY		_oss_dx_unbnd_bit (OSS_VOIDD * ctx);
#define _oss_dx_vary_bit	_oss_dx_unbnd_bit
#define _oss_dx_pad_bit		_oss_dx_unbnd_bit
#define _oss_dx_big_pad_bit	_oss_dx_unbnd_bit
#define _oss_dx_unbnd_octet	_oss_dx_unbnd_bit
#define _oss_dx_vary_octet	_oss_dx_unbnd_bit
extern void CDECL_ENTRY         _oss_dx_fixed_octet (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_null (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_real (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_bool (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_seq (OSS_VOIDD * ctx);
#define _oss_dx_set		_oss_dx_seq
extern void CDECL_ENTRY		_oss_dx_choice (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_link_seqof (OSS_VOIDD * ctx);
#define _oss_dx_link_setof	_oss_dx_link_seqof
extern void CDECL_ENTRY		_oss_dx_dlink_seqof (OSS_VOIDD * ctx);
#define _oss_dx_dlink_setof	_oss_dx_dlink_seqof
#define _oss_dx_dlink_plus_seqof	_oss_dx_link_seqof
#define _oss_dx_dlink_plus_setof	_oss_dx_dlink_plus_seqof
extern void CDECL_ENTRY			_oss_dx_unbnd_seqof (OSS_VOIDD * ctx);
#define _oss_dx_unbnd_setof	_oss_dx_unbnd_seqof
#define _oss_dx_array_seqof	_oss_dx_unbnd_seqof
#define _oss_dx_array_setof	_oss_dx_unbnd_seqof
extern void CDECL_ENTRY		_oss_dx_unbnd_char (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_4byte_char (OSS_VOIDD * ctx);
#define _oss_dx_2byte_char	_oss_dx_4byte_char
extern void CDECL_ENTRY		_oss_dx_pad_char (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_nlltrm_char (OSS_VOIDD * ctx);
#define	_oss_dx_vary_char	_oss_dx_nlltrm_char
extern void CDECL_ENTRY		_oss_dx_array_objid (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_link_objid (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_unbnd_objid (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_utc_time (OSS_VOIDD * ctx);
#define _oss_dx_gen_time	_oss_dx_utc_time
extern void CDECL_ENTRY		_oss_dx_opentype (OSS_VOIDD * ctx);
#define _oss_dx_unbnd_any	_oss_dx_opentype
#define _oss_dx_embedded_pdv	_oss_dx_seq
#define _oss_dx_char_string	_oss_dx_seq
extern void CDECL_ENTRY		_oss_dx_char_real (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_mixed_real (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_huge_int (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_dx_encoded_objid (OSS_VOIDD * ctx);
#define _oss_dx_encoded_reloid	_oss_dx_encoded_objid
extern void CDECL_ENTRY		_oss_dx_containing (OSS_VOIDD * ctx);
#define _oss_dx_defer		_oss_dx_opentype
#define _oss_dx_defer_obj	_oss_dx_opentype
extern void CDECL_ENTRY		_oss_dx_not_supported (OSS_VOIDD * ctx);

#define _oss_dx_nlltrm_date_time	_oss_dx_nlltrm_char

/* No support for the below C representations */
#define _oss_dx_vary_any		_oss_dx_not_supported
#define _oss_dx_unbnd_link_octet	_oss_dx_not_supported
#define _oss_dx_vary_link_octet		_oss_dx_not_supported
#define _oss_dx_unbnd_link_bit		_oss_dx_not_supported
#define _oss_dx_vary_link_bit		_oss_dx_not_supported
#define _oss_dx_vary_link_char		_oss_dx_not_supported
#define _oss_dx_nlltrm_link_char	_oss_dx_not_supported
#define _oss_dx_unbnd_link_char		_oss_dx_not_supported
#define _oss_dx_unbnd_dlink_octet	_oss_dx_not_supported
#define _oss_dx_vary_dlink_octet	_oss_dx_not_supported
#define _oss_dx_unbnd_dlink_bit		_oss_dx_not_supported
#define _oss_dx_vary_dlink_bit		_oss_dx_not_supported
#define _oss_dx_vary_dlink_char		_oss_dx_not_supported
#define _oss_dx_nlltrm_dlink_char	_oss_dx_not_supported
#define _oss_dx_unbnd_dlink_char	_oss_dx_not_supported
#define _oss_dx_unbnd_link_any		_oss_dx_not_supported
#define _oss_dx_unbnd_dlink_any		_oss_dx_not_supported
#define _oss_dx_one_char		_oss_dx_not_supported

#endif /* OSS_SOED_XER ... */

#if defined(OSS_SOED_EXER)

typedef struct {
    unsigned char *_oss_JWwJ;	    
    unsigned char *_oss_HWjJ;    
    unsigned char *_oss_wJjJ;	    
    unsigned char *_oss_JqjJ;	    
    void *_oss_qjHJ;	    
    void *_oss_HjwJ;	    
    OSS_UINT16 _oss_HWwJ;   
    OSS_UINT16 _oss_jjHJ;       
    OSS_UINT16 *_oss_WjwJ;        
} exer_extra_data;
typedef struct {
    OSS_INT32 _oss_JqWJ;	
    void ** _oss_wjwJ;	
} exer_ext;
typedef struct {
    OSS_UINT32 _oss_wWwJ;
    OSS_UINT32 _oss_wwjJ;
    unsigned char *_oss_HqJJ;	    
    OSS_UINT16 _oss_jjjJ;		    
    void *_oss_QWjJ;		    
    exer_extra_data *_oss_qjjJ;    
    exer_ext _oss_qqHJ;	    
} exer_type;

/* EXER-specific control table header */

/* Control table header */
typedef struct {
    OSS_UINT32             table_flags;
    OSS_UINT16             table_version;
    OSS_UINT16             table_compat_version;
    OSS_INT32              type_count;
    exer_type             *type_array;
    OSS_INT32              namespace_count;
    exer_namespace        *namespace_array;
    exer_search		  *namespace_search;
    exer_decode_position   root_decoder;
    unsigned char	  *reserved_prefix;
    OSS_UINT16		   control_ns;
    OSS_UINT16		   asn1_ns;
    OSS_UINT16             main_ns;
    OSS_INT32              ext_count;
    void                 **ext_array;
    OSS_INT32              ext_list_count;
    exer_extensions_list  *ext_list_array;
} exer_table;


typedef struct {
    OSS_UINT32 _oss_wjJW;	    
    OSS_UINT16 *_oss_jJJW;    
} exer_union_data;
typedef struct {
    OSS_UINT16 _oss_qWqJ;		
    OSS_UINT16 _oss_qQJW;	
    OSS_UINT32 _oss_JjQW;	
    OSS_UINT32 *_oss_JHWW;		
} exer_order_data;
typedef struct {
    exer_tag_decoder *_oss_QwqJ; 
    exer_decode_position _oss_qqqJ;   
} exer_set_data;
typedef struct {
    exer_tag_decoder *_oss_QwqJ; 
    exer_decode_position *_oss_jwJW; 
} exer_sequence_data;

/* ekind- and ikind- specific functions for smart linking */

struct _EXEREncContext;
struct _EXERDecContext;

typedef void (CDECL_ENTRY_FPTR *ossEXERencodefp)(struct _EXEREncContext *);
typedef void (CDECL_ENTRY_FPTR *ossEXERencodeIfp)(struct _EXEREncContext *);
typedef void (CDECL_ENTRY_FPTR *ossEXERdecodefp)(struct _EXERDecContext *);
typedef void (CDECL_ENTRY_FPTR *ossEXERdecodeIfp)(struct _EXERDecContext *);

    /*************************************************************************/
    /*      SOED EXER functions section                                      */
    /*************************************************************************/

/* ossLink_[E|D]Exer routines should never be used with DLLs */
PUBLIC void DLL_ENTRY ossLink_EExer (OssGlobal *, void *,
	unsigned short , int const * , ossEXERencodefp *,
	unsigned short , int const * , ossEXERencodeIfp *);
PUBLIC void DLL_ENTRY ossLink_DExer (OssGlobal *, void *,
	unsigned short , int const * , ossEXERdecodefp *,
	unsigned short , int const * , ossEXERdecodeIfp *);

PUBLIC void DLL_ENTRY ossLink_ExerReal(OssGlobal *);

#endif /* OSS_SOED_EXER || !SHIPPING */

#if defined(OSS_SOED_EXER)

/* ************************************************************* *
 * Encoding functions:						 *
 * ************************************************************* */
extern void CDECL_ENTRY		_oss_eex_int (struct _EXEREncContext * ctx);
#define _oss_eex_uint		_oss_eex_int
extern void CDECL_ENTRY		_oss_eex_enum (struct _EXEREncContext * ctx);
#define _oss_eex_uenum		_oss_eex_enum
extern void CDECL_ENTRY		_oss_eex_pad_bit (struct _EXEREncContext * ctx);
#define _oss_eex_big_pad_bit	_oss_eex_pad_bit
extern void CDECL_ENTRY		_oss_eex_unbnd_bit (struct _EXEREncContext * ctx);
#define _oss_eex_vary_bit	_oss_eex_unbnd_bit
extern void CDECL_ENTRY		_oss_eex_null (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_real (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_char_real (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_mixed_real (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_bool (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_unbnd_any (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_seq (struct _EXEREncContext * ctx);
#define _oss_eex_set		_oss_eex_seq
#define _oss_eex_embedded_pdv	_oss_eex_seq
#define _oss_eex_char_string	_oss_eex_seq
extern void CDECL_ENTRY		_oss_eex_choice (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_link_seqof (struct _EXEREncContext * ctx);
#define _oss_eex_dlink_plus_seqof	_oss_eex_link_seqof
#define _oss_eex_link_setof	_oss_eex_link_seqof
#define _oss_eex_dlink_plus_setof	_oss_eex_dlink_plus_seqof
extern void CDECL_ENTRY		_oss_eex_dlink_seqof (struct _EXEREncContext * ctx);
#define _oss_eex_dlink_setof	_oss_eex_dlink_seqof
extern void CDECL_ENTRY		_oss_eex_unbnd_seqof (struct _EXEREncContext * ctx);
#define _oss_eex_unbnd_setof	_oss_eex_unbnd_seqof
#define _oss_eex_array_seqof	_oss_eex_unbnd_seqof
#define _oss_eex_array_setof	_oss_eex_unbnd_seqof
extern void CDECL_ENTRY		_oss_eex_unbnd_octet (struct _EXEREncContext * ctx);
#define _oss_eex_vary_octet	_oss_eex_unbnd_octet
#define _oss_eex_fixed_octet 	_oss_eex_unbnd_octet
extern void CDECL_ENTRY		_oss_eex_unbnd_char (struct _EXEREncContext * ctx);
#define _oss_eex_vary_char	_oss_eex_unbnd_char
#define _oss_eex_nlltrm_char	_oss_eex_unbnd_char
extern void CDECL_ENTRY		_oss_eex_pad_char (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_link_objid (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_unbnd_objid (struct _EXEREncContext * ctx);
#define _oss_eex_array_objid	_oss_eex_unbnd_objid
extern void CDECL_ENTRY		_oss_eex_utc_time (struct _EXEREncContext * ctx);
#define _oss_eex_gen_time	_oss_eex_utc_time
extern void CDECL_ENTRY		_oss_eex_opentype (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_4byte_char (struct _EXEREncContext * ctx);
#define _oss_eex_2byte_char	_oss_eex_4byte_char
extern void CDECL_ENTRY		_oss_eex_huge_int (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_encoded_objid (struct _EXEREncContext * ctx);
#define _oss_eex_encoded_reloid	_oss_eex_encoded_objid
extern void CDECL_ENTRY		_oss_eex_containing (struct _EXEREncContext * ctx);
extern void CDECL_ENTRY		_oss_eex_not_supported (struct _EXEREncContext * ctx);
#define _oss_eex_defer		_oss_eex_not_supported
#define _oss_eex_defer_obj	_oss_eex_not_supported

#define _oss_eex_nlltrm_date_time	_oss_eex_nlltrm_char

/* ************************************************************* *
 * Encoding i_kind functions:					 *
 * ************************************************************* */
extern void CDECL_ENTRY    		_oss_eex_anyattr_nlltrm_char(struct _EXEREncContext * ctx);

extern void CDECL_ENTRY  		_oss_eex_normal_int(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY 		_oss_eex_normal_enum(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY    		_oss_eex_base64_unbnd_char(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY    		_oss_eex_normal_unbnd_char(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY    		_oss_eex_base64_unbnd_octet(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY    		_oss_eex_normal_unbnd_octet(struct _EXEREncContext * ctx);
#define _oss_eex_base64_pad_char	_oss_eex_base64_unbnd_char
#define	_oss_eex_normal_pad_char	_oss_eex_normal_unbnd_char
#define	_oss_eex_base64_nlltrm_char	_oss_eex_base64_unbnd_char
#define _oss_eex_normal_nlltrm_char	_oss_eex_normal_unbnd_char
extern void CDECL_ENTRY			_oss_eex_anyel_nlltrm_char(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY    		_oss_eex_base64_4byte_char(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY    		_oss_eex_normal_4byte_char(struct _EXEREncContext * ctx);
#define _oss_eex_useorder_seq		_oss_eex_not_supported
extern void CDECL_ENTRY    		_oss_eex_qname_seq(struct _EXEREncContext * ctx);
#define _oss_eex_normal_seq		_oss_eex_not_supported
#define _oss_eex_anyattr_link_sof	_oss_eex_anyattr_nlltrm_char
#define _oss_eex_normal_link_sof	_oss_eex_not_supported
#define _oss_eex_base64_opentype	_oss_eex_base64_unbnd_octet
#define _oss_eex_normal_opentype	_oss_eex_normal_unbnd_octet
extern void CDECL_ENTRY			_oss_eex_normal_real(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY			_oss_eex_modified_real(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY			_oss_eex_normal_char_real(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY			_oss_eex_modified_char_real(struct _EXEREncContext * ctx);
extern void CDECL_ENTRY			_oss_eex_decimal_char_real(struct _EXEREncContext * ctx);

/* No support for the below C representations */
#define _oss_eex_vary_any		_oss_eex_not_supported
#define _oss_eex_unbnd_link_octet	_oss_eex_not_supported
#define _oss_eex_vary_link_octet	_oss_eex_not_supported
#define _oss_eex_unbnd_link_bit		_oss_eex_not_supported
#define _oss_eex_vary_link_bit		_oss_eex_not_supported
#define _oss_eex_vary_link_char		_oss_eex_not_supported
#define _oss_eex_nlltrm_link_char	_oss_eex_not_supported
#define _oss_eex_unbnd_link_char	_oss_eex_not_supported
#define _oss_eex_unbnd_dlink_octet	_oss_eex_not_supported
#define _oss_eex_vary_dlink_octet	_oss_eex_not_supported
#define _oss_eex_unbnd_dlink_bit	_oss_eex_not_supported
#define _oss_eex_vary_dlink_bit		_oss_eex_not_supported
#define _oss_eex_vary_dlink_char	_oss_eex_not_supported
#define _oss_eex_nlltrm_dlink_char	_oss_eex_not_supported
#define _oss_eex_unbnd_dlink_char	_oss_eex_not_supported
#define _oss_eex_unbnd_link_any		_oss_eex_not_supported
#define _oss_eex_unbnd_dlink_any	_oss_eex_not_supported
#define _oss_eex_one_char		_oss_eex_not_supported

/* ************************************************************* *
 * Decoding functions:						 *
 * ************************************************************* */
extern void CDECL_ENTRY		_oss_dex_int (struct _EXERDecContext * ctx);
#define _oss_dex_uint		_oss_dex_int
#define _oss_dex_enum		_oss_dex_int
#define _oss_dex_uenum		_oss_dex_int
extern void CDECL_ENTRY		_oss_dex_unbnd_bit (struct _EXERDecContext * ctx);
#define _oss_dex_vary_bit	_oss_dex_unbnd_bit
#define _oss_dex_pad_bit	_oss_dex_unbnd_bit
#define _oss_dex_big_pad_bit	_oss_dex_unbnd_bit
extern void CDECL_ENTRY		_oss_dex_unbnd_octet (struct _EXERDecContext * ctx);
#define _oss_dex_vary_octet	_oss_dex_unbnd_octet
#define _oss_dex_fixed_octet    _oss_dex_unbnd_octet
extern void CDECL_ENTRY		_oss_dex_null (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_real (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_bool (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_seq (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_set (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_choice (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_link_seqof (struct _EXERDecContext * ctx);
#define _oss_dex_dlink_plus_seqof	_oss_dex_link_seqof
#define _oss_dex_link_setof	_oss_dex_link_seqof
#define _oss_dex_dlink_plus_setof	_oss_dex_dlink_plus_seqof
extern void CDECL_ENTRY    	_oss_dex_dlink_seqof (struct _EXERDecContext * ctx);
#define _oss_dex_dlink_setof	_oss_dex_dlink_seqof
extern void CDECL_ENTRY		_oss_dex_unbnd_seqof (struct _EXERDecContext * ctx);
#define _oss_dex_unbnd_setof	_oss_dex_unbnd_seqof
#define _oss_dex_array_seqof	_oss_dex_unbnd_seqof
#define _oss_dex_array_setof	_oss_dex_unbnd_seqof
extern void CDECL_ENTRY		_oss_dex_unbnd_char (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_4byte_char (struct _EXERDecContext * ctx);
#define _oss_dex_2byte_char	_oss_dex_4byte_char
extern void CDECL_ENTRY		_oss_dex_pad_char (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_nlltrm_char (struct _EXERDecContext * ctx);
#define	_oss_dex_vary_char	_oss_dex_nlltrm_char
extern void CDECL_ENTRY		_oss_dex_array_objid (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_link_objid (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_unbnd_objid (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_utc_time (struct _EXERDecContext * ctx);
#define _oss_dex_gen_time	_oss_dex_utc_time
extern void CDECL_ENTRY		_oss_dex_opentype (struct _EXERDecContext * ctx);
#define _oss_dex_unbnd_any	_oss_dex_opentype
#define _oss_dex_embedded_pdv	_oss_dex_seq
#define _oss_dex_char_string	_oss_dex_seq
extern void CDECL_ENTRY		_oss_dex_char_real (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_mixed_real (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_huge_int (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_encoded_objid (struct _EXERDecContext * ctx);
#define _oss_dex_encoded_reloid	_oss_dex_encoded_objid
extern void CDECL_ENTRY		_oss_dex_containing (struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_not_supported (struct _EXERDecContext * ctx);
#define _oss_dex_defer		_oss_dex_not_supported
#define _oss_dex_defer_obj	_oss_dex_not_supported

#define _oss_dex_nlltrm_date_time	_oss_dex_nlltrm_char

/* ************************************************************* *
 * Decoding i_kind functions:					 *
 * ************************************************************* */
extern void CDECL_ENTRY    	_oss_dex_anyattr_nlltrm_char(struct _EXERDecContext *ctx);

#define _oss_dex_normal_int	_oss_dex_not_supported
#define _oss_dex_normal_enum	_oss_dex_not_supported
extern void CDECL_ENTRY    	_oss_dex_base64_unbnd_char(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY    	_oss_dex_normal_unbnd_char(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_base64_unbnd_octet(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_normal_unbnd_octet(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY    	_oss_dex_base64_pad_char(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY    	_oss_dex_normal_pad_char(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY    	_oss_dex_base64_nlltrm_char(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_anyel_nlltrm_char(struct _EXERDecContext *ctx);
extern void CDECL_ENTRY    	_oss_dex_normal_nlltrm_char(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY    	_oss_dex_base64_4byte_char(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY    	_oss_dex_normal_4byte_char(struct _EXERDecContext * ctx);
#define _oss_dex_useorder_seq	_oss_dex_set
extern void CDECL_ENTRY		_oss_dex_qname_seq(struct _EXERDecContext *ctx);
extern void CDECL_ENTRY		_oss_dex_normal_seq(struct _EXERDecContext *ctx);
#define _oss_dex_anyattr_link_sof _oss_dex_anyattr_nlltrm_char
extern void CDECL_ENTRY		_oss_dex_normal_link_sof(struct _EXERDecContext *ctx);
extern void CDECL_ENTRY    	_oss_dex_base64_opentype(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY    	_oss_dex_normal_opentype(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_normal_real(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_modified_real(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_normal_char_real(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_modified_char_real(struct _EXERDecContext * ctx);
extern void CDECL_ENTRY		_oss_dex_decimal_char_real(struct _EXERDecContext * ctx);

extern ossBoolean DLL_ENTRY ossEXValidateAnyUri(unsigned char *string, long length);

/* No support for the below C representations */
#define _oss_dex_vary_any		_oss_dex_not_supported
#define _oss_dex_unbnd_link_octet	_oss_dex_not_supported
#define _oss_dex_vary_link_octet	_oss_dex_not_supported
#define _oss_dex_unbnd_link_bit		_oss_dex_not_supported
#define _oss_dex_vary_link_bit		_oss_dex_not_supported
#define _oss_dex_vary_link_char		_oss_dex_not_supported
#define _oss_dex_nlltrm_link_char	_oss_dex_not_supported
#define _oss_dex_unbnd_link_char	_oss_dex_not_supported
#define _oss_dex_unbnd_dlink_octet	_oss_dex_not_supported
#define _oss_dex_vary_dlink_octet	_oss_dex_not_supported
#define _oss_dex_unbnd_dlink_bit	_oss_dex_not_supported
#define _oss_dex_vary_dlink_bit		_oss_dex_not_supported
#define _oss_dex_vary_dlink_char	_oss_dex_not_supported
#define _oss_dex_nlltrm_dlink_char	_oss_dex_not_supported
#define _oss_dex_unbnd_dlink_char	_oss_dex_not_supported
#define _oss_dex_unbnd_link_any		_oss_dex_not_supported
#define _oss_dex_unbnd_dlink_any	_oss_dex_not_supported
#define _oss_dex_one_char		_oss_dex_not_supported

#endif /* OSS_SOED_EXER && !LED_SOURCECODE_SHIPPING */

#if defined(OSS_SOED_OER)
/*****************************************************************************/
/*  SOED OER section                                                         */
/*****************************************************************************/
#ifndef OSS_VOIDE
#define OSS_VOIDE void
#endif
#ifndef OSS_VOIDD
#define OSS_VOIDD void
#endif

    /*************************************************************************/
    /*      SOED OER functions section                                       */
    /*************************************************************************/
PUBLIC void DLL_ENTRY ossLinkOerReal(OssGlobal *);

typedef void   (CDECL_ENTRY_FPTR * ossOERencodefp)(void *);
typedef void   (CDECL_ENTRY_FPTR * ossOERdecodefp)(void *);

/* DLL-related functions defined at oerfp.c; also used for ASN1Step */

PUBLIC void DLL_ENTRY ossLinkEOer (OssGlobal *, unsigned short,
					int const *, ossOERencodefp *);
PUBLIC void DLL_ENTRY ossLinkDOer (OssGlobal *, unsigned short,
					int const *, ossOERdecodefp *);
extern void CDECL_ENTRY         _oss_eo_real (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_char_real (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_mixed_real (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_null (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_seq (OSS_VOIDE * ctx);
#define _oss_eo_set             _oss_eo_seq
#define _oss_eo_embedded_pdv	_oss_eo_seq
#define _oss_eo_char_string	_oss_eo_seq
extern void CDECL_ENTRY         _oss_eo_nlltrm_char (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_eo_pad_char (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_eo_4byte_char (OSS_VOIDE * ctx);
#define _oss_eo_2byte_char	_oss_eo_4byte_char
extern void CDECL_ENTRY         _oss_eo_unbnd_bit (OSS_VOIDE * ctx);
#define _oss_eo_vary_bit	_oss_eo_unbnd_bit
extern void CDECL_ENTRY		_oss_eo_pad_bit (OSS_VOIDE * ctx);
#define _oss_eo_big_pad_bit	_oss_eo_pad_bit
extern void CDECL_ENTRY         _oss_eo_unbnd_octet (OSS_VOIDE * ctx);
#define _oss_eo_unbnd_any       _oss_eo_unbnd_octet
#define _oss_eo_vary_octet	_oss_eo_unbnd_octet
extern void CDECL_ENTRY         _oss_eo_fixed_octet (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_unbnd_char (OSS_VOIDE * ctx);
#define _oss_eo_vary_char	_oss_eo_unbnd_char
extern void CDECL_ENTRY         _oss_eo_utc_time (OSS_VOIDE * ctx);
#define _oss_eo_gen_time	_oss_eo_utc_time
extern void CDECL_ENTRY         _oss_eo_bool (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_unbnd_seqof (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_array_seqof (OSS_VOIDE * ctx);
#define _oss_eo_unbnd_setof     _oss_eo_unbnd_seqof
#define _oss_eo_array_setof     _oss_eo_array_seqof
extern void CDECL_ENTRY         _oss_eo_link_seqof (OSS_VOIDE * ctx);
#define _oss_eo_link_setof      _oss_eo_link_seqof
#define _oss_eo_dlink_seqof     _oss_eo_link_setof
#define _oss_eo_dlink_setof     _oss_eo_dlink_seqof
#define _oss_eo_dlink_plus_seqof _oss_eo_link_seqof
#define _oss_eo_dlink_plus_setof _oss_eo_dlink_plus_seqof
extern void CDECL_ENTRY         _oss_eo_int (OSS_VOIDE * ctx);
#define _oss_eo_uint            _oss_eo_int
extern void CDECL_ENTRY         _oss_eo_enum (OSS_VOIDE * ctx);
#define _oss_eo_uenum           _oss_eo_enum
extern void CDECL_ENTRY         _oss_eo_huge_int (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_choice (OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_encoded_objid (OSS_VOIDE * ctx);
#define _oss_eo_encoded_reloid	_oss_eo_encoded_objid
extern void CDECL_ENTRY		_oss_eo_link_objid (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_eo_unbnd_objid (OSS_VOIDE * ctx);
#define _oss_eo_array_objid	_oss_eo_unbnd_objid
extern void CDECL_ENTRY         _oss_eo_containing(OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_opentype(OSS_VOIDE * ctx);
extern void CDECL_ENTRY         _oss_eo_not_supported (OSS_VOIDE * ctx);
extern void CDECL_ENTRY		_oss_eo_nlltrm_date_time(OSS_VOIDE * ctx);

#define _oss_eo_one_char		_oss_eo_not_supported
#define _oss_eo_vary_link_bit	_oss_eo_not_supported
#define _oss_eo_vary_dlink_bit	_oss_eo_not_supported
#define _oss_eo_unbnd_link_bit	_oss_eo_not_supported
#define _oss_eo_unbnd_dlink_bit	_oss_eo_not_supported
#define _oss_eo_unbnd_link_octet	_oss_eo_not_supported
#define _oss_eo_unbnd_dlink_octet	_oss_eo_not_supported
#define _oss_eo_vary_link_octet	_oss_eo_not_supported
#define _oss_eo_vary_dlink_octet	_oss_eo_not_supported
#define _oss_eo_unbnd_link_char	_oss_eo_not_supported
#define _oss_eo_unbnd_dlink_char	_oss_eo_not_supported
#define _oss_eo_vary_link_char	_oss_eo_not_supported
#define _oss_eo_vary_dlink_char	_oss_eo_not_supported
#define _oss_eo_nlltrm_link_char	_oss_eo_not_supported
#define _oss_eo_nlltrm_dlink_char	_oss_eo_not_supported
#define _oss_eo_unbnd_link_any	_oss_eo_not_supported
#define _oss_eo_unbnd_dlink_any	_oss_eo_not_supported
#define _oss_eo_vary_any		_oss_eo_not_supported
#define _oss_eo_defer		_oss_eo_not_supported
#define _oss_eo_defer_obj		_oss_eo_not_supported

extern void CDECL_ENTRY         _oss_do_real (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_char_real (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_mixed_real (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_null (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_seq (OSS_VOIDD * ctx);
#define _oss_do_set             _oss_do_seq
#define _oss_do_embedded_pdv	_oss_do_seq
#define _oss_do_char_string	_oss_do_seq
extern void CDECL_ENTRY         _oss_do_nlltrm_char (OSS_VOIDD * ctx);
#define _oss_do_vary_char	_oss_do_nlltrm_char
extern void CDECL_ENTRY		_oss_do_pad_char (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_do_4byte_char (OSS_VOIDD * ctx);
#define _oss_do_2byte_char	_oss_do_4byte_char
extern void CDECL_ENTRY         _oss_do_unbnd_bit (OSS_VOIDD * ctx);
#define _oss_do_vary_bit	_oss_do_unbnd_bit
extern void CDECL_ENTRY		_oss_do_pad_bit (OSS_VOIDD * ctx);
#define _oss_do_big_pad_bit	_oss_do_pad_bit
extern void CDECL_ENTRY         _oss_do_unbnd_octet (OSS_VOIDD * ctx);
#define _oss_do_unbnd_any       _oss_do_unbnd_octet
#define _oss_do_vary_octet	_oss_do_unbnd_octet
extern void CDECL_ENTRY         _oss_do_fixed_octet (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_unbnd_char (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_utc_time (OSS_VOIDD * ctx);
#define _oss_do_gen_time	_oss_do_utc_time
extern void CDECL_ENTRY         _oss_do_bool (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_unbnd_seqof (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_array_seqof (OSS_VOIDD * ctx);
#define _oss_do_unbnd_setof     _oss_do_unbnd_seqof
#define _oss_do_array_setof     _oss_do_array_seqof
extern void CDECL_ENTRY         _oss_do_link_seqof (OSS_VOIDD * ctx);
#define _oss_do_link_setof      _oss_do_link_seqof
#define _oss_do_dlink_seqof     _oss_do_link_setof
#define _oss_do_dlink_setof     _oss_do_dlink_seqof
#define _oss_do_dlink_plus_seqof _oss_do_link_seqof
#define _oss_do_dlink_plus_setof _oss_do_dlink_plus_seqof
extern void CDECL_ENTRY         _oss_do_int (OSS_VOIDD * ctx);
#define _oss_do_uint            _oss_do_int
extern void CDECL_ENTRY         _oss_do_enum (OSS_VOIDD * ctx);
#define _oss_do_uenum           _oss_do_enum
extern void CDECL_ENTRY         _oss_do_huge_int (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_choice (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_encoded_objid (OSS_VOIDD * ctx);
#define _oss_do_encoded_reloid	_oss_do_encoded_objid
extern void CDECL_ENTRY		_oss_do_link_objid (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_do_unbnd_objid (OSS_VOIDD * ctx);
extern void CDECL_ENTRY		_oss_do_array_objid (OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_containing(OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_opentype(OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_skip_Type(OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_not_supported(OSS_VOIDD * ctx);
extern void CDECL_ENTRY         _oss_do_nlltrm_date_time(OSS_VOIDD * ctx);

#define _oss_do_one_char		_oss_do_not_supported
#define _oss_do_vary_link_bit	_oss_do_not_supported
#define _oss_do_vary_dlink_bit	_oss_do_not_supported
#define _oss_do_unbnd_link_bit	_oss_do_not_supported
#define _oss_do_unbnd_dlink_bit	_oss_do_not_supported
#define _oss_do_unbnd_link_octet	_oss_do_not_supported
#define _oss_do_unbnd_dlink_octet	_oss_do_not_supported
#define _oss_do_vary_link_octet	_oss_do_not_supported
#define _oss_do_vary_dlink_octet	_oss_do_not_supported
#define _oss_do_unbnd_link_char	_oss_do_not_supported
#define _oss_do_unbnd_dlink_char	_oss_do_not_supported
#define _oss_do_vary_link_char	_oss_do_not_supported
#define _oss_do_vary_dlink_char	_oss_do_not_supported
#define _oss_do_nlltrm_link_char	_oss_do_not_supported
#define _oss_do_nlltrm_dlink_char	_oss_do_not_supported
#define _oss_do_unbnd_link_any	_oss_do_not_supported
#define _oss_do_unbnd_dlink_any	_oss_do_not_supported
#define _oss_do_vary_any		_oss_do_not_supported
#define _oss_do_defer		_oss_do_not_supported
#define _oss_do_defer_obj		_oss_do_not_supported

	/********************************************************************/
	/*      SOED OER time functions section                             */
	/********************************************************************/

typedef void (CDECL_ENTRY_FPTR *ossOERTimeEncodefp)(OSS_VOIDE *);
typedef void (CDECL_ENTRY_FPTR *ossOERTimeDecodefp)(OSS_VOIDD *);

/* ossLink_[E|D]OERTime routines should never be used with DLLs */
PUBLIC void DLL_ENTRY ossLink_EOerTime (struct ossGlobal *,
 	unsigned short , int const * , ossOERTimeEncodefp *);
PUBLIC void DLL_ENTRY ossLink_DOerTime (struct ossGlobal *,
 	unsigned short , int const * , ossOERTimeDecodefp *);

/* ************************************************************* *
 * OER TIME Encoding functions:				         *
 * ************************************************************* */
extern void CDECL_ENTRY _oss_eot_year(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_any_year(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_year_month(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_any_year_month(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_date(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_any_date(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_hours(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_hours_utc(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_hours_and_diff(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_minutes(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_minutes_utc(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_minutes_and_diff(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_time_of_day(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_time_of_day_utc(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_time_of_day_and_diff(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_time_of_day_and_fraction(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_time_of_day_utc_and_fraction(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_time_of_day_and_diff_and_fraction(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_date_time(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_duration_interval(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_not_supported(OSS_VOIDE * ctx);
extern void CDECL_ENTRY _oss_eot_unoptimized_time(OSS_VOIDE * ctx);
#define _oss_eot_year_week _oss_eot_unoptimized_time
#define _oss_eot_century _oss_eot_unoptimized_time
#define _oss_eot_any_century _oss_eot_unoptimized_time
#define _oss_eot_year_day _oss_eot_unoptimized_time
#define _oss_eot_any_year_day _oss_eot_unoptimized_time
#define _oss_eot_any_year_week _oss_eot_unoptimized_time
#define _oss_eot_year_week_day _oss_eot_unoptimized_time
#define _oss_eot_any_year_week_day _oss_eot_unoptimized_time
#define _oss_eot_minutes_and_diff_and_fraction _oss_eot_unoptimized_time
#define _oss_eot_hours_and_fraction _oss_eot_unoptimized_time
#define _oss_eot_hours_utc_and_fraction _oss_eot_unoptimized_time
#define _oss_eot_hours_and_diff_and_fraction _oss_eot_unoptimized_time
#define _oss_eot_minutes_and_fraction _oss_eot_unoptimized_time
#define _oss_eot_minutes_utc_and_fraction _oss_eot_unoptimized_time
#define _oss_eot_start_end_date_interval _oss_eot_unoptimized_time
#define _oss_eot_start_end_time_interval _oss_eot_unoptimized_time
#define _oss_eot_start_end_date_time_interval _oss_eot_unoptimized_time
#define _oss_eot_start_date_duration_interval _oss_eot_unoptimized_time
#define _oss_eot_start_time_duration_interval _oss_eot_unoptimized_time
#define _oss_eot_start_date_time_duration_interval _oss_eot_unoptimized_time
#define _oss_eot_duration_end_date_interval _oss_eot_unoptimized_time
#define _oss_eot_duration_end_time_interval _oss_eot_unoptimized_time
#define _oss_eot_duration_end_date_time_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_start_end_date_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_start_end_time_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_start_end_date_time_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_duration_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_start_date_duration_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_start_time_duration_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_start_date_time_duration_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_duration_end_date_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_duration_end_time_interval _oss_eot_unoptimized_time
#define _oss_eot_rec_duration_end_date_time_interval _oss_eot_unoptimized_time
#define _oss_eot_mixed _oss_eot_unoptimized_time

/* ************************************************************* *
 * OER TIME decoding functions:					 *
 * ************************************************************* */
extern void CDECL_ENTRY _oss_dot_year(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_any_year(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_year_month(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_any_year_month(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_date(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_any_date(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_hours(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_hours_utc(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_hours_and_diff(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_minutes(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_minutes_utc(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_minutes_and_diff(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_time_of_day(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_time_of_day_utc(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_time_of_day_and_diff(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_time_of_day_and_fraction(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_time_of_day_utc_and_fraction(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_time_of_day_and_diff_and_fraction(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_date_time(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_duration_interval(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_not_supported(OSS_VOIDD * ctx);
extern void CDECL_ENTRY _oss_dot_unoptimized_time(OSS_VOIDD * ctx);
#define _oss_dot_year_week _oss_dot_unoptimized_time
#define _oss_dot_century _oss_dot_unoptimized_time
#define _oss_dot_any_century _oss_dot_unoptimized_time
#define _oss_dot_year_day _oss_dot_unoptimized_time
#define _oss_dot_any_year_day _oss_dot_unoptimized_time
#define _oss_dot_any_year_week _oss_dot_unoptimized_time
#define _oss_dot_year_week_day _oss_dot_unoptimized_time
#define _oss_dot_any_year_week_day _oss_dot_unoptimized_time
#define _oss_dot_minutes_and_diff_and_fraction _oss_dot_unoptimized_time
#define _oss_dot_hours_and_fraction _oss_dot_unoptimized_time
#define _oss_dot_hours_utc_and_fraction _oss_dot_unoptimized_time
#define _oss_dot_hours_and_diff_and_fraction _oss_dot_unoptimized_time
#define _oss_dot_minutes_and_fraction _oss_dot_unoptimized_time
#define _oss_dot_minutes_utc_and_fraction _oss_dot_unoptimized_time
#define _oss_dot_start_end_date_interval _oss_dot_unoptimized_time
#define _oss_dot_start_end_time_interval _oss_dot_unoptimized_time
#define _oss_dot_start_end_date_time_interval _oss_dot_unoptimized_time
#define _oss_dot_start_date_duration_interval _oss_dot_unoptimized_time
#define _oss_dot_start_time_duration_interval _oss_dot_unoptimized_time
#define _oss_dot_start_date_time_duration_interval _oss_dot_unoptimized_time
#define _oss_dot_duration_end_date_interval _oss_dot_unoptimized_time
#define _oss_dot_duration_end_time_interval _oss_dot_unoptimized_time
#define _oss_dot_duration_end_date_time_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_start_end_date_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_start_end_time_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_start_end_date_time_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_duration_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_start_date_duration_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_start_time_duration_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_start_date_time_duration_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_duration_end_date_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_start_date_time_duration_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_duration_end_date_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_duration_end_time_interval _oss_dot_unoptimized_time
#define _oss_dot_rec_duration_end_date_time_interval _oss_dot_unoptimized_time
#define _oss_dot_mixed _oss_dot_unoptimized_time

#endif /* OSS_SOED_OER */


#endif /* _OSS_CODE_FILE */

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
#elif defined(__BORLANDC__) && defined(__WIN32__)
#pragma option -a.
#elif defined(__IBMC__) && defined(__WIN32__)
#pragma pack()
#elif defined(__WATCOMC__) && defined(__NT__)
#pragma pack(pop)
#endif /* _MSC_VER && _WIN32 */

#endif /* !OSSTYPE_H */

