#!/usr/bin/env python
"""TestTidalDropout - test for dropout from TIDAL served tracks.

Parameters:
    arg#1 - Sender DUT
    arg#2 - Receiver/Repeater DUT (None = not present)
    arg#3 - Receiver/SlaveDUT  (None = not present)
    arg#4 - Test duration (secs) or 'forever'
    arg#5 - Number of tracks to test with (use 0 for fixed list of 20 hard-coded tracks)
    arg#6 - Tidal ID
    arg#7 - Tidal username
    arg#8 - Tidal password
local' for internal SoftPlayer on loopback for DUTs

Verifies TIDAL served audio played by the DUT does not suffer from audio dropout.
Additionally checks for dropout on downstream songcast receiver(s)
"""

import _FunctionalTest
import _BaseDropout    as BASE
import os
import sys

kTidalCreds  = 'tidalhifi.com'
kTidalTracks = [
    ('tidal://track?version=1&trackId=33198915', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Trains</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=33198909</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Prog Rock Greats</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Porcupine Tree</upnp:artist><res>tidal://track?version=1&amp;trackId=33198915</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=33198923', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Back Street Luv</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=33198909</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Prog Rock Greats</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Curved Air</upnp:artist><res>tidal://track?version=1&amp;trackId=33198923</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=3327244',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Teen Angst (What The World Needs Now)</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=3327227</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Drive Fast, Rock Hard</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Cracker</upnp:artist><res>tidal://track?version=1&amp;trackId=3327244</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=19604760', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">What Is Right</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=19604756</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Buddha Lounge</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Marcator</upnp:artist><res>tidal://track?version=1&amp;trackId=19604760</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=11875185', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Swingjugend</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=11875180</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">These Metal Days</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">These Metal Days</upnp:artist><res>tidal://track?version=1&amp;trackId=11875185</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=8379405',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Solitary One</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=8379401</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Cars &amp; Trucks</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Cars &amp; Trucks</upnp:artist><res>tidal://track?version=1&amp;trackId=8379405</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=10040068', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Why Does The Zebra Wear Pajamas?</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=10040067</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Animal Songs</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Matan Ariel &amp; Michal Kaplan &amp; Ohad Segev &amp; Tom Rahav</upnp:artist><res>tidal://track?version=1&amp;trackId=10040068</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=2045056',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Save Yourself</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=2045041</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Shaun White Snowboarding: Official Soundtrack</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Stabbing Westward</upnp:artist><res>tidal://track?version=1&amp;trackId=2045056</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=2045044',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">We Come 1 (Radio Edit)</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=2045041</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Shaun White Snowboarding: Official Soundtrack</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Faithless</upnp:artist><res>tidal://track?version=1&amp;trackId=2045044</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=4951039',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Map Of The World</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=4951034</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Wonders Of The Younger (International Version)</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Plain White T`s</upnp:artist><res>tidal://track?version=1&amp;trackId=4951039</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=7048290',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">In a Big Country (Live)</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=7048283</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">101 80s Hits - New Wave, Old School Hip Hop, Hair Metal, Pop &amp; Rock</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Big Country</upnp:artist><res>tidal://track?version=1&amp;trackId=7048290</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=7397753',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Season Of The Witch</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=7397752</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">I Shot Andy Warhol (Music From And Inspired By The Motion Picture)</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Luna</upnp:artist><res>tidal://track?version=1&amp;trackId=7397753</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=9696875',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Send Me on My Way</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=9696865</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Rock - Live from Mountain Stage</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Rusted Root</upnp:artist><res>tidal://track?version=1&amp;trackId=9696875</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=24353073', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">DNA</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=24353066</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Running Hits Winter Mix</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Little Mix</upnp:artist><res>tidal://track?version=1&amp;trackId=24353073</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=2979769',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Spaceman</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=2979750</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Pure Dance Party</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Babylon Zoo</upnp:artist><res>tidal://track?version=1&amp;trackId=2979769</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=14596742', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Ti avrei voluto dire</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=14596734</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">L`arcobaleno della speranza</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Stefano Pippa</upnp:artist><res>tidal://track?version=1&amp;trackId=14596742</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=28528789', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Sick</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=28528782</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Change Your Tune, Vol. 2</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Polar Bears in Purgatory</upnp:artist><res>tidal://track?version=1&amp;trackId=28528789</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=20994125', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">It Takes A Real Man To Sing The Blues</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=20994120</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Silence So Loud</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">On Top Of The Avalanche</upnp:artist><res>tidal://track?version=1&amp;trackId=20994125</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=24219522', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Taxidermy</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=24219517</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">After Robots</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">BLK JKS</upnp:artist><res>tidal://track?version=1&amp;trackId=24219522</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=37606197', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Rialto Bridge</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=37606193</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Rialto Bridge</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Fine China</upnp:artist><res>tidal://track?version=1&amp;trackId=37606197</res></item></DIDL-Lite>')]


class TestTidalDropout( BASE.BaseDropout ):
    """Test dropout on of TIDAL served tracks"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.BaseDropout.__init__( self )
        self.doc = __doc__
        self.tidalId   = ''
        self.tidalUser = ''
        self.tidalPwd  = ''

    def Test( self, args ):
        """Test dropout on of TIDAL served tracks"""
        numTracks = 0
        try:
            numTracks    = int( args[5] )
            self.tidalId   = args[6]
            self.tidalUser = args[7]
            self.tidalPwd  = args[8]
            args[5] = {'aTidalId':args[6]}
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        if numTracks:
            import Instruments.Network.Tidal as Tidal
            tidal = Tidal.Tidal( self.tidalId, 'GB' )
            self.tracks = tidal.RandomTracks( numTracks )
            self.log.Pass( '', 'Testing with list of %d randomly selected' % numTracks )
        else:
            self.tracks = kTidalTracks
            self.log.Pass( '', 'Testing with list of 20 hard-coded tracks')
        BASE.BaseDropout.Test( self, args )

    def SenderSetup( self ):
        """Login to and enable TIDAL"""
        self.sender.credentials.Set( kTidalCreds, self.tidalUser, self.tidalPwd )
        self.sender.credentials.SetEnabled( kTidalCreds, True )

    def Cleanup( self ):
        """Perform post-test cleanup, logout of TIDAL"""
        if self.sender:
            self.sender.credentials.Clear( kTidalCreds )
        BASE.BaseDropout.Cleanup( self )

            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        