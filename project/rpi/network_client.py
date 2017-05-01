#!/usr/bin/env python

import socket
import struct

s = socket.socket()
s.connect(("localhost", 4433))

def Send(s, state, angle, power):
    print("Sending:\n%d\n%.7f\n%.7f"%(state, angle, power))
    data = struct.pack(">iff", state, angle, power)
    s.send(data)

def GetInput(prompt):
    try:
        return float(raw_input(prompt))
    except ValueError:
        return 0.0

state = 1
angle = 0.0
power = 0.0

while True:
    r = raw_input("a,p,s> ")
    if r == "exit":
        break
    if r == "a":
        angle = GetInput("angle: ")
    if r == "p":
        power = GetInput("power: ")
    if r == "s":
        Send(s, state, angle, power)

Send(s, 2,0,0)
s.close()
