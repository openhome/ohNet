//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
//+-------------------------------------------------------------------------
//
//  Microsoft Windows Media
//
//  Copyright (C) Microsoft Corporation, 1999 - 1999
//
//  File:       loadStuff.h
//
//--------------------------------------------------------------------------

#ifndef LOADSTUFF_H
#define LOADSTUFF_H

#ifdef _MSC_VER
#define LITTLE_ENDIAN
#endif

//#ifdef LITTLE_ENDIAN
#if 0 //avoid unligned access on devices

#define GetUnalignedWord( pb, w )   (w) = *(UNALIGNED WORD*)(pb); 

#define GetUnalignedDword( pb, dw ) (dw) = *(UNALIGNED DWORD*)(pb);

#define GetUnalignedQword( pb, qw ) (qw) = *(UNALIGNED QWORD*)(pb);

#define GetUnalignedDouble( pb, d ) (d) = *(UNALIGNED double*)(pb);

#else

#define GetUnalignedWord( pb, w ) \
            (w) = ((WORD) *(pb + 1) << 8) + *pb;

#define GetUnalignedDword( pb, dw ) \
            (dw) = ((DWORD) *(pb + 3) << 24) + \
                   ((DWORD) *(pb + 2) << 16) + \
                   ((DWORD) *(pb + 1) << 8) + *pb;

#define GetUnalignedQword( pb, qw ) \
            GetUnalignedDword( pb, (qw).dwLo ); \
            GetUnalignedDword( (pb + 4), (qw).dwHi );

#define GetUnalignedDouble( pb, d ) (d) = *(UNALIGNED double*)(pb);

#endif

#define GetUnalignedWordEx( pb, w )     GetUnalignedWord( pb, w ); (pb) += sizeof(WORD);
#define GetUnalignedDwordEx( pb, dw )   GetUnalignedDword( pb, dw ); (pb) += sizeof(DWORD);
#define GetUnalignedQwordEx( pb, qw )   GetUnalignedQword( pb, qw ); (pb) += sizeof(QWORD);
#define GetUnalignedDoubleEx( pb, d )   GetUnalignedDouble( pb, d ); (pb) += sizeof(double);

#define LoadBYTE( b, p )    b = *(BYTE *)(p);  (p) += sizeof( BYTE )

#define LoadWORD( w, p )    GetUnalignedWordEx( p, w )
#define LoadDWORD( dw, p )  GetUnalignedDwordEx( p, dw )
#define LoadQWORD( qw, p )  GetUnalignedQwordEx( p, qw )

#define LoadGUID( g, p ) \
        { \
            LoadDWORD( (g).Data1, p ); \
            LoadWORD( (g).Data2, p ); \
            LoadWORD( (g).Data3, p ); \
            LoadBYTE( (g).Data4[0], p ); \
            LoadBYTE( (g).Data4[1], p ); \
            LoadBYTE( (g).Data4[2], p ); \
            LoadBYTE( (g).Data4[3], p ); \
            LoadBYTE( (g).Data4[4], p ); \
            LoadBYTE( (g).Data4[5], p ); \
            LoadBYTE( (g).Data4[6], p ); \
            LoadBYTE( (g).Data4[7], p ); \
        }

#endif  // LOADSTUFF_H
