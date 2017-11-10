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
    # 'r4':          'Float',
    # 'r8':          'Float',
    # 'float':       'Float',
    # 'number':      'Float',
    # 'fixed.14.4':  'Float',
    'boolean':     'Bool',
    'char':        'String',
    'string':      'String',
    'uri':         'String',
    'uuid':        'String',
    # 'date':        'DateTime',
    # 'dateTime':    'DateTime',
    # 'dateTime.tz': 'DateTime',
    'bin.base64':  'Binary',
    'bin.hex':     'Binary'
}


class GenProxy:

    def __init__( self, aType, aXml ):
        """Create python proxy service code for ohNet"""
        m = re.match('urn:([\w\-\.]+):service:([\w\-\.]+):(\d+)', aType )
        domain, service, version = m.groups()
        actions, properties, svs = self._ParseXml( aXml )
        self.proxy = self._BuildProxy( service, domain, int( version ), actions, properties, svs )

    #
    # ==== Internal methods ====
    #

    @staticmethod
    def _ParseXml( aXml ):
        """Extract service info from XML into Python friendly dicts/lists"""
        svs        = []
        actions    = []
        properties = []
        xml        = re.sub( ' xmlns="[^"]+"', '', aXml.decode( 'utf8' ))   # remove namespace
        scpd       = ET.fromstring( xml )

        serviceStateTable = scpd.find( 'serviceStateTable' )
        stateVariables = serviceStateTable.findall( 'stateVariable' )
        for stateVariable in stateVariables:
            allowed = []
            mini    = None
            maxi    = None
            step    = None
            name    = stateVariable.find( 'name' ).text
            dType   = stateVariable.find( 'dataType' ).text

            avList = stateVariable.find( 'allowedValueList' )
            if avList is not None:
                values = avList.findall( 'allowedValue' )
                for value in values:
                    allowed.append( value.text )

            avRange = stateVariable.find( 'allowedValueRange' )
            if avRange is not None:
                mini = avRange.find( 'minimum' ).text
                maxi = avRange.find( 'maximum' ).text
                stp = avRange.find( 'step' )
                if stp is not None:
                    step = stp.text

            if name is not None and dType is not None:
                sv = {'name': name, 'type': dType}
                if len( allowed ):
                    sv['allowed'] = allowed
                if mini is not None:
                    sv['min'] = mini
                if maxi is not None:
                    sv['max'] = maxi
                if step is not None:
                    sv['step'] = step
                svs.append( sv )
                if 'sendEvents' in stateVariable.attrib:
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
                        args.append( {'name': argName, 'direction': direction, 'sv': sv} )
            actions.append( {'name': name, 'args': args} )

        return actions, properties, svs

    def _BuildProxy( self, aService, aDomain, aVersion, aActions, aProperties, aSvs ):
        """Construct the proxy python code"""
        code  = self._BuildHeader( aService, aDomain, aVersion )
        code += self._BuildInit( aService, aDomain, aVersion, aActions, aProperties, aSvs )
        code += self._BuildControl( aActions, aSvs )
        code += self._BuildEventing( aProperties )
        return code

    @staticmethod
    def _BuildHeader( aService, aDomain, aVersion ):
        """Build the proxy code header block"""
        domain = ''
        fields = aDomain.replace( '.', '-' ).split( '-' )
        for field in fields:
            domain += field[0].upper()
            domain += field[1:]

        msg  = '"Proxy for %s:%s:%d service"\n\n' % (domain, aService, aVersion)
        msg += 'import PyOhNet._Cp._Control as Control\n'
        msg += 'import PyOhNet._Cp._Eventing as Eventing\n'
        msg += 'import PyOhNet._Cp._Proxy as Proxy\n\n\n'
        msg += 'class CpProxy%s%s%d( Proxy.Proxy ):\n\n' % (domain, aService, aVersion)
        return msg

    @staticmethod
    def _BuildInit( aService, aDomain, aVersion, aActions, aProperties, aSvs ):
        """Build the proxy code __init__ constructor block"""
        msg  = '    def __init__( self, aDev ):\n'
        msg += "        Proxy.Proxy.__init__( self, '%s', '%s', 1, aDev )\n" % (aDomain, aService)

        for prop in aProperties:
            msg += '        self._property%sCb = None\n' % prop['name']

        msg += '\n'
        msg += '        #\n'
        msg += '        # ==== Define actions ====\n'
        msg += '        #\n'

        for action in aActions:
            msg += "\n        self.action%s = Control.Action( '%s' )\n" % (action['name'], action['name'])
            for arg in action['args']:
                allowed = None
                mini    = None
                maxi    = None
                step    = None
                argType = None
                for sv in aSvs:
                    if sv['name'] == arg['sv']:
                        argType = kArgType[sv['type']]
                        if 'allowed' in sv:
                            allowed = sv['allowed']
                        if 'min' in sv:
                            mini = sv['min']
                        if 'max' in sv:
                            maxi = sv['max']
                        if 'step' in sv:
                            step = sv['step']
                        break
                msg += "        self.action%s.Add%sputParameter( Control.Parameter%s( '%s'" % \
                    (action['name'], arg['direction'].title(), argType, arg['name'])
                if allowed is not None:
                    msg += ', %s' % allowed
                if mini is not None and maxi is not None:
                    msg += ', %s, %s' % (mini, maxi)
                    if step is not None:
                        msg += ', %s' % step
                msg += ' ))\n'
            msg += '        self.actions.append( self.action%s )\n' % action['name']

        msg += '\n'
        msg += '        #\n'
        msg += '        # ==== Define properties ====\n'
        msg += '        #\n\n'

        for prop in aProperties:
            var = 'self.%s%s' % (prop['name'][0].lower(), prop['name'][1:])
            msg += "        %s = Eventing.Property%s( '%s', self._%sPropertyChanged )\n" % \
                (var, kArgType[prop['type']], prop['name'], prop['name'])
            msg += '        self._AddProperty( %s )\n' % var

        domain = aDomain.title().replace( '.', '' )
        msg += '\n    def __str__( self ):\n'
        msg += "        return self._Str( 'Proxy%s%s%d' )" % (domain.replace( '-', '' ), aService, aVersion)
        return msg

    @staticmethod
    def _BuildControl( aActions, aSvs ):
        """Buid the proxy code for action invocation"""
        msg  = '\n\n'
        msg += '    #\n'
        msg += '    # ==== Control (action invocation) interface ====\n'
        msg += '    #\n\n'

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
            var        = ''

            for arg in action['args']:
                for sv in aSvs:
                    if sv['name'] == arg['sv']:
                        argType = kArgType[sv['type']]
                        break
                if arg['direction'] == 'in':
                    inArgs.append( arg['name'] )
                    inInvokes += '        invocation.AddInput( Control.Argument%s( self.action%s.InputParameter( %d ), a%s ))\n' % \
                        (argType, action['name'], inCount, arg['name'])
                    inCount += 1
                else:
                    outInvokes += '        invocation.AddOutput( Control.Argument%s( self.action%s.OutputParameter( %d )))\n' % \
                        (argType, action['name'], outCount)
                    var = '%s%s' % (arg['name'][0].lower(), arg['name'][1:])
                    outResults.append( '        %s = response.Output%s( %d )\n' % (var, argType, outCount ))
                    returns.append( "'%s': %s%s" % (arg['name'], arg['name'][0].lower(), arg['name'][1:] ))
                    outCount += 1
            if inArgs:
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

            msg += '    # ---- %s action ----\n' % action['name']
            msg += '\n    def Sync%s( self%s ):\n' % (action['name'], inArgStr1 )
            msg += '        self.response = None\n'
            msg += '        self.Begin%s( %sself._%sActionComplete )\n' % (action['name'], inArgStr2, action['name'])
            msg += '        self.semaReady.acquire()    # wait for response\n'
            msg += '        return self.response\n'

            msg += '\n    def Begin%s( self%s, aCb ):\n' % (action['name'],  inArgStr1)
            msg += '        invocation = Control.Invocation( self.service, self.action%s, aCb )\n' % action['name']
            msg += inInvokes
            msg += outInvokes
            msg += '        self._InvokeAction( invocation )\n'

            msg += '\n    def End%s( self, aHandle ):\n' % action['name']
            msg += '        response = Control.InvocationResponse( aHandle )\n'
            msg += '        err = response.Error()\n'
            msg += "        if err['err'] is not False:\n"
            msg += "            return( 'Proxy error - %d: %s' % (err['code'], err['desc']) )\n"
            msg += outRes

            msg += '\n    def _%sActionComplete( self, aHandle ):\n' % action['name']
            msg += '        self.response = self.End%s( aHandle )\n' % action['name']
            msg += '        self.semaReady.release()    # signal response available\n\n'
        return msg

    @staticmethod
    def _BuildEventing( aProperties ):
        """Build the proxy code for handling eventing"""
        msg  = '    #\n'
        msg += '    # ==== Properties (eventing) interface ===\n'
        msg += '    #\n'

        msg += '\n    # ---- Property Setters ----\n'
        for prop in aProperties:
            msg += '\n    def SetProperty%sChanged( self, aCb ):\n' % prop['name']
            msg += '        self._property%sCb = aCb\n' % prop['name']

        msg += '\n    # ---- Property Getters ----\n'
        for prop in aProperties:
            msg += '\n    def Property%s( self ):\n' % prop['name']
            msg += '        return self._PropertyValue( self.%s%s )\n' % (prop['name'][0].lower(), prop['name'][1:])

        msg += '\n    # ---- Property Changed callbacks ----\n'
        for prop in aProperties:
            msg += '\n    def _%sPropertyChanged( self, aDummy ):\n' % prop['name']
            msg += '        if self._property%sCb is not None:\n' % prop['name']
            msg += '            self._property%sCb()\n' % prop['name']
        msg += '\n'
        return msg

    def _GetText( self ):
        """Return proxy code as text"""
        return self.proxy

    #
    # ==== Public interface ====
    #

    def Write( self, aFilePath ):
        """Write out proxy code to specified file"""
        try:
            f = open( aFilePath, 'wt+' )
            f.write( self.proxy )
            f.close()
        except:
            print( "Failed to write proxy code to <%s>" % aFilePath )
            raise

    text = property( _GetText, None, None, 'Get Text')
