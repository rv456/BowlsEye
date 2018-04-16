import sys
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from rx_display import rxWindow
from comm import *

#Main Window for BowlsEye control

class MainWindow(QWidget):
	def __init__(self, parent=None,):
		super().__init__()
		self.initUI()

	def initUI(self):

		self.user_in=input_form()
		self.bluetooth=teeth_widget()
		self.sensor=rxWindow(self.bluetooth)

		self.bluetooth.rcv_t.received.connect(self.sensor.parse)
		self.bluetooth.scan.clicked.connect(self.sensor.clear)

		vlayout=QVBoxLayout()
		vlayout.addWidget(self.bluetooth)
		buttons=QWidget()
		buttons.setLayout(vlayout)

		layout=QHBoxLayout()
		layout.addWidget(self.sensor)
		layout.addStretch(1)
		layout.addWidget(buttons)

		self.setLayout(layout)


if __name__ == '__main__':

    import sys

    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
