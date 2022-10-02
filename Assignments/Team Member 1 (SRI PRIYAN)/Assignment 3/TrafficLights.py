import RPi.GPIO as GPIO
import time

# Set GPIO pins
switch = 26
red = 17
yellow = 22
green = 27

# Set BroadCom Mode to use GPIO instead of normal pins
GPIO.setmode(GPIO.BCM)

GPIO.setup(switch, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Pull up mode to remove "floating" state
GPIO.setup(red, GPIO.OUT)
GPIO.setup(yellow, GPIO.OUT)
GPIO.setup(green, GPIO.OUT)  

def preiodicallyTurnOnLeds(leds: list[int], delay: int):
  for index, led in enumerate(leds):
    GPIO.output(leds[index - 1], 0) # Turn OFF Previous LED
    GPIO.output(led, 1) # Turn ON Current LED
    time.sleep(delay)

try:
  while True:
    input_state = GPIO.input(switch)
    if input_state:
       preiodicallyTurnOnLeds([red, yellow, green], 100)
    else: 
      GPIO.output(red, 0)
      GPIO.output(yellow, 0)
      GPIO.output(green, 0)
except KeyboardInterrupt:
      GPIO.cleanup() # Reset state of LED's
