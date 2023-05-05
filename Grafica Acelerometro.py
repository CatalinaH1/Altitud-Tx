import serial
import numpy as np
import matplotlib.pyplot as plt
from pylab import *
from drawnow import drawnow, figure

Acel_x = []
Acel_y = []
Acel_z = []

arduinoData = serial.Serial('COM3', 9600) 

plt.ion()
cnt=0

def makeFig():
    plt.plot(Acel_x, 'r', label='X')
    plt.plot(Acel_y, 'g', label='Y')
    plt.plot(Acel_z, 'b', label='Z')
    plt.legend(loc='upper left')

while True:
    while (arduinoData.inWaiting()==0):
        pass
    arduinoString = arduinoData.readline().decode('utf-8')
    dataArray = arduinoString.split(',')
    Acel_x.append(float(dataArray[0]))
    Acel_y.append(float(dataArray[1]))
    Acel_z.append(float(dataArray[2]))
    drawnow(makeFig)
    plt.pause(.000001)
    cnt=cnt+1
    if(cnt>50):
        Acel_x.pop(0)
        Acel_y.pop(0)
        Acel_z.pop(0)


