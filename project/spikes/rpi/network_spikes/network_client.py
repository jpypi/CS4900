#!/usr/bin/env python

import socket
import struct

s = socket.socket()
s.connect(("localhost", 4433))
angle = 45.0
power = 1.2345
print("Sending:\n%.7f\n%.7f"%(angle, power))

data = struct.pack(">ff", angle, power)

s.send(data)
