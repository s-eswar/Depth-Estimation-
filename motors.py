
import RPi.GPIO as GPIO
from time import sleep


 
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False) 
Motor1A = 18
Motor1B = 23
Motor1E = 24

Motor2A = 17
Motor2B = 22
Motor2E = 4
 
GPIO.setup(Motor1A,GPIO.OUT)
GPIO.setup(Motor1B,GPIO.OUT)
GPIO.setup(Motor1E,GPIO.OUT)
 
GPIO.setup(Motor2A,GPIO.OUT)
GPIO.setup(Motor2B,GPIO.OUT)
GPIO.setup(Motor2E,GPIO.OUT)

while(1):
	k= raw_input()
	if k  	== 'w':
		print "Going Forwards"
	
		GPIO.output(Motor1A,GPIO.LOW)
		GPIO.output(Motor1B,GPIO.HIGH)
		GPIO.output(Motor1E,GPIO.HIGH)
	
		GPIO.output(Motor2A,GPIO.LOW)
		GPIO.output(Motor2B,GPIO.HIGH)
		GPIO.output(Motor2E,GPIO.HIGH) 
	
		sleep(1)
	elif k == 's':
		print "Going Backwards"	

		GPIO.output(Motor1A,GPIO.HIGH)
		GPIO.output(Motor1B,GPIO.LOW)
		GPIO.output(Motor1E,GPIO.HIGH)	

		GPIO.output(Motor2A,GPIO.HIGH)
		GPIO.output(Motor2B,GPIO.LOW)	
		GPIO.output(Motor2E,GPIO.HIGH) 

		sleep(1)
	elif k == 'd':
		print "TURN RIGHT"

		GPIO.output(Motor1A,GPIO.LOW)
		GPIO.output(Motor1B,GPIO.HIGH)
		GPIO.output(Motor1E,GPIO.HIGH)
	
		GPIO.output(Motor2A,GPIO.LOW)
		GPIO.output(Motor2B,GPIO.HIGH)
		GPIO.output(Motor2E,GPIO.LOW) 
	
		sleep(1)
	elif k == 'a':
		print "TURN LEFT"

		GPIO.output(Motor1A,GPIO.LOW)
		GPIO.output(Motor1B,GPIO.LOW)
		GPIO.output(Motor1E,GPIO.LOW)
	
		GPIO.output(Motor2A,GPIO.LOW)
		GPIO.output(Motor2B,GPIO.HIGH)
		GPIO.output(Motor2E,GPIO.HIGH) 
	
		sleep(1)
	else:
	    break
	
GPIO.output(Motor1E,GPIO.LOW)
GPIO.output(Motor2E,GPIO.LOW)

GPIO.cleanup()
