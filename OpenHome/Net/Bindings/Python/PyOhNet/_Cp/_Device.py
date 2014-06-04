"""PyOhNet: control point device support
"""
import PyOhNet
import ctypes
import os
import re
import stat
import sys
import urllib2
import urlparse
import xml.etree.ElementTree as ET
import _GenProxy as GenProxy
import _GlobalLock as GlobalLock


class Device():
    """UPnP Device (from perspective of a control point)"""
    
    def __init__( self, aHandle ):
        self.lib = PyOhNet.lib
        self.handle = aHandle
        self.lib.CpDeviceCAddRef( self.handle )
        self.proxies = []
        PyOhNet.devices.append( self )  
        
    def __str__( self ):
        msg = 'Device %s (%s)' % (self.friendlyName, self.udn)
        for proxy in self.proxies:
            msg += '\n'
            msg += eval( 'self.%s.__str__()' % proxy  )
        return msg
        
    #
    # ==== Internal methods ====
    #
        
    def _GetAttribute( self, aAttr ):
        request  = ctypes.c_char_p( aAttr )
        response = ctypes.c_char_p()
        self.lib.CpDeviceCGetAttribute( self.handle, request, ctypes.byref( response ))
        return response.value 
        
    def _GetServices( self ):
        """Returns list of services reported by device"""
        result   = []
        baseUrl  = re.match('^(.+)(//)([\w\.:]+)', self.location ).group()
        xml      = re.sub( ' xmlns="[^"]+"', '', self.deviceXml )    # remove namespace
        root     = ET.fromstring( xml )
        
        devices = root.findall( 'device' )
        for device in devices:
            serviceList = device.find( 'serviceList' )
            services = serviceList.findall( 'service' )
            for service in services:
                svType = service.find( 'serviceType' ).text
                url  = urlparse.urljoin( baseUrl, service.find( 'SCPDURL' ).text )
                m = re.match('urn:([\w\-\.]+):service:([\w\-\.]+):(\d+)', svType )
                domain, name, version = m.groups()
                domainName = ''
                fields = domain.replace( '.', '-' ).split( '-' )
                for field in fields:
                    domainName += field[0].upper()
                    domainName += field[1:]
                result.append( {'type':svType, 'url':url, 'domain':domainName, 'name':name, 'version':int( version )} )
        return result
                
    def _AddProxy( self, aService ):
        """Generate and add proxy for specified service"""
        # The proxy code is auto-generated (from the service XML) and then
        # imported and added as a class attribute to the device. Named the
        # same as the service, with lower-case first letter. All ohNet proxy
        # actions and properties are accessible via these attributes
        #
        # TestBasic service   -> device.testBasic
        # AVTransport service -> device.aVTRansport
        attrName  = aService['name'][0].lower() + aService['name'][1:]
        proxyName = 'CpProxy%s%s%s' % \
            (aService['domain'], aService['name'][0].upper() + aService['name'][1:], aService['version'])

        # configure (and create if necessary) directory for generated proxies
        head, tail = os.path.split( os.path.dirname( __file__ ))
        proxyDir = os.path.join( head, '.GeneratedProxies' )
        if not os.path.exists( proxyDir ):
            os.mkdir( proxyDir )
        if proxyDir not in sys.path:
            sys.path.append( proxyDir )

        # generate the proxy from the service XML
        serviceXml = urllib2.urlopen( aService['url'] ).read()
        proxy = GenProxy.GenProxy( aService['type'], serviceXml )

        # write out and import the proxy (protected by system-wide mutex)
        mutex = GlobalLock.GlobalLock( 'proxyWriteMutex' )
        mutex.Acquire()
        proxyPath = os.path.join( proxyDir, proxyName+'.py' )
        proxy.Write( proxyPath )
        exec( 'import %s as proxyModule' % proxyName )
        os.chmod( proxyPath, stat.S_IRWXU | stat.S_IRWXG | stat.S_IRWXO )     # R/W by all (enables overwrite)
        mutex.Release()

        # add to list of available proxies
        setattr( self, attrName, eval( 'proxyModule.%s( self )' % proxyName ))
        self.proxies.append( attrName )
    
    def _GetUdn( self ):
        udn = ctypes.c_char_p()
        length = ctypes.c_int()
        self.lib.CpDeviceCGetUdn( self.handle, ctypes.byref( udn ), ctypes.byref( length ))
        return udn.value
    
    def _GetFriendlyName( self ):
        return self._GetAttribute( 'Upnp.FriendlyName' )

    def _GetDeviceXml( self ):
        return self._GetAttribute( 'Upnp.DeviceXml' )
    
    def _GetLocation( self ):
        return self._GetAttribute( 'Upnp.Location' )
    
    #
    # ==== Public interface ====
    #
    
    def Start( self, aProxies=None ):
        """Start device - add proxies for all or specified services on device"""
        if not aProxies: aProxies = ['all']
        services = self._GetServices()
        for service in services:
            if service['name'] in aProxies or 'all' in aProxies:
                self._AddProxy( service )
    
    def Shutdown( self ):
        PyOhNet.devices.remove( self )
        if self.handle:
            self.lib.CpDeviceCRemoveRef( self.handle )

    friendlyName = property( _GetFriendlyName, None, None, '' )        
    udn          = property( _GetUdn, None, None, '' )
    deviceXml    = property( _GetDeviceXml, None, None, '' )
    location     = property( _GetLocation, None, None, '' )
