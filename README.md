# Piotr Lesicki 151052 - Line Follower

## General description
Line Follower - as it's name implies this robot will realise the task of following the line. 
The robot will consist of two motors, imu, line sensors (white/black color detectors), motor
encoders as well as an external data storage (flash/sd card) for data logging and of coures
it will also have an uC for general control.

## Hardware

### Motors & motor encoders
The robot will use a simple brushed motor with an extended shaft for the encoder feedback

### IMU
A six axis IMU will be used for data logging.

### line sensors
Basic refleted light detectors will be used for estimating where a black line on a white
background is.

### External data storage
A external storage in a form of a chip or a sd card will be used for logging

### uC
An STM32WB55RGVx will be used for the heart of the robot. It will also allow for a bluetooth
communication implementation to be included in the project, making the whole project smaller 
and more compact.

## Line Following task - regulator
The appropriate regulator is yet to be chosen

## Software

### RTOS 
For an easier implementation of software a fitting RTOS will be used. Azure RTOS will be used 
for that since it implements many robust sub-libraries allowing for light-weight aplications,
such as storage (file storage) drivers for external flash/sd cards or usb interfaces allowing
for on slave multiple devices implemantation and much more.
<br/> 

## Examples
- https://forbot.pl/blog/leksykon/robot-typu-linefollower
- https://www.jsumo.com/arduino-pid-based-line-follower-kit1
