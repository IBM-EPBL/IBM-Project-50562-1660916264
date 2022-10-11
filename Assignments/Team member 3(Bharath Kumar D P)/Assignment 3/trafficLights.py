import RPi.GPIO as GPIO
from time import sleep

redPin = 16
yellowPin = 17
greenPin = 18

GPIO.setmode(GPIO.BCM)

GPIO.setup(redPin, GPIO.OUT)
GPIO.setup(yellowPin, GPIO.OUT)
GPIO.setup(greenPin, GPIO.OUT)

def operateLight(pin, timer):
    GPIO.output(pin, GPIO.HIGH)
    sleep(timer)
    GPIO.output(pin, GPIO.LOW)

while True:
    operateLight(yellowPin, 20)
    operateLight(greenPin, 100)
    operateLight(redPin, 100)
   