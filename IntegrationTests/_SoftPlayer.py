"""Wrapper for TestMediaPlayer executable

Wraps the TestmediaPlayer executable to permit simple start/stop/configuration 
from integration tests, and to capture SoftPlayer output to test logs
"""

import _FunctionalTest
import Component as BASE
import os
import platform
import subprocess
import threading
import time
import xml.etree.ElementTree as ET

kExe = os.path.join( 'buildhudson', 'TestMediaPlayer.exe' )


class SoftPlayer( BASE.Component ):
    "Class to wrap SoftPlayer executable (TestMediaPlayer.exe)" 
    
    def __init__( self, 
                  aRoom         = None,     # defaults to 'SoftPlayer'
                  aName         = None,     # defaults to 'SoftPlayer'
                  aTuneIn       = None,     # defaults to 'linnproducts'
                  aSenderChannel= None ):   # defaults to a random value
        """Start the SoftPlayer - all parameters are optional and will default
        as described above. These 'configuration' options cannot be changed on
        a running SoftPlayer, so have to be initialised at creation"""
        BASE.Component.__init__( self )
        self.shutdown = False
        self.room     = None
        
        if aRoom == None:
            self.dev = '[SoftPlayer]'
        else:
            self.dev = '[' + aRoom + ']'

        exePath = ''        
        path1 = os.path.abspath( os.path.join( '.', kExe ))
        path2 = os.path.abspath( os.path.join( '..', kExe ))
        if os.path.isfile( path1 ):
            exePath = path1
        elif os.path.isfile( path2 ):
            exePath = path2
        else:
            self.log.Abort( '', 'No SoftPlayer executable found' )
        self.log.Info( '', 'Using SoftPlayer executable at %s' % exePath )
        
        cmd = exePath
        if aRoom:
            cmd += ' -r %s' % aRoom
        if aName:
            cmd += ' -n %s' % aName
        cmd += ' -a %d' % self.__GetHost()
        if aTuneIn:
            cmd += ' -t %s' % aTuneIn
        if aSenderChannel:
            cmd += ' -c %d' % aSenderChannel
        self.log.Info( '', 'SoftPlayer command: %s' % cmd )
            
        self.proc = subprocess.Popen( cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT )
        self.logThread = threading.Thread( target=self.__Log ) 
        self.logThread.start()
        time.sleep( 1 )             # Let it start up 
        
    def Shutdown( self ):
        self.log.Info( self.dev, 'Shutting down......')
        self.shutdown = True
        self.proc.stdin.write( 'q\n' )
        self.proc.stdin.close()
        self.proc.wait()
        self.logThread.join() 
        time.sleep( 1 )             # Let it shut down 
        
    def __Log( self ):
        "Log data received from stdout on SoftPlayer"
        exception = False
        while not self.shutdown:
            msg = self.proc.stdout.readline()
            if 'Unhandled' in msg:
                exception = True
                
            if not exception: 
                self.log.Info( self.dev, '%s' % msg )
            else:
                self.log.Fail( self.dev, '%s' % msg )
                self.shutdown = True        # force loop exit        
            
        msg = self.proc.stdout.readline()   # clear out remaining messages        
        while msg:
            self.log.Info( self.dev, '%s' % msg )
            msg = self.proc.stdout.readline()        

    def __GetHost( self ):
        "Retrieve host adapter to use for player"
        configFile = os.path.abspath( 'Config.xml') 
        if not os.path.exists( configFile ):
            host = 0 
        else:
            config = None
            computerName = platform.node().split( '.' )[0]
            xml = ET.parse( configFile )
            computers = xml.getiterator( 'computer' )
            for computer in computers:
                if computer.attrib['name'] == computerName:
                    config = computer
                    break
            if config is not None:
                adapter = config.find( 'adapter' )
                if adapter is None:
                    host = 0
                else:
                    host = int( adapter.text )
        return host
    
    
if __name__ == '__main__':

    import msvcrt
    import time
        
    s = SoftPlayer( aRoom='TestDev', aHost=1)
    msvcrt.getch()
    s.Shutdown()
    s.log.Cleanup()
