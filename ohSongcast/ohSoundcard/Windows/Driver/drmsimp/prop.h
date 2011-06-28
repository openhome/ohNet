//////////////////////////////////////////////////////////////////////////
// This header file is only used if you compile the driver with the switch
// INCLUDE_PRIVATE_PROPERTY defined. Additionally, this header file is
// also used by the property page sample.
//
// This header file defines the private property (the GUID) and the
// "messages" therin. It also defines the structure passed down.
//

//
// The GUID was generated with guidgen.exe
//

// This is the GUID for the private property request.

// This is the GUID for the private property request.
#define STATIC_KSPROPSETID_Private \
    0x2685C863, 0x5E57, 0x4D9A, 0x86, 0xEC, 0x2E, 0xC9, 0xB7, 0xBB, 0xBC, 0xFD
DEFINE_GUIDSTRUCT("2685C863-5E57-4D9A-86EC-2EC9B7BBBCFD", KSPROPSETID_Private);
#define KSPROPSETID_Private DEFINE_GUIDNAMED(KSPROPSETID_Private)


/*
// {2685C863-5E57-4D9A-86EC-2EC9B7BBBCFD}
DEFINE_GUID(KSPROPSETID_Private, 0x2685C863, 0x5E57, 0x4D9A, 0x86, 0xEC, 0x2E, 0xC9, 0xB7, 0xBB, 0xBC, 0xFD);
*/

// Define the method in the property. You can have multiple methods defined
// for one private property ...

const int KSPROPERTY_OHSOUNDCARD_VERSION = 0;
const int KSPROPERTY_OHSOUNDCARD_ENABLED = 1;
const int KSPROPERTY_OHSOUNDCARD_ACTIVE = 2;
const int KSPROPERTY_OHSOUNDCARD_ENDPOINT = 3;
const int KSPROPERTY_OHSOUNDCARD_TTL = 4;
