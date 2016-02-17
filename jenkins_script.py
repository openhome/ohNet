#!/usr/bin/env python
import os
import os.path
import subprocess
from optparse import OptionParser

parser = OptionParser()
parser.add_option('--debug', dest='debug', action='store_true')
parser.add_option('--release', dest='debug', action='store_false', default=False)
parser.add_option('--type', dest='type', type='choice', choices=['oncommit', 'nightly', 'integration_tests', 'publish'],
                  default='oncommit', help='Build type: oncommit, nightly, integration_tests, publish')
(opts, args) = parser.parse_args()

cenv=os.environ
cdir=cenv['WORKSPACE']
scrd=cenv['WORKSPACE']

if cenv['PLATFORM'].startswith('Windows-'):
    ext='.bat'
else:
    ext=''

type_cargs = {
    'oncommit' : ['--steps=default', '--incremental-fetch'],
    'nightly'  : ['--steps=default,-test,test_full', '--incremental-fetch'],
    'publish'  : ['--steps=-integration_test,default,publish', '--publish-version', cenv.get('RELEASE_VERSION')],
    'integration_tests' : ['--steps=fetch,configure,clean,build,install,integration_test_full',]
}

cargs = type_cargs[opts.type] + ['-t', cenv['PLATFORM']]
if opts.debug:
    cargs += ['--debug',]
else:
    cargs += ['--release',]

subprocess.check_call(args=[os.path.join(scrd, 'ohMediaPlayer', 'go' + ext), 'ci-build'] + cargs, cwd=cdir)
