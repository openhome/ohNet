//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

// table interpolationg of function -- template on TableType

#ifndef FN_TABLE_H
#define FN_TABLE_H

typedef struct {

  TableType *m_pTableBase;
  TableType *m_pTableVal;
  TableType *m_pTableSlope;

  Int m_offset;

  U32 m_tableMask;
  UInt m_remBits;
  U32 m_remMask;

  Bool m_fUseSlope;

  Int m_maxVal;

} FnTableInterp;

// sample-offset must be in {0,...,tableMask|remMask}
// sample must be in {offset,...,tableMask|remMask+offset}
INLINE Int FnTableMinVal(FnTableInterp *p)
{
  return p->m_offset;
}

INLINE Int FnTableMaxVal(FnTableInterp *p)
{
  return (Int)(p->m_tableMask | p->m_remMask) + p->m_offset;
}

void prvFnTableInterpZero(FnTableInterp *p);
void prvFnTableInterpFree(FnTableInterp *p);
WMARESULT prvFnTableInterpInit(FnTableInterp *p,
                        Int tableBits, Int msb,
                        Int offset,
                        Int startPoint, Int endPoint,
                        TableType (*pfnVal)(Int x, Int nFn),
                        TableType (*pfnSlope)(Int x, Int y, Int diff, Int nFn),
                        Int nFn,
                        TableType *valTable,
                        TableType *slopeTable,
                        Bool fUseSlope);

#include "fntableimpl.h"

#endif

