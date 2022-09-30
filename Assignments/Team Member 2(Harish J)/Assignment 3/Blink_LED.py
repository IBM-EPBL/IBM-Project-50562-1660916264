import RPi.GPIO as GPIO
import time

LED_PIN = 22
GPIO.setmode(GPIO.BCM) # Set Broadcom mode to refer GPIO pin numbers
GPIO.setup(LED_PIN, GPIO.OUT) # Set state of LED to write

try:
    while True:
        GPIO.output(LED_PIN, GPIO.HIGH) # LED is in ON state
        time.sleep(2)
        GPIO.output(LED_PIN, GPIO.LOW) # LED is in OFF state
        time.sleep(2)
except KeyboardInterrupt: 
    GPIO.cleanup() # Reset state and perform cleanup 
