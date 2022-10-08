import RPi.GPIO as GPIO
from time import sleep

lightPin = 19
GPIO.setmode(GPIO.BCM)
GPIO.setup(lightPin, GPIO.OUT)

while True:
    GPIO.output(lightPin, GPIO.HIGH)
    sleep(10)

    GPIO.output(lightPin, GPIO.LOW)
    sleep(100)