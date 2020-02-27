# dSPACE MicroAutoBox II - ECU Code

This repository contains the code running on the main ECU of a Formula Student Electric vehicle. The ECU is the [dSPACE MicroAutoBox II](https://www.dspace.com/en/pub/home/products/hw/micautob/microautobox2.cfm) from [dSPACE](https://www.dspace.com/en/pub/home.cfm). This Rapid Prototyping ECU was programmed during the 2nd year (2018-2019) of my participation in [Aristotle University Racing Team Electric - Aristurtle](aristurtle.gr) as the Low Voltage Chief Engineer and also Electrical System Officer of the Electric Vehicle.

## System Overview

The vehicle uses the **dSPACE MicroAutoBox II** as the **Main ECU** which controls the overall behavior of the vehicle. There are several other **general purpose ECUs** inside the vehicle such as in the Dashboard, Battery Management System Master, Motor Controllers & Auxiliary ones. All of them communicate directly with the **Main ECU** via CAN protocol and they **never** communicate between one another.

<img src="https://github.com/vamoirid/Battery-Management-System-LTC6811-STM32/blob/master/images/thetis.JPG">

### Code Overview

The **Main ECU** code was separated into several parts with respect to their responsibilities. The communication with the different ECUs is separated into 2 parts for each ECU, one part being the **received** messages and one part being the **transmitted** messages. All the operations regarding some internal calculations are also different blocks. All these different blocks are the following:

1. CAN Configuration
2. Dashboard CAN Rx
3. Aux CAN Rx
4. Accu CAN Rx
5. General Inputs
6. Inverter LEFT/RIGHT CAN Rx
7. Sensor Error Check
8. APPS Plausibility
9. General Operations
10. DRS
11. Cooling
12. WannabeCooling
13. Regen Handler
14. The Journey of Torque
15. Dashboard CAN Tx
16. Aux CAN Tx
17. Accu CAN Tx
18. General Outputs 
19. Inverters CAN Tx
20. Error Handler

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Overview.png">

---

#### 1. CAN Configuration

The whole car consists of 4 different CAN Channels all arriving in the **Main ECU**. The first channel is connected with the various general purpose ECUs inside the vehicle such as the Dashboard ECU, Auxiliary ECU and Steering Wheel ECU. The second channel is dedicated to the communication of the **Main ECU** with the Battery Management System Master ECU which gathers all the information about the Accumulator Container such as battery cell voltages & temperatures, HVDC Current, Voltage on the HV leads, LV DCDC voltage & temperature and many more. Finally the last 2 channels are directly connected with the LEFT/RIGHT Inverters/Motor Controllers due to the large number of variables transmitted and received from the Inverters. 

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/CAN_Configuration.png">

---

#### 2. Dashboard CAN Rx

The ECU in the dashboard of the car is an STM32 Microcontroller with a Cortex-M4 core which gathers values from various sensors in the front of the car and communicates via CAN with the **Main ECU**. These kind of information with respect to their importance for the **error-free** working of the vehicle were sent in different data rates so as not to overflow the bus and also to reduce the total load required by the ECU. Every variable is also handled in a different regarding their purpose in the operation of the Vehicle. For example, the _APPS1 Raw_ and _APPS2 Raw_ are handled with a lot more care than the _PCB Thermistor_ which just measures the temperature inside the Dashboard and we just want to see it in the Telemetry.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Dashboard_CAN_Rx.png">

---

#### 3. Aux CAN Rx

The Auxiliary ECU is the equivalent of the Dashboard ECU but for the back side of the vehicle. It accesses all the analog and digital sensors that are located in the sidepods and the back side of the vehicle, converts them to values that can be transmitted via CAN and finally adjust the frequency of each variable to be sent with respect to their role in the overall performance and safety of the Vehicle.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Aux_CAN_Rx.png">

---

#### 4. Accu CAN Rx

The BMS Master holds the information about the voltages and the temperatures of the cells inside the Accumulator Container and also some general information such as Temperature of the LV DCDC Converter, the BMS status and the HV IDC current. All these are sent via the dedicated CAN Bus channel.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Accu_CAN_Rx.png">

The exact information about each segment are the following:

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Segment.png">

---

#### 5. General Inputs

Except for all the sensors that are transmitted via CAN protocol to the ECU the are some a lot more important than others concerning the safety of the driver. These are some of the **SCSs - System Critical Signals** and this is the reason that they are directly connected to the ECU for extra safety. Such signals are the state of the Shutdown Circuit of the Vehicle, the actual power that is delivered to the Motor Controllers and finally the actual AC current that the motors draw. A custom algorithm was implemented in order to remove some offset that the sensors might have during their operation.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/General_Inputs.png">

---

#### 6. Inverters LEFT/RIGHT CAN Rx

The blocks that receive messages from the Left and Right Inverter respectively are always completely identical. The way the Inverter sends its messages is different from a common CAN message because it needs to be CANopen compatible. Each Inverter has its own TxID and RxID. Every received message needs to be decoded with the help of the [datasheet](https://www.unitek-industrie-elektronik.de/manual-can-en) in order to identify what each message represents and then how to convert the value of the message into actual valuable data.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Inverter_CAN_Rx.png">

---

#### 7. Sensor Error Check

The Formula Student Rules state that every sensor that affects somehow the Torque Reference to the Motor Controllers must be considered and treated as a SCS and thus it must undergo some safety checks before it is considered valid and reach the Motor Controllers

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Sensor_Error_Check.png">

---

#### 8. APPS Plausibility

The Formula Student Rules state that if there is more than 25% percent of the maximum Torque Reference and also the brake pedal is pushed then the Vehicle must cut off the power to the motors until the Torque Reference reaches less than 10%.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/APPS_Plausibility.png">

---

#### 9. General Operations

The are also some General Operations that **Main ECU** must undergo in order to calculate some basic general variables and also send valuable data in the Telemetry system such as Total Power or kph or total kilometers raced.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/General_Operations.png">

---

#### 10. DRS

DRS stands for Drag Reduction System and is a system controlled by the ECU. It is directly driven by the Torque Reference signals so as to work only in the straights and only when the vehicle is accelerating.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/DRS.png">

---

#### 11. Cooling

The cooling block is responsible for controlling the water pumps and also the fans which are responsible for the air flow in the radiators. The magnitude of their signals is directly controlled from telemetry from the respective signals.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Cooling.png">

---

#### 12. WannabeCooling

The WannabeCooling is the block which is responsible for controlling the fans that "cool" the Accumulator Container. It's funny name derives from the fact that in reality these fans never cooled down the batteries. On the contrary when the fans were ON the batteries were only getting hotter!

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/WannabeCooling.png">

---

#### 13. Regen Handler

This block is responsible for the Regen_Enable signal which is a signals that states if the conditions are met in order to Recuperate. This signal is then acquired by the Regen algorithm to start the procedure.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Regen_Handler.png">

---

#### 14. The Journey of Torque

This block is one of the most important blocks of code in the **Main ECU**. These are all the blocks that handle the Torque Reference signals. The upper two are responsible for the **positive** or **accelarating** Torque Reference. The first one is the Power Limiter which enables us to drive the Vehicle with the desired maximum output Power. This is really handy for the Acceleration and Endurance events. The second one is an Electronic Differential algorithm. It has a really naïve implementation because of the fact that there was no more testing time available to include even more variables. The third block is the Regenerative Braking algorithm. Just like the previous one it is extremely naïve due to lack of testing time.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/The_Journey_Of_Torque.png">

---

#### 15. Dashboard CAN Tx

Just like received messages of the **Main ECU** it also needs to transmit some messages in order to inform the driver about the state of the Vehicle. This messages are sent to the Dashboard which some of them are displayed in LEDs and some of them in the LCD of the Steering Wheel.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Dashboard_CAN_Tx.png">

---

#### 16. Aux CAN Tx

All the variables that were manipulated in the DRS, Cooling and WannabeCooling blocks are transmitted via CAN in the Auxiliary ECU and then the ECU drives the appropriate signals.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Aux_CAN_Tx.png">

---

#### 17. Accu CAN Tx

This block sends only the value "1" from the **Main ECU** to the Accumulator Container because that is how the BMS Master understands that it is in the Vehicle and not in the Charging Station.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Accu_CAN_Tx.png">

---

#### 18. General Outputs

There are some General Outputs from the **Main ECU** that were directly controlled by it and not from another ECU for safety reasons. These are the reset signals for the BMS Master during the Precharge of the High Voltage System in order to avoid errors due to EMI. The Black block with the Red letters is one of the most important signals in the car. This signals is directly connected to the Motor Controllers and enables them to deliver power to the Motors. If this signal is cut down then the Motors will immediately stop drawing power. When this signal is "HIGH" every change in the APPS pedal is going to move the Vehicle.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/General_Outputs.png">

---

#### 19. Inverters CAN Tx

The second most important block in the **Main ECU Code** is this block because is the last block before sending the CAN messages to the Motor Controllers/Inverters. The way of sending messages is complicated due to the fact that Simulink code is neither written nor executed serially thus it makes it difficult to make Initializations. Moreover the Motor Controller accepts messages in a very specific way that is explained in the [datasheet](https://www.unitek-industrie-elektronik.de/manual-can-en) which requires different modes and Less Significant Byte format. This piece of code requires extensive safety features because a wrong Torque Reference value can lead to unwanted results.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Inverters_CAN_Tx.png">

---

#### 20. Error Handler

Last but not least, the **central** and **most important** block of the ECU is the **Error Handler**. This block has multiple inputs and 2 outputs (basically one). The inputs are the state of the errors of all the CAN bus channels, transmitted and received messages, the completion of the **Start-Up Procedure** and the state of all the safety Sub-Systems. If there is no error in each one of them then the Vehicle is safe to be driven. If any of these signals has an error then the **Enable** signal is cut down and the is no power delivered to the motors. The second signal is the Buzzer which is enabled when the Start-Up Procedure is completed and then the vehicle is ready to run.

<img src="https://github.com/vamoirid/ECU_Racing_2019_dSPACE_R2017a/blob/master/dSPACE code photos/Error_Handler.png">

## Conclusion

This is a **quick summary** of how the code works and what all these different blocks are responsible for. By no means is this a **detailed analysis** of the whole code flow and how each signal is interpreted. If there are any questions about this do not hesitate to contact me!

