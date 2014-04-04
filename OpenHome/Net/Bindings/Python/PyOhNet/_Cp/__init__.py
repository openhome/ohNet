"""PyOhNet: control point functionality
""" 
from PyOhNet import lib, OhNetError
from _DevList import *          
from _Device import *
from _GenProxy import *


def _Start( aAdapter ):
    "Start CP stack on specified adapter"
    err = lib.OhNetLibraryStartCp( aAdapter.subnet )
    if err:
        raise OhNetError( 'Failed to start CP stack' )
