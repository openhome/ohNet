"""CpUpnpCppHeader.py - service proxy template (using 'buffers' string class)"""
import Utils


def Generate(desc, sDomain, sType, sVersion):
    # import json
    # print json.dumps(desc, indent=4)

    lookup    = Utils.TypeLookup()
    filename  = Utils.GetFilename('Cp', sDomain, sType, sVersion, 'h')
    headerdef = filename[2:].split('.')[0]
    classname = 'CpProxy' + headerdef
    actions   = Utils.GetActions(desc)
    stateVars = Utils.GetStateVars(desc)
    syncstr   = {}
    beginstr  = {}
    endstr    = {}
    devclass  = 'CpDevice'

    for action in actions:
        args = Utils.GetActionArgs(action, stateVars)
        syncstr[action['name']] = ''
        beginstr[action['name']] = ''
        endstr[action['name']] = ''
        if args:
            for arg in args:
                if arg['direction'] == 'in':
                    syncstr[action['name']] += '{0} a{1}, '.format(lookup.InArgParam(arg['type']), arg['name'])
                    beginstr[action['name']] += '{0} a{1}, '.format(lookup.InArgParam(arg['type']), arg['name'])
                elif arg['direction'] == 'out':
                    syncstr[action['name']] += '{0} a{1}, '.format(lookup.OutArg(arg['type']), arg['name'])
                    endstr[action['name']] += ', {0} a{1}'.format(lookup.OutArg(arg['type']), arg['name'])
            syncstr[action['name']] = syncstr[action['name']].strip(', ')

    lines = [
        '#ifndef HEADER_{0}'.format(headerdef.upper()),
        '#define HEADER_{0}'.format(headerdef.upper()),
        '',
        '#include <OpenHome/Types.h>',
        '#include <OpenHome/Buffer.h>',
        '#include <OpenHome/Exception.h>',
        '#include <OpenHome/Functor.h>',
        '#include <OpenHome/Net/Core/FunctorAsync.h>',
        '#include <OpenHome/Net/Core/CpProxy.h>',
        '',
        'namespace OpenHome {',
        'namespace Net {',
        ''
    ]
    lines.extend([
        'class {0};'.format(devclass),
        'class Action;',
        'class PropertyBinary;',
        'class PropertyBool;',
        'class PropertyInt;',
        'class PropertyString;',
        'class PropertyUint;',
        'class CpProxy;',
        'class I{0} : public ICpProxy'.format(classname),
        '{',
        'public:',
        '    virtual ~I{0}() {1}'.format(classname, '{}')
    ])

    for action in actions:
        lines.extend([
            '    virtual void Sync{0}({1}) = 0;'.format(action['name'], syncstr[action['name']]),
            '    virtual void Begin{0}({1}FunctorAsync& aFunctor) = 0;'.format(action['name'], beginstr[action['name']]),
            '    virtual void End{0}(IAsync& aAsync{1}) = 0;'.format(action['name'], endstr[action['name']])
        ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    virtual void SetProperty{0}Changed(Functor& a{0}Changed) = 0;'.format(sv['name']),
                '    virtual void Property{0}({1} a{0}) const = 0;'.format(sv['name'], lookup.OutArgProperty(sv['dataType']))
            ])

    lines.extend([
        '};',
        '',
        '/**',
        ' * Proxy for {0}:{1}:{2}'.format(sDomain, sType, sVersion),
        ' * @ingroup Proxies',
        ' */',
        'class {0} : public I{0}'.format(classname),
        '{',
        'public:',
        '    /**',
        '     * Constructor.',
        '     *',
        '     * Use iCpProxy::[Un]Subscribe() to enable/disable querying of state variable',
        '     * and reporting of their changes.',
        '     *',
        '     * @param[in]  aDevice   The device to use',
        '     */',
        '    {0}({1}& aDevice);'.format(classname, devclass),
        '    /**',
        '     * Destructor.',
        '     * If any asynchronous method is in progress, this will block until they complete.',
        '     * [Note that any methods still in progress are likely to complete with an error.]',
        '     * Clients who have called Subscribe() do not need to call Unsubscribe() before',
        '     * calling delete.  An unsubscribe will be triggered automatically when required.',
        '     */',
        '    ~{0}();'.format(classname)
    ])

    for action in actions:
        args = Utils.GetActionArgs(action, stateVars)
        lines.extend([
            '',
            '    /**',
            '     * Invoke the action synchronously.  Blocks until the action has been processed',
            '     * on the device and sets any output arguments.'
        ])
        if args:
            lines.extend([
                '     *'
            ])
            for arg in args:
                if arg['direction'] == 'in':
                    lines.extend([
                        '     * @param[in]  a{0}'.format(arg['name'])
                    ])
                else:
                    lines.extend([
                        '     * @param[out] a{0}'.format(arg['name'])
                    ])
        lines.extend([
            '     */',
            '    void Sync{0}({1});'.format(action['name'], syncstr[action['name']]),
            '    /**',
            '     * Invoke the action asynchronously.',
            '     * Returns immediately and will run the client-specified callback when the action',
            '     * later completes.  Any output arguments can then be retrieved by calling',
            '     * End{0}().'.format(action['name']),
            '     *'
        ])
        if args:
            for arg in args:
                if arg['direction'] == 'in':
                    lines.extend([
                        '     * @param[in] a{0}'.format(arg['name'])
                    ])
        lines.extend([
            '     * @param[in] aFunctor   Callback to run when the action completes.',
            '     *                       This is guaranteed to be run but may indicate an error',
            '     */',
            '    void Begin{0}({1}FunctorAsync& aFunctor);'.format(action['name'], beginstr[action['name']])
        ])
        lines.extend([
            '    /**',
            '     * Retrieve the output arguments from an asynchronously invoked action.',
            '     * This may only be called from the callback set in the above Begin function.',
            '     *',
            '     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function'
        ])
        if args:
            for arg in args:
                if arg['direction'] == 'out':
                    lines.extend([
                        '     * @param[out] a{0}'.format(arg['name'])
                    ])
        lines.extend([
            '     */',
            '    void End{0}(IAsync& aAsync{1});'.format(action['name'], endstr[action['name']])
        ])
    lines.extend([
        ''
    ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    /**',
                '     * Set a callback to be run when the {0} state variable changes.'.format(sv['name']),
                '     *',
                '     * Callbacks may be run in different threads but callbacks for a',
                '     * {0} instance will not overlap.'.format(classname),
                '     *',
                '     * @param[in]  aFunctor  The callback to run when the state variable changes',
                '     */',
                '    void SetProperty{0}Changed(Functor& aFunctor);'.format(sv['name'])
            ])
    lines.extend([
        ''
    ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    /**',
                '     * Query the value of the {0} property.'.format(sv['name']),
                '     *',
                '     * This function is threadsafe and can only be called if Subscribe() has been',
                '     * called and a first eventing callback received more recently than any call',
                '     * to Unsubscribe().',
                '     *',
                '     * @param[out] a{0}'.format(sv['name']),
                '     */',
                '    void Property{0}({1}& a{0}) const;'.format(sv['name'], lookup.InArg(sv['dataType']))
            ])

    lines.extend([
        '    /**',
        '    * This function exposes the Subscribe() function of the iCpProxy member variable',
        '    */',
        '    void Subscribe();',
        '    /**',
        '    * This function exposes the Unsubscribe() function of the iCpProxy member variable',
        '    */',
        '    void Unsubscribe();',
        '    /**',
        '    * This function exposes the SetPropertyChanged() function of the iCpProxy member variable',
        '    */',
        '    void SetPropertyChanged(Functor& aFunctor);',
        '    /**',
        '    * This function exposes the SetPropertyInitialEvent() function of the iCpProxy member variable',
        '    */',
        '    void SetPropertyInitialEvent(Functor& aFunctor);',
        '    /**',
        '    * This function exposes the AddProperty() function of the iCpProxy member variable',
        '    */',
        '    void AddProperty(Property* aProperty);',
        '    /**',
        '    * This function exposes DestroyService() function of the iCpProxy member variable',
        '    */',
        '    void DestroyService();',
        '    /**',
        '    * This function exposes the REportEvent() function of the iCpProxy member variable',
        '    */',
        '    void ReportEvent(Functor aFunctor);',
        '    /**',
        '    * This function exposes the Version() function of the iCpProxy member variable',
        '    */',
        '    TUint Version() const;',
        'private:',
        '    CpProxy iCpProxy;'
    ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    void {0}PropertyChanged();'.format(sv['name'])
            ])

    lines.extend([
        'private:'
    ])
    for action in actions:
        lines.extend([
            '    Action* iAction{0};'.format(action['name'])
        ])
    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    {0}* i{1};'.format(lookup.Property(sv['dataType']), sv['name'])
            ])
    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    Functor i{0}Changed;'.format(sv['name'])
            ])

    lines.extend([
        '};',
        '',
        '} // namespace Net',
        '} // namespace OpenHome',
        '',
        '#endif // HEADER_{0}'.format(headerdef.upper()),
        ''
    ])

    return filename, lines
