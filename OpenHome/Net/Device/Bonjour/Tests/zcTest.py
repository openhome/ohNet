# discovers all services on all devices
#from zeroconflocal import ZeroconfServiceTypes
#print('\n'.join(ZeroconfServiceTypes.find()))
#import sys
#sys.exit(23)

# browses for particular service
from six.moves import input
from zeroconflocal import ServiceBrowser, Zeroconf


class MyListener(object):

    def remove_service(self, zeroconf, type, name):
        print("Service %s removed" % (name,))

    def add_service(self, zeroconf, type, name):
        info = zeroconf.get_service_info(type, name)
        #print("Service %s added, service info: %s" % (name, info))
        if "soft" in name.lower():
            print("============= Service %s added =============" % (name))
        else:
            print("Service %s added" % (name))


zeroconf = Zeroconf()
listener = MyListener()
browser = ServiceBrowser(zeroconf, "_odp._tcp.local.", listener)
try:
    input("Press enter to exit...\n\n")
finally:
    zeroconf.close()