"""PyOhNet: control point device support
"""
import PyOhNet
import ctypes
import re
import sys
import types
import xml.etree.ElementTree as ET
import _Cp._GenProxy as GenProxy

try:
    # python 2.x
    from urlparse import urljoin
    from urllib2 import urlopen
except:
    # python 3.x
    from urllib.parse import urljoin
    from urllib.request import urlopen


class Device():
    """UPnP Device (from perspective of a control point)"""

    def __init__( self, aHandle ):
        self.lib = PyOhNet.lib
        self.handle = ctypes.c_void_p( aHandle )
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
        result = ''
        request  = ctypes.c_char_p( aAttr.encode( 'utf8', 'replace' ))
        response = ctypes.c_char_p()
        self.lib.CpDeviceCGetAttribute( self.handle, request, ctypes.byref( response ))
        if response.value:
            result = response.value.decode( 'utf8', 'replace' )
        return result

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
                url  = urljoin( baseUrl, service.find( 'SCPDURL' ).text )
                m = re.match('urn:([\w\-\.]+):service:([\w\-\.]+):(\d+)', svType )
                domain, name, version = m.groups()
                domainName = ''
                fields = domain.replace( '.', '-' ).split( '-' )
                for field in fields:
                    domainName += field[0].upper()
                    domainName += field[1:]
                result.append( {'type': svType, 'url': url, 'domain': domainName, 'name': name, 'version': int( version )} )
        return result

    # noinspection PyUnusedLocal
    def _AddProxy( self, aService ):
        """Generate and add proxy for specified service"""
        # The proxy code is auto-generated (from the service XML) and then
        # imported and added as a class attribute to the device. Named as
        # 'DomainService'. All ohNet proxy actions and properties are
        # accessible via these attributes
        #
        # TestBasic service   -> device.testBasic
        # AVTransport service -> device.aVTRansport
        attrName  = aService['domain'] + aService['name']
        proxyName = 'CpProxy%s%s%s' % \
            (aService['domain'], aService['name'][0].upper() + aService['name'][1:], aService['version'])

        # generate the proxy from the service XML
        serviceXml = urlopen( aService['url'] ).read()  # <<<<<<<<<==================================== This is failure point in discovery
                                                        # we get list of services back from ohnet, but fail to open URL for FIRST service
                                                        # so cannot create proxy (and everything eventually times out). No idea why - most
                                                        # likely product doesn't respond for whatever reason. Pissing around with delays
                                                        # doesn't seem to help much (adding prints did a bit, so some delays somewhere will
                                                        # probably reduce this) 
        proxy = GenProxy.GenProxy( aService['type'], serviceXml )

        # 'import' the generated proxies
        # we always rebuild the module with the most recently read service
        # definition, as service implementation details can vary between
        # different implementations of the same same services. More efficient
        # to only build module on first request and re-use it, but this DOES
        # give issues in case described above
        if proxyName in sys.modules.keys():
            proxyModule = sys.modules[proxyName]
        else:
            proxyModule = types.ModuleType( proxyName )
            sys.modules[proxyName] = proxyModule
        exec( proxy.text, proxyModule.__dict__ )

        # # FOR DEBUG - write generated proxies to, and import from file
        # #             NOTE - no mutex protection on file access, so do NOT use this
        # #                    technique except when debugging is necessary
        # import os
        # head, tail = os.path.split( os.path.dirname( __file__ ))
        # proxyDir = os.path.join( head, '.GeneratedProxies' )
        # if not os.path.exists( proxyDir ):
        #     os.mkdir( proxyDir )
        # if proxyDir not in sys.path:
        #     sys.path.append( proxyDir )
        # proxyPath = os.path.join( proxyDir, proxyName + '.py' )
        # proxy.Write( proxyPath )
        # exec( 'import %s as proxyModule' % proxyName )

        # add to list of available proxies
        setattr( self, attrName, eval( 'proxyModule.%s( self )' % proxyName ))
        self.proxies.append( attrName )

    def _GetUdn( self ):
        udn = ctypes.c_char_p()
        length = ctypes.c_int()
        self.lib.CpDeviceCGetUdn( self.handle, ctypes.byref( udn ), ctypes.byref( length ))
        return udn.value.decode( 'utf8', 'replace' )

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
        if not aProxies:
            aProxies = ['all']
        services = self._GetServices()
        for service in services:
            if service['name'] in aProxies or 'all' in aProxies:
                self._AddProxy( service )

    def Shutdown( self ):
        if self.handle:
            try:
                PyOhNet.devices.remove( self )
            except:
                pass
            self.lib.CpDeviceCRemoveRef( self.handle )
            self.handle = None

    friendlyName = property( _GetFriendlyName, None, None, '' )
    udn          = property( _GetUdn, None, None, '' )
    deviceXml    = property( _GetDeviceXml, None, None, '' )
    location     = property( _GetLocation, None, None, '' )
