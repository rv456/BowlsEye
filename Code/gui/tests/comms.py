from bluetooth import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from time import sleep

#GUI object to scan for available bluetooth devices, display on dropdown menu and then send hello world message to chosen item

class teeth_widget(QWidget):
	def __init__(self, parent=None):
		super(teeth_widget,self).__init__(parent)
		self.initUI()
		self._isConnected=0
		self.c_soc=BluetoothSocket(RFCOMM)		

	def initUI(self):
		#Initialise bluetooth scanning and server objects
		self.scan_t=tooth_scan()
		self.rcv_t=tooth_rcv()
		self.u_in=input_form()	

		#Create and connect widget to begin scanning
		scan_b=QPushButton('Device Search',self)
		scan_b.clicked.connect(self.scan_t.start)

		#Connect scanning thread signal to function to update list of available devices
		self.scan_t.finished.connect(self.scan_update)

		#Combo box for display and selection of bluetooth device, selection of device via Combobox updates self.addr variable for communication
		self.devices=QComboBox(self)
		self.devices.currentIndexChanged.connect(self.con_update)
		
		con=QPushButton('Connect',self)
		con.clicked.connect(self.connect_client)

		self.listen=QPushButton('Start Scan',self)
		self.listen.clicked.connect(self.start_signal)
	

		n_listen=QPushButton('Save Scan',self)
		n_listen.clicked.connect(self.save_rx)

		terminal=QTextEdit()
		terminal.setReadOnly(True)

		layout=QGridLayout(self)
		layout.addWidget(scan_b,1,0,1,2)
		layout.addWidget(self.devices,2,0)
		layout.addWidget(con,2,1)
		layout.addWidget(self.listen,3,0)
		layout.addWidget(n_listen,3,1)
		layout.addWidget(self.u_in,4,0,1,2)
		layout.addWidget(terminal,5,0,4,2)
		

	def scan_update(self):
		for name, addr in self.scan_t.nearby_devices:
				print (" {} - {}".format(addr, name))
				self.devices.addItem("{} - {}".format(addr, name))

	def con_update(self):
		addr=self.scan_t.nearby_devices[self.devices.currentIndex()][0]
		print(addr)
		self.com_t.update(addr)
		self.rcv_t.update(addr)

	def save_rx(self):
		file = open('rx_data.txt','w')
		for i in self.rcv_t.rx:
			file.write(self.rcv_t.rx[i])

	def connect_client(self):
		self.c_soc=BluetoothSocket(RFCOMM)	
		while (not self._isConnected):
			try:
				self.c_soc.connect(('34:C9:F0:84:27:0B', 1))
				self._isConnected = True
				#self.terminal.insertPlainText('Connected')
				self.rcv_t.start()
			except btcommon.BluetoothError as error:
				print ("Could not connect: {}, retrying...".format(error))
				self.c_soc.close()
				sleep(2)
				self.c_soc=BluetoothSocket(RFCOMM)
	

		

	def start_signal(self):
		#clear received data buffer
		self.rcv_t.rx=list()
		print('sending')
		#write scan settings to string and transmit
		out_buf='1,{},{},{}'.format(self.u_in.sr.currentText(),self.u_in.a_res.currentIndex()+1,self.u_in.max_d.currentText())
		self.c_soc.send(out_buf)
		#Begin thread for listening to received data
		


	
#Thread for scanning nearby Bluetooth devices and updating nearby devices buffer
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


#Thread for receiving angle and distance data from the RaspberryPi via Bluetooth
class tooth_rcv(QThread):
	received=pyqtSignal(str)
	def __init__(self):
		QThread.__init__(self)
		self.rx=list()
		

	def listen(self):
		print('listening')
		server_socket=BluetoothSocket( RFCOMM )
		server_socket.bind(('', 1 ))
		server_socket.listen(1)

		client_socket, addr = server_socket.accept()
		print('accepted')
		
		old_data=None
		while True:
			data=None
			data = client_socket.recv(1024)
			print(data)
			data=str(data)
			if data!=old_data:
				self.received.emit(data)
				old_data=data
				print('efosdfiuhzfouhag')
			
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
