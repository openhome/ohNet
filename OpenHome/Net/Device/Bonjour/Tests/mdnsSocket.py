import socket
import zeroconf as zc
data = "\x00\x00\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x09\x5f\x73\x65\x72\x76\x69\x63\x65\x73\x07\x5f\x64\x6e\x73\x2d\x73\x64\x04\x5f\x75\x64\x70\x05\x6c\x6f\x63\x61\x6c\x00\x00\xff\x00\x01\xc0\x0c\x00\x01\x00\x01\x00\x00\x00\x78\x00\x04\xc0\xa8\x01\x1d"
respond_socket = zc.new_socket( )
interfaces = zc.InterfaceChoice.All
interfaces = zc.normalize_interface_choice( interfaces, socket.AF_INET )
print interfaces
respond_socket.setsockopt( socket.IPPROTO_IP, socket.IP_MULTICAST_IF, socket.inet_aton( interfaces[0] ) )

sentBytes = respond_socket.sendto( data, 0, ( "224.0.0.251", 5353 ) )
print( "Sent %d bytes" % sentBytes )
respond_socket.close( )