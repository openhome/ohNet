#!/usr/bin/env python
import os
import os.path
import subprocess

cenv=os.environ
if cenv['PLATFORM'] == 'Linux-mipsel':
    cdir=cenv['CHROMIUM_BASE']
    scrd=cenv['WORKSPACE'].replace(cenv['CHROMIUM_CHROOT'],'',1)
    prefix=[os.path.join(cenv['DEPOT_TOOLS'], 'cros_sdk'), '--']
else:
    cdir=cenv['WORKSPACE']
    scrd=cenv['WORKSPACE']
    prefix=[]

pth = os.path.join(cenv['WORKSPACE'], 'ohNet')
if os.path.isfile(os.path.join(pth, 'hudson_build.py')):
    scrd=os.path.join(scrd, 'ohNet')

cargs=['-p', cenv['PLATFORM']]
if cenv.get('NIGHTLY') == 'true':
    cargs += ['-n',]
if cenv.get('PUBLISH') == 'true':
    cargs += ['-r', '-v', cenv['PUBLISH_VERSION']]

subprocess.check_call(args=prefix + ['python', os.path.join(scrd, 'hudson_build.py')] + cargs, cwd=cdir)

