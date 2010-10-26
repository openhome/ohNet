import sys
import os
import subprocess

def getEnvironment():
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

	if ostype == "Windows" or ostype == "Linux" and arch == "arm":
		valgrind = "0"
		
	else:
		valgrind = ''
										
	if os.environ.get('nightly') == 'true':
		nightly = '1'
		
	else:
		nightly = '0'
		
	return {'tool':tool, 'ostype':ostype, 'arch':arch, 'valgrind_run':valgrind, 'nightly_run':nightly }

Environment = getEnvironment()

def getModule(): 
		if os.environ.get('module') == 'upnp':
				module = 'upnp'
				cmd = 'cd Upnp && python AllTests.py'
		
		if os.environ.get('module') == 'zappSpyGUI':
				module = 'zappSpyGUI'
				cmd = 'cd ZappVs2010 && MSBuild.exe Zapp.sln'
		
		return {'module':module, 'cmd':cmd}
		
Module = getModule()

def getArguments(module,nightly,arch,valgrind):

	if module == "upnp" and nightly == "1" and arch != "arm":
			if valgrind != "0":
				args = ' -s -f -vg'
				
			else:
				args = ' -s -f'
				
	elif module == "upnp" and arch == 'arm':
				args = ' -b'
				
	elif module == "upnp":
				args = ' -s'
				
	else:				
				args = ''

	return {'args':args}
	
Arguments = getArguments(Module['module'],Environment['nightly_run'],Environment['arch'],Environment['valgrind_run'])
			

def Build(tool, cmd, args):

        buildCmd = []
        buildCmd.append(tool + ' && ' + cmd + args)
        print buildCmd
        ret = subprocess.call(buildCmd, shell=True)
        if ret != 0:
                        sys.exit(ret)


Build(Environment['tool'],Module['cmd'],Arguments['args'])

#test
