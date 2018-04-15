from bluetooth import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from time import sleep

#GUI object to scan for available bluetooth devices, display on dropdown menu and then send hello world message to chosen itemn

class teeth_widget(QWidget):
	def __init__(self, parent=None):
		super(teeth_widget,self).__init__(parent)
		self.initUI()
		self._isConnected=0
		self.c_soc=BluetoothSocket(RFCOMM)		

	def initUI(self):
		self.scan_t=tooth_scan()
		self.com_t=tooth_com()
		self.rcv_t=tooth_rcv()	

		self.rcv_t.start()	

		scan_b=QPushButton('Scan',self)
		scan_b.clicked.connect(self.scan_t.start)


		self.scan_t.finished.connect(self.scan_update)

		self.devices=QComboBox(self)
		self.devices.currentIndexChanged.connect(self.con_update)
		
		con=QPushButton('Connect',self)
		con.clicked.connect(self.connect_client)

		listen=QPushButton('Start Scan',self)
		listen.clicked.connect(self.start_signal)

		n_listen=QPushButton('Save Scan',self)
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
		self.rcv_t.rcv=list()
		file = open('rcv_data.txt','w')
		for i in range (0,len(self.rcv_t.rcv)):
			file.write(self.rcv_t.rcv[i])

	def connect_client(self):
		while (not self._isConnected):
			try:
				self.c_soc.connect(('34:C9:F0:84:27:0B', 1))
				self._isConnected = True
				print('Connected')
			except btcommon.BluetoothError as error:
				print ("Could not connect {}, retrying...".format(error))
				self.c_soc.close()
				self.c_soc=BluetoothSocket(RFCOMM)
				sleep(2)

		

	def start_signal(self):
		for i in range(10):
			print('sending')
			data=[88,12,341,51]
			self.c_soc.send('88,56,43,76')
		


	

class tooth_scan(QThread):
	def __init__(self):
		QThread.__init__(self)
		self.nearby_devices=[['','']]
	
	def blu_scan(self):
		self.nearby_devices=list()
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


	def run(self):
		self.connect_client()

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
			data = str(data)
			parse1=data.split('b\'')
			parse1=data.split('\'')
			parse1=float(parse1[1])
			print ('received: {}'.format(parse1))
			self.rcv.append(parse1)
			if (len(self.rcv) % 2) == 0:
				self.received.emit()
			i=i+1
			
	def run(self):
		self.listen()

		
			


if __name__ == '__main__':
    
	app = QApplication(sys.argv)
	ex = teeth_widget()
	ex.show()
	sys.exit(app.exec_())
