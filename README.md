# ESP32-Based Smart Autonomous Waste Collection Robot

An autonomous robot that moves forward and backward over a 1-meter path, detects waste using an ultrasonic sensor, and collects it with a servo-operated lid. Built with an ESP32 and Embedded C/C++.

## Features
- Autonomous forward and backward movement over a 1-meter path
- Object detection using an ultrasonic sensor (15 cm detection range)
- Servo-controlled lid that opens, collects waste, and closes automatically
- Motor control using an L298N motor driver
- Serial monitor status messages for debugging

## Hardware Used
- ESP32
- Ultrasonic sensor
- Servo motor (lid mechanism)
- L298N motor driver
- DC motors and chassis
- Power supply

## Software
- Embedded C/C++
- Arduino IDE
- ESP32Servo library

## How It Works
1. The robot moves forward while checking distance continuously.
2. When an object comes within 15 cm, the robot stops.
3. The servo opens the lid, waits for the waste to enter, then closes it.
4. The robot finishes the 1-meter run, then moves back to the start and repeats.

## How to Run
1. Install the ESP32Servo library in Arduino IDE.
2. Open the .ino file and select your ESP32 board and port.
3. Adjust SIDE_TIME so the robot travels about 1 meter.
4. Upload the code and power the robot.

## Author
Athisahana S, Final-year ECE, PGP College of Engineering and Technology
