from PyQt5.QtWidgets import *
from PyQt5.QtGui import*
from PyQt5.QtCore import *
import sys, random


#Unit test for drawing a circle
#paintEvent method is connected to QSlider object which controls cirlce arc

class draw(QWidget):
    def __init__(self):
        super().__init__()
        self.i=0

    def paintEvent(self,e):
        qp=QPainter()
        qp.begin(self)
        self.draw_widget(qp)
        qp.end()

    def draw_widget(self,qp):
        rectangle=QRect(QPoint(1, 20), QSize(200, 200))
        pen=QPen(QColor(20, 20, 20), 1, Qt.SolidLine)
        pen.setWidth(2)
        qp.setPen(pen)

        qp.drawArc(rectangle,0,self.i*16)


class window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.arc=draw()
        self.slider=QSlider(Qt.Horizontal,self)
        self.slider.setMaximum(360)
        self.slider.valueChanged.connect(self.drawCircle)

        layout=QVBoxLayout()
        layout.addWidget(self.arc)
        layout.stretch(1)
        layout.addWidget(self.slider)

        self.setLayout(layout)
        self.setGeometry(250,250,290,300)

    def drawCircle(self):
        self.arc.i=self.slider.value()
        self.arc.repaint()
        print(self.slider.value())



if __name__ == '__main__':

    app = QApplication(sys.argv)
    window=window()
    window.show()
    sys.exit(app.exec_())
