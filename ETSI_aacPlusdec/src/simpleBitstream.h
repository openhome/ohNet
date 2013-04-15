/*
   simple bitstream handler
 */

#if !defined (__simpleBitstream_H__)
#define __simpleBitstream_H__

typedef struct simpleBitstream
{
  const unsigned char *buffer ;

  unsigned int readBits ;

  unsigned int dataWord ;
  unsigned int validBits ;

} simpleBitstream, *simpleBitstreamPtr ;

static void __initializeBitstream (simpleBitstreamPtr self, const unsigned char *p)
{
  self->validBits = self->readBits = self->dataWord = 0 ;

  self->buffer = p ;
}

static int __getBits (simpleBitstreamPtr self, const unsigned int numberOfBits)
{
  if (self->validBits <= 16)
  {
    self->validBits += 16 ;
    self->dataWord <<= 16 ;

    self->dataWord |= (unsigned int) *self->buffer++ << 8 ;
    self->dataWord |= (unsigned int) *self->buffer++ ;
  }

  self->readBits += numberOfBits ;
  self->validBits -= numberOfBits ;

  return ((self->dataWord >> self->validBits) & ((1L << numberOfBits) - 1)) ;
}

static int __getReadBits(simpleBitstreamPtr self)
{
  return self->readBits;
}
#endif
