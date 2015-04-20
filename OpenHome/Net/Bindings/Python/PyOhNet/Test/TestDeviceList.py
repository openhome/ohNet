"""PyOhNet: Test use of device list and devices (manually check output)
"""
import sys
sys.path.append( '../..' )
sys.path.append( '../../../../../../Build/Obj/Mac-x64/Release' )
import PyOhNet as ohNet


class TestDeviceList:

    def __init__( self, aAdapter=None ):
        ohNet.Initialise()
        ohNet.Start( 'CP', aAdapter )
        self.devList = None
        
    @staticmethod
    def Shutdown( ):
        ohNet.Shutdown()

    def Show1( self ):
        print "\nSearching for devices (1) - press ENTER key to continue"
        self.devList = ohNet.Cp.DeviceListUpnpAll( self._Added1, self._Removed1 )
        sys.stdin.read( 1 )
        
    def Show2( self ):
        print "\nContinuing searching (2) - press ENTER to continue"
        self.devList.AddAddedCb( self._Added2 )
        self.devList.AddRemovedCb( self._Removed2 )
        sys.stdin.read( 1 )
        
    def Show3( self ):
        print "\nContinuing searching (3) - press ENTER key to continue"
        self.devList.RemoveAddedCb( self._Added1 )
        self.devList.RemoveRemovedCb( self._Removed1 )
        sys.stdin.read( 1 )

    def ShowAllDevs( self ):
        devs = self.devList.devs
        print '\n%d devices detected' % len( devs )
        for dev in devs:
            print ''
            print '    FriendlyName: %s' % dev.friendlyName
            print '    UDN:          %s' % dev.udn
    
    @staticmethod
    def _Added1( aDev ):
       print "    (1) ADDED ->", aDev.friendlyName, '  ', aDev.handle
    
    @staticmethod
    def _Removed1( aDev ):
       print "    (1) REMOVED ->", aDev.friendlyName
                
    @staticmethod
    def _Added2( aDev ):
       print "    (2) ADDED ->", aDev.friendlyName
    
    @staticmethod
    def _Removed2( aDev ):
       print "    (2) REMOVED ->", aDev.friendlyName


if __name__ == '__main__':

    e = TestDeviceList()
    e.Show1()
    e.Show2()
    e.Show3()
    e.ShowAllDevs()
