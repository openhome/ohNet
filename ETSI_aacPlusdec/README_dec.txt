===================================================================

                 3GPP Enhanced aacPlus decoder,
           Fixed-Point Implemetation using ETSI operators
                           Linux/Win32
                       for Intel x86 CPUs

===================================================================

CONTENTS: Enhanced aacPlus decoder source code, 
          fixed-point ETSI operators


REVISION NOTES:

 - Contents:

   README.txt             -- this file
   Makefile               -- Linux Makefile
   enhAacPlusdec.dsw      -- Win32 MSVC 6.0 workspace
   enhAacPlusdec.dsp      -- Win32 MSVC 6.0 makefile

   src/                   -- directory for the frontend
   etsiop_bitbuf/         -- bitstream reading/writing library
   etsiop_aacdec/         -- AAC decoder library
   etsiop_sbrdec/         -- SBR decoder library
   etsiop_ffrlib/         -- general purpose functionalities
   etsioplib/             -- ETSI operator library
 
   3g_lib/                -- precompiled MPEG-4 / 3GPP file format 
        w32/                   and audio file library (for wav support),
    linux/                 for Linux OS and Windows 32-bit



 - Compilation: 

   o for Win32 use the enhAacPlusdec.dsw 6.0 workspace, activate 
     the enhAacPlusDec project and choose the appropriate 
     "Win32 Release/Debug" target

   o for Linux use >gmake clean all< in the root directory


 - Instrumentation:

   To measure the weighted mops, set WMOPS=1 on the Linux gmake
   commandline, respectively add the define WMOPS to the Win32 
   workspace makefiles.


 - MONO_ONLY, LP_SBR_ONLY:

   These defines are introduced to be able to compile a mono-only
   decoder using LP-SBR. They are set by default when choosing the 
   Mono compile targets in the Win32 workspace, resp. setting the 
   MONO=1 option on the Linux gmake commandline.

===================================================================
for info mailto: 3gpp-support@codingtechnologies.com
===================================================================