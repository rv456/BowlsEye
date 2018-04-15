from bluetooth import *

#Unit test to perform robust bluetooth communication with RPi

def con(c):
	chk=1
	while chk!=None:
		chk=c.connect(('34:C9:F0:84:27:0B',1))
		print(chk)
	print('Connected')
	for i in range(10):
		print('sending')
		data=[88,12,341,51]
		#for i in range(len(data)):
		c.send('88,56,43,76')
	c.close()


client_socket=BluetoothSocket(RFCOMM)
#client_socket.connect(('34:C9:F0:84:27:0B',1))
con(client_socket)

