#!/usr/bin/env python

from RPi import GPIO as io
from time import sleep

def freqtimeduty(ms_time, freq_hz=50):
    return float(ms_time)/(1000.0/freq_hz)*100.0

port = 13#18

io.setmode(io.BCM)
io.setup(port, io.OUT)

p = io.PWM(port, 50)

# Between 0.0 and 100.0
#p.start(2.5)

# CENTER THE LAD
p.start(7.5)

# Control lives in 2.5% to 12.5%
# 0.5ms to 2.5ms (50hz -> 20ms periods)
# .025 to .125 * 20 -> 0.5ms to 2.5ms

# Servo rate .15 sec/60deg
sleep(3)

#for i in range(25,126):
#    f = i/10.0
#    print(f)
#    p.ChangeDutyCycle(f)
#    sleep(0.03)

p.stop()
io.cleanup()
