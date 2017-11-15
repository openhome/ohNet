"""PyOhNet: control point functionality
"""
# noinspection PyUnresolvedReferences
from PyOhNet import lib, OhNetError
from _DevList import *
from _Device import *
from _GenProxy import *


def Start( aAdapter ):
    """Start CP stack on specified adapter"""
    err = lib.OhNetLibraryStartCp( aAdapter.subnet )
    if err:
        raise OhNetError( 'Failed to start CP stack' )
