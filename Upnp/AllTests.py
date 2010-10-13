import os
import sys
import subprocess

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
    aCmdLine.insert(0, testExe)
    ret = subprocess.call(aCmdLine)
    if ret != 0:
        print '\nTest ' + aTarget + ' failed, aborting'
        sys.exit(ret)

def testNoArgs(aTarget):
    test(aTarget, [''])

def runTests():
    buildOnly = 0
    incremental = 0
    for arg in sys.argv:
        if arg == '-b' or arg == '--buildonly':
            buildOnly = 1
        elif arg == '-i' or arg == '--incremental':
            incremental = 1
        elif arg != 'AllTests.py':
            print 'Unrecognised argument - ' + arg
            sys.exit(1)
    if incremental == 0:
        if os.name == 'nt':
            cleanCmd = 'nmake /s /f Zapp.mak clean'
        else:
            cleanCmd = 'make clean'
        os.system(cleanCmd)
    build('Tests')
    build('Zapp')
    build('CpProxyDlls')
    build('DvDeviceDlls')
    print '\nBuilds complete'
    if buildOnly == 0:
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
        testNoArgs('TestProxyCs')
        print '\nFinished.  All tests passed'

cleanCmd = ''
os.environ["ABORT_ON_FAILURE"] = "1"
runTests()
