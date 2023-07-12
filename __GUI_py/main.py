
# imports
import sys
import time
import serial
from threading import *
from PyQt5.QtWidgets import QMainWindow, QWidget, QApplication, QLCDNumber, QPushButton, QLabel

################################################################################################
# Import the generated UI
################################################################################################
from interface_ui import Ui_MainWindow as interface_ui

ser = serial.Serial('COM9', 9600)  # to send and recieve data through UART

# class ReadLine:
#     def __init__(self, s):
#         self.buf = bytearray()
#         self.s = s
#
#     def readline(self):
#         i = self.buf.find(b"\n")
#         if i >= 0:
#             r = self.buf[:i+1]
#             self.buf = self.buf[i+1:]
#             return r
#         while True:
#             i = max(1, min(2048, self.s.in_waiting))
#             data = self.s.read(i)
#             i = data.find(b"\n")
#             if i >= 0:
#                 r = self.buf + data[:i+1]
#                 self.buf[0:] = data[i+1:]
#                 return r
#             else:
#                 self.buf.extend(data)
class ReadLine:
    def __init__(self, s):
        self.buf = bytearray()
        self.s = s

    def readline(self):
        while True:
            i = max(1, min(2048, self.s.in_waiting))
            data = self.s.read(i)
            i = data.find(b"\n")
            if i >= 0:
                r = self.buf + data[:i+1]
                self.buf[0:] = data[i+1:]
                try:
                    # Extract the speed and distance from the received message
                    speed_str, distance_str = r.strip().decode().split("d")
                    speed = int(speed_str)
                    distance = int(distance_str)
                    return speed, distance
                except ValueError:
                    pass
            else:
                self.buf.extend(data)

rl = ReadLine(ser)

################################################################################################
# @MAIN WINDOW CLASS
################################################################################################
class MainWindow(QMainWindow, interface_ui):
    mode = 0

    def __init__(self, parent=None):
        QMainWindow.__init__(self)
        ################################################################################################
        # Setup the UI main window
        ################################################################################################
        self.setupUi(self)

        ################################################################################################
        # buttons
        ################################################################################################
        self.accel.setAutoRepeat(True)
        self.accel.setAutoRepeatDelay(1000)
        self.decl.setAutoRepeat(True)
        self.decl.setAutoRepeatDelay(1000)
        self.accel.clicked.connect(self.accell)  # button to accelerate the motor
        self.decl.clicked.connect(self.decll)  # button to deacelerate the motor
        self.ACC.clicked.connect(self.acc)  # button to activate Adabtive Cruise Control (ACC) mode
        self.NCC.clicked.connect(self.ncc)  # button to activate Normal Cruise Control (NCC) mode
        self.CC.clicked.connect(self.cc)  # button to turn off the cruise control
        self.Range1.clicked.connect(self.thread1)  # button to select range1 of distance ranges
        self.Range2.clicked.connect(self.thread2)  # button to select range2 of distance ranges
        self.Range3.clicked.connect(self.thread3)  # button to select range3 of distance ranges
        self.stop.clicked.connect(self.stopFun)  # button to stop the system

        ###ffff
        ################################################################################################
        # Show window
        ################################################################################################
        self.show()

        ##############################################################################################
        # customize Analogue Gauge Wadget
        ##############################################################################################
        self.widget.enableBarGraph = True

        self.widget.setEnableBarGraph(False)

        # set Gauge units
        self.widget.units = "m/min"

        # set minimum gaugae value
        self.widget.minValue = 0

        # set max gaugae value
        self.widget.maxValue = 50

        # set scale value
        self.widget.scalacount = 5

        ##############################################################################################
        # displaying the Analogue widget needle current value on the LCD
        ##############################################################################################
        def change(value):
            self.lcd.display(value)

        self.widget.valueChanged.connect(change)

        # select gauage theme
        self.widget.setGaugeTheme(20)  # choose number from zero to 24

        self.widget.setScalePolygonColor(
            color1="Red",
            color2="green",
            color3="white"

        )

        self.widget.setNeedleCenterColor(
            color1="white",
            color2="#2D16B3",
            color3="#green"

        )

        self.widget.setBigScaleColor("white")  # set the Big scaler color
        self.widget.setFineScaleColor("blue")  # set the small scaler color

        self.widget.setScaleValueColor(255, 255, 255, 255)
        self.widget.setDisplayValueColor(255, 255, 255, 255)

        self.widget.setNeedleColor(255, 255, 255, 255)

        self.widget.setEnableCenterPoint(True)

        self.widget.setMouseTracking(False)

        ##############################################################################

    # threads and functions of the buttons
    ##############################################################################
    def thread1(self):
        t1 = Thread(target=self.range1)
        t1.start()

    def thread2(self):
        t1 = Thread(target=self.range2)
        t1.start()

    def thread3(self):
        t1 = Thread(target=self.range3)
        t1.start()

    def thread4(self):
        t1 = Thread(target=self.stop)
        t1.start()

    def threadRead(self):
        t12 = Thread(target=self.SerUpdate)
        t12.start()

    def accell(self):
        ser.write(b"A")
        print('sent A')

    def decll(self):
        if self.mode == 2:
            self.mode = 1
            self.lineEdit_2.clear()
            self.lineEdit_2.setText('NCC')
        ser.write(b"D")
        print('sent D')

    def acc(self):
        self.lineEdit_2.setText('ACC')
        self.lineEdit_3.setText('CC ON')
        self.mode = 2
        ser.write(b"V")
        print('sent V')

    def ncc(self):
        self.lineEdit_2.setText('NCC')
        self.lineEdit_3.setText('CC ON')
        self.mode = 1
        ser.write(b"N")
        print('sent N')

    def cc(self):
        self.lineEdit_2.clear()
        self.lineEdit_3.setText('CC OFF')
        self.mode = 0
        ser.write(b"O")
        print('sent O')

    def range1(self):
        ser.write(b"C")
        print('sent C')

    def range2(self):
        ser.write(b"M")
        print('sent M')

    def range3(self):
        ser.write(b"F")
        print('sent F')

    def stopFun(self):
        self.lineEdit_2.clear()
        self.lineEdit_3.setText('CC OFF')
        ser.write(b"S")
        print('sent S')

    def SerUpdate(self):
        cnt = 0
        while True:
            speed, distance = rl.readline()
            print("Speed:", speed)
            print("Distance:", distance)

           # Speed = int(rl.readline.speed.strip())
          #  Dist =  int(rl.readline.distance.strip())
            if (distance < 20):
                speed = 0
                
            while cnt < speed :
                if (distance < 20):
                    speed = 0
                cnt += 1
                self.lcd.display(cnt)
                self.widget.updateValue(cnt)
                time.sleep(0.0000000000000000000000000000000000001)
             
            while cnt > speed :
                if (distance < 20):
                    speed = 0
                cnt -= 1
                self.lcd.display(cnt)
                self.widget.updateValue(cnt)
                time.sleep(0.0000000000000000000000000000000000001)
                
           
            self.lineEdit.setText(str(distance))
            cnt = speed

########################################################################
## EXECUTE APP
########################################################################
########################################################################
#  main function
########################################################################
if __name__ == '__main__':
    app = QApplication(sys.argv)

    window = MainWindow()  # the name of the main class
    window.show()
    window.threadRead()
    sys.exit(app.exec_())

########################################################################
## END
########################################################################
