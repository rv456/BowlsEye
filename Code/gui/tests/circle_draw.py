from PyQt5.QtWidgets import QWidget, QApplication
from PyQt5.QtGui import QPainter
from PyQt5.QtCore import Qt
import sys, random

class radar(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.full_w=500
        self.full_h=500

        self.show()
        self.circ_h=10
        self.circ_w=50
        self.circ_r=180
        self.circ_c=[self.circ_w+int(self.circ_r/2),self.circ_h+int((self.circ_r/2))]
        print(self.circ_c)

    def paintEvent(self, e):


        qp = QPainter()
        qp.begin(self)
        qp.drawEllipse(self.circ_h, self.circ_w, self.circ_r, self.circ_r)
        #qp.drawPoint(self.circ_c[1],self.circ_c[2])
        self.drawPoints(qp)
        qp.end()


    def drawPoints(self, qp):
        w=self.circ_c[0]
        h=self.circ_c[1]
        for i in range (0,60):
            qp.setPen(Qt.red)
            size = self.size()
            qp.drawPoint(h+i,w+i)




if __name__ == '__main__':

    app = QApplication(sys.argv)
    radar = radar()
    window=QWidget()
    hbox=QHBoxLayout()
    addRow(radar)
    window.setLayout(hbox)
    window.show()
    sys.exit(app.exec_())
