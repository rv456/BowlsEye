
from PyQt5.QtCore import *
from PyQt5.QtBluetooth import *

class test(QObject):
    def __init__(self):
        self.scan()

    def scan(self):
        local=QBluetoothLocalDevice()
        if (local.isValid()):
            local.powerOn()
            localName = local.name()
            print(localName)

        self.info=QBluetoothServiceDiscoveryAgent()
        device=QBluetoothDeviceInfo()
        self.dev=QBluetoothServiceInfo()
        self.info.serviceDiscovered.connect(self.yoyo)
        self.info.finished.connect(self.finished)
        self.info.start()

    def finished(self):
        self.info.stop()
        print('Finished...')

    def yoyo(self):
        print('yoyo')

if __name__ == '__main__':

    import sys

    app = QCoreApplication(sys.argv)
    test=test()
    sys.exit(app.exec_())
