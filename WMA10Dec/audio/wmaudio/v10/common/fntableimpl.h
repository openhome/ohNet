//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

void prvFnTableInterpZero(FnTableInterp *p)
{
  memset(p, 0, sizeof(FnTableInterp));
}

void prvFnTableInterpFree(FnTableInterp *p)
{
  if (NULL==p) return;
  auFree(p->m_pTableBase);
  prvFnTableInterpZero(p);
}

WMARESULT prvFnTableInterpInit(FnTableInterp *p,
                        Int tableBits, Int msb,
                        Int offset,
                        Int startPoint, Int endPoint,
                        TableType (*pfnVal)(Int x, Int nFn),
                        TableType (*pfnSlope)(Int x, Int y, Int diff, Int nFn),
                        Int nFn,
                        TableType *valTable,
                        TableType *slopeTable,
                        Bool fUseSlope)
{
  WMARESULT wr = WMA_OK;
  Int numEntries, alloc;
  I32 i, sample, nextSample;
  TableType *base = NULL;

  if (p->m_pTableBase != NULL) {
    wr = WMA_E_INVALIDARG;
    goto exit;
  }
  if ((valTable == NULL && pfnVal == NULL) ||
      (slopeTable == NULL && pfnSlope == NULL)) {
    wr = WMA_E_INVALIDARG;
    goto exit;
  }

  p->m_remBits = msb - tableBits;
  p->m_tableMask = ((1<<tableBits) - 1) << p->m_remBits;
  p->m_remMask = (1<<p->m_remBits)-1;

  p->m_offset = offset;
  p->m_fUseSlope = fUseSlope;

  if (endPoint <= startPoint) endPoint = (1<<tableBits) + startPoint;
  numEntries = endPoint - startPoint;

  alloc = 0;
  if (valTable == NULL) alloc += numEntries + 1;
  if (p->m_fUseSlope) {
    if (slopeTable == NULL) alloc += numEntries + 1;
  }

  if (alloc > 0) {
    p->m_pTableBase = (TableType*)auMalloc(alloc*sizeof(TableType));
    if (p->m_pTableBase == NULL) {
      wr = WMA_E_OUTOFMEMORY;
      goto exit;
    }
  }

  base = p->m_pTableBase;
  if (valTable == NULL) {
    p->m_pTableVal = base - startPoint;
    base += numEntries + 1;
  } else {
    p->m_pTableVal = valTable - startPoint;
  }
  if (p->m_fUseSlope) {
    if (slopeTable == NULL) {
      p->m_pTableSlope = base - startPoint;
      base += numEntries + 1;
    } else {
      p->m_pTableSlope = slopeTable - startPoint;
    }
  }
  if (valTable == NULL || slopeTable == NULL) {
    for (i=startPoint; i <= endPoint; i++) {
      sample = i << (I32)p->m_remBits;
      nextSample = (i+1) << p->m_remBits;
      sample += p->m_offset;
      nextSample += p->m_offset;
      if (valTable == NULL)
        p->m_pTableVal[i] = (*pfnVal)(sample, nFn);
      if (p->m_fUseSlope) {
        if (slopeTable == NULL)
          p->m_pTableSlope[i] = (*pfnSlope)(sample, nextSample,
                                            1<<p->m_remBits, nFn);
      }
    }
  }

exit:
  return wr;
}

INLINE TableType prvGetFnTable(FnTableInterp *p, I32 sample)
{
  I32 index, rem;

  sample -= p->m_offset;
  index = (sample & p->m_tableMask) >> p->m_remBits;
  rem = sample & p->m_remMask;
  assert(((index<<p->m_remBits) | rem) == sample);

  if (p->m_fUseSlope) {
    return
      p->m_pTableVal[index] +
      ((TableType)rem*p->m_pTableSlope[index]);
  } else {
#ifdef BUILD_INTEGER
    return
      p->m_pTableVal[index] +
      (((TableType)rem*
        (p->m_pTableVal[index+1]-p->m_pTableVal[index])) >>
       p->m_remBits);
#else
    return
      p->m_pTableVal[index] +
      ((TableType)rem*
       (p->m_pTableVal[index+1]-p->m_pTableVal[index])/
       (1<<p->m_remBits));
#endif
  }
}

