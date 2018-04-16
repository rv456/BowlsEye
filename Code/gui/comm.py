from bluetooth import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from time import sleep

#GUI object to scan for available bluetooth devices, display on dropdown menu and then send hello world message to chosen item

class teeth_widget(QWidget):
	def __init__(self, parent=None):
		super(teeth_widget,self).__init__(parent)
		self.c_soc=BluetoothSocket(RFCOMM)	
		self.initUI()
	

	def initUI(self):
		################Create UI objects
		self.u_in=input_form()	
		scan_b=QPushButton('Device Search',self)
		self.devices=QComboBox(self)
		con=QPushButton('Connect',self)
		self.scan=QPushButton('Start Scan',self)
		save=QPushButton('Save Scan',self)
		self.terminal=QTextEdit()
		self.terminal.setReadOnly(True)


		#####################Create instances of communication threads
		self.scan_t=tooth_scan(self.terminal)
		self.rcv_t=tooth_rcv(self.terminal)
		self.com_t=tooth_com(self.terminal)
		

		######################Connect signals to slots
		self.devices.currentIndexChanged.connect(self.con_update)
		scan_b.clicked.connect(self.scan_t.start)
		self.scan_t.finished.connect(self.scan_update)
		con.clicked.connect(self.com_t.run)
		self.scan.clicked.connect(self.start_signal)
		save.clicked.connect(self.save_rx)
		self.com_t.connected.connect(self.rcv_t.start)


		#########################Define widget layout
		layout=QGridLayout(self)
		layout.addWidget(scan_b,1,0,1,2)
		layout.addWidget(self.devices,2,0)
		layout.addWidget(con,2,1)
		layout.addWidget(self.scan,3,0)
		layout.addWidget(save,3,1)
		layout.addWidget(self.u_in,4,0,1,2)
		layout.addWidget(self.terminal,5,0,4,2)
		

	def scan_update(self):
		for name, addr in self.scan_t.nearby_devices:
				self.devices.addItem("{} - {}".format(addr, name))

	def con_update(self):
		device=self.scan_t.nearby_devices[self.devices.currentIndex()][0]
		self.com_t.update(device)

	def save_rx(self):
		file = open('rx_data.txt','w')
		for i in self.rcv_t.rx:
			file.write(self.rcv_t.rx[i])
		

	def start_signal(self):
		if self.com_t._isConnected!=True:
			self.terminal.insertPlainText('Please connect to the Pi before sending the start signal!\n')
		else:
			#clear received data buffer
			self.terminal.insertPlainText('Beginning scan process...\n')
			#write scan settings to string and transmit
			out_buf='1,{},{},{}'.format(self.u_in.sr.currentText(),self.u_in.a_res.currentIndex()+1,self.u_in.max_d.currentText())
			self.com_t.c_soc.send(out_buf)
			#Begin thread for listening to received data
		


	
#Thread for scanning nearby Bluetooth devices and updating nearby devices buffer
class tooth_scan(QThread):
	def __init__(self,terminal):
		QThread.__init__(self)
		self.nearby_devices=[['','']]
		self.terminal=terminal
	
	def blu_scan(self):
		self.nearby_devices=list()
	#	self.terminal.insertPlainText('Performing device search...\n')
		self.nearby_devices=discover_devices(lookup_names=True)
		#self.terminal.insertPlainText('Found {} devices!\n'.format(len(self.nearby_devices)))


	def run(self):
		self.blu_scan()

#Thread for creating client socket to RPi
class tooth_com(QThread):
	connected=pyqtSignal()
	def __init__(self,terminal):
			QThread.__init__(self,terminal)
			self._isConnected=0
			self.terminal=terminal
			self.device='B8:27:EB:7F:72:74'

	def update(self,device):
		self.device='B8:27:EB:7F:72:74'

	def connect_client(self):
		if self.device==None:
			self.terminal.insertPlainText('No device selected, try searching for one...\n')
		else:
			self._isConnected=0
			self.c_soc=BluetoothSocket(RFCOMM)
			self.terminal.insertPlainText('Connecting to {}...\n'.format(self.device))
			i=0	
			while (not self._isConnected) and i<10:
				try:
					self.c_soc.connect((self.device, 1))
					self._isConnected = True
					self.terminal.insertPlainText('Connected!\n')
					self.connected.emit()
				except btcommon.BluetoothError as error:
					self.terminal.insertPlainText ("Could not connect: retrying...\n".format(error))
					i=i+1
					self.c_soc.close()
					self.c_soc=BluetoothSocket(RFCOMM)
					sleep(1)
			if i==10:
				self.terminal.insertPlainText("Failed after 10 attempts, retry if you want!\n")


	def run(self):
		self.connect_client()

#Thread for receiving angle and distance data from the RaspberryPi via Bluetooth
class tooth_rcv(QThread):
	received=pyqtSignal(str)
	def __init__(self,terminal):
		QThread.__init__(self)
		self.rx=list()
		self.terminal=terminal
		

	def listen(self):
		server_socket=BluetoothSocket( RFCOMM )
		server_socket.bind(('', 1 ))
		server_socket.listen(1)

		client_socket, addr = server_socket.accept()
		self.terminal.insertPlainText('Receiving data...\n')
		
		old_data=None
		while True:
			data=None
			data = client_socket.recv(1024)
			data=str(data)
			if data!=old_data:
				self.received.emit(data)
				old_data=data
			
	def run(self):
		self.listen()

#Widget for user input of scan parameters
class input_form(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        #Labels for input boxes
        label1=QLabel()
        label1.setText("Sample Rate (kHz)")
        label1.setAlignment(Qt.AlignLeft)
        label2=QLabel()
        label2.setText("Angular Step Size (deg)")
        label2.setAlignment(Qt.AlignLeft)
        label3=QLabel()
        label3.setText("Maximum Distance (cm)")
        label3.setAlignment(Qt.AlignLeft)

        #Integer inputs for scan settings
        self.sr=QComboBox()
        self.a_res=QComboBox()
        self.max_d=QComboBox()

		#adding options for user input
        for i in range(500,1050,50):
            self.sr.addItem(str(i))

        for i in range(1,11):
            self.a_res.addItem(str(0.9*i))

        for i in range(50,105,5):
            self.max_d.addItem(str(i))


        #adding buttons to grid layout
        form=QFormLayout()
        form.addRow(label1,self.sr)
        form.addRow(label2,self.a_res)
        form.addRow(label3,self.max_d)

        self.setLayout(form)


		
			


if __name__ == '__main__':
    
	app = QApplication(sys.argv)
	ex = teeth_widget()
	ex.show()
	sys.exit(app.exec_())
