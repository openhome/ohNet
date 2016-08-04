"""Update code to latest and build ohMediaPlayer
"""

import _Paths
import CommonBuild as BASE
import os
import platform
import sys

# NOTE - this requires GIT to operate without requirement for password entry.
#        the necessary SSH key must be configured on the GIT server machine
#        Use Git-bash on windows to generate key (ssh-keygen), and paste key
#        into ~/.ssh/authorized_keys on server


class BuildOhmp( BASE.CommonBuild ):

    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.CommonBuild.__init__( self )
        self.watchdogTime = 300  # secs
        self.excludes     = ['\\thirdparty\\',
                             "warning C4005: 'max' : macro redefinition",
                             "warning C4005: 'min' : macro redefinition",
                             'warning generated',
                             'warnings generated',
                             'TestUpnpErrors',
                             'FLAC__STREAM_DECODER_OGG_ERROR',
                             'Test 12: TestFailedConnection',
                             'Test 4: TestRestreamAfterM3uError',
                             'Test 5: TestStreamSegmentError',
                             'Test 10: TestSeekForwardFailStillSeeks',
                             'Test 2: TestRecognitionFail',
                             'Test 2: InsertFailsWhenIdAfterInvalid',
                             'Test 3: InsertFailsWhenFull',
                             'Test 15: GetTrackByInvalidIdFails',
                             'Test 9: TestPlayNoAfterNotifyFailed',
                             'Test 8: TestSeekForwardFailStillSeeks',
                             'Test 11: TestFailedConnection',
                             'Test 3: TestGetNextSegmentFail',
                             'Test 2: TestStreamErrorRecoverable',
                             'Test 3: TestStreamM3uError',
                             'Test 4: TestStreamSegmentError',
                             'Test 6: TestStreamM3uConnectionError',
                             'Test 8: TestStreamSegmentConnectionError',
                             'Test 9: TestSeekForwardFailStillSeeks',
                             'Failed to recognise audio format (iStreamStopped',
                             'Upnp error reporting tests',
                             '0 of',
                             "['valgrind', '--error-exitcode=255'",
                             'Memcheck; a memory error detector',
                             'ERROR SUMMARY: 0 errors from',
                             'For counts of detected and suppressed errors',
                             'a memory error detector']

    def Test( self, aArgs ):
        """Perform update and build"""
        buildOpts = ['--steps=default,-integration_test', '--incremental-fetch']

        if len( aArgs ) > 1:
            if aArgs[1].lower() == 'debug':
                buildOpts.append( '--debug' )

        go = 'go'
        if sys.platform in ['win32', 'win64', 'cli']:
            go += '.bat'

        ohmpPath  = os.path.normpath( os.path.split( os.getcwd() )[0] )
        goCmd     = os.path.normpath( os.path.join( ohmpPath, go ))
        cleanDeps = [goCmd, 'fetch', '--clean']
        buildCmd  = [goCmd, 'build']
        buildCmd.extend( buildOpts )
        self._Execute( ['git', 'pull'], ohmpPath, 'Updating source to latest' )
        self._Execute( cleanDeps, ohmpPath, 'Cleaning dependencies' )
        self._Execute( buildCmd, ohmpPath, 'Executing build' )

    @staticmethod
    def UpdatePyOhNetPath():
        """Update python search path (as PyOhNet may have changed from Release to Debug within build"""
        # Get pathing for for FunctionalTest
        root = os.path.dirname( __file__ )
        while not os.path.isdir( os.path.join( root, 'IntegrationTests' ) ):
            root = os.path.dirname( root )
        deps = os.path.join( root, 'dependencies' )

        # Get pathing for PyOhNet (platform/architecture dependent)
        ohnetRls = ''
        ohnetDbg = ''
        _platform = platform.system( )
        _architecture = platform.architecture( )
        if _platform in ['Windows', 'cli']:
            if '32' in _architecture[0]:
                ohnetRls = os.path.abspath( os.path.join( deps, 'Windows-x86/ohNet-Windows-x86-Release' ) )
                ohnetDbg = os.path.abspath( os.path.join( deps, 'Windows-x86/ohNet-Windows-x86-Debug' ) )
            elif '64' in _architecture[0]:
                ohnetRls = os.path.abspath( os.path.join( deps, 'Windows-x64/ohNet-Windows-x64-Release' ) )
                ohnetDbg = os.path.abspath( os.path.join( deps, 'Windows-x64/ohNet-Windows-x64-Debug' ) )
        elif _platform == 'Linux':
            if '32' in _architecture[0]:
                ohnetRls = os.path.abspath( os.path.join( deps, 'Linux-x86/ohNet-Linux-x86-Release' ) )
                ohnetDbg = os.path.abspath( os.path.join( deps, 'Linux-x86/ohNet-Linux-x86-Debug' ) )
            elif '64' in _architecture[0]:
                ohnetRls = os.path.abspath( os.path.join( deps, 'Linux-x64/ohNet-Linux-x64-Release' ) )
                ohnetDbg = os.path.abspath( os.path.join( deps, 'Linux-x64/ohNet-Linux-x64-Debug' ) )
        elif _platform == 'Darwin':
            ohnetRls = os.path.abspath( os.path.join( deps, 'Mac-x64/ohNet-Mac-x64-Release' ) )
            ohnetDbg = os.path.abspath( os.path.join( deps, 'Mac-x64/ohNet-Mac-x64-Debug' ) )
        if os.path.exists( ohnetRls ):
            ohnet = ohnetRls
        elif os.path.exists( ohnetDbg ):
            ohnet = ohnetDbg
        else:
            ohnet = deps  # should never happen

        # configure the Python module search path
        sys.path.insert( 0, os.path.normpath( os.path.join( ohnet, 'lib' ) ) )

    def Cleanup( self ):
        """Clean up base class"""
        self.UpdatePyOhNetPath()
        BASE.CommonBuild.Cleanup( self )


if __name__ == '__main__':

    BASE.Run( sys.argv )
