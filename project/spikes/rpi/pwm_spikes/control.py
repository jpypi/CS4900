#!/usr/bin/env python

from RPi import GPIO as io
from time import sleep


def freqtimeduty(ms_time, freq_hz=50):
    return float(ms_time)/(1000.0/freq_hz)*100.0


io.setmode(io.BCM)
# Set up servo
io.setup(13, io.OUT)
io.setup(18, io.OUT)

servo = io.PWM(13, 50)
esc = io.PWM(18, 100)

# Initialize
#servo.start(2.5)
servo.start(freqtimeduty(0.5, 50))
esc.start(freqtimeduty(0.9, 100))
print("Sleeping for 5")
sleep(5)

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


esc.ChangeDutyCycle(freqtimeduty(1.2, 100))
servo.ChangeDutyCycle(freqtimeduty(2.5, 50))

sleep(2)

#for i in range(25,126):
#    f = i/10.0
#    print(f)
#    servo.ChangeDutyCycle(f)
#    sleep(0.03)

#for i in range(1140, 1500):
#    ms = i/1000.0
#    f = freqtimeduty(ms, hertz)
#    print(ms)
#    esc.ChangeDutyCycle(f)
#    sleep(0.5)

servo.stop()
esc.stop()
io.cleanup()
