import serial
import numpy as np
import matplotlib.pyplot as plt
from pylab import *
from drawnow import drawnow, figure


gyro_x = []
gyro_y = []
gyro_z = []
arduinoData = serial.Serial('COM3', 9600) 
plt.ion()
cnt=0
def makeFig():
    plt.plot(gyro_x, 'r', label='X')
    plt.plot(gyro_y, 'g', label='Y')
    plt.plot(gyro_z, 'b', label='Z')
    plt.legend(loc='upper left')
while True:
    while (arduinoData.inWaiting()==0):
        pass
    arduinoString = arduinoData.readline().decode('utf-8')
    dataArray = arduinoString.split(',')
    gyro_x.append(float(dataArray[0]))
    gyro_y.append(float(dataArray[1]))
    gyro_z.append(float(dataArray[2]))
    drawnow(makeFig)
    plt.pause(.000001)
    cnt=cnt+1
    if(cnt>50):
        gyro_x.pop(0)
        gyro_y.pop(0)
        gyro_z.pop(0)
