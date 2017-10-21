# -*- coding: utf-8 -*-
from socket import *
msg = "\r\n Write here the content of your electronic message"
#Mail messages must end with a line containing only the character '.'
endLine = "\r\n.\r\n"
#Mail server we are going to connect to
serverName ="correo.aut.uah.es"
serverPort = 25
#We create the socket and connect to the server
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
#220 mail10.aut.uah.es ESMTP
recv1 = clientSocket.recv(1024)
print recv1
#We first send 'HELO' and show the response
heloCommand = 'HELO aut.uah.es\r\n'
clientSocket.send(heloCommand)
recv1 = clientSocket.recv(1024)
#250 mail10.aut.uah.es
print recv1
if recv1[:3] != '250':
	print 'Expected response code not received'

mail_fromCommand = 'MAIL FROM: arqredes@aut.uah.es\r\n'
clientSocket.send(mail_fromCommand)
recv1 = clientSocket.recv(1024)
#250 
print recv1
if recv1[:3] != '250':
	print 'Expected response code not received'

rcpt_toCommand = 'RCPT TO: gibanez@aut.uah.es\r\n'
clientSocket.send(rcpt_toCommand)
recv1 = clientSocket.recv(1024)
#250 
print recv1
if recv1[:3] != '250':
	print 'Expected response code not received'

dataCommand = 'DATA\r\n'
clientSocket.send(dataCommand)
recv1 = clientSocket.recv(1024)
#354 
print recv1
if recv1[:3] != '354':
	print 'Expected response code not received'

quitCommand = 'QUIT\r\n'
clientSocket.send(quitCommand)
recv1 = clientSocket.recv(1024)
#221
print recv1
if recv1[:3] != '221':
	print 'Expected response code not received'

exit
clientSocket.close()
