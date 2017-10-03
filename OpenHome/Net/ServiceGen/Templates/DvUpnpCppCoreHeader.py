"""DvUpnpCppCoreHeader.py - service proxy template"""
import Utils


def Generate(desc, sDomain, sType, sVersion):
    # import json
    # print json.dumps(desc, indent=4)

    lookup    = Utils.TypeLookup()
    filename  = Utils.GetFilename('Dv', sDomain, sType, sVersion, 'h')
    headerdef = filename.split('.')[0]
    classname = 'DvProvider' + headerdef[2:]
    actions    = Utils.GetActions(desc)
    stateVars  = Utils.GetStateVars(desc)

    lines = [
        '#ifndef HEADER_{0}'.format(headerdef.upper()),
        '#define HEADER_{0}'.format(headerdef.upper()),
        '',
        '#include <OpenHome/Types.h>',
        '#include <OpenHome/Buffer.h>',
        '#include <OpenHome/Net/Core/DvDevice.h>',
        '#include <OpenHome/Net/Core/DvProvider.h>',
        '',
        'namespace OpenHome {',
        'namespace Net {',
        '',
        'class DviDevice;',
        'class IDviInvocation;',
        'class PropertyInt;',
        'class PropertyUint;',
        'class PropertyBool;',
        'class PropertyString;',
        'class PropertyBinary;',
        '',
        '/**',
        ' * Provider for the {0}:{1}:{2} UPnP service'.format(sDomain, sType, sVersion),
        ' * @ingroup Providers',
        ' */',
        'class {0} : public DvProvider'.format(classname),
        '{',
        'public:',
        '    virtual ~{0}() {1}'.format(classname, '{}')
    ]

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    /**',
                '     * Set the value of the {0} property'.format(sv['name']),
                '     *',
                '     * Can only be called if EnableProperty{0} has previously been called.'.format(sv['name']),
                '     *',
                '     * @return  true if the value has been updated; false if aValue was the same as the previous value',
                '     */',
                '    TBool SetProperty{0}({1} aValue);'.format( sv['name'], lookup.InArgParam(sv['dataType'])),
                '    /**',
                '     * Get a copy of the value of the {0} property'.format(sv['name']),
                '     *',
                '     * Can only be called if EnableProperty{0} has previously been called.'.format(sv['name']),
                '     */',
                '    void GetProperty{0}({1} aValue);'.format( sv['name'], lookup.OutArgProperty(sv['dataType']))
            ])
            if sv['dataType'] in ['string', 'bin.base64', 'uri']:
                lines.extend([
                    '    /**',
                    '     * Output the value of the {0} property without an intermediate copy.'.format(sv['name']),
                    '     *',
                    '     * Can only be called if EnableProperty{0} has previously been called.'.format(sv['name']),
                    '     */',
                    '    void WriteProperty{0}(IWriter& aWriter);'.format(sv['name'])
                ])

    lines.extend([
        'protected:',
        '    /**',
        '     * Constructor',
        '     *',
        '     * @param[in] aDevice  Device which owns this provider',
        '     */',
        '    {0}(DvDevice& aDevice);'.format(classname),
        '    /**',
        '     * Constructor.  Not for external use.',
        '     *',
        '     * @param[in] aDevice  Device which owns this provider',
        '     */',
        '    {0}(DviDevice& aDevice);'.format(classname)
    ])

    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    /**',
                '     * Enable the {0} property.'.format(sv['name']),
                '     */',
                '    void EnableProperty{0}();'.format(sv['name'])
            ])

    for action in actions:
        lines.extend([
            '    /**',
            '     * Signal that the action {0} is supported.'.format(action['name']),
            "     * The action's availability will be published in the device's service.xml.",
            '     * {0} must be overridden if this is called.'.format(action['name']),
            '     */',
            '    void EnableAction{0}();'.format(action['name'])
        ])

    lines.extend([
        'private:'
    ])
    for action in actions:
        argstr = ''
        args = Utils.GetActionArgs(action, stateVars)
        if args is not None:
            for arg in Utils.GetActionArgs(action, stateVars):
                if arg['direction'] == 'in':
                    argstr += ', {0} a{1}'.format(lookup.InArgParam(arg['type']), arg['name'])
                else:
                    argstr += ', {0} a{1}'.format(lookup.OutArgAction(arg['type']), arg['name'])

        lines.extend([
            '    /**',
            '     * {0} action.'.format(action['name']),
            '     *',
            '     * Will be called when the device stack receives an invocation of the',
            '     * {0} action for the owning device.'.format(action['name']),
            '     * Must be implemented iff EnableAction{0} was called.'.format(action['name']),
            '     */',
            '    virtual void {0}(IDvInvocation& aInvocation{1});'.format(action['name'], argstr)
        ])

    lines.extend([
        'private:',
        '    {0}();'.format(classname),
        '    void Construct();'
    ])
    for action in actions:
        lines.extend([
            '    void Do{0}(IDviInvocation& aInvocation);'.format(action['name'])
        ])

    lines.extend([
        'private:'
    ])
    for sv in stateVars:
        if sv['@sendEvents'] == 'yes':
            lines.extend([
                '    {0}* iProperty{1};'.format(lookup.Property(sv['dataType']), sv['name'])
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
