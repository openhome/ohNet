/*
This software module was originally developed by Apple Computer, Inc.
in the course of development of MPEG-4. 
*/

#ifndef INCLUDED_MP4OSMACROS_H
#define INCLUDED_MP4OSMACROS_H

/* includes not used by the library, but harmless & used by programs using the library - dws */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

#ifndef TEST_RETURN
#define TEST_RETURN(err)
/*#define TEST_RETURN(err) assert((err)==0)*/
#endif

#define MP4_EXTERN(v) extern v

#if 1
typedef long long u64;
typedef long long s64;

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;
typedef short s16;
typedef char s8;
#else

typedef uint64_t u64;
typedef int64_t s64;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint8_t u8;
typedef int8_t s8;

#endif

#define MP4_FOUR_CHAR_CODE( a, b, c, d ) (((a)<<24)|((b)<<16)|((c)<<8)|(d))

#endif
