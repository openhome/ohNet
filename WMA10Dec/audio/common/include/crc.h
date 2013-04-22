//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __CRC_H_
#define __CRC_H_

#define CRC_BITS 16

#if (CRC_BITS == 16)
#define CRCType U16
#else // CRC_BITS == 24 or 32
#define CRCType U32
#endif

#ifdef __cplusplus
extern "C" {
#endif

void InitCRCTable();
void InitCRC(CRCType *puCRC);
void GenerateCRC(const U8 *pBuf, const Int cBuf, CRCType *puCRC);
void GetCRC(CRCType *puCRC);

#ifdef __cplusplus
}
#endif

#endif // crc.h
