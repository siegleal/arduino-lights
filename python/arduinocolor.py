import sys
import struct
import serial
import time

if len(sys.argv) < 4:
    print "Too few arguments"
    exit(1)

#sys.argv = ['','FF', 'DD', '99']
s = serial.Serial('COM3', baudrate=9600, timeout=10)
s.read()

redval = int(sys.argv[1], 16)
greenval = int(sys.argv[2], 16)
blueval = int(sys.argv[3], 16)

bytestring = struct.pack('!B', redval)
bytestring += struct.pack('!B', greenval)
bytestring += struct.pack('!B', blueval)

s.write(bytestring)
s.close()

