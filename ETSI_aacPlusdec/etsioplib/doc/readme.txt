$Id: readme.txt,v 1.3 2005-02-16 15:07:38 ehr Exp $
---------------------------------------------------------------------

This library has been started using source code files from the WB-AMR
source code package 26073-530.zip. Only slight adaptations have been
made to the count.c file in order to reflect the different sampling rate
and frame lengths we are targeting. Especially the following files have 
been used:

typedef.h                -- type definitions by ETSI
typedefs.h               -- extended type definitions

basic_op.h               -- basic operators prototypes
basicop2.c               -- basic operators implementations

oper_32b.h               -- double precision prototypes
oper_32b.c               -- double precision extensions

count.h                  -- WMOPS counter prototypes
count.c                  -- WMOPS counters


The test/ directory contains a very simple test application plus
Makefile/Workspace that shows how the basic operators are used.

More complete example code is available from the WB-AMR workitem, it can
be downloaded here:
http://www.3gpp.org/ftp/Specs/2004-03/Rel-5/26_series/26073-530.zip

---------------------------------------------------------------------
mailto: 3gpp-support@codingtechnologies.com



