/*
    ISOMovies.h: A wrapper for the code defined in the MPEG-4 library.
*/

#ifndef INCLUDED_ISOMOVIE_H
#define INCLUDED_ISOMOVIE_H

#ifndef INCLUDED_MP4MOVIE_H
#include "MP4Movies.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* These data types are common to both MPEG-4 and JPEG-2; ideally the "ISO" names should be used. */
#define ISOHandle                                   MP4Handle
#define ISOErr                                      MP4Err
#define ISOMovie                                    MP4Movie
#define ISOTrack                                    MP4Track
#define ISOMedia                                    MP4Media
#define ISOTrackReader                              MP4TrackReader
#define ISOUserData                                 MP4UserData
#define ISOAtomPtr                                  MP4AtomPtr
#define ISOLinkedList                               MP4LinkedList

#define ISO_EXTERN                                  MP4_EXTERN

/* These constants are common to both MPEG-4 and JPEG-2; ideally the "ISO" names should be used. */
#define ISOEOF                                      MP4EOF
#define ISONoErr                                    MP4NoErr
#define ISOFileNotFoundErr                          MP4FileNotFoundErr
#define ISOBadParamErr                              MP4BadParamErr
#define ISONoMemoryErr                              MP4NoMemoryErr
#define ISOIOErr                                    MP4IOErr
#define ISONoLargeAtomSupportErr                    MP4NoLargeAtomSupportErr
#define ISOBadDataErr                               MP4BadDataErr
#define ISOVersionNotSupportedErr                   MP4VersionNotSupportedErr
#define ISOInvalidMediaErr                          MP4InvalidMediaErr
#define ISODataEntryTypeNotSupportedErr             MP4DataEntryTypeNotSupportedErr
#define ISONoQTAtomErr                              MP4NoQTAtomErr
#define ISONotImplementedErr                        MP4NotImplementedErr

#define ISONewTrackIsVisual                         MP4NewTrackIsVisual
#define ISONewTrackIsAudio                          MP4NewTrackIsAudio
#define ISONewTrackIsPrivate                        MP4NewTrackIsPrivate

#define ISOVisualHandlerType                        MP4VisualHandlerType
#define ISOAudioHandlerType                         MP4AudioHandlerType

/* constants for the graphics modes (e.g. for MJ2SetMediaGraphicsMode) */
enum
{
    ISOGraphicsModeSrcCopy                          = 0x00000000,
    ISOGraphicsModeTransparent                      = 0x00000024,
    ISOGraphicsModeAlpha                            = 0x00000100,
    ISOGraphicsModeWhiteAlpha                       = 0x00000101,
    ISOGraphicsModeBlackAlpha                       = 0x00000102
};

/* These data types are specific to JPEG-2; however, they have "ISO" names. */
struct ISOMatrixRecord
{
    u32 data[9];
};
typedef struct ISOMatrixRecord ISOMatrixRecord;
typedef ISOMatrixRecord* ISOMatrix;

struct ISORGBColor
{
    u16 red;
    u16 green;
    u16 blue;
};
typedef struct ISORGBColor ISORGBColor;
typedef ISORGBColor* ISORGBColorPtr;


/* constants for the fileType field of the MP4PrivateMovieRecord structure */
enum
{
    ISOUnknownFileType                              = (u32)0,
    ISOMPEG4FileType                                = (u32)1,
    ISOStillJPEG2000FileType                        = (u32)2,
    ISOMotionJPEG2000FileType                       = (u32)3,
    ISOQuickTimeFileType                            = (u32)4,
    ISO3GPPFileType                                 = (u32)5
};

/* constants for the qt_componentType field of the MP4HandlerAtom structure */
enum
{
    ISOMediaHandlerType                             = MP4_FOUR_CHAR_CODE( 'm', 'h', 'l', 'r' ),
    ISODataHandlerType                              = MP4_FOUR_CHAR_CODE( 'd', 'h', 'l', 'r' )
};

/* These functions are general movie-handling functions and are common to both MPEG-4 and JPEG-2;
   ideally the "ISO" names should be used. */
#define ISODisposeMovie                             MP4DisposeMovie
#define ISOGetMovieTimeScale                        MP4GetMovieTimeScale
#define ISOGetMovieTrack                            MP4GetMovieTrack
#define ISOOpenMovieFile                            MP4OpenMovieFile
#define ISOPutMovieIntoHandle                       MP4PutMovieIntoHandle
#define ISOSetMovieTimeScale                        MP4SetMovieTimeScale
#define ISOAddTrackReference                        MP4AddTrackReference
#define ISOAddTrackReferenceWithID                  MP4AddTrackReferenceWithID
#define ISOGetMovieIndTrack                         MP4GetMovieIndTrack
#define ISOGetMovieTrackCount                       MP4GetMovieTrackCount
#define ISOGetTrackEnabled                          MP4GetTrackEnabled
#define ISOGetTrackID                               MP4GetTrackID
#define ISOGetTrackMedia                            MP4GetTrackMedia
#define ISOGetTrackMovie                            MP4GetTrackMovie
#define ISOGetTrackOffset                           MP4GetTrackOffset
#define ISOGetTrackReference                        MP4GetTrackReference
#define ISOGetTrackReferenceCount                   MP4GetTrackReferenceCount
#define ISOInsertMediaIntoTrack                     MP4InsertMediaIntoTrack
#define ISONewMovieTrack                            MP4NewMovieTrack
#define ISONewMovieTrackWithID                      MP4NewMovieTrackWithID
#define ISONewTrackMedia                            MP4NewTrackMedia
#define ISOSetTrackEnabled                          MP4SetTrackEnabled
#define ISOSetTrackOffset                           MP4SetTrackOffset
#define ISOTrackTimeToMediaTime                     MP4TrackTimeToMediaTime
#define ISOAddMediaDataReference                    MP4AddMediaDataReference
#define ISOAddMediaSampleReference                  MP4AddMediaSampleReference
#define ISOAddMediaSamples                          MP4AddMediaSamples
#define ISOAddMediaSamplesPad                       MP4AddMediaSamplesPad
#define ISOBeginMediaEdits                          MP4BeginMediaEdits
#define ISOCheckMediaDataReferences                 MP4CheckMediaDataReferences
#define ISOEndMediaEdits                            MP4EndMediaEdits
#define ISOGetIndMediaSample                        MP4GetIndMediaSample
#define ISOGetIndMediaSampleWithPad                 MP4GetIndMediaSampleWithPad
#define ISOGetMediaDataReference                    MP4GetMediaDataReference
#define ISOGetMediaDuration                         MP4GetMediaDuration
#define ISOGetMediaHandlerDescription               MP4GetMediaHandlerDescription
#define ISOGetMediaLanguage                         MP4GetMediaLanguage
#define ISOGetMediaSample                           MP4GetMediaSample
#define ISOGetMediaSampleWithPad                    MP4GetMediaSampleWithPad
#define ISOGetMediaSampleCount                      MP4GetMediaSampleCount
#define ISOGetMediaTimeScale                        MP4GetMediaTimeScale
#define ISOGetMediaTrack                            MP4GetMediaTrack
#define ISOMediaTimeToSampleNum                     MP4MediaTimeToSampleNum
#define ISOSampleNumToMediaTime                     MP4SampleNumToMediaTime
#define ISOSetMediaLanguage                         MP4SetMediaLanguage
#define ISOAddUserData                              MP4AddUserData
#define ISOGetIndUserDataType                       MP4GetIndUserDataType
#define ISOGetMovieUserData                         MP4GetMovieUserData
#define ISOGetTrackUserData                         MP4GetTrackUserData
#define ISOGetUserDataEntryCount                    MP4GetUserDataEntryCount
#define ISOGetUserDataItem                          MP4GetUserDataItem
#define ISOGetUserDataTypeCount                     MP4GetUserDataTypeCount
#define ISONewUserData                              MP4NewUserData
#define ISOCreateTrackReader                        MP4CreateTrackReader
#define ISODisposeTrackReader                       MP4DisposeTrackReader
#define ISONewHandle                                MP4NewHandle
#define ISOSetHandleSize                            MP4SetHandleSize
#define ISODisposeHandle                            MP4DisposeHandle
#define ISOGetHandleSize                            MP4GetHandleSize
#define ISOAddListEntry                             MP4AddListEntry

#define QTPutMovieIntoHandle                        MP4PutMovieIntoHandle
#define MJ2PutMovieIntoHandle                       MP4PutMovieIntoHandle
#define ISOPutMovieIntoHandle                       MP4PutMovieIntoHandle

#define QTWriteMovieToFile                          MP4WriteMovieToFile
#define MJ2WriteMovieToFile                         MP4WriteMovieToFile
#define ISOWriteMovieToFile                         MP4WriteMovieToFile

/* These functions are specific to Motion JPEG-2; they have only the "MJ2" names. */
ISO_EXTERN ( ISOErr )
MJ2SetMovieMatrix( ISOMovie theMovie, u32 matrix[9] );

ISO_EXTERN ( ISOErr )
MJ2GetMovieMatrix( ISOMovie theMovie, u32 outMatrix[9] );

ISO_EXTERN ( ISOErr )
MJ2SetMoviePreferredRate( ISOMovie theMovie, u32 rate );

ISO_EXTERN ( ISOErr )
MJ2GetMoviePreferredRate( ISOMovie theMovie, u32 *outRate );

ISO_EXTERN ( ISOErr )
MJ2SetMoviePreferredVolume( ISOMovie theMovie, s16 volume );

ISO_EXTERN ( ISOErr )
MJ2GetMoviePreferredVolume( ISOMovie theMovie, s16 *outVolume );

ISO_EXTERN ( ISOErr )
MJ2SetTrackMatrix( ISOTrack theTrack, u32 matrix[9] );

ISO_EXTERN ( ISOErr )
MJ2GetTrackMatrix( ISOTrack theTrack, u32 outMatrix[9] );

ISO_EXTERN ( ISOErr )
MJ2SetTrackLayer( ISOTrack theTrack, s16 layer );

ISO_EXTERN ( ISOErr )
MJ2GetTrackLayer( ISOTrack theTrack, s16 *outLayer );

ISO_EXTERN ( ISOErr )
MJ2SetTrackDimensions( ISOTrack theTrack, u32 width, u32 height );

ISO_EXTERN ( ISOErr )
MJ2GetTrackDimensions( ISOTrack theTrack, u32 *outWidth, u32 *outHeight );

ISO_EXTERN ( ISOErr )
MJ2SetTrackVolume( ISOTrack theTrack, s16 volume );

ISO_EXTERN ( ISOErr )
MJ2GetTrackVolume( ISOTrack theTrack, s16 *outVolume );

ISO_EXTERN ( ISOErr )
MJ2SetMediaGraphicsMode( ISOMedia theMedia, u32 mode, const ISORGBColor *opColor );

ISO_EXTERN ( ISOErr )
MJ2GetMediaGraphicsMode( ISOMedia theMedia, u32 *outMode, ISORGBColor *outOpColor );

ISO_EXTERN( ISOErr )
MJ2SetMediaSoundBalance( ISOMedia theMedia, s16 balance );

ISO_EXTERN( ISOErr )
MJ2GetMediaSoundBalance( ISOMedia theMedia, s16 *outBalance );

ISO_EXTERN ( ISOErr )
MJ2NewMovie( ISOMovie *outMovie );

/* These functions are specific to 3GPP; they have only the "3GPP" names. */
ISO_EXTERN ( ISOErr )
New3GPPMovie( ISOMovie *outMovie, u16 release );

/* These functions are specific to QuickTime; they have only the "QT" names. */
ISO_EXTERN ( ISOErr )
QTNewMovie( ISOMovie *outMovie );

/* These functions are general. */
ISO_EXTERN ( ISOErr )
ISOWriteMovieToFile( ISOMovie theMovie, const char *filename );

ISO_EXTERN ( ISOErr )
ISOSetMovieBrand( ISOMovie theMovie, u32 brand, u32 minorversion );

ISO_EXTERN ( ISOErr )
ISOSetMovieCompatibleBrand( ISOMovie theMovie, u32 brand );

ISO_EXTERN ( ISOErr )
ISOGetMovieBrand( ISOMovie theMovie, u32* brand, u32* minorversion );

ISO_EXTERN ( u32 )
ISOIsMovieCompatibleBrand( ISOMovie theMovie, u32 brand );

#ifdef PRAGMA_EXPORT
#pragma export on
#endif

#ifdef PRAGMA_EXPORT
#pragma export off
#endif

#ifdef __cplusplus
}
#endif

#endif
