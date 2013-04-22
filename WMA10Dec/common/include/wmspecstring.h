//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef _WMSPECSTRING_H_
#define _WMSPECSTRING_H_

#if (!defined UNDER_CE && !defined NO_WINDOWS && !defined SPECSTRINGS_H)
#define SPECSTRINGS_H

/*************************************************************************
* See specstrings_strict.h for documentation of all user visible macros.
*************************************************************************/
#if _MSC_VER
#pragma once
#endif
#include <wmsal.h>  

#ifndef __SAL_H_FULL_VER
#define __SAL_H_FULL_VER 140050727
#endif

#ifdef  __cplusplus
extern "C" {
#endif 

/* version specific fixes to bring sal.h upto date */
#if __SAL_H_FULL_VER <= 140050727

/* Missing from RTM sal.h */
#if !defined(__midl) && defined(_PREFAST_) && _MSC_VER >= 1000

#define __inexpressible_readableTo(size)  __declspec("SAL_readableTo(inexpressibleCount('" SPECSTRINGIZE(size) "'))")
#define __inexpressible_writableTo(size)  __declspec("SAL_writableTo(inexpressibleCount('" SPECSTRINGIZE(size) "'))")
#define __inner_bound                     __declspec("SAL_bound")
#define __inner_range(lb,ub)              __declspec("SAL_range(" SPECSTRINGIZE(lb) "," SPECSTRINGIZE(ub) ")")
#define __inner_assume_bound_dec          __inline __nothrow void __AssumeBoundInt(__post __inner_bound int i) {i;}
#define __inner_assume_bound(i)           __AssumeBoundInt(i);
#define __inner_allocator                 __declspec("SAL_allocator")
#else 
#define __inexpressible_readableTo(size)
#define __inexpressible_writableTo(size)
#define __inner_bound
#define __inner_range(lb,ub)
#define __inner_assume_bound_dec
#define __inner_assume_bound(i)
#define __inner_allocator
#endif

#define __xcount(size)                                          __notnull __inexpressible_writableTo(size)
#define __in_xcount(size)                                       __in __pre __inexpressible_readableTo(size)
#define __out_xcount(size)                                      __xcount(size) __post __valid __refparam
#define __out_xcount_part(size,length)                          __out_xcount(size) __post __inexpressible_readableTo(length)
#define __out_xcount_full(size)                                 __out_xcount_part(size,size)
#define __inout_xcount(size)                                    __out_xcount(size) __pre __valid
#define __inout_xcount_part(size,length)                        __out_xcount_part(size,length) __pre __valid __pre __inexpressible_readableTo(length)
#define __inout_xcount_full(size)                               __inout_xcount_part(size,size)
#define __xcount_opt(size)                                      __xcount(size)                              __exceptthat __maybenull
#define __in_xcount_opt(size)                                   __in_xcount(size)                           __exceptthat __maybenull
#define __out_xcount_opt(size)                                  __out_xcount(size)                          __exceptthat __maybenull
#define __out_xcount_part_opt(size,length)                      __out_xcount_part(size,length)              __exceptthat __maybenull
#define __out_xcount_full_opt(size)                             __out_xcount_full(size)                     __exceptthat __maybenull
#define __inout_xcount_opt(size)                                __inout_xcount(size)                        __exceptthat __maybenull
#define __inout_xcount_part_opt(size,length)                    __inout_xcount_part(size,length)            __exceptthat __maybenull
#define __inout_xcount_full_opt(size)                           __inout_xcount_full(size)                   __exceptthat __maybenull
#define __deref_xcount(size)                                    __ecount(1) __post __elem_readableTo(1) __post __deref __notnull __post __deref __inexpressible_writableTo(size)
#define __deref_in                                              __in __pre __deref __deref __readonly
#define __deref_in_ecount(size)                                 __deref_in __pre __deref __elem_readableTo(size)
#define __deref_in_bcount(size)                                 __deref_in __pre __deref __byte_readableTo(size)
#define __deref_in_xcount(size)                                 __deref_in __pre __deref __inexpressible_readableTo(size)
#define __deref_out_xcount(size)                                __deref_xcount(size) __post __deref __valid __refparam
#define __deref_out_xcount_part(size,length)                    __deref_out_xcount(size) __post __deref __inexpressible_readableTo(length)
#define __deref_out_xcount_full(size)                           __deref_out_xcount_part(size,size)
#define __deref_out_xcount(size)                                __deref_xcount(size) __post __deref __valid __refparam
#define __inout_xcount_opt(size)                                __inout_xcount(size)                        __exceptthat __maybenull
#define __inout_xcount_part_opt(size,length)                    __inout_xcount_part(size,length)            __exceptthat __maybenull
#define __inout_xcount_full_opt(size)                           __inout_xcount_full(size)                   __exceptthat __maybenull
#define __deref_xcount(size)                                    __ecount(1) __post __elem_readableTo(1) __post __deref __notnull __post __deref __inexpressible_writableTo(size)
#define __deref_in                                              __in __pre __deref __deref __readonly
#define __deref_in_ecount(size)                                 __deref_in __pre __deref __elem_readableTo(size)
#define __deref_in_bcount(size)                                 __deref_in __pre __deref __byte_readableTo(size)
#define __deref_in_xcount(size)                                 __deref_in __pre __deref __inexpressible_readableTo(size)
#define __deref_out_xcount(size)                                __deref_xcount(size) __post __deref __valid __refparam
#define __deref_out_xcount_part(size,length)                    __deref_out_xcount(size) __post __deref __inexpressible_readableTo(length)
#define __deref_out_xcount_full(size)                           __deref_out_xcount_part(size,size)
#define __deref_out_xcount(size)                                __deref_xcount(size) __post __deref __valid __refparam
#define __deref_inout_xcount(size)                              __deref_inout __pre __deref __inexpressible_writableTo(size) __post __deref __inexpressible_writableTo(size)
#define __deref_inout_xcount_part(size,length)                  __deref_inout_xcount(size) __pre __deref __inexpressible_readableTo(length) __post __deref __inexpressible_readableTo(length)
#define __deref_inout_xcount_full(size)                         __deref_inout_xcount_part(size,size)
#define __deref_xcount_opt(size)                                __deref_xcount(size)                        __post __deref __exceptthat __maybenull
#define __deref_in_opt                                          __deref_in                                  __pre __deref __exceptthat __maybenull
#define __deref_in_ecount_opt(size)                             __deref_in_ecount(size)                     __pre __deref __exceptthat __maybenull
#define __deref_in_bcount_opt(size)                             __deref_in_bcount(size)                     __pre __deref __exceptthat __maybenull
#define __deref_in_xcount_opt(size)                             __deref_in_xcount(size)                     __pre __deref __exceptthat __maybenull
#define __deref_out_xcount_opt(size)                            __deref_out_xcount(size)                    __post __deref __exceptthat __maybenull
#define __deref_out_xcount_part_opt(size,length)                __deref_out_xcount_part(size,length)        __post __deref __exceptthat __maybenull
#define __deref_out_xcount_full_opt(size)                       __deref_out_xcount_full(size)               __post __deref __exceptthat __maybenull
#define __deref_inout_xcount_opt(size)                          __deref_inout_xcount(size)                  __pre __deref __exceptthat __maybenull __post __deref __exceptthat __maybenull
#define __deref_inout_xcount_part_opt(size,length)              __deref_inout_xcount_part(size,length)      __pre __deref __exceptthat __maybenull __post __deref __exceptthat __maybenull
#define __deref_inout_xcount_full_opt(size)                     __deref_inout_xcount_full(size)             __pre __deref __exceptthat __maybenull __post __deref __exceptthat __maybenull
#define __deref_opt_xcount(size)                                __deref_xcount(size)                        __exceptthat __maybenull
#define __deref_opt_in                                          __deref_in                                  __exceptthat __maybenull
#define __deref_opt_in_ecount(size)                             __deref_in_ecount(size)                     __exceptthat __maybenull
#define __deref_opt_in_bcount(size)                             __deref_in_bcount(size)                     __exceptthat __maybenull
#define __deref_opt_in_xcount(size)                             __deref_in_xcount(size)                     __exceptthat __maybenull
#define __deref_opt_out_xcount(size)                            __deref_out_xcount(size)                    __exceptthat __maybenull
#define __deref_opt_out_xcount_part(size,length)                __deref_out_xcount_part(size,length)        __exceptthat __maybenull
#define __deref_opt_out_xcount_full(size)                       __deref_out_xcount_full(size)               __exceptthat __maybenull
#define __deref_opt_inout_xcount(size)                          __deref_inout_xcount(size)                  __exceptthat __maybenull
#define __deref_opt_inout_xcount_part(size,length)              __deref_inout_xcount_part(size,length)      __exceptthat __maybenull
#define __deref_opt_inout_xcount_full(size)                     __deref_inout_xcount_full(size)             __exceptthat __maybenull
#define __deref_opt_xcount_opt(size)                            __deref_xcount_opt(size)                    __exceptthat __maybenull
#define __deref_opt_in_opt                                      __deref_in_opt                              __exceptthat __maybenull
#define __deref_opt_in_ecount_opt(size)                         __deref_in_ecount_opt(size)                 __exceptthat __maybenull
#define __deref_opt_in_bcount_opt(size)                         __deref_in_bcount_opt(size)                 __exceptthat __maybenull
#define __deref_opt_in_xcount_opt(size)                         __deref_in_xcount_opt(size)                 __exceptthat __maybenull
#define __deref_opt_out_xcount_opt(size)                        __deref_out_xcount_opt(size)                __exceptthat __maybenull
#define __deref_opt_out_xcount_part_opt(size,length)            __deref_out_xcount_part_opt(size,length)    __exceptthat __maybenull
#define __deref_opt_out_xcount_full_opt(size)                   __deref_out_xcount_full_opt(size)           __exceptthat __maybenull
#define __deref_opt_inout_xcount_opt(size)                      __deref_inout_xcount_opt(size)              __exceptthat __maybenull
#define __deref_opt_inout_xcount_part_opt(size,length)          __deref_inout_xcount_part_opt(size,length)  __exceptthat __maybenull
#define __deref_opt_inout_xcount_full_opt(size)                 __deref_inout_xcount_full_opt(size)         __exceptthat __maybenull
/* Must protect redfinitions of macros to workaround rc.exe issues. */
#ifndef RC_INVOKED
#undef __nullnullterminated
#define __nullnullterminated __xcount("string terminated by two nulls")
#undef __checkReturn
#define __checkReturn __post __inner_checkReturn
#endif
#endif  //__SAL_H_FULL_VER <= 140050727

/************************************************************************
 New extensions to sal.h follow here.
*************************************************************************/
/* Internal defintions */
#if (_MSC_VER >= 1000) && !defined(__midl) && defined(_PREFAST_)
#define __inner_control_entrypoint(category) __declspec("SAL_entrypoint(controlEntry, "SPECSTRINGIZE(category)")")
#define __inner_data_entrypoint(category)   __declspec("SAL_entrypoint(dataEntry, "SPECSTRINGIZE(category)")")
#define __inner_success(expr)               __declspec("SAL_success("SPECSTRINGIZE(expr)")")
#define __inner_typefix(ctype)              __declspec("SAL_typefix("SPECSTRINGIZE(ctype)")")
#define __inner_override                    __declspec("__override")
#define __inner_callback                    __declspec("__callback")
#define __inner_blocksOn(resource)          __declspec("SAL_blocksOn("SPECSTRINGIZE(resource)")")
#define __inner_data_source(src)            __declspec("SAL_untrusted_data_source(" SPECSTRINGIZE(src) ")")
#define __inner_out_validated(type)         __declspec("SAL_post") __declspec("SAL_validated(" SPECSTRINGIZE(type) ")")  
#define __inner_assume_validated_dec        __inline __nothrow void __AssumeValidated(__inner_out_validated(BY_DESIGN) const void *p) {p;}
#define __inner_assume_validated(p)         __AssumeValidated(p)
#define __inner_transfer(formal)            __declspec("SAL_transfer_adt_property_from(" SPECSTRINGIZE(formal) ")")
#define __inner_file_parser(type)           __declspec("SAL_file_parser(function, " SPECSTRINGIZE(type) ")")    
#define __inner_file_parser_class(type)     __declspec("SAL_file_parser(class, " SPECSTRINGIZE(type) ")")
#define __inner_file_parser_library(type)   extern int __declspec("SAL_file_parser(library, " SPECSTRINGIZE(type) ")") __iSALFileParserLibrary;
#define __inner_encoded                     __declspec("SAL_encoded")
#define __$adt_prop(adt,prop)  __declspec("SAL_adt("#adt","#prop")")
#define __$adt_add_prop(adt,prop)  __declspec("SAL_add_adt_property("#adt","#prop")")
#define __$adt_remove_prop(adt,prop)  __declspec("SAL_remove_adt_property("#adt","#prop")")
#define __$adt_transfer_prop(arg)  __declspec("SAL_transfer_adt_property_from("#arg")")
#define __$adt_type_props(typ)  __declspec("SAL_post_type("#typ")")
#define __analysis_assert(e) __assume(e)
#else
#define __inner_control_entrypoint(category)
#define __inner_data_entrypoint(category)
#define __inner_success(expr)
#define __inner_typefix(ctype)
#define __inner_override
#define __inner_callback
#define __inner_blocksOn(resource)
#define __inner_data_source(src)
#define __inner_out_validated(type)
#define __inner_assume_validated_dec
#define __inner_assume_validated(p)
#define __inner_transfer(formal)
#define __inner_file_parser(type)
#define __inner_file_parser_class(type)
#define __inner_file_parser_library(type)
#define __inner_encoded
#define __$adt_prop(adt,prop)   
#define __$adt_add_prop(adt,prop)   
#define __$adt_remove_prop(adt,prop)   
#define __$adt_transfer_prop(arg)   
#define __$adt_type_props(typ)   
#define __analysis_assert(e)
#endif // #if (_MSC_VER >= 1000) && !defined(__midl) && defined(_PREFAST_)

#define __field_ecount(size)                __notnull __elem_writableTo(size)
#define __field_bcount(size)                __notnull __byte_writableTo(size)
#define __field_xcount(size)                __notnull __inexpressible_writableTo(size)

#define __field_ecount_opt(size)            __maybenull __elem_writableTo(size)
#define __field_bcount_opt(size)            __maybenull __byte_writableTo(size)
#define __field_xcount_opt(size)            __maybenull __inexpressible_writableTo(size)

#define __field_ecount_part(size,init)      __notnull __elem_writableTo(size) __elem_readableTo(init)
#define __field_bcount_part(size,init)      __notnull __byte_writableTo(size) __byte_readableTo(init)
#define __field_xcount_part(size,init)      __notnull __inexpressible_writableTo(size) __inexpressible_readableTo(init)

#define __field_ecount_part_opt(size,init)  __maybenull __elem_writableTo(size) __elem_readableTo(init)
#define __field_bcount_part_opt(size,init)  __maybenull __byte_writableTo(size) __byte_readableTo(init)
#define __field_xcount_part_opt(size,init)  __maybenull __inexpressible_writableTo(size) __inexpressible_readableTo(init)

#define __field_ecount_full(size)           __field_ecount_part(size,size)  
#define __field_bcount_full(size)           __field_bcount_part(size,size)  
#define __field_xcount_full(size)           __field_xcount_part(size,size)      

#define __field_ecount_full_opt(size)       __field_ecount_part_opt(size,size)  
#define __field_bcount_full_opt(size)       __field_bcount_part_opt(size,size)  
#define __field_xcount_full_opt(size)       __field_xcount_part_opt(size,size)      

#define __struct_bcount(size)               __field_bcount(size)
#define __struct_xcount(size)               __field_xcount(size)
#if (defined(_MSC_VER) && (_MSC_VER < 1400))		// Using VC++ 7.1 or below
// The macros __out_awcount() and __in_awcount() are already defined in
// $VCInstallDir\PlatformSDK\include\specstrings.h for VC++ 8.0 or above.
#define __out_awcount(expr,size)            __pre __notnull \
                                            __out_xcount("__precond(" #expr ") __byte_writableTo(" #size ")") \
                                            __out_xcount("__precond(!(" #expr ")) __byte_writableTo((" #size ")*2)") \
                                            __post __valid __refparam
#define __in_awcount(expr,size)             __pre __valid \
                                            __pre __deref __readonly \
                                            __in_xcount("__precond(" #expr ") __byte_readableTo(" #size ")") \
                                            __in_xcount("__precond(!(" #expr ")) __elem_readableTo(" #size ")")
#endif // #if (defined(_MSC_VER) && (_MSC_VER < 1400))
#define __allocator                         __inner_allocator
#define __bound                             __inner_bound
#define __range(lb,ub)                      __inner_range(lb,ub)
#define __in_bound                          __pre __inner_bound
#define __out_bound                         __post __inner_bound
#define __deref_out_bound                   __post __deref __inner_bound
#define __in_range(lb,ub)                   __pre __inner_range(lb,ub)
#define __out_range(lb,ub)                  __post __inner_range(lb,ub)
#define __deref_in_range(lb,ub)             __pre __deref __inner_range(lb,ub)
#define __deref_out_range(lb,ub)            __post __deref __inner_range(lb,ub)
#define __field_range(lb,ub)                __range(lb,ub)
#define __field_data_source(src)            __inner_data_source(src)
#define __in_data_source(src)               __pre __inner_data_source(src)
#define __out_data_source(src)              __post __inner_data_source(src)
#define __out_validated(type)               __inner_out_validated(type)
#define __transfer(formal)                  __post __inner_transfer(formal)
#define __file_parser(type)                 __inner_file_parser(type)
#define __file_parser_class(type)           __inner_file_parser_class(type)
#define __file_parser_library(type)         __inner_file_parser_library(type)
#define __rpc_entry                         __inner_control_entrypoint(RPC)
#define __kernel_entry                      __inner_control_entrypoint(UserToKernel)   
#define __gdi_entry                         __inner_control_entrypoint(GDI)
#define __encoded_pointer                   __inner_encoded
#define __encoded_array                     __inner_encoded
#define __field_encoded_pointer             __inner_encoded
#define __field_encoded_array               __inner_encoded
#define __type_has_adt_prop(adt,prop)       __$adt_prop(adt,prop)
#define __out_has_adt_prop(adt,prop)        __post __$adt_add_prop(adt,prop)
#define __out_not_has_adt_prop(adt,prop)    __post __$adt_remove_prop(adt,prop)
#define __out_transfer_adt_prop(arg)        __post __$adt_transfer_prop(arg)
#define __out_has_type_adt_props(typ)       __post __$adt_type_props(typ)
/* declare stub functions for macros */
__inner_assume_validated_dec 
__inner_assume_bound_dec 

#define __assume_validated(p) __inner_assume_validated(p)
#define __assume_bound(i) __inner_assume_bound(i)
#ifdef  __cplusplus
}
#endif
#include <wmspecstrings_adt.h>
#ifdef _PREFIX_
/**************************************************************************
* Defintion of __pfx_assume and __pfx_assert. Thse should be the only
* defintions of these functions.  
***************************************************************************/
#if __cplusplus
extern "C" void __pfx_assert(bool, const char *);
extern "C" void __pfx_assume(bool, const char *);
#else
void __pfx_assert(int, const char *);
void __pfx_assume(int, const char *);
#endif
/**************************************************************************
* Redefintion of __analysis_assume and __analysis_assert for PREFIX build
**************************************************************************/
#undef  __analysis_assume
#undef  __analysis_assert
#define __analysis_assume(e) (__pfx_assume(e,"pfx_assume"),__assume(e));
#define __analysis_assert(e) (__pfx_assert(e,"pfx_assert"),__assume(e));
#endif /* ifdef _PREFIX_ */
/**************************************************************************
* This include should always be the last thing in this file. 
* Must avoid redfinitions of macros to workaround rc.exe issues. 
***************************************************************************/
#ifndef RC_INVOKED
#include <wmspecstrings_strict.h>
#endif /* RC_INVOKED */
#endif /* #ifndef SPECSTRINGS_H */

// Some CE versions don't have specstrings.h, some have very old version without
// __specstrings defined. So we handle CE separately in wmasalce.h
#if defined(UNDER_CE) || defined(NO_WINDOWS)
  #include "wmspecstringce.h"
#endif

#endif //_WMSPECSTRING_H_
