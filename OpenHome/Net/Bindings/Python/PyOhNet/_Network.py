"""PyOhNet: network (adapter) support
"""
import PyOhNet
import ctypes
import uuid


class Adapter():
    """ohNet representation of a network adapter"""

    def __init__( self, aHandle ):
        self.lib = PyOhNet.lib
        self.handle = aHandle
        self.cookie = uuid.uuid4().urn.encode( 'utf8', 'replace' )
        self.lib.OhNetNetworkAdapterAddRef( self.handle, self.cookie )
        PyOhNet.adapters.append( self )

    def Shutdown( self ):
        PyOhNet.adapters.remove( self )
        if self.handle:
            self.lib.OhNetNetworkAdapterRemoveRef( self.handle, self.cookie )

    #
    # ==== Internal methods ====
    #

    def _GetAddress( self ):
        x = self.lib.OhNetNetworkAdapterAddress( self.handle )
        if x < 0:
            x += 2**32  # convert to unsigned long
        return x

    def _GetSubnet( self ):
        return self.lib.OhNetNetworkAdapterSubnet( self.handle )

    def _GetMask( self ):
        return self.lib.OhNetNetworkAdapterMask( self.handle )

    def _GetName( self ):
        self.lib.OhNetNetworkAdapterName.restype = ctypes.c_char_p
        return self.lib.OhNetNetworkAdapterName( self.handle ).decode( 'utf8', 'replace' )

    def _GetFullName( self ):
        self.lib.OhNetNetworkAdapterFullName.restype = ctypes.c_char_p
        return self.lib.OhNetNetworkAdapterFullName( self.handle ).decode( 'utf8', 'replace' )

    def _GetStrAddress( self ):
        return self._Num2DottedQuad( self.address )

    def _GetStrSubnet( self ):
        return self._Num2DottedQuad( self.subnet )

    def _GetStrMask( self ):
        return self._Num2DottedQuad( self.mask )

    @staticmethod
    def _Num2DottedQuad( n ):
        """Convert long int to dotted quad string"""
        d = 256 * 256 * 256
        q = []
        while d > 0:
            m, n = divmod( n, d )
            q.append( str( m ))
            d = int( d / 256 )
        q.reverse()
        return '.' . join( q )

    #
    # ==== Public interface ====
    #

    address    = property( _GetAddress, None, None, '' )     # int in network-byte order
    addressStr = property( _GetStrAddress, None, None, '' )  # dotted-quad
    subnet     = property( _GetSubnet, None, None, '' )      # int in network-byte order
    subnetStr  = property( _GetStrSubnet, None, None, '' )   # dotted-quad
    mask       = property( _GetMask, None, None, '' )        # int in network-byte order
    maskStr    = property( _GetStrMask, None, None, '' )     # dotted-quad
    name       = property( _GetName, None, None, '' )
    fullName   = property( _GetFullName, None, None, '' )


class AdapterList():
    """List of available network adapters"""

    def __init__( self ):
        self.lib = PyOhNet.lib
        self.handle = None
        self.lib.OhNetSubnetListCreate.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.OhNetSubnetListCreate() )
        PyOhNet.adapterLists.append( self )

    def Shutdown( self ):
        PyOhNet.adapterLists.remove( self )
        if self.handle:
            self.lib.OhNetSubnetListDestroy( self.handle )

    #
    # ==== Internal methods ====
    #

    def _GetSize( self ):
        size = 0
        if self.handle:
            size = self.lib.OhNetNetworkAdapterListSize( self.handle )
        return size

    def _GetAdapters( self ):
        adapters = []
        if self.handle:
            for i in range( self.size ):
                self.lib.OhNetNetworkAdapterAt.restype = ctypes.c_void_p
                adapters.append( Adapter( ctypes.c_void_p( self.lib.OhNetNetworkAdapterAt( self.handle, i ))))
        return adapters

    #
    # ==== Public interface ====
    #

    adapters = property( _GetAdapters, None, None, '' )
    size     = property( _GetSize, None, None, '' )
