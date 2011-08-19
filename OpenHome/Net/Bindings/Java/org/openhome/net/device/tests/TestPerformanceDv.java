package org.openhome.net.device.tests;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.openhome.net.core.InitParams;
import org.openhome.net.core.Library;

public class TestPerformanceDv {
	
	public static void main(String[] args) throws IOException
    {
        System.out.println("TestPerformanceDvJava - starting ('q' to quit)");
        InitParams initParams = new InitParams();
        Library lib = Library.create(initParams);
        lib.startDv();
        DeviceBasic device = new DeviceBasic();
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        try
        {
        	while(in.read() != 'q') ;
        }
        catch (IOException io)
        {
        	System.err.println("ERROR: Exiting abnormally");
        }
        device.dispose();
    }
}
