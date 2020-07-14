#!/usr/bin/env python
#==============================================================================
#TITLE           :PowerSupply_Rev01.py
#DESCRIPTION     :This module offers a UI for the PI3 - POWER SUPPLY
#AUTHOR          :Alex Riviello
#DATE            :2017-12-03
#VERSION         :1.0
#NOTES           :
#PYTHON_VERSION  :2.7.11 
#==============================================================================
import sys
from PyQt4 import QtGui, QtCore
from hc import Aardvark # TODO: Add hc file (missing from project)
import time

ICON_RED_LED = "icons/led-red-on.png"
ICON_GREEN_LED = "icons/green-led-on.png"
SYMBOL_WIRE_BASIC = "symbols/wire_basic.png"
SYMBOL_WIRE_PLUS = "symbols/wire_plus_red.png"
SYMBOL_WIRE_NEG = "symbols/wire_minus_red.png"
SYMBOL_POLY = "symbols/poly_logo.png"

class Window(QtGui.QMainWindow):

    def __init__(self):
        #Main Window Setup
        super(Window, self).__init__()
        self.setGeometry(50, 50, 1000, 550)
        self.setWindowTitle("Power Supply PI3")
        self.mainLayout = QtGui.QWidget()
        self.setCentralWidget(self.mainLayout)

        #Creating Aardvark
        self.aa = Aardvark(0)
        
        #Menu Bar Setup
        exitProgram = QtGui.QAction("&Exit", self)
        exitProgram.setShortcut("Ctrl+Q")
        exitProgram.setStatusTip("Closes the application.")
        exitProgram.triggered.connect(self.close_application)
        
        mainMenu = self.menuBar()
        fileMenu = mainMenu.addMenu('&File')
        fileMenu.addAction(exitProgram)

        self.mainPage()

        #Status read or stop + Qtimer
        self.connect_sys = False
        self.vin_pos = 1.26
        self.vin_neg = 1.27
        self.device_add = 0x6B
        
        self.timer = QtCore.QTimer()
        self.timer.setSingleShot(False)
        self.timer.setInterval(100)
        self.timer.timeout.connect(self.update_info) 
        self.timer.start()
        
        #Home method
        self.home()

    def mainPage(self):
        #LEDs
        self.redLED = QtGui.QPixmap(ICON_RED_LED)
        self.greenLED = QtGui.QPixmap(ICON_GREEN_LED)

        hbox_Load = QtGui.QHBoxLayout()
        self.btn_Load = QtGui.QPushButton("Connect")
        self.btn_Load.setMinimumHeight(80)
        self.btn_Load.setMinimumWidth(160)
        self.btn_Load.clicked.connect(self.connect_func) #change
        self.LED_status_Load = QtGui.QLabel(self)
        self.LED_status_Load.setPixmap(self.redLED)
        self.LED_status_Load.setScaledContents(True)
        self.LED_status_Load.setFixedSize(30,30)
        self.status_Load = QtGui.QLabel(self)
        self.status_Load.setText("Disconnected.")
        hbox_Load.addWidget(self.btn_Load)
        hbox_Load.addWidget(self.LED_status_Load)
        hbox_Load.addWidget(self.status_Load)
        hbox_Load.addStretch()
        
        hbox_Vpos = QtGui.QHBoxLayout()
        self.btn_Vpos = QtGui.QPushButton("Set V+")
        self.btn_Vpos.setMinimumHeight(60)
        self.btn_Vpos.clicked.connect(self.set_Vpos_func) #change
        self.Input_Vpos = QtGui.QLineEdit(self)
        self.Input_Vpos.setValidator(QtGui.QDoubleValidator(0.99,99.99,2))
        self.Input_Vpos.setMaxLength(5)
        self.Input_Vpos.setFont(QtGui.QFont("Arial",14))
        #self.Input_Vpos.textChanged.connect(self.update_vpos)
        hbox_Vpos.addWidget(self.btn_Vpos)
        hbox_Vpos.addWidget(self.Input_Vpos)
        hbox_Vpos.addStretch()

        hbox_Vneg = QtGui.QHBoxLayout()
        self.btn_Vneg = QtGui.QPushButton("Set V-")
        self.btn_Vneg.setMinimumHeight(60)
        self.btn_Vneg.clicked.connect(self.set_Vneg_func) #change
        self.Input_Vneg = QtGui.QLineEdit(self)
        self.Input_Vneg.setValidator(QtGui.QDoubleValidator(0.99,99.99,2))
        self.Input_Vneg.setMaxLength(6)
        self.Input_Vneg.setFont(QtGui.QFont("Arial",14))
        #self.Input_Vneg.textChanged.connect(self.update_vneg)
        hbox_Vneg.addWidget(self.btn_Vneg)
        hbox_Vneg.addWidget(self.Input_Vneg)
        hbox_Vneg.addStretch()

        #Vbox1
        vbox1 = QtGui.QVBoxLayout()
        vbox1.addLayout(hbox_Load)
        vbox1.addLayout(hbox_Vpos)
        vbox1.addLayout(hbox_Vneg)
        vbox1.addStretch()

        #Vbox2
        vbox2 = QtGui.QVBoxLayout()
        label_LOGO = QtGui.QLabel()
        label_LOGO.setPixmap(QtGui.QPixmap(SYMBOL_POLY))
        label_LOGO.setScaledContents(True)
        label_LOGO.setFixedSize(400,200)
        label_LOGO.setAlignment(QtCore.Qt.AlignRight | QtCore.Qt.AlignTop)

        vbox2.addWidget(label_LOGO)
        vbox2.addStretch()

        #vbox_graphical
        BER_RES_widget = QtGui.QWidget()
        BER_RES_widget.setStyleSheet(".QWidget{background-color:white;\
                                      color:black;\
                                      border-style: solid;\
                                      border-color:black;\
                                      border-width:3px;\
                                      border-radius:10px;}")
        vbox_graphical = QtGui.QVBoxLayout(BER_RES_widget)
        
        status_Label = QtGui.QLabel()
        status_Label.setText("SUPPLY STATUS")
        status_Label.setFont(QtGui.QFont("Old Century", 14, QtGui.QFont.Bold))
        space_Label = QtGui.QLabel()
        space_Label.setText("")

        #Vplus
        self.Vplus_current = QtGui.QLabel()
        self.Vplus_current.setText("        I = 0 A")
        self.Vplus_current.setFont(QtGui.QFont("Old Century", 12, QtGui.QFont.Bold))
        self.Vplus_rail = QtGui.QLabel()
        self.Vplus_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_BASIC))
        self.Vplus_rail.setScaledContents(True)
        self.Vplus_rail.setFixedSize(200,30)
        self.Vplus_rail_volt = QtGui.QLabel()
        self.Vplus_rail_volt.setText("V+ = 0 V")
        self.Vplus_rail_volt.setFont(QtGui.QFont("Old Century", 12, QtGui.QFont.Bold))
        Vplus_box = QtGui.QHBoxLayout()
        Vplus_box.addWidget(self.Vplus_rail)
        Vplus_box.addWidget(self.Vplus_rail_volt)
        
        #Vneutral
        self.Vneutral_current = QtGui.QLabel()
        self.Vneutral_current.setText("        I = 0 A")
        self.Vneutral_current.setFont(QtGui.QFont("Old Century", 12, QtGui.QFont.Bold))
        self.Vneutral_rail = QtGui.QLabel()
        self.Vneutral_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_BASIC))
        self.Vneutral_rail.setScaledContents(True)
        self.Vneutral_rail.setFixedSize(200,30)
        self.Vneutral_rail_volt = QtGui.QLabel()
        self.Vneutral_rail_volt.setText("0 V")
        self.Vneutral_rail_volt.setFont(QtGui.QFont("Old Century", 12, QtGui.QFont.Bold))
        Vneutral_box = QtGui.QHBoxLayout()
        Vneutral_box.addWidget(self.Vneutral_rail)
        Vneutral_box.addWidget(self.Vneutral_rail_volt)

        #Vminus
        self.Vminus_current = QtGui.QLabel()
        self.Vminus_current.setText("        I = 0 A")
        self.Vminus_current.setFont(QtGui.QFont("Old Century", 12, QtGui.QFont.Bold))
        self.Vminus_rail = QtGui.QLabel()
        self.Vminus_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_BASIC))
        self.Vminus_rail.setScaledContents(True)
        self.Vminus_rail.setFixedSize(200,30)
        self.Vminus_rail_volt = QtGui.QLabel()
        self.Vminus_rail_volt.setText("V- = 0 V")
        self.Vminus_rail_volt.setFont(QtGui.QFont("Old Century", 12, QtGui.QFont.Bold))
        Vminus_box = QtGui.QHBoxLayout()
        Vminus_box.addWidget(self.Vminus_rail)
        Vminus_box.addWidget(self.Vminus_rail_volt)

        vbox_graphical.addWidget(status_Label)
        vbox_graphical.addWidget(space_Label)
        vbox_graphical.addWidget(self.Vplus_current)
        vbox_graphical.addLayout(Vplus_box)
        vbox_graphical.addWidget(self.Vneutral_current)
        vbox_graphical.addLayout(Vneutral_box)
        vbox_graphical.addWidget(self.Vminus_current)
        vbox_graphical.addLayout(Vminus_box)

        #Vbox_PowerShort
        vbox_PowerShort = QtGui.QVBoxLayout()
        self.power_label = QtGui.QLabel()
        self.space_label = QtGui.QLabel()
        self.space_label.setText("")
        self.power_label.setText("             Power: 0.00 W")
        self.power_label.setFont(QtGui.QFont("Old Century", 18, QtGui.QFont.Bold))
        self.supply_status = QtGui.QLabel()
        self.supply_status.setText("            Normal operation")
        self.supply_status.setFont(QtGui.QFont("Old Century", 18, QtGui.QFont.Bold))
        vbox_PowerShort.addWidget(self.space_label)
        vbox_PowerShort.addWidget(self.space_label)
        vbox_PowerShort.addWidget(self.space_label)
        vbox_PowerShort.addWidget(self.space_label)
        vbox_PowerShort.addWidget(self.power_label)
        vbox_PowerShort.addWidget(self.supply_status)
        vbox_PowerShort.addStretch()
        
        #Hbox1
        hbox1 = QtGui.QHBoxLayout()
        hbox1.addLayout(vbox1)
        hbox1.addLayout(vbox2)

        #Hbox2
        hbox2 = QtGui.QHBoxLayout()
        hbox2.addWidget(BER_RES_widget)
        hbox2.addLayout(vbox_PowerShort)


        #Vbox3
        vbox3 = QtGui.QVBoxLayout()
        vbox3.addLayout(hbox1)
        vbox3.addLayout(hbox2)
    
        self.mainLayout.setLayout(vbox3)    

    def home(self):
        self.show()

    def update_info(self):
        if(self.connect_sys == True):
            self.aa.i2c_write(self.device_add,[0x04])
            P_MSB = self.aa.i2c_read(self.device_add,1)[0]
            P_LSB = self.aa.i2c_read(self.device_add,1)[0]
            N_MSB = self.aa.i2c_read(self.device_add,1)[0]
            N_LSB = self.aa.i2c_read(self.device_add,1)[0]
            current_positive = (P_MSB<<8) + P_LSB
            current_negative = (N_MSB<<8) + N_LSB
            current_positive = 0.9871*((float(current_positive)/1023.0)*2.4) - 0.0026
            current_negative = 0.8808*((float(current_negative)/1023.0)*2.4) + 0.0007
            total_power = (current_positive*self.vin_pos) + (current_negative*self.vin_neg)
            current_positive = float("{0:.3f}".format(current_positive))
            current_neutral = current_positive - current_negative
            neutral_orient = False
            if(current_neutral > 0):
                neutral_orient = False #Left
            else:
                neutral_orient = True #Right
            current_neutral = float("{0:.3f}".format(abs(current_neutral)))
            current_negative = float("{0:.3f}".format(current_negative))
            total_power = float("{0:.2f}".format(total_power))

            if(current_positive > 0.01):
                self.Vplus_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_PLUS))
            else:
                self.Vplus_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_BASIC))

            if(current_neutral > 0.01):
                if(neutral_orient == False):
                    self.Vneutral_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_NEG))
                else:
                    self.Vneutral_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_PLUS))
            else:
                self.Vneutral_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_BASIC))

            if(current_negative > 0.01):
                self.Vminus_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_NEG))
            else:
                self.Vminus_rail.setPixmap(QtGui.QPixmap(SYMBOL_WIRE_BASIC))

            self.aa.i2c_write(self.device_add,[0x08])
            short_register = self.aa.i2c_read(self.device_add,1)[0]
            if(((short_register&0x01)==1) | ((short_register&0x02)==2)):
                self.supply_status.setText("             SHORT DETECTED")
                self.supply_status.setStyleSheet('color: red')
            else:
                self.supply_status.setText("            Normal operation")
                self.supply_status.setStyleSheet('color: black')
                

            
            output_pos_curr = str(current_positive)
            output_neut_curr = str(current_neutral)
            output_neg_curr = str(current_negative)
            output_total_power = str(total_power)
            output_vin_pos = str(self.vin_pos)
            output_vin_neg = str(self.vin_neg)

            self.Vplus_current.setText("        I = " + output_pos_curr + " A")
            self.Vneutral_current.setText("        I = " + output_neut_curr + " A")
            self.Vminus_current.setText("        I = " + output_neg_curr + " A")
            self.Vplus_rail_volt.setText("V+ = " + output_vin_pos + " V")
            self.Vminus_rail_volt.setText("V- = " + output_vin_neg + " V")
            self.power_label.setText("             Power: " + output_total_power + " W")

    def update_vpos(self):
        if(self.Input_Vpos.text() == ""):
            self.vin_pos = 0.0
        else:
            self.vin_pos = float(self.Input_Vpos.text())
        
    def update_vneg(self):
        if(self.Input_Vneg.text() == ""):
            self.vin_neg = 0.0
        else:
            self.vin_neg = float(self.Input_Vneg.text())
    
    def connect_func(self):
        try:
            self.aa.i2c_write(self.device_add, [0x00])
            if(self.connect_sys == False):
                self.connect_sys = True
                self.btn_Load.setText("Disconnect")
                self.status_Load.setText("Connected.")
                self.LED_status_Load.setPixmap(self.greenLED)
                self.supply_status.setText("            Normal operation")
                self.supply_status.setStyleSheet('color: black')
            else:
                self.connect_sys = False
                self.btn_Load.setText("Connect")
                self.status_Load.setText("Disconnected.")
                self.LED_status_Load.setPixmap(self.redLED)
                self.supply_status.setText("            Normal operation")
                self.supply_status.setStyleSheet('color: black')
        except:
                self.connect_sys = False
                self.btn_Load.setText("Connect")
                self.status_Load.setText("Disconnected.")
                self.LED_status_Load.setPixmap(self.redLED)
                self.supply_status.setText("         Connection problem.")
                self.supply_status.setStyleSheet('color: red')

    def set_Vpos_func(self):
        try:
            if(self.connect_sys == True):
                self.update_vpos()
                pos_volt = 175.625*self.vin_pos-221.25
                if(pos_volt<0):
                    pos_volt = 0
                    self.Input_Vpos.setText("1.26")
                    self.vin_pos = 1.26
                if(pos_volt>2047):
                    pos_volt = 2047
                    self.Input_Vpos.setText("12.91")
                    self.vin_pos = 12.91
                
                pos_volt = int(pos_volt)
                self.aa.i2c_write(self.device_add, [0x01,(pos_volt&0xFF)])
                self.aa.i2c_write(self.device_add, [0x00,(pos_volt>>8)])

        except:
            print("Problem with connection.")
            self.connect_sys = False
            self.btn_Load.setText("Connect")
            self.status_Load.setText("Disconnected.")
            self.LED_status_Load.setPixmap(self.redLED)
            self.supply_status.setText("         Connection problem.")
            self.supply_status.setStyleSheet('color: red')

    def set_Vneg_func(self):
        try:
            if(self.connect_sys == True):
                self.update_vneg()
                neg_volt = 174.875*self.vin_neg-221.75
                if(neg_volt<0):
                    neg_volt = 0
                    self.Input_Vneg.setText("1.27")
                    self.vin_neg = 1.27
                if(neg_volt>2047):
                    neg_volt = 2047
                    self.Input_Vneg.setText("12.97")
                    self.vin_neg = 12.97
                neg_volt = int(neg_volt)
                self.aa.i2c_write(self.device_add, [0x03,(neg_volt&0xFF)])
                self.aa.i2c_write(self.device_add, [0x02,(neg_volt>>8)])

        except:
            print("Problem with connection.")
            self.connect_sys = False
            self.btn_Load.setText("Connect")
            self.status_Load.setText("Disconnected.")
            self.LED_status_Load.setPixmap(self.redLED)
            self.supply_status.setText("         Connection problem.")
            self.supply_status.setStyleSheet('color: red')  

        
    def close_application(self):
        choice = QtGui.QMessageBox.question(self, 'Exit',
                "Are you sure you wish to exit this program?",
                QtGui.QMessageBox.Yes | QtGui.QMessageBox.No)
        if choice == QtGui.QMessageBox.Yes:
            sys.exit()
        else:
            pass     

    def __del__(self):
        del self.gg
        del self.aa

if __name__=='__main__':
    app = QtGui.QApplication(sys.argv)
    GUI = Window()
    sys.exit(app.exec_())
