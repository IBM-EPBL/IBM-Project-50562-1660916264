import RPi.GPIO as GPIO
import time

# Set GPIO pins
switch = 26
red_led = 17
yellow_led = 22
green_led = 27

# Set BroadCom Mode to use GPIO instead of normal pins
GPIO.setmode(GPIO.BCM)

GPIO.setup(switch, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Pull up mode to remove "floating" state
GPIO.setup(red_led, GPIO.OUT)
GPIO.setup(yellow_led, GPIO.OUT)
GPIO.setup(green_led, GPIO.OUT)  

try:
  def operate_traffic_lights(led_1, led_2, led_3, delay):
    GPIO.output(led_1, 1) # RED ON
    time.sleep(delay)
    GPIO.output(led_1, 0) # RED OFF
    GPIO.output(led_2, 1) # YELLOW ON
    time.sleep(delay)
    GPIO.output(led_2, 0) # YELLOW OFF
    GPIO.output(led_3, 1) # GREEN ON  
    time.sleep(delay)
    GPIO.output(led_3, 0) # GREEN OFF 
 
  while True:
    input_state = GPIO.input(switch)
    if input_state:
       operate_traffic_lights(red_led, yellow_led, green_led, 2) # 2ms delay
    else: 
      GPIO.output(red_led, 0)
      GPIO.output(yellow_led, 0)
      GPIO.output(green_led, 0)
except KeyboardInterrupt:
      GPIO.cleanup() # Reset state of LED's
