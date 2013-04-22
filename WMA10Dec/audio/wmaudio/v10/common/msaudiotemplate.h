//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#ifndef _MSAUDIOTEMPLATE_H
#define _MSAUDIOTEMPLATE_H

#ifdef AUINV_RECON_CHANNEL

// different function names
#ifdef AUINV_RECON_CHANNEL_ENC
#define auReconCoefficentsHighRate auReconCoefficentsHighRate_Enc
#endif
#ifdef AUINV_RECON_CHANNEL_DEC
#define auInvRlcCoefV3_Channel auInvRlcCoefV3_Channel_Dec
#define auReconCoefficentsHighRate auReconCoefficentsHighRate_Dec
#define auInvRlcCoefV3_ChannelHT auInvRlcCoefV3_ChannelHT_Dec
#endif

WMARESULT auReconCoefficentsHighRate (CAudioObject* pau, Void* pcaller,
                                      PerChannelInfo* ppcinfo);
WMARESULT auInvRlcCoefV3_Channel (CAudioObject* pau, Void* pcaller,
                                  PerChannelInfo* ppcinfo,
                                  Int iChSrc);
WMARESULT auInvRlcCoefV3_ChannelHT (CAudioObject* pau, Void* pcaller,
                                    PerChannelInfo* ppcinfo,
                                    Int iChSrc);

#endif // AUINV_RECON_CHANNEL

#endif // _MSAUDIOTEMPLATE_H

