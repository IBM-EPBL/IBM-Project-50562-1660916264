import RPi.GPIO as GPIO
import time

LED_PIN = 24
GPIO.setmode(GPIO.BCM) 
GPIO.setup(LED_PIN, GPIO.OUT)

while True:
   GPIO.output(LED_PIN, GPIO.HIGH) # LED is in ON state
   time.sleep(2)
   GPIO.output(LED_PIN, GPIO.LOW) # LED is in OFF state
   time.sleep(2)
