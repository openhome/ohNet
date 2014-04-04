"""PyOhNet: Test use of device list and devices (manually check output)
"""
import sys
sys.path.append( '../..' )
import PyOhNet as ohNet


class TestDeviceList:

    def __init__( self, aAdapter=None ):
        ohNet.Initialise()
        ohNet.Start( 'CP', aAdapter )
        self.devList = None
        
    def Shutdown( self ):        
        ohNet.Shutdown()

    def Show1( self ):
        print "\nSearching for devices (1) - press ENTER key to continue"
        self.devList = ohNet.Cp.DeviceListUpnpAll( self._Added1, self._Removed1 )
        x = sys.stdin.read( 1 )
        
    def Show2( self ):
        print "\nContinuing searching (2) - press ENTER to continue"
        self.devList.AddAddedCb( self._Added2 )
        self.devList.AddRemovedCb( self._Removed2 )
        x = sys.stdin.read( 1 )
        
    def Show3( self ):
        print "\nContinuing searching (3) - press ENTER key to continue"
        self.devList.RemoveAddedCb( self._Added1 )
        self.devList.RemoveRemovedCb( self._Removed1 )
        x = sys.stdin.read( 1 )

    def ShowAllDevs( self ):
        devs = self.devList.devs
        print '\n%d devices detected' % len( devs )
        for dev in devs:
            print ''
            print '    FriendlyName: %s' % dev.friendlyName
            print '    UDN:          %s' % dev.udn
    
    def _Added1( self, aDev ):
       print "    (1) ADDED ->", aDev.friendlyName
    
    def _Removed1( self, aDev ):
       print "    (1) REMOVED ->", aDev.friendlyName
                
    def _Added2( self, aDev ):
       print "    (2) ADDED ->", aDev.friendlyName
    
    def _Removed2( self, aDev ):
       print "    (2) REMOVED ->", aDev.friendlyName


if __name__ == '__main__':

    e = TestDeviceList()
    e.Show1()
    e.Show2()
    e.Show3()
    e.ShowAllDevs()
