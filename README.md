# Autonomous Firefighter Robot

An Arduino-based autonomous robot designed to detect and extinguish fires. The robot navigates using three infrared (IR) flame sensors, drives using a 4-wheel drive system, and puts out fires using a mini water pump mounted on a sweeping servo motor.

## Features

* **Fire Detection:** Uses left, center, and right IR flame sensors to locate the direction of the fire.
* **Autonomous Navigation:** Turns automatically towards the detected flame and stops when centered.
* **Sweeping Extinguisher:** Activates a water pump and sweeps a servo-mounted nozzle back and forth to effectively extinguish the fire.

## Hardware Components

* 1x Arduino Uno (or compatible board)
* 1x L298N Motor Driver
* 4x DC Gear Motors (with chassis and wheels)
* 3x IR Flame Sensors (LM393 based)
* 1x Standard/Micro Servo Motor (for the nozzle)
* 1x Mini DC Water Pump
* 1x 9V Battery (or equivalent power supply for the motor driver)
* Jumper wires and breadboard (as needed)

## Circuit & Pin Mapping

### Sensors
* **Left Flame Sensor:** `A0`
* **Center Flame Sensor:** `A1`
* **Right Flame Sensor:** `A2`

### L298N Motor Driver
* **IN1:** `D4`
* **IN2:** `D5`
* **IN3:** `D6`
* **IN4:** `D7`

### Actuators
* **Water Pump:** `D8` (Note: Driven via a relay or transistor if it draws more current than the Arduino can provide)
* **Servo Motor (PWM):** `D10`

## Installation and Usage

1. **Wiring:** Connect all components according to the pin mapping above. Ensure your L298N motor driver is properly powered by the external battery, and that the Arduino shares a common GND with the motor driver.

2. **Software:**
   * Open the `.ino` file in the Arduino IDE.
   * Ensure you have the standard `Servo.h` library included (it comes pre-installed with the Arduino IDE).
   * Select your Arduino Uno board and the correct COM port.
   * Click **Upload**.

3. **Calibration:**
   * The IR flame sensors usually have an onboard potentiometer (a small blue box with a screw). Use a small screwdriver to adjust the sensitivity of each sensor so they don't trigger on ambient room light, but only when a flame (like a lighter) is presented nearby.

4. **Operation:**
   * Place the robot on a flat surface.
   * Power it on.
   * Present a safe test flame. The robot will turn toward the flame, stop, and activate the pump and servo sweep routine.

## Troubleshooting

* **Robot moves away from the fire:** Reverse the motor wires on the L298N driver, or swap `HIGH` and `LOW` in the directional functions in the code.
* **Pump turns on when there is no fire:** Your sensors might have inverted logic. Change `const int FIRE_DETECTED = LOW;` to `HIGH` in the code.
* **Sensors constantly triggered:** Adjust the potentiometers on the sensor modules to lower their sensitivity.
