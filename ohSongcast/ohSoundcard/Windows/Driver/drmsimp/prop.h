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
    0xff89e492, 0x5c4a, 0x4b2c, 0x87, 0x9a, 0x6a, 0xf, 0xa6, 0x56, 0x1a, 0x63
DEFINE_GUIDSTRUCT("FF89E492-5C4A-4b2c-879A-6A0FA6561A63", KSPROPSETID_Private);
#define KSPROPSETID_Private DEFINE_GUIDNAMED(KSPROPSETID_Private)

/*
// {FF89E492-5C4A-4b2c-879A-6A0FA6561A63}
DEFINE_GUID(KSPROPSETID_Private, 0xff89e492, 0x5c4a, 0x4b2c, 0x87, 0x9a, 0x6a, 0xf, 0xa6, 0x56, 0x1a, 0x63);
*/

// Define the method in the property. You can have multiple methods defined
// for one private property ...

const int KSPROPERTY_SNEAKY_FEATURES = 0;
const int KSPROPERTY_SNEAKY_VERSION = 1;
const int KSPROPERTY_SNEAKY_ENDPOINT = 2;
const int KSPROPERTY_SNEAKY_ACTIVE = 3;
const int KSPROPERTY_SNEAKY_TTL = 4;

// Structure passed in the private property request with method
// KSPROPERTY_SNEAKY_FEATURES.

typedef struct
{
	UINT iVersion;
} SneakyFeatures;

