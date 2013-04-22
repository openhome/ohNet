//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

// ===========================================================================
// Configuration file for PK's
// This file contains configurations that must be set prior to building the
// decoder.

// ===========================================================================
// Build Configuration:
// One of the following must be defined to 1 depending on what
// configurations are to be supported

// WMA STD Only
#define BUILDCFG_STD               (0)
// WMA STD + PRO Stereo (including LBR V1, PRO support is only down to 48kbps)
#define BUILDCFG_STDPROSTEREOLBRV1 (0)
// WMA STD + PRO Stereo (including all versions of LBR)
#define BUILDCFG_STDPROSTEREOLBR   (0)
// WMA STD + PRO (includes support for multichannel PRO, all versions of LBR)
#define BUILDCFG_STDPROLBR         (0)
// WMA LSL only
#define BUILDCFG_LSL               (0)
// WMA STD + PRO (includes multichannel, all versions of LBR) + LSL
#define BUILDCFG_ALL               (1)

