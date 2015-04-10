/*
   DSP specific implementation of vector functions
 */
   
#include <assert.h>
#include "ffr.h"
#include "count.h"


/*!
 *
 *  \brief Calculate max possible scale factor for input vector
 *
 *  \return Maximum scale factor
 *
 */
Word16 ffr_getScalefactorOfWord32Vector(const Word32 *vector, /*!< Pointer to input vector */ 
                                        Word16 len)           /*!< Length of input vector */
{
  Word32 maxVal = 1;
  Word32 absVal;
  Word16 i;

  for(i=0; i<len; i++){
    absVal = L_abs(vector[i]);
    maxVal |= absVal; logic32();
  }

  test();
  return maxVal ? ffr_norm32(maxVal) : 31;
}


/*!
 *
 *  \brief Calculate max possible scale factor for input vector of shorts
 *
 *  \return Maximum scale factor
 *
 */
Word16 ffr_getScalefactorOfShortVector(const Word16 *vector, /*!< Pointer to input vector */
                                       Word16 len)           /*!< Length of input vector */
{
  Word16 maxVal = 1;
  Word16 absVal;
  Word16 i;

  for(i=0; i<len; i++){
    absVal = abs_s(vector[i]);
    maxVal |= absVal; logic16();
  }
  test();
  return  maxVal ? norm_s(maxVal) : 15;
}

/*!
 *
 *  \brief Calculate max possible scale factor for input vector of shorts
 *
 *  \return Maximum scale factor
 *
 */
Word16 ffr_getScalefactorOfShortVectorStride(const Word16 *vector, /*!< Pointer to input vector */
                                             Word16 len,           /*!< Length of input vector */
                                             Word16 stride)        /*!< Stride of input vector */
{
  Word16 maxVal = 0;
  Word16 absVal;
  Word16 i;

  for(i=0; i<len; i++){
    absVal = abs_s(vector[i*stride]);
    maxVal |= absVal; logic16();
  }
  test();
  return( maxVal ? norm_s(maxVal) : 15);
}



/*!
 *
 *  \brief  Multiply input vector by \f$ 2^{scalefactor} \f$
 *
 *  \return
 *
 */
void ffr_scaleWord32Vector(Word32 *vector,     /*!< Vector */
                           Word32 len,         /*!< Length */
                           Word16 scalefactor) /*!< Scalefactor */
{
  Word32 i;

  for (i=0; i<len; i++)
  {
    vector[i] = L_shl(vector[i],scalefactor); move32();
  }

}


/*!                               
 *
 *  \brief Multiply input vector of shorts by \f$ 2^{scalefactor} \f$
 *
 *  \return Scaled input
 *
 */
void ffr_scaleShortVector(Word16 *vector,   /*!< Vector */
                          Word32 len,         /*!< Length */
                          Word16 scalefactor) /*!< Scalefactor */
{
  Word32 i;

  for (i=0; i<len; i++)
  {
    vector[i] = shl(vector[i],scalefactor); move16();
  }

}


