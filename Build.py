import sys
import os
import subprocess
import threading

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
				tool = 'call vcvarsall.bat && set'
				ostype = 'Windows'
				arch = 'x86'

        elif os.environ.get('label') == 'windows-x64':
				tool = 'call vcvarsall.bat amd64 && set'
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
                print ret        
		sys.exit(10)


Build(Environment['tool'],Module['cmd'],Arguments['args'])

vgpath = "Upnp/vgout"

def StripChars(charname):

        charname = charname.replace('&', '')

        return charname

def ParseValgrind(filename):
        import xml.etree.ElementTree as ET
        fullpath = vgpath + '/' + filename

        doc = ET.parse(fullpath)
        errors = doc.findall('//error')

        out = open(vgpath + '/' + "xunit-" + filename,"w")
        out.write('<?xml version="1.0" encoding="UTF-8"?>\n')
        out.write('<testsuite name="memcheck" tests="1" errors="0" failures="'+str(len(errors))+'" skip="0">\n')
        out.write('    <testcase classname="ValgrindMemoryCheck " \n')
        out.write('              name="'+filename+'" time="0">\n')

        for error in errors:
            kind = error.find('kind')
            what = error.find('what')
            if  what == None:
                what = error.find('xwhat/text')

            out.write('        <error type="'+kind.text+'">\n')
            out.write('            '+what.text+'\n')


            frames = error.findall('.//frame')

            for frame in frames:

                getObj = frame.find('ip')
                getFn = frame.find('fn')
                getDir = frame.find('dir')
                getFile = frame.find('file')
                getLine = frame.find('line')

                out.write(' ---- frame start ----\n')
                if getObj != None:
                        obj = StripChars(getObj.text)
                        out.write(' Object: '+obj+'\n')

                if getFn != None:
                        function = StripChars(getFn.text)
                        out.write(' Function: '+function+'\n')


                if getDir != None:
                        dir = StripChars(getDir.text)
                        out.write(' Directory: '+dir+'\n')

                if getFile != None:
                        file = StripChars(getFile.text)
                        out.write(' File: '+file+'\n')

                if getLine != None:
                        line = StripChars(getLine.text)
                        out.write(' Line: '+line+'\n')

                out.write(' ---- frame end ----\n')

            out.write('        </error>\n')

        out.write('    </testcase>\n')
        out.write('</testsuite>\n')
        out.close()


def ParseDir():

        dirList=os.listdir(vgpath)
        for fname in dirList:
                if fname != "ParseValgrind.py":
                        print fname
                        ParseValgrind(fname)



valgrind_run = Environment['valgrind_run']
valgrind_nightly = Environment['nightly_run']

if valgrind_run != "0" and valgrind_nightly == "1":
        ParseDir()
else:
	os.mkdir(vgpath)
	dummy = open("Upnp/vgout/xunit-dummy.xml", "w")
	dummy.writelines('<?xml version="1.0" encoding="UTF-8"?><testsuite errors="0" failures="0" name="no-valgrind" tests="0"><testcase classname="no-valgrind" name="valgrind-off" time="0"></testcase></testsuite>')
	dummy.close()

def ArmTests(module, arch, nightly):

        host = "10.2.9.84"
        username = "hudson-zapp"

        if module == "upnp" and arch == "arm":

                import paramiko

                rsyncCmd = "rsync -avz --exclude='*.o' --exclude='*.a' --exclude='Include' Upnp/Build "+host+":~/ && rsync -avz Upnp/AllTests.py "+host+":~/"
                ret = subprocess.call(rsyncCmd, shell=True)
                if ret != 0:
			  print ret
                          sys.exit(10)

                ssh = paramiko.SSHClient()
                ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

                ssh.connect(host, username=username, look_for_keys='True')

		if nightly == "1":

                	stdin, stdout, stderr = ssh.exec_command("python AllTests.py -f -t")

		else:
			stdin, stdout, stderr = ssh.exec_command("python AllTests.py -t")
			
                def get_thread(pipe):
                                for line in pipe.readlines():
                                        print line

                stdout_thread = threading.Thread(target=get_thread, args=(stdout,))
                stderr_thread = threading.Thread(target=get_thread, args=(stderr,))

                stdout_thread.start()
                stderr_thread.start()
                stdout_thread.join()
                stderr_thread.join()

                channel = stdout.channel

                exit_status = channel.recv_exit_status()

                if exit_status != 0:
                        print "FAILED: non-zero exit status on sheeva node"
                        ssh.close()
                        print exit_status
			sys.exit(10)

                ssh.close()


ArmTests(Module['module'],Environment['arch'],Environment['nightly_run'])
