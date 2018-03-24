#!/usr/bin/env python
import time
import serial

ser = serial.Serial(
        port='/dev/ttyS0', #Replace ttyS0 with ttyAMA0 for Pi1,Pi2,Pi0
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

counter=0
##print("reached before loop")
while True:
        ##print("In loop..")
        ##data = 'abc'.encode()
        ##print("Encoded")
        ## ser.write(data)
##        ser.close();
        print("Write counter: %d "%(counter))
        time.sleep(1)
        counter += 1


