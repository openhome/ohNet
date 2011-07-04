/*++

Copyright (c) 1997-2000  Microsoft Corporation All Rights Reserved

Module Name:

    Msvad.h

Abstract:

    Header file for common stuff.

--*/

#ifndef _MSVAD_H_
#define _MSVAD_H_

#include <portcls.h>
#include <stdunk.h>
#include <ksdebug.h>
#include "kshelper.h"

//=============================================================================
// Defines
//=============================================================================

// Pool tag used for MSVAD allocations
#define OHSOUNDCARD_POOLTAG               'OHSC'  

// Debug module name
#define STR_MODULENAME              "OHSOUNDCARD: "

// Debug utility macros
#define D_FUNC                      4
#define D_BLAB                      DEBUGLVL_BLAB
#define D_VERBOSE                   DEBUGLVL_VERBOSE        
#define D_TERSE                     DEBUGLVL_TERSE          
#define D_ERROR                     DEBUGLVL_ERROR          
#define DPF                         _DbgPrintF
#define DPF_ENTER(x)                DPF(D_FUNC, x)

// Channel orientation
#define CHAN_LEFT                   0
#define CHAN_RIGHT                  1
#define CHAN_MASTER                 (-1)

// Dma Settings.
#define DMA_BUFFER_SIZE             0x16000

#define KSPROPERTY_TYPE_ALL         KSPROPERTY_TYPE_BASICSUPPORT | \
                                    KSPROPERTY_TYPE_GET | \
                                    KSPROPERTY_TYPE_SET
                                    
// Specific node numbers for vadsampl.sys
#define DEV_SPECIFIC_VT_BOOL 9
#define DEV_SPECIFIC_VT_I4   10
#define DEV_SPECIFIC_VT_UI4  11

//=============================================================================
// Typedefs
//=============================================================================

// Connection table for registering topology/wave bridge connection
typedef struct _PHYSICALCONNECTIONTABLE
{
    ULONG       ulTopologyIn;
    ULONG       ulTopologyOut;
    ULONG       ulWaveIn;
    ULONG       ulWaveOut;
} PHYSICALCONNECTIONTABLE, *PPHYSICALCONNECTIONTABLE;

//=============================================================================
// Externs
//=============================================================================

// Physical connection table. Defined in mintopo.cpp for each sample
extern PHYSICALCONNECTIONTABLE TopologyPhysicalConnections;

// Generic topology handler
extern NTSTATUS PropertyHandler_Topology
( 
    IN  PPCPROPERTY_REQUEST     PropertyRequest 
);

// Generic wave port handler
extern NTSTATUS PropertyHandler_Wave
(
    IN  PPCPROPERTY_REQUEST     PropertyRequest
);

// Default WaveFilter automation table.
// Handles the GeneralComponentId request.
extern NTSTATUS PropertyHandler_WaveFilter
(
    IN PPCPROPERTY_REQUEST PropertyRequest
);

#endif
