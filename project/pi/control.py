#!/usr/bin/env python

import sys
import socket
import struct
import signal

from RPi import GPIO as io
from time import sleep

PORT = 4433

# Set up a signal handler to exit nicely on ctrl-c
RUN = True

def sig_int(signal, frame):
    global RUN
    RUN = False

signal.signal(signal.SIGINT, sig_int)

# Initialization and setup
io.setmode(io.BCM)

io.setup(13, io.OUT)
io.setup(18, io.OUT)

servo = io.PWM(13, 50)
ESC_FREQ = 100
esc = io.PWM(18, ESC_FREQ)


# FUNCTIONS

def FreqtimeDuty(ms_time, freq_hz=50):
    return float(ms_time)/(1000.0/freq_hz)*100.0


def AngleTime(angle):
    """
    -30 to 30 -> 1.2 to 1.9
    """
    # Safety clamping to prevent servo stress
    angle = min(max(angle, -30), 30)

    start = 1.2
    stop = 1.9
    return (angle + 30) / 60.0 * (stop - start) + start


def SetSteeringAngle(angle):
    time = AngleTime(angle)
    print("Steering pulse width: %f"%time)
    duty_cycle = FreqtimeDuty(time, 50)
    servo.ChangeDutyCycle(duty_cycle)


def SetPowerPercent(pct):
    """
    0.0 to 1.0 -> 0.9 to 2.5
    """
    time = pct * 1.6 + 0.9
    duty_cycle = FreqtimeDuty(time, ESC_FREQ)
    print("Power duty cycle: %f"%duty_cycle)
    esc.ChangeDutyCycle(duty_cycle)


def exit():
    print("Cleaning up")
    servo.stop()
    esc.stop()
    io.cleanup()
    sys.exit()
    

def main():
    
    servo.start(FreqtimeDuty(AngleTime(0), 50))
    esc.start(FreqtimeDuty(0.9, ESC_FREQ))
    #esc.ChangeDutyCycle(FreqtimeDuty(0.9, 100))
    print("Letting PWM initializtion happen (3 sec)")
    sleep(3)
    
    print("Creating socket")
    s = socket.socket()
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(("", PORT))

    print("Starting server loop")
    # Listen with a queue lenght of 1
    s.listen(1)

    while RUN:
        client, client_addr = s.accept()
        print("Connection from %s"%str(client_addr))

        while RUN:
            data = client.recv(12)
            if not data:
                break
            state, angle, power = struct.unpack(">iff", data)
            print(state, angle, power)
            #servo.ChangeDutyCycle(FreqtimeDuty(angle, 50))
            SetSteeringAngle(angle)
            SetPowerPercent(power)
            if state == 2:
                print("Closing connection")
                client.close()
                break


try:
    main()
finally:
    exit()


#SetPowerPercent(0.27)
#esc.ChangeDutyCycle(FreqtimeDuty(1.31, 100))
#sleep(2)
#esc.ChangeDutyCycle(FreqtimeDuty(1, 100))

#for i in range(1140, 1500):
#    ms = i/1000.0
#    f = FreqtimeDuty(ms, hertz)
#    print(ms)
#    esc.ChangeDutyCycle(f)
#    sleep(0.5)


## SERVO
# Control lives in 2.5% to 12.5%
# 0.5ms to 2.5ms (50hz -> 20ms periods)
# .025 to .125 * 20 -> 0.5ms to 2.5ms
# Servo rate .15 sec/60deg

## ESC
# 1.2ms and .9 ms For base to arm
# x * 20 = .9
# 4.5% duty cycle @ 50hz
# 
# 1.156ms movement begins
# 1.142ms buzzing

