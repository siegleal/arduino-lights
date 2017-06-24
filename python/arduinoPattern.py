import sys
import struct
import telnetlib
import time

#if len(sys.argv) < 5:
#    print "Too few arguments"
#    exit(1)


hostname = "192.168.1.126"
#hostname = sys.argv[4]
tn = telnetlib.Telnet(hostname)

#redval = int(sys.argv[1], 16)
#if redval == 255:
#	redval = 254
#greenval = int(sys.argv[2], 16)
#if greenval == 255:
#	greenval = 254
#blueval = int(sys.argv[3], 16)
#if blueval == 255:
#	blueval = 254
def sendValues(redval, greenval, blueval):
    bytestring = struct.pack('!B', redval)
    bytestring += struct.pack('!B', greenval)
    bytestring += struct.pack('!B', blueval)

    tn.write(bytestring)

for r in range(0,250,25):
    for g in range(0,250, 25):
        for b in range(0,250, 25):
            sendValues(r,g,b)
            time.sleep(1)


tn.close()

