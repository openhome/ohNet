#ifndef __ALAC__DECOMP_H
#define __ALAC__DECOMP_H

#include "bool.h"

typedef struct alac_file alac_file;

alac_file *create_alac(int samplesize, int numchannels);
bool decode_frame(alac_file *alac,
                  unsigned char *inbuffer,
                  void *outbuffer, int *outputsize);
void alac_set_info(alac_file *alac, char *inputbuffer);
void alac_free_buffers(alac_file *alac);

#endif /* __ALAC__DECOMP_H */

