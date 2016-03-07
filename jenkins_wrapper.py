import os
import sys
import subprocess
from os import path

chroot = os.environ.get('QNAP_CHROOT')
ohnetdir = path.dirname(path.realpath(__file__))
hudson_scr = 'hudson_build.py'

if chroot:
    cmd = [path.join(path.expanduser('~'), 'bin', 'chroot'), chroot, 'python', path.join(ohnetdir.replace(chroot, '', 1), hudson_scr)]
else:
    cmd = ['python', path.join(ohnetdir, hudson_scr)]

ret = subprocess.check_call(cmd)
if ret != 0:
    print ret
    sys.exit(10)
