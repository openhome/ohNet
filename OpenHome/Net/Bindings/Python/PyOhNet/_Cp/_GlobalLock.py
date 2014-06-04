"""GlobalLock: cross process / thread lock
"""
import os
import string
import sys

_windows = (sys.platform == 'win32')
_dotnet  = (sys.platform == 'cli')

if _windows:
    import win32event
    import win32api
    import pywintypes

elif _dotnet:
    import System.Threading

else:
    import fcntl
    import threading


class GlobalLock:
    """This lock must act as a global mutex (block between different processes
       AND between threads within the same process)"""

    def __init__( self, aName ):
        """Create OS specific mutex mechanism"""
        if _windows:
            self.name = string.replace( aName, '\\', '_' )
            self.mutex = win32event.CreateMutex( None, False, self.name )

        elif _dotnet:
            self.name = string.replace( aName, '\\', '_' )
            self.mutex = System.Threading.Mutex( self.name )

        else: # Unix
            self.name = os.path.join( os.environ['HOME'], '.' + aName )
            self.flock = open( self.name, 'w' )
            self.fdlock = self.flock.fileno()
            self.threadLock = threading.RLock()

    def __del__( self ):
        """Cleanup on destruction"""
        try:
            self.release()
        except:
            pass

        if _windows:
            win32api.CloseHandle( self.mutex )
        elif _dotnet:
            self.mutex.Close()
        else:
            self.flock.close()

    def Acquire( self ):
        """Locks - suspends caller until done"""
        if _windows:
            win32event.WaitForSingleObject( self.mutex, win32event.INFINITE )
        elif _dotnet:
            self.mutex.WaitOne()
        else:
            fcntl.flock( self.fdlock, fcntl.LOCK_EX )   # inter-process lock
            self.threadLock.acquire()                   # inter-thread lock

    def Release( self ):
        """Unlocks (caller must hold the lock)"""
        if _windows:
            win32event.ReleaseMutex( self.mutex )
        elif _dotnet:
            self.mutex.ReleaseMutex()
        else:
            self.threadLock.release()                   # inter-thread lock
            fcntl.flock( self.fdlock, fcntl.LOCK_UN )   # inter-process lock
