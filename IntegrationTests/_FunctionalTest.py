"""_FunctionalTest - add pathing to access FunctionalTest code
"""
import os
import sys
root = '../dependencies/AnyPlatform/FunctionalTest'
sys.path.append( os.path.normpath( os.path.join( os.path.dirname( __file__ ), root, 'Framework' )))
sys.path.append( os.path.normpath( os.path.join( os.path.dirname( __file__ ), root, 'Components' )))

# Path to ohNet DLLs (depends on execution environment)
if os.path.isfile( os.path.join( os.getcwd(), '_FunctionalTest.py' )):
    sys.path.append( os.path.abspath( '../dependencies/Windows-x86/ohNet-Windows-x86-Release/lib' ))
elif os.path.isfile( os.path.join( os.getcwd(), 'go.bat' )):  
    sys.path.append( os.path.abspath( 'dependencies/Windows-x86/ohNet-Windows-x86-Release/lib' ))
