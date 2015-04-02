#!/usr/bin/env python
"""TestCompliance - ohMediaServer compliance test

Parameters:
    arg#1 - DUT - UPnP frindly name of device-under-test

Test to ensure device complies with ohMediaServer standard. Basically ensures that
all services, actions and attributes are correctly present and operational as defined
by ohMediaPlayer 'standard'
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import sys

kServices = {
    'Configuration':   {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Credentials':     {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Exakt':           {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Info':            {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'NetworkMonitor':  {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Playlist':        {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Product':         {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Radio':           {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Receiver':        {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Sender':          {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Time':            {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']},
    'Volume':          {'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            'a',
                            'b']}
}
kMandatory = ['Product']
kRequested = ['Credentials', 'Exakt', 'Info', 'Sender', 'Time', 'Volume']
kOptional  = ['Configuration', 'NetworkMonitor', 'Playlist', 'Radio', 'Receiver']


class TestCompliance( BASE.BaseTest ):
    
    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.dut            = None
        self.dutDev         = ''

    def Test( self, aArgs ):
        """Test compliance with ohMediaPlayer 'standard'"""
        dutName = ''
        try:
            dutName = aArgs[1]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( aArgs )) )

        self.dutDev = dutName.split( ':' )[0]
        self.dut = OHMP.OhMediaPlayerDevice( dutName )

        for service in kMandatory:
            self._Check( service, 'mandatory' )
        for service in kRequested:
            self._Check( service, 'requested' )
        for service in kOptional:
            self._Check( service, 'optional' )

    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut:
            self.dut.Shutdown()
        BASE.BaseTest.Cleanup( self )

    def _Check( self, aService, aType ):
        """Check for correct presence of service, and compliance thereof"""
        failure   = None
        present   = False
        requested = False
        try:
            present = hasattr( self.dut.device, aService[0].lower()+aService[1:] )
            requested = aService in self.dut.product.attributes
        except:
            pass

        if aType == 'mandatory':
            if not present:
                failure = 'Mandatory service <%s> NOT present' % aService
        elif aType == 'requested':
            self.log.Debug( '%s, %s' % (aService, str(present) ))
            if requested and not present:
                failure = 'Requested service <%s> NOT present' % aService
            if not requested and present:
                failure = 'Service <%s> NOT listed in product attributes' % aService

        if failure:
            self.log.Fail( self.dutDev, failure )
        else:
            if present:
                self._CheckCompliance( aService )

    def _CheckCompliance( self, aService ):
        """Check compliance of specified service"""
        self.log.Header1( self.dutDev, 'Checking compliance of <%s> service' % aService )


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
