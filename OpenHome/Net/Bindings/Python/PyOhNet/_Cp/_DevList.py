"""PyOhNet: control point device-list support
"""
import PyOhNet
import abc
import ctypes
import time
import _Cp._Device as Device


# noinspection PyUnusedLocal
class DeviceList():
    """Abstract base class for device list handlers"""
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def __init__( self, aAddedCb, aRemovedCb ):
        self.lib        = PyOhNet.lib
        self.handle     = None
        self.devices    = []
        self.addedCbs   = []
        self.removedCbs = []

        if aAddedCb:
            self.addedCbs.append( aAddedCb )
        if aRemovedCb:
            self.removedCbs.append( aRemovedCb )

        CB = PyOhNet.makeCb( None, ctypes.c_void_p, ctypes.c_void_p )
        self._PrimaryAddedCb = CB( self._Added )
        self._PrimaryRemovedCb = CB( self._Removed )
        PyOhNet.devLists.append( self )

    #
    # ==== Internal methods ====
    #

    def _Added( self, aDummy, aDev ):
        dev = Device.Device( aDev )
        self.devices.append( dev )
        for cb in self.addedCbs:
            cb( dev )

    def _Removed( self, aDummy, aDev ):
        handle = ctypes.c_void_p( aDev )
        udn = ctypes.c_char_p()
        length = ctypes.c_int()
        self.lib.CpDeviceCGetUdn( handle, ctypes.byref( udn ), ctypes.byref( length ))
        time.sleep( 0.01 )  # udn not populated correctly without this delay (on Win10)
        for dev in self.devices:
            if dev.udn == udn.value.decode( 'ascii' ):
                for cb in self.removedCbs:
                    cb( dev )
                self.devices.remove( dev )
                dev.Shutdown()

    def _GetDevs( self ):
        return self.devices

    def _GetUdns( self ):
        udns = []
        for device in self.devices:
            udns.append( device.udn )
        return udns

    def _GetFriendlyNames( self ):
        friendlyNames = []
        for device in self.devices:
            friendlyNames.append( device.friendlyName )
        return friendlyNames

    #
    # ==== Public Interface ====
    #

    def DevByName( self, aName ):
        dev = None
        for device in self.devices:
            if device.friendlyName == aName:
                dev = device
                break
        return dev

    def DevByUdn( self, aUdn ):
        dev = None
        for device in self.devices:
            if device.udn == aUdn:
                dev = device
                break
        return dev

    def AddAddedCb( self, aCb ):
        self.addedCbs.append( aCb )

    def AddRemovedCb( self, aCb ):
        self.removedCbs.append( aCb )

    def RemoveAddedCb( self, aCb ):
        if aCb in self.addedCbs:
            self.addedCbs.remove( aCb )

    def RemoveRemovedCb( self, aCb ):
        if aCb in self.removedCbs:
            self.removedCbs.remove( aCb )

    def Refresh( self ):
        if self.handle:
            self.lib.CpDeviceListRefresh( self.handle )

    def Shutdown( self ):
        PyOhNet.devLists.remove( self )
        if self.handle:
            self.lib.CpDeviceListDestroy( self.handle )

    devs          = property( _GetDevs, None, None, '' )
    udns          = property( _GetUdns, None, None, '' )
    friendlyNames = property( _GetFriendlyNames, None, None, '' )


#
# ==== Concrete Device Lists ====
#

# - These take optional 'Added' and 'Removed' callbacks as init parameters
# - Added and Removed Callbacks can be added/removed at any time during the
#       lifetime of the device list using the AddXXXCb and RemoveXXXCb
# - These callbacks require a Device object as their only parameter.

class DeviceListUpnpRoot( DeviceList ):
    """Device list handler for UPnP Root devices"""

    def __init__( self, aAddedCb=None, aRemovedCb=None ):
        DeviceList.__init__( self, aAddedCb, aRemovedCb )
        self.lib.CpDeviceListCreateUpnpRoot.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.CpDeviceListCreateUpnpRoot(
            self._PrimaryAddedCb, None, self._PrimaryRemovedCb, None ))


class DeviceListUpnpAll( DeviceList ):
    """Device list handler for ALL UPnP devices"""

    def __init__( self, aAddedCb=None, aRemovedCb=None ):
        DeviceList.__init__( self, aAddedCb, aRemovedCb )
        self.lib.CpDeviceListCreateUpnpAll.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.CpDeviceListCreateUpnpAll(
            self._PrimaryAddedCb, None, self._PrimaryRemovedCb, None ))


class DeviceListUpnpDeviceType( DeviceList ):
    """Device list handler for UPnP devices of specified device type"""

    def __init__( self, aDomain, aType, aVersion, aAddedCb=None, aRemovedCb=None ):
        DeviceList.__init__( self, aAddedCb, aRemovedCb )
        self.lib.CpDeviceListCreateUpnpDeviceType.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.CpDeviceListCreateUpnpDeviceType(
            ctypes.c_char_p( aDomain.encode( 'utf8', 'replace' )), ctypes.c_char_p( aType.encode( 'utf8', 'replace' )), aVersion,
            self._PrimaryAddedCb, None, self._PrimaryRemovedCb, None ))


class DeviceListUpnpServiceType( DeviceList ):
    """Device list handler for UPnP devices containing specified service type"""

    def __init__( self, aDomain, aType, aVersion, aAddedCb=None, aRemovedCb=None ):
        DeviceList.__init__( self, aAddedCb, aRemovedCb )
        self.lib.CpDeviceListCreateUpnpServiceType.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.CpDeviceListCreateUpnpServiceType(
            ctypes.c_char_p( aDomain.encode( 'utf8', 'replace' ) ), ctypes.c_char_p( aType.encode( 'utf8', 'replace' ) ), aVersion,
            self._PrimaryAddedCb, None, self._PrimaryRemovedCb, None ))


class DeviceListUpnpUuid( DeviceList ):
    """Device list handler for UPnP devices with specified UUID"""

    def __init__( self, aUuid, aAddedCb=None, aRemovedCb=None ):
        DeviceList.__init__( self, aAddedCb, aRemovedCb )
        self.lib.CpDeviceListCreateUpnpUuid.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.CpDeviceListCreateUpnpUuid(
            ctypes.c_char_p( aUuid.encode( 'utf8', 'replace' ) ), self._PrimaryAddedCb, None, self._PrimaryRemovedCb, None ))
