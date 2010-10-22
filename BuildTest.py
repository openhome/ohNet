import sys
import os
import subprocess

def getToolEnvironment():
        if os.environ.get('label') == 'arm':
                tool = 'env'
                ostype = 'Linux'
		arch = 'arm'
                os.environ['PATH'] = "/usr/local/arm-2010q1/bin:"+ os.environ['PATH']
                os.environ['CROSS_COMPILE'] = 'arm-none-linux-gnueabi-'

        elif os.environ.get('label') == 'linux-x64':
                tool = 'env'
                ostype = 'Linux'
		arch = 'x64'

        elif os.environ.get('label') == 'linux-x86':
                tool = 'env'
                ostype = 'Linux'
		arch = 'x86'

        elif os.environ.get('label') == 'windows-x86':
                tool = 'call vcvarsall.bat'
                ostype = 'Windows'
		arch = 'x86'

        elif os.environ.get('label') == 'windows-x64':
                tool = 'call vcvarsall.bat amd64'
                ostype = 'Windows'
		arch = 'x64'

        return tool, ostype, arch


Tool = getToolEnvironment()



def getModule(ostype, arch):
        if os.environ.get('module') == 'upnp':
                        module = 'upnp'
                        cmd = 'cd Upnp && python AllTests.py -s'

			if arch != "arm" and ostype == "Linux":
				nightlyArgs = ' -f -vg'

			elif ostype == "Windows":
				nightlyArgs = ' -f'

			else:
				nightlyargs = ' -b'

        if os.environ.get('module') == 'zappSpyGUI':
                        module = 'zappSpyGUI'
                        cmd = 'cd ../ZappVs2010 && MSBuild.exe Zapp.sln'
			nightlyArgs = ''

	if os.environ.get('nightly') != 'true':
			nightlyArgs = ''

        return module, cmd, nightlyArgs


Module = getModule(Tool[1],Tool[2])


def Build(tool, ostype, module, cmd, args):

        buildCmd = []
        buildCmd.append(tool + ' && ' + cmd + args)
        print buildCmd
        ret = subprocess.call(buildCmd, shell=True)
        if ret != 0:
                        sys.exit(ret)


Build(Tool[0],Tool[1],Module[0], Module[1], Module[2])
