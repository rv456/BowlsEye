from bluetooth import *

print('performing enquiry')

nearby_devices=discover_devices(lookup_names=True)

print('found {} devices'.format(len(nearby_devices)))

for name, addr in nearby_devices:
     print (" {} - {}".format(addr, name))
