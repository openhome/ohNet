/*++

Copyright (c) 1997-2000  Microsoft Corporation All Rights Reserved

Module Name:

    drmsimp.h

Abstract:

    Node and Pin numbers for simple drm sample.

--*/

#ifndef _MSVAD_DRMSIMP_H_
#define _MSVAD_DRMSIMP_H_

// Pin properties.
#define MAX_OUTPUT_STREAMS          1       // Number of capture streams.
#define MAX_INPUT_STREAMS           1       // Number of render streams.
#define MAX_TOTAL_STREAMS           MAX_OUTPUT_STREAMS + MAX_INPUT_STREAMS                      

// PCM Info
#define MIN_CHANNELS                1       // Min Channels.
#define MAX_CHANNELS_PCM            2       // Max Channels.
#define MIN_BITS_PER_SAMPLE_PCM     16      // Min Bits Per Sample
#define MAX_BITS_PER_SAMPLE_PCM     24      // Max Bits Per Sample
#define MIN_SAMPLE_RATE             8000    // Min Sample Rate
#define MAX_SAMPLE_RATE             192000  // Max Sample Rate

// Wave pins
enum 
{
    KSPIN_WAVE_RENDER_SINK, 
    KSPIN_WAVE_RENDER_SOURCE
};

// Wave Topology nodes.
enum 
{
    KSNODE_WAVE_DAC
};

// topology pins.
enum
{
    KSPIN_TOPO_WAVEOUT_SOURCE,
    KSPIN_TOPO_LINEOUT_DEST,
};

// topology nodes.
enum
{
    KSNODE_TOPO_WAVEOUT_MUTE
};

#endif

