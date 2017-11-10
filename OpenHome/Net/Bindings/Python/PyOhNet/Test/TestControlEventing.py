"""PyOhNet: Test discovery, control and eventing of TestBasic device
"""

# This expects an _ohNetTestDevice to be running on the default interface. This
# can be executed using TestDvTestBasic.exe with '-c /' parameter (provided in
# same directory as this file)

import sys
sys.path.append( '../..' )
import PyOhNet as ohNet
import os
import random
import threading
import time


class TestControlEventing:

    def __init__( self, aDevName, aDevDomain, aDevType, aDevVersion, aTimeout=10, aInterface=None ):
        """Initialise class data, start ohNet and UPnP discovery"""
        self.nameToFind    = None
        self.failed        = False
        self.evVarUint     = 0
        self.evVarInt      = 0
        self.evVarStr      = 0
        self.evVarBin      = 0
        self.nameFound     = threading.Event()
        self.initEvent     = threading.Event()
        self.uintChanged   = threading.Event()
        self.intChanged    = threading.Event()
        self.boolChanged   = threading.Event()
        self.strChanged    = threading.Event()
        self.binChanged    = threading.Event()
        self.anyChanged    = threading.Event()

        ohNet.Initialise()
        ohNet.Start( 'CP', aInterface )

        dev = self.FindDev( aDevName, aDevDomain, aDevType, aDevVersion, aTimeout )
        if dev:
            dev.Start()
            print( '\n' + str( dev ) + '\n' )
            self.testBasic = dev.OpenhomeOrgTestBasic
            self.TestBasicProxy()
            dev.Shutdown()
        else:
            print( 'FAILED to find %s' % aDevName )

        if self.failed:
            print( '\n*** FAILED ***' )
        else:
            print( '\n*** PASSED ***' )
        ohNet.Shutdown()
        # noinspection PyProtectedMember
        os._exit( 0 )

    def _DevAdded( self, aDev ):
        """Callback on devicelist added event"""
        if self.nameToFind == aDev.friendlyName:
            self.nameFound.set()

    def FindDev( self, aName, aDomain, aType, aVersion, aTimeout ):
        """Find device within specified time, returns None on failure"""
        devList = ohNet.Cp.DeviceListUpnpDeviceType( aDomain, aType, aVersion )
        if aName not in devList.friendlyNames:
            self.nameToFind = aName
            devList.AddAddedCb( self._DevAdded )
            self.nameFound.wait( aTimeout )
            devList.RemoveAddedCb( self._DevAdded )
        return devList.DevByName( aName )

    def _CheckSetGet( self, aVar, aSet, aGet, aEvented=None ):
        """Check set/get/evented variables all match"""
        time.sleep( 0.5 )   # let ANY event printout clear
        msg = 'Set %s to %s, Get returned %s' % (aVar, str(aSet), str(aGet))
        if aSet == aGet:
            print( '++PASS++ ', msg )
        else:
            print( '--FAIL-- ', msg )
            self.failed = True

        if aEvented is not None:
            msg = 'Set %s to %s, Event returned %s' % (aVar, str(aSet), str(aEvented))
            if aSet == aEvented:
                print( '++PASS++ ', msg )
            else:
                print( '--FAIL-- ', msg )
                self.failed = True

    def _CheckCombo( self, aAction, aSet, aGet, aExpected ):
        """Check combo (set/<alter>/get) actions"""
        msg = '%s set to %s returned %s' % (aAction, str(aSet), str(aGet))
        if aGet == aExpected:
            print( '++PASS++ ', msg )
        else:
            print( '--FAIL-- ', msg )
            self.failed = True

    def TestBasicProxy( self ):
        """Test the proxy to the TestBasic service"""

        # ==== Set up event handlers and start event monitoring ====

        self.testBasic.SetPropertyInitialEvent( self._InitEvent )
        self.testBasic.SetPropertyVarUintChanged( self._VarUintChanged )
        self.testBasic.SetPropertyVarIntChanged( self._VarIntChanged )
        self.testBasic.SetPropertyVarBoolChanged( self._VarBoolChanged )
        self.testBasic.SetPropertyVarStrChanged( self._VarStrChanged )
        self.testBasic.SetPropertyVarBinChanged( self._VarBinChanged )
        self.testBasic.SetPropertyChanged( self._AnyEvent )

        self.initEvent.clear()
        self.testBasic.Subscribe()
        print( "\nSubscribe to service" )
        self.initEvent.wait()

        # ==== Sync Set/Get Actions, with event checking ====

        self.uintChanged.clear()
        val = random.randint( 0, 99999 )
        res = self.testBasic.SyncSetUint( val )
        print( '\nSyncSetUint (%d) returned --> %s' % (val, str( res )) )
        res = self.testBasic.SyncGetUint()
        print( 'SyncGetUint returned -->', res )
        print( 'Waiting for Uint event' )
        self.uintChanged.wait()
        self._CheckSetGet( 'VarUint', val, res, self.evVarUint )

        self.intChanged.clear()
        val = random.randint( -99999, 99999 )
        res = self.testBasic.SyncSetInt( val )
        print( '\nSyncSetIint (%d) returned --> %s' % (val, str( res )) )
        res = self.testBasic.SyncGetInt()
        print( 'SyncGetInt returned -->', res )
        print( 'Waiting for Int event' )
        self.intChanged.wait()
        self._CheckSetGet( 'VarInt', val, res, self.evVarInt )

        self.boolChanged.clear()
        bool1 = not random.randint( 0, 1 )
        res = self.testBasic.SyncSetBool( bool1 )
        print( '\nSyncSetBool (%s) returned --> %s' % (bool1, res) )
        res = self.testBasic.SyncGetBool()
        print( 'SyncGetBool returned -->', res )
        print( 'Waiting for Bool event' )
        self.boolChanged.wait( 10 )  # timeout as 50% chance nothing changed
        self._CheckSetGet( 'VarBool', bool1, res, None )

        self.strChanged.clear()
        string = time.asctime()
        res = self.testBasic.SyncSetString( string )
        print( '\nSyncSetString (%s) returned --> %s ' % (string, str( res )) )
        res = self.testBasic.SyncGetString()
        print( 'SyncGetString returned -->', res )
        print( 'Waiting for String event' )
        self.strChanged.wait()
        self._CheckSetGet( 'VarString', string, res, self.evVarStr )

        self.binChanged.clear()
        randomData = [random.randint( 0, 255 ), 0, random.randint( 0, 255 ), 0, 3, 0]
        binArray = bytearray( randomData )  # Py2 and Py3
        # binArray = ''
        # for item in randomData:
        #     binArray += chr( item )       # Py2 ONLY
        res = self.testBasic.SyncSetBinary( binArray )
        print( '\nSyncSetBinary (%s) returned --> %s' % (randomData, res) )
        res = self.testBasic.SyncGetBinary()
        print( 'SyncGetBinary returned --> %s' % res )
        print( 'Waiting for Binary event' )
        self.binChanged.wait()
        self._CheckSetGet( 'VarBin', randomData, res, self.evVarBin )

        self.anyChanged.clear()
        val1 = random.randint( 0, 99999 )
        val2 = random.randint( 0, 99999 )
        bool1 = not random.randint( 0, 1 )
        res = self.testBasic.SyncSetMultiple( val1, val2, bool1 )
        print( '\nSyncSetMultiple (%d, %d, %s) returned --> %s' % (val1, val2, bool1, res) )
        res = self.testBasic.SyncGetMultiple()
        print( 'SyncGetMultiple returned --> %s' % res )
        print( 'SyncGetUint returned -->', self.testBasic.SyncGetUint() )
        print( 'SyncGetInt returned -->', self.testBasic.SyncGetInt() )
        print( 'SyncGetBool returned -->', self.testBasic.SyncGetBool() )
        print( 'Waiting for ANY event' )
        self.anyChanged.wait()
        self._CheckSetGet( 'Multiple:VarUint', val1, res['ValueUint'], self.evVarUint )
        self._CheckSetGet( 'Multiple:VarInt', val2, res['ValueInt'], self.evVarInt )
        self._CheckSetGet( 'Multiple:VarInt', bool1, res['ValueBool'], None )

        # ==== Combined actions ====

        res = self.testBasic.SyncIncrement( 42 )
        print( '\nSyncIncrement (42) returned -->', res )
        self._CheckCombo( 'SyncIncrement', 42, res, 43 )

        res = self.testBasic.SyncDecrement( 667 )
        print( '\nSyncDecrement (667) returned -->', res )
        self._CheckCombo( 'SyncDecrement', 667, res, 666 )

        res = self.testBasic.SyncToggle( True )
        print( '\nSyncToggle (True) returned -->', res )
        self._CheckCombo( 'SyncToggle', True, res, False )

        res = self.testBasic.SyncEchoString( 'Echo..' )
        print( '\nSyncEchoString (Echo..) returned -->', res )
        self._CheckCombo( 'SyncEchoString', 'Echo..', res, 'Echo..' )

        data = [0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0]
        binArray = bytearray( data )  # Py2 and Py3
        # binArray = ''
        # for item in data:
        #     binArray += chr( item )   # Py2 ONLY
        res = self.testBasic.SyncEchoBinary( binArray )
        print( '\nSyncEchoBinary (%s) returned --> %s' % (data, res) )
        self._CheckCombo( 'SyncEchoBinary', data, res, data )

        print( "\nUnsubscribe from service - no further events monitored\n" )
        self.testBasic.Unsubscribe()

        # Allowed value / range actions

        res = self.testBasic.SyncEchoAllowedRangeUint( 12 )
        print( 'SyncEchoAllowedRangeUint (12) returned -->', res )

        # res = self.testBasic.SyncEchoAllowedRangeUint( 37 )            causes assert
        # print 'SyncEchoAllowedRangeUint (37) returned -->', res        see #1006

        res = self.testBasic.SyncEchoAllowedValueString( 'One' )
        print( 'SyncEchoAllowedValueString (One) returned -->', res )

        # res = self.testBasic.SyncEchoAllowedValueString( 'Zero' )      causes assert
        # print 'SyncEchoAllowedValueString (Zero) returned -->', res    see #1006

        # ==== Misc actions ====

        res = self.testBasic.SyncWriteFile( 'Test data\nSecond line', 'c:\\Temp\\TestDvTestBasic.out' )
        print( 'SyncWriteFile returned -->', res )
        time.sleep( 1 )

    # ==== Event (Property) Callbacks ====

    def _AnyEvent( self ):
        print( 'EVENT Any' )
        self.anyChanged.set()

    def _InitEvent( self ):
        print( 'EVENT Init Event' )
        print( '    VarUint:',  self.testBasic.PropertyVarUint() )
        print( '    VarInt: ',  self.testBasic.PropertyVarInt() )
        print( '    VarBool:',  self.testBasic.PropertyVarBool() )
        print( '    VarStr: ',  self.testBasic.PropertyVarStr() )
        print( '    VarBin :',  self.testBasic.PropertyVarBin() )
        self.initEvent.set()

    def _VarUintChanged( self ):
        self.evVarUint = self.testBasic.PropertyVarUint()
        print( 'EVENT VarUint:', self.evVarUint )
        self.uintChanged.set()

    def _VarIntChanged( self ):
        self.evVarInt = self.testBasic.PropertyVarInt()
        print( 'EVENT VarInt:', self.evVarInt )
        self.intChanged.set()

    def _VarBoolChanged( self ):
        print( 'EVENT VarBool:', self.testBasic.PropertyVarBool() )
        self.boolChanged.set()

    def _VarStrChanged( self ):
        self.evVarStr = self.testBasic.PropertyVarStr()
        print( 'EVENT VarStr:', self.evVarStr )
        self.strChanged.set()

    def _VarBinChanged( self ):
        self.evVarBin = self.testBasic.PropertyVarBin()
        print( 'EVENT VarBin:', self.evVarBin )
        self.binChanged.set()


if __name__ == '__main__':

    e = TestControlEventing('_ohNetTestDevice', 'openhome.org', 'Test', 1, 10, None )
