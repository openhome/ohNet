"""_Config - properties to access test configuration data (from __Config.xml)

Where any data is undefined, 'None' will be returned by getter
"""
import _FunctionalTest
import xml.etree.ElementTree as ET
import os
import platform

kConfigFile = '__Config.xml'

def _Find( aDomain, aValue ):
    val = None
    if aDomain is not None:
        val = aDomain.find( aValue )
        if val is not None:
            if not len( list( val )):
                val = val.text
    return val


class Config:

    def __init__( self ):

        config     = None
        configFile = os.path.abspath( kConfigFile )

        if os.path.exists( configFile ):
            computerName = platform.node()
            xml = ET.parse( configFile )

            computers = xml.iter( 'computer' )
            for computer in computers:
                if computer.attrib['name'] == computerName:
                    config = computer
                    break

        dir     = _Find( config, 'dir' )
        install = _Find( dir, 'install' )
        exakt   = _Find( dir, 'exakt' )
        self.cDir = Dir( {'install': install, 'exakt': exakt} )

        itunes  = _Find( config, 'itunes' )
        guid    = _Find( itunes, 'guid' )
        library = _Find( itunes, 'library' )
        address = _Find( itunes, 'address' )
        track1k = _Find( itunes, 'track1k' )
        self.cItunes = Itunes( {'guid': guid, 'library': library, 'address': address, 'track1k':track1k} )

        stimdev = _Find( config, 'stimdev' )
        self.cStimdev = Stimdev( stimdev )

        measdev = _Find( config, 'measdev' )
        self.cMeasdev = Measdev( measdev )

        playlist = _Find( config, 'playlist' )
        self.cPlaylist = Playlist( playlist )

        softplayer = _Find( config, 'softplayer' )
        adapter    = _Find( softplayer, 'adapter' )
        self.cSoftplayer = Softplayer( {'adapter':adapter} )

    dir        = property( lambda self: self.cDir )
    itunes     = property( lambda self: self.cItunes )
    stimdev    = property( lambda self: self.cStimdev )
    measdev    = property( lambda self: self.cMeasdev )
    playlist   = property( lambda self: self.cPlaylist )
    softplayer = property( lambda self: self.cSoftplayer )


class Dir():

    def __init__( self, aConfig={'install':None, 'exakt':None} ):
        self.config = aConfig

    install = property( lambda self: self.config['install'] )
    exakt   = property( lambda self: self.config['exakt'] )


class Itunes():

    def __init__( self, aConfig={'guid':None, 'library':None, 'address':None, 'track1k':None} ):
        self.config = aConfig

    guid    = property( lambda self: self.config['guid'] )
    library = property( lambda self: self.config['library'] )
    address = property( lambda self: self.config['address'] )
    track1k = property( lambda self: self.config['track1k'] )


class ExtDevice():

    def __init__( self, aExtDevice ):
        self.extDevice = aExtDevice

    def Device( self, aType, aNum ):
        entry  = _Find( self.extDevice, '%s%d' % (aType, aNum) )
        device = _Find( entry, 'device')
        name   = _Find( entry, 'name')
        return ExtDeviceInfo( {'device':device, 'name':name} )

class ExtDeviceInfo():

    def __init__( self, aConfig={'device':None, 'name':None} ):
        self.config = aConfig

    device = property( lambda self: self.config['device'] )
    name   = property( lambda self: self.config['name'] )


class Stimdev( ExtDevice ):

    def __init__( self, aStimdev ):
        ExtDevice.__init__( self, aStimdev )

    anadig1 = property( lambda self: self.Device( 'anadig', 1 ) )
    anadig2 = property( lambda self: self.Device( 'anadig', 2 ))
    anadig3 = property( lambda self: self.Device( 'anadig', 3 ))
    anadig4 = property( lambda self: self.Device( 'anadig', 4 ))
    anadig5 = property( lambda self: self.Device( 'anadig', 5 ))

    hdmi1   = property( lambda self: self.Device( 'hdmi', 1 ))
    hdmi2   = property( lambda self: self.Device( 'hdmi', 2 ))
    hdmi3   = property( lambda self: self.Device( 'hdmi', 3 ))
    hdmi4   = property( lambda self: self.Device( 'hdmi', 4 ))


class Measdev( ExtDevice ):

    def __init__( self, aMeasdev ):
        ExtDevice.__init__( self, aMeasdev )

    scope1 = property( lambda self: self.Device( 'scope', 1 ) )
    scope2 = property( lambda self: self.Device( 'scope', 2 ))
    scope3 = property( lambda self: self.Device( 'scope', 3 ))
    scope4 = property( lambda self: self.Device( 'scope', 4 ))
    scope5 = property( lambda self: self.Device( 'scope', 5 ))


class StimDev():

    def __init__( self, aConfig={'device':None, 'name':None} ):
        self.config = aConfig

    device = property( lambda self: self.config['device'] )
    name   = property( lambda self: self.config['name'] )


class Playlist():

    def __init__( self, aPlaylist ):
        self.playlist = aPlaylist

    def Server( self, aServer ):
        server  = _Find( self.playlist, '%s' % aServer )
        encodings = _Find( server, 'encodings' )
        mixed     = _Find( server, 'mixed' )
        albums    = _Find( server, 'albums' )
        return PlaylistInfo( {'encodings':encodings, 'mixed':mixed, 'albums':albums} )

    asset = property( lambda self: self.Server( 'asset' ))


class PlaylistInfo():

    def __init__( self, aConfig={'encodings':None, 'mixed':None, 'albums':None} ):
        self.config = aConfig

    encodings = property( lambda self: self.config['encodings'] )
    mixed     = property( lambda self: self.config['mixed'] )
    albums    = property( lambda self: self.config['albums'] )


class Softplayer():

    def __init__( self, aConfig={'adapter':None} ):
        self.config = aConfig

    adapter = property( lambda self: self.config['adapter'] )
