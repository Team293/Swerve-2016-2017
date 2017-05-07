#https://www.piborg.org/joyborg

import time
import pygame
import serial
import math
      
ser = serial.Serial(            
	port='/dev/ttyUSB0',
	baudrate = 9600,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS,
	timeout=1
    )
     
'''
NOTES:


Goals:
-Take the outputs of the XboxController
-convert the output array into Vector and Angle arrays
-


Log:
-10/31 - Created the file and assigned goals
'''


Velocities=[0,0,0,0]
VelocitiesX=[0,0,0,0]
VelocitiesY=[0,0,0,0]
VelocitiesXRot=[0,0,0,0]
VelocitiesYRot=[0,0,0,0]
Angles=[0,0,0,0]
ControllerID=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]  #The Values of all of the ids in the Controller
Velocityprevious=[0,0,0,0]
Anglesprevious=[0,0,0,0]

# Setup pygame and key states
global hadEvent
global moveUp
global moveDown
global moveLeft
global moveRight
global moveQuit
hadEvent = True
moveUp = False
moveDown = False
moveLeft = False
moveRight = False
moveQuit = False
pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()
screen = pygame.display.set_mode([300,300])
pygame.display.set_caption("JoyBorg - Press [ESC] to quit")

# Function to handle pygame events
def PygameHandler(events):
	for event in events:
		if event.type ==pygame.JOYAXISMOTION:
			ControllerID[0]=joystick.get_axis(0)
			ControllerID[1]=joystick.get_axis(1)
			ControllerID[2]=joystick.get_axis(2)
			ControllerID[3]=joystick.get_axis(3)
			hadEvent=True

			
     
def Sendvalues():
	#print ("VelocitiesX and VelocitiesY")
	#print(str(VelocitiesX[0:4]))
	#print(str(VelocitiesY[0:4]))
	
	for iterators in range(0,4):
		Velocities[iterators]=int(Velocities[iterators]*100)
		Angles[iterators]=int(Angles[iterators])
	
	print ("Final Velocities:")
	print(str(Velocities[0:4]))
	print ("Final Angles:")
	print(str(Angles[0:4]))
	ser.write("!")
	for iteratorz in range(0,4):
		ser.write(str(Velocities[iteratorz])) # $VR: 0,80,80,80,80,150,150,150,150 CR,LF
		ser.write(",")
		ser.write(str(Angles[iteratorz]))										#  Start bit  device ID or all the eight values  Line Return
		if iteratorz!=3:
			ser.write(",")
	
	Velocityprevious=Velocities
	Anglesprevious=Angles
	hadEvent=False
	
	
	
try:	
	while True:
		PygameHandler(pygame.event.get())
		if hadEvent:		
			VelocitiesXRot[0]=((ControllerID[3]/1)*.707)
			VelocitiesXRot[1]=((ControllerID[3]/1)*-.707)
			VelocitiesXRot[2]=ControllerID[3]/1*.707
			VelocitiesXRot[3]=ControllerID[3]/1*-.707 
			VelocitiesYRot[0]=ControllerID[3]/1*.707 
			VelocitiesYRot[1]=ControllerID[3]/1*-.707
			VelocitiesYRot[2]=ControllerID[3]/1*(.707)
			VelocitiesYRot[3]=ControllerID[3]/1*(-.707)
			
			VelocitiesX[0]=((ControllerID[1]/1)+VelocitiesXRot[0])
			VelocitiesX[1]=((ControllerID[1]/1)+VelocitiesXRot[1])
			VelocitiesX[2]=((ControllerID[1]/1)+VelocitiesXRot[2])
			VelocitiesX[3]=((ControllerID[1]/1)+VelocitiesXRot[3])
			VelocitiesY[0]=((ControllerID[0]/1)+VelocitiesYRot[0])
			VelocitiesY[1]=((ControllerID[0]/1)+VelocitiesYRot[1])
			VelocitiesY[2]=((ControllerID[0]/1)+VelocitiesYRot[2])
			VelocitiesY[3]=((ControllerID[0]/1)+VelocitiesYRot[3])
			
			Velocities[0]=pow(VelocitiesX[0]**2+VelocitiesY[0]**2,.5)/2  #Final stuff
			Velocities[1]=pow(VelocitiesX[0]**2+VelocitiesY[0]**2,.5)/2
			Velocities[2]=pow(VelocitiesX[0]**2+VelocitiesY[0]**2,.5)/2
			Velocities[3]=pow(VelocitiesX[0]**2+VelocitiesY[0]**2,.5)/2
			
			Angles[0]=math.degrees(math.atan2(VelocitiesY[0],VelocitiesX[0]))
			Angles[1]=math.degrees(math.atan2(VelocitiesY[1],VelocitiesX[1]))
			Angles[2]=math.degrees(math.atan2(VelocitiesY[2],VelocitiesX[2]))
			Angles[3]=math.degrees(math.atan2(VelocitiesY[3],VelocitiesX[3]))
			for iterators in range(0,4):
				if (VelocitiesY[iterators]<0):  # to correct for tangent problems
					Angles[iterators]=(360+Angles[iterators])				
				
		#	for iterator in range(0,4):
		#		if (abs(Angles[iterator]-Anglesprevious[iterator])>90):
		#			Angles[iterator]=Angles[iterator]+180
		#			Velocities[iterator]=Velocities[iterator]*(-1)
					
			Sendvalues()
			time.sleep(.05)			
							
			
except KeyboardInterrupt:
	pygame.display.set_caption("JoyBorg - Press [ESC] to quit")
#Buttons on xbox controller:

#Left stick X values id0 -32767 to 32767 and down is positive

#Left stick Y =1
#Left Stick X =0

#Right stick 3=x
#Right stick 4=y
#Button A =6 
#Button X = 8
#Button Y=9
#Button B=7
#Left top trigger =10
#Right top trigger = 11
#Cross button thing =17 and gives an array
#https://github.com/team2517/2014FRC/blob/master/docs/swerveMath.pdf