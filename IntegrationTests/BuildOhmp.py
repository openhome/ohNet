"""Utility to update code to latest and build ohMediaPlayer
"""

import _FunctionalTest
import BaseTest as BASE
import os
import subprocess
import sys
import threading

# NOTE - this requires GIT to operate without requirement for password entry.
#        the necessary SSH key must be configured on the GIT server machine
#        Use Git-bash on windows to generate key (ssh-keygen), and paste key
#        into ~/.ssh/authorized_keys on server

kWatchdogTime = 60  # secs
kExcludes     = ['TestUpnpErrors',
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
                 'Failed to recognise audio format (iStreamStopped',
                 'Upnp error reporting tests',
                 '0 of']

class BuildOhmp( BASE.BaseTest ):

    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.logThread = None
        self.proc      = None
        self.jobDone   = False

    def Test( self, aArgs ):
        """Perform update and build"""
        buildOpts = '--steps="default,-integration_test" --incremental-fetch'

        if len( aArgs ) > 1:
            if aArgs[1].lower() == 'debug':
                buildOpts += ' --debug'

        ohmpPath = os.path.normpath( os.path.split( os.getcwd() )[0] )
        self.__Execute( 'git pull', ohmpPath, 'Updating source to latest' )
        self.__Execute( '%s\\go.bat build %s' % (ohmpPath, buildOpts), ohmpPath, 'Executing build' )

    def __Execute( self, aCmd, aCwd, aMsg ):
        """Execute the command in defined CWD, logging to FunctionalTest logger"""
        self.log.Header2( '', aMsg )
        self.watchdog = threading.Timer( kWatchdogTime, self.__Watchdog )
        self.watchdog.start()
        self.jobDone = False
        self.log.Info( '', '%s' % aCmd )
        self.proc = subprocess.Popen( aCmd, cwd=aCwd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT )
        logThread = threading.Thread( target=self.__Log )
        logThread.start()
        self.proc.wait()
        self.jobDone = True
        logThread.join()
        self.watchdog.cancel()

    def __Log( self ):
        """Log data received from stdout/stderr"""
        while not self.jobDone:
            msg = self.proc.stdout.readline()
            self.__ResetWatchdog()
            lower = msg.lower()
            if 'fail' in lower or 'abort' in lower or 'error' in lower:
                fail = True
                for exclude in kExcludes:
                    if exclude in msg:
                        fail = False
                        break
                if fail:
                    self.log.Fail( '', '%s' % msg )
                else:
                    self.log.Info( '', '%s' % msg )
            elif 'warn' in lower:
                self.log.Warn( '', '%s' % msg )
            elif 'pass' in lower:
                self.log.Pass( '', '%s' % msg )
            else:
                self.log.Info( '', '%s' % msg )

    def __ResetWatchdog( self ):
        """Reset the watchdog timer"""
        self.watchdog.cancel()
        self.watchdog = threading.Timer( kWatchdogTime, self.__Watchdog )
        self.watchdog.start()

    def __Watchdog( self ):
        """Watchdog timer CB - exit the build"""
        self.log.Fail( '', 'Watchdog timer tripped - forcing build exit' )
        self.proc.kill()

    def Cleanup( self ):
        """Clean up base class"""
        BASE.BaseTest.Cleanup( self )


if __name__ == '__main__':

    BASE.Run( sys.argv )
