import os
import platform
import sys
import subprocess


if os.environ.get('label') == 'arm':
	if sys.platform == 'linux2':
        	os.environ['PATH'] = "/usr/local/arm-2010q1/bin:"+ os.environ['PATH']
		os.environ['CROSS_COMPILE'] = 'arm-none-linux-gnueabi-'

if os.environ.get('module') == 'upnp':
        print "upnp selected"
        if sys.platform == 'linux2':
                print "linux 2"
                buildCmd = 'cd Upnp && python AllTests.py -s'

		if os.environ.get('nightly') == 'true':
			buildCmd = 'cd Upnp && python AllTests.py -f -s -vg'


		if os.environ.get('label') == 'arm':
			buildCmd = 'cd Upnp && python AllTests.py -b'



        elif sys.platform == 'win32':
                print "windows"
                buildCmd = "call vcvarsall.bat && cd Upnp && python AllTests.py -s"

		if os.environ.get('nightly') == 'true':
			buildCmd = "call vcvarsall.bat && cd Upnp && python AllTests.py -f -s"

		if os.environ.get('label') == 'windows-x64':
			buildCmd = "call vcvarsall.bat amd64 && cd Upnp && python AllTests.py -s"

			if os.environ.get('nightly') == 'true':
				buildCmd = "call vcvarsall.bat amd64 && cd Upnp && python AllTests.py -f -s"
			
        else:
                print "Cant find Target"


if os.environ.get('module') == 'zappSpyGUI':
        print "zappspy selected"
        if sys.platform == 'win32':
                print "windows"
                buildCmd = 'call vcvarsall.bat && cd ZappVs2010 && MSBuild.exe Zapp.sln'

		if os.environ.get('label') == 'windows-x64':
			buildCmd = "call vcvarsall.bat amd64 && cd ZappVs2010 && MSBuild.exe Zapp.sln"

ret = subprocess.call(buildCmd, shell=True)
if ret != 0:
        sys.exit(ret)