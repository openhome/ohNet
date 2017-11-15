"""PyOhNet: Test network adapter and adapter lists (manually check output)
"""
import sys
sys.path.append( '../..' )
import PyOhNet as ohNet


class TestAdapters:

    def __init__( self ):
        ohNet.Initialise()

    @staticmethod
    def Shutdown( ):
        ohNet.Shutdown()

    @staticmethod
    def ShowAdapters( ):
        adapterList = ohNet.AdapterList()
        print( '\n %d network adapters detected' % adapterList.size )
        for adapter in adapterList.adapters:
            print( '' )
            print( '    FullName:       %s' % adapter.fullName )
            print( '    Name:           %s' % adapter.name )
            print( '    Address:        %d' % adapter.address )
            print( '    Address (str):  %s' % adapter.addressStr )
            print( '    Subnet:         %d' % adapter.subnet )
            print( '    Subnet (str):   %s' % adapter.subnetStr )
            print( '    Net Mask:       %d' % adapter.mask )
            print( '    Net Mask (str): %s' % adapter.maskStr )


if __name__ == '__main__':

    e = TestAdapters()
    e.ShowAdapters()
    e.Shutdown()
