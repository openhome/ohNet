#include "cpudetect.h"

int CALL_CONVENTION g_SupportMMX (void) {return 0;}
int CALL_CONVENTION g_SupportSSE1 (void) {return 0;}
int CALL_CONVENTION g_SupportSSE2 (void) {return 0;}
int CALL_CONVENTION g_SupportSSE2_Intrin (void) {return 0;}
int CALL_CONVENTION g_SupportSSE2_64_Intrin (void) {return 0;}
int CALL_CONVENTION g_SupportSSE3 (void) {return 0;}
int CALL_CONVENTION g_SupportSSSE3 (void) {return 0;}
int CALL_CONVENTION g_SupportMVI (void) {return 0;}
int CALL_CONVENTION g_SupportCMOV (void) {return 0;}