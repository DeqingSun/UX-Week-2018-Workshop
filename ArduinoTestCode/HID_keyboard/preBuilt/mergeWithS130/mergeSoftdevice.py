#!/usr/bin/python
import sys
import re

if (len(sys.argv)<2):
    print "Need parameter to process hex"
    sys.exit(1)
    
fileName = sys.argv[1];
print "Process file: " + fileName
targetFile = open(fileName, "r")
targetFileContent = targetFile.read() 
targetFile.close()

softDeviceFile = open("s130_nrf51_2.0.1_softdevice.hex", "r")
softDeviceFileContent = softDeviceFile.read() 
softDeviceFile.close()

softDeviceFileContent = re.sub(r':00000001FF[\r\n]+', '', softDeviceFileContent)

if (targetFileContent.startswith(softDeviceFileContent)):
    print "Softdevice already there"
    sys.exit(1)

targetFileContent=softDeviceFileContent+targetFileContent

targetFile = open(fileName, "w")
targetFile.write(targetFileContent) 
targetFile.close()


