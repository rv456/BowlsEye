from PyQt5.QtWidgets import *
from PyQt5.QtGui import*
from PyQt5.QtCore import *
import sys, random


#drawing circle with slider for control

class draw(QWidget):
    def __init__(self):
        super().__init__()
    #    def start(self):
    #        timer = QTimer()
    #        timer.timeout.connect(draw.update)
    #        timer.start(1000)

    def paintEvent(self,e):
        qp=QPainter()
        qp.begin(self)
        self.draw_widget(qp)
        qp.end()

    def draw_widget(self,qp):
        rectangle=QRect(QPoint(1, 20), QSize(200, 200))
        pen=QPen(QColor(20, 20, 20), 1, Qt.SolidLine)
        dot=QPen(QColor(20, 20, 20), 1, Qt.SolidLine)
        pen.setWidth(2)
        dot.setWidth(5)
        qp.setPen(pen)
        qp.drawArc(rectangle,0,360*16)
        qp.setPen(dot)
        #for i in range(0,self.i):
            #qp.drawPoint(random.randint(0,200),random.randint(0,200))


class window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        arc=draw()
        slider=QSlider(Qt.Horizontal,self)

        layout=QVBoxLayout()
        layout.addWidget(arc)
        layout.stretch(1)
        layout.addWidget(slider)

        self.setLayout(layout)
        self.setGeometry(250,250,290,300)



if __name__ == '__main__':

    app = QApplication(sys.argv)
    window=window()
    window.show()
    sys.exit(app.exec_())
