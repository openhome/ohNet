#!/usr/bin/env python
import os, subprocess, Helpers.valgrind_parser
from optparse import OptionParser

class JenkinsBuild():
	def get_options(self):
		parser = OptionParser()
		parser.add_option("-p", "--platform", dest="platform",
			help="linux-x86, linux-x64, windows-x86, windows-x64, arm")
		parser.add_option("-n", "--nightly",
                  action="store_true", dest="nightly", default=False,
                  help="Perform a nightly build")

		(self.options, self.args) = parser.parse_args()

	def get_platform(self):
		
		platforms = { 
		'linux-x86': { 'os':'linux', 'arch':'x86'},
		'linux-x64': { 'os':'linux', 'arch':'x64'},
		'windows-x86': { 'os': 'windows', 'arch':'x86'},
		'windows-x64': { 'os': 'windows', 'arch':'x64'},
		'macos-x64': { 'os': 'macos', 'arch':'x86'},
		'arm': { 'os': 'linux', 'arch': 'arm'},
		 }

		if self.options.platform == None:
			self.options.platform = os.environ.get('PLATFORM')
		
		current_platform = self.options.platform

		self.platform = platforms[current_platform]

	def set_platform_args(self):
		os_platform = self.platform['os']
		arch = self.platform['arch']
		args=[]
		
		if os_platform == 'windows' and arch == 'x86':
			args.append('vcvarsall.bat')
		if os_platform == 'windows' and arch == 'x64':
			args.append('vcvarsall.bat')
			args.append('amd64')
			os.environ['CS_PLATFORM'] = 'x64'
		if arch == 'arm':
			os.environ['CROSS_COMPILE'] = 'arm-none-linux-gnueabi-'

		self.platform_args = args

	def get_build_args(self):
		nightly = self.options.nightly
		arch = self.platform['arch']
		os_platform = self.platform['os']
		args=[]
		args.append('python')
		args.append('AllTests.py')
		args.append('--silent')

		if arch == 'arm':
			args.append('--buildonly')
		elif arch == 'x64':
			args.append('--native')
		if os_platform == 'macos':
			args.append('--buildonly')
		if os_platform == 'windows' and arch == 'x86':
			args.append('--js')
			args.append('--java')
		if os_platform == 'windows' or nightly == True:
			args.append('--release')
		if os_platform == 'linux' and arch == 'x86':
			args.append('--java')
		if nightly == True:
			args.append('--full')
			if os_platform == 'linux' and arch == 'x86':
				args.append('--valgrind')	
		self.build_args = args

	def do_build(self):
		nightly = self.options.nightly
		os_platform = self.platform['os']

		build_args = self.build_args
		platform_args = self.platform_args

		if platform_args == []:
			platform_args.extend(build_args)

		else:
			platform_args.append('&&')
			platform_args.extend(build_args)

		print "building with %s on platform %s" %(platform_args, os_platform)

		ret = subprocess.check_call(platform_args)
		if ret != 0:
			print ret
			sys.exit(10)

def main():
	Build = JenkinsBuild()
	Build.get_options()
	Build.get_platform()
	Build.set_platform_args()
	Build.get_build_args()
	Build.do_build()
	
if __name__ == "__main__":
	main()

