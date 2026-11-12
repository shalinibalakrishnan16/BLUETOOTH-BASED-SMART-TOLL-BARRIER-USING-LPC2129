Bluetooth-Based Wireless Smart Toll Barrier using LPC2129

A low-cost wireless toll barrier built on an ARM7 LPC2149 microcontroller. An IR sensor detects a vehicle, the system alerts the operator over Bluetooth, and the operator opens or closes the gate by sending a text command from a smartphone. A servo motor lifts and lowers the barrier.

Abstract

This project uses an LPC2149 (ARM7) microcontroller with an IR sensor and a Bluetooth module to build a wireless barrier gate. When the IR sensor detects a vehicle through an external interrupt, the LCD shows a "VEHICLE FOUND" message and a request is sent to the operator's smartphone over Bluetooth. The operator replies with "OPEN" or "CLOSE", and the servo motor lifts or lowers the barrier. An LED shows the gate status. The system lets the operator control the gate from a distance and is a low-cost solution for societies, campuses and factories.

Components Used

1.Hardware Requirements

LPC2129 ARM7 Microcontroller

Bluetooth Module (HC-05 / HC-06)

Servo Motor

16×2 LCD Display

LED

External Trigger / Sensor

Power Supply

Connecting Wires

2.Software Requirements

Keil µVision IDE

Embedded C

Proteus Design Suite (for simulation, if used)

Working Principle

1.Initially, the LPC2129 microcontroller initializes UART0, LCD, PWM and external interrupt configurations.

2.When an external event occurs, EINT0 is triggered.

3.The LCD displays a detection message.

4.The system prompts the user to send a command through Bluetooth.

5.The Bluetooth module transmits the command to the LPC2129 through UART0.

6.The microcontroller receives and compares the command using the strcmp() function.

7.If the received command is OPEN, the PWM output controls the servo motor to move the barrier to the open position.

8.If the received command is CLOSE, the servo motor returns the barrier to the closed position.

9.Finally, the LCD displays the corresponding gate status.

Technical Implementation

UART Communication
UART0 is used for serial communication between the Bluetooth module and the LPC2129 microcontroller. It handles the transmission and reception of wireless control commands.

PWM Generation
PWM5 is configured on pin P0.21 to control the servo motor. The servo position is controlled by varying the PWM pulse width.

External Interrupt
External Interrupt 0 (EINT0) is configured on pin P0.16 to detect an external triggering event and initiate the gate-control operation.

LCD Interfacing
A 16×2 LCD is interfaced in 4-bit mode to display system messages and gate status.

Applications

1.Automated toll barrier systems

2.Parking management systems

3.Residential gate access control

4.Industrial entry control systems

5.Wireless access control applications

Advantages

1.Wireless gate operation

2.Reduced manual intervention

3.Simple and cost-effective control system

4.Real-time status indication

5.Accurate servo-based barrier movement
