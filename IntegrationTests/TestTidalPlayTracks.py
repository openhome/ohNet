#!/usr/bin/env python
"""TestTidalPlayTracks - test Playing of Tidal served tracks.

Parameters:
    arg#1 - Sender DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Receiver DUT ['local' for internal SoftPlayer on loopback] (None->not present)
    arg#3 - Time to play before skipping to next (None = play all)
    arg#4 - Repeat mode [on/off]
    arg#5 - Shuffle mode [on/off]
    arg#6 - Number of tracks to test with (use 0 for fixed list of 20 hard-coded tracks)
    arg#7 - Tidal ID
    arg#8 - Tidal username
    arg#9 - Tidal password

Test test which plays Tidal served tracks from a playlist sequentially. The tracks
may be played for their entirety or any specified length of time. Repeat and shuffle
modes may be selected
"""

import _FunctionalTest
import _BasePlayTracks                as BASE
import Upnp.ControlPoints.MediaServer as Server
import sys
import threading
import time

kTidalCreds  = 'tidalhifi.com'
kTidalTracks = [
    ('tidal://track?version=1&trackId=21691876', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Lonely Are the Brave</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=21691868</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">The Dark and the Light</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Doogie White &amp; La Paz</upnp:artist><res>tidal://track?version=1&amp;trackId=21691876</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=25319855', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Do It Again</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=25319854</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Do It Again</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Life On Standby</upnp:artist><res>tidal://track?version=1&amp;trackId=25319855</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=17719348', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Good Days</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=17719347</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Good Days</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Marmozets</upnp:artist><res>tidal://track?version=1&amp;trackId=17719348</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=36666349', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Black Brown and White</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=36666334</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Just the Blues</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Big Bill Broonzy</upnp:artist><res>tidal://track?version=1&amp;trackId=36666349</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=25347004', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Boo Hoo Hoo</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=25347003</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Boo Hoo Hoo</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">No Sinner</upnp:artist><res>tidal://track?version=1&amp;trackId=25347004</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=23093712', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Fade Into You</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=23093709</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Still Climbing</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Leslie West</upnp:artist><res>tidal://track?version=1&amp;trackId=23093712</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=20751430', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Mother Mary</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=20751426</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Beautiful Curse</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">The Quireboys</upnp:artist><res>tidal://track?version=1&amp;trackId=20751430</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=18233701', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Just a Ride</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=18233698</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">King of Conflict</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">The Virginmarys</upnp:artist><res>tidal://track?version=1&amp;trackId=18233701</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=18457099', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Kiss Tried To Kill Me</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=18457098</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Kiss Tried To Kill Me</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Black Spiders</upnp:artist><res>tidal://track?version=1&amp;trackId=18457099</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=31214177', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Bring Down the City</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=31214169</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Full Throttle</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Massive</upnp:artist><res>tidal://track?version=1&amp;trackId=31214177</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=25481067', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">I Bleed Rock + Roll</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=25481066</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Running With The Dogs</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">The Treatment</upnp:artist><res>tidal://track?version=1&amp;trackId=25481067</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=33093661', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Road Less Travelled</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=33093650</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">New Horizon</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">The Answer</upnp:artist><res>tidal://track?version=1&amp;trackId=33093661</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=30554888', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Chimpanzee Twist</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=30554880</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Fists Of Fury</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Tijuana Bibles</upnp:artist><res>tidal://track?version=1&amp;trackId=30554888</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=24155300', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Valley of the Dolls</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=24155292</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Mind Control</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Uncle Acid &amp; the Deadbeats</upnp:artist><res>tidal://track?version=1&amp;trackId=24155300</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=20159140', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Your Way</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=20159134</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Songs To Invade Countries To</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Voodoo Six</upnp:artist><res>tidal://track?version=1&amp;trackId=20159140</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=2717446',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Princess &amp; The Frog</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=2717437</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">The Jim Jones Revue</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">The Jim Jones Revue</upnp:artist><res>tidal://track?version=1&amp;trackId=2717446</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=16909477', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Rough Cut</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=16909471</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Ultimate Rebel</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Bonafide</upnp:artist><res>tidal://track?version=1&amp;trackId=16909477</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=36301127', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">Better Days</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=36301126</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Taking On The World (Deluxe Edition)</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Gun</upnp:artist><res>tidal://track?version=1&amp;trackId=36301127</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=9066215',  '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">One Bullet</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=9066204</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Bang!</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Thunder</upnp:artist><res>tidal://track?version=1&amp;trackId=9066215</res></item></DIDL-Lite>'),
    ('tidal://track?version=1&trackId=18440593', '<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title xmlns:dc="http://purl.org/dc/elements/1.1/">When I Get Down</dc:title><upnp:class xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">object.item.audioItem.musicTrack</upnp:class><upnp:albumArtURI xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">http://images.tidalhifi.com/im/im?w=250&amp;h=250&amp;albumid=18440586</upnp:albumArtURI><upnp:album xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Anthology 2003 - 2006</upnp:album><upnp:artist xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/">Logan</upnp:artist><res>tidal://track?version=1&amp;trackId=18440593</res></item></DIDL-Lite>')]


class TestTidalPlayTracks( BASE.BasePlayTracks ):
    """Test playing of UPnP Media Server served tracks"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.BasePlayTracks.__init__( self )
        self.doc     = __doc__
        self.tidalId = ''
        self.seqNum  = threading.Event()

    def Test( self, args ):
        """Check playback of Tidal served tracks"""
        numTracks = 0
        try:
            numTracks      = int( args[6] )
            self.tidalId   = args[7]
            self.tidalUser = args[8]
            self.tidalPwd  = args[9]
            args[6] = {'aTidalId':args[7]}
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

        BASE.BasePlayTracks.Test( self, args )

    def Cleanup( self ):
        """Perform post-test cleanup, logout of TIDAL"""
        if self.sender:
            self.sender.credentials.Clear( kTidalCreds )
        BASE.BasePlayTracks.Cleanup( self )

    def SenderSetup( self ):
        """Login to and enable TIDAL"""
        self.sender.credentials.AddSubscriber( self._CredentialsCb )
        self.seqNum.clear()
        self.sender.credentials.Set( kTidalCreds, self.tidalUser, self.tidalPwd )
        self.seqNum.wait( 10 )
        time.sleep( 1 )
        err = self.sender.credentials.Status( kTidalCreds )
        if err:
            self.log.Abort( 'Tidal', '%s' % err )
        else:
            self.sender.credentials.SetEnabled( kTidalCreds, True )
            self.log.Pass( self.senderDev, 'Logged into TIDAL' )
        self.sender.credentials.RemoveSubscriber( self._CredentialsCb )

    # noinspection PyUnusedLocal
    def _CredentialsCb( self, aService, aSvName, aSvVal, aSvSeq ):
        """Callback from Sender's Credentials service events"""
        if aSvName == 'SequenceNumber':
            self.seqNum.set()


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
    