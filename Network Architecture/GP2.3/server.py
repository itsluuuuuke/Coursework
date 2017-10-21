






































































import socket 
import sys
import time

HOST = ''
PORT = 8000
BUFFER = 10000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
	s.bind((socket.gethostname(),PORT))

except socket.error as msg:
	print 'Error using bind()' + str(msg[0]) + 'Message' + msg[1]
	sys.exit()

print 'Socket Bound.....'

s.listen(10) #10 connections can be kept
print 'Socket listening...'

while 1:

	(client, addr) = s.accept()
	print 'ip address of the client: ' + str(addr[0]) + ' ' + str(addr[1])
	time.sleep(5)

	while 1:
		data = client.recv(BUFFER)
		if data:
			 client.send(data)
			 print 'Got: ' + data

			 if data[0:4] == 'EXIT':
				 client.close()
				 break
s.close()
			

		
