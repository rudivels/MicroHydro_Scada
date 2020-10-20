import RPi.GPIO as gpio

>> pwm1.ChangeDutyCycle(30)
>>> pwm1.ChangeDutyCycle(50)
>>> 
gpio.setmode(gpio.BOARD)
gpio.setup(35,gpio.OUT)

pwm1 = gpio.PWM(35,1000)
pwm1.start(50)
pwm1.ChangeDutyCycle(1)

>>> pwm1.ChangeDutyCycle(91)
>>> pwm1.ChangeDutyCycle(1)
>>> pwm1.ChangeDutyCycle(91)
>>> pwm1.ChangeDutyCycle(51)
>>> pwm1.ChangeDutyCycle(99)
>>> pwm1.ChangeDutyCycle(50)
>>> pwm1.ChangeDutyCycle(20)
>>> pwm1.ChangeDutyCycle(1)
>>> pwm1.ChangeDutyCycle(75)

