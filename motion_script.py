#!/usr/bin/python

import RPi.GPIO as GPIO
import time
import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Use server IP and port number
# (Replace SERVER IP with the IP address of the server)
client_socket.connect(('SERVER IP', 5555))

GPIO.setmode(GPIO.BCM)

# Set PIR_PIN to whatever pin your PIR output wire is connected to on your Pi
# (for me it is pin 7)
PIR_PIN = 7 
GPIO.setup(PIR_PIN, GPIO.IN)
message = "Motion detected!"

# Callback function
def MOTION(PIR_PIN):
    print message
    client_socket.send(message)

print "PIR Module Test (CTRL+C to exit)"
time.sleep(2)
print "Ready"

try:
    GPIO.add_event_detect(PIR_PIN, GPIO.RISING, callback=MOTION)
    while 1:
        time.sleep(100)

except KeyboardInterrupt:
    print " Quit"
    GPIO.cleanup()

