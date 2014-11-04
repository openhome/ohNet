"""CpControl - python ohNet bindings to support Control of devices by CPs"""

import PyOhNet
import abc
import copy
import ctypes

kMaxInt32 = 2147483647
kMinInt32 = -2147483648
kMaxUint  = 4294967295

gAsyncCbs = []

class Action:
    """Define the controllable ACTION"""
    
    def __init__( self, aName ):
        self.lib = PyOhNet.lib
        self.lib.ServiceActionCreate.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.ServiceActionCreate( aName ))
        self.inputParams = []
        self.outputParams = []
        PyOhNet.actions.append( self )

    def Shutdown( self ):
        PyOhNet.actions.remove( self )
        if self.handle is not None:
            self.lib.ServiceActionDestroy( self.handle )
            self.handle = None

    def AddInputParameter( self, aParam ):
        self.inputParams.append( aParam )
        self.lib.ServiceActionAddInputParameter( self.handle, aParam.handle )
        
    def AddOutputParameter( self, aParam ):
        self.outputParams.append( aParam )
        self.lib.ServiceActionAddOutputParameter( self.handle, aParam.handle )
        
    def InputParameter( self, aIndex ):
        return self.inputParams[aIndex]
        
    def OutputParameter( self, aIndex ):
        return self.outputParams[aIndex]
    
    def Name( self ):
        strn = ctypes.c_char_p()
        length = ctypes.c_int()
        self.lib.ServiceActionGetName( self.handle, ctypes.byref( strn ), ctypes.byref( length ))
        return strn.value

    def __str__( self ):
        msg = '      %s:' % self.Name()
        msg += '\n        Inputs:'
        for param in self.inputParams:
            msg += '\n' + param.__str__()
        msg += '\n        Outputs:'
        for param in self.outputParams:
            msg += '\n' + param.__str__()
        return msg

#
# ==== Invocation / Response handling ====
#

# noinspection PyUnusedLocal
class Invocation:
    """Define and setup the invocation - called back on action completion/errors"""
    
    def __init__( self, aService, aAction, aCb ):
        global gAsyncCbs
        self.lib = PyOhNet.lib
        self.callersCb = aCb
        CB = PyOhNet.makeCb( None, ctypes.c_void_p, ctypes.c_void_p )
        asyncCb = CB( self.AsyncComplete )
        self.lib.CpServiceInvocation.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.CpServiceInvocation( aService, aAction.handle, asyncCb, None ))
        gAsyncCbs.append( {'handle':self.handle, 'cb':asyncCb} )    # keep CB in scope until called

    def AddInput( self, aArgument ):
        self.lib.CpInvocationAddInput( self.handle, aArgument.handle )
                
    def AddOutput( self, aArgument ):
        self.lib.CpInvocationAddOutput( self.handle, aArgument.handle )
                
    def AsyncComplete( self, aDummy, aHandle ):
        self.callersCb( ctypes.c_void_p( aHandle ))
        
        
class InvocationResponse:
    """Extract response to an invocation on completion"""
    
    def __init__( self, aHandle ):
        global gAsyncCbs
        self.lib = PyOhNet.lib
        self.handle = aHandle
        for cb in gAsyncCbs:
            if cb['handle'] == self.handle:
                gAsyncCbs.remove( cb )
                break

    def Error( self ):
        code = ctypes.c_int()
        desc = ctypes.c_char_p()
        err = self.lib.CpInvocationError( self.handle, ctypes.byref( code ), ctypes.byref( desc ))
        return {'err':err!=0, 'code':code.value, 'desc':desc.value}

    def OutputInt( self, aIndex ):
        return self.lib.CpInvocationOutputInt( self.handle, aIndex )
        
    def OutputUint( self, aIndex ):
        return self.lib.CpInvocationOutputUint( self.handle, aIndex )
            
    def OutputBool( self, aIndex ):
        val = self.lib.CpInvocationOutputBool( self.handle, aIndex )
        return val != 0
    
    def OutputString( self, aIndex ):
        string = ''
        strn   = ctypes.c_char_p()
        length = ctypes.c_int()
        self.lib.CpInvocationGetOutputString( self.handle, aIndex, ctypes.byref( strn ), ctypes.byref( length ))
        if strn.value:
            string = copy.deepcopy( strn.value )
        self.lib.OhNetFree( strn )
        return string
    
    def OutputBinary( self, aIndex ):
        binary = []
        pData  = ctypes.pointer( ctypes.c_ubyte() )
        ppData = ctypes.pointer( pData )
        length = ctypes.c_int()
        self.lib.CpInvocationGetOutputBinary( self.handle, aIndex, ppData, ctypes.byref( length ))
        data = ppData.contents
        for i in range( length.value ):
            binary.append( data[i] )
        self.lib.OhNetFree( pData )
        return binary
    
#
# ==== Parameters ====
#

class Parameter:
    __metaclass__ = abc.ABCMeta
    
    @abc.abstractmethod
    def __init__( self, aName, aType ):
        self.lib = PyOhNet.lib
        self.handle = None
        self.name = aName
        self.type = aType
        
    def __str__( self ):
        msg = '          %s (%s)' % (self.name, self.type)
        return msg
    

class ParameterInt( Parameter ):
    
    def __init__( self, aName, aMinValue=kMinInt32, aMaxValue=kMaxInt32, aStep=1 ):
        Parameter.__init__( self, aName, 'Int' )
        self.lib.ServiceParameterCreateInt.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.ServiceParameterCreateInt( aName, aMinValue, aMaxValue, aStep ))


class ParameterUint( Parameter ):
    
    def __init__( self, aName, aMinValue=0, aMaxValue=kMaxUint, aStep=1 ):
        Parameter.__init__( self, aName, 'Uint' )
        self.lib.ServiceParameterCreateUint.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.ServiceParameterCreateUint( aName, aMinValue, aMaxValue, aStep ))

        
class ParameterBool( Parameter ):
    
    def __init__( self, aName ):
        Parameter.__init__( self, aName, 'Bool' )
        self.lib.ServiceParameterCreateBool.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.ServiceParameterCreateBool( aName ))


class ParameterString( Parameter ):
    
    # noinspection PyCallingNonCallable
    def __init__( self, aName, aAllowedValues=None ):
        if not aAllowedValues: aAllowedValues = []
        Parameter.__init__( self, aName, 'String' )
        numAllowedValues = len( aAllowedValues )
        allowed = (ctypes.c_char_p * numAllowedValues)()
        for i in range( numAllowedValues ):
            allowed[i] = aAllowedValues[i]
        self.lib.ServiceParameterCreateString.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.ServiceParameterCreateString( aName, allowed, numAllowedValues ))
        

class ParameterBinary( Parameter ):
    
    def __init__( self, aName ):        
        Parameter.__init__( self, aName, 'Binary' )
        self.lib.ServiceParameterCreateBinary.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.ServiceParameterCreateBinary( aName ))
        

class ParameterRelated( Parameter ):
    
    def __init__( self, aName, aProperty ):        
        Parameter.__init__( self, aName, 'Related' )
        self.lib.ServiceParameterCreateRelated.restype = ctypes.c_void_p
        self.handle = ctypes.c_void_p( self.lib.ServiceParameterCreateRelated( aName, aProperty.handle ))

#
# ==== Arguments ====
#

class Argument:
    __metaclass__ = abc.ABCMeta
    
    @abc.abstractmethod
    def __init__( self ):
        self.lib = PyOhNet.lib
        self.handle = None


class ArgumentInt( Argument ):
    
    def __init__( self, aParameter, aValue=None ):
        Argument.__init__( self )
        if aValue:
            self.lib.ActionArgumentCreateIntInput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateIntInput( aParameter.handle, aValue ))
        else:
            self.lib.ActionArgumentCreateIntOutput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateIntOutput( aParameter.handle ))

    def Value( self ):
        return self.lib.ActionArgumentValueInt( self.handle )


class ArgumentUint( Argument ):
    
    def __init__( self, aParameter, aValue=None ):
        Argument.__init__( self )
        if aValue:
            self.lib.ActionArgumentCreateUintInput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateUintInput( aParameter.handle, aValue ))
        else:
            self.lib.ActionArgumentCreateUintOutput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateUintOutput( aParameter.handle ))

    def Value( self ):
        return self.lib.ActionArgumentValueUint( self.handle )


class ArgumentBool( Argument ):
    
    def __init__( self, aParameter, aValue=None ):
        Argument.__init__( self )
        if aValue:
            if not aValue:
                val = 0
            else:
                val = 1
            self.lib.ActionArgumentCreateBoolInput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateBoolInput( aParameter.handle, val ))
        else:
            self.lib.ActionArgumentCreateBoolOutput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateBoolOutput( aParameter.handle ))

    def Value( self ):
        val = self.lib.ActionArgumentValueBool( self.handle )
        return val!=0


class ArgumentString( Argument ):
    
    def __init__( self, aParameter, aValue=None ):
        Argument.__init__( self )
        if aValue:
            val = ctypes.c_char_p( aValue )
            self.lib.ActionArgumentCreateStringInput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateStringInput( aParameter.handle, val ))
        else:
            self.lib.ActionArgumentCreateStringOutput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateStringOutput( aParameter.handle ))

    def Value( self ):
        strn = ctypes.c_char_p()
        length = ctypes.c_int()
        self.lib.ActionArgumentGetValueString( self.handle, ctypes.byref( strn ), ctypes.byref( length ))
        return strn.value


class ArgumentBinary( Argument ):
    
    def __init__( self, aParameter, aValue=None ):
        Argument.__init__( self )
        if aValue:
            val = aValue
            length = len( val )
            self.lib.ActionArgumentCreateBinaryInput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateBinaryInput( aParameter.handle, val, length ))
        else:
            self.lib.ActionArgumentCreateBinaryOutput.restype = ctypes.c_void_p
            self.handle = ctypes.c_void_p( self.lib.ActionArgumentCreateBinaryOutput( aParameter.handle ))

    def Value( self ):
        strn = ctypes.c_char_p()
        length = ctypes.c_int()
        self.lib.ActionArgumentGetValueString( self.handle, ctypes.byref( strn ), ctypes.byref( length ))
        return strn.value
