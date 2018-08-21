"""PyOhNet: entry point for python ohNet bindings
"""
#
# ==== Initialise module-level data ====
#

lib        = None
makeCb     = None
initParams = None


#
# ==== Exception handler for ohNet-python ====
#

class OhNetError( Exception ):

    def __init__( self, aMsg ):
        self.msg = aMsg

    def __str__( self ):
        return repr( self.msg )


#
# ==== Load ohNet library and configure callback calling convention ====
#

import os
import ctypes
import platform
__platform = platform.system()
__libPath1 = os.path.dirname( __file__ )
__libPath2 = os.path.split( __libPath1 )[0]

if __platform in ['Windows', 'cli']:
    __libName = 'ohNet.dll'
elif __platform == 'Linux':
    __libName = 'libohNet.so'
elif __platform == 'Darwin':
    __libName = 'libohNet.dylib'
else:
    raise OhNetError( 'Unsupported platform - %s' % __platform )

__library = os.path.join( __libPath1, __libName )
if not os.path.isfile( __library ):
    __library = os.path.join( __libPath2, __libName )
if not os.path.isfile( __library ):
    raise OhNetError( 'Cannot find  %s' % __library )

try:
    if __platform in ['Windows', 'cli']:
        lib = ctypes.windll.LoadLibrary( __library )
    else:
        lib = ctypes.cdll.LoadLibrary( __library )
except:
    raise OhNetError( 'Failed to load %s' % __library )

if __platform in ['Windows', 'cli']:
    makeCb = ctypes.WINFUNCTYPE
else:
    makeCb = ctypes.CFUNCTYPE

#
# ==== Import rest of ohNet-python functionality ====
#

import sys
sys.path.append( os.path.dirname( __file__ ))
from _Network import Adapter, AdapterList   # NOQA
from _DebugLevels import kDebugLevel
import _Cp as Cp            # control point stack

#
# ==== Track ohNet objects (updated on object create/delete) to permit clean shutdown ====
#

adapters     = []
adapterLists = []
devices      = []
devLists     = []
actions      = []
cpProxies    = []


#
# ==== Public module-level methods ====
#

def Initialise( aInitParams=None ):
    """Initialise ohNet library - must be first call to module"""
    # aInitParams is a dict, which can contain the following key/value pairs
    #   - loopack:  True or False
    lib.OhNetInitParamsCreate.restype = ctypes.c_void_p
    params = ctypes.c_void_p( lib.OhNetInitParamsCreate() )
    if aInitParams:
        if 'loopback' in aInitParams:
            if aInitParams['loopback'] is not False:
                lib.OhNetInitParamsSetUseLoopbackNetworkAdapter( params )
        if 'invokeTimeout' in aInitParams:
            lib.OhNetInitParamsSetInvocationTimeout( params, aInitParams['invokeTimeout'] )     # in millisecs
    if lib.OhNetLibraryInitialise( params ):
        raise OhNetError( 'Failed to initialise Library')


def SetDebugLevel( aDebugLevel=kDebugLevel['None'] ):
    """Configure debug logging for underlying ohNet library"""
    level = ctypes.c_int64( aDebugLevel )
    lib.OhNetDebugSetLevel( level )


def Start( aMode='cp', aInterface=None ):
    """Start ohNet (optionally specifying interface by adapter, IP or subnet)"""
    adapterList = AdapterList()
    theAdapters = adapterList.adapters
    numAdapters = adapterList.size
    adapter     = None

    if numAdapters == 0:
        # no adapters present - throw
        raise OhNetError( 'NO network adapter detected' )
    elif numAdapters == 1:
        # only one adapter - use it (ignoring aHost param if requested)
        adapter = theAdapters[0]
    else:
        if aInterface is None:
            # no host specified - use first adapter
            adapter = theAdapters[0]
        else:
            # host specified - find matching adapter and use it
            for item in theAdapters:
                if aInterface == item or \
                   aInterface == item.addressStr or \
                   aInterface == item.subnetStr:
                    adapter = item
                    break
            if not adapter:
                raise OhNetError( 'NO network adapter matching %s found' % aInterface )

    if aMode.lower() == 'cp':
        Cp.Start( adapter )
    else:
        raise OhNetError( 'Stack mode <%s> not supported' % aMode )


def Shutdown():
    """Cleanly shut down ohNet"""
    while len( adapters ):
        adapters[0].Shutdown()
    while len( adapterLists ):
        adapterLists[0].Shutdown()
    while len( devices ):
        devices[0].Shutdown()
    while len( devLists ):
        devLists[0].Shutdown()
    while len( actions ):
        actions[0].Shutdown()
    while len( cpProxies ):
        cpProxies[0].Shutdown()
    if lib:
        if initParams:
            lib.OhNetInitParamsDestroy( initParams )
        lib.OhNetLibraryClose()
