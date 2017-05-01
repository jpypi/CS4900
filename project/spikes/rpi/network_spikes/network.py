#!/usr/bin/env python

import socket
import struct
import signal

PORT = 4433

s = socket.socket()
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(("", PORT))

# Listen with a queue lenght of 1
s.listen(1)

# Set up a signal handler to exit nicely on ctrl-c
RUN = True
def sig_int(signal, frame):
    global RUN
    RUN = False
signal.signal(signal.SIGINT, sig_int)

print("Starting server loop")
while RUN:
    client, client_addr = s.accept()
    print("Connection from %s"%str(client_addr))

    data = client.recv(8)
    angle, power = struct.unpack(">ff", data)
    print(angle, power)
