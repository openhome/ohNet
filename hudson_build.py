#!/usr/bin/env python
#
import json
import os
import requests
import subprocess
import shutil
import sys
import stat
from optparse import OptionParser
from Helpers.valgrind_parser import *
from Helpers.remote import *
from os import path


try:
    import boto3
except:
    print('\nAWS fetch requires boto3 module')
    print("Please install this using 'pip install boto3'\n")
else:
    awsSlave = False
    try:
        resp = requests.get( 'http://169.254.169.254/latest/meta-data/iam/info', timeout=1 )
        meta = json.loads( resp.text )
        if 'InstanceProfileArn' in meta:
            if 'dev-tools-EC2SlaveInstanceProfile' in meta['InstanceProfileArn']:
                awsSlave = True
    except:
        pass

    if not awsSlave:
        # create AWS credentials file (if not already present)
        home = None
        if 'HOMEPATH' in os.environ and 'HOMEDRIVE' in os.environ:
            home = os.path.join(os.environ['HOMEDRIVE'], os.environ['HOMEPATH'])
        elif 'HOME' in os.environ:
            home = os.environ['HOME']
        if home:
            awsCreds = os.path.join(home, '.aws', 'credentials')
            if not os.path.exists(awsCreds):
                if sys.version_info[0] == 2:
                    from urllib2 import urlopen
                else:
                    from urllib.request import urlopen
                try:
                    os.mkdir(os.path.join(home, '.aws'))
                except:
                    pass
                try:
                    credsFile = urlopen('http://core.linn.co.uk/aws-credentials' )
                    creds = credsFile.read()
                    with open(awsCreds, 'wt') as f:
                        f.write(creds)
                except:
                    pass


class PostActions():
    def valgrind_parse(self):
        val = valgrindParser()
        val.get_files('vgout')
        val.parse_file()

    def valgrind_stub(self):
        val = valgrindParser()
        val.put_dummy('vgout')

    def do_release(self, platform):
        release_targets = []
        release_targets.append('release')
        release_targets.append('debug')

    def gen_docs(self):
        ret = subprocess.check_call('make docs', shell=True)
        if ret != 0:
            print( ret )
            sys.exit(10)
        print( 'WARNING: publication of API docs disabled' )

    def armel_tests(self, type, release):
        self.__remote_tests('sheeva010.linn.co.uk', 'root', type, release)

    def __remote_tests(self, host, user, type, release):
        # type will be either 'nightly' or 'commit'
        # release will be either '0' or '1'
        rem = remote()
        ret = rem.rsync(user, host, 'Build', '~/', excludes=['*.o', '*.a', 'Bundles'])
        if ret != 0:
            print( ret )
            sys.exit(10)
        ret = rem.rsync(user, host, 'AllTests.py', '~/')
        if ret != 0:
            print( ret )
            sys.exit(10)

        alltests_cmd = 'python AllTests.py -t --native'  # Setup AllTests cmd line to run tests only.

        if type == 'nightly':
            alltests_cmd += ' -f'        # Add 'full test' flag if in nightly-mode
        if release == '0':
            alltests_cmd += ' --debug'   # Run binaries residing in Build/Debug instead of Build/Release

        ret = rem.rssh(user, host, alltests_cmd)
        if ret != 0:
            print( ret )
            sys.exit(10)


class JenkinsBuild():
    def get_options(self):
        env_platform = os.environ.get('PLATFORM')
        env_nightly = os.environ.get('NIGHTLY')
        env_release = os.environ.get('PUBLISH')
        env_version = os.environ.get('PUBLISH_VERSION')

        parser = OptionParser()
        parser.add_option("-p", "--platform", dest="platform",
            help="Linux-x86, Linux-x64, Windows-x86, Windows-x64, Linux-ARM, Linux-armhf, Linux-mipsel, Linux-ppc32, Linux-rpi, Mac-x64, Core-ppc32, Core-armv6, iOs-arm64, iOs-x64, Qnap-x86, Qnap-x19")
        parser.add_option("-n", "--nightly",
                  action="store_true", dest="nightly", default=False,
                  help="Perform a nightly build")
        parser.add_option("-r", "--publish",
          action="store_true", dest="release", default=False,
          help="publish release")
        parser.add_option("-v", "--version", dest="version",
            help="version number for release")
        parser.add_option("-j", "--parallel",
            action="store_true", dest="parallel", default=False,
            help="Tell AllTests.py to parallelise the build.")
        (self.options, self.args) = parser.parse_args()

        # check if env variables are set
        # if they are, ignore what is on the command line.

        if env_platform is not None:
            self.options.platform = env_platform
        if env_version is not None:
            self.options.version = env_version
        if env_nightly == 'true' or self.options.nightly:
            self.options.nightly = '1'
        else:
            self.options.nightly = '0'
        if env_release == 'true' or self.options.release:
            self.options.release = '1'
        else:
            self.options.release = '0'

        print( "options for build are nightly:%s and release:%s on platform %s" % (self.options.nightly, self.options.release, self.options.platform))

    def get_platform(self):
        platforms = {
            'Linux-x86': { 'os': 'linux', 'arch': 'x86', 'publish': True, 'system': 'Linux'},
            'Linux-x64': { 'os': 'linux', 'arch': 'x64', 'publish': True, 'system': 'Linux'},
            'Linux-ppc32': { 'os': 'linux', 'arch': 'ppc32', 'publish': True, 'system': 'Linux'},
            'Windows-x86': { 'os': 'windows', 'arch': 'x86', 'publish': True, 'system': 'Windows'},
            'Windows-x64': { 'os': 'windows', 'arch': 'x64', 'publish': True, 'system': 'Windows'},
            'Macos-x64': { 'os': 'macos', 'arch': 'x86', 'publish': False, 'system': 'Mac'},  # Old Jenkins label
            'Mac-x64': { 'os': 'macos', 'arch': 'x64', 'publish': True, 'system': 'Mac'},     # New Jenkins label, matches downstream builds
            'Linux-ARM': { 'os': 'linux', 'arch': 'armel', 'publish': True, 'system': 'Linux'},
            'Linux-armhf': { 'os': 'linux', 'arch': 'armhf', 'publish': True, 'system': 'Linux'},
            'Linux-rpi': { 'os': 'linux', 'arch': 'rpi', 'publish': True, 'system': 'Linux'},
            'Linux-mipsel': { 'os': 'linux', 'arch': 'mipsel', 'publish': True, 'system': 'Linux'},
            'Linux-arm64': { 'os': 'linux', 'arch': 'arm64', 'publish': True, 'system': 'Linux'},
            'iOs-x64': { 'os': 'iOs', 'arch': 'x64', 'publish': True, 'system': 'iOs'},
            'iOs-arm64': { 'os': 'iOs', 'arch': 'arm64', 'publish': True, 'system': 'iOs'},
            'Core-ppc32': { 'os': 'Core', 'arch': 'ppc32', 'publish': True, 'system': 'Core'},
            'Core-armv6': { 'os': 'Core', 'arch': 'armv6', 'publish': True, 'system': 'Core'},
            'Android-anycpu': { 'os': 'Android', 'arch': 'anycpu', 'publish': True, 'system': 'Android'},
            'Qnap-x86': { 'os': 'Qnap', 'arch': 'x86', 'publish': True, 'system': 'Qnap'},
            'Qnap-x19': {'os': 'Qnap', 'arch': 'x19', 'publish': True, 'system': 'Qnap'}
        }
        current_platform = self.options.platform
        self.platform = platforms[current_platform]
        
    def install_dotnet(self):
        os_platform = self.platform['os']
        arch = self.platform['arch']

        dotnet_install_cmd = []
        
        pre_installed_platforms = [
            'windows',
            'macos',
            'iOs',
        ]

        if os_platform in pre_installed_platforms:
            print ('dotnet SDK should be preinstalled on for this platform ')
            return

        dotnet_install_cmd.append('./dotnet-install.sh')
        dotnet_install_cmd.append('--channel')
        dotnet_install_cmd.append('LTS')

        print( 'running install_dotnet with %s' % (dotnet_install_cmd,))

        ret = subprocess.check_call(dotnet_install_cmd)
        if ret != 0:
            print('Failed to install dotnet: %s' % ret)
            sys.exit(10)

        #NOTE: The script doesn't set up any PATH entries for dotnet. No point setting them here as the env isn't
        #      provided to the makefile so we configure the paths there

    def set_platform_args(self):
        os_platform = self.platform['os']
        arch = self.platform['arch']
        args = []

        if os_platform == 'windows' and arch == 'x86':
            args.append('C:\\Program Files\\Microsoft Visual Studio\\2022\\Professional\\VC\\Auxiliary\\Build\\vcvarsall.bat')
            args.append('x86')
        if os_platform == 'windows' and arch == 'x64':
            args.append('C:\\Program Files\\Microsoft Visual Studio\\2022\\Professional\\VC\\Auxiliary\\Build\\vcvarsall.bat')
            args.append('amd64')
            os.environ['CS_PLATFORM'] = 'x64'
        if os_platform == 'linux' and arch == 'armel':
            os.environ['CROSS_COMPILE'] = '/usr/local/arm-2011.09/bin/arm-none-linux-gnueabi-'
        if os_platform == 'linux' and arch == 'armhf':
            # get built SDK from our AWS storage
            # print("working dir is " + os.getcwd())
            # print("running as " + os.getlogin())
            # resource = boto3.resource('s3')
            # bucket = resource.Bucket("linn-artifacts-private")
            # with open("/home/hudson-smarties/yocto_sdk.sh", "wb") as sdk_file:
            #     bucket.download_fileobj("yocto_core4_sdk/linn-fb-glibc-x86_64-linn-image-core-cortexa9t2hf-neon-linn-imx6dl-toolchain-5.15-kirkstone-0.0.23.sh", sdk_file)
            # os.chmod("/home/hudson-smarties/yocto_sdk.sh", stat.S_IXUSR)
            
            # subprocess.check_output("/home/hudson-smarties/yocto_sdk.sh -y -d /home/hudson-smarties/linn-fb/5.15-kirkstone", shell=True)

            # Parse yocto environment file, set up for build
            env_string = subprocess.check_output(". /opt/linn-fb/5.15-kirkstone/environment-setup-cortexa9t2hf-neon-poky-linux-gnueabi && env", shell=True)
            for el in env_string.decode("utf-8").split("\n"):
                if "=" in el:
                    os.environ[el.split("=")[0]] = el.split("=", 1)[1]
            if os.environ.get("CC", None):
                os.environ["CFLAGS"] = " ".join(os.environ["CC"].split(" ")[1:])
            if os.environ.get("CXX", None):
                os.environ["CXXFLAGS"] = " ".join(os.environ["CXX"].split(" ")[1:])  
        if os_platform == 'linux' and arch == 'rpi':
            os.environ['CROSS_COMPILE'] = '/opt/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-'
        if os_platform == 'linux' and arch == 'mipsel':
            os.environ['CROSS_COMPILE'] = '/opt/mips-2015.05-18/bin/mips-linux-gnu-'
        if os_platform == 'linux' and arch == 'ppc32':
            os.environ['CROSS_COMPILE'] = 'powerpc-linux-gnu-'
        if os_platform == 'Core' and arch == 'ppc32':
            os.environ['CROSS_COMPILE'] = '/opt/rtems-4.11-rsb/bin/powerpc-rtems4.11-'
        if os_platform == 'Core' and (arch == 'armv5' or arch == 'armv6'):
            os.environ['CROSS_COMPILE'] = '/opt/rtems-4.11-rsb/bin/arm-rtems4.11-'
        if os_platform == 'Qnap' and arch == 'x19':
            os.environ['CROSS_COMPILE'] = '/home/bldslv/qnap-gcc/cross-project/arm/marvell/bin/arm-none-linux-gnueabi-'

        # If building on a 64-bit machine it is possible that both 32-bit and 64-bit JDKs/JREs are installed, and JAVA_HOME may point to the wrong one for the target architecture.
        # Python provides no generic way to check if build machine OS is 32-bit or 64-bit.
        # Just check if the arch of the target platform is 32-bit or 64-bit, and see if the respective JAVA_HOME_XX environment variable is set.
        # If JAVA_HOME_XX is not set, assume that only one JDK/JRE is installed and use JAVA_HOME as set on build machine.

        print("arch: ", arch)
        if 'JAVA_HOME_64' in os.environ:
            print('JAVA_HOME_64: ', os.environ['JAVA_HOME_64'])
        if 'JAVA_HOME_32' in os.environ:
            print('JAVA_HOME_32: ', os.environ['JAVA_HOME_32'])
        if 'JAVA_HOME' in os.environ:
            print('JAVA_HOME: ', os.environ['JAVA_HOME'])

        if arch == 'x64' and 'JAVA_HOME_64' in os.environ:
            os.environ['JAVA_HOME'] = os.environ['JAVA_HOME_64']
        elif arch == 'x86' and 'JAVA_HOME_32' in os.environ:
            os.environ['JAVA_HOME'] = os.environ['JAVA_HOME_32']

        self.platform_args = args

    def get_build_args(self):
        nightly = self.options.nightly
        arch = self.platform['arch']
        os_platform = self.platform['os']
        args = []
        args.append('python')
        args.append('AllTests.py')
        args.append('--silent')

        self.platform_make_args = []

        if    arch in ['armel', 'armhf', 'armv7', 'arm64', 'armv5', 'armv6', 'mipsel', 'ppc32', 'rpi', 'arm64'] \
           or os_platform in ['iOs', 'Android']                                       \
           or self.options.release == '1':
            args.append('--buildonly')
        elif arch == 'x64':
            if os_platform  == 'macos':
                args.append('--native-tests')
            elif os_platform not in ['windows', 'linux', 'iOs']:
                args.append('--native-builds')
        if os_platform == 'windows' and arch == 'x86':
            args.append('--js')
            args.append('--java')
            args.append('--native-tests') # see #7609
        if os_platform == 'linux' and arch == 'x86':
            args.append('--java')
        if os_platform == 'macos':
            args.append('--mac-64')
            self.platform_make_args.append('mac-64=1')
        if os_platform == 'iOs':
            if arch == 'x64':
                args.append('--iOs-x64')
                self.platform_make_args.append('iOs-x64=1')
            elif arch == 'arm64':
                args.append('--iOs-arm64')
                self.platform_make_args.append('iOs-arm64=1')
        if os_platform == 'Linux':
            if arch == 'rpi':
                args.append('--Linux-rpi')
                self.platform_make_args.append('Linux-rpi=1')
            # 32 and 64-bit builds run in parallel on the same slave.
            # Overlapping test instances interfere with each other so only run tests for the (assumed more useful) 32-bit build.
            # Temporarily disable all tests on mac as publish jobs hang otherwise
            args.append('--buildonly')
        if os_platform == 'Android':
            args.append('--Android-anycpu')
            self.platform_make_args.append('Android-anycpu=1')
        if os_platform == 'Qnap':
            args.extend(['--qnap', '--buildonly'])
        if os_platform == 'Core':
            args.append('--core')
        if os_platform == 'linux' and arch == 'x86':
            args.append('--native-tests')
        if nightly == '1':
            args.append('--full')
            if os_platform == 'linux' and arch == 'x86':
                args.append('--valgrind')
        if self.options.parallel:
            args.append('--parallel')
        self.build_args = args

    def do_build(self):
        release = self.options.release
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

            print( 'running build with %s' % (build,))

            ret = subprocess.check_call(build)
            if ret != 0:
                print( ret )
                sys.exit(10)

    def do_release(self):
        release = self.options.release
        platform_args = self.platform_args
        platform = self.options.platform
        version = self.options.version
        openhome_system = self.platform['system']
        openhome_architecture = self.platform['arch']

        release_targets = []
        release_targets.append('release')
        release_targets.append('debug')

        # clean slate so as not to upload random junk inadvertently
        shutil.rmtree(os.path.join('Build', 'Bundles'), ignore_errors=True)

        for release in release_targets:
            openhome_configuration = release.title()
            build = []
            if platform_args != []:
                build.extend(platform_args)
                build.append('&&')
            build.append('make')
            build.append('tt')
            build.append('uset4=yes')
            if self.platform['os'] == 'Qnap':
                build.append('platform=' + platform)
            ret = subprocess.check_call(build)
            if ret != 0:
                print( ret )
                sys.exit(10)

            build = []
            if platform_args != []:
                build.extend(platform_args)
                build.append('&&')

            build.append('make')
            build.append('bundle')
            build.append('uset4=yes')
            if self.platform['os'] == 'Qnap':
                build.append('platform=' + platform)
            build.append('openhome_system=' + openhome_system)
            build.append('openhome_architecture=' + openhome_architecture)
            build.append('openhome_configuration=' + openhome_configuration)
            build.extend(self.platform_make_args)
            print( "doing release with bundle %s" % (build,))

            ret = subprocess.check_call(build)
            if ret != 0:
                print( ret )
                sys.exit(10)

            native_bundle_name = os.path.join('Build/Bundles', "ohNet-%s-%s-%s.tar.gz" % (openhome_system, openhome_architecture, openhome_configuration))
            native_dest = os.path.join('Build/Bundles', "ohNet-%s-%s-%s-%s.tar.gz" % (version, openhome_system, openhome_architecture, openhome_configuration))
            if os.path.exists(native_dest):
                os.remove(native_dest)
            os.rename(native_bundle_name, native_dest)

        entries = os.listdir('Build/Bundles/')
        for entry in entries:
            src = 'Build/Bundles/' + entry
            dst = 's3://linn-artifacts-public/artifacts/ohNet/' + entry.split('/')[-1]
            print('Publish %s --> %s' % (src, dst))
            resource = boto3.resource('s3')
            bucket = resource.Bucket(dst.split('/')[2])
            key = '/'.join(dst.split('/')[3:])
            with open( src, 'rb' ) as data:
                bucket.upload_fileobj(data, key)

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

            if os_platform == 'linux':
                if arch == 'armel':
                    postAction.armel_tests('nightly', release)
        else:
            if os_platform == 'linux':
                if arch == 'armel':
                    postAction.armel_tests('commit', release)

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
    Build.install_dotnet()
    Build.get_build_args()
    Build.do_build()
    Build.do_postAction()


if __name__ == "__main__":
    main()
