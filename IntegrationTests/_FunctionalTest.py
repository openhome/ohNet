"""_FunctionalTest - add pathing to access FunctionalTest code
"""
import os
import sys
root = '../dependencies/AnyPlatform/FunctionalTest'
sys.path.append( os.path.normpath( os.path.join( os.path.dirname( __file__ ), root, 'Framework' )))
sys.path.append( os.path.normpath( os.path.join( os.path.dirname( __file__ ), root, 'Components' )))

# Path to ohNet DLLs (depends on execution environment)
if os.path.isfile( os.path.join( os.getcwd(), '_FunctionalTest.py' )):
    if os.path.isdir( '../dependencies/Windows-x86/ohNet-Windows-x86-Release' ):
        sys.path.append( os.path.abspath( '../dependencies/Windows-x86/ohNet-Windows-x86-Release/lib' ))
    elif os.path.isdir( '../dependencies/Windows-x86/ohNet-Windows-x86-Debug' ):
        sys.path.append( os.path.abspath( '../dependencies/Windows-x86/ohNet-Windows-x86-Debug/lib' ))
elif os.path.isfile( os.path.join( os.getcwd(), 'go.bat' )):  
    if os.path.isdir( '../dependencies/Windows-x86/ohNet-Windows-x86-Release' ):
        sys.path.append( os.path.abspath( 'dependencies/Windows-x86/ohNet-Windows-x86-Release/lib' ))
    elif os.path.isdir( '../dependencies/Windows-x86/ohNet-Windows-x86-Debug' ):
        sys.path.append( os.path.abspath( 'dependencies/Windows-x86/ohNet-Windows-x86-Debug/lib' ))
