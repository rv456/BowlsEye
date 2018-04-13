from bluetooth import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

#GUI object to scan for available bluetooth devices, display on dropdown menu and then send hello world message to chosen itemn

class teeth_widget(QWidget):
	def __init__(self, parent=None):
		super(teeth_widget,self).__init__(parent)
		self.initUI()

	def initUI(self):
		self.scan_t=tooth_scan()
		self.com_t=tooth_com()
		self.rcv_t=tooth_rcv()		

		scan_b=QPushButton('Scan',self)
		scan_b.clicked.connect(self.scan_t.start)


		self.scan_t.finished.connect(self.scan_update)

		self.devices=QComboBox(self)
		self.devices.currentIndexChanged.connect(self.con_update)
		
		con=QPushButton('Send Hello',self)
		con.clicked.connect(self.com_t.start)

		listen=QPushButton('Start Listening',self)
		listen.clicked.connect(self.rcv_t.start)

		n_listen=QPushButton('Stop Listening',self)
		n_listen.clicked.connect(self.rcv_t.quit)
		n_listen.clicked.connect(self.close_listen)

		layout=QGridLayout(self)
		layout.addWidget(scan_b,1,0)
		layout.addWidget(self.devices,2,0)
		layout.addWidget(con,2,1)
		layout.addWidget(listen,3,0)
		layout.addWidget(n_listen,3,1)

	def scan_update(self):
		for name, addr in self.scan_t.nearby_devices:
				print (" {} - {}".format(addr, name))
				self.devices.addItem("{} - {}".format(addr, name))

	def con_update(self):
		addr=self.scan_t.nearby_devices[self.devices.currentIndex()][0]
		print(addr)
		self.com_t.update(addr)
		self.rcv_t.update(addr)

	def close_listen(self):
		file = open('rcv_data.txt','w')
		for i in range (0,len(self.rcv_t.rcv)):
			file.write(self.rcv_t.rcv[i])
		


	

class tooth_scan(QThread):
	def __init__(self):
		QThread.__init__(self)
		self.nearby_devices=[['','']]
	
	def blu_scan(self):
		print('performing enquiry')
		self.nearby_devices=discover_devices(lookup_names=True)
		print(self.nearby_devices)
		print('found {} devices'.format(len(self.nearby_devices)))


	def run(self):
		self.blu_scan()



class tooth_com(QThread):
	def __init__(self):
		QThread.__init__(self)

	def update(self,addr):
		self.addr=addr

	def create_client(self):
		self.client_socket=BluetoothSocket(RFCOMM)
		self.client_socket.connect((self.addr,1))
		self.client_socket.send("Hello World")
		print('finished')
		self.client_socket.close()

	def run(self):
		self.create_client()

class tooth_rcv(QThread):
	received=pyqtSignal()
	def __init__(self):
		QThread.__init__(self)
		self.rcv=list()
		

	def update(self,addr):
		self.addr=addr

	def listen(self):
		print('listening')
		server_socket=BluetoothSocket( RFCOMM )
		i=0
		server_socket.bind(('', 1 ))
		server_socket.listen(1)

		client_socket, addr = server_socket.accept()
		print('accepted')

		while True:
			data = client_socket.recv(1024)
			parse1[i]=parse1[i].rsplit('\'',1)[0]
			parse1[i]=parse1[i].split('\\x')[0]
			parse1[i]=parse1[i].split('b\'')[1]
			parse1[i]=float(parse1[i])
			print (parse1[i])
			self.rcv.append(parse1[i])
			print ("received {}".format(data))
			self.received.emit()
			#print ("rcv buffer: {}".format(self.rcv[i]))
			i=i+1
			
	def run(self):
		self.listen()

		
			


if __name__ == '__main__':
    
	app = QApplication(sys.argv)
	ex = teeth_widget()
	ex.show()
	sys.exit(app.exec_())
