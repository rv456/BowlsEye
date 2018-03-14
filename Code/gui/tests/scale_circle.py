from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

#scaleable circle widget which draws line from centre point


class BowlDisplay(QFrame):
  def __init__(self, parent=None):
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

  def sizeHint(self):
      return QSize(401, 401)

  def HeightForWidth(self, width):
      return width



class MainWindow(QWidget):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.initUI()

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






if __name__ == '__main__':

    import sys

    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
