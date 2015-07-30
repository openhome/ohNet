#!/usr/bin/env python
"""SongcastConnect - test connect/disconnect/following works correctly

Parameters:
    arg#1 - DUT #1 ['local' for internal SoftPlayer on loopback]
    arg#2 - DUT #2 ['local' for internal SoftPlayer on loopback]
    arg#3 - DUT #3 ['local' for internal SoftPlayer on loopback]
    arg#4 - DUT #4 ['local' for internal SoftPlayer on loopback]
    arg#5 - test scenarios [1,2,3,4,5,all]
    arg#6 - disconnect method [stop,source,sender,standby,all]
    arg#7 - sender mode [unicast/multicast] - (optional - default unicast)

Terminology:
    Sender   - device which is the original source of the audio stream
    Repeater - device receiving stream directly from sender and re-sending
               the stream out to the slave device(s)
    Slave(s) - device(s) receiving audio from a receiver

Test configuration:
                                              +-----+
                                              |     |
                    +-------------------------+  C  |
                    |                         |     |
                    |                         +-----+
                    |
                    |
        +-----+     |      +-----+            +-----+
        |     |     |      |     |            |     |
        |  A  +-----+------+  B  +------------+  D  |
        |     |            |     |            |     |
        +-----+            +-----+            +-----+

        A - Sender
        B - Repeater, following A
        C - Slave (on B) following A
        D - Slave (on B) following B

Test Scenarios:

        1) Checking audio on sender
            - Soundcard on A    (A=DS-1, B=DS-2, C=DS-3, D=DS-4)
            - A playing
            - connect B to A    - no dropout on A
            - connect C to A    - no dropout on A
            - connect D to B    - no dropout on A
            - disconnect B      - no dropout on A, D state -> waiting
            - disconnect C      - no dropout on A
            - disconnect D      - no dropout on A
            - A stopped         - A drops out

        2) Checking audio on repeater
            - Soundcard on B    (B=DS-1, A=DS-2, C=DS-3, D=DS-4)
            - A playing
            - connect B to A    - no dropout on B
            - connect C to A    - no dropout on B
            - connect D to B    - no dropout on B
            - disconnect C      - no dropout on B
            - disconnect D      - no dropout on B
            - disconnect A      - B drops out

        3) Checking audio on slave on sender
            - Soundcard on C    (C=DS-1, A=DS-2, B=DS-3, D=DS-4)
            - A playing
            - connect B to A
            - connect C to A
            - connect D to B    - no dropout on C
            - disconnect B      - no dropout on C, D state -> waiting
            - disconnect D      - no dropout on C
            - disconnect A      - C drops out

        4) Checking audio on slave on repeater
            - Soundcard on D    (D=DS-1, A=DS-2, B=DS-3, C=DS-4)
            - A playing
            - connect B to A
            - connect D to B
            - connect C to A    - no dropout on D
            - disconnect C      - no dropout on D
            - disconnect B      - D drops out - state-> waiting
            
        5) Checking audio on slave follows repeater (trac #3165)  
            - Soundcard on D    (D=DS-1, A=DS-2, B=DS-3, C=DS-4)
            - A playing
            - C playing
            - connect B to A    - no dropout on B
            - connect D to B    - audio on D = audio on C
            - connect B to C    - audio on D = audio on C
"""
import _Paths
import CommonSongcastConnect as BASE
import sys


class TestSongcastConnect( BASE.CommonSongcastConnect ):

    def __init__( self ):
        BASE.CommonSongcastConnect.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
