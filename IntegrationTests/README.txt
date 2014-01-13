
            ReadMe for ohMediaPlayer integration tests
            ------------------------------------------
            
These tests only run on Windows (due to IronPython dependency)            
            
            
Required Dependencies
---------------------

    Iron Python V2.7 - install from http://ironpython.net/
    
    iTunes (for Airplay tests) - running on local machine, session key setup in
         DacpClient.py (this needs sorting out - key in local lookup etc...)
         
    Access to UPnP media server with necessary files/playlists (for tests using
        UPnP media server to serve the test data [audio] files)
        
    Test PC network interface defined in Config.xml (if more than one i/f present)
    
            
Test and Suite Execution
------------------------

    Tests and Suites are executed from command prompt. Execute without any
    parameters to get help screen. The parameters required (depending on 
    test/suite being executed) are:
    
        DUT name:
             UPnP friendly name of the device-under-test (eg. SoftPlayer:Softplayer)
             
        UPnP Media Server:
            UPnP friendly name of media server to use  (eg: "Asset UPnP: PC887")
            
        Playlist name:
            Name of plauylist to use from UPnP media server
            
    NOTE/
        Examples of parameters can be seen in SuiteXXX.py test suites
         