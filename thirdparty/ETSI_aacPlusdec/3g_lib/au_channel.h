/* general audio library wrapper */

#ifndef __AU_CHANNEL_H
#define __AU_CHANNEL_H

#define KSDATAFORMAT_SUBTYPE_PCM   "\x01\x00\x00\x00\x00\x00\x10\x00\x80\x00\x00\xaa\x00\x38\x9b\x71"
#define KSDATAFORMAT_SUBTYPE_FLOAT "\x03\x00\x00\x00\x00\x00\x10\x00\x80\x00\x00\xaa\x00\x38\x9b\x71"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  WAVE_EXT_TYPE_PCM = 0,
  WAVE_EXT_TYPE_FLOAT
};


  typedef void* hAudioChannel;
  
  typedef struct {
    char date[20];
    char versionNo[20];
  } AuChanLibInfo;

  typedef struct {
    int   card;       /**< alsa only */
    int   device;     /**< alsa/Win32 ASIO only; Win32: For ASIO in-/output set device = 1, else set device = 0 */
    float level;
    int   inputSource;
    int   outputDrain;
  } AuChanInfoRT;

  typedef struct {
    int   bitrate;
    int   ID;
    int   flags;
    int   blockSize;
    int   framesPerBlock;
    int   codecDelay;
  } AuChanInfoMP3;

  typedef struct {
    int   bitrate;
    int   ID;
    int   flags;
    int   profile;
    int   channelConfiguration;
    int   nPrograms;
    int   codecDelay;
  } AuChanInfoAAC;

  typedef struct {
    long   valBitsPerSample;
    long   channelMask;
    long   subFormat;
  } AuChanInfoWaveExt;

  typedef union {
    AuChanInfoRT  rt;
    AuChanInfoMP3 mp3;
    AuChanInfoAAC aac;
  } typeSpecInfo;

  typedef struct {
    int    valid;
    int    bitsPerSample;
    int    sampleRate;
    int    nChannels;
    long   nSamples;
    int    isLittleEndian;
    double fpScaleFactor;    /**< for scaling floating point values */
    typeSpecInfo typeInfo;
    int    useWaveExt;
    AuChanInfoWaveExt wavex;
  } AuChanInfo;

  /* error codes */

  typedef enum {
    AU_CHAN_OK=0,
    /* for open:*/
    AU_CHAN_FILE_INEXISTENT,
    AU_CHAN_OUT_OF_MEMORY,
    AU_CHAN_UNSUPPORTED_SETTINGS,
    AU_CHAN_BAD_SETTINGS_COMBINATION,
    AU_CHAN_INFO_INVALID,
    AU_CHAN_OPEN_FAILED,

    /* for read/write/seek */
    AU_CHAN_READ_ERROR,
    AU_CHAN_WRITE_ERROR,
    AU_CHANNEL_READ_EXHAUSTED,
    AU_CHAN_SEEK_ERROR,

    AU_CHAN_UNIMPLEMENTED_FEATURE,
    AU_CHAN_GENERAL_ERROR
  } AuChanError;

  typedef enum {
    AU_CHAN_READ,
    AU_CHAN_READ_STDIN,
    AU_CHAN_WRITE,
    AU_CHAN_WRITE_STDOUT
  } AuChanMode;

  typedef enum {
    TYPE_AUTODETECT = 0,
    TYPE_AIFF,
    TYPE_AIFC,
    TYPE_RIFF,
    TYPE_SND,
    TYPE_PCM,
    TYPE_DVD,     /**< DVD raw data format (6 channels, 24 bits) */
    TYPE_MP3,     /**< MPEG-LAYER3 bitstream data in RIFF */
    TYPE_AAC,     /**< MPEG AAC bitstream data in RIFF */

    TYPE_VOID,
    TYPE_RT
  } AuChanType;

  /**
  Use to initialize soundcard of specified audio in-/output type
  */
  typedef enum {
    AU_CARD_NOTSPECIFIED,      /**< type not specified */
    AU_CARD_WINDOWSMM,         /**< Windows Multimedia audio in-/output */
    AU_CARD_ASIO               /**< ASIO audio in-/output */
  } AuChanSoundcard;

#ifdef WAVE_EXTENSIBLE

#define SPEAKER_FRONT_LEFT            0x00001
#define SPEAKER_FRONT_RIGHT           0x00002
#define SPEAKER_FRONT_CENTER          0x00004
#define SPEAKER_LOW_FREQUENCY         0x00008
#define SPEAKER_BACK_LEFT             0x00010
#define SPEAKER_BACK_RIGHT            0x00020
#define SPEAKER_FRONT_LEFT_OF_CENTER  0x00040
#define SPEAKER_FRONT_RIGHT_OF_CENTER 0x00080
#define SPEAKER_BACK_CENTER           0x00100
#define SPEAKER_SIDE_LEFT             0x00200
#define SPEAKER_SIDE_RIGHT            0x00400
#define SPEAKER_TOP_CENTER            0x00800
#define SPEAKER_TOP_FRONT_LEFT        0x01000
#define SPEAKER_TOP_FRONT_CENTER      0x02000
#define SPEAKER_TOP_FRONT_RIGHT       0x04000
#define SPEAKER_TOP_BACK_LEFT         0x08000
#define SPEAKER_TOP_BACK_CENTER       0x10000
#define SPEAKER_TOP_BACK_RIGHT        0x20000

#endif

#define OUT_SPEAKER 1
#define OUT_HEADPHONE 2
#define OUT_LINE 4

#define IN_MIC 1
#define IN_LINE 2
#define IN_CD 4

  enum {
    MPEGLAYER3_ID_MPEG = 1,
    MPEGLAYER3_FLAG_PADDING_ISO = 2
  };

  /**
    Use to initialize soundcard(s) of specifified audio in-/output type AuChanSoundcard.
    The call of this function is optional and should be called before AuChannelOpen(). 
    Purpose of this function is actually to anticipate ASIO driver query.
      <ul>
        <li>AU_CARD_ASIO: Initializing ASIO soundcard(s), i.e. looking for the ASIO driver with the 
        most in-/output channels.</li>
        <li>AU_CARD_WINDOWSMM: Initializing Windows Multimedia soundcard(s). Actually does nothing.</li>
        <li>AU_CARD_NOTSPECIFIED: Initializing not specified soundcard(s). Actually does nothing.</li>
      </ul>
    The function returns AU_CHAN_OK on success and AU_CHAN_OPEN_FAILED on failure 
    (i.e. no soundcard of the specified type exist or it could not initialized).\n 
    Please note that ASIO functionality is actually only implemented for WIN32 systems.
  */
  AuChanError AuChannelSoundcardInit(AuChanSoundcard card);

  /**
    Use to get the name  of the actually used ASIO driver name. 
    The driver must already be preselected, either by a call of AuChannelOpen() or AuChannelSoundcardInit().
    The function returns AU_CHAN_OK on success and AU_CHAN_GENERAL_ERROR on failure, i.e. if no 
    ASIO driver is selected or ASIO is not supported by the system.

    Please note that ASIO functionality is actually only implemented for WIN32 systems.
  */
  AuChanError AuChannelGetAsioDriverName(char *driverName, long maxLenght);

  AuChanError AuChannelOpen ( hAudioChannel* audioChannel,
                              char const* filename,
                              AuChanMode mode,
                              AuChanType* type,
                              AuChanInfo* info);

  AuChanError AuChannelSeek ( hAudioChannel audioChannel, int nSamples );

  void AuChannelClose (hAudioChannel audioChannel);

#ifdef WAVE_EXTENSIBLE
  AuChanError AuChannelWriteDouble( hAudioChannel audioChannel,
                                    const double* samples,
                                    int nSamples,
                                    int* written);
#endif

  AuChanError AuChannelWriteLong( hAudioChannel audioChannel,
                                  const long* samples,
                                  int nBytes,
                                  int* written);

  AuChanError AuChannelWriteShort( hAudioChannel audioChannel,
                                   const short* samples,
                                   int nSamples,
                                   int* written);

  AuChanError AuChannelWriteFloat( hAudioChannel audioChannel,
                                   const float* samples,
                                   int nSamples,
                                   int* written);

  AuChanError AuChannelWriteBytes( hAudioChannel audioChannel,
                                   const char* bytes,
                                   int nBytes,
                                   int* written);

#ifdef WAVE_EXTENSIBLE
  AuChanError AuChannelReadDouble( hAudioChannel audioChannel,
                                   double* samples,
                                   int nSamples,
                                   int* read);

  AuChanError AuChannelReadLong( hAudioChannel audioChannel,
                                 long* samples,
                                 int nSamples,
                                 int* written);
#endif

#ifdef WIN32
  long AuWriteStdOut( const void *from, long bytes );

  long AuReadStdIn( void *to, long bytes );
#endif

  AuChanError AuChannelReadShort( hAudioChannel audioChannel,
                                  short* samples,
                                  int nSamples,
                                  int* written);

  AuChanError AuChannelReadFloat( hAudioChannel audioChannel,
                                  float* samples,
                                  int nSamples,
                                  int* read);

  AuChanError AuChannelReadBytes( hAudioChannel audioChannel,
                                   char* bytes,
                                   int nBytes,
                                   int* read);

  AuChanError AuChannelSetLevel( hAudioChannel audioChannel,
                                 int volume);

  AuChanError AuChannelParseFormatString(const char* format,
                                         AuChanInfo* info,
                                         AuChanType* type);

  void AuChannelGetLibInfo (AuChanLibInfo* libInfo);

#ifdef WAVE_EXTENSIBLE
  void print_channel_cnfg(long channelMask);
#endif

#ifdef __cplusplus
}
#endif


#endif /* AU_CHANNEL_H */
