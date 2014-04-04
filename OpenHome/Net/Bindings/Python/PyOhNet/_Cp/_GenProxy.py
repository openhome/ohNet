"""GenProxy - generate python-ohNet proxy from supplied service xml"""

import re
import xml.etree.ElementTree as ET

kArgType = {
             'ui1':         'Uint',
             'ui2':         'Uint',
             'ui4':         'Uint',
             'i1':          'Int',
             'i2':          'Int',
             'i4':          'Int',
             'int':         'Int',
             'time':        'Int',
             'time.tz':     'Int',
#             'r4':          'Float', 
#             'r8':          'Float', 
#             'float':       'Float', 
#             'number':      'Float', 
#             'fixed.14.4':  'Float', 
             'boolean':     'Bool',
             'char':        'String',
             'string':      'String',
             'uri':         'String',
             'uuid':        'String',
#             'date':        'DateTime', 
#             'dateTime':    'DateTime', 
#             'dateTime.tz': 'DateTime', 
             'bin.base64':  'Binary',
             'bin.hex':     'Binary'
           }


class GenProxy:
    
    def __init__( self, aType, aXml ):
        "Create python proxy service code for ohNet"
        m = re.match('urn:([\w\-\.]+):service:([\w\-\.]+):(\d+)', aType )
        domain, service, version = m.groups()
        actions, properties, svs = self._ParseXml( aXml )
        self.proxy = self._BuildProxy( service, domain, int( version ), actions, properties, svs )
            
    #        
    # ==== Internal methods ====
    #
           
    def _ParseXml( self, aXml ):
        "Extract service info form XML into Python friendly dicts/lists"
        svs        = []
        actions    = []
        properties = []
        xml        = re.sub( ' xmlns="[^"]+"', '', aXml )   # remove namespace
        scpd       = ET.fromstring( xml )
        
        serviceStateTable = scpd.find( 'serviceStateTable' )
        stateVariables = serviceStateTable.findall( 'stateVariable' )
        for stateVariable in stateVariables:
            allowed = []
            min     = None
            max     = None
            step    = None
            name    = stateVariable.find( 'name' ).text
            type    = stateVariable.find( 'dataType' ).text
            
            avList = stateVariable.find( 'allowedValueList' )           
            if avList is not None:
                values = avList.findall( 'allowedValue' )
                for value in values:
                    allowed.append( value.text )
                    
            avRange = stateVariable.find( 'allowedValueRange' )           
            if avRange is not None:
                min = avRange.find( 'minimum' ).text
                max = avRange.find( 'maximum' ).text
                stp = avRange.find( 'step' )
                if stp is not None:
                    step = stp.text
            
            if name is not None and type is not None:
                sv = {'name':name, 'type':type}
                if len( allowed ):
                    sv['allowed'] = allowed
                if min is not None: 
                    sv['min'] = min
                if max is not None: 
                    sv['max'] = max
                if step is not None: 
                    sv['step'] = step
                svs.append( sv )
                if stateVariable.attrib.has_key( 'sendEvents' ):
                    if stateVariable.attrib['sendEvents'].lower() == 'yes':
                        properties.append( sv )
                if stateVariable.find( 'sendEventsAttribute' ) is not None:
                    if stateVariable.find( 'sendEventsAttribute' ).text.lower() == 'yes':
                        properties.append( sv )

        actionList = scpd.find( 'actionList' )
        xactions = actionList.findall( 'action' )
        for action in xactions:
            args = []
            name = action.find( 'name' ).text
            if name is not None:
                argumentList = action.find( 'argumentList' )
                if argumentList is not None:
                    arguments = argumentList.findall( 'argument' )
                    for argument in arguments:
                        argName   = argument.find( 'name' ).text
                        direction = argument.find( 'direction' ).text
                        sv        = argument.find( 'relatedStateVariable' ).text
                        args.append( {'name':argName, 'direction':direction, 'sv':sv} )
            actions.append( {'name':name, 'args':args} )
        
        return (actions, properties, svs)
    
    def _BuildProxy( self, aService, aDomain, aVersion, aActions, aProperties, aSvs ):
        "Construct the proxy python code"
        code =  self._BuildHeader( aService, aDomain, aVersion )
        code += self._BuildInit( aService, aDomain, aVersion, aActions, aProperties, aSvs )
        code += self._BuildControl( aActions, aSvs )
        code += self._BuildEventing( aProperties )
        return code 
                                
    def _BuildHeader( self, aService, aDomain, aVersion ):
        "Build the proxy code header block"
        domain = ''
        fields = aDomain.replace( '.', '-' ).split( '-' )
        for field in fields:
            domain += field[0].upper()
            domain += field[1:]
        
        msg  = '"Proxy for %s:%s:%d service"\n\n' % (domain, aService, aVersion) 
        msg += 'import PyOhNet\n'
        msg += 'import PyOhNet._Cp._Control  as Control\n'
        msg += 'import PyOhNet._Cp._Eventing as Eventing\n'
        msg += 'import PyOhNet._Cp._Proxy    as Proxy\n'
        msg += 'import ctypes\n'
        msg += 'import sys\n'
        msg += 'import threading\n\n\n'
        msg += 'class CpProxy%s%s%d( Proxy.Proxy ):\n\n' % (domain, aService, aVersion)
        return msg
    
    def _BuildInit( self, aService, aDomain, aVersion, aActions, aProperties, aSvs ):
        "Build the proxy code __init__ constructor block"
        msg  = '    def __init__( self, aDev ):\n'
        msg += "        Proxy.Proxy.__init__( self, '%s', '%s', 1, aDev )\n" % (aDomain, aService)
        
        for property in aProperties:
            msg += '        self._property%sCb = None\n' % property['name']
            
        msg += '\n'
        msg += '        #\n'
        msg += '        # ==== Define actions ====\n'
        msg += '        #\n'
                
        for action in aActions:
            msg += "\n        self.action%s = Control.Action( '%s' )\n" % (action['name'], action['name']) 
            for arg in action['args']:
                allowed = None
                min     = None
                max     = None
                step    = None
                for sv in aSvs:
                    if sv['name'] == arg['sv']:
                        type = kArgType[sv['type']]
                        if sv.has_key( 'allowed' ):
                            allowed = sv['allowed']
                        if sv.has_key( 'min' ):
                            min = sv['min']
                        if sv.has_key( 'max' ):
                            max = sv['max']
                        if sv.has_key( 'step' ):
                            step = sv['step']
                        break
                msg += "        self.action%s.Add%sputParameter( Control.Parameter%s( '%s'" % \
                    (action['name'], arg['direction'].title(), type, arg['name'])
                if allowed is not None:
                    msg += ', %s' % allowed
                if min is not None and max is not None:
                    msg += ', %s, %s' % (min, max)
                    if step is not None:
                        msg += ', %s' % step
                msg += ' ))\n'
            msg += '        self.actions.append( self.action%s )\n' % action['name']
            
        msg += '\n'
        msg += '        #\n'
        msg += '        # ==== Define properties ====\n'
        msg += '        #\n\n'

        for property in aProperties:
            var = 'self.%s%s' % (property['name'][0].lower(), property['name'][1:])
            msg += "        %s = Eventing.Property%s( '%s', self._%sPropertyChanged )\n" % \
                (var, kArgType[property['type']], property['name'], property['name'])
            msg += '        self._AddProperty( %s )\n' % var
            
        domain = aDomain.title().replace( '.', '' )
        msg += '\n    def __str__( self ):\n'
        msg += "        return self._Str( 'Proxy%s%s%d' )" % (domain.replace( '-', '' ), aService, aVersion) 
        return msg

    def _BuildControl( self, aActions, aSvs ):
        "Buid the proxy code for action invocation"
        msg  = '\n\n'
        msg += '    #\n'
        msg += '    # ==== Control (action invocation) interface ====\n'
        msg += '    #\n'
        
        for action in aActions:
            inArgs     = []
            inArgStr1  = ''
            inArgStr2  = ''
            inInvokes  = ''
            outInvokes = ''
            outRes     = ''
            outResults = []
            returns    = []
            inCount    = 0
            outCount   = 0
            
            for arg in action['args']:
                for sv in aSvs:
                    if sv['name'] == arg['sv']:
                        type = kArgType[sv['type']]
                        break
                if arg['direction'] == 'in':
                    inArgs.append( arg['name'] )
                    inInvokes += '        invocation.AddInput( Control.Argument%s( self.action%s.InputParameter( %d ), a%s ))\n' % \
                        (type, action['name'], inCount, arg['name'])
                    inCount += 1
                else:
                    outInvokes += '        invocation.AddOutput( Control.Argument%s( self.action%s.OutputParameter( %d )))\n' % \
                        (type, action['name'], outCount)
                    var = '%s%s' % (arg['name'][0].lower(), arg['name'][1:])
                    outResults.append( '        %s = response.Output%s( %d )\n' % (var, type, outCount ))
                    returns.append( "'%s':%s%s" % (arg['name'],arg['name'][0].lower(), arg['name'][1:] ))
                    outCount += 1
            if inArgs != []:
                inArgStr1 = ', a' + ', a'.join( inArgs )
                inArgStr2 = 'a' + ', a'.join( inArgs ) + ', ' 
                    
            if outCount == 0:                    
                outRes = '        return\n'
            elif outCount == 1:
                outRes += outResults[0]
                outRes += '        return %s\n' % var
            else:
                for outResult in outResults:
                    outRes += outResult
                outRes += '        return( {%s} )\n' % ', '.join( returns )
            
            msg += '\n    def Sync%s( self%s ):\n' % (action['name'], inArgStr1 )
            msg += '        self.response = None\n'
            msg += '        self.Begin%s( %sself._%sActionComplete )\n' % (action['name'], inArgStr2, action['name'])
            msg += '        self.semaReady.acquire()\n'
            msg += '        return self.response\n'
            
            msg += '\n    def Begin%s( self%s, aCb ):\n' % (action['name'],  inArgStr1)
            msg += '        invocation = Control.Invocation( self.service, self.action%s, aCb )\n' % action['name']
            msg += inInvokes
            msg += outInvokes
            msg += '        self._InvokeAction( invocation )\n'
            
            msg += '\n    def End%s( self, aHandle ):\n' % action['name']
            msg += '        response = Control.InvocationResponse( aHandle )\n'
            msg += outRes
            
            msg += '\n    def _%sActionComplete( self, aHandle ):\n' % action['name']
            msg += '        self.response = self.End%s( aHandle )\n' % action['name']
            msg += '        self.semaReady.release()\n\n'        
        return msg
    
    def _BuildEventing( self, aProperties ):
        "Build the proxy code for handling eventing"
        msg  = '    #\n'
        msg += '    # ==== Properties (eventing) interface ===\n'
        msg += '    #\n'
        
        for property in aProperties:
            msg += '\n    def SetProperty%sChanged( self, aCb ):\n' % property['name']
            msg += '        self._property%sCb = aCb\n' % property['name']

        msg += '\n'            
        for property in aProperties:
            msg += '\n    def Property%s( self ):\n' % property['name']
            msg += '        return self._PropertyValue( self.%s%s )\n' % (property['name'][0].lower(), property['name'][1:])
            
        msg += '\n'
        for property in aProperties:
            msg += '\n    def _%sPropertyChanged( self, aDummy ):\n' % property['name']
            msg += '        if self._property%sCb is not None:\n' % property['name']
            msg += '            self._property%sCb()\n' % property['name']
        msg += '\n' 
        return msg
    
    def _GetText( self ):
        "Return proxy code as text"
        return self.proxy
    
    #
    # ==== Public interface ====
    #
        
    def Write( self, aFilePath ):
        "Write out proxy code to specified file"
        try:
            f = open( aFilePath, 'wt+' )
            f.write( self.proxy )
            f.close()
        except:
            print "Failed to write proxy code to <%s>" % aFilePath
            raise
        
    text = property( _GetText, None, None, 'Get Text')
