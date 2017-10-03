"""DvUpnpCppCoreSource.py - service proxy template"""
import Utils


def Generate(desc, sDomain, sType, sVersion):
    # import json
    # print json.dumps(desc, indent=4)

    lookup    = Utils.TypeLookup()
    filename  = Utils.GetFilename('Dv', sDomain, sType, sVersion, 'cpp')
    classname = 'DvProvider' + filename[2:].split('.')[0]
    actions    = Utils.GetActions(desc)
    stateVars  = Utils.GetStateVars(desc)

    actionArgs = {}
    for action in actions:
        actionArgs[action['name']] = Utils.GetActionArgs(action, stateVars)

    lines = [
        '#include "{0}"'.format(filename).replace('.cpp', '.h'),
        '#include <OpenHome/Types.h>',
        '#include <OpenHome/Net/Core/DvInvocationResponse.h>',
        '#include <OpenHome/Net/Private/Service.h>',
        '#include <OpenHome/Net/Private/FunctorDviInvocation.h>',
        '#include <OpenHome/Net/Private/DviStack.h>',
        '',
        'using namespace OpenHome;',
        'using namespace OpenHome::Net;'
    ]

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '',
                'TBool {0}::SetProperty{1}({2} aValue)'.format(classname, sv['name'], lookup.InArgParam(sv['dataType'])),
                '{',
                '    ASSERT(iProperty{0} != NULL);'.format(sv['name']),
                '    return {0}(*iProperty{1}, aValue);'.format(lookup.PropertySetter(sv['dataType']), sv['name']),
                '}',
                '',
                'void {0}::GetProperty{1}({2}& aValue)'.format(classname, sv['name'], lookup.InArg(sv['dataType'])),
                '{',
                '    ASSERT(iProperty{0} != NULL);'.format(sv['name']),
            ])
            if sv['dataType'] in ['string', 'bin.base64', 'uri']:
                lines.extend([
                    '    aValue.Set(iProperty{0}->Value());'.format(sv['name'])
                ])
            else:
                lines.extend([
                    '    aValue = iProperty{0}->Value();'.format(sv['name'])
                ])
            lines.extend([
                '}'
            ])
            if sv['dataType'] in ['string', 'bin.base64', 'uri']:
                lines.extend([
                    '',
                    'void {0}::WriteProperty{1}(IWriter& aWriter)'.format(classname, sv['name']),
                    '{',
                    '    iProperty{0}->Write(aWriter);'.format(sv['name']),
                    '}'
                ])

    lines.extend([
        '',
        '{0}::{0}(DvDevice& aDevice)'.format(classname, classname),
        '    : DvProvider(aDevice.Device(), "{0}", "{1}", {2})'.format(sDomain, sType, sVersion),
        '{',
        '    Construct();',
        '}',
        '',
        '{0}::{0}(DviDevice& aDevice)'.format(classname, classname),
        '    : DvProvider(aDevice, "{0}", "{1}", {2})'.format(sDomain, sType, sVersion),
        '{',
        '    Construct();',
        '}',
        '',
        'void {0}::Construct()'.format(classname),
        '{'
    ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    iProperty{0} = NULL;'.format(sv['name'])
            ])
    lines.extend([
        '}'
    ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '',
                'void {0}::EnableProperty{1}()'.format(classname, sv['name']),
                '{'
            ])
            avParam = ''
            avlist = Utils.GetAllowedValueList(sv)
            if len(avlist) > 0:
                avParam = ', allowedValues, {0}'.format(len(avlist))
                lines.extend([
                    '    TChar** allowedValues;',
                    '    TUint index = 0;',
                    '    allowedValues = new TChar*[{0}];'.format(len(avlist))
                ])
                for av in avlist:
                    lines.extend([
                        '    allowedValues[index++] = (TChar*)"{0}";'.format(av)
                    ])
            lines.extend([
                '    iProperty{0} = new {1}(new {2}("{3}"{4}));'.format(sv['name'], lookup.Property(sv['dataType']), lookup.Param(sv['dataType']), sv['name'], avParam ),
            ])
            if len(avlist) > 0:
                lines.extend([
                    '    delete[] allowedValues;'
                ])
            lines.extend([
                '    iService->AddProperty(iProperty{0}); // passes ownership'.format(sv['name']),
                '}'
            ])

    for action in actions:
        lines.extend([
            '',
            'void {0}::EnableAction{1}()'.format(classname, action['name']),
            '{',
            '    OpenHome::Net::Action* action = new OpenHome::Net::Action("{0}");'.format(action['name'])
        ])
        if actionArgs[action['name']] is not None:
            for arg in actionArgs[action['name']]:
                sv = Utils.GetRelated(arg['relatedStateVariable'], stateVars)
                avlist = Utils.GetAllowedValueList(sv)
                if len(avlist) and arg['evented'] == 'no':
                    lines.extend([
                        '    TChar** allowedValues;',
                        '    TUint index;'
                    ])
                    break

            for arg in actionArgs[action['name']]:
                sv = Utils.GetRelated(arg['relatedStateVariable'], stateVars)
                avlist = Utils.GetAllowedValueList(sv)

                if arg['direction'] == 'in':
                    if arg['evented'] == 'yes':
                        if len(avlist):
                            lines.extend([
                                '    index = 0;',
                                '    allowedValues = new TChar*[{0}];'.format(len(avlist))
                            ])
                        for av in avlist:
                            lines.extend([
                                '    allowedValues[index++] = (TChar*)"{0}";'.format(av)
                            ])
                        if len(avlist):
                            lines.extend([
                                '    delete[] allowedValues;'
                            ])
                        lines.extend([
                            '    action->AddInputParameter(new ParameterRelated("{0}", *iProperty{1}));'.format(arg['name'], arg['relatedStateVariable'])
                        ])
                    else:
                        if len(avlist):
                            lines.extend([
                                '    index = 0;',
                                '    allowedValues = new TChar*[{0}];'.format(len(avlist))
                            ])
                        for av in avlist:
                            lines.extend([
                                '    allowedValues[index++] = (TChar*)"{0}";'.format(av)
                            ])
                        lines.extend([
                            '    action->AddInputParameter(new {0}("{1}"{2}));'.format(lookup.Param(arg['type']), arg['name'], Utils.GetParameterAllowedValues(sv))
                        ])
                        if len(avlist):
                            lines.extend([
                                '    delete[] allowedValues;'
                            ])

                elif arg['direction'] == 'out':
                    if arg['evented'] == 'yes':
                        lines.extend([
                            '    action->AddOutputParameter(new ParameterRelated("{0}", *iProperty{1}));'.format(arg['name'], arg['relatedStateVariable'])
                        ])
                    else:
                        if len(avlist):
                            lines.extend([
                                '    index = 0;',
                                '    allowedValues = new TChar*[{0}];'.format(len(avlist))
                            ])
                        for av in avlist:
                            lines.extend([
                                '    allowedValues[index++] = (TChar*)"{0}";'.format(av)
                            ])
                        lines.extend([
                            '    action->AddOutputParameter(new {0}("{1}"{2}));'.format(lookup.Param(arg['type']), arg['name'], Utils.GetParameterAllowedValues(sv))
                        ])
                        if len(avlist):
                            lines.extend([
                                '    delete[] allowedValues;'
                            ])
        lines.extend([
            '    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &{0}::Do{1});'.format(classname, action['name']),
            '    iService->AddAction(action, functor);',
            '}'
        ])

    for action in actions:
        argnames = ''
        lines.extend([
            '',
            'void {0}::Do{1}(IDviInvocation& aInvocation)'.format(classname, action['name']),
            '{',
            '    aInvocation.InvocationReadStart();'
        ])

        if actionArgs[action['name']] is not None:
            for arg in actionArgs[action['name']]:
                if arg['direction'] == 'in':
                    argnames += ', {0}'.format(arg['name'])
                    if arg['type'] in ['string', 'bin.base64', 'uri']:
                        lines.extend([
                            '    {0} {1};'.format(lookup.InArg(arg['type']), arg['name'] ),
                            '    aInvocation.{0}("{1}", {1});'.format(lookup.InvRead(arg['type']), arg['name'])
                        ])
                    else:
                        lines.extend([
                            '    {0} {1} = aInvocation.{2}("{1}");'.format(lookup.InArg(arg['type']), arg['name'], lookup.InvRead(arg['type']))
                        ])

        lines.extend([
            '    aInvocation.InvocationReadEnd();',
            '    DviInvocation invocation(aInvocation);'
        ])

        if actionArgs[action['name']] is not None:
            for arg in actionArgs[action['name']]:
                if arg['direction'] == 'out':
                    argnames += ', resp{0}'.format(arg['name'])
                    lines.extend([
                        '    {0} resp{1}(aInvocation, "{1}");'.format(lookup.InvResp(arg['type']), arg['name'])
                    ])

        lines.extend([
            '    {0}(invocation{1});'.format(action['name'], argnames),
            '}'
        ])

    for action in actions:
        argtypenames = ''
        if actionArgs[action['name']] is not None:
            for arg in actionArgs[action['name']]:
                if arg['direction'] == 'in':
                    argtypenames += ', {0} /*a{1}*/'.format(lookup.InArgParam(arg['type']), arg['name'])
                elif arg['direction'] == 'out':
                    argtypenames += ', {0} /*a{1}*/'.format(lookup.OutArgAction(arg['type']), arg['name'])
        lines.extend([
            '',
            'void {0}::{1}(IDvInvocation& /*aResponse*/{2})'.format(classname, action['name'], argtypenames),
            '{',
            '    ASSERTS();',
            '}'
        ])

    lines.extend([
        ''
    ])

    return filename, lines
