//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include <stdio.h>
#include "wmatypes.h"
#include "crc.h"

#define CRC32B_POLY     (0xedb88320) // 11101101101110001000001100100000 CRC-32B
#define CRC16ANSI_POLY  (0xa001)     // 1010000000000001 - CRC-16-ANSI
#define CRC16CCITT_POLY (0x8408)     // 1000010000001000 - CRC-16-CCITT
#define CRC16SDLC_POLY  (0xe905)     // 1110100100000101 - CRC-16-SDLC
#define CRC24_POLY      (0x808a01)   // 100000001000101000000001 - CRC-24

#if (CRC_BITS==16)
#define CRC_POLY CRC16ANSI_POLY
#elif (CRC_BITS==24)
#define CRC_POLY CRC24_POLY
#elif (CRC_BITS==32)
#define CRC_POLY CRC32B_POLY
#else
#error "No polynomial defined"
#endif

#if 1

// CRC Table for CRC16-ANSI
const CRCType g_CRCTable[256] = {
    0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
    0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
    0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
    0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
    0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
    0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
    0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
    0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
    0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
    0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
    0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
    0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
    0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
    0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
    0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
    0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
    0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
    0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
    0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
    0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
    0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
    0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
    0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
    0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
    0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
    0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
    0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
    0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
    0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
    0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
    0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
    0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040,
};

void InitCRCTable()
{
}

#else

CRCType g_CRCTable[256];
Int g_CRCTableInit = 0;

// build lookup table
void InitCRCTable()
{
    CRCType i, j, iCRC;

    if (g_CRCTableInit) return;

    for (i=0; i < 256; i++)
    {
        iCRC = i;
        for (j=8; j > 0; j--)
        {
            if (iCRC & 0x1)
                iCRC = (iCRC >> 1) ^ CRC_POLY;
            else
                iCRC = (iCRC >> 1);
        }
        g_CRCTable[i] = iCRC;
    }

    g_CRCTableInit = 1;
}

#endif

void InitCRC(CRCType *puCRC)
{
    CRCType mask;

    if (NULL==puCRC) return;

#if (CRC_BITS == 32) 
    mask = (CRCType)0xffffffff;
#else 
    mask = (1<<CRC_BITS)-1;
#endif

    *puCRC = mask;
}

/*
  The following simplifications are used when going from table based method
  to bit based method.
  If we know byte ordering, then can operate directly on int32, but
  else we may have to swap on some platforms depending on endianness.
#if 0
        CRCType val = (uPrevCRC & 0xff) ^ pBuf[i];
        for (j=8; j > 0; j--)
        {
            if (val & 0x1)
                val = (val >> 1) ^ CRC_POLY;
            else
                val = (val >> 1);
        }
        uPrevCRC = (uPrevCRC>>8) ^ val;
#elif 0
        CRCType bit, val = pBuf[i];
        for (j=8; j > 0; j--)
        {
            bit = (uPrevCRC ^ val) & 0x1;
            if (bit & 0x1)
                bit = CRC_POLY;
            else
                bit = 0;
            uPrevCRC = (uPrevCRC>>1) ^ bit;
            val >>= 1;
        }
#elif 1
        CRCType bit, val = pBuf[i];
        for (j=8; j > 0; j--)
        {
            bit = (uPrevCRC ^ val) & 0x1; // equivalent (uPrevCRC>>15) & bit
            uPrevCRC >>= 1;
            if (bit)
                uPrevCRC ^= CRC_POLY;
            val >>= 1;
        }
#endif
*/

#define USE_CRC_TABLE

// generate crc
void GenerateCRC(const U8 *pBuf,
                 const Int cBuf,
                 CRCType *puCRC)
{
    Int i;
    CRCType uPrevCRC;

    uPrevCRC = *puCRC;
    for (i=0; i < cBuf; i++)
    {
#ifdef USE_CRC_TABLE
        uPrevCRC = (uPrevCRC>>8) ^ g_CRCTable[(uPrevCRC & 0xff) ^ pBuf[i]];
#else
        Int j;
        CRCType bit, val = pBuf[i];
        for (j=8; j > 0; j--)
        {
            bit = (uPrevCRC ^ val) & 0x1; // equivalent (uPrevCRC>>15) & bit
            uPrevCRC >>= 1;
            if (bit)
                uPrevCRC ^= CRC_POLY;
            val >>= 1;
        }
#endif
    }
    *puCRC = uPrevCRC;
}

void GetCRC(CRCType *puCRC)
{
    CRCType mask;

    if (NULL==puCRC) return;

    InitCRC(&mask);
    *puCRC ^= mask;
}

#ifdef CRC_TEST_STANDALONE
#include <windows.h>

void main(Int argc, LPCTSTR argv[])
{
    //U8 buf[] = {0x32, 0x5f, 0x21, 0x9a, 0xa4, 0x23, 0x54, 0xd3, 0xac, 0xe4};
    U8 buf[] = {'A', 'B', 'C'};
    CRCType uCRC;
    FILE *fp = NULL;

    InitCRCTable(); // needed only once

    InitCRC(&uCRC); // will set uCRC to initial value

    if (argc == 2) {
      fp = fopen(argv[1], "rb");
      if (fp == NULL) goto exit;
      while (fread(buf, 1, 1, fp)) {
        GenerateCRC(buf, 1, &uCRC);
      }
    } else {
      GenerateCRC(buf, 3, &uCRC); // update CRC, call as many times as needed
    }

    GetCRC(&uCRC); // will modify final value to "true" CRC value

    printf("CRC = %x\n", uCRC);

#if 0
    {
      Int i;

      for (i=0; i < 256; i++)
      {
        if (i % 8 == 0) printf("\n");
        printf("0x%04x, ", g_CRCTable[i]);
      }
    }
#endif

exit:
    if (fp) fclose(fp);
}

#endif

