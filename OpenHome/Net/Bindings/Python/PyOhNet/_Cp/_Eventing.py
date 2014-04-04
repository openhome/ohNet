"""CpControl - python ohNet bindings to support Eventing of devices to CPs"""

import PyOhNet
import abc
import ctypes


class Property:
    __metaclass__ = abc.ABCMeta
    
    @abc.abstractmethod
    def __init__( self, aName, aCb ):
        self.lib = PyOhNet.lib
        self.handle = None
        self.name = aName
        CB = PyOhNet.makeCb( None, ctypes.c_void_p )
        self.callback = CB( aCb )
        
    def __str__( self ):
        msg = '      %s' % self.name
        return msg

        
class PropertyInt( Property ):
    
    def __init__( self, aName, aCb ):
        Property.__init__( self, aName, aCb )
        self.handle = self.lib.ServicePropertyCreateIntCp( ctypes.c_char_p( aName ), self.callback, None )
        
    def Value( self ):
        val = ctypes.c_int()
        self.lib.ServicePropertyValueInt( self.handle, ctypes.byref( val ) )
        return val.value

    def SetValue( self, aValue ):
        changed = self.lib.ServicePropertySetValueInt( self.handle, aValue )
        return (changed != 0)


class PropertyUint( Property ):
    
    def __init__( self, aName, aCb ):
        Property.__init__( self, aName, aCb )
        self.handle = self.lib.ServicePropertyCreateUintCp( ctypes.c_char_p( aName ), self.callback, None )
                               
    def Value( self ):
        val = ctypes.c_uint()
        self.lib.ServicePropertyValueUint( self.handle, ctypes.byref( val ) )
        return val.value

    def SetValue( self, aValue ):
        changed = self.lib.ServicePropertySetValueUint( self.handle, aValue )
        return (changed != 0)


class PropertyBool( Property ):
    
    def __init__( self, aName, aCb ):
        Property.__init__( self, aName, aCb )        
        self.handle = self.lib.ServicePropertyCreateBoolCp( ctypes.c_char_p( aName ), self.callback, None )
        
    def Value( self ):
        val = ctypes.c_uint()
        self.lib.ServicePropertyValueUint( self.handle, ctypes.byref( val ) )
        return val.value != 0

    def SetValue( self, aValue ):
        val = 0
        if aValue:
            val= 1
        changed = self.lib.ServicePropertySetValueBool( self.handle, val )
        return (changed != 0)


class PropertyString( Property ):
    
    def __init__( self, aName, aCb ):
        Property.__init__( self, aName, aCb )        
        self.handle = self.lib.ServicePropertyCreateStringCp( ctypes.c_char_p( aName ), self.callback, None )
        
    def Value( self ):
        ret = ''
        str = ctypes.c_char_p()
        len = ctypes.c_int()
        self.lib.ServicePropertyGetValueString( self.handle, ctypes.byref( str ), ctypes.byref( len ))
        if str.value is not None:
            ret = str.value[0:len.value]    
        return ret

    def SetValue( self, aValue ):
        val = ctypes.c_char_p( aValue )
        changed = self.lib.ServicePropertySetValueString( self.handle, aValue )
        return (changed != 0)


class PropertyBinary( Property ):
    
    def __init__( self, aName, aCb ):
        Property.__init__( self, aName, aCb )        
        self.handle = self.lib.ServicePropertyCreateBinaryCp( ctypes.c_char_p( aName ), self.callback, None )
        
    def Value( self ):
        bin = []
        pData = ctypes.pointer( ctypes.pointer( ctypes.c_ubyte() ))        
        length = ctypes.c_int()
        self.lib.ServicePropertyGetValueBinary( self.handle, pData, ctypes.byref( length ))
        data = pData.contents
        for i in range( length.value ):
            bin.append( data[i] )
        return bin

    def SetValue( self, aValue ):
        val = ctypes.c_void_p( aValue )
        len = len( aValue )
        changed = self.lib.ServicePropertySetValueBinary( self.handle, val, len )
        return (changed != 0)
