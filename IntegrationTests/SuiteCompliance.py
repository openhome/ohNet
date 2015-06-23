"""SuiteCompliance - suite of all compliance tests for ohMediaPlayer

Parameters:
    arg#1 - Player to test (UPnP friendly name)

ohMediaPlayer compliant devices should pass the tests applicable to their
supported services cleanly
"""

# Missing:
#   - Credentials - requires account with credentials provider
#   - Radio       - requires non-device-specific way to setup TuneIn account

import _FunctionalTest
import BaseSuite as Suite
import os
import sys
 
try:
    dut = sys.argv[1]
except:
    print '\n', __doc__, '\n'
    print 'Invalid arguments %s' % (str( sys.argv ))
    # noinspection PyProtectedMember
    os._exit( -1 )

tests = [
    [ 'TestComplianceDevice',           dut ],
    [ 'TestCompliancePlaylist1',        dut ],
    [ 'TestCompliancePlaylist2',        dut ],
    [ 'TestCompliancePlaylist3',        dut ],
    [ 'TestComplianceRadio',            dut ],
    [ 'TestComplianceProduct',          dut ],
    [ 'TestComplianceVolume',           dut ],
    [ 'TestComplianceReceiver',         dut ],
    [ 'TestComplianceSender',           dut ]
]

Suite.Suite( tests )
