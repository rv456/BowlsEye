import sys
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from draw_rcv import DataWindow
from input_layout import input_form
from pyblu_listen import *

class MainWindow(QWidget):
	def __init__(self, parent=None,):
		super().__init__()
		self.initUI() 

	def initUI(self):
		
		self.user_in=input_form()
		self.bluetooth=teeth_widget()
		self.sensor=DataWindow(self.bluetooth)

		#self.user_in.start.clicked.connect(self.sensor.timer.start)
		#self.user_in.stop.clicked.connect(self.sensor.timer.stop)

		#self.bluetooth.rcv_t.received.connect(self.sensor.update)

		vlayout=QVBoxLayout()
		vlayout.addWidget(self.bluetooth)
		vlayout.addWidget(self.user_in)
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
