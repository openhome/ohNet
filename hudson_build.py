#!/usr/bin/env python
#
import os, subprocess
from optparse import OptionParser
from Helpers.valgrind_parser import *
from Helpers.remote import *
import sys
from os import path

class PostActions():
    def valgrind_parse(self):
        val = valgrindParser()
        val.get_files('vgout')
        val.parse_file()

    def valgrind_stub(self):
        val = valgrindParser()
        val.put_dummy('vgout')

    def do_release(self,platform):
        rem = remote()
        release_targets = []
        release_targets.append('release')
        release_targets.append('debug')

    def gen_docs(self):
        rem = remote()
        ret = subprocess.check_call('make docs', shell=True)
        if ret != 0:
            print ret
            sys.exit(10)
        rem.rsync('hudson-zapp','ohnet.linn.co.uk','Build/Docs/','~/doc')
        if ret != 0:
            print ret
            sys.exit(10)
        rem.rsync('hudson-rsync','openhome.org','Build/Docs/','~/build/nightly/docs')
        if ret != 0:
            print ret
            sys.exit(10)

    def arm_tests(self,type):
        rem = remote()
        ret = rem.rsync('root','sheeva010.linn.co.uk','Build','~/')
        if ret != 0:
            print ret
            sys.exit(10)
        ret = rem.rsync('root','sheeva010.linn.co.uk','AllTests.py','~/')
        if ret != 0:
            print ret
            sys.exit(10)
        if type == 'nightly':
            ret = rem.rssh('root','sheeva010.linn.co.uk','python AllTests.py -f -t')            
            if ret != 0:
                print ret
                sys.exit(10)
        else:
            ret = rem.rssh('root','sheeva010.linn.co.uk','python AllTests.py -t')
            if ret != 0:
                print ret
                sys.exit(10)        
    
class JenkinsBuild():
    def get_options(self):
        env_platform = os.environ.get('PLATFORM')
        env_nightly = os.environ.get('NIGHTLY')
        env_release = os.environ.get('PUBLISH')
        env_version = os.environ.get('PUBLISH_VERSION')

        parser = OptionParser()
        parser.add_option("-p", "--platform", dest="platform",
            help="Linux-x86, Linux-x64, Windows-x86, Windows-x64, Linux-ARM, Mac-x64")
        parser.add_option("-n", "--nightly",
                  action="store_true", dest="nightly", default=False,
                  help="Perform a nightly build")
        parser.add_option("-r", "--publish",
          action="store_true", dest="release", default=False,
          help="publish release")
        parser.add_option("-v", "--version", dest="version",
            help="version number for release")
        (self.options, self.args) = parser.parse_args()
        
        # check if env variables are set
        # if they are, ignore what is on the command line.

        if env_platform != None:
            self.options.platform = env_platform
        if env_version != None:
            self.options.version = env_version
        if env_nightly == 'true' or self.options.nightly == True:
             self.options.nightly = '1'
        else:
            self.options.nightly = '0'
        if env_release == 'true' or self.options.release == True:
            self.options.release = '1'
        else:
            self.options.release = '0'

        print "options for build are nightly:%s and release:%s on platform %s" %(self.options.nightly,self.options.release,self.options.platform)

    def get_platform(self):
        platforms = { 
            'Linux-x86': { 'os':'linux', 'arch':'x86', 'publish':True},
            'Linux-x64': { 'os':'linux', 'arch':'x64', 'publish':True},
            'Windows-x86': { 'os': 'windows', 'arch':'x86', 'publish':True},
            'Windows-x64': { 'os': 'windows', 'arch':'x64', 'publish':True},
            'Macos-x64': { 'os': 'macos', 'arch':'x86', 'publish':False}, # Old Jenkins label
            'Mac-x64': { 'os': 'macos', 'arch':'x64', 'publish':True}, # New Jenkins label, matches downstream builds
            'Mac-x86': { 'os': 'macos', 'arch':'x86', 'publish':True}, # New Jenkins label, matches downstream builds
            'Linux-ARM': { 'os': 'linux', 'arch': 'arm', 'publish':True},
            'iOs-ARM': { 'os': 'macos', 'arch':'arm', 'publish':True},
        }
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
        if os_platform == 'linux' and arch == 'arm':
            os.environ['CROSS_COMPILE'] = '/usr/local/arm-2011.09/bin/arm-none-linux-gnueabi-'

        self.platform_args = args

    def get_build_args(self):
        nightly = self.options.nightly
        arch = self.platform['arch']
        os_platform = self.platform['os']
        args=[]
        args.append('python')
        args.append('AllTests.py')
        args.append('--silent')

        self.platform_make_args = []

        if arch == 'arm':
            args.append('--buildonly')
        elif arch == 'x64':
            args.append('--native')
        if os_platform == 'windows' and arch == 'x86':
            args.append('--js')
            args.append('--java')
        if os_platform == 'linux' and arch == 'x86':
            args.append('--java')
        if os_platform == 'macos':
            if arch == 'x64':
                args.append('--mac-64')
                self.platform_make_args.append('mac-64=1')
            elif arch == 'arm':
                args.append('--mac-arm')
                self.platform_make_args.append('mac-arm=1')
            # 32 and 64-bit builds run in parallel on the same slave.
            # Overlapping test instances interfere with each other so only run tests for the (assumed more useful) 32-bit build.
            # Temporarily disable all tests on mac as publish jobs hang otherwise
            args.append('--buildonly')
        if nightly == '1':
            args.append('--full')
            if os_platform == 'linux' and arch == 'x86':
                args.append('--valgrind')    
        self.build_args = args

    def do_build(self):
        nightly = self.options.nightly
        release = self.options.release
        os_platform = self.platform['os']
        build_args = self.build_args
        platform_args = self.platform_args
        common_args = []
            
        if platform_args == []:
            common_args.extend(build_args)
        else:
            common_args.extend(platform_args)
            common_args.append('&&')
            common_args.extend(build_args)
            
        build_targets = []
        build_targets.append('debug')

        if release == '1':
            build_targets.append('release')

        for build_t in build_targets:
            build = list(common_args)
            if build_t == 'debug':
                build.append('--debug')
            if build_t == 'release':
                build.append('--incremental')

            print 'running build with %s' %(build,)

            ret = subprocess.check_call(build)            
            if ret != 0:
                print ret
                sys.exit(10)

    def do_release(self):
        rem = remote()

        nightly = self.options.nightly
        release = self.options.release
        platform_args = self.platform_args
        platform = self.options.platform
        version = self.options.version
        
        release_targets = []
        release_targets.append('release')
        release_targets.append('debug')
        
        for release in release_targets:
            build = []
            if platform_args != []:
                build.extend(platform_args)
                build.append('&&')

            build.append('make')
            build.append('bundle-dev')
            build.append('targetplatform=%s' %(platform,))
            build.append('releasetype=%s' %(release,))
            build.append('uset4=yes')
            build.extend(self.platform_make_args)

            print "doing release with bundle %s" %(build,)

            ret = subprocess.check_call(build)
            if ret != 0:
                print ret
                sys.exit(10)

            bundle_name = os.path.join('Build/Bundles',"ohNet-%s-%s-dev.tar.gz" %(platform,release))        
            dest = os.path.join('Build/Bundles',"ohNet-%s-%s-dev-%s.tar.gz" %(version,platform,release))
            if os.path.exists(dest):
                os.remove(dest)
            os.rename(bundle_name, dest)
            rem.check_rsync('releases','www.openhome.org','Build/Bundles/','~/www/artifacts/ohNet/')
                        
    
    def do_postAction(self):
        nightly = self.options.nightly
        release = self.options.release
        os_platform = self.platform['os']
        arch = self.platform['arch']
        postAction = PostActions()

        # generate dummy XML even on on-commit tests
        postAction.valgrind_stub()

        if nightly == '1':
            if os_platform == 'linux' and arch == 'x86':
                postAction.valgrind_parse()
                postAction.gen_docs()

            if os_platform == 'linux' and arch == 'arm':
                postAction.arm_tests('nightly')
        else:
            if os_platform == 'linux' and arch == 'arm':
                postAction.arm_tests('commit')    
        if self.platform['publish'] and release == '1':
            self.do_release()

def switch_to_script_directory():
    ohnet_dir = path.split(path.realpath(__file__))[0]
    os.chdir(ohnet_dir)

def main():
    switch_to_script_directory()
    Build = JenkinsBuild()
    Build.get_options()
    Build.get_platform()
    Build.set_platform_args()
    Build.get_build_args()
    Build.do_build()
    Build.do_postAction()

if __name__ == "__main__":
    main()

