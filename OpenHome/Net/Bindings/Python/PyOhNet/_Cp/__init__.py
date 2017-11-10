"""PyOhNet: control point functionality
"""
# noinspection PyUnresolvedReferences
from PyOhNet import lib, OhNetError
from _Cp._DevList import *   # NOQA
from _Cp._Device import *    # NOQA
from _Cp._GenProxy import *  # NOQA


def Start( aAdapter ):
    """Start CP stack on specified adapter"""
    err = lib.OhNetLibraryStartCp( aAdapter.subnet )
    if err:
        raise OhNetError( 'Failed to start CP stack' )
