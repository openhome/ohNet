"""CpControl - python ohNet bindings to support Control of devices by CPs"""

import PyOhNet
import abc
import ctypes

kMaxInt32 = 2147483647
kMinInt32 = -2147483648
kMaxUint  = 4294967295


class Action:
    "Define the controllable ACTION"
    
    def __init__( self, aName ):
        self.lib = PyOhNet.lib
        self.handle = self.lib.ServiceActionCreate( aName )
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
        str = ctypes.c_char_p()
        length = ctypes.c_int()
        self.lib.ServiceActionGetName( self.handle, ctypes.byref( str ), ctypes.byref( length ))
        return str.value

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

class Invocation:
    "Define and setup the invocation - called back on action completion/errors"
    
    def __init__( self, aService, aAction, aCb ):
        self.lib = PyOhNet.lib
        self.callersCb = aCb
        CB = PyOhNet.makeCb( None, ctypes.c_void_p, ctypes.c_void_p )
        self.asyncCb = CB( self.AsyncComplete )     # must stay in scope until called or ohNet crashes
        self.handle = self.lib.CpServiceInvocation( aService, aAction.handle, self.asyncCb, None )
        
    def AddInput( self, aArgument ):
        self.lib.CpInvocationAddInput( self.handle, aArgument.handle )
                
    def AddOutput( self, aArgument ):
        self.lib.CpInvocationAddOutput( self.handle, aArgument.handle )
                
    def AsyncComplete( self, aDummy, aHandle ):
        response = InvocationResponse( aHandle ) 
        err = response.Error()
        if err['err'] is not False:
            raise PyOhNet.OhNetError( 'Proxy error - %d: %s' % (err['code'],err['desc']) )
        self.callersCb( aHandle )
        
        
class InvocationResponse:
    "Extract response to an invocation on completion"
    
    def __init__( self, aHandle ):
        self.lib = PyOhNet.lib
        self.handle = aHandle
                
    def Error( self ):
        code = ctypes.c_int()
        desc = ctypes.c_char_p()
        err = self.lib.CpInvocationError( self.handle, ctypes.byref( code ), ctypes.byref( desc ))
        return( {'err':err!=0, 'code':code.value, 'desc':desc.value} )

    def OutputInt( self, aIndex ):
        return self.lib.CpInvocationOutputInt( self.handle, aIndex )
        
    def OutputUint( self, aIndex ):
        return self.lib.CpInvocationOutputUint( self.handle, aIndex )
            
    def OutputBool( self, aIndex ):
        val = self.lib.CpInvocationOutputBool( self.handle, aIndex )
        return val != 0
    
    def OutputString( self, aIndex ):
        str = ctypes.c_char_p()
        length = ctypes.c_int()
        self.lib.CpInvocationGetOutputString( self.handle, aIndex, ctypes.byref( str ), ctypes.byref( length ))
        string = str.value
        self.lib.OhNetFree( str )
        return string
    
    def OutputBinary( self, aIndex ):
        bin = []
        pData = ctypes.pointer( ctypes.pointer( ctypes.c_ubyte() ))        
        length = ctypes.c_int()
        self.lib.CpInvocationGetOutputBinary( self.handle, aIndex, pData, ctypes.byref( length ))
        data = pData.contents
        self.lib.OhNetFree( pData )
        for i in range( length.value ):
            bin.append( data[i] )
        return bin
    
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
        self.handle = self.lib.ServiceParameterCreateInt( aName, aMinValue, aMaxValue, aStep )


class ParameterUint( Parameter ):
    
    def __init__( self, aName, aMinValue=0, aMaxValue=kMaxUint, aStep=1 ):
        Parameter.__init__( self, aName, 'Uint' )
        self.handle = self.lib.ServiceParameterCreateUint( aName, aMinValue, aMaxValue, aStep )

        
class ParameterBool( Parameter ):
    
    def __init__( self, aName ):
        Parameter.__init__( self, aName, 'Bool' )
        self.handle = self.lib.ServiceParameterCreateBool( aName )


class ParameterString( Parameter ):
    
    def __init__( self, aName, aAllowedValues=[] ):
        Parameter.__init__( self, aName, 'String' )
        numAllowedValues = len( aAllowedValues )
        allowed = ((ctypes.c_char_p) * numAllowedValues)()
        for i in range( numAllowedValues ):
            allowed[i] = aAllowedValues[i] 
        self.handle = self.lib.ServiceParameterCreateString( aName, allowed, numAllowedValues )
        

class ParameterBinary( Parameter ):
    
    def __init__( self, aName ):        
        Parameter.__init__( self, aName, 'Binary' )
        self.handle = self.lib.ServiceParameterCreateBinary( aName )        
        

class ParameterRelated( Parameter ):
    
    def __init__( self, aName, aProperty ):        
        Parameter.__init__( self, aName, 'Related' )
        self.handle = self.lib.ServiceParameterCreateRelated( aName, aProperty.handle )

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
            self.handle = self.lib.ActionArgumentCreateIntInput( aParameter.handle, aValue )
        else:
            self.handle = self.lib.ActionArgumentCreateIntOutput( aParameter.handle )
        
    def Value( self ):
        return self.lib.ActionArgumentValueInt( self.handle )


class ArgumentUint( Argument ):
    
    def __init__( self, aParameter, aValue=None ):
        Argument.__init__( self )
        if aValue:
            self.handle = self.lib.ActionArgumentCreateUintInput( aParameter.handle, aValue )
        else:
            self.handle = self.lib.ActionArgumentCreateUintOutput( aParameter.handle )
        
    def Value( self ):
        return self.lib.ActionArgumentValueUint( self.handle )


class ArgumentBool( Argument ):
    
    def __init__( self, aParameter, aValue=None ):
        Argument.__init__( self )
        if aValue:
            if aValue==False:
                val = 0
            else:
                val = 1
            self.handle = self.lib.ActionArgumentCreateBoolInput( aParameter.handle, val )
        else:
            self.handle = self.lib.ActionArgumentCreateBoolOutput( aParameter.handle )
        
    def Value( self ):
        val = self.lib.ActionArgumentValueBool( self.handle )
        return val!=0


class ArgumentString( Argument ):
    
    def __init__( self, aParameter, aValue=None ):
        Argument.__init__( self )
        if aValue:
            val = ctypes.c_char_p( aValue )
            self.handle = self.lib.ActionArgumentCreateStringInput( aParameter.handle, val )
        else:
            self.handle = self.lib.ActionArgumentCreateStringOutput( aParameter.handle )
        
    def Value( self ):
        str = ctypes.c_char_p()
        length = ctypes.c_int()
        val = self.lib.ActionArgumentGetValueString( self.handle, ctypes.byref( str ), ctypes.byref( length ))
        return val.value


class ArgumentBinary( Argument ):
    
    def __init__( self, aParameter, aValue=None ):
        Argument.__init__( self )
        if aValue:
            val = aValue
            length = len( val )
            self.handle = self.lib.ActionArgumentCreateBinaryInput( aParameter.handle, val, length )
        else:
            self.handle = self.lib.ActionArgumentCreateBinaryOutput( aParameter.handle )
        
    def Value( self ):
        str = ctypes.c_char_p()
        length = ctypes.c_int()
        val = self.lib.ActionArgumentGetValueString( self.handle, ctypes.byref( str ), ctypes.byref( length ))
        return val.value
