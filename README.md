# Microprocessors-Peripherals--Project

<p align=justify>The code implements a system that consists of a temperature sensor and ultrasonic distance sensor as well as several LED's and an LCD screen for output display. The code relies heavily on the usage of timers. <br></p>

### Distance
<p align=justify> For every iteration of the loop, the ultrasonic sensor checks if there are any detectable objects at a certain distance, which is a design parameter. If there are objects close to the sensor system, this distance is displayed on the LCD screen and so is the mean temperature as described below.  <br> </p>

### Temperature 
<p align=justify> The temperature is being measured iteratively (once per loop execution) and its mean value is calculated every 24 iterations. This mean value is displayed once an object comes close to the system, which is detected using the ultrasonic system. The temperature is also evaluated in terms of maximum and minimum values considered "extreme". If a temperature measurement comes above a certain level, a red LED (as in hot) is turned on, while if it lies below another pre-set level, the blue LED (as in cold) is switched on. <br></p>

### Timers
<p align=justify> The code involves an extended usage of the timer header, which means that pre-fixed amounts of time are set to pass before different processes. <br> </p>

## Library Dependencies

<p align=justify> For the code to execute properly, the user needs to include the C++ libraries listed below: <br></p>

- DHT
- NewPing
- LiquidCrystal
- Event
- Timer
- String

## Hardware

  - Arduino Uno & a compatible USB cable
  - LCD 1602 Screen
  - DHT Temperature Sensor
  - HC-SR04 Ultrasonic Sensor
  - LED's
  - Jumper Wires
  
