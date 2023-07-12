# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'interfaceyQwmrv.ui'
##
## Created by: Qt User Interface Compiler version 5.15.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

from AnalogueGauageWidget import AnalogueGauageWidget


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(2381, 852)
        MainWindow.setStyleSheet(u"background-color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(135, 135, 135, 255), stop:1 rgba(173, 216, 230, 255));\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(173, 216, 230, 255), stop:1 rgba(255, 255, 255, 255));\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(173, 216, 230, 255), stop:1 rgba(255, 255, 255, 255));")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.widget = AnalogueGauageWidget(self.centralwidget)
        self.widget.setObjectName(u"widget")
        self.widget.setGeometry(QRect(130, 70, 411, 401))
        self.lcd = QLCDNumber(self.centralwidget)
        self.lcd.setObjectName(u"lcd")
        self.lcd.setGeometry(QRect(340, 530, 111, 51))
        self.lcd.setStyleSheet(u"background: #ff4b63")
        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")
        self.label.setGeometry(QRect(160, 530, 111, 51))
        font = QFont()
        font.setFamily(u"MS Shell Dlg 2")
        font.setPointSize(14)
        font.setBold(False)
        font.setItalic(False)
        font.setWeight(50)
        self.label.setFont(font)
        self.label.setStyleSheet(u"background:#b4b4b4;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)")
        self.Range3 = QPushButton(self.centralwidget)
        self.Range3.setObjectName(u"Range3")
        self.Range3.setGeometry(QRect(980, 140, 131, 51))
        self.Range3.setFont(font)
        self.Range3.setStyleSheet(u"background:#4AC752;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)")
        self.Range1 = QPushButton(self.centralwidget)
        self.Range1.setObjectName(u"Range1")
        self.Range1.setGeometry(QRect(680, 140, 131, 51))
        self.Range1.setFont(font)
        self.Range1.setStyleSheet(u"background:#fcc201;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)")
        self.label_8 = QLabel(self.centralwidget)
        self.label_8.setObjectName(u"label_8")
        self.label_8.setGeometry(QRect(990, 200, 111, 51))
        self.label_8.setFont(font)
        self.label_8.setStyleSheet(u"background:#b4b4b4;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)")
        self.label_6 = QLabel(self.centralwidget)
        self.label_6.setObjectName(u"label_6")
        self.label_6.setGeometry(QRect(690, 200, 111, 51))
        self.label_6.setFont(font)
        self.label_6.setStyleSheet(u"background:#b4b4b4;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)")
        self.Range2 = QPushButton(self.centralwidget)
        self.Range2.setObjectName(u"Range2")
        self.Range2.setGeometry(QRect(830, 140, 131, 51))
        self.Range2.setFont(font)
        self.Range2.setStyleSheet(u"background:#c8b8bc;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)")
        self.label_7 = QLabel(self.centralwidget)
        self.label_7.setObjectName(u"label_7")
        self.label_7.setGeometry(QRect(840, 200, 111, 51))
        self.label_7.setFont(font)
        self.label_7.setStyleSheet(u"background:#b4b4b4;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)")
        self.NCC = QPushButton(self.centralwidget)
        self.NCC.setObjectName(u"NCC")
        self.NCC.setGeometry(QRect(820, 450, 161, 51))
        self.NCC.setFont(font)
        self.NCC.setStyleSheet(u"background:#58b5ba;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)rgb(14, 5, 135)rgb(88, 181, 186)")
        self.accel = QPushButton(self.centralwidget)
        self.accel.setObjectName(u"accel")
        self.accel.setGeometry(QRect(690, 360, 121, 61))
        self.accel.setFont(font)
        self.accel.setStyleSheet(u"background:#b2a2ff;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)rgb(14, 5, 135)")
        self.decl = QPushButton(self.centralwidget)
        self.decl.setObjectName(u"decl")
        self.decl.setGeometry(QRect(840, 360, 121, 61))
        self.decl.setFont(font)
        self.decl.setStyleSheet(u"background:#b2a2ff;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)rgb(14, 5, 135)")
        self.stop = QPushButton(self.centralwidget)
        self.stop.setObjectName(u"stop")
        self.stop.setGeometry(QRect(670, 630, 161, 51))
        self.stop.setFont(font)
        self.stop.setStyleSheet(u"background:#ff2407;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)rgb(14, 5, 135)")
        self.CC = QPushButton(self.centralwidget)
        self.CC.setObjectName(u"CC")
        self.CC.setGeometry(QRect(920, 630, 161, 51))
        self.CC.setFont(font)
        self.CC.setStyleSheet(u"background:#ff2407;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)rgb(14, 5, 135)")
        self.ACC = QPushButton(self.centralwidget)
        self.ACC.setObjectName(u"ACC")
        self.ACC.setGeometry(QRect(990, 360, 131, 61))
        self.ACC.setFont(font)
        self.ACC.setStyleSheet(u"background:#b2a2ff;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)rgb(14, 5, 135)")
        self.label_5 = QLabel(self.centralwidget)
        self.label_5.setObjectName(u"label_5")
        self.label_5.setGeometry(QRect(1150, 530, 231, 31))
        self.label_5.setFont(font)
        self.label_5.setStyleSheet(u"background:#b4b4b4;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)")
        self.lineEdit = QLineEdit(self.centralwidget)
        self.lineEdit.setObjectName(u"lineEdit")
        self.lineEdit.setGeometry(QRect(660, 570, 151, 31))
        self.lineEdit.setStyleSheet(u"background:rgb(0, 0, 255);\n"
"font: 18pt \"MS Shell Dlg 2\";\n"
"color: white")
        self.label_4 = QLabel(self.centralwidget)
        self.label_4.setObjectName(u"label_4")
        self.label_4.setGeometry(QRect(880, 530, 231, 31))
        self.label_4.setFont(font)
        self.label_4.setStyleSheet(u"background:#b4b4b4;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)")
        self.label_3 = QLabel(self.centralwidget)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setGeometry(QRect(630, 530, 231, 31))
        self.label_3.setFont(font)
        self.label_3.setStyleSheet(u"background:#b4b4b4;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)")
        self.label_9 = QLabel(self.centralwidget)
        self.label_9.setObjectName(u"label_9")
        self.label_9.setGeometry(QRect(680, 70, 431, 51))
        self.label_9.setFont(font)
        self.label_9.setStyleSheet(u"background:#b4b4b4;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)")
        self.lineEdit_2 = QLineEdit(self.centralwidget)
        self.lineEdit_2.setObjectName(u"lineEdit_2")
        self.lineEdit_2.setGeometry(QRect(910, 570, 151, 31))
        self.lineEdit_2.setStyleSheet(u"background:rgb(0, 0, 255);\n"
"font: 18pt \"MS Shell Dlg 2\";\n"
"color: white")
        self.lineEdit_3 = QLineEdit(self.centralwidget)
        self.lineEdit_3.setObjectName(u"lineEdit_3")
        self.lineEdit_3.setGeometry(QRect(1180, 570, 151, 31))
        self.lineEdit_3.setStyleSheet(u"background:rgb(0, 0, 255);\n"
"font: 18pt \"MS Shell Dlg 2\";\n"
"color: white")
        self.label_10 = QLabel(self.centralwidget)
        self.label_10.setObjectName(u"label_10")
        self.label_10.setGeometry(QRect(690, 300, 431, 51))
        self.label_10.setFont(font)
        self.label_10.setStyleSheet(u"background:#b4b4b4;\n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"color: blackrgb(200, 184, 188)rgb(230, 230, 230)")
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\">Speed:</p></body></html>", None))
        self.Range3.setText(QCoreApplication.translate("MainWindow", u"Far", None))
        self.Range1.setText(QCoreApplication.translate("MainWindow", u"Close", None))
        self.label_8.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\">Max 120m</p></body></html>", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\">Max 60m</p></body></html>", None))
        self.Range2.setText(QCoreApplication.translate("MainWindow", u"Medium", None))
        self.label_7.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\">Max 90m</p></body></html>", None))
        self.NCC.setText(QCoreApplication.translate("MainWindow", u"NCC on", None))
        self.accel.setText(QCoreApplication.translate("MainWindow", u"ACC", None))
        self.decl.setText(QCoreApplication.translate("MainWindow", u"DEC", None))
        self.stop.setText(QCoreApplication.translate("MainWindow", u"Stop", None))
        self.CC.setText(QCoreApplication.translate("MainWindow", u"CC off", None))
        self.ACC.setText(QCoreApplication.translate("MainWindow", u"ACC on", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\">CC ON/OFF</p></body></html>", None))
        self.label_4.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\">CC Mode</p></body></html>", None))
        self.label_3.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\">Distance</p><p align=\"center\"><br/></p></body></html>", None))
        self.label_9.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\">Select Safety distance</p></body></html>", None))
        self.lineEdit_3.setText(QCoreApplication.translate("MainWindow", u"CC Off", None))
        self.label_10.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\">Adaptive Cruise Control</p></body></html>", None))
    # retranslateUi

