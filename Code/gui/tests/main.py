import sys
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from point_clicking import DataWindow
from input_layout import input_form

class MainWindow(QWidget):
      def __init__(self, parent=None,):
          super().__init__()
          self.initUI()

      def initUI(self):
          self.sensor=DataWindow()
          self.user_in=input_form()

          self.user_in.start.clicked.connect(self.sensor.timer.start)
          self.user_in.stop.clicked.connect(self.sensor.timer.stop)

          layout=QHBoxLayout()
          layout.addWidget(self.sensor)
          layout.addStretch(1)
          layout.addWidget(self.user_in)

          self.setLayout(layout)

if __name__ == '__main__':

    import sys

    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
