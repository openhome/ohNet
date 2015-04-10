/*
   independent channel concealment
 */

#ifndef CONCEAL_H
#define CONCEAL_H
#include "channel.h"
#include "channelinfo.h"


#define MAXSFB  51            /*!< maximum number of scalefactor bands  */
#define MAX_FADE_FRAMES 8     /*!< maximum number of frames for ramp down / ramp up */

typedef enum{
  CConcealment_Uninitialized = -1,
  CConcealment_Ok         = 0x0000,
  CConcealment_Interpolate= 0x0001,
  CConcealment_FadeOut    = 0x0002,
  CConcealment_Mute       = 0x0004,
  CConcealment_Suppressed = 0x0008, 
  CConcealment_FadeIn     = 0x0010
} CConcealmentState;

typedef struct
{
  Word32   SpectralCoefficient[Channels][FRAME_SIZE]; /*!< Spectral data of previous frame   */
  Word16   SpecScale[Channels][MAX_WINDOWS];          /*!< Scaling factors of previous frame */
  Word16    WindowShape[Channels];                     /*!< Window shape of previous frame */
  Word16    WindowSequence[Channels];                  /*!< Block type of previous frame */ 
  Flag     prevFrameOk[Channels][2];                  /*!< Stores frameOK flag of two previous frames */
  Word16   cntConcealFrame[Channels];                 /*!< Counter of concealed frames */
  CConcealmentState ConcealState[Channels];           /*!< Status of concealment state machine */

  Word16   iRandomPhase;                              /*!< Index into random phase table */
} CConcealmentInfo;


typedef enum {
  CConcealment_NoExpand,
  CConcealment_Expand,
  CConcealment_Compress
} CConcealmentExpandType;


CConcealmentInfo*
CConcealment_Init (Word16 ch);

void
CConcealment_Apply (CConcealmentInfo *pConcealmentInfo,
                    Word32 *pSpectralCoefficient,
                    Word16 *pSpecScale,
                    CIcsInfo *pIcsInfo,
                    Word16 ch,
                    Flag frameOK
                    );

#endif /* #ifndef CONCEAL_H */
