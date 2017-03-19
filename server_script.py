#!/usr/bin/python

import socket
import sys

server_address = ('', 5555)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(server_address)

sock.listen(1)

while True:
    print >>sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()

    try:
        print >> sys.stderr, 'client connected:', client_address

	while True:
            data = connection.recv(16)
	    print >> sys.stderr, 'received "%s"' % data

	    if data == "":
	        break



    finally:
        connection.close()