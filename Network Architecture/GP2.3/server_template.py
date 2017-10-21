import socket
import sys

HOST = ''  # Server Name or address. For the server, this can be empty
PORT = 8888  # Listening socket port. PORT >= 5000
BUFFER = 1000 # Reception buffer size

s = socket.XXXXXXX (socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created...'

# Bind the socket to the local port and adress 
try:
    s.bind((XXXXXXX, XXXXXXX))

# Catch exception. If any, an error will be printed out
except socket.error as msg:
    print 'Fallo en BIND. Cod. Error: ' + str(msg[0]) + ' Mensaje ' + msg[1]
    sys.exit()
print 'Socket bound...'

# Start listening 
s.listen(10)
print 'Socket listening...'

while 1:
    # Wait for clients to connect
    cliente, addr = s.XXXXXXX()
    print 'Connected with ' + addr[0] + ':' + str(addr[1])
    
    while 1:
	    # Data reception
	    data = client.XXXXXXX (XXXXXXX)
	    if data:
	        client.XXXXXXX (XXXXXXX)
	        print 'Got: ' + datos
		 # After the reception of 'EXIT' string, the connection will be closed
	        if data[0:4] == 'EXIT':
	        	client.close() 
	    		break
s.close()
