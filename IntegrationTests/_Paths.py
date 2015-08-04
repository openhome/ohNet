"""_Paths - setup Python search path
"""
import os
import platform
import sys

# Find MediaPlayer root from anywhere INSIDE MediaPlayer tree
root = os.path.dirname( __file__ )
while not os.path.isdir( os.path.join( root, 'IntegrationTests' )):
    root = os.path.dirname( root )

# Get pathing for for FunctionalTest
deps  = os.path.join( root, 'dependencies' )
test  = os.path.abspath( os.path.join( deps, 'AnyPlatform/FunctionalTest' ))

# Get pathing for PyOhNet (platform/architecture dependent)
ohnetRls = ''
ohnetDbg = ''
_platform = platform.system()
_architecture = platform.architecture()
if _platform in ['Windows', 'cli']:
    if '32' in _architecture[0]:
        ohnetRls = os.path.abspath( os.path.join( deps, 'Windows-x86/ohNet-Windows-x86-Release' ))
        ohnetDbg = os.path.abspath( os.path.join( deps, 'Windows-x86/ohNet-Windows-x86-Debug' ))
    elif '64' in _architecture[0]:
        ohnetRls = os.path.abspath( os.path.join( deps, 'Windows-x64/ohNet-Windows-x64-Release' ))
        ohnetDbg = os.path.abspath( os.path.join( deps, 'Windows-x64/ohNet-Windows-x64-Debug' ))
elif _platform == 'Linux':
    if '32' in _architecture[0]:
        ohnetRls = os.path.abspath( os.path.join( deps, 'Linux-x86/ohNet-Linux-x86-Release' ))
        ohnetDbg = os.path.abspath( os.path.join( deps, 'Linux-x86/ohNet-Linux-x86-Debug' ))
    elif '64' in _architecture[0]:
        ohnetRls = os.path.abspath( os.path.join( deps, 'Linux-x64/ohNet-Linux-x64-Release' ))
        ohnetDbg = os.path.abspath( os.path.join( deps, 'Linux-x64/ohNet-Linux-x64-Debug' ))
elif _platform == 'Darwin':
    ohnetRls = os.path.abspath( os.path.join( deps, 'Mac-x64/ohNet-Mac-x64-Release' ))
    ohnetDbg = os.path.abspath( os.path.join( deps, 'Mac-x64/ohNet-Mac-x64-Debug' ))

ohnet = ''
if os.path.exists( ohnetRls ):
    ohnet = ohnetRls
elif os.path.exists( ohnetDbg ):
    ohnet = ohnetDbg
else:
    ohnet = deps    # should never happen

# configure the Python module search path
sys.path.insert( 0, os.path.normpath( os.path.join( ohnet, 'lib' )))
sys.path.insert( 0, os.path.normpath( os.path.join( test, 'Components' )))
sys.path.insert( 0, os.path.normpath( os.path.join( test, 'Framework' )))
sys.path.insert( 0, os.path.normpath( os.path.join( test, 'CommonTests' )))

# paths to data files
audioDir = os.path.join( deps, 'AnyPlatform/FunctionalTestData/Audio' )
