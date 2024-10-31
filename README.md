# Car Project Using Arduino

Welcome to the **Car Project Using Arduino**! In this project, we will build a simple robotic car using Arduino and program it to perform basic movements and functionalities. The car will be controlled via code, and you can extend the project with various features like obstacle avoidance, Bluetooth control, or line following.

---

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Google Docs Link](#google-docs-link)
- [Components Required](#components-required)
- [Wiring Diagram](#wiring-diagram)
- [Arduino Code](./x.cpp)
- [Installation](#installation)
- [How to Use](#how-to-use)
- [Future Improvements](#future-improvements)
- [Contributing](#contributing)
- [License](#license)

---

## Introduction

This project aims to teach you how to create a simple robotic car using an Arduino microcontroller. The car will have basic movement capabilities such as moving forward, backward, and turning left or right. This project is perfect for beginners who are interested in learning robotics, Arduino programming, and basic electronics.

---

## Features

- **Basic Movements:** Forward, backward, left, right
- **Motor Control:** Control DC motors using an L298N motor driver
- **Expandable:** Easily add features like sensors (ultrasonic, infrared), Bluetooth control, and more
- **Customizable:** Modify the code to create your own custom behavior

---

## Google Docs Link

[Project Document on Google Docs](https://docs.google.com/document/d/1o8-U-m10rtVJzTOSS3xftw8My19UU8IhWQbNSGpuQuU/edit?tab=t.0)

---

## Components Required

To build this project, you will need the following components:

1. **Arduino Uno** (or compatible board)
2. **L298N Motor Driver**
3. **DC Motors (x2)** (with wheels)
4. **Chassis** (for car body)
5. **Caster Wheel** (for balance)
6. **Battery Pack** (6-12V)
7. **Jumper Wires** (male-male, male-female)
8. **Breadboard** (optional, for wiring)
9. **Ultrasonic Sensor (optional)** (for obstacle avoidance)
10. **Bluetooth Module (optional)** (for remote control)

---

## Wiring Diagram

Below is the basic wiring diagram for the car:

1. **DC Motors**: Connect the two DC motors to the outputs of the L298N motor driver (OUT1, OUT2 for one motor, and OUT3, OUT4 for the other motor).
2. **L298N Motor Driver**: Connect the `IN1`, `IN2`, `IN3`, and `IN4` pins of the motor driver to digital pins on the Arduino (e.g., pins 9, 8, 7, and 6, respectively).
3. **Power Supply**: Connect the battery pack to the L298N motor driver (12V input and ground). Also, provide power to the Arduino (through the power jack or the VIN pin).
4. **Arduino**: Ensure that the Arduino has a common ground connection with the motor driver.

### Optional Add-ons:

- **Ultrasonic Sensor**: Connect to the Arduino’s digital pins for obstacle avoidance.
- **Bluetooth Module**: Connect to TX/RX pins for wireless control.


## Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/your-username/car-project-arduino.git
   cd car-project-arduino
   ```

2. **Install the Arduino IDE:**

   Download and install the Arduino IDE from [here](https://www.arduino.cc/en/software).

3. **Open the Code:**

   Open the Arduino code from the `src/` directory in the Arduino IDE.

4. **Upload the Code:**

   Connect your Arduino to your computer, select the appropriate board and port, and upload the code.

---

## How to Use

1. **Power the Car:** 
   Connect your battery pack to the L298N motor driver and Arduino.

2. **Test Basic Movements:** 
   Once the code is uploaded, the car will move forward for 2 seconds, backward for 2 seconds, and then stop.

3. **Customize the Movements:** 
   Modify the delays, speed, or add more functionality to the code to suit your needs.

4. **Add Sensors or Bluetooth:** 
   Add sensors like ultrasonic for obstacle detection or a Bluetooth module for remote control, and modify the code to integrate them.

---

## Future Improvements

Here are some potential improvements you can make to the car:

- **Obstacle Avoidance**: Add an ultrasonic sensor and program the car to avoid obstacles.
- **Bluetooth Control**: Use a Bluetooth module to control the car via a mobile app.
- **Line Following**: Add IR sensors to create a line-following robot.
- **Speed Control**: Use PWM (Pulse Width Modulation) to control the speed of the motors.
- **Advanced Movement Patterns**: Program the car for more complex movement patterns or autonomous navigation.

---

## Contributing

We welcome contributions to improve this project! Here’s how you can contribute:

1. Fork the repository
2. Create a new branch for your feature (`git checkout -b feature-name`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature-name`)
5. Create a pull request

---

## License

This project is licensed under the GNU 3.0 General Public License - see the [LICENSE](./LICENSE) file for details.



