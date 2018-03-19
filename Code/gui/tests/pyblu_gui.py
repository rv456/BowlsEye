from bluetooth import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

#GUI object to scan for available bluetooth devices, display on dropdown menu and then send hello world message

class teeth_widget(QWidget):
	def __init__(self, parent=None):
		super(teeth_widget,self).__init__(parent)
		self.initUI()

	def initUI(self):
		scan=QPushButton('Scan',self)
		scan.clicked.connect(self.blu_scan)
		self.devices=QComboBox(self)
		con=QPushButton('Connect',self)
		con.clicked.connect(self.create_server)

		layout=QGridLayout(self)
		layout.addWidget(scan,1,0)
		layout.addWidget(self.devices,2,0)
		layout.addWidget(con,2,1)
		
	
	def blu_scan(self):
		print('performing enquiry')
		self.nearby_devices=discover_devices(lookup_names=True)
		print(self.nearby_devices)
		print('found {} devices'.format(len(self.nearby_devices)))
		for name, addr in self.nearby_devices:
				print (" {} - {}".format(addr, name))
				self.devices.addItem("{} - {}".format(addr, name))

	def create_server(self):
		addr=(self.nearby_devices[0][self.devices.currentIndex()])
		self.client_socket=BluetoothSocket(RFCOMM)
		self.client_socket.connect((addr,3))
		self.client_socket.send("Hello World")
		print('finished')
		self.client_socket.close()
		
			


if __name__ == '__main__':
    
	app = QApplication(sys.argv)
	ex = teeth_widget()
	ex.show()
	sys.exit(app.exec_())
