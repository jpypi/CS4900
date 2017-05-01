#!/usr/bin/env python
# esc.py

from RPi import GPIO as io
from time import sleep

def freqtimeduty(ms_time, freq_hz=50):
    return float(ms_time)/(1000.0/freq_hz)*100.0

io.setmode(io.BCM)
io.setup(18, io.OUT)

hertz = 100
p = io.PWM(18, hertz)

# Between 0.0 and 100.0
#p.start(4.5)
p.start(freqtimeduty(1, 100))
sleep(2)

# Control lives in 2.5% to 12.5%
# 0.5ms to 2.5ms (50hz -> 20ms periods)
# .025 to .125 * 20 -> 0.5ms to 2.5ms


# 1.2ms and .9 ms For base to arm
# x * 20 = .9
# 4.5% duty cycle @ 50hz
# 
# 1.156ms movement begins
# 1.142ms buzzing

#1.222 - 1.235


#freqtimeduty(0.9)

print("Lanuching")
p.ChangeDutyCycle(freqtimeduty(1.31, 100))
sleep(2.5)

print("Moving")
p.ChangeDutyCycle(freqtimeduty(1.284, 100))
sleep(8)

print("Reverse?")
p.ChangeDutyCycle(freqtimeduty(0.8, 100))
sleep(10)

#for i in range(1140, 1500):
#    ms = i/1000.0
#    f = freqtimeduty(ms, hertz)
#    print(ms)
#    p.ChangeDutyCycle(f)
#    sleep(0.5)

p.stop()
io.cleanup()
