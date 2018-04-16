# echoserver.py
from bluetooth import *

HOST = ''          # Symbolic name
PORT = 1     # Non-privileged port

#test for receiving bluetooth data

s=BluetoothSocket( RFCOMM )


s.bind((HOST, PORT))
s.listen(1)

conn, addr = s.accept()
file=open('rcv_data_test.txt','w')
print ('Connected by {}'.format(addr))
while True:
    data = conn.recv(1024)
    print(data)
    file.write('{}\n'.format(str(data)))
    if not data: break
    conn.send(data)
file.close()
conn.close()
