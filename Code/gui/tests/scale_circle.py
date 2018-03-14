from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class BowlDisplay(QWidget):
  def __init__(self, parent=None):
      super(BowlDisplay, self).__init__(parent)
      p=QSizePolicy()
      p.setHeightForWidth(True)
      self.setSizePolicy(p)


  def paintEvent(self, e):
      side = min(self.width(), self.height())
      print(self.width())
      print(self.height())
      painter = QPainter(self)
      rectangle=QRect(QPoint(0,0),QSize(self.width(),self.height()))

      pen=QPen(QColor(20, 20, 20), 1, Qt.SolidLine)
      pen.setWidth(2)

      painter.drawArc(rectangle,0,360*16)

  def resizeEvent(self, e):
      self.setMinimumWidth(self.height())

class MainWindow(QWidget):
    def __init__(self, parent=None):


if __name__ == '__main__':

    import sys

    app = QApplication(sys.argv)
    clock = BowlDisplay()
    clock.show()
    sys.exit(app.exec_())
