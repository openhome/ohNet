import os
import sys

def build(aTarget):
    buildCmd = 'make -s '
    if os.name == 'nt':
        buildCmd = 'nmake /s /f Zapp.mak '
    buildCmd += aTarget
    ret = os.system(buildCmd)
    if (0 != ret):
        print '\nBuild for ' + aTarget + ' failed, aborting'
        sys.exit(ret)

def test(aTarget, aCmdLine):
    build(aTarget)
    testExe = 'Build/Obj/'
    if os.name == 'nt':
        testExe += 'Windows/'
    else:
        testExe += 'Posix/'
    testExe += aTarget
    if os.name == 'nt':
        testExe += '.exe'
    else:
        testExe += '.elf'
    ret = os.spawnv(os.P_WAIT, testExe, aCmdLine)
    if ret != 0:
        print '\nTest ' + aTarget + ' failed, aborting'
        sys.exit(ret)

def testNoArgs(aTarget):
    test(aTarget, [''])

def runTests():
    build('Tests')
    build('Zapp')
    build('CpProxyDlls')
    build('DvDeviceDlls')
    testNoArgs('TestBuffer')
    testNoArgs('TestThread')
    testNoArgs('TestFifo')
    testNoArgs('TestQueue')
    testNoArgs('TestNetwork')
    # TestEcho is interactive so can't be run here
    # TestTimer is relatively long running and covers an area that rarely changes
    test('TestSsdpMListen', ['-d', '10'])
    test('TestSsdpUListen', ['-t', 'linn.co.uk:service:Radio:1'])
    test('TestDeviceList', ['-t', 'linn.co.uk:service:Radio:1', '-f'])
    test('TestDeviceListStd', ['-t', 'linn.co.uk:service:Radio:1', '-f'])
    test('TestDeviceListC', ['-t', 'linn.co.uk:service:Radio:1', '-f'])
    testNoArgs('TestInvocation')
    testNoArgs('TestInvocationStd')
    testNoArgs('TestSubscription')
    testNoArgs('TestProxyC')
    testNoArgs('TestDviDiscovery')
    testNoArgs('TestDviDeviceList')
    testNoArgs('TestDvInvocation')
    testNoArgs('TestDvSubscription')
    testNoArgs('TestDvDeviceStd')
    testNoArgs('TestDvDeviceC')
    # TestTopology1, TestTopology2 not quite ready for general use just yet
    # TestDviDiscovery doesn't support overlapping instances on a network

cleanCmd = ''
if os.name == 'nt':
    cleanCmd = 'nmake /s /f Zapp.mak clean'
else:
    cleanCmd = 'make clean'
os.system(cleanCmd)
os.environ["ABORT_ON_FAILURE"] = "1"
runTests()
print '\nFinished.  All tests passed'
