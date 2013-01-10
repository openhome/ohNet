#ifndef OHNET_GLOBALS
#define OHNET_GLOBALS

namespace OpenHome {

class Environment;
extern Environment* gEnv;

namespace Net {

class CpStack;
class DvStack;

extern CpStack*     gCpStack;
extern DvStack*     gDvStack;

} // namespace Net
} // namespace OpenHome

#endif // OHNET_GLOBALS
