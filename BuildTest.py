import sys
import os
import subprocess

def getToolEnvironment():
        if os.environ.get('label') == 'arm':
                tool = 'env'
                ostype = 'Linux'
                os.environ['PATH'] = "/usr/local/arm-2010q1/bin:"+ os.environ['PATH']
                os.environ['CROSS_COMPILE'] = 'arm-none-linux-gnueabi-'

        elif os.environ.get('label') == 'linux-x64':
                tool = 'env'
                ostype = 'Linux'

        elif os.environ.get('label') == 'linux-x86':
                tool = 'env'
                ostype = 'Linux'

        elif os.environ.get('label') == 'windows-x86':
                tool = 'call vcvarsall.bat'
                ostype = 'Windows'

        elif os.environ.get('label') == 'windows-x64':
                tool = 'call vcvarsall.bat amd64'
                ostype = 'Windows'

        return tool, ostype



def getModule():
        if os.environ.get('module') == 'upnp':
                        module = 'upnp'
                        cmd = 'cd upnp && python AllTests.py -s'
                        nightlyArgs = ' -f -vg'

        if os.environ.get('module') == 'zappSpyGUI':
                        module = 'zappSpyGUI'
                        cmd = 'cd ZappVs2010 && MSBuild.exe Zapp.sln'
                        nightlyArgs = ' -f'

		
	if os.environ.get('nightly') != 'true':
			nightlyArgs = ''

        return module, cmd, nightlyArgs


Tool = getToolEnvironment()
Module = getModule()


def Build(tool, ostype, module, cmd, args):

        buildCmd = []
        buildCmd.append(tool + ' && ' + cmd + args)
        print buildCmd
        ret = subprocess.call(buildCmd, shell=True)
        if ret != 0:
                        sys.exit(ret)


Build(Tool[0],Tool[1],Module[0], Module[1], Module[2])
