

//#include <stddef.h>
#include "wmatypes.h"
#include "wmawintypes.h"
//#include "wmaudio_inc.h"
#include "wmaudio.h"
#include "macros.h"
#include "pcmfmt.h"




#define kCodec 0x1 //temp
#define LOG(x,...)

//#define WMALOSSLESS_TO_PCM




time_t g_ulFullSec = 0;
time_t g_ulOutputSamples = 0;
unsigned int  g_SampleRate;

#define MAX_SAMPLES 16384
short g_pLeft [MAX_SAMPLES * 2]; // expand the container for 24-bit samples
short g_pRight [MAX_SAMPLES * 2]; // expand the container for 24-bit samples

tWMAFileHdrState g_hdrstate;
tHWMAFileState g_state;
tWMAFileHeader g_hdr;


void decodeWMA()
{
Bool bDropPacket = FALSE;
U16 nDecoderFlags = 0; 
U16 nDRCSetting = 0; 
U32 nDstChannelMask = 0;
U32 nInterpResampRate = 0;
U16 nMBRTargetStream = 1;



// from original main() for arm...
    //fold-down to 2 channels, -cm 0x03
    nDecoderFlags  |= DECOPT_CHANNEL_DOWNMIXING;
    nDstChannelMask = (U32) 0x03;

    //resample to 16 bits, -pcm 16
    nDecoderFlags |= DECOPT_REQUANTTO16;

    //downsample to 44.1 or 48 kHZ
    nDecoderFlags |= DECOPT_DOWNSAMPLETO44OR48;
//

    tWMA_U32 msSeekTo;

    PCMFormat pcmFormat;
    
    tWMAFileStatus rc;
    tWMA_U32 num_samples;
    tWMA_U32 nDecodedSamples;
    tWMA_U32 cFetchedSamples;
    int cCountGetPCM = 0;
    tWMAExtendedContentDesc const *pECDesc;
    int iRV = 1;    // assume error exit return value
    tWMA_U16 wMBRTotalStreams = 0;



    // reset global values for each file call.
    g_ulFullSec = 0;
    g_ulOutputSamples = 0;


    tWMAFileContDesc const *pdesc = 0;

   
    /* init struct */
    memset ((void *)&g_hdrstate, 0, sizeof(g_hdrstate));
    memset ((void *)&g_state, 0, sizeof(g_state));
    memset ((void *)&g_hdr, 0, sizeof(g_hdr));


    /* test the checking API */
    rc = WMAFileSetTargetMBRAudioStream(&g_hdrstate, nMBRTargetStream);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Error while setting target stream number.\n");
        goto lexit;
    }
    
    rc = WMAFileIsWMA (&g_hdrstate);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** The file is not a WMA file.\n");
        goto lexit;
    }

    // Check for MBR
    rc = WMAFileMBRAudioStreams(&g_hdrstate, &wMBRTotalStreams);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Error while verifying MBR information.\n");
        goto lexit;
    }

    if (wMBRTotalStreams > 1)
    {
        LOG(kCodec, "\n** This is an MBR (Multiple Bit Rates) file\n");
        LOG(kCodec, stdout, "Decoding audio stream %d out of %d audio streams\n", 
            nMBRTargetStream, wMBRTotalStreams);
        LOG(kCodec, "Use -mbr option to decode a different stream\n\n");
    }

    /* init the decoder */

    rc = WMAFileDecodeCreate (&g_state);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Cannot create the WMA decoder.\n");
        goto lexit;
    }
    
    rc = WMAFileDecodeInitEx (g_state, nDecoderFlags, nDRCSetting, bDropPacket,
                              nDstChannelMask, nInterpResampRate, &pcmFormat,
                              nMBRTargetStream);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Cannot initialize the WMA decoder.\n");
        goto lexit;
    }
#ifdef WMALOSSLESS_TO_PCM
    rc = WMAFileIsLosslessWMA (g_state);
    if (rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Unsupported input format. Must be WMA Lossless.\n");
        goto lexit;        
    }
#endif //WMALOSSLESS_TO_PCM

    
    /* get header information */

    rc = WMAFileDecodeInfo (g_state, &g_hdr);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Failed to retrieve information.\n");
        goto lexit;
    }

    /* get content description */

    rc = WMAFileContentDesc (g_state, &pdesc);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Failed to retrieve content description.\n");
        goto lexit;
    }

    /* display information */

    if (pdesc != 0)
    {
/*
        unsigned char szTemp [STRING_SIZE];
        szTemp[0] = 0;
        wcstombs(szTemp, (wchar_t*)pdesc->pTitle, pdesc->title_len);
        LOG(kCodec, "++            Song title: %s\n", szTemp);
        szTemp[0] = 0;
        wcstombs(szTemp, (wchar_t*)pdesc->pAuthor, pdesc->author_len);
        LOG(kCodec, "++                Author: %s\n", szTemp);
        szTemp[0] = 0;
        wcstombs(szTemp, (wchar_t*)pdesc->pCopyright, pdesc->copyright_len);
        LOG(kCodec, "++             Copyright: %s\n", szTemp);
        szTemp[0] = 0;
        wcstombs(szTemp, (wchar_t*)pdesc->pDescription, pdesc->description_len);
        LOG(kCodec, "++           Description: %s\n", szTemp);
        szTemp[0] = 0;
        wcstombs(szTemp, (wchar_t*)pdesc->pRating, pdesc->rating_len);
        LOG(kCodec, "++                Rating: %s\n", szTemp);
*/
    }

    rc = WMAFileExtendedContentDesc (g_state, &pECDesc);

    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Failed to retrieve extended content description.\n");
        goto lexit;
    }

    LOG(kCodec, "++ WMA bitstream version: %d\n", g_hdr.version);
    LOG(kCodec, "++         sampling rate: %ld Hz\n", g_hdr.sample_rate);
    g_SampleRate = g_hdr.sample_rate;
    LOG(kCodec, "++         # of channels: %d\n", g_hdr.num_channels);
    LOG(kCodec, "++              bit-rate: %ld bps\n", g_hdr.bitrate);
    LOG(kCodec, "++              duration: %ld ms\n", g_hdr.duration);
    LOG(kCodec, "++           DRM content: %s\n", g_hdr.has_DRM ? "Yes" : "No");




    /* decoding loop */

    msSeekTo = 0;
    do
    {

        rc = WMAFileDecodeData(g_state, &nDecodedSamples);


        if(rc != cWMA_NoErr)
        {
            //wchen: I don't understand why failed is normal
            if ( rc == cWMA_NoMoreFrames || rc == cWMA_Failed )
            {
                iRV = 0;        // normal exit
                break;
            }
            else {
                iRV = 2;        // error decoding data
                LOG(kCodec, "DECODING ERR: decoding failed");                
                goto lexit;
            }            
        }

        cFetchedSamples = 0;

        if( 0 < nDecodedSamples ) do
        { 
            tWMA_I64 tPresTime = 0;

            cCountGetPCM++;

            assert(cFetchedSamples <= nDecodedSamples);
            num_samples = WMAFileGetPCM (g_state, g_pLeft, g_pRight, sizeof(g_pLeft),
                nDecodedSamples - cFetchedSamples, &tPresTime);

            cFetchedSamples += num_samples; 
            if (num_samples == 0)
            {
                /* no more, so on with the decoding... */
                break;
            }


// #define BREAK_AT_SAMPLE 146431 /* tough_16m_16.wma overflow of noise_subst_level in next frame */
//#define BREAK_AT_SAMPLE 50680  /* dire_200k_wmaV1_16k16kHzM.wma unstable frame after this */
//#define BREAK_AT_SAMPLE 68000 
#ifdef BREAK_AT_SAMPLE
            if ( g_ulOutputSamples <= BREAK_AT_SAMPLE && BREAK_AT_SAMPLE < (g_ulOutputSamples+num_samples) )
            { int j; j = (int)g_ulOutputSamples; }
#endif //BREAK_AT_SAMPLE

            g_ulOutputSamples += num_samples;

        } while(cFetchedSamples <  nDecodedSamples);
        assert (cFetchedSamples == nDecodedSamples);

    } while (1);



    LOG(kCodec, "Full Read and Decode took %d s.\r\nPlay Time would be %d s.\r\n",
        (UInt)g_ulFullSec, (UInt)(g_ulOutputSamples/g_SampleRate));





lexit:



    WMAFileDecodeClose (&g_state);
}




tWMA_U32 WMAFileCBGetData (
    tHWMAFileState state,
    tWMA_U64 offset,
    tWMA_U32 num_bytes,
    tWMA_U8  **ppData)
{
    U32 bytesRead = 0;
                                                 //ToDo !!! - Read()
    return bytesRead;
}


// need to provide a platform independent fprintf to stderr for wmaudio.c and wmaudio_parse.c
void WMADebugMessage(const char* pszFmt, ... )
{
}
