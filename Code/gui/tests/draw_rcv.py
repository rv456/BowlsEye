from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import numpy as np

#scaleable circle widget which plots data stored in 'output.txt' as distance from centre of circle and angle


class BowlDisplay(QFrame):
  click=pyqtSignal()
  def __init__(self, parent=None,):
      super(BowlDisplay, self).__init__(parent)
      self.initUI()

  def initUI(self):
      self.setFrameStyle(1)
      p=QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
      p.setHeightForWidth(True)
      self.setSizePolicy(p)
      layout = QHBoxLayout()
      self.setLayout(layout)
      self.setSizeIncrement(1,1)
      self.ang=0


  def paintEvent(self, e):
      self.centre=QPoint(int(self.width())/2,int(self.height())/2)
      painter = QPainter(self)

      rectangle=QRect(QPoint(0,0),QSize(self.width(),self.height()))
      line=QLineF()
      line.setP1(self.centre)
      line.setLength(int(self.width()/2))
      line.setAngle(self.ang)


      pen=QPen(QColor(20, 20, 20), 1, Qt.SolidLine)
      pen.setWidth(2)
      painter.setPen(pen)
      painter.drawArc(rectangle,0,360*16)
      painter.drawLine(line)

      for i in range(0,self.ang):
        #calculate x,y coordinate based on input angle/distance
        point=QLineF()
        point.setP1(self.centre)
        d=int(self.width()/2)*(self.data[i][1])
        point.setLength(d)
        angle=self.data[i][0]
        point.setAngle(angle)
        #draw point
        painter.drawPoint(point.p2())

  def sizeHint(self):
      return QSize(401, 401)

  def HeightForWidth(self, width):
      return width

  def mouseReleaseEvent(self, QMouseEvent):
      print('(', QMouseEvent.x(), ', ', QMouseEvent.y(), ')')
      p2=QPoint(QMouseEvent.x(),QMouseEvent.y())
      point=QLineF()
      point.setP1(self.centre)
      point.setP2(p2)
      self.x_pos=point.angle()
      self.y_pos=point.length()
      self.click.emit()




class DataWindow(QWidget):
    def __init__(self, teeth, parent=None):
        super(DataWindow, self).__init__(parent)
        self.initUI()
        self.teeth=teeth

    def initUI(self):
        self.circle=BowlDisplay()
        self.angle=QLineEdit()
        self.distance=QLineEdit()
        label1=QLabel()
        label1.setText("Angle (deg) ")
        label1.setAlignment(Qt.AlignLeft)
        label2=QLabel()
        label2.setText("Distance (m) ")
        label2.setAlignment(Qt.AlignLeft)


        layout=QGridLayout()
        layout.addWidget(self.circle,0,0,4,4)
        layout.addWidget(label1,4,0)
        layout.addWidget(self.angle,4,1)
        layout.addWidget(label2,4,2)
        layout.addWidget(self.distance,4,3)

        #self.circle.click.connect(self.click_pos)

        #self.timer=QTimer(self)
        #self.timer.timeout.connect(self.inc_ang)

        self.setLayout(layout)

    def inc_ang(self):
        if self.circle.ang>360:
            self.circle.ang=0
        self.circle.ang=self.circle.ang+1
        self.circle.repaint()

    def load_data(self,data):
        self.circle.data=np.loadtxt('output.txt',delimiter=',',skiprows=2)

    def update(self,data_in):
        self.circle.data=self.teeth.rcv_t.rcv
        self.circle.repaint()

    def click_pos(self):
        in_a=round(self.circle.x_pos,2)
        in_d=round(self.circle.y_pos,2)
        print(str(in_a))
        self.angle.setText('{}'.format(str(in_a)))
        self.distance.setText('{}'.format(str(in_d)))



if __name__ == '__main__':

    import sys

    app = QApplication(sys.argv)
    window = DataWindow()
    window.show()
    sys.exit(app.exec_())
