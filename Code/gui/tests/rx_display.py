from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import numpy as np

#scaleable circle widget which plots rx stored in 'output.txt' as distance from centre of circle and angle


class BowlDisplay(QFrame):
  click=pyqtSignal()
  def __init__(self, parent=None,):
      super(BowlDisplay, self).__init__(parent)
      self.initUI()
      self.rx=list()
      self._isFinished=0

  def initUI(self):
      self.setFrameStyle(1)
      p=QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
      p.setHeightForWidth(True)
      self.setSizePolicy(p)
      layout = QHBoxLayout()
      self.setLayout(layout)
      self.setSizeIncrement(1,1)
      self.ang=0
      self.setBaseSize(200,200)


  def paintEvent(self, e):
      self.centre=QPoint(int(self.width())/2,int(self.width())/2)
      painter = QPainter(self)

      #define black pen for drawing circle and points
      pen=QPen(QColor(20, 20, 20), 1, Qt.SolidLine)
      pen.setWidth(2)
      painter.setPen(pen)


      rectangle=QRect(QPoint(0,0),QSize(self.width(),self.width()))
      painter.setBrush(QColor(34, 139, 34))
      painter.drawEllipse(rectangle)

      painter.setPen(pen)
      painter.drawArc(rectangle,0,360*16)
      line=QLineF()
      line.setP1(self.centre)
      line.setLength(int(self.width()/2))
      line.setAngle(0)
      if len(self.rx)!=0:
         line.setAngle(self.rx[-1])          
      painter.drawLine(line)

      for i in range(0,len(self.rx)):
        #calculate x,y coordinate based on input angle/distance
        point=QLineF()
        point.setP1(self.centre)
        d=int(self.width()/2)*(self.rx[i])
        point.setLength(d)
        angle=self.rx[i+1]
        point.setAngle(angle)
        #draw point
        painter.drawPoint(point.p2())
		

  def sizeHint(self):
      return QSize(300, 300)

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




class rxWindow(QWidget):
    def __init__(self, teeth, parent=None):
        super(rxWindow, self).__init__(parent)
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

        self.circle.click.connect(self.click_pos)

        self.setLayout(layout)

	
    def update(self):
        nu_rx=(self.teeth.rx[-2],self.teeth.rx[-1])
        self.circle.rx.append(nu_rx)
        

    @pyqtSlot(str)
    def parse(self, data):
        if 'complete' in data:
            self._isFinished=True
            self.teeth.terminal.insertPlainText('Scan Finished! Click on a point on the display to determine the distance!\n')
#check for dropped packets
        else:
            parse=data.split('b\'')
            parse=parse[1].rsplit('\'')
            print(parse)
            if len(parse[0])>16:
                for i in range(0,(int(len(parse[0])/8))):
                    dodge=float(parse[0][i*(8):(i*8)+7])
                    self.circle.rx.append(dodge)
    
            else:
                self.circle.rx.append(float(parse[0][0:7]))
                self.circle.rx.append(float(parse[0][8:15]))
        self.circle.repaint()
			

    def clear(self):
        self.circle.rx=list()

    def click_pos(self):
        in_a=round(self.circle.x_pos,2)
        in_d=round(self.circle.y_pos,2)
        self.angle.setText('{}'.format(str(in_a)))
        self.distance.setText('{}'.format(str(in_d)))


if __name__ == '__main__':

    import sys

    app = QApplication(sys.argv)
    window = rxWindow()
    window.show()
    sys.exit(app.exec_())
