"""CpUpnpCppBufferSource.py - service proxy template (using 'buffers' string class)"""
import Utils


def Generate(desc, sDomain, sType, sVersion):
    # import json
    # print json.dumps(desc, indent=4)

    lookup     = Utils.TypeLookup()
    filename   = Utils.GetFilename('Cp', sDomain, sType, sVersion, 'cpp')
    classname  = 'CpProxy' + filename[2:].split('.')[0]
    actions    = Utils.GetActions(desc)
    stateVars  = Utils.GetStateVars(desc)
    syncSuffix = filename[2:].split('.')[0]
    syncstr    = {}
    beginstr   = {}
    endstr     = {}

    actionArgs = {}
    for action in actions:
        actionArgs[action['name']] = Utils.GetActionArgs(action, stateVars)

    for action in actions:
        args = Utils.GetActionArgs(action, stateVars)
        syncstr[action['name']] = ''
        beginstr[action['name']] = ''
        endstr[action['name']] = ''
        if args:
            for arg in args:
                if arg['direction'] == 'in':
                    beginstr[action['name']] += '{0} a{1}, '.format(lookup.InArgParam(arg['type']), arg['name'])
                elif arg['direction'] == 'out':
                    syncstr[action['name']] += ', {0} a{1}'.format(lookup.OutArg(arg['type']), arg['name'])
                    endstr[action['name']] += ', {0} a{1}'.format(lookup.OutArg(arg['type']), arg['name'])

    lines = [
        '#include "{0}.h"'.format(filename.split('.')[0]),
        '#include <OpenHome/Net/Core/CpProxy.h>',
        '#include <OpenHome/Net/Private/CpiService.h>',
        '#include <OpenHome/Private/Thread.h>',
        '#include <OpenHome/Net/Private/AsyncPrivate.h>',
        '#include <OpenHome/Net/Core/CpDevice.h>',
        '#include <OpenHome/Net/Private/Error.h>',
        '#include <OpenHome/Net/Private/CpiDevice.h>',
        '',
        'namespace OpenHome {',
        'namespace Net {',
        ''
    ]

    for action in actions:
        lines.extend([
            'class Sync{0}{1} : public SyncProxyAction'.format(action['name'], syncSuffix),
            '{',
            'public:',
            '    Sync{0}{1}({2}& aProxy{3});'.format(action['name'], syncSuffix, classname, syncstr[action['name']]),
            '    virtual void CompleteRequest(IAsync& aAsync);',
            'private:',
            '    {0}& iService;'.format(classname)
        ])
        if actionArgs[action['name']]:
            for arg in actionArgs[action['name']]:
                if arg['direction'] == 'out':
                    lines.extend([
                        '    {0} i{1};'.format(lookup.OutArg(arg['type']), arg['name'])
                    ])
        lines.extend([
            '};',
            ''
        ])

    lines.extend([
        '} // namespace Net',
        '} // namespace OpenHome',
        '',
        '',
        'using namespace OpenHome;',
        'using namespace OpenHome::Net;',
        ''
    ])

    for action in actions:
        argstr = ''
        lines.extend([
            '',
            '// Sync{0}{1}'.format(action['name'], syncSuffix),
            '',
            'Sync{0}{1}::Sync{0}{1}({2}& aProxy{3})'.format(action['name'], syncSuffix, classname, syncstr[action['name']]),
            '    : iService(aProxy)'
        ])
        if actionArgs[action['name']]:
            for arg in actionArgs[action['name']]:
                if arg['direction'] == 'out':
                    argstr += ', i{0}'.format(arg['name'])
                    lines.extend([
                        '    , i{0}(a{0})'.format(arg['name'])
                    ])
        lines.extend([
            '{',
            '}',
            '',
            'void Sync{0}{1}::CompleteRequest(IAsync& aAsync)'.format(action['name'], syncSuffix),
            '{',
            '    iService.End{0}(aAsync{1});'.format(action['name'], argstr),
            '}'
        ])

    dom = sDomain.replace('.', '-')
    if dom == 'upnp-org':
        dom = 'schemas-upnp-org'
    lines.extend([
        '',
        '',
        '// {0}'.format(classname),
        '',
        '{0}::{0}(CpDevice& aDevice)'.format(classname),
        '    : iCpProxy("{0}", "{1}", {2}, aDevice.Device())'.format( dom, sType, sVersion),
        '{'
    ])
    if len(actions):
        lines.extend([
            '    OpenHome::Net::Parameter* param;'
        ])

        gotallowedvalues = False
        for action in actions:
            args = actionArgs[action['name']]
            if args:
                for arg in args:
                    related = Utils.GetRelated(arg['relatedStateVariable'], stateVars)
                    if 'allowedValueList' in related:
                        gotallowedvalues = True
                        break
        if gotallowedvalues:
            lines.extend([
                '    TChar** allowedValues;',
                '    TUint index;'
            ])

    for action in actions:
        lines.extend([
            '',
            '    iAction{0} = new Action("{0}");'.format(action['name'])
        ])
        args = actionArgs[action['name']]
        if args:
            for arg in args:
                related = Utils.GetRelated(arg['relatedStateVariable'], stateVars)
                avlist = Utils.GetAllowedValueList(related)
                avparam = ''
                if arg['direction'] == 'in':
                    direction = 'Input'
                elif arg['direction'] == 'out':
                    direction = 'Output'

                if 'allowedValueRange' in related:
                    rng = related['allowedValueRange']
                    if 'minimum' in rng:
                        avparam += ', {0}, '.format(rng['minimum'])
                        if 'maximum' in rng:
                            avparam += rng['maximum']
                        else:
                            avparam += '2147483647'
                        if 'step' in rng:
                            avparam += ', {0}'.format(rng['step'])

                if len(avlist) > 0:
                    avparam = ', allowedValues, {0}'.format(len(avlist))
                    lines.extend([
                        '    index = 0;',
                        '    allowedValues = new TChar*[{0}];'.format(len(avlist))
                    ])
                    for av in avlist:
                        lines.extend([
                            '    allowedValues[index++] = (TChar*)"{0}";'.format(av)
                        ])
                lines.extend([
                    '    param = new OpenHome::Net::{0}("{1}"{2});'.format(lookup.Param(arg['type']), arg['name'], avparam),
                    '    iAction{0}->Add{1}Parameter(param);'.format(action['name'], direction)
                ])
                if len(avlist) > 0:
                    lines.extend([
                        '    delete[] allowedValues;'
                    ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '',
                '    Functor functor;'
            ])
            break
    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    functor = MakeFunctor(*this, &{0}::{1}PropertyChanged);'.format(classname, sv['name']),
                '    i{0} = new {1}("{0}", functor);'.format(sv['name'], lookup.Property(sv['dataType'])),
                '    AddProperty(i{0});'.format(sv['name'])
            ])

    lines.extend([
        '}',
        '',
        '{0}::~{0}()'.format(classname),
        '{',
        '    DestroyService();'
    ])
    for action in actions:
        lines.extend([
            '    delete iAction{0};'.format(action['name'])
        ])
    lines.extend([
        '}'
    ])

    for action in actions:
        args = actionArgs[action['name']]
        incount = 0
        outcount = 0
        begin1 = ''
        begin2 = ''
        sync1 = ''
        sync2 = ''
        end1 = ''
        if args:
            for arg in args:
                if arg['direction'] == 'in':
                    incount += 1
                    begin1 += '{0} a{1}, '.format(lookup.InArgParam(arg['type']), arg['name'])
                    begin2 += 'a{0}, '.format(arg['name'])
                    sync1 += ', {0} a{1}'.format(lookup.InArgParam(arg['type']), arg['name'])
                else:
                    outcount += 1
                    sync1 += ', {0} a{1}'.format(lookup.OutArg(arg['type']), arg['name'])
                    sync2 += ', a{0}'.format(arg['name'])
                    end1 += ', {0} a{1}'.format(lookup.OutArg(arg['type']), arg['name'])
            sync1 = sync1.strip(', ')

        lines.extend([
            '',
            'void {0}::Sync{1}({2})'.format(classname, action['name'], sync1),
            '{',
            '    Sync{0}{1} sync(*this{2});'.format(action['name'], syncSuffix, sync2),
            '    Begin{0}({1}sync.Functor());'.format(action['name'], begin2),
            '    sync.Wait();',
            '}',
            '',
            'void {0}::Begin{1}({2}FunctorAsync& aFunctor)'.format(classname, action['name'], begin1),
            '{',
            '    Invocation* invocation = iCpProxy.GetService().Invocation(*iAction{0}, aFunctor);'.format(action['name'])
        ])

        if incount:
            lines.extend([
                '    TUint inIndex = 0;',
                '    const Action::VectorParameters& inParams = iAction{0}->InputParameters();'.format(action['name'])
            ])
            for arg in args:
                if arg['direction'] == 'in':
                    lines.extend([
                        '    invocation->AddInput(new Argument{0}(*inParams[inIndex++], a{1}));'.format(lookup.Raw(arg['type']), arg['name'])
                    ])

        if outcount:
            lines.extend([
                '    TUint outIndex = 0;',
                '    const Action::VectorParameters& outParams = iAction{0}->OutputParameters();'.format(action['name'])
            ])
            for arg in args:
                if arg['direction'] == 'out':
                    lines.extend([
                        '    invocation->AddOutput(new Argument{0}(*outParams[outIndex++]));'.format(lookup.Raw(arg['type']))
                    ])

        lines.extend([
            '    iCpProxy.GetInvocable().InvokeAction(*invocation);',
            '}',
            '',
            'void {0}::End{1}(IAsync& aAsync{2})'.format(classname, action['name'], end1),
            '{',
            '    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);',
            '    Invocation& invocation = (Invocation&)aAsync;',
            '    ASSERT(invocation.Action().Name() == Brn("{0}"));'.format(action['name']),
            '',
            '    Error::ELevel level;',
            '    TUint code;',
            '    const TChar* ignore;',
            '    if (invocation.Error(level, code, ignore)) {',
            '        THROW_PROXYERROR(level, code);',
            '    }'
        ])

        if outcount:
            lines.extend([
                '    TUint index = 0;'
            ])
            for arg in args:
                if arg['direction'] == 'out':
                    if arg['type'] in ['string', 'bin.base64', 'uri']:
                        lines.extend([
                            '    ((Argument{0}*)invocation.OutputArguments()[index++])->TransferTo(a{1});'.format(lookup.Raw(arg['type']), arg['name'])
                        ])
                    else:
                        lines.extend([
                            '    a{0} = ((Argument{1}*)invocation.OutputArguments()[index++])->Value();'.format(arg['name'], lookup.Raw(arg['type']))
                        ])
        lines.extend([
            '}'
        ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '',
                'void {0}::SetProperty{1}Changed(Functor& aFunctor)'.format(classname, sv['name']),
                '{',
                '    iCpProxy.GetLock().Wait();',
                '    i{0}Changed = aFunctor;'.format(sv['name']),
                '    iCpProxy.GetLock().Signal();',
                '}'
            ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '',
                'void {0}::Property{1}({2}& a{1}) const'.format(classname, sv['name'], lookup.InArg(sv['dataType'])),
                '{',
                '    AutoMutex a(iCpProxy.PropertyReadLock());',
                '    if (iCpProxy.GetSubscriptionStatus() != CpProxy::eSubscribed) {',
                '        THROW(ProxyNotSubscribed);',
                '    }'
            ])
            if sv['dataType'] in ['string', 'bin.base64', 'uri']:
                lines.extend([
                    '    a{0}.Set(i{0}->Value());'.format(sv['name']),
                    '}'
                ])
            else:
                lines.extend([
                    '    a{0} = i{0}->Value();'.format(sv['name']),
                    '}'
                ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '',
                'void {0}::{1}PropertyChanged()'.format(classname, sv['name']),
                '{',
                '    ReportEvent(i{0}Changed);'.format(sv['name']),
                '}'
            ])

    lines.extend([
        '',
        '',
        'void {0}::Subscribe()'.format(classname),
        '{',
        '  iCpProxy.Subscribe();',
        '}',
        '',
        'void {0}::Unsubscribe()'.format(classname),
        '{',
        ' iCpProxy.Unsubscribe();',
        '}',
        '',
        'void {0}::SetPropertyChanged(Functor& aFunctor)'.format(classname),
        '{',
        '  iCpProxy.SetPropertyChanged(aFunctor);',
        '}',
        '',
        'void {0}::SetPropertyInitialEvent(Functor& aFunctor)'.format(classname),
        '{',
        '  iCpProxy.SetPropertyInitialEvent(aFunctor);',
        '}'
        '',
        'void {0}::AddProperty(Property* aProperty)'.format(classname),
        '{',
        '  iCpProxy.AddProperty(aProperty);',
        '}',
        '',
        'void {0}::DestroyService()'.format(classname),
        '{',
        '  iCpProxy.DestroyService();',
        '}',
        '',
        'void {0}::ReportEvent(Functor aFunctor)'.format(classname),
        '{',
        '  iCpProxy.ReportEvent(aFunctor);',
        '}',
        '',
        'TUint {0}::Version() const'.format(classname),
        '{',
        '  return iCpProxy.Version();',
        '}',
        '',
        ''
    ])

    return filename, lines
