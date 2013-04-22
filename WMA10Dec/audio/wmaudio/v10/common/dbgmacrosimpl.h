//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef _DBG_MACROS_IMPL_H
#define _DBG_MACROS_IMPL_H

#if defined(DBG_CX_STAGES)

INLINE WMARESULT DbgRefrInit(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;

    if (ENABLE_PCM)
    {
        g_hist_PCM = (CoefType*)callocAligned(RECONPROC_HIST_SIZE*sizeof(CoefType)*pau->m_cChannel, 32);
        CHECKWMA_ALLOC(wmaResult, g_hist_PCM);
    }
    if (ENABLE_FWDMLT)
    {
        g_hist_FWDMLT = (CoefType*)callocAligned(RECONPROC_HIST_SIZE*sizeof(CoefType)*pau->m_cChannel, 32);
        CHECKWMA_ALLOC(wmaResult, g_hist_FWDMLT);
    }
    if (ENABLE_RFX)
    {
        g_hist_RFX = (CoefType*)callocAligned(RECONPROC_HIST_SIZE*sizeof(CoefType)*pau->m_cChannel, 32);
        CHECKWMA_ALLOC(wmaResult, g_hist_RFX);
    }
    if (ENABLE_CX)
    {
        g_hist_CX = (CoefType*)callocAligned(RECONPROC_HIST_SIZE*sizeof(CoefType)*pau->m_cChannel, 32);
        CHECKWMA_ALLOC(wmaResult, g_hist_CX);
    }

    g_bufRefr = (CoefType*)callocAligned(prp->m_cFrameSampleHalfChex*2*sizeof(CoefType), 32);
    CHECKWMA_ALLOC(wmaResult, g_bufRefr);

    g_bufRefr2 = (CoefType*)callocAligned(prp->m_cFrameSampleHalfChex*2*sizeof(CoefType), 32);
    CHECKWMA_ALLOC(wmaResult, g_bufRefr2);

exit:
    return wmaResult;
}

INLINE Void DbgRefrFree(CAudioObject *pau)
{
    ReconProc *prp = pau->m_prp;

    freeAligned(g_hist_PCM);
    freeAligned(g_hist_FWDMLT);
    freeAligned(g_hist_RFX);
    freeAligned(g_hist_CX);

    freeAligned(g_bufRefr);
    freeAligned(g_bufRefr2);
}

INLINE WMARESULT DbgRefrOpenRef(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;

    if (g_bEnableStageWiseConf)                                 
    {         
        PCMFormat pcmfmt;

        size_t len = _tcslen(g_fileNameRef);
        assert(len >= 0 && len < 1000);                         
                                                                
        pcmfmt.nSamplesPerSec = pau->m_iSamplingRate;           
        pcmfmt.nChannels = pau->m_cOrigChannel;                 
        pcmfmt.nChannelMask = pau->m_nOrigChannelMask;          
        pcmfmt.nValidBitsPerSample = pau->m_nBitsPerSample;     
        pcmfmt.cbPCMContainerSize = pau->m_nBitsPerSample/8;    
        pcmfmt.pcmData = PCMDataPCM;                            
        PCMFormat2WaveFormatEx(&pcmfmt, &g_wfx.Format);           
                
        if (ENABLE_PCM)
        {
            _tcscpy(g_fileNameRef+len, TEXT(".pcm.raw"));                
            DBG_CX_OPEN_FILE(PCM,WRITE,g_fileNameRef,"wb")               
        }
        
        if (ENABLE_FWDMLT)
        {
            _tcscpy(g_fileNameRef+len, TEXT(".fwdmlt.raw"));             
            DBG_CX_OPEN_FILE(FWDMLT,WRITE,g_fileNameRef,"wb")            
        }                                                      

        if (ENABLE_RFX)
        {
            _tcscpy(g_fileNameRef+len, TEXT(".rfx.raw"));                
            DBG_CX_OPEN_FILE(RFX,WRITE,g_fileNameRef,"wb")               
        }
 
        if (ENABLE_CX)
        {
            _tcscpy(g_fileNameRef+len, TEXT(".cx.raw"));                 
            DBG_CX_OPEN_FILE(CX,WRITE,g_fileNameRef,"wb")                

            _tcscpy(g_fileNameRef+len, TEXT(".cx.wav"));                 
            DBG_CX_OPEN_FILE_PCM(CX,PCM,g_fileNameRef,wfioModeWrite)     
        }
                                                                
        pcmfmt.nChannels = 1;                                   
        PCMFormat2WaveFormatEx(&pcmfmt, &g_wfx.Format);           
         
        if (ENABLE_PCM)
        {                                                       
            _tcscpy(g_fileNameRef+len, TEXT(".pcm.wav"));                
            DBG_CX_OPEN_FILE_PCM(PCM,PCM,g_fileNameRef,wfioModeWrite)    
        }                                                        

        if (ENABLE_FWDMLT)
        {
            _tcscpy(g_fileNameRef+len, TEXT(".fwdmlt.wav"));             
            DBG_CX_OPEN_FILE_PCM(FWDMLT,PCM,g_fileNameRef,wfioModeWrite) 
        }

        if (ENABLE_RFX)
        {
            _tcscpy(g_fileNameRef+len, TEXT(".rfx.wav"));                
            DBG_CX_OPEN_FILE_PCM(RFX,PCM,g_fileNameRef,wfioModeWrite)    
        }

        TRACEWMA_EXIT(wmaResult, DbgRefrInit(pau));
    }            

exit:
    return wmaResult;
}

INLINE Void DbgRefrCloseRef(CAudioObject *pau)
{
    if (g_bEnableStageWiseConf)                                 
    {                                                           
        DBG_CX_CLOSE_FILES(WRITE)                               
        DBG_CX_CLOSE_FILES_PCM(PCM)                             
        DbgRefrFree(pau);
    }
}

INLINE Void DbgRefrRef(CAudioObject *pau,
                       PerChannelInfo *ppcinfo,
                       ReconTileInfo *prti,
                       Bool bUseDSTRecon,
                       Int iSamples,
                       Int iCh,
                       Int nCoef,
                       Int bEnable,
                       Bool bPCM,
                       FILE *fpWrite,
                       WavFileIO *fpPCM,
                       CoefType *pHist)
{
    ReconProc *prp = pau->m_prp;

    if (g_bEnableStageWiseConf)                                 
    {
        CoefType *buf = g_bufRefr;
        CoefType *buf2 = g_bufRefr2;
        Float *pfBuf = (Float*)g_bufRefr;
        I16 *piBuf = (I16*)g_bufRefr; 
        Int i, iVal;
        Int iPCMSamples = (bPCM ? prti->m_iSizeCurr : iSamples);
                                                                    
        if (bEnable) {                                           
            assert(fpWrite != NULL);                     
            fwrite(&nCoef, sizeof(Int), 1,  fpWrite);

            for (i=0; i < nCoef; i++)
            {
                pfBuf[i] = FLOAT_FROM_COEF(pau->m_rgCoefXFormMCLT[i]);
            }
            fwrite(pfBuf, sizeof(Float), nCoef,  fpWrite);

            assert(fpPCM != NULL);
            assert(nCoef <= BUFSIZE);                               
            assert(RECONPROC_HIST_SIZE*pau->m_cChannel <= BUFSIZE); 

            if (!bPCM)
            {
                memcpy(buf2, pau->m_rgCoefXFormMCLT,                    
                       sizeof(CoefType)*nCoef);                         
                chexIMCLTTile(pau, ppcinfo, prti, bUseDSTRecon,         
                              buf2, buf, pHist +                   
                              RECONPROC_HIST_SIZE*iCh);
            }
            else
            {
                memcpy(buf, pau->m_rgCoefXFormMCLT+prti->m_iSizeCurr/2,
                       sizeof(CoefType)*prti->m_iSizeCurr);
            }
                 
            for (i=0; i < iPCMSamples; i++)                            
            {                                                       
                ROUND_AND_CHECK_RANGE(iVal,                         
                    INT_FROM_COEF(buf[i]), SHRT_MIN, SHRT_MAX)      
                piBuf[i] = (I16)iVal;                               
            }

            wfioWrite(fpPCM, (Char*)piBuf, sizeof(I16)*iPCMSamples);
        }                                                           
    }                                                           
}

INLINE WMARESULT DbgRefrOpenCan(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;

    if (g_bEnableStageWiseConf)                                 
    {                             
        PCMFormat pcmfmt;

        size_t lenRef = _tcslen(g_fileNameRef);
        size_t lenCan = _tcslen(g_fileNameCan);
        assert(lenRef >= 0 && lenRef < 1000);
        assert(lenCan >= 0 && lenCan < 1000);
                                                                
        pcmfmt.nSamplesPerSec = pau->m_iSamplingRate;           
        pcmfmt.nChannels = pau->m_cOrigChannel;                 
        pcmfmt.nChannelMask = pau->m_nOrigChannelMask;          
        pcmfmt.nValidBitsPerSample = pau->m_nBitsPerSample;     
        pcmfmt.cbPCMContainerSize = pau->m_nBitsPerSample/8;    
        pcmfmt.pcmData = PCMDataPCM;                            
        PCMFormat2WaveFormatEx(&pcmfmt, &g_wfx.Format);           
                                                                
        if (ENABLE_PCM)
        {
            _tcscpy(g_fileNameRef+lenRef, TEXT(".pcm.raw"));                
            DBG_CX_OPEN_FILE(PCM,READ,g_fileNameRef,"rb")                
                                                                
            _tcscpy(g_fileNameCan+lenCan, TEXT(".pcm.raw"));            
            DBG_CX_OPEN_FILE(PCM,WRITE,g_fileNameCan,"wb")               
        }

        if (ENABLE_FWDMLT)
        {
            _tcscpy(g_fileNameRef+lenRef, TEXT(".fwdmlt.raw"));             
            DBG_CX_OPEN_FILE(FWDMLT,READ,g_fileNameRef,"rb")             
                                                                
            _tcscpy(g_fileNameCan+lenCan, TEXT(".fwdmlt.raw"));         
            DBG_CX_OPEN_FILE(FWDMLT,WRITE,g_fileNameCan,"wb")            
        }
                                                                
        if (ENABLE_RFX)
        {
            _tcscpy(g_fileNameRef+lenRef, TEXT(".rfx.raw"));                
            DBG_CX_OPEN_FILE(RFX,READ,g_fileNameRef,"rb")                
              
            _tcscpy(g_fileNameCan+lenCan, TEXT(".rfx.raw"));            
            DBG_CX_OPEN_FILE(RFX,WRITE,g_fileNameCan,"wb")               
        }

        if (ENABLE_CX)
        {                                                        
            _tcscpy(g_fileNameRef+lenRef, TEXT(".cx.raw"));                 
            DBG_CX_OPEN_FILE(CX,READ,g_fileNameRef,"rb")                 

            _tcscpy(g_fileNameCan+lenCan, TEXT(".cx.raw"));             
            DBG_CX_OPEN_FILE(CX,WRITE,g_fileNameCan,"wb")                
                                                                
            _tcscpy(g_fileNameCan+lenCan, TEXT(".cx.wav"));             
            DBG_CX_OPEN_FILE_PCM(CX,PCM,g_fileNameCan,wfioModeWrite)     
        }
                                                                
        pcmfmt.nChannels = 1;                                   
        PCMFormat2WaveFormatEx(&pcmfmt, &g_wfx.Format);           
                                                                
        if (ENABLE_PCM)
        {
            _tcscpy(g_fileNameCan+lenCan, TEXT(".pcm.wav"));            
            DBG_CX_OPEN_FILE_PCM(PCM,PCM,g_fileNameCan,wfioModeWrite)    
        }

        if (ENABLE_FWDMLT)
        {
            _tcscpy(g_fileNameCan+lenCan, TEXT(".fwdmlt.wav"));         
            DBG_CX_OPEN_FILE_PCM(FWDMLT,PCM,g_fileNameCan,wfioModeWrite) 
        }

        if (ENABLE_RFX)
        {
            _tcscpy(g_fileNameCan+lenCan, TEXT(".rfx.wav"));            
            DBG_CX_OPEN_FILE_PCM(RFX,PCM,g_fileNameCan,wfioModeWrite)    
        }
                                                                 
        TRACEWMA_EXIT(wmaResult, DbgRefrInit(pau));
    }

exit:
    return wmaResult;
}

INLINE Void DbgRefrCloseCan(CAudioObject *pau)
{
    if (g_bEnableStageWiseConf)                                 
    {                                                           
        DBG_CX_CLOSE_FILES(READ)                                
        DBG_CX_CLOSE_FILES(WRITE)                               
        DBG_CX_CLOSE_FILES_PCM(PCM)                             
        DbgRefrFree(pau);
    }
}

INLINE Void DbgRefrCan(CAudioObject *pau,
                       PerChannelInfo *ppcinfo,
                       ReconTileInfo *prti,
                       Bool bUseDSTRecon,
                       Int iSamples,
                       Int iCh,
                       Int nCoefRead,
                       Bool bEnable,
                       Bool bPCM,
                       FILE *fpRead,
                       FILE *fpWrite,
                       WavFileIO *fpPCM,
                       CoefType *pHist)
{
    ReconProc *prp = pau->m_prp;

    if (g_bEnableStageWiseConf)                                 
    {                                                           
        CoefType *buf = g_bufRefr;
        CoefType *buf2 = g_bufRefr2;
        CoefType *ptr = (CoefType*)pau->m_rgCoefXFormMCLT;      
        Int nCoef,i,iVal;
        Float *pfBuf = (Float*)g_bufRefr;                            
        I16 *piBuf = (I16*)g_bufRefr;  
        Int iPCMSamples = (bPCM ? prti->m_iSizeCurr : iSamples);

        if (bEnable) {                                           
            assert(fpWrite != NULL);                     
            assert(fpRead != NULL);                      
                                                                    
            fread(&nCoef, sizeof(Int),                              
                1, fpRead );                             
            assert(nCoef == nCoefRead);                         
                                                                    
            catchFP();                                              
            fwrite(&(nCoef), sizeof(Int),                           
                1,  fpWrite);                            
            fwrite(ptr, sizeof(Float), nCoef,  fpWrite); 
                                                                    
            assert(fpPCM != NULL);                       
            assert(nCoef <= BUFSIZE);                               
            assert(RECONPROC_HIST_SIZE*pau->m_cChannel <= BUFSIZE); 

            if (!bPCM)
            {
                memcpy(buf2, pau->m_rgCoefXFormMCLT,                    
                       sizeof(CoefType)*nCoef);                         
                chexIMCLTTile(pau, ppcinfo, prti, bUseDSTRecon,         
                              buf2, buf, pHist +                   
                              RECONPROC_HIST_SIZE*iCh);                   
            }
            else
            {
                memcpy(buf, pau->m_rgCoefXFormMCLT+prti->m_iSizeCurr/2,
                       sizeof(CoefType)*prti->m_iSizeCurr);
            }
                                                                    
            for(i=0; i<iPCMSamples; ++i )
            {                                                       
                ROUND_AND_CHECK_RANGE(iVal,                         
                    INT_FROM_COEF(buf[i]), SHRT_MIN, SHRT_MAX)      
                piBuf[i] = (I16)iVal;                               
            }
   
            wfioWrite(fpPCM, (Char*)piBuf, sizeof(I16)*iPCMSamples);
                                                                    
            fread(pfBuf, sizeof(Float), nCoef, fpRead);

            if (g_fMaxAbsDiffThreshold != 0) 
            {
                g_fMaxAbsDiff = 0.0f;
                g_iMaxAbsDiffIndex = -1;
            }

            for(i=0; i<nCoef; ++i )                                 
            {   
                if (g_fMaxAbsDiffThreshold != 0) 
                {
                    // calculate the max diff to facilitate the debugging
                    Float coefAbsDiff = ABS(pfBuf[i] - FLOAT_FROM_COEF(ptr[i]));

                    if (coefAbsDiff > g_fMaxAbsDiff)
                    {
                        g_fMaxAbsDiff = coefAbsDiff;
                        g_iMaxAbsDiffIndex = i;
                    }

                    assert(g_fMaxAbsDiff <= g_fMaxAbsDiffThreshold);
                }

                ptr[i] = COEF_FROM_FLOAT( pfBuf[i] );
            }                                                       
            initFP();                                               
        }                                                           
    
    }                                                           
}

#endif // #if defined(DBG_CX_STAGES)

#endif // _DBG_MACROS_IMPL_H
