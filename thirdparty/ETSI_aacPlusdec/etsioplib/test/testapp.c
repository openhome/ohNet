/*
 * test application to check that the etsi-ops and the WMOPS counting
 * works as expected
 *
 * $Id: count.h,v 1.2 2004/06/23 13:30:55 ehr Exp
 */

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "basic_op.h"
#include "oper_32b.h"
#include "count.h"

#define FRAME_LEN 2048

int main(int argc, char **argv)
{ 
  int cntId1, samples, i, frameCnt=0;
  FILE *inputFile;
  FILE *outputFile;

  short inputBuffer[FRAME_LEN];
  short outputBuffer[FRAME_LEN];
  Word32 workBuffer[FRAME_LEN];

  if ( argc != 3 ) {
    fprintf(stderr, "\nUsage: %s <inputfile> <outputfile>", argv[0]);
    fprintf(stderr, "\nBoth files are expected to be raw PCM data files\n");
    exit(-1);
  }

  if ( (inputFile = fopen( argv[1], "rb" )) == NULL ) {
    fprintf( stderr, "can't open input file for reading\n" );
    goto error_exit;
  }

  
  if ( (outputFile = fopen( argv[2], "wb" )) == NULL ) {
    fprintf( stderr, "can't open output file for writing\n" );
    goto error_exit;
  }

  /* initiate counter */
  cntId1=getCounterId("Sample operation");
  setCounter(cntId1); 
  Init_WMOPS_counter();

  
  /* processing loop */
  do {
    Word16 fac = 2;

    /* set counter per frame */
    setCounter(cntId1); 
    Reset_WMOPS_counter ();

    /* read data from file */
    samples = fread (inputBuffer, sizeof(short), FRAME_LEN, inputFile);

    /* the operation */
    for (i=0; i<samples; i++) {
      workBuffer[i] = L_mult (fac, (Word16) inputBuffer[i]);
    }

    /* store worst case counter */
    fwc();
    
    /* cast to short, write data to file */
    for (i=0; i<samples; i++) {
      outputBuffer[i] = (short) workBuffer[i];
    }
    fwrite (outputBuffer, sizeof(short), FRAME_LEN, outputFile);
    
    fprintf(stderr,"\rFrame [%d]",frameCnt);
    frameCnt++;

  } while (samples>0);
  
  WMOPS_output(0);

 error_exit:

  if (inputFile)
    fclose (inputFile);

  if (outputFile)
    fclose (outputFile);

  return 0;
}
