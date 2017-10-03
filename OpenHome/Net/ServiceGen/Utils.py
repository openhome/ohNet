import types


class TypeLookup:

    def __init__(self):
        self.table = {
            'ui1':        ['Uint',   'TUint', 'TUint',      'TUint'],
            'ui2':        ['Uint',   'TUint', 'TUint',      'TUint'],
            'ui4':        ['Uint',   'TUint', 'TUint',      'TUint'],
            'boolean':    ['Bool',   'TBool', 'TBool',      'TBool'],
            'i1':         ['Int',    'TInt',  'TInt',       'TInt'],
            'i2':         ['Int',    'TInt',  'TInt',       'TInt'],
            'i4':         ['Int',    'TInt',  'TInt',       'TInt'],
            'string':     ['String', 'Brhz',  'const Brx&', 'Brh'],
            'bin.base64': ['Binary', 'Brh',   'const Brx&', 'Brh'],
            'uri':        ['String', 'Brhz',  'const Brx&', 'Brh']
        }

    def Raw(self, entry):
        return self._Get(entry, 0)

    def InArg(self, entry):
        return self._Get(entry, 1)

    def InArgParam(self, entry):
        return self._Get(entry, 2)

    def Param(self, entry):
        return 'Parameter' + self._Get(entry, 0)

    def Property(self, entry):
        return 'Property' + self._Get(entry, 0)

    def PropertySetter(self, entry):
        return 'SetProperty' + self._Get(entry, 0)

    def InvRead(self, entry):
        return 'InvocationRead' + self._Get(entry, 0)

    def InvResp(self, entry):
        return 'DviInvocationResponse' + self._Get(entry, 0)

    def OutArg(self, entry):
        return self._Get(entry, 3) + '&'

    def OutArgProperty(self, entry):
        return self._Get(entry, 1) + '&'

    def OutArgAction(self, entry):
        return 'IDvInvocationResponse' + self._Get(entry, 0) + '&'

    def _Get(self, entry, column):
        result = None
        if entry in self.table:
            result = self.table[entry][column]
        return result


def GetFilename(prefix, domain, type, version, suffix):
    """Create filename from service info"""
    name = prefix
    substrs = domain.split('.')
    for substr in substrs:
        name += substr[0].upper() + substr[1:]
    name += type
    name += str( version )
    name += '.' + suffix
    return name


def GetActions(desc):
    """Extrace actions list from service JSON"""
    if isinstance(desc['actionList']['action'], types.ListType):
        actions  = desc['actionList']['action']
    else:
        actions = [desc['actionList']['action']]
    return actions


def GetStateVars(desc):
    """Extrace state variable list from service JSON"""
    if isinstance(desc['serviceStateTable']['stateVariable'], types.ListType):
        stateVars  = desc['serviceStateTable']['stateVariable']
    else:
        stateVars = [desc['serviceStateTable']['stateVariable']]
    return stateVars


def GetActionArgs(action, svs):
    """Action arguments can be 'not-present', single entry or a list of entries.
       This method sorts this out and returns args as a list of dicts for all cases"""

    args = []
    if 'argumentList' in action:
        if isinstance(action['argumentList']['argument'], types.ListType):    # list if >1 arg
            for arg in action['argumentList']['argument']:
                rsv = arg['relatedStateVariable']
                name = arg['name']
                direction = arg['direction']
                args.append({'name': name, 'direction': direction, 'relatedStateVariable': rsv})
        else:   # 1 arg - not in a list .....
            rsv = action['argumentList']['argument']['relatedStateVariable']
            name = action['argumentList']['argument']['name']
            direction = action['argumentList']['argument']['direction']
            args.append({'name': name, 'direction': direction, 'relatedStateVariable': rsv})

        for arg in args:
            for sv in svs:
                if sv['name'] == arg['relatedStateVariable']:
                    arg['type'] = sv['dataType']
                    arg['evented'] = sv['@sendEvents']
        return args


def GetAllowedValueList(stateVar):
    avlist = []
    if 'allowedValueList' in stateVar:
        if isinstance(stateVar['allowedValueList']['allowedValue'], types.ListType):    # list if >1 allowed value
            for item in stateVar['allowedValueList']['allowedValue']:
                avlist.append( item )
        else:
            avlist = [stateVar['allowedValueList']['allowedValue']]
    return avlist


def GetRelated(svName, stateVars):
    rsv = None
    for sv in stateVars:
        if sv['name'] == svName:
            rsv = sv
            break
    return rsv


def GetParameterAllowedValues(stateVar):
    param = ''
    av = GetAllowedValueList(stateVar)
    if len(av):
        param = ', allowedValues, {0}'.format(len(av))
    elif 'allowedValueRange' in stateVar:
        if 'minimum' in stateVar['allowedValueRange']:
            param += ', {0}'.format(stateVar['allowedValueRange']['minimum'])
        if 'maximum' in stateVar['allowedValueRange']:
            param += ', {0}'.format(stateVar['allowedValueRange']['maximum'])
        if 'step' in stateVar['allowedValueRange']:
            param += ', {0}'.format((2 ** 31) - 1)
            param += ', {0}'.format(stateVar['allowedValueRange']['step'])
    return param
