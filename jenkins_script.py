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

cargs=['-p', cenv['PLATFORM']]
if 'NIGHTLY' in cenv:
    cargs += ['-n',]
if 'PUBLISH' in cenv:
    cargs += ['-r', '-v', cenv['PUBLISH_VERSION']]

subprocess.check_call(args=prefix + ['python', os.path.join(scrd, 'hudson_build.py')] + cargs, cwd=cdir)

