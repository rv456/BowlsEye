from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import numpy as np

#scaleable circle widget which plots data stored in 'output.txt' as distance from centre of circle and angle


class BowlDisplay(QFrame):
  def __init__(self, parent=None,):
      super(BowlDisplay, self).__init__(parent)
      self.setFrameStyle(1)
      p=QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
      p.setHeightForWidth(True)
      self.setSizePolicy(p)
      layout = QVBoxLayout()
      self.setLayout(layout)
      self.setSizeIncrement(1,1)
      self.ang=0


  def paintEvent(self, e):
      centre=QPoint(int(self.width())/2,int(self.height())/2)
      painter = QPainter(self)

      rectangle=QRect(QPoint(0,0),QSize(self.width(),self.height()))
      line=QLineF()
      line.setP1(centre)
      line.setLength(int(self.width()/2))
      line.setAngle(self.ang)


      pen=QPen(QColor(20, 20, 20), 1, Qt.SolidLine)
      pen.setWidth(2)
      painter.setPen(pen)
      painter.drawArc(rectangle,0,360*16)
      painter.drawLine(line)

      for i in range(0,self.ang):
        point=QLineF()
        point.setP1(centre)
        d=int(self.width()/2)*(self.data[i][1])
        print(d)
        point.setLength(d)
        angle=self.data[i][0]
        point.setAngle(angle)
        print(angle)
        print(point.p2())
        painter.drawPoint(point.p2())

  def sizeHint(self):
      return QSize(401, 401)

  def HeightForWidth(self, width):
      return width



class MainWindow(QWidget):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.initUI()
        self.load_data()
        print(self.circle.data[0][1])
        print(self.circle.data[1][1])
    def initUI(self):
        self.circle=BowlDisplay()
        layout=QVBoxLayout()
        layout.addWidget(self.circle,0,Qt.AlignCenter)
        timer=QTimer(self)
        timer.timeout.connect(self.inc_ang)
        timer.start(50)

        self.setLayout(layout)

    def inc_ang(self):
        if self.circle.ang>360:
            self.circle.ang=0
        self.circle.ang=self.circle.ang+1
        self.circle.repaint()

    def load_data(self):
        self.circle.data=np.loadtxt('output.txt',delimiter=',',skiprows=2)




if __name__ == '__main__':

    import sys

    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
